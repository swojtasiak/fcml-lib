#include <stdio.h>
#include <stdlib.h>

#include "ira.h"
#include "ira_ren.h"

struct ab {
	uint32_t t;
	uint32_t t1;
};

struct ab a[] = {{ 1,1 }};

int main()
{

    uint8_t data[] = {0x10, 0x16, 0x01, 0x02};

    struct ira_disassemble_info info;
    info.address = &data;
    info.size = 4;
    info.address_size_attribute = 16;
    info.operand_size_attribute = 16;
    info.mode = IRA_MOD_16BIT;

    struct ira_disassemble_result result;

    ira_init();

    // Disassemble.
    ira_disassemble( &info, &result );

    // Print.
    char buffer[512] = {0};

    struct ira_format_info format;

    ira_format_intel_instruction( buffer, sizeof(buffer), &result, &format );

    printf( "%s\n", buffer );

    ira_deinit();

    return 0;
}
