/*
 * fcml_asm_encoding.h
 *
 *  Created on: 31-03-2013
 *      Author: tAs
 */

#ifndef FCML_ASM_ENCODING_H_
#define FCML_ASM_ENCODING_H_

#include "fcml_def.h"
#include "fcml_asm_int.h"
#include "fcml_ceh.h"
#include "fcml_coll.h"
#include "fcml_common.h"

struct fcml_st_asm_instruction_addr_modes;

typedef fcml_bool (*fcml_fnp_asm_operand_encoder)( fcml_st_operand *operand_def, fcml_st_asm_encoded_operand *operand_enc );
typedef fcml_ceh_error (*fcml_fnp_asm_instruction_encoder)( fcml_st_asm_encoding_context *context, struct fcml_st_asm_instruction_addr_modes *addr_modes );

typedef struct fcml_st_asm_operand_encoder {
	// Typ obslugiwany przez ponizszy encoder, uzywany w zasadzie tylko z powodow wydajnosciowych, aby wstepnie porownac typy.
	fcml_en_operand_type supported_operand_type;
	// Enkoder wlasciwy odpowiedzialnyz za enkodowanie operandu.
	fcml_fnp_asm_operand_encoder operand_encoder;
	// Argumenty dla enkodera.
	fcml_st_def_decoded_addr_mode* decoded_addr_mode;
} fcml_st_asm_operand_encoder;

typedef struct fcml_st_asm_instruction_addr_modes {
	// All addressing modes for given mnemonic are available in this list.
	fcml_st_coll_list *addr_modes;
	// Mnemonic.
	fcml_string mnemonic;
	// Instruction encoder.
	fcml_fnp_asm_instruction_encoder instruction_encoder;
} fcml_st_asm_instruction_addr_modes;

typedef struct fcml_st_asm_instruction_addr_mode {
	// Instruction definition.
	fcml_st_def_addr_mode_desc *addr_mode_desc;
	// Akceptory operandow odpowiedzialne za wstepna akceptacje operandów.
	fcml_st_asm_operand_encoder operand_encoders[FCML_OPERANDS_COUNT];
} fcml_st_asm_instruction_addr_mode;

fcml_ceh_error fcml_fn_asm_init_instruction_encodings();
fcml_ceh_error fcml_fn_asm_get_instruction_encodings( fcml_string mnemonic, fcml_st_asm_instruction_addr_modes ** );
void fcml_fn_asm_free_instruction_encodings();

#endif /* FCML_ASM_ENCODING_H_ */
