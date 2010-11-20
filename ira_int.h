#ifndef IRA_INT_H_INCLUDED
#define IRA_INT_H_INCLUDED

#include <stdint.h>
#include <stdio.h>
#include "ira.h"

/* Structures used to store information about memory. */

struct memory_stream {
    void *base_address; /* Base address of memory. */
    uint32_t offset; /* Offset. */
    uint32_t size; /* Size. */
};

/* Methods used for streaming. */

enum seek_type {
    START = 0,
    END,
    CURRENT
};

void stream_seek( struct memory_stream *stream, uint32_t offset, enum seek_type type );

uint8_t stream_read( struct memory_stream *stream, int *result );

uint8_t stream_peek( struct memory_stream *stream, int *result );

/* Gets size of the data to read. */
uint32_t stream_size( struct memory_stream *stream );

/* Disassemblation context. */

enum prefix_types {
    GROUP_1 = 1,
    GROUP_2,
    GROUP_3,
    GROUP_4,
    REX
};

struct instruction_prefix {
    uint8_t prefix;             /* Prefix itself. */
    uint8_t prefix_type;        /* Type of prefix, see enumeration above. */
    uint8_t mandatory_prefix;   /* 1 if prefix can be treated as mendatory one. */
};

struct diss_context {
    enum operation_mode mode; /* Architecture. */
    uint16_t operand_size_attribute; /* Operand size attribute. */
    uint16_t address_size_attribute; /* Address size attribute. */
    struct instruction_prefix prefixes[12];      /* Identified prefixes. */
    uint8_t instruction_prefix_count;    /* Number of prefixes identified for instruction. */
    struct memory_stream *stream; /* Stream. */
};

/* Structures used to build disassemblation arrays. */

typedef int arguments_decoder( struct diss_context* );

/* Internal representation of decoding tree. */

struct decoding_option {
    uint8_t option_type;  /* Option type: Opcode, Prefix, Escape etc. */
    uint8_t data;         /* Data used by disassembler to check if this is a appropriate option. */
};

struct decoding_options {
    int count;
    struct decoding_option **decoding_option;
};

struct primary_opcode_details {
    int escape_bytes_count;
    uint8_t escape_bytes[3];
    uint8_t mandatory_prefix;
};

struct primary_opcode_decoding {
    void *decoding_details;
    arguments_decoder *decoder;
};

struct primary_opcode_def {
    uint8_t opcode_details_count;
    struct primary_opcode_details opcode_details[20];
};

void identify_prefixes( struct diss_context *context );

void disassemble_default( struct diss_context *context, struct disassemble_result *result );

/* Structures used to describe instructions. */

struct opcode_desc {
	char *name_override; // Mnemonic, if there is another mnemonic available for this opcode.
	uint16_t allowed_prefixes; // Flags describing allowed prefixes.
	uint32_t opcode_flags; // Some flags that contains various information about opcode.
	uint8_t primary_opcode; // Index of primary opcode in table below.
	uint8_t opcode[3]; // Opcode bytes.
	uint8_t opperand_1; // Addressing of first instruction operand .
	uint8_t oppernad_2; // Second etc.
	uint8_t opperand_3;
	uint8_t opperand_4;
};

struct instruction_desc {
	char *name; // Mnemonic.
	uint8_t opcode_desc_count; // Number of opcodes' descriptions.
	struct opcode_desc *opcodes; // Opcodes' descriptions.
};

/* Operands encoding */

#define _IRA_NA	0x00

#define _IRA_MODRM_BASE 0x80 // Base for ModRM based operands.

#define _IRA_MODRM(x) _MOD_RM_BASE + x

/* Instruction definitions. */

extern struct instruction_desc _instructions_desc[];

#endif // IRA_INT_H_INCLUDED
