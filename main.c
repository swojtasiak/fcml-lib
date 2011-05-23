#include <stdio.h>
#include <stdlib.h>

#include "ira.h"
#include "ira_ren_intel.h"

struct ab {
	uint32_t t;
	uint32_t t1;
};

struct ab a[] = {{ 1,1 }};

#define _IRA_CLEAR_BIT(x,y)	( ~(0x01 << y) & x )

int main()
{
    //uint8_t data[] = { 0x67, 0x47, 0x10, 0x4c, 0x5c, 0x81 };
	//uint8_t data[] = { 0x67, 0x10, 0x4c, 0x5c, 0x81 };
	//uint8_t data[] = { 0xD5, 0xff };
	//uint8_t data[] = { 0x66, 0x40, 0x15, 0xff, 0xff, 0xff, 0xff }; // adc
	uint8_t data[] = { 0x80, 0xD5, 0x15, 0xff, 0xff, 0xff, 0xff }; // adc

    struct ira_disassemble_info info;
    info.address = &data;
    info.size = sizeof(data);
    info.address_size_attribute = 0;
    info.operand_size_attribute = 0;
    info.mode = IRA_MOD_64BIT;

    struct ira_disassemble_result result;

    ira_init();

    // Disassemble.
    ira_disassemble( &info, &result );

    if( result.code == RC_OK ) {

		// Print.
		char buffer[512] = {0};

		struct ira_intel_format_info format;
		format.show_zero_displacement = 0;
		format.show_extended_displacement = 1;
		format.immediate_hex_display = 1;
		format.immediate_signed = 1;
		format.show_instruction_code = 1;
		format.show_extended_immediate = 1;

		ira_format_intel_instruction( buffer, sizeof(buffer), &result, &format );

		printf( "%s\n", buffer );

    }

    ira_deinit();

    return 0;
}
