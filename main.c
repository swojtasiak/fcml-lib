#include <stdio.h>
#include <stdlib.h>

#include "ira.h"
#include "ira_ren.h"

struct ab {
	uint32_t t;
	uint32_t t1;
};

struct ab a[] = {{ 1,1 }};

#define _IRA_CLEAR_BIT(x,y)	( ~(0x01 << y) & x )

int main()
{
	int i = 0x0111;

	int a = _IRA_CLEAR_BIT( i, 0 );

    uint8_t data[] = { 0x67, 0x47, 0x10, 0x4c, 0x5c, 0x00 };

    struct ira_disassemble_info info;
    info.address = &data;
    info.size = sizeof(data);
    info.address_size_attribute = 64;
    info.operand_size_attribute = 32;
    info.mode = IRA_MOD_64BIT;

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
