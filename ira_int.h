#ifndef IRA_INT_H_INCLUDED
#define IRA_INT_H_INCLUDED

#include <stdint.h>
#include <stdio.h>
#include "ira.h"

#define _IRA_TRUE 1
#define _IRA_FALSE 0

/* Internal error codes */

#define _IRA_INT_ERROR_NO_ERROR				0x00
#define _IRA_INT_ERROR_CODE_UNEXPECTED_EOS	0x01
#define _IRA_INT_ERROR_OUT_OF_MEMORY		0x02
#define _IRA_INT_ERROR_ILLEGAL_ARGUMENT		0x03

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
	// Number of prefixes decoded for instruction.
	uint8_t instruction_prefix_count;
	// Decoded ModRM.
	struct ira_decoded_mod_rm mod_rm;
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
};

/* Returns 1 is there is given prefix found for given instruction. */
int _ira_diss_context_is_prefix_available( struct ira_diss_context *context, uint8_t prefix );

/* Gets REX prefix. */
uint8_t _ira_diss_context_get_REX_prefix( struct ira_diss_context *context, int *found );

/* Disassemblation tree. */

struct ira_diss_tree_opcode {
	struct ira_diss_tree_opcode* opcodes[256];
	struct ira_diss_tree_instruction_decoding *instructions;
};

/* Decoders responsible for instruction disassemblation. */
typedef int (*ira_instruction_decoder)( struct ira_diss_context *context, struct ira_diss_tree_instruction_decoding *instruction, struct ira_disassemble_result *result );

/* Decoders responsible for operand disassemblation. */
typedef int (*ira_operand_decoder)( struct ira_diss_context *context, struct ira_instruction_operand *operand );

struct ira_operand_decoding {
	// Operand access mode.
	enum ira_access_mode access_mode;
	// Operand decoder.
	ira_operand_decoder decoder;
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
	uint8_t opperand_1; // Addressing of first instruction operand .
	uint8_t opperand_2; // Second etc.
	uint8_t opperand_3;
	uint8_t opperand_4;
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

#define _IRA_PREFIX_REX(x) 					_IRA_GET_BIT(x,11)
#define _IRA_PREFIX_MANDATORY_66(x) 		_IRA_GET_BIT(x,12)
#define _IRA_PREFIX_MANDATORY_F2(x) 		_IRA_GET_BIT(x,13)
#define _IRA_PREFIX_MANDATORY_F3(x) 		_IRA_GET_BIT(x,14)

/* Opcode flags. */

#define _IRA_OPCODE_FLAGS_OPCODE_EXT(x) 		( ( x & 0x00007000 ) >> 12 )
#define _IRA_OPCODE_FLAGS_OPCODE_IS_MODRM(x) 	_IRA_GET_BIT(x,15)
#define _IRA_OPCODE_FLAGS_OPCODE_IS_EXT(x) 		_IRA_GET_BIT(x,16)
#define _IRA_OPCODE_FLAGS_OPCODE_IS_REX_EXT(x) 	_IRA_GET_BIT(x,17)
#define _IRA_OPCODE_FLAGS_OPCODE_NUM(x) 		( ( x & 0x000C0000 ) >> 18 )

/* Instruction types. */

#define _IRA_IT_IA			0x00

/* Operand register size */

#define _IRA_OR_8			0
#define _IRA_OR_DEFAULT		1

/* Operands */

#define _IRA_RM_8		0
#define _IRA_R_8		1

/* Operands encoding */

#define _IRA_R	0x00
#define _IRA_W	0x80

#define _IRA_NA	0x00

#define _IRA_OPERAND_IB		0x01
#define _IRA_OPERAND_IB_W	( _IRA_OPERAND_IB | _IRA_W )
#define _IRA_OPERAND_IW		0x02
#define _IRA_OPERAND_IW_W	( _IRA_OPERAND_IW | _IRA_W )
#define _IRA_OPERAND_ID		0x03
#define _IRA_OPERAND_ID_W	( _IRA_OPERAND_ID | _IRA_W )
#define _IRA_OPERAND_IO		0x04
#define _IRA_OPERAND_IO_W	( _IRA_OPERAND_IO | _IRA_W )


#define _IRA_MODRM_BASE 0x40 // Base for ModRM based operands.

#define _IRA_MODRM(x) ( _IRA_MODRM_BASE + x )

#define _IRA_OPERAND_MODRM_RM_8		_IRA_MODRM(_IRA_RM_8)
#define _IRA_OPERAND_MODRM_RM_8_W	( _IRA_OPERAND_MODRM_RM_8 | _IRA_W )
#define _IRA_OPERAND_MODRM_R_8		_IRA_MODRM(_IRA_R_8)
#define _IRA_OPERAND_MODRM_R_8_W	( _IRA_OPERAND_MODRM_R_8 | _IRA_W )

/* Externals. */

extern struct ira_instruction_desc _ira_instructions_desc[];

#endif // IRA_INT_H_INCLUDED
