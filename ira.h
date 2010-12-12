#ifndef IRA_H_INCLUDED
#define IRA_H_INCLUDED

#include <stdint.h>

#define _IRA_OPERANDS_COUNT						4
#define _IRA_PREFIXES_COUNT						12

enum ira_operation_mode {
    IRA_MOD_16BIT,
    IRA_MOD_32BIT, // IA32/IA32e.
    IRA_MOD_64BIT
};

enum ira_result_code {
    RC_OK = 0,
    RC_ERROR_ILLEGAL_OPERATION_MODE,
    RC_ERROR_ILLEGAL_ADDRESS_ATTRIBUTE_SIZE,
    /* When disassembler is not able to disassemble instruction due to incomplete data in stream. */
    RC_ERROR_INSTRUCTION_INCOMPLETE,
    RC_ILLEGAL_IMMEDIATE_DATA_SIZE
};

enum ira_operand_type {
	IRA_NONE = 0,
	IRA_IMMEDIATE_ADDRESS,
	IRA_IMMEDIATE_DATA_8,
	IRA_IMMEDIATE_DATA_16,
	IRA_IMMEDIATE_DATA_32,
	IRA_IMMEDIATE_DATA_64
};

struct ira_disassemble_info {
    /* Architecture. */
    enum ira_operation_mode mode;
    /* Operand size attribute. */
    uint16_t operand_size_attribute;
    /* Address size attribute. */
    uint16_t address_size_attribute;
    /* Address of the code to disassemble. */
    void *address;
    /* Size of the data to disassemble. */
    uint32_t size;
};

union ira_immediate_data {
	uint8_t immediate_8;
	uint16_t immediate_16;
	uint32_t immediate_32;
	uint64_t immediate_64;
};

struct ira_instruction_operand {
	/* Type of operand. */
	enum ira_operand_type operand_type;
	/* Place for immediate data. */
	union ira_immediate_data immediate;
};

struct ira_instruction_prefix {
	/* Prefix itself. */
    uint8_t prefix;
    /* Type of prefix, see enumeration above. */
    uint8_t prefix_type;
    /* 1 if prefix can be treated as mandatory one. */
    uint8_t mandatory_prefix;
};

struct ira_disassemble_result {
    /* Disassemblation result code. */
    enum ira_result_code code;
    /* Mnemonic */
    char *mnemonic;
    // Number of prefixes.
    uint8_t prefixes_count;
    // Prefixes.
    struct ira_instruction_prefix prefixes[_IRA_PREFIXES_COUNT];
	// Number of opcode bytes.
    uint8_t opcodes_count;
    // Opcode bytes without mandatory prefixes.
    uint8_t opcodes[3];
    /* Disassembled operands. */
    struct ira_instruction_operand operands[_IRA_OPERANDS_COUNT];
};


void ira_init(void);

void ira_disassemble( struct ira_disassemble_info *info, struct ira_disassemble_result *result );

void ira_deinit(void);

#endif // IRA_H_INCLUDED
