#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ira.h"
#include "ira_ren_intel.h"

struct ab {
	uint32_t t;
	uint32_t t1;
};

struct ab a[] = {{ 1,1 }};

#define _IRA_CLEAR_BIT(x,y)	( ~(0x01 << y) & x )

void test();

int main()
{
	ira_init();
	test();
	ira_deinit();

	//REX.W - 48.

    //uint8_t data[] = { 0x67, 0x47, 0x10, 0x4c, 0x5c, 0x81 };
	//uint8_t data[] = { 0x67, 0x10, 0x4c, 0x5c, 0x81 };
	//uint8_t data[] = { 0xD5, 0xff };
	//uint8_t data[] = { 0x66, 0x40, 0x15, 0xff, 0xff, 0xff, 0xff }; // adc

	// REX.W + 81 /2 id ADC r/m64, imm32 B Valid N.E. Add with CF imm32 sign extended to 64-bits to r/m64.
	// uint8_t data[] = { 0x48, 0x81, 0xD5, 0x15, 0xff, 0xff, 0xff }; // adc

	// REX.W + 83 /2 ib ADC r/m64, imm8 B Valid N.E. Add with CF sign-extended imm8 into r/m64.
	// uint8_t data[] = { 0x48, 0x83, 0xD5, 0x15, 0xff, 0xff, 0xff }; // adc

	/*
	uint8_t data[] = { 0x66, 0x40, 0x15, 0x54, 0x64, 0xD5, 0x15, 0xff, 0xff, 0xff,0xff,0xff,0xff,0xff,0xff }; // adc

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


*/
    return 0;
}

void test_code_32( int is32, uint8_t code[], int size, char *mnemonic ) {

	struct ira_disassemble_info info;
	info.address = code;
	info.size = size;
	info.address_size_attribute = 0;
	info.operand_size_attribute = 0;
	info.mode = is32 ? IRA_MOD_32BIT : IRA_MOD_64BIT;

	struct ira_disassemble_result result;

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

		if( strcmp( buffer, mnemonic ) != 0 ) {
			printf("Failed: %s (%s)\n", mnemonic, buffer);
			exit(0);
		}

	} else {
		printf("Failed: %s\n", mnemonic);
		exit(0);
	}

}

#define _TEST32(x,...) { uint8_t code[] = {__VA_ARGS__}; test_code_32( 1, code, sizeof(code), x ); }
#define _TEST64(x,...) { uint8_t code[] = {__VA_ARGS__}; test_code_32( 0, code, sizeof(code), x ); }

void test(void) {
	// ADC
	// 14 ib ADC AL, imm8 C Valid Valid Add with carry imm8 to AL.
	// { NULL, 0x0001, 0x00C40000, { 0x14, 0x00, 0x00 }, _IRA_OPERAND_REG_ACCUMULATOR_8, _IRA_OPERAND_IB, _IRA_NA, _IRA_NA },
	_TEST32( "1442 adc al,42h", 0x14, 0x42 );
	_TEST32( "1400 adc al,00h", 0x14, 0x00 );
	_TEST32( "14ff adc al,0ffh", 0x14, 0xff );
	_TEST64( "1442 adc al,42h", 0x14, 0x42 );
	_TEST64( "1400 adc al,00h", 0x14, 0x00 );
	_TEST64( "14ff adc al,0ffh", 0x14, 0xff );
	// 15 iw ADC AX, imm16 C Valid Valid Add with carry imm16 to AX.
	// 15 id ADC EAX, imm32 C Valid Valid Add with carry imm32 to EAX.
	// { NULL, 0x0001, 0x00D40000, { 0x15, 0x00, 0x00 }, _IRA_OPERAND_REG_ACCUMULATOR_OSA_W, _IRA_OPERAND_IMM_EOSA, _IRA_NA, _IRA_NA },
	_TEST32( "66154280 adc ax,8042h", 0x66, 0x15, 0x42, 0x80 );
	_TEST32( "1521658042 adc eax,42806521h", 0x15, 0x21, 0x65, 0x80, 0x42 );
	_TEST64( "401521658042 adc eax,42806521h", 0x40, 0x15, 0x21, 0x65, 0x80, 0x42 );
	_TEST64( "481521658042 adc rax,0000000042806521h", 0x48, 0x15, 0x21, 0x65, 0x80, 0x42 );
	_TEST64( "66481521658042 adc rax,0000000042806521h", 0x66, 0x48, 0x15, 0x21, 0x65, 0x80, 0x42 );
	_TEST64( "6766481521658042 adc rax,0000000042806521h", 0x67, 0x66, 0x48, 0x15, 0x21, 0x65, 0x80, 0x42 );
	_TEST64( "6640152165 adc ax,6521h", 0x66, 0x40, 0x15, 0x21, 0x65, 0x80, 0x42 );
	//_TEST32( "1400 adc al,00h", 0x14, 0x00 );
}

