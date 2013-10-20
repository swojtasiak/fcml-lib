/*
 * fcml_disassembler.h
 *
 *  Created on: 08-02-2013
 *      Author: tAs
 */

#ifndef FCML_DISASSEMBLER_H_
#define FCML_DISASSEMBLER_H_

#include "fcml_errors.h"
#include "fcml_stream.h"
#include "fcml_common.h"
#include "fcml_ceh.h"
#include "fcml_asm_dialect.h"
#include "fcml_disassembler_result.h"

typedef struct fcml_st_disassembler {
} fcml_st_disassembler;

typedef struct fcml_st_disassembler_configuration {
	fcml_bool use_short_form_mnemonics;
	fcml_bool imm_extend_to_osa;
} fcml_st_disassembler_configuration;

typedef struct fcml_st_disassembler_context {
	fcml_st_disassembler *disassembler;
	fcml_st_disassembler_configuration configuration;
	fcml_en_addr_form addr_form;
	fcml_data_size address_size_attribute;
	fcml_data_size operand_size_attribute;
	fcml_ptr code_address;
	fcml_data_size code_size;
	fcml_st_instruction_pointer ip;
} fcml_st_disassembler_context;

// R,X and B are stored in 1's complement form.
#define FCML_VEX_W(x)				FCML_TP_GET_BIT(x, 7)
#define FCML_VEX_R(x)				!FCML_TP_GET_BIT(x, 7)
#define FCML_VEX_X(x)				!FCML_TP_GET_BIT(x, 6)
#define FCML_VEX_B(x)				!FCML_TP_GET_BIT(x, 5)
#define FCML_VEX_L(x)				FCML_TP_GET_BIT(x, 2)
#define FCML_VEX_MMMM(x)			( x & 0x1F )
#define FCML_VEX_VVVV(x)			( ~( ( x & 0x78 ) >> 3 ) & 0x00F )
#define FCML_VEX_PP(x)				( x & 0x03 )

fcml_ceh_error fcml_fn_disassembler_init( fcml_st_dialect_context *context, fcml_st_disassembler **disassembler );
fcml_ceh_error fcml_fn_disassemble( fcml_st_disassembler_context *context, fcml_st_disassembler_result **result );
void fcml_fn_disassemble_result_free( fcml_st_disassembler_result *result );
void fcml_fn_disassembler_free( fcml_st_disassembler *disassembler );

#endif /* FCML_DISASSEMBLER_H_ */
