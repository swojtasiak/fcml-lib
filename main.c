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

void test_code( int is32, uint8_t code[], int size, char *mnemonic );

int main()
{
	ira_init();
	test();
	ira_deinit();

    return 0;
}


#define _TEST32(x,...) { uint8_t code[] = {__VA_ARGS__}; test_code( 1, code, sizeof(code), x ); }
#define _TEST64(x,...) { uint8_t code[] = {__VA_ARGS__}; test_code( 0, code, sizeof(code), x ); }

void _test_vax(void);

//102
void test(void) {

	_test_vax();

	// OR
	// 0C ib OR AL, imm8 I Valid Valid AL OR imm8.
	_TEST32( "0c42 or al,42h", 0x0c, 0x42 );
	_TEST32( "0cff or al,0ffh", 0x0c, 0xff );
	_TEST64( "0c42 or al,42h", 0x0c, 0x42 );
	_TEST64( "0c00 or al,00h", 0x0c, 0x00 );
	_TEST64( "0cff or al,0ffh", 0x0c, 0xff );
	// 0D iw OR AX, imm16 I Valid Valid AX OR imm16.
	// 0D id OR EAX, imm32 I Valid Valid EAX OR imm32.
	_TEST32( "660d4280 or ax,8042h", 0x66, 0x0d, 0x42, 0x80 );
	_TEST32( "0d21658042 or eax,42806521h", 0x0d, 0x21, 0x65, 0x80, 0x42 );
	_TEST64( "400d21658042 or eax,42806521h", 0x40, 0x0d, 0x21, 0x65, 0x80, 0x42 );
	_TEST64( "66400d2165 or ax,6521h", 0x66, 0x40, 0x0d, 0x21, 0x65, 0x80, 0x42 );
	// REX.W + 0D id OR RAX, imm32 I Valid N.E. RAX OR imm32 (sign-extended).
	_TEST64( "480d21658042 or rax,0000000042806521h", 0x48, 0x0d, 0x21, 0x65, 0x80, 0x42 );
	_TEST64( "66480d21658042 or rax,0000000042806521h", 0x66, 0x48, 0x0d, 0x21, 0x65, 0x80, 0x42 );
	_TEST64( "6766480d21658042 or rax,0000000042806521h", 0x67, 0x66, 0x48, 0x0d, 0x21, 0x65, 0x80, 0x42 );
	_TEST64( "6766480dffffffff or rax,0ffffffffffffffffh", 0x67, 0x66, 0x48, 0x0d, 0xff, 0xff, 0xff, 0xff );
	// 80 /1 ib OR r/m8, imm8 MI Valid Valid r/m8 OR imm8.
	// REX + 80 /1 ib OR r/m8*, imm8 MI Valid N.E. r/m8 OR imm8.
	_TEST32( "800d01020304ff or byte ptr [04030201h],0ffh", 0x80, 0x0d, 0x01, 0x02, 0x03, 0x04, 0xff );
	_TEST32( "808e01020304ff or byte ptr [esi+04030201h],0ffh", 0x80, 0x8e, 0x01, 0x02, 0x03, 0x04, 0xff, 0x00, 0x00 );
	_TEST32( "804c010203 or byte ptr [ecx+eax+00000002h],03h", 0x80, 0x4c, 0x01, 0x02, 0x03 );
	// 81 /1 iw OR r/m16, imm16 MI Valid Valid r/m16 OR imm16.
	// 81 /1 id OR r/m32, imm32 MI Valid Valid r/m32 OR imm32.
	_TEST32( "81cd01020304 or ebp,04030201h", 0x81, 0xcd, 0x01, 0x02, 0x03, 0x04 );
	_TEST32( "6681cd0102 or bp,0201h", 0x66, 0x81, 0xcd, 0x01, 0x02 );
	_TEST64( "67664081cd0102 or bp,0201h", 0x67, 0x66, 0x40, 0x81, 0xcd, 0x01, 0x02 ); // 32 bit mode doesn't not allow REX.
	// REX.W + 81 /1 id OR r/m64, imm32 MI Valid N.E. r/m64 OR imm32 (sign-extended).
	_TEST64( "4881cd01020304 or rbp,0000000004030201h", 0x48, 0x81, 0xcd, 0x01, 0x02, 0x03, 0x04 );
	_TEST64( "4881cdffffffff or rbp,0ffffffffffffffffh", 0x48, 0x81, 0xcd, 0xff, 0xff, 0xff, 0xff );
	_TEST64( "674881cdffffffff or rbp,0ffffffffffffffffh", 0x67, 0x48, 0x81, 0xcd, 0xff, 0xff, 0xff, 0xff );
	_TEST64( "664881cdffffffff or rbp,0ffffffffffffffffh", 0x66, 0x48, 0x81, 0xcd, 0xff, 0xff, 0xff, 0xff );
	// 83 /1 ib OR r/m16, imm8 MI Valid Valid r/m16 OR imm8 (sign-extended).
	// 83 /1 ib OR r/m32, imm8 MI Valid Valid r/m32 OR imm8 (sign-extended).
	_TEST32( "830e01 or dword ptr [esi],00000001h", 0x83, 0x0e, 0x01, 0x02, 0x03, 0x04 );
	_TEST32( "66830e01 or word ptr [esi],0001h", 0x66, 0x83, 0x0e, 0x01, 0x02, 0x03, 0x04 );
	_TEST32( "67830e010203 or dword ptr [0201h],00000003h", 0x67, 0x83, 0x0e, 0x01, 0x02, 0x03 );
	// REX.W + 83 /1 ib OR r/m64, imm8 MI Valid N.E. r/m64 OR imm8 (sign-extended).
	_TEST64( "48838f0102030405 or qword ptr [rdi+0000000004030201h],0000000000000005h", 0x48, 0x83, 0x8f, 0x01, 0x02, 0x03, 0x4, 0x05 );
	_TEST64( "48838f01020304ff or qword ptr [rdi+0000000004030201h],0ffffffffffffffffh", 0x48, 0x83, 0x8f, 0x01, 0x02, 0x03, 0x4, 0xff );
	// 08 /r OR r/m8, r8 MR Valid Valid r/m8 OR r8.
	// REX + 08 /r OR r/m8*, r8* MR Valid N.E. r/m8 OR r8.
	_TEST32( "08a501020304 or byte ptr [ebp+04030201h],ah", 0x08, 0xa5, 0x01, 0x02, 0x03, 04 );
	_TEST64( "4808a501020304 or byte ptr [rbp+0000000004030201h],spl", 0x48, 0x08, 0xa5, 0x01, 0x02, 0x03, 04 );
	_TEST64( "480864a501 or byte ptr [rbp+0000000000000001h],spl", 0x48, 0x08, 0x64, 0xa5, 0x01, 0x02, 0x03, 04 );
	// 09 /r OR r/m16, r16 MR Valid Valid r/m16 OR r16.
	// 09 /r OR r/m32, r32 MR Valid Valid r/m32 OR r32.
	// REX.W + 09 /r OR r/m64, r64 MR Valid N.E. r/m64 OR r64.
	_TEST32( "09a501020304 or dword ptr [ebp+04030201h],esp", 0x09, 0xa5, 0x01, 0x02, 0x03, 04 );
	_TEST32( "676609a50102 or word ptr [di+0201h],sp", 0x67, 0x66, 0x09, 0xa5, 0x01, 0x02 );
	_TEST32( "6709a50102 or dword ptr [di+0201h],esp", 0x67, 0x09, 0xa5, 0x01, 0x02 );
	_TEST64( "4d09648901 or qword ptr [r9+rcx*4+0000000000000001h],r12", 0x4D, 0x09, 0x64, 0x89, 0x01 );
	// 0A /r OR r8, r/m8 RM Valid Valid r8 OR r/m8.
	// REX + 0A /r OR r8*, r/m8* RM Valid N.E. r8 OR r/m8.
	_TEST32( "0aa501020304 or ah,byte ptr [ebp+04030201h]", 0x0a, 0xa5, 0x01, 0x02, 0x03, 04 );
	_TEST64( "480aa501020304 or spl,byte ptr [rbp+0000000004030201h]", 0x48, 0x0a, 0xa5, 0x01, 0x02, 0x03, 04 );
	_TEST64( "480a64a501 or spl,byte ptr [rbp+0000000000000001h]", 0x48, 0x0a, 0x64, 0xa5, 0x01, 0x02, 0x03, 04 );
	// 0B /r OR r16, r/m16 RM Valid Valid r16 OR r/m16.
	// 0B /r OR r32, r/m32 RM Valid Valid r32 OR r/m32.
	// REX.W + 0B /r OR r64, r/m64 RM Valid N.E. r64 OR r/m64.
	_TEST32( "0ba501020304 or esp,dword ptr [ebp+04030201h]", 0x0b, 0xa5, 0x01, 0x02, 0x03, 04 );
	_TEST32( "67660ba50102 or sp,word ptr [di+0201h]", 0x67, 0x66, 0x0b, 0xa5, 0x01, 0x02 );
	_TEST32( "670ba50102 or esp,dword ptr [di+0201h]", 0x67, 0x0b, 0xa5, 0x01, 0x02 );
	_TEST64( "4d0b648901 or r12,qword ptr [r9+rcx*4+0000000000000001h]", 0x4D, 0x0b, 0x64, 0x89, 0x01 );

	// NOT
	// F6 /2 NOT r/m8 M Valid Valid Reverse each bit of r/m8.
	// REX + F6 /2 NOT r/m8* M Valid N.E. Reverse each bit of r/m8.
	_TEST32( "f610 not byte ptr [eax]", 0xF6, 0x10 );
	_TEST64( "48f610 not byte ptr [rax]", 0x48, 0xF6, 0x10 );
	// F7 /2 NOT r/m16 M Valid Valid Reverse each bit of r/m16.
	// F7 /2 NOT r/m32 M Valid Valid Reverse each bit of r/m32.
	// REX.W + F7 /2 NOT r/m64 M Valid N.E. Reverse each bit of r/m64.
	_TEST32( "66f710 not word ptr [eax]", 0x66, 0xF7, 0x10 );
	_TEST32( "f710 not dword ptr [eax]", 0xF7, 0x10 );
	_TEST64( "48f710 not qword ptr [rax]", 0x48, 0xF7, 0x10 );

	// NOP
	// 90 NOP NP Valid Valid One byte no-operation instruction.
	_TEST32( "90 nop", 0x90 );
	_TEST64( "90 nop", 0x90 );
	// 0F 1F /0 NOP r/m16 M Valid Valid Multi-byte no-operation instruction.
	// 0F 1F /0 NOP r/m32 M Valid Valid Multi-byte no-operation instruction.
	_TEST32( "660f1f00 nop word ptr [eax]", 0x66, 0x0f, 0x1f, 0x00 );
	_TEST32( "0f1f00 nop dword ptr [eax]", 0x0f, 0x1f, 0x00 );
	_TEST64( "480f1f00 nop qword ptr [rax]", 0x48, 0x0f, 0x1f, 0x00 );

	// NEG
	// F6 /3 NEG r/m8 M Valid Valid Two's complement negate r/m8.
	// REX + F6 /3 NEG r/m8* M Valid N.E. Two's complement negate r/m8.
	_TEST32( "f618 neg byte ptr [eax]", 0xF6, 0x18 );
	_TEST64( "48f618 neg byte ptr [rax]", 0x48, 0xF6, 0x18);
	// F7 /3 NEG r/m16 M Valid Valid Two's complement negate r/m16.
	// F7 /3 NEG r/m32 M Valid Valid Two's complement negate r/m32.
	// REX.W + F7 /3 NEG r/m64 M Valid N.E. Two's complement negate r/m64.
	_TEST32( "66f718 neg word ptr [eax]", 0x66, 0xF7, 0x18 );
	_TEST32( "f718 neg dword ptr [eax]", 0xF7, 0x18 );
	_TEST64( "48f718 neg qword ptr [rax]", 0x48, 0xF7, 0x18 );

	// MWAIT
	// 0F 01 C9
	_TEST32( "0f01c9 mwait", 0x0F, 0x01, 0xC9 );
	_TEST64( "0f01c9 mwait", 0x0F, 0x01, 0xC9 );

	// MULSS
	// F3 0F 59 /r MULSS xmm1,xmm2/m32
	_TEST32( "f30f5910 mulss xmm2,dword ptr [eax]", 0xF3, 0x0F, 0x59, 0x10 );
	_TEST32( "f30f59d8 mulss xmm3,xmm0", 0xF3, 0x0F, 0x59, 0xD8 );
	_TEST64( "f30f5910 mulss xmm2,dword ptr [rax]", 0xF3, 0x0F, 0x59, 0x10 );

	// MULSD
	//F2 0F 59 /r MULSD xmm1,xmm2/m64
	_TEST32( "f20f5910 mulsd xmm2,qword ptr [eax]", 0xF2, 0x0F, 0x59, 0x10 );
	_TEST32( "f20f59d8 mulsd xmm3,xmm0", 0xF2, 0x0F, 0x59, 0xD8 );
	_TEST64( "f20f5910 mulsd xmm2,qword ptr [rax]", 0xF2, 0x0F, 0x59, 0x10 );

	// MULPS
	// 0F 59 /r MULPS xmm1,xmm2/m128
	_TEST32( "0f5910 mulps xmm2,oword ptr [eax]", 0x0F, 0x59, 0x10 );
	_TEST32( "0f59d8 mulps xmm3,xmm0", 0x0F, 0x59, 0xD8 );
	_TEST64( "0f5910 mulps xmm2,oword ptr [rax]", 0x0F, 0x59, 0x10 );

	// MULPD
	// 66 0F 59 /r MULPD xmm1,xmm2/m128
	_TEST32( "660f5910 mulpd xmm2,oword ptr [eax]", 0x66, 0x0F, 0x59, 0x10 );
	_TEST32( "660f59d8 mulpd xmm3,xmm0", 0x66, 0x0F, 0x59, 0xD8 );
	_TEST64( "660f5910 mulpd xmm2,oword ptr [rax]", 0x66, 0x0F, 0x59, 0x10 );

	// MUL
	// F6 /4 MUL r/m8
	// REX + F6 /4 MUL r/m8
	_TEST32( "66f620 mul byte ptr [eax]", 0x66, 0xF6, 0x20 );
	_TEST32( "f620 mul byte ptr [eax]", 0xF6, 0x20 );
	_TEST64( "66f620 mul byte ptr [rax]", 0x66, 0xF6, 0x20 );
	_TEST64( "f620 mul byte ptr [rax]", 0xF6, 0x20 );
	_TEST64( "48f620 mul byte ptr [rax]", 0x48, 0xF6, 0x20 );
	// F7 /4 MUL r/m16
	// F7 /4 MUL r/m32
	// REX.W + F7 /4 MUL r/m64
	_TEST32( "66f720 mul word ptr [eax]", 0x66, 0xF7, 0x20 );
	_TEST32( "f720 mul dword ptr [eax]", 0xF7, 0x20 );
	_TEST64( "66f720 mul word ptr [rax]", 0x66, 0xF7, 0x20 );
	_TEST64( "f720 mul dword ptr [rax]", 0xF7, 0x20 );
	_TEST64( "48f720 mul qword ptr [rax]", 0x48, 0xF7, 0x20 );

	// MPSADBW
	// 66 0F 3A 42 /r ib MPSADBW xmm1, xmm2/m128, imm8
	_TEST32( "660f3a421020 mpsadbw xmm2,oword ptr [eax],20h", 0x66, 0x0F, 0x3A, 0x42, 0x10, 0x20 );
	_TEST32( "660f3a42d620 mpsadbw xmm2,xmm6,20h", 0x66, 0x0F, 0x3A, 0x42, 0xD6, 0x20 );
	_TEST64( "660f3a421020 mpsadbw xmm2,oword ptr [rax],20h", 0x66, 0x0F, 0x3A, 0x42, 0x10, 0x20 );
	_TEST64( "66480f3a421020 mpsadbw xmm2,oword ptr [rax],20h", 0x66, 0x48, 0x0F, 0x3A, 0x42, 0x10, 0x20 );

	// 0F B6 /r MOVZX r16, r/m8
	// 0F B6 /r MOVZX r32, r/m8
	// REX.W + 0F B6 /r MOVZX r64, r/m8
	_TEST32( "660fb610 movzx dx,byte ptr [eax]", 0x66, 0x0F, 0xB6, 0x10 );
	_TEST32( "0fb610 movzx edx,byte ptr [eax]", 0x0F, 0xB6, 0x10 );
	_TEST64( "660fb610 movzx dx,byte ptr [rax]", 0x66, 0x0F, 0xB6, 0x10 );
	_TEST64( "0fb610 movzx edx,byte ptr [rax]", 0x0F, 0xB6, 0x10 );
	_TEST64( "480fb610 movzx rdx,byte ptr [rax]", 0x48, 0x0F, 0xB6, 0x10 );
	// 0F B7 /r MOVZX r32,r/m16
	// REX.W + 0F B7 /r MOVZX r64,r/m16
	_TEST32( "660fb710 movzx edx,word ptr [eax]", 0x66, 0x0F, 0xB7, 0x10 );
	_TEST32( "0fb710 movzx edx,word ptr [eax]", 0x0F, 0xB7, 0x10 );
	_TEST64( "660fb710 movzx edx,word ptr [rax]", 0x66, 0x0F, 0xB7, 0x10 );
	_TEST64( "480fb710 movzx rdx,word ptr [rax]", 0x48, 0x0F, 0xB7, 0x10 );

	// MOVUPS
	// 0F 10 /r MOVUPS xmm1,xmm2/m128
	_TEST32( "0f1010 movups xmm2,oword ptr [eax]", 0x0F, 0x10, 0x10 );
	_TEST32( "0f10d8 movups xmm3,xmm0", 0x0F, 0x10, 0xD8 );
	_TEST64( "0f1010 movups xmm2,oword ptr [rax]",0x0F, 0x10, 0x10 );
	// 0F 11 /r MOVUPS xmm2/m128, xmm1
	_TEST32( "0f1110 movups oword ptr [eax],xmm2", 0x0F, 0x11, 0x10 );
	_TEST32( "0f11d8 movups xmm0,xmm3", 0x0F, 0x11, 0xD8 );
	_TEST64( "0f1110 movups oword ptr [rax],xmm2", 0x0F, 0x11, 0x10 );

	// MOVUPD
	// 66 0F 10 /r MOVUPD xmm1,xmm2/m128
	_TEST32( "660f1010 movupd xmm2,oword ptr [eax]", 0x66, 0x0F, 0x10, 0x10 );
	_TEST32( "660f10d8 movupd xmm3,xmm0", 0x66, 0x0F, 0x10, 0xD8 );
	_TEST64( "660f1010 movupd xmm2,oword ptr [rax]", 0x66, 0x0F, 0x10, 0x10 );
	// 66 0F 11 /r MOVUPD xmm2/m128,xmm
	_TEST32( "660f1110 movupd oword ptr [eax],xmm2", 0x66, 0x0F, 0x11, 0x10 );
	_TEST32( "660f11d8 movupd xmm0,xmm3", 0x66, 0x0F, 0x11, 0xD8 );
	_TEST64( "660f1110 movupd oword ptr [rax],xmm2", 0x66, 0x0F, 0x11, 0x10 );

	// MOVSX
	// 0F BE /r MOVSX r16, r/m8
	// 0F BE /r MOVSX r32, r/m8
	_TEST32( "660fbe10 movsx dx,byte ptr [eax]", 0x66, 0x0F, 0xBE, 0x10 );
	_TEST32( "0fbe10 movsx edx,byte ptr [eax]", 0x0F, 0xBE, 0x10 );
	// REX + 0F BE /r MOVSX r64, r/m8
	_TEST64( "660fbe10 movsx dx,byte ptr [rax]", 0x66, 0x0F, 0xBE, 0x10 );
	_TEST64( "0fbe10 movsx edx,byte ptr [rax]", 0x0F, 0xBE, 0x10 );
	_TEST64( "480fbe10 movsx rdx,byte ptr [rax]", 0x48, 0x0F, 0xBE, 0x10 );
	// 0F BF /r MOVSX r32, r/m16
	// REX.W + 0F BF /r MOVSX r64, r/m16
	_TEST32( "660fbf10 movsx edx,word ptr [eax]", 0x66, 0x0F, 0xBF, 0x10 );
	_TEST32( "0fbf10 movsx edx,word ptr [eax]", 0x0F, 0xBF, 0x10 );
	_TEST64( "480fbf10 movsx rdx,word ptr [rax]", 0x48, 0x0F, 0xBF, 0x10 );
	// REX.W** + 63 /r MOVSXD r64, r/m32
	_TEST64( "486310 movsxd rdx,dword ptr [rax]", 0x48, 0x63, 0x10 );

	// MOVSS
	// F3 0F 10 /r MOVSS xmm1,xmm2/m32
	_TEST32( "f30f1010 movss xmm2,dword ptr [eax]", 0xF3, 0x0F, 0x10, 0x10 );
	_TEST32( "f30f10d8 movss xmm3,xmm0", 0xF3, 0x0F, 0x10, 0xD8 );
	_TEST64( "f30f1010 movss xmm2,dword ptr [rax]", 0xF3, 0x0F, 0x10, 0x10 );
	// F3 0F 11 /r MOVSS xmm2/m32, xmm
	_TEST32( "f30f1110 movss dword ptr [eax],xmm2", 0xF3, 0x0F, 0x11, 0x10 );
	_TEST32( "f30f11d8 movss xmm0,xmm3", 0xF3, 0x0F, 0x11, 0xD8 );
	_TEST64( "f30f1110 movss dword ptr [rax],xmm2", 0xF3, 0x0F, 0x11, 0x10 );

	// MOVSLDUP
	// F3 0F 12 /r MOVSLDUP xmm1,xmm2/m128
	_TEST32( "f30f1210 movsldup xmm2,oword ptr [eax]", 0xF3, 0x0F, 0x12, 0x10 );
	_TEST32( "f30f12d8 movsldup xmm3,xmm0", 0xF3, 0x0F, 0x12, 0xD8 );
	_TEST64( "f30f1210 movsldup xmm2,oword ptr [rax]", 0xF3, 0x0F, 0x12, 0x10 );

	// MOVSHDUP
	// F3 0F 16 /r MOVSHDUP xmm1,xmm2/m128
	_TEST32( "f30f1610 movshdup xmm2,oword ptr [eax]", 0xF3, 0x0F, 0x16, 0x10 );
	_TEST32( "f30f16d8 movshdup xmm3,xmm0", 0xF3, 0x0F, 0x16, 0xD8 );
	_TEST64( "f30f1610 movshdup xmm2,oword ptr [rax]", 0xF3, 0x0F, 0x16, 0x10 );

	// MOVSD
	// F2 0F 10 /r MOVSD xmm1,xmm2/m64
	_TEST32( "f20f1010 movsd xmm2,qword ptr [eax]", 0xF2, 0x0F, 0x10, 0x10 );
	_TEST32( "f20f10d8 movsd xmm3,xmm0", 0xF2, 0x0F, 0x10, 0xD8 );
	_TEST64( "f20f1010 movsd xmm2,qword ptr [rax]", 0xF2, 0x0F, 0x10, 0x10 );
	// F2 0F 11 /r MOVSD xmm2/m64, xmm1
	_TEST32( "f20f1110 movsd qword ptr [eax],xmm2", 0xF2, 0x0F, 0x11, 0x10 );
	_TEST32( "f20f11d8 movsd xmm0,xmm3", 0xF2, 0x0F, 0x11, 0xD8 );
	_TEST64( "f20f1110 movsd qword ptr [rax],xmm2", 0xF2, 0x0F, 0x11, 0x10 );

	// MOVS
	// A4 MOVS m8, m8
	_TEST32( "67a4 movs byte ptr [si],byte ptr [di]", 0x67, 0xA4 );
	_TEST32( "6667a4 movs byte ptr [si],byte ptr [di]", 0x66, 0x67, 0xA4 );
	_TEST32( "a4 movs byte ptr [esi],byte ptr [edi]", 0xA4 );
	_TEST64( "48a4 movs byte ptr [rsi],byte ptr [rdi]", 0x48, 0xA4 );
	_TEST64( "40a4 movs byte ptr [rsi],byte ptr [rdi]", 0x40, 0xA4 );
	_TEST64( "6740a4 movs byte ptr [esi],byte ptr [edi]", 0x67, 0x40, 0xA4 );
	_TEST64( "666740a4 movs byte ptr [esi],byte ptr [edi]", 0x66, 0x67, 0x40, 0xA4 );
	// A5 MOVS m16, m16
	// A5 MOVS m32, m32
	// REX.W + A5 MOVS m64, m64
	_TEST32( "67a5 movs dword ptr [si],dword ptr [di]", 0x67, 0xA5 );
	_TEST32( "6667a5 movs word ptr [si],word ptr [di]", 0x66, 0x67, 0xA5 );
	_TEST32( "a5 movs dword ptr [esi],dword ptr [edi]", 0xA5 );
	_TEST64( "48a5 movs qword ptr [rsi],qword ptr [rdi]", 0x48, 0xA5 );
	_TEST64( "40a5 movs dword ptr [rsi],dword ptr [rdi]", 0x40, 0xA5 );
	_TEST64( "6740a5 movs dword ptr [esi],dword ptr [edi]", 0x67, 0x40, 0xA5 );
	_TEST64( "666740a5 movs word ptr [esi],word ptr [edi]", 0x66, 0x67, 0x40, 0xA5 );

	// MOVQ2DQ
	// F3 0F D6 MOVQ2DQ xmm,mm
	_TEST32( "f30fd6d0 movq2dq xmm0,mm2", 0xF3, 0x0F, 0xD6, 0xD0 );
	_TEST32( "f30fd6d8 movq2dq xmm0,mm3", 0xF3, 0x0F, 0xD6, 0xD8 );
	_TEST64( "f30fd6d0 movq2dq xmm0,mm2", 0xF3, 0x0F, 0xD6, 0xD0 );
	_TEST64( "f3480fd6d0 movq2dq xmm0,mm2", 0xF3, 0x48, 0x0F, 0xD6, 0xD0 );

	// MOVQ
	// 0F 6F /r MOVQ mm, mm/m64 A Valid Valid Move quadword from mm/m64 to mm.
	_TEST32( "0f6f00 movq mm0,qword ptr [eax]", 0x0F, 0x6F, 0x00 );
	_TEST64( "0f6f00 movq mm0,qword ptr [rax]",  0x0F, 0x6F, 0x00 );
	_TEST64( "0f6fd0 movq mm2,mm0",  0x0F, 0x6F, 0xD0 );
	_TEST64( "480f6f00 movq mm0,qword ptr [rax]", 0x48, 0x0F, 0x6F, 0x00 );
	// 0F 7F /r MOVQ mm/m64, mm B Valid Valid Move quadword from mm to mm/m64.
	_TEST32( "0f7f00 movq qword ptr [eax],mm0", 0x0F, 0x7F, 0x00 );
	_TEST64( "0f7f00 movq qword ptr [rax],mm0",  0x0F, 0x7F, 0x00 );
	_TEST64( "0f7fd0 movq mm0,mm2",  0x0F, 0x7F, 0xD0 );
	_TEST64( "480f7f00 movq qword ptr [rax],mm0", 0x48, 0x0F, 0x7F, 0x00 );
	// F3 0F 7E MOVQ xmm1, xmm2/m64 A Valid Valid Move quadword from xmm2/mem64 to xmm1.
	_TEST32( "f30f7e00 movq xmm0,qword ptr [eax]", 0xF3, 0x0F, 0x7E, 0x00 );
	_TEST64( "f30f7e00 movq xmm0,qword ptr [rax]", 0xF3, 0x0F, 0x7E, 0x00 );
	_TEST64( "f30f7ed0 movq xmm2,xmm0",  0xF3, 0x0F, 0x7E, 0xD0 );
	_TEST64( "f3480f7e00 movq xmm0,qword ptr [rax]", 0xF3, 0x48, 0x0F, 0x7E, 0x00 );
	// 66 0F D6 MOVQ xmm2/m64, xmm1 B Valid Valid Move quadword from xmm1 to xmm2/mem64.
	_TEST32( "660fd600 movq qword ptr [eax],xmm0", 0x66, 0x0F, 0xD6, 0x00 );
	_TEST64( "660fd600 movq qword ptr [rax],xmm0", 0x66, 0x0F, 0xD6, 0x00 );
	_TEST64( "660fd6d0 movq xmm0,xmm2",  0x66, 0x0F, 0xD6, 0xD0 );
	_TEST64( "66480fd600 movq qword ptr [rax],xmm0", 0x66, 0x48, 0x0F, 0xD6, 0x00 );

	// MOVNTQ
	// 0F E7 /r MOVNTQ m64,mm
	_TEST32( "0fe700 movntq qword ptr [eax],mm0", 0x0F, 0xE7, 0x00 );
	_TEST64( "0fe700 movntq qword ptr [rax],mm0",  0x0F, 0xE7, 0x00 );
	_TEST64( "480fe700 movntq qword ptr [rax],mm0", 0x48, 0x0F, 0xE7, 0x00 );

	// MOVNTPS
	// 0F 2B /r MOVNTPS m128,xmm
	_TEST32( "0f2b00 movntps oword ptr [eax],xmm0", 0x0F, 0x2B, 0x00 );
	_TEST64( "0f2b00 movntps oword ptr [rax],xmm0", 0x0F, 0x2B, 0x00 );
	_TEST64( "480f2b00 movntps oword ptr [rax],xmm0", 0x48, 0x0F, 0x2B, 0x00 );

	// MOVNTPD
	// 66 0F 2B /r MOVNTPD m128,xmm
	_TEST32( "660f2b00 movntpd oword ptr [eax],xmm0", 0x66, 0x0F, 0x2B, 0x00 );
	_TEST64( "660f2b00 movntpd oword ptr [rax],xmm0", 0x66, 0x0F, 0x2B, 0x00 );
	_TEST64( "66480f2b00 movntpd oword ptr [rax],xmm0", 0x66, 0x48, 0x0F, 0x2B, 0x00 );

	// MOVNTI
	// 0F C3 /r MOVNTI m32, r32
	// REX.W + 0F C3 /r MOVNTI m64, r64
	_TEST32( "0fc300 movnti dword ptr [eax],eax", 0x0F, 0xC3, 0x00 );
	_TEST32( "660fc300 movnti dword ptr [eax],eax", 0x66, 0x0F, 0xC3, 0x00 );
	_TEST64( "0fc300 movnti dword ptr [rax],eax", 0x0F, 0xC3, 0x00 );
	_TEST64( "480fc300 movnti qword ptr [rax],rax", 0x48, 0x0F, 0xC3, 0x00 );

	// MOVNTDQ
	// 66 0F E7 /r MOVNTDQ m128,xmm
	_TEST32( "660fe700 movntdq oword ptr [eax],xmm0", 0x66, 0x0F, 0xE7, 0x00 );
	_TEST64( "660fe700 movntdq oword ptr [rax],xmm0", 0x66, 0x0F, 0xE7, 0x00 );
	_TEST64( "66480fe700 movntdq oword ptr [rax],xmm0", 0x66, 0x48, 0x0F, 0xE7, 0x00 );

	// MOVNTDQA
	// 66 0F 38 2A /r MOVNTDQA xmm1, m128
	_TEST32( "660f382a00 movntdqa xmm0,oword ptr [eax]", 0x66, 0x0F, 0x38, 0x2A, 0x00 );
	_TEST64( "660f382a00 movntdqa xmm0,oword ptr [rax]", 0x66, 0x0F, 0x38, 0x2A, 0x00 );
	_TEST64( "66480f382a00 movntdqa xmm0,oword ptr [rax]", 0x66, 0x48, 0x0F, 0x38, 0x2A, 0x00 );

	// MOVMSKPS
	// 0F 50 /r MOVMSKPS reg,xmm
	_TEST32( "0f50d0 movmskps edx,xmm0", 0x0F, 0x50, 0xD0 );
	_TEST32( "0f50d8 movmskps ebx,xmm0", 0x0F, 0x50, 0xD8 );
	_TEST64( "0f50d0 movmskps rdx,xmm0", 0x0F, 0x50, 0xD0 );
	_TEST64( "480f50d0 movmskps rdx,xmm0", 0x48, 0x0F, 0x50, 0xD0 );

	// MOVMSKPD
	// 66 0F 50 /r MOVMSKPD reg, xmm
	_TEST32( "660f50d0 movmskpd edx,xmm0", 0x66, 0x0F, 0x50, 0xD0 );
	_TEST32( "660f50d8 movmskpd ebx,xmm0", 0x66, 0x0F, 0x50, 0xD8 );
	_TEST64( "660f50d0 movmskpd rdx,xmm0", 0x66, 0x0F, 0x50, 0xD0 );
	_TEST64( "66480f50d0 movmskpd rdx,xmm0", 0x66, 0x48, 0x0F, 0x50, 0xD0 );

	// MOVLPS
	// 0F 12 /r MOVLPS xmm, m64
	_TEST32( "0f1200 movlps xmm0,qword ptr [eax]", 0x0F, 0x12, 0x00 );
	_TEST64( "0f1200 movlps xmm0,qword ptr [rax]", 0x0F, 0x12, 0x00 );
	_TEST64( "480f1200 movlps xmm0,qword ptr [rax]", 0x48, 0x0F, 0x12, 0x00 );
	// 0F 13 /r MOVLPS m64, xmm
	_TEST32( "0f1300 movlps qword ptr [eax],xmm0", 0x0F, 0x13, 0x00 );
	_TEST64( "0f1300 movlps qword ptr [rax],xmm0",  0x0F, 0x13, 0x00 );
	_TEST64( "480f1300 movlps qword ptr [rax],xmm0", 0x48, 0x0F, 0x13, 0x00 );

	// MOVLPD
	// 66 0F 12 /r MOVLPD xmm, m64
	_TEST32( "660f1200 movlpd xmm0,qword ptr [eax]", 0x66, 0x0F, 0x12, 0x00 );
	_TEST64( "660f1200 movlpd xmm0,qword ptr [rax]", 0x66, 0x0F, 0x12, 0x00 );
	_TEST64( "66480f1200 movlpd xmm0,qword ptr [rax]", 0x66, 0x48, 0x0F, 0x12, 0x00 );
	// 66 0F 13 /r MOVLPD m64,xmm
	_TEST32( "660f1300 movlpd qword ptr [eax],xmm0", 0x66, 0x0F, 0x13, 0x00 );
	_TEST64( "660f1300 movlpd qword ptr [rax],xmm0", 0x66, 0x0F, 0x13, 0x00 );
	_TEST64( "66480f1300 movlpd qword ptr [rax],xmm0", 0x66, 0x48, 0x0F, 0x13, 0x00 );

	// 0F 16 /r MOVLHPS xmm1, xmm2 A Valid Valid Move two packed singleprecision floating-point values from low quadword of xmm2 to high quadword of xmm1.
	_TEST32( "0f16d0 movlhps xmm2,xmm0", 0x0F, 0x16, 0xD0 );
	_TEST32( "0f16d8 movlhps xmm3,xmm0", 0x0F, 0x16, 0xD8 );
	_TEST64( "0f16d0 movlhps xmm2,xmm0", 0x0F, 0x16, 0xD0 );
	_TEST64( "480f16d0 movlhps xmm2,xmm0", 0x48, 0x0F, 0x16, 0xD0 );

	// MOVHPS
	// 0F 16 /r MOVHPS xmm, m64 A Valid Valid Move two packed singleprecision floating-point values from m64 to high quadword of xmm.
	_TEST32( "0f1608 movhps xmm1,qword ptr [eax]", 0x0F, 0x16, 0x08 );
	_TEST64( "0f1608 movhps xmm1,qword ptr [rax]", 0x0F, 0x16, 0x08 );
	_TEST64( "480f1600 movhps xmm0,qword ptr [rax]", 0x48, 0x0F, 0x16, 0x00 );
	// 0F 17 /r MOVHPS m64, xmm B Valid Valid Move two packed singleprecision floating-point values from high quadword of xmm to m64.
	_TEST32( "0f1708 movhps qword ptr [eax],xmm1", 0x0F, 0x17, 0x08 );
	_TEST64( "0f1708 movhps qword ptr [rax],xmm1", 0x0F, 0x17, 0x08 );
	_TEST64( "480f1700 movhps qword ptr [rax],xmm0", 0x48, 0x0F, 0x17, 0x00 );

	// MOVHPD
	// 66 0F 16 /r MOVHPD xmm, m64 A Valid Valid Move double-precision floating-point value from m64 to high quadword of xmm.
	_TEST32( "660f1608 movhpd xmm1,qword ptr [eax]", 0x66, 0x0F, 0x16, 0x08 );
	_TEST64( "660f1608 movhpd xmm1,qword ptr [rax]", 0x66, 0x0F, 0x16, 0x08 );
	_TEST64( "66480f1600 movhpd xmm0,qword ptr [rax]", 0x66, 0x48, 0x0F, 0x16, 0x00 );
	// 66 0F 17 /r MOVHPD m64, xmm B Valid Valid Move double-precision floating-point value from high quadword of xmm to m64.
	_TEST32( "660f1708 movhpd qword ptr [eax],xmm1", 0x66, 0x0F, 0x17, 0x08 );
	_TEST64( "660f1708 movhpd qword ptr [rax],xmm1", 0x66, 0x0F, 0x17, 0x08 );
	_TEST64( "66480f1700 movhpd qword ptr [rax],xmm0", 0x66, 0x48, 0x0F, 0x17, 0x00 );

	// MOVHLPS
	// 0F 12 /r MOVHLPS xmm1, xmm2 A Valid Valid Move two packed singleprecision floating-point values from high quadword of xmm2 to low quadword of xmm1.
	_TEST32( "0f12d0 movhlps xmm2,xmm0", 0x0F, 0x12, 0xD0 );
	_TEST32( "0f12d8 movhlps xmm3,xmm0", 0x0F, 0x12, 0xD8 );
	_TEST64( "0f12d0 movhlps xmm2,xmm0", 0x0F, 0x12, 0xD0 );
	_TEST64( "480f12d0 movhlps xmm2,xmm0", 0x48, 0x0F, 0x12, 0xD0 );

	// MOVDQ2Q
	// F2 0F D6 MOVDQ2Q mm, xmm A Valid Valid Move low quadword from xmm to mmx register.
	_TEST32( "f20fd6d0 movdq2q mm2,xmm0", 0xF2, 0x0F, 0xD6, 0xD0 );
	_TEST32( "f20fd6d8 movdq2q mm3,xmm0", 0xF2, 0x0F, 0xD6, 0xD8 );
	_TEST64( "f20fd6d0 movdq2q mm2,xmm0", 0xF2, 0x0F, 0xD6, 0xD0 );
	_TEST64( "f2480fd6d0 movdq2q mm2,xmm0", 0xF2, 0x48, 0x0F, 0xD6, 0xD0 );

	// MOVDQU
	// F3 0F 6F /r MOVDQU xmm1, xmm2/m128 A Valid Valid Move unaligned double quadword from xmm2/m128 to xmm1.
	_TEST32( "f30f6f10 movdqu xmm2,oword ptr [eax]", 0xF3, 0x0F, 0x6F, 0x10 );
	_TEST32( "f30f6fd8 movdqu xmm3,xmm0", 0xF3, 0x0F, 0x6F, 0xD8 );
	_TEST64( "f30f6f10 movdqu xmm2,oword ptr [rax]", 0xF3, 0x0F, 0x6F, 0x10 );
	// F3 0F 7F /r MOVDQU xmm2/m128, xmm1 B Valid Valid Move unaligned double quadword from xmm1 to xmm2/m128.
	_TEST32( "f30f7f10 movdqu oword ptr [eax],xmm2", 0xF3, 0x0F, 0x7F, 0x10 );
	_TEST32( "f30f7fd8 movdqu xmm0,xmm3", 0xF3, 0x0F, 0x7F, 0xD8 );
	_TEST64( "f30f7f10 movdqu oword ptr [rax],xmm2", 0xF3, 0x0F, 0x7F, 0x10 );

	// MOVDQA
	// 66 0F 6F /r MOVDQA xmm1, xmm2/m128 A Valid Valid Move aligned double quadword from xmm2/m128 to xmm1.
	_TEST32( "660f6f10 movdqa xmm2,oword ptr [eax]", 0x66, 0x0F, 0x6F, 0x10 );
	_TEST32( "660f6fd8 movdqa xmm3,xmm0", 0x66, 0x0F, 0x6F, 0xD8 );
	_TEST64( "660f6f10 movdqa xmm2,oword ptr [rax]", 0x66, 0x0F, 0x6F, 0x10 );
	// 66 0F 7F /r MOVDQA xmm2/m128, xmm1 B Valid Valid Move aligned double quadword from xmm1 to xmm2/m128.
	_TEST32( "660f7f10 movdqa oword ptr [eax],xmm2", 0x66, 0x0F, 0x7F, 0x10 );
	_TEST32( "660f7fd8 movdqa xmm0,xmm3", 0x66, 0x0F, 0x7F, 0xD8 );
	_TEST64( "660f7f10 movdqa oword ptr [rax],xmm2", 0x66, 0x0F, 0x7F, 0x10 );

	// MOVDDUP
	// F2 0F 12 /r MOVDDUP xmm1, xmm2/m64 A Valid Valid Move one double-precision floating-point value from the lower 64-bit operand in xmm2/m64 to xmm1 and duplicate.
	_TEST32( "f20f1210 movddup xmm2,qword ptr [eax]", 0xF2, 0x0F, 0x12, 0x10 );
	_TEST32( "f20f12d8 movddup xmm3,xmm0", 0xF2, 0x0F, 0x12, 0xD8 );
	_TEST64( "f20f1210 movddup xmm2,qword ptr [rax]", 0xF2, 0x0F, 0x12, 0x10 );

	// MOVD
	// 0F 6E /r MOVD mm,r/m32 A Valid Valid Move doubleword from r/m32 to mm.
	_TEST32( "0f6e10 movd mm2,dword ptr [eax]", 0x0F, 0x6E, 0x10 );
	_TEST64( "0f6e10 movd mm2,dword ptr [rax]", 0x0F, 0x6E, 0x10 );
	// REX.W + 0F 6E /r MOVQ mm, r/m64 A Valid N.E. Move quadword from r/m64 to mm.
	_TEST64( "480f6e10 movq mm2,qword ptr [rax]", 0x48, 0x0F, 0x6E, 0x10 );
	// 0F 7E /r MOVD r/m32, mm B Valid Valid Move doubleword from mm to r/m32.
	_TEST32( "0f7e10 movd dword ptr [eax],mm2", 0x0F, 0x7E, 0x10 );
	_TEST64( "0f7e10 movd dword ptr [rax],mm2", 0x0F, 0x7E, 0x10 );
	// REX.W + 0F 7E /r MOVQ r/m64, mm B Valid N.E. Move quadword from mm to r/m64.
	_TEST64( "480f7e10 movq qword ptr [rax],mm2", 0x48, 0x0F, 0x7E, 0x10 );
	// 66 0F 6E /r MOVD xmm, r/m32 A Valid Valid Move doubleword from r/m32 to xmm.
	_TEST32( "660f6e10 movd xmm2,dword ptr [eax]", 0x66, 0x0F, 0x6E, 0x10 );
	_TEST64( "660f6e10 movd xmm2,dword ptr [rax]", 0x66, 0x0F, 0x6E, 0x10 );
	// 66 REX.W 0F 6E /r MOVQ xmm, r/m64 A Valid N.E. Move quadword from r/m64 to xmm.
	_TEST64( "66480f6e10 movq xmm2,qword ptr [rax]", 0x66, 0x48, 0x0F, 0x6E, 0x10 );
	// 66 0F 7E /r MOVD r/m32, xmm B Valid Valid Move doubleword from xmm register to r/m32.
	_TEST32( "660f7e10 movd dword ptr [eax],xmm2", 0x66, 0x0F, 0x7E, 0x10 );
	_TEST64( "660f7e10 movd dword ptr [rax],xmm2", 0x66, 0x0F, 0x7E, 0x10 );
	// 66 REX.W 0F 7E /r MOVQ r/m64, xmm B Valid N.E. Move quadword from xmm register to r/m64.
	_TEST64( "66480f7e10 movq qword ptr [rax],xmm2", 0x66, 0x48, 0x0F, 0x7E, 0x10 );

	// MOV (DR)
	// 0F 21/r MOV r32, DR0–DR7 A N.E. Valid Move debug register to r32
	_TEST32( "0f21d0 mov eax,dr2", 0x0F, 0x21, 0xD0 );
	_TEST32( "660f21d0 mov eax,dr2", 0x66, 0x0F, 0x21, 0xD0 );
	// 0F 21/r MOV r64, DR0–DR7 A Valid N.E. Move extended debug register to r64.
	_TEST64( "660f21d0 mov rax,dr2", 0x66, 0x0F, 0x21, 0xD0 );
	_TEST64( "480f21d0 mov rax,dr2", 0x48, 0x0F, 0x21, 0xD0 );
	_TEST64( "0f21d0 mov rax,dr2", 0x0F, 0x21, 0xD0 );
	// 0F 23 /r MOV DR0–DR7, r32 A N.E. Valid Move r32 to debug register
	_TEST32( "0f23d0 mov dr2,eax", 0x0F, 0x23, 0xD0 );
	_TEST32( "660f23d0 mov dr2,eax", 0x66, 0x0F, 0x23, 0xD0 );
	// 0F 23 /r MOV DR0–DR7, r64 A Valid N.E. Move r64 to extended debug register.
	_TEST64( "660f23d0 mov dr2,rax", 0x66, 0x0F, 0x23, 0xD0 );
	_TEST64( "480f23d0 mov dr2,rax", 0x48, 0x0F, 0x23, 0xD0 );
	_TEST64( "0f23d0 mov dr2,rax", 0x0F, 0x23, 0xD0 );

	_TEST32( "0f21c0 mov eax,dr0", 0x0F, 0x21, 0xC0 );
	_TEST32( "0f21c8 mov eax,dr1", 0x0F, 0x21, 0xC8 );
	_TEST32( "0f21d0 mov eax,dr2", 0x0F, 0x21, 0xD0 );
	_TEST32( "0f21d8 mov eax,dr3", 0x0F, 0x21, 0xD8 );
	_TEST32( "0f21e0 mov eax,dr4", 0x0F, 0x21, 0xE0 );
	_TEST32( "0f21e8 mov eax,dr5", 0x0F, 0x21, 0xE8 );
	_TEST32( "0f21f0 mov eax,dr6", 0x0F, 0x21, 0xF0 );
	_TEST32( "0f21f8 mov eax,dr7", 0x0F, 0x21, 0xF8 );
	_TEST64( "440f21c0 mov rax,<unknown DR>", 0x44, 0x0F, 0x21, 0xC0 );
	_TEST64( "440f21c8 mov rax,<unknown DR>", 0x44, 0x0F, 0x21, 0xC8 );
	_TEST64( "440f21d0 mov rax,<unknown DR>", 0x44, 0x0F, 0x21, 0xD0 );
	_TEST64( "440f21d8 mov rax,<unknown DR>", 0x44, 0x0F, 0x21, 0xD8 );
	_TEST64( "440f21e0 mov rax,<unknown DR>", 0x44, 0x0F, 0x21, 0xE0 );
	_TEST64( "440f21e8 mov rax,<unknown DR>", 0x44, 0x0F, 0x21, 0xE8 );
	_TEST64( "440f21f0 mov rax,<unknown DR>", 0x44, 0x0F, 0x21, 0xF0 );
	_TEST64( "440f21f8 mov rax,<unknown DR>", 0x44, 0x0F, 0x21, 0xF8 );

	// MOV (CR)
	// 0F 20/r MOV r32, CR0–CR7 A N.E. Valid Move control register to r32
	// 0F 20/r MOV r64, CR0–CR7 A Valid N.E. Move extended control register to r64.
	_TEST32( "0f20d0 mov eax,cr2", 0x0F, 0x20, 0xD0 );
	_TEST32( "660f20d0 mov eax,cr2", 0x66, 0x0F, 0x20, 0xD0 );
	// REX.R + 0F 20 /0 MOV r64, CR8 A Valid N.E. Move extended CR8 to r64.1
	_TEST64( "660f20d0 mov rax,cr2", 0x66, 0x0F, 0x20, 0xD0 );
	_TEST64( "480f20d0 mov rax,cr2", 0x48, 0x0F, 0x20, 0xD0 );
	_TEST64( "0f20d0 mov rax,cr2", 0x0F, 0x20, 0xD0 );
	// 0F 22 /r MOV CR0–CR7, r32 A N.E. Valid Move r32 to control register
	// 0F 22 /r MOV CR0–CR7, r64 A Valid N.E. Move r64 to extended control register.
	_TEST32( "0f22d0 mov cr2,eax", 0x0F, 0x22, 0xD0 );
	_TEST32( "660f22d0 mov cr2,eax", 0x66, 0x0F, 0x22, 0xD0 );
	// REX.R + 0F 22 /0 MOV CR8, r64 A Valid N.E. Move r64 to extended CR8.1
	_TEST64( "660f22d0 mov cr2,rax", 0x66, 0x0F, 0x22, 0xD0 );
	_TEST64( "480f22d0 mov cr2,rax", 0x48, 0x0F, 0x22, 0xD0 );
	_TEST64( "0f22d0 mov cr2,rax", 0x0F, 0x22, 0xD0 );

	// TODO: Zastanowic sie na koncu czyc chemy pokazywac unknown czy takze nieistiejace numerowac.
	_TEST32( "0f20c0 mov eax,cr0", 0x0F, 0x20, 0xC0 );
	_TEST32( "0f20c8 mov eax,<unknown CR>", 0x0F, 0x20, 0xC8 );
	_TEST32( "0f20d0 mov eax,cr2", 0x0F, 0x20, 0xD0 );
	_TEST32( "0f20d8 mov eax,cr3", 0x0F, 0x20, 0xD8 );
	_TEST32( "0f20e0 mov eax,cr4", 0x0F, 0x20, 0xE0 );
	_TEST32( "0f20e8 mov eax,<unknown CR>", 0x0F, 0x20, 0xE8 );
	_TEST32( "0f20f0 mov eax,<unknown CR>", 0x0F, 0x20, 0xF0 );
	_TEST32( "0f20f8 mov eax,<unknown CR>", 0x0F, 0x20, 0xF8 );
	_TEST64( "440f20c0 mov rax,cr8", 0x44, 0x0F, 0x20, 0xC0 );
	_TEST64( "440f20c8 mov rax,<unknown CR>", 0x44, 0x0F, 0x20, 0xC8 );
	_TEST64( "440f20d0 mov rax,<unknown CR>", 0x44, 0x0F, 0x20, 0xD0 );
	_TEST64( "440f20d8 mov rax,<unknown CR>", 0x44, 0x0F, 0x20, 0xD8 );
	_TEST64( "440f20e0 mov rax,<unknown CR>", 0x44, 0x0F, 0x20, 0xE0 );
	_TEST64( "440f20e8 mov rax,<unknown CR>", 0x44, 0x0F, 0x20, 0xE8 );
	_TEST64( "440f20f0 mov rax,<unknown CR>", 0x44, 0x0F, 0x20, 0xF0 );
	_TEST64( "440f20f8 mov rax,<unknown CR>", 0x44, 0x0F, 0x20, 0xF8 );

	// MOV
	// 88 /r MOV r/m8,r8 A Valid Valid Move r8 to r/m8.
	// REX + 88 /r MOV r/m8***,r8*** A Valid N.E. Move r8 to r/m8.
	_TEST64( "488810 mov byte ptr [rax],dl", 0x48, 0x88, 0x10 );
	_TEST32( "8810 mov byte ptr [eax],dl", 0x88, 0x10 );
	// 89 /r MOV r/m16,r16 A Valid Valid Move r16 to r/m16.
	// 89 /r MOV r/m32,r32 A Valid Valid Move r32 to r/m32.
	// REX.W + 89 /r MOV r/m64,r64 A Valid N.E. Move r64 to r/m64.
	_TEST64( "488910 mov qword ptr [rax],rdx", 0x48, 0x89, 0x10 );
	_TEST32( "8910 mov dword ptr [eax],edx", 0x89, 0x10 );
	_TEST32( "668910 mov word ptr [eax],dx", 0x66, 0x89, 0x10 );
	// 8A /r MOV r8,r/m8 B Valid Valid Move r/m8 to r8.
	// REX + 8A /r MOV r8***,r/m8*** B Valid N.E. Move r/m8 to r8.
	_TEST64( "488a10 mov dl,byte ptr [rax]", 0x48, 0x8A, 0x10 );
	_TEST32( "8a10 mov dl,byte ptr [eax]", 0x8A, 0x10 );
	// 8B /r MOV r16,r/m16 B Valid Valid Move r/m16 to r16.
	// 8B /r MOV r32,r/m32 B Valid Valid Move r/m32 to r32.
	// REX.W + 8B /r MOV r64,r/m64 B Valid N.E. Move r/m64 to r64.
	_TEST64( "488b10 mov rdx,qword ptr [rax]", 0x48, 0x8B, 0x10 );
	_TEST32( "8b10 mov edx,dword ptr [eax]", 0x8B, 0x10 );
	_TEST32( "668b10 mov dx,word ptr [eax]", 0x66, 0x8B, 0x10 );
	// 8C /r MOV r/m16,Sreg** A Valid Valid Move segment register to r/m16.
	_TEST32( "8c10 mov word ptr [eax],ss", 0x8C, 0x10 );
	_TEST32( "668c10 mov word ptr [eax],ss", 0x66, 0x8C, 0x10 );
	_TEST64( "8c10 mov word ptr [rax],ss", 0x8C, 0x10 );
	// REX.W + 8C /r MOV r/m64,Sreg** A Valid Valid Move zero extended 16-bit segment register to r/m64.
	_TEST64( "488c10 mov qword ptr [rax],ss", 0x48, 0x8C, 0x10 );
	// A0 MOV AL,moffs8* C Valid Valid Move byte at (seg:offset) to AL.
	// REX.W + A0 MOV AL,moffs8* C Valid N.E. Move byte at (offset) to AL.
	_TEST32( "a010203040 mov al,byte ptr [40302010h]", 0xA0, 0x10, 0x20, 0x30, 0x40 );
	_TEST32( "67a01020 mov al,byte ptr [2010h]", 0x67, 0xA0, 0x10, 0x20 );
	_TEST64( "a01020304050515253 mov al,byte ptr [5352515040302010h]", 0xA0, 0x10, 0x20, 0x30, 0x40, 0x50, 0x51, 0x52, 0x53 );
	_TEST64( "67a010203040 mov al,byte ptr [40302010h]", 0x67, 0xA0, 0x10, 0x20, 0x30, 0x40 );
	// A1 MOV AX,moffs16* C Valid Valid Move word at (seg:offset) to AX.
	// A1 MOV EAX,moffs32* C Valid Valid Move doubleword at (seg:offset) to EAX.
	// REX.W + A1 MOV RAX,moffs64* C Valid N.E. Move quadword at (offset) to RAX.
	_TEST32( "a110203040 mov eax,dword ptr [40302010h]", 0xA1, 0x10, 0x20, 0x30, 0x40 );
	_TEST32( "6667a11020 mov ax,word ptr [2010h]", 0x66, 0x67, 0xA1, 0x10, 0x20 );
	_TEST32( "66a110203040 mov ax,word ptr [40302010h]", 0x66, 0xA1, 0x10, 0x20, 0x30, 0x040 );
	_TEST64( "a11020304050515253 mov eax,dword ptr [5352515040302010h]", 0xA1, 0x10, 0x20, 0x30, 0x40, 0x50, 0x51, 0x52, 0x53 );
	_TEST64( "66a11020304050515253 mov ax,word ptr [5352515040302010h]", 0x66, 0xA1, 0x10, 0x20, 0x30, 0x40, 0x50, 0x51, 0x52, 0x53 );
	_TEST64( "48a11020304050515253 mov rax,qword ptr [5352515040302010h]", 0x48, 0xA1, 0x10, 0x20, 0x30, 0x40, 0x50, 0x51, 0x52, 0x53 );
	_TEST64( "6667a110203040 mov ax,word ptr [40302010h]", 0x66, 0x67, 0xA1, 0x10, 0x20, 0x30, 0x40 );
	// A2 MOV moffs8,AL D Valid Valid Move AL to (seg:offset).
	// REX.W + A2 MOV moffs8***,AL D Valid N.E. Move AL to (offset).
	_TEST32( "a210203040 mov byte ptr [40302010h],al", 0xA2, 0x10, 0x20, 0x30, 0x40 );
	_TEST32( "67a21020 mov byte ptr [2010h],al", 0x67, 0xA2, 0x10, 0x20 );
	_TEST64( "a21020304050515253 mov byte ptr [5352515040302010h],al", 0xA2, 0x10, 0x20, 0x30, 0x40, 0x50, 0x51, 0x52, 0x53 );
	_TEST64( "67a210203040 mov byte ptr [40302010h],al", 0x67, 0xA2, 0x10, 0x20, 0x30, 0x40 );
	// A3 MOV moffs16*,AX D Valid Valid Move AX to (seg:offset).
	// A3 MOV moffs32*,EAX D Valid Valid Move EAX to (seg:offset).
	// REX.W + A3 MOV moffs64*,RAX D Valid N.E. Move RAX to (offset).
	_TEST32( "a310203040 mov dword ptr [40302010h],eax", 0xA3, 0x10, 0x20, 0x30, 0x40 );
	_TEST32( "6667a31020 mov word ptr [2010h],ax", 0x66, 0x67, 0xA3, 0x10, 0x20 );
	_TEST32( "66a310203040 mov word ptr [40302010h],ax", 0x66, 0xA3, 0x10, 0x20, 0x30, 0x040 );
	_TEST64( "a31020304050515253 mov dword ptr [5352515040302010h],eax", 0xA3, 0x10, 0x20, 0x30, 0x40, 0x50, 0x51, 0x52, 0x53 );
	_TEST64( "66a31020304050515253 mov word ptr [5352515040302010h],ax", 0x66, 0xA3, 0x10, 0x20, 0x30, 0x40, 0x50, 0x51, 0x52, 0x53 );
	_TEST64( "48a31020304050515253 mov qword ptr [5352515040302010h],rax", 0x48, 0xA3, 0x10, 0x20, 0x30, 0x40, 0x50, 0x51, 0x52, 0x53 );
	_TEST64( "6667a310203040 mov word ptr [40302010h],ax", 0x66, 0x67, 0xA3, 0x10, 0x20, 0x30, 0x40 );
	// B0+ rb MOV r8, imm8 E Valid Valid Move imm8 to r8.
	// REX + B0+ rb MOV r8***, imm8 E Valid N.E. Move imm8 to r8.
	_TEST32( "b0d0 mov al,0d0h", 0xB0, 0xD0  );
	_TEST32( "b1d0 mov cl,0d0h", 0xB1, 0xD0  );
	_TEST32( "66b0d0 mov al,0d0h", 0x66, 0xB0, 0xD0 );
	_TEST64( "b0d0 mov al,0d0h", 0xB0, 0xD0 );
	// B8+ rw MOV r16, imm16 E Valid Valid Move imm16 to r16.
	// B8+ rd MOV r32, imm32 E Valid Valid Move imm32 to r32.
	// REX.W + B8+ rd MOV r64, imm64 E Valid N.E. Move imm64 to r64.
	_TEST32( "b8d0d0d0d1 mov eax,0d1d0d0d0h", 0xB8, 0xD0, 0xD0, 0xD0, 0xD1  );
	_TEST32( "b9d0d0d0d1 mov ecx,0d1d0d0d0h", 0xB9, 0xD0, 0xD0, 0xD0, 0xD1  );
	_TEST32( "66b8d0d1 mov ax,0d1d0h", 0x66, 0xB8, 0xD0, 0xD1 );
	_TEST64( "48b8d0d0d0d1d0d0d0d1 mov rax,0d1d0d0d0d1d0d0d0h", 0x48, 0xB8, 0xD0, 0xD0, 0xD0, 0xD1, 0xD0, 0xD0, 0xD0, 0xD1);
	_TEST64( "66b8d0d0 mov ax,0d0d0h", 0x66, 0xB8, 0xD0, 0xD0, 0xD0, 0xD1 );
	// C6 /0 MOV r/m8, imm8 F Valid Valid Move imm8 to r/m8.
	// REX + C6 /0 MOV r/m8***, imm8 F Valid N.E. Move imm8 to r/m8.
	_TEST32( "c6401020 mov byte ptr [eax+00000010h],20h", 0xC6, 0x40, 0x10, 0x20 );
	_TEST32( "66c6401020 mov byte ptr [eax+00000010h],20h", 0x66, 0xC6, 0x40, 0x10, 0x20  );
	_TEST32( "66c6c020 mov al,20h", 0x66, 0xC6, 0xc0, 0x20  );
	_TEST64( "48c6401020 mov byte ptr [rax+0000000000000010h],20h", 0x48, 0xC6, 0x40, 0x10, 0x20);
	// C7 /0 MOV r/m16, imm16 F Valid Valid Move imm16 to r/m16.
	// C7 /0 MOV r/m32, imm32 F Valid Valid Move imm32 to r/m32.
	// REX.W + C7 /0 MOV r/m64, imm32 F Valid N.E. Move imm32 sign extended to 64-bits to r/m64.
	_TEST32( "c7401010203040 mov dword ptr [eax+00000010h],40302010h", 0xC7, 0x40, 0x10, 0x10, 0x20, 0x30, 0x40 );
	_TEST32( "66c740101020 mov word ptr [eax+00000010h],2010h", 0x66, 0xC7, 0x40, 0x10, 0x10, 0x20  );
	_TEST32( "66c7c01020 mov ax,2010h", 0x66, 0xC7, 0xC0,  0x10, 0x20, 0x30, 0x40 );
	_TEST64( "48c7401010203040 mov qword ptr [rax+0000000000000010h],0000000040302010h", 0x48, 0xC7, 0x40, 0x10, 0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70, 0x80 );
	_TEST64( "48c784dd1020304050607080 mov qword ptr [rbp+rbx*8+0000000040302010h],0ffffffff80706050h", 0x48, 0xC7, 0x84, 0xDD, 0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70, 0x80, 0x10, 0x20, 0x30, 0x40, 0x50 );

	// MOVBE
	// 0F 38 F0 /r MOVBE r16, m16 A Valid Valid Reverse byte order in m16 and move to r16
	// 0F 38 F0 /r MOVBE r32, m32 A Valid Valid Reverse byte order in m32 and move to r32
	// REX.W + 0F 38 F0 /r MOVBE r64, m64 A Valid N.E. Reverse byte order in m64 and move to r64.
	_TEST64( "0f38f010 movbe edx,dword ptr [rax]", 0x0F, 0x38, 0xF0, 0x10 );
	_TEST64( "480f38f010 movbe rdx,qword ptr [rax]", 0x48, 0x0F, 0x38, 0xF0, 0x10 );
	_TEST32( "0f38f0c2 movbe eax,edx", 0x0F, 0x38, 0xF0, 0xC2 );
	_TEST32( "660f38f010 movbe dx,word ptr [eax]", 0x66, 0x0F, 0x38, 0xF0, 0x10 );
	// 0F 38 F1 /r MOVBE m16, r16 B Valid Valid Reverse byte order in r16 and move to m16
	// 0F 38 F1 /r MOVBE m32, r32 B Valid Valid Reverse byte order in r32 and move to m32
	// REX.W + 0F 38 F1 /r MOVBE m64, r64 B Valid N.E. Reverse byte order in
	_TEST64( "0f38f110 movbe dword ptr [rax],edx", 0x0F, 0x38, 0xF1, 0x10 );
	_TEST64( "480f38f110 movbe qword ptr [rax],rdx", 0x48, 0x0F, 0x38, 0xF1, 0x10 );
	_TEST32( "0f38f1c2 movbe edx,eax", 0x0F, 0x38, 0xF1, 0xC2 );
	_TEST32( "660f38f110 movbe word ptr [eax],dx", 0x66, 0x0F, 0x38, 0xF1, 0x10 );

	// MOVAPS
	// 66 0F 28 /r MOVAPD xmm1, xmm2/m128 A Valid Valid Move packed doubleprecision floating-point values from xmm2/m128 to xmm1.
	_TEST64( "0f284020 movaps xmm0,oword ptr [rax+0000000000000020h]", 0x0F, 0x28, 0x40, 0x20 );
	_TEST64( "480f284020 movaps xmm0,oword ptr [rax+0000000000000020h]", 0x48, 0x0F, 0x28, 0x40, 0x20 );
	_TEST32( "0f28c2 movaps xmm0,xmm2", 0x0F, 0x28, 0xC2 );
	_TEST32( "0f284020 movaps xmm0,oword ptr [eax+00000020h]", 0x0F, 0x28, 0x40, 0x20 );
	// 66 0F 29 /r MOVAPD xmm2/m128, xmm1 B Valid Valid Move packed doubleprecision floating-point values from xmm1 to xmm2/m128.
	_TEST64( "0f294020 movaps oword ptr [rax+0000000000000020h],xmm0", 0x0F, 0x29, 0x40, 0x20 );
	_TEST64( "480f294020 movaps oword ptr [rax+0000000000000020h],xmm0", 0x48, 0x0F, 0x29, 0x40, 0x20 );
	_TEST32( "0f29c2 movaps xmm2,xmm0", 0x0F, 0x29, 0xC2 );
	_TEST32( "0f294020 movaps oword ptr [eax+00000020h],xmm0", 0x0F, 0x29, 0x40, 0x20 );

	// MOVAPD
	// 66 0F 28 /r MOVAPD xmm1, xmm2/m128 A Valid Valid Move packed doubleprecision floating-point values from xmm2/m128 to xmm1.
	_TEST64( "660f284020 movapd xmm0,oword ptr [rax+0000000000000020h]", 0x66, 0x0F, 0x28, 0x40, 0x20 );
	_TEST64( "66480f284020 movapd xmm0,oword ptr [rax+0000000000000020h]", 0x66, 0x48, 0x0F, 0x28, 0x40, 0x20 );
	_TEST32( "660f28c2 movapd xmm0,xmm2", 0x66, 0x0F, 0x28, 0xC2 );
	_TEST32( "660f284020 movapd xmm0,oword ptr [eax+00000020h]", 0x66, 0x0F, 0x28, 0x40, 0x20 );
	// 66 0F 29 /r MOVAPD xmm2/m128, xmm1 B Valid Valid Move packed doubleprecision floating-point values from xmm1 to xmm2/m128.
	_TEST64( "660f294020 movapd oword ptr [rax+0000000000000020h],xmm0", 0x66, 0x0F, 0x29, 0x40, 0x20 );
	_TEST64( "66480f294020 movapd oword ptr [rax+0000000000000020h],xmm0", 0x66, 0x48, 0x0F, 0x29, 0x40, 0x20 );
	_TEST32( "660f29c2 movapd xmm2,xmm0", 0x66, 0x0F, 0x29, 0xC2 );
	_TEST32( "660f294020 movapd oword ptr [eax+00000020h],xmm0", 0x66, 0x0F, 0x29, 0x40, 0x20 );

	// MONITOR
	_TEST64( "0f01c8 monitor rax,rcx,rdx", 0x0F, 0x01, 0xC8 );
	_TEST32( "0f01c8 monitor eax,ecx,edx", 0x0F, 0x01, 0xC8 );

	// MINSD
	_TEST64( "f30f5d4020 minss xmm0,dword ptr [rax+0000000000000020h]", 0xF3, 0x0F, 0x5D, 0x40, 0x20 );
	_TEST32( "f30f5dc2 minss xmm0,xmm2", 0xF3, 0x0F, 0x5D, 0xC2 );
	_TEST32( "f30f5d4020 minss xmm0,dword ptr [eax+00000020h]", 0xF3, 0x0F, 0x5D, 0x40, 0x20 );

	// MINSD
	_TEST64( "f20f5d4020 minsd xmm0,qword ptr [rax+0000000000000020h]", 0xF2, 0x0F, 0x5D, 0x40, 0x20 );
	_TEST32( "f20f5dc2 minsd xmm0,xmm2", 0xF2, 0x0F, 0x5D, 0xC2 );
	_TEST32( "f20f5d4020 minsd xmm0,qword ptr [eax+00000020h]", 0xF2, 0x0F, 0x5D, 0x40, 0x20 );

	// MINPS
	_TEST64( "0f5d4020 minps xmm0,oword ptr [rax+0000000000000020h]", 0x0F, 0x5D, 0x40, 0x20 );
	_TEST32( "0f5dc2 minps xmm0,xmm2", 0x0F, 0x5D, 0xC2 );
	_TEST32( "0f5d4020 minps xmm0,oword ptr [eax+00000020h]", 0x0F, 0x5D, 0x40, 0x20 );

	// MINPD
	_TEST64( "660f5d4020 minpd xmm0,oword ptr [rax+0000000000000020h]", 0x66, 0x0F, 0x5D, 0x40, 0x20 );
	_TEST32( "660f5dc2 minpd xmm0,xmm2", 0x66, 0x0F, 0x5D, 0xC2 );
	_TEST32( "660f5d4020 minpd xmm0,oword ptr [eax+00000020h]", 0x66, 0x0F, 0x5D, 0x40, 0x20 );

	// MFENCE
	_TEST32( "0faef0 mfence", 0x0F, 0xAE, 0xF0 );
	_TEST64( "0faef0 mfence",0x0F, 0xAE, 0xF0 );

	// MAXSD
	_TEST64( "f30f5f4020 maxss xmm0,dword ptr [rax+0000000000000020h]", 0xF3, 0x0F, 0x5F, 0x40, 0x20 );
	_TEST32( "f30f5fc2 maxss xmm0,xmm2", 0xF3, 0x0F, 0x5F, 0xC2 );
	_TEST32( "f30f5f4020 maxss xmm0,dword ptr [eax+00000020h]", 0xF3, 0x0F, 0x5F, 0x40, 0x20 );

	// MAXSD
	_TEST64( "f20f5f4020 maxsd xmm0,qword ptr [rax+0000000000000020h]", 0xF2, 0x0F, 0x5F, 0x40, 0x20 );
	_TEST32( "f20f5fc2 maxsd xmm0,xmm2", 0xF2, 0x0F, 0x5F, 0xC2 );
	_TEST32( "f20f5f4020 maxsd xmm0,qword ptr [eax+00000020h]", 0xF2, 0x0F, 0x5F, 0x40, 0x20 );

	// MAXPS
	_TEST64( "0f5f4020 maxps xmm0,oword ptr [rax+0000000000000020h]", 0x0F, 0x5F, 0x40, 0x20 );
	_TEST32( "0f5fc2 maxps xmm0,xmm2", 0x0F, 0x5F, 0xC2 );
	_TEST32( "0f5f4020 maxps xmm0,oword ptr [eax+00000020h]", 0x0F, 0x5F, 0x40, 0x20 );

	// MAXPD
	_TEST64( "660f5f4020 maxpd xmm0,oword ptr [rax+0000000000000020h]", 0x66, 0x0F, 0x5F, 0x40, 0x20 );
	_TEST32( "660f5fc2 maxpd xmm0,xmm2", 0x66, 0x0F, 0x5F, 0xC2 );
	_TEST32( "660f5f4020 maxpd xmm0,oword ptr [eax+00000020h]", 0x66, 0x0F, 0x5F, 0x40, 0x20 );

	// MASKMOVDQU
	_TEST64( "0ff7d8 maskmovq mm3,mm0", 0x0F, 0xF7, 0xD8 );
	_TEST32( "0ff7e0 maskmovq mm4,mm0", 0x0F, 0xF7, 0xE0 );
	_TEST32( "FAIL", 0x0F, 0xF7, 0x40, 0x20 );

	// MASKMOVDQU
	_TEST64( "660ff7d8 maskmovdqu xmm3,xmm0", 0x66, 0x0F, 0xF7, 0xD8 );
	_TEST32( "660ff7e0 maskmovdqu xmm4,xmm0", 0x66, 0x0F, 0xF7, 0xE0 );
	_TEST32( "FAIL", 0x66, 0x0F, 0xF7, 0x40, 0x20 );

	// LTR
	_TEST32( "0f005820 ltr word ptr [eax+00000020h]", 0x0F, 0x00, 0x58, 0x20);
	_TEST32( "0f00d8 ltr ax", 0x0F, 0x00, 0xD8);
	_TEST64( "0f005820 ltr word ptr [rax+0000000000000020h]", 0x0F, 0x00, 0x58, 0x20);

	// LSL
	// 0F 03 /r LSL r16, r16/m16 A Valid Valid Load: r16 segment limit, selector r16/m16.
	// 0F 03 /r LSL r32, r32/m16*A Valid Valid Load: r32 segment limit, selector r32/m16.
	_TEST32( "0f036820 lsl ebp,word ptr [eax+00000020h]", 0x0f, 0x03, 0x68, 0x20 );
	_TEST32( "0f03cc lsl ecx,esp", 0x0f, 0x03, 0xcc );
	_TEST32( "660f036820 lsl bp,word ptr [eax+00000020h]", 0x66, 0x0f, 0x03, 0x68, 0x20 );
	_TEST32( "660f03cc lsl cx,sp", 0x66, 0x0f, 0x03, 0xcc );
	_TEST64( "0f036820 lsl ebp,word ptr [rax+0000000000000020h]", 0x0f, 0x03, 0x68, 0x20 );
	_TEST64( "0f03cc lsl ecx,esp", 0x0f, 0x03, 0xcc );
	// REX.W + 0F 03 /r LSL r64, r32/m16*A Valid Valid Load: r64 segment limit, selector r32/m16
	_TEST64( "480f036820 lsl rbp,word ptr [rax+0000000000000020h]", 0x48, 0x0f, 0x03, 0x68, 0x20 );
	_TEST64( "480f03cc lsl rcx,esp", 0x48, 0x0f, 0x03, 0xcc );

	// LOOP
	_TEST32( "e210 loop 00401012h", 0xE2, 0x10);
	_TEST32( "67e210 loop 00401013h", 0x67, 0xE2, 0x10);
	_TEST64( "48e210 loop 0000800000401013h", 0x48, 0xE2, 0x10);

	// LODS
	// TODO: Dodac mozliwosc wyswietlania rejestrow segmentowych. i dodac tu test nadpisywania.
	_TEST32( "26ac lods byte ptr [esi]", 0x26, 0xAC );
	_TEST32( "ac lods byte ptr [esi]", 0xAC );
	_TEST32( "ad lods dword ptr [esi]", 0xAD );
	_TEST32( "6667ad lods word ptr [si]",0x66, 0x67, 0xAD );
	_TEST64( "66ad lods word ptr [rsi]",0x66, 0xAD );
	_TEST64( "48ad lods qword ptr [rsi]", 0x48, 0xAD );

	// TODO: Allow to add LOCK prefix only to instructions for wjich this prefix ais allowed, see LOCK instruction description.
	// LOCK Prefix.
	_TEST32( "f02442 lock and al,42h", 0xF0, 0x24, 0x42 );

	// LMSW
	_TEST32( "0f017020 lmsw word ptr [eax+00000020h]", 0x0F, 0x01, 0x70, 0x20 );
	_TEST32( "660f017020 lmsw word ptr [eax+00000020h]", 0x66, 0x0F, 0x01, 0x70, 0x20 );
	_TEST64( "480f017020 lmsw word ptr [rax+0000000000000020h]", 0x48, 0x0F, 0x01, 0x70, 0x20 );

	// LGDT
	_TEST32( "0f005020 lldt word ptr [eax+00000020h]", 0x0F, 0x00, 0x50, 0x20 );
	_TEST32( "660f005020 lldt word ptr [eax+00000020h]", 0x66, 0x0F, 0x00, 0x50, 0x20 );
	_TEST64( "480f005020 lldt word ptr [rax+0000000000000020h]", 0x48, 0x0F, 0x00, 0x50, 0x20 );

	// LGDT
	_TEST32( "0f015020 lgdt fword ptr [eax+00000020h]", 0x0F, 0x01, 0x50, 0x20 );
	_TEST32( "660f015020 lgdt fword ptr [eax+00000020h]", 0x66, 0x0F, 0x01, 0x50, 0x20 );
	_TEST64( "0f015020 lgdt fword ptr [rax+0000000000000020h]", 0x0F, 0x01, 0x50, 0x20 );
	_TEST64( "660f015020 lgdt fword ptr [rax+0000000000000020h]", 0x66, 0x0F, 0x01, 0x50, 0x20 );
	_TEST64( "480f015020 lgdt tbyte ptr [rax+0000000000000020h]", 0x48, 0x0F, 0x01, 0x50, 0x20 );

	// LFENCE
	_TEST32( "0faee8 lfence", 0x0F, 0xAE, 0xE8 );
	_TEST64( "0faee8 lfence",0x0F, 0xAE, 0xE8 );

	// LEAVE
	_TEST32( "c9 leave", 0xc9 );
	_TEST64( "c9 leave", 0xc9 );

	// LEA
	_TEST32( "8d6820 lea ebp,[eax+00000020h]", 0x8D, 0x68, 0x20 );
	_TEST32( "668d6820 lea bp,[eax+00000020h]", 0x66, 0x8D, 0x68, 0x20 );
	_TEST64( "488d6820 lea rbp,[rax+0000000000000020h]", 0x48, 0x8D, 0x68, 0x20 );

	// LDS
	// C5 /r LDS r16,m16:16 A Invalid Valid Load DS:r16 with far pointer from memory.
	// C5 /r LDS r32,m16:32 A Invalid Valid Load DS:r32 with far pointer from memory.
	_TEST32( "c56820 lds ebp,fword ptr [eax+00000020h]", 0xC5, 0x68, 0x20, 0x40, 0x60 );
	_TEST32( "66c56820 lds bp,dword ptr [eax+00000020h]", 0x66, 0xc5, 0x68, 0x20 );
	// 0F B2 /r LSS r16,m16:16 A Valid Valid Load SS:r16 with far pointer from memory.
	// 0F B2 /r LSS r32,m16:32 A Valid Valid Load SS:r32 with far pointer from memory.
	// REX + 0F B2 /r LSS r64,m16:64 A Valid N.E. Load SS:r64 with far pointer from memory.
	_TEST32( "0fb26820 lss ebp,fword ptr [eax+00000020h]", 0x0F, 0xB2, 0x68, 0x20, 0x40, 0x60 );
	_TEST64( "0fb26820 lss ebp,fword ptr [rax+0000000000000020h]", 0x0F, 0xB2, 0x68, 0x20, 0x40, 0x60 );
	_TEST32( "660fb26820 lss bp,dword ptr [eax+00000020h]", 0x66, 0x0F, 0xB2, 0x68, 0x20 );
	_TEST64( "660fb26820 lss bp,dword ptr [rax+0000000000000020h]", 0x66, 0x0F, 0xB2, 0x68, 0x20 );
	_TEST64( "480fb26820 lss rbp,tbyte ptr [rax+0000000000000020h]", 0x48, 0x0F, 0xB2, 0x68, 0x20 );
	// C4 /r LES r16,m16:16 A Invalid Valid Load ES:r16 with far pointer from memory.
	// C4 /r LES r32,m16:32 A Invalid Valid Load ES:r32 with far pointer from memory.
	_TEST32( "c46820 les ebp,fword ptr [eax+00000020h]", 0xC4, 0x68, 0x20, 0x40, 0x60 );
	_TEST32( "66c46820 les bp,dword ptr [eax+00000020h]", 0x66, 0xc4, 0x68, 0x20 );
	// 0F B4 /r LFS r16,m16:16 A Valid Valid Load FS:r16 with far pointer from memory.
	// 0F B4 /r LFS r32,m16:32 A Valid Valid Load FS:r32 with far pointer from memory.
	// REX + 0F B4 /r LFS r64,m16:64 A Valid N.E. Load FS:r64 with far pointer from memory.
	_TEST32( "0fb46820 lfs ebp,fword ptr [eax+00000020h]", 0x0F, 0xB4, 0x68, 0x20, 0x40, 0x60 );
	_TEST64( "0fb46820 lfs ebp,fword ptr [rax+0000000000000020h]", 0x0F, 0xB4, 0x68, 0x20, 0x40, 0x60 );
	_TEST32( "660fb46820 lfs bp,dword ptr [eax+00000020h]", 0x66, 0x0F, 0xB4, 0x68, 0x20 );
	_TEST64( "660fb46820 lfs bp,dword ptr [rax+0000000000000020h]", 0x66, 0x0F, 0xB4, 0x68, 0x20 );
	_TEST64( "480fb46820 lfs rbp,tbyte ptr [rax+0000000000000020h]", 0x48, 0x0F, 0xB4, 0x68, 0x20 );
	// 0F B5 /r LGS r16,m16:16 A Valid Valid Load GS:r16 with far pointer from memory.
	// 0F B5 /r LGS r32,m16:32 A Valid Valid Load GS:r32 with far pointer from memory.
	// REX + 0F B5 /r LGS r64,m16:64 A Valid N.E. Load GS:r64 with far pointer from memory.
	_TEST32( "0fb56820 lgs ebp,fword ptr [eax+00000020h]", 0x0F, 0xB5, 0x68, 0x20, 0x40, 0x60 );
	_TEST64( "0fb56820 lgs ebp,fword ptr [rax+0000000000000020h]", 0x0F, 0xB5, 0x68, 0x20, 0x40, 0x60 );
	_TEST32( "660fb56820 lgs bp,dword ptr [eax+00000020h]", 0x66, 0x0F, 0xB5, 0x68, 0x20 );
	_TEST64( "660fb56820 lgs bp,dword ptr [rax+0000000000000020h]", 0x66, 0x0F, 0xB5, 0x68, 0x20 );
	_TEST64( "480fb56820 lgs rbp,tbyte ptr [rax+0000000000000020h]", 0x48, 0x0F, 0xB5, 0x68, 0x20 );

	// LAR
	// 0F 02 /r LAR r16, r16/m16 A Valid Valid r16 r16/m16 masked by FF00H.
	// 0F 02 /r LAR r32, r32/m16 A Valid Valid r32 r32/m16 masked by 00FxFF00H
	_TEST32( "0f026820 lar ebp,word ptr [eax+00000020h]", 0x0f, 0x02, 0x68, 0x20 );
	_TEST32( "0f02cc lar ecx,esp", 0x0f, 0x02, 0xcc );
	_TEST32( "660f026820 lar bp,word ptr [eax+00000020h]", 0x66, 0x0f, 0x02, 0x68, 0x20 );
	_TEST32( "660f02cc lar cx,sp", 0x66, 0x0f, 0x02, 0xcc );
	_TEST64( "0f026820 lar ebp,word ptr [rax+0000000000000020h]", 0x0f, 0x02, 0x68, 0x20 );
	_TEST64( "0f02cc lar ecx,esp", 0x0f, 0x02, 0xcc );
	// REX.W + 0F 02 /r LAR r64, r32/m16 A Valid N.E. r64 r32/m16 masked by 00FxFF00H
	_TEST64( "480f026820 lar rbp,word ptr [rax+0000000000000020h]", 0x48, 0x0f, 0x02, 0x68, 0x20 );
	_TEST64( "480f02cc lar rcx,esp", 0x48, 0x0f, 0x02, 0xcc );

	// LDMXCSR
	_TEST32( "0fae5020 ldmxcsr dword ptr [eax+00000020h]", 0x0F, 0xAE, 0x50, 0x20 );
	_TEST64( "0fae5020 ldmxcsr dword ptr [rax+0000000000000020h]", 0x0F, 0xAE, 0x50, 0x20 );

	// LDDQU
	_TEST32( "f20ff06820 lddqu xmm5,[eax+00000020h]", 0xF2, 0x0F, 0xF0, 0x68, 0x20 );
	_TEST64( "f20ff06820 lddqu xmm5,[rax+0000000000000020h]", 0xF2, 0x0F, 0xF0, 0x68, 0x20 );

	// LAHF
	_TEST32( "9f lahf", 0x9F );
	_TEST64( "9f lahf", 0x9F );

	// IRET
	_TEST32( "cf iretd", 0xCF );
	_TEST32( "66cf iret", 0x66, 0xCF );
	_TEST64( "cf iretd", 0xCF );
	_TEST64( "66cf iret", 0x66, 0xCF );
	_TEST64( "48cf iretq", 0x48, 0xCF );

	// INVPCID
	_TEST32( "660f388210 invpcid edx,oword ptr [eax]", 0x66, 0x0F, 0x38, 0x82, 0x10 );
	_TEST64( "660f388210 invpcid rdx,oword ptr [rax]", 0x66, 0x0F, 0x38, 0x82, 0x10 );

	// INVLPG
	_TEST32( "0f017820 invlpg [eax+00000020h]", 0x0F, 0x01, 0x78, 0x20 );
	_TEST64( "0f017820 invlpg [rax+0000000000000020h]", 0x0F, 0x01, 0x78, 0x20 );

	// INVD
	_TEST32( "0f08 invd", 0x0F, 0x08 );
	_TEST64( "0f08 invd", 0x0F, 0x08 );

	// INT
	_TEST32( "cc int 03h", 0xCC );
	_TEST64( "cc int 03h", 0xCC );
	_TEST32( "cd20 int 20h", 0xCD, 0x20 );
	_TEST64( "cd20 int 20h", 0xCD, 0x20 );
	_TEST64( "ce into", 0xCE );
	_TEST32( "ce into", 0xCE );

	// INSERTPS
	_TEST32( "660f3a212040 insertps xmm4,dword ptr [eax],40h", 0x66, 0x0F, 0x3A, 0x21, 0x20, 0x40 );
	_TEST64( "660f3a212040 insertps xmm4,dword ptr [rax],40h", 0x66, 0x0F, 0x3A, 0x21, 0x20, 0x40 );

	// INS
	// 6C INS m8, DX A Valid Valid Input byte from I/O port specified in DX into memory location specified in ES:(E)DI or RDI.*
	_TEST32( "6c ins byte ptr [edi],dx", 0x6c );
	_TEST64( "6c ins byte ptr [rdi],dx", 0x6c );
	_TEST64( "676c ins byte ptr [edi],dx", 0x67, 0x6c );
	// 6D INS m16, DX A Valid Valid Input word from I/O port specified in DX into memory location specified in ES:(E)DI or RDI.1
	// 6D INS m32, DX A Valid Valid Input doubleword from I/O port specified in DX into memory location specified in ES:(E)DI or RDI.1
	_TEST32( "6d ins dword ptr [edi],dx", 0x6D );
	_TEST64( "6d ins dword ptr [rdi],dx", 0x6D );
	_TEST64( "676d ins dword ptr [edi],dx", 0x67, 0x6D );
	_TEST64( "67666d ins word ptr [edi],dx", 0x67, 0x66, 0x6D );
	_TEST64( "486d ins dword ptr [rdi],dx", 0x48, 0x6D );

	// INC
	// FE /0 INC r/m8 A Valid Valid Increment r/m byte by 1.
	// REX + FE /0 INC r/m8* A Valid N.E. Increment r/m byte by 1.
	_TEST32( "40 inc eax", 0x40 );
	_TEST32( "6640 inc ax", 0x66, 0x40 );
	_TEST32( "41 inc ecx", 0x41 );
	_TEST32( "6641 inc cx", 0x66, 0x41 );
	// FF /0 INC r/m16 A Valid Valid Increment r/m word by 1.
	// FF /0 INC r/m32 A Valid Valid Increment r/m doubleword by 1.
	// REX.W + FF /0 INC r/m64 A Valid N.E. Increment r/m quadword by 1.
	_TEST32( "fe00 inc byte ptr [eax]", 0xFE, 0x00 );
	_TEST64( "fe00 inc byte ptr [rax]", 0xFE, 0x00 );
	_TEST64( "48fe00 inc byte ptr [rax]", 0x48, 0xFE, 0x00 );
	_TEST64( "48fec4 inc spl", 0x48, 0xFE, 0xC4 );
	// 40+ rw** INC r16 B N.E. Valid Increment word register by 1.
	// 40+ rd INC r32 B N.E. Valid Increment doubleword register by 1.
	_TEST32( "ff03 inc dword ptr [ebx]", 0xFF, 0x03 );
	_TEST32( "66ff03 inc word ptr [ebx]", 0x66, 0xFF, 0x03 );
	_TEST64( "ff03 inc dword ptr [rbx]", 0xFF, 0x03 );
	_TEST64( "48ff03 inc qword ptr [rbx]", 0x48, 0xFF, 0x03 );
	_TEST64( "6640ff03 inc word ptr [rbx]", 0x66, 0x40, 0xFF, 0x03 );
	_TEST64( "49ffc4 inc r12", 0x49, 0xFF, 0xC4 );

	// IN
	// E4 ib IN AL, imm8 A Valid Valid Input byte from imm8 I/O port address into AL.
	// E5 ib IN AX, imm8 A Valid Valid Input word from imm8 I/O port address into AX.
	// E5 ib IN EAX, imm8 A Valid Valid Input dword from imm8 I/O port address into EAX.
	_TEST32( "e420 in al,20h", 0xE4, 0x20 );
	_TEST64( "66e420 in al,20h", 0x66, 0xE4, 0x20 );
	_TEST32( "e520 in eax,20h", 0xE5, 0x20 );
	_TEST32( "66e520 in ax,20h", 0x66, 0xE5, 0x20 );
	_TEST64( "48e520 in eax,20h", 0x48, 0xE5, 0x20 );
	// EC IN AL,DX B Valid Valid Input byte from I/O port in DX into AL.
	// ED IN AX,DX B Valid Valid Input word from I/O port in DX into AX.
	// ED IN EAX,DX B Valid Valid Input doubleword from I/O port in DX into EAX.
	_TEST32( "ec in al,dx", 0xEC, 0x20 );
	_TEST64( "66ec in al,dx", 0x66, 0xEC, 0x20 );
	_TEST32( "ed in eax,dx", 0xED, 0x20 );
	_TEST32( "66ed in ax,dx", 0x66, 0xED, 0x20 );
	_TEST64( "48ed in eax,dx", 0x48, 0xED, 0x20 );

	// IMUL
	// F6 /5 IMUL r/m8* A Valid Valid AX AL r/m byte.
	_TEST32( "f66820 imul byte ptr [eax+00000020h]", 0xF6, 0x68, 0x20 );
	_TEST32( "66f66820 imul byte ptr [eax+00000020h]", 0x66, 0xF6, 0x68, 0x20 );
	_TEST64( "f66820 imul byte ptr [rax+0000000000000020h]", 0xF6, 0x68, 0x20 );
	// F7 /5 IMUL r/m16 A Valid Valid DX:AX AX r/m word.
	// F7 /5 IMUL r/m32 A Valid Valid EDX:EAX EAX r/m32.
	// REX.W + F7 /5 IMUL r/m64 A Valid N.E. RDX:RAX RAX r/m64.
	_TEST32( "f76820 imul dword ptr [eax+00000020h]", 0xF7, 0x68, 0x20 );
	_TEST32( "66f76820 imul word ptr [eax+00000020h]", 0x66, 0xF7, 0x68, 0x20 );
	_TEST64( "f76820 imul dword ptr [rax+0000000000000020h]", 0xF7, 0x68, 0x20 );
	_TEST64( "66f76820 imul word ptr [rax+0000000000000020h]", 0x66, 0xF7, 0x68, 0x20 );
	_TEST64( "48f76820 imul qword ptr [rax+0000000000000020h]", 0x48, 0xF7, 0x68, 0x20 );
	// 0F AF /r IMUL r16, r/m16 B Valid Valid word register word register r/m16.
	// 0F AF /r IMUL r32, r/m32 B Valid Valid doubleword register doubleword register r/m32.
	// REX.W + 0F AF /r IMUL r64, r/m64 B Valid N.E. Quadword register Quadword register r/m64.
	_TEST32( "0faf6820 imul ebp,dword ptr [eax+00000020h]", 0x0F, 0xAF, 0x68, 0x20 );
	_TEST32( "660faf6820 imul bp,word ptr [eax+00000020h]", 0x66, 0x0F, 0xAF, 0x68, 0x20 );
	_TEST64( "0faf6820 imul ebp,dword ptr [rax+0000000000000020h]", 0x0F, 0xAF, 0x68, 0x20 );
	_TEST64( "660faf6820 imul bp,word ptr [rax+0000000000000020h]", 0x66, 0x0F, 0xAF, 0x68, 0x20 );
	_TEST64( "480faf6820 imul rbp,qword ptr [rax+0000000000000020h]", 0x48, 0x0F, 0xAF, 0x68, 0x20 );
	// 6B /r ib IMUL r16, r/m16, imm8 C Valid Valid word register r/m16 sign-extended immediate byte.
	// 6B /r ib IMUL r32, r/m32, imm8 C Valid Valid doubleword register r/m32 sign-extended immediate byte.
	// REX.W + 6B /r ib IMUL r64, r/m64, imm8 C Valid N.E. Quadword register r/m64 sign-extended immediate byte.
	_TEST32( "6b682040 imul ebp,dword ptr [eax+00000020h],00000040h", 0x6B, 0x68, 0x20, 0x40 );
	_TEST32( "666b682040 imul bp,word ptr [eax+00000020h],0040h", 0x66, 0x6B, 0x68, 0x20, 0x40 );
	_TEST64( "6b682040 imul ebp,dword ptr [rax+0000000000000020h],00000040h", 0x6B, 0x68, 0x20, 0x40 );
	_TEST64( "666b682040 imul bp,word ptr [rax+0000000000000020h],0040h", 0x66, 0x6B, 0x68, 0x20, 0x40 );
	_TEST64( "486b682040 imul rbp,qword ptr [rax+0000000000000020h],0000000000000040h", 0x48, 0x6B, 0x68, 0x20, 0x40 );
	// 69 /r iw IMUL r16, r/m16, imm16 C Valid Valid word register r/m16 immediate word.
	// 69 /r id IMUL r32, r/m32, imm32 C Valid Valid doubleword register r/m32 immediate doubleword.
	// REX.W + 69 /r id IMUL r64, r/m64, imm32 C Valid N.E. Quadword register r/m64 immediate doubleword.
	_TEST32( "69682040506070 imul ebp,dword ptr [eax+00000020h],70605040h", 0x69, 0x68, 0x20, 0x40, 0x50, 0x60, 0x70 );
	_TEST32( "666968204050 imul bp,word ptr [eax+00000020h],5040h", 0x66, 0x69, 0x68, 0x20, 0x40, 0x50 );
	_TEST64( "69682040506070 imul ebp,dword ptr [rax+0000000000000020h],70605040h", 0x69, 0x68, 0x20, 0x40, 0x50, 0x60, 0x70 );
	_TEST64( "666968204050 imul bp,word ptr [rax+0000000000000020h],5040h", 0x66, 0x69, 0x68, 0x20, 0x40, 0x50 );
	_TEST64( "48696820405060ff imul rbp,qword ptr [rax+0000000000000020h],0ffffffffff605040h", 0x48, 0x69, 0x68, 0x20, 0x40, 0x50, 0x60, 0xFF );

	// IDIV
	// F6 /7 IDIV r/m8 A Valid Valid Signed divide AX by r/m8,with result stored in: AL Quotient, AH Remainder.
	// REX + F6 /7 IDIV r/m8* A Valid N.E. Signed divide AX by r/m8, with result stored in AL Quotient, AH Remainder.
	_TEST32( "f63b idiv ax,byte ptr [ebx]", 0xF6, 0x3B );
	_TEST32( "66f63b idiv ax,byte ptr [ebx]", 0x66, 0xF6, 0x3B );
	_TEST64( "48f6fe idiv ax,sil", 0x48, 0xF6, 0xFE );
	_TEST64( "f6fe idiv ax,dh", 0xF6, 0xFE );
	// F7 /7 IDIV r/m16 A Valid Valid Signed divide DX:AX by r/m16, with result stored in AX Quotient, DX Remainder.
	// F7 /7 IDIV r/m32 A Valid Valid Signed divide EDX:EAX by r/m32, with result stored in EAX Quotient, EDX Remainder.
	// REX.W + F7 /7 IDIV r/m64 A Valid N.E. Signed divide RDX:RAX by r/m64, with result stored in RAX Quotient, RDX Remainder.
	_TEST32( "f73b idiv eax,dword ptr [ebx]", 0xF7, 0x3B );
	_TEST32( "66f73b idiv ax,word ptr [ebx]", 0x66, 0xF7, 0x3B );
	_TEST64( "48f7fe idiv rax,rsi", 0x48, 0xF7, 0xFE );
	_TEST64( "f7fe idiv eax,esi", 0xF7, 0xFE );

	// HSUBPS
	_TEST64( "f20f7d4020 hsubps xmm0,oword ptr [rax+0000000000000020h]", 0xF2, 0x0F, 0x7D, 0x40, 0x20 );
	_TEST32( "f20f7d4020 hsubps xmm0,oword ptr [eax+00000020h]", 0xF2, 0x0F, 0x7D, 0x40, 0x20 );

	// HSUBPD
	_TEST64( "660f7d4020 hsubpd xmm0,oword ptr [rax+0000000000000020h]", 0x66, 0x0F, 0x7D, 0x40, 0x20 );
	_TEST32( "660f7d4020 hsubpd xmm0,oword ptr [eax+00000020h]", 0x66, 0x0F, 0x7D, 0x40, 0x20 );

	// HLT
	_TEST64( "f4 hlt", 0xF4 );
	_TEST32( "f4 hlt", 0xF4 );

	// HADDPS
	_TEST64( "f20f7c4020 haddps xmm0,oword ptr [rax+0000000000000020h]", 0xF2, 0x0F, 0x7C, 0x40, 0x20 );
	_TEST32( "f20f7c4020 haddps xmm0,oword ptr [eax+00000020h]", 0xF2, 0x0F, 0x7C, 0x40, 0x20 );

	// HADDPD
	_TEST64( "660f7c4020 haddpd xmm0,oword ptr [rax+0000000000000020h]", 0x66, 0x0F, 0x7C, 0x40, 0x20 );
	_TEST32( "660f7c4020 haddpd xmm0,oword ptr [eax+00000020h]", 0x66, 0x0F, 0x7C, 0x40, 0x20 );

	// FYL2X
	_TEST64( "d9f9 fyl2xp1", 0xD9, 0xF9 );
	_TEST32( "d9f9 fyl2xp1", 0xD9, 0xF9 );

	// FYL2X
	_TEST64( "d9f1 fyl2x", 0xD9, 0xF1 );
	_TEST32( "d9f1 fyl2x", 0xD9, 0xF1 );

	// FXTRACT
	_TEST64( "d9f4 fxtract", 0xD9, 0xF4 );
	_TEST32( "d9f4 fxtract", 0xD9, 0xF4 );

	// FXRSAVE
	_TEST64( "0fae4020 fxsave 512byte ptr [rax+0000000000000020h]", 0x0F, 0xAE, 0x40, 0x20 );
	_TEST32( "0fae4020 fxsave 512byte ptr [eax+00000020h]", 0x0F, 0xAE, 0x40, 0x20 );
	_TEST64( "660fae4020 fxsave 512byte ptr [rax+0000000000000020h]", 0x66, 0x0F, 0xAE, 0x40, 0x20 );
	_TEST32( "660fae4020 fxsave 512byte ptr [eax+00000020h]", 0x66, 0x0F, 0xAE, 0x40, 0x20 );
	_TEST64( "480fae4020 fxsave64 512byte ptr [rax+0000000000000020h]", 0x48, 0x0F, 0xAE, 0x40, 0x20 );

	// FXRSTOR
	_TEST64( "0fae4820 fxrstor 512byte ptr [rax+0000000000000020h]", 0x0F, 0xAE, 0x48, 0x20 );
	_TEST32( "0fae4820 fxrstor 512byte ptr [eax+00000020h]", 0x0F, 0xAE, 0x48, 0x20 );
	_TEST64( "660fae4820 fxrstor 512byte ptr [rax+0000000000000020h]", 0x66, 0x0F, 0xAE, 0x48, 0x20 );
	_TEST32( "660fae4820 fxrstor 512byte ptr [eax+00000020h]", 0x66, 0x0F, 0xAE, 0x48, 0x20 );
	_TEST64( "480fae4820 fxrstor64 512byte ptr [rax+0000000000000020h]", 0x48, 0x0F, 0xAE, 0x48, 0x20 );

	// FXCH
	_TEST64( "d9c9 fxch st(1)", 0xD9, 0xC9 );
	_TEST32( "d9c9 fxch st(1)", 0xD9, 0xC9 );

	// FXAM
	_TEST64( "d9e5 fxam", 0xD9, 0xE5 );
	_TEST32( "d9e5 fxam", 0xD9, 0xE5 );

	// FUCOM/FUCOMP/FUCOMPP
	_TEST64( "dde1 fucom st(1)", 0xDD, 0xE1 );
	_TEST32( "dde1 fucom st(1)", 0xDD, 0xE1 );
	_TEST64( "dde9 fucomp st(1)", 0xDD, 0xE9 );
	_TEST32( "dde9 fucomp st(1)", 0xDD, 0xE9 );
	_TEST64( "dae9 fucompp", 0xDA, 0xE9 );
	_TEST32( "dae9 fucompp", 0xDA, 0xE9 );

	//FTST
	_TEST64( "d9e4 ftst", 0xD9, 0xE4 );
	_TEST32( "d9e4 ftst", 0xD9, 0xE4 );

	// FSUBR/FSUBRP/FISUBR
	_TEST64( "d86820 fsubr dword ptr [rax+0000000000000020h]", 0xD8, 0x68, 0x20 );
	_TEST32( "d86820 fsubr dword ptr [eax+00000020h]", 0xD8, 0x68, 0x20 );
	_TEST64( "dc6820 fsubr qword ptr [rax+0000000000000020h]", 0xDC, 0x68, 0x20 );
	_TEST32( "dc6820 fsubr qword ptr [eax+00000020h]", 0xDC, 0x68, 0x20 );
	_TEST32( "d8e9 fsubr st(0),st(1)", 0xD8, 0xe9 );
	_TEST64( "d8e9 fsubr st(0),st(1)", 0xD8, 0xe9 );
	_TEST64( "dce1 fsubr st(1),st(0)", 0xDC, 0xe1 );
	_TEST32( "dce1 fsubr st(1),st(0)", 0xDC, 0xe1 );
	_TEST64( "dee1 fsubrp st(1),st(0)", 0xDE, 0xe1 );
	_TEST32( "dee1 fsubrp st(1),st(0)", 0xDE, 0xe1 );
	_TEST64( "da6820 fisubr dword ptr [rax+0000000000000020h]", 0xDA, 0x68, 0x20 );
	_TEST32( "da6820 fisubr dword ptr [eax+00000020h]", 0xDA, 0x68, 0x20 );
	_TEST64( "de6820 fisubr word ptr [rax+0000000000000020h]", 0xDE, 0x68, 0x20 );
	_TEST32( "de6820 fisubr word ptr [eax+00000020h]", 0xDE, 0x68, 0x20 );

	// FSUB/FSUBP/FISUB
	_TEST64( "d86020 fsub dword ptr [rax+0000000000000020h]", 0xD8, 0x60, 0x20 );
	_TEST32( "d86020 fsub dword ptr [eax+00000020h]", 0xD8, 0x60, 0x20 );
	_TEST64( "dc6020 fsub qword ptr [rax+0000000000000020h]", 0xDC, 0x60, 0x20 );
	_TEST32( "dc6020 fsub qword ptr [eax+00000020h]", 0xDC, 0x60, 0x20 );
	_TEST32( "d8e1 fsub st(0),st(1)", 0xD8, 0xe1 );
	_TEST64( "d8e1 fsub st(0),st(1)", 0xD8, 0xe1 );
	_TEST64( "dce9 fsub st(1),st(0)", 0xDC, 0xe9 );
	_TEST32( "dce9 fsub st(1),st(0)", 0xDC, 0xe9 );
	_TEST64( "dee9 fsubp st(1),st(0)", 0xDE, 0xe9 );
	_TEST32( "dee9 fsubp st(1),st(0)", 0xDE, 0xe9 );
	_TEST64( "da6020 fisub dword ptr [rax+0000000000000020h]", 0xDA, 0x60, 0x20 );
	_TEST32( "da6020 fisub dword ptr [eax+00000020h]", 0xDA, 0x60, 0x20 );
	_TEST64( "de6020 fisub word ptr [rax+0000000000000020h]", 0xDE, 0x60, 0x20 );
	_TEST32( "de6020 fisub word ptr [eax+00000020h]", 0xDE, 0x60, 0x20 );

	// FSTSW/FNSTSW
	_TEST64( "9bdd7820 fstsw word ptr [rax+0000000000000020h]", 0x9B, 0xDD, 0x78, 0x20 );
	_TEST32( "9bdd7820 fstsw word ptr [eax+00000020h]", 0x9B, 0xDD, 0x78, 0x20 );
	_TEST64( "9bdfe0 fstsw ax", 0x9B, 0xDF, 0xE0 );
	_TEST32( "9bdfe0 fstsw ax", 0x9B, 0xDF, 0xE0  );
	_TEST64( "dd7820 fnstsw word ptr [rax+0000000000000020h]", 0xDD, 0x78, 0x20 );
	_TEST32( "dd7820 fnstsw word ptr [eax+00000020h]", 0xDD, 0x78, 0x20  );
	_TEST64( "dfe0 fnstsw ax", 0xDF, 0xE0 );
	_TEST32( "dfe0 fnstsw ax", 0xDF, 0xE0  );

	// FSTENV/FNSTENV
	_TEST64( "9bd97020 fstenv 28byte ptr [rax+0000000000000020h]", 0x9B, 0xD9, 0x70, 0x20 );
	_TEST32( "9bd97020 fstenv 28byte ptr [eax+00000020h]", 0x9B, 0xD9, 0x70, 0x20 );
	_TEST32( "669bd97020 fstenv 14byte ptr [eax+00000020h]", 0x66, 0x9B, 0xD9, 0x70, 0x20 );
	_TEST64( "d97020 fnstenv 28byte ptr [rax+0000000000000020h]", 0xD9, 0x70, 0x20 );
	_TEST64( "66d97020 fnstenv 14byte ptr [rax+0000000000000020h]", 0x66, 0xD9, 0x70, 0x20 );
	_TEST32( "d97020 fnstenv 28byte ptr [eax+00000020h]", 0xD9, 0x70, 0x20 );

	// FSTCW/FNSTCW
	_TEST64( "9bd97820 fstcw word ptr [rax+0000000000000020h]", 0x9B, 0xD9, 0x78, 0x20 );
	_TEST32( "9bd97820 fstcw word ptr [eax+00000020h]",0x9B, 0xD9, 0x78, 0x20 );
	_TEST64( "d97820 fnstcw word ptr [rax+0000000000000020h]", 0xD9, 0x78, 0x20 );
	_TEST32( "d97820 fnstcw word ptr [eax+00000020h]", 0xD9, 0x78, 0x20 );

	// FST/FSTP
	_TEST64( "d95020 fst dword ptr [rax+0000000000000020h]", 0xD9, 0x50, 0x20 );
	_TEST32( "d95020 fst dword ptr [eax+00000020h]", 0xD9, 0x50, 0x20 );
	_TEST64( "dd5020 fst qword ptr [rax+0000000000000020h]", 0xDD, 0x50, 0x20 );
	_TEST32( "dd5020 fst qword ptr [eax+00000020h]", 0xDD, 0x50, 0x20 );
	_TEST64( "ddd1 fst st(1)", 0xDD, 0xD1 );
	_TEST32( "ddd1 fst st(1)", 0xDD, 0xD1 );
	_TEST64( "d95820 fstp dword ptr [rax+0000000000000020h]", 0xD9, 0x58, 0x20 );
	_TEST32( "d95820 fstp dword ptr [eax+00000020h]", 0xD9, 0x58, 0x20 );
	_TEST64( "dd5820 fstp qword ptr [rax+0000000000000020h]", 0xDD, 0x58, 0x20 );
	_TEST32( "dd5820 fstp qword ptr [eax+00000020h]", 0xDD, 0x58, 0x20 );
	_TEST64( "db7820 fstp tbyte ptr [rax+0000000000000020h]", 0xDB, 0x78, 0x20 );
	_TEST32( "db7820 fstp tbyte ptr [eax+00000020h]", 0xDB, 0x78, 0x20 );
	_TEST64( "ddd9 fstp st(1)", 0xDD, 0xD9 );
	_TEST32( "ddd9 fstp st(1)", 0xDD, 0xD9 );

	// FSQRT
	_TEST64( "d9fa fsqrt", 0xD9, 0xFA );
	_TEST32( "d9fa fsqrt", 0xD9, 0xFA );

	//FSINCOS
	_TEST64( "d9fb fsincos", 0xD9, 0xFB );
	_TEST32( "d9fb fsincos", 0xD9, 0xFB );

	//FSIN
	_TEST64( "d9fe fsin", 0xD9, 0xFE );
	_TEST32( "d9fe fsin", 0xD9, 0xFE );

	//FSCALE
	_TEST64( "d9fd fscale", 0xD9, 0xFD );
	_TEST32( "d9fd fscale", 0xD9, 0xFD  );

	// FSAVE/FNSAVE
	_TEST64( "9bdd7020 fsave 108byte ptr [rax+0000000000000020h]", 0x9B, 0xDD, 0x70, 0x20 );
	_TEST32( "9bdd7020 fsave 108byte ptr [eax+00000020h]", 0x9B, 0xDD, 0x70, 0x20  );
	_TEST32( "669bdd7020 fsave 94byte ptr [eax+00000020h]", 0x66, 0x9B, 0xDD, 0x70, 0x20  );
	_TEST64( "dd7020 fnsave 108byte ptr [rax+0000000000000020h]", 0xDD, 0x70, 0x20 );
	_TEST64( "66dd7020 fnsave 94byte ptr [rax+0000000000000020h]", 0x66, 0xDD, 0x70, 0x20 );
	_TEST32( "dd7020 fnsave 108byte ptr [eax+00000020h]", 0xDD, 0x70, 0x20 );

	// FRSTOR
	//todo: drokowanie niestandardowych size directive opcjonanie. opcja konfiguracyjna do wylaczania drukowania takich wartosci.
	_TEST64( "dd6020 frstor 108byte ptr [rax+0000000000000020h]", 0xDD, 0x60, 0x20 );
	_TEST32( "dd6020 frstor 108byte ptr [eax+00000020h]", 0xDD, 0x60, 0x20 );
	_TEST32( "66dd6020 frstor 94byte ptr [eax+00000020h]", 0x66, 0xDD, 0x60, 0x20 );

	// FRNDINT
	_TEST64( "d9fc frndint", 0xD9, 0xFc );
	_TEST32( "d9fc frndint", 0xD9, 0xFc );

	// FPTAN
	_TEST64( "d9f2 fptan", 0xD9, 0xF2 );
	_TEST32( "d9f2 fptan", 0xD9, 0xF2 );

	// FPREM1
	_TEST64( "d9f5 fprem1", 0xD9, 0xF5 );
	_TEST32( "d9f5 fprem1", 0xD9, 0xF5 );

	// FPREM
	_TEST64( "d9f8 fprem", 0xD9, 0xF8 );
	_TEST32( "d9f8 fprem", 0xD9, 0xF8 );

	// FPATAN
	_TEST64( "d9f3 fpatan", 0xD9, 0xF3 );
	_TEST32( "d9f3 fpatan", 0xD9, 0xF3 );

	// FNOP
	_TEST64( "d9d0 fnop", 0xD9, 0xD0 );
	_TEST32( "d9d0 fnop", 0xD9, 0xD0 );

	// FMUL/FMULP/FIMUL
	_TEST64( "d84820 fmul dword ptr [rax+0000000000000020h]", 0xD8, 0x48, 0x20 );
	_TEST32( "d84820 fmul dword ptr [eax+00000020h]", 0xD8, 0x48, 0x20 );
	_TEST64( "dc4820 fmul qword ptr [rax+0000000000000020h]", 0xDC, 0x48, 0x20 );
	_TEST32( "dc4820 fmul qword ptr [eax+00000020h]", 0xDC, 0x48, 0x20 );
	_TEST32( "d8c9 fmul st(0),st(1)", 0xD8, 0xc9 );
	_TEST64( "d8c9 fmul st(0),st(1)", 0xD8, 0xc9 );
	_TEST64( "dcc9 fmul st(1),st(0)", 0xDC, 0xc9 );
	_TEST32( "dcc9 fmul st(1),st(0)", 0xDC, 0xc9 );
	_TEST64( "dec9 fmulp st(1),st(0)", 0xDE, 0xc9 );
	_TEST32( "dec9 fmulp st(1),st(0)", 0xDE, 0xc9 );
	_TEST64( "da4820 fimul dword ptr [rax+0000000000000020h]", 0xDA, 0x48, 0x20 );
	_TEST32( "da4820 fimul dword ptr [eax+00000020h]", 0xDA, 0x48, 0x20 );
	_TEST64( "de4820 fimul word ptr [rax+0000000000000020h]", 0xDE, 0x48, 0x20 );
	_TEST32( "de4820 fimul word ptr [eax+00000020h]", 0xDE, 0x48, 0x20 );

	// FLDENV
	//todo: drokowanie niestandardowych size directive opcjonanie. opcja konfiguracyjna do wylaczania drukowania takich wartosci.
	_TEST64( "d96020 fldenv 28byte ptr [rax+0000000000000020h]", 0xD9, 0x60, 0x20 );
	_TEST32( "d96020 fldenv 28byte ptr [eax+00000020h]", 0xD9, 0x60, 0x20 );
	_TEST32( "66d96020 fldenv 14byte ptr [eax+00000020h]", 0x66, 0xD9, 0x60, 0x20 );

	// FLDCW
	_TEST32( "d96840 fldcw word ptr [eax+00000040h]", 0xD9, 0x68, 0x40 );
	_TEST64( "d96840 fldcw word ptr [rax+0000000000000040h]", 0xD9, 0x68, 0x40 );

	// FLD1
	_TEST32( "d9e8 fld1", 0xD9, 0xE8 );
	_TEST64( "d9e8 fld1", 0xD9, 0xE8 );

	_TEST32( "d9e9 fldl2t", 0xD9, 0xE9 );
	_TEST64( "d9e9 fldl2t", 0xD9, 0xE9 );

	_TEST32( "d9ea fldl2e", 0xD9, 0xEA );
	_TEST64( "d9ea fldl2e", 0xD9, 0xEA );

	_TEST32( "d9eb fldpi", 0xD9, 0xEB );
	_TEST64( "d9eb fldpi", 0xD9, 0xEB );

	_TEST32( "d9ec fldlg2", 0xD9, 0xEC );
	_TEST64( "d9ec fldlg2", 0xD9, 0xEC );

	_TEST32( "d9ed fldln2", 0xD9, 0xED );
	_TEST64( "d9ed fldln2", 0xD9, 0xED );

	_TEST32( "d9ee fldz", 0xD9, 0xEE );
	_TEST64( "d9ee fldz", 0xD9, 0xEE );

	// FLD
	_TEST32( "d94020 fld dword ptr [eax+00000020h]", 0xD9, 0x40, 0x20 );
	_TEST64( "d94020 fld dword ptr [rax+0000000000000020h]", 0xD9, 0x40, 0x20 );
	_TEST32( "dd4020 fld qword ptr [eax+00000020h]", 0xDD, 0x40, 0x20 );
	_TEST64( "dd4020 fld qword ptr [rax+0000000000000020h]", 0xDD, 0x40, 0x20 );
	_TEST32( "db6820 fld tbyte ptr [eax+00000020h]", 0xDB, 0x68, 0x20 );
	_TEST64( "db6820 fld tbyte ptr [rax+0000000000000020h]", 0xDB, 0x68, 0x20 );
	_TEST32( "d9c1 fld st(1)", 0xD9, 0xC1 );
	_TEST64( "d9c1 fld st(1)", 0xD9, 0xC1 );

	// FISTTP
	_TEST32( "df4820 fisttp word ptr [eax+00000020h]", 0xDF, 0x48, 0x20 );
	_TEST64( "df4820 fisttp word ptr [rax+0000000000000020h]", 0xDF, 0x48, 0x20 );
	_TEST32( "db4820 fisttp dword ptr [eax+00000020h]", 0xDB, 0x48, 0x20 );
	_TEST64( "db4820 fisttp dword ptr [rax+0000000000000020h]", 0xDB, 0x48, 0x20 );
	_TEST32( "dd4820 fisttp qword ptr [eax+00000020h]", 0xDD, 0x48, 0x20 );
	_TEST64( "dd4820 fisttp qword ptr [rax+0000000000000020h]", 0xDD, 0x48, 0x20 );

	// FIST/FISTP
	_TEST32( "df5020 fist word ptr [eax+00000020h]", 0xDF, 0x50, 0x20 );
	_TEST64( "df5020 fist word ptr [rax+0000000000000020h]", 0xDF, 0x50, 0x20 );
	_TEST32( "db5020 fist dword ptr [eax+00000020h]", 0xDB, 0x50, 0x20 );
	_TEST64( "db5020 fist dword ptr [rax+0000000000000020h]", 0xDB, 0x50, 0x20 );
	_TEST32( "df5820 fistp word ptr [eax+00000020h]", 0xDF, 0x58, 0x20 );
	_TEST64( "df5820 fistp word ptr [rax+0000000000000020h]", 0xDF, 0x58, 0x20 );
	_TEST32( "db5820 fistp dword ptr [eax+00000020h]", 0xDB, 0x58, 0x20 );
	_TEST64( "db5820 fistp dword ptr [rax+0000000000000020h]", 0xDB, 0x58, 0x20 );
	_TEST32( "df7820 fistp qword ptr [eax+00000020h]", 0xDF, 0x78, 0x20 );
	_TEST64( "df7820 fistp qword ptr [rax+0000000000000020h]", 0xDF, 0x78, 0x20 );

	// FINIT/FNINIT
	_TEST32( "9bdbe3 finit", 0x9B, 0xDB, 0xE3 );
	_TEST64( "dbe3 fninit", 0xDB, 0xE3 );

	// FINCSTP
	_TEST32( "d9f7 fincstp", 0xD9, 0xF7 );
	_TEST64( "d9f7 fincstp", 0xD9, 0xF7);

	// FILD
	_TEST32( "df4040 fild word ptr [eax+00000040h]", 0xDF, 0x40, 0x40 );
	_TEST64( "df4040 fild word ptr [rax+0000000000000040h]", 0xDF, 0x40, 0x40 );
	_TEST32( "db4040 fild dword ptr [eax+00000040h]", 0xDB, 0x40, 0x40 );
	_TEST64( "db4040 fild dword ptr [rax+0000000000000040h]", 0xDB, 0x40, 0x40 );
	_TEST32( "df6840 fild qword ptr [eax+00000040h]", 0xDF, 0x68, 0x40 );
	_TEST64( "df6840 fild qword ptr [rax+0000000000000040h]", 0xDF, 0x68, 0x40 );

	// FICOM
	_TEST32( "de5040 ficom word ptr [eax+00000040h]", 0xDE, 0x50, 0x40 );
	_TEST64( "de5040 ficom word ptr [rax+0000000000000040h]", 0xDE, 0x50, 0x40 );
	_TEST32( "da5040 ficom dword ptr [eax+00000040h]", 0xDA, 0x50, 0x40 );
	_TEST64( "da5040 ficom dword ptr [rax+0000000000000040h]", 0xDA, 0x50, 0x40 );
	_TEST32( "de5840 ficomp word ptr [eax+00000040h]", 0xDE, 0x58, 0x40 );
	_TEST64( "de5840 ficomp word ptr [rax+0000000000000040h]", 0xDE, 0x58, 0x40 );
	_TEST32( "da5840 ficomp dword ptr [eax+00000040h]", 0xDA, 0x58, 0x40 );
	_TEST64( "da5840 ficomp dword ptr [rax+0000000000000040h]", 0xDA, 0x58, 0x40 );

	// FFREE
	_TEST32( "ddc1 ffree st(1)", 0xDD, 0xC1 );
	_TEST64( "ddc1 ffree st(1)", 0xDD, 0xC1 );

	// FDIVR
	_TEST64( "d87820 fdivr dword ptr [rax+0000000000000020h]", 0xD8, 0x78, 0x20 );
	_TEST32( "d87820 fdivr dword ptr [eax+00000020h]", 0xD8, 0x78, 0x20 );
	_TEST64( "dc7820 fdivr qword ptr [rax+0000000000000020h]", 0xDC, 0x78, 0x20 );
	_TEST32( "dc7820 fdivr qword ptr [eax+00000020h]", 0xDC, 0x78, 0x20 );
	_TEST32( "d8f9 fdivr st(0),st(1)", 0xD8, 0xF9 );
	_TEST64( "d8f9 fdivr st(0),st(1)", 0xD8, 0xF9 );
	_TEST64( "dcf1 fdivr st(1),st(0)", 0xDC, 0xF1 );
	_TEST32( "dcf1 fdivr st(1),st(0)", 0xDC, 0xF1 );
	_TEST64( "def1 fdivrp st(1),st(0)", 0xDE, 0xF1 );
	_TEST32( "def1 fdivrp st(1),st(0)", 0xDE, 0xF1 );
	_TEST64( "da7820 fidivr dword ptr [rax+0000000000000020h]", 0xDA, 0x78, 0x20 );
	_TEST32( "da7820 fidivr dword ptr [eax+00000020h]", 0xDA, 0x78, 0x20 );
	_TEST64( "de7820 fidivr word ptr [rax+0000000000000020h]", 0xDE, 0x78, 0x20 );
	_TEST32( "de7820 fidivr word ptr [eax+00000020h]", 0xDE, 0x78, 0x20 );

	// FDIV
	_TEST64( "d87020 fdiv dword ptr [rax+0000000000000020h]", 0xD8, 0x70, 0x20 );
	_TEST32( "d87020 fdiv dword ptr [eax+00000020h]", 0xD8, 0x70, 0x20 );
	_TEST64( "dc7020 fdiv qword ptr [rax+0000000000000020h]", 0xDC, 0x70, 0x20 );
	_TEST32( "dc7020 fdiv qword ptr [eax+00000020h]", 0xDC, 0x70, 0x20 );
	_TEST32( "d8f1 fdiv st(0),st(1)", 0xD8, 0xF1 );
	_TEST64( "d8f1 fdiv st(0),st(1)", 0xD8, 0xF1 );
	_TEST64( "dcf9 fdiv st(1),st(0)", 0xDC, 0xF9 );
	_TEST32( "dcf9 fdiv st(1),st(0)", 0xDC, 0xF9 );
	_TEST64( "def9 fdivp st(1),st(0)", 0xDE, 0xF9 );
	_TEST32( "def9 fdivp st(1),st(0)", 0xDE, 0xF9 );
	_TEST64( "da7020 fidiv dword ptr [rax+0000000000000020h]", 0xDA, 0x70, 0x20 );
	_TEST32( "da7020 fidiv dword ptr [eax+00000020h]", 0xDA, 0x70, 0x20 );
	_TEST64( "de7020 fidiv word ptr [rax+0000000000000020h]", 0xDE, 0x70, 0x20 );
	_TEST32( "de7020 fidiv word ptr [eax+00000020h]", 0xDE, 0x70, 0x20 );


	// FDECSTP
	_TEST64( "d9f6 fdecstp", 0xD9, 0xf6 );
	_TEST32( "d9f6 fdecstp", 0xD9, 0xf6 );

	// FCOS
	_TEST64( "d9ff fcos", 0xD9, 0xFF );
	_TEST32( "d9ff fcos", 0xD9, 0xFF );

	// FCOMI
	_TEST64( "dbf1 fcomi st(0),st(1)", 0xDB, 0xF1 );
	_TEST32( "dbf1 fcomi st(0),st(1)", 0xDB, 0xF1 );

	// FCOMIP
	_TEST64( "dff1 fcomip st(0),st(1)", 0xDF, 0xF1 );
	_TEST32( "dff1 fcomip st(0),st(1)", 0xDF, 0xF1 );

	// FUCOMI
	_TEST64( "dbe9 fucomi st(0),st(1)", 0xDB, 0xE9 );
	_TEST32( "dbe9 fucomi st(0),st(1)", 0xDB, 0xE9 );

	// FUCOMIP
	_TEST64( "dfe9 fucomip st(0),st(1)", 0xDF, 0xE9 );
	_TEST32( "dfe9 fucomip st(0),st(1)", 0xDF, 0xE9 );

	// FCMOVNU
	_TEST64( "dbd9 fcmovnu st(0),st(1)", 0xDB, 0xD9 );
	_TEST32( "dbd9 fcmovnu st(0),st(1)", 0xDB, 0xD9 );

	// FCMOVNBE
	_TEST64( "dbd1 fcmovnbe st(0),st(1)", 0xDB, 0xD1 );
	_TEST32( "dbd1 fcmovnbe st(0),st(1)", 0xDB, 0xD1 );

	// FCMOVNE
	_TEST64( "dbc9 fcmovne st(0),st(1)", 0xDB, 0xC9 );
	_TEST32( "dbc9 fcmovne st(0),st(1)", 0xDB, 0xC9 );

	// FCMOVNB
	_TEST64( "dbc1 fcmovnb st(0),st(1)", 0xDB, 0xC1 );
	_TEST32( "dbc1 fcmovnb st(0),st(1)", 0xDB, 0xC1 );

	// FCMOVU
	_TEST64( "dad9 fcmovu st(0),st(1)", 0xDA, 0xD9 );
	_TEST32( "dad9 fcmovu st(0),st(1)", 0xDA, 0xD9);

	// FCMOVBE
	_TEST64( "dad1 fcmovbe st(0),st(1)", 0xDA, 0xD1 );
	_TEST32( "dad1 fcmovbe st(0),st(1)", 0xDA, 0xD1 );

	// FCMOVB
	_TEST64( "dac1 fcmovb st(0),st(1)", 0xDA, 0xC1 );
	_TEST32( "dac1 fcmovb st(0),st(1)", 0xDA, 0xC1 );

	// FCMOVE
	_TEST64( "dac9 fcmove st(0),st(1)", 0xDA, 0xC9 );
	_TEST32( "dac9 fcmove st(0),st(1)", 0xDA, 0xC9 );

	// FNCLEX
	_TEST64( "dbe2 fnclex", 0xDB, 0xE2 );
	_TEST32( "dbe2 fnclex", 0xDB, 0xE2 );

	// FCHS
	_TEST64( "d9e0 fchs", 0xD9, 0xE0 ) ;
	_TEST32( "d9e0 fchs", 0xD9, 0xE0 );

	// FBSTP
	_TEST64( "df7020 fbstp tbyte ptr [rax+0000000000000020h]", 0xDf, 0x70, 0x20 ) ;
	_TEST32( "df7020 fbstp tbyte ptr [eax+00000020h]", 0xDf, 0x70, 0x20 );

	// FBLD
	_TEST64( "df6020 fbld tbyte ptr [rax+0000000000000020h]", 0xDf, 0x60, 0x20 ) ;
	_TEST32( "df6020 fbld tbyte ptr [eax+00000020h]", 0xDf, 0x60, 0x20 );

	// FADD
	_TEST64( "d84020 fadd dword ptr [rax+0000000000000020h]", 0xD8, 0x40, 0x20 );
	_TEST32( "d84020 fadd dword ptr [eax+00000020h]", 0xD8, 0x40, 0x20 );
	_TEST64( "dc4020 fadd qword ptr [rax+0000000000000020h]", 0xDC, 0x40, 0x20 );
	_TEST32( "dc4020 fadd qword ptr [eax+00000020h]", 0xDC, 0x40, 0x20 );

	_TEST32( "d8c0 fadd st(0),st(0)", 0xD8, 0xC0 );
	_TEST32( "d8c1 fadd st(0),st(1)", 0xD8, 0xC1 );
	_TEST32( "d8c2 fadd st(0),st(2)", 0xD8, 0xC2 );
	_TEST32( "d8c3 fadd st(0),st(3)", 0xD8, 0xC3 );
	_TEST32( "d8c4 fadd st(0),st(4)", 0xD8, 0xC4 );
	_TEST32( "d8c5 fadd st(0),st(5)", 0xD8, 0xC5 );
	_TEST32( "d8c6 fadd st(0),st(6)", 0xD8, 0xC6 );
	_TEST32( "d8c7 fadd st(0),st(7)", 0xD8, 0xC7 );

	_TEST64( "d8c0 fadd st(0),st(0)", 0xD8, 0xC0 );

	_TEST64( "dcc1 fadd st(1),st(0)", 0xDC, 0xC1 );
	_TEST32( "dcc1 fadd st(1),st(0)", 0xDC, 0xC1 );

	_TEST64( "dec1 faddp st(1),st(0)", 0xDE, 0xC1 );
	_TEST32( "dec1 faddp st(1),st(0)", 0xDE, 0xC1 );

	_TEST64( "da4020 fiadd dword ptr [rax+0000000000000020h]", 0xDA, 0x40, 0x20 );
	_TEST32( "da4020 fiadd dword ptr [eax+00000020h]", 0xDA, 0x40, 0x20 );
	_TEST64( "de4020 fiadd word ptr [rax+0000000000000020h]", 0xDE, 0x40, 0x20 );
	_TEST32( "de4020 fiadd word ptr [eax+00000020h]", 0xDE, 0x40, 0x20 );

	// F2XM1
	_TEST64( "d9f0 f2xm1", 0xD9, 0xF0 );
	_TEST32( "d9f0 f2xm1", 0xD9, 0xF0);

	// FABS
	_TEST64( "d9e1 fabs", 0xD9, 0xE1 );
	_TEST32( "d9e1 fabs", 0xD9, 0xE1);

	// EXTRACTPS
	_TEST64( "660f3a17402050 extractps dword ptr [rax+0000000000000020h],xmm0,50h", 0x66, 0x0F, 0x3A, 0x17, 0x40, 0x20, 0x50 );
	_TEST32( "660f3a17402050 extractps dword ptr [eax+00000020h],xmm0,50h", 0x66, 0x0F, 0x3A, 0x17, 0x40, 0x20, 0x50 );

	// ENTER
	_TEST32( "c8eeff55 enter 0ffeeh,55h", 0xc8, 0xEE, 0xFF, 0x55 );
	_TEST32( "66c8eeff55 enter 0ffeeh,55h", 0x66, 0xc8, 0xEE, 0xFF, 0x55 );
	_TEST64( "c8eeff55 enter 0ffeeh,55h", 0xc8, 0xEE, 0xFF, 0x55 );
	_TEST64( "66c8eeff55 enter 0ffeeh,55h", 0x66, 0xc8, 0xEE, 0xFF, 0x55 );
	_TEST64( "6648c8eeff55 enter 0ffeeh,55h", 0x66, 0x48, 0xc8, 0xEE, 0xFF, 0x55 );
	_TEST32( "c8eeff00 enter 0ffeeh,00h", 0xc8, 0xEE, 0xFF, 0x00 );
	_TEST32( "c8eeff01 enter 0ffeeh,01h", 0xc8, 0xEE, 0xFF, 0x01 );

	// EMMS
	_TEST32( "0f77 emms", 0x0F, 0x77 );
	_TEST64( "0f77 emms", 0x0F, 0x77 );

	// DPPD
	_TEST32( "660f3a411401ff dppd xmm2,oword ptr [ecx+eax],0ffh", 0x66, 0x0F, 0x3A, 0x41, 0x14, 0x01, 0xFF );
	_TEST64( "660f3a411401ff dppd xmm2,oword ptr [rcx+rax],0ffh", 0x66, 0x0F, 0x3A, 0x41, 0x14, 0x01, 0xFF );

	// DPPS
	_TEST32( "660f3a401401ff dpps xmm2,oword ptr [ecx+eax],0ffh", 0x66, 0x0F, 0x3A, 0x40, 0x14, 0x01, 0xFF );
	_TEST64( "660f3a401401ff dpps xmm2,oword ptr [rcx+rax],0ffh", 0x66, 0x0F, 0x3A, 0x40, 0x14, 0x01, 0xFF );

	// DIVSD
	_TEST64( "f20f5e4020 divsd xmm0,qword ptr [rax+0000000000000020h]", 0xF2, 0x0F, 0x5E, 0x40, 0x20 );
	_TEST32( "f20f5ec2 divsd xmm0,xmm2", 0xF2, 0x0F, 0x5E, 0xC2 );
	_TEST32( "f20f5e4020 divsd xmm0,qword ptr [eax+00000020h]", 0xF2, 0x0F, 0x5E, 0x40, 0x20 );

	// DIVSS
	_TEST64( "f30f5e4020 divss xmm0,dword ptr [rax+0000000000000020h]", 0xF3, 0x0F, 0x5E, 0x40, 0x20 );
	_TEST32( "f30f5ec2 divss xmm0,xmm2", 0xF3, 0x0F, 0x5E, 0xC2 );
	_TEST32( "f30f5e4020 divss xmm0,dword ptr [eax+00000020h]", 0xF3, 0x0F, 0x5E, 0x40, 0x20 );

	// DIVPD
	_TEST32( "660f5e1401 divpd xmm2,oword ptr [ecx+eax]", 0x66, 0x0F, 0x5E, 0x14, 0x01 );
	_TEST64( "660f5e1401 divpd xmm2,oword ptr [rcx+rax]", 0x66, 0x0F, 0x5E, 0x14, 0x01 );

	// DIVPS
	_TEST32( "0f5e1401 divps xmm2,oword ptr [ecx+eax]", 0x0F, 0x5E, 0x14, 0x01 );
	_TEST64( "0f5e1401 divps xmm2,oword ptr [rcx+rax]", 0x0F, 0x5E, 0x14, 0x01 );

	// DIV
	// F6 /6 DIV r/m8 A Valid Valid Unsigned divide AX by r/m8,with result stored in AL Quotient, AH Remainder.
	// REX + F6 /6 DIV r/m8* A Valid N.E. Unsigned divide AX by r/m8, with result stored in AL Quotient, AH Remainder.
	_TEST32( "f633 div ax,byte ptr [ebx]", 0xF6, 0x33 );
	_TEST32( "66f633 div ax,byte ptr [ebx]", 0x66, 0xF6, 0x33 );
	_TEST64( "48f6f6 div ax,sil", 0x48, 0xF6, 0xF6 );
	_TEST64( "f6f6 div ax,dh", 0xF6, 0xF6 );
	// F7 /6 DIV r/m16 A Valid Valid Unsigned divide DX:AX by r/m16, with result stored in AX Quotient, DX Remainder.
	// F7 /6 DIV r/m32 A Valid Valid Unsigned divide EDX:EAX by r/m32, with result stored in EAX Quotient, EDX Remainder.
	// REX.W + F7 /6 DIV r/m64 A Valid N.E. Unsigned divide RDX:RAX by r/m64, with result stored in RAX Quotient, RDX Remainder.
	_TEST32( "f733 div eax,dword ptr [ebx]", 0xF7, 0x33 );
	_TEST32( "66f733 div ax,word ptr [ebx]", 0x66, 0xF7, 0x33 );
	_TEST64( "48f7f6 div rax,rsi", 0x48, 0xF7, 0xF6 );
	_TEST64( "f7f6 div eax,esi", 0xF7, 0xF6 );

	// DEC
	// 48+rw DEC r16 B N.E. Valid Decrement r16 by 1.
	// 48+rd DEC r32 B N.E. Valid Decrement r32 by 1.
	_TEST32( "48 dec eax", 0x48 );
	_TEST32( "6648 dec ax", 0x66, 0x48 );
	_TEST32( "49 dec ecx", 0x49 );
	_TEST32( "6649 dec cx", 0x66, 0x49 );
	_TEST64( "FAIL", 0x48 );
	// FE /1 DEC r/m8 A Valid Valid Decrement r/m8 by 1.
	// REX + FE /1 DEC r/m8* A Valid N.E. Decrement r/m8 by 1.
	_TEST32( "fe0b dec byte ptr [ebx]", 0xFE, 0x0B );
	_TEST64( "fe0b dec byte ptr [rbx]", 0xFE, 0x0B );
	_TEST64( "48fe0b dec byte ptr [rbx]", 0x48, 0xFE, 0x0B );
	_TEST64( "48fecc dec spl", 0x48, 0xFE, 0xCC );
	// FF /1 DEC r/m16 A Valid Valid Decrement r/m16 by 1.
	// FF /1 DEC r/m32 A Valid Valid Decrement r/m32 by 1.
	// REX.W + FF /1 DEC r/m64 A Valid N.E. Decrement r/m64 by 1.
	_TEST32( "ff0b dec dword ptr [ebx]", 0xFF, 0x0B );
	_TEST32( "66ff0b dec word ptr [ebx]", 0x66, 0xFF, 0x0B );
	_TEST64( "ff0b dec dword ptr [rbx]", 0xFF, 0x0B );
	_TEST64( "48ff0b dec qword ptr [rbx]", 0x48, 0xFF, 0x0B );
	_TEST64( "6640ff0b dec word ptr [rbx]", 0x66, 0x40, 0xFF, 0x0B );
	_TEST64( "49ffcc dec r12", 0x49, 0xFF, 0xCC );

	// DAS
	_TEST32( "2f das", 0x2F );
	_TEST64( "FAIL", 0x2F );

	// DAA
	_TEST32( "27 daa", 0x27 );
	_TEST64( "FAIL", 0x27 );

	// CWD_CDQ_CQO
	_TEST32( "99 cdq", 0x99 );
	_TEST32( "6699 cwd", 0x66, 0x99 );
	_TEST64( "99 cdq", 0x99 );
	_TEST64( "6699 cwd", 0x66, 0x99 );
	_TEST64( "664899 cqo", 0x66, 0x48, 0x99 );
	_TEST64( "4899 cqo", 0x48, 0x99 );
	_TEST64( "4099 cdq", 0x40, 0x99 );

	// CVTTSS2SI
	_TEST64( "f3480f2cc2 cvttss2si rax,xmm2", 0xF3, 0x48, 0x0F, 0x2C, 0xC2 );
	_TEST64( "f30f2c4020 cvttss2si eax,dword ptr [rax+0000000000000020h]", 0xF3, 0x0F, 0x2C, 0x40, 0x20 );
	_TEST32( "f30f2cc2 cvttss2si eax,xmm2", 0xF3, 0x0F, 0x2C, 0xC2 );
	_TEST32( "f30f2c4020 cvttss2si eax,dword ptr [eax+00000020h]", 0xF3, 0x0F, 0x2C, 0x40, 0x20 );
	_TEST64( "f30f2c4020 cvttss2si eax,dword ptr [rax+0000000000000020h]", 0xF3, 0x0F, 0x2C, 0x40, 0x20 );
	_TEST64( "f30f2cc2 cvttss2si eax,xmm2", 0xF3, 0x0F, 0x2C, 0xC2 );

	// CVTTSD2SI
	_TEST64( "f2480f2cc2 cvttsd2si rax,xmm2", 0xF2, 0x48, 0x0F, 0x2C, 0xC2 );
	_TEST64( "f20f2c4020 cvttsd2si eax,qword ptr [rax+0000000000000020h]", 0xF2, 0x0F, 0x2C, 0x40, 0x20 );
	_TEST32( "f20f2cc2 cvttsd2si eax,xmm2", 0xF2, 0x0F, 0x2C, 0xC2 );
	_TEST32( "f20f2c4020 cvttsd2si eax,qword ptr [eax+00000020h]", 0xF2, 0x0F, 0x2C, 0x40, 0x20 );
	_TEST64( "f20f2c4020 cvttsd2si eax,qword ptr [rax+0000000000000020h]", 0xF2, 0x0F, 0x2C, 0x40, 0x20 );
	_TEST64( "f20f2cc2 cvttsd2si eax,xmm2", 0xF2, 0x0F, 0x2C, 0xC2 );

	// CVTTPS2PI
	_TEST64( "0f2c4020 cvttps2pi mm0,qword ptr [rax+0000000000000020h]", 0x0F, 0x2C, 0x40, 0x20 );
	_TEST32( "0f2cc2 cvttps2pi mm0,xmm2", 0x0F, 0x2C, 0xC2 );
	_TEST32( "0f2c4020 cvttps2pi mm0,qword ptr [eax+00000020h]", 0x0F, 0x2C, 0x40, 0x20 );

	// CVTTPS2DQ
	_TEST64( "f30f5b4020 cvttps2dq xmm0,oword ptr [rax+0000000000000020h]", 0xF3, 0x0F, 0x5B, 0x40, 0x20 );
	_TEST32( "f30f5bc2 cvttps2dq xmm0,xmm2", 0xF3, 0x0F, 0x5B, 0xC2 );
	_TEST32( "f30f5b4020 cvttps2dq xmm0,oword ptr [eax+00000020h]", 0xF3, 0x0F, 0x5B, 0x40, 0x20 );

	// CVTTPD2PI
	_TEST64( "660f2c4020 cvttpd2pi mm0,oword ptr [rax+0000000000000020h]", 0x66, 0x0F, 0x2C, 0x40, 0x20 );
	_TEST32( "660f2cc2 cvttpd2pi mm0,xmm2", 0x66, 0x0F, 0x2C, 0xC2 );
	_TEST32( "660f2c4020 cvttpd2pi mm0,oword ptr [eax+00000020h]", 0x66, 0x0F, 0x2C, 0x40, 0x20 );

	// CVTTPD2DQ
	_TEST64( "660fe64020 cvttpd2dq xmm0,oword ptr [rax+0000000000000020h]", 0x66, 0x0F, 0xE6, 0x40, 0x20 );
	_TEST32( "660fe6c2 cvttpd2dq xmm0,xmm2", 0x66, 0x0F, 0xE6, 0xC2 );
	_TEST32( "660fe64020 cvttpd2dq xmm0,oword ptr [eax+00000020h]", 0x66, 0x0F, 0xE6, 0x40, 0x20 );

	// CVTSS2SI
	_TEST64( "f3480f2dc2 cvtss2si rax,xmm2", 0xF3, 0x48, 0x0F, 0x2D, 0xC2 );
	_TEST64( "f30f2d4020 cvtss2si eax,dword ptr [rax+0000000000000020h]", 0xF3, 0x0F, 0x2D, 0x40, 0x20 );
	_TEST32( "f30f2dc2 cvtss2si eax,xmm2", 0xF3, 0x0F, 0x2D, 0xC2 );
	_TEST32( "f30f2d4020 cvtss2si eax,dword ptr [eax+00000020h]", 0xF3, 0x0F, 0x2D, 0x40, 0x20 );
	_TEST64( "f30f2d4020 cvtss2si eax,dword ptr [rax+0000000000000020h]", 0xF3, 0x0F, 0x2D, 0x40, 0x20 );
	_TEST64( "f30f2dc2 cvtss2si eax,xmm2", 0xF3, 0x0F, 0x2D, 0xC2 );

	// CVTSS2SD
	_TEST64( "f30f5a4020 cvtss2sd xmm0,dword ptr [rax+0000000000000020h]", 0xF3, 0x0F, 0x5A, 0x40, 0x20 );
	_TEST32( "f30f5ac2 cvtss2sd xmm0,xmm2", 0xF3, 0x0F, 0x5A, 0xC2 );
	_TEST32( "f30f5a4020 cvtss2sd xmm0,dword ptr [eax+00000020h]", 0xF3, 0x0F, 0x5A, 0x40, 0x20 );

	// CVTSI2SS
	_TEST64( "f3480f2ac2 cvtsi2ss xmm0,rdx", 0xF3, 0x48, 0x0F, 0x2A, 0xC2 );
	_TEST64( "f30f2a4020 cvtsi2ss xmm0,dword ptr [rax+0000000000000020h]", 0xF3, 0x0F, 0x2A, 0x40, 0x20 );
	_TEST32( "f30f2ac2 cvtsi2ss xmm0,edx", 0xF3, 0x0F, 0x2A, 0xC2 );
	_TEST32( "f30f2a4020 cvtsi2ss xmm0,dword ptr [eax+00000020h]", 0xF3, 0x0F, 0x2A, 0x40, 0x20 );
	_TEST64( "f30f2a4020 cvtsi2ss xmm0,dword ptr [rax+0000000000000020h]", 0xF3, 0x0F, 0x2A, 0x40, 0x20 );
	_TEST64( "f30f2ac2 cvtsi2ss xmm0,edx", 0xF3, 0x0F, 0x2A, 0xC2 );

	// CVTSI2SD
	_TEST64( "f20f2a4020 cvtsi2sd xmm0,dword ptr [rax+0000000000000020h]", 0xF2, 0x0F, 0x2A, 0x40, 0x20 );
	_TEST32( "f20f2ac2 cvtsi2sd xmm0,edx", 0xF2, 0x0F, 0x2A, 0xC2 );
	_TEST32( "f20f2a4020 cvtsi2sd xmm0,dword ptr [eax+00000020h]", 0xF2, 0x0F, 0x2A, 0x40, 0x20 );
	_TEST64( "f20f2a4020 cvtsi2sd xmm0,dword ptr [rax+0000000000000020h]", 0xF2, 0x0F, 0x2A, 0x40, 0x20 );
	_TEST64( "f20f2ac2 cvtsi2sd xmm0,edx", 0xF2, 0x0F, 0x2A, 0xC2 );
	_TEST64( "f2480f2ac2 cvtsi2sd xmm0,rdx", 0xF2, 0x48, 0x0F, 0x2A, 0xC2 );

	// CVTSD2SS
	_TEST64( "f20f5a4020 cvtsd2ss xmm0,qword ptr [rax+0000000000000020h]", 0xF2, 0x0F, 0x5A, 0x40, 0x20 );
	_TEST32( "f20f5ac2 cvtsd2ss xmm0,xmm2", 0xF2, 0x0F, 0x5A, 0xC2 );
	_TEST32( "f20f5a4020 cvtsd2ss xmm0,qword ptr [eax+00000020h]", 0xF2, 0x0F, 0x5A, 0x40, 0x20 );

	// CVTSD2SI
	_TEST64( "f20f2d4020 cvtsd2si eax,qword ptr [rax+0000000000000020h]", 0xF2, 0x0F, 0x2D, 0x40, 0x20 );
	_TEST32( "f20f2dc2 cvtsd2si eax,xmm2", 0xF2, 0x0F, 0x2D, 0xC2 );
	_TEST32( "f20f2d4020 cvtsd2si eax,qword ptr [eax+00000020h]", 0xF2, 0x0F, 0x2D, 0x40, 0x20 );
	_TEST64( "f2480f2d4020 cvtsd2si rax,qword ptr [rax+0000000000000020h]", 0xF2, 0x48, 0x0F, 0x2D, 0x40, 0x20 );

	// CVTPS2PI
	_TEST64( "0f2d4020 cvtps2pi mm0,qword ptr [rax+0000000000000020h]", 0x0F, 0x2D, 0x40, 0x20 );
	_TEST32( "0f2dc2 cvtps2pi mm0,xmm2", 0x0F, 0x2D, 0xC2 );
	_TEST32( "0f2d4020 cvtps2pi mm0,qword ptr [eax+00000020h]", 0x0F, 0x2D, 0x40, 0x20 );

	// CVTPS2PD
	_TEST64( "0f5a4020 cvtps2pd xmm0,qword ptr [rax+0000000000000020h]", 0x0F, 0x5A, 0x40, 0x20 );
	_TEST32( "0f5ac2 cvtps2pd xmm0,xmm2", 0x0F, 0x5A, 0xC2 );
	_TEST32( "0f5a4020 cvtps2pd xmm0,qword ptr [eax+00000020h]", 0x0F, 0x5A, 0x40, 0x20 );

	// CVTPS2DQ
	_TEST64( "660f5b4020 cvtps2dq xmm0,oword ptr [rax+0000000000000020h]", 0x66, 0x0F, 0x5B, 0x40, 0x20 );
	_TEST32( "660f5bc2 cvtps2dq xmm0,xmm2", 0x66, 0x0F, 0x5B, 0xC2 );
	_TEST32( "660f5b4020 cvtps2dq xmm0,oword ptr [eax+00000020h]", 0x66, 0x0F, 0x5B, 0x40, 0x20 );

	// CVTPI2PS
	_TEST64( "0f2a4020 cvtpi2ps xmm0,qword ptr [rax+0000000000000020h]", 0x0F, 0x2A, 0x40, 0x20 );
	_TEST32( "0f2ac2 cvtpi2ps xmm0,mm2", 0x0F, 0x2A, 0xC2 );
	_TEST32( "0f2a4020 cvtpi2ps xmm0,qword ptr [eax+00000020h]", 0x0F, 0x2A, 0x40, 0x20 );

	// CVTPI2PD
	_TEST64( "660f2a4020 cvtpi2pd xmm0,qword ptr [rax+0000000000000020h]", 0x66, 0x0F, 0x2A, 0x40, 0x20 );
	_TEST32( "660f2ac2 cvtpi2pd xmm0,mm2", 0x66, 0x0F, 0x2A, 0xC2 );
	_TEST32( "660f2a4020 cvtpi2pd xmm0,qword ptr [eax+00000020h]", 0x66, 0x0F, 0x2A, 0x40, 0x20 );

	// CVTPD2PI
	_TEST64( "660f2d4020 cvtpd2pi mm0,oword ptr [rax+0000000000000020h]", 0x66, 0x0F, 0x2D, 0x40, 0x20 );
	_TEST32( "660f2dc2 cvtpd2pi mm0,xmm2", 0x66, 0x0F, 0x2D, 0xC2 );
	_TEST32( "660f2d4020 cvtpd2pi mm0,oword ptr [eax+00000020h]", 0x66, 0x0F, 0x2D, 0x40, 0x20 );

	// CVTPD2DQ
	_TEST64( "f20fe64020 cvtpd2dq xmm0,oword ptr [rax+0000000000000020h]", 0xF2, 0x0F, 0xE6, 0x40, 0x20 );
	_TEST32( "f20fe6c2 cvtpd2dq xmm0,xmm2", 0xF2, 0x0F, 0xE6, 0xC2 );
	_TEST32( "f20fe64020 cvtpd2dq xmm0,oword ptr [eax+00000020h]", 0xF2, 0x0F, 0xE6, 0x40, 0x20 );

	// CVTDQ2PS
	_TEST64( "0f5b4020 cvtdq2ps xmm0,oword ptr [rax+0000000000000020h]", 0x0F, 0x5b, 0x40, 0x20 );
	_TEST32( "0f5bc2 cvtdq2ps xmm0,xmm2", 0x0F, 0x5b, 0xC2 );
	_TEST32( "0f5b4020 cvtdq2ps xmm0,oword ptr [eax+00000020h]", 0x0F, 0x5b, 0x40, 0x20 );

	// CVTDQ2PD
	_TEST64( "f30fe64020 cvtdq2pd xmm0,qword ptr [rax+0000000000000020h]", 0xF3, 0x0F, 0xE6, 0x40, 0x20, 0x50 );
	_TEST32( "f30fe6c2 cvtdq2pd xmm0,xmm2", 0xF3, 0x0F, 0xE6, 0xC2 );
	_TEST32( "f30fe64020 cvtdq2pd xmm0,qword ptr [eax+00000020h]", 0xF3, 0x0F, 0xE6, 0x40, 0x20, 0x50 );

	// CRC32
	// F2 0F 38 F0 /r CRC32 r32, r/m8 A Valid Valid Accumulate CRC32 on r/m8.
	// F2 REX 0F 38 F0 /r CRC32 r32, r/m8* A Valid N.E. Accumulate CRC32 on r/m8.
	_TEST64( "f2400f38f04020 crc32 eax,byte ptr [rax+0000000000000020h]", 0xF2, 0x40, 0x0F, 0x38, 0xF0, 0x40, 0x20, 0x50 );
	_TEST64( "66f20f38f04020 crc32 eax,byte ptr [rax+0000000000000020h]", 0x66, 0xF2, 0x0F, 0x38, 0xF0, 0x40, 0x20, 0x50 );
	_TEST64( "f20f38f04020 crc32 eax,byte ptr [rax+0000000000000020h]", 0xF2, 0x0F, 0x38, 0xF0, 0x40, 0x20, 0x50 );
	_TEST32( "66f20f38f04020 crc32 eax,byte ptr [eax+00000020h]", 0x66, 0xF2, 0x0F, 0x38, 0xF0, 0x40, 0x20, 0x50 );
	_TEST32( "f20f38f04020 crc32 eax,byte ptr [eax+00000020h]", 0xF2, 0x0F, 0x38, 0xF0, 0x40, 0x20, 0x50 );
	// F2 REX.W 0F 38 F0 /r CRC32 r64, r/m8 A Valid N.E. Accumulate CRC32 on r/m8.
	_TEST64( "f2480f38f04020 crc32 rax,byte ptr [rax+0000000000000020h]", 0xF2, 0x48, 0x0F, 0x38, 0xF0, 0x40, 0x20, 0x50 );

	// F2 0F 38 F1 /r CRC32 r32, r/m16 A Valid Valid Accumulate CRC32 on r/m16.
	// F2 0F 38 F1 /r CRC32 r32, r/m32 A Valid Valid Accumulate CRC32 on r/m32.
	_TEST64( "f2400f38f14020 crc32 eax,dword ptr [rax+0000000000000020h]", 0xF2, 0x40, 0x0F, 0x38, 0xF1, 0x40, 0x20, 0x50 );
	_TEST64( "66f20f38f14020 crc32 eax,word ptr [rax+0000000000000020h]", 0x66, 0xF2, 0x0F, 0x38, 0xF1, 0x40, 0x20, 0x50 );
	_TEST64( "f20f38f14020 crc32 eax,dword ptr [rax+0000000000000020h]", 0xF2, 0x0F, 0x38, 0xF1, 0x40, 0x20, 0x50 );
	_TEST32( "66f20f38f14020 crc32 eax,word ptr [eax+00000020h]", 0x66, 0xF2, 0x0F, 0x38, 0xF1, 0x40, 0x20, 0x50 );
	_TEST32( "f20f38f14020 crc32 eax,dword ptr [eax+00000020h]", 0xF2, 0x0F, 0x38, 0xF1, 0x40, 0x20, 0x50 );
	// F2 REX.W 0F 38 F1 /r CRC32 r64, r/m64 A Valid N.E. Accumulate CRC32 on r/m64.
	_TEST64( "f2480f38f14020 crc32 rax,qword ptr [rax+0000000000000020h]", 0xF2, 0x48, 0x0F, 0x38, 0xF1, 0x40, 0x20, 0x50 );

	// CPUID
	_TEST64( "0fa2 cpuid", 0x0F, 0xA2 );
	_TEST32( "0fa2 cpuid", 0x0F, 0xA2 );

	// COMISS
	_TEST64( "0f2fc2 comiss xmm0,xmm2", 0x0F, 0x2F, 0xC2, 0x40, 0x20, 0x50 );
	_TEST64( "0f2f4020 comiss xmm0,dword ptr [rax+0000000000000020h]", 0x0F, 0x2F, 0x40, 0x20, 0x50 );
	_TEST32( "0f2fc2 comiss xmm0,xmm2", 0x0F, 0x2F, 0xC2 );
	_TEST32( "0f2f4020 comiss xmm0,dword ptr [eax+00000020h]", 0x0F, 0x2F, 0x40, 0x20, 0x50 );

	// COMISD
	_TEST64( "660f2fc2 comisd xmm0,xmm2", 0x66, 0x0F, 0x2F, 0xC2, 0x40, 0x20, 0x50 );
	_TEST64( "660f2f4020 comisd xmm0,qword ptr [rax+0000000000000020h]", 0x66, 0x0F, 0x2F, 0x40, 0x20, 0x50 );
	_TEST32( "660f2fc2 comisd xmm0,xmm2", 0x66, 0x0F, 0x2F, 0xC2 );
	_TEST32( "660f2f4020 comisd xmm0,qword ptr [eax+00000020h]", 0x66, 0x0F, 0x2F, 0x40, 0x20, 0x50 );

	// CMPS
	// A6
	_TEST32( "67a6 cmps byte ptr [si],byte ptr [di]", 0x67, 0xA6 );
	_TEST32( "6667a6 cmps byte ptr [si],byte ptr [di]", 0x66, 0x67, 0xA6 );
	_TEST32( "a6 cmps byte ptr [esi],byte ptr [edi]", 0xA6 );
	_TEST64( "48a6 cmps byte ptr [rsi],byte ptr [rdi]", 0x48, 0xA6 );
	_TEST64( "40a6 cmps byte ptr [rsi],byte ptr [rdi]", 0x40, 0xA6 );
	_TEST64( "6740a6 cmps byte ptr [esi],byte ptr [edi]", 0x67, 0x40, 0xA6 );
	_TEST64( "666740a6 cmps byte ptr [esi],byte ptr [edi]", 0x66, 0x67, 0x40, 0xA6 );
	// A7
	_TEST32( "67a7 cmps dword ptr [si],dword ptr [di]", 0x67, 0xA7 );
	_TEST32( "6667a7 cmps word ptr [si],word ptr [di]", 0x66, 0x67, 0xA7 );
	_TEST32( "a7 cmps dword ptr [esi],dword ptr [edi]", 0xA7 );
	_TEST64( "48a7 cmps qword ptr [rsi],qword ptr [rdi]", 0x48, 0xA7 );
	_TEST64( "40a7 cmps dword ptr [rsi],dword ptr [rdi]", 0x40, 0xA7 );
	_TEST64( "6740a7 cmps dword ptr [esi],dword ptr [edi]", 0x67, 0x40, 0xA7 );
	_TEST64( "666740a7 cmps word ptr [esi],word ptr [edi]", 0x66, 0x67, 0x40, 0xA7 );

	// CMPXCHG16B/CMPXCHG8B
	// REX.W + 0F C7 /1 m128 CMPXCHG16B m128 A Valid N.E. Compare RDX:RAX with m128. If equal, set ZF and load RCX:RBX into m128. Else, clear ZF and load m128 into RDX:RAX.
	_TEST64( "480fc749ff cmpxchg16b oword ptr [rcx+0ffffffffffffffffh]", 0x48, 0x0F, 0xC7, 0x49, 0xFF, 0x0FF, 0xFF, 0xFF );
	// 0F C7 /1 m64 CMPXCHG8B m64 A Valid Valid* Compare EDX:EAX with m64. If equal, set ZF and load ECX:EBX into m64. Else, clear ZF and load m64 into EDX:EAX.
	_TEST64( "0fc749ff cmpxchg8b qword ptr [rcx+0ffffffffffffffffh]", 0x0F, 0xC7, 0x49, 0xFF, 0x0FF, 0xFF, 0xFF );
	_TEST32( "0fc749ff cmpxchg8b qword ptr [ecx+0ffffffffh]", 0x0F, 0xC7, 0x49, 0xFF, 0x0FF, 0xFF, 0xFF );

	// TODO: Testy dla CMP, CMPPD

	// CMPSS
	// dodac support dla mmword i odkomentowac.
	_TEST64( "f30fc2402050 cmpss xmm0,dword ptr [rax+0000000000000020h],50h", 0xF3, 0x0F, 0xC2, 0x40, 0x20, 0x50 );
	_TEST32( "f30fc2402050 cmpss xmm0,dword ptr [eax+00000020h],50h", 0xF3, 0x0F, 0xC2, 0x40, 0x20, 0x50 );

	// CMPSD
	_TEST32( "f20fc2402050 cmpsd xmm0,qword ptr [eax+00000020h],50h", 0xF2, 0x0F, 0xC2, 0x40, 0x20, 0x50 );
	_TEST64( "f20fc2402050 cmpsd xmm0,qword ptr [rax+0000000000000020h],50h", 0xF2, 0x0F, 0xC2, 0x40, 0x20, 0x50 );

	// JMP
	_TEST32( "ebff jmp 00401001h", 0xeb, 0xff );
	// E9 cw JMP rel16 A N.S. Valid Jump near, relative, displacement relative to next instruction. Not supported in 64-bit mode.
	// E9 cd JMP rel32 A Valid Valid Jump near, relative, RIP = RIP + 32-bit displacement sign extended to 64-bits
	_TEST32( "e9ffff9090 jmp 90d11004h", 0xe9, 0xff,0xff, 0x90, 0x90 );
	_TEST32( "66e9ff90 jmp 0000a103h", 0x66, 0xe9, 0xff, 0x90 );
	// FF /4 JMP r/m16 B N.S. Valid Jump near, absolute indirect, address = zero-extended r/m16. Not supported in 64- bit mode.
	// FF /4 JMP r/m32 B N.S. Valid Jump near, absolute indirect, address given in r/m32. Not supported in 64-bit mode.
	// FF /4 JMP r/m64 B Valid N.E. Jump near, absolute indirect, RIP = 64-Bit offset from register or memory
	_TEST32( "ffe5 jmp ebp", 0xff, 0xe5, 0x01, 0x02, 0x03, 0x04 );
	_TEST32( "66ffe5 jmp bp", 0x66, 0xff, 0xe5, 0x01, 0x02 );

	/// TODO: Sprawdzi\E6 pod visualem, ppowino wykorzysta\E6 rejestr 8 bitory a nie 64 bitowy.
	_TEST64( "676640ffe5 jmp rbp", 0x67, 0x66, 0x40, 0xff, 0xe5, 0x01, 0x02 ); // 32 bit mode doesn't not allow REX.

	_TEST32( "ea112233445566 jmp far 6655h:44332211h", 0xEA, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66 );
	_TEST32( "66ea11223344 jmp far 4433h:2211h", 0x66, 0xEA, 0x11, 0x22, 0x33, 0x44 );

	// m16:16,m16:32,m16:64
	_TEST32( "ff6b01 jmp fword ptr [ebx+00000001h]", 0xFF, 0x6B, 0x01 );
	_TEST32( "66ff6b01 jmp dword ptr [ebx+00000001h]", 0x66, 0xFF, 0x6B, 0x01 );
	_TEST64( "6648ff6b01 jmp tbyte ptr [rbx+0000000000000001h]", 0x66, 0x48, 0xFF, 0x6B, 0x01 ); // Verified.
	_TEST64( "6640ff6b01 jmp dword ptr [rbx+0000000000000001h]", 0x66, 0x40, 0xFF, 0x6B, 0x01 ); // Verified.
	_TEST64( "676640ff6b01 jmp dword ptr [ebx+00000001h]", 0x67, 0x66, 0x40, 0xFF, 0x6B, 0x01 );
	_TEST64( "40ff6b01 jmp fword ptr [rbx+0000000000000001h]", 0x40, 0xFF, 0x6B, 0x01 );

	//{ NULL, 0x0001, 0x40C40000, { 0xE9, 0x00, 0x00 }, _IRA_OPERAND_IMMEDIATE_DIS_RELATIVE_EOSA, _IRA_NA, _IRA_NA, _IRA_NA },

	// Jcc.
	_TEST64( "6673ff jnc 0000800000401002h", 0x66, 0x73, 0xff );
	_TEST64( "666773ff jnc 0000800000401003h", 0x66, 0x67, 0x73, 0xff );
	_TEST64( "4873ff jnc 0000800000401002h", 0x48, 0x73, 0xff );
	_TEST32( "666773ff jnc 00001003h", 0x66, 0x67, 0x73, 0xff );
	_TEST32( "6773ff jnc 00401002h", 0x67, 0x73, 0xff );
	_TEST32( "73ff jnc 00401001h", 0x73, 0xff );

	// Przetestowac pod VS.
	_TEST64( "660f83ff0f0f01 jnc 00008000014f2006h", 0x66, 0x0f, 0x83, 0xff, 0x0f, 0x0f, 0x01 );
	_TEST64( "660f83010f0fff jnc 00007fffff4f1f08h", 0x66, 0x0f, 0x83, 0x01, 0x0f, 0x0f, 0xff );
	// operand size not 16 but 64 bits.
	_TEST64( "FAIL", 0x66, 0x67, 0x0f, 0x83, 0xff, 0xff );
	_TEST64( "66670f83ffffffff jnc 0000800000401007h", 0x66, 0x67, 0x0f, 0x83, 0xff, 0xff, 0xff, 0xff );
	_TEST64( "480f83ffffffff jnc 0000800000401006h", 0x48, 0x0f, 0x83, 0xff, 0xff, 0xff, 0xff );
	_TEST32( "66670f83ffff jnc 00001005h", 0x66, 0x67, 0x0f, 0x83, 0xff, 0xff );
	// operand size not 16 but 32.
	_TEST32( "FAIL", 0x67, 0x0f, 0x83, 0xff, 0xff );
	_TEST32( "670f83fff1fff1 jnc 0f2400206h", 0x67, 0x0f, 0x83, 0xff, 0xf1, 0xff, 0xf1 );
	_TEST32( "0f83ff335565 jnc 65954405h", 0x0f, 0x83, 0xff, 0x33, 0x55, 0x65 );

	// JCXZ
	_TEST64( "66e3ff jrcxz 0000800000401002h", 0x66, 0xe3, 0xff );
	_TEST64( "6667e3ff jecxz 0000800000401003h", 0x66, 0x67, 0xe3, 0xff );
	_TEST64( "48e3ff jrcxz 0000800000401002h", 0x48, 0xe3, 0xff );
	_TEST32( "6667e3ff jcxz 00001003h", 0x66, 0x67, 0xe3, 0xff );
	_TEST32( "67e3ff jcxz 00401002h", 0x67, 0xe3, 0xff );
	_TEST32( "e3ff jecxz 00401001h", 0xe3, 0xff );

	// CMOV
	_TEST32( "0f40a501020304 cmovo esp,dword ptr [ebp+04030201h]", 0x0f, 0x40, 0xa5, 0x01, 0x02, 0x03, 04 );
	_TEST32( "67660f40a50102 cmovo sp,word ptr [di+0201h]", 0x67, 0x66, 0x0f, 0x40, 0xa5, 0x01, 0x02 );
	_TEST32( "670f40a50102 cmovo esp,dword ptr [di+0201h]", 0x67, 0x0f, 0x40, 0xa5, 0x01, 0x02 );
	_TEST64( "4d0f40648901 cmovo r12,qword ptr [r9+rcx*4+0000000000000001h]", 0x4D, 0x0f, 0x40, 0x64, 0x89, 0x01 );

	_TEST32( "0f40a501020304 cmovo esp,dword ptr [ebp+04030201h]", 0x0f, 0x40, 0xa5, 0x01, 0x02, 0x03, 04 );
	_TEST32( "0f41a501020304 cmovno esp,dword ptr [ebp+04030201h]", 0x0f, 0x41, 0xa5, 0x01, 0x02, 0x03, 04 );
	_TEST32( "0f42a501020304 cmovc esp,dword ptr [ebp+04030201h]", 0x0f, 0x42, 0xa5, 0x01, 0x02, 0x03, 04 );
	_TEST32( "0f43a501020304 cmovnc esp,dword ptr [ebp+04030201h]", 0x0f, 0x43, 0xa5, 0x01, 0x02, 0x03, 04 );
	_TEST32( "0f44a501020304 cmove esp,dword ptr [ebp+04030201h]", 0x0f, 0x44, 0xa5, 0x01, 0x02, 0x03, 04 );
	_TEST32( "0f45a501020304 cmovne esp,dword ptr [ebp+04030201h]", 0x0f, 0x45, 0xa5, 0x01, 0x02, 0x03, 04 );
	_TEST32( "0f46a501020304 cmovbe esp,dword ptr [ebp+04030201h]", 0x0f, 0x46, 0xa5, 0x01, 0x02, 0x03, 04 );
	_TEST32( "0f47a501020304 cmovnbe esp,dword ptr [ebp+04030201h]", 0x0f, 0x47, 0xa5, 0x01, 0x02, 0x03, 04 );
	_TEST32( "0f48a501020304 cmovs esp,dword ptr [ebp+04030201h]", 0x0f, 0x48, 0xa5, 0x01, 0x02, 0x03, 04 );
	_TEST32( "0f49a501020304 cmovns esp,dword ptr [ebp+04030201h]", 0x0f, 0x49, 0xa5, 0x01, 0x02, 0x03, 04 );
	_TEST32( "0f4aa501020304 cmovp esp,dword ptr [ebp+04030201h]", 0x0f, 0x4a, 0xa5, 0x01, 0x02, 0x03, 04 );
	_TEST32( "0f4ba501020304 cmovnp esp,dword ptr [ebp+04030201h]", 0x0f, 0x4b, 0xa5, 0x01, 0x02, 0x03, 04 );
	_TEST32( "0f4ca501020304 cmovl esp,dword ptr [ebp+04030201h]", 0x0f, 0x4c, 0xa5, 0x01, 0x02, 0x03, 04 );
	_TEST32( "0f4da501020304 cmovnl esp,dword ptr [ebp+04030201h]", 0x0f, 0x4d, 0xa5, 0x01, 0x02, 0x03, 04 );
	_TEST32( "0f4ea501020304 cmovle esp,dword ptr [ebp+04030201h]", 0x0f, 0x4e, 0xa5, 0x01, 0x02, 0x03, 04 );
	_TEST32( "0f4fa501020304 cmovnle esp,dword ptr [ebp+04030201h]", 0x0f, 0x4f, 0xa5, 0x01, 0x02, 0x03, 04 );

	// CMC
	_TEST32( "f5 cmc", 0xf5 );
	_TEST64( "f5 cmc", 0xf5 );

	// CLTS.
	_TEST32( "0f06 clts", 0x0f, 0x06 );
	_TEST64( "0f06 clts", 0x0f, 0x06 );

	// CLFLUSH.
	_TEST32( "0fae7c1420 clflush byte ptr [esp+edx+00000020h]", 0x0F, 0xAE, 0x7C, 0x14, 0x20 );
	_TEST32( "660fae7c1420 clflush byte ptr [esp+edx+00000020h]", 0x66, 0x0F, 0xAE, 0x7C, 0x14, 0x20 );
	_TEST64( "0fae7c1420 clflush byte ptr [rsp+rdx+0000000000000020h]", 0x0F, 0xAE, 0x7C, 0x14, 0x20 );
	_TEST64( "660fae7c1420 clflush byte ptr [rsp+rdx+0000000000000020h]", 0x66, 0x0F, 0xAE, 0x7C, 0x14, 0x20 );
	_TEST64( "0fae7d01 clflush byte ptr [rbp+0000000000000001h]", 0x0F, 0xAE, 0x7D, 0x01 );

	// CLD.
	_TEST32( "fc cld", 0xfc );
	_TEST64( "fc cld", 0xfc );

	// CLD.
	_TEST32( "fc cld", 0xfc );
	_TEST64( "fc cld", 0xfc );

	// CLC.
	_TEST32( "f8 clc", 0xf8 );
	_TEST64( "f8 clc", 0xf8 );

	// CBW, CWDE, CDQE
	_TEST32( "6698 cbw", 0x66, 0x98 );
	_TEST32( "98 cwde", 0x98 );
	_TEST64( "4898 cdqe", 0x48, 0x98 );

	// CALL
	// m16:16,m16:32,m16:64
	_TEST32( "ff5b01 call fword ptr [ebx+00000001h]", 0xFF, 0x5B, 0x01 );
	_TEST32( "66ff5b01 call dword ptr [ebx+00000001h]", 0x66, 0xFF, 0x5B, 0x01 );
	_TEST64( "6648ff5b01 call tbyte ptr [rbx+0000000000000001h]", 0x66, 0x48, 0xFF, 0x5B, 0x01 ); // Verified.
	_TEST64( "6640ff5b01 call dword ptr [rbx+0000000000000001h]", 0x66, 0x40, 0xFF, 0x5B, 0x01 ); // Verified.
	_TEST64( "676640ff5b01 call dword ptr [ebx+00000001h]", 0x67, 0x66, 0x40, 0xFF, 0x5B, 0x01 );
	_TEST64( "40ff5b01 call fword ptr [rbx+0000000000000001h]", 0x40, 0xFF, 0x5B, 0x01 );
	// prt16:16 ptr16:32
	_TEST32( "9a112233445566 call far 6655h:44332211h", 0x9A, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66 );
	_TEST32( "669a11223344 call far 4433h:2211h", 0x66, 0x9A, 0x11, 0x22, 0x33, 0x44 );
	// r/m32
	_TEST32( "ff5701 call dword ptr [edi+00000001h]", 0xFF, 0x57, 0x01 );
	// r/m16
	_TEST32( "66ff5701 call word ptr [edi+00000001h]", 0x66, 0xFF, 0x57, 0x01 );
	// r/m64 (Size directives are the same for operand size 32 and 64 bits.)
	_TEST64( "6648ff5701 call qword ptr [rdi+0000000000000001h]", 0x66, 0x48, 0xFF, 0x57, 0x01 );
	// Look at the position of REX prefix, it has to fail.
	_TEST64( "FAIL", 0x48, 0x66, 0xFF, 0x57, 0x01 );
	_TEST64( "66ff5701 call qword ptr [rdi+0000000000000001h]", 0x66, 0xFF, 0x57, 0x01 );
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
	_TEST64( "4810a501020304 adc byte ptr [rbp+0000000004030201h],spl", 0x48, 0x10, 0xa5, 0x01, 0x02, 0x03, 04 );
	_TEST64( "481064a501 adc byte ptr [rbp+0000000000000001h],spl", 0x48, 0x10, 0x64, 0xa5, 0x01, 0x02, 0x03, 04 );
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
	_TEST64( "4812a501020304 adc spl,byte ptr [rbp+0000000004030201h]", 0x48, 0x12, 0xa5, 0x01, 0x02, 0x03, 04 );
	_TEST64( "481264a501 adc spl,byte ptr [rbp+0000000000000001h]", 0x48, 0x12, 0x64, 0xa5, 0x01, 0x02, 0x03, 04 );
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
	_TEST64( "4800a501020304 add byte ptr [rbp+0000000004030201h],spl", 0x48, 0x00, 0xa5, 0x01, 0x02, 0x03, 04 );
	_TEST64( "480064a501 add byte ptr [rbp+0000000000000001h],spl", 0x48, 0x00, 0x64, 0xa5, 0x01, 0x02, 0x03, 04 );
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
	_TEST64( "4802a501020304 add spl,byte ptr [rbp+0000000004030201h]", 0x48, 0x02, 0xa5, 0x01, 0x02, 0x03, 04 );
	_TEST64( "480264a501 add spl,byte ptr [rbp+0000000000000001h]", 0x48, 0x02, 0x64, 0xa5, 0x01, 0x02, 0x03, 04 );
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
	_TEST64( "4820a501020304 and byte ptr [rbp+0000000004030201h],spl", 0x48, 0x20, 0xa5, 0x01, 0x02, 0x03, 04 );
	_TEST64( "482064a501 and byte ptr [rbp+0000000000000001h],spl", 0x48, 0x20, 0x64, 0xa5, 0x01, 0x02, 0x03, 04 );
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
	_TEST64( "4822a501020304 and spl,byte ptr [rbp+0000000004030201h]", 0x48, 0x22, 0xa5, 0x01, 0x02, 0x03, 04 );
	_TEST64( "482264a501 and spl,byte ptr [rbp+0000000000000001h]", 0x48, 0x22, 0x64, 0xa5, 0x01, 0x02, 0x03, 04 );
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

void _test_vax(void) {
/*
	uint8_t code[] = {0xC4, 0xC4, 0x00};

	struct ira_disassemble_info info;
	info.address = code;
	info.size = sizeof(code);
	info.address_size_attribute = 0;
	info.operand_size_attribute = 0;
	info.config.flags = 0;
	info.config.flags |= _IRA_CF_ENABLE_VAX;
	info.mode = IRA_MOD_32BIT;

	info.instruction_pointer.eip = 0x00401000;

	struct ira_disassemble_result result;

	// Disassemble.
	ira_disassemble( &info, &result );
*/
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
		format.show_conditional_mnemonics_for_carry_flag = 1;
		format.conditional_suffix_group = 0;

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


