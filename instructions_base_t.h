/*
 * instructions_base_t.h
 *
 *  Created on: 01-06-2013
 *      Author: tAs
 */

#ifndef INSTRUCTIONS_BASE_T_H_
#define INSTRUCTIONS_BASE_T_H_

#include <CUnit/CUnit.h>
#include "fcml_types.h"
#include "fcml_optimizers.h"
#include "fcml_disassembler.h"

fcml_st_dialect *dialect_intel;
fcml_st_asm_assembler *assembler_intel;
fcml_st_dasm_disassembler *disassembler_intel;

fcml_st_dialect *dialect_att;
fcml_st_asm_assembler *assembler_att;
fcml_st_dasm_disassembler *disassembler_att;

#define FCML_TSF_SHOULD_FAIL		0x00000001
#define FCML_TSF_SHORT				0x00000002
#define FCML_TSF_PRINT_ONLY			0x00000004
#define FCML_TSF_ENABLE_RIP			0x00000008
#define FCML_TSF_MULTI_ASM_RESULTS	0x00000010
#define FCML_TSF_ASM_ONLY			0x00000020
#define FCML_TSF_GAS_DIALECT		0x00000040

#define FCML_MI(...) 				( sizeof( ( fcml_uint8_t[] ) { __VA_ARGS__ } ) / sizeof( fcml_uint8_t ) ), __VA_ARGS__

#define FCML_I32_M(x,...)			{ fcml_uint8_t code[] = {__VA_ARGS__}; CU_ASSERT( fcml_fn_ts_instruction_test( code, sizeof( code ), FCML_AF_32_BIT, x, FCML_TSF_MULTI_ASM_RESULTS, 0 ) ); }
#define FCML_A32_M(x,...)			{ fcml_uint8_t code[] = {__VA_ARGS__}; CU_ASSERT( fcml_fn_ts_instruction_test( code, sizeof( code ), FCML_AF_32_BIT, x, FCML_TSF_MULTI_ASM_RESULTS | FCML_TSF_GAS_DIALECT, 0 ) ); }
#define FCML_I64_M(x,...)			{ fcml_uint8_t code[] = {__VA_ARGS__}; CU_ASSERT( fcml_fn_ts_instruction_test( code, sizeof( code ), FCML_AF_64_BIT, x, FCML_TSF_MULTI_ASM_RESULTS, 0 ) ); }
#define FCML_A64_M(x,...)			{ fcml_uint8_t code[] = {__VA_ARGS__}; CU_ASSERT( fcml_fn_ts_instruction_test( code, sizeof( code ), FCML_AF_64_BIT, x, FCML_TSF_MULTI_ASM_RESULTS | FCML_TSF_GAS_DIALECT, 0 ) ); }
#define FCML_I32_RIP_M(x,...)		{ fcml_uint8_t code[] = {__VA_ARGS__}; CU_ASSERT(fcml_fn_ts_instruction_test( code, sizeof( code ), FCML_AF_32_BIT, x, FCML_TSF_ENABLE_RIP | FCML_TSF_MULTI_ASM_RESULTS, 0)); }
#define FCML_I64_RIP_M(x,...)		{ fcml_uint8_t code[] = {__VA_ARGS__}; CU_ASSERT(fcml_fn_ts_instruction_test( code, sizeof( code ), FCML_AF_64_BIT, x, FCML_TSF_ENABLE_RIP | FCML_TSF_MULTI_ASM_RESULTS, 0)); }
#define FCML_I3264_M(x,...)			{ FCML_I32_M( x, __VA_ARGS__ ); FCML_I64_M( x, __VA_ARGS__ ); }
#define FCML_A3264_M(x,...)			{ FCML_A32_M( x, __VA_ARGS__ ); FCML_A64_M( x, __VA_ARGS__ ); }

#define FCML_I32_M_A(x,...)			{ fcml_uint8_t code[] = {__VA_ARGS__}; CU_ASSERT(fcml_fn_ts_instruction_test( code, sizeof( code ), FCML_AF_32_BIT, x, FCML_TSF_MULTI_ASM_RESULTS | FCML_TSF_ASM_ONLY, 0)); }
#define FCML_I64_M_A(x,...)			{ fcml_uint8_t code[] = {__VA_ARGS__}; CU_ASSERT(fcml_fn_ts_instruction_test( code, sizeof( code ), FCML_AF_64_BIT, x, FCML_TSF_MULTI_ASM_RESULTS | FCML_TSF_ASM_ONLY, 0)); }
#define FCML_I3264_M_A(x,...)		{ FCML_I32_M_A( x, __VA_ARGS__ ); FCML_I64_M_A( x, __VA_ARGS__ ); }

#define FCML_I32_M_P(x,...)			{ fcml_uint8_t code[] = {__VA_ARGS__}; fcml_fn_ts_instruction_test( code, sizeof( code ), FCML_AF_32_BIT, x, FCML_TSF_PRINT_ONLY | FCML_TSF_MULTI_ASM_RESULTS, 0); }
#define FCML_I64_M_P(x,...)			{ fcml_uint8_t code[] = {__VA_ARGS__}; fcml_fn_ts_instruction_test( code, sizeof( code ), FCML_AF_64_BIT, x, FCML_TSF_PRINT_ONLY | FCML_TSF_MULTI_ASM_RESULTS, 0); }

#define FCML_I3264(x,...)			{ FCML_I32(x,__VA_ARGS__); FCML_I64(x,__VA_ARGS__); }
#define FCML_I16_DF(x,tf,rf,...)	{ fcml_uint8_t code[] = {__VA_ARGS__}; CU_ASSERT(fcml_fn_ts_instruction_test( code, sizeof( code ), FCML_AF_16_BIT, x, tf, rf)); }
#define FCML_I32_DF(x,tf,rf,...)	{ fcml_uint8_t code[] = {__VA_ARGS__}; CU_ASSERT(fcml_fn_ts_instruction_test( code, sizeof( code ), FCML_AF_32_BIT, x, tf, rf)); }
#define FCML_I64_DF(x,tf,rf,...)	{ fcml_uint8_t code[] = {__VA_ARGS__}; CU_ASSERT(fcml_fn_ts_instruction_test( code, sizeof( code ), FCML_AF_64_BIT, x, tf, rf)); }
#define FCML_I16(x,...)				{ fcml_uint8_t code[] = {__VA_ARGS__}; CU_ASSERT(fcml_fn_ts_instruction_test( code, sizeof( code ), FCML_AF_16_BIT, x, 0, 0)); }
#define FCML_I32(x,...)				{ fcml_uint8_t code[] = {__VA_ARGS__}; CU_ASSERT(fcml_fn_ts_instruction_test( code, sizeof( code ), FCML_AF_32_BIT, x, 0, 0)); }
#define FCML_A32(x,...)				{ fcml_uint8_t code[] = {__VA_ARGS__}; CU_ASSERT(fcml_fn_ts_instruction_test( code, sizeof( code ), FCML_AF_32_BIT, x, FCML_TSF_GAS_DIALECT, 0)); }
#define FCML_I64(x,...)				{ fcml_uint8_t code[] = {__VA_ARGS__}; CU_ASSERT(fcml_fn_ts_instruction_test( code, sizeof( code ), FCML_AF_64_BIT, x, 0, 0)); }
#define FCML_A64(x,...)				{ fcml_uint8_t code[] = {__VA_ARGS__}; CU_ASSERT(fcml_fn_ts_instruction_test( code, sizeof( code ), FCML_AF_64_BIT, x, FCML_TSF_GAS_DIALECT, 0)); }
#define FCML_I32_RF(x,ren,...)		{ fcml_uint8_t code[] = {__VA_ARGS__}; CU_ASSERT(fcml_fn_ts_instruction_test( code, sizeof( code ), FCML_AF_32_BIT, x, 0, ren)); }
#define FCML_I64_RF(x,ren,...)		{ fcml_uint8_t code[] = {__VA_ARGS__}; CU_ASSERT(fcml_fn_ts_instruction_test( code, sizeof( code ), FCML_AF_64_BIT, x, 0, ren)); }
#define FCML_I32_RIP(x,...)			{ fcml_uint8_t code[] = {__VA_ARGS__}; CU_ASSERT(fcml_fn_ts_instruction_test( code, sizeof( code ), FCML_AF_32_BIT, x, FCML_TSF_ENABLE_RIP, 0)); }
#define FCML_I64_RIP(x,...)			{ fcml_uint8_t code[] = {__VA_ARGS__}; CU_ASSERT(fcml_fn_ts_instruction_test( code, sizeof( code ), FCML_AF_64_BIT, x, FCML_TSF_ENABLE_RIP, 0)); }
#define FCML_I32_FAILED(x,...)		{ fcml_uint8_t code[] = {__VA_ARGS__}; CU_ASSERT(fcml_fn_ts_instruction_test( code, sizeof( code ), FCML_AF_32_BIT, x, FCML_TSF_SHOULD_FAIL, 0)); }
#define FCML_A32_FAILED(x,...)		{ fcml_uint8_t code[] = {__VA_ARGS__}; CU_ASSERT(fcml_fn_ts_instruction_test( code, sizeof( code ), FCML_AF_32_BIT, x, FCML_TSF_SHOULD_FAIL | FCML_TSF_GAS_DIALECT, 0)); }
#define FCML_I64_FAILED(x,...)		{ fcml_uint8_t code[] = {__VA_ARGS__}; CU_ASSERT(fcml_fn_ts_instruction_test( code, sizeof( code ), FCML_AF_64_BIT, x, FCML_TSF_SHOULD_FAIL,  0)); }
#define FCML_A64_FAILED(x,...)		{ fcml_uint8_t code[] = {__VA_ARGS__}; CU_ASSERT(fcml_fn_ts_instruction_test( code, sizeof( code ), FCML_AF_64_BIT, x, FCML_TSF_SHOULD_FAIL | FCML_TSF_GAS_DIALECT,  0)); }

#define FCML_I3264_P(x,...)			{ FCML_I32_P( x, __VA_ARGS__ ); FCML_I64_P( x, __VA_ARGS__ ); }
#define FCML_I16_P(x,...)			{ fcml_uint8_t code[] = {__VA_ARGS__}; fcml_fn_ts_instruction_test( code, sizeof( code ), FCML_AF_16_BIT, x, FCML_TSF_PRINT_ONLY, 0); }
#define FCML_I32_P(x,...)			{ fcml_uint8_t code[] = {__VA_ARGS__}; fcml_fn_ts_instruction_test( code, sizeof( code ), FCML_AF_32_BIT, x, FCML_TSF_PRINT_ONLY, 0); }
#define FCML_I64_P(x,...)			{ fcml_uint8_t code[] = {__VA_ARGS__}; fcml_fn_ts_instruction_test( code, sizeof( code ), FCML_AF_64_BIT, x, FCML_TSF_PRINT_ONLY, 0); }
#define FCML_I64_RIP_P(x,...)		{ fcml_uint8_t code[] = {__VA_ARGS__}; fcml_fn_ts_instruction_test( code, sizeof( code ), FCML_AF_64_BIT, x, FCML_TSF_PRINT_ONLY | FCML_TSF_ENABLE_RIP | FCML_TSF_MULTI_ASM_RESULTS, 0); }

#define FCML_I3264_D(x,...)			{ FCML_I32_D( x, __VA_ARGS__ ); FCML_I64_D( x, __VA_ARGS__ ); }
#define FCML_I16_D(x,...)			{ fcml_uint8_t code[] = {__VA_ARGS__}; CU_ASSERT(fcml_fn_ts_instruction_test_diss( code, sizeof( code ), FCML_AF_16_BIT, x, 0, 0)); }
#define FCML_I32_D(x,...)			{ fcml_uint8_t code[] = {__VA_ARGS__}; CU_ASSERT(fcml_fn_ts_instruction_test_diss( code, sizeof( code ), FCML_AF_32_BIT, x, 0, 0)); }
#define FCML_I32_D_P(x,...)			{ fcml_uint8_t code[] = {__VA_ARGS__}; fcml_fn_ts_instruction_test_diss( code, sizeof( code ), FCML_AF_32_BIT, x, FCML_TSF_PRINT_ONLY, 0 ); }
#define FCML_I32_D_RF(x,ren,...)	{ fcml_uint8_t code[] = {__VA_ARGS__}; CU_ASSERT(fcml_fn_ts_instruction_test_diss( code, sizeof( code ), FCML_AF_32_BIT, x, 0, ren)); }
#define FCML_I64_D(x,...)			{ fcml_uint8_t code[] = {__VA_ARGS__}; CU_ASSERT(fcml_fn_ts_instruction_test_diss( code, sizeof( code ), FCML_AF_64_BIT, x, 0, 0)); }
#define FCML_I64_D_P(x,...)			{ fcml_uint8_t code[] = {__VA_ARGS__}; fcml_fn_ts_instruction_test_diss( code, sizeof( code ), FCML_AF_64_BIT, x, FCML_TSF_PRINT_ONLY, 0); }
#define FCML_I64_D_RF(x,ren,...)	{ fcml_uint8_t code[] = {__VA_ARGS__}; CU_ASSERT(fcml_fn_ts_instruction_test_diss( code, sizeof( code ), FCML_AF_64_BIT, x, 0, ren)); }
#define FCML_I32_D_FAILED(x,...)	{ fcml_uint8_t code[] = {__VA_ARGS__}; CU_ASSERT(fcml_fn_ts_instruction_test_diss( code, sizeof( code ), FCML_AF_32_BIT, x, FCML_TSF_SHOULD_FAIL, 0)); }
#define FCML_I64_D_FAILED(x,...)	{ fcml_uint8_t code[] = {__VA_ARGS__}; CU_ASSERT(fcml_fn_ts_instruction_test_diss( code, sizeof( code ), FCML_AF_64_BIT, x, FCML_TSF_SHOULD_FAIL, 0)); }
#define FCML_I32_D_SHORT(x,...)		{ fcml_uint8_t code[] = {__VA_ARGS__}; CU_ASSERT(fcml_fn_ts_instruction_test_diss( code, sizeof( code ), FCML_AF_32_BIT, x, FCML_TSF_SHORT, 0)); }
#define FCML_I64_D_SHORT(x,...)		{ fcml_uint8_t code[] = {__VA_ARGS__}; CU_ASSERT(fcml_fn_ts_instruction_test_diss( code, sizeof( code ), FCML_AF_64_BIT, x, FCML_TSF_SHORT, 0)); }
#define FCML_I32_D_SHORT_P(x,...)	{ fcml_uint8_t code[] = {__VA_ARGS__}; fcml_fn_ts_instruction_test_diss( code, sizeof( code ), FCML_AF_32_BIT, x, FCML_TSF_PRINT_ONLY | FCML_TSF_SHORT, 0); }
#define FCML_I64_D_SHORT_P(x,...)	{ fcml_uint8_t code[] = {__VA_ARGS__}; fcml_fn_ts_instruction_test_diss( code, sizeof( code ), FCML_AF_64_BIT, x, FCML_TSF_PRINT_ONLY | FCML_TSF_SHORT, 0); }

#define FCML_I3264_A(x,...)			{ FCML_I32_A(x,__VA_ARGS__); FCML_I64_A(x,__VA_ARGS__); }
#define FCML_I3264_A_FAILED(x,...)	{ FCML_I32_A_FAILED(x,__VA_ARGS__); FCML_I64_A_FAILED(x,__VA_ARGS__); }
#define FCML_I32_A(x,...)			{ fcml_uint8_t code[] = {__VA_ARGS__}; CU_ASSERT(fcml_fn_ts_instruction_test( code, sizeof( code ), FCML_AF_32_BIT, x, FCML_TSF_ASM_ONLY, 0)); }
#define FCML_I32_A_RF(x,ren,...)	{ fcml_uint8_t code[] = {__VA_ARGS__}; CU_ASSERT(fcml_fn_ts_instruction_test( code, sizeof( code ), FCML_AF_32_BIT, x, FCML_TSF_ASM_ONLY, ren)); }
#define FCML_I32_A_FAILED(x,...)	{ fcml_uint8_t code[] = {__VA_ARGS__}; CU_ASSERT(fcml_fn_ts_instruction_test( code, sizeof( code ), FCML_AF_32_BIT, x, FCML_TSF_SHOULD_FAIL | FCML_TSF_ASM_ONLY, 0)); }
#define FCML_I64_A(x,...)			{ fcml_uint8_t code[] = {__VA_ARGS__}; CU_ASSERT(fcml_fn_ts_instruction_test( code, sizeof( code ), FCML_AF_64_BIT, x, FCML_TSF_ASM_ONLY, 0)); }
#define FCML_I64_A_RF(x,ren,...)	{ fcml_uint8_t code[] = {__VA_ARGS__}; CU_ASSERT(fcml_fn_ts_instruction_test( code, sizeof( code ), FCML_AF_64_BIT, x, FCML_TSF_ASM_ONLY, ren)); }
#define FCML_I64_RIP_A(x,...)		{ fcml_uint8_t code[] = {__VA_ARGS__}; CU_ASSERT(fcml_fn_ts_instruction_test( code, sizeof( code ), FCML_AF_64_BIT, x, FCML_TSF_ENABLE_RIP | FCML_TSF_ASM_ONLY, 0)); }
#define FCML_I64_A_FAILED(x,...)	{ fcml_uint8_t code[] = {__VA_ARGS__}; CU_ASSERT(fcml_fn_ts_instruction_test( code, sizeof( code ), FCML_AF_64_BIT, x, FCML_TSF_SHOULD_FAIL | FCML_TSF_ASM_ONLY, 0)); }

#define FCML_I3264_A_P(x,...)		{ FCML_I32_A_P(x,__VA_ARGS__); FCML_I64_A_P(x,__VA_ARGS__); }
#define FCML_I32_A_P(x,...)			{ fcml_uint8_t code[] = {__VA_ARGS__}; fcml_fn_ts_instruction_test( code, sizeof( code ), FCML_AF_32_BIT, x, FCML_TSF_PRINT_ONLY | FCML_TSF_ASM_ONLY, 0); }
#define FCML_I64_A_P(x,...)			{ fcml_uint8_t code[] = {__VA_ARGS__}; fcml_fn_ts_instruction_test( code, sizeof( code ), FCML_AF_64_BIT, x, FCML_TSF_PRINT_ONLY | FCML_TSF_ASM_ONLY, 0); }
#define FCML_I64_A_FAILED_P(x,...)	{ fcml_uint8_t code[] = {__VA_ARGS__}; fcml_fn_ts_instruction_test( code, sizeof( code ), FCML_AF_64_BIT, x, FCML_TSF_SHOULD_FAIL | FCML_TSF_PRINT_ONLY | FCML_TSF_ASM_ONLY, 0); }

fcml_bool fcml_fn_ts_instruction_test( fcml_uint8_t *code, int size, fcml_en_addr_form addr_mode, fcml_string mnemonic, fcml_uint32_t t_flags, fcml_uint32_t rend_flags );
fcml_bool fcml_fn_ts_instruction_test_diss( fcml_uint8_t *code, int size, fcml_en_addr_form addr_mode, fcml_string mnemonic, fcml_uint32_t t_flags, fcml_uint32_t ren_flags );

#endif /* INSTRUCTIONS_BASE_T_H_ */
