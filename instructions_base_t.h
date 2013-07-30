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

#define FCML_I3264(x,...) { FCML_I32(x,__VA_ARGS__); FCML_I64(x,__VA_ARGS__); }
#define FCML_I32(x,...) { fcml_uint8_t code[] = {__VA_ARGS__}; CU_ASSERT(IA3264_instruction_test( code, sizeof( code ), FCML_FALSE, x, FCML_TRUE, FCML_FALSE, FCML_FALSE, FCML_EN_OP_DEFAULT_ADDRESSING_MODE_OPTIMIZER, 0)); }
#define FCML_I32_OPT(x, opt, flags,...) { fcml_uint8_t code[] = {__VA_ARGS__}; CU_ASSERT(IA3264_instruction_test( code, sizeof( code ), FCML_FALSE, x, FCML_TRUE, FCML_FALSE, FCML_FALSE, opt, flags)); }
#define FCML_I64(x,...) { fcml_uint8_t code[] = {__VA_ARGS__}; CU_ASSERT(IA3264_instruction_test( code, sizeof( code ), FCML_TRUE, x, FCML_TRUE, FCML_FALSE, FCML_FALSE, FCML_EN_OP_DEFAULT_ADDRESSING_MODE_OPTIMIZER, 0)); }
#define FCML_I64_OPT(x, opt, flags,...) { fcml_uint8_t code[] = {__VA_ARGS__}; CU_ASSERT(IA3264_instruction_test( code, sizeof( code ), FCML_TRUE, x, FCML_TRUE, FCML_FALSE, FCML_FALSE, opt, flags)); }
#define FCML_I32_RIP(x,...) { fcml_uint8_t code[] = {__VA_ARGS__}; CU_ASSERT(IA3264_instruction_test( code, sizeof( code ), FCML_FALSE, x, FCML_TRUE, FCML_FALSE, FCML_TRUE, FCML_EN_OP_DEFAULT_ADDRESSING_MODE_OPTIMIZER, 0)); }
#define FCML_I64_RIP(x,...) { fcml_uint8_t code[] = {__VA_ARGS__}; CU_ASSERT(IA3264_instruction_test( code, sizeof( code ), FCML_TRUE, x, FCML_TRUE, FCML_FALSE, FCML_TRUE, FCML_EN_OP_DEFAULT_ADDRESSING_MODE_OPTIMIZER, 0)); }
#define FCML_I32_FAILED(x,...) { fcml_uint8_t code[] = {__VA_ARGS__}; CU_ASSERT(IA3264_instruction_test( code, sizeof( code ), FCML_FALSE, x, FCML_FALSE, FCML_FALSE, FCML_FALSE, FCML_EN_OP_DEFAULT_ADDRESSING_MODE_OPTIMIZER, 0)); }
#define FCML_I64_FAILED(x,...) { fcml_uint8_t code[] = {__VA_ARGS__}; CU_ASSERT(IA3264_instruction_test( code, sizeof( code ), FCML_TRUE, x, FCML_FALSE, FCML_FALSE, FCML_FALSE, FCML_EN_OP_DEFAULT_ADDRESSING_MODE_OPTIMIZER, 0)); }

#define FCML_I3264_P(x,...) { FCML_I32_P(x,__VA_ARGS__); FCML_I64_P(x,__VA_ARGS__); }
#define FCML_I32_P(x,...) { fcml_uint8_t code[] = {__VA_ARGS__}; IA3264_instruction_test( code, sizeof( code ), FCML_FALSE, x, FCML_TRUE, FCML_TRUE, FCML_FALSE, FCML_EN_OP_DEFAULT_ADDRESSING_MODE_OPTIMIZER, 0); }
#define FCML_I64_P(x,...) { fcml_uint8_t code[] = {__VA_ARGS__}; IA3264_instruction_test( code, sizeof( code ), FCML_TRUE, x, FCML_TRUE, FCML_TRUE, FCML_FALSE, FCML_EN_OP_DEFAULT_ADDRESSING_MODE_OPTIMIZER, 0); }
#define FCML_I32_OPT_P(x,opt,flags,...) { fcml_uint8_t code[] = {__VA_ARGS__}; IA3264_instruction_test( code, sizeof( code ), FCML_FALSE, x, FCML_TRUE, FCML_TRUE, FCML_FALSE, opt, flags); }
#define FCML_I64_OPT_P(x,opt,flags,...) { fcml_uint8_t code[] = {__VA_ARGS__}; IA3264_instruction_test( code, sizeof( code ), FCML_TRUE, x, FCML_TRUE, FCML_TRUE, FCML_FALSE, opt, flags); }
#define FCML_I3264_RIP_P(x,...) { FCML_I32_RIP_P(x,__VA_ARGS__); FCML_I64_RIP_P(x,__VA_ARGS__); }
#define FCML_I32_RIP_P(x,...) { fcml_uint8_t code[] = {__VA_ARGS__}; IA3264_instruction_test( code, sizeof( code ), FCML_FALSE, x, FCML_TRUE, FCML_TRUE, FCML_TRUE, FCML_EN_OP_DEFAULT_ADDRESSING_MODE_OPTIMIZER, 0); }
#define FCML_I64_RIP_P(x,...) { fcml_uint8_t code[] = {__VA_ARGS__}; IA3264_instruction_test( code, sizeof( code ), FCML_TRUE, x, FCML_TRUE, FCML_TRUE, FCML_TRUE, FCML_EN_OP_DEFAULT_ADDRESSING_MODE_OPTIMIZER, 0); }

#define FCML_I3264_D(x,...) { FCML_I32_D(x,__VA_ARGS__); FCML_I64_D(x,__VA_ARGS__); }
#define FCML_I32_D(x,...) { fcml_uint8_t code[] = {__VA_ARGS__}; CU_ASSERT(IA3264_instruction_diss_test( code, sizeof( code ), FCML_FALSE, x, FCML_TRUE)); }
#define FCML_I64_D(x,...) { fcml_uint8_t code[] = {__VA_ARGS__}; CU_ASSERT(IA3264_instruction_diss_test( code, sizeof( code ), FCML_TRUE, x, FCML_TRUE)); }
#define FCML_I32_D_FAILED(x,...) { fcml_uint8_t code[] = {__VA_ARGS__}; CU_ASSERT(IA3264_instruction_diss_test( code, sizeof( code ), FCML_FALSE, x, FCML_FALSE, FCML_EN_OP_DEFAULT_ADDRESSING_MODE_OPTIMIZER, 0)); }
#define FCML_I64_D_FAILED(x,...) { fcml_uint8_t code[] = {__VA_ARGS__}; CU_ASSERT(IA3264_instruction_diss_test( code, sizeof( code ), FCML_TRUE, x, FCML_FALSE, FCML_EN_OP_DEFAULT_ADDRESSING_MODE_OPTIMIZER, 0)); }

fcml_bool IA3264_instruction_test( fcml_uint8_t *code, int size, fcml_bool x64, fcml_string mnemonic, fcml_bool failed, fcml_bool only_print_result, fcml_bool enable_rip, fcml_en_assembler_optimizers optimizer, fcml_uint16_t opt_flags );
fcml_bool IA3264_instruction_diss_test( fcml_uint8_t *code, int size, fcml_bool x64, fcml_string mnemonic, fcml_bool failed );

#endif /* INSTRUCTIONS_BASE_T_H_ */
