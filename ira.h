#ifndef IRA_H_INCLUDED
#define IRA_H_INCLUDED

#include <stdint.h>

enum operation_mode {
    mod_16bit,
    mod_32bit, // IA32/IA32e.
    mod_64bit
};

enum result_code {
    RC_OK = 0,
    RC_ERROR_ILLEGAL_OPERATION_MODE,
    RC_ERROR_ILLEGAL_ADDRESS_ATTRIBUTE_SIZE
};

struct disassemble_info {
    /* Architecture. */
    enum operation_mode mode;
    /* Operand size attribute. */
    uint16_t operand_size_attribute;
    /* Address size attribute. */
    uint16_t address_size_attribute;
    /* Address of the code to disassemble. */
    void *address;
    /* Size of the data to disassemble. */
    uint32_t size;
};

struct disassemble_result {
    /* Disassemblation result. */
    enum result_code code;
};

void ira_disassemble( struct disassemble_info *info, struct disassemble_result *result );



#endif // IRA_H_INCLUDED
