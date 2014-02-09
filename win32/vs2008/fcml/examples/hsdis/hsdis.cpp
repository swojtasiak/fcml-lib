
#include "stdafx.h"

#include <fcml_disassembler.h>
#include <fcml_intel_dialect.h>
#include <fcml_renderer.h>

/*
 * -XX:+UnlockDiagnosticVMOptions -XX:+PrintAssembly -XX:+LogCompilation
 */

#include "hsdis.h"

#if __x86_64__
#define MACH_ARCH	"amd64"
#define ADDR_FORM	FCML_AF_64_BIT
/* 64-bit */
#else
#define MACH_ARCH	"i386"
#define ADDR_FORM	FCML_AF_32_BIT
#endif

fcml_st_dialect *dialect;

fcml_st_disassembler *disassembler;

#define REND_FLAGS		FCML_REND_FLAG_HEX_IMM | FCML_REND_FLAG_RENDER_CODE | FCML_REND_FLAG_RENDER_DEFAULT_SEG | FCML_REND_FLAG_RENDER_INDIRECT_HINT | FCML_REND_FLAG_CODE_PADDING | FCML_REND_FLAG_RENDER_ABS_HINT

void* HSDIS_CALL decode_instructions( void* start, void* end, jvm_event_callback event_callback, void* event_stream, jvm_printf_callback printf_callback, void* printf_stream, const char* options ) {

	fcml_char buffer[FCML_REND_MAX_BUFF_LEN] = {0};

	/* Current instruction pointer. */
	uintptr_t ip = (uintptr_t) start;

	intptr_t code_length = (intptr_t)end - (intptr_t)start;

	(*printf_callback)(printf_stream, "RIP: %ld LEN: 0x%08x\n", (intptr_t)start, code_length );

	/* Inform internal disassembler about used architecture. */
	(*event_callback)(event_stream, "mach", (void*) MACH_ARCH);

	/* Initialize INTEL dialect. */
	fcml_ceh_error error = fcml_fn_intel_dialect_init( FCML_INTEL_DIALECT_CF_DEFAULT, &dialect );
	if( error ) {
		(*printf_callback)(printf_stream, "Fatal error: Can not initialize intel dialect. Error code: %d", error );
		return start;
	}

	/* Initialize assembler. */
	error = fcml_fn_disassembler_init( dialect, &disassembler );
	if( error ) {
		(*printf_callback)(printf_stream, "Fatal error: Can not initialize disassembler. Error code: %d", error );
		fcml_fn_intel_dialect_free( dialect );
		return start;
	}

	/* Prepare structures for disassembler results. */
	fcml_st_disassembler_result disassembler_result;

	fcml_fn_disassembler_result_prepare( &disassembler_result );

	bool finish = false;

	/* Prepares disassembler context. */

	fcml_st_disassembler_context context = {0};
	context.configuration.short_forms = FCML_FALSE;
	context.configuration.extend_disp_to_asa = FCML_TRUE;
	context.disassembler = disassembler;
	context.entry_point.addr_form = ADDR_FORM;

	while ( ip < (uintptr_t) end ) {

		context.code = (fcml_ptr)ip;
		context.code_length = (fcml_data_size)code_length;

#if __x86_64__
		context.entry_point.ip.rip = (fcml_uint64_t)ip;
#else
		context.entry_point.ip.eip = (fcml_uint32_t)ip;
#endif

		/* Inform internal disassembler about newly assembled instruction. */
		(*event_callback)(event_stream, "insn", (void*) ip);

		error = fcml_fn_disassemble( &context, &disassembler_result );
		if( error ) {
			(*printf_callback)(printf_stream, "Fatal error: Disassemblation failed with error code: %d", error );
			break;
		}

		fcml_data_size code_len = disassembler_result.instruction_details.instruction_size;

		// Skip to next instruction.
		ip += code_len;

		error = fcml_fn_render( dialect, buffer, sizeof( buffer ), &disassembler_result, REND_FLAGS );
		if( error ) {
			(*printf_callback)(printf_stream, "Fatal error: Rendering failed with error code: %d", error );
			break;
		}

		(*printf_callback)(printf_stream, "%s", buffer );

		/* End current instruction. */
		(*event_callback)(event_stream, "/insn", (void*) ip);

		/* follow each complete insn by a nice newline */
		(*printf_callback)(printf_stream, "\n");

		code_length -= code_len;

	}

	fcml_fn_disassembler_result_free( &disassembler_result );

	fcml_fn_disassembler_free( disassembler );

	fcml_fn_intel_dialect_free( dialect );

	return (void*) ip;

}

