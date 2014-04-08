/*
 * fcml_common_utils.h
 *
 *  Created on: Nov 7, 2013
 *      Author: tas
 */

#ifndef FCML_COMMON_UTILS_H_
#define FCML_COMMON_UTILS_H_

#include "fcml_lib_export.h"

#include "fcml_common.h"

#ifdef __cplusplus
extern "C" {
#endif

extern LIB_EXPORT fcml_st_register fcml_reg_AL;
extern LIB_EXPORT fcml_st_register fcml_reg_AX;
extern LIB_EXPORT fcml_st_register fcml_reg_EAX;
extern LIB_EXPORT fcml_st_register fcml_reg_RAX;
extern LIB_EXPORT fcml_st_register fcml_reg_MM0;
extern LIB_EXPORT fcml_st_register fcml_reg_XMM0;
extern LIB_EXPORT fcml_st_register fcml_reg_YMM0;

extern LIB_EXPORT fcml_st_register fcml_reg_CL;
extern LIB_EXPORT fcml_st_register fcml_reg_CX;
extern LIB_EXPORT fcml_st_register fcml_reg_ECX;
extern LIB_EXPORT fcml_st_register fcml_reg_RCX;
extern LIB_EXPORT fcml_st_register fcml_reg_MM1;
extern LIB_EXPORT fcml_st_register fcml_reg_XMM1;
extern LIB_EXPORT fcml_st_register fcml_reg_YMM1;

extern LIB_EXPORT fcml_st_register fcml_reg_DL;
extern LIB_EXPORT fcml_st_register fcml_reg_DX;
extern LIB_EXPORT fcml_st_register fcml_reg_EDX;
extern LIB_EXPORT fcml_st_register fcml_reg_RDX;
extern LIB_EXPORT fcml_st_register fcml_reg_MM2;
extern LIB_EXPORT fcml_st_register fcml_reg_XMM2;
extern LIB_EXPORT fcml_st_register fcml_reg_YMM2;

extern LIB_EXPORT fcml_st_register fcml_reg_BL;
extern LIB_EXPORT fcml_st_register fcml_reg_BX;
extern LIB_EXPORT fcml_st_register fcml_reg_EBX;
extern LIB_EXPORT fcml_st_register fcml_reg_RBX;
extern LIB_EXPORT fcml_st_register fcml_reg_MM3;
extern LIB_EXPORT fcml_st_register fcml_reg_XMM3;
extern LIB_EXPORT fcml_st_register fcml_reg_YMM3;

extern LIB_EXPORT fcml_st_register fcml_reg_AH;
extern LIB_EXPORT fcml_st_register fcml_reg_SPL;
extern LIB_EXPORT fcml_st_register fcml_reg_SP;
extern LIB_EXPORT fcml_st_register fcml_reg_ESP;
extern LIB_EXPORT fcml_st_register fcml_reg_RSP;
extern LIB_EXPORT fcml_st_register fcml_reg_MM4;
extern LIB_EXPORT fcml_st_register fcml_reg_XMM4;
extern LIB_EXPORT fcml_st_register fcml_reg_YMM4;

extern LIB_EXPORT fcml_st_register fcml_reg_CH;
extern LIB_EXPORT fcml_st_register fcml_reg_BPL;
extern LIB_EXPORT fcml_st_register fcml_reg_BP;
extern LIB_EXPORT fcml_st_register fcml_reg_EBP;
extern LIB_EXPORT fcml_st_register fcml_reg_RBP;
extern LIB_EXPORT fcml_st_register fcml_reg_MM5;
extern LIB_EXPORT fcml_st_register fcml_reg_XMM5;
extern LIB_EXPORT fcml_st_register fcml_reg_YMM5;

extern LIB_EXPORT fcml_st_register fcml_reg_DH;
extern LIB_EXPORT fcml_st_register fcml_reg_SIL;
extern LIB_EXPORT fcml_st_register fcml_reg_SI;
extern LIB_EXPORT fcml_st_register fcml_reg_ESI;
extern LIB_EXPORT fcml_st_register fcml_reg_RSI;
extern LIB_EXPORT fcml_st_register fcml_reg_MM6;
extern LIB_EXPORT fcml_st_register fcml_reg_XMM6;
extern LIB_EXPORT fcml_st_register fcml_reg_YMM6;

extern LIB_EXPORT fcml_st_register fcml_reg_BH;
extern LIB_EXPORT fcml_st_register fcml_reg_DIL;
extern LIB_EXPORT fcml_st_register fcml_reg_DI;
extern LIB_EXPORT fcml_st_register fcml_reg_EDI;
extern LIB_EXPORT fcml_st_register fcml_reg_RDI;
extern LIB_EXPORT fcml_st_register fcml_reg_MM7;
extern LIB_EXPORT fcml_st_register fcml_reg_XMM7;
extern LIB_EXPORT fcml_st_register fcml_reg_YMM7;

extern LIB_EXPORT fcml_st_register fcml_reg_R8L;
extern LIB_EXPORT fcml_st_register fcml_reg_R8W;
extern LIB_EXPORT fcml_st_register fcml_reg_R8D;
extern LIB_EXPORT fcml_st_register fcml_reg_R8;
extern LIB_EXPORT fcml_st_register fcml_reg_XMM8;
extern LIB_EXPORT fcml_st_register fcml_reg_YMM8;

extern LIB_EXPORT fcml_st_register fcml_reg_R9L;
extern LIB_EXPORT fcml_st_register fcml_reg_R9W;
extern LIB_EXPORT fcml_st_register fcml_reg_R9D;
extern LIB_EXPORT fcml_st_register fcml_reg_R9;
extern LIB_EXPORT fcml_st_register fcml_reg_XMM9;
extern LIB_EXPORT fcml_st_register fcml_reg_YMM9;

extern LIB_EXPORT fcml_st_register fcml_reg_R10L;
extern LIB_EXPORT fcml_st_register fcml_reg_R10W;
extern LIB_EXPORT fcml_st_register fcml_reg_R10D;
extern LIB_EXPORT fcml_st_register fcml_reg_R10;
extern LIB_EXPORT fcml_st_register fcml_reg_XMM10;
extern LIB_EXPORT fcml_st_register fcml_reg_YMM10;

extern LIB_EXPORT fcml_st_register fcml_reg_R11L;
extern LIB_EXPORT fcml_st_register fcml_reg_R11W;
extern LIB_EXPORT fcml_st_register fcml_reg_R11D;
extern LIB_EXPORT fcml_st_register fcml_reg_R11;
extern LIB_EXPORT fcml_st_register fcml_reg_XMM11;
extern LIB_EXPORT fcml_st_register fcml_reg_YMM11;

extern LIB_EXPORT fcml_st_register fcml_reg_R12L;
extern LIB_EXPORT fcml_st_register fcml_reg_R12W;
extern LIB_EXPORT fcml_st_register fcml_reg_R12D;
extern LIB_EXPORT fcml_st_register fcml_reg_R12;
extern LIB_EXPORT fcml_st_register fcml_reg_XMM12;
extern LIB_EXPORT fcml_st_register fcml_reg_YMM12;

extern LIB_EXPORT fcml_st_register fcml_reg_R13L;
extern LIB_EXPORT fcml_st_register fcml_reg_R13W;
extern LIB_EXPORT fcml_st_register fcml_reg_R13D;
extern LIB_EXPORT fcml_st_register fcml_reg_R13;
extern LIB_EXPORT fcml_st_register fcml_reg_XMM13;
extern LIB_EXPORT fcml_st_register fcml_reg_YMM13;

extern LIB_EXPORT fcml_st_register fcml_reg_R14L;
extern LIB_EXPORT fcml_st_register fcml_reg_R14W;
extern LIB_EXPORT fcml_st_register fcml_reg_R14D;
extern LIB_EXPORT fcml_st_register fcml_reg_R14;
extern LIB_EXPORT fcml_st_register fcml_reg_XMM14;
extern LIB_EXPORT fcml_st_register fcml_reg_YMM14;

extern LIB_EXPORT fcml_st_register fcml_reg_R15L;
extern LIB_EXPORT fcml_st_register fcml_reg_R15W;
extern LIB_EXPORT fcml_st_register fcml_reg_R15D;
extern LIB_EXPORT fcml_st_register fcml_reg_R15;
extern LIB_EXPORT fcml_st_register fcml_reg_XMM15;
extern LIB_EXPORT fcml_st_register fcml_reg_YMM15;

extern LIB_EXPORT fcml_st_register fcml_reg_ES;
extern LIB_EXPORT fcml_st_register fcml_reg_CS;
extern LIB_EXPORT fcml_st_register fcml_reg_SS;
extern LIB_EXPORT fcml_st_register fcml_reg_DS;
extern LIB_EXPORT fcml_st_register fcml_reg_FS;
extern LIB_EXPORT fcml_st_register fcml_reg_GS;

extern LIB_EXPORT fcml_st_register fcml_reg_ST0;
extern LIB_EXPORT fcml_st_register fcml_reg_ST1;
extern LIB_EXPORT fcml_st_register fcml_reg_ST2;
extern LIB_EXPORT fcml_st_register fcml_reg_ST3;
extern LIB_EXPORT fcml_st_register fcml_reg_ST4;
extern LIB_EXPORT fcml_st_register fcml_reg_ST5;
extern LIB_EXPORT fcml_st_register fcml_reg_ST6;
extern LIB_EXPORT fcml_st_register fcml_reg_ST7;

extern LIB_EXPORT fcml_st_register fcml_reg_CR0;
extern LIB_EXPORT fcml_st_register fcml_reg_CR2;
extern LIB_EXPORT fcml_st_register fcml_reg_CR3;
extern LIB_EXPORT fcml_st_register fcml_reg_CR4;
extern LIB_EXPORT fcml_st_register fcml_reg_CR8;

extern LIB_EXPORT fcml_st_register fcml_reg_DR0;
extern LIB_EXPORT fcml_st_register fcml_reg_DR1;
extern LIB_EXPORT fcml_st_register fcml_reg_DR2;
extern LIB_EXPORT fcml_st_register fcml_reg_DR3;
extern LIB_EXPORT fcml_st_register fcml_reg_DR4;
extern LIB_EXPORT fcml_st_register fcml_reg_DR5;
extern LIB_EXPORT fcml_st_register fcml_reg_DR6;
extern LIB_EXPORT fcml_st_register fcml_reg_DR7;

extern LIB_EXPORT fcml_st_register fcml_reg_IP;
extern LIB_EXPORT fcml_st_register fcml_reg_EIP;
extern LIB_EXPORT fcml_st_register fcml_reg_RIP;

/* REG.*/
LIB_EXPORT fcml_st_operand LIB_CALL fcml_fn_cu_operand_reg( fcml_st_register *reg );

/* IMM.*/
LIB_EXPORT fcml_st_operand LIB_CALL fcml_fn_cu_operand_unsigned_imm_8( fcml_uint8_t value );
LIB_EXPORT fcml_st_operand LIB_CALL fcml_fn_cu_operand_signed_imm_8( fcml_int8_t value );
LIB_EXPORT fcml_st_operand LIB_CALL fcml_fn_cu_operand_unsigned_imm_16( fcml_uint16_t value );
LIB_EXPORT fcml_st_operand LIB_CALL fcml_fn_cu_operand_signed_imm_16( fcml_int16_t value );
LIB_EXPORT fcml_st_operand LIB_CALL fcml_fn_cu_operand_unsigned_imm_32( fcml_uint32_t value );
LIB_EXPORT fcml_st_operand LIB_CALL fcml_fn_cu_operand_signed_imm_32( fcml_int32_t value );
LIB_EXPORT fcml_st_operand LIB_CALL fcml_fn_cu_operand_unsigned_imm_64( fcml_uint64_t value );
LIB_EXPORT fcml_st_operand LIB_CALL fcml_fn_cu_operand_signed_imm_64( fcml_int64_t value );

/* Memory addressing.*/
LIB_EXPORT fcml_st_operand LIB_CALL fcml_fn_cu_operand_addr_far_pointer_offset16( fcml_int16_t seg, fcml_int16_t offset );
LIB_EXPORT fcml_st_operand LIB_CALL fcml_fn_cu_operand_addr_far_pointer_offset32( fcml_int16_t seg, fcml_int32_t offset );
LIB_EXPORT fcml_st_operand LIB_CALL fcml_fn_cu_operand_addr_offset_16( fcml_int16_t offset );
LIB_EXPORT fcml_st_operand LIB_CALL fcml_fn_cu_operand_addr_offset_32( fcml_int32_t offset );
LIB_EXPORT fcml_st_operand LIB_CALL fcml_fn_cu_operand_addr_offset_abs_64( fcml_int64_t offset );
LIB_EXPORT fcml_st_operand LIB_CALL fcml_fn_cu_operand_addr_offset_rel_64( fcml_int64_t offset );
LIB_EXPORT fcml_st_operand LIB_CALL fcml_fn_cu_operand_addr_disp_16( fcml_int16_t disp );
LIB_EXPORT fcml_st_operand LIB_CALL fcml_fn_cu_operand_addr_disp_32( fcml_int32_t disp );
LIB_EXPORT fcml_st_operand LIB_CALL fcml_fn_cu_operand_addr_disp_64( fcml_int64_t disp );
LIB_EXPORT fcml_st_operand LIB_CALL fcml_fn_cu_operand_addr_b_disp_8( fcml_st_register *base, fcml_int8_t disp );
LIB_EXPORT fcml_st_operand LIB_CALL fcml_fn_cu_operand_addr_b_disp_16( fcml_st_register *base, fcml_int16_t disp );
LIB_EXPORT fcml_st_operand LIB_CALL fcml_fn_cu_operand_addr_b_disp_32( fcml_st_register *base, fcml_int32_t disp );
LIB_EXPORT fcml_st_operand LIB_CALL fcml_fn_cu_operand_addr_b_disp_64( fcml_st_register *base, fcml_int64_t disp );
LIB_EXPORT fcml_st_operand LIB_CALL fcml_fn_cu_operand_addr_is_disp_8( fcml_st_register *index, fcml_uint8_t scale_factor, fcml_int8_t disp );
LIB_EXPORT fcml_st_operand LIB_CALL fcml_fn_cu_operand_addr_is_disp_32( fcml_st_register *index, fcml_uint8_t scale_factor, fcml_int32_t disp );
LIB_EXPORT fcml_st_operand LIB_CALL fcml_fn_cu_operand_addr_is_disp_64( fcml_st_register *index, fcml_uint8_t scale_factor, fcml_int64_t disp );
LIB_EXPORT fcml_st_operand LIB_CALL fcml_fn_cu_operand_addr_bis_disp_8( fcml_st_register *base, fcml_st_register *index, fcml_uint8_t scale_factor, fcml_int8_t disp );
LIB_EXPORT fcml_st_operand LIB_CALL fcml_fn_cu_operand_addr_bis_disp_32( fcml_st_register *base, fcml_st_register *index, fcml_uint8_t scale_factor, fcml_int32_t disp );
LIB_EXPORT fcml_st_operand LIB_CALL fcml_fn_cu_operand_addr_bis_disp_64( fcml_st_register *base, fcml_st_register *index, fcml_uint8_t scale_factor, fcml_int64_t disp );

/* Hints*/
LIB_EXPORT fcml_st_operand LIB_CALL fcml_fn_cu_add_operand_hints( fcml_st_operand operand, fcml_hints hints );

/* Cloning. */

// TODO: Add implementation.

fcml_st_instruction *fcml_fn_cu_clone_instruction( fcml_st_instruction *instruction );
void fcml_fn_cu_free_instruction( fcml_st_instruction *instruction );

/* Some shortcuts for these who prefer to use macros instead of functions.*/

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

#define FCML_FAR_POINTER_16( seg, offset )           fcml_fn_cu_operand_addr_far_pointer_offset16( seg, offset )
#define FCML_FAR_POINTER_32( seg, offset )           fcml_fn_cu_operand_addr_far_pointer_offset32( seg, offset )
#define FCML_OFFSET_16( offset )                     fcml_fn_cu_operand_addr_offset_16( offset )
#define FCML_OFFSET_32( offset )                     fcml_fn_cu_operand_addr_offset_32( offset )
#define FCML_OFFSET_ABS_64( offset )                 fcml_fn_cu_operand_addr_offset_abs_64( offset )
#define FCML_OFFSET_REL_64( offset )                 fcml_fn_cu_operand_addr_offset_rel_64( offset )
#define FCML_DISP_16( offset )                       fcml_fn_cu_operand_addr_disp_16( offset )
#define FCML_DISP_32( offset )                       fcml_fn_cu_operand_addr_disp_32( offset )
#define FCML_DISP_64( offset )                       fcml_fn_cu_operand_addr_disp_64( offset )

#ifdef FCML_USE_SHORT_REG
#define FCML_B_DISP_8( base, offset )                   fcml_fn_cu_operand_addr_b_disp_8( &fcml_reg_##base, offset )
#define FCML_B_DISP_16( base, offset )                  fcml_fn_cu_operand_addr_b_disp_16( &fcml_reg_##base, offset )
#define FCML_B_DISP_32( base, offset )                  fcml_fn_cu_operand_addr_b_disp_32( &fcml_reg_##base, offset )
#define FCML_B_DISP_64( base, offset )                  fcml_fn_cu_operand_addr_b_disp_64( &fcml_reg_##base, offset )
#define FCML_IS_DISP_8( index, scale, offset )          fcml_fn_cu_operand_addr_is_disp_8( &fcml_reg_##index, scale, offset )
#define FCML_IS_DISP_16( index, scale, offset )         fcml_fn_cu_operand_addr_is_disp_32( &fcml_reg_##index, scale, offset )
#define FCML_IS_DISP_32( index, scale, offset )         fcml_fn_cu_operand_addr_is_disp_64( &fcml_reg_##index, scale, offset )
#define FCML_BIS_DISP_8( base, index, scale, offset )   fcml_fn_cu_operand_addr_bis_disp_8( &fcml_reg_##base, &fcml_reg_##index, scale, offset )
#define FCML_BIS_DISP_16( base, index, scale, offset )  fcml_fn_cu_operand_addr_bis_disp_32( &fcml_reg_##base, &fcml_reg_##index, scale, offset )
#define FCML_BIS_DISP_32( base, index, scale, offset )  fcml_fn_cu_operand_addr_bis_disp_64( &fcml_reg_##base, &fcml_reg_##index, scale, offset )
#else
#define FCML_B_DISP_8( base, offset )                   fcml_fn_cu_operand_addr_b_disp_8( &base, offset )
#define FCML_B_DISP_16( base, offset )                  fcml_fn_cu_operand_addr_b_disp_16( &base, offset )
#define FCML_B_DISP_32( base, offset )                  fcml_fn_cu_operand_addr_b_disp_32( &base, offset )
#define FCML_B_DISP_64( base, offset )                  fcml_fn_cu_operand_addr_b_disp_64( &base, offset )
#define FCML_IS_DISP_8( index, scale, offset )          fcml_fn_cu_operand_addr_is_disp_8( &index, scale, offset )
#define FCML_IS_DISP_16( index, scale, offset )         fcml_fn_cu_operand_addr_is_disp_32( &index, scale, offset )
#define FCML_IS_DISP_32( index, scale, offset )         fcml_fn_cu_operand_addr_is_disp_64( &index, scale, offset )
#define FCML_BIS_DISP_8( base, index, scale, offset )   fcml_fn_cu_operand_addr_bis_disp_8( &base, &index, scale, offset )
#define FCML_BIS_DISP_16( base, index, scale, offset )  fcml_fn_cu_operand_addr_bis_disp_32( &base, &index, scale, offset )
#define FCML_BIS_DISP_32( base, index, scale, offset )  fcml_fn_cu_operand_addr_bis_disp_64( &base, &index, scale, offset )
#endif

#ifdef __cplusplus
}
#endif

#endif /* FCML_COMMON_UTILS_H_ */
