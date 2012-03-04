#ifndef IRA_INT_H_INCLUDED
#define IRA_INT_H_INCLUDED

#include <stdint.h>
#include <stdio.h>
#include "ira.h"

#define _IRA_TRUE 1
#define _IRA_FALSE 0

/* Internal error codes */

#define _IRA_INT_ERROR_NO_ERROR						0x00
#define _IRA_INT_ERROR_CODE_UNEXPECTED_EOS			0x01
#define _IRA_INT_ERROR_OUT_OF_MEMORY				0x02
#define _IRA_INT_ERROR_ILLEGAL_ARGUMENT				0x03
#define _IRA_INT_ERROR_ILLEGAL_ADDRESSING			0x04

#define _IRA_INT_ERROR_INSTRUCTION_NOT_ENCODABLE	0x05
#define _IRA_INT_ERROR_SYNTAX_NOT_SUPPORTED			0x06
#define _IRA_INT_ERROR_ILLEGAL_INSTRUCTION			0x07

/* Structures used to store information about memory. */

struct ira_memory_stream {
    void *base_address; /* Base address of memory. */
    uint32_t offset; /* Offset. */
    uint32_t size; /* Size. */
};

/* Methods used for streaming. */

enum ira_seek_type {
    IRA_START = 0,
    IRA_END,
    IRA_CURRENT
};

void _ira_stream_seek( struct ira_memory_stream *stream, uint32_t offset, enum ira_seek_type type );

uint8_t _ira_stream_read( struct ira_memory_stream *stream, int *result );

uint8_t _ira_stream_peek( struct ira_memory_stream *stream, int *result );

/* Gets size of the data to read. */
uint32_t _ira_stream_size( struct ira_memory_stream *stream );

/* Reads specified number of bytes from stream and stores them in given buffer. */
int _ira_stream_read_bytes( struct ira_memory_stream *stream, void *buffer , int size);

/* ModRM decoding. */

struct ira_decoded_mod_rm {
	// Set to _IRA_TRUE if ModRM exists and addressing has been decoded for the current instruction.
	uint8_t decoded_addressing;
	// Set to _IRA_TRUE if ModRM exists and register has been decoded for the current instruction.
	uint8_t decoded_reg;
	// ModRM byte.
	n_byte raw_mod_rm;
	// SIB byte.
	n_byte raw_sib;
	// REX prefix.
	n_byte raw_rex;
	// Base register.
	struct ira_register base_reg;
	// Index register.
	struct ira_register index_reg;
	// Scale factor value for 32 and 64 bit addressing modes.
	n_byte scale;
	// Displacement value.
	struct ira_displacement displacement;
	// Register decoded if "mod" = 3.
	struct ira_register reg;
	// Register operand encoded in "reg" field of the ModRM.
	struct ira_register operand_reg;
};

/* Disassemblation context. */

enum ira_prefix_types {
    IRA_GROUP_1 = 1,
    IRA_GROUP_2,
    IRA_GROUP_3,
    IRA_GROUP_4,
    IRA_REX
};

struct ira_decoding_context {
	// Operand size attribute.
	uint8_t effective_operand_size_attribute;
	// Address size attribute.
	uint8_t effective_address_size_attribute;
	// Decoded prefixes.
	struct ira_instruction_prefix prefixes[_IRA_PREFIXES_COUNT];
	// Base opcode bytes without opcode fields applied.
	uint8_t base_opcodes[3];
	// Opcode bytes without mandatory prefixes.
	uint8_t opcodes[3];
	// Number of opcode bytes.
	uint8_t opcodes_count;
	// Primary opcode byte.
	uint8_t primary_opcode_index;
	// Number of prefixes decoded for instruction.
	uint8_t instruction_prefix_count;
	// Decoded ModRM.
	struct ira_decoded_mod_rm mod_rm;
	// Instruction size. This value is only available during post processing.
	int32_t instruction_size;
};

struct ira_diss_context {
	// Architecture.
    enum ira_operation_mode mode;
    // Operand size attribute.
    uint8_t operand_size_attribute;
    // Address size attribute.
    uint8_t address_size_attribute;
    // Context that is shared by methods taking part in the decoding process.
    struct ira_decoding_context decoding_context;
    // Stream.
    struct ira_memory_stream *stream;
    // Instruction pointer.
    union ira_instruction_pointer instruction_pointer;
};

/* Returns 1 is there is given prefix found for given instruction. */
int _ira_diss_context_is_prefix_available( struct ira_diss_context *context, uint8_t prefix );

/* Gets REX prefix. */
uint8_t _ira_diss_context_get_REX_prefix( struct ira_diss_context *context, int *found );

/* Decoding arguments. */

/* Structure that can be used to pass register type to operand decoding function. */
struct ira_reg_type_args {
	// Register type.
	enum ira_register_type reg_type;
	// Register number.
	int reg;
};

/* Structure that can be used to pass immediate value type/size to operand decoding function. */
struct ira_immediate_type_args {
	// Immediate value type.
	enum ira_immediate_data_type immediate_data_type;
};

/* Structure that can be used to pass register type and its size to operand decoding function. */
struct ira_modrm_decoding_args {
	// Register type.
	enum ira_register_type reg_type;
	// Register size.
	int operand_register_size;
	// Size directive.
	int size_directive;
};

typedef int (*ira_size_directive_provider)( struct ira_diss_context *context );

/* Structure used to decode  */
struct ira_modm_decoding_args {
	// Size directive provider.
	ira_size_directive_provider size_directive_provider;
};

/* Disassemblation tree. */

struct ira_diss_tree_opcode {
	struct ira_diss_tree_opcode* opcodes[256];
	struct ira_diss_tree_instruction_decoding *instructions;
};

/* Operand wrapper. */

typedef int (*ira_instruction_operand_handler)( struct ira_diss_context *context, struct ira_instruction_operand *operand, struct ira_instruction_operand *istruction_operands[4] );

struct ira_instruction_operand_wrapper {
	// Instruction operand.
	struct ira_instruction_operand operand;
	// Optional post processor, that can be registered by decoder.
	ira_instruction_operand_handler post_processor;
};

/* Decoders responsible for instruction disassemblation. */
typedef int (*ira_instruction_decoder)( struct ira_diss_context *context, struct ira_diss_tree_instruction_decoding *instruction, struct ira_disassemble_result *result );

/* Decoders responsible for operand disassemblation. */
typedef int (*ira_operand_decoder)( struct ira_diss_context *context, struct ira_instruction_operand_wrapper *operand, void *args );

struct ira_operand_decoding {
	// Operand access mode.
	enum ira_access_mode access_mode;
	// Operand decoder.
	ira_operand_decoder decoder;
	// Optional arguments passed to operand decoder.
	void *args;
};

struct ira_diss_tree_instruction_decoding {
	/* Pointer to the next decoding. There is no need to provide additional structure for one directional list */
	struct ira_diss_tree_instruction_decoding *next_instruction_decoding;
	/* Opcodes. */
	uint8_t opcodes[3];
	/* Instruction mnemonic */
	char *mnemonic;
	/* Flags that describe prefixes usage. */
	uint16_t allowed_prefixes;
	/* Flags that describe some details of opcodes. */
	uint32_t opcode_flags;
	/* Instruction decoder. */
	ira_instruction_decoder instruction_decoder;
	/* Function used to decode instruction operands. */
	struct ira_operand_decoding operand_decodings[4];
};

struct ira_diss_tree_instruction_details {
};

extern struct ira_diss_tree_opcode* _ira_disassemblation_tree[256];

/* Structures used to describe instructions. */

struct ira_opcode_desc {
	char *mnemonic_override; // Mnemonic, if there is another mnemonic available for this opcode.
	uint16_t allowed_prefixes; // Flags describing allowed prefixes.
	uint32_t opcode_flags; // Some flags that contains various information about opcode.
	uint8_t opcode[3]; // Opcode bytes.
	uint16_t opperand_1; // Addressing of first instruction operand .
	uint16_t opperand_2; // Second etc.
	uint16_t opperand_3;
	uint16_t opperand_4;
};

struct ira_instruction_desc {
	// Mnemonic.
	char *mnemonic;
	// Type of the instruction.
	uint8_t instruction_type;
	// Number of opcodes' descriptions.
	uint8_t opcode_desc_count;
	// Opcodes' descriptions.
	struct ira_opcode_desc *opcodes;
};

/* Macro for bit manipulations. */

#define _IRA_GET_BIT(x,y)	( ( x >> y ) & 0x01 )

/* ModR/M decoding. */

#define _IRA_MODRM_MOD(x)			( x >> 6 )
#define _IRA_MODRM_REG_OPCODE(x)	( ( x & 0x38 ) >> 3 )
#define _IRA_MODRM_RM(x)			( x & 0x07 )

/* SIB decoding */

#define _IRA_SIB_SS(x)				( x >> 6 )
#define _IRA_SIB_INDEX(x)			( ( x & 0x38 ) >> 3 )
#define _IRA_SIB_BASE(x)			( x & 0x07 )

/* REX decoding */

#define _IRA_REX_W(x)				_IRA_GET_BIT(x, 3)
#define _IRA_REX_R(x)				_IRA_GET_BIT(x, 2)
#define _IRA_REX_X(x)				_IRA_GET_BIT(x, 1)
#define _IRA_REX_B(x)				_IRA_GET_BIT(x, 0)

/* Prefixes flags. */

#define _IRA_PREFIX_REX_W_1(x)				_IRA_GET_BIT(x,03)
#define _IRA_PREFIX_MANDATORY_66(x) 		_IRA_GET_BIT(x,12)
#define _IRA_PREFIX_MANDATORY_F2(x) 		_IRA_GET_BIT(x,13)
#define _IRA_PREFIX_MANDATORY_F3(x) 		_IRA_GET_BIT(x,14)

/* TTTN - Conditional instructions. */


/* Opcode flags. */

#define _IRA_REG_FIELD_SIZE								3
#define _IRA_REG_FIELD_POS								0

#define _IRA_REG_FIELD_NUMBER_OF_REGISTERS				8

#define _IRA_OPCODE_FLAGS_OPCODE_FIELD_REG(x)			( x & 0x00000001 )
#define _IRA_OPCODE_FLAGS_OPCODE_FIELD_TTTN(x)			( x & 0x00000040 )
#define _IRA_OPCODE_FLAGS_POS(x)						( ( x & 0x00000700 ) >> 8 )
#define _IRA_OPCODE_FLAGS_OPCODE_EXT(x) 				( ( x & 0x00003800 ) >> 11 )
#define _IRA_OPCODE_FLAGS_OPCODE_REX_EXT(x)				( ( x & 0x00007800 ) >> 11 )
#define _IRA_OPCODE_FLAGS_OPCODE_IS_MODRM(x) 			_IRA_GET_BIT(x,15)
#define _IRA_OPCODE_FLAGS_OPCODE_IS_EXT(x) 				_IRA_GET_BIT(x,16)
#define _IRA_OPCODE_FLAGS_OPCODE_IS_REX_EXT(x) 			_IRA_GET_BIT(x,17)
#define _IRA_OPCODE_FLAGS_OPCODE_NUM(x) 				( ( x & 0x000C0000 ) >> 18 )
#define _IRA_OPCODE_FLAGS_PRIMARY_OPCODE(x) 			( ( x & 0x00300000 ) >> 20 )
#define _IRA_OPCODE_FLAGS_64_BIT_MODE_SUPPORTED(x)		( x & 0x00800000 )
#define _IRA_OPCODE_FLAGS_16_32_BIT_MODE_SUPPORTED(x)	( x & 0x00400000 )
#define _IRA_OPCODE_FLAGS_EOSA_16(x)					( x & 0x01000000 )
#define _IRA_OPCODE_FLAGS_EOSA_32(x)					( x & 0x02000000 )
#define _IRA_OPCODE_FLAGS_EOSA_64(x)					( x & 0x04000000 )
#define _IRA_OPCODE_FLAGS_IS_EOSA_RESTRICTION(x)		( x & 0x07000000 )


/* Instruction types. */

#define _IRA_IT_IA			0x00

/* Operand register size. Adding new values here, you probably have to modify _ira_modrm_decode_register() also. */

// Register size forced to 8 bits.
#define _IRA_OR_8			0
// Register size forced to 16 bits.
#define _IRA_OR_16			1
// Choose operand size (register) using EOSA.
#define _IRA_OR_DEFAULT		2

/* Size directive */

// If operand size directive is set to _IRA_DEFAULT_SIZE_DIRECTIVE,
// size is set to EOSA.
#define _IRA_DEFAULT_SIZE_DIRECTIVE	-1

/* Operands encoding */

#define _IRA_OPERANDS_SIZEOF(x)	( sizeof( x ) / sizeof( struct ira_opcode_desc ) )

#define _IA_INSTRUCTION(x,y) { x, _IRA_IT_IA, _IRA_OPERANDS_SIZEOF(y), y }

// Source operand (Reads).
#define _IRA_READ	0x0000

// Destination operand (Writes).
#define _IRA_WRITE	0x8000

#define _IRA_NA	0x0000

#define _IRA_OPERAND_IB						0x0100
// imm8 sign extended to effective operand size attribute.
#define _IRA_OPERAND_IB_EX_EOSA				0x0200
#define _IRA_OPERAND_IW						0x0300
#define _IRA_OPERAND_IW_EX_EOSA				0x0400
#define _IRA_OPERAND_ID						0x0500
// imm32 sign extended to effective operand size attribute.
#define _IRA_OPERAND_ID_EX_EOSA				0x0600
#define _IRA_OPERAND_IO						0x0700
#define _IRA_OPERAND_IO_EOSA				0x0800
// Immediate value with size calculated using EOSA.
#define _IRA_OPERAND_IMM_EOSA				0x0900
#define _IRA_OPERAND_REG_ACCUMULATOR_8		0x0A00
#define _IRA_OPERAND_REG_ACCUMULATOR_OSA	0x0B00
#define _IRA_OPERAND_REG_ACCUMULATOR_8_W	( _IRA_OPERAND_REG_ACCUMULATOR_8   | _IRA_WRITE )
#define _IRA_OPERAND_REG_ACCUMULATOR_OSA_W	( _IRA_OPERAND_REG_ACCUMULATOR_OSA | _IRA_WRITE )

// Base for ModRM based operands.
#define _IRA_MODRM_BASE 					0x0C00

/* Operands for ModRM encoding. */

#define _IRA_RM_8		0
#define _IRA_R_8		1
#define _IRA_RM_16		2
#define _IRA_R_16		3
#define _IRA_RM			4
#define _IRA_R			5
#define _IRA_RM_MMX		6
#define _IRA_R_MMX		7
#define _IRA_RM_XMM_128	8
#define _IRA_R_XMM_128	9
#define _IRA_RM_XMM_64	10
#define _IRA_R_XMM_64	11
#define _IRA_RM_XMM_32	12
#define _IRA_R_XMM_32	13
// m16&16, m32&32.
#define _IRA_OSA_MM		14
// m8
#define _IRA_M_8		15

/* ModRM based operands. */

#define _IRA_MODRM(x) ( _IRA_MODRM_BASE + x )

#define _IRA_OPERAND_MODRM_RM_8			_IRA_MODRM(_IRA_RM_8)
#define _IRA_OPERAND_MODRM_RM_8_W		( _IRA_OPERAND_MODRM_RM_8 | _IRA_WRITE )
#define _IRA_OPERAND_MODRM_RM_16		_IRA_MODRM(_IRA_RM_16)
#define _IRA_OPERAND_MODRM_RM_16_W		( _IRA_OPERAND_MODRM_RM_16 | _IRA_WRITE )
#define _IRA_OPERAND_MODRM_RM			_IRA_MODRM(_IRA_RM)
#define _IRA_OPERAND_MODRM_RM_W			( _IRA_OPERAND_MODRM_RM | _IRA_WRITE )
#define _IRA_OPERAND_MODRM_R_8			_IRA_MODRM(_IRA_R_8)
#define _IRA_OPERAND_MODRM_R_8_W		( _IRA_OPERAND_MODRM_R_8 | _IRA_WRITE )
#define _IRA_OPERAND_MODRM_R_16			_IRA_MODRM(_IRA_R_16)
#define _IRA_OPERAND_MODRM_R_16_W		( _IRA_OPERAND_MODRM_R_16 | _IRA_WRITE )
#define _IRA_OPERAND_MODRM_R		_IRA_MODRM(_IRA_R)
#define _IRA_OPERAND_MODRM_R_W		( _IRA_OPERAND_MODRM_R | _IRA_WRITE )
#define _IRA_OPERAND_MODRM_RM_MMX		_IRA_MODRM(_IRA_RM_MMX)
#define _IRA_OPERAND_MODRM_RM_MMX_W		( _IRA_OPERAND_MODRM_RM_MMX | _IRA_WRITE )
#define _IRA_OPERAND_MODRM_R_MMX		_IRA_MODRM(_IRA_R_MMX)
#define _IRA_OPERAND_MODRM_R_MMX_W		( _IRA_OPERAND_MODRM_R_MMX | _IRA_WRITE )
#define _IRA_OPERAND_MODRM_RM_XMM_128	_IRA_MODRM(_IRA_RM_XMM_128)
#define _IRA_OPERAND_MODRM_RM_XMM_128_W	( _IRA_OPERAND_MODRM_RM_XMM_128 | _IRA_WRITE )
#define _IRA_OPERAND_MODRM_R_XMM_128	_IRA_MODRM(_IRA_R_XMM_128)
#define _IRA_OPERAND_MODRM_R_XMM_128_W	( _IRA_OPERAND_MODRM_R_XMM_128 | _IRA_WRITE )
#define _IRA_OPERAND_MODRM_RM_XMM_64	_IRA_MODRM(_IRA_RM_XMM_64)
#define _IRA_OPERAND_MODRM_RM_XMM_64_W	( _IRA_OPERAND_MODRM_RM_XMM_64 | _IRA_WRITE )
#define _IRA_OPERAND_MODRM_R_XMM_64		_IRA_MODRM(_IRA_R_XMM_64)
#define _IRA_OPERAND_MODRM_R_XMM_64_W	( _IRA_OPERAND_MODRM_R_XMM_64 | _IRA_WRITE )
#define _IRA_OPERAND_MODRM_RM_XMM_32	_IRA_MODRM(_IRA_RM_XMM_32)
#define _IRA_OPERAND_MODRM_RM_XMM_32_W	( _IRA_OPERAND_MODRM_RM_XMM_32 | _IRA_WRITE )
#define _IRA_OPERAND_MODRM_R_XMM_32		_IRA_MODRM(_IRA_R_XMM_32)
#define _IRA_OPERAND_MODRM_R_XMM_32_W	( _IRA_OPERAND_MODRM_R_XMM_32 | _IRA_WRITE )
#define _IRA_OPERAND_MODRM_MM_OSA		_IRA_MODRM(_IRA_OSA_MM)
#define _IRA_OPERAND_MODRM_M_8			_IRA_MODRM(_IRA_M_8)
#define _IRA_OPERAND_MODRM_M_8_W		(_IRA_OPERAND_MODRM_M_8 | _IRA_WRITE)


// Implicit register.
#define _IRA_IMPLICIT_REG_BASE						0x0D00
#define _IRA_IMPLICIT_REG(reg_type,reg_num)			( _IRA_IMPLICIT_REG_BASE | reg_type << 4 | reg_num )

// Register field in opcode byte.
#define _IRA_OPERAND_OPCODE_REG_BASE				0x0E00
#define _IRA_OPERAND_OPCODE_REG(reg_type)			( _IRA_OPERAND_OPCODE_REG_BASE | reg_type )

// Relative addressing.
#define _IRA_OPERAND_IMMEDIATE_DIS_RELATIVE			0x0F00

// Addressing based on ModR/M value for CALL.
#define _IRA_OPERAND_CALL_RM						0x1000

// Far pointers.
#define _IRA_OPERAND_FAR_POINTER					0x1100

// Far indirect pointer.
#define _IRA_OPERAND_FAR_POINTER_INDIRECT			0x1200

/* Externals. */

extern struct ira_instruction_desc _ira_instructions_desc[];

#endif // IRA_INT_H_INCLUDED
