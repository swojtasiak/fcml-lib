/*
 * fcml_diss_int.h
 *
 *  Created on: 31-03-2013
 *      Author: tAs
 */

#ifndef FCML_DISS_INT_H_
#define FCML_DISS_INT_H_

#include "ira_int.h"

// Describes operand size.
typedef struct fcml_st_diss_decoded_operand_size {
	// Explicit operand size.
	uint16_t operand_size;
	// Operand size provider.
	ira_operand_size_provider operand_size_provider;
} fcml_st_diss_decoded_operand_size;

/* Operand decoders arguments. */

/* Structure that can be used to pass register type and its size to operand decoding function. */
struct ira_modrm_decoding_args {
	// Register type.
	enum ira_register_type reg_type;
	// Allows to dynamically calculate memory operand size.
	fcml_st_diss_decoded_operand_size memory_operand_size;
	// Allows to dynamically calculate register operand size.
	fcml_st_diss_decoded_operand_size register_operand_size;
	// Flags.
	uint8_t flags;
};

/* Structure that can be used to pass register type to operand decoding function. */
struct ira_reg_type_args {
	// Operand size details used to calculate its size at runtime.
	struct fcml_st_diss_decoded_operand_size operand_size;
	// Register itself.
	struct ira_register reg;
};

/* Structure that can be used to pass immediate value type/size to operand decoding function. */
struct ira_immediate_type_args {
	// Immediate value type.
	struct fcml_st_diss_decoded_operand_size imm_size;
	struct fcml_st_diss_decoded_operand_size imm_ex_size;
};

#endif /* FCML_DISS_INT_H_ */
