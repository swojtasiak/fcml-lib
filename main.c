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

#include "ira_int.h"

int main()
{
	//int i = _IRA_OPERAND_MODRM_RM_ASA_W;

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

void test_code( int is32, uint8_t code[], int size, char *mnemonic ) {

	struct ira_disassemble_info info;
	info.address = code;
	info.size = size;
	info.address_size_attribute = 0;
	info.operand_size_attribute = 0;
	info.mode = is32 ? IRA_MOD_32BIT : IRA_MOD_64BIT;

	if( is32 ) {
		info.instruction_pointer.eip = 0x00401000;
	} else {
		info.instruction_pointer.rip = 0x0000800000401000;
	}

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
		if( strcmp( "FAIL", mnemonic ) != 0 ) {
			printf("Failed: %s\n", mnemonic);
			exit(0);
		}
	}

}

#define _TEST32(x,...) { uint8_t code[] = {__VA_ARGS__}; test_code( 1, code, sizeof(code), x ); }
#define _TEST64(x,...) { uint8_t code[] = {__VA_ARGS__}; test_code( 0, code, sizeof(code), x ); }

void test(void) {

	// CALL
	_TEST32( "e8000030ff call 0ff701005h", 0xE8, 0x00, 0x00, 0x30, 0xFF );

	// ADC
	_TEST32( "801501020304ff adc byte ptr [04030201h],0ffh", 0x80, 0x15, 0x01, 0x02, 0x03, 0x04, 0xff );
	// 14 ib ADC AL, imm8 C Valid Valid Add with carry imm8 to AL.
	_TEST32( "1442 adc al,42h", 0x14, 0x42 );
	_TEST32( "1400 adc al,00h", 0x14, 0x00 );
	_TEST32( "14ff adc al,0ffh", 0x14, 0xff );
	_TEST64( "1442 adc al,42h", 0x14, 0x42 );
	_TEST64( "1400 adc al,00h", 0x14, 0x00 );
	_TEST64( "14ff adc al,0ffh", 0x14, 0xff );
	// 15 iw ADC AX, imm16 C Valid Valid Add with carry imm16 to AX.
	// 15 id ADC EAX, imm32 C Valid Valid Add with carry imm32 to EAX.
	_TEST32( "66154280 adc ax,8042h", 0x66, 0x15, 0x42, 0x80 );
	_TEST32( "1521658042 adc eax,42806521h", 0x15, 0x21, 0x65, 0x80, 0x42 );
	_TEST64( "401521658042 adc eax,42806521h", 0x40, 0x15, 0x21, 0x65, 0x80, 0x42 );
	_TEST64( "6640152165 adc ax,6521h", 0x66, 0x40, 0x15, 0x21, 0x65, 0x80, 0x42 );
	// REX.W + 15 id ADC RAX, imm32 C Valid N.E. Add with carry imm32 sign extended to 64-bits to RAX.
	_TEST64( "481521658042 adc rax,0000000042806521h", 0x48, 0x15, 0x21, 0x65, 0x80, 0x42 );
	_TEST64( "66481521658042 adc rax,0000000042806521h", 0x66, 0x48, 0x15, 0x21, 0x65, 0x80, 0x42 );
	_TEST64( "6766481521658042 adc rax,0000000042806521h", 0x67, 0x66, 0x48, 0x15, 0x21, 0x65, 0x80, 0x42 );
	_TEST64( "67664815ffffffff adc rax,0ffffffffffffffffh", 0x67, 0x66, 0x48, 0x15, 0xff, 0xff, 0xff, 0xff );
	// 80 /2 ib ADC r/m8, imm8 B Valid Valid Add with carry imm8 to r/m8.
	// REX + 80 /2 ib ADC r/m8*, imm8 B Valid N.E. Add with carry imm8 to r/m8.
	_TEST32( "801501020304ff adc byte ptr [04030201h],0ffh", 0x80, 0x15, 0x01, 0x02, 0x03, 0x04, 0xff );
	_TEST32( "809601020304ff adc byte ptr [esi+04030201h],0ffh", 0x80, 0x96, 0x01, 0x02, 0x03, 0x04, 0xff, 0x00, 0x00 );
	_TEST32( "8054010203 adc byte ptr [ecx+eax+00000002h],03h", 0x80, 0x54, 0x01, 0x02, 0x03 );
	// 81 /2 iw ADC r/m16, imm16 B Valid Valid Add with carry imm16 to r/m16.
	// 81 /2 id ADC r/m32, imm32 B Valid Valid Add with CF imm32 to r/m32.
	_TEST32( "81d501020304 adc ebp,04030201h", 0x81, 0xD5, 0x01, 0x02, 0x03, 0x04 );
	_TEST32( "6681d50102 adc bp,0201h", 0x66, 0x81, 0xD5, 0x01, 0x02 );
	_TEST32( "FAIL", 0x67, 0x66, 0x40, 0x81, 0xD5, 0x01, 0x02, 0x03, 0x04 ); // 32 bit mode doesn't not allow REX.
	_TEST64( "67664081d50102 adc bp,0201h", 0x67, 0x66, 0x40, 0x81, 0xD5, 0x01, 0x02 ); // 32 bit mode doesn't not allow REX.
	// REX.W + 81 /2 id ADC r/m64, imm32 B Valid N.E. Add with CF imm32 sign extended to 64-bits to r/m64.
	_TEST64( "4881d501020304 adc rbp,0000000004030201h", 0x48, 0x81, 0xD5, 0x01, 0x02, 0x03, 0x04 );
	_TEST64( "4881d5ffffffff adc rbp,0ffffffffffffffffh", 0x48, 0x81, 0xD5, 0xff, 0xff, 0xff, 0xff );
	_TEST64( "674881d5ffffffff adc rbp,0ffffffffffffffffh", 0x67, 0x48, 0x81, 0xD5, 0xff, 0xff, 0xff, 0xff );
	_TEST64( "664881d5ffffffff adc rbp,0ffffffffffffffffh", 0x66, 0x48, 0x81, 0xD5, 0xff, 0xff, 0xff, 0xff );
	// 83 /2 ib ADC r/m16, imm8 B Valid Valid Add with CF sign-extended imm8 to r/m16.
	// 83 /2 ib ADC r/m32, imm8 B Valid Valid Add with CF sign-extended imm8 into r/m32.
	_TEST32( "831601 adc dword ptr [esi],00000001h", 0x83, 0x16, 0x01, 0x02, 0x03, 0x04 );
	_TEST32( "66831601 adc word ptr [esi],0001h", 0x66, 0x83, 0x16, 0x01, 0x02, 0x03, 0x04 );
	_TEST32( "678316010203 adc dword ptr [0201h],00000003h", 0x67, 0x83, 0x16, 0x01, 0x02, 0x03 );
	// REX.W + 83 /2 ib ADC r/m64, imm8 B Valid N.E. Add with CF sign-extended imm8 into r/m64.
	_TEST64( "4883970102030405 adc qword ptr [rdi+0000000004030201h],0000000000000005h", 0x48, 0x83, 0x97, 0x01, 0x02, 0x03, 0x4, 0x05 );
	_TEST64( "48839701020304ff adc qword ptr [rdi+0000000004030201h],0ffffffffffffffffh", 0x48, 0x83, 0x97, 0x01, 0x02, 0x03, 0x4, 0xff );
	// 10 /r ADC r/m8, r8 A Valid Valid Add with carry byte register to r/m8.
	// REX + 10 /r ADC r/m8*, r8* A Valid N.E. Add with carry byte register to r/m64.
	_TEST32( "10a501020304 adc byte ptr [ebp+04030201h],ah", 0x10, 0xa5, 0x01, 0x02, 0x03, 04 );
	_TEST64( "4810a501020304 adc byte ptr [rbp+0000000004030201h],dil", 0x48, 0x10, 0xa5, 0x01, 0x02, 0x03, 04 );
	_TEST64( "481064a501 adc byte ptr [rbp+0000000000000001h],dil", 0x48, 0x10, 0x64, 0xa5, 0x01, 0x02, 0x03, 04 );
	// 11 /r ADC r/m16, r16 A Valid Valid Add with carry r16 to r/m16.
	// 11 /r ADC r/m32, r32 A Valid Valid Add with CF r32 to r/m32.
	// REX.W + 11 /r ADC r/m64, r64 A Valid N.E. Add with CF r64 to r/m64.
	_TEST32( "11a501020304 adc dword ptr [ebp+04030201h],esp", 0x11, 0xa5, 0x01, 0x02, 0x03, 04 );
	_TEST32( "676611a50102 adc word ptr [di+0201h],sp", 0x67, 0x66, 0x11, 0xa5, 0x01, 0x02 );
	_TEST32( "6711a50102 adc dword ptr [di+0201h],esp", 0x67, 0x11, 0xa5, 0x01, 0x02 );
	_TEST64( "4d11648901 adc qword ptr [r9+rcx*4+0000000000000001h],r12", 0x4D, 0x11, 0x64, 0x89, 0x01 );
	// 12 /r ADC r8, r/m8 A Valid Valid Add with carry r/m8 to byte register.
	// REX + 12 /r ADC r8*, r/m8* A Valid N.E. Add with carry r/m64 to byte register.
	_TEST32( "12a501020304 adc ah,byte ptr [ebp+04030201h]", 0x12, 0xa5, 0x01, 0x02, 0x03, 04 );
	_TEST64( "4812a501020304 adc dil,byte ptr [rbp+0000000004030201h]", 0x48, 0x12, 0xa5, 0x01, 0x02, 0x03, 04 );
	_TEST64( "481264a501 adc dil,byte ptr [rbp+0000000000000001h]", 0x48, 0x12, 0x64, 0xa5, 0x01, 0x02, 0x03, 04 );
	// 13 /r ADC r16, r/m16 A Valid Valid Add with carry r/m16 to r16.
	// 13 /r ADC r32, r/m32 A Valid Valid Add with CF r/m32 to r32.
	// REX.W + 13 /r ADC r64, r/m64 A Valid N.E. Add with CF r/m64 to r64.
	_TEST32( "13a501020304 adc esp,dword ptr [ebp+04030201h]", 0x13, 0xa5, 0x01, 0x02, 0x03, 04 );
	_TEST32( "676613a50102 adc sp,word ptr [di+0201h]", 0x67, 0x66, 0x13, 0xa5, 0x01, 0x02 );
	_TEST32( "6713a50102 adc esp,dword ptr [di+0201h]", 0x67, 0x13, 0xa5, 0x01, 0x02 );
	_TEST64( "4d13648901 adc r12,qword ptr [r9+rcx*4+0000000000000001h]", 0x4D, 0x13, 0x64, 0x89, 0x01 );

	// ADD.

	// 04 ib ADD AL, imm8 C Valid Valid Add imm8 to AL..
	_TEST32( "0442 add al,42h", 0x04, 0x42 );
	_TEST32( "04ff add al,0ffh", 0x04, 0xff );
	_TEST64( "0442 add al,42h", 0x04, 0x42 );
	_TEST64( "0400 add al,00h", 0x04, 0x00 );
	_TEST64( "04ff add al,0ffh", 0x04, 0xff );
	// 05 iw ADD AX, imm16 C Valid Valid Add imm16 to AX.
	// 05 id ADD EAX, imm32 C Valid Valid Add imm32 to EAX.
	_TEST32( "66054280 add ax,8042h", 0x66, 0x05, 0x42, 0x80 );
	_TEST32( "0521658042 add eax,42806521h", 0x05, 0x21, 0x65, 0x80, 0x42 );
	_TEST64( "400521658042 add eax,42806521h", 0x40, 0x05, 0x21, 0x65, 0x80, 0x42 );
	_TEST64( "6640052165 add ax,6521h", 0x66, 0x40, 0x05, 0x21, 0x65, 0x80, 0x42 );
	// REX.W + 05 id ADD RAX, imm32 C Valid N.E. Add imm32 sign-extended to 64-bits to RAX.
	_TEST64( "480521658042 add rax,0000000042806521h", 0x48, 0x05, 0x21, 0x65, 0x80, 0x42 );
	_TEST64( "66480521658042 add rax,0000000042806521h", 0x66, 0x48, 0x05, 0x21, 0x65, 0x80, 0x42 );
	_TEST64( "6766480521658042 add rax,0000000042806521h", 0x67, 0x66, 0x48, 0x05, 0x21, 0x65, 0x80, 0x42 );
	_TEST64( "67664805ffffffff add rax,0ffffffffffffffffh", 0x67, 0x66, 0x48, 0x05, 0xff, 0xff, 0xff, 0xff );
	// 80 /0 ib ADD r/m8, imm8 B Valid Valid Add imm8 to r/m8.
	// REX + 80 /0 ib ADD r/m8*, imm8 B Valid N.E. Add sign-extended imm8 to r/m64.
	_TEST32( "800501020304ff add byte ptr [04030201h],0ffh", 0x80, 0x05, 0x01, 0x02, 0x03, 0x04, 0xff );
	_TEST32( "808601020304ff add byte ptr [esi+04030201h],0ffh", 0x80, 0x86, 0x01, 0x02, 0x03, 0x04, 0xff, 0x00, 0x00 );
	_TEST32( "8044010203 add byte ptr [ecx+eax+00000002h],03h", 0x80, 0x44, 0x01, 0x02, 0x03 );
	// 81 /0 iw ADD r/m16, imm16 B Valid Valid Add imm16 to r/m16.
	// 81 /0 id ADD r/m32, imm32 B Valid Valid Add imm32 to r/m32.
	_TEST32( "81c501020304 add ebp,04030201h", 0x81, 0xc5, 0x01, 0x02, 0x03, 0x04 );
	_TEST32( "6681c50102 add bp,0201h", 0x66, 0x81, 0xc5, 0x01, 0x02 );
	_TEST32( "FAIL", 0x67, 0x66, 0x40, 0x81, 0xc5, 0x01, 0x02, 0x03, 0x04 ); // 32 bit mode doesn't not allow REX.
	_TEST64( "67664081c50102 add bp,0201h", 0x67, 0x66, 0x40, 0x81, 0xc5, 0x01, 0x02 ); // 32 bit mode doesn't not allow REX.
	// REX.W + 81 /0 id ADD r/m64, imm32 B Valid N.E. Add imm32 sign-extended to 64-bits to r/m64.
	_TEST64( "4881c501020304 add rbp,0000000004030201h", 0x48, 0x81, 0xc5, 0x01, 0x02, 0x03, 0x04 );
	_TEST64( "4881c5ffffffff add rbp,0ffffffffffffffffh", 0x48, 0x81, 0xc5, 0xff, 0xff, 0xff, 0xff );
	_TEST64( "674881c5ffffffff add rbp,0ffffffffffffffffh", 0x67, 0x48, 0x81, 0xc5, 0xff, 0xff, 0xff, 0xff );
	_TEST64( "664881c5ffffffff add rbp,0ffffffffffffffffh", 0x66, 0x48, 0x81, 0xc5, 0xff, 0xff, 0xff, 0xff );
	// 83 /0 ib ADD r/m16, imm8 B Valid Valid Add sign-extended imm8 to r/m16.
	// 83 /0 ib ADD r/m32, imm8 B Valid Valid Add sign-extended imm8 to r/m32.
	_TEST32( "830601 add dword ptr [esi],00000001h", 0x83, 0x06, 0x01, 0x02, 0x03, 0x04 );
	_TEST32( "66830601 add word ptr [esi],0001h", 0x66, 0x83, 0x06, 0x01, 0x02, 0x03, 0x04 );
	_TEST32( "678306010203 add dword ptr [0201h],00000003h", 0x67, 0x83, 0x06, 0x01, 0x02, 0x03 );
	// REX.W + 83 /0 ib ADD r/m64, imm8 B Valid N.E. Add sign-extended imm8 to r/m64.
	_TEST64( "4883870102030405 add qword ptr [rdi+0000000004030201h],0000000000000005h", 0x48, 0x83, 0x87, 0x01, 0x02, 0x03, 0x4, 0x05 );
	_TEST64( "48838701020304ff add qword ptr [rdi+0000000004030201h],0ffffffffffffffffh", 0x48, 0x83, 0x87, 0x01, 0x02, 0x03, 0x4, 0xff );
	// 00 /r ADD r/m8, r8 A Valid Valid Add r8 to r/m8.
	// REX + 00 /r ADD r/m8*, r8* A Valid N.E. Add r8 to r/m8.
	_TEST32( "00a501020304 add byte ptr [ebp+04030201h],ah", 0x00, 0xa5, 0x01, 0x02, 0x03, 04 );
	_TEST64( "4800a501020304 add byte ptr [rbp+0000000004030201h],dil", 0x48, 0x00, 0xa5, 0x01, 0x02, 0x03, 04 );
	_TEST64( "480064a501 add byte ptr [rbp+0000000000000001h],dil", 0x48, 0x00, 0x64, 0xa5, 0x01, 0x02, 0x03, 04 );
	// 01 /r ADD r/m16, r16 A Valid Valid Add r16 to r/m16.
	// 01 /r ADD r/m32, r32 A Valid Valid Add r32 to r/m32.
	// REX.W + 01 /r ADD r/m64, r64 A Valid N.E. Add r64 to r/m64.
	_TEST32( "01a501020304 add dword ptr [ebp+04030201h],esp", 0x01, 0xa5, 0x01, 0x02, 0x03, 04 );
	_TEST32( "676601a50102 add word ptr [di+0201h],sp", 0x67, 0x66, 0x01, 0xa5, 0x01, 0x02 );
	_TEST32( "6701a50102 add dword ptr [di+0201h],esp", 0x67, 0x01, 0xa5, 0x01, 0x02 );
	_TEST64( "4d01648901 add qword ptr [r9+rcx*4+0000000000000001h],r12", 0x4D, 0x01, 0x64, 0x89, 0x01 );
	// 02 /r ADD r8, r/m8 A Valid Valid Add r/m8 to r8.
	// REX + 02 /r ADD r8*, r/m8* A Valid N.E. Add r/m8 to r8.
	_TEST32( "02a501020304 add ah,byte ptr [ebp+04030201h]", 0x02, 0xa5, 0x01, 0x02, 0x03, 04 );
	_TEST64( "4802a501020304 add dil,byte ptr [rbp+0000000004030201h]", 0x48, 0x02, 0xa5, 0x01, 0x02, 0x03, 04 );
	_TEST64( "480264a501 add dil,byte ptr [rbp+0000000000000001h]", 0x48, 0x02, 0x64, 0xa5, 0x01, 0x02, 0x03, 04 );
	// 03 /r ADD r16, r/m16 A Valid Valid Add r/m16 to r16.
	// 03 /r ADD r32, r/m32 A Valid Valid Add r/m32 to r32.
	// REX.W + 03 /r ADD r64, r/m64 A Valid N.E. Add r/m64 to r64.
	_TEST32( "03a501020304 add esp,dword ptr [ebp+04030201h]", 0x03, 0xa5, 0x01, 0x02, 0x03, 04 );
	_TEST32( "676603a50102 add sp,word ptr [di+0201h]", 0x67, 0x66, 0x03, 0xa5, 0x01, 0x02 );
	_TEST32( "6703a50102 add esp,dword ptr [di+0201h]", 0x67, 0x03, 0xa5, 0x01, 0x02 );
	_TEST64( "4d03648901 add r12,qword ptr [r9+rcx*4+0000000000000001h]", 0x4D, 0x03, 0x64, 0x89, 0x01 );

	// ADDPD
	_TEST32( "660f581401 addpd xmm2,oword ptr [ecx+eax]", 0x66, 0x0F, 0x58, 0x14, 0x01 );
	_TEST64( "660f581401 addpd xmm2,oword ptr [rcx+rax]", 0x66, 0x0F, 0x58, 0x14, 0x01 );

	// ADDPS
	_TEST32( "0f581401 addps xmm2,oword ptr [ecx+eax]", 0x0F, 0x58, 0x14, 0x01 );
	_TEST64( "0f581401 addps xmm2,oword ptr [rcx+rax]", 0x0F, 0x58, 0x14, 0x01 );

	// ADDSD
	_TEST32( "f20f581401 addsd xmm2,qword ptr [ecx+eax]", 0xF2, 0x0F, 0x58, 0x14, 0x01 );
	_TEST64( "f20f581401 addsd xmm2,qword ptr [rcx+rax]", 0xF2, 0x0F, 0x58, 0x14, 0x01 );

	// ADDSS
	_TEST32( "f30f581401 addss xmm2,dword ptr [ecx+eax]", 0xF3, 0x0F, 0x58, 0x14, 0x01 );
	_TEST64( "f30f581401 addss xmm2,dword ptr [rcx+rax]", 0xF3, 0x0F, 0x58, 0x14, 0x01 );

	// ADDSUBPD
	_TEST32( "660fd01401 addsubpd xmm2,oword ptr [ecx+eax]", 0x66, 0x0F, 0xD0, 0x14, 0x01 );
	_TEST64( "660fd01401 addsubpd xmm2,oword ptr [rcx+rax]", 0x66, 0x0F, 0xD0, 0x14, 0x01 );

	// ADDSUBPS
	_TEST32( "f20fd01401 addsubps xmm2,oword ptr [ecx+eax]", 0xf2, 0x0F, 0xD0, 0x14, 0x01 );
	_TEST64( "f20fd01401 addsubps xmm2,oword ptr [rcx+rax]", 0xf2, 0x0F, 0xD0, 0x14, 0x01 );

	// AESDEC
	_TEST32( "660f38de1401 aesdec xmm2,oword ptr [ecx+eax]", 0x66, 0x0F, 0x38, 0xDE, 0x14, 0x01 );
	_TEST64( "660f38de1401 aesdec xmm2,oword ptr [rcx+rax]", 0x66, 0x0F, 0x38, 0xDE, 0x14, 0x01 );

	// AESDECLAST
	_TEST32( "660f38df1401 aesdeclast xmm2,oword ptr [ecx+eax]", 0x66, 0x0F, 0x38, 0xDF, 0x14, 0x01 );
	_TEST64( "660f38df1401 aesdeclast xmm2,oword ptr [rcx+rax]", 0x66, 0x0F, 0x38, 0xDF, 0x14, 0x01 );

	// AESENC
	_TEST32( "660f38dc1401 aesenc xmm2,oword ptr [ecx+eax]", 0x66, 0x0F, 0x38, 0xDC, 0x14, 0x01 );
	_TEST64( "660f38dc1401 aesenc xmm2,oword ptr [rcx+rax]", 0x66, 0x0F, 0x38, 0xDC, 0x14, 0x01 );

	// AESENCLAST
	_TEST32( "660f38dd1401 aesenclast xmm2,oword ptr [ecx+eax]", 0x66, 0x0F, 0x38, 0xDD, 0x14, 0x01 );
	_TEST64( "660f38dd1401 aesenclast xmm2,oword ptr [rcx+rax]", 0x66, 0x0F, 0x38, 0xDD, 0x14, 0x01 );

	// AESIMC
	_TEST32( "660f38db1401 aesimc xmm2,oword ptr [ecx+eax]", 0x66, 0x0F, 0x38, 0xDB, 0x14, 0x01 );
	_TEST64( "660f38db1401 aesimc xmm2,oword ptr [rcx+rax]", 0x66, 0x0F, 0x38, 0xDB, 0x14, 0x01 );

	// AESKEYGENASSIST
	_TEST32( "660f3adf1401ff aeskeygenassist xmm2,oword ptr [ecx+eax],0ffh", 0x66, 0x0F, 0x3a, 0xDF, 0x14, 0x01, 0xFF );
	_TEST64( "660f3adf1401ff aeskeygenassist xmm2,oword ptr [rcx+rax],0ffh", 0x66, 0x0F, 0x3a, 0xDF, 0x14, 0x01, 0xFF );

	// AND

	// 24 ib AND AL, imm8 C Valid Valid AL AND imm8.
	_TEST32( "2442 and al,42h", 0x24, 0x42 );
	_TEST32( "24ff and al,0ffh", 0x24, 0xff );
	_TEST64( "2442 and al,42h", 0x24, 0x42 );
	_TEST64( "2400 and al,00h", 0x24, 0x00 );
	_TEST64( "24ff and al,0ffh", 0x24, 0xff );
	// 25 iw AND AX, imm16 C Valid Valid AX AND imm16.
	// 25 id AND EAX, imm32 C Valid Valid EAX AND imm32.
	_TEST32( "66254280 and ax,8042h", 0x66, 0x25, 0x42, 0x80 );
	_TEST32( "2521658042 and eax,42806521h", 0x25, 0x21, 0x65, 0x80, 0x42 );
	_TEST64( "402521658042 and eax,42806521h", 0x40, 0x25, 0x21, 0x65, 0x80, 0x42 );
	_TEST64( "6640252165 and ax,6521h", 0x66, 0x40, 0x25, 0x21, 0x65, 0x80, 0x42 );
	// REX.W + 25 id AND RAX, imm32 C Valid N.E. RAX AND imm32 signextended to 64-bits.
	_TEST64( "482521658042 and rax,0000000042806521h", 0x48, 0x25, 0x21, 0x65, 0x80, 0x42 );
	_TEST64( "66482521658042 and rax,0000000042806521h", 0x66, 0x48, 0x25, 0x21, 0x65, 0x80, 0x42 );
	_TEST64( "6766482521658042 and rax,0000000042806521h", 0x67, 0x66, 0x48, 0x25, 0x21, 0x65, 0x80, 0x42 );
	_TEST64( "67664825ffffffff and rax,0ffffffffffffffffh", 0x67, 0x66, 0x48, 0x25, 0xff, 0xff, 0xff, 0xff );
	// 80 /4 ib AND r/m8, imm8 B Valid Valid r/m8 AND imm8.
	// REX + 80 /4 ib AND r/m8*, imm8 B Valid N.E. r/m64 AND imm8 (signextended).
	_TEST32( "802501020304ff and byte ptr [04030201h],0ffh", 0x80, 0x25, 0x01, 0x02, 0x03, 0x04, 0xff );
	_TEST32( "80a601020304ff and byte ptr [esi+04030201h],0ffh", 0x80, 0xA6, 0x01, 0x02, 0x03, 0x04, 0xff, 0x00, 0x00 );
	_TEST32( "8064010203 and byte ptr [ecx+eax+00000002h],03h", 0x80, 0x64, 0x01, 0x02, 0x03 );
	// 81 /4 iw AND r/m16, imm16 B Valid Valid r/m16 AND imm16.
	// 81 /4 id AND r/m32, imm32 B Valid Valid r/m32 AND imm32.
	_TEST32( "81e501020304 and ebp,04030201h", 0x81, 0xe5, 0x01, 0x02, 0x03, 0x04 );
	_TEST32( "6681e50102 and bp,0201h", 0x66, 0x81, 0xe5, 0x01, 0x02 );
	_TEST32( "FAIL", 0x67, 0x66, 0x40, 0x81, 0xe5, 0x01, 0x02, 0x03, 0x04 ); // 32 bit mode doesn't not allow REX.
	_TEST64( "67664081e50102 and bp,0201h", 0x67, 0x66, 0x40, 0x81, 0xe5, 0x01, 0x02 ); // 32 bit mode doesn't not allow REX.
	// REX.W + 81 /4 id AND r/m64, imm32 B Valid N.E. r/m64 AND imm32 sign extended to 64-bits.
	_TEST64( "4881e501020304 and rbp,0000000004030201h", 0x48, 0x81, 0xe5, 0x01, 0x02, 0x03, 0x04 );
	_TEST64( "4881e5ffffffff and rbp,0ffffffffffffffffh", 0x48, 0x81, 0xe5, 0xff, 0xff, 0xff, 0xff );
	_TEST64( "674881e5ffffffff and rbp,0ffffffffffffffffh", 0x67, 0x48, 0x81, 0xe5, 0xff, 0xff, 0xff, 0xff );
	_TEST64( "664881e5ffffffff and rbp,0ffffffffffffffffh", 0x66, 0x48, 0x81, 0xe5, 0xff, 0xff, 0xff, 0xff );
	// 83 /4 ib AND r/m16, imm8 B Valid Valid r/m16 AND imm8 (signextended).
	// 83 /4 ib AND r/m32, imm8 B Valid Valid r/m32 AND imm8 (signextended).
	_TEST32( "832601 and dword ptr [esi],00000001h", 0x83, 0x26, 0x01, 0x02, 0x03, 0x04 );
	_TEST32( "66832601 and word ptr [esi],0001h", 0x66, 0x83, 0x26, 0x01, 0x02, 0x03, 0x04 );
	_TEST32( "678326010203 and dword ptr [0201h],00000003h", 0x67, 0x83, 0x26, 0x01, 0x02, 0x03 );
	// REX.W + 83 /4 ib AND r/m64, imm8 B Valid N.E. r/m64 AND imm8 (signextended).
	_TEST64( "4883a70102030405 and qword ptr [rdi+0000000004030201h],0000000000000005h", 0x48, 0x83, 0xA7, 0x01, 0x02, 0x03, 0x4, 0x05 );
	_TEST64( "4883a701020304ff and qword ptr [rdi+0000000004030201h],0ffffffffffffffffh", 0x48, 0x83, 0xA7, 0x01, 0x02, 0x03, 0x4, 0xff );
	// 20 /r AND r/m8, r8 A Valid Valid r/m8 AND r8.
	// REX + 20 /r AND r/m8*, r8* A Valid N.E. r/m64 AND r8 (signextended).
	_TEST32( "20a501020304 and byte ptr [ebp+04030201h],ah", 0x20, 0xa5, 0x01, 0x02, 0x03, 04 );
	_TEST64( "4820a501020304 and byte ptr [rbp+0000000004030201h],dil", 0x48, 0x20, 0xa5, 0x01, 0x02, 0x03, 04 );
	_TEST64( "482064a501 and byte ptr [rbp+0000000000000001h],dil", 0x48, 0x20, 0x64, 0xa5, 0x01, 0x02, 0x03, 04 );
	// 21 /r AND r/m16, r16 A Valid Valid r/m16 AND r16.
	// 21 /r AND r/m32, r32 A Valid Valid r/m32 AND r32.
	// REX.W + 21 /r AND r/m64, r64 A Valid N.E. r/m64 AND r32.
	_TEST32( "21a501020304 and dword ptr [ebp+04030201h],esp", 0x21, 0xa5, 0x01, 0x02, 0x03, 04 );
	_TEST32( "676621a50102 and word ptr [di+0201h],sp", 0x67, 0x66, 0x21, 0xa5, 0x01, 0x02 );
	_TEST32( "6721a50102 and dword ptr [di+0201h],esp", 0x67, 0x21, 0xa5, 0x01, 0x02 );
	_TEST64( "4d21648901 and qword ptr [r9+rcx*4+0000000000000001h],r12", 0x4D, 0x21, 0x64, 0x89, 0x01 );
	// 22 /r AND r8, r/m8 A Valid Valid r8 AND r/m8.
	// REX + 22 /r AND r8*, r/m8* A Valid N.E. r/m64 AND r8 (signextended).
	_TEST32( "22a501020304 and ah,byte ptr [ebp+04030201h]", 0x22, 0xa5, 0x01, 0x02, 0x03, 04 );
	_TEST64( "4822a501020304 and dil,byte ptr [rbp+0000000004030201h]", 0x48, 0x22, 0xa5, 0x01, 0x02, 0x03, 04 );
	_TEST64( "482264a501 and dil,byte ptr [rbp+0000000000000001h]", 0x48, 0x22, 0x64, 0xa5, 0x01, 0x02, 0x03, 04 );
	// 23 /r AND r16, r/m16 A Valid Valid r16 AND r/m16.
	// 23 /r AND r32, r/m32 A Valid Valid r32 AND r/m32.
	// REX.W + 23 /r AND r64, r/m64 A Valid N.E. r64 AND r/m64.
	_TEST32( "23a501020304 and esp,dword ptr [ebp+04030201h]", 0x23, 0xa5, 0x01, 0x02, 0x03, 04 );
	_TEST32( "676623a50102 and sp,word ptr [di+0201h]", 0x67, 0x66, 0x23, 0xa5, 0x01, 0x02 );
	_TEST32( "6723a50102 and esp,dword ptr [di+0201h]", 0x67, 0x23, 0xa5, 0x01, 0x02 );
	_TEST64( "4d23648901 and r12,qword ptr [r9+rcx*4+0000000000000001h]", 0x4D, 0x23, 0x64, 0x89, 0x01 );

	// ANDPD
	_TEST32( "660f541401 andpd xmm2,oword ptr [ecx+eax]", 0x66, 0x0F, 0x54, 0x14, 0x01 );
	_TEST64( "660f541401 andpd xmm2,oword ptr [rcx+rax]", 0x66, 0x0F, 0x54, 0x14, 0x01 );

	// ANDPS
	_TEST32( "0f541401 andps xmm2,oword ptr [ecx+eax]", 0x0F, 0x54, 0x14, 0x01 );
	_TEST64( "0f541401 andps xmm2,oword ptr [rcx+rax]", 0x0F, 0x54, 0x14, 0x01 );

	// ANDNPD
	_TEST32( "660f551401 andnpd xmm2,oword ptr [ecx+eax]", 0x66, 0x0F, 0x55, 0x14, 0x01 );
	_TEST64( "660f551401 andnpd xmm2,oword ptr [rcx+rax]", 0x66, 0x0F, 0x55, 0x14, 0x01 );

	// ANDNPS
	_TEST32( "0f551401 andnps xmm2,oword ptr [ecx+eax]", 0x0F, 0x55, 0x14, 0x01 );
	_TEST64( "0f551401 andnps xmm2,oword ptr [rcx+rax]", 0x0F, 0x55, 0x14, 0x01 );

	// ARPL
	_TEST32( "631401 arpl word ptr [ecx+eax],dx", 0x63, 0x14, 0x01 );
	_TEST32( "66631401 arpl word ptr [ecx+eax],dx", 0x66, 0x63, 0x14, 0x01 );
	_TEST32( "676314 arpl word ptr [si],dx", 0x67, 0x63, 0x14, 0x01 );
	_TEST64( "FAIL", 0x63, 0xdf );

	// BLENDPD
	_TEST32( "660f3a0d1401ff blendpd xmm2,oword ptr [ecx+eax],0ffh", 0x66, 0x0F, 0x3a, 0x0D, 0x14, 0x01, 0xFF );
	_TEST64( "660f3a0d1401ff blendpd xmm2,oword ptr [rcx+rax],0ffh", 0x66, 0x0F, 0x3a, 0x0D, 0x14, 0x01, 0xFF );

	// BLENDPS
	_TEST32( "660f3a0c1401ff blendps xmm2,oword ptr [ecx+eax],0ffh", 0x66, 0x0F, 0x3a, 0x0C, 0x14, 0x01, 0xFF );
	_TEST64( "660f3a0c1401ff blendps xmm2,oword ptr [rcx+rax],0ffh", 0x66, 0x0F, 0x3a, 0x0C, 0x14, 0x01, 0xFF );

	//0x0F, 0x38, 0x15

	// BLENDVPD
	_TEST32( "660f38151401 blendvpd xmm2,oword ptr [ecx+eax],xmm0", 0x66, 0x0F, 0x38, 0x15, 0x14, 0x01, 0xFF );
	_TEST64( "660f38151401 blendvpd xmm2,oword ptr [rcx+rax],xmm0", 0x66, 0x0F, 0x38, 0x15, 0x14, 0x01, 0xFF );

	// BLENDVPS
	_TEST32( "660f38141401 blendvps xmm2,oword ptr [ecx+eax],xmm0", 0x66, 0x0F, 0x38, 0x14, 0x14, 0x01, 0xFF );
	_TEST64( "660f38141401 blendvps xmm2,oword ptr [rcx+rax],xmm0", 0x66, 0x0F, 0x38, 0x14, 0x14, 0x01, 0xFF );

	// BOUND
	_TEST32( "6230 bound esi,qword ptr [eax]", 0x62, 0x30 );
	_TEST32( "666230 bound si,dword ptr [eax]", 0x66, 0x62, 0x30 );
	_TEST32( "67666230 bound si,dword ptr [bx+si]", 0x67, 0x66, 0x62, 0x30 );
	_TEST64( "FAIL", 0x62, 0x30 ); // Not supported in 64.
	_TEST32( "FAIL", 0x62, 0xc0 ); // Addressing not supported, only memory addressing is allowed here.

	// BSF
	_TEST32( "0fbca501020304 bsf esp,dword ptr [ebp+04030201h]", 0x0f, 0xbc, 0xa5, 0x01, 0x02, 0x03, 04 );
	_TEST32( "67660fbca50102 bsf sp,word ptr [di+0201h]", 0x67, 0x66, 0x0f, 0xbc, 0xa5, 0x01, 0x02 );
	_TEST32( "670fbca50102 bsf esp,dword ptr [di+0201h]", 0x67, 0x0f, 0xbc, 0xa5, 0x01, 0x02 );
	_TEST64( "4d0fbc648901 bsf r12,qword ptr [r9+rcx*4+0000000000000001h]", 0x4D, 0x0f, 0xbc, 0x64, 0x89, 0x01 );

	// BSWAP
	_TEST32( "0fc8 bswap eax", 0x0f, 0xc8 );
	_TEST32( "0fc9 bswap ecx", 0x0f, 0xc9 );
	_TEST32( "0fca bswap edx", 0x0f, 0xca );
	_TEST32( "0fcb bswap ebx", 0x0f, 0xcb );
	_TEST32( "0fcc bswap esp", 0x0f, 0xcc );
	_TEST32( "0fcd bswap ebp", 0x0f, 0xcd );
	_TEST32( "0fce bswap esi", 0x0f, 0xce );
	_TEST32( "0fcf bswap edi", 0x0f, 0xcf );

	_TEST32( "660fc8 bswap eax", 0x66, 0x0f, 0xc8 );
	_TEST32( "660fc9 bswap ecx", 0x66, 0x0f, 0xc9 );
	_TEST32( "660fca bswap edx", 0x66, 0x0f, 0xca );
	_TEST32( "660fcb bswap ebx", 0x66, 0x0f, 0xcb );
	_TEST32( "660fcc bswap esp", 0x66, 0x0f, 0xcc );
	_TEST32( "660fcd bswap ebp", 0x66, 0x0f, 0xcd );
	_TEST32( "660fce bswap esi", 0x66, 0x0f, 0xce );
	_TEST32( "660fcf bswap edi", 0x66, 0x0f, 0xcf );

	_TEST64( "0fc8 bswap eax", 0x0f, 0xc8 );
	_TEST64( "0fc9 bswap ecx", 0x0f, 0xc9 );
	_TEST64( "0fca bswap edx", 0x0f, 0xca );
	_TEST64( "0fcb bswap ebx", 0x0f, 0xcb );
	_TEST64( "0fcc bswap esp", 0x0f, 0xcc );
	_TEST64( "0fcd bswap ebp", 0x0f, 0xcd );
	_TEST64( "0fce bswap esi", 0x0f, 0xce );
	_TEST64( "0fcf bswap edi", 0x0f, 0xcf );

	_TEST64( "660fc8 bswap eax", 0x66, 0x0f, 0xc8 );
	_TEST64( "660fc9 bswap ecx", 0x66, 0x0f, 0xc9 );
	_TEST64( "660fca bswap edx", 0x66, 0x0f, 0xca );
	_TEST64( "660fcb bswap ebx", 0x66, 0x0f, 0xcb );
	_TEST64( "660fcc bswap esp", 0x66, 0x0f, 0xcc );
	_TEST64( "660fcd bswap ebp", 0x66, 0x0f, 0xcd );
	_TEST64( "660fce bswap esi", 0x66, 0x0f, 0xce );
	_TEST64( "660fcf bswap edi", 0x66, 0x0f, 0xcf );

	// only REX.R
	_TEST64( "4c0fc8 bswap r8", 0x4c, 0x0f, 0xc8 );
	_TEST64( "4c0fc9 bswap r9", 0x4c, 0x0f, 0xc9 );
	_TEST64( "4c0fca bswap r10", 0x4c, 0x0f, 0xca );
	_TEST64( "4c0fcb bswap r11", 0x4c, 0x0f, 0xcb );
	_TEST64( "4c0fcc bswap r12", 0x4c, 0x0f, 0xcc );
	_TEST64( "4c0fcd bswap r13", 0x4c, 0x0f, 0xcd );
	_TEST64( "4c0fce bswap r14", 0x4c, 0x0f, 0xce );
	_TEST64( "4c0fcf bswap r15", 0x4c, 0x0f, 0xcf );

	// BT.
	// 0F A3 BT r/m16, r16 A Valid Valid Store selected bit in CF flag.
	// 0F A3 BT r/m32, r32 A Valid Valid Store selected bit in CF flag.
	// REX.W + 0F A3 BT r/m64, r64 A Valid N.E. Store selected bit in CF flag.
	_TEST32( "0fa306 bt dword ptr [esi],eax", 0x0F, 0xA3, 0x06 );
	_TEST32( "660fa306 bt word ptr [esi],ax", 0x66, 0x0F, 0xA3, 0x06 );
	_TEST32( "670fa3060102 bt dword ptr [0201h],eax", 0x67, 0x0F, 0xA3, 0x06, 0x01, 0x02 );
	// 0F BA /4 ib BT r/m16, imm8 B Valid Valid Store selected bit in CF flag.
	// 0F BA /4 ib BT r/m32, imm8 B Valid Valid Store selected bit in CF flag.
	// REX.W + 0F BA /4 ib BT r/m64, imm8 B Valid N.E. Store selected bit in CF flag.
	// EOS=32 EAS=64 (displacement extended to 64 bits)
	_TEST64( "0fbaa70102030405 bt dword ptr [rdi+0000000004030201h],05h", 0x0F, 0xBA, 0xA7, 0x01, 0x02, 0x03, 0x4, 0x05 );
	// EOS=32 EAS=32 (displacement is not extended because EAS is 32)
	_TEST64( "670fbaa70102030405 bt dword ptr [edi+04030201h],05h", 0x67, 0x0F, 0xBA, 0xA7, 0x01, 0x02, 0x03, 0x4, 0x05 );
	// EOS=64 EAS=64
	_TEST64( "480fbaa70102030405 bt qword ptr [rdi+0000000004030201h],05h", 0x48, 0x0F, 0xBA, 0xA7, 0x01, 0x02, 0x03, 0x4, 0x05 );
	// EOS=64 EAS=64
	_TEST64( "480fbaa701020304ff bt qword ptr [rdi+0000000004030201h],0ffh", 0x48, 0x0F, 0xBA, 0xA7, 0x01, 0x02, 0x03, 0x4, 0xff );

	// BTC.
	// 0F BB BTC r/m16, r16 A Valid Valid Store selected bit in CF flag and complement.
	// 0F BB BTC r/m32, r32 A Valid Valid Store selected bit in CF flag and complement.
	// REX.W + 0F BB BTC r/m64, r64 A Valid N.E. Store selected bit in CF flag and complement.
	_TEST32( "0fbb06 btc dword ptr [esi],eax", 0x0F, 0xBB, 0x06 );
	_TEST32( "660fbb06 btc word ptr [esi],ax", 0x66, 0x0F, 0xBB, 0x06 );
	_TEST32( "670fbb060102 btc dword ptr [0201h],eax", 0x67, 0x0F, 0xBB, 0x06, 0x01, 0x02 );
	// 0F BA /7 ib BTC r/m16, imm8 B Valid Valid Store selected bit in CF flag and complement.
	// 0F BA /7 ib BTC r/m32, imm8 B Valid Valid Store selected bit in CF flag and complement.
	// REX.W + 0F BA /7 ib BTC r/m64, imm8 B Valid N.E. Store selected bit in CF flag and complement.
	// EOS=32 EAS=64 (displacement extended to 64 bits)
	_TEST64( "0fbabf0102030405 btc dword ptr [rdi+0000000004030201h],05h", 0x0F, 0xBA, 0xBF, 0x01, 0x02, 0x03, 0x4, 0x05 );
	// EOS=32 EAS=32 (displacement is not extended because EAS is 32)
	_TEST64( "670fbabf0102030405 btc dword ptr [edi+04030201h],05h", 0x67, 0x0F, 0xBA, 0xBF, 0x01, 0x02, 0x03, 0x4, 0x05 );
	// EOS=64 EAS=64
	_TEST64( "480fbabf0102030405 btc qword ptr [rdi+0000000004030201h],05h", 0x48, 0x0F, 0xBA, 0xBF, 0x01, 0x02, 0x03, 0x4, 0x05 );
	// EOS=64 EAS=64
	_TEST64( "480fbabf01020304ff btc qword ptr [rdi+0000000004030201h],0ffh", 0x48, 0x0F, 0xBA, 0xBF, 0x01, 0x02, 0x03, 0x4, 0xff );

	// BTR.
	// 0F B3 BTR r/m16, r16 A Valid Valid Store selected bit in CF flag and clear.
	// 0F B3 BTR r/m32, r32 A Valid Valid Store selected bit in CF flag and clear.
	// REX.W + 0F B3 BTR r/m64, r64 A Valid N.E. Store selected bit in CF flag and clear.
	_TEST32( "0fb306 btr dword ptr [esi],eax", 0x0F, 0xB3, 0x06 );
	_TEST32( "660fb306 btr word ptr [esi],ax", 0x66, 0x0F, 0xB3, 0x06 );
	_TEST32( "670fb3060102 btr dword ptr [0201h],eax", 0x67, 0x0F, 0xB3, 0x06, 0x01, 0x02 );
	// 0F BA /6 ib BTR r/m16, imm8 B Valid Valid Store selected bit in CF flag and clear.
	// 0F BA /6 ib BTR r/m32, imm8 B Valid Valid Store selected bit in CF flag and clear.
	// REX.W + 0F BA /6 ib BTR r/m64, imm8 B Valid N.E. Store selected bit in CF flag and clear.
	// EOS=32 EAS=64 (displacement extended to 64 bits)
	_TEST64( "0fbab70102030405 btr dword ptr [rdi+0000000004030201h],05h", 0x0F, 0xBA, 0xB7, 0x01, 0x02, 0x03, 0x4, 0x05 );
	// EOS=32 EAS=32 (displacement is not extended because EAS is 32)
	_TEST64( "670fbab70102030405 btr dword ptr [edi+04030201h],05h", 0x67, 0x0F, 0xBA, 0xB7, 0x01, 0x02, 0x03, 0x4, 0x05 );
	// EOS=64 EAS=64
	_TEST64( "480fbab70102030405 btr qword ptr [rdi+0000000004030201h],05h", 0x48, 0x0F, 0xBA, 0xB7, 0x01, 0x02, 0x03, 0x4, 0x05 );
	// EOS=64 EAS=64
	_TEST64( "480fbab701020304ff btr qword ptr [rdi+0000000004030201h],0ffh", 0x48, 0x0F, 0xBA, 0xB7, 0x01, 0x02, 0x03, 0x4, 0xff );

	// BTS.
	// 0F AB BTS r/m16, r16 A Valid Valid Store selected bit in CF flag and set.
	// 0F AB BTS r/m32, r32 A Valid Valid Store selected bit in CF flag and set.
	// REX.W + 0F AB BTS r/m64, r64 A Valid N.E. Store selected bit in CF flag and set.
	_TEST32( "0fab06 bts dword ptr [esi],eax", 0x0F, 0xAB, 0x06 );
	_TEST32( "660fab06 bts word ptr [esi],ax", 0x66, 0x0F, 0xAB, 0x06 );
	_TEST32( "670fab060102 bts dword ptr [0201h],eax", 0x67, 0x0F, 0xAB, 0x06, 0x01, 0x02 );
	// 0F BA /5 ib BTS r/m16, imm8 B Valid Valid Store selected bit in CF flag and set.
	// 0F BA /5 ib BTS r/m32, imm8 B Valid Valid Store selected bit in CF flag and set.
	// REX.W + 0F BA /5 ib BTS r/m64, imm8 B Valid N.E. Store selected bit in CF flag and set.
	// EOS=32 EAS=64 (displacement extended to 64 bits)
	_TEST64( "0fbaaf0102030405 bts dword ptr [rdi+0000000004030201h],05h", 0x0F, 0xBA, 0xAF, 0x01, 0x02, 0x03, 0x4, 0x05 );
	// EOS=32 EAS=32 (displacement is not extended because EAS is 32)
	_TEST64( "670fbaaf0102030405 bts dword ptr [edi+04030201h],05h", 0x67, 0x0F, 0xBA, 0xAF, 0x01, 0x02, 0x03, 0x4, 0x05 );
	// EOS=64 EAS=64
	_TEST64( "480fbaaf0102030405 bts qword ptr [rdi+0000000004030201h],05h", 0x48, 0x0F, 0xBA, 0xAF, 0x01, 0x02, 0x03, 0x4, 0x05 );
	// EOS=64 EAS=64
	_TEST64( "480fbaaf01020304ff bts qword ptr [rdi+0000000004030201h],0ffh", 0x48, 0x0F, 0xBA, 0xAF, 0x01, 0x02, 0x03, 0x4, 0xff );

}


