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

typedef struct fcml_st_disassembler {
} fcml_st_disassembler;

typedef struct fcml_st_disassembler_configuration {
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

/* Prefixes */

#define FCML_DASM_PREFIXES_COUNT						12

typedef enum fcml_st_dasm_prefix_types {
	FCML_PT_GROUP_UNKNOWN = 0,
	FCML_PT_GROUP_1 = 1,
	FCML_PT_GROUP_2,
	FCML_PT_GROUP_3,
	FCML_PT_GROUP_4,
	FCML_PT_REX,
	FCML_PT_VEX,
	FCML_PT_XOP,
} fcml_st_dasm_prefix_types;

// R,X and B are stored in 1's complement form.
#define FCML_VEX_W(x)				FCML_TP_GET_BIT(x, 7)
#define FCML_VEX_R(x)				!FCML_TP_GET_BIT(x, 7)
#define FCML_VEX_X(x)				!FCML_TP_GET_BIT(x, 6)
#define FCML_VEX_B(x)				!FCML_TP_GET_BIT(x, 5)
#define FCML_VEX_L(x)				FCML_TP_GET_BIT(x, 2)
#define FCML_VEX_MMMM(x)			( x & 0x1F )
#define FCML_VEX_VVVV(x)			( ~( ( x & 0x78 ) >> 3 ) & 0x00F )
#define FCML_VEX_PP(x)				( x & 0x03 )

typedef struct fcml_st_dasm_instruction_prefix {
	/* Prefix itself. */
	fcml_uint8_t prefix;
	/* Type of prefix, see enumeration above. */
	fcml_st_dasm_prefix_types prefix_type;
	/* 1 if prefix can be treated as mandatory one. */
	fcml_bool mandatory_prefix;
	/* Place for additional bytes of VEX prefix. */
	fcml_uint8_t vex_xop_bytes[2];
} fcml_st_dasm_instruction_prefix;

typedef struct fcml_st_dasm_dec_prefixes {
	fcml_st_dasm_instruction_prefix prefixes[FCML_DASM_PREFIXES_COUNT];
	fcml_int prefixes_count;
	fcml_bool is_vex;
	fcml_bool is_xop;
	fcml_bool is_rex;
	// Fields.
	fcml_uint8_t vex_xop_first_byte;
	fcml_uint8_t r;
	fcml_uint8_t x;
	fcml_uint8_t b;
	fcml_uint8_t w;
	fcml_uint8_t l;
	fcml_uint8_t mmmm;
	fcml_uint8_t vvvv;
	fcml_uint8_t pp;
} fcml_st_asm_dec_prefixes;

typedef struct fcml_st_disassembler_result {
	fcml_st_ceh_error_container *errors;
	fcml_st_asm_dec_prefixes prefixes;
} fcml_st_disassembler_result;

fcml_ceh_error fcml_fn_disassembler_init( fcml_st_dialect_context context, fcml_st_disassembler **disassembler );
fcml_ceh_error fcml_fn_disassemble( fcml_st_disassembler_context *context, fcml_st_disassembler_result **result );
void fcml_fn_disassemble_result_free( fcml_st_disassembler_result *result );
void fcml_fn_disassembler_free( fcml_st_disassembler *disassembler );

#endif /* FCML_DISASSEMBLER_H_ */
