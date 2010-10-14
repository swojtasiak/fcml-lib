#include <stdio.h>
#include <stdlib.h>

#include "ira.h"

int main()
{

    uint8_t data[] = {0x66, 0x36, 0xf2, 0xF3, 0x42, 0x0F, 0x6E};

    struct disassemble_info info;
    info.address = &data;
    info.size = 2;
    info.address_size_attribute = 32;
    info.operand_size_attribute = 64;
    info.mode = mod_64bit;

    struct disassemble_result result;

    ira_disassemble( &info, &result );

    return 0;
}
