#ifndef IRA_INT_H_INCLUDED
#define IRA_INT_H_INCLUDED

#include <stdint.h>
#include <stdio.h>
#include "ira.h"

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

void ira_stream_seek( struct ira_memory_stream *stream, uint32_t offset, enum ira_seek_type type );

uint8_t ira_stream_read( struct ira_memory_stream *stream, int *result );

uint8_t ira_stream_peek( struct ira_memory_stream *stream, int *result );

/* Gets size of the data to read. */
uint32_t ira_stream_size( struct ira_memory_stream *stream );

/* Disassemblation context. */

enum ira_prefix_types {
    IRA_GROUP_1 = 1,
    IRA_GROUP_2,
    IRA_GROUP_3,
    IRA_GROUP_4,
    IRA_REX
};

struct ira_instruction_prefix {
    uint8_t prefix;             /* Prefix itself. */
    uint8_t prefix_type;        /* Type of prefix, see enumeration above. */
    uint8_t mandatory_prefix;   /* 1 if prefix can be treated as mendatory one. */
};

struct ira_decoding_context {
	struct ira_instruction_prefix prefixes[12];      /* Identified prefixes. */
	uint8_t instruction_prefix_count;    /* Number of prefixes identified for instruction. */
	uint8_t mod_rm; /* ModR/M byte. */
	uint8_t sib; /* SIB byte. */
};

struct ira_diss_context {
    enum ira_operation_mode mode; /* Architecture. */
    uint16_t operand_size_attribute; /* Operand size attribute. */
    uint16_t address_size_attribute; /* Address size attribute. */
    struct ira_decoding_context decoding_context;
    struct ira_memory_stream *stream; /* Stream. */
};

/* Disassemblation tree. */

/* Decoders responsible for instruction disassemblation. */
typedef struct ira_disassemble_result (*ira_instruction_decoder)( struct ira_diss_context *context );

/* Decoders responsible for operand disassemblation. */
typedef struct ira_instruction_operand (*ira_operand_decoder)( struct ira_diss_context *context );

struct ira_diss_tree_opcode {
	struct ira_diss_tree_opcode* opcodes[256];
	struct ira_diss_tree_instruction_decoding *instructions;
};

struct ira_diss_tree_instruction_decoding {
	/* Pointer to the next decoding. There is no need to provide additional structure for one directional list */
	struct ira_diss_tree_instruction_decoding *next_instruction_decoding;
	/* Instruction mnemonic */
	char *mnemonic;
	/* Flags that describe prefixes usage. */
	uint16_t allowed_prefixes;
	/* Flags that describe some details of opcodes. */
	uint32_t opcode_flags;
	/* Function used to decode instruction operands. */
	ira_operand_decoder operand_decoders[4];
};

struct ira_diss_tree_instruction_details {
};

extern struct ira_diss_tree_opcode* _ira_disassemblation_tree[256];

/* Structures used to describe instructions. */

#define _IRA_OPCODE_FLAGS_OPCODE_NUM(x) ( ( (uint32_t)x & 0x000C0000 ) >> 18 )

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
	char *mnemonic; // Mnemonic.
	uint8_t opcode_desc_count; // Number of opcodes' descriptions.
	struct ira_opcode_desc *opcodes; // Opcodes' descriptions.
};

/* Operands encoding */

#define _IRA_NA	0x00

#define _IRA_OPERAND_IB		0x01
#define _IRA_OPERAND_IW		0x02
#define _IRA_OPERAND_ID		0x03
#define _IRA_OPERAND_IO		0x04

#define _IRA_MODRM_BASE 0x80 // Base for ModRM based operands.

#define _IRA_MODRM(x) _MOD_RM_BASE + x

/* Instruction definitions. */

void ira_identify_prefixes( struct ira_diss_context *context );

void ira_disassemble_default( struct ira_diss_context *context, struct ira_disassemble_result *result );

/* Externals. */

extern struct ira_instruction_desc _ira_instructions_desc[];

#endif // IRA_INT_H_INCLUDED
