#ifndef IRA_H_INCLUDED
#define IRA_H_INCLUDED

#include <stdint.h>

enum ira_operation_mode {
    IRA_MOD_16BIT,
    IRA_MOD_32BIT, // IA32/IA32e.
    IRA_MOD_64BIT
};

enum ira_result_code {
    RC_OK = 0,
    RC_ERROR_ILLEGAL_OPERATION_MODE,
    RC_ERROR_ILLEGAL_ADDRESS_ATTRIBUTE_SIZE
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

struct ira_instruction_operand {
	/* Type of operand. */
	int operand_type;
	/* Pointer to structure describing given operand. */
	void *operand_details;
};

struct ira_disassemble_result {
    /* Disassemblation result. */
    enum ira_result_code code;
    /* Disassembled operands. */
    struct ira_instruction_operand operands[4];
};


void ira_init(void);

void ira_disassemble( struct ira_disassemble_info *info, struct ira_disassemble_result *result );

void ira_deinit(void);

#endif // IRA_H_INCLUDED