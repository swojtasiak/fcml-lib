/*
 * ira_def.h
 *
 *  Created on: 27-12-2012
 *      Author: tAs
 */

#ifndef IRA_DEF_H_
#define IRA_DEF_H_

#include "fcml_types.h"
#define FCML_OS_EOSA		0xFFFF
#define FCML_OS_EASA		0xFFFE

/* Constants used to encode operand size on one byte. Used only in instruction descriptions. */

// Take into account that every size is given in a number of bytes.
#define FCML_EOS_UNDEFINED	0
#define FCML_EOS_512B		FCML_EOS_UNDEFINED
#define FCML_EOS_BYTE		1
#define FCML_EOS_WORD		2
#define FCML_EOS_DWORD		4
#define FCML_EOS_FWORD		6
#define FCML_EOS_QWORD		8
#define FCML_EOS_TBYTE		10
#define FCML_EOS_OWORD		16
#define FCML_EOS_YWORD		32

// Dynamic encoded operand sizes calculated at runtime.

// Operand size calculated by Effective Operand Size Attribute and Effective Address Size Attribute.
#define FCML_EOS_EOSA		0xFF
#define FCML_EOS_EASA		0xFE

// Operand size calculated on L field.
#define FCML_EOS_L			0xFD

// Oprand sizes that cannot be simply written as number of bytes.
#define FCML_EOS_14_28		0xFC
#define FCML_EOS_94_108		0xFB
#define FCML_EOS_32_64		0xFA

// True if encoded operand size is a dynamic one.
#define FCML_IS_EOS_DYNAMIC(x)	( ( x & 0x80 ) != 0 )

/* Structures used to describe instructions with they all allowed addressing modes. */
typedef struct fcml_st_def_addr_mode_desc {
	// Mnemonic, if there is another mnemonic available for this opcode.
	fcml_string mnemonic_override;
	// Flags describing allowed prefixes.
	fcml_uint16_t allowed_prefixes;
	// Some flags that contains various information about opcode.
	fcml_uint32_t opcode_flags;
	// Opcode bytes.
	fcml_uint8_t opcode[3];
	// Addressing of instruction operands.
	fcml_uint32_t opperand_1;
	fcml_uint32_t opperand_2;
	fcml_uint32_t opperand_3;
	fcml_uint32_t opperand_4;
} fcml_st_def_addr_mode_desc;

/* Describes one addressing mode of instruction. */
typedef struct fcml_st_def_instruction_description {
	// Mnemonic.
	fcml_string mnemonic;
	// Type of the instruction.
	fcml_uint8_t instruction_type;
	// Number of opcodes' descriptions.
	fcml_uint8_t opcode_desc_count;
	// Opcodes' descriptions.
	struct fcml_st_def_addr_mode_desc *addr_modes;
} fcml_st_def_instruction_description;

/* Operands encoding */

#define FCML_IA_INSTRUCTION(x,y) { x, FCML_IT_IA, ( sizeof( y ) / sizeof( struct fcml_st_def_addr_mode_desc ) ), y }

/*********************************
 * Addressing modes.
 *********************************/

/* Instruction types. */

#define FCML_IT_IA			0x00

// Source operand (Reads).
#define _IRA_READ	0x00000000

// Destination operand (Writes).
#define _IRA_WRITE	0x80000000

#define _IRA_NA	0x00000000

// todo: zmienic to na jedno parametryzowane makro, ktore jako parametr przyjmie wielkosc wartosci natychmiastowej.
#define _IRA_OPERAND_IB						0x01000000
// imm8 sign extended to effective operand size attribute.
#define _IRA_OPERAND_IB_EX_EOSA				0x02000000
#define _IRA_OPERAND_IW						0x03000000
#define _IRA_OPERAND_IW_EX_EOSA				0x04000000
#define _IRA_OPERAND_ID						0x05000000
// imm32 sign extended to effective operand size attribute.
#define _IRA_OPERAND_ID_EX_EOSA				0x06000000
#define _IRA_OPERAND_IO						0x07000000
#define _IRA_OPERAND_IO_EOSA				0x08000000
// Immediate value with size calculated using EOSA.
#define _IRA_OPERAND_IMM_EOSA				0x09000000

// todo: wywalic to, mamy explicit register, tylko komplikutje model opisu trybow adreowania.
#define _IRA_OPERAND_REG_ACCUMULATOR_8		0x0A000000
#define _IRA_OPERAND_REG_ACCUMULATOR_OSA	0x0B000000
#define _IRA_OPERAND_REG_ACCUMULATOR_8_W	( _IRA_OPERAND_REG_ACCUMULATOR_8   | _IRA_WRITE )
#define _IRA_OPERAND_REG_ACCUMULATOR_OSA_W	( _IRA_OPERAND_REG_ACCUMULATOR_OSA | _IRA_WRITE )

// Base for ModRM based operands.
#define _IRA_MODRM_BASE 					0x0C000000

/* Operands for ModRM encoding. */

#define _IRA_RM_8		0
#define _IRA_R_8		1
#define _IRA_RM_16		2
#define _IRA_R_16		3
#define _IRA_RM_32		4
#define _IRA_R_32		5
#define _IRA_RM_64		6
#define _IRA_R_64		7
#define _IRA_RM			8
#define _IRA_R			9
#define _IRA_RM_MMX		10
#define _IRA_R_MMX		11
#define _IRA_RM_XMM_128	12
#define _IRA_R_XMM_128	13
#define _IRA_RM_XMM_64	14
#define _IRA_R_XMM_64	15
#define _IRA_RM_XMM_32	16
#define _IRA_R_XMM_32	17
// m16&16, m32&32.
#define _IRA_OSA_MM		18
// m8-m128
#define _IRA_M_8		19
#define _IRA_M_16		20
#define _IRA_M_32		21
#define _IRA_M_64		22
#define _IRA_M_80		23
#define _IRA_M_128		24
#define _IRA_M_14_28	25
#define _IRA_M_94_108	26
#define _IRA_M_512B		27
#define _IRA_M_UNDEF	28

/* ModRM based operands. */

#define _IRA_MODRM(x) ( _IRA_MODRM_BASE + x )

// todo: czy to nie ejst nadmiarowe? sprobowal przepisac na parametryzowane makra.


// todo: nie implicit tylko explicit
// todo: dodac kodowanie wilkosci rejestru na podstawie encoded operand size.
// Implicit registers with size determined by operand-size-attribute.
#define _IRA_EXPLICIT_REG_BASE_OSA						0x0D000000
#define _IRA_EXPLICIT_REG_OSA(reg_type,reg_num)			( _IRA_EXPLICIT_REG_BASE_OSA | reg_type << 4 | reg_num )

// Implicit registers with size determined by address-size-attribute.
#define _IRA_EXPLICIT_REG_BASE_ASA						0x0E000000
#define _IRA_EXPLICIT_REG_ASA(reg_type,reg_num)			( _IRA_EXPLICIT_REG_BASE_ASA | reg_type << 4 | reg_num )

#define _IRA_EXPLICIT_REG_BASE							0x0F000000
#define _IRA_EXPLICIT_REG(reg_type, reg_num, reg_size)	( _IRA_EXPLICIT_REG_BASE | reg_type << 20 | reg_num << 16 | reg_size )

// Register field in opcode byte.
#define _IRA_OPERAND_OPCODE_REG_BASE					0x10000000
#define _IRA_OPERAND_OPCODE_REG(reg_type, reg_size)	( _IRA_OPERAND_OPCODE_REG_BASE | reg_type << 16 | reg_size)

// Relative addressing.
#define _IRA_OPERAND_IMMEDIATE_DIS_RELATIVE_EOSA	0x11000000

// rel8
#define _IRA_OPERAND_IMMEDIATE_DIS_RELATIVE_R_8		0x12000000

// Far pointers.
#define _IRA_OPERAND_FAR_POINTER					0x13000000

// Far indirect pointer.
#define _IRA_OPERAND_FAR_POINTER_INDIRECT			0x14000000

// Addressing by explicit GPR register. (Used by CMPS for instance.)
#define _IRA_EXPLICIT_GPS_REG_ADDRESSING_BASE		0x15000000
#define _IRA_EXPLICIT_GPS_REG_ADDRESSING(reg_num, encoded_operand_size, encoded_segment_register)	( _IRA_EXPLICIT_GPS_REG_ADDRESSING_BASE | reg_num << 16 | encoded_operand_size << 8 | encoded_segment_register )

// It allows defining explicit IMM8 operand type. See INT instruction.
#define _IRA_EXPLICIT_OPERAND_IB_BASE				0x16000000
#define _IRA_EXPLICIT_OPERAND_IB(value)				( _IRA_EXPLICIT_OPERAND_IB_BASE | value )

// todo: Mozna sie zastanowic nad dodaniem flag M, R zeby mona bylo wybierac tryb adreacji rm/r/m
// Allows to encode all common ModR/M based addressing modes using only one macro.

#define _IRA_RMF_R		0x01
#define _IRA_RMF_M		0x02
#define _IRA_RMF_RM		( _IRA_RMF_R | _IRA_RMF_M )
// TODO: Zastanowic sie czy do sterowania flagami nie da ie wykorzystac nowych bitow MOD3 ModNot3 zamiast bezposredniego ich podawania.
#define _IRA_OPERAND_RM_BASE						0x17000000
#define _IRA_OPERAND_RM(reg_type, encoded_register_operand_size, encoded_memory_operand_size, flags )		( _IRA_OPERAND_RM_BASE | encoded_memory_operand_size << 16 | encoded_register_operand_size << 8 | reg_type << 4 | flags )
#define _IRA_OPERAND_RM_W(reg_type, encoded_register_operand_size, encoded_memory_operand_size, flags )		( _IRA_OPERAND_RM(reg_type, encoded_register_operand_size, encoded_memory_operand_size, flags) | _IRA_WRITE )

// TODO: do usuniecia, wytarczy _IRA_OPERAND_RM z flaga: _IRA_RMF_M
#define _IRA_OPERAND_M_BASE							0x18000000
#define _IRA_OPERAND_M( memory_operand_size )		( _IRA_OPERAND_M_BASE | memory_operand_size )

#define _IRA_OPERAND_R_BASE											0x19000000
#define _IRA_OPERAND_R( reg_type, encoded_register_operand_size )	( _IRA_OPERAND_R_BASE | ( encoded_register_operand_size << 4 ) | reg_type )

#define _IRA_OPERAND_SEGMENT_RELATIVE_OFFSET_BASE	0x1A000000
#define _IRA_OPERAND_SEGMENT_RELATIVE_OFFSET( operand_size, encoded_segment_register )	( _IRA_OPERAND_SEGMENT_RELATIVE_OFFSET_BASE | operand_size << 8 | encoded_segment_register )

#define _IRA_VEX_VVVV_REG_BASE									0x1B000000
#define _IRA_VEX_VVVV_REG( reg_type, register_operand_size )	( _IRA_VEX_VVVV_REG_BASE | ( register_operand_size << 4 ) | reg_type )

#define _IRA_OPERAND_IS4							0x1C000000

// VSIB operand decoding.

// Vector index register.
#define _IRA_VSIB_XMM	0x01
#define _IRA_VSIB_YMM	0x02

// Index value size.
#define _IRA_VSIB_IS_32	0x01
#define _IRA_VSIB_IS_64	0x02

#define _IRA_OPERAND_VSIB_BASE						0x1D000000
#define _IRA_OPERAND_VSIB( vector_index_register, index_value_size )		( _IRA_OPERAND_VSIB_BASE | vector_index_register << 2 | index_value_size )

// Shorthands

#define _IRA_OPERAND_MODRM_RM_8				_IRA_OPERAND_RM(IRA_REG_GPR, FCML_EOS_BYTE, FCML_EOS_BYTE, _IRA_RMF_RM )
#define _IRA_OPERAND_MODRM_RM_8_W			( _IRA_OPERAND_MODRM_RM_8 | _IRA_WRITE )
#define _IRA_OPERAND_MODRM_RM_16			_IRA_OPERAND_RM(IRA_REG_GPR, FCML_EOS_WORD, FCML_EOS_WORD, _IRA_RMF_RM )
#define _IRA_OPERAND_MODRM_RM_16_W			( _IRA_OPERAND_MODRM_RM_16 | _IRA_WRITE )
#define _IRA_OPERAND_MODRM_RM_32			_IRA_OPERAND_RM(IRA_REG_GPR, FCML_EOS_DWORD, FCML_EOS_DWORD, _IRA_RMF_RM )
#define _IRA_OPERAND_MODRM_RM_32_W			( _IRA_OPERAND_MODRM_RM_32 | _IRA_WRITE )
#define _IRA_OPERAND_MODRM_RM_64			_IRA_OPERAND_RM(IRA_REG_GPR, FCML_EOS_QWORD, FCML_EOS_QWORD, _IRA_RMF_RM )
#define _IRA_OPERAND_MODRM_RM_64_W			( _IRA_OPERAND_MODRM_RM_64 | _IRA_WRITE )
#define _IRA_OPERAND_MODRM_RM				_IRA_OPERAND_RM(IRA_REG_GPR, FCML_EOS_EOSA, FCML_EOS_EOSA, _IRA_RMF_RM )
#define _IRA_OPERAND_MODRM_RM_W				( _IRA_OPERAND_MODRM_RM | _IRA_WRITE )
#define _IRA_OPERAND_MODRM_R_8				_IRA_OPERAND_R(IRA_REG_GPR, FCML_EOS_BYTE )
#define _IRA_OPERAND_MODRM_R_8_W			( _IRA_OPERAND_MODRM_R_8 | _IRA_WRITE )
#define _IRA_OPERAND_MODRM_R_16				_IRA_OPERAND_R(IRA_REG_GPR, FCML_EOS_WORD )
#define _IRA_OPERAND_MODRM_R_16_W			( _IRA_OPERAND_MODRM_R_16 | _IRA_WRITE )
#define _IRA_OPERAND_MODRM_R_32				_IRA_OPERAND_R(IRA_REG_GPR, FCML_EOS_DWORD )
#define _IRA_OPERAND_MODRM_R_32_W			( _IRA_OPERAND_MODRM_R_32 | _IRA_WRITE )
#define _IRA_OPERAND_MODRM_R_64				_IRA_OPERAND_R(IRA_REG_GPR, FCML_EOS_QWORD )
#define _IRA_OPERAND_MODRM_R_64_W			( _IRA_OPERAND_MODRM_R_64 | _IRA_WRITE )
#define _IRA_OPERAND_MODRM_R				_IRA_OPERAND_R(IRA_REG_GPR, FCML_EOS_EOSA )
#define _IRA_OPERAND_MODRM_R_W				( _IRA_OPERAND_MODRM_R | _IRA_WRITE )
#define _IRA_OPERAND_MODRM_M_8				_IRA_OPERAND_RM(IRA_NO_REG, FCML_EOS_UNDEFINED, FCML_EOS_BYTE, _IRA_RMF_M )
#define _IRA_OPERAND_MODRM_M_8_W			(_IRA_OPERAND_MODRM_M_8 | _IRA_WRITE)
#define _IRA_OPERAND_MODRM_M_16				_IRA_OPERAND_RM(IRA_NO_REG, FCML_EOS_UNDEFINED, FCML_EOS_WORD, _IRA_RMF_M )
#define _IRA_OPERAND_MODRM_M_16_W			(_IRA_OPERAND_MODRM_M_16 | _IRA_WRITE)
#define _IRA_OPERAND_MODRM_M_32				_IRA_OPERAND_RM(IRA_NO_REG, FCML_EOS_UNDEFINED, FCML_EOS_DWORD, _IRA_RMF_M )
#define _IRA_OPERAND_MODRM_M_32_W			(_IRA_OPERAND_MODRM_M_32 | _IRA_WRITE)
#define _IRA_OPERAND_MODRM_M_64				_IRA_OPERAND_RM(IRA_NO_REG, FCML_EOS_UNDEFINED, FCML_EOS_QWORD, _IRA_RMF_M )
#define _IRA_OPERAND_MODRM_M_64_W			(_IRA_OPERAND_MODRM_M_64 | _IRA_WRITE)
#define _IRA_OPERAND_MODRM_M_80				_IRA_OPERAND_RM(IRA_NO_REG, FCML_EOS_UNDEFINED, FCML_EOS_TBYTE, _IRA_RMF_M )
#define _IRA_OPERAND_MODRM_M_80_W			(_IRA_OPERAND_MODRM_M_80 | _IRA_WRITE)
#define _IRA_OPERAND_MODRM_M_128			_IRA_OPERAND_RM(IRA_NO_REG, FCML_EOS_UNDEFINED, FCML_EOS_OWORD, _IRA_RMF_M )
#define _IRA_OPERAND_MODRM_M_128_W			(_IRA_OPERAND_MODRM_M_128 | _IRA_WRITE)
#define _IRA_OPERAND_MODRM_M_256			_IRA_OPERAND_RM(IRA_NO_REG, FCML_EOS_UNDEFINED, FCML_EOS_YWORD, _IRA_RMF_M )
#define _IRA_OPERAND_MODRM_M_256_W			(_IRA_OPERAND_MODRM_M_256 | _IRA_WRITE)
#define _IRA_OPERAND_MODRM_M_14_28			_IRA_OPERAND_RM(IRA_NO_REG, FCML_EOS_UNDEFINED, FCML_EOS_14_28, _IRA_RMF_M )
#define _IRA_OPERAND_MODRM_M_14_28_W		(_IRA_OPERAND_MODRM_M_14_28 | _IRA_WRITE)
#define _IRA_OPERAND_MODRM_M_94_108			_IRA_OPERAND_RM(IRA_NO_REG, FCML_EOS_UNDEFINED, FCML_EOS_94_108, _IRA_RMF_M )
#define _IRA_OPERAND_MODRM_M_94_108_W		(_IRA_OPERAND_MODRM_M_94_108 | _IRA_WRITE)
#define _IRA_OPERAND_MODRM_M_512B			_IRA_OPERAND_RM(IRA_NO_REG, FCML_EOS_UNDEFINED, FCML_EOS_512B, _IRA_RMF_M )
#define _IRA_OPERAND_MODRM_M_512B_W			(_IRA_OPERAND_MODRM_M_512B | _IRA_WRITE)
#define _IRA_OPERAND_MODRM_M_UNDEF			_IRA_OPERAND_RM(IRA_NO_REG, FCML_EOS_UNDEFINED, FCML_EOS_UNDEFINED, _IRA_RMF_M )
#define _IRA_OPERAND_MODRM_M_UNDEF_W		(_IRA_OPERAND_MODRM_M_UNDEF | _IRA_WRITE)
#define _IRA_OPERAND_MODRM_MM_OSA			_IRA_OPERAND_RM(IRA_NO_REG, FCML_EOS_UNDEFINED, FCML_EOS_32_64, _IRA_RMF_M )
#define _IRA_OPERAND_MODRM_RM_MMX			_IRA_OPERAND_RM(IRA_REG_SIMD, FCML_EOS_QWORD, FCML_EOS_QWORD, _IRA_RMF_RM )
#define _IRA_OPERAND_MODRM_RM_MMX_W			( _IRA_OPERAND_MODRM_RM_MMX | _IRA_WRITE )
#define _IRA_OPERAND_MODRM_RM_MMX_32		_IRA_OPERAND_RM(IRA_REG_SIMD, FCML_EOS_QWORD, FCML_EOS_DWORD, _IRA_RMF_RM )
#define _IRA_OPERAND_MODRM_RM_MMX_32_W		( _IRA_OPERAND_MODRM_RM_MMX_32 | _IRA_WRITE )
#define _IRA_OPERAND_MODRM_R_MMX			_IRA_OPERAND_R(IRA_REG_SIMD, FCML_EOS_QWORD )
#define _IRA_OPERAND_MODRM_R_MMX_W			( _IRA_OPERAND_MODRM_R_MMX | _IRA_WRITE )
#define _IRA_OPERAND_MODRM_RM_YMM_256		_IRA_OPERAND_RM(IRA_REG_SIMD, FCML_EOS_YWORD, FCML_EOS_YWORD, _IRA_RMF_RM )
#define _IRA_OPERAND_MODRM_RM_YMM_256_W		( _IRA_OPERAND_MODRM_RM_YMM_256 | _IRA_WRITE )
#define _IRA_OPERAND_MODRM_RM_XMM_128		_IRA_OPERAND_RM(IRA_REG_SIMD, FCML_EOS_OWORD, FCML_EOS_OWORD, _IRA_RMF_RM )
#define _IRA_OPERAND_MODRM_RM_XMM_128_W		( _IRA_OPERAND_MODRM_RM_XMM_128 | _IRA_WRITE )
#define _IRA_OPERAND_MODRM_RM_XMM_64		_IRA_OPERAND_RM(IRA_REG_SIMD, FCML_EOS_OWORD, FCML_EOS_QWORD, _IRA_RMF_RM )
#define _IRA_OPERAND_MODRM_RM_XMM_64_W		( _IRA_OPERAND_MODRM_RM_XMM_64 | _IRA_WRITE )
#define _IRA_OPERAND_MODRM_RM_XMM_32		_IRA_OPERAND_RM(IRA_REG_SIMD, FCML_EOS_OWORD, FCML_EOS_DWORD, _IRA_RMF_RM )
#define _IRA_OPERAND_MODRM_RM_XMM_32_W		( _IRA_OPERAND_MODRM_RM_XMM_32 | _IRA_WRITE )
#define _IRA_OPERAND_MODRM_RM_XMM_16		_IRA_OPERAND_RM(IRA_REG_SIMD, FCML_EOS_OWORD, FCML_EOS_WORD, _IRA_RMF_RM )
#define _IRA_OPERAND_MODRM_RM_XMM_16_W		( _IRA_OPERAND_MODRM_RM_XMM_16 | _IRA_WRITE )
#define _IRA_OPERAND_MODRM_R_XMM			_IRA_OPERAND_R(IRA_REG_SIMD, FCML_EOS_OWORD )
#define _IRA_OPERAND_MODRM_R_XMM_W			( _IRA_OPERAND_MODRM_R_XMM | _IRA_WRITE )
#define _IRA_OPERAND_MODRM_R_YMM			_IRA_OPERAND_R(IRA_REG_SIMD, FCML_EOS_YWORD )
#define _IRA_OPERAND_MODRM_R_YMM_W			( _IRA_OPERAND_MODRM_R_YMM | _IRA_WRITE )
#define _IRA_OPERAND_MODRM_RM_SIMD			_IRA_OPERAND_RM(IRA_REG_SIMD, FCML_EOS_L, FCML_EOS_L, _IRA_RMF_RM )
#define _IRA_OPERAND_MODRM_RM_SIMD_W		( _IRA_OPERAND_MODRM_RM_SIMD | _IRA_WRITE )
#define _IRA_OPERAND_MODRM_RM_SIMD_EOSA		_IRA_OPERAND_RM(IRA_REG_SIMD, FCML_EOS_EOSA, FCML_EOS_EOSA, _IRA_RMF_RM )
#define _IRA_OPERAND_MODRM_RM_SIMD_EOSA_W	( _IRA_OPERAND_MODRM_RM_SIMD_EOSA | _IRA_WRITE )
#define _IRA_OPERAND_MODRM_RM_SIMD_128		_IRA_OPERAND_RM(IRA_REG_SIMD, FCML_EOS_EOSA, FCML_EOS_OWORD, _IRA_RMF_RM )
#define _IRA_OPERAND_MODRM_RM_SIMD_128_W	( _IRA_OPERAND_MODRM_RM_SIMD_128 | _IRA_WRITE )
#define _IRA_OPERAND_MODRM_RM_SIMD_64		_IRA_OPERAND_RM(IRA_REG_SIMD, FCML_EOS_EOSA, FCML_EOS_QWORD, _IRA_RMF_RM )
#define _IRA_OPERAND_MODRM_RM_SIMD_64_W		( _IRA_OPERAND_MODRM_RM_SIMD_64 | _IRA_WRITE )
#define _IRA_OPERAND_MODRM_RM_SIMD_32		_IRA_OPERAND_RM(IRA_REG_SIMD, FCML_EOS_EOSA, FCML_EOS_DWORD, _IRA_RMF_RM )
#define _IRA_OPERAND_MODRM_RM_SIMD_32_W		( _IRA_OPERAND_MODRM_RM_SIMD_32 | _IRA_WRITE )
#define _IRA_OPERAND_MODRM_RM_SIMD_16		_IRA_OPERAND_RM(IRA_REG_SIMD, FCML_EOS_EOSA, FCML_EOS_WORD, _IRA_RMF_RM )
#define _IRA_OPERAND_MODRM_RM_SIMD_16_W		( _IRA_OPERAND_MODRM_RM_SIMD_16 | _IRA_WRITE )
#define _IRA_OPERAND_MODRM_RM_SIMD_8		_IRA_OPERAND_RM(IRA_REG_SIMD, FCML_EOS_EOSA, FCML_EOS_BYTE, _IRA_RMF_RM )
#define _IRA_OPERAND_MODRM_RM_SIMD_8_W		( _IRA_OPERAND_MODRM_RM_SIMD_8 | _IRA_WRITE )
#define _IRA_OPERAND_MODRM_R_SIMD			_IRA_OPERAND_R(IRA_REG_SIMD, FCML_EOS_L )
#define _IRA_OPERAND_MODRM_R_SIMD_W			( _IRA_OPERAND_MODRM_R_SIMD | _IRA_WRITE )
#define _IRA_OPERAND_MODRM_R_SIMD_EOSA		_IRA_OPERAND_R(IRA_REG_SIMD, FCML_EOS_EOSA )
#define _IRA_OPERAND_MODRM_R_SIMD_EOSA_W	( _IRA_OPERAND_MODRM_R_SIMD | _IRA_WRITE )
#define _IRA_OPERAND_MODRM_M_SIMD			_IRA_OPERAND_RM(IRA_NO_REG, FCML_EOS_UNDEFINED, FCML_EOS_L, _IRA_RMF_M )
#define _IRA_OPERAND_MODRM_M_SIMD_W			( _IRA_OPERAND_MODRM_M_SIMD | _IRA_WRITE )
#define _IRA_OPERAND_MODRM_M_SIMD_EOSA		_IRA_OPERAND_RM(IRA_NO_REG, FCML_EOS_UNDEFINED, FCML_EOS_EOSA, _IRA_RMF_M )
#define _IRA_OPERAND_MODRM_M_SIMD_EOSA_W	( _IRA_OPERAND_MODRM_M_SIMD | _IRA_WRITE )

// Shorthands for VVVV addressing.

#define _IRA_VEX_VVVV_SIMD_REG		_IRA_VEX_VVVV_REG( IRA_REG_SIMD, FCML_OS_EOSA )
#define _IRA_VEX_VVVV_XMM_REG		_IRA_VEX_VVVV_REG( IRA_REG_SIMD, _IRA_OS_XMMWORD )
#define _IRA_VEX_VVVV_YMM_REG		_IRA_VEX_VVVV_REG( IRA_REG_SIMD, _IRA_OS_YMMWORD )

/* Segment registers encoding. */

#define _IRA_SEG_ALLOW_OVERRIDE		0x80
#define _IRA_SEG_DENY_OVERRIDE		0x00
#define _IRA_SEG_ENCODE_REGISTER( reg_num, override )		( reg_num | override )
#define _IRA_SEG_DECODE_IS_OVERRIDE_ALLOWED( encoded )		( _IRA_SEG_ALLOW_OVERRIDE & encoded )
#define _IRA_SEG_DECODE_REGISTER( encoded )					( encoded & ~_IRA_SEG_ALLOW_OVERRIDE )

/* Externals. */

extern struct fcml_st_def_instruction_description fcml_ext_instructions_def[];

#define _IRA_EMPTY_MNEMONIC	""

/* Functions. */

/* Methods. */

//! Decoding given encoded operand size.
/*!
 * \brief Decodes given operand size using provided EOSA. Some functions have operand size described on 8 bits using
 * IRA_EOS_ constants. This form of operand size description notation is used to allow encoding more than 128
 * bits operand sizes using only one byte.
 *
 * \param encoded_operand_size Size directive to decode.
 * \return Decoded operand size.
 */
uint16_t _ira_common_decode_8b_operand_size( uint8_t encoded_operand_size );

uint16_t fcml_fn_def_decode_operand_size( uint8_t encoded_operand_size, uint8_t effective_operand_size_attribute, uint8_t effective_address_size_attribute, fcml_bool l_prefix );


#endif /* IRA_DEF_H_ */
