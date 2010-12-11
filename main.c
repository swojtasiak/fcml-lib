#include <stdio.h>
#include <stdlib.h>

#include "ira.h"

struct ab {
	uint32_t t;
	uint32_t t1;
};

struct ab a[] = {{ 1,1 }};

int main()
{

    uint8_t data[] = {0xD4, 0x50};

    struct ira_disassemble_info info;
    info.address = &data;
    info.size = 2;
    info.address_size_attribute = 32;
    info.operand_size_attribute = 64;
    info.mode = IRA_MOD_64BIT;

    struct ira_disassemble_result result;

    ira_init();
    ira_disassemble( &info, &result );
    ira_deinit();

    return 0;
}
