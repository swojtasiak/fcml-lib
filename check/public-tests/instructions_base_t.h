/*
 * FCML - Free Code Manipulation Library.
 * Copyright (C) 2010-2014 Slawomir Wojtasiak
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

#ifndef INSTRUCTIONS_BASE_T_H_
#define INSTRUCTIONS_BASE_T_H_

#include <fcml_stf.h>

#include <fcml_types.h>
#include <fcml_optimizers.h>
#include <fcml_disassembler.h>
#include <fcml_assembler.h>

extern fcml_st_dialect *dialect_intel;
extern fcml_st_assembler *assembler_intel;
extern fcml_st_disassembler *disassembler_intel;

extern fcml_st_dialect *dialect_gas;
extern fcml_st_assembler *assembler_gas;
extern fcml_st_disassembler *disassembler_gas;

#define FCML_TSF_SHOULD_FAIL		0x00000001
#define FCML_TSF_SHORT				0x00000002
#define FCML_TSF_PRINT_ONLY			0x00000004
#define FCML_TSF_ENABLE_RIP			0x00000008
#define FCML_TSF_MULTI_ASM_RESULTS	0x00000010
#define FCML_TSF_ASM_ONLY			0x00000020
#define FCML_TSF_GAS_DIALECT		0x00000040

#ifdef FCML_MSCC

int fcml_fn_test_number_of_arguments( fcml_string code );

#define FCML_MI(...) 				fcml_fn_test_number_of_arguments(#__VA_ARGS__), __VA_ARGS__

#else
#define FCML_MI(...) 				( sizeof( ( fcml_uint8_t[] ) { __VA_ARGS__ } ) / sizeof( fcml_uint8_t ) ), __VA_ARGS__
#endif

#define FCML_I16_M(x,...)			{ fcml_uint8_t code[] = {__VA_ARGS__}; STF_ASSERT( fcml_fn_ts_instruction_test( code, sizeof( code ), FCML_OM_16_BIT, x, FCML_TSF_MULTI_ASM_RESULTS, 0 ) ); }
#define FCML_I32_M(x,...)			{ fcml_uint8_t code[] = {__VA_ARGS__}; STF_ASSERT( fcml_fn_ts_instruction_test( code, sizeof( code ), FCML_OM_32_BIT, x, FCML_TSF_MULTI_ASM_RESULTS, 0 ) ); }
#define FCML_A32_M(x,...)			{ fcml_uint8_t code[] = {__VA_ARGS__}; STF_ASSERT( fcml_fn_ts_instruction_test( code, sizeof( code ), FCML_OM_32_BIT, x, FCML_TSF_MULTI_ASM_RESULTS | FCML_TSF_GAS_DIALECT, 0 ) ); }
#define FCML_I64_M(x,...)			{ fcml_uint8_t code[] = {__VA_ARGS__}; STF_ASSERT( fcml_fn_ts_instruction_test( code, sizeof( code ), FCML_OM_64_BIT, x, FCML_TSF_MULTI_ASM_RESULTS, 0 ) ); }
#define FCML_A64_M(x,...)			{ fcml_uint8_t code[] = {__VA_ARGS__}; STF_ASSERT( fcml_fn_ts_instruction_test( code, sizeof( code ), FCML_OM_64_BIT, x, FCML_TSF_MULTI_ASM_RESULTS | FCML_TSF_GAS_DIALECT, 0 ) ); }
#define FCML_I32_RIP_M(x,...)		{ fcml_uint8_t code[] = {__VA_ARGS__}; STF_ASSERT(fcml_fn_ts_instruction_test( code, sizeof( code ), FCML_OM_32_BIT, x, FCML_TSF_ENABLE_RIP | FCML_TSF_MULTI_ASM_RESULTS, 0)); }
#define FCML_I64_RIP_M(x,...)		{ fcml_uint8_t code[] = {__VA_ARGS__}; STF_ASSERT(fcml_fn_ts_instruction_test( code, sizeof( code ), FCML_OM_64_BIT, x, FCML_TSF_ENABLE_RIP | FCML_TSF_MULTI_ASM_RESULTS, 0)); }
#define FCML_I3264_M(x,...)			{ FCML_I32_M( x, __VA_ARGS__ ); FCML_I64_M( x, __VA_ARGS__ ); }
#define FCML_A3264_M(x,...)			{ FCML_A32_M( x, __VA_ARGS__ ); FCML_A64_M( x, __VA_ARGS__ ); }

#define FCML_I16_M_A(x,...)			{ fcml_uint8_t code[] = {__VA_ARGS__}; STF_ASSERT(fcml_fn_ts_instruction_test( code, sizeof( code ), FCML_OM_16_BIT, x, FCML_TSF_MULTI_ASM_RESULTS | FCML_TSF_ASM_ONLY, 0)); }
#define FCML_I32_M_A(x,...)			{ fcml_uint8_t code[] = {__VA_ARGS__}; STF_ASSERT(fcml_fn_ts_instruction_test( code, sizeof( code ), FCML_OM_32_BIT, x, FCML_TSF_MULTI_ASM_RESULTS | FCML_TSF_ASM_ONLY, 0)); }
#define FCML_A32_M_A(x,...)			{ fcml_uint8_t code[] = {__VA_ARGS__}; STF_ASSERT(fcml_fn_ts_instruction_test( code, sizeof( code ), FCML_OM_32_BIT, x, FCML_TSF_MULTI_ASM_RESULTS | FCML_TSF_ASM_ONLY | FCML_TSF_GAS_DIALECT, 0)); }
#define FCML_I64_M_A(x,...)			{ fcml_uint8_t code[] = {__VA_ARGS__}; STF_ASSERT(fcml_fn_ts_instruction_test( code, sizeof( code ), FCML_OM_64_BIT, x, FCML_TSF_MULTI_ASM_RESULTS | FCML_TSF_ASM_ONLY, 0)); }
#define FCML_A64_M_A(x,...)			{ fcml_uint8_t code[] = {__VA_ARGS__}; STF_ASSERT(fcml_fn_ts_instruction_test( code, sizeof( code ), FCML_OM_64_BIT, x, FCML_TSF_MULTI_ASM_RESULTS | FCML_TSF_ASM_ONLY | FCML_TSF_GAS_DIALECT, 0)); }
#define FCML_I3264_M_A(x,...)		{ FCML_I32_M_A( x, __VA_ARGS__ ); FCML_I64_M_A( x, __VA_ARGS__ ); }

#define FCML_I32_M_P(x,...)			{ fcml_uint8_t code[] = {__VA_ARGS__}; fcml_fn_ts_instruction_test( code, sizeof( code ), FCML_OM_32_BIT, x, FCML_TSF_PRINT_ONLY | FCML_TSF_MULTI_ASM_RESULTS, 0); }
#define FCML_I64_M_P(x,...)			{ fcml_uint8_t code[] = {__VA_ARGS__}; fcml_fn_ts_instruction_test( code, sizeof( code ), FCML_OM_64_BIT, x, FCML_TSF_PRINT_ONLY | FCML_TSF_MULTI_ASM_RESULTS, 0); }
#define FCML_A32_M_P(x,...)			{ fcml_uint8_t code[] = {__VA_ARGS__}; fcml_fn_ts_instruction_test( code, sizeof( code ), FCML_OM_32_BIT, x, FCML_TSF_PRINT_ONLY | FCML_TSF_MULTI_ASM_RESULTS | FCML_TSF_GAS_DIALECT, 0); }
#define FCML_A64_M_P(x,...)			{ fcml_uint8_t code[] = {__VA_ARGS__}; fcml_fn_ts_instruction_test( code, sizeof( code ), FCML_OM_64_BIT, x, FCML_TSF_PRINT_ONLY | FCML_TSF_MULTI_ASM_RESULTS | FCML_TSF_GAS_DIALECT, 0); }

#define FCML_I3264(x,...)			{ FCML_I32(x,__VA_ARGS__); FCML_I64(x,__VA_ARGS__); }
#define FCML_A3264(x,...)			{ FCML_A32(x,__VA_ARGS__); FCML_A64(x,__VA_ARGS__); }
#define FCML_I16_DF(x,tf,rf,...)	{ fcml_uint8_t code[] = {__VA_ARGS__}; STF_ASSERT(fcml_fn_ts_instruction_test( code, sizeof( code ), FCML_OM_16_BIT, x, tf, rf)); }
#define FCML_I32_DF(x,tf,rf,...)	{ fcml_uint8_t code[] = {__VA_ARGS__}; STF_ASSERT(fcml_fn_ts_instruction_test( code, sizeof( code ), FCML_OM_32_BIT, x, tf, rf)); }
#define FCML_I64_DF(x,tf,rf,...)	{ fcml_uint8_t code[] = {__VA_ARGS__}; STF_ASSERT(fcml_fn_ts_instruction_test( code, sizeof( code ), FCML_OM_64_BIT, x, tf, rf)); }
#define FCML_I16(x,...)				{ fcml_uint8_t code[] = {__VA_ARGS__}; STF_ASSERT(fcml_fn_ts_instruction_test( code, sizeof( code ), FCML_OM_16_BIT, x, 0, 0)); }
#define FCML_I32(x,...)				{ fcml_uint8_t code[] = {__VA_ARGS__}; STF_ASSERT(fcml_fn_ts_instruction_test( code, sizeof( code ), FCML_OM_32_BIT, x, 0, 0)); }
#define FCML_A32(x,...)				{ fcml_uint8_t code[] = {__VA_ARGS__}; STF_ASSERT(fcml_fn_ts_instruction_test( code, sizeof( code ), FCML_OM_32_BIT, x, FCML_TSF_GAS_DIALECT, 0)); }
#define FCML_I64(x,...)				{ fcml_uint8_t code[] = {__VA_ARGS__}; STF_ASSERT(fcml_fn_ts_instruction_test( code, sizeof( code ), FCML_OM_64_BIT, x, 0, 0)); }
#define FCML_A64(x,...)				{ fcml_uint8_t code[] = {__VA_ARGS__}; STF_ASSERT(fcml_fn_ts_instruction_test( code, sizeof( code ), FCML_OM_64_BIT, x, FCML_TSF_GAS_DIALECT, 0)); }
#define FCML_I32_RF(x,ren,...)		{ fcml_uint8_t code[] = {__VA_ARGS__}; STF_ASSERT(fcml_fn_ts_instruction_test( code, sizeof( code ), FCML_OM_32_BIT, x, 0, ren)); }
#define FCML_I64_RF(x,ren,...)		{ fcml_uint8_t code[] = {__VA_ARGS__}; STF_ASSERT(fcml_fn_ts_instruction_test( code, sizeof( code ), FCML_OM_64_BIT, x, 0, ren)); }
#define FCML_I32_RIP(x,...)			{ fcml_uint8_t code[] = {__VA_ARGS__}; STF_ASSERT(fcml_fn_ts_instruction_test( code, sizeof( code ), FCML_OM_32_BIT, x, FCML_TSF_ENABLE_RIP, 0)); }
#define FCML_I64_RIP(x,...)			{ fcml_uint8_t code[] = {__VA_ARGS__}; STF_ASSERT(fcml_fn_ts_instruction_test( code, sizeof( code ), FCML_OM_64_BIT, x, FCML_TSF_ENABLE_RIP, 0)); }
#define FCML_I32_FAILED(x,...)		{ fcml_uint8_t code[] = {__VA_ARGS__}; STF_ASSERT(fcml_fn_ts_instruction_test( code, sizeof( code ), FCML_OM_32_BIT, x, FCML_TSF_SHOULD_FAIL, 0)); }
#define FCML_A32_FAILED(x,...)		{ fcml_uint8_t code[] = {__VA_ARGS__}; STF_ASSERT(fcml_fn_ts_instruction_test( code, sizeof( code ), FCML_OM_32_BIT, x, FCML_TSF_SHOULD_FAIL | FCML_TSF_GAS_DIALECT, 0)); }
#define FCML_I64_FAILED(x,...)		{ fcml_uint8_t code[] = {__VA_ARGS__}; STF_ASSERT(fcml_fn_ts_instruction_test( code, sizeof( code ), FCML_OM_64_BIT, x, FCML_TSF_SHOULD_FAIL,  0)); }
#define FCML_A64_FAILED(x,...)		{ fcml_uint8_t code[] = {__VA_ARGS__}; STF_ASSERT(fcml_fn_ts_instruction_test( code, sizeof( code ), FCML_OM_64_BIT, x, FCML_TSF_SHOULD_FAIL | FCML_TSF_GAS_DIALECT,  0)); }

#define FCML_I3264_P(x,...)			{ FCML_I32_P( x, __VA_ARGS__ ); FCML_I64_P( x, __VA_ARGS__ ); }
#define FCML_I16_P(x,...)			{ fcml_uint8_t code[] = {__VA_ARGS__}; fcml_fn_ts_instruction_test( code, sizeof( code ), FCML_OM_16_BIT, x, FCML_TSF_PRINT_ONLY, 0); }
#define FCML_I32_P(x,...)			{ fcml_uint8_t code[] = {__VA_ARGS__}; fcml_fn_ts_instruction_test( code, sizeof( code ), FCML_OM_32_BIT, x, FCML_TSF_PRINT_ONLY, 0); }
#define FCML_A32_P(x,...)			{ fcml_uint8_t code[] = {__VA_ARGS__}; fcml_fn_ts_instruction_test( code, sizeof( code ), FCML_OM_32_BIT, x, FCML_TSF_PRINT_ONLY | FCML_TSF_GAS_DIALECT, 0); }
#define FCML_I64_P(x,...)			{ fcml_uint8_t code[] = {__VA_ARGS__}; fcml_fn_ts_instruction_test( code, sizeof( code ), FCML_OM_64_BIT, x, FCML_TSF_PRINT_ONLY, 0); }
#define FCML_A64_P(x,...)			{ fcml_uint8_t code[] = {__VA_ARGS__}; fcml_fn_ts_instruction_test( code, sizeof( code ), FCML_OM_64_BIT, x, FCML_TSF_PRINT_ONLY | FCML_TSF_GAS_DIALECT, 0); }
#define FCML_I64_RIP_P(x,...)		{ fcml_uint8_t code[] = {__VA_ARGS__}; fcml_fn_ts_instruction_test( code, sizeof( code ), FCML_OM_64_BIT, x, FCML_TSF_PRINT_ONLY | FCML_TSF_ENABLE_RIP | FCML_TSF_MULTI_ASM_RESULTS, 0); }

#define FCML_I3264_D(x,...)			{ FCML_I32_D( x, __VA_ARGS__ ); FCML_I64_D( x, __VA_ARGS__ ); }
#define FCML_I16_D(x,...)			{ fcml_uint8_t code[] = {__VA_ARGS__}; STF_ASSERT(fcml_fn_ts_instruction_test_diss( code, sizeof( code ), FCML_OM_16_BIT, x, 0, 0)); }
#define FCML_I32_D(x,...)			{ fcml_uint8_t code[] = {__VA_ARGS__}; STF_ASSERT(fcml_fn_ts_instruction_test_diss( code, sizeof( code ), FCML_OM_32_BIT, x, 0, 0)); }
#define FCML_A32_D(x,...)			{ fcml_uint8_t code[] = {__VA_ARGS__}; STF_ASSERT(fcml_fn_ts_instruction_test_diss( code, sizeof( code ), FCML_OM_32_BIT, x, FCML_TSF_GAS_DIALECT, 0)); }
#define FCML_I16_D_P(x,...)			{ fcml_uint8_t code[] = {__VA_ARGS__}; fcml_fn_ts_instruction_test_diss( code, sizeof( code ), FCML_OM_16_BIT, x, FCML_TSF_PRINT_ONLY, 0 ); }
#define FCML_I32_D_P(x,...)			{ fcml_uint8_t code[] = {__VA_ARGS__}; fcml_fn_ts_instruction_test_diss( code, sizeof( code ), FCML_OM_32_BIT, x, FCML_TSF_PRINT_ONLY, 0 ); }
#define FCML_A16_D_P(x,...)			{ fcml_uint8_t code[] = {__VA_ARGS__}; fcml_fn_ts_instruction_test_diss( code, sizeof( code ), FCML_OM_16_BIT, x, FCML_TSF_PRINT_ONLY | FCML_TSF_GAS_DIALECT, 0 ); }
#define FCML_A32_D_P(x,...)			{ fcml_uint8_t code[] = {__VA_ARGS__}; fcml_fn_ts_instruction_test_diss( code, sizeof( code ), FCML_OM_32_BIT, x, FCML_TSF_PRINT_ONLY | FCML_TSF_GAS_DIALECT, 0 ); }
#define FCML_I32_D_RF(x,ren,...)	{ fcml_uint8_t code[] = {__VA_ARGS__}; STF_ASSERT(fcml_fn_ts_instruction_test_diss( code, sizeof( code ), FCML_OM_32_BIT, x, 0, ren)); }
#define FCML_I32_D_RF_P(x,ren,...)	{ fcml_uint8_t code[] = {__VA_ARGS__}; fcml_fn_ts_instruction_test_diss( code, sizeof( code ), FCML_OM_32_BIT, x, FCML_TSF_PRINT_ONLY, ren); }
#define FCML_I64_D(x,...)			{ fcml_uint8_t code[] = {__VA_ARGS__}; STF_ASSERT(fcml_fn_ts_instruction_test_diss( code, sizeof( code ), FCML_OM_64_BIT, x, 0, 0)); }
#define FCML_A64_D(x,...)			{ fcml_uint8_t code[] = {__VA_ARGS__}; STF_ASSERT(fcml_fn_ts_instruction_test_diss( code, sizeof( code ), FCML_OM_64_BIT, x, FCML_TSF_GAS_DIALECT, 0)); }
#define FCML_I64_D_P(x,...)			{ fcml_uint8_t code[] = {__VA_ARGS__}; fcml_fn_ts_instruction_test_diss( code, sizeof( code ), FCML_OM_64_BIT, x, FCML_TSF_PRINT_ONLY, 0); }
#define FCML_A64_D_P(x,...)			{ fcml_uint8_t code[] = {__VA_ARGS__}; fcml_fn_ts_instruction_test_diss( code, sizeof( code ), FCML_OM_64_BIT, x, FCML_TSF_PRINT_ONLY | FCML_TSF_GAS_DIALECT, 0); }
#define FCML_I64_D_RF(x,ren,...)	{ fcml_uint8_t code[] = {__VA_ARGS__}; STF_ASSERT(fcml_fn_ts_instruction_test_diss( code, sizeof( code ), FCML_OM_64_BIT, x, 0, ren)); }
#define FCML_I32_D_FAILED(x,...)	{ fcml_uint8_t code[] = {__VA_ARGS__}; STF_ASSERT(fcml_fn_ts_instruction_test_diss( code, sizeof( code ), FCML_OM_32_BIT, x, FCML_TSF_SHOULD_FAIL, 0)); }
#define FCML_A32_D_FAILED(x,...)	{ fcml_uint8_t code[] = {__VA_ARGS__}; STF_ASSERT(fcml_fn_ts_instruction_test_diss( code, sizeof( code ), FCML_OM_32_BIT, x, FCML_TSF_SHOULD_FAIL | FCML_TSF_GAS_DIALECT, 0)); }
#define FCML_I64_D_FAILED(x,...)	{ fcml_uint8_t code[] = {__VA_ARGS__}; STF_ASSERT(fcml_fn_ts_instruction_test_diss( code, sizeof( code ), FCML_OM_64_BIT, x, FCML_TSF_SHOULD_FAIL, 0)); }
#define FCML_A64_D_FAILED(x,...)	{ fcml_uint8_t code[] = {__VA_ARGS__}; STF_ASSERT(fcml_fn_ts_instruction_test_diss( code, sizeof( code ), FCML_OM_64_BIT, x, FCML_TSF_SHOULD_FAIL | FCML_TSF_GAS_DIALECT, 0)); }
#define FCML_I32_D_SHORT(x,...)		{ fcml_uint8_t code[] = {__VA_ARGS__}; STF_ASSERT(fcml_fn_ts_instruction_test_diss( code, sizeof( code ), FCML_OM_32_BIT, x, FCML_TSF_SHORT, 0)); }
#define FCML_A32_D_SHORT(x,...)		{ fcml_uint8_t code[] = {__VA_ARGS__}; STF_ASSERT(fcml_fn_ts_instruction_test_diss( code, sizeof( code ), FCML_OM_32_BIT, x, FCML_TSF_SHORT | FCML_TSF_GAS_DIALECT, 0)); }
#define FCML_I64_D_SHORT(x,...)		{ fcml_uint8_t code[] = {__VA_ARGS__}; STF_ASSERT(fcml_fn_ts_instruction_test_diss( code, sizeof( code ), FCML_OM_64_BIT, x, FCML_TSF_SHORT, 0)); }
#define FCML_A64_D_SHORT(x,...)		{ fcml_uint8_t code[] = {__VA_ARGS__}; STF_ASSERT(fcml_fn_ts_instruction_test_diss( code, sizeof( code ), FCML_OM_64_BIT, x, FCML_TSF_SHORT | FCML_TSF_GAS_DIALECT, 0)); }
#define FCML_I32_D_SHORT_P(x,...)	{ fcml_uint8_t code[] = {__VA_ARGS__}; fcml_fn_ts_instruction_test_diss( code, sizeof( code ), FCML_OM_32_BIT, x, FCML_TSF_PRINT_ONLY | FCML_TSF_SHORT, 0); }
#define FCML_A32_D_SHORT_P(x,...)	{ fcml_uint8_t code[] = {__VA_ARGS__}; fcml_fn_ts_instruction_test_diss( code, sizeof( code ), FCML_OM_32_BIT, x, FCML_TSF_PRINT_ONLY | FCML_TSF_SHORT | FCML_TSF_GAS_DIALECT, 0); }
#define FCML_I64_D_SHORT_P(x,...)	{ fcml_uint8_t code[] = {__VA_ARGS__}; fcml_fn_ts_instruction_test_diss( code, sizeof( code ), FCML_OM_64_BIT, x, FCML_TSF_PRINT_ONLY | FCML_TSF_SHORT, 0); }
#define FCML_A64_D_SHORT_P(x,...)	{ fcml_uint8_t code[] = {__VA_ARGS__}; fcml_fn_ts_instruction_test_diss( code, sizeof( code ), FCML_OM_64_BIT, x, FCML_TSF_PRINT_ONLY | FCML_TSF_SHORT | FCML_TSF_GAS_DIALECT, 0); }

#define FCML_I3264_A(x,...)			{ FCML_I32_A(x,__VA_ARGS__); FCML_I64_A(x,__VA_ARGS__); }
#define FCML_A3264_A(x,...)			{ FCML_A32_A(x,__VA_ARGS__); FCML_A64_A(x,__VA_ARGS__); }
#define FCML_I3264_A_FAILED(x,...)	{ FCML_I32_A_FAILED(x,__VA_ARGS__); FCML_I64_A_FAILED(x,__VA_ARGS__); }
#define FCML_I32_A(x,...)			{ fcml_uint8_t code[] = {__VA_ARGS__}; STF_ASSERT(fcml_fn_ts_instruction_test( code, sizeof( code ), FCML_OM_32_BIT, x, FCML_TSF_ASM_ONLY, 0)); }
#define FCML_I16_A(x,...)			{ fcml_uint8_t code[] = {__VA_ARGS__}; STF_ASSERT(fcml_fn_ts_instruction_test( code, sizeof( code ), FCML_OM_16_BIT, x, FCML_TSF_ASM_ONLY, 0)); }
#define FCML_A32_A(x,...)			{ fcml_uint8_t code[] = {__VA_ARGS__}; STF_ASSERT(fcml_fn_ts_instruction_test( code, sizeof( code ), FCML_OM_32_BIT, x, FCML_TSF_ASM_ONLY | FCML_TSF_GAS_DIALECT, 0)); }
#define FCML_A16_A(x,...)			{ fcml_uint8_t code[] = {__VA_ARGS__}; STF_ASSERT(fcml_fn_ts_instruction_test( code, sizeof( code ), FCML_OM_16_BIT, x, FCML_TSF_ASM_ONLY | FCML_TSF_GAS_DIALECT, 0)); }
#define FCML_I32_A_RF(x,ren,...)	{ fcml_uint8_t code[] = {__VA_ARGS__}; STF_ASSERT(fcml_fn_ts_instruction_test( code, sizeof( code ), FCML_OM_32_BIT, x, FCML_TSF_ASM_ONLY, ren)); }
#define FCML_I32_A_FAILED(x,...)	{ fcml_uint8_t code[] = {__VA_ARGS__}; STF_ASSERT(fcml_fn_ts_instruction_test( code, sizeof( code ), FCML_OM_32_BIT, x, FCML_TSF_SHOULD_FAIL | FCML_TSF_ASM_ONLY, 0)); }
#define FCML_I64_A(x,...)			{ fcml_uint8_t code[] = {__VA_ARGS__}; STF_ASSERT(fcml_fn_ts_instruction_test( code, sizeof( code ), FCML_OM_64_BIT, x, FCML_TSF_ASM_ONLY, 0)); }
#define FCML_A64_A(x,...)			{ fcml_uint8_t code[] = {__VA_ARGS__}; STF_ASSERT(fcml_fn_ts_instruction_test( code, sizeof( code ), FCML_OM_64_BIT, x, FCML_TSF_ASM_ONLY | FCML_TSF_GAS_DIALECT, 0)); }
#define FCML_I64_A_RF(x,ren,...)	{ fcml_uint8_t code[] = {__VA_ARGS__}; STF_ASSERT(fcml_fn_ts_instruction_test( code, sizeof( code ), FCML_OM_64_BIT, x, FCML_TSF_ASM_ONLY, ren)); }
#define FCML_I64_RIP_A(x,...)		{ fcml_uint8_t code[] = {__VA_ARGS__}; STF_ASSERT(fcml_fn_ts_instruction_test( code, sizeof( code ), FCML_OM_64_BIT, x, FCML_TSF_ENABLE_RIP | FCML_TSF_ASM_ONLY, 0)); }
#define FCML_I64_A_FAILED(x,...)	{ fcml_uint8_t code[] = {__VA_ARGS__}; STF_ASSERT(fcml_fn_ts_instruction_test( code, sizeof( code ), FCML_OM_64_BIT, x, FCML_TSF_SHOULD_FAIL | FCML_TSF_ASM_ONLY, 0)); }
#define FCML_A64_A_FAILED(x,...)	{ fcml_uint8_t code[] = {__VA_ARGS__}; STF_ASSERT(fcml_fn_ts_instruction_test( code, sizeof( code ), FCML_OM_64_BIT, x, FCML_TSF_SHOULD_FAIL | FCML_TSF_ASM_ONLY | FCML_TSF_GAS_DIALECT, 0)); }

#define FCML_I3264_A_P(x,...)		{ FCML_I32_A_P(x,__VA_ARGS__); FCML_I64_A_P(x,__VA_ARGS__); }
#define FCML_I32_A_P(x,...)			{ fcml_uint8_t code[] = {__VA_ARGS__}; fcml_fn_ts_instruction_test( code, sizeof( code ), FCML_OM_32_BIT, x, FCML_TSF_PRINT_ONLY | FCML_TSF_ASM_ONLY, 0); }
#define FCML_A32_A_P(x,...)			{ fcml_uint8_t code[] = {__VA_ARGS__}; fcml_fn_ts_instruction_test( code, sizeof( code ), FCML_OM_32_BIT, x, FCML_TSF_PRINT_ONLY | FCML_TSF_ASM_ONLY | FCML_TSF_GAS_DIALECT, 0); }
#define FCML_I64_A_P(x,...)			{ fcml_uint8_t code[] = {__VA_ARGS__}; fcml_fn_ts_instruction_test( code, sizeof( code ), FCML_OM_64_BIT, x, FCML_TSF_PRINT_ONLY | FCML_TSF_ASM_ONLY, 0); }
#define FCML_A64_A_P(x,...)			{ fcml_uint8_t code[] = {__VA_ARGS__}; fcml_fn_ts_instruction_test( code, sizeof( code ), FCML_OM_64_BIT, x, FCML_TSF_PRINT_ONLY | FCML_TSF_ASM_ONLY | FCML_TSF_GAS_DIALECT, 0); }
#define FCML_I64_A_FAILED_P(x,...)	{ fcml_uint8_t code[] = {__VA_ARGS__}; fcml_fn_ts_instruction_test( code, sizeof( code ), FCML_OM_64_BIT, x, FCML_TSF_SHOULD_FAIL | FCML_TSF_PRINT_ONLY | FCML_TSF_ASM_ONLY, 0); }

fcml_bool fcml_fn_ts_instruction_test( fcml_uint8_t *code, fcml_int size, fcml_en_operating_mode addr_mode, fcml_string mnemonic, fcml_uint32_t t_flags, fcml_uint32_t rend_flags );
fcml_bool fcml_fn_ts_instruction_test_diss( fcml_uint8_t *code, fcml_int size, fcml_en_operating_mode addr_mode, fcml_string mnemonic, fcml_uint32_t t_flags, fcml_uint32_t ren_flags );

#endif /* INSTRUCTIONS_BASE_T_H_ */
