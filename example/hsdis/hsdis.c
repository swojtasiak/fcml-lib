/*
 * FCML - Free Code Manipulation Library.
 * Copyright (C) 2010-2016 Slawomir Wojtasiak
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include <fcml_types.h>

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <fcml_disassembler.h>
#include <fcml_intel_dialect.h>
#include <fcml_gas_dialect.h>
#include <fcml_renderer.h>

/*
 * -XX:+UnlockDiagnosticVMOptions -XX:+PrintAssembly -XX:+LogCompilation \
 * -XX:PrintAssemblyOptions=intel,mpad=10,cpad=10,code
 */
#include "hsdis.h"

#if _M_X64 || __x86_64__
#define MACH_ARCH	"amd64"
#define ADDR_FORM	FCML_OM_64_BIT
/* 64-bit */
#else
#define MACH_ARCH	"i386"
#define ADDR_FORM	FCML_OM_32_BIT
#endif

char HELP[] = "Optional arguments:\n" \
	" code - Print machine code before mnemonic.\n" \
	" intel - Use intel dialect.\n" \
	" gas - Use GNU assembler dialect (AT&T).\n" \
	" dec - IMM and displacement as decimal values.\n" \
	" mpad=XX - Padding for mnemonic part of the instruction.\n" \
	" cpad=XX - Padding for machine code.\n" \
	" seg - Show default segment registers.\n" \
	" zeros - Show leading zeros in case of HEX values.\n" \
	"";

typedef struct hdis_config {
	fcml_bool enable_code;
	fcml_bool enable_seg;
	fcml_bool intel;
	fcml_bool dec;
	fcml_bool seg;
	fcml_bool zeros;
	fcml_uint16_t code_padding;
	fcml_uint16_t mnemonic_padding;
} hdis_config;

typedef struct hsdis_app {
	fcml_st_dialect *dialect;
	fcml_st_disassembler *disassembler;
	jvm_event_callback event_callback;
	void *printf_stream;
	jvm_printf_callback printf_callback;
	const char *options;
	hdis_config config;
} hsdis_app;

void parse_options( hsdis_app *app );
void prepare_render_config( fcml_st_render_config *config, hsdis_app *app );

void* HSDIS_CALL decode_instructions( void* start, void* end, jvm_event_callback event_callback,
        void* event_stream, jvm_printf_callback printf_callback,
        void* printf_stream, const char* options ) {

	hsdis_app app = {0};

	app.event_callback = event_callback;
	app.printf_callback = printf_callback;
	app.printf_stream = printf_stream;
	app.options = options;

	/* Parse options passed by: -XX:PrintAssemblyOptions. */
	parse_options( &app ); 

	fcml_char buffer[FCML_REND_MAX_BUFF_LEN] = {0};

	/* Current instruction pointer. */
	fcml_ip ip = (fcml_ip) start;

	intptr_t code_length = (intptr_t)end - (intptr_t)start;

#if __x86_64__ || _M_X64
	(*printf_callback)(printf_stream, "RIP: 0x%llx Code size: 0x%08x\n", (intptr_t)start, code_length );
#else
	(*printf_callback)(printf_stream, "RIP: 0x%x Code size: 0x%08x\n", (intptr_t)start, code_length );
#endif

	/* Inform internal disassembler about used architecture. */
	(*event_callback)(event_stream, "mach", (void*) MACH_ARCH);

	/* Initialize INTEL dialect. */
	fcml_ceh_error error;
	
	if( app.config.intel ) {
		error = fcml_fn_dialect_init_intel( FCML_INTEL_DIALECT_CF_DEFAULT, &(app.dialect) );
	} else {
		error = fcml_fn_dialect_init_gas( FCML_GAS_DIALECT_CF_DEFAULT, &(app.dialect) );
	}

	if( error ) {
		(*printf_callback)(printf_stream, "Fatal error: Can not initialize Intel dialect. Error code: %d", error );
		return start;
	}

	/* Initialize assembler. */
	error = fcml_fn_disassembler_init( app.dialect, &(app.disassembler) );
	if( error ) {
		(*printf_callback)(printf_stream, "Fatal error: Can not initialize disassembler. Error code: %d", error );
		fcml_fn_dialect_free( app.dialect );
		return start;
	}

	/* Prepare structures for disassembler results. */
	fcml_st_disassembler_result disassembler_result;

	fcml_fn_disassembler_result_prepare( &disassembler_result );

	fcml_bool finish = FCML_FALSE;

	/* Prepares disassembler context. */

	fcml_st_disassembler_context context = {0};
	context.configuration.short_forms = FCML_FALSE;
	context.configuration.extend_disp_to_asa = FCML_TRUE;
	context.disassembler = app.disassembler;
	context.entry_point.op_mode = ADDR_FORM;

	/* Prepares renderer configuration. */

	fcml_st_render_config config = {0};
	prepare_render_config( &config, &app ); 

	while ( ip < (fcml_ip) end ) {

		context.code = (fcml_ptr)ip;
		context.code_length = (fcml_usize)code_length;

		context.entry_point.ip = ip;

		/* Inform internal disassembler about newly assembled instruction. */
		(*event_callback)(event_stream, "insn", (void*) ip);

		error = fcml_fn_disassemble( &context, &disassembler_result );
		if( error ) {
			(*printf_callback)(printf_stream, "Fatal error: Disassembling failed with error code: %d", error );
			break;
		}

		fcml_usize code_len = disassembler_result.instruction_details.instruction_size;

		/* Skip to the next instruction. */
		ip += code_len;

		error = fcml_fn_render( app.dialect, &config, buffer, sizeof( buffer ), &disassembler_result );
		if( error ) {
			(*printf_callback)(printf_stream, "Fatal error: Rendering failed with error code: %d", error );
			break;
		}

		(*printf_callback)(printf_stream, "%s", buffer );

		/* End current instruction. */
		(*event_callback)(event_stream, "/insn", (void*) ip);

		(*printf_callback)(printf_stream, "\n");

		code_length -= code_len;

	}

	fcml_fn_disassembler_result_free( &disassembler_result );

	fcml_fn_disassembler_free( app.disassembler );

	fcml_fn_dialect_free( app.dialect );

	return (void*) ip;

}

void prepare_render_config( fcml_st_render_config *config, hsdis_app *app ) {

	config->render_flags = ( FCML_REND_FLAG_RENDER_INDIRECT_HINT | FCML_REND_FLAG_RENDER_ABS_HINT |
	        FCML_REND_FLAG_MNEMONIC_PADDING );

	/* Remove leading zeros. */
	if( !app->config.zeros ) {
		config->render_flags |= ( FCML_REND_FLAG_REMOVE_LEADING_ZEROS );
	}

	/* Decimal IMM and displacement. */
	if( !app->config.dec ) {
		config->render_flags |= ( FCML_REND_FLAG_HEX_IMM | FCML_REND_FLAG_HEX_DISPLACEMENT );
	} 

	/* Show default segment registers. */
	if( app->config.seg ) {
		config->render_flags |= FCML_REND_FLAG_RENDER_DEFAULT_SEG;
	}

	/* Enable binary code rendering. */
	if( app->config.enable_code ) {
		config->render_flags |= ( FCML_REND_FLAG_RENDER_CODE | FCML_REND_FLAG_CODE_PADDING );
		config->prefered_code_padding = app->config.code_padding ? app->config.code_padding : 10;
		config->prefered_mnemonic_padding = app->config.mnemonic_padding ? app->config.mnemonic_padding : 7;
	}
}

void parse_options( hsdis_app *app ) {

#ifdef FCML_MSCC
	/* Intel dialect by default for Microsoft compilers. */
	app->config.intel = FCML_TRUE;
#else
	/* In case of different systems AT&T dialect seems to be a good
	 * choice since it will be GNU/Linux or another Unix like system
	 * in 99%.
	 */
	app->config.intel = FCML_FALSE;
#endif

	int index = 0;

	const char *current = app->options;
	while( current ) {

		/* Skip comma. */
		if( *current == ',' ) {
			current++;
		}

		if( strncmp( current, "intel", 5 ) == 0 ) {
			app->config.intel = FCML_TRUE;
		} else if( strncmp( current, "help", 3 ) == 0 ) {
			app->printf_callback( app->printf_stream, HELP );
		} else if( strncmp( current, "gas", 3 ) == 0 ) {
			app->config.intel = FCML_FALSE;
		} else if( strncmp( current, "seg", 3 ) == 0 ) {
			app->config.seg = FCML_TRUE;
		} else if( strncmp( current, "dec", 3 ) == 0 ) {
			app->config.dec = FCML_TRUE;
		} else if( strncmp( current, "code", 4 ) == 0 ) {
			app->config.enable_code = FCML_TRUE;
		} else if( strncmp( current, "zeros", 5 ) == 0 ) {
			app->config.zeros = FCML_TRUE;
		} else if( strncmp( current, "mpad=", 5 ) == 0 ) {
			app->config.mnemonic_padding = atoi( current + 5 );
		} else if( strncmp( current, "cpad=", 5 ) == 0 ) {
			app->config.code_padding = atoi( current + 5 );
		} else {
			app->printf_callback( app->printf_stream, "Argument %d is unknown.", index );
		}

		current = strchr( current, ',' );
	}
	 
}
