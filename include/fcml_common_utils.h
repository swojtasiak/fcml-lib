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

LIB_EXPORT fcml_st_register fcml_reg_AL;
LIB_EXPORT fcml_st_register fcml_reg_AX;
LIB_EXPORT fcml_st_register fcml_reg_EAX;
LIB_EXPORT fcml_st_register fcml_reg_RAX;
LIB_EXPORT fcml_st_register fcml_reg_MM0;
LIB_EXPORT fcml_st_register fcml_reg_XMM0;
LIB_EXPORT fcml_st_register fcml_reg_YMM0;

LIB_EXPORT fcml_st_register fcml_reg_CL;
LIB_EXPORT fcml_st_register fcml_reg_CX;
LIB_EXPORT fcml_st_register fcml_reg_ECX;
LIB_EXPORT fcml_st_register fcml_reg_RCX;
LIB_EXPORT fcml_st_register fcml_reg_MM1;
LIB_EXPORT fcml_st_register fcml_reg_XMM1;
LIB_EXPORT fcml_st_register fcml_reg_YMM1;

LIB_EXPORT fcml_st_register fcml_reg_DL;
LIB_EXPORT fcml_st_register fcml_reg_DX;
LIB_EXPORT fcml_st_register fcml_reg_EDX;
LIB_EXPORT fcml_st_register fcml_reg_RDX;
LIB_EXPORT fcml_st_register fcml_reg_MM2;
LIB_EXPORT fcml_st_register fcml_reg_XMM2;
LIB_EXPORT fcml_st_register fcml_reg_YMM2;

LIB_EXPORT fcml_st_register fcml_reg_BL;
LIB_EXPORT fcml_st_register fcml_reg_BX;
LIB_EXPORT fcml_st_register fcml_reg_EBX;
LIB_EXPORT fcml_st_register fcml_reg_RBX;
LIB_EXPORT fcml_st_register fcml_reg_MM3;
LIB_EXPORT fcml_st_register fcml_reg_XMM3;
LIB_EXPORT fcml_st_register fcml_reg_YMM3;

LIB_EXPORT fcml_st_register fcml_reg_AH;
LIB_EXPORT fcml_st_register fcml_reg_SPL;
LIB_EXPORT fcml_st_register fcml_reg_SP;
LIB_EXPORT fcml_st_register fcml_reg_ESP;
LIB_EXPORT fcml_st_register fcml_reg_RSP;
LIB_EXPORT fcml_st_register fcml_reg_MM4;
LIB_EXPORT fcml_st_register fcml_reg_XMM4;
LIB_EXPORT fcml_st_register fcml_reg_YMM4;

LIB_EXPORT fcml_st_register fcml_reg_CH;
LIB_EXPORT fcml_st_register fcml_reg_BPL;
LIB_EXPORT fcml_st_register fcml_reg_BP;
LIB_EXPORT fcml_st_register fcml_reg_EBP;
LIB_EXPORT fcml_st_register fcml_reg_RBP;
LIB_EXPORT fcml_st_register fcml_reg_MM5;
LIB_EXPORT fcml_st_register fcml_reg_XMM5;
LIB_EXPORT fcml_st_register fcml_reg_YMM5;

LIB_EXPORT fcml_st_register fcml_reg_DH;
LIB_EXPORT fcml_st_register fcml_reg_SIL;
LIB_EXPORT fcml_st_register fcml_reg_SI;
LIB_EXPORT fcml_st_register fcml_reg_ESI;
LIB_EXPORT fcml_st_register fcml_reg_RSI;
LIB_EXPORT fcml_st_register fcml_reg_MM6;
LIB_EXPORT fcml_st_register fcml_reg_XMM6;
LIB_EXPORT fcml_st_register fcml_reg_YMM6;

LIB_EXPORT fcml_st_register fcml_reg_BH;
LIB_EXPORT fcml_st_register fcml_reg_DIL;
LIB_EXPORT fcml_st_register fcml_reg_DI;
LIB_EXPORT fcml_st_register fcml_reg_EDI;
LIB_EXPORT fcml_st_register fcml_reg_RDI;
LIB_EXPORT fcml_st_register fcml_reg_MM7;
LIB_EXPORT fcml_st_register fcml_reg_XMM7;
LIB_EXPORT fcml_st_register fcml_reg_YMM7;

LIB_EXPORT fcml_st_register fcml_reg_R8L;
LIB_EXPORT fcml_st_register fcml_reg_R8W;
LIB_EXPORT fcml_st_register fcml_reg_R8D;
LIB_EXPORT fcml_st_register fcml_reg_R8;
LIB_EXPORT fcml_st_register fcml_reg_XMM8;
LIB_EXPORT fcml_st_register fcml_reg_YMM8;

LIB_EXPORT fcml_st_register fcml_reg_R9L;
LIB_EXPORT fcml_st_register fcml_reg_R9W;
LIB_EXPORT fcml_st_register fcml_reg_R9D;
LIB_EXPORT fcml_st_register fcml_reg_R9;
LIB_EXPORT fcml_st_register fcml_reg_XMM9;
LIB_EXPORT fcml_st_register fcml_reg_YMM9;

LIB_EXPORT fcml_st_register fcml_reg_R10L;
LIB_EXPORT fcml_st_register fcml_reg_R10W;
LIB_EXPORT fcml_st_register fcml_reg_R10D;
LIB_EXPORT fcml_st_register fcml_reg_R10;
LIB_EXPORT fcml_st_register fcml_reg_XMM10;
LIB_EXPORT fcml_st_register fcml_reg_YMM10;

LIB_EXPORT fcml_st_register fcml_reg_R11L;
LIB_EXPORT fcml_st_register fcml_reg_R11W;
LIB_EXPORT fcml_st_register fcml_reg_R11D;
LIB_EXPORT fcml_st_register fcml_reg_R11;
LIB_EXPORT fcml_st_register fcml_reg_XMM11;
LIB_EXPORT fcml_st_register fcml_reg_YMM11;

LIB_EXPORT fcml_st_register fcml_reg_R12L;
LIB_EXPORT fcml_st_register fcml_reg_R12W;
LIB_EXPORT fcml_st_register fcml_reg_R12D;
LIB_EXPORT fcml_st_register fcml_reg_R12;
LIB_EXPORT fcml_st_register fcml_reg_XMM12;
LIB_EXPORT fcml_st_register fcml_reg_YMM12;

LIB_EXPORT fcml_st_register fcml_reg_R13L;
LIB_EXPORT fcml_st_register fcml_reg_R13W;
LIB_EXPORT fcml_st_register fcml_reg_R13D;
LIB_EXPORT fcml_st_register fcml_reg_R13;
LIB_EXPORT fcml_st_register fcml_reg_XMM13;
LIB_EXPORT fcml_st_register fcml_reg_YMM13;

LIB_EXPORT fcml_st_register fcml_reg_R14L;
LIB_EXPORT fcml_st_register fcml_reg_R14W;
LIB_EXPORT fcml_st_register fcml_reg_R14D;
LIB_EXPORT fcml_st_register fcml_reg_R14;
LIB_EXPORT fcml_st_register fcml_reg_XMM14;
LIB_EXPORT fcml_st_register fcml_reg_YMM14;

LIB_EXPORT fcml_st_register fcml_reg_R15L;
LIB_EXPORT fcml_st_register fcml_reg_R15W;
LIB_EXPORT fcml_st_register fcml_reg_R15D;
LIB_EXPORT fcml_st_register fcml_reg_R15;
LIB_EXPORT fcml_st_register fcml_reg_XMM15;
LIB_EXPORT fcml_st_register fcml_reg_YMM15;

LIB_EXPORT fcml_st_register fcml_reg_ES;
LIB_EXPORT fcml_st_register fcml_reg_CS;
LIB_EXPORT fcml_st_register fcml_reg_SS;
LIB_EXPORT fcml_st_register fcml_reg_DS;
LIB_EXPORT fcml_st_register fcml_reg_FS;
LIB_EXPORT fcml_st_register fcml_reg_GS;

LIB_EXPORT fcml_st_register fcml_reg_ST0;
LIB_EXPORT fcml_st_register fcml_reg_ST1;
LIB_EXPORT fcml_st_register fcml_reg_ST2;
LIB_EXPORT fcml_st_register fcml_reg_ST3;
LIB_EXPORT fcml_st_register fcml_reg_ST4;
LIB_EXPORT fcml_st_register fcml_reg_ST5;
LIB_EXPORT fcml_st_register fcml_reg_ST6;
LIB_EXPORT fcml_st_register fcml_reg_ST7;

LIB_EXPORT fcml_st_register fcml_reg_CR0;
LIB_EXPORT fcml_st_register fcml_reg_CR2;
LIB_EXPORT fcml_st_register fcml_reg_CR3;
LIB_EXPORT fcml_st_register fcml_reg_CR4;
LIB_EXPORT fcml_st_register fcml_reg_CR8;

LIB_EXPORT fcml_st_register fcml_reg_DR0;
LIB_EXPORT fcml_st_register fcml_reg_DR1;
LIB_EXPORT fcml_st_register fcml_reg_DR2;
LIB_EXPORT fcml_st_register fcml_reg_DR3;
LIB_EXPORT fcml_st_register fcml_reg_DR4;
LIB_EXPORT fcml_st_register fcml_reg_DR5;
LIB_EXPORT fcml_st_register fcml_reg_DR6;
LIB_EXPORT fcml_st_register fcml_reg_DR7;

LIB_EXPORT fcml_st_register fcml_reg_IP;
LIB_EXPORT fcml_st_register fcml_reg_EIP;
LIB_EXPORT fcml_st_register fcml_reg_RIP;

/* REG.*/
fcml_st_operand LIB_CALL LIB_EXPORT fcml_fn_cu_operand_reg( fcml_st_register *reg );

/* IMM.*/
fcml_st_operand LIB_CALL LIB_EXPORT fcml_fn_cu_operand_unsigned_imm_8( fcml_uint8_t value );
fcml_st_operand LIB_CALL LIB_EXPORT fcml_fn_cu_operand_signed_imm_8( fcml_int8_t value );
fcml_st_operand LIB_CALL LIB_EXPORT fcml_fn_cu_operand_unsigned_imm_16( fcml_uint16_t value );
fcml_st_operand LIB_CALL LIB_EXPORT fcml_fn_cu_operand_signed_imm_16( fcml_int16_t value );
fcml_st_operand LIB_CALL LIB_EXPORT fcml_fn_cu_operand_unsigned_imm_32( fcml_uint32_t value );
fcml_st_operand LIB_CALL LIB_EXPORT fcml_fn_cu_operand_signed_imm_32( fcml_int32_t value );
fcml_st_operand LIB_CALL LIB_EXPORT fcml_fn_cu_operand_unsigned_imm_64( fcml_uint64_t value );
fcml_st_operand LIB_CALL LIB_EXPORT fcml_fn_cu_operand_signed_imm_64( fcml_int64_t value );

/* Memory addressing.*/
fcml_st_operand LIB_CALL LIB_EXPORT fcml_fn_cu_operand_addr_far_pointer_offset16( fcml_int16_t seg, fcml_int16_t offset );
fcml_st_operand LIB_CALL LIB_EXPORT fcml_fn_cu_operand_addr_far_pointer_offset32( fcml_int16_t seg, fcml_int32_t offset );
fcml_st_operand LIB_CALL LIB_EXPORT fcml_fn_cu_operand_addr_offset_16( fcml_int16_t offset );
fcml_st_operand LIB_CALL LIB_EXPORT fcml_fn_cu_operand_addr_offset_32( fcml_int32_t offset );
fcml_st_operand LIB_CALL LIB_EXPORT fcml_fn_cu_operand_addr_offset_abs_64( fcml_int64_t offset );
fcml_st_operand LIB_CALL LIB_EXPORT fcml_fn_cu_operand_addr_offset_rel_64( fcml_int64_t offset );
fcml_st_operand LIB_CALL LIB_EXPORT fcml_fn_cu_operand_addr_disp_16( fcml_int16_t disp );
fcml_st_operand LIB_CALL LIB_EXPORT fcml_fn_cu_operand_addr_disp_32( fcml_int32_t disp );
fcml_st_operand LIB_CALL LIB_EXPORT fcml_fn_cu_operand_addr_disp_64( fcml_int64_t disp );
fcml_st_operand LIB_CALL LIB_EXPORT fcml_fn_cu_operand_addr_b_disp_8( fcml_st_register *base, fcml_int8_t disp );
fcml_st_operand LIB_CALL LIB_EXPORT fcml_fn_cu_operand_addr_b_disp_16( fcml_st_register *base, fcml_int16_t disp );
fcml_st_operand LIB_CALL LIB_EXPORT fcml_fn_cu_operand_addr_b_disp_32( fcml_st_register *base, fcml_int32_t disp );
fcml_st_operand LIB_CALL LIB_EXPORT fcml_fn_cu_operand_addr_b_disp_64( fcml_st_register *base, fcml_int64_t disp );
fcml_st_operand LIB_CALL LIB_EXPORT fcml_fn_cu_operand_addr_is_disp_8( fcml_st_register *index, fcml_uint8_t scale_factor, fcml_int8_t disp );
fcml_st_operand LIB_CALL LIB_EXPORT fcml_fn_cu_operand_addr_is_disp_32( fcml_st_register *index, fcml_uint8_t scale_factor, fcml_int32_t disp );
fcml_st_operand LIB_CALL LIB_EXPORT fcml_fn_cu_operand_addr_is_disp_64( fcml_st_register *index, fcml_uint8_t scale_factor, fcml_int64_t disp );
fcml_st_operand LIB_CALL LIB_EXPORT fcml_fn_cu_operand_addr_bis_disp_8( fcml_st_register *base, fcml_st_register *index, fcml_uint8_t scale_factor, fcml_int8_t disp );
fcml_st_operand LIB_CALL LIB_EXPORT fcml_fn_cu_operand_addr_bis_disp_32( fcml_st_register *base, fcml_st_register *index, fcml_uint8_t scale_factor, fcml_int32_t disp );
fcml_st_operand LIB_CALL LIB_EXPORT fcml_fn_cu_operand_addr_bis_disp_64( fcml_st_register *base, fcml_st_register *index, fcml_uint8_t scale_factor, fcml_int64_t disp );

/* Hints*/
fcml_st_operand LIB_CALL LIB_EXPORT fcml_fn_cu_add_operand_hints( fcml_st_operand operand, fcml_hints hints );

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
