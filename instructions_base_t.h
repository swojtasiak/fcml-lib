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

#define FCML_I3264(x,...) { FCML_I32(x,__VA_ARGS__); FCML_I64(x,__VA_ARGS__); }
#define FCML_I32(x,...) { fcml_uint8_t code[] = {__VA_ARGS__}; IA3264_instruction_test( code, sizeof( code ), FCML_FALSE, x, FCML_TRUE, FCML_FALSE, FCML_FALSE); }
#define FCML_I64(x,...) { fcml_uint8_t code[] = {__VA_ARGS__}; IA3264_instruction_test( code, sizeof( code ), FCML_TRUE, x, FCML_TRUE, FCML_FALSE, FCML_FALSE); }
#define FCML_I32_RIP(x,...) { fcml_uint8_t code[] = {__VA_ARGS__}; IA3264_instruction_test( code, sizeof( code ), FCML_FALSE, x, FCML_TRUE, FCML_FALSE, FCML_TRUE); }
#define FCML_I64_RIP(x,...) { fcml_uint8_t code[] = {__VA_ARGS__}; IA3264_instruction_test( code, sizeof( code ), FCML_TRUE, x, FCML_TRUE, FCML_FALSE, FCML_TRUE); }
#define FCML_I32_FAILED(x,...) { fcml_uint8_t code[] = {__VA_ARGS__}; IA3264_instruction_test( code, sizeof( code ), FCML_FALSE, x, FCML_FALSE, FCML_FALSE, FCML_FALSE); }
#define FCML_I64_FAILED(x,...) { fcml_uint8_t code[] = {__VA_ARGS__}; IA3264_instruction_test( code, sizeof( code ), FCML_TRUE, x, FCML_FALSE, FCML_FALSE, FCML_FALSE); }

#define FCML_I3264_P(x,...) { FCML_I32_P(x,__VA_ARGS__); FCML_I64_P(x,__VA_ARGS__); }
#define FCML_I32_P(x,...) { fcml_uint8_t code[] = {__VA_ARGS__}; IA3264_instruction_test( code, sizeof( code ), FCML_FALSE, x, FCML_TRUE, FCML_TRUE, FCML_FALSE); }
#define FCML_I64_P(x,...) { fcml_uint8_t code[] = {__VA_ARGS__}; IA3264_instruction_test( code, sizeof( code ), FCML_TRUE, x, FCML_TRUE, FCML_TRUE, FCML_FALSE); }
#define FCML_I3264_RIP_P(x,...) { FCML_I32_RIP_P(x,__VA_ARGS__); FCML_I64_RIP_P(x,__VA_ARGS__); }
#define FCML_I32_RIP_P(x,...) { fcml_uint8_t code[] = {__VA_ARGS__}; IA3264_instruction_test( code, sizeof( code ), FCML_FALSE, x, FCML_TRUE, FCML_TRUE, FCML_TRUE); }
#define FCML_I64_RIP_P(x,...) { fcml_uint8_t code[] = {__VA_ARGS__}; IA3264_instruction_test( code, sizeof( code ), FCML_TRUE, x, FCML_TRUE, FCML_TRUE, FCML_TRUE); }

#define FCML_I3264_D(x,...) { FCML_I32_D(x,__VA_ARGS__); FCML_I64_D(x,__VA_ARGS__); }
#define FCML_I32_D(x,...) { fcml_uint8_t code[] = {__VA_ARGS__}; IA3264_instruction_diss_test( code, sizeof( code ), FCML_FALSE, x, FCML_TRUE); }
#define FCML_I64_D(x,...) { fcml_uint8_t code[] = {__VA_ARGS__}; IA3264_instruction_diss_test( code, sizeof( code ), FCML_TRUE, x, FCML_TRUE); }
#define FCML_I32_D_FAILED(x,...) { fcml_uint8_t code[] = {__VA_ARGS__}; IA3264_instruction_diss_test( code, sizeof( code ), FCML_FALSE, x, FCML_FALSE); }
#define FCML_I64_D_FAILED(x,...) { fcml_uint8_t code[] = {__VA_ARGS__}; IA3264_instruction_diss_test( code, sizeof( code ), FCML_TRUE, x, FCML_FALSE); }

void IA3264_instruction_test( fcml_uint8_t *bytes, int size, fcml_bool x64, fcml_string mnemonic, fcml_bool failed, fcml_bool only_print_result, fcml_bool is_rip );
void IA3264_instruction_diss_test( fcml_uint8_t *code, int size, fcml_bool x64, fcml_string mnemonic, fcml_bool failed );

#endif /* INSTRUCTIONS_BASE_T_H_ */
