/*
 * fcml_asm_decoding.h
 *
 *  Created on: Oct 13, 2013
 *      Author: tas
 */

#ifndef FCML_ASM_DECODING_H_
#define FCML_ASM_DECODING_H_

#include "fcml_stream.h"
#include "fcml_disassembler.h"
#include "fcml_asm_dialect.h"

typedef struct fcml_st_asm_decoding_context {
	fcml_st_disassembler_context *disassembler_context;
	fcml_uint8_t opcodes[3];
	fcml_int opcodes_count;
	fcml_st_asm_dec_prefixes prefixes;
	fcml_data_size effective_address_size;
	fcml_data_size effective_operand_size;
	fcml_st_memory_stream *stream;
} fcml_st_asm_decoding_context;

fcml_ceh_error fcml_fn_asm_init_instruction_decodings( fcml_st_dialect_context *dialect_context, fcml_st_disassembler **disassembler );
// TODO: sprawdzic spujnosc z assemblerem, encoder tam tylko dostarcza strukture enkodingu reszte robi assembler, tu chyba bedzie trzeba zrobic podobnie.
fcml_ceh_error fcml_fn_asm_decode_instruction( fcml_st_asm_decoding_context *context );
void fcml_fn_asm_free_instruction_decodings( fcml_st_disassembler *disassembler );

#endif /* FCML_ASM_DECODING_H_ */
