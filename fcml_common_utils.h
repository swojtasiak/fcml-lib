/*
 * fcml_common_utils.h
 *
 *  Created on: Nov 7, 2013
 *      Author: tas
 */

#ifndef FCML_COMMON_UTILS_H_
#define FCML_COMMON_UTILS_H_

#include "fcml_common.h"

extern fcml_st_register fcml_reg_AL;
extern fcml_st_register fcml_reg_AX;
extern fcml_st_register fcml_reg_EAX;
extern fcml_st_register fcml_reg_RAX;
extern fcml_st_register fcml_reg_MM0;
extern fcml_st_register fcml_reg_XMM0;
extern fcml_st_register fcml_reg_YMM0;

extern fcml_st_register fcml_reg_CL;
extern fcml_st_register fcml_reg_CX;
extern fcml_st_register fcml_reg_ECX;
extern fcml_st_register fcml_reg_RCX;
extern fcml_st_register fcml_reg_MM1;
extern fcml_st_register fcml_reg_XMM1;
extern fcml_st_register fcml_reg_YMM1;

extern fcml_st_register fcml_reg_DL;
extern fcml_st_register fcml_reg_DX;
extern fcml_st_register fcml_reg_EDX;
extern fcml_st_register fcml_reg_RDX;
extern fcml_st_register fcml_reg_MM2;
extern fcml_st_register fcml_reg_XMM2;
extern fcml_st_register fcml_reg_YMM2;

extern fcml_st_register fcml_reg_BL;
extern fcml_st_register fcml_reg_BX;
extern fcml_st_register fcml_reg_EBX;
extern fcml_st_register fcml_reg_RBX;
extern fcml_st_register fcml_reg_MM3;
extern fcml_st_register fcml_reg_XMM3;
extern fcml_st_register fcml_reg_YMM3;

extern fcml_st_register fcml_reg_AH;
extern fcml_st_register fcml_reg_SPL;
extern fcml_st_register fcml_reg_SP;
extern fcml_st_register fcml_reg_ESP;
extern fcml_st_register fcml_reg_RSP;
extern fcml_st_register fcml_reg_MM4;
extern fcml_st_register fcml_reg_XMM4;
extern fcml_st_register fcml_reg_YMM4;

extern fcml_st_register fcml_reg_CH;
extern fcml_st_register fcml_reg_BPL;
extern fcml_st_register fcml_reg_BP;
extern fcml_st_register fcml_reg_EBP;
extern fcml_st_register fcml_reg_RBP;
extern fcml_st_register fcml_reg_MM5;
extern fcml_st_register fcml_reg_XMM5;
extern fcml_st_register fcml_reg_YMM5;

extern fcml_st_register fcml_reg_DH;
extern fcml_st_register fcml_reg_SIL;
extern fcml_st_register fcml_reg_SI;
extern fcml_st_register fcml_reg_ESI;
extern fcml_st_register fcml_reg_RSI;
extern fcml_st_register fcml_reg_MM6;
extern fcml_st_register fcml_reg_XMM6;
extern fcml_st_register fcml_reg_YMM6;

extern fcml_st_register fcml_reg_BH;
extern fcml_st_register fcml_reg_DIL;
extern fcml_st_register fcml_reg_DI;
extern fcml_st_register fcml_reg_EDI;
extern fcml_st_register fcml_reg_RDI;
extern fcml_st_register fcml_reg_MM7;
extern fcml_st_register fcml_reg_XMM7;
extern fcml_st_register fcml_reg_YMM7;

extern fcml_st_register fcml_reg_R8L;
extern fcml_st_register fcml_reg_R8W;
extern fcml_st_register fcml_reg_R8D;
extern fcml_st_register fcml_reg_R8;
extern fcml_st_register fcml_reg_XMM8;
extern fcml_st_register fcml_reg_YMM8;

extern fcml_st_register fcml_reg_R9L;
extern fcml_st_register fcml_reg_R9W;
extern fcml_st_register fcml_reg_R9D;
extern fcml_st_register fcml_reg_R9;
extern fcml_st_register fcml_reg_XMM9;
extern fcml_st_register fcml_reg_YMM9;

extern fcml_st_register fcml_reg_R10L;
extern fcml_st_register fcml_reg_R10W;
extern fcml_st_register fcml_reg_R10D;
extern fcml_st_register fcml_reg_R10;
extern fcml_st_register fcml_reg_XMM10;
extern fcml_st_register fcml_reg_YMM10;

extern fcml_st_register fcml_reg_R11L;
extern fcml_st_register fcml_reg_R11W;
extern fcml_st_register fcml_reg_R11D;
extern fcml_st_register fcml_reg_R11;
extern fcml_st_register fcml_reg_XMM11;
extern fcml_st_register fcml_reg_YMM11;

extern fcml_st_register fcml_reg_R12L;
extern fcml_st_register fcml_reg_R12W;
extern fcml_st_register fcml_reg_R12D;
extern fcml_st_register fcml_reg_R12;
extern fcml_st_register fcml_reg_XMM12;
extern fcml_st_register fcml_reg_YMM12;

extern fcml_st_register fcml_reg_R13L;
extern fcml_st_register fcml_reg_R13W;
extern fcml_st_register fcml_reg_R13D;
extern fcml_st_register fcml_reg_R13;
extern fcml_st_register fcml_reg_XMM13;
extern fcml_st_register fcml_reg_YMM13;

extern fcml_st_register fcml_reg_R14L;
extern fcml_st_register fcml_reg_R14W;
extern fcml_st_register fcml_reg_R14D;
extern fcml_st_register fcml_reg_R14;
extern fcml_st_register fcml_reg_XMM14;
extern fcml_st_register fcml_reg_YMM14;

extern fcml_st_register fcml_reg_R15L;
extern fcml_st_register fcml_reg_R15W;
extern fcml_st_register fcml_reg_R15D;
extern fcml_st_register fcml_reg_R15;
extern fcml_st_register fcml_reg_XMM15;
extern fcml_st_register fcml_reg_YMM15;

extern fcml_st_register fcml_reg_ES;
extern fcml_st_register fcml_reg_CS;
extern fcml_st_register fcml_reg_SS;
extern fcml_st_register fcml_reg_DS;
extern fcml_st_register fcml_reg_FS;
extern fcml_st_register fcml_reg_GS;

extern fcml_st_register fcml_reg_ST0;
extern fcml_st_register fcml_reg_ST1;
extern fcml_st_register fcml_reg_ST2;
extern fcml_st_register fcml_reg_ST3;
extern fcml_st_register fcml_reg_ST4;
extern fcml_st_register fcml_reg_ST5;
extern fcml_st_register fcml_reg_ST6;
extern fcml_st_register fcml_reg_ST7;

extern fcml_st_register fcml_reg_CR0;
extern fcml_st_register fcml_reg_CR2;
extern fcml_st_register fcml_reg_CR3;
extern fcml_st_register fcml_reg_CR4;
extern fcml_st_register fcml_reg_CR8;

extern fcml_st_register fcml_reg_DR0;
extern fcml_st_register fcml_reg_DR1;
extern fcml_st_register fcml_reg_DR2;
extern fcml_st_register fcml_reg_DR3;
extern fcml_st_register fcml_reg_DR4;
extern fcml_st_register fcml_reg_DR5;
extern fcml_st_register fcml_reg_DR6;
extern fcml_st_register fcml_reg_DR7;

extern fcml_st_register fcml_reg_IP;
extern fcml_st_register fcml_reg_EIP;
extern fcml_st_register fcml_reg_RIP;

// REG.
fcml_st_operand fcml_fn_cu_operand_reg( fcml_st_register *reg );

// IMM.
fcml_st_operand fcml_fn_cu_operand_unsigned_imm_8( fcml_uint8_t value );
fcml_st_operand fcml_fn_cu_operand_signed_imm_8( fcml_int8_t value );
fcml_st_operand fcml_fn_cu_operand_unsigned_imm_16( fcml_uint16_t value );
fcml_st_operand fcml_fn_cu_operand_signed_imm_16( fcml_int16_t value );
fcml_st_operand fcml_fn_cu_operand_unsigned_imm_32( fcml_uint32_t value );
fcml_st_operand fcml_fn_cu_operand_signed_imm_32( fcml_int32_t value );
fcml_st_operand fcml_fn_cu_operand_unsigned_imm_64( fcml_uint64_t value );
fcml_st_operand fcml_fn_cu_operand_signed_imm_64( fcml_int64_t value );

// Some shortcuts for these who prefer to use macros instead of functions.

#define FCML_IMM8_S( x )		fcml_fn_cu_operand_signed_imm_8( x )
#define FCML_IMM8( x )			fcml_fn_cu_operand_unsigned_imm_8( x )
#define FCML_IMM16_S( x )		fcml_fn_cu_operand_signed_imm_16( x )
#define FCML_IMM16( x )			fcml_fn_cu_operand_unsigned_imm_16( x )
#define FCML_IMM32_S( x )		fcml_fn_cu_operand_signed_imm_32( x )
#define FCML_IMM32( x )			fcml_fn_cu_operand_unsigned_imm_32( x )
#define FCML_IMM64_S( x )		fcml_fn_cu_operand_signed_imm_64( x )
#define FCML_IMM64( x )			fcml_fn_cu_operand_unsigned_imm_64( x )

#ifdef FCML_USE_SHORT_REG
#define FCML_REG( x )			fcml_fn_cu_operand_reg( &fcml_reg_##x )
#else
#define FCML_REG( x )			fcml_fn_cu_operand_reg( &x )
#endif

#endif /* FCML_COMMON_UTILS_H_ */
