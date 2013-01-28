#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

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

void test_code( int isVEX, int is32, uint8_t code[], int size, char *mnemonic );

int main()
{
	ira_init();
	test();
	ira_deinit();

    return 0;
}


#define _TEST32(x,...) { uint8_t code[] = {__VA_ARGS__}; test_code( 0, 1, code, sizeof(code), x ); }
#define _TEST64(x,...) { uint8_t code[] = {__VA_ARGS__}; test_code( 0, 0, code, sizeof(code), x ); }
#define _TEST32_VEX(x,...) { uint8_t code[] = {__VA_ARGS__}; test_code( 1, 1, code, sizeof(code), x ); }
#define _TEST64_VEX(x,...) { uint8_t code[] = {__VA_ARGS__}; test_code( 1, 0, code, sizeof(code), x ); }

void _test_vax(void);

#include "ira_int.h"
/*
void __ira_test_xmm1_r_xmm2_rm( char *mnemonic, int n_args, ... ) {
	va_list ap;
	va_start(ap, n_args);
	int i = 0;
	for(i = 0; i < n_args; i++ ) {
		uint8_t opcode = va_arg(ap, uint8_t);
	}
	va_end(ap);
}*/




//102
void test(void) {

	// TODO: W tym przypadku powinno zdekodowa� do FAIL, a wybiera inna instrukcj� poniewa� instrukcja ta nie posiada mandatory opcodes.
	// Trzeba b�dzie jakos obs�ugiwa� instrukcje ktotre nie wymagaja manadatory opcode, zeby nie byly wybierane, jak
	// jakis mandatory opcode wystepuje.
	// _TEST32_VEX( "FAIL", 0xC5, 0xDF, 0x58, 0x14, 0x01 );
	//_test_vax();

	// VPMACSDD
	// VPMACSDD xmm1, xmm2, xmm3/mem128, xmm4 8F RXB.01000 0.src.0.00 9E /r ib
	_TEST32_VEX( "8fe8509e1401 vpmacsdd xmm2,xmm5,oword ptr [ecx+eax],xmm2", 0x8F, 0xE8, 0x50, 0x9E, 0x14, 0x01, 0x20 );
	_TEST64_VEX( "8fe8509ec0 vpmacsdd xmm0,xmm5,xmm0,xmm2", 0x8F, 0xE8, 0x50, 0x9E, 0xC0, 0x20 );

	// VPHSUBWD
	// VPHSUBWD xmm1, xmm2/mem128 8F RXB.01001 0.1111.0.00 E2 /r
	_TEST32_VEX( "8fe978e200 vphsubwd xmm0,oword ptr [eax]", 0x8F, 0xE9, 0x78, 0xE2, 0x00 );
	_TEST32_VEX( "8fe978e2c1 vphsubwd xmm0,xmm1", 0x8F, 0xE9, 0x78, 0xE2, 0xC1 );

	// VPHSUBDQ
	// VPHSUBDQ xmm1, xmm2/mem128 8F RXB.01001 0.1111.0.00 E3 /r
	_TEST32_VEX( "8fe978e300 vphsubdq xmm0,oword ptr [eax]", 0x8F, 0xE9, 0x78, 0xE3, 0x00 );
	_TEST32_VEX( "8fe978e3c1 vphsubdq xmm0,xmm1", 0x8F, 0xE9, 0x78, 0xE3, 0xC1 );

	// VPHSUBBW
	// VPHSUBBW xmm1, xmm2/mem128 8F RXB.01001 0.1111.0.00 E1 /r
	_TEST32_VEX( "8fe978e100 vphsubbw xmm0,oword ptr [eax]", 0x8F, 0xE9, 0x78, 0xE1, 0x00 );
	_TEST32_VEX( "8fe978e1c1 vphsubbw xmm0,xmm1", 0x8F, 0xE9, 0x78, 0xE1, 0xC1 );

	// VPHADDWQ
	// VPHADDWQ xmm1, xmm2/mem128 8F RXB.01001 0.1111.0.00 C7 /r
	_TEST32_VEX( "8fe978c700 vphaddwq xmm0,oword ptr [eax]", 0x8F, 0xE9, 0x78, 0xC7, 0x00 );
	_TEST32_VEX( "8fe978c7c1 vphaddwq xmm0,xmm1", 0x8F, 0xE9, 0x78, 0xC7, 0xC1 );

	// VPHADDWD
	// VPHADDWD xmm1, xmm2/mem128 8F RXB.01001 0.1111.0.00 C6 /r
	_TEST32_VEX( "8fe978c600 vphaddwd xmm0,oword ptr [eax]", 0x8F, 0xE9, 0x78, 0xC6, 0x00 );
	_TEST32_VEX( "8fe978c6c1 vphaddwd xmm0,xmm1", 0x8F, 0xE9, 0x78, 0xC6, 0xC1 );

	// VPHADDUWQ
	// VPHADDUWQ xmm1, xmm2/mem128 8F RXB.01001 0.1111.0.00 D7 /r
	_TEST32_VEX( "8fe978d700 vphadduwq xmm0,oword ptr [eax]", 0x8F, 0xE9, 0x78, 0xD7, 0x00 );
	_TEST32_VEX( "8fe978d7c1 vphadduwq xmm0,xmm1", 0x8F, 0xE9, 0x78, 0xD7, 0xC1 );

	// VPHADDUWD
	// VPHADDUWD xmm1, xmm2/mem128 8F RXB.01001 0.1111.0.00 D6 /r
	_TEST32_VEX( "8fe978d600 vphadduwd xmm0,oword ptr [eax]", 0x8F, 0xE9, 0x78, 0xD6, 0x00 );
	_TEST32_VEX( "8fe978d6c1 vphadduwd xmm0,xmm1", 0x8F, 0xE9, 0x78, 0xD6, 0xC1 );

	// VPHADDUDQ
	// VPHADDUDQ xmm1, xmm2/mem128 8F RXB.01001 0.1111.0.00 DB /r
	_TEST32_VEX( "8fe978db00 vphaddudq xmm0,oword ptr [eax]", 0x8F, 0xE9, 0x78, 0xDB, 0x00 );
	_TEST32_VEX( "8fe978dbc1 vphaddudq xmm0,xmm1", 0x8F, 0xE9, 0x78, 0xDB, 0xC1 );

	// VPHADDUBWD
	// VPHADDUBWD xmm1, xmm2/mem128 8F RXB.01001 0.1111.0.00 D1 /r
	_TEST32_VEX( "8fe978d100 vphaddubwd xmm0,oword ptr [eax]", 0x8F, 0xE9, 0x78, 0xD1, 0x00 );
	_TEST32_VEX( "8fe978d1c1 vphaddubwd xmm0,xmm1", 0x8F, 0xE9, 0x78, 0xD1, 0xC1 );

	// VPHADDUBQ
	// VPHADDUBQ xmm1, xmm2/mem128 8F RXB.01001 0.1111.0.00 D3 /r
	_TEST32_VEX( "8fe978d300 vphaddubq xmm0,oword ptr [eax]", 0x8F, 0xE9, 0x78, 0xD3, 0x00 );
	_TEST32_VEX( "8fe978d3c1 vphaddubq xmm0,xmm1", 0x8F, 0xE9, 0x78, 0xD3, 0xC1 );

	// VPHADDUBD
	// VPHADDUBD xmm1, xmm2/mem128 8F RXB.01001 0.1111.0.00 D2 /r
	_TEST32_VEX( "8fe978d200 vphaddubd xmm0,oword ptr [eax]", 0x8F, 0xE9, 0x78, 0xD2, 0x00 );
	_TEST32_VEX( "8fe978d2c1 vphaddubd xmm0,xmm1", 0x8F, 0xE9, 0x78, 0xD2, 0xC1 );

	// VPHADDDQ
	// VPHADDDQ xmm1, xmm2/mem128 8F RXB.01001 0.1111.0.00 CB /r
	_TEST32_VEX( "8fe978cb00 vphadddq xmm0,oword ptr [eax]", 0x8F, 0xE9, 0x78, 0xCB, 0x00 );
	_TEST32_VEX( "8fe978cbc1 vphadddq xmm0,xmm1", 0x8F, 0xE9, 0x78, 0xCB, 0xC1 );

	// VPHADDBQ
	// VPHADDBQ xmm1, xmm2/mem128 8F RXB.01001 0.1111.0.00 C3 /r
	_TEST32_VEX( "8fe978c300 vphaddbq xmm0,oword ptr [eax]", 0x8F, 0xE9, 0x78, 0xC3, 0x00 );
	_TEST32_VEX( "8fe978c3c1 vphaddbq xmm0,xmm1", 0x8F, 0xE9, 0x78, 0xC3, 0xC1 );

	// VPHADDBW
	// VPHADDBW xmm1, xmm2/mem128 8F RXB.01001 0.1111.0.00 C1 /r
	_TEST32_VEX( "8fe978c100 vphaddbw xmm0,oword ptr [eax]", 0x8F, 0xE9, 0x78, 0xC1, 0x00 );
	_TEST32_VEX( "8fe978c1c1 vphaddbw xmm0,xmm1", 0x8F, 0xE9, 0x78, 0xC1, 0xC1 );

	// VPHADDBD
	// VPHADDBD xmm1, xmm2/mem128 8F RXB.01001 0.1111.0.00 C2 /r
	_TEST32_VEX( "8fe978c200 vphaddbd xmm0,oword ptr [eax]", 0x8F, 0xE9, 0x78, 0xC2, 0x00 );
	_TEST32_VEX( "8fe978c2c1 vphaddbd xmm0,xmm1", 0x8F, 0xE9, 0x78, 0xC2, 0xC1 );

	//__ira_test_xmm1_r_xmm2_rm( "pmovsxbw", 0x66, 0x0F, 0x38, 0x20 );

	// VPCOMUB xmm1, xmm2, xmm3/mem128, imm8 8F RXB.01000 0.src.0.00 EC /r ib
	_TEST32_VEX( "8fe850ec140100 vpcomub xmm2,xmm5,oword ptr [ecx+eax],00h", 0x8F, 0xE8, 0x50, 0xEC, 0x14, 0x01, 0x00 );
	_TEST64_VEX( "8fe850ecc020 vpcomub xmm0,xmm5,xmm0,20h", 0x8F, 0xE8, 0x50, 0xEC, 0xC0, 0x20 );
	// VPCOMUD xmm1, xmm2, xmm3/mem128, imm8 8F RXB.01000 0.src.0.00 EE /r ib
	_TEST32_VEX( "8fe850ee140100 vpcomud xmm2,xmm5,oword ptr [ecx+eax],00h", 0x8F, 0xE8, 0x50, 0xEE, 0x14, 0x01, 0x00 );
	_TEST64_VEX( "8fe850eec020 vpcomud xmm0,xmm5,xmm0,20h", 0x8F, 0xE8, 0x50, 0xEE, 0xC0, 0x20 );
	// VPCOMUQ xmm1, xmm2, xmm3/mem128, imm8 8F RXB.01000 0.src.0.00 EF /r ib
	_TEST32_VEX( "8fe850ef140100 vpcomuq xmm2,xmm5,oword ptr [ecx+eax],00h", 0x8F, 0xE8, 0x50, 0xEF, 0x14, 0x01, 0x00 );
	_TEST64_VEX( "8fe850efc020 vpcomuq xmm0,xmm5,xmm0,20h", 0x8F, 0xE8, 0x50, 0xEF, 0xC0, 0x20 );
	// VPCOMUW xmm1, xmm2, xmm3/mem128, imm8 8F RXB.01000 0.src.0.00 ED /r ib
	_TEST32_VEX( "8fe850ed140100 vpcomuw xmm2,xmm5,oword ptr [ecx+eax],00h", 0x8F, 0xE8, 0x50, 0xED, 0x14, 0x01, 0x00 );
	_TEST64_VEX( "8fe850edc020 vpcomuw xmm0,xmm5,xmm0,20h", 0x8F, 0xE8, 0x50, 0xED, 0xC0, 0x20 );

	// VPCOMB
	// VPCOMB xmm1, xmm2, xmm3/mem128, imm8 8F RXB.01000 0.src.0.00 CC /r ib
	_TEST32_VEX( "8fe850cc140100 vpcomb xmm2,xmm5,oword ptr [ecx+eax],00h", 0x8F, 0xE8, 0x50, 0xCC, 0x14, 0x01, 0x00 );
	_TEST64_VEX( "8fe850ccc020 vpcomb xmm0,xmm5,xmm0,20h", 0x8F, 0xE8, 0x50, 0xCC, 0xC0, 0x20 );
	// VPCOMW xmm1, xmm2, xmm3/mem128, imm8 8F RXB.01000 0.src.0.00 CD /r ib
	_TEST32_VEX( "8fe850cd140100 vpcomw xmm2,xmm5,oword ptr [ecx+eax],00h", 0x8F, 0xE8, 0x50, 0xCD, 0x14, 0x01, 0x00 );
	_TEST64_VEX( "8fe850cdc020 vpcomw xmm0,xmm5,xmm0,20h", 0x8F, 0xE8, 0x50, 0xCD, 0xC0, 0x20 );
	// VPCOMD xmm1, xmm2, xmm3/mem128, imm8 8F RXB.01000 0.src.0.00 CE /r ib
	_TEST32_VEX( "8fe850ce140100 vpcomd xmm2,xmm5,oword ptr [ecx+eax],00h", 0x8F, 0xE8, 0x50, 0xCE, 0x14, 0x01, 0x00 );
	_TEST64_VEX( "8fe850cec020 vpcomd xmm0,xmm5,xmm0,20h", 0x8F, 0xE8, 0x50, 0xCE, 0xC0, 0x20 );
	// VPCOMQ xmm1, xmm2, xmm3/mem128, imm8 8F RXB.01000 0.src.0.00 CF /r ib
	_TEST32_VEX( "8fe850cf140100 vpcomq xmm2,xmm5,oword ptr [ecx+eax],00h", 0x8F, 0xE8, 0x50, 0xCF, 0x14, 0x01, 0x00 );
	_TEST64_VEX( "8fe850cfc020 vpcomq xmm0,xmm5,xmm0,20h", 0x8F, 0xE8, 0x50, 0xCF, 0xC0, 0x20 );

	// VPCMOV
	// VPCMOV xmm1, xmm2, xmm3/mem128, xmm4 8F RXB.01000 0.src.0.00 A2 /r ib
	// VPCMOV ymm1, ymm2, ymm3/mem256, ymm4 8F RXB.01000 0.src.1.00 A2 /r ib
	_TEST64_VEX( "8fe850a21401 vpcmov xmm2,xmm5,oword ptr [rcx+rax],xmm2", 0x8F, 0xE8, 0x50, 0xA2, 0x14, 0x01, 0x20 );
	_TEST64_VEX( "8fe854a21401 vpcmov ymm2,ymm5,ymmword ptr [rcx+rax],ymm2", 0x8F, 0xE8, 0x54, 0xA2, 0x14, 0x01, 0x20 );
	_TEST64_VEX( "8fe854a2c0 vpcmov ymm0,ymm5,ymm0,ymm2", 0x8F, 0xE8, 0x54, 0xA2, 0xC0, 0x20 );
	// VPCMOV xmm1, xmm2, xmm3, xmm4/mem128 8F RXB.01000 1.src.0.00 A2 /r ib
	// VPCMOV ymm1, ymm2, ymm3, ymm4/mem256 8F RXB.01000 1.src.1.00 A2 /r ib
	_TEST64_VEX( "8fe8d0a21401 vpcmov xmm2,xmm5,xmm2,oword ptr [rcx+rax]", 0x8F, 0xE8, 0xD0, 0xA2, 0x14, 0x01, 0x20 );
	_TEST64_VEX( "8fe8d4a21401 vpcmov ymm2,ymm5,ymm2,ymmword ptr [rcx+rax]", 0x8F, 0xE8, 0xD4, 0xA2, 0x14, 0x01, 0x20 );
	_TEST64_VEX( "8fe8d4a2c0 vpcmov ymm0,ymm5,ymm2,ymm0", 0x8F, 0xE8, 0xD4, 0xA2, 0xC0, 0x20 );

	// VFRCZSD xmm1,xmm2/mem64 8F RXB.01001 0.1111.0.00 83 /r
	_TEST32_VEX( "8fe9788300 vfrczsd xmm0,qword ptr [eax]", 0x8F, 0xE9, 0x78, 0x83, 0x00 );
	_TEST32_VEX( "8fe97883c1 vfrczsd xmm0,xmm1", 0x8F, 0xE9, 0x78, 0x83, 0xC1 );
	_TEST64_VEX( "8fe9788300 vfrczsd xmm0,qword ptr [rax]", 0x8F, 0xE9, 0x78, 0x83, 0x00 );
	_TEST64_VEX( "8fe97883c1 vfrczsd xmm0,xmm1", 0x8F, 0xE9, 0x78, 0x83, 0xC1 );

	// VFRCZSS xmm1, xmm2/mem32 8F RXB.01001 0.1111.0.00 82 /r
	_TEST32_VEX( "8fe9788200 vfrczss xmm0,dword ptr [eax]", 0x8F, 0xE9, 0x78, 0x82, 0x00 );
	_TEST32_VEX( "8fe97882c1 vfrczss xmm0,xmm1", 0x8F, 0xE9, 0x78, 0x82, 0xC1 );
	_TEST64_VEX( "8fe9788200 vfrczss xmm0,dword ptr [rax]", 0x8F, 0xE9, 0x78, 0x82, 0x00 );
	_TEST64_VEX( "8fe97882c1 vfrczss xmm0,xmm1", 0x8F, 0xE9, 0x78, 0x82, 0xC1 );

	// VFRCZPS
	// VFRCZPS xmm1, xmm2/mem128 8F RXB.01001 0.1111.0.00 80 /r
	// VFRCZPS ymm1, ymm2/mem256 8F RXB.01001 0.1111.1.00 80 /r
	_TEST32_VEX( "8fe9788000 vfrczps xmm0,oword ptr [eax]", 0x8F, 0xE9, 0x78, 0x80, 0x00 );
	_TEST32_VEX( "8fe97880c1 vfrczps xmm0,xmm1", 0x8F, 0xE9, 0x78, 0x80, 0xC1 );
	_TEST32_VEX( "8fe97c8000 vfrczps ymm0,ymmword ptr [eax]", 0x8F, 0xE9, 0x7C, 0x80, 0x00 );
	_TEST32_VEX( "8fe97c80c1 vfrczps ymm0,ymm1", 0x8F, 0xE9, 0x7C, 0x80, 0xC1 );
	_TEST64_VEX( "8fe9788000 vfrczps xmm0,oword ptr [rax]", 0x8F, 0xE9, 0x78, 0x80, 0x00 );
	_TEST64_VEX( "8fe97c8000 vfrczps ymm0,ymmword ptr [rax]", 0x8F, 0xE9, 0x7C, 0x80, 0x00 );

	// VFRCZPD
	// VFRCZPD xmm1, xmm2/mem128 8F RXB.01001 0.1111.0.00 81 /r
	// VFRCZPD ymm1, ymm2/mem256 8F RXB.01001 0.1111.1.00 81 /r
	_TEST32_VEX( "8fe9788100 vfrczpd xmm0,oword ptr [eax]", 0x8F, 0xE9, 0x78, 0x81, 0x00 );
	_TEST32_VEX( "8fe97881c1 vfrczpd xmm0,xmm1", 0x8F, 0xE9, 0x78, 0x81, 0xC1 );
	_TEST32_VEX( "8fe97c8100 vfrczpd ymm0,ymmword ptr [eax]", 0x8F, 0xE9, 0x7C, 0x81, 0x00 );
	_TEST32_VEX( "8fe97c81c1 vfrczpd ymm0,ymm1", 0x8F, 0xE9, 0x7C, 0x81, 0xC1 );
	_TEST64_VEX( "8fe9788100 vfrczpd xmm0,oword ptr [rax]", 0x8F, 0xE9, 0x78, 0x81, 0x00 );
	_TEST64_VEX( "8fe97c8100 vfrczpd ymm0,ymmword ptr [rax]", 0x8F, 0xE9, 0x7C, 0x81, 0x00 );

	// PADDQ
	// 0F D4 /r1 PADDQ mm1,mm2/m64
	_TEST64( "0fd400 paddq mm0,qword ptr [rax]", 0x0F, 0xD4, 0x00 );
	_TEST32( "0fd4c1 paddq mm0,mm1", 0x0F, 0xD4, 0xC1 );
	// 66 0F D4 /r PADDQ xmm1,xmm2/m128
	_TEST64( "660fd400 paddq xmm0,oword ptr [rax]", 0x66, 0x0F, 0xD4, 0x00 );
	_TEST32( "660fd4c1 paddq xmm0,xmm1", 0x66, 0x0F, 0xD4, 0xC1 );
	// VEX.NDS.128.66.0F.WIG D4 /r VPADDQ xmm1,xmm2,xmm3/m128
	_TEST64_VEX( "c4e179d400 vpaddq xmm0,xmm0,oword ptr [rax]", 0xC4, 0xE1, 0x79, 0xD4, 0x00 );
	_TEST32_VEX( "c4e179d4c1 vpaddq xmm0,xmm0,xmm1", 0xC4, 0xE1, 0x79, 0xD4, 0xC1 );

	// MOVNTSD
	// MOVNTSD mem64, xmm F2 0F 2B /r
	_TEST32( "f20f2b00 movntsd qword ptr [eax],xmm0", 0xF2, 0x0F, 0x2B, 0x00 );
	_TEST64( "f20f2b00 movntsd qword ptr [rax],xmm0", 0xF2, 0x0F, 0x2B, 0x00 );
	_TEST32( "FAIL", 0xF2, 0x0F, 0x2B, 0xC0 );

	// MOVNTSS
	// MOVNTSS mem32, xmm F3 0F 2B /r
	_TEST32( "f30f2b00 movntss dword ptr [eax],xmm0", 0xF3, 0x0F, 0x2B, 0x00 );
	_TEST64( "f30f2b00 movntss dword ptr [rax],xmm0", 0xF3, 0x0F, 0x2B, 0x00 );
	_TEST32( "FAIL", 0xF3, 0x0F, 0x2B, 0xC0 );

	// INSERTQ
	// INSERTQ xmm1, xmm2, imm8, imm8 F2 0F 78 /r ib ib
	_TEST32( "f20f78da0102 insertq xmm3,xmm2,01h,02h", 0xF2, 0x0F, 0x78, 0xDA, 0x01, 0x02 );
	_TEST64( "f20f78da0102 insertq xmm3,xmm2,01h,02h", 0xF2, 0x0F, 0x78, 0xDA, 0x01, 0x02 );
	// INSERTQ xmm1, xmm2 F2 0F 79 /r
	_TEST32( "f20f79da insertq xmm3,xmm2", 0xF2, 0x0F, 0x79, 0xDA );
	_TEST64( "f20f79da insertq xmm3,xmm2", 0xF2, 0x0F, 0x79, 0xDA );

	// EXTRQ
	// EXTRQ xmm1,imm8,imm8 66 0F 78 /0 ib ib
	_TEST32( "660f78c10102 extrq xmm1,01h,02h", 0x66, 0x0F, 0x78, 0xC1, 0x01, 0x02 );
	_TEST32( "660f78c20102 extrq xmm2,01h,02h", 0x66, 0x0F, 0x78, 0xC2, 0x01, 0x02 );
	_TEST64( "660f78c10102 extrq xmm1,01h,02h", 0x66, 0x0F, 0x78, 0xC1, 0x01, 0x02 );
	_TEST64( "660f78c20102 extrq xmm2,01h,02h", 0x66, 0x0F, 0x78, 0xC2, 0x01, 0x02 );
	// EXTRQ xmm1,xmm2 66 0F 79 /r
	_TEST32( "660f79c5 extrq xmm0,xmm5", 0x66, 0x0F, 0x79, 0xC5 );
	_TEST32( "660f79e1 extrq xmm4,xmm1", 0x66, 0x0F, 0x79, 0xE1 );
	_TEST64( "660f79c5 extrq xmm0,xmm5", 0x66, 0x0F, 0x79, 0xC5 );
	_TEST64( "660f79e1 extrq xmm4,xmm1", 0x66, 0x0F, 0x79, 0xE1 );

	// VMSAVE
	// VMSAVE rAX 0F 01 DB Save additional guest state to VMCB.
	_TEST32_VEX( "0f01db vmsave eax", 0x0F, 0x01, 0xDB );
	_TEST32_VEX( "670f01db vmsave ax", 0x67, 0x0F, 0x01, 0xDB );
	_TEST64_VEX( "0f01db vmsave rax", 0x0F, 0x01, 0xDB );
	_TEST64_VEX( "670f01db vmsave eax", 0x67, 0x0F, 0x01, 0xDB );

	// VMRUN
	// VMRUN rAX 0F 01 D8 Performs a world-switch to guest.
	_TEST32_VEX( "0f01d8 vmrun eax", 0x0F, 0x01, 0xD8 );
	_TEST32_VEX( "670f01d8 vmrun ax", 0x67, 0x0F, 0x01, 0xD8 );
	_TEST64_VEX( "0f01d8 vmrun rax", 0x0F, 0x01, 0xD8 );
	_TEST64_VEX( "670f01d8 vmrun eax", 0x67, 0x0F, 0x01, 0xD8 );

	// VMMCALL
	// VMMCALL 0F 01 D9 Explicit communication with the VMM.
	_TEST32_VEX( "0f01d9 vmmcall", 0x0F, 0x01, 0xD9 );
	_TEST64_VEX( "0f01d9 vmmcall", 0x0F, 0x01, 0xD9 );

	// VMLOAD
	// VMLOAD rAX 0F 01 DA Load additional state from VMCB.
	_TEST32_VEX( "0f01da vmload eax", 0x0F, 0x01, 0xDA );
	_TEST32_VEX( "670f01da vmload ax", 0x67, 0x0F, 0x01, 0xDA );
	_TEST64_VEX( "0f01da vmload rax", 0x0F, 0x01, 0xDA );
	_TEST64_VEX( "670f01da vmload eax", 0x67, 0x0F, 0x01, 0xDA );

	// STGI
	// STGI 0F 01 DC Sets the global interrupt flag (GIF)
	_TEST32_VEX( "0f01dc stgi", 0x0F, 0x01, 0xDC );
	_TEST64_VEX( "0f01dc stgi", 0x0F, 0x01, 0xDC );

	// SKINIT
	// SKINIT EAX 0F 01 DE Secure initialization and jump, with attestation.
	_TEST32_VEX( "0f01de skinit eax", 0x0F, 0x01, 0xDE );
	_TEST64_VEX( "0f01de skinit eax", 0x0F, 0x01, 0xDE );

	// INVLPGA
	// INVLPGA rAX, ECX 0F 01 DF
	_TEST32_VEX( "0f01df invlpga eax,ecx", 0x0F, 0x01, 0xDF );
	_TEST32_VEX( "670f01df invlpga ax,ecx", 0x67, 0x0F, 0x01, 0xDF );
	_TEST64_VEX( "0f01df invlpga rax,ecx", 0x0F, 0x01, 0xDF );
	_TEST64_VEX( "670f01df invlpga eax,ecx", 0x67, 0x0F, 0x01, 0xDF );

	// CLGI
	// CLGI 0F 01 DD Clears the global interrupt flag (GIF).
	_TEST32_VEX( "0f01dd clgi", 0x0F, 0x01, 0xDD );
	_TEST32_VEX( "0f01dd clgi", 0x0F, 0x01, 0xDD );

	// TZMSK
	// TZMSK reg32, reg/mem32 8F RXB.09 0.dest.0.00 01 /4
	_TEST32_VEX( "8fe9600120 tzmsk ebx,dword ptr [eax]", 0x8F, 0xE9, 0x60, 0x01, 0x20 );
	_TEST32_VEX( "8fe96001e0 tzmsk ebx,eax", 0x8F, 0xE9, 0x60, 0x01, 0xE0 );
	// TZMSK reg64, reg/mem64 8F RXB.09 1.dest.0.00 01 /4
	_TEST32_VEX( "8fe9e00120 tzmsk rbx,qword ptr [eax]", 0x8F, 0xE9, 0xE0, 0x01, 0x20 );
	_TEST32_VEX( "8fe9e001e0 tzmsk rbx,rax", 0x8F, 0xE9, 0xE0, 0x01, 0xE0 );

	// T1MSKC
	// T1MSKC reg32, reg/mem32 8F RXB.09 0.dest.0.00 01 /7
	_TEST32_VEX( "8fe9600138 t1mskc ebx,dword ptr [eax]", 0x8F, 0xE9, 0x60, 0x01, 0x38 );
	_TEST32_VEX( "8fe96001f8 t1mskc ebx,eax", 0x8F, 0xE9, 0x60, 0x01, 0xF8 );
	// T1MSKC reg64, reg/mem64 8F RXB.09 1.dest.0.00 01 /7
	_TEST32_VEX( "8fe9e00138 t1mskc rbx,qword ptr [eax]", 0x8F, 0xE9, 0xE0, 0x01, 0x38 );
	_TEST32_VEX( "8fe9e001f8 t1mskc rbx,rax", 0x8F, 0xE9, 0xE0, 0x01, 0xF8 );

	// SLWPCB
	// SLWPCB reg32 8F RXB.09 0.1111.0.00 12 /1
	_TEST32_VEX( "8fe96012c8 slwpcb eax", 0x8F, 0xE9, 0x60, 0x12, 0xC8 );
	// SLWPCB reg64 8F RXB.09 1.1111.0.00 12 /1
	_TEST32_VEX( "8fe96012c8 slwpcb eax", 0x8F, 0xE9, 0x60, 0x12, 0xC8 );

	// LWPVAL
	// LWPVAL reg32.vvvv, reg/mem32, imm32 8F RXB.0A 0.src1.0.00 12 /1 /imm32
	_TEST32_VEX( "8fea60120800112233 lwpval ebx,dword ptr [eax],33221100h", 0x8F, 0xEA, 0x60, 0x12, 0x08, 0x00, 0x11, 0x22, 0x33 );
	_TEST32_VEX( "8fea6012c800112233 lwpval ebx,eax,33221100h", 0x8F, 0xEA, 0x60, 0x12, 0xC8, 0x00, 0x11, 0x22, 0x33 );
	// LWPVAL reg64.vvvv, reg/mem32, imm32 8F RXB.0A 1.src1.0.00 12 /1 /imm32
	_TEST32_VEX( "8feae0120800112233 lwpval rbx,qword ptr [eax],33221100h", 0x8F, 0xEA, 0xE0, 0x12, 0x08, 0x00, 0x11, 0x22, 0x33 );
	_TEST32_VEX( "8feae012c800112233 lwpval rbx,rax,33221100h", 0x8F, 0xEA, 0xE0, 0x12, 0xC8, 0x00, 0x11, 0x22, 0x33 );

	// LWPINS
	// LWPINS reg32.vvvv, reg/mem32, imm32 8F RXB.0A 0.src1.0.00 12 /0 /imm32
	_TEST32_VEX( "8fea60120000112233 lwpins ebx,dword ptr [eax],33221100h", 0x8F, 0xEA, 0x60, 0x12, 0x00, 0x00, 0x11, 0x22, 0x33 );
	_TEST32_VEX( "8fea6012c000112233 lwpins ebx,eax,33221100h", 0x8F, 0xEA, 0x60, 0x12, 0xC0, 0x00, 0x11, 0x22, 0x33 );
	// LWPINS reg64.vvvv, reg/mem32, imm32 8F RXB.0A 1.src1.0.00 12 /0 /imm32
	_TEST32_VEX( "8feae0120000112233 lwpins rbx,qword ptr [eax],33221100h", 0x8F, 0xEA, 0xE0, 0x12, 0x00, 0x00, 0x11, 0x22, 0x33 );
	_TEST32_VEX( "8feae012c000112233 lwpins rbx,rax,33221100h", 0x8F, 0xEA, 0xE0, 0x12, 0xC0, 0x00, 0x11, 0x22, 0x33 );

	// LLWPCB
	// LLWPCB reg32 8F RXB.09 0.1111.0.00 12 /0
	_TEST32_VEX( "8fe96012c0 llwpcb eax", 0x8F, 0xE9, 0x60, 0x12, 0xC0 );
	// LLWPCB reg64 8F RXB.09 1.1111.0.00 12 /0
	_TEST32_VEX( "8fe9e012c0 llwpcb rax", 0x8F, 0xE9, 0xE0, 0x12, 0xC0 );

	// BLSIC
	// BLSIC reg32, reg/mem32 8F RXB.09 0.dest.0.00 01 /6
	_TEST32_VEX( "8fe9600130 blsic ebx,dword ptr [eax]", 0x8F, 0xE9, 0x60, 0x01, 0x30 );
	_TEST32_VEX( "8fe96001f0 blsic ebx,eax", 0x8F, 0xE9, 0x60, 0x01, 0xF0 );
	// BLSIC reg64, reg/mem64 8F RXB.09 1.dest.0.00 01 /6
	_TEST32_VEX( "8fe9e00130 blsic rbx,qword ptr [eax]", 0x8F, 0xE9, 0xE0, 0x01, 0x30 );
	_TEST32_VEX( "8fe9e001f0 blsic rbx,rax", 0x8F, 0xE9, 0xE0, 0x01, 0xF0 );

	// BLSFILL
	// BLSFILL reg32, reg/mem32 8F RXB.09 0.dest.0.00 01 /2
	_TEST32_VEX( "8fe9600110 blsfill ebx,dword ptr [eax]", 0x8F, 0xE9, 0x60, 0x01, 0x10 );
	_TEST32_VEX( "8fe96001d0 blsfill ebx,eax", 0x8F, 0xE9, 0x60, 0x01, 0xD0 );
	// BLSFILL reg64, reg/mem64 8F RXB.09 1.dest.0.00 01 /2
	_TEST32_VEX( "8fe9e00110 blsfill rbx,qword ptr [eax]", 0x8F, 0xE9, 0xE0, 0x01, 0x10 );
	_TEST32_VEX( "8fe9e001d0 blsfill rbx,rax", 0x8F, 0xE9, 0xE0, 0x01, 0xD0 );

	// BLCS
	// BLCS reg32, reg/mem32 8F RXB.09 0.dest.0.00 01 /3
	_TEST32_VEX( "8fe9600118 blcs ebx,dword ptr [eax]", 0x8F, 0xE9, 0x60, 0x01, 0x18 );
	_TEST32_VEX( "8fe96001d8 blcs ebx,eax", 0x8F, 0xE9, 0x60, 0x01, 0xD8 );
	// BLCS reg64, reg/mem64 8F RXB.09 1.dest.0.00 01 /3
	_TEST32_VEX( "8fe9e00118 blcs rbx,qword ptr [eax]", 0x8F, 0xE9, 0xE0, 0x01, 0x18 );
	_TEST32_VEX( "8fe9e001d8 blcs rbx,rax", 0x8F, 0xE9, 0xE0, 0x01, 0xD8 );

	// BLCMSK
	// BLCMSK reg32, reg/mem32 8F RXB.09 0.dest.0.00 02 /1
	_TEST32_VEX( "8fe9600208 blcmsk ebx,dword ptr [eax]", 0x8F, 0xE9, 0x60, 0x02, 0x08 );
	_TEST32_VEX( "8fe96002c8 blcmsk ebx,eax", 0x8F, 0xE9, 0x60, 0x02, 0xC8 );
	// BLCMSK reg64, reg/mem64 8F RXB.09 1.dest.0.00 02 /1
	_TEST32_VEX( "8fe9e00208 blcmsk rbx,qword ptr [eax]", 0x8F, 0xE9, 0xE0, 0x02, 0x08 );
	_TEST32_VEX( "8fe9e002c8 blcmsk rbx,rax", 0x8F, 0xE9, 0xE0, 0x02, 0xC8 );

	// BLCIC
	// BLCIC reg32, reg/mem32 8F RXB.09 0.dest.0.00 01 /5
	_TEST32_VEX( "8fe9600128 blcic ebx,dword ptr [eax]", 0x8F, 0xE9, 0x60, 0x01, 0x28 );
	_TEST32_VEX( "8fe96001e8 blcic ebx,eax", 0x8F, 0xE9, 0x60, 0x01, 0xE8 );
	// BLCIC reg64, reg/mem64 8F RXB.09 1.dest.0.00 01 /5
	_TEST32_VEX( "8fe9e00128 blcic rbx,qword ptr [eax]", 0x8F, 0xE9, 0xE0, 0x01, 0x28 );
	_TEST32_VEX( "8fe9e001e8 blcic rbx,rax", 0x8F, 0xE9, 0xE0, 0x01, 0xE8 );

	// BLCI
	// BLCI reg32, reg/mem32 8F RXB.09 0.dest.0.00 02 /6
	_TEST32_VEX( "8fe9600230 blci ebx,dword ptr [eax]", 0x8F, 0xE9, 0x60, 0x02, 0x30 );
	_TEST32_VEX( "8fe96002f0 blci ebx,eax", 0x8F, 0xE9, 0x60, 0x02, 0xF0 );
	// BLCI reg64, reg/mem64 8F RXB.09 1.dest.0.00 02 /6
	_TEST32_VEX( "8fe9e00230 blci rbx,qword ptr [eax]", 0x8F, 0xE9, 0xE0, 0x02, 0x30 );
	_TEST32_VEX( "8fe9e002f0 blci rbx,rax", 0x8F, 0xE9, 0xE0, 0x02, 0xF0 );

	// BEXTR
	// BEXTR reg32, reg/mem32, imm32 8F RXB.0A 0.1111.0.00 10 /r /id
	_TEST32_VEX( "8fea78100001020304 bextr eax,dword ptr [eax],04030201h", 0x8F, 0xEA, 0x78, 0x10, 0x00, 0x01, 0x02, 0x03, 0x04 );
	_TEST32_VEX( "8fea7810c001020304 bextr eax,eax,04030201h", 0x8F, 0xEA, 0x78, 0x10, 0xC0, 0x01, 0x02, 0x03, 0x04 );
	// BEXTR reg64, reg/mem64, imm32 8F RXB.0A 1.1111.0.00 10 /r /id
	_TEST64_VEX( "8feaf8100001020304 bextr rax,qword ptr [rax],04030201h", 0x8F, 0xEA, 0xF8, 0x10, 0x00, 0x01, 0x02, 0x03, 0x04 );
	_TEST64_VEX( "8feaf810c001020304 bextr rax,rax,04030201h", 0x8F, 0xEA, 0xF8, 0x10, 0xC0, 0x01, 0x02, 0x03, 0x04 );

	// BLCFILL
	// BLCFILL reg32, reg/mem32 8F RXB.09 0.dest.0.00 01 /1
	_TEST32_VEX( "8fe9600108 blcfill ebx,dword ptr [eax]", 0x8F, 0xE9, 0x60, 0x01, 0x08 );
	_TEST32_VEX( "8fe96001c8 blcfill ebx,eax", 0x8F, 0xE9, 0x60, 0x01, 0xC8 );
	// BLCFILL reg64, reg/mem64 8F RXB.09 1.dest.0.00 01 /1
	_TEST32_VEX( "8fe9e00108 blcfill rbx,qword ptr [eax]", 0x8F, 0xE9, 0xE0, 0x01, 0x08 );
	_TEST32_VEX( "8fe9e001c8 blcfill rbx,rax", 0x8F, 0xE9, 0xE0, 0x01, 0xC8 );

	// ADCX
	// 66 0F 38 F6 /r ADCX r32, r/m32
	// REX.W + 66 0F 38 F6 /r ADCX r64,r/m64
	_TEST32( "660f38f600 adcx eax,dword ptr [eax]", 0x66, 0x0F, 0x38, 0xF6, 0x00 );
	_TEST64( "660f38f600 adcx eax,dword ptr [rax]", 0x66, 0x0F, 0x38, 0xF6, 0x00 );
	_TEST64( "66480f38f600 adcx rax,qword ptr [rax]", 0x66, 0x48, 0x0F, 0x38, 0xF6, 0x00 );

	// ADOX
	// F3 0F 38 F6 /r ADOX r32, r/m32
	// REX.w + F3 0F 38 F6 /r ADOX r64, r/m64
	_TEST32( "f30f38f600 adox eax,dword ptr [eax]", 0xF3, 0x0F, 0x38, 0xF6, 0x00 );
	_TEST64( "f30f38f600 adox eax,dword ptr [rax]", 0xF3, 0x0F, 0x38, 0xF6, 0x00 );
	_TEST64( "f3480f38f600 adox rax,qword ptr [rax]", 0xF3, 0x48, 0x0F, 0x38, 0xF6, 0x00 );

	// RDSEED
	// 0F C7 /7 RDSEED r16
	_TEST32( "660fc7f8 rdseed ax", 0x66, 0x0F, 0xC7, 0xF8 );
	_TEST64( "660fc7f8 rdseed ax", 0x66, 0x0F, 0xC7, 0xF8 );
	// 0F C7 /7 RDSEED r32
	_TEST32( "0fc7f8 rdseed eax", 0x0F, 0xC7, 0xF8 );
	_TEST64( "0fc7f8 rdseed eax", 0x0F, 0xC7, 0xF8 );
	// REX.W + 0F C7 /7 RDSEED r64
	_TEST64( "480fc7f8 rdseed rax", 0x48, 0x0F, 0xC7, 0xF8 );

	// 0F 01 CA CLAC
	_TEST32( "0f01ca clac", 0x0F, 0x01, 0xCA );
	_TEST64( "0f01ca clac", 0x0F, 0x01, 0xCA );

	// 0F 01 CB STAC
	_TEST32( "0f01cb stac", 0x0F, 0x01, 0xCB );
	_TEST64( "0f01cb stac", 0x0F, 0x01, 0xCB );

	// HLE

	// C6 F8 ib XABORT imm8
	_TEST32( "c6f820 xabort 20h", 0xC6, 0xF8, 0x20 );
	_TEST64( "c6f820 xabort 20h", 0xC6, 0xF8, 0x20 );

	// C7 F8 XBEGIN rel16
	// C7 F8 XBEGIN rel32
	_TEST32( "66c7f82040 xbegin 00005025h", 0x66, 0xC7, 0xF8, 0x20, 0x40 );
	_TEST64( "c7f820201010 xbegin 10503026h", 0xC7, 0xF8, 0x20, 0x20, 0x10, 0x10 );
	_TEST64( "48c7f820201010 xbegin 0000800010503027h", 0x48, 0xC7, 0xF8, 0x20, 0x20, 0x10, 0x10 );

	// 0F 01 D5 XEND
	_TEST32( "0f01d5 xend", 0x0F, 0x01, 0xD5 );
	_TEST64( "0f01d5 xend", 0x0F, 0x01, 0xD5 );

	// 0F 01 D6 XTEST
	_TEST32( "0f01d6 xtest", 0x0F, 0x01, 0xD6 );
	_TEST64( "0f01d6 xtest", 0x0F, 0x01, 0xD6 );

	// VEX GPR

	// TZCNT
	// F3 0F BC /r TZCNT r16, r/m16
	// F3 0F BC /r TZCNT r32, r/m32
	// REX.W + F3 0F BC /r TZCNT r64, r/m64
	_TEST32( "f30fbc00 tzcnt eax,dword ptr [eax]", 0xF3, 0x0F, 0xBC, 0x00 );
	_TEST32( "66f30fbc00 tzcnt ax,word ptr [eax]", 0x66, 0xF3, 0x0F, 0xBC, 0x00 );
	_TEST32( "66f30fbcc0 tzcnt ax,ax", 0x66, 0xF3, 0x0F, 0xBC, 0xC0 );
	_TEST64( "f3480fbc00 tzcnt rax,qword ptr [rax]", 0xF3, 0x48, 0x0F, 0xBC, 0x00 );

	// VEX.NDS1.LZ.66.0F38.W0 F7 /r SHLX r32a, r/m32, r32b
	// VEX.NDS1.LZ.66.0F38.W1 F7 /r SHLX r64a, r/m64, r64b
	_TEST32_VEX( "c4e241f700 shlx eax,dword ptr [eax],edi", 0xC4, 0xE2, 0x41, 0xF7, 0x00 );
	_TEST32_VEX( "c4e241f7c0 shlx eax,eax,edi", 0xC4, 0xE2, 0x41, 0xF7, 0xC0 );
	_TEST32_VEX( "c4e2c1f700 shlx rax,qword ptr [eax],rdi", 0xC4, 0xE2, 0xC1, 0xF7, 0x00 );
	_TEST32_VEX( "c4e2c1f7c0 shlx rax,rax,rdi", 0xC4, 0xE2, 0xC1, 0xF7, 0xC0 );
	// VEX.NDS1.LZ.F2.0F38.W0 F7 /r SHRX r32a, r/m32, r32b
	// VEX.NDS1.LZ.F2.0F38.W1 F7 /r SHRX r64a, r/m64, r64b
	_TEST32_VEX( "c4e243f700 shrx eax,dword ptr [eax],edi", 0xC4, 0xE2, 0x43, 0xF7, 0x00 );
	_TEST32_VEX( "c4e243f7c0 shrx eax,eax,edi", 0xC4, 0xE2, 0x43, 0xF7, 0xC0 );
	_TEST32_VEX( "c4e2c3f700 shrx rax,qword ptr [eax],rdi", 0xC4, 0xE2, 0xC3, 0xF7, 0x00 );
	_TEST32_VEX( "c4e2c3f7c0 shrx rax,rax,rdi", 0xC4, 0xE2, 0xC3, 0xF7, 0xC0 );
	// VEX.NDS1.LZ.F3.0F38.W0 F7 /r SARX r32a, r/m32, r32b
	// VEX.NDS1.LZ.F3.0F38.W1 F7 /r SARX r64a, r/m64, r64b
	_TEST32_VEX( "c4e242f700 sarx eax,dword ptr [eax],edi", 0xC4, 0xE2, 0x42, 0xF7, 0x00 );
	_TEST32_VEX( "c4e242f7c0 sarx eax,eax,edi", 0xC4, 0xE2, 0x42, 0xF7, 0xC0 );
	_TEST32_VEX( "c4e2c2f700 sarx rax,qword ptr [eax],rdi", 0xC4, 0xE2, 0xC2, 0xF7, 0x00 );
	_TEST32_VEX( "c4e2c2f7c0 sarx rax,rax,rdi", 0xC4, 0xE2, 0xC2, 0xF7, 0xC0 );

	// RORX
	// VEX.LZ.F2.0F3A.W0 F0 /r ib RORX r32, r/m32, imm8
	_TEST32_VEX( "c4e243f00001 rorx eax,dword ptr [eax],01h", 0xC4, 0xE2, 0x43, 0xF0, 0x00, 0x01 );
	_TEST32_VEX( "c4e243f0c001 rorx eax,eax,01h", 0xC4, 0xE2, 0x43, 0xF0, 0xC0, 0x01 );
	// VEX.LZ.F2.0F3A.W1 F0 /r ib RORX r64, r/m64, imm8
	_TEST32_VEX( "c4e2c3f00001 rorx rax,qword ptr [eax],01h", 0xC4, 0xE2, 0xC3, 0xF0, 0x00, 0x01 );
	_TEST32_VEX( "c4e2c3f0c001 rorx rax,rax,01h", 0xC4, 0xE2, 0xC3, 0xF0, 0xC0, 0x01 );

	// PEXT
	// VEX.NDS.LZ.F3.0F38.W0 F5 /r PEXT r32a, r32b, r/m32
	_TEST32_VEX( "c4e242f500 pext eax,edi,dword ptr [eax]", 0xC4, 0xE2, 0x42, 0xF5, 0x00 );
	_TEST32_VEX( "c4e242f5c0 pext eax,edi,eax", 0xC4, 0xE2, 0x42, 0xF5, 0xC0 );
	// VEX.NDS.LZ.F3.0F38.W1 F5 /r PEXT r64a, r64b, r/m64
	_TEST32_VEX( "c4e2c2f500 pext rax,rdi,qword ptr [eax]", 0xC4, 0xE2, 0xC2, 0xF5, 0x00 );
	_TEST32_VEX( "c4e2c2f5c0 pext rax,rdi,rax", 0xC4, 0xE2, 0xC2, 0xF5, 0xC0 );

	// PDEP
	// VEX.NDS.LZ.F2.0F38.W0 F5 /r PDEP r32a, r32b, r/m32
	_TEST32_VEX( "c4e243f500 pdep eax,edi,dword ptr [eax]", 0xC4, 0xE2, 0x43, 0xF5, 0x00 );
	_TEST32_VEX( "c4e243f5c0 pdep eax,edi,eax", 0xC4, 0xE2, 0x43, 0xF5, 0xC0 );
	// VEX.NDS.LZ.F2.0F38.W1 F5 /r PDEP r64a, r64b, r/m64
	_TEST32_VEX( "c4e2c3f500 pdep rax,rdi,qword ptr [eax]", 0xC4, 0xE2, 0xC3, 0xF5, 0x00 );
	_TEST32_VEX( "c4e2c3f5c0 pdep rax,rdi,rax", 0xC4, 0xE2, 0xC3, 0xF5, 0xC0 );

	// MULX
	// VEX.NDD.LZ.F2.0F38.W0 F6 /r MULX r32a, r32b, r/m32
	_TEST32_VEX( "c4e243f600 mulx eax,edi,dword ptr [eax]", 0xC4, 0xE2, 0x43, 0xF6, 0x00 );
	_TEST32_VEX( "c4e243f6c0 mulx eax,edi,eax", 0xC4, 0xE2, 0x43, 0xF6, 0xC0 );
	// VEX.NDD.LZ.F2.0F38.W1 F6 /r MULX r64a, r64b, r/m64
	_TEST32_VEX( "c4e2c3f600 mulx rax,rdi,qword ptr [eax]", 0xC4, 0xE2, 0xC3, 0xF6, 0x00 );
	_TEST32_VEX( "c4e2c3f6c0 mulx rax,rdi,rax", 0xC4, 0xE2, 0xC3, 0xF6, 0xC0 );

	// LZCNT
	// F3 0F BD /r LZCNT r16,r/m16
	// F3 0F BD /r LZCNT r32,r/m32
	// REX.W + F3 0F BD /r LZCNT r64,r/m64
	_TEST32( "f30fbd00 lzcnt eax,dword ptr [eax]", 0xF3, 0x0F, 0xBD, 0x00 );
	_TEST32( "66f30fbd00 lzcnt ax,word ptr [eax]", 0x66, 0xF3, 0x0F, 0xBD, 0x00 );
	_TEST32( "66f30fbdc0 lzcnt ax,ax", 0x66, 0xF3, 0x0F, 0xBD, 0xC0 );
	_TEST64( "f3480fbd00 lzcnt rax,qword ptr [rax]", 0xF3, 0x48, 0x0F, 0xBD, 0x00 );

	// BZHI
	// VEX.NDS1.LZ.0F38.W0 F5 /r BZHI r32a, r/m32, r32b
	_TEST32_VEX( "c4e240f500 bzhi eax,dword ptr [eax],edi", 0xC4, 0xE2, 0x40, 0xF5, 0x00 );
	_TEST32_VEX( "c4e240f5c0 bzhi eax,eax,edi", 0xC4, 0xE2, 0x40, 0xF5, 0xC0 );
	// VEX.NDS1.LZ.0F38.W1 F5 /r BZHI r64a, r/m64, r64b
	_TEST32_VEX( "c4e2c0f500 bzhi rax,qword ptr [eax],rdi", 0xC4, 0xE2, 0xC0, 0xF5, 0x00 );
	_TEST32_VEX( "c4e2c0f5c0 bzhi rax,rax,rdi", 0xC4, 0xE2, 0xC0, 0xF5, 0xC0 );

	// BLSR
	// VEX.NDD.LZ.0F38.W0 F3 /1 BLSR r32, r/m32
	_TEST32_VEX( "c4e240f308 blsr edi,dword ptr [eax]", 0xC4, 0xE2, 0x40, 0xF3, 0x08 );
	_TEST32_VEX( "c4e240f3c8 blsr edi,eax", 0xC4, 0xE2, 0x40, 0xF3, 0xC8 );
	// VEX.NDD.LZ.0F38.W1 F3 /1 BLSR r64, r/m64
	_TEST32_VEX( "c4e2c0f308 blsr rdi,qword ptr [eax]", 0xC4, 0xE2, 0xC0, 0xF3, 0x08 );
	_TEST32_VEX( "c4e2c0f3c8 blsr rdi,rax", 0xC4, 0xE2, 0xC0, 0xF3, 0xC8 );

	// BLSMSK
	// VEX.NDD.LZ.0F38.W0 F3 /2 BLSMSK r32, r/m32
	_TEST32_VEX( "c4e240f310 blsmsk edi,dword ptr [eax]", 0xC4, 0xE2, 0x40, 0xF3, 0x10 );
	_TEST32_VEX( "c4e240f3d0 blsmsk edi,eax", 0xC4, 0xE2, 0x40, 0xF3, 0xD0 );
	// VEX.NDD.LZ.0F38.W1 F3 /2 BLSMSK r64, r/m64
	_TEST32_VEX( "c4e2c0f310 blsmsk rdi,qword ptr [eax]", 0xC4, 0xE2, 0xC0, 0xF3, 0x10 );
	_TEST32_VEX( "c4e2c0f3d0 blsmsk rdi,rax", 0xC4, 0xE2, 0xC0, 0xF3, 0xD0 );

	// BMI1
	// VEX.NDD.LZ.0F38.W0 F3 /3 BLSI r32, r/m32
	_TEST32_VEX( "c4e240f318 blsi edi,dword ptr [eax]", 0xC4, 0xE2, 0x40, 0xF3, 0x18 );
	_TEST32_VEX( "c4e240f3d8 blsi edi,eax", 0xC4, 0xE2, 0x40, 0xF3, 0xD8 );
	// VEX.NDD.LZ.0F38.W1 F3 /3 BLSI r64, r/m64
	_TEST32_VEX( "c4e2c0f318 blsi rdi,qword ptr [eax]", 0xC4, 0xE2, 0xC0, 0xF3, 0x18 );
	_TEST32_VEX( "c4e2c0f3d8 blsi rdi,rax", 0xC4, 0xE2, 0xC0, 0xF3, 0xD8 );

	// BEXR
	// VEX.NDS1.LZ.0F38.W0 F7 /r BEXR r32a, r/m32, r32b
	_TEST32_VEX( "c4e240f700 bexr eax,dword ptr [eax],edi", 0xC4, 0xE2, 0x40, 0xF7, 0x00 );
	_TEST32_VEX( "c4e240f7c0 bexr eax,eax,edi", 0xC4, 0xE2, 0x40, 0xF7, 0xC0 );
	// VEX.NDS1.LZ.0F38.W1 F7 /r BEXR r64a, r/m64, r64b
	_TEST32_VEX( "c4e2c0f700 bexr rax,qword ptr [eax],rdi", 0xC4, 0xE2, 0xC0, 0xF7, 0x00 );
	_TEST32_VEX( "c4e2c0f7c0 bexr rax,rax,rdi", 0xC4, 0xE2, 0xC0, 0xF7, 0xC0 );

	// ANDN
	// VEX.NDS.LZ.0F38.W0 F2 /r ANDN r32a, r32b, r/m32
	_TEST32_VEX( "c4e240f200 andn eax,edi,dword ptr [eax]", 0xC4, 0xE2, 0x40, 0xF2, 0x00 );
	_TEST32_VEX( "c4e240f2c0 andn eax,edi,eax", 0xC4, 0xE2, 0x40, 0xF2, 0xC0 );
	// VEX.NDS.LZ.0F38.W1 F2 /r ANDN r64a, r64b, r/m64
	_TEST32_VEX( "c4e2c0f200 andn rax,rdi,qword ptr [eax]", 0xC4, 0xE2, 0xC0, 0xF2, 0x00 );
	_TEST32_VEX( "c4e2c0f2c0 andn rax,rdi,rax", 0xC4, 0xE2, 0xC0, 0xF2, 0xC0 );

	// FMA

	// VEX.DDS.128.66.0F38.W0 98 /r VFMADD132PS xmm0,xmm1,xmm2/m128
	// VEX.DDS.256.66.0F38.W0 98 /r VFMADD132PS ymm0,ymm1,ymm2/m256
	_TEST32_VEX( "c4e2619800 vfmadd132ps xmm0,xmm3,oword ptr [eax]", 0xC4, 0xE2, 0x61, 0x98, 0x00 );
	_TEST64_VEX( "c4e2659800 vfmadd132ps ymm0,ymm3,ymmword ptr [rax]", 0xC4, 0xE2, 0x65, 0x98, 0x00 );
	_TEST32_VEX( "c4e26598c0 vfmadd132ps ymm0,ymm3,ymm0", 0xC4, 0xE2, 0x65, 0x98, 0xC0 );
	// VEX.DDS.128.66.0F38.W0 A8 /r VFMADD213PS xmm0,xmm1,xmm2/m128
	// VEX.DDS.256.66.0F38.W0 A8 /r VFMADD213PS ymm0,ymm1,ymm2/m256
	_TEST32_VEX( "c4e261a800 vfmadd213ps xmm0,xmm3,oword ptr [eax]", 0xC4, 0xE2, 0x61, 0xA8, 0x00 );
	_TEST64_VEX( "c4e265a800 vfmadd213ps ymm0,ymm3,ymmword ptr [rax]", 0xC4, 0xE2, 0x65, 0xA8, 0x00 );
	_TEST32_VEX( "c4e265a8c0 vfmadd213ps ymm0,ymm3,ymm0", 0xC4, 0xE2, 0x65, 0xA8, 0xC0 );
	// VEX.DDS.128.66.0F38.W0 B8 /r VFMADD231PS xmm0,xmm1,xmm2/m128
	// VEX.DDS.256.66.0F38.W0 B8 /r VFMADD231PS ymm0,ymm1,ymm2/m256
	_TEST32_VEX( "c4e261b800 vfmadd231ps xmm0,xmm3,oword ptr [eax]", 0xC4, 0xE2, 0x61, 0xB8, 0x00 );
	_TEST64_VEX( "c4e265b800 vfmadd231ps ymm0,ymm3,ymmword ptr [rax]", 0xC4, 0xE2, 0x65, 0xB8, 0x00 );
	_TEST32_VEX( "c4e265b8c0 vfmadd231ps ymm0,ymm3,ymm0", 0xC4, 0xE2, 0x65, 0xB8, 0xC0 );
	// VFMADDPS xmm1, xmm2, xmm3/mem128, xmm4 C4 RXB.00011 0.src.0.01 68 /r /is4
	// VFMADDPS ymm1, ymm2, ymm3/mem256, ymm4 C4 RXB.00011 0.src.1.01 68 /r /is4
	_TEST64_VEX( "c4e351681401 vfmaddps xmm2,xmm5,oword ptr [rcx+rax],xmm2", 0xC4, 0xE3, 0x51, 0x68, 0x14, 0x01, 0x20 );
	_TEST64_VEX( "c4e355681401 vfmaddps ymm2,ymm5,ymmword ptr [rcx+rax],ymm2", 0xC4, 0xE3, 0x55, 0x68, 0x14, 0x01, 0x20 );
	_TEST64_VEX( "c4e35568c0 vfmaddps ymm0,ymm5,ymm0,ymm2", 0xC4, 0xE3, 0x55, 0x68, 0xC0, 0x20 );
	// VFMADDPS xmm1, xmm2, xmm3, xmm4/mem128 C4 RXB.00011 1.src.0.01 68 /r /is4
	// VFMADDPS ymm1, ymm2, ymm3, ymm4/mem256 C4 RXB.00011 1.src.1.01 68 /r /is4
	_TEST64_VEX( "c4e3d1681401 vfmaddps xmm2,xmm5,xmm2,oword ptr [rcx+rax]", 0xC4, 0xE3, 0xD1, 0x68, 0x14, 0x01, 0x20 );
	_TEST64_VEX( "c4e3d5681401 vfmaddps ymm2,ymm5,ymm2,ymmword ptr [rcx+rax]", 0xC4, 0xE3, 0xD5, 0x68, 0x14, 0x01, 0x20 );
	_TEST64_VEX( "c4e3d568c0 vfmaddps ymm0,ymm5,ymm2,ymm0", 0xC4, 0xE3, 0xD5, 0x68, 0xC0, 0x20 );

	// VEX.DDS.LIG.128.66.0F38.W1 99 /r VFMADD132SD xmm0,xmm1,xmm2/m64
	_TEST32_VEX( "c4e2e19900 vfmadd132sd xmm0,xmm3,qword ptr [eax]", 0xC4, 0xE2, 0xE1, 0x99, 0x00 );
	_TEST64_VEX( "c4e2e199c0 vfmadd132sd xmm0,xmm3,xmm0", 0xC4, 0xE2, 0xE1, 0x99, 0xC0 );
	// VEX.DDS.LIG.128.66.0F38.W1 A9 /r VFMADD213SD xmm0,xmm1,xmm2/m64
	_TEST32_VEX( "c4e2e1a900 vfmadd213sd xmm0,xmm3,qword ptr [eax]", 0xC4, 0xE2, 0xE1, 0xA9, 0x00 );
	_TEST64_VEX( "c4e2e1a9c0 vfmadd213sd xmm0,xmm3,xmm0", 0xC4, 0xE2, 0xE1, 0xA9, 0xC0 );
	// VEX.DDS.LIG.128.66.0F38.W1 B9 /r VFMADD231SD xmm0,xmm1,xmm2/m64
	_TEST32_VEX( "c4e2e1b900 vfmadd231sd xmm0,xmm3,qword ptr [eax]", 0xC4, 0xE2, 0xE1, 0xB9, 0x00 );
	_TEST64_VEX( "c4e2e1b9c0 vfmadd231sd xmm0,xmm3,xmm0", 0xC4, 0xE2, 0xE1, 0xB9, 0xC0 );
	// VFMADDSD xmm1, xmm2, xmm3/mem128, xmm4 C4 RXB.00011 0.src.X.01 6B /r /is4
	// VFMADDSD xmm1, xmm2, xmm3, xmm4/mem128 C4 RXB.00011 1.src.X.01 6B /r /is4
	_TEST64_VEX( "c4e3516b1401 vfmaddsd xmm2,xmm5,oword ptr [rcx+rax],xmm2", 0xC4, 0xE3, 0x51, 0x6B, 0x14, 0x01, 0x20 );
	_TEST64_VEX( "c4e3516bc0 vfmaddsd xmm0,xmm5,xmm0,xmm2", 0xC4, 0xE3, 0x51, 0x6B, 0xC0, 0x20 );
	_TEST64_VEX( "c4e3d16b1401 vfmaddsd xmm2,xmm5,xmm2,oword ptr [rcx+rax]", 0xC4, 0xE3, 0xD1, 0x6B, 0x14, 0x01, 0x20 );
	_TEST64_VEX( "c4e3d16bc0 vfmaddsd xmm0,xmm5,xmm2,xmm0", 0xC4, 0xE3, 0xD1, 0x6B, 0xC0, 0x20 );

	// VFMADD132SS
	// VEX.DDS.LIG.128.66.0F38.W0 99 /r VFMADD132SS xmm0,xmm1,xmm2/m32
	_TEST32_VEX( "c4e2619900 vfmadd132ss xmm0,xmm3,dword ptr [eax]", 0xC4, 0xE2, 0x61, 0x99, 0x00 );
	_TEST64_VEX( "c4e26199c0 vfmadd132ss xmm0,xmm3,xmm0", 0xC4, 0xE2, 0x61, 0x99, 0xC0 );
	// VEX.DDS.LIG.128.66.0F38.W0 A9 /r VFMADD213SS xmm0,xmm1,xmm2/m32
	_TEST32_VEX( "c4e261a900 vfmadd213ss xmm0,xmm3,dword ptr [eax]", 0xC4, 0xE2, 0x61, 0xA9, 0x00 );
	_TEST64_VEX( "c4e261a9c0 vfmadd213ss xmm0,xmm3,xmm0", 0xC4, 0xE2, 0x61, 0xA9, 0xC0 );
	// VEX.DDS.LIG.128.66.0F38.W0 B9 /r VFMADD231SS xmm0,xmm1,xmm2/m32
	_TEST32_VEX( "c4e261b900 vfmadd231ss xmm0,xmm3,dword ptr [eax]", 0xC4, 0xE2, 0x61, 0xB9, 0x00 );
	_TEST64_VEX( "c4e261b9c0 vfmadd231ss xmm0,xmm3,xmm0", 0xC4, 0xE2, 0x61, 0xB9, 0xC0 );
	// VFMADDSS xmm1, xmm2, xmm3/mem32, xmm4 C4 RXB.00011 0.src.X.01 6A /r /is4
	// VFMADDSS xmm1, xmm2, xmm3, xmm4/mem32 C4 RXB.00011 1.src.X.01 6A /r /is4
	_TEST64_VEX( "c4e3516a1401 vfmaddss xmm2,xmm5,dword ptr [rcx+rax],xmm2", 0xC4, 0xE3, 0x51, 0x6A, 0x14, 0x01, 0x20 );
	_TEST64_VEX( "c4e3516ac0 vfmaddss xmm0,xmm5,xmm0,xmm2", 0xC4, 0xE3, 0x51, 0x6A, 0xC0, 0x20 );
	_TEST64_VEX( "c4e3d16a1401 vfmaddss xmm2,xmm5,xmm2,dword ptr [rcx+rax]", 0xC4, 0xE3, 0xD1, 0x6A, 0x14, 0x01, 0x20 );
	_TEST64_VEX( "c4e3d16ac0 vfmaddss xmm0,xmm5,xmm2,xmm0", 0xC4, 0xE3, 0xD1, 0x6A, 0xC0, 0x20 );

	// VFMADDSUB132PD
	// VEX.DDS.128.66.0F38.W1 96 /r VFMADDSUB132PD xmm0,xmm1,xmm2/m128
	// VEX.DDS.256.66.0F38.W1 96 /r VFMADDSUB132PD ymm0,ymm1,ymm2/m256
	_TEST32_VEX( "c4e2e19600 vfmaddsub132pd xmm0,xmm3,oword ptr [eax]", 0xC4, 0xE2, 0xE1, 0x96, 0x00 );
	_TEST64_VEX( "c4e2e59600 vfmaddsub132pd ymm0,ymm3,ymmword ptr [rax]", 0xC4, 0xE2, 0xE5, 0x96, 0x00 );
	_TEST32_VEX( "c4e2e596c0 vfmaddsub132pd ymm0,ymm3,ymm0", 0xC4, 0xE2, 0xE5, 0x96, 0xC0 );
	// VEX.DDS.128.66.0F38.W1 A6 /r VFMADDSUB213PD xmm0,xmm1,xmm2/m128
	// VEX.DDS.256.66.0F38.W1 A6 /r VFMADDSUB213PD ymm0,ymm1,ymm2/m256
	_TEST32_VEX( "c4e2e1a600 vfmaddsub213pd xmm0,xmm3,oword ptr [eax]", 0xC4, 0xE2, 0xE1, 0xA6, 0x00 );
	_TEST64_VEX( "c4e2e5a600 vfmaddsub213pd ymm0,ymm3,ymmword ptr [rax]", 0xC4, 0xE2, 0xE5, 0xA6, 0x00 );
	_TEST32_VEX( "c4e2e5a6c0 vfmaddsub213pd ymm0,ymm3,ymm0", 0xC4, 0xE2, 0xE5, 0xA6, 0xC0 );
	// VEX.DDS.128.66.0F38.W1 B6 /r VFMADDSUB231PD xmm0,xmm1,xmm2/m128
	// VEX.DDS.256.66.0F38.W1 B6 /r VFMADDSUB231PD ymm0,ymm1,ymm2/m256
	_TEST32_VEX( "c4e2e1b600 vfmaddsub231pd xmm0,xmm3,oword ptr [eax]", 0xC4, 0xE2, 0xE1, 0xB6, 0x00 );
	_TEST64_VEX( "c4e2e5b600 vfmaddsub231pd ymm0,ymm3,ymmword ptr [rax]", 0xC4, 0xE2, 0xE5, 0xB6, 0x00 );
	_TEST32_VEX( "c4e2e5b6c0 vfmaddsub231pd ymm0,ymm3,ymm0", 0xC4, 0xE2, 0xE5, 0xB6, 0xC0 );
	// VFMADDSUBPD xmm1, xmm2, xmm3/mem128, xmm4 C4 RXB.00011 0.src.0.01 5D /r /is4
	// VFMADDSUBPD ymm1, ymm2, ymm3/mem256, ymm4 C4 RXB.00011 0.src.1.01 5D /r /is4
	_TEST64_VEX( "c4e3515d1401 vfmaddsubpd xmm2,xmm5,oword ptr [rcx+rax],xmm2", 0xC4, 0xE3, 0x51, 0x5D, 0x14, 0x01, 0x20 );
	_TEST64_VEX( "c4e3555d1401 vfmaddsubpd ymm2,ymm5,ymmword ptr [rcx+rax],ymm2", 0xC4, 0xE3, 0x55, 0x5D, 0x14, 0x01, 0x20 );
	_TEST64_VEX( "c4e3555dc0 vfmaddsubpd ymm0,ymm5,ymm0,ymm2", 0xC4, 0xE3, 0x55, 0x5D, 0xC0, 0x20 );
	// VFMADDSUBPD xmm1, xmm2, xmm3, xmm4/mem128 C4 RXB.00011 1.src.0.01 5D /r /is4
	// VFMADDSUBPD ymm1, ymm2, ymm3, ymm4/mem256 C4 RXB.00011 1.src.1.01 5D /r /is4
	_TEST64_VEX( "c4e3d15d1401 vfmaddsubpd xmm2,xmm5,xmm2,oword ptr [rcx+rax]", 0xC4, 0xE3, 0xD1, 0x5D, 0x14, 0x01, 0x20 );
	_TEST64_VEX( "c4e3d55d1401 vfmaddsubpd ymm2,ymm5,ymm2,ymmword ptr [rcx+rax]", 0xC4, 0xE3, 0xD5, 0x5D, 0x14, 0x01, 0x20 );
	_TEST64_VEX( "c4e3d55dc0 vfmaddsubpd ymm0,ymm5,ymm2,ymm0", 0xC4, 0xE3, 0xD5, 0x5D, 0xC0, 0x20 );

	// VFMADDSUB132PS
	// VEX.DDS.128.66.0F38.W0 96 /r VFMADDSUB132PS xmm0,xmm1,xmm2/m128
	// VEX.DDS.256.66.0F38.W0 96 /r VFMADDSUB132PS ymm0,ymm1,ymm2/m256
	_TEST32_VEX( "c4e2619600 vfmaddsub132ps xmm0,xmm3,oword ptr [eax]", 0xC4, 0xE2, 0x61, 0x96, 0x00 );
	_TEST64_VEX( "c4e2659600 vfmaddsub132ps ymm0,ymm3,ymmword ptr [rax]", 0xC4, 0xE2, 0x65, 0x96, 0x00 );
	_TEST32_VEX( "c4e26596c0 vfmaddsub132ps ymm0,ymm3,ymm0", 0xC4, 0xE2, 0x65, 0x96, 0xC0 );
	// VEX.DDS.128.66.0F38.W0 A6 /r VFMADDSUB213PS xmm0,xmm1,xmm2/m128
	// VEX.DDS.256.66.0F38.W0 A6 /r VFMADDSUB213PS ymm0,ymm1,ymm2/m256
	_TEST32_VEX( "c4e261a600 vfmaddsub213ps xmm0,xmm3,oword ptr [eax]", 0xC4, 0xE2, 0x61, 0xA6, 0x00 );
	_TEST64_VEX( "c4e265a600 vfmaddsub213ps ymm0,ymm3,ymmword ptr [rax]", 0xC4, 0xE2, 0x65, 0xA6, 0x00 );
	_TEST32_VEX( "c4e265a6c0 vfmaddsub213ps ymm0,ymm3,ymm0", 0xC4, 0xE2, 0x65, 0xA6, 0xC0 );
	// VEX.DDS.128.66.0F38.W0 B6 /r VFMADDSUB231PS xmm0,xmm1,xmm2/m128
	// VEX.DDS.256.66.0F38.W0 B6 /r VFMADDSUB231PS ymm0,ymm1,ymm2/m256
	_TEST32_VEX( "c4e261b600 vfmaddsub231ps xmm0,xmm3,oword ptr [eax]", 0xC4, 0xE2, 0x61, 0xB6, 0x00 );
	_TEST64_VEX( "c4e265b600 vfmaddsub231ps ymm0,ymm3,ymmword ptr [rax]", 0xC4, 0xE2, 0x65, 0xB6, 0x00 );
	_TEST32_VEX( "c4e265b6c0 vfmaddsub231ps ymm0,ymm3,ymm0", 0xC4, 0xE2, 0x65, 0xB6, 0xC0 );
	// VFMADDSUBPS xmm1, xmm2, xmm3/mem128, xmm4 C4 RXB.00011 0.src.0.01 5C /r /is4
	// VFMADDSUBPS ymm1, ymm2, ymm3/mem256, ymm4 C4 RXB.00011 0.src.1.01 5C /r /is4
	_TEST64_VEX( "c4e3515c1401 vfmaddsubps xmm2,xmm5,oword ptr [rcx+rax],xmm2", 0xC4, 0xE3, 0x51, 0x5C, 0x14, 0x01, 0x20 );
	_TEST64_VEX( "c4e3555c1401 vfmaddsubps ymm2,ymm5,ymmword ptr [rcx+rax],ymm2", 0xC4, 0xE3, 0x55, 0x5C, 0x14, 0x01, 0x20 );
	_TEST64_VEX( "c4e3555cc0 vfmaddsubps ymm0,ymm5,ymm0,ymm2", 0xC4, 0xE3, 0x55, 0x5C, 0xC0, 0x20 );
	// VFMADDSUBPS xmm1, xmm2, xmm3, xmm4/mem128 C4 RXB.00011 1.src.0.01 5C /r /is4
	// VFMADDSUBPS ymm1, ymm2, ymm3, ymm4/mem256 C4 RXB.00011 1.src.1.01 5C /r /is4
	_TEST64_VEX( "c4e3d15c1401 vfmaddsubps xmm2,xmm5,xmm2,oword ptr [rcx+rax]", 0xC4, 0xE3, 0xD1, 0x5C, 0x14, 0x01, 0x20 );
	_TEST64_VEX( "c4e3d55c1401 vfmaddsubps ymm2,ymm5,ymm2,ymmword ptr [rcx+rax]", 0xC4, 0xE3, 0xD5, 0x5C, 0x14, 0x01, 0x20 );
	_TEST64_VEX( "c4e3d55cc0 vfmaddsubps ymm0,ymm5,ymm2,ymm0", 0xC4, 0xE3, 0xD5, 0x5C, 0xC0, 0x20 );

	// VEX.DDS.128.66.0F38.W1 97 /r VFMSUBADD132PD xmm0,xmm1,xmm2/m128
	// VEX.DDS.256.66.0F38.W1 97 /r VFMSUBADD132PD ymm0,ymm1,ymm2/m256
	_TEST32_VEX( "c4e2e19700 vfmsubadd132pd xmm0,xmm3,oword ptr [eax]", 0xC4, 0xE2, 0xE1, 0x97, 0x00 );
	_TEST64_VEX( "c4e2e59700 vfmsubadd132pd ymm0,ymm3,ymmword ptr [rax]", 0xC4, 0xE2, 0xE5, 0x97, 0x00 );
	_TEST32_VEX( "c4e2e597c0 vfmsubadd132pd ymm0,ymm3,ymm0", 0xC4, 0xE2, 0xE5, 0x97, 0xC0 );
	// VEX.DDS.128.66.0F38.W1 A7 /r VFMSUBADD213PD xmm0,xmm1,xmm2/m128
	// VEX.DDS.256.66.0F38.W1 A7 /r VFMSUBADD213PD ymm0,ymm1,ymm2/m256
	_TEST32_VEX( "c4e2e1a700 vfmsubadd213pd xmm0,xmm3,oword ptr [eax]", 0xC4, 0xE2, 0xE1, 0xA7, 0x00 );
	_TEST64_VEX( "c4e2e5a700 vfmsubadd213pd ymm0,ymm3,ymmword ptr [rax]", 0xC4, 0xE2, 0xE5, 0xA7, 0x00 );
	_TEST32_VEX( "c4e2e5a7c0 vfmsubadd213pd ymm0,ymm3,ymm0", 0xC4, 0xE2, 0xE5, 0xA7, 0xC0 );
	// VEX.DDS.128.66.0F38.W1 B7 /r VFMSUBADD231PD xmm0,xmm1,xmm2/m128
	// VEX.DDS.256.66.0F38.W1 B7 /r VFMSUBADD231PD ymm0,ymm1,ymm2/m256
	_TEST32_VEX( "c4e2e1b700 vfmsubadd231pd xmm0,xmm3,oword ptr [eax]", 0xC4, 0xE2, 0xE1, 0xB7, 0x00 );
	_TEST64_VEX( "c4e2e5b700 vfmsubadd231pd ymm0,ymm3,ymmword ptr [rax]", 0xC4, 0xE2, 0xE5, 0xB7, 0x00 );
	_TEST32_VEX( "c4e2e5b7c0 vfmsubadd231pd ymm0,ymm3,ymm0", 0xC4, 0xE2, 0xE5, 0xB7, 0xC0 );
	// VFMSUBADDPD xmm1, xmm2, xmm3/mem128, xmm4 C4 RXB.00011 0.src.0.01 5F /r /is4
	// VFMSUBADDPD ymm1, ymm2, ymm3/mem256, ymm4 C4 RXB.00011 0.src.1.01 5F /r /is4
	_TEST64_VEX( "c4e3515f1401 vfmsubaddpd xmm2,xmm5,oword ptr [rcx+rax],xmm2", 0xC4, 0xE3, 0x51, 0x5F, 0x14, 0x01, 0x20 );
	_TEST64_VEX( "c4e3555f1401 vfmsubaddpd ymm2,ymm5,ymmword ptr [rcx+rax],ymm2", 0xC4, 0xE3, 0x55, 0x5F, 0x14, 0x01, 0x20 );
	_TEST64_VEX( "c4e3555fc0 vfmsubaddpd ymm0,ymm5,ymm0,ymm2", 0xC4, 0xE3, 0x55, 0x5F, 0xC0, 0x20 );
	// VFMSUBADDPD xmm1, xmm2, xmm3, xmm4/mem128 C4 RXB.00011 1.src.0.01 5F /r /is4
	// VFMSUBADDPD ymm1, ymm2, ymm3, ymm4/mem256 C4 RXB.00011 1.src.1.01 5F /r /is4
	_TEST64_VEX( "c4e3d15f1401 vfmsubaddpd xmm2,xmm5,xmm2,oword ptr [rcx+rax]", 0xC4, 0xE3, 0xD1, 0x5F, 0x14, 0x01, 0x20 );
	_TEST64_VEX( "c4e3d55f1401 vfmsubaddpd ymm2,ymm5,ymm2,ymmword ptr [rcx+rax]", 0xC4, 0xE3, 0xD5, 0x5F, 0x14, 0x01, 0x20 );
	_TEST64_VEX( "c4e3d55fc0 vfmsubaddpd ymm0,ymm5,ymm2,ymm0", 0xC4, 0xE3, 0xD5, 0x5F, 0xC0, 0x20 );

	// VEX.DDS.128.66.0F38.W0 97 /r VFMSUBADD132PS xmm0,xmm1,xmm2/m128
	// VEX.DDS.256.66.0F38.W0 97 /r VFMSUBADD132PS ymm0,ymm1,ymm2/m256
	_TEST32_VEX( "c4e2619700 vfmsubadd132ps xmm0,xmm3,oword ptr [eax]", 0xC4, 0xE2, 0x61, 0x97, 0x00 );
	_TEST64_VEX( "c4e2659700 vfmsubadd132ps ymm0,ymm3,ymmword ptr [rax]", 0xC4, 0xE2, 0x65, 0x97, 0x00 );
	_TEST32_VEX( "c4e26597c0 vfmsubadd132ps ymm0,ymm3,ymm0", 0xC4, 0xE2, 0x65, 0x97, 0xC0 );
	// VEX.DDS.128.66.0F38.W0 A7 /r VFMSUBADD213PS xmm0,xmm1,xmm2/m128
	// VEX.DDS.256.66.0F38.W0 A7 /r VFMSUBADD213PS ymm0,ymm1,ymm2/m256
	_TEST32_VEX( "c4e261a700 vfmsubadd213ps xmm0,xmm3,oword ptr [eax]", 0xC4, 0xE2, 0x61, 0xA7, 0x00 );
	_TEST64_VEX( "c4e265a700 vfmsubadd213ps ymm0,ymm3,ymmword ptr [rax]", 0xC4, 0xE2, 0x65, 0xA7, 0x00 );
	_TEST32_VEX( "c4e265a7c0 vfmsubadd213ps ymm0,ymm3,ymm0", 0xC4, 0xE2, 0x65, 0xA7, 0xC0 );
	// VEX.DDS.128.66.0F38.W0 B7 /r VFMSUBADD231PS xmm0,xmm1,xmm2/m128
	// VEX.DDS.256.66.0F38.W0 B7 /r VFMSUBADD231PS ymm0,ymm1,ymm2/m256
	_TEST32_VEX( "c4e261b700 vfmsubadd231ps xmm0,xmm3,oword ptr [eax]", 0xC4, 0xE2, 0x61, 0xB7, 0x00 );
	_TEST64_VEX( "c4e265b700 vfmsubadd231ps ymm0,ymm3,ymmword ptr [rax]", 0xC4, 0xE2, 0x65, 0xB7, 0x00 );
	_TEST32_VEX( "c4e265b7c0 vfmsubadd231ps ymm0,ymm3,ymm0", 0xC4, 0xE2, 0x65, 0xB7, 0xC0 );
	// VFMSUBADDPS xmm1, xmm2, xmm3/mem128, xmm4 C4 RXB.00011 0.src.0.01 5E /r /is4
	// VFMSUBADDPS ymm1, ymm2, ymm3/mem256, ymm4 C4 RXB.00011 0.src.1.01 5E /r /is4
	_TEST64_VEX( "c4e3515e1401 vfmsubaddps xmm2,xmm5,oword ptr [rcx+rax],xmm2", 0xC4, 0xE3, 0x51, 0x5E, 0x14, 0x01, 0x20 );
	_TEST64_VEX( "c4e3555e1401 vfmsubaddps ymm2,ymm5,ymmword ptr [rcx+rax],ymm2", 0xC4, 0xE3, 0x55, 0x5E, 0x14, 0x01, 0x20 );
	_TEST64_VEX( "c4e3555ec0 vfmsubaddps ymm0,ymm5,ymm0,ymm2", 0xC4, 0xE3, 0x55, 0x5E, 0xC0, 0x20 );
	// VFMSUBADDPS xmm1, xmm2, xmm3, xmm4/mem128 C4 RXB.00011 1.src.0.01 5E /r /is4
	// VFMSUBADDPS ymm1, ymm2, ymm3, ymm4/mem256 C4 RXB.00011 1.src.1.01 5E /r /is4
	_TEST64_VEX( "c4e3d15e1401 vfmsubaddps xmm2,xmm5,xmm2,oword ptr [rcx+rax]", 0xC4, 0xE3, 0xD1, 0x5E, 0x14, 0x01, 0x20 );
	_TEST64_VEX( "c4e3d55e1401 vfmsubaddps ymm2,ymm5,ymm2,ymmword ptr [rcx+rax]", 0xC4, 0xE3, 0xD5, 0x5E, 0x14, 0x01, 0x20 );
	_TEST64_VEX( "c4e3d55ec0 vfmsubaddps ymm0,ymm5,ymm2,ymm0", 0xC4, 0xE3, 0xD5, 0x5E, 0xC0, 0x20 );

	// VEX.DDS.128.66.0F38.W1 9A /r VFMSUB132PD xmm0,xmm1,xmm2/m128
	// VEX.DDS.256.66.0F38.W1 9A /r VFMSUB132PD ymm0,ymm1,ymm2/m256
	_TEST32_VEX( "c4e2e19a00 vfmsub132pd xmm0,xmm3,oword ptr [eax]", 0xC4, 0xE2, 0xE1, 0x9A, 0x00 );
	_TEST64_VEX( "c4e2e59a00 vfmsub132pd ymm0,ymm3,ymmword ptr [rax]", 0xC4, 0xE2, 0xE5, 0x9A, 0x00 );
	_TEST32_VEX( "c4e2e59ac0 vfmsub132pd ymm0,ymm3,ymm0", 0xC4, 0xE2, 0xE5, 0x9A, 0xC0 );
	// VEX.DDS.128.66.0F38.W1 AA /r VFMSUB213PD xmm0,xmm1,xmm2/m128
	// VEX.DDS.256.66.0F38.W1 AA /r VFMSUB213PD ymm0,ymm1,ymm2/m256
	_TEST32_VEX( "c4e2e1aa00 vfmsub213pd xmm0,xmm3,oword ptr [eax]", 0xC4, 0xE2, 0xE1, 0xAA, 0x00 );
	_TEST64_VEX( "c4e2e5aa00 vfmsub213pd ymm0,ymm3,ymmword ptr [rax]", 0xC4, 0xE2, 0xE5, 0xAA, 0x00 );
	_TEST32_VEX( "c4e2e5aac0 vfmsub213pd ymm0,ymm3,ymm0", 0xC4, 0xE2, 0xE5, 0xAA, 0xC0 );
	// VEX.DDS.128.66.0F38.W1 BA /r VFMSUB231PD xmm0,xmm1,xmm2/m128
	// VEX.DDS.256.66.0F38.W1 BA /r VFMSUB231PD ymm0,ymm1,ymm2/m256
	_TEST32_VEX( "c4e2e1ba00 vfmsub231pd xmm0,xmm3,oword ptr [eax]", 0xC4, 0xE2, 0xE1, 0xBA, 0x00 );
	_TEST64_VEX( "c4e2e5ba00 vfmsub231pd ymm0,ymm3,ymmword ptr [rax]", 0xC4, 0xE2, 0xE5, 0xBA, 0x00 );
	_TEST32_VEX( "c4e2e5bac0 vfmsub231pd ymm0,ymm3,ymm0", 0xC4, 0xE2, 0xE5, 0xBA, 0xC0 );
	// VFMSUBPD xmm1, xmm2, xmm3/mem128, xmm4 C4 RXB.00011 0.src.0.01 6D /r /is4
	// VFMSUBPD ymm1, ymm2, ymm3/mem256, ymm4 C4 RXB.00011 0.src.1.01 6D /r /is4
	_TEST64_VEX( "c4e3516d1401 vfmsubpd xmm2,xmm5,oword ptr [rcx+rax],xmm2", 0xC4, 0xE3, 0x51, 0x6D, 0x14, 0x01, 0x20 );
	_TEST64_VEX( "c4e3556d1401 vfmsubpd ymm2,ymm5,ymmword ptr [rcx+rax],ymm2", 0xC4, 0xE3, 0x55, 0x6D, 0x14, 0x01, 0x20 );
	_TEST64_VEX( "c4e3556dc0 vfmsubpd ymm0,ymm5,ymm0,ymm2", 0xC4, 0xE3, 0x55, 0x6D, 0xC0, 0x20 );
	// VFMSUBPD xmm1, xmm2, xmm3, xmm4/mem128 C4 RXB.00011 1.src.0.01 6D /r /is4
	// VFMSUBPD ymm1, ymm2, ymm3, ymm4/mem256 C4 RXB.00011 1.src.1.01 6D /r /is4
	_TEST64_VEX( "c4e3d16d1401 vfmsubpd xmm2,xmm5,xmm2,oword ptr [rcx+rax]", 0xC4, 0xE3, 0xD1, 0x6D, 0x14, 0x01, 0x20 );
	_TEST64_VEX( "c4e3d56d1401 vfmsubpd ymm2,ymm5,ymm2,ymmword ptr [rcx+rax]", 0xC4, 0xE3, 0xD5, 0x6D, 0x14, 0x01, 0x20 );
	_TEST64_VEX( "c4e3d56dc0 vfmsubpd ymm0,ymm5,ymm2,ymm0", 0xC4, 0xE3, 0xD5, 0x6D, 0xC0, 0x20 );

	// VEX.DDS.128.66.0F38.W0 9A /r VFMSUB132PS xmm0,xmm1,xmm2/m128
	// VEX.DDS.256.66.0F38.W0 9A /r VFMSUB132PS ymm0,ymm1,ymm2/m256
	_TEST32_VEX( "c4e2619a00 vfmsub132ps xmm0,xmm3,oword ptr [eax]", 0xC4, 0xE2, 0x61, 0x9A, 0x00 );
	_TEST64_VEX( "c4e2659a00 vfmsub132ps ymm0,ymm3,ymmword ptr [rax]", 0xC4, 0xE2, 0x65, 0x9A, 0x00 );
	_TEST32_VEX( "c4e2659ac0 vfmsub132ps ymm0,ymm3,ymm0", 0xC4, 0xE2, 0x65, 0x9A, 0xC0 );
	// VEX.DDS.128.66.0F38.W0 AA /r VFMSUB213PS xmm0,xmm1,xmm2/m128
	// VEX.DDS.256.66.0F38.W0 AA /r VFMSUB213PS ymm0,ymm1,ymm2/m256
	_TEST32_VEX( "c4e261aa00 vfmsub213ps xmm0,xmm3,oword ptr [eax]", 0xC4, 0xE2, 0x61, 0xAA, 0x00 );
	_TEST64_VEX( "c4e265aa00 vfmsub213ps ymm0,ymm3,ymmword ptr [rax]", 0xC4, 0xE2, 0x65, 0xAA, 0x00 );
	_TEST32_VEX( "c4e265aac0 vfmsub213ps ymm0,ymm3,ymm0", 0xC4, 0xE2, 0x65, 0xAA, 0xC0 );
	// VEX.DDS.128.66.0F38.W0 BA /r VFMSUB231PS xmm0,xmm1,xmm2/m128
	// VEX.DDS.256.66.0F38.W0 BA /r VFMSUB231PS ymm0,ymm1,ymm2/m256
	_TEST32_VEX( "c4e261ba00 vfmsub231ps xmm0,xmm3,oword ptr [eax]", 0xC4, 0xE2, 0x61, 0xBA, 0x00 );
	_TEST64_VEX( "c4e265ba00 vfmsub231ps ymm0,ymm3,ymmword ptr [rax]", 0xC4, 0xE2, 0x65, 0xBA, 0x00 );
	_TEST32_VEX( "c4e265bac0 vfmsub231ps ymm0,ymm3,ymm0", 0xC4, 0xE2, 0x65, 0xBA, 0xC0 );
	// VFMSUBPS xmm1, xmm2, xmm3/mem128, xmm4 C4 RXB.00011 0.src.0.01 6C /r /is4
	// VFMSUBPS ymm1, ymm2, ymm3/mem256, ymm4 C4 RXB.00011 0.src.1.01 6C /r /is4
	_TEST64_VEX( "c4e3516c1401 vfmsubps xmm2,xmm5,oword ptr [rcx+rax],xmm2", 0xC4, 0xE3, 0x51, 0x6C, 0x14, 0x01, 0x20 );
	_TEST64_VEX( "c4e3556c1401 vfmsubps ymm2,ymm5,ymmword ptr [rcx+rax],ymm2", 0xC4, 0xE3, 0x55, 0x6C, 0x14, 0x01, 0x20 );
	_TEST64_VEX( "c4e3556cc0 vfmsubps ymm0,ymm5,ymm0,ymm2", 0xC4, 0xE3, 0x55, 0x6C, 0xC0, 0x20 );
	// VFMSUBPS xmm1, xmm2, xmm3, xmm4/mem128 C4 RXB.00011 1.src.0.01 6C /r /is4
	// VFMSUBPS ymm1, ymm2, ymm3, ymm4/mem256 C4 RXB.00011 1.src.1.01 6C /r /is4
	_TEST64_VEX( "c4e3d16c1401 vfmsubps xmm2,xmm5,xmm2,oword ptr [rcx+rax]", 0xC4, 0xE3, 0xD1, 0x6C, 0x14, 0x01, 0x20 );
	_TEST64_VEX( "c4e3d56c1401 vfmsubps ymm2,ymm5,ymm2,ymmword ptr [rcx+rax]", 0xC4, 0xE3, 0xD5, 0x6C, 0x14, 0x01, 0x20 );
	_TEST64_VEX( "c4e3d56cc0 vfmsubps ymm0,ymm5,ymm2,ymm0", 0xC4, 0xE3, 0xD5, 0x6C, 0xC0, 0x20 );

	// VEX.DDS.LIG.128.66.0F38.W1 9B /r VFMSUB132SD xmm0,xmm1,xmm2/m64
	_TEST32_VEX( "c4e2e19b00 vfmsub132sd xmm0,xmm3,qword ptr [eax]", 0xC4, 0xE2, 0xE1, 0x9B, 0x00 );
	_TEST64_VEX( "c4e2e19bc0 vfmsub132sd xmm0,xmm3,xmm0", 0xC4, 0xE2, 0xE1, 0x9B, 0xC0 );
	// VEX.DDS.LIG.128.66.0F38.W1 AB /r VFMSUB213SD xmm0,xmm1,xmm2/m64
	_TEST32_VEX( "c4e2e1ab00 vfmsub213sd xmm0,xmm3,qword ptr [eax]", 0xC4, 0xE2, 0xE1, 0xAB, 0x00 );
	_TEST64_VEX( "c4e2e1abc0 vfmsub213sd xmm0,xmm3,xmm0", 0xC4, 0xE2, 0xE1, 0xAB, 0xC0 );
	// VEX.DDS.LIG.128.66.0F38.W1 BB /r VFMSUB231SD xmm0,xmm1,xmm2/m64
	_TEST32_VEX( "c4e2e1bb00 vfmsub231sd xmm0,xmm3,qword ptr [eax]", 0xC4, 0xE2, 0xE1, 0xBB, 0x00 );
	_TEST64_VEX( "c4e2e1bbc0 vfmsub231sd xmm0,xmm3,xmm0", 0xC4, 0xE2, 0xE1, 0xBB, 0xC0 );
	// VFMSUBSD xmm1, xmm2, xmm3/mem64, xmm4 C4 RXB.00011 0.src.X.01 6F /r /is4
	// VFMSUBSD xmm1, xmm2, xmm3, xmm4/mem64 C4 RXB.00011 1.src.X.01 6F /r /is4
	_TEST64_VEX( "c4e3516f1401 vfmsubsd xmm2,xmm5,qword ptr [rcx+rax],xmm2", 0xC4, 0xE3, 0x51, 0x6F, 0x14, 0x01, 0x20 );
	_TEST64_VEX( "c4e3516fc0 vfmsubsd xmm0,xmm5,xmm0,xmm2", 0xC4, 0xE3, 0x51, 0x6F, 0xC0, 0x20 );
	_TEST64_VEX( "c4e3d16f1401 vfmsubsd xmm2,xmm5,xmm2,qword ptr [rcx+rax]", 0xC4, 0xE3, 0xD1, 0x6F, 0x14, 0x01, 0x20 );
	_TEST64_VEX( "c4e3d16fc0 vfmsubsd xmm0,xmm5,xmm2,xmm0", 0xC4, 0xE3, 0xD1, 0x6F, 0xC0, 0x20 );

	// VEX.DDS.LIG.128.66.0F38.W0 9B /r VFMSUB132SS xmm0,xmm1,xmm2/m32
	_TEST32_VEX( "c4e2619b00 vfmsub132ss xmm0,xmm3,dword ptr [eax]", 0xC4, 0xE2, 0x61, 0x9B, 0x00 );
	_TEST64_VEX( "c4e2619bc0 vfmsub132ss xmm0,xmm3,xmm0", 0xC4, 0xE2, 0x61, 0x9B, 0xC0 );
	// VEX.DDS.LIG.128.66.0F38.W0 AB /r VFMSUB213SS xmm0,xmm1,xmm2/m32
	_TEST32_VEX( "c4e261ab00 vfmsub213ss xmm0,xmm3,dword ptr [eax]", 0xC4, 0xE2, 0x61, 0xAB, 0x00 );
	_TEST64_VEX( "c4e261abc0 vfmsub213ss xmm0,xmm3,xmm0", 0xC4, 0xE2, 0x61, 0xAB, 0xC0 );
	// VEX.DDS.LIG.128.66.0F38.W0 BB /r VFMSUB231SS xmm0,xmm1,xmm2/m32
	_TEST32_VEX( "c4e261bb00 vfmsub231ss xmm0,xmm3,dword ptr [eax]", 0xC4, 0xE2, 0x61, 0xBB, 0x00 );
	_TEST64_VEX( "c4e261bbc0 vfmsub231ss xmm0,xmm3,xmm0", 0xC4, 0xE2, 0x61, 0xBB, 0xC0 );
	// VFMSUBSS xmm1, xmm2, xmm3/mem32, xmm4 C4 RXB.00011 0.src.X.01 6E /r /is4
	// VFMSUBSS xmm1, xmm2, xmm3, xmm4/mem32 C4 RXB.00011 1.src.X.01 6E /r /is4
	_TEST64_VEX( "c4e3516e1401 vfmsubss xmm2,xmm5,dword ptr [rcx+rax],xmm2", 0xC4, 0xE3, 0x51, 0x6E, 0x14, 0x01, 0x20 );
	_TEST64_VEX( "c4e3516ec0 vfmsubss xmm0,xmm5,xmm0,xmm2", 0xC4, 0xE3, 0x51, 0x6E, 0xC0, 0x20 );
	_TEST64_VEX( "c4e3d16e1401 vfmsubss xmm2,xmm5,xmm2,dword ptr [rcx+rax]", 0xC4, 0xE3, 0xD1, 0x6E, 0x14, 0x01, 0x20 );
	_TEST64_VEX( "c4e3d16ec0 vfmsubss xmm0,xmm5,xmm2,xmm0", 0xC4, 0xE3, 0xD1, 0x6E, 0xC0, 0x20 );

	// VEX.DDS.128.66.0F38.W1 9C /r VFNMADD132PD xmm0,xmm1,xmm2/m128
	// VEX.DDS.256.66.0F38.W1 9C /r VFNMADD132PD ymm0,ymm1,ymm2/m256
	_TEST32_VEX( "c4e2e19c00 vfnmadd132pd xmm0,xmm3,oword ptr [eax]", 0xC4, 0xE2, 0xE1, 0x9C, 0x00 );
	_TEST64_VEX( "c4e2e59c00 vfnmadd132pd ymm0,ymm3,ymmword ptr [rax]", 0xC4, 0xE2, 0xE5, 0x9C, 0x00 );
	_TEST32_VEX( "c4e2e59cc0 vfnmadd132pd ymm0,ymm3,ymm0", 0xC4, 0xE2, 0xE5, 0x9C, 0xC0 );
	// VEX.DDS.128.66.0F38.W1 AC /r VFNMADD213PD xmm0,xmm1,xmm2/m128
	// VEX.DDS.256.66.0F38.W1 AC /r VFNMADD213PD ymm0,ymm1,ymm2/m256
	_TEST32_VEX( "c4e2e1ac00 vfnmadd213pd xmm0,xmm3,oword ptr [eax]", 0xC4, 0xE2, 0xE1, 0xAC, 0x00 );
	_TEST64_VEX( "c4e2e5ac00 vfnmadd213pd ymm0,ymm3,ymmword ptr [rax]", 0xC4, 0xE2, 0xE5, 0xAC, 0x00 );
	_TEST32_VEX( "c4e2e5acc0 vfnmadd213pd ymm0,ymm3,ymm0", 0xC4, 0xE2, 0xE5, 0xAC, 0xC0 );
	// VEX.DDS.128.66.0F38.W1 BC /r VFNMADD231PD xmm0,xmm1,xmm2/m128
	// VEX.DDS.256.66.0F38.W1 BC /r VFNMADD231PD ymm0,ymm1,ymm2/m256
	_TEST32_VEX( "c4e2e1bc00 vfnmadd231pd xmm0,xmm3,oword ptr [eax]", 0xC4, 0xE2, 0xE1, 0xBC, 0x00 );
	_TEST64_VEX( "c4e2e5bc00 vfnmadd231pd ymm0,ymm3,ymmword ptr [rax]", 0xC4, 0xE2, 0xE5, 0xBC, 0x00 );
	_TEST32_VEX( "c4e2e5bcc0 vfnmadd231pd ymm0,ymm3,ymm0", 0xC4, 0xE2, 0xE5, 0xBC, 0xC0 );
	// VFNMADDPD xmm1, xmm2, xmm3/mem128, xmm4 C4 RXB.00011 0.src.0.01 79 /r /is4
	// VFNMADDPD ymm1, ymm2, ymm3/mem256, ymm4 C4 RXB.00011 0.src.1.01 79 /r /is4
	_TEST64_VEX( "c4e351791401 vfnmaddpd xmm2,xmm5,oword ptr [rcx+rax],xmm2", 0xC4, 0xE3, 0x51, 0x79, 0x14, 0x01, 0x20 );
	_TEST64_VEX( "c4e355791401 vfnmaddpd ymm2,ymm5,ymmword ptr [rcx+rax],ymm2", 0xC4, 0xE3, 0x55, 0x79, 0x14, 0x01, 0x20 );
	_TEST64_VEX( "c4e35579c0 vfnmaddpd ymm0,ymm5,ymm0,ymm2", 0xC4, 0xE3, 0x55, 0x79, 0xC0, 0x20 );
	// VFNMADDPD xmm1, xmm2, xmm3, xmm4/mem128 C4 RXB.00011 1.src.0.01 79 /r /is4
	// VFNMADDPD ymm1, ymm2, ymm3, ymm4/mem256 C4 RXB.00011 1.src.1.01 79 /r /is4
	_TEST64_VEX( "c4e3d1791401 vfnmaddpd xmm2,xmm5,xmm2,oword ptr [rcx+rax]", 0xC4, 0xE3, 0xD1, 0x79, 0x14, 0x01, 0x20 );
	_TEST64_VEX( "c4e3d5791401 vfnmaddpd ymm2,ymm5,ymm2,ymmword ptr [rcx+rax]", 0xC4, 0xE3, 0xD5, 0x79, 0x14, 0x01, 0x20 );
	_TEST64_VEX( "c4e3d579c0 vfnmaddpd ymm0,ymm5,ymm2,ymm0", 0xC4, 0xE3, 0xD5, 0x79, 0xC0, 0x20 );

	// VEX.DDS.128.66.0F38.W0 9C /r VFNMADD132PS xmm0,xmm1,xmm2/m128
	// VEX.DDS.256.66.0F38.W0 9C /r VFNMADD132PS ymm0,ymm1,ymm2/m256
	_TEST32_VEX( "c4e2619c00 vfnmadd132ps xmm0,xmm3,oword ptr [eax]", 0xC4, 0xE2, 0x61, 0x9C, 0x00 );
	_TEST64_VEX( "c4e2659c00 vfnmadd132ps ymm0,ymm3,ymmword ptr [rax]", 0xC4, 0xE2, 0x65, 0x9C, 0x00 );
	_TEST32_VEX( "c4e2659cc0 vfnmadd132ps ymm0,ymm3,ymm0", 0xC4, 0xE2, 0x65, 0x9C, 0xC0 );
	// VEX.DDS.128.66.0F38.W0 AC /r VFNMADD213PS xmm0,xmm1,xmm2/m128
	// VEX.DDS.256.66.0F38.W0 AC /r VFNMADD213PS ymm0,ymm1,ymm2/m256
	_TEST32_VEX( "c4e261ac00 vfnmadd213ps xmm0,xmm3,oword ptr [eax]", 0xC4, 0xE2, 0x61, 0xAC, 0x00 );
	_TEST64_VEX( "c4e265ac00 vfnmadd213ps ymm0,ymm3,ymmword ptr [rax]", 0xC4, 0xE2, 0x65, 0xAC, 0x00 );
	_TEST32_VEX( "c4e265acc0 vfnmadd213ps ymm0,ymm3,ymm0", 0xC4, 0xE2, 0x65, 0xAC, 0xC0 );
	// VEX.DDS.128.66.0F38.W0 BC /r VFNMADD231PS xmm0,xmm1,xmm2/m128
	// VEX.DDS.256.66.0F38.W0 BC /r VFNMADD231PS ymm0,ymm1,ymm2/m256
	_TEST32_VEX( "c4e261bc00 vfnmadd231ps xmm0,xmm3,oword ptr [eax]", 0xC4, 0xE2, 0x61, 0xBC, 0x00 );
	_TEST64_VEX( "c4e265bc00 vfnmadd231ps ymm0,ymm3,ymmword ptr [rax]", 0xC4, 0xE2, 0x65, 0xBC, 0x00 );
	_TEST32_VEX( "c4e265bcc0 vfnmadd231ps ymm0,ymm3,ymm0", 0xC4, 0xE2, 0x65, 0xBC, 0xC0 );
	// VFNMADDPS xmm1, xmm2, xmm3/mem128, xmm4 C4 RXB.00011 0.src.0.01 78 /r /is4
	// VFNMADDPS ymm1, ymm2, ymm3/mem256, ymm4 C4 RXB.00011 0.src.1.01 78 /r /is4
	_TEST64_VEX( "c4e351781401 vfnmaddps xmm2,xmm5,oword ptr [rcx+rax],xmm2", 0xC4, 0xE3, 0x51, 0x78, 0x14, 0x01, 0x20 );
	_TEST64_VEX( "c4e355781401 vfnmaddps ymm2,ymm5,ymmword ptr [rcx+rax],ymm2", 0xC4, 0xE3, 0x55, 0x78, 0x14, 0x01, 0x20 );
	_TEST64_VEX( "c4e35578c0 vfnmaddps ymm0,ymm5,ymm0,ymm2", 0xC4, 0xE3, 0x55, 0x78, 0xC0, 0x20 );
	// VFNMADDPS xmm1, xmm2, xmm3, xmm4/mem128 C4 RXB.00011 1.src.0.01 78 /r /is4
	// VFNMADDPS ymm1, ymm2, ymm3, ymm4/mem256 C4 RXB.00011 1.src.1.01 78 /r /is4
	_TEST64_VEX( "c4e3d1781401 vfnmaddps xmm2,xmm5,xmm2,oword ptr [rcx+rax]", 0xC4, 0xE3, 0xD1, 0x78, 0x14, 0x01, 0x20 );
	_TEST64_VEX( "c4e3d5781401 vfnmaddps ymm2,ymm5,ymm2,ymmword ptr [rcx+rax]", 0xC4, 0xE3, 0xD5, 0x78, 0x14, 0x01, 0x20 );
	_TEST64_VEX( "c4e3d578c0 vfnmaddps ymm0,ymm5,ymm2,ymm0", 0xC4, 0xE3, 0xD5, 0x78, 0xC0, 0x20 );

	// VEX.DDS.LIG.128.66.0F38.W1 9D /r VFNMADD132SD xmm0,xmm1,xmm2/m64
	_TEST32_VEX( "c4e2e19d00 vfnmadd132sd xmm0,xmm3,qword ptr [eax]", 0xC4, 0xE2, 0xE1, 0x9D, 0x00 );
	_TEST64_VEX( "c4e2e19dc0 vfnmadd132sd xmm0,xmm3,xmm0", 0xC4, 0xE2, 0xE1, 0x9D, 0xC0 );
	// VEX.DDS.LIG.128.66.0F38.W1 AD /r VFNMADD213SD xmm0,xmm1,xmm2/m64
	_TEST32_VEX( "c4e2e1ad00 vfnmadd213sd xmm0,xmm3,qword ptr [eax]", 0xC4, 0xE2, 0xE1, 0xAD, 0x00 );
	_TEST64_VEX( "c4e2e1adc0 vfnmadd213sd xmm0,xmm3,xmm0", 0xC4, 0xE2, 0xE1, 0xAD, 0xC0 );
	// VEX.DDS.LIG.128.66.0F38.W1 BD /r VFNMADD231SD xmm0,xmm1,xmm2/m64
	_TEST32_VEX( "c4e2e1bd00 vfnmadd231sd xmm0,xmm3,qword ptr [eax]", 0xC4, 0xE2, 0xE1, 0xBD, 0x00 );
	_TEST64_VEX( "c4e2e1bdc0 vfnmadd231sd xmm0,xmm3,xmm0", 0xC4, 0xE2, 0xE1, 0xBD, 0xC0 );
	// VFNMADDSD xmm1, xmm2, xmm3/mem64, xmm4 C4 RXB.00011 0.src.X.01 7B /r /is4
	// VFNMADDSD xmm1, xmm2, xmm3, xmm4/mem64 C4 RXB.00011 1.src.X.01 7B /r /is4
	_TEST64_VEX( "c4e3517b1401 vfnmaddsd xmm2,xmm5,qword ptr [rcx+rax],xmm2", 0xC4, 0xE3, 0x51, 0x7B, 0x14, 0x01, 0x20 );
	_TEST64_VEX( "c4e3517bc0 vfnmaddsd xmm0,xmm5,xmm0,xmm2", 0xC4, 0xE3, 0x51, 0x7B, 0xC0, 0x20 );
	_TEST64_VEX( "c4e3d17b1401 vfnmaddsd xmm2,xmm5,xmm2,qword ptr [rcx+rax]", 0xC4, 0xE3, 0xD1, 0x7B, 0x14, 0x01, 0x20 );
	_TEST64_VEX( "c4e3d17bc0 vfnmaddsd xmm0,xmm5,xmm2,xmm0", 0xC4, 0xE3, 0xD1, 0x7B, 0xC0, 0x20 );

	// VEX.DDS.LIG.128.66.0F38.W0 9D /r VFNMADD132SS xmm0,xmm1,xmm2/m32
	_TEST32_VEX( "c4e2619d00 vfnmadd132ss xmm0,xmm3,dword ptr [eax]", 0xC4, 0xE2, 0x61, 0x9D, 0x00 );
	_TEST64_VEX( "c4e2619dc0 vfnmadd132ss xmm0,xmm3,xmm0", 0xC4, 0xE2, 0x61, 0x9D, 0xC0 );
	// VEX.DDS.LIG.128.66.0F38.W0 AD /r VFNMADD213SS xmm0,xmm1,xmm2/m32
	_TEST32_VEX( "c4e261ad00 vfnmadd213ss xmm0,xmm3,dword ptr [eax]", 0xC4, 0xE2, 0x61, 0xAD, 0x00 );
	_TEST64_VEX( "c4e261adc0 vfnmadd213ss xmm0,xmm3,xmm0", 0xC4, 0xE2, 0x61, 0xAD, 0xC0 );
	// VEX.DDS.LIG.128.66.0F38.W0 BD /r VFNMADD231SS xmm0,xmm1,xmm2/m32
	_TEST32_VEX( "c4e261bd00 vfnmadd231ss xmm0,xmm3,dword ptr [eax]", 0xC4, 0xE2, 0x61, 0xBD, 0x00 );
	_TEST64_VEX( "c4e261bdc0 vfnmadd231ss xmm0,xmm3,xmm0", 0xC4, 0xE2, 0x61, 0xBD, 0xC0 );
	// VFNMADDSS xmm1, xmm2, xmm3/mem32, xmm4 C4 RXB.00011 0.src.X.01 7A /r /is4
	// VFNMADDSS xmm1, xmm2, xmm3, xmm4/mem32 C4 RXB.00011 1.src.X.01 7A /r /is4
	_TEST64_VEX( "c4e3517a1401 vfnmaddss xmm2,xmm5,dword ptr [rcx+rax],xmm2", 0xC4, 0xE3, 0x51, 0x7A, 0x14, 0x01, 0x20 );
	_TEST64_VEX( "c4e3517ac0 vfnmaddss xmm0,xmm5,xmm0,xmm2", 0xC4, 0xE3, 0x51, 0x7A, 0xC0, 0x20 );
	_TEST64_VEX( "c4e3d17a1401 vfnmaddss xmm2,xmm5,xmm2,dword ptr [rcx+rax]", 0xC4, 0xE3, 0xD1, 0x7A, 0x14, 0x01, 0x20 );
	_TEST64_VEX( "c4e3d17ac0 vfnmaddss xmm0,xmm5,xmm2,xmm0", 0xC4, 0xE3, 0xD1, 0x7A, 0xC0, 0x20 );

	// VEX.DDS.128.66.0F38.W1 9E /r VFNMSUB132PD xmm0,xmm1,xmm2/m128
	// VEX.DDS.256.66.0F38.W1 9E /r VFNMSUB132PD ymm0,ymm1,ymm2/m256
	_TEST32_VEX( "c4e2e19e00 vfnmsub132pd xmm0,xmm3,oword ptr [eax]", 0xC4, 0xE2, 0xE1, 0x9E, 0x00 );
	_TEST64_VEX( "c4e2e59e00 vfnmsub132pd ymm0,ymm3,ymmword ptr [rax]", 0xC4, 0xE2, 0xE5, 0x9E, 0x00 );
	_TEST32_VEX( "c4e2e59ec0 vfnmsub132pd ymm0,ymm3,ymm0", 0xC4, 0xE2, 0xE5, 0x9E, 0xC0 );
	// VEX.DDS.128.66.0F38.W1 AE /r VFNMSUB213PD xmm0,xmm1,xmm2/m128
	// VEX.DDS.256.66.0F38.W1 AE /r VFNMSUB213PD ymm0,ymm1,ymm2/m256
	_TEST32_VEX( "c4e2e1ae00 vfnmsub213pd xmm0,xmm3,oword ptr [eax]", 0xC4, 0xE2, 0xE1, 0xAE, 0x00 );
	_TEST64_VEX( "c4e2e5ae00 vfnmsub213pd ymm0,ymm3,ymmword ptr [rax]", 0xC4, 0xE2, 0xE5, 0xAE, 0x00 );
	_TEST32_VEX( "c4e2e5aec0 vfnmsub213pd ymm0,ymm3,ymm0", 0xC4, 0xE2, 0xE5, 0xAE, 0xC0 );
	// VEX.DDS.128.66.0F38.W1 BE /r VFNMSUB231PD xmm0,xmm1,xmm2/m128
	// VEX.DDS.256.66.0F38.W1 BE /r VFNMSUB231PD ymm0,ymm1,ymm2/m256
	_TEST32_VEX( "c4e2e1be00 vfnmsub231pd xmm0,xmm3,oword ptr [eax]", 0xC4, 0xE2, 0xE1, 0xBE, 0x00 );
	_TEST64_VEX( "c4e2e5be00 vfnmsub231pd ymm0,ymm3,ymmword ptr [rax]", 0xC4, 0xE2, 0xE5, 0xBE, 0x00 );
	_TEST32_VEX( "c4e2e5bec0 vfnmsub231pd ymm0,ymm3,ymm0", 0xC4, 0xE2, 0xE5, 0xBE, 0xC0 );
	// VFNMSUBPD xmm1, xmm2, xmm3/mem128, xmm4 C4 RXB.00011 0.src.0.01 7D /r /is4
	// VFNMSUBPD ymm1, ymm2, ymm3/mem256, ymm4 C4 RXB.00011 0.src.1.01 7D /r /is4
	_TEST64_VEX( "c4e3517d1401 vfnmsubpd xmm2,xmm5,oword ptr [rcx+rax],xmm2", 0xC4, 0xE3, 0x51, 0x7D, 0x14, 0x01, 0x20 );
	_TEST64_VEX( "c4e3557d1401 vfnmsubpd ymm2,ymm5,ymmword ptr [rcx+rax],ymm2", 0xC4, 0xE3, 0x55, 0x7D, 0x14, 0x01, 0x20 );
	_TEST64_VEX( "c4e3557dc0 vfnmsubpd ymm0,ymm5,ymm0,ymm2", 0xC4, 0xE3, 0x55, 0x7D, 0xC0, 0x20 );
	// VFNMSUBPD xmm1, xmm2, xmm3, xmm4/mem128 C4 RXB.00011 1.src.0.01 7D /r /is4
	// VFNMSUBPD ymm1, ymm2, ymm3, ymm4/mem256 C4 RXB.00011 1.src.1.01 7D /r /is4
	_TEST64_VEX( "c4e3d17d1401 vfnmsubpd xmm2,xmm5,xmm2,oword ptr [rcx+rax]", 0xC4, 0xE3, 0xD1, 0x7D, 0x14, 0x01, 0x20 );
	_TEST64_VEX( "c4e3d57d1401 vfnmsubpd ymm2,ymm5,ymm2,ymmword ptr [rcx+rax]", 0xC4, 0xE3, 0xD5, 0x7D, 0x14, 0x01, 0x20 );
	_TEST64_VEX( "c4e3d57dc0 vfnmsubpd ymm0,ymm5,ymm2,ymm0", 0xC4, 0xE3, 0xD5, 0x7D, 0xC0, 0x20 );

	// VEX.DDS.128.66.0F38.W0 9E /r VFNMSUB132PS xmm0,xmm1,xmm2/m128
	// VEX.DDS.256.66.0F38.W0 9E /r VFNMSUB132PS ymm0,ymm1,ymm2/m256
	_TEST32_VEX( "c4e2619e00 vfnmsub132ps xmm0,xmm3,oword ptr [eax]", 0xC4, 0xE2, 0x61, 0x9E, 0x00 );
	_TEST64_VEX( "c4e2659e00 vfnmsub132ps ymm0,ymm3,ymmword ptr [rax]", 0xC4, 0xE2, 0x65, 0x9E, 0x00 );
	_TEST32_VEX( "c4e2659ec0 vfnmsub132ps ymm0,ymm3,ymm0", 0xC4, 0xE2, 0x65, 0x9E, 0xC0 );
	// VEX.DDS.128.66.0F38.W0 AE /r VFNMSUB213PS xmm0,xmm1,xmm2/m128
	// VEX.DDS.256.66.0F38.W0 AE /r VFNMSUB213PS ymm0,ymm1,ymm2/m256
	_TEST32_VEX( "c4e261ae00 vfnmsub213ps xmm0,xmm3,oword ptr [eax]", 0xC4, 0xE2, 0x61, 0xAE, 0x00 );
	_TEST64_VEX( "c4e265ae00 vfnmsub213ps ymm0,ymm3,ymmword ptr [rax]", 0xC4, 0xE2, 0x65, 0xAE, 0x00 );
	_TEST32_VEX( "c4e265aec0 vfnmsub213ps ymm0,ymm3,ymm0", 0xC4, 0xE2, 0x65, 0xAE, 0xC0 );
	// VEX.DDS.128.66.0F38.W0 BE /r VFNMSUB231PS xmm0,xmm1,xmm2/m128
	// VEX.DDS.256.66.0F38.W0 BE /r VFNMSUB231PS ymm0,ymm1,ymm2/m256
	_TEST32_VEX( "c4e261be00 vfnmsub231ps xmm0,xmm3,oword ptr [eax]", 0xC4, 0xE2, 0x61, 0xBE, 0x00 );
	_TEST64_VEX( "c4e265be00 vfnmsub231ps ymm0,ymm3,ymmword ptr [rax]", 0xC4, 0xE2, 0x65, 0xBE, 0x00 );
	_TEST32_VEX( "c4e265bec0 vfnmsub231ps ymm0,ymm3,ymm0", 0xC4, 0xE2, 0x65, 0xBE, 0xC0 );
	// VFNMSUBPS xmm1, xmm2, xmm3/mem128, xmm4 C4 RXB.00011 0.src.0.01 7C /r /is4
	// VFNMSUBPS ymm1, ymm2, ymm3/mem256, ymm4 C4 RXB.00011 0.src.1.01 7C /r /is4
	_TEST64_VEX( "c4e3517c1401 vfnmsubps xmm2,xmm5,oword ptr [rcx+rax],xmm2", 0xC4, 0xE3, 0x51, 0x7C, 0x14, 0x01, 0x20 );
	_TEST64_VEX( "c4e3557c1401 vfnmsubps ymm2,ymm5,ymmword ptr [rcx+rax],ymm2", 0xC4, 0xE3, 0x55, 0x7C, 0x14, 0x01, 0x20 );
	_TEST64_VEX( "c4e3557cc0 vfnmsubps ymm0,ymm5,ymm0,ymm2", 0xC4, 0xE3, 0x55, 0x7C, 0xC0, 0x20 );
	// VFNMSUBPS xmm1, xmm2, xmm3, xmm4/mem128 C4 RXB.00011 1.src.0.01 7C /r /is4
	// VFNMSUBPS ymm1, ymm2, ymm3, ymm4/mem256 C4 RXB.00011 1.src.1.01 7C /r /is4
	_TEST64_VEX( "c4e3d17c1401 vfnmsubps xmm2,xmm5,xmm2,oword ptr [rcx+rax]", 0xC4, 0xE3, 0xD1, 0x7C, 0x14, 0x01, 0x20 );
	_TEST64_VEX( "c4e3d57c1401 vfnmsubps ymm2,ymm5,ymm2,ymmword ptr [rcx+rax]", 0xC4, 0xE3, 0xD5, 0x7C, 0x14, 0x01, 0x20 );
	_TEST64_VEX( "c4e3d57cc0 vfnmsubps ymm0,ymm5,ymm2,ymm0", 0xC4, 0xE3, 0xD5, 0x7C, 0xC0, 0x20 );

	// VEX.DDS.LIG.128.66.0F38.W1 9F /r VFNMSUB132SD xmm0,xmm1,xmm2/m64
	_TEST32_VEX( "c4e2e19f00 vfnmsub132sd xmm0,xmm3,qword ptr [eax]", 0xC4, 0xE2, 0xE1, 0x9F, 0x00 );
	_TEST64_VEX( "c4e2e19fc0 vfnmsub132sd xmm0,xmm3,xmm0", 0xC4, 0xE2, 0xE1, 0x9F, 0xC0 );
	// VEX.DDS.LIG.128.66.0F38.W1 AF /r VFNMSUB213SD xmm0,xmm1,xmm2/m64
	_TEST32_VEX( "c4e2e1af00 vfnmsub213sd xmm0,xmm3,qword ptr [eax]", 0xC4, 0xE2, 0xE1, 0xAF, 0x00 );
	_TEST64_VEX( "c4e2e1afc0 vfnmsub213sd xmm0,xmm3,xmm0", 0xC4, 0xE2, 0xE1, 0xAF, 0xC0 );
	// VEX.DDS.LIG.128.66.0F38.W1 BF /r VFNMSUB231SD xmm0,xmm1,xmm2/m64
	_TEST32_VEX( "c4e2e1bf00 vfnmsub231sd xmm0,xmm3,qword ptr [eax]", 0xC4, 0xE2, 0xE1, 0xBF, 0x00 );
	_TEST64_VEX( "c4e2e1bfc0 vfnmsub231sd xmm0,xmm3,xmm0", 0xC4, 0xE2, 0xE1, 0xBF, 0xC0 );
	// VFNMSUBSD xmm1, xmm2, xmm3/mem64, xmm4 C4 RXB.00011 0.src.X.01 7F /r /is4
	// VFNMSUBSD xmm1, xmm2, xmm3, xmm4/mem64 C4 RXB.00011 1.src.X.01 7F /r /is4
	_TEST64_VEX( "c4e3517f1401 vfnmsubsd xmm2,xmm5,qword ptr [rcx+rax],xmm2", 0xC4, 0xE3, 0x51, 0x7F, 0x14, 0x01, 0x20 );
	_TEST64_VEX( "c4e3517fc0 vfnmsubsd xmm0,xmm5,xmm0,xmm2", 0xC4, 0xE3, 0x51, 0x7F, 0xC0, 0x20 );
	_TEST64_VEX( "c4e3d17f1401 vfnmsubsd xmm2,xmm5,xmm2,qword ptr [rcx+rax]", 0xC4, 0xE3, 0xD1, 0x7F, 0x14, 0x01, 0x20 );
	_TEST64_VEX( "c4e3d17fc0 vfnmsubsd xmm0,xmm5,xmm2,xmm0", 0xC4, 0xE3, 0xD1, 0x7F, 0xC0, 0x20 );

	// VEX.DDS.LIG.128.66.0F38.W0 9F /r VFNMSUB132SS xmm0,xmm1,xmm2/m32
	_TEST32_VEX( "c4e2619f00 vfnmsub132ss xmm0,xmm3,dword ptr [eax]", 0xC4, 0xE2, 0x61, 0x9F, 0x00 );
	_TEST64_VEX( "c4e2619fc0 vfnmsub132ss xmm0,xmm3,xmm0", 0xC4, 0xE2, 0x61, 0x9F, 0xC0 );
	// VEX.DDS.LIG.128.66.0F38.W0 AF /r VFNMSUB213SS xmm0,xmm1,xmm2/m32
	_TEST32_VEX( "c4e261af00 vfnmsub213ss xmm0,xmm3,dword ptr [eax]", 0xC4, 0xE2, 0x61, 0xAF, 0x00 );
	_TEST64_VEX( "c4e261afc0 vfnmsub213ss xmm0,xmm3,xmm0", 0xC4, 0xE2, 0x61, 0xAF, 0xC0 );
	// VEX.DDS.LIG.128.66.0F38.W0 BF /r VFNMSUB231SS xmm0,xmm1,xmm2/m32
	_TEST32_VEX( "c4e261bf00 vfnmsub231ss xmm0,xmm3,dword ptr [eax]", 0xC4, 0xE2, 0x61, 0xBF, 0x00 );
	_TEST64_VEX( "c4e261bfc0 vfnmsub231ss xmm0,xmm3,xmm0", 0xC4, 0xE2, 0x61, 0xBF, 0xC0 );
	// VFNMSUBSS xmm1, xmm2, xmm3/mem32, xmm4 C4 RXB.00011 0.src.X.01 7E /r /is4
	// VFNMSUBSS xmm1, xmm2, xmm3, xmm4/mem32 C4 RXB.00011 1.src.X.01 7E /r /is4
	_TEST64_VEX( "c4e3517e1401 vfnmsubss xmm2,xmm5,dword ptr [rcx+rax],xmm2", 0xC4, 0xE3, 0x51, 0x7E, 0x14, 0x01, 0x20 );
	_TEST64_VEX( "c4e3517ec0 vfnmsubss xmm0,xmm5,xmm0,xmm2", 0xC4, 0xE3, 0x51, 0x7E, 0xC0, 0x20 );
	_TEST64_VEX( "c4e3d17e1401 vfnmsubss xmm2,xmm5,xmm2,dword ptr [rcx+rax]", 0xC4, 0xE3, 0xD1, 0x7E, 0x14, 0x01, 0x20 );
	_TEST64_VEX( "c4e3d17ec0 vfnmsubss xmm0,xmm5,xmm2,xmm0", 0xC4, 0xE3, 0xD1, 0x7E, 0xC0, 0x20 );

	// VEX.DDS.128.66.0F38.W1 98 /r VFMADD132PD xmm0,xmm1,xmm2/m128
	// VEX.DDS.256.66.0F38.W1 98 /r VFMADD132PD ymm0,ymm1,ymm2/m256
	_TEST32_VEX( "c4e2e19800 vfmadd132pd xmm0,xmm3,oword ptr [eax]", 0xC4, 0xE2, 0xE1, 0x98, 0x00 );
	_TEST64_VEX( "c4e2e59800 vfmadd132pd ymm0,ymm3,ymmword ptr [rax]", 0xC4, 0xE2, 0xE5, 0x98, 0x00 );
	_TEST32_VEX( "c4e2e598c0 vfmadd132pd ymm0,ymm3,ymm0", 0xC4, 0xE2, 0xE5, 0x98, 0xC0 );
	// VEX.DDS.128.66.0F38.W1 A8 /r VFMADD213PD xmm0,xmm1,xmm2/m128
	// VEX.DDS.256.66.0F38.W1 A8 /r VFMADD213PD ymm0,ymm1,ymm2/m256
	_TEST32_VEX( "c4e2e1a800 vfmadd213pd xmm0,xmm3,oword ptr [eax]", 0xC4, 0xE2, 0xE1, 0xA8, 0x00 );
	_TEST64_VEX( "c4e2e5a800 vfmadd213pd ymm0,ymm3,ymmword ptr [rax]", 0xC4, 0xE2, 0xE5, 0xA8, 0x00 );
	_TEST32_VEX( "c4e2e5a8c0 vfmadd213pd ymm0,ymm3,ymm0", 0xC4, 0xE2, 0xE5, 0xA8, 0xC0 );
	// VEX.DDS.128.66.0F38.W1 B8 /r VFMADD231PD xmm0,xmm1,xmm2/m128
	// VEX.DDS.256.66.0F38.W1 B8 /r VFMADD231PD ymm0,ymm1,ymm2/m256
	_TEST32_VEX( "c4e2e1b800 vfmadd231pd xmm0,xmm3,oword ptr [eax]", 0xC4, 0xE2, 0xE1, 0xB8, 0x00 );
	_TEST64_VEX( "c4e2e5b800 vfmadd231pd ymm0,ymm3,ymmword ptr [rax]", 0xC4, 0xE2, 0xE5, 0xB8, 0x00 );
	_TEST32_VEX( "c4e2e5b8c0 vfmadd231pd ymm0,ymm3,ymm0", 0xC4, 0xE2, 0xE5, 0xB8, 0xC0 );
	// VFMADDPD xmm1, xmm2, xmm3/mem128, xmm4 C4 RXB.00011 0.src.0.01 69 /r /is4
	// VFMADDPD ymm1, ymm2, ymm3/mem256, ymm4 C4 RXB.00011 0.src.1.01 69 /r /is4
	_TEST64_VEX( "c4e351691401 vfmaddpd xmm2,xmm5,oword ptr [rcx+rax],xmm2", 0xC4, 0xE3, 0x51, 0x69, 0x14, 0x01, 0x20 );
	_TEST64_VEX( "c4e355691401 vfmaddpd ymm2,ymm5,ymmword ptr [rcx+rax],ymm2", 0xC4, 0xE3, 0x55, 0x69, 0x14, 0x01, 0x20 );
	_TEST64_VEX( "c4e35569c0 vfmaddpd ymm0,ymm5,ymm0,ymm2", 0xC4, 0xE3, 0x55, 0x69, 0xC0, 0x20 );
	// VFMADDPD xmm1, xmm2, xmm3, xmm4/mem128 C4 RXB.00011 1.src.0.01 69 /r /is4
	// VFMADDPD ymm1, ymm2, ymm3, ymm4/mem256 C4 RXB.00011 1.src.1.01 69 /r /is4
	_TEST64_VEX( "c4e3d1691401 vfmaddpd xmm2,xmm5,xmm2,oword ptr [rcx+rax]", 0xC4, 0xE3, 0xD1, 0x69, 0x14, 0x01, 0x20 );
	_TEST64_VEX( "c4e3d5691401 vfmaddpd ymm2,ymm5,ymm2,ymmword ptr [rcx+rax]", 0xC4, 0xE3, 0xD5, 0x69, 0x14, 0x01, 0x20 );
	_TEST64_VEX( "c4e3d569c0 vfmaddpd ymm0,ymm5,ymm2,ymm0", 0xC4, 0xE3, 0xD5, 0x69, 0xC0, 0x20 );


	// END OF FMA

	// PF2IW
	// PF2IW mmreg1, mmreg2/mem64 0Fh 0Fh / 1Ch Packed floating-point to integer word conversion with PF2IW sign extend
	_TEST32( "0f0fc100 pf2iw mm0,qword ptr [eax]", 0x0F, 0x0F, 0xC1, 0x00 );
	_TEST64( "0f0fc1c1 pf2iw mm0,mm1", 0x0F, 0x0F, 0xC1, 0xC1 );

	// PFNACC
	// PFNACC mmreg1, mmreg2/mem64 0Fh 0Fh / 8Ah Packed floating-point negative accumulate
	_TEST32( "0f0f8a00 pfnacc mm0,qword ptr [eax]", 0x0F, 0x0F, 0x8A, 0x00 );
	_TEST64( "0f0f8ac1 pfnacc mm0,mm1", 0x0F, 0x0F, 0x8A, 0xC1 );

	// PFPNACC
	// PFPNACC mmreg1, mmreg2/mem64 0Fh 0Fh / 8Eh Packed floating-point mixed positive-negative accumulate
	_TEST32( "0f0f8e00 pfpnacc mm0,qword ptr [eax]", 0x0F, 0x0F, 0x8E, 0x00 );
	_TEST64( "0f0f8ec1 pfpnacc mm0,mm1", 0x0F, 0x0F, 0x8E, 0xC1 );

	// PI2FW
	// PI2FW mmreg1, mmreg2/mem64 0Fh 0Fh / 0Ch Packed 16-bit integer to floating-point conversion
	_TEST32( "0f0f0c00 pi2fw mm0,qword ptr [eax]", 0x0F, 0x0F, 0x0C, 0x00 );
	_TEST64( "0f0f0cc1 pi2fw mm0,mm1", 0x0F, 0x0F, 0x0C, 0xC1 );

	// PSWAPD
	// PSWAPD mmreg1, mmreg2/mem64 0Fh 0Fh / BBh Packed swap doubleword
	_TEST32( "0f0fbb00 pswapd mm0,qword ptr [eax]", 0x0F, 0x0F, 0xBB, 0x00 );
	_TEST64( "0f0fbbc1 pswapd mm0,mm1", 0x0F, 0x0F, 0xBB, 0xC1 );

	// PREFETCH
	// PREFETCH(W) mem8 0F 0Dh Prefetch processor cache line into L1 data cache (Dcache)
	_TEST32( "0f0d00 prefetch byte ptr [eax]", 0x0F, 0x0D, 0x00 );
	_TEST64( "0f0d08 prefetchw byte ptr [rax]", 0x0F, 0x0D, 0x08 );

	// PMULHRW
	// PMULHRW mmreg1, mmreg2/mem64 0F 0Fh/B7h Multiply signed packed 16-bit values with rounding and store the high 16 bits.
	_TEST32( "0f0fb700 pmulhrw mm0,qword ptr [eax]", 0x0F, 0x0F, 0xB7, 0x00 );
	_TEST64( "0f0fb7c1 pmulhrw mm0,mm1", 0x0F, 0x0F, 0xB7, 0xC1 );

	// PI2FD
	// PI2FD mmreg1, mmreg2/mem64 0Fh 0Fh / 0Dh Packed 32-bit integer to floating-point conversion
	_TEST32( "0f0f0d00 pi2fd mm0,qword ptr [eax]", 0x0F, 0x0F, 0x0D, 0x00 );
	_TEST64( "0f0f0dc1 pi2fd mm0,mm1", 0x0F, 0x0F, 0x0D, 0xC1 );

	// PFSUBR
	// PFSUBR mmreg1, mmreg2/mem64 0Fh 0Fh / AAh Packed floating-point reverse subtraction
	_TEST32( "0f0faa00 pfsubr mm0,qword ptr [eax]", 0x0F, 0x0F, 0xAA, 0x00 );
	_TEST64( "0f0faac1 pfsubr mm0,mm1", 0x0F, 0x0F, 0xAA, 0xC1 );

	// PFSUB
	// PFSUB mmreg1, mmreg2/mem64 0Fh 0Fh / 9Ah Packed floating-point subtraction
	_TEST32( "0f0f9a00 pfsub mm0,qword ptr [eax]", 0x0F, 0x0F, 0x9A, 0x00 );
	_TEST64( "0f0f9ac1 pfsub mm0,mm1", 0x0F, 0x0F, 0x9A, 0xC1 );

	// PFRSQRT
	// PFRSQRT mmreg1, mmreg2/mem64 0Fh 0Fh / 97h Floating-point reciprocal square root approximation
	_TEST32( "0f0f9700 pfrsqrt mm0,qword ptr [eax]", 0x0F, 0x0F, 0x97, 0x00 );
	_TEST64( "0f0f97c1 pfrsqrt mm0,mm1", 0x0F, 0x0F, 0x97, 0xC1 );

	// PFRSQIT1
	// PFRSQIT1 mmreg1, mmreg2/mem64 0Fh 0Fh / A7h Packed floating-point reciprocal square root, first iteration step
	_TEST32( "0f0fa700 pfrsqit1 mm0,qword ptr [eax]", 0x0F, 0x0F, 0xA7, 0x00 );
	_TEST64( "0f0fa7c1 pfrsqit1 mm0,mm1", 0x0F, 0x0F, 0xA7, 0xC1 );

	// PFRCPIT2
	// PFRCPIT2 mmreg1, mmreg2/mem64 0Fh 0Fh / B6h Packed floating-point reciprocal/reciprocal square root, second iteration step
	_TEST32( "0f0fb600 pfrcpit2 mm0,qword ptr [eax]", 0x0F, 0x0F, 0xB6, 0x00 );
	_TEST64( "0f0fb6c1 pfrcpit2 mm0,mm1", 0x0F, 0x0F, 0xB6, 0xC1 );

	// PFRCPIT1
	// PFRCPIT1 mmreg1, mmreg2/mem64 0Fh 0Fh / A6h Packed floating-point reciprocal, first iteration step
	_TEST32( "0f0fa600 pfrcpit1 mm0,qword ptr [eax]", 0x0F, 0x0F, 0xA6, 0x00 );
	_TEST64( "0f0fa6c1 pfrcpit1 mm0,mm1", 0x0F, 0x0F, 0xA6, 0xC1 );

	// PFRCP
	// PFRCP mmreg1, mmreg2/mem64 0Fh 0Fh / 96h Floating-point reciprocal approximation
	_TEST32( "0f0f9600 pfrcp mm0,qword ptr [eax]", 0x0F, 0x0F, 0x96, 0x00 );
	_TEST64( "0f0f96c1 pfrcp mm0,mm1", 0x0F, 0x0F, 0x96, 0xC1 );

	// PFMUL
	// PFMUL mmreg1, mmreg2/mem64 0Fh 0Fh / B4h Packed floating-point multiplication
	_TEST32( "0f0fb400 pfmul mm0,qword ptr [eax]", 0x0F, 0x0F, 0xB4, 0x00 );
	_TEST64( "0f0fb4c1 pfmul mm0,mm1", 0x0F, 0x0F, 0xB4, 0xC1 );

	// PFMIN
	// PFMIN mmreg1, mmreg2/mem64 0Fh 0Fh / 94h Packed floating-point minimum
	_TEST32( "0f0f9400 pfmin mm0,qword ptr [eax]", 0x0F, 0x0F, 0x94, 0x00 );
	_TEST64( "0f0f94c1 pfmin mm0,mm1", 0x0F, 0x0F, 0x94, 0xC1 );

	// PFMAX
	// PFMAX mmreg1, mmreg2/mem64 0Fh 0Fh / A4h Packed floating-point maximum
	_TEST32( "0f0fa400 pfmax mm0,qword ptr [eax]", 0x0F, 0x0F, 0xA4, 0x00 );
	_TEST64( "0f0fa4c1 pfmax mm0,mm1", 0x0F, 0x0F, 0xA4, 0xC1 );

	// PFCMPGT
	// PFCMPGT mmreg1, mmreg2/mem64 0Fh 0Fh / A0h Packed floating-point comparison, greater than
	_TEST32( "0f0fa000 pfcmpgt mm0,qword ptr [eax]", 0x0F, 0x0F, 0xA0, 0x00 );
	_TEST64( "0f0fa0c1 pfcmpgt mm0,mm1", 0x0F, 0x0F, 0xA0, 0xC1 );

	// PFCMPGE
	// PFCMPGE mmreg1, mmreg2/mem64 0Fh 0Fh / 90h Packed floating-point comparison, greater than or equal to
	_TEST32( "0f0f9000 pfcmpge mm0,qword ptr [eax]", 0x0F, 0x0F, 0x90, 0x00 );
	_TEST64( "0f0f90c1 pfcmpge mm0,mm1", 0x0F, 0x0F, 0x90, 0xC1 );

	// PFCMPEQ
	// PFCMPEQ mmreg1, mmreg2/mem64 0Fh 0Fh / B0h Packed floating-point comparison, equal to
	_TEST32( "0f0fb000 pfcmpeq mm0,qword ptr [eax]", 0x0F, 0x0F, 0xB0, 0x00 );
	_TEST64( "0f0fb0c1 pfcmpeq mm0,mm1", 0x0F, 0x0F, 0xB0, 0xC1 );

	// PFADD
	// PFADD mmreg1, mmreg2/mem64 0Fh 0Fh / 9Eh Packed, floating-point addition
	_TEST32( "0f0f9e00 pfadd mm0,qword ptr [eax]", 0x0F, 0x0F, 0x9E, 0x00 );
	_TEST64( "0f0f9ec1 pfadd mm0,mm1", 0x0F, 0x0F, 0x9E, 0xC1 );

	// PFACC
	// PFACC mmreg1, mmreg2/mem64 0Fh 0Fh / AEh Floating-point accumulate
	_TEST32( "0f0fae00 pfacc mm0,qword ptr [eax]", 0x0F, 0x0F, 0xAE, 0x00 );
	_TEST64( "0f0faec1 pfacc mm0,mm1", 0x0F, 0x0F, 0xAE, 0xC1 );

	// PF2ID
	// PF2ID mmreg1, mmreg2/mem64 0Fh 0Fh / 1Dh Converts packed floating-point operand to packed 32-bit integer
	_TEST32( "0f0f1d00 pf2id mm0,qword ptr [eax]", 0x0F, 0x0F, 0x1D, 0x00 );
	_TEST64( "0f0f1dc1 pf2id mm0,mm1", 0x0F, 0x0F, 0x1D, 0xC1 );

	// PAVGUSB
	// PAVGUSB mmreg1, mmreg2/mem64 0F 0Fh / BFh Average of unsigned packed 8-bit values
	_TEST32( "0f0fbf00 pavgusb mm0,qword ptr [eax]", 0x0F, 0x0F, 0xBF, 0x00 );
	_TEST64( "0f0fbfc1 pavgusb mm0,mm1", 0x0F, 0x0F, 0xBF, 0xC1 );

	// FEMMS
	_TEST64( "0f0e femms", 0x0F, 0x0E );
	_TEST32( "0f0e femms", 0x0F, 0x0E );

	// XSETBV
	// 0F 01 D1 XSETBV NP Valid Valid Write the value in EDX:EAX to the XCR specified by ECX.
	_TEST64( "0f01d1 xsetbv", 0x0F, 0x01, 0xD1 );
	_TEST32( "0f01d1 xsetbv", 0x0F, 0x01, 0xD1 );

	// XSAVEOPT
	// 0F AE /6 XSAVEOPT mem M V/V XSAVEOPT Save processor extended states specified in EDX:EAX to memory, optimizing the state save operation if possible.
	// REX.W + 0F AE /6 XSAVEOPT64 mem M V/V XSAVEOPT Save processor extended states specified in EDX:EAX to memory, optimizing the state save operation if possible.
	_TEST64( "0fae30 xsaveopt [rax]", 0x0F, 0xAE, 0x30 );
	_TEST32( "0fae30 xsaveopt [eax]", 0x0F, 0xAE, 0x30 );
	_TEST64( "660fae30 xsaveopt [rax]", 0x66, 0x0F, 0xAE, 0x30 );
	_TEST32( "660fae30 xsaveopt [eax]", 0x66, 0x0F, 0xAE, 0x30 );
	_TEST64( "480fae30 xsaveopt64 [rax]", 0x48, 0x0F, 0xAE, 0x30 );

	// XSAVE
	// 0F AE /4 XSAVE mem M Valid Valid Save processor extended states to memory. The states are specified by EDX:EAX
	// REX.W+ 0F AE /4 XSAVE64 mem M Valid N.E. Save processor extended states to memory. The states are specified by EDX:EAX
	_TEST64( "0fae20 xsave 512byte ptr [rax]", 0x0F, 0xAE, 0x20 );
	_TEST32( "0fae20 xsave 512byte ptr [eax]", 0x0F, 0xAE, 0x20 );
	_TEST64( "660fae20 xsave 512byte ptr [rax]", 0x66, 0x0F, 0xAE, 0x20 );
	_TEST32( "660fae20 xsave 512byte ptr [eax]", 0x66, 0x0F, 0xAE, 0x20 );
	_TEST64( "480fae20 xsave64 512byte ptr [rax]", 0x48, 0x0F, 0xAE, 0x20 );

	// FXRSTOR
	// 0F AE /5 XRSTOR mem M Valid Valid Restore processor extended states from memory. The states are specified by EDX:EAX
	// REX.W+ 0F AE /5 XRSTOR64 mem M Valid N.E. Restore processor extended states from memory. The states are specified by EDX:EAX
	_TEST64( "0fae28 xrstor 512byte ptr [rax]", 0x0F, 0xAE, 0x28 );
	_TEST32( "0fae28 xrstor 512byte ptr [eax]", 0x0F, 0xAE, 0x28 );
	_TEST64( "660fae28 xrstor 512byte ptr [rax]", 0x66, 0x0F, 0xAE, 0x28 );
	_TEST32( "660fae28 xrstor 512byte ptr [eax]", 0x66, 0x0F, 0xAE, 0x28 );
	_TEST64( "480fae28 xrstor64 512byte ptr [rax]", 0x48, 0x0F, 0xAE, 0x28 );

	// XORPS
	// 0F 57 /r XORPS xmm1,xmm2/m128
	_TEST64( "0f574020 xorps xmm0,oword ptr [rax+0000000000000020h]", 0x0F, 0x57, 0x40, 0x20 );
	_TEST32( "0f574020 xorps xmm0,oword ptr [eax+00000020h]", 0x0F, 0x57, 0x40, 0x20 );
	// VEX.NDS.128.0F.WIG 57 /r VXORPS xmm1,xmm2,xmm3/m128
	// VEX.NDS.256.0F.WIG 57 /r VXORPS ymm1,ymm2,ymm3/m256
	_TEST64_VEX( "c4410c571401 vxorps ymm10,ymm14,ymmword ptr [r9+rax]", 0xC4, 0x41, 0x0C, 0x57, 0x14, 0x01 );
	_TEST32_VEX( "c4c140571401 vxorps xmm2,xmm7,oword ptr [ecx+eax]", 0xC4, 0xC1, 0x40, 0x57, 0x14, 0x01 );
	_TEST32_VEX( "c4c168571401 vxorps xmm2,xmm2,oword ptr [ecx+eax]", 0xC4, 0xC1, 0x68, 0x57, 0x14, 0x01 );

	// XORPD
	// 66 0F 57 /r XORPD xmm1,xmm2/m128
	_TEST64( "660f574020 xorpd xmm0,oword ptr [rax+0000000000000020h]", 0x66, 0x0F, 0x57, 0x40, 0x20 );
	_TEST32( "660f574020 xorpd xmm0,oword ptr [eax+00000020h]", 0x66, 0x0F, 0x57, 0x40, 0x20 );
	// VEX.NDS.128.66.0F.WIG 57 /r VXORPD xmm1,xmm2,xmm3/m128
	// VEX.NDS.256.66.0F.WIG 57 /r VXORPD ymm1,ymm2,ymm3/m256
	_TEST64_VEX( "c4410d571401 vxorpd ymm10,ymm14,ymmword ptr [r9+rax]", 0xC4, 0x41, 0x0D, 0x57, 0x14, 0x01 );
	_TEST32_VEX( "c4c141571401 vxorpd xmm2,xmm7,oword ptr [ecx+eax]", 0xC4, 0xC1, 0x41, 0x57, 0x14, 0x01 );
	_TEST32_VEX( "c4c169571401 vxorpd xmm2,xmm2,oword ptr [ecx+eax]", 0xC4, 0xC1, 0x69, 0x57, 0x14, 0x01 );

	// 34 ib XOR AL, imm8 I Valid Valid AL XOR imm8.
	_TEST32( "34ff xor al,0ffh", 0x34, 0xff );
	// 35 iw XOR AX, imm16 I Valid Valid AX XOR imm16.
	// 35 id XOR EAX, imm32 I Valid Valid EAX XOR imm32.
	_TEST32( "6635ff11 xor ax,11ffh", 0x66, 0x35, 0xff, 0x11 );
	// REX.W + 35 id XOR RAX, imm32 I Valid N.E. RAX XOR imm32 (sign-extended).
	_TEST64( "4835ff117722 xor rax,00000000227711ffh", 0x48, 0x35, 0xff, 0x11, 0x77, 0x22 );
	// 80 /6 ib XOR r/m8, imm8 MI Valid Valid r/m8 XOR imm8.
	_TEST32( "803011 xor byte ptr [eax],11h", 0x80, 0x30, 0x11 );
	// REX + 80 /6 ib XOR r/m8*, imm8 MI Valid N.E. r/m8 XOR imm8.
	_TEST64( "48803030 xor byte ptr [rax],30h", 0x48, 0x80, 0x30, 0x30, 0xff  );
	// 81 /6 iw XOR r/m16, imm16 MI Valid Valid r/m16 XOR imm16.
	// 81 /6 id XOR r/m32, imm32 MI Valid Valid r/m32 XOR imm32.
	// REX.W + 81 /6 id XOR r/m64, imm32 MI Valid N.E. r/m64 XOR imm32 (sign-extended).
	_TEST64( "40813030ffff22 xor dword ptr [rax],22ffff30h", 0x40, 0x81, 0x30, 0x30, 0xff, 0xff, 0x22  );
	_TEST64( "48813030ffffff xor qword ptr [rax],0ffffffffffffff30h", 0x48, 0x81, 0x30, 0x30, 0xff, 0xff, 0xff  );
	// 83 /6 ib XOR r/m16, imm8 MI Valid Valid r/m16 XOR imm8 (sign-extended).
	// 83 /6 ib XOR r/m32, imm8 MI Valid Valid r/m32 XOR imm8 (sign-extended).
	// REX.W + 83 /6 ib XOR r/m64, imm8 MI Valid N.E. r/m64 XOR imm8 (sign-extended).
	_TEST64( "833030 xor dword ptr [rax],00000030h", 0x83, 0x30, 0x30  );
	_TEST64( "66833030 xor word ptr [rax],0030h", 0x66, 0x83, 0x30, 0x30  );
	_TEST64( "48833030 xor qword ptr [rax],0000000000000030h", 0x48, 0x83, 0x30, 0x30  );
	// 30 /r XOR r/m8, r8 MR Valid Valid r/m8 XOR r8.
	// REX + 30 /r XOR r/m8*, r8* MR Valid N.E. r/m8 XOR r8.
	_TEST64( "3030 xor byte ptr [rax],dh", 0x30, 0x30 );
	_TEST64( "483030 xor byte ptr [rax],sil", 0x48, 0x30, 0x30  );
	// 31 /r XOR r/m16, r16 MR Valid Valid r/m16 XOR r16.
	// 31 /r XOR r/m32, r32 MR Valid Valid r/m32 XOR r32.
	// REX.W + 31 /r XOR r/m64, r64 MR Valid N.E. r/m64 XOR r64.
	_TEST64( "3130 xor dword ptr [rax],esi", 0x31, 0x30  );
	_TEST64( "663130 xor word ptr [rax],si", 0x66, 0x31, 0x30 );
	_TEST64( "483130 xor qword ptr [rax],rsi", 0x48, 0x31, 0x30  );
	// 32 /r XOR r8, r/m8 RM Valid Valid r8 XOR r/m8.
	// REX + 32 /r XOR r8*, r/m8* RM Valid N.E. r8 XOR r/m8.
	_TEST64( "3230 xor dh,byte ptr [rax]", 0x32, 0x30  );
	_TEST64( "663230 xor dh,byte ptr [rax]", 0x66, 0x32, 0x30 );
	_TEST64( "483230 xor sil,byte ptr [rax]", 0x48, 0x32, 0x30  );
	// 33 /r XOR r16, r/m16 RM Valid Valid r16 XOR r/m16.
	// 33 /r XOR r32, r/m32 RM Valid Valid r32 XOR r/m32.
	// REX.W + 33 /r XOR r64, r/m64 RM Valid N.E. r64 XOR r/m64.
	_TEST64( "3330 xor esi,dword ptr [rax]", 0x33, 0x30  );
	_TEST64( "663330 xor si,word ptr [rax]", 0x66, 0x33, 0x30 );
	_TEST64( "483330 xor rsi,qword ptr [rax]", 0x48, 0x33, 0x30  );

	// XLAT
	// D7 XLAT m8 NP Valid Valid Set AL to memory byte DS:[(E)BX + unsigned AL].
	// D7 XLATB NP Valid Valid Set AL to memory byte DS:[(E)BX + unsigned AL].
	// REX.W + D7 XLATB NP Valid N.E. Set AL to memory byte [RBX + unsigned AL].
	_TEST32( "d7 xlat byte ptr [ebx]", 0xD7 );
	_TEST32( "67d7 xlat byte ptr [bx]", 0x67, 0xD7 );

	// XGETBV
	// 0F 01 D0 XGETBV NP Valid Valid Reads an XCR specified by ECX into EDX:EAX.
	_TEST32( "0f01d0 xgetbv", 0x0F, 0x01, 0xD0 );
	_TEST64( "0f01d0 xgetbv", 0x0F, 0x01, 0xD0 );

	// 90+rw XCHG AX, r16 O Valid Valid Exchange r16 with AX.
	// 90+rw XCHG r16, AX O Valid Valid Exchange AX with r16.
	// 90+rd XCHG EAX, r32 O Valid Valid Exchange r32 with EAX.
	// 90+rd XCHG r32, EAX O Valid Valid Exchange EAX with r32.
	// REX.W + 90+rd XCHG RAX, r64 O Valid N.E. Exchange r64 with RAX.
	// REX.W + 90+rd XCHG r64, RAX O Valid N.E. Exchange RAX with r64.
	_TEST32( "91 xchg eax,ecx", 0x91 );
	_TEST64( "91 xchg eax,ecx", 0x91 );
	_TEST64( "6691 xchg ax,cx", 0x66, 0x91 );
	_TEST64( "4891 xchg rax,rcx", 0x48, 0x91 );
	// 86 /r XCHG r/m8, r8 MR Valid Valid Exchange r8 (byte register) with byte from r/m8.
	// REX + 86 /r XCHG r/m8*, r8* MR Valid N.E. Exchange r8 (byte register) with byte from r/m8.
	// 86 /r XCHG r8, r/m8 RM Valid Valid Exchange byte from r/m8 with r8 (byte register).
	// REX + 86 /r XCHG r8*, r/m8* RM Valid N.E. Exchange byte from r/m8 with r8 (byte register).
	_TEST32( "8600 xchg byte ptr [eax],al", 0x86, 0x00 );
	_TEST32( "86c0 xchg al,al", 0x86, 0xC0 );
	// 87 /r XCHG r/m16, r16 MR Valid Valid Exchange r16 with word from r/m16.
	// 87 /r XCHG r16, r/m16 RM Valid Valid Exchange word from r/m16 with r16.
	// 87 /r XCHG r/m32, r32 MR Valid Valid Exchange r32 with doubleword from r/m32.
	// 87 /r XCHG r32, r/m32 RM Valid Valid Exchange doubleword from r/m32 with r32.
	// REX.W + 87 /r XCHG r/m64, r64 MR Valid N.E. Exchange r64 with quadword from r/m64.
	// REX.W + 87 /r XCHG r64, r/m64 RM Valid N.E. Exchange quadword from r/m64 with r64.
	_TEST32( "8700 xchg dword ptr [eax],eax", 0x87, 0x00 );
	_TEST32( "87c0 xchg eax,eax", 0x87, 0xC0 );
	_TEST32( "6687c0 xchg ax,ax", 0x66, 0x87, 0xC0 );
	_TEST64( "4887c0 xchg rax,rax", 0x48, 0x87, 0xC0 );

	// XADD
	// 0F C0 /r XADD r/m8,r8 MR Valid Valid Exchange r8 and r/m8; load sum into r/m8.
	// REX + 0F C0 /r XADD r/m8*,r8* MR Valid N.E. Exchange r8 and r/m8; load sum into r/m8.
	_TEST64( "480fc010 xadd byte ptr [rax],dl", 0x48, 0x0F, 0xC0, 0x10 );
	_TEST32( "0fc010 xadd byte ptr [eax],dl", 0x0F, 0xC0, 0x10 );
	// 0F C1 /r XADD r/m16,r16 MR Valid Valid Exchange r16 and r/m16; load sum into r/m16.
	// 0F C1 /r XADD r/m32,r32 MR Valid Valid Exchange r32 and r/m32; load sum into r/m32.
	// REX.W + 0F C1 /r XADD r/m64,r64 MR Valid N.E. Exchange r64 and r/m64; load sum into r/m64.
	_TEST64( "480fc110 xadd qword ptr [rax],rdx", 0x48, 0x0F, 0xC1, 0x10 );
	_TEST32( "0fc110 xadd dword ptr [eax],edx", 0x0F, 0xC1, 0x10 );
	_TEST32( "660fc110 xadd word ptr [eax],dx", 0x66, 0x0F, 0xC1, 0x10 );

	// WRMSR
	// 0F 30 WRMSR NP Valid Valid Write the value in EDX:EAX to MSR specified by ECX.
	_TEST32_VEX( "0f30 wrmsr", 0x0F, 0x30 );
	_TEST64_VEX( "0f30 wrmsr", 0x0F, 0x30 );

	// WRFSBASE
	// F3 0F AE /2 WRFSBASE r32 M V/I FSGSBASE Load the FS base address with the 32-bit value in the source register.
	// REX.W + F3 0F AE /2 WRFSBASE r64 M V/I FSGSBASE Load the FS base address with the 64-bit value in the source register.
	_TEST64_VEX( "f30faed0 wrfsbase eax", 0xF3, 0x0F, 0xAE, 0xD0 );
	_TEST64_VEX( "66f30faed0 wrfsbase eax", 0x66, 0xF3, 0x0F, 0xAE, 0xD0 );
	_TEST64_VEX( "f3480faed0 wrfsbase rax", 0xF3, 0x48, 0x0F, 0xAE, 0xD0 );
	// F3 0F AE /3 WRGSBASE r32 M V/I FSGSBASE Load the GS base address with the 32-bit value in the source register.
	// REX.W + F3 0F AE /3 WRGSBASE r64 M V/I FSGSBASE Load the GS base address with the 64-bit value in the source register.
	_TEST64_VEX( "f30faed8 wrgsbase eax", 0xF3, 0x0F, 0xAE, 0xD8 );
	_TEST64_VEX( "66f30faed8 wrgsbase eax", 0x66, 0xF3, 0x0F, 0xAE, 0xD8 );
	_TEST64_VEX( "f3480faed8 wrgsbase rax", 0xF3, 0x48, 0x0F, 0xAE, 0xD8 );

	// WBINVD
	// 0F 09 WBINVD NP Valid Valid Write back and flush Internal caches; initiate writing-back and flushing of external caches.
	_TEST64_VEX( "0f09 wbinvd", 0x0F, 0x09 );
	_TEST32_VEX( "0f09 wbinvd", 0x0F, 0x09 );

	// WAIT
	// 9B WAIT NP Valid Valid Check pending unmasked floating-point exceptions.
	// 9B FWAIT NP Valid Valid Check pending unmasked floating-point exceptions.
	_TEST64_VEX( "9b wait", 0x9B );
	_TEST32_VEX( "9b wait", 0x9B );

	// VZEROUPPER
	// VEX.128.0F.WIG 77 VZEROUPPER NP V/V AVX Zero upper 128 bits of all YMM registers.
	_TEST64_VEX( "c4e17877 vzeroupper", 0xC4, 0xE1, 0x78, 0x77 );
	_TEST32_VEX( "c4e17877 vzeroupper", 0xC4, 0xE1, 0x78, 0x77 );

	// VZEROALL
	// VEX.256.0F.WIG 77 VZEROALL NP V/V AVX Zero all YMM registers.
	_TEST64_VEX( "c4e17c77 vzeroall", 0xC4, 0xE1, 0x7C, 0x77 );
	_TEST32_VEX( "c4e17c77 vzeroall", 0xC4, 0xE1, 0x7C, 0x77 );

	// VEX.128.66.0F38.W0 0E /r VTESTPS xmm1,xmm2/m128 RM V/V AVX Set ZF and CF depending on sign bit AND and ANDN of packed single-precision floatingpoint sources.
	// VEX.256.66.0F38.W0 0E /r VTESTPS ymm1,ymm2/m256 RM V/V AVX Set ZF and CF depending on sign bit AND and ANDN of packed single-precision floatingpoint sources.
	_TEST64_VEX( "c4e2790ec8 vtestps xmm1,xmm0", 0xC4, 0xE2, 0x79, 0x0E, 0xC8 );
	_TEST32_VEX( "c4e2790ec8 vtestps xmm1,xmm0", 0xC4, 0xE2, 0x79, 0x0E, 0xC8 );
	_TEST32_VEX( "c4e2790e00 vtestps xmm0,oword ptr [eax]", 0xC4, 0xE2, 0x79, 0x0E, 0x00 );
	_TEST32_VEX( "c4e27d0e00 vtestps ymm0,ymmword ptr [eax]", 0xC4, 0xE2, 0x7D, 0x0E, 0x00 );
	// VEX.128.66.0F38.W0 0F /r VTESTPD xmm1,xmm2/m128 RM V/V AVX Set ZF and CF depending on sign bit AND and ANDN of packed double-precision floatingpoint sources.
	// VEX.256.66.0F38.W0 0F /r VTESTPD ymm1,ymm2/m256 RM V/V AVX Set ZF and CF depending on sign bit AND and ANDN of packed double-precision floatingpoint sources.
	_TEST64_VEX( "c4e2790fc0 vtestpd xmm0,xmm0", 0xC4, 0xE2, 0x79, 0x0f, 0xC0 );
	_TEST32_VEX( "c4e2790fc0 vtestpd xmm0,xmm0", 0xC4, 0xE2, 0x79, 0x0f, 0xC0 );
	_TEST32_VEX( "c4e2790f00 vtestpd xmm0,oword ptr [eax]", 0xC4, 0xE2, 0x79, 0x0F, 0x00 );
	_TEST32_VEX( "c4e27d0f00 vtestpd ymm0,ymmword ptr [eax]", 0xC4, 0xE2, 0x7D, 0x0F, 0x00 );

	// VPSLLVD
	// VEX.NDS.128.66.0F38.W0 47 /r VPSLLVD xmm1,xmm2,xmm3/m128
	// VEX.NDS.256.66.0F38.W0 47 /r VPSLLVD ymm1,ymm2,ymm3/m256
	_TEST32_VEX( "c4e2494700 vpsllvd xmm0,xmm6,oword ptr [eax]", 0xC4, 0xE2, 0x49, 0x47, 0x00 );
	_TEST32_VEX( "c4e24d4700 vpsllvd ymm0,ymm6,ymmword ptr [eax]", 0xC4, 0xE2, 0x4D, 0x47, 0x00 );
	_TEST32_VEX( "c4e24d47c0 vpsllvd ymm0,ymm6,ymm0", 0xC4, 0xE2, 0x4D, 0x47, 0xC0 );
	// VEX.NDS.128.66.0F38.W1 47 /r VPSLLVQ xmm1,xmm2,xmm3/m128
	// VEX.NDS.256.66.0F38.W1 47 /r VPSLLVQ ymm1,ymm2,ymm3/m256
	_TEST32_VEX( "c4e2c94700 vpsllvq xmm0,xmm6,oword ptr [eax]", 0xC4, 0xE2, 0xC9, 0x47, 0x00 );
	_TEST32_VEX( "c4e2cd4700 vpsllvq ymm0,ymm6,ymmword ptr [eax]", 0xC4, 0xE2, 0xCD, 0x47, 0x00 );
	_TEST32_VEX( "c4e2cd47c0 vpsllvq ymm0,ymm6,ymm0", 0xC4, 0xE2, 0xCD, 0x47, 0xC0 );

	// VPSRAVD
	// VEX.NDS.128.66.0F38.W0 46 /r VPSRAVD xmm1,xmm2,xmm3/m128
	// VEX.NDS.256.66.0F38.W0 46 /r VPSRAVD ymm1,ymm2,ymm3/m256
	_TEST32_VEX( "c4e2494600 vpsravd xmm0,xmm6,oword ptr [eax]", 0xC4, 0xE2, 0x49, 0x46, 0x00 );
	_TEST32_VEX( "c4e24d4600 vpsravd ymm0,ymm6,ymmword ptr [eax]", 0xC4, 0xE2, 0x4D, 0x46, 0x00 );
	_TEST32_VEX( "c4e24d46c0 vpsravd ymm0,ymm6,ymm0", 0xC4, 0xE2, 0x4D, 0x46, 0xC0 );

	// VPSRLVD
	// VEX.NDS.128.66.0F38.W0 45 /r VPSRLVD xmm1,xmm2,xmm3/m128
	// VEX.NDS.256.66.0F38.W0 45 /r VPSRLVD ymm1,ymm2,ymm3/m256
	_TEST32_VEX( "c4e2494500 vpsrlvd xmm0,xmm6,oword ptr [eax]", 0xC4, 0xE2, 0x49, 0x45, 0x00 );
	_TEST32_VEX( "c4e24d4500 vpsrlvd ymm0,ymm6,ymmword ptr [eax]", 0xC4, 0xE2, 0x4D, 0x45, 0x00 );
	_TEST32_VEX( "c4e24d45c0 vpsrlvd ymm0,ymm6,ymm0", 0xC4, 0xE2, 0x4D, 0x45, 0xC0 );
	// VEX.NDS.128.66.0F38.W1 45 /r VPSRLVQ xmm1,xmm2,xmm3/m128
	// VEX.NDS.256.66.0F38.W1 45 /r VPSRLVQ ymm1,ymm2,ymm3/m256
	_TEST32_VEX( "c4e2c94500 vpsrlvq xmm0,xmm6,oword ptr [eax]", 0xC4, 0xE2, 0xC9, 0x45, 0x00 );
	_TEST32_VEX( "c4e2cd4500 vpsrlvq ymm0,ymm6,ymmword ptr [eax]", 0xC4, 0xE2, 0xCD, 0x45, 0x00 );
	_TEST32_VEX( "c4e2cd45c0 vpsrlvq ymm0,ymm6,ymm0", 0xC4, 0xE2, 0xCD, 0x45, 0xC0 );

	// VGATHERDPD
	// VEX.DDS.128.66.0F38.W1 92 /r VGATHERDPD xmm1, vm32x, xmm2
	// VEX.DDS.256.66.0F38.W1 92 /r VGATHERDPD ymm1, vm32x, ymm2
	_TEST32_VEX( "c4e2f9920428 vgatherdpd xmm0,dword ptr [eax+xmm5],xmm0", 0xC4, 0xE2, 0xF9, 0x92, 0x04, 0x28 );
	_TEST32_VEX( "c4e2fd920428 vgatherdpd ymm0,dword ptr [eax+xmm5],ymm0", 0xC4, 0xE2, 0xFD, 0x92, 0x04, 0x28 );
	// VEX.DDS.128.66.0F38.W1 93 /r VGATHERQPD xmm1, vm64x, xmm2
	// VEX.DDS.256.66.0F38.W1 93 /r VGATHERQPD ymm1, vm64y, ymm2
	_TEST32_VEX( "c4e2f9930428 vgatherqpd xmm0,qword ptr [eax+xmm5],xmm0", 0xC4, 0xE2, 0xF9, 0x93, 0x04, 0x28 );
	_TEST32_VEX( "c4e2fd930428 vgatherqpd ymm0,qword ptr [eax+ymm5],ymm0", 0xC4, 0xE2, 0xFD, 0x93, 0x04, 0x28 );

	// VGATHERDPS
	// VEX.DDS.128.66.0F38.W0 92 /r VGATHERDPS xmm1,vm32x,xmm2
	// VEX.DDS.256.66.0F38.W0 92 /r VGATHERDPS ymm1,vm32y,ymm2
	_TEST32_VEX( "c4e279920428 vgatherdps xmm0,dword ptr [eax+xmm5],xmm0", 0xC4, 0xE2, 0x79, 0x92, 0x04, 0x28 );
	_TEST32_VEX( "c4e27d920428 vgatherdps ymm0,dword ptr [eax+ymm5],ymm0", 0xC4, 0xE2, 0x7D, 0x92, 0x04, 0x28 );
	// VEX.DDS.128.66.0F38.W0 93 /r VGATHERQPS xmm1,vm64x,xmm2
	// VEX.DDS.256.66.0F38.W0 93 /r VGATHERQPS xmm1,vm64y,xmm2
	_TEST32_VEX( "c4e279930428 vgatherqps xmm0,qword ptr [eax+xmm5],xmm0", 0xC4, 0xE2, 0x79, 0x93, 0x04, 0x28 );
	_TEST32_VEX( "c4e27d930428 vgatherqps ymm0,qword ptr [eax+ymm5],ymm0", 0xC4, 0xE2, 0x7D, 0x93, 0x04, 0x28 );

	// VPGATHERDD
	// VEX.DDS.128.66.0F38.W0 90 /r VPGATHERDD xmm1,vm32x,xmm2
	// VEX.DDS.256.66.0F38.W0 90 /r VPGATHERDD ymm1,vm32y,ymm2
	_TEST32_VEX( "c4e279900428 vpgatherdd xmm0,dword ptr [eax+xmm5],xmm0", 0xC4, 0xE2, 0x79, 0x90, 0x04, 0x28 );
	_TEST32_VEX( "c4e27d900428 vpgatherdd ymm0,dword ptr [eax+ymm5],ymm0", 0xC4, 0xE2, 0x7D, 0x90, 0x04, 0x28 );
	// VEX.DDS.128.66.0F38.W0 91 /r VPGATHERQD xmm1,vm64x,xmm2
	// VEX.DDS.256.66.0F38.W0 91 /r VPGATHERQD xmm1,vm64y,xmm2
	_TEST32_VEX( "c4e279910428 vpgatherqd xmm0,qword ptr [eax+xmm5],xmm0", 0xC4, 0xE2, 0x79, 0x91, 0x04, 0x28 );
	_TEST32_VEX( "c4e27d910428 vpgatherqd ymm0,qword ptr [eax+ymm5],ymm0", 0xC4, 0xE2, 0x7D, 0x91, 0x04, 0x28 );

	// VPGATHERDQ
	// VEX.DDS.128.66.0F38.W1 90 /r VPGATHERDQ xmm1,vm32x,xmm2
	// VEX.DDS.256.66.0F38.W1 90 /r VPGATHERDQ ymm1,vm32x,ymm2
	_TEST32_VEX( "c4e2f9900428 vpgatherdq xmm0,dword ptr [eax+xmm5],xmm0", 0xC4, 0xE2, 0xF9, 0x90, 0x04, 0x28 );
	_TEST32_VEX( "c4e2fd900428 vpgatherdq ymm0,dword ptr [eax+xmm5],ymm0", 0xC4, 0xE2, 0xFD, 0x90, 0x04, 0x28 );
	// VEX.DDS.128.66.0F38.W1 91 /r VPGATHERQQ xmm1,vm64x,xmm2
	// VEX.DDS.256.66.0F38.W1 91 /r VPGATHERQQ ymm1,vm64y,ymm2
	_TEST32_VEX( "c4e2f9910428 vpgatherqq xmm0,qword ptr [eax+xmm5],xmm0", 0xC4, 0xE2, 0xF9, 0x91, 0x04, 0x28 );
	_TEST32_VEX( "c4e2fd910428 vpgatherqq ymm0,qword ptr [eax+ymm5],ymm0", 0xC4, 0xE2, 0xFD, 0x91, 0x04, 0x28 );

	// VPERMD
	// VEX.NDS.256.66.0F38.W0 36 /r VPERMD ymm1,ymm2,ymm3/m256
	_TEST32_VEX( "c4e24d3600 vpermd ymm0,ymm6,ymmword ptr [eax]", 0xC4, 0xE2, 0x4D, 0x36, 0x00 );
	_TEST32_VEX( "c4e24d36c0 vpermd ymm0,ymm6,ymm0", 0xC4, 0xE2, 0x4D, 0x36, 0xC0 );
	_TEST64_VEX( "c4e24d3600 vpermd ymm0,ymm6,ymmword ptr [rax]", 0xC4, 0xE2, 0x4D, 0x36, 0x00 );

	// VPERMPD
	// VEX.256.66.0F3A.W1 01 /r ib VPERMPD ymm1,ymm2/m256,imm8
	_TEST32_VEX( "c4e3fd0100ff vpermpd ymm0,ymmword ptr [eax],0ffh", 0xC4, 0xE3, 0xFD, 0x01, 0x00, 0xFF );
	_TEST32_VEX( "c4e3fd01c0ff vpermpd ymm0,ymm0,0ffh", 0xC4, 0xE3, 0xFD, 0x01, 0xC0, 0xFF );

	// VPERMQ
	// VEX.256.66.0F3A.W1 00 /r ib VPERMQ ymm1,ymm2/m256,imm8
	_TEST32_VEX( "c4e3fd0000ff vpermq ymm0,ymmword ptr [eax],0ffh", 0xC4, 0xE3, 0xFD, 0x00, 0x00, 0xFF );
	_TEST32_VEX( "c4e3fd00c0ff vpermq ymm0,ymm0,0ffh", 0xC4, 0xE3, 0xFD, 0x00, 0xC0, 0xFF );

	// VPERMPS
	// VEX.NDS.256.66.0F38.W0 16 /r VPERMPS ymm1,ymm2,ymm3/m256
	_TEST32_VEX( "c4e24d1600 vpermps ymm0,ymm6,ymmword ptr [eax]", 0xC4, 0xE2, 0x4D, 0x16, 0x00 );
	_TEST32_VEX( "c4e24d16c0 vpermps ymm0,ymm6,ymm0", 0xC4, 0xE2, 0x4D, 0x16, 0xC0 );
	_TEST64_VEX( "c4e24d1600 vpermps ymm0,ymm6,ymmword ptr [rax]", 0xC4, 0xE2, 0x4D, 0x16, 0x00 );

	// VPERM2F128
	// VEX.NDS.256.66.0F3A.W0 06 /r ib VPERM2F128 ymm1,ymm2,ymm3/m256,imm8 RVMI V/V AVX Permute 128-bit floating-point fields in ymm2 and ymm3/mem using controls from imm8 and store result in ymm1.
	_TEST32_VEX( "c4e34d0600ff vperm2f128 ymm0,ymm6,ymmword ptr [eax],0ffh", 0xC4, 0xE3, 0x4D, 0x06, 0x00, 0xFF );
	_TEST32_VEX( "c4e34d06c0ff vperm2f128 ymm0,ymm6,ymm0,0ffh", 0xC4, 0xE3, 0x4D, 0x06, 0xC0, 0xFF );
	_TEST64_VEX( "c4e34d0600ff vperm2f128 ymm0,ymm6,ymmword ptr [rax],0ffh", 0xC4, 0xE3, 0x4D, 0x06, 0x00, 0xFF );

	// VPERM2I128
	// VEX.NDS.256.66.0F3A.W0 46 /r ib VPERM2I128 ymm1,ymm2,ymm3/m256,imm8
	_TEST32_VEX( "c4e34d4600ff vperm2i128 ymm0,ymm6,ymmword ptr [eax],0ffh", 0xC4, 0xE3, 0x4D, 0x46, 0x00, 0xFF );
	_TEST32_VEX( "c4e34d46c0ff vperm2i128 ymm0,ymm6,ymm0,0ffh", 0xC4, 0xE3, 0x4D, 0x46, 0xC0, 0xFF );
	_TEST64_VEX( "c4e34d4600ff vperm2i128 ymm0,ymm6,ymmword ptr [rax],0ffh", 0xC4, 0xE3, 0x4D, 0x46, 0x00, 0xFF );

	// VEX.256.66.0F3A.W0 39 /r ib VEXTRACTI128 xmm1/m128,ymm2,imm8
	_TEST32_VEX( "c4e37d3900ff vextracti128 oword ptr [eax],ymm0,0ffh", 0xC4, 0xE3, 0x7D, 0x39, 0x00, 0xFF );
	_TEST64_VEX( "c4e37d39c0ff vextracti128 xmm0,ymm0,0ffh", 0xC4, 0xE3, 0x7D, 0x39, 0xC0, 0xFF );

	// VEX.NDS.256.66.0F3A.W0 38 /r ib VINSERTI128 ymm1,ymm2,xmm3/m128,imm8
	_TEST32_VEX( "c4e34d3800ff vinserti128 ymm0,ymm6,ymmword ptr [eax],0ffh", 0xC4, 0xE3, 0x4D, 0x38, 0x00, 0xFF );
	_TEST32_VEX( "c4e34d38c0ff vinserti128 ymm0,ymm6,ymm0,0ffh", 0xC4, 0xE3, 0x4D, 0x38, 0xC0, 0xFF );
	_TEST64_VEX( "c4e34d3800ff vinserti128 ymm0,ymm6,ymmword ptr [rax],0ffh", 0xC4, 0xE3, 0x4D, 0x38, 0x00, 0xFF );

	// VPMASKMOVD/VPMASKMOVQ
	// VEX.NDS.128.66.0F38.W0 8C /r VPMASKMOVD xmm1,xmm2,m128
	// VEX.NDS.256.66.0F38.W0 8C /r VPMASKMOVD ymm1,ymm2,m256
	// VEX.NDS.128.66.0F38.W1 8C /r VPMASKMOVQ xmm1,xmm2,m128
	// VEX.NDS.256.66.0F38.W1 8C /r VPMASKMOVQ ymm1,ymm2,m256
	_TEST64_VEX( "c4e2698c18 vpmaskmovd xmm3,xmm2,oword ptr [rax]", 0xC4, 0xE2, 0x69, 0x8C, 0x18 );
	_TEST32_VEX( "c4e26d8c18 vpmaskmovd ymm3,ymm2,ymmword ptr [eax]", 0xC4, 0xE2, 0x6D, 0x8C, 0x18 );
	_TEST64_VEX( "c4e2e98c18 vpmaskmovq xmm3,xmm2,oword ptr [rax]", 0xC4, 0xE2, 0xE9, 0x8C, 0x18 );
	_TEST32_VEX( "c4e2ed8c18 vpmaskmovq ymm3,ymm2,ymmword ptr [eax]", 0xC4, 0xE2, 0xED, 0x8C, 0x18 );
	// VEX.NDS.128.66.0F38.W0 8E /r VPMASKMOVD m128,xmm1,xmm2
	// VEX.NDS.256.66.0F38.W0 8E /r VPMASKMOVD m256,ymm1,ymm2
	// VEX.NDS.128.66.0F38.W1 8E /r VPMASKMOVQ m128,xmm1,xmm2
	// VEX.NDS.256.66.0F38.W1 8E /r VPMASKMOVQ m256,ymm1,ymm2
	_TEST64_VEX( "c4e2698e18 vpmaskmovd oword ptr [rax],xmm2,xmm3", 0xC4, 0xE2, 0x69, 0x8E, 0x18 );
	_TEST32_VEX( "c4e26d8e18 vpmaskmovd ymmword ptr [eax],ymm2,ymm3", 0xC4, 0xE2, 0x6D, 0x8E, 0x18 );
	_TEST64_VEX( "c4e2e98e18 vpmaskmovq oword ptr [rax],xmm2,xmm3", 0xC4, 0xE2, 0xE9, 0x8E, 0x18 );
	_TEST32_VEX( "c4e2ed8e18 vpmaskmovq ymmword ptr [eax],ymm2,ymm3", 0xC4, 0xE2, 0xED, 0x8E, 0x18 );

	// VPERMILPS
	// VEX.NDS.128.66.0F38.W0 0C /r VPERMILPS xmm1,xmm2,xmm3/m128 RVM V/V AVX Permute single-precision floating-point values in xmm2 using controls from xmm3/mem and store result in xmm1.
	// VEX.NDS.256.66.0F38.W0 0C /r VPERMILPS ymm1,ymm2,ymm3/m256 RVM V/V AVX Permute single-precision floating-point values in ymm2 using controls from ymm3/mem and store result in ymm1.
	_TEST32_VEX( "c4e2490c00 vpermilps xmm0,xmm6,oword ptr [eax]", 0xC4, 0xE2, 0x49, 0x0C, 0x00 );
	_TEST32_VEX( "c4e2490cc0 vpermilps xmm0,xmm6,xmm0", 0xC4, 0xE2, 0x49, 0x0C, 0xC0 );
	_TEST64_VEX( "c4e24d0c00 vpermilps ymm0,ymm6,ymmword ptr [rax]", 0xC4, 0xE2, 0x4D, 0x0C, 0x00 );
	// VEX.128.66.0F3A.W0 04 /r ib VPERMILPS xmm1,xmm2/m128,imm8 RMI V/V AVX Permute single-precision floating-point values in xmm2/mem using controls from imm8 and store result in xmm1.
	// VEX.256.66.0F3A.W0 04 /r ib VPERMILPS ymm1,ymm2/m256,imm8 RMI V/V AVX Permute single-precision floating-point values in ymm2/mem using controls from imm8 and store result in ymm1.
	_TEST32_VEX( "c4e3490400ff vpermilps xmm0,oword ptr [eax],0ffh", 0xC4, 0xE3, 0x49, 0x04, 0x00, 0xFF );
	_TEST32_VEX( "c4e34904c0ff vpermilps xmm0,xmm0,0ffh", 0xC4, 0xE3, 0x49, 0x04, 0xC0, 0xFF );
	_TEST64_VEX( "c4e34d0400ff vpermilps ymm0,ymmword ptr [rax],0ffh", 0xC4, 0xE3, 0x4D, 0x04, 0x00, 0xFF );

	// VPERMILPD
	// VEX.NDS.128.66.0F38.W0 0D /r VPERMILPD xmm1,xmm2,xmm3/m128 RVM V/V AVX Permute double-precision floating-point values in xmm2 using controls from xmm3/mem and store result in xmm1.
	// VEX.NDS.256.66.0F38.W0 0D /r VPERMILPD ymm1,ymm2,ymm3/m256 RVM V/V AVX Permute double-precision floating-point values in ymm2 using controls from ymm3/mem and store result in ymm1.
	_TEST32_VEX( "c4e2490d00 vpermilpd xmm0,xmm6,oword ptr [eax]", 0xC4, 0xE2, 0x49, 0x0D, 0x00 );
	_TEST32_VEX( "c4e2490dc0 vpermilpd xmm0,xmm6,xmm0", 0xC4, 0xE2, 0x49, 0x0D, 0xC0 );
	_TEST64_VEX( "c4e24d0d00 vpermilpd ymm0,ymm6,ymmword ptr [rax]", 0xC4, 0xE2, 0x4D, 0x0D, 0x00 );
	// VEX.128.66.0F3A.W0 05 /r ib VPERMILPD xmm1,xmm2/m128,imm8 RMI V/V AVX Permute double-precision floating-point values in xmm2/mem using controls from imm8.
	// VEX.256.66.0F3A.W0 05 /r ib VPERMILPD ymm1,ymm2/m256,imm8 RMI V/V AVX Permute double-precision floating-point values in ymm2/mem using controls from imm8.
	_TEST32_VEX( "c4e3490500ff vpermilpd xmm0,oword ptr [eax],0ffh", 0xC4, 0xE3, 0x49, 0x05, 0x00, 0xFF );
	_TEST32_VEX( "c4e34905c0ff vpermilpd xmm0,xmm0,0ffh", 0xC4, 0xE3, 0x49, 0x05, 0xC0, 0xFF );
	_TEST64_VEX( "c4e34d0500ff vpermilpd ymm0,ymmword ptr [rax],0ffh", 0xC4, 0xE3, 0x4D, 0x05, 0x00, 0xFF );

	// VERR
	// 0F 00 /4 VERR r/m16 M Valid Valid Set ZF=1 if segment specified with r/m16 can be read.
	_TEST32( "0f0020 verr word ptr [eax]", 0x0F, 0x00, 0x20 );
	_TEST32( "0f00e0 verr ax", 0x0F, 0x00, 0xE0 );
	_TEST32( "660f00e0 verr ax", 0x66, 0x0F, 0x00, 0xE0 );
	_TEST64( "0f0020 verr word ptr [rax]", 0x0F, 0x00, 0x20 );
	// 0F 00 /5 VERW r/m16 M Valid Valid Set ZF=1 if segment specified with r/m16 can be written.
	_TEST32( "0f0028 verw word ptr [eax]", 0x0F, 0x00, 0x28 );
	_TEST32( "0f00e8 verw ax", 0x0F, 0x00, 0xE8 );
	_TEST32( "660f00e8 verw ax", 0x66, 0x0F, 0x00, 0xE8 );
	_TEST64( "0f0028 verw word ptr [rax]", 0x0F, 0x00, 0x28 );

	// VCVTPS2PH
	// VEX.128.66.0F3A.W0.1D /r VCVTPS2PH xmm1/m64,xmm2,imm8 ib MR V/V F16C Convert four packed single-precision floating-point value in xmm2 to packed halfprecision (16-bit) floating-point value in xmm1/mem. Imm8 provides rounding controls.
	_TEST32_VEX( "c4e3791d00ff vcvtps2ph qword ptr [eax],xmm0,0ffh", 0xC4, 0xE3, 0x79, 0x1D, 0x00, 0xFF );
	_TEST32_VEX( "c4e3791dc0ff vcvtps2ph xmm0,xmm0,0ffh", 0xC4, 0xE3, 0x79, 0x1D, 0xC0, 0xFF );
	// VEX.256.66.0F3A.W0 1D /r VCVTPS2PH xmm1/m128,ymm2,imm8 ib MR V/V F16C Convert eight packed single-precision floating-point value in ymm2 to packed half-precision (16-bit) floating-point value in xmm1/mem. Imm8 provides rounding controls.
	_TEST32_VEX( "c4e37d1d00ff vcvtps2ph oword ptr [eax],xmm0,0ffh", 0xC4, 0xE3, 0x7D, 0x1D, 0x00, 0xFF );
	_TEST64_VEX( "c4e37d1dc0ff vcvtps2ph xmm0,xmm0,0ffh", 0xC4, 0xE3, 0x7D, 0x1D, 0xC0, 0xFF );

	// VEX.128.66.0F38.W0 13 /r VCVTPH2PS xmm1,xmm2/m64 RM V/V F16C Convert four packed half precision (16-bit) floating-point values in xmm2/m64 to packed single-precision floating-point value in xmm1.
	_TEST32_VEX( "c4e2791300 vcvtph2ps xmm0,qword ptr [eax]", 0xC4, 0xE2, 0x79, 0x13, 0x00 );
	_TEST32_VEX( "c4e27913c0 vcvtph2ps xmm0,xmm0", 0xC4, 0xE2, 0x79, 0x13, 0xC0 );
	// VEX.256.66.0F38.W0 13 /r VCVTPH2PS ymm1,xmm2/m128 RM V/V F16C Convert eight packed half precision (16-bit) floating-point values in xmm2/m128 to packed single-precision floating-point value in ymm1.
	_TEST32_VEX( "c4e27d1300 vcvtph2ps xmm0,oword ptr [eax]", 0xC4, 0xE2, 0x7D, 0x13, 0x00 );
	_TEST64_VEX( "c4e27d13c0 vcvtph2ps xmm0,xmm0", 0xC4, 0xE2, 0x7D, 0x13, 0xC0 );

	// 66 0F 15 /r UNPCKHPD xmm1,xmm2/m128
	_TEST32( "660f1500 unpckhpd xmm0,oword ptr [eax]", 0x66, 0x0F, 0x15, 0x00 );
	_TEST32( "660f15c0 unpckhpd xmm0,xmm0",  0x66, 0x0F, 0x15, 0xC0 );
	_TEST64( "660f1500 unpckhpd xmm0,oword ptr [rax]", 0x66, 0x0F, 0x15, 0x00 );
	// VEX.NDS.128.66.0F.WIG 15 /r VUNPCKHPD xmm1,xmm2,xmm3/m128
	// VEX.NDS.256.66.0F.WIG 15 /r VUNPCKHPD ymm1,ymm2,ymm3/m256
	_TEST32_VEX( "c4e1491500 vunpckhpd xmm0,xmm6,oword ptr [eax]", 0xC4, 0xE1, 0x49, 0x15, 0x00 );
	_TEST32_VEX( "c4e14915c0 vunpckhpd xmm0,xmm6,xmm0", 0xC4, 0xE1, 0x49, 0x15, 0xC0 );
	_TEST64_VEX( "c4e1491500 vunpckhpd xmm0,xmm6,oword ptr [rax]", 0xC4, 0xE1, 0x49, 0x15, 0x00 );
	_TEST64_VEX( "c4e14d1500 vunpckhpd ymm0,ymm6,ymmword ptr [rax]", 0xC4, 0xE1, 0x4D, 0x15, 0x00 );

	// UNPCKHPS
	// 0F 15 /r UNPCKHPS xmm1,xmm2/m128
	_TEST32( "0f1500 unpckhps xmm0,oword ptr [eax]", 0x0F, 0x15, 0x00 );
	_TEST32( "0f15c0 unpckhps xmm0,xmm0", 0x0F, 0x15, 0xC0 );
	_TEST64( "0f1500 unpckhps xmm0,oword ptr [rax]", 0x0F, 0x15, 0x00 );
	// VEX.NDS.128.0F.WIG 15 /r VUNPCKHPS xmm1,xmm2,xmm3/m128
	// VEX.NDS.256.0F.WIG 15 /r VUNPCKHPS ymm1,ymm2,ymm3/m256
	_TEST32_VEX( "c4e1481500 vunpckhps xmm0,xmm6,oword ptr [eax]", 0xC4, 0xE1, 0x48, 0x15, 0x00 );
	_TEST32_VEX( "c4e14815c0 vunpckhps xmm0,xmm6,xmm0", 0xC4, 0xE1, 0x48, 0x15, 0xC0 );
	_TEST64_VEX( "c4e1481500 vunpckhps xmm0,xmm6,oword ptr [rax]", 0xC4, 0xE1, 0x48, 0x15, 0x00 );

	// 66 0F 14 /r UNPCKLPD xmm1,xmm2/m128
	_TEST32( "660f1400 unpcklpd xmm0,oword ptr [eax]", 0x66, 0x0F, 0x14, 0x00 );
	_TEST32( "660f14c0 unpcklpd xmm0,xmm0",  0x66, 0x0F, 0x14, 0xC0 );
	_TEST64( "660f1400 unpcklpd xmm0,oword ptr [rax]", 0x66, 0x0F, 0x14, 0x00 );
	// VEX.NDS.128.66.0F.WIG 14 /r VUNPCKLPD xmm1,xmm2,xmm3/m128
	// VEX.NDS.256.66.0F.WIG 14 /r VUNPCKLPD ymm1,ymm2,ymm3/m256
	_TEST32_VEX( "c4e1491400 vunpcklpd xmm0,xmm6,oword ptr [eax]", 0xC4, 0xE1, 0x49, 0x14, 0x00 );
	_TEST32_VEX( "c4e14914c0 vunpcklpd xmm0,xmm6,xmm0", 0xC4, 0xE1, 0x49, 0x14, 0xC0 );
	_TEST64_VEX( "c4e1491400 vunpcklpd xmm0,xmm6,oword ptr [rax]", 0xC4, 0xE1, 0x49, 0x14, 0x00 );

	// UNPCKLPS
	// 0F 14 /r UNPCKLPS xmm1,xmm2/m128
	_TEST32( "0f1400 unpcklps xmm0,oword ptr [eax]", 0x0F, 0x14, 0x00 );
	_TEST32( "0f14c0 unpcklps xmm0,xmm0", 0x0F, 0x14, 0xC0 );
	_TEST64( "0f1400 unpcklps xmm0,oword ptr [rax]", 0x0F, 0x14, 0x00 );
	// VEX.NDS.128.0F.WIG 14 /r VUNPCKLPS xmm1,xmm2,xmm3/m128
	// VEX.NDS.256.0F.WIG 14 /r VUNPCKLPS ymm1,ymm2,ymm3/m256
	_TEST32_VEX( "c4e1481400 vunpcklps xmm0,xmm6,oword ptr [eax]", 0xC4, 0xE1, 0x48, 0x14, 0x00 );
	_TEST32_VEX( "c4e14814c0 vunpcklps xmm0,xmm6,xmm0", 0xC4, 0xE1, 0x48, 0x14, 0xC0 );
	_TEST64_VEX( "c4e1481400 vunpcklps xmm0,xmm6,oword ptr [rax]", 0xC4, 0xE1, 0x48, 0x14, 0x00 );

	// UD2
	// 0F 0B UD2 NP Valid Valid Raise invalid opcode exception.
	_TEST32( "0f0b ud2", 0x0F, 0x0B );
	_TEST64( "0f0b ud2", 0x0F, 0x0B );

	// UCOMISS
	// 0F 2E /r UCOMISS xmm1,xmm2/m32 RM V/V SSE Compare lower single-precision floating-point value in xmm1 register with lower singleprecision floating-point value in xmm2/mem and set the status flags accordingly.
	_TEST32( "0f2e1401 ucomiss xmm2,dword ptr [ecx+eax]", 0x0F, 0x2E, 0x14, 0x01 );
	_TEST64( "0f2e1401 ucomiss xmm2,dword ptr [rcx+rax]", 0x0F, 0x2E, 0x14, 0x01 );
	_TEST64( "0f2ec0 ucomiss xmm0,xmm0", 0x0F, 0x2E, 0xC0 );
	// VEX.LIG.0F.WIG 2E /r VUCOMISS xmm1,xmm2/m32 RM V/V AVX Compare low single precision floating-point values in xmm1 and xmm2/mem32 and set the EFLAGS flags accordingly.
	_TEST32_VEX( "c4e1782e00 vucomiss xmm0,dword ptr [eax]", 0xC4, 0xE1, 0x78, 0x2E, 0x00 );
	_TEST64_VEX( "c4e1782ec1 vucomiss xmm0,xmm1", 0xC4, 0xE1, 0x78, 0x2E, 0xC1 );

	// UCOMISD
	// 66 0F 2E /r UCOMISD xmm1,xmm2/m64 RM V/V SSE2 Compares (unordered) the low doubleprecision floating-point values in xmm1 and xmm2/m64 and set the EFLAGS accordingly.
	_TEST32( "660f2e1401 ucomisd xmm2,qword ptr [ecx+eax]", 0x66, 0x0F, 0x2E, 0x14, 0x01 );
	_TEST64( "660f2e1401 ucomisd xmm2,qword ptr [rcx+rax]", 0x66, 0x0F, 0x2E, 0x14, 0x01 );
	_TEST64( "660f2ec0 ucomisd xmm0,xmm0", 0x66, 0x0F, 0x2E, 0xC0 );
	// VEX.LIG.66.0F.WIG 2E /r VUCOMISD xmm1,xmm2/m64 RM V/V AVX Compare low double precision floating-point values in xmm1 and xmm2/mem64 and set the EFLAGS flags accordingly.
	_TEST32_VEX( "c4e1792e00 vucomisd xmm0,qword ptr [eax]", 0xC4, 0xE1, 0x79, 0x2E, 0x00 );
	_TEST64_VEX( "c4e1792ec1 vucomisd xmm0,xmm1", 0xC4, 0xE1, 0x79, 0x2E, 0xC1 );

	// TEST
	// A8 ib TEST AL, imm8 I Valid Valid AND imm8 with AL; set SF, ZF, PF according to result.
	_TEST32( "a820 test al,20h", 0xA8, 0x20 );
	_TEST64( "a820 test al,20h", 0xA8, 0x20 );
	// A9 iw TEST AX, imm16 I Valid Valid AND imm16 with AX; set SF, ZF, PF according to result.
	// A9 id TEST EAX, imm32 I Valid Valid AND imm32 with EAX; set SF, ZF, PF according to result.
	_TEST32( "a920401000 test eax,00104020h", 0xA9, 0x20, 0x40, 0x10, 0x00 );
	_TEST32( "66a92000 test ax,0020h", 0x66, 0xA9, 0x20, 0x00 );
	// REX.W + A9 id TEST RAX, imm32 I Valid N.E. AND imm32 sign-extended to 64-bits with RAX; set SF, ZF, PF according to result.
	_TEST64( "48a9204010ff test rax,0ffffffffff104020h", 0x48, 0xA9, 0x20, 0x40, 0x10, 0xFF );
	// F6 /0 ib TEST r/m8, imm8 MI Valid Valid AND imm8 with r/m8; set SF, ZF, PF according to result.
	// REX + F6 /0 ib TEST r/m8*, imm8 MI Valid N.E. AND imm8 with r/m8; set SF, ZF, PF according to result.
	_TEST32( "f600ff test byte ptr [eax],0ffh", 0xF6, 0x00, 0xFF );
	_TEST64( "48f600ff test byte ptr [rax],0ffh", 0x48, 0xF6, 0x00, 0xFF );
	// F7 /0 iw TEST r/m16, imm16 MI Valid Valid AND imm16 with r/m16; set SF, ZF, PF according to result.
	// F7 /0 id TEST r/m32, imm32 MI Valid Valid AND imm32 with r/m32; set SF, ZF, PF according to result.
	_TEST32( "f700401000ff test dword ptr [eax],0ff001040h", 0xF7, 0x00, 0x40, 0x10, 0x00, 0xFF );
	_TEST32( "66f70000ff test word ptr [eax],0ff00h", 0x66, 0xF7, 0x00, 0x00, 0xff );
	// REX.W + F7 /0 id TEST r/m64, imm32 MI Valid N.E. AND imm32 sign-extended to 64-bits with r/m64; set SF, ZF, PF according to result.
	_TEST64( "48f7004010ff11 test qword ptr [rax],0000000011ff1040h", 0x48, 0xF7, 0x00, 0x40, 0x10, 0xFF, 0x11 );
	// 84 /r TEST r/m8, r8 MR Valid Valid AND r8 with r/m8; set SF, ZF, PF according to result.
	// REX + 84 /r TEST r/m8*, r8* MR Valid N.E. AND r8 with r/m8; set SF, ZF, PF according to result.
	_TEST32( "8400 test byte ptr [eax],al", 0x84, 0x00 );
	_TEST64( "488400 test byte ptr [rax],al", 0x48, 0x84, 0x00 );
	// 85 /r TEST r/m16, r16 MR Valid Valid AND r16 with r/m16; set SF, ZF, PF according to result.
	// 85 /r TEST r/m32, r32 MR Valid Valid AND r32 with r/m32; set SF, ZF, PF according to result.
	// REX.W + 85 /r TEST r/m64, r64 MR Valid N.E. AND r64 with r/m64; set SF, ZF, PF according to result.
	_TEST32( "668500 test word ptr [eax],ax", 0x66, 0x85, 0x00 );
	_TEST64( "488500 test qword ptr [rax],rax", 0x48, 0x85, 0x00 );

	// SYSRET
	// 0F 07 SYSRET NP Valid Invalid Return to compatibility mode from fast system call
	// REX.W + 0F 07 SYSRET NP Valid Invalid Return to 64-bit mode from fast system call
	_TEST32( "FAIL", 0x0F, 0x07 );
	_TEST64( "0f07 sysret", 0x0F, 0x07 );
	_TEST64( "480f07 sysret", 0x48, 0x0F, 0x07 );

	// SYSEXIT
	// 0F 35 SYSEXIT NP Valid Valid Fast return to privilege level 3 user code.
	// REX.W + 0F 35 SYSEXIT NP Valid Valid Fast return to 64-bit mode privilege level 3 user code.
	_TEST32( "0f35 sysexit", 0x0F, 0x35 );
	_TEST64( "0f35 sysexit", 0x0F, 0x35 );
	_TEST64( "480f35 sysexit", 0x48, 0x0F, 0x35 );

	// SYSENTER
	// 0F 34 SYSENTER NP Valid Valid Fast call to privilege level 0 system procedures.
	_TEST64( "0f34 sysenter", 0x0F, 0x34 );
	_TEST32( "0f34 sysenter", 0x0F, 0x34 );

	// SYSCALL
	// 0F 05 SYSCALL NP Valid Invalid Fast call to privilege level 0 system procedures.
	_TEST64( "0f05 syscall", 0x0F, 0x05 );
	_TEST32( "FAIL", 0x0F, 0x05 );

	// SWAPGS
	// 0F 01 F8 SWAPGS NP Valid Invalid Exchanges the current GS base register value with the value contained in MSR address C0000102H.
	_TEST64( "0f01f8 swapgs", 0x0F, 0x01, 0xF8 );
	_TEST32( "FAIL", 0x0F, 0x01, 0xF8 );

	// SUBSS
	// F3 0F 5C /r SUBSS xmm1,xmm2/m32
	_TEST32( "f30f5c1401 subss xmm2,dword ptr [ecx+eax]", 0xF3, 0x0F, 0x5C, 0x14, 0x01 );
	_TEST64( "f30f5c1401 subss xmm2,dword ptr [rcx+rax]", 0xF3, 0x0F, 0x5C, 0x14, 0x01 );
	// VEX.NDS.LIG.F3.0F.WIG 5C /r VSUBSS xmm1,xmm2,xmm3/m32
	_TEST32_VEX( "c4e1525c1401 vsubss xmm2,xmm5,dword ptr [ecx+eax]", 0xC4, 0xE1, 0x52, 0x5C, 0x14, 0x01 );
	_TEST32_VEX( "c5da5c1401 vsubss xmm2,xmm4,dword ptr [ecx+eax]", 0xC5, 0xDA, 0x5C, 0x14, 0x01 );

	// SUBSD
	// F2 0F 5C /r SUBSD xmm1,xmm2/m64 RM V/V SSE2 Subtracts the low double-precision floatingpoint values in xmm2/mem64 from xmm1.
	_TEST32( "f20f5c1401 subsd xmm2,qword ptr [ecx+eax]", 0xF2, 0x0F, 0x5C, 0x14, 0x01 );
	_TEST64( "f20f5c1401 subsd xmm2,qword ptr [rcx+rax]", 0xF2, 0x0F, 0x5C, 0x14, 0x01 );
	// VEX.NDS.LIG.F2.0F.WIG 5C /r VSUBSD xmm1,xmm2,xmm3/m64 RVM V/V AVX Subtract the low double-precision floatingpoint value in xmm3/mem from xmm2 and store the result in xmm1.
	_TEST32_VEX( "c4e1535c1401 vsubsd xmm2,xmm5,qword ptr [ecx+eax]", 0xC4, 0xE1, 0x53, 0x5C, 0x14, 0x01 );
	_TEST32_VEX( "c5db5c1401 vsubsd xmm2,xmm4,qword ptr [ecx+eax]", 0xC5, 0xDB, 0x5C, 0x14, 0x01 );

	// SUBPS
	// 0F 5C /r SUBPS xmm1 xmm2/m128
	_TEST32( "0f5c00 subps xmm0,oword ptr [eax]", 0x0F, 0x5C, 0x00 );
	_TEST32( "0f5cc0 subps xmm0,xmm0", 0x0F, 0x5C, 0xC0 );
	_TEST64( "0f5c00 subps xmm0,oword ptr [rax]", 0x0F, 0x5C, 0x00 );
	// VEX.NDS.128.0F.WIG 5C /r VSUBPS xmm1,xmm2,xmm3/m128
	// VEX.NDS.256.0F.WIG 5C /r VSUBPS ymm1,ymm2,ymm3/m256
	_TEST32_VEX( "c4e1485c00 vsubps xmm0,xmm6,oword ptr [eax]", 0xC4, 0xE1, 0x48, 0x5C, 0x00 );
	_TEST32_VEX( "c4e1485cc0 vsubps xmm0,xmm6,xmm0", 0xC4, 0xE1, 0x48, 0x5C, 0xC0 );
	_TEST64_VEX( "c4e1485c00 vsubps xmm0,xmm6,oword ptr [rax]", 0xC4, 0xE1, 0x48, 0x5C, 0x00 );

	// SUBPD
	// 66 0F 5C /r SUBPD xmm1,xmm2/m128
	_TEST32( "660f5c00 subpd xmm0,oword ptr [eax]", 0x66, 0x0F, 0x5C, 0x00 );
	_TEST32( "660f5cc0 subpd xmm0,xmm0", 0x66, 0x0F, 0x5C, 0xC0 );
	_TEST64( "660f5c00 subpd xmm0,oword ptr [rax]", 0x66, 0x0F, 0x5C, 0x00 );
	// VEX.NDS.128.66.0F.WIG 5C /r VSUBPD xmm1,xmm2,xmm3/m128
	// VEX.NDS.256.66.0F.WIG 5C /r VSUBPD ymm1,ymm2,ymm3/m256
	_TEST32_VEX( "c4e1495c00 vsubpd xmm0,xmm6,oword ptr [eax]", 0xC4, 0xE1, 0x49, 0x5C, 0x00 );
	_TEST32_VEX( "c4e1495cc0 vsubpd xmm0,xmm6,xmm0", 0xC4, 0xE1, 0x49, 0x5C, 0xC0 );
	_TEST64_VEX( "c4e1495c00 vsubpd xmm0,xmm6,oword ptr [rax]", 0xC4, 0xE1, 0x49, 0x5C, 0x00 );

	// SUB
	// 2C ib SUB AL, imm8 I Valid Valid Subtract imm8 from AL.
	_TEST32( "2c42 sub al,42h", 0x2C, 0x42 );
	_TEST32( "2cff sub al,0ffh", 0x2C, 0xff );
	_TEST64( "2c42 sub al,42h", 0x2C, 0x42 );
	_TEST64( "2c00 sub al,00h", 0x2C, 0x00 );
	_TEST64( "2cff sub al,0ffh", 0x2C, 0xff );
	// 2D iw SUB AX, imm16 I Valid Valid Subtract imm16 from AX.
	// 2D id SUB EAX, imm32 I Valid Valid Subtract imm32 from EAX.
	_TEST32( "662d4280 sub ax,8042h", 0x66, 0x2D, 0x42, 0x80 );
	_TEST32( "2d21658042 sub eax,42806521h", 0x2D, 0x21, 0x65, 0x80, 0x42 );
	_TEST64( "402d21658042 sub eax,42806521h", 0x40, 0x2D, 0x21, 0x65, 0x80, 0x42 );
	_TEST64( "66402d2165 sub ax,6521h", 0x66, 0x40, 0x2D, 0x21, 0x65, 0x80, 0x42 );
	// REX.W + 2D id SUB RAX, imm32 I Valid N.E. Subtract imm32 sign-extended to 64-bits from RAX.
	_TEST64( "482d21658042 sub rax,0000000042806521h", 0x48, 0x2D, 0x21, 0x65, 0x80, 0x42 );
	_TEST64( "66482d21658042 sub rax,0000000042806521h", 0x66, 0x48, 0x2D, 0x21, 0x65, 0x80, 0x42 );
	_TEST64( "6766482d21658042 sub rax,0000000042806521h", 0x67, 0x66, 0x48, 0x2D, 0x21, 0x65, 0x80, 0x42 );
	_TEST64( "6766482dffffffff sub rax,0ffffffffffffffffh", 0x67, 0x66, 0x48, 0x2D, 0xff, 0xff, 0xff, 0xff );
	// 80 /5 ib SUB r/m8, imm8 MI Valid Valid Subtract imm8 from r/m8.
	// REX + 80 /5 ib SUB r/m8*, imm8 MI Valid N.E. Subtract imm8 from r/m8.
	_TEST32( "802d01020304ff sub byte ptr [04030201h],0ffh", 0x80, 0x2D, 0x01, 0x02, 0x03, 0x04, 0xff );
	_TEST32( "80ae01020304ff sub byte ptr [esi+04030201h],0ffh", 0x80, 0xAE, 0x01, 0x02, 0x03, 0x04, 0xff, 0x00, 0x00 );
	_TEST32( "806c010203 sub byte ptr [ecx+eax+00000002h],03h", 0x80, 0x6C, 0x01, 0x02, 0x03 );
	// 81 /5 iw SUB r/m16, imm16 MI Valid Valid Subtract imm16 from r/m16.
	// 81 /5 id SUB r/m32, imm32 MI Valid Valid Subtract imm32 from r/m32.
	_TEST32( "81ed01020304 sub ebp,04030201h", 0x81, 0xED, 0x01, 0x02, 0x03, 0x04 );
	_TEST32( "6681ed0102 sub bp,0201h", 0x66, 0x81, 0xED, 0x01, 0x02 );
	_TEST64( "67664081ed0102 sub bp,0201h", 0x67, 0x66, 0x40, 0x81, 0xED, 0x01, 0x02 ); // 32 bit mode doesn't not allow REX.
	// REX.W + 81 /5 id SUB r/m64, imm32 MI Valid N.E. Subtract imm32 sign-extended to 64-bits from r/m64.
	_TEST64( "4881ed01020304 sub rbp,0000000004030201h", 0x48, 0x81, 0xed, 0x01, 0x02, 0x03, 0x04 );
	_TEST64( "4881edffffffff sub rbp,0ffffffffffffffffh", 0x48, 0x81, 0xed, 0xff, 0xff, 0xff, 0xff );
	_TEST64( "674881edffffffff sub rbp,0ffffffffffffffffh", 0x67, 0x48, 0x81, 0xed, 0xff, 0xff, 0xff, 0xff );
	_TEST64( "664881edffffffff sub rbp,0ffffffffffffffffh", 0x66, 0x48, 0x81, 0xed, 0xff, 0xff, 0xff, 0xff );
	// 83 /5 ib SUB r/m16, imm8 MI Valid Valid Subtract sign-extended imm8 from r/m16.
	// 83 /5 ib SUB r/m32, imm8 MI Valid Valid Subtract sign-extended imm8 from r/m32.
	_TEST32( "832e01 sub dword ptr [esi],00000001h", 0x83, 0x2E, 0x01, 0x02, 0x03, 0x04 );
	_TEST32( "66832e01 sub word ptr [esi],0001h", 0x66, 0x83, 0x2E, 0x01, 0x02, 0x03, 0x04 );
	_TEST32( "67832e010203 sub dword ptr [0201h],00000003h", 0x67, 0x83, 0x2E, 0x01, 0x02, 0x03 );
	// REX.W + 83 /5 ib SUB r/m64, imm8 MI Valid N.E. Subtract sign-extended imm8 from r/m64.
	_TEST64( "4883af0102030405 sub qword ptr [rdi+0000000004030201h],0000000000000005h", 0x48, 0x83, 0xAF, 0x01, 0x02, 0x03, 0x4, 0x05 );
	_TEST64( "4883af01020304ff sub qword ptr [rdi+0000000004030201h],0ffffffffffffffffh", 0x48, 0x83, 0xAF, 0x01, 0x02, 0x03, 0x4, 0xff );
	// 28 /r SUB r/m8, r8 MR Valid Valid Subtract r8 from r/m8.
	// REX + 28 /r SUB r/m8*, r8* MR Valid N.E. Subtract r8 from r/m8.
	_TEST32( "28a501020304 sub byte ptr [ebp+04030201h],ah", 0x28, 0xa5, 0x01, 0x02, 0x03, 04 );
	_TEST64( "4828a501020304 sub byte ptr [rbp+0000000004030201h],spl", 0x48, 0x28, 0xa5, 0x01, 0x02, 0x03, 04 );
	_TEST64( "482864a501 sub byte ptr [rbp+0000000000000001h],spl", 0x48, 0x28, 0x64, 0xa5, 0x01, 0x02, 0x03, 04 );
	// 29 /r SUB r/m16, r16 MR Valid Valid Subtract r16 from r/m16.
	// 29 /r SUB r/m32, r32 MR Valid Valid Subtract r32 from r/m32.
	// REX.W + 29 /r SUB r/m64, r32 MR Valid N.E. Subtract r64 from r/m64.
	_TEST32( "29a501020304 sub dword ptr [ebp+04030201h],esp", 0x29, 0xa5, 0x01, 0x02, 0x03, 04 );
	_TEST32( "676629a50102 sub word ptr [di+0201h],sp", 0x67, 0x66, 0x29, 0xa5, 0x01, 0x02 );
	_TEST32( "6729a50102 sub dword ptr [di+0201h],esp", 0x67, 0x29, 0xa5, 0x01, 0x02 );
	_TEST64( "4d29648901 sub qword ptr [r9+rcx*4+0000000000000001h],r12", 0x4D, 0x29, 0x64, 0x89, 0x01 );
	_TEST64( "29648101 sub dword ptr [rcx+rax*4+0000000000000001h],esp", 0x29, 0x64, 0x81, 0x01 );
	// 2A /r SUB r8, r/m8 RM Valid Valid Subtract r/m8 from r8.
	// REX + 2A /r SUB r8*, r/m8* RM Valid N.E. Subtract r/m8 from r8.
	_TEST32( "2aa501020304 sub ah,byte ptr [ebp+04030201h]", 0x2A, 0xa5, 0x01, 0x02, 0x03, 04 );
	_TEST64( "482aa501020304 sub spl,byte ptr [rbp+0000000004030201h]", 0x48, 0x2A, 0xa5, 0x01, 0x02, 0x03, 04 );
	_TEST64( "482a64a501 sub spl,byte ptr [rbp+0000000000000001h]", 0x48, 0x2A, 0x64, 0xa5, 0x01, 0x02, 0x03, 04 );
	// 2B /r SUB r16, r/m16 RM Valid Valid Subtract r/m16 from r16.
	// 2B /r SUB r32, r/m32 RM Valid Valid Subtract r/m32 from r32.
	// REX.W + 2B /r SUB r64, r/m64 RM Valid N.E. Subtract r/m64 from r64.
	_TEST32( "2ba501020304 sub esp,dword ptr [ebp+04030201h]", 0x2b, 0xa5, 0x01, 0x02, 0x03, 04 );
	_TEST32( "67662ba50102 sub sp,word ptr [di+0201h]", 0x67, 0x66, 0x2b, 0xa5, 0x01, 0x02 );
	_TEST32( "672ba50102 sub esp,dword ptr [di+0201h]", 0x67, 0x2b, 0xa5, 0x01, 0x02 );
	_TEST64( "4d2b648901 sub r12,qword ptr [r9+rcx*4+0000000000000001h]", 0x4D, 0x2b, 0x64, 0x89, 0x01 );

	// STR
	// 0F 00 /1 STR r/m16 M Valid Valid Stores segment selector from TR in r/m16.
	_TEST32( "0f0008 str word ptr [eax]",  0x0F, 0x00, 0x08 );
	_TEST64( "0f0008 str word ptr [rax]", 0x0F, 0x00, 0x08 );

	// STOS
	// AA STOS m8 NA Valid Valid For legacy mode, store AL at address ES:(E)DI; For 64-bit mode store AL at address RDI or EDI.
	_TEST32( "67aa stos byte ptr [si],byte ptr [di]", 0x67, 0xAA );
	_TEST32( "6667aa stos byte ptr [si],byte ptr [di]", 0x66, 0x67, 0xAA );
	_TEST32( "aa stos byte ptr [esi],byte ptr [edi]", 0xAA );
	_TEST64( "48aa stos byte ptr [rsi],byte ptr [rdi]", 0x48, 0xAA );
	_TEST64( "40aa stos byte ptr [rsi],byte ptr [rdi]", 0x40, 0xAA );
	_TEST64( "6740aa stos byte ptr [esi],byte ptr [edi]", 0x67, 0x40, 0xAA );
	_TEST64( "666740aa stos byte ptr [esi],byte ptr [edi]", 0x66, 0x67, 0x40, 0xAA );
	// AB STOS m16 NA Valid Valid For legacy mode, store AX at address ES:(E)DI; For 64-bit mode store AX at address RDI or EDI.
	// AB STOS m32 NA Valid Valid For legacy mode, store EAX at address ES:(E)DI; For 64-bit mode store EAX at address RDI or EDI.
	// REX.W + AB STOS m64 NA Valid N.E. Store RAX at address RDI or EDI.
	_TEST32( "67ab stos dword ptr [si],dword ptr [di]", 0x67, 0xAB );
	_TEST32( "6667ab stos word ptr [si],word ptr [di]", 0x66, 0x67, 0xAB );
	_TEST32( "ab stos dword ptr [esi],dword ptr [edi]", 0xAB );
	_TEST64( "48ab stos qword ptr [rsi],qword ptr [rdi]", 0x48, 0xAB );
	_TEST64( "40ab stos dword ptr [rsi],dword ptr [rdi]", 0x40, 0xAB );
	_TEST64( "6740ab stos dword ptr [esi],dword ptr [edi]", 0x67, 0x40, 0xAB );
	_TEST64( "666740ab stos word ptr [esi],word ptr [edi]", 0x66, 0x67, 0x40, 0xAB );
	// AA STOSB NA Valid Valid For legacy mode, store AL at address ES:(E)DI; For 64-bit mode store AL at address RDI or EDI.
	// AB STOSW NA Valid Valid For legacy mode, store AX at address ES:(E)DI; For 64-bit mode store AX at address RDI or EDI.
	// AB STOSD NA Valid Valid For legacy mode, store EAX at address ES:(E)DI; For 64-bit mode store EAX at address RDI or EDI.
	// REX.W + AB STOSQ NA Valid N.E. Store RAX at address RDI or EDI.

	// STMXCSR
	// 0F AE /3 STMXCSR m32 M V/V SSE Store contents of MXCSR register to m32.
	_TEST32( "0fae5820 stmxcsr dword ptr [eax+00000020h]", 0x0F, 0xAE, 0x58, 0x20 );
	_TEST64( "0fae5820 stmxcsr dword ptr [rax+0000000000000020h]", 0x0F, 0xAE, 0x58, 0x20 );
	// VEX.LZ.0F.WIG AE /3 VSTMXCSR m32 M V/V AVX Store contents of MXCSR register to m32.
	_TEST64_VEX( "c4c178ae18 vstmxcsr dword ptr [r8]", 0xC4, 0xC1, 0x78, 0xAE, 0x18 );
	_TEST32_VEX( "c4e178ae18 vstmxcsr dword ptr [eax]", 0xC4, 0xE1, 0x78, 0xAE, 0x18 );
	_TEST32_VEX( "c5f8ae18 vstmxcsr dword ptr [eax]", 0xC5, 0xF8, 0xAE, 0x18 );

	// STI
	// FB STI NP Valid Valid Set interrupt flag; external, maskable interrupts enabled at the end of the next instruction.
	_TEST32( "fb sti", 0xFB );
	_TEST64( "fb sti", 0xFB );

	// STD
	// FD STD NP Valid Valid Set DF flag.
	_TEST32( "fd std", 0xFD );
	_TEST64( "fd std", 0xFD );

	// STC
	// F9 STC NP Valid Valid Set CF flag.
	_TEST32( "f9 stc", 0xF9 );
	_TEST64( "f9 stc", 0xF9 );

	// SQRTSS
	// F3 0F 51 /r SQRTSS xmm1,xmm2/m32
	_TEST32( "f30f511401 sqrtss xmm2,dword ptr [ecx+eax]", 0xF3, 0x0F, 0x51, 0x14, 0x01 );
	_TEST64( "f30f511401 sqrtss xmm2,dword ptr [rcx+rax]", 0xF3, 0x0F, 0x51, 0x14, 0x01 );
	_TEST64( "f30f51c0 sqrtss xmm0,xmm0", 0xF3, 0x0F, 0x51, 0xC0 );
	// VEX.NDS.LIG.F3.0F.WIG 51 VSQRTSS xmm1, xmm2, xmm3/m32
	_TEST32_VEX( "c4e152511401 vsqrtss xmm2,xmm5,dword ptr [ecx+eax]", 0xC4, 0xE1, 0x52, 0x51, 0x14, 0x01 );
	_TEST32_VEX( "c5da511401 vsqrtss xmm2,xmm4,dword ptr [ecx+eax]", 0xC5, 0xDA, 0x51, 0x14, 0x01 );

	// SQRTSD
	// F2 0F 51 /r SQRTSD xmm1,xmm2/m64
	_TEST32( "f20f511401 sqrtsd xmm2,qword ptr [ecx+eax]", 0xF2, 0x0F, 0x51, 0x14, 0x01 );
	_TEST64( "f20f511401 sqrtsd xmm2,qword ptr [rcx+rax]", 0xF2, 0x0F, 0x51, 0x14, 0x01 );
	// VEX.NDS.LIG.F2.0F.WIG 51 /r VSQRTSD xmm1,xmm2,xmm3/m64
	_TEST32_VEX( "c4e153511401 vsqrtsd xmm2,xmm5,qword ptr [ecx+eax]", 0xC4, 0xE1, 0x53, 0x51, 0x14, 0x01 );
	_TEST32_VEX( "c5db511401 vsqrtsd xmm2,xmm4,qword ptr [ecx+eax]", 0xC5, 0xDB, 0x51, 0x14, 0x01 );

	// SQRTPS
	// 0F 51 /r SQRTPS xmm1,xmm2/m128
	_TEST64_VEX( "0f5100 sqrtps xmm0,oword ptr [rax]", 0x0F, 0x51, 0x00 );
	_TEST32_VEX( "0f51c1 sqrtps xmm0,xmm1", 0x0F, 0x51, 0xC1 );
	// VEX.128.0F.WIG 51 /r VSQRTPS xmm1,xmm2/m128
	// VEX.256.0F.WIG 51 /r VSQRTPS ymm1,ymm2/m256
	_TEST64_VEX( "c4e17851d8 vsqrtps xmm3,xmm0", 0xC4, 0xE1, 0x78, 0x51, 0xD8 );
	_TEST32_VEX( "c4e17851d8 vsqrtps xmm3,xmm0", 0xC4, 0xE1, 0x78, 0x51, 0xD8 );
	_TEST32_VEX( "c4e17c5100 vsqrtps ymm0,ymmword ptr [eax]", 0xC4, 0xE1, 0x7C, 0x51, 0x00 );

	// SQRTPD
	// 66 0F 51 /r SQRTPD xmm1,xmm2/m128 RM V/V SSE2 Computes square roots of the packed doubleprecision floating-point values in xmm2/m128 and stores the results in xmm1.
	_TEST64_VEX( "660f5100 sqrtpd xmm0,oword ptr [rax]", 0x66, 0x0F, 0x51, 0x00 );
	_TEST32_VEX( "660f51c1 sqrtpd xmm0,xmm1", 0x66, 0x0F, 0x51, 0xC1 );
	// VEX.128.66.0F.WIG 51 /r VSQRTPD xmm1,xmm2/m128 RM V/V AVX Computes Square Roots of the packed doubleprecision floating-point values in xmm2/m128 and stores the result in xmm1.
	// VEX.256.66.0F.WIG 51 /r VSQRTPD ymm1,ymm2/m256 RM V/V AVX Computes Square Roots of the packed doubleprecision floating-point values in ymm2/m256 and stores the result in ymm1.
	_TEST64_VEX( "c4e17951d8 vsqrtpd xmm3,xmm0", 0xC4, 0xE1, 0x79, 0x51, 0xD8 );
	_TEST32_VEX( "c4e17951d8 vsqrtpd xmm3,xmm0", 0xC4, 0xE1, 0x79, 0x51, 0xD8 );
	_TEST32_VEX( "c4e17d5100 vsqrtpd ymm0,ymmword ptr [eax]", 0xC4, 0xE1, 0x7D, 0x51, 0x00 );

	// 0F 01 /4 SMSW r/m16 M Valid Valid Store machine status word to r/m16.
	// 0F 01 /4 SMSW r32/m16 M Valid Valid Store machine status word in low-order 16 bits of r32/m16; high-order 16 bits of r32 are undefined.
	// REX.W + 0F 01 /4 SMSW r64/m16 M Valid Valid Store machine status word in low-order 16 bits of r64/m16; high-order 16 bits of r32 are undefined.
	_TEST32( "0f0120 smsw word ptr [eax]", 0x0f, 0x01, 0x20 );
	_TEST32( "0f01e0 smsw eax", 0x0f, 0x01, 0xE0 );
	_TEST32( "660f0120 smsw word ptr [eax]", 0x66, 0x0f, 0x01, 0x20 );
	_TEST32( "660f01e0 smsw ax", 0x66, 0x0f, 0x01, 0xE0 );
	_TEST64( "480f0120 smsw word ptr [rax]", 0x48, 0x0f, 0x01, 0x20 );
	_TEST64( "480f01e0 smsw rax", 0x48, 0x0f, 0x01, 0xE0 );

	// SLDT
	// 0F 00 /0 SLDT r/m16 M Valid Valid Stores segment selector from LDTR in r/m16.
	_TEST32( "0f0000 sldt word ptr [eax]", 0x0f, 0x00, 0x00 );
	_TEST64( "0f00c0 sldt ax", 0x0f, 0x00, 0xC0 );
	// REX.W + 0F 00 /0 SLDT r64/m16 M Valid Valid Stores segment selector from LDTR in r64/m16.
	_TEST64( "480f00c0 sldt rax", 0x48, 0x0f, 0x00, 0xC0 );
	_TEST64( "480f0000 sldt word ptr [rax]", 0x48, 0x0f, 0x00, 0x00 );

	// SIDT
	// 0F 01 /1 SIDT m M Valid Valid Store IDTR to m.
	_TEST32( "0f0108 sidt [eax]", 0x0f, 0x01, 0x08 );
	_TEST64( "0f0108 sidt [rax]", 0x0f, 0x01, 0x08 );

	// SHUFPS
	// 0F C6 /r ib SHUFPS xmm1, xmm2/m128, imm8 RMI V/V SSE Shuffle packed single-precision floating-point values selected by imm8 from xmm1 and xmm1/m128 to xmm1.
	_TEST32( "0fc61401ff shufps xmm2,oword ptr [ecx+eax],0ffh", 0x0F, 0xC6, 0x14, 0x01, 0xFF );
	_TEST64( "0fc61401ff shufps xmm2,oword ptr [rcx+rax],0ffh", 0x0F, 0xC6, 0x14, 0x01, 0xFF );
	// VEX.NDS.128.0F.WIG C6 /r ib VSHUFPS xmm1, xmm2, xmm3/m128, imm8 RVMI V/V AVX Shuffle Packed single-precision floating-point values selected by imm8 from xmm2 and xmm3/mem.
	// VEX.NDS.256.0F.WIG C6 /r ib VSHUFPS ymm1, ymm2, ymm3/m256, imm8 RVMI V/V AVX Shuffle Packed single-precision floating-point values selected by imm8 from ymm2 and ymm3/mem.
	_TEST32_VEX( "c4e148c6140120 vshufps xmm2,xmm6,oword ptr [ecx+eax],20h", 0xC4, 0xE1, 0x48, 0xC6, 0x14, 0x01, 0x20 );
	_TEST64_VEX( "c4e148c6140120 vshufps xmm2,xmm6,oword ptr [rcx+rax],20h", 0xC4, 0xE1, 0x48, 0xC6, 0x14, 0x01, 0x20 );

	// SHUFPD
	// 66 0F C6 /r ib SHUFPD xmm1,xmm2/m128,imm8
	_TEST32( "660fc61401ff shufpd xmm2,oword ptr [ecx+eax],0ffh", 0x66, 0x0F, 0xC6, 0x14, 0x01, 0xFF );
	_TEST64( "660fc61401ff shufpd xmm2,oword ptr [rcx+rax],0ffh", 0x66, 0x0F, 0xC6, 0x14, 0x01, 0xFF );
	// VEX.NDS.128.66.0F.WIG C6 /r ib VSHUFPD xmm1,xmm2,xmm3/m128,imm8
	// VEX.NDS.256.66.0F.WIG C6 /r ib VSHUFPD ymm1,ymm2,ymm3/m256,imm8
	_TEST32_VEX( "c4e149c6140120 vshufpd xmm2,xmm6,oword ptr [ecx+eax],20h", 0xC4, 0xE1, 0x49, 0xC6, 0x14, 0x01, 0x20 );
	_TEST64_VEX( "c4e149c6140120 vshufpd xmm2,xmm6,oword ptr [rcx+rax],20h", 0xC4, 0xE1, 0x49, 0xC6, 0x14, 0x01, 0x20 );

	// 0F AC SHRD r/m16, r16, imm8 MRI Valid Valid Shift r/m16 to right imm8 places while shifting bits from r16 in from the left.
	// 0F AC SHRD r/m32, r32, imm8 MRI Valid Valid Shift r/m32 to right imm8 places while shifting bits from r32 in from the left.
	// REX.W + 0F AC SHRD r/m64, r64, imm8 MRI Valid N.E. Shift r/m64 to right imm8 places while shifting bits from r64 in from the left.
	_TEST32( "0fac00ff shrd dword ptr [eax],eax,0ffh", 0x0f, 0xAC, 0x00, 0xFF );
	_TEST32( "660fac00ff shrd word ptr [eax],ax,0ffh", 0x66, 0x0f, 0xAC, 0x00, 0xFF );
	_TEST64( "480fac00ff shrd qword ptr [rax],rax,0ffh", 0x48, 0x0f, 0xAC, 0x00, 0xFF );
	// 0F AD SHRD r/m16, r16, CL MRC Valid Valid Shift r/m16 to right CL places while shifting bits from r16 in from the left.
	// 0F AD SHRD r/m32, r32, CL MRC Valid Valid Shift r/m32 to right CL places while shifting bits from r32 in from the left.
	// REX.W + 0F AD SHRD r/m64, r64, CL MRC Valid N.E. Shift r/m64 to right CL places while shifting bits from r64 in from the left.
	_TEST32( "0fad00 shrd dword ptr [eax],eax,cl", 0x0f, 0xAD, 0x00 );
	_TEST32( "660fad00 shrd word ptr [eax],ax,cl", 0x66, 0x0f, 0xAD, 0x00 );
	_TEST64( "480fad00 shrd qword ptr [rax],rax,cl", 0x48, 0x0f, 0xAD, 0x00 );

	// SHLD
	// 0F A4 SHLD r/m16,r16,imm8
	// 0F A4 SHLD r/m32,r32,imm8
	// REX.W + 0F A4 SHLD r/m64,r64,imm8
	_TEST32( "0fa400ff shld dword ptr [eax],eax,0ffh", 0x0f, 0xA4, 0x00, 0xFF );
	_TEST32( "660fa400ff shld word ptr [eax],ax,0ffh", 0x66, 0x0f, 0xA4, 0x00, 0xFF );
	_TEST64( "480fa400ff shld qword ptr [rax],rax,0ffh", 0x48, 0x0f, 0xA4, 0x00, 0xFF );
	// 0F A5 SHLD r/m16,r16,CL
	// 0F A5 SHLD r/m32,r32,CL
	// REX.W + 0F A5 SHLD r/m64,r64,CL
	_TEST32( "0fa500 shld dword ptr [eax],eax,cl", 0x0f, 0xA5, 0x00 );
	_TEST32( "660fa500 shld word ptr [eax],ax,cl", 0x66, 0x0f, 0xA5, 0x00 );
	_TEST64( "480fa500 shld qword ptr [rax],rax,cl", 0x48, 0x0f, 0xA5, 0x00 );

	// SGDT
	// 0F 01 /0 SGDT m
	_TEST32( "0f0100 sgdt [eax]", 0x0f, 0x01, 0x00 );
	_TEST64( "0f0100 sgdt [rax]", 0x0f, 0x01, 0x00 );

	// SFENCE
	// 0F AE /7 SFENCE
	_TEST32( "0faef8 sfence", 0x0f, 0xae, 0xf8 );

	// 0F 97 SETA r/m8 M Valid Valid Set byte if above (CF=0 and ZF=0).
	// REX + 0F 97 SETA r/m8*
	_TEST32( "0f9700 setnbe byte ptr [eax]", 0x0F, 0x97, 0x00 );
	_TEST32( "0f97c0 setnbe al", 0x0F, 0x97, 0xC0 );
	_TEST64( "400f97c0 setnbe al", 0x40, 0x0F, 0x97, 0xC0 );

	// AE SCAS m8 NP Valid Valid Compare AL with byte at ES:(E)DI or RDI, then set status flags.
	_TEST32( "ae scas byte ptr [edi]", 0xAE );
	// AF SCAS m16 NP Valid Valid Compare AX with word at ES:(E)DI or RDI, then set status flags.
	// AF SCAS m32 NP Valid Valid Compare EAX with doubleword at ES(E)DI or RDI then set status flags.
	// REX.W + AF SCAS m64 NP Valid N.E. Compare RAX with quadword at RDI or EDI then set status flags.
	_TEST32( "af scas dword ptr [edi]", 0xAF );
	_TEST32( "66af scas word ptr [edi]", 0x66, 0xAF );
	_TEST64( "48af scas qword ptr [rdi]", 0x48, 0xAF );
	// AE SCASB NP Valid Valid Compare AL with byte at ES:(E)DI or RDI then set status flags.
	// AF SCASW NP Valid Valid Compare AX with word at ES:(E)DI or RDI then set status flags.
	// AF SCASD NP Valid Valid Compare EAX with doubleword at ES:(E)DI or RDI then set status flags.
	// REX.W + AF SCASQ NP Valid N.E. Compare RAX with quadword at RDI or EDI then set status flags.

	// SBB
	_TEST32( "801501020304ff adc byte ptr [04030201h],0ffh", 0x80, 0x15, 0x01, 0x02, 0x03, 0x04, 0xff );
	// 1C ib SBB AL,imm8
	_TEST32( "1c42 sbb al,42h", 0x1C, 0x42 );
	// 1D iw SBB AX,imm16
	// 1D id SBB EAX,imm32
	_TEST32( "661d4280 sbb ax,8042h", 0x66, 0x1D, 0x42, 0x80 );
	_TEST32( "1d21658042 sbb eax,42806521h", 0x1D, 0x21, 0x65, 0x80, 0x42 );
	_TEST64( "66401d2165 sbb ax,6521h", 0x66, 0x40, 0x1D, 0x21, 0x65, 0x80, 0x42 );
	// REX.W + 1D id SBB RAX,imm32X.
	_TEST64( "481d21658042 sbb rax,0000000042806521h", 0x48, 0x1D, 0x21, 0x65, 0x80, 0x42 );
	// 80 /3 ib SBB r/m8,imm8
	// REX + 80 /3 ib SBB r/m8,imm8
	_TEST32( "8018ff sbb byte ptr [eax],0ffh", 0x80, 0x18, 0xff );
	_TEST32( "80d8ff sbb al,0ffh", 0x80, 0xD8, 0xff );
	_TEST64( "488018ff sbb byte ptr [rax],0ffh", 0x48, 0x80, 0x18, 0xff );
	// 81 /3 iw SBB r/m16,imm16
	// 81 /3 id SBB r/m32,imm32
	_TEST32( "81dd01020304 sbb ebp,04030201h", 0x81, 0xDD, 0x01, 0x02, 0x03, 0x04 );
	_TEST32( "6681dd0102 sbb bp,0201h", 0x66, 0x81, 0xDD, 0x01, 0x02 );
	_TEST64( "67664081dd0102 sbb bp,0201h", 0x67, 0x66, 0x40, 0x81, 0xDD, 0x01, 0x02 ); // 32 bit mode doesn't not allow REX.
	// REX.W + 81 /3 id SBB r/m64,imm32
	_TEST64( "4881dd01020304 sbb rbp,0000000004030201h", 0x48, 0x81, 0xDD, 0x01, 0x02, 0x03, 0x04 );
	// 83 /3 ib SBB r/m16,imm8
	// 83 /3 ib SBB r/m32,imm8
	_TEST32( "8318ff sbb dword ptr [eax],0ffffffffh", 0x83, 0x18, 0xFF );
	_TEST32( "668318ff sbb word ptr [eax],0ffffh", 0x66, 0x83, 0x18, 0xFF );
	_TEST32( "83d8ff sbb eax,0ffffffffh", 0x83, 0xD8, 0xFF );
	// REX.W + 83 /3 ib SBB r/m64,imm8
	_TEST64( "48839f0102030405 sbb qword ptr [rdi+0000000004030201h],0000000000000005h", 0x48, 0x83, 0x9F, 0x01, 0x02, 0x03, 0x4, 0x05 );
	_TEST64( "48839f01020304ff sbb qword ptr [rdi+0000000004030201h],0ffffffffffffffffh", 0x48, 0x83, 0x9F, 0x01, 0x02, 0x03, 0x4, 0xff );
	// 18 /r SBB r/m8,r8
	// REX + 18 /r SBB r/m8,r8
	_TEST32( "18a501020304 sbb byte ptr [ebp+04030201h],ah", 0x18, 0xa5, 0x01, 0x02, 0x03, 04 );
	_TEST64( "4818a501020304 sbb byte ptr [rbp+0000000004030201h],spl", 0x48, 0x18, 0xa5, 0x01, 0x02, 0x03, 04 );
	_TEST64( "481864a501 sbb byte ptr [rbp+0000000000000001h],spl", 0x48, 0x18, 0x64, 0xa5, 0x01, 0x02, 0x03, 04 );
	// 19 /r SBB r/m16,r16
	// 19 /r SBB r/m32,r32
	// REX.W + 19 /r SBB r/m64,r64
	_TEST32( "19a501020304 sbb dword ptr [ebp+04030201h],esp", 0x19, 0xa5, 0x01, 0x02, 0x03, 04 );
	_TEST32( "676619a50102 sbb word ptr [di+0201h],sp", 0x67, 0x66, 0x19, 0xa5, 0x01, 0x02 );
	_TEST32( "6719a50102 sbb dword ptr [di+0201h],esp", 0x67, 0x19, 0xa5, 0x01, 0x02 );
	_TEST64( "4d19648901 sbb qword ptr [r9+rcx*4+0000000000000001h],r12", 0x4D, 0x19, 0x64, 0x89, 0x01 );
	// 1A /r SBB r8,r/m8
	// REX + 1A /r SBB r8,r/m8
	_TEST32( "1aa501020304 sbb ah,byte ptr [ebp+04030201h]", 0x1A, 0xa5, 0x01, 0x02, 0x03, 04 );
	_TEST64( "481aa501020304 sbb spl,byte ptr [rbp+0000000004030201h]", 0x48, 0x1A, 0xa5, 0x01, 0x02, 0x03, 04 );
	_TEST64( "481a64a501 sbb spl,byte ptr [rbp+0000000000000001h]", 0x48, 0x1A, 0x64, 0xa5, 0x01, 0x02, 0x03, 04 );
	// 1B /r SBB r16,r/m16
	// 1B /r SBB r32,r/m32
	// REX.W + 1B /r SBB r64,r/m64
	_TEST32( "1ba501020304 sbb esp,dword ptr [ebp+04030201h]", 0x1B, 0xa5, 0x01, 0x02, 0x03, 04 );
	_TEST32( "67661ba50102 sbb sp,word ptr [di+0201h]", 0x67, 0x66, 0x1B, 0xa5, 0x01, 0x02 );
	_TEST32( "671ba50102 sbb esp,dword ptr [di+0201h]", 0x67, 0x1B, 0xa5, 0x01, 0x02 );
	_TEST64( "4d1b648901 sbb r12,qword ptr [r9+rcx*4+0000000000000001h]", 0x4D, 0x1B, 0x64, 0x89, 0x01 );

	// D0 /7 SAR r/m8, 1 M1 Valid Valid Signed divide* r/m8 by 2, once.
	// REX + D0 /7 SAR r/m8**, 1 M1 Valid N.E. Signed divide* r/m8 by 2, once.
	_TEST32( "d038 sar byte ptr [eax],01h", 0xD0, 0x38 );
	_TEST32( "d0f8 sar al,01h", 0xD0, 0xF8 );
	_TEST64( "48d0f8 sar al,01h", 0x48, 0xD0, 0xF8 );
	// D2 /7 SAR r/m8, CL MC Valid Valid Signed divide* r/m8 by 2, CL times.
	// REX + D2 /7 SAR r/m8**, CL MC Valid N.E. Signed divide* r/m8 by 2, CL times.
	_TEST32( "d238 sar byte ptr [eax],cl", 0xD2, 0x38 );
	_TEST32( "d2f8 sar al,cl", 0xD2, 0xF8 );
	_TEST64( "48d2f8 sar al,cl", 0x48, 0xD2, 0xF8 );
	// C0 /7 ib SAR r/m8, imm8 MI Valid Valid Signed divide* r/m8 by 2, imm8 time.
	// REX + C0 /7 ib SAR r/m8**, imm8 MI Valid N.E. Signed divide* r/m8 by 2, imm8 times.
	_TEST32( "c038ff sar byte ptr [eax],0ffh", 0xC0, 0x38, 0xFF );
	_TEST32( "c0f8ff sar al,0ffh", 0xC0, 0xF8, 0xFF );
	_TEST64( "48c0f8ff sar al,0ffh", 0x48, 0xC0, 0xF8, 0xFF );
	// D1 /7 SAR r/m16,1 M1 Valid Valid Signed divide* r/m16 by 2, once.
	// D1 /7 SAR r/m32, 1 M1 Valid Valid Signed divide* r/m32 by 2, once.
	// REX.W + D1 /7 SAR r/m64, 1 M1 Valid N.E. Signed divide* r/m64 by 2, once.
	_TEST32( "d138 sar dword ptr [eax],01h", 0xD1, 0x38 );
	_TEST32( "d1f8 sar eax,01h", 0xD1, 0xF8 );
	_TEST64( "48d1f8 sar rax,01h", 0x48, 0xD1, 0xF8 );
	// D3 /7 SAR r/m16, CL MC Valid Valid Signed divide* r/m16 by 2, CL times.
	// D3 /7 SAR r/m32, CL MC Valid Valid Signed divide* r/m32 by 2, CL times.
	// REX.W + D3 /7 SAR r/m64, CL MC Valid N.E. Signed divide* r/m64 by 2, CL times.
	_TEST32( "d338 sar dword ptr [eax],cl", 0xD3, 0x38 );
	_TEST32( "d3f8 sar eax,cl", 0xD3, 0xF8 );
	_TEST64( "48d3f8 sar rax,cl", 0x48, 0xD3, 0xF8 );
	// C1 /7 ib SAR r/m16, imm8 MI Valid Valid Signed divide* r/m16 by 2, imm8 times.
	// C1 /7 ib SAR r/m32, imm8 MI Valid Valid Signed divide* r/m32 by 2, imm8 times.
	// REX.W + C1 /7 ib SAR r/m64, imm8 MI Valid N.E. Signed divide* r/m64 by 2, imm8 times
	_TEST32( "c138ff sar dword ptr [eax],0ffh", 0xC1, 0x38, 0xff );
	_TEST32( "c1f8ff sar eax,0ffh", 0xC1, 0xF8, 0xff );
	_TEST64( "48c1f8ff sar rax,0ffh", 0x48, 0xC1, 0xF8, 0xff );

	// D0 /4 SHL r/m8, 1 M1 Valid Valid Multiply r/m8 by 2, once.
	// REX + D0 /4 SHL r/m8**, 1 M1 Valid N.E. Multiply r/m8 by 2, once.
	_TEST32( "d020 shl byte ptr [eax],01h", 0xD0, 0x20 );
	_TEST32( "d0e0 shl al,01h", 0xD0, 0xE0 );
	_TEST64( "48d0e0 shl al,01h", 0x48, 0xD0, 0xE0 );
	// D2 /4 SHL r/m8, CL MC Valid Valid Multiply r/m8 by 2, CL times.
	// REX + D2 /4 SHL r/m8**, CL MC Valid N.E. Multiply r/m8 by 2, CL times.
	_TEST32( "d220 shl byte ptr [eax],cl", 0xD2, 0x20 );
	_TEST32( "d2e0 shl al,cl", 0xD2, 0xE0 );
	_TEST64( "48d2e0 shl al,cl", 0x48, 0xD2, 0xE0 );
	// C0 /4 ib SHL r/m8, imm8 MI Valid Valid Multiply r/m8 by 2, imm8 times.
	// REX + C0 /4 ib SHL r/m8**, imm8 MI Valid N.E. Multiply r/m8 by 2, imm8 times.
	_TEST32( "c020ff shl byte ptr [eax],0ffh", 0xC0, 0x20, 0xFF );
	_TEST32( "c0e0ff shl al,0ffh", 0xC0, 0xE0, 0xFF );
	_TEST64( "48c0e0ff shl al,0ffh", 0x48, 0xC0, 0xE0, 0xFF );
	// D1 /4 SHL r/m16,1 M1 Valid Valid Multiply r/m16 by 2, once.
	// D1 /4 SHL r/m32,1 M1 Valid Valid Multiply r/m32 by 2, once.
	// REX.W + D1 /4 SHL r/m64,1 M1 Valid N.E. Multiply r/m64 by 2, once.
	_TEST32( "d120 shl dword ptr [eax],01h", 0xD1, 0x20 );
	_TEST32( "d1e0 shl eax,01h", 0xD1, 0xE0 );
	_TEST64( "48d1e0 shl rax,01h", 0x48, 0xD1, 0xE0 );
	// D3 /4 SHL r/m16, CL MC Valid Valid Multiply r/m16 by 2, CL times.
	// D3 /4 SHL r/m32, CL MC Valid Valid Multiply r/m32 by 2, CL times.
	// REX.W + D3 /4 SHL r/m64, CL MC Valid N.E. Multiply r/m64 by 2, CL times.
	_TEST32( "d320 shl dword ptr [eax],cl", 0xD3, 0x20 );
	_TEST32( "d3e0 shl eax,cl", 0xD3, 0xE0 );
	_TEST64( "48d3e0 shl rax,cl", 0x48, 0xD3, 0xE0 );
	// C1 /4 ib SHL r/m16, imm8 MI Valid Valid Multiply r/m16 by 2, imm8 times.
	// C1 /4 ib SHL r/m32, imm8 MI Valid Valid Multiply r/m32 by 2, imm8 times.
	// REX.W + C1 /4 ib SHL r/m64, imm8 MI Valid N.E. Multiply r/m64 by 2, imm8 times.
	_TEST32( "c120ff shl dword ptr [eax],0ffh", 0xC1, 0x20, 0xff );
	_TEST32( "c1e0ff shl eax,0ffh", 0xC1, 0xE0, 0xff );
	_TEST64( "48c1e0ff shl rax,0ffh", 0x48, 0xC1, 0xE0, 0xff );

	// D0 /5 SHR r/m8,1 M1 Valid Valid Unsigned divide r/m8 by 2, once.
	// REX + D0 /5 SHR r/m8**, 1 M1 Valid N.E. Unsigned divide r/m8 by 2, once.
	_TEST32( "d028 shr byte ptr [eax],01h", 0xD0, 0x28 );
	_TEST32( "d0e8 shr al,01h", 0xD0, 0xE8 );
	_TEST64( "48d0e8 shr al,01h", 0x48, 0xD0, 0xE8 );
	// D2 /5 SHR r/m8, CL MC Valid Valid Unsigned divide r/m8 by 2, CL times.
	// REX + D2 /5 SHR r/m8**, CL MC Valid N.E. Unsigned divide r/m8 by 2, CL times.
	_TEST32( "d228 shr byte ptr [eax],cl", 0xD2, 0x28 );
	_TEST32( "d2e8 shr al,cl", 0xD2, 0xE8 );
	_TEST64( "48d2e8 shr al,cl", 0x48, 0xD2, 0xE8 );
	// C0 /5 ib SHR r/m8, imm8 MI Valid Valid Unsigned divide r/m8 by 2, imm8 times.
	// REX + C0 /5 ib SHR r/m8**, imm8 MI Valid N.E. Unsigned divide r/m8 by 2, imm8 times.
	_TEST32( "c028ff shr byte ptr [eax],0ffh", 0xC0, 0x28, 0xFF );
	_TEST32( "c0e8ff shr al,0ffh", 0xC0, 0xE8, 0xFF );
	_TEST64( "48c0e8ff shr al,0ffh", 0x48, 0xC0, 0xE8, 0xFF );
	// D1 /5 SHR r/m16, 1 M1 Valid Valid Unsigned divide r/m16 by 2, once.
	// D1 /5 SHR r/m32, 1 M1 Valid Valid Unsigned divide r/m32 by 2, once.
	// REX.W + D1 /5 SHR r/m64, 1 M1 Valid N.E. Unsigned divide r/m64 by 2, once.
	_TEST32( "d128 shr dword ptr [eax],01h", 0xD1, 0x28 );
	_TEST32( "d1e8 shr eax,01h", 0xD1, 0xE8 );
	_TEST64( "48d1e8 shr rax,01h", 0x48, 0xD1, 0xE8 );
	// D3 /5 SHR r/m16, CL MC Valid Valid Unsigned divide r/m16 by 2, CL times
	// D3 /5 SHR r/m32, CL MC Valid Valid Unsigned divide r/m32 by 2, CL times.
	// REX.W + D3 /5 SHR r/m64, CL MC Valid N.E. Unsigned divide r/m64 by 2, CL times.
	_TEST32( "d328 shr dword ptr [eax],cl", 0xD3, 0x28 );
	_TEST32( "d3e8 shr eax,cl", 0xD3, 0xE8 );
	_TEST64( "48d3e8 shr rax,cl", 0x48, 0xD3, 0xE8 );
	// C1 /5 ib SHR r/m16, imm8 MI Valid Valid Unsigned divide r/m16 by 2, imm8 times.
	// C1 /5 ib SHR r/m32, imm8 MI Valid Valid Unsigned divide r/m32 by 2, imm8 times.
	// REX.W + C1 /5 ib SHR r/m64, imm8 MI Valid N.E. Unsigned divide r/m64 by 2, imm8 times.
	_TEST32( "c128ff shr dword ptr [eax],0ffh", 0xC1, 0x28, 0xff );
	_TEST32( "c1e8ff shr eax,0ffh", 0xC1, 0xE8, 0xff );
	_TEST64( "48c1e8ff shr rax,0ffh", 0x48, 0xC1, 0xE8, 0xff );

	// 9E SAHF
	_TEST32( "9e sahf", 0x9E );
	_TEST64( "9e sahf", 0x9E );

	// F3 0F 52 /r RSQRTSS xmm1,xmm2/m32
	_TEST64( "f30f5200 rsqrtss xmm0,dword ptr [rax]", 0xF3, 0x0F, 0x52, 0x00 );
	_TEST32( "f30f52c1 rsqrtss xmm0,xmm1", 0xF3, 0x0F, 0x52, 0xC1 );
	// VEX.NDS.LIG.F3.0F.WIG 52 /r VRSQRTSS xmm1,xmm2,xmm3/m32
	_TEST64_VEX( "c4e14a5200 vrsqrtss xmm0,xmm6,dword ptr [rax]", 0xC4, 0xE1, 0x4A, 0x52, 0x00 );
	_TEST32_VEX( "c4e14a52d8 vrsqrtss xmm3,xmm6,xmm0", 0xC4, 0xE1, 0x4A, 0x52, 0xD8 );

	// 0F 52 /r RSQRTPS xmm1,xmm2/m128
	_TEST64_VEX( "0f5200 rsqrtps xmm0,oword ptr [rax]", 0x0F, 0x52, 0x00 );
	_TEST32_VEX( "0f52c1 rsqrtps xmm0,xmm1", 0x0F, 0x52, 0xC1 );
	// VEX.128.0F.WIG 52 /r VRSQRTPS xmm1,xmm2/m128
	// VEX.256.0F.WIG 52 /r VRSQRTPS ymm1,ymm2/m256
	_TEST64_VEX( "c4e17852d8 vrsqrtps xmm3,xmm0", 0xC4, 0xE1, 0x78, 0x52, 0xD8 );
	_TEST32_VEX( "c4e17852d8 vrsqrtps xmm3,xmm0", 0xC4, 0xE1, 0x78, 0x52, 0xD8 );
	_TEST32_VEX( "c4e17c5200 vrsqrtps ymm0,ymmword ptr [eax]", 0xC4, 0xE1, 0x7C, 0x52, 0x00 );

	// 0F AA RSM NP Invalid Valid Resume operation of interrupted program.
	_TEST32( "0faa rsm", 0x0F, 0xAA );
	_TEST64( "FAIL", 0x0F, 0xAA );

	// 66 0F 3A 0A /r ib ROUNDSS xmm1,xmm2/m32,imm8
	_TEST64_VEX( "660f3a0a00ff roundss xmm0,dword ptr [rax],0ffh", 0x66, 0x0F, 0x3A, 0x0A, 0x00, 0xFF );
	_TEST32_VEX( "660f3a0ac1ff roundss xmm0,xmm1,0ffh", 0x66, 0x0F, 0x3A, 0x0A, 0xC1, 0xFF );
	// VEX.NDS.LIG.66.0F3A.WIG 0A ib VROUNDSS xmm1,xmm2,xmm3/m32,imm8
	_TEST64_VEX( "c4e3790ad8ff vroundss xmm3,xmm0,xmm0,0ffh", 0xC4, 0xE3, 0x79, 0x0A, 0xD8, 0xFF );
	_TEST32_VEX( "c4e3490ad8ff vroundss xmm3,xmm6,xmm0,0ffh", 0xC4, 0xE3, 0x49, 0x0A, 0xD8, 0xFF );

	// 66 0F 3A 0B /r ib ROUNDSD xmm1,xmm2/m64,imm8
	_TEST64_VEX( "660f3a0b00ff roundsd xmm0,qword ptr [rax],0ffh", 0x66, 0x0F, 0x3A, 0x0B, 0x00, 0xFF );
	_TEST32_VEX( "660f3a0bc1ff roundsd xmm0,xmm1,0ffh", 0x66, 0x0F, 0x3A, 0x0B, 0xC1, 0xFF );
	// VEX.NDS.LIG.66.0F3A.WIG 0B /r ib VROUNDSD xmm1,xmm2,xmm3/m64,imm8
	_TEST64_VEX( "c4e3790bd8ff vroundsd xmm3,xmm0,xmm0,0ffh", 0xC4, 0xE3, 0x79, 0x0B, 0xD8, 0xFF );
	_TEST32_VEX( "c4e3610bd8ff vroundsd xmm3,xmm3,xmm0,0ffh", 0xC4, 0xE3, 0x61, 0x0B, 0xD8, 0xFF );

	// 66 0F 3A 08 /r ib ROUNDPS xmm1,xmm2/m128,imm8
	_TEST64_VEX( "660f3a0800ff roundps xmm0,oword ptr [rax],0ffh", 0x66, 0x0F, 0x3A, 0x08, 0x00, 0xFF );
	_TEST32_VEX( "660f3a08c1ff roundps xmm0,xmm1,0ffh", 0x66, 0x0F, 0x3A, 0x08, 0xC1, 0xFF );
	// VEX.128.66.0F3A.WIG 08 /r ib VROUNDPS xmm1,xmm2/m128,imm8
	// VEX.256.66.0F3A.WIG 08 /r ib VROUNDPS ymm1,ymm2/m256,imm8
	_TEST64_VEX( "c4e37908d8ff vroundps xmm3,xmm0,0ffh", 0xC4, 0xE3, 0x79, 0x08, 0xD8, 0xFF );
	_TEST32_VEX( "c4e37908d8ff vroundps xmm3,xmm0,0ffh", 0xC4, 0xE3, 0x79, 0x08, 0xD8, 0xFF );
	_TEST32_VEX( "c4e37d0800ff vroundps ymm0,ymmword ptr [eax],0ffh", 0xC4, 0xE3, 0x7D, 0x08, 0x00, 0xFF );

	// ROUNDPD
	// 66 0F 3A 09 /r ib ROUNDPD xmm1,xmm2/m128,imm8
	_TEST64_VEX( "660f3a0900ff roundpd xmm0,oword ptr [rax],0ffh", 0x66, 0x0F, 0x3A, 0x09, 0x00, 0xFF );
	_TEST32_VEX( "660f3a09c1ff roundpd xmm0,xmm1,0ffh", 0x66, 0x0F, 0x3A, 0x09, 0xC1, 0xFF );
	// VEX.128.66.0F3A.WIG 09 /r ib VROUNDPD xmm1,xmm2/m128,imm8
	// VEX.256.66.0F3A.WIG 09 /r ib VROUNDPD ymm1,ymm2/m256,imm8
	_TEST64_VEX( "c4e37909d8ff vroundpd xmm3,xmm0,0ffh", 0xC4, 0xE3, 0x79, 0x09, 0xD8, 0xFF );
	_TEST32_VEX( "c4e37909d8ff vroundpd xmm3,xmm0,0ffh", 0xC4, 0xE3, 0x79, 0x09, 0xD8, 0xFF );
	_TEST32_VEX( "c4e37d0900ff vroundpd ymm0,ymmword ptr [eax],0ffh", 0xC4, 0xE3, 0x7D, 0x09, 0x00, 0xFF );

	// C3 RET
	// CB RET
	_TEST32( "c3 ret", 0xC3 );
	_TEST64( "c3 ret", 0xC3 );
	_TEST32( "cb retf", 0xCB );
	_TEST64( "cb retf", 0xCB );
	// C2 iw RET imm16
	// CA iw RET imm16
	_TEST32( "c2ffff ret 0ffffh", 0xC2, 0xFF, 0xFF );
	_TEST64( "c2ffff ret 0ffffh", 0xC2, 0xFF, 0xFF );
	_TEST32( "caffff retf 0ffffh", 0xCA, 0xFF, 0xFF );
	_TEST64( "caffff retf 0ffffh", 0xCA, 0xFF, 0xFF );


	// 0F 01 F9 RDTSCP
	_TEST32( "0f01f9 rdtscp", 0x0f, 0x01, 0xf9 );
	_TEST64( "0f01f9 rdtscp", 0x0f, 0x01, 0xf9 );

	// 0F 31 RDTSC
	_TEST32( "0f31 rdtsc", 0x0F, 0x31 );
	_TEST64( "0f31 rdtsc", 0x0F, 0x31 );

	// 0F C7 /6 RDRAND r16
	_TEST32( "660fc7f0 rdrand ax", 0x66, 0x0F, 0xC7, 0xF0 );
	_TEST64( "660fc7f0 rdrand ax", 0x66, 0x0F, 0xC7, 0xF0 );
	// 0F C7 /6 RDRAND r32
	_TEST32( "0fc7f0 rdrand eax", 0x0F, 0xC7, 0xF0 );
	_TEST64( "0fc7f0 rdrand eax", 0x0F, 0xC7, 0xF0 );
	// REX.W + 0F C7 /6 RDRAND r64
	_TEST64( "480fc7f0 rdrand rax", 0x48, 0x0F, 0xC7, 0xF0 );

	// 0F 33 RDPMC
	_TEST32( "0f33 rdpmc", 0x0F, 0x33 );
	_TEST64( "0f33 rdpmc", 0x0F, 0x33 );

	// 0F 32 RDMSR
	_TEST32( "0f32 rdmsr", 0x0F, 0x32 );
	_TEST64( "0f32 rdmsr", 0x0F, 0x32 );

	// F3 0F AE /0 RDFSBASE r32
	// REX.W + F3 0F AE /0 RDFSBASE r64
	_TEST32( "FAIL", 0x66, 0xF3, 0x0F, 0xAE, 0xC0 );
	_TEST64( "f30faec0 rdfsbase eax", 0xF3, 0x0F, 0xAE, 0xC0 );
	_TEST64( "66f30faec0 rdfsbase eax", 0x66, 0xF3, 0x0F, 0xAE, 0xC0 );
	_TEST64( "f3480faec0 rdfsbase rax", 0xF3, 0x48, 0x0F, 0xAE, 0xC0 );
	// F3 0F AE /1 RDGSBASE r32
	// REX.W + F3 0F AE /1 RDGSBASE r64
	_TEST32( "FAIL", 0xF3, 0x0F, 0xAE, 0xC8 );
	_TEST64( "f30faec8 rdgsbase eax", 0xF3, 0x0F, 0xAE, 0xC8 );
	_TEST64( "66f30faec8 rdgsbase eax", 0x66, 0xF3, 0x0F, 0xAE, 0xC8 );
	_TEST64( "f3480faec8 rdgsbase rax", 0xF3, 0x48, 0x0F, 0xAE, 0xC8 );

	// F3 0F 53 /r RCPSS xmm1,xmm2/m32
	_TEST32( "f30f5310 rcpss xmm2,dword ptr [eax]", 0xF3, 0x0F, 0x53, 0x10 );
	_TEST32( "f30f53d8 rcpss xmm3,xmm0", 0xF3, 0x0F, 0x53, 0xD8 );
	_TEST64( "f30f5310 rcpss xmm2,dword ptr [rax]", 0xF3, 0x0F, 0x53, 0x10 );
	// VEX.NDS.LIG.F3.0F.WIG 53 /r VRCPSS xmm1,xmm2,xmm3/m32
	_TEST64_VEX( "c4e16253d8 vrcpss xmm3,xmm3,xmm0", 0xC4, 0xE1, 0x62, 0x53, 0xD8 );
	_TEST32_VEX( "c4e14253d8 vrcpss xmm3,xmm7,xmm0", 0xC4, 0xE1, 0x42, 0x53, 0xD8 );
	_TEST32_VEX( "c4e17a5318 vrcpss xmm3,xmm0,dword ptr [eax]", 0xC4, 0xE1, 0x7A, 0x53, 0x18 );

	// RCPPS
	// 0F 53 /r RCPPS xmm1,xmm2/m128
	_TEST64( "0f5300 rcpps xmm0,oword ptr [rax]", 0x0F, 0x53, 0x00 );
	_TEST32( "0f53c1 rcpps xmm0,xmm1", 0x0F, 0x53, 0xC1 );
	// VEX.128.0F.WIG 53 /r VRCPPS xmm1, xmm2/m128
	// VEX.256.0F.WIG 53 /r VRCPPS ymm1, ymm2/m256
	_TEST32_VEX( "c4e1785310 vrcpps xmm2,oword ptr [eax]", 0xC4, 0xE1, 0x78, 0x53, 0x10 );
	_TEST64_VEX( "c4e17c5310 vrcpps ymm2,ymmword ptr [rax]", 0xC4, 0xE1, 0x7C, 0x53, 0x10 );

	// D0 /2 RCL r/m8, 1
	// REX + D0 /2 RCL r/m8, 1
	_TEST32( "d010 rcl byte ptr [eax],01h", 0xD0, 0x10 );
	_TEST32( "d0d0 rcl al,01h", 0xD0, 0xD0 );
	_TEST64( "48d0d0 rcl al,01h", 0x48, 0xD0, 0xD0 );
	// D2 /2 RCL r/m8, CL
	// REX + D2 /2 RCL r/m8, CL
	_TEST32( "d210 rcl byte ptr [eax],cl", 0xD2, 0x10 );
	_TEST32( "d2d0 rcl al,cl", 0xD2, 0xD0 );
	_TEST64( "48d2d0 rcl al,cl", 0x48, 0xD2, 0xD0 );
	// C0 /2 ib RCL r/m8, imm8
	// REX + C0 /2 ib RCL r/m8, imm8
	_TEST32( "c010ff rcl byte ptr [eax],0ffh", 0xC0, 0x10, 0xFF );
	_TEST32( "c0d0ff rcl al,0ffh", 0xC0, 0xD0, 0xFF );
	_TEST64( "48c0d0ff rcl al,0ffh", 0x48, 0xC0, 0xD0, 0xFF );
	// D1 /2 RCL r/m16, 1
	// D1 /2 RCL r/m32, 1
	// REX.W + D1 /2 RCL r/m64, 1
	_TEST32( "d110 rcl dword ptr [eax],01h", 0xD1, 0x10 );
	_TEST32( "d1d0 rcl eax,01h", 0xD1, 0xD0 );
	_TEST64( "48d1d0 rcl rax,01h", 0x48, 0xD1, 0xD0 );
	// D3 /2 RCL r/m16, CL
	// D3 /2 RCL r/m32, CL
	// REX.W + D3 /2 RCL r/m64, CL
	_TEST32( "d310 rcl dword ptr [eax],cl", 0xD3, 0x10 );
	_TEST32( "d3d0 rcl eax,cl", 0xD3, 0xD0 );
	_TEST64( "48d3d0 rcl rax,cl", 0x48, 0xD3, 0xD0 );
	// C1 /2 ib RCL r/m16, imm8
	// C1 /2 ib RCL r/m32, imm8
	// REX.W + C1 /2 ib RCL r/m64, imm8
	_TEST32( "c110ff rcl dword ptr [eax],0ffh", 0xC1, 0x10, 0xff );
	_TEST32( "c1d0ff rcl eax,0ffh", 0xC1, 0xD0, 0xff );
	_TEST64( "48c1d0ff rcl rax,0ffh", 0x48, 0xC1, 0xD0, 0xff );

	// D0 /3 RCR r/m8, 1
	// REX + D0 /3 RCR r/m8, 1
	_TEST32( "d018 rcr byte ptr [eax],01h", 0xD0, 0x18 );
	_TEST32( "d0d8 rcr al,01h", 0xD0, 0xD8 );
	_TEST64( "48d0d8 rcr al,01h", 0x48, 0xD0, 0xD8 );
	// D2 /3 RCR r/m8, CL
	// REX + D2 /3 RCR r/m8, CL
	_TEST32( "d218 rcr byte ptr [eax],cl", 0xD2, 0x18 );
	_TEST32( "d2d8 rcr al,cl", 0xD2, 0xD8 );
	_TEST64( "48d2d8 rcr al,cl", 0x48, 0xD2, 0xD8 );
	// C0 /3 ib RCR r/m8, imm8
	// REX + C0 /3 ib RCR r/m8, imm8
	_TEST32( "c018ff rcr byte ptr [eax],0ffh", 0xC0, 0x18, 0xFF );
	_TEST32( "c0d8ff rcr al,0ffh", 0xC0, 0xD8, 0xFF );
	_TEST64( "48c0d8ff rcr al,0ffh", 0x48, 0xC0, 0xD8, 0xFF );
	// D1 /3 RCR r/m16, 1
	// D1 /3 RCR r/m32, 1
	// REX.W + D1 /3 RCR r/m64, 1
	_TEST32( "d118 rcr dword ptr [eax],01h", 0xD1, 0x18 );
	_TEST32( "d1d8 rcr eax,01h", 0xD1, 0xD8 );
	_TEST64( "48d1d8 rcr rax,01h", 0x48, 0xD1, 0xD8 );
	// D3 /3 RCR r/m16, CL
	// D3 /3 RCR r/m32, CL
	// REX.W + D3 /3 RCR r/m64, CL
	_TEST32( "d318 rcr dword ptr [eax],cl", 0xD3, 0x18 );
	_TEST32( "d3d8 rcr eax,cl", 0xD3, 0xD8 );
	_TEST64( "48d3d8 rcr rax,cl", 0x48, 0xD3, 0xD8 );
	// C1 /3 ib RCR r/m16, imm8
	// C1 /3 ib RCR r/m32, imm8
	// REX.W + C1 /3 ib RCR r/m64, imm8
	_TEST32( "c118ff rcr dword ptr [eax],0ffh", 0xC1, 0x18, 0xff );
	_TEST32( "c1d8ff rcr eax,0ffh", 0xC1, 0xD8, 0xff );
	_TEST64( "48c1d8ff rcr rax,0ffh", 0x48, 0xC1, 0xD8, 0xff );

	// D0 /0 ROL r/m8, 1
	// REX + D0 /0 ROL r/m8, 1
	_TEST32( "d000 rol byte ptr [eax],01h", 0xD0, 0x00 );
	_TEST32( "d0c0 rol al,01h", 0xD0, 0xC0 );
	_TEST64( "48d0c0 rol al,01h", 0x48, 0xD0, 0xC0 );
	// D2 /0 ROL r/m8, CL
	// REX + D2 /0 ROL r/m8, CL
	_TEST32( "d200 rol byte ptr [eax],cl", 0xD2, 0x00 );
	_TEST32( "d2c0 rol al,cl", 0xD2, 0xC0 );
	_TEST64( "48d2c0 rol al,cl", 0x48, 0xD2, 0xC0 );
	// C0 /0 ib ROL r/m8, imm8
	// REX + C0 /0 ib ROL r/m8, imm8
	_TEST32( "c000ff rol byte ptr [eax],0ffh", 0xC0, 0x00, 0xFF );
	_TEST32( "c0c0ff rol al,0ffh", 0xC0, 0xC0, 0xFF );
	_TEST64( "48c0c0ff rol al,0ffh", 0x48, 0xC0, 0xC0, 0xFF );
	// D1 /0 ROL r/m16, 1
	// D1 /0 ROL r/m32, 1
	// REX.W + D1 /0 ROL r/m64, 1
	_TEST32( "d100 rol dword ptr [eax],01h", 0xD1, 0x00 );
	_TEST32( "d1c0 rol eax,01h", 0xD1, 0xC0 );
	_TEST64( "48d1c0 rol rax,01h", 0x48, 0xD1, 0xC0 );
	// D3 /0 ROL r/m16, CL
	// D3 /0 ROL r/m32, CL
	// REX.W + D3 /0 ROL r/m64, CL
	_TEST32( "d300 rol dword ptr [eax],cl", 0xD3, 0x00 );
	_TEST32( "d3c0 rol eax,cl", 0xD3, 0xC0 );
	_TEST64( "48d3c0 rol rax,cl", 0x48, 0xD3, 0xC0 );
	// C1 /0 ib ROL r/m16, imm8
	// C1 /0 ib ROL r/m32, imm8
	// C1 /0 ib ROL r/m64, imm8
	_TEST32( "c100ff rol dword ptr [eax],0ffh", 0xC1, 0x00, 0xff );
	_TEST32( "c1c0ff rol eax,0ffh", 0xC1, 0xC0, 0xff );
	_TEST64( "48c1c0ff rol rax,0ffh", 0x48, 0xC1, 0xC0, 0xff );

	// D0 /1 ROR r/m8, 1
	// REX + D0 /1 ROR r/m8, 1
	_TEST32( "d008 ror byte ptr [eax],01h", 0xD0, 0x08 );
	_TEST32( "d0c8 ror al,01h", 0xD0, 0xC8 );
	_TEST64( "48d0c8 ror al,01h", 0x48, 0xD0, 0xC8 );
	// D2 /1 ROR r/m8, CL
	// REX + D2 /1 ROR r/m8, CL
	_TEST32( "d208 ror byte ptr [eax],cl", 0xD2, 0x08 );
	_TEST32( "d2c8 ror al,cl", 0xD2, 0xC8 );
	_TEST64( "48d2c8 ror al,cl", 0x48, 0xD2, 0xC8 );
	// C0 /1 ib ROR r/m8, imm8
	// REX + C0 /1 ib ROR r/m8, imm8
	_TEST32( "c008ff ror byte ptr [eax],0ffh", 0xC0, 0x08, 0xFF );
	_TEST32( "c0c8ff ror al,0ffh", 0xC0, 0xC8, 0xFF );
	_TEST64( "48c0c8ff ror al,0ffh", 0x48, 0xC0, 0xC8, 0xFF );
	// D1 /1 ROR r/m16, 1
	// D1 /1 ROR r/m32, 1
	// REX.W + D1 /1 ROR r/m64, 1
	_TEST32( "d108 ror dword ptr [eax],01h", 0xD1, 0x08 );
	_TEST32( "d1c8 ror eax,01h", 0xD1, 0xC8 );
	_TEST64( "48d1c8 ror rax,01h", 0x48, 0xD1, 0xC8 );
	// D3 /1 ROR r/m16, CL
	// D3 /1 ROR r/m32, CL
	// REX.W + D3 /1 ROR r/m64, CL
	_TEST32( "d308 ror dword ptr [eax],cl", 0xD3, 0x08 );
	_TEST32( "d3c8 ror eax,cl", 0xD3, 0xC8 );
	_TEST64( "48d3c8 ror rax,cl", 0x48, 0xD3, 0xC8 );
	// C1 /1 ib ROR r/m16, imm8
	// C1 /1 ib ROR r/m32, imm8
	// REX.W + C1 /1 ib ROR r/m64, imm8
	_TEST32( "c108ff ror dword ptr [eax],0ffh", 0xC1, 0x08, 0xff );
	_TEST32( "c1c8ff ror eax,0ffh", 0xC1, 0xC8, 0xff );
	_TEST64( "48c1c8ff ror rax,0ffh", 0x48, 0xC1, 0xC8, 0xff );

	// PXOR
	// 0F EF /r PXOR mm,mm/m64
	_TEST64( "0fef00 pxor mm0,qword ptr [rax]", 0x0F, 0xEF, 0x00 );
	_TEST32( "0fefc1 pxor mm0,mm1", 0x0F, 0xEF, 0xC1 );
	// 66 0F EF /r PXOR xmm1,xmm2/m128
	_TEST64( "660fef00 pxor xmm0,oword ptr [rax]", 0x66, 0x0F, 0xEF, 0x00 );
	_TEST32( "660fefc1 pxor xmm0,xmm1", 0x66, 0x0F, 0xEF, 0xC1 );
	// VEX.NDS.128.66.0F.WIG EF /r VPXOR xmm1,xmm2,xmm3/m128
	_TEST64_VEX( "c4e179ef00 vpxor xmm0,xmm0,oword ptr [rax]", 0xC4, 0xE1, 0x79, 0xEF, 0x00 );
	_TEST32_VEX( "c4e179efc1 vpxor xmm0,xmm0,xmm1", 0xC4, 0xE1, 0x79, 0xEF, 0xC1 );
	// VEX.NDS.256.66.0F.WIG EF /r VPXOR ymm1,ymm2,ymm3/m256
	_TEST64_VEX( "c4e17def00 vpxor ymm0,ymm0,ymmword ptr [rax]", 0xC4, 0xE1, 0x7D, 0xEF, 0x00 );
	_TEST32_VEX( "c4e17defc1 vpxor ymm0,ymm0,ymm1", 0xC4, 0xE1, 0x7D, 0xEF, 0xC1 );

	// PUSHF
	// 9C PUSHF NP Valid Valid Push lower 16 bits of EFLAGS.
	_TEST32( "669c pushf", 0x66, 0x9C );
	_TEST64( "669c pushf", 0x66, 0x9C );
	// 9C PUSHFD NP N.E. Valid Push EFLAGS.
	_TEST32( "9c pushfd", 0x9C );
	_TEST64( "FAIL", 0x9C );
	// 9C PUSHFQ NP Valid N.E. Push RFLAGS.
	_TEST64( "489c pushfq", 0x48, 0x9C );

	// PUSHA
	// 60 PUSHA NP Invalid Valid Push AX, CX, DX, BX, original SP, BP, SI, and DI.
	// 60 PUSHAD NP Invalid Valid Push EAX, ECX, EDX, EBX, original ESP, EBP, ESI, and EDI.
	_TEST32( "60 pushad", 0x60 );
	_TEST64( "FAIL", 0x60 );
	_TEST32( "6660 pusha", 0x66, 0x60 );

	// FF /6 PUSH r/m16 M Valid Valid Push r/m16.
	// FF /6 PUSH r/m32 M N.E. Valid Push r/m32.
	// FF /6 PUSH r/m64 M Valid N.E. Push r/m64.
	// 32 BIT.
	_TEST32( "ff30 push dword ptr [eax]", 0xFF, 0x30 );
	_TEST32( "fff1 push ecx", 0xFF, 0xF1 );
	_TEST32( "66ff30 push word ptr [eax]", 0x66, 0xFF, 0x30 );
	_TEST32( "66fff1 push cx", 0x66, 0xFF, 0xF1 );
	_TEST32( "67ff30 push dword ptr [bx+si]", 0x67, 0xFF, 0x30 );
	_TEST32( "67fff1 push ecx", 0x67, 0xFF, 0xF1 );
	_TEST32( "6667ff30 push word ptr [bx+si]", 0x66, 0x67, 0xFF, 0x30 );
	_TEST32( "6667fff1 push cx", 0x66, 0x67, 0xFF, 0xF1 );
	// 64 BIT.
	_TEST64( "ff30 push qword ptr [rax]", 0xFF, 0x30 );
	_TEST64( "fff1 push rcx", 0xFF, 0xF1 );
	_TEST64( "66ff30 push word ptr [rax]", 0x66, 0xFF, 0x30 );
	_TEST64( "66fff1 push cx", 0x66, 0xFF, 0xF1 );
	_TEST64( "67ff30 push qword ptr [eax]", 0x67, 0xFF, 0x30 );
	_TEST64( "67fff1 push rcx", 0x67, 0xFF, 0xF1 );
	_TEST64( "6667ff30 push word ptr [eax]", 0x66, 0x67, 0xFF, 0x30 );
	_TEST64( "6667fff1 push cx", 0x66, 0x67, 0xFF, 0xF1 );
	_TEST64( "48ff30 push qword ptr [rax]", 0x48, 0xFF, 0x30 );
	_TEST64( "48fff1 push rcx", 0x48, 0xFF, 0xF1 );
	// 50+rw PUSH r16 O Valid Valid Push r16.
	// 50+rd PUSH r32 O N.E. Valid Push r32.
	// 50+rd PUSH r64 O Valid N.E. Push r64.
	_TEST32( "50 push eax", 0x50 );
	_TEST32( "6650 push ax", 0x66, 0x50 );
	_TEST32( "6750 push eax", 0x67, 0x50 );
	_TEST64( "50 push rax", 0x50 );
	_TEST64( "6650 push ax", 0x66, 0x50 );
	_TEST64( "6750 push rax", 0x67, 0x50 );
	_TEST64( "4850 push rax", 0x48, 0x50 );
	// 6A PUSH imm8 I Valid Valid Push imm8.
	// 68 PUSH imm16 I Valid Valid Push imm16.
	// 68 PUSH imm32 I Valid Valid Push imm32.
	// TODO: Sprawdzic pod jakims nomalnym debugerem nie WinDBG.
	_TEST32( "6aff push 0ffffffffh", 0x6A, 0xFF );
	_TEST32( "6a20 push 00000020h", 0x6A, 0x20 );
	_TEST32( "666aff push 0ffffh", 0x66, 0x6A, 0xFF );
	_TEST32( "6820204050 push 50402020h", 0x68, 0x20, 0x20, 0x40, 0x50 );
	_TEST32( "68ff20ff11 push 11ff20ffh", 0x68, 0xFF, 0x20, 0xFF, 0x11 );
	_TEST32( "6668ff11 push 11ffh", 0x66, 0x68, 0xFF, 0x11 );
	_TEST64( "6668ff11 push 11ffh", 0x66, 0x68, 0xFF, 0x11 );
	_TEST64( "68ff111122 push 221111ffh", 0x68, 0xFF, 0x11, 0x11, 0x22 );
	_TEST64( "4868ff111122 push 00000000221111ffh", 0x48, 0x68, 0xFF, 0x11, 0x11, 0x22 );
	_TEST64( "68ff1111ff push 0ff1111ffh", 0x68, 0xFF, 0x11, 0x11, 0xFF );
	_TEST64( "4868ff1111ff push 0ffffffffff1111ffh", 0x48, 0x68, 0xFF, 0x11, 0x11, 0xFF );
	// 0E PUSH CS NP Invalid Valid Push CS.
	// 16 PUSH SS NP Invalid Valid Push SS.
	// 1E PUSH DS NP Invalid Valid Push DS.
	// 06 PUSH ES NP Invalid Valid Push ES.
	_TEST32( "0e push cs", 0x0e );
	_TEST32( "16 push ss", 0x16 );
	_TEST32( "1e push ds", 0x1e );
	_TEST32( "06 push es", 0x06 );
	_TEST64( "FAIL", 0x0e );
	_TEST64( "FAIL", 0x16 );
	_TEST64( "FAIL", 0x1e );
	_TEST64( "FAIL", 0x06 );
	// 0F A0 PUSH FS NP Valid Valid Push FS.
	// 0F A8 PUSH GS NP Valid Valid Push GS.
	_TEST32( "0fa0 push fs", 0x0f, 0xa0 );
	_TEST32( "0fa8 push gs", 0x0f, 0xa8 );
	_TEST64( "0fa0 push fs", 0x0f, 0xa0 );
	_TEST64( "0fa8 push gs", 0x0f, 0xa8 );

	// PUNPCKLB
	// 0F 60 /r PUNPCKLBW mm,mm/m32
	_TEST64( "0f6000 punpcklbw mm0,dword ptr [rax]", 0x0F, 0x60, 0x00 );
	_TEST32( "0f60c1 punpcklbw mm0,mm1", 0x0F, 0x60, 0xC1 );
	// 0F 61 /r PUNPCKLWD mm,mm/m32
	_TEST64( "0f6100 punpcklwd mm0,dword ptr [rax]", 0x0F, 0x61, 0x00 );
	_TEST32( "0f61c1 punpcklwd mm0,mm1", 0x0F, 0x61, 0xC1 );
	// 0F 62 /r PUNPCKLDQ mm,mm/m32
	_TEST64( "0f6200 punpckldq mm0,dword ptr [rax]", 0x0F, 0x62, 0x00 );
	_TEST32( "0f62c1 punpckldq mm0,mm1", 0x0F, 0x62, 0xC1 );
	// 66 0F 60 /r PUNPCKLBW xmm1,xmm2/m128
	_TEST64( "660f6000 punpcklbw xmm0,oword ptr [rax]", 0x66, 0x0F, 0x60, 0x00 );
	_TEST32( "660f60c1 punpcklbw xmm0,xmm1", 0x66, 0x0F, 0x60, 0xC1 );
	// 66 0F 61 /r PUNPCKLWD xmm1,xmm2/m128
	_TEST64( "660f6100 punpcklwd xmm0,oword ptr [rax]", 0x66, 0x0F, 0x61, 0x00 );
	_TEST32( "660f61c1 punpcklwd xmm0,xmm1", 0x66, 0x0F, 0x61, 0xC1 );
	// 66 0F 62 /r PUNPCKLDQ xmm1,xmm2/m128
	_TEST64( "660f6200 punpckldq xmm0,oword ptr [rax]", 0x66, 0x0F, 0x62, 0x00 );
	_TEST32( "660f62c1 punpckldq xmm0,xmm1", 0x66, 0x0F, 0x62, 0xC1 );
	// 66 0F 6C /r PUNPCKLQDQ xmm1,xmm2/m128
	_TEST64( "660f6c00 punpcklqdq xmm0,oword ptr [rax]", 0x66, 0x0F, 0x6c, 0x00 );
	_TEST32( "660f6cc1 punpcklqdq xmm0,xmm1", 0x66, 0x0F, 0x6c, 0xC1 );
	// VEX.NDS.128.66.0F.WIG 60/r VPUNPCKLBW xmm1,xmm2,xmm3/m128
	_TEST64_VEX( "c4e1796000 vpunpcklbw xmm0,xmm0,oword ptr [rax]", 0xC4, 0xE1, 0x79, 0x60, 0x00 );
	_TEST32_VEX( "c4e17960c1 vpunpcklbw xmm0,xmm0,xmm1", 0xC4, 0xE1, 0x79, 0x60, 0xC1 );
	// VEX.NDS.128.66.0F.WIG 61/r VPUNPCKLWD xmm1,xmm2,xmm3/m128
	_TEST64_VEX( "c4e1796100 vpunpcklwd xmm0,xmm0,oword ptr [rax]", 0xC4, 0xE1, 0x79, 0x61, 0x00 );
	_TEST32_VEX( "c4e17961c1 vpunpcklwd xmm0,xmm0,xmm1", 0xC4, 0xE1, 0x79, 0x61, 0xC1 );
	// VEX.NDS.128.66.0F.WIG 62/r VPUNPCKLDQ xmm1,xmm2,xmm3/m128
	_TEST64_VEX( "c4e1796200 vpunpckldq xmm0,xmm0,oword ptr [rax]", 0xC4, 0xE1, 0x79, 0x62, 0x00 );
	_TEST32_VEX( "c4e17962c1 vpunpckldq xmm0,xmm0,xmm1", 0xC4, 0xE1, 0x79, 0x62, 0xC1 );
	// VEX.NDS.128.66.0F.WIG 6C/r VPUNPCKLQDQ xmm1,xmm2,xmm3/m128
	_TEST64_VEX( "c4e1796c00 vpunpcklqdq xmm0,xmm0,oword ptr [rax]", 0xC4, 0xE1, 0x79, 0x6c, 0x00 );
	_TEST32_VEX( "c4e1796cc1 vpunpcklqdq xmm0,xmm0,xmm1", 0xC4, 0xE1, 0x79, 0x6c, 0xC1 );

	// VEX.NDS.256.66.0F.WIG 60 /r VPUNPCKLBW ymm1,ymm2,ymm3/m256
	_TEST64_VEX( "c4e17d6000 vpunpcklbw ymm0,ymm0,ymmword ptr [rax]", 0xC4, 0xE1, 0x7D, 0x60, 0x00 );
	_TEST32_VEX( "c4e17d60c1 vpunpcklbw ymm0,ymm0,ymm1", 0xC4, 0xE1, 0x7D, 0x60, 0xC1 );
	// VEX.NDS.256.66.0F.WIG 61 /r VPUNPCKLWD ymm1,ymm2,ymm3/m256
	_TEST64_VEX( "c4e17d6100 vpunpcklwd ymm0,ymm0,ymmword ptr [rax]", 0xC4, 0xE1, 0x7D, 0x61, 0x00 );
	_TEST32_VEX( "c4e17d61c1 vpunpcklwd ymm0,ymm0,ymm1", 0xC4, 0xE1, 0x7D, 0x61, 0xC1 );
	// VEX.NDS.256.66.0F.WIG 62 /r VPUNPCKLDQ ymm1,ymm2,ymm3/m256
	_TEST64_VEX( "c4e17d6200 vpunpckldq ymm0,ymm0,ymmword ptr [rax]", 0xC4, 0xE1, 0x7D, 0x62, 0x00 );
	_TEST32_VEX( "c4e17d62c1 vpunpckldq ymm0,ymm0,ymm1", 0xC4, 0xE1, 0x7D, 0x62, 0xC1 );
	// VEX.NDS.256.66.0F.WIG 6C /r VPUNPCKLQDQ ymm1,ymm2,ymm3/m256
	_TEST64_VEX( "c4e17d6c00 vpunpcklqdq ymm0,ymm0,ymmword ptr [rax]", 0xC4, 0xE1, 0x7D, 0x6c, 0x00 );
	_TEST32_VEX( "c4e17d6cc1 vpunpcklqdq ymm0,ymm0,ymm1", 0xC4, 0xE1, 0x7D, 0x6c, 0xC1 );

	// PUNPCKHB
	// 0F 68 /r PUNPCKHBW mm,mm/m64
	_TEST64( "0f6800 punpckhbw mm0,qword ptr [rax]", 0x0F, 0x68, 0x00 );
	_TEST32( "0f68c1 punpckhbw mm0,mm1", 0x0F, 0x68, 0xC1 );
	// 0F 69 /r PUNPCKHWD mm,mm/m64
	_TEST64( "0f6900 punpckhwd mm0,qword ptr [rax]", 0x0F, 0x69, 0x00 );
	_TEST32( "0f69c1 punpckhwd mm0,mm1", 0x0F, 0x69, 0xC1 );
	// 0F 6A /r PUNPCKHDQ mm,mm/m64
	_TEST64( "0f6a00 punpckhdq mm0,qword ptr [rax]", 0x0F, 0x6A, 0x00 );
	_TEST32( "0f6ac1 punpckhdq mm0,mm1", 0x0F, 0x6A, 0xC1 );
	// 66 0F 68 /r PUNPCKHBW xmm1,xmm2/m128
	_TEST64( "660f6800 punpckhbw xmm0,oword ptr [rax]", 0x66, 0x0F, 0x68, 0x00 );
	_TEST32( "660f68c1 punpckhbw xmm0,xmm1", 0x66, 0x0F, 0x68, 0xC1 );
	// 66 0F 69 /r PUNPCKHWD xmm1,xmm2/m128
	_TEST64( "660f6900 punpckhwd xmm0,oword ptr [rax]", 0x66, 0x0F, 0x69, 0x00 );
	_TEST32( "660f69c1 punpckhwd xmm0,xmm1", 0x66, 0x0F, 0x69, 0xC1 );
	// 66 0F 6A /r PUNPCKHDQ xmm1,xmm2/m128
	_TEST64( "660f6a00 punpckhdq xmm0,oword ptr [rax]", 0x66, 0x0F, 0x6A, 0x00 );
	_TEST32( "660f6ac1 punpckhdq xmm0,xmm1", 0x66, 0x0F, 0x6A, 0xC1 );
	// 66 0F 6D /r PUNPCKHQDQ xmm1,xmm2/m128
	_TEST64( "660f6d00 punpckhqdq xmm0,oword ptr [rax]", 0x66, 0x0F, 0x6D, 0x00 );
	_TEST32( "660f6dc1 punpckhqdq xmm0,xmm1", 0x66, 0x0F, 0x6D, 0xC1 );
	// VEX.NDS.128.66.0F.WIG 68/r VPUNPCKHBW xmm1,xmm2,xmm3/m128
	_TEST64_VEX( "c4e1796800 vpunpckhbw xmm0,xmm0,oword ptr [rax]", 0xC4, 0xE1, 0x79, 0x68, 0x00 );
	_TEST32_VEX( "c4e17968c1 vpunpckhbw xmm0,xmm0,xmm1", 0xC4, 0xE1, 0x79, 0x68, 0xC1 );
	// VEX.NDS.128.66.0F.WIG 69/r VPUNPCKHWD xmm1,xmm2,xmm3/m128
	_TEST64_VEX( "c4e1796900 vpunpckhwd xmm0,xmm0,oword ptr [rax]", 0xC4, 0xE1, 0x79, 0x69, 0x00 );
	_TEST32_VEX( "c4e17969c1 vpunpckhwd xmm0,xmm0,xmm1", 0xC4, 0xE1, 0x79, 0x69, 0xC1 );
	// VEX.NDS.128.66.0F.WIG 6A/r VPUNPCKHDQ xmm1,xmm2,xmm3/m128
	_TEST64_VEX( "c4e1796a00 vpunpckhdq xmm0,xmm0,oword ptr [rax]", 0xC4, 0xE1, 0x79, 0x6a, 0x00 );
	_TEST32_VEX( "c4e1796ac1 vpunpckhdq xmm0,xmm0,xmm1", 0xC4, 0xE1, 0x79, 0x6a, 0xC1 );
	// VEX.NDS.128.66.0F.WIG 6D/r VPUNPCKHQDQ xmm1,xmm2,xmm3/m128
	_TEST64_VEX( "c4e1796d00 vpunpckhqdq xmm0,xmm0,oword ptr [rax]", 0xC4, 0xE1, 0x79, 0x6d, 0x00 );
	_TEST32_VEX( "c4e1796dc1 vpunpckhqdq xmm0,xmm0,xmm1", 0xC4, 0xE1, 0x79, 0x6d, 0xC1 );
	// VEX.NDS.256.66.0F.WIG 68 /r VPUNPCKHBW ymm1,ymm2,ymm3/m256
	_TEST64_VEX( "c4e17d6800 vpunpckhbw ymm0,ymm0,ymmword ptr [rax]", 0xC4, 0xE1, 0x7D, 0x68, 0x00 );
	_TEST32_VEX( "c4e17d68c1 vpunpckhbw ymm0,ymm0,ymm1", 0xC4, 0xE1, 0x7D, 0x68, 0xC1 );
	// VEX.NDS.256.66.0F.WIG 69 /r VPUNPCKHWD ymm1,ymm2,ymm3/m256
	_TEST64_VEX( "c4e17d6900 vpunpckhwd ymm0,ymm0,ymmword ptr [rax]", 0xC4, 0xE1, 0x7D, 0x69, 0x00 );
	_TEST32_VEX( "c4e17d69c1 vpunpckhwd ymm0,ymm0,ymm1", 0xC4, 0xE1, 0x7D, 0x69, 0xC1 );
	// VEX.NDS.256.66.0F.WIG 6A /r VPUNPCKHDQ ymm1,ymm2,ymm3/m256
	_TEST64_VEX( "c4e17d6a00 vpunpckhdq ymm0,ymm0,ymmword ptr [rax]", 0xC4, 0xE1, 0x7D, 0x6a, 0x00 );
	_TEST32_VEX( "c4e17d6ac1 vpunpckhdq ymm0,ymm0,ymm1", 0xC4, 0xE1, 0x7D, 0x6a, 0xC1 );
	// VEX.NDS.256.66.0F.WIG 6D /r VPUNPCKHQDQ ymm1,ymm2,ymm3/m256
	_TEST64_VEX( "c4e17d6d00 vpunpckhqdq ymm0,ymm0,ymmword ptr [rax]", 0xC4, 0xE1, 0x7D, 0x6d, 0x00 );
	_TEST32_VEX( "c4e17d6dc1 vpunpckhqdq ymm0,ymm0,ymm1", 0xC4, 0xE1, 0x7D, 0x6d, 0xC1 );

	// PTEST
	// 66 0F 38 17 /r PTEST xmm1,xmm2/m128
	_TEST64( "660f381700 ptest xmm0,oword ptr [rax]", 0x66, 0x0F, 0x38, 0x17, 0x00 );
	_TEST32( "660f3817c1 ptest xmm0,xmm1", 0x66, 0x0F, 0x38, 0x17, 0xC1 );
	// VEX.128.66.0F38.WIG 17 /r VPTEST xmm1,xmm2/m128
	// VEX.256.66.0F38.WIG 17 /r VPTEST ymm1,ymm2/m256
	_TEST64_VEX( "c4e27917d8 vptest xmm3,xmm0", 0xC4, 0xE2, 0x79, 0x17, 0xD8 );
	_TEST32_VEX( "c4e27917d8 vptest xmm3,xmm0", 0xC4, 0xE2, 0x79, 0x17, 0xD8 );
	_TEST32_VEX( "c4e27d1700 vptest ymm0,ymmword ptr [eax]", 0xC4, 0xE2, 0x7D, 0x17, 0x00 );

	// PSUBUS
	// 0F D8 /r PSUBUSB mm,mm/m64
	_TEST64( "0fd800 psubusb mm0,qword ptr [rax]", 0x0F, 0xD8, 0x00 );
	_TEST32( "0fd8c1 psubusb mm0,mm1", 0x0F, 0xD8, 0xC1 );
	// 0F D9 /r1 PSUBUSW mm,mm/m64
	_TEST64( "0fd900 psubusw mm0,qword ptr [rax]", 0x0F, 0xD9, 0x00 );
	_TEST32( "0fd9c1 psubusw mm0,mm1", 0x0F, 0xD9, 0xC1 );
	// 66 0F D8 /r PSUBUSB xmm1,xmm2/m128
	_TEST64( "660fd800 psubusb xmm0,oword ptr [rax]", 0x66, 0x0F, 0xD8, 0x00 );
	_TEST32( "660fd8c1 psubusb xmm0,xmm1", 0x66, 0x0F, 0xD8, 0xC1 );
	// 66 0F D9 /r PSUBUSW xmm1,xmm2/m128
	_TEST64( "660fd900 psubusw xmm0,oword ptr [rax]", 0x66, 0x0F, 0xD9, 0x00 );
	_TEST32( "660fd9c1 psubusw xmm0,xmm1", 0x66, 0x0F, 0xD9, 0xC1 );
	// VEX.NDS.128.66.0F.WIG D8 /r VPSUBUSB xmm1,xmm2,xmm3/m128
	_TEST64_VEX( "c4e179d800 vpsubusb xmm0,xmm0,oword ptr [rax]", 0xC4, 0xE1, 0x79, 0xD8, 0x00 );
	_TEST32_VEX( "c4e179d8c1 vpsubusb xmm0,xmm0,xmm1", 0xC4, 0xE1, 0x79, 0xD8, 0xC1 );
	// VEX.NDS.128.66.0F.WIG D9 /r VPSUBUSW xmm1,xmm2,xmm3/m128
	_TEST64_VEX( "c4e179d900 vpsubusw xmm0,xmm0,oword ptr [rax]", 0xC4, 0xE1, 0x79, 0xD9, 0x00 );
	_TEST32_VEX( "c4e179d9c1 vpsubusw xmm0,xmm0,xmm1", 0xC4, 0xE1, 0x79, 0xD9, 0xC1 );
	// VEX.NDS.256.66.0F.WIG D8 /r VPSUBUSB ymm1,ymm2,ymm3/m256
	_TEST64_VEX( "c4e17dd800 vpsubusb ymm0,ymm0,ymmword ptr [rax]", 0xC4, 0xE1, 0x7D, 0xD8, 0x00 );
	_TEST32_VEX( "c4e17dd8c1 vpsubusb ymm0,ymm0,ymm1", 0xC4, 0xE1, 0x7D, 0xD8, 0xC1 );
	// VEX.NDS.256.66.0F.WIG D9 /r VPSUBUSW ymm1,ymm2,ymm3/m256
	_TEST64_VEX( "c4e17dd900 vpsubusw ymm0,ymm0,ymmword ptr [rax]", 0xC4, 0xE1, 0x7D, 0xD9, 0x00 );
	_TEST32_VEX( "c4e17dd9c1 vpsubusw ymm0,ymm0,ymm1", 0xC4, 0xE1, 0x7D, 0xD9, 0xC1 );

	// PSUBS
	// 0F E8 /r PSUBSB mm,mm/m64
	_TEST64( "0fe800 psubsb mm0,qword ptr [rax]", 0x0F, 0xE8, 0x00 );
	_TEST32( "0fe8c1 psubsb mm0,mm1", 0x0F, 0xE8, 0xC1 );
	// 0F E9 /r PSUBSW mm,mm/m64
	_TEST64( "0fe900 psubsw mm0,qword ptr [rax]", 0x0F, 0xE9, 0x00 );
	_TEST32( "0fe9c1 psubsw mm0,mm1", 0x0F, 0xE9, 0xC1 );
	// 66 0F E8 /r PSUBSB xmm1,xmm2/m128
	_TEST64( "660fe800 psubsb xmm0,oword ptr [rax]", 0x66, 0x0F, 0xE8, 0x00 );
	_TEST32( "660fe8c1 psubsb xmm0,xmm1", 0x66, 0x0F, 0xE8, 0xC1 );
	// 66 0F E9 /r PSUBSW xmm1,xmm2/m128
	_TEST64( "660fe900 psubsw xmm0,oword ptr [rax]", 0x66, 0x0F, 0xE9, 0x00 );
	_TEST32( "660fe9c1 psubsw xmm0,xmm1", 0x66, 0x0F, 0xE9, 0xC1 );
	// VEX.NDS.128.66.0F.WIG E8 /r VPSUBSB xmm1,xmm2,xmm3/m128
	_TEST64_VEX( "c4e179e800 vpsubsb xmm0,xmm0,oword ptr [rax]", 0xC4, 0xE1, 0x79, 0xE8, 0x00 );
	_TEST32_VEX( "c4e179e8c1 vpsubsb xmm0,xmm0,xmm1", 0xC4, 0xE1, 0x79, 0xE8, 0xC1 );
	// VEX.NDS.128.66.0F.WIG E9 /r VPSUBSW xmm1,xmm2,xmm3/m128
	_TEST64_VEX( "c4e179e900 vpsubsw xmm0,xmm0,oword ptr [rax]", 0xC4, 0xE1, 0x79, 0xE9, 0x00 );
	_TEST32_VEX( "c4e179e9c1 vpsubsw xmm0,xmm0,xmm1", 0xC4, 0xE1, 0x79, 0xE9, 0xC1 );
	// VEX.NDS.256.66.0F.WIG E8 /r VPSUBSB ymm1,ymm2,ymm3/m256
	_TEST64_VEX( "c4e17de800 vpsubsb ymm0,ymm0,ymmword ptr [rax]", 0xC4, 0xE1, 0x7D, 0xE8, 0x00 );
	_TEST32_VEX( "c4e17de8c1 vpsubsb ymm0,ymm0,ymm1", 0xC4, 0xE1, 0x7D, 0xE8, 0xC1 );
	// VEX.NDS.256.66.0F.WIG E9 /r VPSUBSW ymm1,ymm2,ymm3/m256
	_TEST64_VEX( "c4e17de900 vpsubsw ymm0,ymm0,ymmword ptr [rax]", 0xC4, 0xE1, 0x7D, 0xE9, 0x00 );
	_TEST32_VEX( "c4e17de9c1 vpsubsw ymm0,ymm0,ymm1", 0xC4, 0xE1, 0x7D, 0xE9, 0xC1 );

	// PSUBQ
	// 0F FB /r PSUBQ mm1,mm2/m64
	_TEST64( "0ffb00 psubq mm0,qword ptr [rax]", 0x0F, 0xFB, 0x00 );
	_TEST32( "0ffbc1 psubq mm0,mm1", 0x0F, 0xFB, 0xC1 );
	// 66 0F FB /r PSUBQ xmm1,xmm2/m128
	_TEST64( "660ffb00 psubq xmm0,oword ptr [rax]", 0x66, 0x0F, 0xFB, 0x00 );
	_TEST32( "660ffbc1 psubq xmm0,xmm1", 0x66, 0x0F, 0xFB, 0xC1 );
	// VEX.NDS.128.66.0F.WIG FB/r VPSUBQ xmm1,xmm2,xmm3/m128
	_TEST64_VEX( "c4e179fb00 vpsubq xmm0,xmm0,oword ptr [rax]", 0xC4, 0xE1, 0x79, 0xFB, 0x00 );
	_TEST32_VEX( "c4e179fbc1 vpsubq xmm0,xmm0,xmm1", 0xC4, 0xE1, 0x79, 0xFB, 0xC1 );

	// PSUB
	// 0F F8 /r PSUBB mm,mm/m64
	_TEST64( "0ff800 psubb mm0,qword ptr [rax]", 0x0F, 0xF8, 0x00 );
	_TEST32( "0ff8c1 psubb mm0,mm1", 0x0F, 0xF8, 0xC1 );
	// 0F F9 /r PSUBW mm,mm/m64
	_TEST64( "0ff900 psubw mm0,qword ptr [rax]", 0x0F, 0xF9, 0x00 );
	_TEST32( "0ff9c1 psubw mm0,mm1", 0x0F, 0xF9, 0xC1 );
	// 0F FA /r PSUBD mm,mm/m64
	_TEST64( "0ffa00 psubd mm0,qword ptr [rax]", 0x0F, 0xFA, 0x00 );
	_TEST32( "0ffac1 psubd mm0,mm1", 0x0F, 0xFA, 0xC1 );
	// 66 0F F8 /r PSUBB xmm1,xmm2/m128
	_TEST64( "660ff800 psubb xmm0,oword ptr [rax]", 0x66, 0x0F, 0xF8, 0x00 );
	_TEST32( "660ff8c1 psubb xmm0,xmm1", 0x66, 0x0F, 0xF8, 0xC1 );
	// 66 0F F9 /r PSUBW xmm1,xmm2/m128
	_TEST64( "660ff900 psubw xmm0,oword ptr [rax]", 0x66, 0x0F, 0xF9, 0x00 );
	_TEST32( "660ff9c1 psubw xmm0,xmm1", 0x66, 0x0F, 0xF9, 0xC1 );
	// 66 0F FA /r PSUBD xmm1,xmm2/m128
	_TEST64( "660ffa00 psubd xmm0,oword ptr [rax]", 0x66, 0x0F, 0xFA, 0x00 );
	_TEST32( "660ffac1 psubd xmm0,xmm1", 0x66, 0x0F, 0xFA, 0xC1 );
	// VEX.NDS.128.66.0F.WIG F8 /r VPSUBB xmm1,xmm2,xmm3/m128
	_TEST64_VEX( "c4e179f800 vpsubb xmm0,xmm0,oword ptr [rax]", 0xC4, 0xE1, 0x79, 0xF8, 0x00 );
	_TEST32_VEX( "c4e179f8c1 vpsubb xmm0,xmm0,xmm1", 0xC4, 0xE1, 0x79, 0xF8, 0xC1 );
	// VEX.NDS.128.66.0F.WIG F9 /r VPSUBW xmm1,xmm2,xmm3/m128
	_TEST64_VEX( "c4e179f900 vpsubw xmm0,xmm0,oword ptr [rax]", 0xC4, 0xE1, 0x79, 0xF9, 0x00 );
	_TEST32_VEX( "c4e179f9c1 vpsubw xmm0,xmm0,xmm1", 0xC4, 0xE1, 0x79, 0xF9, 0xC1 );
	// VEX.NDS.128.66.0F.WIG FA /r VPSUBD xmm1,xmm2,xmm3/m128
	_TEST64_VEX( "c4e179fa00 vpsubd xmm0,xmm0,oword ptr [rax]", 0xC4, 0xE1, 0x79, 0xFA, 0x00 );
	_TEST32_VEX( "c4e179fac1 vpsubd xmm0,xmm0,xmm1", 0xC4, 0xE1, 0x79, 0xFA, 0xC1 );
	// VEX.NDS.256.66.0F.WIG F8 /r VPSUBB ymm1,ymm2,ymm3/m256
	_TEST64_VEX( "c4e17df800 vpsubb ymm0,ymm0,ymmword ptr [rax]", 0xC4, 0xE1, 0x7D, 0xF8, 0x00 );
	_TEST32_VEX( "c4e17df8c1 vpsubb ymm0,ymm0,ymm1", 0xC4, 0xE1, 0x7D, 0xF8, 0xC1 );
	// VEX.NDS.256.66.0F.WIG F9 /r VPSUBW ymm1,ymm2,ymm3/m256
	_TEST64_VEX( "c4e17df900 vpsubw ymm0,ymm0,ymmword ptr [rax]", 0xC4, 0xE1, 0x7D, 0xF9, 0x00 );
	_TEST32_VEX( "c4e17df9c1 vpsubw ymm0,ymm0,ymm1", 0xC4, 0xE1, 0x7D, 0xF9, 0xC1 );
	// VEX.NDS.256.66.0F.WIG FA /r VPSUBD ymm1,ymm2,ymm3/m256
	_TEST64_VEX( "c4e17dfa00 vpsubd ymm0,ymm0,ymmword ptr [rax]", 0xC4, 0xE1, 0x7D, 0xFA, 0x00 );
	_TEST32_VEX( "c4e17dfac1 vpsubd ymm0,ymm0,ymm1", 0xC4, 0xE1, 0x7D, 0xFA, 0xC1 );
	// VEX.NDS.256.66.0F.WIG FB /r VPSUBQ ymm1,ymm2,ymm3/m256
	_TEST64_VEX( "c4e17dfb00 vpsubq ymm0,ymm0,ymmword ptr [rax]", 0xC4, 0xE1, 0x7D, 0xFB, 0x00 );
	_TEST32_VEX( "c4e17dfbc1 vpsubq ymm0,ymm0,ymm1", 0xC4, 0xE1, 0x7D, 0xFB, 0xC1 );

	// PSRL
	// 0F D1 /r PSRLW mm,mm/m64
	_TEST64( "0fd100 psrlw mm0,qword ptr [rax]", 0x0F, 0xD1, 0x00 );
	_TEST32( "0fd1c1 psrlw mm0,mm1", 0x0F, 0xD1, 0xC1 );
	// 0F D2 /r PSRLD mm,mm/m64
	_TEST64( "0fd200 psrld mm0,qword ptr [rax]", 0x0F, 0xD2, 0x00 );
	_TEST32( "0fd2c1 psrld mm0,mm1", 0x0F, 0xD2, 0xC1 );
	// 0F D3 /r PSRLQ mm,mm/m64
	_TEST64( "0fd300 psrlq mm0,qword ptr [rax]", 0x0F, 0xD3, 0x00 );
	_TEST32( "0fd3c1 psrlq mm0,mm1", 0x0F, 0xD3, 0xC1 );
	// 66 0F D1 /r PSRLW xmm1,xmm2/m128
	_TEST64( "660fd100 psrlw xmm0,oword ptr [rax]", 0x66, 0x0F, 0xD1, 0x00 );
	_TEST32( "660fd1c1 psrlw xmm0,xmm1", 0x66, 0x0F, 0xD1, 0xC1 );
	// 66 0F D2 /r PSRLD xmm1,xmm2/m128
	_TEST64( "660fd200 psrld xmm0,oword ptr [rax]", 0x66, 0x0F, 0xD2, 0x00 );
	_TEST32( "660fd2c1 psrld xmm0,xmm1", 0x66, 0x0F, 0xD2, 0xC1 );
	// 66 0F D3 /r PSRLQ xmm1,xmm2/m128
	_TEST64( "660fd300 psrlq xmm0,oword ptr [rax]", 0x66, 0x0F, 0xD3, 0x00 );
	_TEST32( "660fd3c1 psrlq xmm0,xmm1", 0x66, 0x0F, 0xD3, 0xC1 );
	// 0F 71 /2 ib PSRLW mm,imm8
	_TEST32( "0f71d1ff psrlw mm1,0ffh", 0x0F, 0x71, 0xD1, 0xFF );
	// 0F 72 /2 ib PSRLD mm,imm8
	_TEST32( "0f72d2ff psrld mm2,0ffh", 0x0F, 0x72, 0xD2, 0xFF );
	// 0F 73 /2 ib PSRLQ mm,imm8
	_TEST32( "0f73d3ff psrlq mm3,0ffh", 0x0F, 0x73, 0xD3, 0xFF );
	// 66 0F 71 /2 ib PSRLW xmm1,imm8
	_TEST32( "660f71d1ff psrlw xmm1,0ffh", 0x66, 0x0F, 0x71, 0xD1, 0xFF );
	// 66 0F 72 /2 ib PSRLD xmm1,imm8
	_TEST32( "660f72d1ff psrld xmm1,0ffh", 0x66, 0x0F, 0x72, 0xD1, 0xFF );
	// 66 0F 73 /2 ib PSRLQ xmm1,imm8
	_TEST32( "660f73d1ff psrlq xmm1,0ffh", 0x66, 0x0F, 0x73, 0xD1, 0xFF );
	// VEX.NDS.128.66.0F.WIG D1 /r VPSRLW xmm1,xmm2,xmm3/m128
	_TEST64_VEX( "c4e179d100 vpsrlw xmm0,xmm0,oword ptr [rax]", 0xC4, 0xE1, 0x79, 0xD1, 0x00 );
	_TEST32_VEX( "c4e179d1c1 vpsrlw xmm0,xmm0,xmm1", 0xC4, 0xE1, 0x79, 0xD1, 0xC1 );
	// VEX.NDS.256.66.0F.WIG D1 /r VPSRLW ymm1,ymm2,xmm3/m128
	_TEST64_VEX( "c4e17dd100 vpsrlw ymm0,ymm0,oword ptr [rax]", 0xC4, 0xE1, 0x7D, 0xD1, 0x00 );
	_TEST32_VEX( "c4e17dd1c1 vpsrlw ymm0,ymm0,xmm1", 0xC4, 0xE1, 0x7D, 0xD1, 0xC1 );
	// VEX.NDS.128.66.0F.WIG D2 /r VPSRLD xmm1,xmm2,xmm3/m128
	_TEST64_VEX( "c4e179d200 vpsrld xmm0,xmm0,oword ptr [rax]", 0xC4, 0xE1, 0x79, 0xD2, 0x00 );
	_TEST32_VEX( "c4e179d2c1 vpsrld xmm0,xmm0,xmm1", 0xC4, 0xE1, 0x79, 0xD2, 0xC1 );
	// VEX.NDS.256.66.0F.WIG D2 /r VPSRLD ymm1,ymm2,xmm3/m128
	_TEST64_VEX( "c4e17dd200 vpsrld ymm0,ymm0,oword ptr [rax]", 0xC4, 0xE1, 0x7D, 0xD2, 0x00 );
	_TEST32_VEX( "c4e17dd2c1 vpsrld ymm0,ymm0,xmm1", 0xC4, 0xE1, 0x7D, 0xD2, 0xC1 );
	// VEX.NDS.128.66.0F.WIG D3 /r VPSRLQ xmm1,xmm2,xmm3/m128
	_TEST64_VEX( "c4e179d300 vpsrlq xmm0,xmm0,oword ptr [rax]", 0xC4, 0xE1, 0x79, 0xD3, 0x00 );
	_TEST32_VEX( "c4e179d3c1 vpsrlq xmm0,xmm0,xmm1", 0xC4, 0xE1, 0x79, 0xD3, 0xC1 );
	// VEX.NDD.128.66.0F.WIG 71 /2 ib VPSRLW xmm1,xmm2,imm8
	_TEST32_VEX( "c4e16171d0ff vpsrlw xmm3,xmm0,0ffh", 0xC4, 0xE1, 0x61, 0x71, 0xD0, 0xFF );
	// VEX.NDD.128.66.0F.WIG 72 /2 ib VPSRLD xmm1,xmm2,imm8
	_TEST32_VEX( "c4e16172d0ff vpsrld xmm3,xmm0,0ffh", 0xC4, 0xE1, 0x61, 0x72, 0xD0, 0xFF );
	// VEX.NDD.128.66.0F.WIG 73 /2 ib VPSRLQ xmm1,xmm2,imm8
	_TEST32_VEX( "c4e16173d0ff vpsrlq xmm3,xmm0,0ffh", 0xC4, 0xE1, 0x61, 0x73, 0xD0, 0xFF );
	// VEX.NDD.256.66.0F.WIG 71 /2 ib VPSRLW ymm1,ymm2,imm8
	_TEST32_VEX( "c4e16571d0ff vpsrlw ymm3,ymm0,0ffh", 0xC4, 0xE1, 0x65, 0x71, 0xD0, 0xFF );

	// PSRLDQ
	// 66 0F 73 /7 ib PSLLDQ xmm1,imm8
	_TEST32( "660f73f9ff pslldq xmm1,0ffh", 0x66, 0x0F, 0x73, 0xF9, 0xFF );
	// VEX.NDD.128.66.0F.WIG 73 /7 ib VPSLLDQ xmm1,xmm2,imm8
	_TEST32_VEX( "c4e16173f8ff vpslldq xmm3,xmm0,0ffh", 0xC4, 0xE1, 0x61, 0x73, 0xF8, 0xFF );
	// VEX.NDD.256.66.0F.WIG 73 /7 ib VPSLLDQ ymm1,ymm2,imm8
	_TEST32_VEX( "c4e16573f8ff vpslldq ymm3,ymm0,0ffh", 0xC4, 0xE1, 0x65, 0x73, 0xF8, 0xFF );

	// PSRLDQ
	// 66 0F 73 /3 ib PSRLDQ xmm1,imm8
	_TEST32( "660f73d9ff psrldq xmm1,0ffh", 0x66, 0x0F, 0x73, 0xD9, 0xFF );
	// VEX.NDD.128.66.0F.WIG 73 /3 ib VPSRLDQ xmm1,xmm2,imm8
	_TEST32_VEX( "c4e16173d8ff vpsrldq xmm3,xmm0,0ffh", 0xC4, 0xE1, 0x61, 0x73, 0xD8, 0xFF );

	// PSIGN
	// 0F 38 08 /r PSIGNB mm1,mm2/m64
	_TEST64( "0f380800 psignb mm0,qword ptr [rax]", 0x0F, 0x38, 0x08, 0x00 );
	_TEST32( "0f3808c1 psignb mm0,mm1", 0x0F, 0x38, 0x08, 0xC1 );
	// 0F 38 09 /r PSIGNW mm1,mm2/m64
	_TEST64( "0f380900 psignw mm0,qword ptr [rax]", 0x0F, 0x38, 0x09, 0x00 );
	_TEST32( "0f3809c1 psignw mm0,mm1", 0x0F, 0x38, 0x09, 0xC1 );
	// 0F 38 0A /r PSIGND mm1,mm2/m64
	_TEST64( "0f380a00 psignd mm0,qword ptr [rax]", 0x0F, 0x38, 0x0A, 0x00 );
	_TEST32( "0f380ac1 psignd mm0,mm1", 0x0F, 0x38, 0x0A, 0xC1 );
	// 66 0F 38 08 /r PSIGNB xmm1,xmm2/m128
	_TEST64( "660f380800 psignb xmm0,oword ptr [rax]", 0x66, 0x0F, 0x38, 0x08, 0x00 );
	_TEST32( "660f3808c1 psignb xmm0,xmm1", 0x66, 0x0F, 0x38, 0x08, 0xC1 );
	// 66 0F 38 09 /r PSIGNW xmm1,xmm2/m128
	_TEST64( "660f380900 psignw xmm0,oword ptr [rax]", 0x66, 0x0F, 0x38, 0x09, 0x00 );
	_TEST32( "660f3809c1 psignw xmm0,xmm1", 0x66, 0x0F, 0x38, 0x09, 0xC1 );
	// 66 0F 38 0A /r PSIGND xmm1,xmm2/m128
	_TEST64( "660f380a00 psignd xmm0,oword ptr [rax]", 0x66, 0x0F, 0x38, 0x0A, 0x00 );
	_TEST32( "660f380ac1 psignd xmm0,xmm1", 0x66, 0x0F, 0x38, 0x0A, 0xC1 );
	// VEX.NDS.128.66.0F38.WIG 08 /r VPSIGNB xmm1,xmm2,xmm3/m128
	_TEST64_VEX( "c4e2790800 vpsignb xmm0,xmm0,oword ptr [rax]", 0xC4, 0xE2, 0x79, 0x08, 0x00 );
	_TEST32_VEX( "c4e27908c1 vpsignb xmm0,xmm0,xmm1", 0xC4, 0xE2, 0x79, 0x08, 0xC1 );
	// VEX.NDS.128.66.0F38.WIG 09 /r VPSIGNW xmm1,xmm2,xmm3/m128
	_TEST64_VEX( "c4e2790900 vpsignw xmm0,xmm0,oword ptr [rax]", 0xC4, 0xE2, 0x79, 0x09, 0x00 );
	_TEST32_VEX( "c4e27909c1 vpsignw xmm0,xmm0,xmm1", 0xC4, 0xE2, 0x79, 0x09, 0xC1 );
	// VEX.NDS.128.66.0F38.WIG 0A /r VPSIGND xmm1,xmm2,xmm3/m128
	_TEST64_VEX( "c4e2790a00 vpsignd xmm0,xmm0,oword ptr [rax]", 0xC4, 0xE2, 0x79, 0x0A, 0x00 );
	_TEST32_VEX( "c4e2790ac1 vpsignd xmm0,xmm0,xmm1", 0xC4, 0xE2, 0x79, 0x0A, 0xC1 );
	// VEX.NDS.256.66.0F38.WIG 08 /r VPSIGNB ymm1,ymm2,ymm3/m256
	_TEST64_VEX( "c4e27d0800 vpsignb ymm0,ymm0,ymmword ptr [rax]", 0xC4, 0xE2, 0x7D, 0x08, 0x00 );
	_TEST32_VEX( "c4e27d08c1 vpsignb ymm0,ymm0,ymm1", 0xC4, 0xE2, 0x7D, 0x08, 0xC1 );
	// VEX.NDS.256.66.0F38.WIG 09 /r VPSIGNW ymm1,ymm2,ymm3/m256
	_TEST64_VEX( "c4e27d0900 vpsignw ymm0,ymm0,ymmword ptr [rax]", 0xC4, 0xE2, 0x7D, 0x09, 0x00 );
	_TEST32_VEX( "c4e27d09c1 vpsignw ymm0,ymm0,ymm1", 0xC4, 0xE2, 0x7D, 0x09, 0xC1 );
	// VEX.NDS.256.66.0F38.WIG 0A /r VPSIGND ymm1,ymm2,ymm3/m256
	_TEST64_VEX( "c4e27d0a00 vpsignd ymm0,ymm0,ymmword ptr [rax]", 0xC4, 0xE2, 0x7D, 0x0A, 0x00 );
	_TEST32_VEX( "c4e27d0ac1 vpsignd ymm0,ymm0,ymm1", 0xC4, 0xE2, 0x7D, 0x0A, 0xC1 );

	// PSRA
	// 0F E1 /r1 PSRAW mm,mm/m64
	// 0F E2 /r1 PSRAD mm,mm/m64
	_TEST64( "0fe100 psraw mm0,qword ptr [rax]", 0x0F, 0xE1, 0x00 );
	_TEST32( "0fe1c1 psraw mm0,mm1", 0x0F, 0xE1, 0xC1 );
	_TEST64( "0fe200 psrad mm0,qword ptr [rax]", 0x0F, 0xE2, 0x00 );
	_TEST32( "0fe2c1 psrad mm0,mm1", 0x0F, 0xE2, 0xC1 );
	// 66 0F E1 /r PSRAW xmm1,xmm2/m128
	// 66 0F E2 /r PSRAD xmm1,xmm2/m128
	_TEST64( "660fe100 psraw xmm0,oword ptr [rax]", 0x66, 0x0F, 0xE1, 0x00 );
	_TEST32( "660fe1c1 psraw xmm0,xmm1", 0x66, 0x0F, 0xE1, 0xC1 );
	_TEST64( "660fe200 psrad xmm0,oword ptr [rax]", 0x66, 0x0F, 0xE2, 0x00 );
	_TEST32( "660fe2c1 psrad xmm0,xmm1", 0x66, 0x0F, 0xE2, 0xC1 );
	// VEX.NDS.128.66.0F.WIG E1 /r VPSRAW xmm1,xmm2,xmm3/m128
	// VEX.NDS.128.66.0F.WIG E2 /r VPSRAD xmm1,xmm2,xmm3/m128
	_TEST64_VEX( "c4e179e100 vpsraw xmm0,xmm0,oword ptr [rax]", 0xC4, 0xE1, 0x79, 0xE1, 0x00 );
	_TEST32_VEX( "c4e179e1c1 vpsraw xmm0,xmm0,xmm1", 0xC4, 0xE1, 0x79, 0xE1, 0xC1 );
	_TEST64_VEX( "c4e179e200 vpsrad xmm0,xmm0,oword ptr [rax]", 0xC4, 0xE1, 0x79, 0xE2, 0x00 );
	_TEST32_VEX( "c4e179e2c1 vpsrad xmm0,xmm0,xmm1", 0xC4, 0xE1, 0x79, 0xE2, 0xC1 );
	// VEX.NDS.256.66.0F.WIG E1 /r VPSRAW ymm1, ymm2, xmm3/m128
	// VEX.NDS.256.66.0F.WIG E2 /r VPSRAD ymm1, ymm2, xmm3/m128
	_TEST64_VEX( "c4e17de100 vpsraw ymm0,ymm0,oword ptr [rax]", 0xC4, 0xE1, 0x7D, 0xE1, 0x00 );
	_TEST32_VEX( "c4e17de1c1 vpsraw ymm0,ymm0,xmm1", 0xC4, 0xE1, 0x7D, 0xE1, 0xC1 );
	_TEST64_VEX( "c4e17de200 vpsrad ymm0,ymm0,oword ptr [rax]", 0xC4, 0xE1, 0x7D, 0xE2, 0x00 );
	_TEST32_VEX( "c4e17de2c1 vpsrad ymm0,ymm0,xmm1", 0xC4, 0xE1, 0x7D, 0xE2, 0xC1 );
	// 0F 71 /4 ib1 PSRAW mm,imm8
	// 0F 72 /4 ib1 PSRAD mm,imm8
	_TEST32( "0f71e1ff psraw mm1,0ffh", 0x0F, 0x71, 0xE1, 0xFF );
	_TEST32( "0f72e2ff psrad mm2,0ffh", 0x0F, 0x72, 0xE2, 0xFF );
	// 66 0F 71 /4 ib PSRAW xmm1,imm8
	// 66 0F 72 /4 ib PSRAD xmm1,imm8
	_TEST32( "660f71e1ff psraw xmm1,0ffh", 0x66, 0x0F, 0x71, 0xE1, 0xFF );
	_TEST32( "660f72e1ff psrad xmm1,0ffh", 0x66, 0x0F, 0x72, 0xE1, 0xFF );
	// VEX.NDD.128.66.0F.WIG 71 /4 ib VPSRAW xmm1,xmm2,imm8
	// VEX.NDD.128.66.0F.WIG 72 /4 ib VPSRAD xmm1,xmm2,imm8
	_TEST32_VEX( "c4e16171e0ff vpsraw xmm3,xmm0,0ffh", 0xC4, 0xE1, 0x61, 0x71, 0xE0, 0xFF );
	_TEST32_VEX( "c4e16172e0ff vpsrad xmm3,xmm0,0ffh", 0xC4, 0xE1, 0x61, 0x72, 0xE0, 0xFF );
	// VEX.NDD.256.66.0F.WIG 71 /4 ib VPSRAW ymm1, ymm2, imm8
	// VEX.NDD.256.66.0F.WIG 72 /4 ib VPSRAD ymm1, ymm2, imm8
	_TEST32_VEX( "c4e16571e0ff vpsraw ymm3,ymm0,0ffh", 0xC4, 0xE1, 0x65, 0x71, 0xE0, 0xFF );
	_TEST32_VEX( "c4e16572e0ff vpsrad ymm3,ymm0,0ffh", 0xC4, 0xE1, 0x65, 0x72, 0xE0, 0xFF );

	// PSLL
	// 0F F1 /r1 PSLLW mm,mm/m64
	// 0F F2 /r1 PSLLD mm,mm/m64
	// 0F F3 /r1 PSLLQ mm,mm/m64
	_TEST64( "0ff100 psllw mm0,qword ptr [rax]", 0x0F, 0xF1, 0x00 );
	_TEST32( "0ff1c1 psllw mm0,mm1", 0x0F, 0xF1, 0xC1 );
	_TEST64( "0ff200 pslld mm0,qword ptr [rax]", 0x0F, 0xF2, 0x00 );
	_TEST32( "0ff2c1 pslld mm0,mm1", 0x0F, 0xF2, 0xC1 );
	_TEST64( "0ff300 psllq mm0,qword ptr [rax]", 0x0F, 0xF3, 0x00 );
	_TEST32( "0ff3c1 psllq mm0,mm1", 0x0F, 0xF3, 0xC1 );
	// 66 0F F1 /r PSLLW xmm1,xmm2/m128
	// 66 0F F2 /r PSLLD xmm1,xmm2/m128
	// 66 0F F3 /r PSLLQ xmm1,xmm2/m128
	_TEST64( "660ff100 psllw xmm0,oword ptr [rax]", 0x66, 0x0F, 0xF1, 0x00 );
	_TEST32( "660ff1c1 psllw xmm0,xmm1", 0x66, 0x0F, 0xF1, 0xC1 );
	_TEST64( "660ff200 pslld xmm0,oword ptr [rax]", 0x66, 0x0F, 0xF2, 0x00 );
	_TEST32( "660ff2c1 pslld xmm0,xmm1", 0x66, 0x0F, 0xF2, 0xC1 );
	_TEST64( "660ff300 psllq xmm0,oword ptr [rax]", 0x66, 0x0F, 0xF3, 0x00 );
	_TEST32( "660ff3c1 psllq xmm0,xmm1", 0x66, 0x0F, 0xF3, 0xC1 );
	// 0F 71 /6 ib PSLLW mm,imm8
	// 0F 72 /6 ib1 PSLLD mm,imm8
	// 0F 73 /6 ib1 PSLLQ mm,imm8
	_TEST32( "0f71f1ff psllw mm1,0ffh", 0x0F, 0x71, 0xF1, 0xFF );
	_TEST32( "0f72f2ff pslld mm2,0ffh", 0x0F, 0x72, 0xF2, 0xFF );
	_TEST32( "0f73f3ff psllq mm3,0ffh", 0x0F, 0x73, 0xf3, 0xFF );
	// 66 0F 71 /6 ib PSLLW xmm1,imm8
	// 66 0F 72 /6 ib PSLLD xmm1,imm8
	// 66 0F 73 /6 ib PSLLQ xmm1,imm8
	_TEST32( "660f71f1ff psllw xmm1,0ffh", 0x66, 0x0F, 0x71, 0xF1, 0xFF );
	_TEST32( "660f72f1ff pslld xmm1,0ffh", 0x66, 0x0F, 0x72, 0xF1, 0xFF );
	_TEST32( "660f73f1ff psllq xmm1,0ffh", 0x66, 0x0F, 0x73, 0xF1, 0xFF );
	// VEX.NDS.128.66.0F.WIG F1 /r VPSLLW xmm1,xmm2,xmm3/m128
	// VEX.NDS.128.66.0F.WIG F2 /r VPSLLD xmm1,xmm2,xmm3/m128
	// VEX.NDS.128.66.0F.WIG F3 /r VPSLLQ xmm1,xmm2,xmm3/m128
	_TEST64_VEX( "c4e179f100 vpsllw xmm0,xmm0,oword ptr [rax]", 0xC4, 0xE1, 0x79, 0xF1, 0x00 );
	_TEST32_VEX( "c4e179f1c1 vpsllw xmm0,xmm0,xmm1", 0xC4, 0xE1, 0x79, 0xF1, 0xC1 );
	_TEST64_VEX( "c4e179f200 vpslld xmm0,xmm0,oword ptr [rax]", 0xC4, 0xE1, 0x79, 0xF2, 0x00 );
	_TEST32_VEX( "c4e179f2c1 vpslld xmm0,xmm0,xmm1", 0xC4, 0xE1, 0x79, 0xF2, 0xC1 );
	_TEST64_VEX( "c4e179f300 vpsllq xmm0,xmm0,oword ptr [rax]", 0xC4, 0xE1, 0x79, 0xF3, 0x00 );
	_TEST32_VEX( "c4e179f3c1 vpsllq xmm0,xmm0,xmm1", 0xC4, 0xE1, 0x79, 0xF3, 0xC1 );
	// VEX.NDS.256.66.0F.WIG F2 /r VPSLLD ymm1,ymm2,xmm3/m128
	_TEST64_VEX( "c4e17df200 vpslld ymm0,ymm0,ymmword ptr [rax]", 0xC4, 0xE1, 0x7D, 0xF2, 0x00 );
	_TEST32_VEX( "c4e17df2c1 vpslld ymm0,ymm0,ymm1", 0xC4, 0xE1, 0x7D, 0xF2, 0xC1 );
	// VEX.NDD.128.66.0F.WIG 71 /6 ib VPSLLW xmm1,xmm2,imm8
	// VEX.NDD.128.66.0F.WIG 72 /6 ib VPSLLD xmm1,xmm2,imm8
	// VEX.NDD.128.66.0F.WIG 73 /6 ib VPSLLQ xmm1,xmm2,imm8
	_TEST32_VEX( "c4e16171f0ff vpsllw xmm3,xmm0,0ffh", 0xC4, 0xE1, 0x61, 0x71, 0xF0, 0xFF );
	_TEST32_VEX( "c4e16172f0ff vpslld xmm3,xmm0,0ffh", 0xC4, 0xE1, 0x61, 0x72, 0xF0, 0xFF );
	_TEST32_VEX( "c4e16173f0ff vpsllq xmm3,xmm0,0ffh", 0xC4, 0xE1, 0x61, 0x73, 0xF0, 0xFF );
	// VEX.NDD.256.66.0F.WIG 71 /6 ib VPSLLW ymm1,ymm2,imm8
	_TEST32_VEX( "c4e16571f0ff vpsllw ymm3,ymm0,0ffh", 0xC4, 0xE1, 0x65, 0x71, 0xF0, 0xFF );

	// PSHUFW
	// 0F 70 /r ib PSHUFW mm1,mm2/m64,imm8
	_TEST64_VEX( "0f7000ff pshufw mm0,qword ptr [rax],0ffh", 0x0F, 0x70, 0x00, 0xFF );
	_TEST32_VEX( "0f70c1ff pshufw mm0,mm1,0ffh", 0x0F, 0x70, 0xC1, 0xFF );

	// PSHUFLW
	// F2 0F 70 /r ib PSHUFLW xmm1,xmm2/m128,imm8
	_TEST64_VEX( "f20f7000ff pshuflw xmm0,oword ptr [rax],0ffh", 0xF2, 0x0F, 0x70, 0x00, 0xFF );
	_TEST32_VEX( "f20f70c1ff pshuflw xmm0,xmm1,0ffh", 0xF2, 0x0F, 0x70, 0xC1, 0xFF );
	// VEX.128.F2.0F.WIG 70 /r ib VPSHUFLW xmm1,xmm2/m128,imm8
	_TEST64_VEX( "c4e17b7000ff vpshuflw xmm0,oword ptr [rax],0ffh", 0xC4, 0xE1, 0x7B, 0x70, 0x00, 0xFF );
	_TEST32_VEX( "c4e17b70c1ff vpshuflw xmm0,xmm1,0ffh", 0xC4, 0xE1, 0x7B, 0x70, 0xC1, 0xFF );
	// VEX.256.F2.0F.WIG 70 /r ib VPSHUFLW ymm1,ymm2/m256,imm8
	_TEST64_VEX( "c4e17f7000ff vpshuflw ymm0,ymmword ptr [rax],0ffh", 0xC4, 0xE1, 0x7F, 0x70, 0x00, 0xFF );
	_TEST32_VEX( "c4e17f70c1ff vpshuflw ymm0,ymm1,0ffh", 0xC4, 0xE1, 0x7F, 0x70, 0xC1, 0xFF );

	// PSHUFHW
	// F3 0F 70 /r ib PSHUFHW xmm1,xmm2/m128,imm8
	_TEST64_VEX( "f30f7000ff pshufhw xmm0,oword ptr [rax],0ffh", 0xF3, 0x0F, 0x70, 0x00, 0xFF );
	_TEST32_VEX( "f30f70c1ff pshufhw xmm0,xmm1,0ffh", 0xF3, 0x0F, 0x70, 0xC1, 0xFF );
	// VEX.128.F3.0F.WIG 70 /r ib VPSHUFHW xmm1,xmm2/m128,imm8
	_TEST64_VEX( "c4e17a7000ff vpshufhw xmm0,oword ptr [rax],0ffh", 0xC4, 0xE1, 0x7A, 0x70, 0x00, 0xFF );
	_TEST32_VEX( "c4e17a70c1ff vpshufhw xmm0,xmm1,0ffh", 0xC4, 0xE1, 0x7A, 0x70, 0xC1, 0xFF );
	// VEX.256.F3.0F.WIG 70 /r ib VPSHUFHW ymm1,ymm2/m256,imm8
	_TEST64_VEX( "c4e17e7000ff vpshufhw ymm0,ymmword ptr [rax],0ffh", 0xC4, 0xE1, 0x7E, 0x70, 0x00, 0xFF );
	_TEST32_VEX( "c4e17e70c1ff vpshufhw ymm0,ymm1,0ffh", 0xC4, 0xE1, 0x7E, 0x70, 0xC1, 0xFF );

	// PSHUFD
	// 66 0F 70 /r ib PSHUFD xmm1,xmm2/m128,imm8
	_TEST64_VEX( "660f7000ff pshufd xmm0,oword ptr [rax],0ffh", 0x66, 0x0F, 0x70, 0x00, 0xFF );
	_TEST32_VEX( "660f70c1ff pshufd xmm0,xmm1,0ffh", 0x66, 0x0F, 0x70, 0xC1, 0xFF );
	// VEX.128.66.0F.WIG 70 /r ib VPSHUFD xmm1,xmm2/m128,imm8
	_TEST64_VEX( "c4e1797000ff vpshufd xmm0,oword ptr [rax],0ffh", 0xC4, 0xE1, 0x79, 0x70, 0x00, 0xFF );
	_TEST32_VEX( "c4e17970c1ff vpshufd xmm0,xmm1,0ffh", 0xC4, 0xE1, 0x79, 0x70, 0xC1, 0xFF );
	// VEX.256.66.0F.WIG 70 /r ib VPSHUFD ymm1,ymm2/m256,imm8
	_TEST64_VEX( "c4e17d7000ff vpshufd ymm0,ymmword ptr [rax],0ffh", 0xC4, 0xE1, 0x7D, 0x70, 0x00, 0xFF );
	_TEST32_VEX( "c4e17d70c1ff vpshufd ymm0,ymm1,0ffh", 0xC4, 0xE1, 0x7D, 0x70, 0xC1, 0xFF );

	// PSHUFB
	// 0F 38 00 /r PSHUFB mm1, mm2/m64
	_TEST64( "0f380000 pshufb mm0,qword ptr [rax]", 0x0F, 0x38, 0x00, 0x00 );
	_TEST32( "0f3800c1 pshufb mm0,mm1", 0x0F, 0x38, 0x00, 0xC1 );
	// 66 0F 38 00 /r PSHUFB xmm1, xmm2/m128
	_TEST64( "660f380000 pshufb xmm0,oword ptr [rax]", 0x66, 0x0F, 0x38, 0x00, 0x00 );
	_TEST32( "660f3800c1 pshufb xmm0,xmm1", 0x66, 0x0F, 0x38, 0x00, 0xC1 );
	// VEX.NDS.128.66.0F38.WIG 00 /r VPSHUFB xmm1, xmm2, xmm3/m128
	_TEST64_VEX( "c4e2790000 vpshufb xmm0,xmm0,oword ptr [rax]", 0xC4, 0xE2, 0x79, 0x00, 0x00 );
	_TEST32_VEX( "c4e27900c1 vpshufb xmm0,xmm0,xmm1", 0xC4, 0xE2, 0x79, 0x00, 0xC1 );
	// VEX.NDS.256.66.0F38.WIG 00 /r VPSHUFB ymm1,ymm2,ymm3/m256
	_TEST64_VEX( "c4e27d0000 vpshufb ymm0,ymm0,ymmword ptr [rax]", 0xC4, 0xE2, 0x7D, 0x00, 0x00 );
	_TEST32_VEX( "c4e27d00c1 vpshufb ymm0,ymm0,ymm1", 0xC4, 0xE2, 0x7D, 0x00, 0xC1 );

	// PSADBW
	// 0F F6 /r PSADBW mm1,mm2/m64
	_TEST64( "0ff600 psadbw mm0,qword ptr [rax]", 0x0F, 0xF6, 0x00 );
	_TEST32( "0ff6c1 psadbw mm0,mm1", 0x0F, 0xF6, 0xC1 );
	// 66 0F F6 /r PSADBW xmm1,xmm2/m128
	_TEST64( "660ff600 psadbw xmm0,oword ptr [rax]", 0x66, 0x0F, 0xF6, 0x00 );
	_TEST32( "660ff6c1 psadbw xmm0,xmm1", 0x66, 0x0F, 0xF6, 0xC1 );
	// VEX.NDS.128.66.0F.WIG F6 /r VPSADBW xmm1,xmm2,xmm3/m128
	_TEST64_VEX( "c4e179f600 vpsadbw xmm0,xmm0,oword ptr [rax]", 0xC4, 0xE1, 0x79, 0xF6, 0x00 );
	_TEST32_VEX( "c4e179f6c1 vpsadbw xmm0,xmm0,xmm1", 0xC4, 0xE1, 0x79, 0xF6, 0xC1 );
	// VEX.NDS.256.66.0F.WIG F6 /r VPSADBW ymm1,ymm2,ymm3/m256
	_TEST64_VEX( "c4e17df600 vpsadbw ymm0,ymm0,ymmword ptr [rax]", 0xC4, 0xE1, 0x7D, 0xF6, 0x00 );
	_TEST32_VEX( "c4e17df6c1 vpsadbw ymm0,ymm0,ymm1", 0xC4, 0xE1, 0x7D, 0xF6, 0xC1 );

	// PREFETCHT
	// 0F 18 /1 PREFETCHT0 m8 M Valid Valid Move data from m8 closer to the processor using T0 hint.
	_TEST32( "0f1808 prefetcht0 byte ptr [eax]", 0x0F, 0x18, 0x08 );
	_TEST64( "0f1808 prefetcht0 byte ptr [rax]", 0x0F, 0x18, 0x08 );
	// 0F 18 /2 PREFETCHT1 m8 M Valid Valid Move data from m8 closer to the processor using T1 hint.
	_TEST32( "0f1810 prefetcht1 byte ptr [eax]", 0x0F, 0x18, 0x10 );
	_TEST64( "0f1810 prefetcht1 byte ptr [rax]", 0x0F, 0x18, 0x10 );
	// 0F 18 /3 PREFETCHT2 m8 M Valid Valid Move data from m8 closer to the processor using T2 hint.
	_TEST32( "0f1818 prefetcht2 byte ptr [eax]", 0x0F, 0x18, 0x18 );
	_TEST64( "0f1818 prefetcht2 byte ptr [rax]", 0x0F, 0x18, 0x18 );
	// 0F 18 /0 PREFETCHNTA m8 M Valid Valid Move data from m8 closer to the processor using NTA hint.
	_TEST32( "0f1800 prefetchnta byte ptr [eax]", 0x0F, 0x18, 0x00 );
	_TEST64( "0f1800 prefetchnta byte ptr [rax]", 0x0F, 0x18, 0x00 );

	// POR
	// 0F EB /r1 POR mm,mm/m64
	_TEST64( "0feb00 por mm0,qword ptr [rax]", 0x0F, 0xEB, 0x00 );
	_TEST32( "0febc1 por mm0,mm1", 0x0F, 0xEB, 0xC1 );
	// 66 0F EB /r POR xmm1,xmm2/m128
	_TEST64( "660feb00 por xmm0,oword ptr [rax]", 0x66, 0x0F, 0xEB, 0x00 );
	_TEST32( "660febc1 por xmm0,xmm1", 0x66, 0x0F, 0xEB, 0xC1 );
	// VEX.NDS.128.66.0F.WIG EB /r VPOR xmm1,xmm2,xmm3/m128
	_TEST64_VEX( "c4e179eb00 vpor xmm0,xmm0,oword ptr [rax]", 0xC4, 0xE1, 0x79, 0xEB, 0x00 );
	_TEST32_VEX( "c4e179ebc1 vpor xmm0,xmm0,xmm1", 0xC4, 0xE1, 0x79, 0xEB, 0xC1 );
	// VEX.NDS.256.66.0F.WIG EB /r VPOR ymm1,ymm2,ymm3/m256
	_TEST64_VEX( "c4e17deb00 vpor ymm0,ymm0,ymmword ptr [rax]", 0xC4, 0xE1, 0x7D, 0xEB, 0x00 );
	_TEST32_VEX( "c4e17debc1 vpor ymm0,ymm0,ymm1", 0xC4, 0xE1, 0x7D, 0xEB, 0xC1 );

	// POPF
	// 9D POPF NP Valid Valid Pop top of stack into lower 16 bits of EFLAGS.
	_TEST32( "669d popf", 0x66, 0x9D );
	_TEST64( "669d popf", 0x66, 0x9D );
	// 9D POPFD NP N.E. Valid Pop top of stack into EFLAGS.
	_TEST32( "9d popfd", 0x9D );
	_TEST64( "FAIL", 0x9D );
	// REX.W + 9D POPFQ NP Valid N.E. Pop top of stack and zero-extend into RFLAGS.
	_TEST64( "489d popfq", 0x48, 0x9D );

	// POPCNT
	// F3 0F B8 /r POPCNT r16, r/m16 RM Valid Valid POPCNT on r/m16
	_TEST32( "66f30fb800 popcnt ax,word ptr [eax]", 0x66, 0xF3, 0x0F, 0xB8, 0x00 );
	_TEST32( "66f30fb8c0 popcnt ax,ax", 0x66, 0xF3, 0x0F, 0xB8, 0xC0 );
	// F3 0F B8 /r POPCNT r32, r/m32 RM Valid Valid POPCNT on r/m32
	_TEST32( "f30fb800 popcnt eax,dword ptr [eax]", 0xF3, 0x0F, 0xB8, 0x00 );
	// F3 REX.W 0F B8 /r POPCNT r64, r/m64 RM Valid N.E. POPCNT on r/m64
	_TEST64( "f3480fb800 popcnt rax,qword ptr [rax]", 0xF3, 0x48, 0x0F, 0xB8, 0x00 );

	// POPA
	// 61 POPA NP Invalid Valid Pop DI, SI, BP, BX, DX, CX, and AX.
	_TEST32( "61 popad", 0x61 );
	_TEST64( "FAIL", 0x61 );
	// 61 POPAD NP Invalid Valid Pop EDI, ESI, EBP, EBX, EDX, ECX, and EAX.
	_TEST32( "6661 popa", 0x66, 0x61 );

	// POP
	// 8F /0 POP r/m16 M Valid Valid Pop top of stack into m16; increment stack pointer.
	// 8F /0 POP r/m32 M N.E. Valid Pop top of stack into m32; increment stack pointer.
	// 8F /0 POP r/m64 M Valid N.E. Pop top of stack into m64; increment stack pointer. Cannot encode 32-bit operand size.
	// 32 BIT.
	_TEST32( "8f00 pop dword ptr [eax]", 0x8F, 0x00 );
	_TEST32( "8fc1 pop ecx", 0x8F, 0xC1 );
	_TEST32( "668f00 pop word ptr [eax]", 0x66, 0x8F, 0x00 );
	_TEST32( "668fc1 pop cx", 0x66, 0x8F, 0xC1 );
	_TEST32( "678f00 pop dword ptr [bx+si]", 0x67, 0x8F, 0x00 );
	_TEST32( "678fc1 pop ecx", 0x67, 0x8F, 0xC1 );
	_TEST32( "66678f00 pop word ptr [bx+si]", 0x66, 0x67, 0x8F, 0x00 );
	_TEST32( "66678fc1 pop cx", 0x66, 0x67, 0x8F, 0xC1 );
	// 64 BIT.
	_TEST64( "8f00 pop qword ptr [rax]", 0x8F, 0x00 );
	_TEST64( "8fc1 pop rcx", 0x8F, 0xC1 );
	_TEST64( "668f00 pop word ptr [rax]", 0x66, 0x8F, 0x00 );
	_TEST64( "668fc1 pop cx", 0x66, 0x8F, 0xC1 );
	_TEST64( "678f00 pop qword ptr [eax]", 0x67, 0x8F, 0x00 );
	_TEST64( "678fc1 pop rcx", 0x67, 0x8F, 0xC1 );
	_TEST64( "66678f00 pop word ptr [eax]", 0x66, 0x67, 0x8F, 0x00 );
	_TEST64( "66678fc1 pop cx", 0x66, 0x67, 0x8F, 0xC1 );
	_TEST64( "488f00 pop qword ptr [rax]", 0x48, 0x8F, 0x00 );
	_TEST64( "488fc1 pop rcx", 0x48, 0x8F, 0xC1 );
	// 58+ rw POP r16 O Valid Valid Pop top of stack into r16; increment stack pointer.
	// 58+ rd POP r32 O N.E. Valid Pop top of stack into r32; increment stack pointer.
	// 58+ rd POP r64 O Valid N.E. Pop top of stack into r64; increment stack pointer. Cannot encode 32-bit operand size.
	_TEST32( "58 pop eax", 0x58 );
	_TEST32( "6658 pop ax", 0x66, 0x58 );
	_TEST32( "6758 pop eax", 0x67, 0x58 );
	_TEST64( "58 pop rax", 0x58 );
	_TEST64( "6658 pop ax", 0x66, 0x58 );
	_TEST64( "6758 pop rax", 0x67, 0x58 );
	_TEST64( "4858 pop rax", 0x48, 0x58 );
	// 1F POP DS NP Invalid Valid Pop top of stack into DS; increment stack pointer.
	// 07 POP ES NP Invalid Valid Pop top of stack into ES; increment stack pointer.
	// 17 POP SS NP Invalid Valid Pop top of stack into SS; increment stack pointer.
	_TEST32( "1f pop ds", 0x1F );
	_TEST32( "07 pop es", 0x07 );
	_TEST32( "17 pop ss", 0x17 );
	// 0F A1 POP FS NP Valid Valid Pop top of stack into FS; increment stack pointer by 16 bits.
	// 0F A1 POP FS NP N.E. Valid Pop top of stack into FS; increment stack pointer by 32 bits.
	// 0F A1 POP FS NP Valid N.E. Pop top of stack into FS; increment stack pointer by 64 bits.
	_TEST32( "0fa1 pop fs", 0x0F, 0xA1 );
	_TEST64( "0fa1 pop fs", 0x0F, 0xA1 );
	// 0F A9 POP GS NP Valid Valid Pop top of stack into GS; increment stack pointer by 16 bits.
	// 0F A9 POP GS NP N.E. Valid Pop top of stack into GS; increment stack pointer by 32 bits.
	// 0F A9 POP GS NP Valid N.E. Pop top of stack into GS; increment stack pointer by 64 bits.
	_TEST32( "0fa9 pop gs", 0x0F, 0xA9 );
	_TEST64( "0fa9 pop gs", 0x0F, 0xA9 );

	// PMULUDQ
	// 0F F4 /r1 PMULUDQ mm1,mm2/m64
	_TEST64( "0ff400 pmuludq mm0,qword ptr [rax]", 0x0F, 0xF4, 0x00 );
	_TEST32( "0ff4c1 pmuludq mm0,mm1", 0x0F, 0xF4, 0xC1 );
	// 66 0F F4 /r PMULUDQ xmm1,xmm2/m128
	_TEST64( "660ff400 pmuludq xmm0,oword ptr [rax]", 0x66, 0x0F, 0xF4, 0x00 );
	_TEST32( "660ff4c1 pmuludq xmm0,xmm1", 0x66, 0x0F, 0xF4, 0xC1 );
	// VEX.NDS.128.66.0F.WIG F4 /r VPMULUDQ xmm1,xmm2,xmm3/m128
	_TEST64_VEX( "c4e179f400 vpmuludq xmm0,xmm0,oword ptr [rax]", 0xC4, 0xE1, 0x79, 0xF4, 0x00 );
	_TEST32_VEX( "c4e179f4c1 vpmuludq xmm0,xmm0,xmm1", 0xC4, 0xE1, 0x79, 0xF4, 0xC1 );
	// VEX.NDS.256.66.0F.WIG F4 /r VPMULUDQ ymm1,ymm2,ymm3/m256
	_TEST64_VEX( "c4e17df400 vpmuludq ymm0,ymm0,ymmword ptr [rax]", 0xC4, 0xE1, 0x7D, 0xF4, 0x00 );
	_TEST32_VEX( "c4e17df4c1 vpmuludq ymm0,ymm0,ymm1", 0xC4, 0xE1, 0x7D, 0xF4, 0xC1 );

	// PMULLW
	// 0F D5 /r PMULLW mm,mm/m64
	_TEST64( "0fd500 pmullw mm0,qword ptr [rax]", 0x0F, 0xD5, 0x00 );
	_TEST32( "0fd5c1 pmullw mm0,mm1", 0x0F, 0xD5, 0xC1 );
	// 66 0F D5 /r PMULLW xmm1,xmm2/m128
	_TEST64( "660fd500 pmullw xmm0,oword ptr [rax]", 0x66, 0x0F, 0xD5, 0x00 );
	_TEST32( "660fd5c1 pmullw xmm0,xmm1", 0x66, 0x0F, 0xD5, 0xC1 );
	// VEX.NDS.128.66.0F.WIG D5 /r VPMULLW xmm1,xmm2,xmm3/m128
	_TEST64_VEX( "c4e179d500 vpmullw xmm0,xmm0,oword ptr [rax]", 0xC4, 0xE1, 0x79, 0xD5, 0x00 );
	_TEST32_VEX( "c4e179d5c1 vpmullw xmm0,xmm0,xmm1", 0xC4, 0xE1, 0x79, 0xD5, 0xC1 );
	// VEX.NDS.256.66.0F.WIG D5 /r VPMULLW ymm1,ymm2,ymm3/m256
	_TEST64_VEX( "c4e17dd500 vpmullw ymm0,ymm0,ymmword ptr [rax]", 0xC4, 0xE1, 0x7D, 0xD5, 0x00 );
	_TEST32_VEX( "c4e17dd5c1 vpmullw ymm0,ymm0,ymm1", 0xC4, 0xE1, 0x7D, 0xD5, 0xC1 );

	// PMULLD
	// 66 0F 38 40 /r PMULLD xmm1,xmm2/m128
	_TEST64( "660f384000 pmulld xmm0,oword ptr [rax]", 0x66, 0x0F, 0x38, 0x40, 0x00 );
	_TEST32( "660f3840c1 pmulld xmm0,xmm1", 0x66, 0x0F, 0x38, 0x40, 0xC1 );
	// VEX.NDS.128.66.0F38.WIG 40 /r VPMULLD xmm1,xmm2,xmm3/m128
	_TEST64_VEX( "c4e2794000 vpmulld xmm0,xmm0,oword ptr [rax]", 0xC4, 0xE2, 0x79, 0x40, 0x00 );
	_TEST32_VEX( "c4e27940c1 vpmulld xmm0,xmm0,xmm1", 0xC4, 0xE2, 0x79, 0x40, 0xC1 );
	// VEX.NDS.256.66.0F38.WIG 40 /r VPMULLD ymm1,ymm2,ymm3/m256
	_TEST64_VEX( "c4e27d4000 vpmulld ymm0,ymm0,ymmword ptr [rax]", 0xC4, 0xE2, 0x7D, 0x40, 0x00 );
	_TEST32_VEX( "c4e27d40c1 vpmulld ymm0,ymm0,ymm1", 0xC4, 0xE2, 0x7D, 0x40, 0xC1 );

	// PMULHW
	// 0F E5 /r PMULHW mm,mm/m64
	_TEST64( "0fe500 pmulhw mm0,qword ptr [rax]", 0x0F, 0xE5, 0x00 );
	_TEST32( "0fe5c1 pmulhw mm0,mm1", 0x0F, 0xE5, 0xC1 );
	// 66 0F E5 /r PMULHW xmm1,xmm2/m128
	_TEST64( "660fe500 pmulhw xmm0,oword ptr [rax]", 0x66, 0x0F, 0xE5, 0x00 );
	_TEST32( "660fe5c1 pmulhw xmm0,xmm1", 0x66, 0x0F, 0xE5, 0xC1 );
	// VEX.NDS.128.66.0F.WIG E5 /r VPMULHW xmm1,xmm2,xmm3/m128
	_TEST64_VEX( "c4e179e500 vpmulhw xmm0,xmm0,oword ptr [rax]", 0xC4, 0xE1, 0x79, 0xE5, 0x00 );
	_TEST32_VEX( "c4e179e5c1 vpmulhw xmm0,xmm0,xmm1", 0xC4, 0xE1, 0x79, 0xE5, 0xC1 );
	// VEX.NDS.256.66.0F.WIG E5 /r VPMULHW ymm1,ymm2,ymm3/m256
	_TEST64_VEX( "c4e17de500 vpmulhw ymm0,ymm0,ymmword ptr [rax]", 0xC4, 0xE1, 0x7D, 0xE5, 0x00 );
	_TEST32_VEX( "c4e17de5c1 vpmulhw ymm0,ymm0,ymm1", 0xC4, 0xE1, 0x7D, 0xE5, 0xC1 );

	// PMULHUW
	// 0F E4 /r PMULHUW mm1,mm2/m64
	_TEST64( "0fe400 pmulhuw mm0,qword ptr [rax]", 0x0F, 0xE4, 0x00 );
	_TEST32( "0fe4c1 pmulhuw mm0,mm1", 0x0F, 0xE4, 0xC1 );
	// 66 0F E4 /r PMULHUW xmm1,xmm2/m128
	_TEST64( "660fe400 pmulhuw xmm0,oword ptr [rax]", 0x66, 0x0F, 0xE4, 0x00 );
	_TEST32( "660fe4c1 pmulhuw xmm0,xmm1", 0x66, 0x0F, 0xE4, 0xC1 );
	// VEX.NDS.128.66.0F.WIG E4 /r VPMULHUW xmm1,xmm2,xmm3/m128
	_TEST64_VEX( "c4e179e400 vpmulhuw xmm0,xmm0,oword ptr [rax]", 0xC4, 0xE1, 0x79, 0xE4, 0x00 );
	_TEST32_VEX( "c4e179e4c1 vpmulhuw xmm0,xmm0,xmm1", 0xC4, 0xE1, 0x79, 0xE4, 0xC1 );
	// VEX.NDS.256.66.0F.WIG E4 /r VPMULHUW ymm1,ymm2,ymm3/m256
	_TEST64_VEX( "c4e17de400 vpmulhuw ymm0,ymm0,ymmword ptr [rax]", 0xC4, 0xE1, 0x7D, 0xE4, 0x00 );
	_TEST32_VEX( "c4e17de4c1 vpmulhuw ymm0,ymm0,ymm1", 0xC4, 0xE1, 0x7D, 0xE4, 0xC1 );

	// PMULHRSW
	// 0F 38 0B /r1 PMULHRSW mm1,mm2/m64
	_TEST64( "0f380b00 pmulhrsw mm0,qword ptr [rax]", 0x0F, 0x38, 0x0B, 0x00 );
	_TEST32( "0f380bc1 pmulhrsw mm0,mm1", 0x0F, 0x38, 0x0B, 0xC1 );
	// 66 0F 38 0B /r PMULHRSW xmm1,xmm2/m128
	_TEST64( "660f380b00 pmulhrsw xmm0,oword ptr [rax]", 0x66, 0x0F, 0x38, 0x0B, 0x00 );
	_TEST32( "660f380bc1 pmulhrsw xmm0,xmm1", 0x66, 0x0F, 0x38, 0x0B, 0xC1 );
	// VEX.NDS.128.66.0F38.WIG 0B /r VPMULHRSW xmm1,xmm2,xmm3/m128
	_TEST64_VEX( "c4e2790b00 vpmulhrsw xmm0,xmm0,oword ptr [rax]", 0xC4, 0xE2, 0x79, 0x0B, 0x00 );
	_TEST32_VEX( "c4e2790bc1 vpmulhrsw xmm0,xmm0,xmm1", 0xC4, 0xE2, 0x79, 0x0B, 0xC1 );
	// VEX.NDS.256.66.0F38.WIG 0B /r VPMULHRSW ymm1,ymm2,ymm3/m256
	_TEST64_VEX( "c4e27d0b00 vpmulhrsw ymm0,ymm0,ymmword ptr [rax]", 0xC4, 0xE2, 0x7D, 0x0B, 0x00 );
	_TEST32_VEX( "c4e27d0bc1 vpmulhrsw ymm0,ymm0,ymm1", 0xC4, 0xE2, 0x7D, 0x0B, 0xC1 );

	// PMULDQ
	// 66 0F 38 28 /r PMULDQ xmm1,xmm2/m128
	_TEST64( "660f382800 pmuldq xmm0,oword ptr [rax]", 0x66, 0x0F, 0x38, 0x28, 0x00 );
	_TEST32( "660f3828c1 pmuldq xmm0,xmm1", 0x66, 0x0F, 0x38, 0x28, 0xC1 );
	// VEX.NDS.128.66.0F38.WIG 28 /r VPMULDQ xmm1,xmm2,xmm3/m128
	_TEST64_VEX( "c4e2792800 vpmuldq xmm0,xmm0,oword ptr [rax]", 0xC4, 0xE2, 0x79, 0x28, 0x00 );
	_TEST32_VEX( "c4e27928c1 vpmuldq xmm0,xmm0,xmm1", 0xC4, 0xE2, 0x79, 0x28, 0xC1 );
	// VEX.NDS.256.66.0F38.WIG 28 /r VPMULDQ ymm1,ymm2,ymm3/m256
	_TEST64_VEX( "c4e27d2800 vpmuldq ymm0,ymm0,ymmword ptr [rax]", 0xC4, 0xE2, 0x7D, 0x28, 0x00 );
	_TEST32_VEX( "c4e27d28c1 vpmuldq ymm0,ymm0,ymm1", 0xC4, 0xE2, 0x7D, 0x28, 0xC1 );

	// 66 0f 38 30 /r PMOVZXBW xmm1, xmm2/m64
	_TEST64( "660f383000 pmovzxbw xmm0,qword ptr [rax]", 0x66, 0x0F, 0x38, 0x30, 0x00 );
	_TEST32( "660f3830c1 pmovzxbw xmm0,xmm1", 0x66, 0x0F, 0x38, 0x30, 0xC1 );
	// 66 0f 38 31 /r PMOVZXBD xmm1, xmm2/m32
	_TEST64( "660f383100 pmovzxbd xmm0,dword ptr [rax]", 0x66, 0x0F, 0x38, 0x31, 0x00 );
	_TEST32( "660f3831c1 pmovzxbd xmm0,xmm1", 0x66, 0x0F, 0x38, 0x31, 0xC1 );
	// 66 0f 38 32 /r PMOVZXBQ xmm1, xmm2/m16
	_TEST64( "660f383200 pmovzxbq xmm0,word ptr [rax]", 0x66, 0x0F, 0x38, 0x32, 0x00 );
	_TEST32( "660f3832c1 pmovzxbq xmm0,xmm1", 0x66, 0x0F, 0x38, 0x32, 0xC1 );
	// 66 0f 38 33 /r PMOVZXWD xmm1, xmm2/m64
	_TEST64( "660f383300 pmovzxwd xmm0,qword ptr [rax]", 0x66, 0x0F, 0x38, 0x33, 0x00 );
	_TEST32( "660f3833c1 pmovzxwd xmm0,xmm1", 0x66, 0x0F, 0x38, 0x33, 0xC1 );
	// 66 0f 38 34 /r PMOVZXWQ xmm1, xmm2/m32
	_TEST64( "660f383400 pmovzxwq xmm0,dword ptr [rax]", 0x66, 0x0F, 0x38, 0x34, 0x00 );
	_TEST32( "660f3834c1 pmovzxwq xmm0,xmm1", 0x66, 0x0F, 0x38, 0x34, 0xC1 );
	// 66 0f 38 35 /r PMOVZXDQ xmm1, xmm2/m64
	_TEST64( "660f383500 pmovzxdq xmm0,qword ptr [rax]", 0x66, 0x0F, 0x38, 0x35, 0x00 );
	_TEST32( "660f3835c1 pmovzxdq xmm0,xmm1", 0x66, 0x0F, 0x38, 0x35, 0xC1 );
	// VEX.128.66.0F38.WIG 30 /r VPMOVZXBW xmm1, xmm2/m64
	_TEST32_VEX( "c4e2793000 vpmovzxbw xmm0,qword ptr [eax]", 0xC4, 0xE2, 0x79, 0x30, 0x00 );
	_TEST64_VEX( "c4e27930c1 vpmovzxbw xmm0,xmm1", 0xC4, 0xE2, 0x79, 0x30, 0xC1 );
	// VEX.128.66.0F38.WIG 31 /r VPMOVZXBD xmm1, xmm2/m32
	_TEST32_VEX( "c4e2793100 vpmovzxbd xmm0,dword ptr [eax]", 0xC4, 0xE2, 0x79, 0x31, 0x00 );
	_TEST64_VEX( "c4e27931c1 vpmovzxbd xmm0,xmm1", 0xC4, 0xE2, 0x79, 0x31, 0xC1 );
	// VEX.128.66.0F38.WIG 32 /r VPMOVZXBQ xmm1, xmm2/m16
	_TEST32_VEX( "c4e2793200 vpmovzxbq xmm0,word ptr [eax]", 0xC4, 0xE2, 0x79, 0x32, 0x00 );
	_TEST64_VEX( "c4e27932c1 vpmovzxbq xmm0,xmm1", 0xC4, 0xE2, 0x79, 0x32, 0xC1 );
	// VEX.128.66.0F38.WIG 33 /r VPMOVZXWD xmm1, xmm2/m64
	_TEST32_VEX( "c4e2793300 vpmovzxwd xmm0,qword ptr [eax]", 0xC4, 0xE2, 0x79, 0x33, 0x00 );
	_TEST64_VEX( "c4e27933c1 vpmovzxwd xmm0,xmm1", 0xC4, 0xE2, 0x79, 0x33, 0xC1 );
	// VEX.128.66.0F38.WIG 34 /r VPMOVZXWQ xmm1, xmm2/m32
	_TEST32_VEX( "c4e2793400 vpmovzxwq xmm0,dword ptr [eax]", 0xC4, 0xE2, 0x79, 0x34, 0x00 );
	_TEST64_VEX( "c4e27934c1 vpmovzxwq xmm0,xmm1", 0xC4, 0xE2, 0x79, 0x34, 0xC1 );
	// VEX.128.66.0F38.WIG 35 /r VPMOVZXDQ xmm1, xmm2/m64
	_TEST32_VEX( "c4e2793500 vpmovzxdq xmm0,qword ptr [eax]", 0xC4, 0xE2, 0x79, 0x35, 0x00 );
	_TEST64_VEX( "c4e27935c1 vpmovzxdq xmm0,xmm1", 0xC4, 0xE2, 0x79, 0x35, 0xC1 );
	// VEX.256.66.0F38.WIG 30 /r VPMOVZXBW ymm1,xmm2/m128
	_TEST32_VEX( "c4e27d3000 vpmovzxbw ymm0,oword ptr [eax]", 0xC4, 0xE2, 0x7D, 0x30, 0x00 );
	_TEST64_VEX( "c4e27d30c1 vpmovzxbw ymm0,xmm1", 0xC4, 0xE2, 0x7D, 0x30, 0xC1 );
	// VEX.256.66.0F38.WIG 31 /r VPMOVZXBD ymm1,xmm2/m64
	_TEST32_VEX( "c4e27d3100 vpmovzxbd ymm0,qword ptr [eax]", 0xC4, 0xE2, 0x7D, 0x31, 0x00 );
	_TEST64_VEX( "c4e27d31c1 vpmovzxbd ymm0,xmm1", 0xC4, 0xE2, 0x7D, 0x31, 0xC1 );
	// VEX.256.66.0F38.WIG 32 /r VPMOVZXBQ ymm1,xmm2/m32
	_TEST32_VEX( "c4e27d3200 vpmovzxbq ymm0,dword ptr [eax]", 0xC4, 0xE2, 0x7D, 0x32, 0x00 );
	_TEST64_VEX( "c4e27d32c1 vpmovzxbq ymm0,xmm1", 0xC4, 0xE2, 0x7D, 0x32, 0xC1 );
	// VEX.256.66.0F38.WIG 33 /r VPMOVZXWD ymm1,xmm2/m128
	_TEST32_VEX( "c4e27d3300 vpmovzxwd ymm0,oword ptr [eax]", 0xC4, 0xE2, 0x7D, 0x33, 0x00 );
	_TEST64_VEX( "c4e27d33c1 vpmovzxwd ymm0,xmm1", 0xC4, 0xE2, 0x7D, 0x33, 0xC1 );

	// PMOVSXBW
	// 66 0f 38 20 /r PMOVSXBW xmm1,xmm2/m64
	_TEST64( "660f382000 pmovsxbw xmm0,qword ptr [rax]", 0x66, 0x0F, 0x38, 0x20, 0x00 );
	_TEST32( "660f3820c1 pmovsxbw xmm0,xmm1", 0x66, 0x0F, 0x38, 0x20, 0xC1 );
	// 66 0f 38 21 /r PMOVSXBD xmm1,xmm2/m32
	_TEST64( "660f382100 pmovsxbd xmm0,dword ptr [rax]", 0x66, 0x0F, 0x38, 0x21, 0x00 );
	_TEST32( "660f3821c1 pmovsxbd xmm0,xmm1", 0x66, 0x0F, 0x38, 0x21, 0xC1 );
	// 66 0f 38 22 /r PMOVSXBQ xmm1,xmm2/m16
	_TEST64( "660f382200 pmovsxbq xmm0,word ptr [rax]", 0x66, 0x0F, 0x38, 0x22, 0x00 );
	_TEST32( "660f3822c1 pmovsxbq xmm0,xmm1", 0x66, 0x0F, 0x38, 0x22, 0xC1 );
	// 66 0f 38 23 /r PMOVSXWD xmm1,xmm2/m64
	_TEST64( "660f382300 pmovsxwd xmm0,qword ptr [rax]", 0x66, 0x0F, 0x38, 0x23, 0x00 );
	_TEST32( "660f3823c1 pmovsxwd xmm0,xmm1", 0x66, 0x0F, 0x38, 0x23, 0xC1 );
	// 66 0f 38 24 /r PMOVSXWQ xmm1,xmm2/m32
	_TEST64( "660f382400 pmovsxwq xmm0,dword ptr [rax]", 0x66, 0x0F, 0x38, 0x24, 0x00 );
	_TEST32( "660f3824c1 pmovsxwq xmm0,xmm1", 0x66, 0x0F, 0x38, 0x24, 0xC1 );
	// 66 0f 38 25 /r PMOVSXDQ xmm1,xmm2/m64
	_TEST64( "660f382500 pmovsxdq xmm0,qword ptr [rax]", 0x66, 0x0F, 0x38, 0x25, 0x00 );
	_TEST32( "660f3825c1 pmovsxdq xmm0,xmm1", 0x66, 0x0F, 0x38, 0x25, 0xC1 );
	// VEX.128.66.0F38.WIG 20 /r VPMOVSXBW xmm1,xmm2/m64
	_TEST32_VEX( "c4e2792000 vpmovsxbw xmm0,qword ptr [eax]", 0xC4, 0xE2, 0x79, 0x20, 0x00 );
	_TEST64_VEX( "c4e27920c1 vpmovsxbw xmm0,xmm1", 0xC4, 0xE2, 0x79, 0x20, 0xC1 );
	// VEX.128.66.0F38.WIG 21 /r VPMOVSXBD xmm1,xmm2/m32
	_TEST32_VEX( "c4e2792100 vpmovsxbd xmm0,dword ptr [eax]", 0xC4, 0xE2, 0x79, 0x21, 0x00 );
	_TEST64_VEX( "c4e27921c1 vpmovsxbd xmm0,xmm1", 0xC4, 0xE2, 0x79, 0x21, 0xC1 );
	// VEX.128.66.0F38.WIG 22 /r VPMOVSXBQ xmm1,xmm2/m16
	_TEST32_VEX( "c4e2792200 vpmovsxbq xmm0,word ptr [eax]", 0xC4, 0xE2, 0x79, 0x22, 0x00 );
	_TEST64_VEX( "c4e27922c1 vpmovsxbq xmm0,xmm1", 0xC4, 0xE2, 0x79, 0x22, 0xC1 );
	// VEX.128.66.0F38.WIG 23 /r VPMOVSXWD xmm1,xmm2/m64
	_TEST32_VEX( "c4e2792300 vpmovsxwd xmm0,qword ptr [eax]", 0xC4, 0xE2, 0x79, 0x23, 0x00 );
	_TEST64_VEX( "c4e27923c1 vpmovsxwd xmm0,xmm1", 0xC4, 0xE2, 0x79, 0x23, 0xC1 );
	// VEX.128.66.0F38.WIG 24 /r VPMOVSXWQ xmm1,xmm2/m32
	_TEST32_VEX( "c4e2792400 vpmovsxwq xmm0,dword ptr [eax]", 0xC4, 0xE2, 0x79, 0x24, 0x00 );
	_TEST64_VEX( "c4e27924c1 vpmovsxwq xmm0,xmm1", 0xC4, 0xE2, 0x79, 0x24, 0xC1 );
	// VEX.128.66.0F38.WIG 25 /r VPMOVSXDQ xmm1,xmm2/m64
	_TEST32_VEX( "c4e2792500 vpmovsxdq xmm0,qword ptr [eax]", 0xC4, 0xE2, 0x79, 0x25, 0x00 );
	_TEST64_VEX( "c4e27925c1 vpmovsxdq xmm0,xmm1", 0xC4, 0xE2, 0x79, 0x25, 0xC1 );
	// VEX.256.66.0F38.WIG 20 /r VPMOVSXBW ymm1,xmm2/m128
	_TEST32_VEX( "c4e27d2000 vpmovsxbw ymm0,oword ptr [eax]", 0xC4, 0xE2, 0x7D, 0x20, 0x00 );
	_TEST64_VEX( "c4e27d20c1 vpmovsxbw ymm0,xmm1", 0xC4, 0xE2, 0x7D, 0x20, 0xC1 );
	// VEX.256.66.0F38.WIG 21 /r VPMOVSXBD ymm1,xmm2/m64
	_TEST32_VEX( "c4e27d2100 vpmovsxbd ymm0,qword ptr [eax]", 0xC4, 0xE2, 0x7D, 0x21, 0x00 );
	_TEST64_VEX( "c4e27d21c1 vpmovsxbd ymm0,xmm1", 0xC4, 0xE2, 0x7D, 0x21, 0xC1 );
	// VEX.256.66.0F38.WIG 22 /r VPMOVSXBQ ymm1,xmm2/m32
	_TEST32_VEX( "c4e27d2200 vpmovsxbq ymm0,dword ptr [eax]", 0xC4, 0xE2, 0x7D, 0x22, 0x00 );
	_TEST64_VEX( "c4e27d22c1 vpmovsxbq ymm0,xmm1", 0xC4, 0xE2, 0x7D, 0x22, 0xC1 );

	// PMOVMSKB
	// 0F D7 /r PMOVMSKB reg,mm
	_TEST32( "0fd7c1 pmovmskb eax,mm1", 0x0F, 0xD7, 0xC1 );
	_TEST64( "0fd7c1 pmovmskb rax,mm1", 0x0F, 0xD7, 0xC1 );
	// 66 0F D7 /r PMOVMSKB reg,xmm
	_TEST32( "660fd7c1 pmovmskb eax,xmm1", 0x66, 0x0F, 0xD7, 0xC1 );
	_TEST64( "660fd7c1 pmovmskb rax,xmm1", 0x66, 0x0F, 0xD7, 0xC1 );
	// VEX.128.66.0F.WIG D7 /r VPMOVMSKB reg,xmm1
	_TEST32_VEX( "c4e179d7c1 vpmovmskb eax,xmm0", 0xC4, 0xE1, 0x79, 0xD7, 0xC1 );
	_TEST64_VEX( "c4e179d7c1 vpmovmskb rax,xmm0", 0xC4, 0xE1, 0x79, 0xD7, 0xC1 );
	// VEX.256.66.0F.WIG D7 /r VPMOVMSKB reg,ymm1
	_TEST32_VEX( "c4e17dd7c1 vpmovmskb eax,ymm0", 0xC4, 0xE1, 0x7D, 0xD7, 0xC1 );
	_TEST64_VEX( "c4e17dd7c1 vpmovmskb rax,ymm0", 0xC4, 0xE1, 0x7D, 0xD7, 0xC1 );

	// PMINUW
	// 66 0F 38 3A /r PMINUW xmm1,xmm2/m128
	_TEST64( "660f383a00 pminuw xmm0,oword ptr [rax]", 0x66, 0x0F, 0x38, 0x3A, 0x00 );
	_TEST32( "660f383ac1 pminuw xmm0,xmm1", 0x66, 0x0F, 0x38, 0x3A, 0xC1 );
	// VEX.NDS.128.66.0F38.WIG 3A /r VPMINUW xmm1,xmm2,xmm3/m128
	_TEST64_VEX( "c4e2793a00 vpminuw xmm0,xmm0,oword ptr [rax]", 0xC4, 0xE2, 0x79, 0x3A, 0x00 );
	_TEST32_VEX( "c4e2793ac1 vpminuw xmm0,xmm0,xmm1", 0xC4, 0xE2, 0x79, 0x3A, 0xC1 );
	// VEX.NDS.256.66.0F38.WIG 3A /r VPMINUW ymm1,ymm2,ymm3/m256
	_TEST64_VEX( "c4e27d3a00 vpminuw ymm0,ymm0,ymmword ptr [rax]", 0xC4, 0xE2, 0x7D, 0x3A, 0x00 );
	_TEST32_VEX( "c4e27d3ac1 vpminuw ymm0,ymm0,ymm1", 0xC4, 0xE2, 0x7D, 0x3A, 0xC1 );

	// PMINUD
	// 66 0F 38 3B /r PMINUD xmm1,xmm2/m128
	_TEST64( "660f383b00 pminud xmm0,oword ptr [rax]", 0x66, 0x0F, 0x38, 0x3B, 0x00 );
	_TEST32( "660f383bc1 pminud xmm0,xmm1", 0x66, 0x0F, 0x38, 0x3B, 0xC1 );
	// VEX.NDS.128.66.0F38.WIG 3B /r VPMINUD xmm1,xmm2,xmm3/m128
	_TEST64_VEX( "c4e2793b00 vpminud xmm0,xmm0,oword ptr [rax]", 0xC4, 0xE2, 0x79, 0x3B, 0x00 );
	_TEST32_VEX( "c4e2793bc1 vpminud xmm0,xmm0,xmm1", 0xC4, 0xE2, 0x79, 0x3B, 0xC1 );
	// VEX.NDS.256.66.0F38.WIG 3B /r VPMINUD ymm1,ymm2,ymm3/m256
	_TEST64_VEX( "c4e27d3b00 vpminud ymm0,ymm0,ymmword ptr [rax]", 0xC4, 0xE2, 0x7D, 0x3B, 0x00 );
	_TEST32_VEX( "c4e27d3bc1 vpminud ymm0,ymm0,ymm1", 0xC4, 0xE2, 0x7D, 0x3B, 0xC1 );

	// PMINUB
	// 0F DA /r PMINUB mm1,mm2/m64
	_TEST64( "0fda00 pminub mm0,qword ptr [rax]", 0x0F, 0xDA, 0x00 );
	_TEST32( "0fdac1 pminub mm0,mm1", 0x0F, 0xDA, 0xC1 );
	// 66 0F DA /r PMINUB xmm1,xmm2/m128
	_TEST64( "660fda00 pminub xmm0,oword ptr [rax]", 0x66, 0x0F, 0xDA, 0x00 );
	_TEST32( "660fdac1 pminub xmm0,xmm1", 0x66, 0x0F, 0xDA, 0xC1 );
	// VEX.NDS.128.66.0F.WIG DA /r VPMINUB xmm1,xmm2,xmm3/m128
	_TEST64_VEX( "c4e179da00 vpminub xmm0,xmm0,oword ptr [rax]", 0xC4, 0xE1, 0x79, 0xDA, 0x00 );
	_TEST32_VEX( "c4e179dac1 vpminub xmm0,xmm0,xmm1", 0xC4, 0xE1, 0x79, 0xDA, 0xC1 );
	// VEX.NDS.256.66.0F.WIG DA /r VPMINUB ymm1,ymm2,ymm3/m256
	_TEST64_VEX( "c4e17dda00 vpminub ymm0,ymm0,ymmword ptr [rax]", 0xC4, 0xE1, 0x7D, 0xDA, 0x00 );
	_TEST32_VEX( "c4e17ddac1 vpminub ymm0,ymm0,ymm1", 0xC4, 0xE1, 0x7D, 0xDA, 0xC1 );

	// PMINSW
	// 0F EA /r PMINSW mm1,mm2/m64
	_TEST64( "0fea00 pminsw mm0,qword ptr [rax]", 0x0F, 0xEA, 0x00 );
	_TEST32( "0feac1 pminsw mm0,mm1", 0x0F, 0xEA, 0xC1 );
	// 66 0F EA /r PMINSW xmm1,xmm2/m128
	_TEST64( "660fea00 pminsw xmm0,oword ptr [rax]", 0x66, 0x0F, 0xEA, 0x00 );
	_TEST32( "660feac1 pminsw xmm0,xmm1", 0x66, 0x0F, 0xEA, 0xC1 );
	// VEX.NDS.128.66.0F.WIG EA /r VPMINSW xmm1,xmm2,xmm3/m128
	_TEST64_VEX( "c4e179ea00 vpminsw xmm0,xmm0,oword ptr [rax]", 0xC4, 0xE1, 0x79, 0xEA, 0x00 );
	_TEST32_VEX( "c4e179eac1 vpminsw xmm0,xmm0,xmm1", 0xC4, 0xE1, 0x79, 0xEA, 0xC1 );
	// VEX.NDS.256.66.0F.WIG EA /r VPMINSW ymm1,ymm2,ymm3/m256
	_TEST64_VEX( "c4e17dea00 vpminsw ymm0,ymm0,ymmword ptr [rax]", 0xC4, 0xE1, 0x7D, 0xEA, 0x00 );
	_TEST32_VEX( "c4e17deac1 vpminsw ymm0,ymm0,ymm1", 0xC4, 0xE1, 0x7D, 0xEA, 0xC1 );

	// PMINSD
	// 66 0F 38 39 /r PMINSD xmm1, xmm2/m128
	_TEST64( "660f383900 pminsd xmm0,oword ptr [rax]", 0x66, 0x0F, 0x38, 0x39, 0x00 );
	_TEST32( "660f3839c1 pminsd xmm0,xmm1", 0x66, 0x0F, 0x38, 0x39, 0xC1 );
	// VEX.NDS.128.66.0F38.WIG 39 /r VPMINSD xmm1, xmm2, xmm3/m128
	_TEST64_VEX( "c4e2793900 vpminsd xmm0,xmm0,oword ptr [rax]", 0xC4, 0xE2, 0x79, 0x39, 0x00 );
	_TEST32_VEX( "c4e27939c1 vpminsd xmm0,xmm0,xmm1", 0xC4, 0xE2, 0x79, 0x39, 0xC1 );
	// VEX.NDS.256.66.0F38.WIG 39 /r VPMINSD ymm1,ymm2,ymm3/m256
	_TEST64_VEX( "c4e27d3900 vpminsd ymm0,ymm0,ymmword ptr [rax]", 0xC4, 0xE2, 0x7D, 0x39, 0x00 );
	_TEST32_VEX( "c4e27d39c1 vpminsd ymm0,ymm0,ymm1", 0xC4, 0xE2, 0x7D, 0x39, 0xC1 );

	// PMINSB
	// 66 0F 38 38 /r PMINSB xmm1,xmm2/m128
	_TEST64( "660f383800 pminsb xmm0,oword ptr [rax]", 0x66, 0x0F, 0x38, 0x38, 0x00 );
	_TEST32( "660f3838c1 pminsb xmm0,xmm1", 0x66, 0x0F, 0x38, 0x38, 0xC1 );
	// VEX.NDS.128.66.0F38.WIG 38 /r VPMINSB xmm1,xmm2,xmm3/m128
	_TEST64_VEX( "c4e2793800 vpminsb xmm0,xmm0,oword ptr [rax]", 0xC4, 0xE2, 0x79, 0x38, 0x00 );
	_TEST32_VEX( "c4e27938c1 vpminsb xmm0,xmm0,xmm1", 0xC4, 0xE2, 0x79, 0x38, 0xC1 );
	// VEX.NDS.256.66.0F38.WIG 38 /r VPMINSB ymm1,ymm2,ymm3/m256
	_TEST64_VEX( "c4e27d3800 vpminsb ymm0,ymm0,ymmword ptr [rax]", 0xC4, 0xE2, 0x7D, 0x38, 0x00 );
	_TEST32_VEX( "c4e27d38c1 vpminsb ymm0,ymm0,ymm1", 0xC4, 0xE2, 0x7D, 0x38, 0xC1 );

	// PMAXUW
	// 66 0F 38 3E /r PMAXUW xmm1,xmm2/m128
	_TEST64( "660f383e00 pmaxuw xmm0,oword ptr [rax]", 0x66, 0x0F, 0x38, 0x3E, 0x00 );
	_TEST32( "660f383ec1 pmaxuw xmm0,xmm1", 0x66, 0x0F, 0x38, 0x3E, 0xC1 );
	// VEX.NDS.128.66.0F38.WIG 3E/r VPMAXUW xmm1,xmm2,xmm3/m128
	_TEST64_VEX( "c4e2793e00 vpmaxuw xmm0,xmm0,oword ptr [rax]", 0xC4, 0xE2, 0x79, 0x3E, 0x00 );
	_TEST32_VEX( "c4e2793ec1 vpmaxuw xmm0,xmm0,xmm1", 0xC4, 0xE2, 0x79, 0x3E, 0xC1 );
	// VEX.NDS.256.66.0F38.WIG 3E /r VPMAXUW ymm1,ymm2,ymm3/m256
	_TEST64_VEX( "c4e27d3e00 vpmaxuw ymm0,ymm0,ymmword ptr [rax]", 0xC4, 0xE2, 0x7D, 0x3E, 0x00 );
	_TEST32_VEX( "c4e27d3ec1 vpmaxuw ymm0,ymm0,ymm1", 0xC4, 0xE2, 0x7D, 0x3E, 0xC1 );

	// PMAXUD
	// 66 0F 38 3F /r PMAXUD xmm1, xmm2/m128
	_TEST64( "660f383f00 pmaxud xmm0,oword ptr [rax]", 0x66, 0x0F, 0x38, 0x3F, 0x00 );
	_TEST32( "660f383fc1 pmaxud xmm0,xmm1", 0x66, 0x0F, 0x38, 0x3F, 0xC1 );
	// VEX.NDS.128.66.0F38.WIG 3F /r VPMAXUD xmm1,xmm2,xmm3/m128
	_TEST64_VEX( "c4e2793f00 vpmaxud xmm0,xmm0,oword ptr [rax]", 0xC4, 0xE2, 0x79, 0x3F, 0x00 );
	_TEST32_VEX( "c4e2793fc1 vpmaxud xmm0,xmm0,xmm1", 0xC4, 0xE2, 0x79, 0x3F, 0xC1 );
	// VEX.NDS.256.66.0F38.WIG 3F /r VPMAXUD ymm1,ymm2,ymm3/m256
	_TEST64_VEX( "c4e27d3f00 vpmaxud ymm0,ymm0,ymmword ptr [rax]", 0xC4, 0xE2, 0x7D, 0x3F, 0x00 );
	_TEST32_VEX( "c4e27d3fc1 vpmaxud ymm0,ymm0,ymm1", 0xC4, 0xE2, 0x7D, 0x3F, 0xC1 );

	// PMAXUB
	// 0F DE /r PMAXUB mm1,mm2/m64
	_TEST64( "0fde00 pmaxub mm0,qword ptr [rax]", 0x0F, 0xDE, 0x00 );
	_TEST32( "0fdec1 pmaxub mm0,mm1", 0x0F, 0xDE, 0xC1 );
	// 66 0F DE /r PMAXUB xmm1,xmm2/m128
	_TEST64( "660fde00 pmaxub xmm0,oword ptr [rax]", 0x66, 0x0F, 0xDE, 0x00 );
	_TEST32( "660fdec1 pmaxub xmm0,xmm1", 0x66, 0x0F, 0xDE, 0xC1 );
	// VEX.NDS.128.66.0F.WIG DE /r VPMAXUB xmm1,xmm2,xmm3/m128
	_TEST64_VEX( "c4e179de00 vpmaxub xmm0,xmm0,oword ptr [rax]", 0xC4, 0xE1, 0x79, 0xDE, 0x00 );
	_TEST32_VEX( "c4e179dec1 vpmaxub xmm0,xmm0,xmm1", 0xC4, 0xE1, 0x79, 0xDE, 0xC1 );
	// VEX.NDS.256.66.0F.WIG DE /r VPMAXUB ymm1,ymm2,ymm3/m256
	_TEST64_VEX( "c4e17dde00 vpmaxub ymm0,ymm0,ymmword ptr [rax]", 0xC4, 0xE1, 0x7D, 0xDE, 0x00 );
	_TEST32_VEX( "c4e17ddec1 vpmaxub ymm0,ymm0,ymm1", 0xC4, 0xE1, 0x7D, 0xDE, 0xC1 );

	// PMAXSW
	// 0F EE /r PMAXSW mm1,mm2/m64
	_TEST64( "0fee00 pmaxsw mm0,qword ptr [rax]", 0x0F, 0xEE, 0x00 );
	_TEST32( "0feec1 pmaxsw mm0,mm1", 0x0F, 0xEE, 0xC1 );
	// 66 0F EE /r PMAXSW xmm1,xmm2/m128
	_TEST64( "660fee00 pmaxsw xmm0,oword ptr [rax]", 0x66, 0x0F, 0xEE, 0x00 );
	_TEST32( "660feec1 pmaxsw xmm0,xmm1", 0x66, 0x0F, 0xEE, 0xC1 );
	// VEX.NDS.128.66.0F.WIG EE /r VPMAXSW xmm1,xmm2,xmm3/m128
	_TEST64_VEX( "c4e179ee00 vpmaxsw xmm0,xmm0,oword ptr [rax]", 0xC4, 0xE1, 0x79, 0xEE, 0x00 );
	_TEST32_VEX( "c4e179eec1 vpmaxsw xmm0,xmm0,xmm1", 0xC4, 0xE1, 0x79, 0xEE, 0xC1 );
	// VEX.NDS.256.66.0F.WIG EE /r VPMAXSW ymm1,ymm2,ymm3/m256
	_TEST64_VEX( "c4e17dee00 vpmaxsw ymm0,ymm0,ymmword ptr [rax]", 0xC4, 0xE1, 0x7D, 0xEE, 0x00 );
	_TEST32_VEX( "c4e17deec1 vpmaxsw ymm0,ymm0,ymm1", 0xC4, 0xE1, 0x7D, 0xEE, 0xC1 );

	// PMAXSD
	// 66 0F 38 3D /r PMAXSD xmm1,xmm2/m128
	_TEST64( "660f383d00 pmaxsd xmm0,oword ptr [rax]", 0x66, 0x0F, 0x38, 0x3D, 0x00 );
	_TEST32( "660f383dc1 pmaxsd xmm0,xmm1", 0x66, 0x0F, 0x38, 0x3D, 0xC1 );
	// VEX.NDS.128.66.0F38.WIG 3D /r VPMAXSD xmm1,xmm2,xmm3/m128
	_TEST64_VEX( "c4e2793d00 vpmaxsd xmm0,xmm0,oword ptr [rax]", 0xC4, 0xE2, 0x79, 0x3D, 0x00 );
	_TEST32_VEX( "c4e2793dc1 vpmaxsd xmm0,xmm0,xmm1", 0xC4, 0xE2, 0x79, 0x3D, 0xC1 );
	// VEX.NDS.256.66.0F38.WIG 3D /r VPMAXSD ymm1,ymm2,ymm3/m256
	_TEST64_VEX( "c4e27d3d00 vpmaxsd ymm0,ymm0,ymmword ptr [rax]", 0xC4, 0xE2, 0x7D, 0x3D, 0x00 );
	_TEST32_VEX( "c4e27d3dc1 vpmaxsd ymm0,ymm0,ymm1", 0xC4, 0xE2, 0x7D, 0x3D, 0xC1 );

	// PMAXSB
	// 66 0F 38 3C /r PMAXSB xmm1,xmm2/m128
	_TEST64( "660f383c00 pmaxsb xmm0,oword ptr [rax]", 0x66, 0x0F, 0x38, 0x3C, 0x00 );
	_TEST32( "660f383cc1 pmaxsb xmm0,xmm1", 0x66, 0x0F, 0x38, 0x3C, 0xC1 );
	// VEX.NDS.128.66.0F38.WIG 3C /r VPMAXSB xmm1,xmm2,xmm3/m128
	_TEST64_VEX( "c4e2793c00 vpmaxsb xmm0,xmm0,oword ptr [rax]", 0xC4, 0xE2, 0x79, 0x3C, 0x00 );
	_TEST32_VEX( "c4e2793cc1 vpmaxsb xmm0,xmm0,xmm1", 0xC4, 0xE2, 0x79, 0x3C, 0xC1 );
	// VEX.NDS.256.66.0F38.WIG 3C /r VPMAXSB ymm1,ymm2,ymm3/m256
	_TEST64_VEX( "c4e27d3c00 vpmaxsb ymm0,ymm0,ymmword ptr [rax]", 0xC4, 0xE2, 0x7D, 0x3C, 0x00 );
	_TEST32_VEX( "c4e27d3cc1 vpmaxsb ymm0,ymm0,ymm1", 0xC4, 0xE2, 0x7D, 0x3C, 0xC1 );

	// PMADDWD
	// 0F F5 /r PMADDWD mm,mm/m64
	_TEST64( "0ff500 pmaddwd mm0,qword ptr [rax]", 0x0F, 0xF5, 0x00 );
	_TEST32( "0ff5c1 pmaddwd mm0,mm1", 0x0F, 0xF5, 0xC1 );
	// 66 0F F5 /r PMADDWD xmm1,xmm2/m128
	_TEST64( "660ff500 pmaddwd xmm0,oword ptr [rax]", 0x66, 0x0F, 0xF5, 0x00 );
	_TEST32( "660ff5c1 pmaddwd xmm0,xmm1", 0x66, 0x0F, 0xF5, 0xC1 );
	// VEX.NDS.128.66.0F.WIG F5 /r VPMADDWD xmm1,xmm2,xmm3/m128
	_TEST64_VEX( "c4e179f500 vpmaddwd xmm0,xmm0,oword ptr [rax]", 0xC4, 0xE1, 0x79, 0xF5, 0x00 );
	_TEST32_VEX( "c4e179f5c1 vpmaddwd xmm0,xmm0,xmm1", 0xC4, 0xE1, 0x79, 0xF5, 0xC1 );
	// VEX.NDS.256.66.0F.WIG F5 /r VPMADDWD ymm1,ymm2,ymm3/m256
	_TEST64_VEX( "c4e17df500 vpmaddwd ymm0,ymm0,ymmword ptr [rax]", 0xC4, 0xE1, 0x7D, 0xF5, 0x00 );
	_TEST32_VEX( "c4e17df5c1 vpmaddwd ymm0,ymm0,ymm1", 0xC4, 0xE1, 0x7D, 0xF5, 0xC1 );


	// PMADDUBSW
	// 0F 38 04 /r PMADDUBSW mm1,mm2/m64
	_TEST64( "0f380400 pmaddubsw mm0,qword ptr [rax]", 0x0F, 0x38, 0x04, 0x00 );
	_TEST32( "0f3804c1 pmaddubsw mm0,mm1", 0x0F, 0x38, 0x04, 0xC1 );
	// 66 0F 38 04 /r PMADDUBSW xmm1,xmm2/m128
	_TEST64( "660f380400 pmaddubsw xmm0,oword ptr [rax]", 0x66, 0x0F, 0x38, 0x04, 0x00 );
	_TEST32( "660f3804c1 pmaddubsw xmm0,xmm1", 0x66, 0x0F, 0x38, 0x04, 0xC1 );
	// VEX.NDS.128.66.0F38.WIG 04 /r VPMADDUBSW xmm1,xmm2,xmm3/m128
	_TEST64_VEX( "c4e2790400 vpmaddubsw xmm0,xmm0,oword ptr [rax]", 0xC4, 0xE2, 0x79, 0x04, 0x00 );
	_TEST32_VEX( "c4e27904c1 vpmaddubsw xmm0,xmm0,xmm1", 0xC4, 0xE2, 0x79, 0x04, 0xC1 );
	// VEX.NDS.256.66.0F38.WIG 04 /r VPMADDUBSW ymm1,ymm2,ymm3/m256
	_TEST64_VEX( "c4e27d0400 vpmaddubsw ymm0,ymm0,ymmword ptr [rax]", 0xC4, 0xE2, 0x7D, 0x04, 0x00 );
	_TEST32_VEX( "c4e27d04c1 vpmaddubsw ymm0,ymm0,ymm1", 0xC4, 0xE2, 0x7D, 0x04, 0xC1 );

	// PINSRW
	// 0F C4 /r ib PINSRW mm,r32/m16,imm8
	_TEST64( "0fc400ff pinsrw mm0,word ptr [rax],0ffh", 0x0F, 0xC4, 0x00, 0xFF );
	_TEST32( "0fc4c1ff pinsrw mm0,ecx,0ffh", 0x0F, 0xC4, 0xC1, 0xFF );
	// 66 0F C4 /r ib PINSRW xmm,r32/m16,imm8
	_TEST64( "660fc400ff pinsrw xmm0,word ptr [rax],0ffh", 0x66, 0x0F, 0xC4, 0x00, 0xFF );
	_TEST32( "660fc4c1ff pinsrw xmm0,ecx,0ffh", 0x66, 0x0F, 0xC4, 0xC1, 0xFF );
	// VEX.NDS.128.66.0F.W0 C4 /r ib VPINSRW xmm1,xmm2,r32/m16,imm8
	_TEST64_VEX( "c4e179c400ff vpinsrw xmm0,xmm0,word ptr [rax],0ffh", 0xC4, 0xE1, 0x79, 0xC4, 0x00, 0xFF );
	_TEST32_VEX( "c4e179c4c1ff vpinsrw xmm0,xmm0,ecx,0ffh", 0xC4, 0xE1, 0x79, 0xC4, 0xC1, 0xFF );

	// PINSR
	// 66 0F 3A 20 /r ib PINSRB xmm1,r32/m8,imm8
	_TEST64( "660f3a2000ff pinsrb xmm0,byte ptr [rax],0ffh", 0x66, 0x0F, 0x3A, 0x20, 0x00, 0xFF );
	_TEST32( "660f3a20c1ff pinsrb xmm0,ecx,0ffh", 0x66, 0x0F, 0x3A, 0x20, 0xC1, 0xFF );
	// 66 0F 3A 22 /r ib PINSRD xmm1,r/m32,imm8
	_TEST64( "660f3a2200ff pinsrd xmm0,dword ptr [rax],0ffh", 0x66, 0x0F, 0x3A, 0x22, 0x00, 0xFF );
	_TEST32( "660f3a22c1ff pinsrd xmm0,ecx,0ffh", 0x66, 0x0F, 0x3A, 0x22, 0xC1, 0xFF );
	// 66 REX.W 0F 3A 22 /r ib PINSRQ xmm1,r/m64,imm8
	_TEST64( "66480f3a2200ff pinsrq xmm0,qword ptr [rax],0ffh", 0x66, 0x48, 0x0F, 0x3A, 0x22, 0x00, 0xFF );
	// VEX.NDS.128.66.0F3A.W0 20 /r ib VPINSRB xmm1,xmm2,r32/m8,imm8
	// VEX.NDS.128.66.0F3A.W0 22 /r ib VPINSRD xmm1,xmm2,r32/m32,imm8
	// VEX.NDS.128.66.0F3A.W1 22 /r ib VPINSRQ xmm1,xmm2,r64/m64,imm8
	_TEST64_VEX( "c4e3792000ff vpinsrb xmm0,xmm0,byte ptr [rax],0ffh", 0xC4, 0xE3, 0x79, 0x20, 0x00, 0xFF );
	_TEST32_VEX( "c4e37920c1ff vpinsrb xmm0,xmm0,ecx,0ffh", 0xC4, 0xE3, 0x79, 0x20, 0xC1, 0xFF );
	_TEST64_VEX( "c4e3792200ff vpinsrd xmm0,xmm0,dword ptr [rax],0ffh", 0xC4, 0xE3, 0x79, 0x22, 0x00, 0xFF );
	_TEST32_VEX( "c4e37922c1ff vpinsrd xmm0,xmm0,ecx,0ffh", 0xC4, 0xE3, 0x79, 0x22, 0xC1, 0xFF );
	_TEST64_VEX( "c4e3f92200ff vpinsrq xmm0,xmm0,qword ptr [rax],0ffh", 0xC4, 0xE3, 0xF9, 0x22, 0x00, 0xFF );

	// PHSUBSW
	// 0F 38 07 /r1 PHSUBSW mm1,mm2/m64
	_TEST64( "0f380700 phsubsw mm0,qword ptr [rax]", 0x0F, 0x38, 0x07, 0x00 );
	_TEST32( "0f3807c1 phsubsw mm0,mm1", 0x0F, 0x38, 0x07, 0xC1 );
	// 66 0F 38 07 /r PHSUBSW xmm1,xmm2/m128
	_TEST64( "660f380700 phsubsw xmm0,oword ptr [rax]", 0x66, 0x0F, 0x38, 0x07, 0x00 );
	_TEST32( "660f3807c1 phsubsw xmm0,xmm1", 0x66, 0x0F, 0x38, 0x07, 0xC1 );
	// VEX.NDS.128.66.0F38.WIG 07 /r VPHSUBSW xmm1,xmm2,xmm3/m128
	_TEST64_VEX( "c4e2790700 vphsubsw xmm0,xmm0,oword ptr [rax]", 0xC4, 0xE2, 0x79, 0x07, 0x00 );
	_TEST32_VEX( "c4e27907c1 vphsubsw xmm0,xmm0,xmm1", 0xC4, 0xE2, 0x79, 0x07, 0xC1 );
	// VEX.NDS.256.66.0F38.WIG 07 /r VPHSUBSW ymm1,ymm2,ymm3/m256
	_TEST64_VEX( "c4e27d0700 vphsubsw ymm0,ymm0,ymmword ptr [rax]", 0xC4, 0xE2, 0x7D, 0x07, 0x00 );
	_TEST32_VEX( "c4e27d07c1 vphsubsw ymm0,ymm0,ymm1", 0xC4, 0xE2, 0x7D, 0x07, 0xC1 );

	// PHSUBW
	// 0F 38 05 /r1 PHSUBW mm1,mm2/m64
	// 0F 38 06 /r PHSUBD mm1,mm2/m64
	_TEST64( "0f380500 phsubw mm0,qword ptr [rax]", 0x0F, 0x38, 0x05, 0x00 );
	_TEST32( "0f3805c1 phsubw mm0,mm1", 0x0F, 0x38, 0x05, 0xC1 );
	_TEST64( "0f380600 phsubd mm0,qword ptr [rax]", 0x0F, 0x38, 0x06, 0x00 );
	_TEST32( "0f3806c1 phsubd mm0,mm1", 0x0F, 0x38, 0x06, 0xC1 );
	// 66 0F 38 05 /r PHSUBW xmm1,xmm2/m128
	// 66 0F 38 06 /r PHSUBD xmm1,xmm2/m128
	_TEST64( "660f380500 phsubw xmm0,oword ptr [rax]", 0x66, 0x0F, 0x38, 0x05, 0x00 );
	_TEST32( "660f3805c1 phsubw xmm0,xmm1", 0x66, 0x0F, 0x38, 0x05, 0xC1 );
	_TEST64( "660f380600 phsubd xmm0,oword ptr [rax]", 0x66, 0x0F, 0x38, 0x06, 0x00 );
	_TEST32( "660f3806c1 phsubd xmm0,xmm1", 0x66, 0x0F, 0x38, 0x06, 0xC1 );
	// VEX.NDS.128.66.0F38.WIG 05 /r VPHSUBW xmm1,xmm2,xmm3/m128
	// VEX.NDS.128.66.0F38.WIG 06 /r VPHSUBD xmm1,xmm2,xmm3/m128
	_TEST64_VEX( "c4e2790500 vphsubw xmm0,xmm0,oword ptr [rax]", 0xC4, 0xE2, 0x79, 0x05, 0x00 );
	_TEST32_VEX( "c4e27905c1 vphsubw xmm0,xmm0,xmm1", 0xC4, 0xE2, 0x79, 0x05, 0xC1 );
	_TEST64_VEX( "c4e2790600 vphsubd xmm0,xmm0,oword ptr [rax]", 0xC4, 0xE2, 0x79, 0x06, 0x00 );
	_TEST32_VEX( "c4e27906c1 vphsubd xmm0,xmm0,xmm1", 0xC4, 0xE2, 0x79, 0x06, 0xC1 );
	// VEX.NDS.256.66.0F38.WIG 05 /r VPHSUBW ymm1,ymm2,ymm3/m256
	// VEX.NDS.256.66.0F38.WIG 06 /r VPHSUBD ymm1,ymm2,ymm3/m256
	_TEST64_VEX( "c4e27d0500 vphsubw ymm0,ymm0,ymmword ptr [rax]", 0xC4, 0xE2, 0x7D, 0x05, 0x00 );
	_TEST32_VEX( "c4e27d05c1 vphsubw ymm0,ymm0,ymm1", 0xC4, 0xE2, 0x7D, 0x05, 0xC1 );
	_TEST64_VEX( "c4e27d0600 vphsubd ymm0,ymm0,ymmword ptr [rax]", 0xC4, 0xE2, 0x7D, 0x06, 0x00 );
	_TEST32_VEX( "c4e27d06c1 vphsubd ymm0,ymm0,ymm1", 0xC4, 0xE2, 0x7D, 0x06, 0xC1 );

	// PHMINPOSUW
	// 66 0F 38 41 /r PHMINPOSUW xmm1,xmm2/m128
	_TEST64( "660f384100 phminposuw xmm0,oword ptr [rax]", 0x66, 0x0F, 0x38, 0x41, 0x00 );
	_TEST32( "660f3841c1 phminposuw xmm0,xmm1", 0x66, 0x0F, 0x38, 0x41, 0xC1 );
	// VEX.128.66.0F38.WIG 41 /r VPHMINPOSUW xmm1,xmm2/m128
	_TEST64_VEX( "c4e2794100 vphminposuw xmm0,oword ptr [rax]", 0xC4, 0xE2, 0x79, 0x41, 0x00 );
	_TEST32_VEX( "c4e27941c1 vphminposuw xmm0,xmm1", 0xC4, 0xE2, 0x79, 0x41, 0xC1 );

	// PHADDSW
	// 0F 38 03 /r PHADDSW mm1,mm2/m64
	_TEST64( "0f380300 phaddsw mm0,qword ptr [rax]", 0x0F, 0x38, 0x03, 0x00 );
	_TEST32( "0f3803c1 phaddsw mm0,mm1", 0x0F, 0x38, 0x03, 0xC1 );
	// 66 0F 38 03 /r PHADDSW xmm1,xmm2/m128
	_TEST64( "660f380300 phaddsw xmm0,oword ptr [rax]", 0x66, 0x0F, 0x38, 0x03, 0x00 );
	_TEST32( "660f3803c1 phaddsw xmm0,xmm1", 0x66, 0x0F, 0x38, 0x03, 0xC1 );
	// VEX.NDS.128.66.0F38.WIG 03 /r VPHADDSW xmm1,xmm2,xmm3/m128
	_TEST64_VEX( "c4e2790300 vphaddsw xmm0,xmm0,oword ptr [rax]", 0xC4, 0xE2, 0x79, 0x03, 0x00 );
	_TEST32_VEX( "c4e27903c1 vphaddsw xmm0,xmm0,xmm1", 0xC4, 0xE2, 0x79, 0x03, 0xC1 );
	// VEX.NDS.256.66.0F38.WIG 03 /r VPHADDSW ymm1,ymm2,ymm3/m256
	_TEST64_VEX( "c4e27d0300 vphaddsw ymm0,ymm0,ymmword ptr [rax]", 0xC4, 0xE2, 0x7D, 0x03, 0x00 );
	_TEST32_VEX( "c4e27d03c1 vphaddsw ymm0,ymm0,ymm1", 0xC4, 0xE2, 0x7D, 0x03, 0xC1 );


	// PHADDW
	// 0F 38 01 /r PHADDW mm1, mm2/m64
	// 0F 38 02 /r PHADDD mm1, mm2/m64
	_TEST64( "0f380100 phaddw mm0,qword ptr [rax]", 0x0F, 0x38, 0x01, 0x00 );
	_TEST32( "0f3801c1 phaddw mm0,mm1", 0x0F, 0x38, 0x01, 0xC1 );
	_TEST64( "0f380200 phaddd mm0,qword ptr [rax]", 0x0F, 0x38, 0x02, 0x00 );
	_TEST32( "0f3802c1 phaddd mm0,mm1", 0x0F, 0x38, 0x02, 0xC1 );
	// 66 0F 38 01 /r PHADDW xmm1, xmm2/m128
	// 66 0F 38 02 /r PHADDD xmm1, xmm2/m128
	_TEST64( "660f380100 phaddw xmm0,oword ptr [rax]", 0x66, 0x0F, 0x38, 0x01, 0x00 );
	_TEST32( "660f3801c1 phaddw xmm0,xmm1", 0x66, 0x0F, 0x38, 0x01, 0xC1 );
	_TEST64( "660f380200 phaddd xmm0,oword ptr [rax]", 0x66, 0x0F, 0x38, 0x02, 0x00 );
	_TEST32( "660f3802c1 phaddd xmm0,xmm1", 0x66, 0x0F, 0x38, 0x02, 0xC1 );
	// VEX.NDS.128.66.0F38.WIG 01 /r VPHADDW xmm1,xmm2,xmm3/m128
	// VEX.NDS.128.66.0F38.WIG 02 /r VPHADDD xmm1,xmm2,xmm3/m128
	_TEST64_VEX( "c4e2790100 vphaddw xmm0,xmm0,oword ptr [rax]", 0xC4, 0xE2, 0x79, 0x01, 0x00 );
	_TEST32_VEX( "c4e27901c1 vphaddw xmm0,xmm0,xmm1", 0xC4, 0xE2, 0x79, 0x01, 0xC1 );
	_TEST64_VEX( "c4e2790200 vphaddd xmm0,xmm0,oword ptr [rax]", 0xC4, 0xE2, 0x79, 0x02, 0x00 );
	_TEST32_VEX( "c4e27902c1 vphaddd xmm0,xmm0,xmm1", 0xC4, 0xE2, 0x79, 0x02, 0xC1 );
	// VEX.NDS.256.66.0F38.WIG 01 /r VPHADDW ymm1,ymm2,ymm3/m256
	// VEX.NDS.256.66.0F38.WIG 02 /r VPHADDD ymm1,ymm2,ymm3/m256
	_TEST64_VEX( "c4e27d0100 vphaddw ymm0,ymm0,ymmword ptr [rax]", 0xC4, 0xE2, 0x7D, 0x01, 0x00 );
	_TEST32_VEX( "c4e27d01c1 vphaddw ymm0,ymm0,ymm1", 0xC4, 0xE2, 0x7D, 0x01, 0xC1 );
	_TEST64_VEX( "c4e27d0200 vphaddd ymm0,ymm0,ymmword ptr [rax]", 0xC4, 0xE2, 0x7D, 0x02, 0x00 );
	_TEST32_VEX( "c4e27d02c1 vphaddd ymm0,ymm0,ymm1", 0xC4, 0xE2, 0x7D, 0x02, 0xC1 );

	// PEXTRW
	// TODO: WinDBG
	// 0F C5 /r ib PEXTRW reg,mm,imm8
	_TEST64( "0fc5c1ff pextrw rax,mm1,0ffh", 0x0F, 0xC5, 0xC1, 0xFF );
	_TEST32( "0fc5c1ff pextrw eax,mm1,0ffh", 0x0F, 0xC5, 0xC1, 0xFF );
	// 66 0F C5 /r ib PEXTRW reg,xmm,imm8
	_TEST64( "660fc5c1ff pextrw rax,xmm1,0ffh", 0x66, 0x0F, 0xC5, 0xC1, 0xFF );
	_TEST32( "660fc5c1ff pextrw eax,xmm1,0ffh", 0x66, 0x0F, 0xC5, 0xC1, 0xFF );
	// 66 0F 3A 15 /r ib PEXTRW reg/m16,xmm,imm8
	_TEST64( "660f3a1500ff pextrw word ptr [rax],xmm0,0ffh", 0x66, 0x0F, 0x3A, 0x15, 0x00, 0xFF );
	_TEST64( "660f3a15c1ff pextrw rcx,xmm0,0ffh", 0x66, 0x0F, 0x3A, 0x15, 0xC1, 0xFF );
	_TEST32( "660f3a1500ff pextrw word ptr [eax],xmm0,0ffh", 0x66, 0x0F, 0x3A, 0x15, 0x00, 0xFF );
	_TEST32( "660f3a15c1ff pextrw ecx,xmm0,0ffh", 0x66, 0x0F, 0x3A, 0x15, 0xC1, 0xFF );
	// VEX.128.66.0F.W0 C5 /r ib VPEXTRW reg,xmm1,imm8
	_TEST64_VEX( "c4e179c5c1ff vpextrw rax,xmm1,0ffh", 0xC4, 0xE1, 0x79, 0xC5, 0xC1, 0xFF );
	_TEST32_VEX( "c4e179c5c1ff vpextrw eax,xmm1,0ffh", 0xC4, 0xE1, 0x79, 0xC5, 0xC1, 0xFF );
	// VEX.128.66.0F3A.W0 15 /r ib VPEXTRW reg/m16,xmm2,imm8
	_TEST64_VEX( "c4e3791500ff vpextrw word ptr [rax],xmm0,0ffh", 0xC4, 0xE3, 0x79, 0x15, 0x00, 0xFF );
	_TEST64_VEX( "c4e37915c1ff vpextrw rcx,xmm0,0ffh", 0xC4,0xE3, 0x79, 0x15, 0xC1, 0xFF );
	_TEST32_VEX( "c4e3791500ff vpextrw word ptr [eax],xmm0,0ffh", 0xC4, 0xE3, 0x79, 0x15, 0x00, 0xFF );
	_TEST32_VEX( "c4e37915c1ff vpextrw ecx,xmm0,0ffh", 0xC4, 0xE3, 0x79, 0x15, 0xC1, 0xFF );

	// PEXTRB
	// TODO: WinDBG
	// 66 0F 3A 14 /r ib PEXTRB reg/m8,xmm2,imm8
	_TEST64( "660f3a1400ff pextrb byte ptr [rax],xmm0,0ffh", 0x66, 0x0F, 0x3A, 0x14, 0x00, 0xFF );
	_TEST64( "660f3a14c1ff pextrb rcx,xmm0,0ffh", 0x66, 0x0F, 0x3A, 0x14, 0xC1, 0xFF );
	_TEST32( "660f3a1400ff pextrb byte ptr [eax],xmm0,0ffh", 0x66, 0x0F, 0x3A, 0x14, 0x00, 0xFF );
	_TEST32( "660f3a14c1ff pextrb ecx,xmm0,0ffh", 0x66, 0x0F, 0x3A, 0x14, 0xC1, 0xFF );
	// 66 0F 3A 16 /r ib PEXTRD r/m32, xmm2, imm8
	_TEST64( "660f3a1600ff pextrd dword ptr [rax],xmm0,0ffh", 0x66, 0x0F, 0x3A, 0x16, 0x00, 0xFF );
	_TEST64( "660f3a16c1ff pextrd rcx,xmm0,0ffh", 0x66, 0x0F, 0x3A, 0x16, 0xC1, 0xFF );
	_TEST32( "660f3a1600ff pextrd dword ptr [eax],xmm0,0ffh", 0x66, 0x0F, 0x3A, 0x16, 0x00, 0xFF );
	_TEST32( "660f3a16c1ff pextrd ecx,xmm0,0ffh", 0x66, 0x0F, 0x3A, 0x16, 0xC1, 0xFF );
	// 66 REX.W 0F 3A 16 /r ib PEXTRQ r/m64, xmm2, imm8
	_TEST64( "66480f3a1600ff pextrq qword ptr [rax],xmm0,0ffh", 0x66, 0x48, 0x0F, 0x3A, 0x16, 0x00, 0xFF );
	_TEST64( "66480f3a16c1ff pextrq rcx,xmm0,0ffh", 0x66, 0x48, 0x0F, 0x3A, 0x16, 0xC1, 0xFF );
	// VEX.128.66.0F3A.W0 14 /r ib VPEXTRB reg/m8, xmm2, imm8
	_TEST64_VEX( "c4e3791400ff vpextrb byte ptr [rax],xmm0,0ffh", 0xC4, 0xE3, 0x79, 0x14, 0x00, 0xFF );
	_TEST64_VEX( "c4e37914c1ff vpextrb rcx,xmm0,0ffh", 0xC4, 0xE3, 0x79, 0x14, 0xC1, 0xFF );
	_TEST32_VEX( "c4e3791400ff vpextrb byte ptr [eax],xmm0,0ffh", 0xC4, 0xE3, 0x79, 0x14, 0x00, 0xFF );
	_TEST32_VEX( "c4e37914c1ff vpextrb ecx,xmm0,0ffh", 0xC4, 0xE3, 0x79, 0x14, 0xC1, 0xFF );
	// VEX.128.66.0F3A.W0 16 /r ib VPEXTRD r32/m32, xmm2, imm8
	_TEST64_VEX( "c4e3791600ff vpextrd dword ptr [rax],xmm0,0ffh", 0xC4, 0xE3, 0x79, 0x16, 0x00, 0xFF );
	_TEST64_VEX( "c4e37916c1ff vpextrd rcx,xmm0,0ffh", 0xC4, 0xE3, 0x79, 0x16, 0xC1, 0xFF );
	_TEST32_VEX( "c4e3791600ff vpextrd dword ptr [eax],xmm0,0ffh", 0xC4, 0xE3, 0x79, 0x16, 0x00, 0xFF );
	_TEST32_VEX( "c4e37916c1ff vpextrd ecx,xmm0,0ffh", 0xC4, 0xE3, 0x79, 0x16, 0xC1, 0xFF );
	// VEX.128.66.0F3A.W1 16 /r ib VPEXTRQ r64/m64, xmm2, imm8
	_TEST64_VEX( "c4e3f91600ff vpextrq qword ptr [rax],xmm0,0ffh", 0xC4, 0xE3, 0xF9, 0x16, 0x00, 0xFF );
	_TEST64_VEX( "c4e3f916c1ff vpextrq rcx,xmm0,0ffh", 0xC4, 0xE3, 0xF9, 0x16, 0xC1, 0xFF );

	// PCMPISTRM
	// 66 0F 3A 62 /r imm8 PCMPISTRM xmm1,xmm2/m128,imm8
	_TEST64_VEX( "660f3a6200ff pcmpistrm xmm0,oword ptr [rax],0ffh", 0x66, 0x0F, 0x3A, 0x62, 0x00, 0xFF );
	_TEST32_VEX( "660f3a62c1ff pcmpistrm xmm0,xmm1,0ffh", 0x66, 0x0F, 0x3A, 0x62, 0xC1, 0xFF );
	// VEX.128.66.0F3A.WIG 62 /r ib VPCMPISTRM xmm1,xmm2/m128,imm8
	_TEST64_VEX( "c4e3796200ff vpcmpistrm xmm0,oword ptr [rax],0ffh", 0xC4, 0xE3, 0x79, 0x62, 0x00, 0xFF );
	_TEST32_VEX( "c4e37962c1ff vpcmpistrm xmm0,xmm1,0ffh", 0xC4, 0xE3, 0x79, 0x62, 0xC1, 0xFF );

	// PCMPISTRI
	// 66 0F 3A 63 /r imm8 PCMPISTRI xmm1,xmm2/m128,imm8
	_TEST64_VEX( "660f3a6300ff pcmpistri xmm0,oword ptr [rax],0ffh", 0x66, 0x0F, 0x3A, 0x63, 0x00, 0xFF );
	_TEST32_VEX( "660f3a63c1ff pcmpistri xmm0,xmm1,0ffh", 0x66, 0x0F, 0x3A, 0x63, 0xC1, 0xFF );
	// VEX.128.66.0F3A.WIG 63 /r ib VPCMPISTRI xmm1,xmm2/m128,imm8
	_TEST64_VEX( "c4e3796300ff vpcmpistri xmm0,oword ptr [rax],0ffh", 0xC4, 0xE3, 0x79, 0x63, 0x00, 0xFF );
	_TEST32_VEX( "c4e37963c1ff vpcmpistri xmm0,xmm1,0ffh", 0xC4, 0xE3, 0x79, 0x63, 0xC1, 0xFF );

	// PCMPGTQ
	// 66 0F 38 37 /r PCMPGTQ xmm1,xmm2/m128
	_TEST64_VEX( "660f383700 pcmpgtq xmm0,oword ptr [rax]", 0x66, 0x0F, 0x38, 0x37, 0x00 );
	_TEST32_VEX( "660f3837c1 pcmpgtq xmm0,xmm1", 0x66, 0x0F, 0x38, 0x37, 0xC1 );
	// VEX.NDS.128.66.0F38.WIG 37 /r VPCMPGTQ xmm1,xmm2,xmm3/m128
	_TEST64_VEX( "c4e2793700 vpcmpgtq xmm0,xmm0,oword ptr [rax]", 0xC4, 0xE2, 0x79, 0x37, 0x00 );
	_TEST32_VEX( "c4e27937c1 vpcmpgtq xmm0,xmm0,xmm1", 0xC4, 0xE2, 0x79, 0x37, 0xC1 );
	// VEX.NDS.256.66.0F38.WIG 37 /r VPCMPGTQ ymm1,ymm2,ymm3/m256
	_TEST64_VEX( "c4e27d3700 vpcmpgtq ymm0,ymm0,ymmword ptr [rax]", 0xC4, 0xE2, 0x7D, 0x37, 0x00 );
	_TEST32_VEX( "c4e27d37c1 vpcmpgtq ymm0,ymm0,ymm1", 0xC4, 0xE2, 0x7D, 0x37, 0xC1 );

	// PCMPGT
	// 0F 64 /r1 PCMPGTB mm,mm/m64
	// 0F 65 /r1 PCMPGTW mm,mm/m64
	// 0F 66 /r1 PCMPGTD mm,mm/m64
	_TEST64( "0f6400 pcmpgtb mm0,qword ptr [rax]", 0x0F, 0x64, 0x00 );
	_TEST32( "0f64c1 pcmpgtb mm0,mm1", 0x0F, 0x64, 0xC1 );
	_TEST64( "0f6500 pcmpgtw mm0,qword ptr [rax]", 0x0F, 0x65, 0x00 );
	_TEST32( "0f65c1 pcmpgtw mm0,mm1", 0x0F, 0x65, 0xC1 );
	_TEST64( "0f6600 pcmpgtd mm0,qword ptr [rax]", 0x0F, 0x66, 0x00 );
	_TEST32( "0f66c1 pcmpgtd mm0,mm1", 0x0F, 0x66, 0xC1 );
	// 66 0F 64 /r PCMPGTB xmm1,xmm2/m128
	// 66 0F 65 /r PCMPGTW xmm1,xmm2/m128
	// 66 0F 66 /r PCMPGTD xmm1,xmm2/m128
	_TEST64_VEX( "660f6400 pcmpgtb xmm0,oword ptr [rax]", 0x66, 0x0F, 0x64, 0x00 );
	_TEST32_VEX( "660f64c1 pcmpgtb xmm0,xmm1", 0x66, 0x0F, 0x64, 0xC1 );
	_TEST64_VEX( "660f6500 pcmpgtw xmm0,oword ptr [rax]", 0x66, 0x0F, 0x65, 0x00 );
	_TEST32_VEX( "660f65c1 pcmpgtw xmm0,xmm1", 0x66, 0x0F, 0x65, 0xC1 );
	_TEST64_VEX( "660f6600 pcmpgtd xmm0,oword ptr [rax]", 0x66, 0x0F, 0x66, 0x00 );
	_TEST32_VEX( "660f66c1 pcmpgtd xmm0,xmm1", 0x66, 0x0F, 0x66, 0xC1 );
	// VEX.NDS.128.66.0F.WIG 64 /r VPCMPGTB xmm1,xmm2,xmm3/m128
	// VEX.NDS.128.66.0F.WIG 65 /r VPCMPGTW xmm1,xmm2,xmm3/m128
	// VEX.NDS.128.66.0F.WIG 66 /r VPCMPGTD xmm1,xmm2,xmm3/m128
	_TEST64_VEX( "c4e1796400 vpcmpgtb xmm0,xmm0,oword ptr [rax]", 0xC4, 0xE1, 0x79, 0x64, 0x00 );
	_TEST32_VEX( "c4e17964c1 vpcmpgtb xmm0,xmm0,xmm1", 0xC4, 0xE1, 0x79, 0x64, 0xC1 );
	_TEST64_VEX( "c4e1796500 vpcmpgtw xmm0,xmm0,oword ptr [rax]", 0xC4, 0xE1, 0x79, 0x65, 0x00 );
	_TEST32_VEX( "c4e17965c1 vpcmpgtw xmm0,xmm0,xmm1", 0xC4, 0xE1, 0x79, 0x65, 0xC1 );
	_TEST64_VEX( "c4e1796600 vpcmpgtd xmm0,xmm0,oword ptr [rax]", 0xC4, 0xE1, 0x79, 0x66, 0x00 );
	_TEST32_VEX( "c4e17966c1 vpcmpgtd xmm0,xmm0,xmm1", 0xC4, 0xE1, 0x79, 0x66, 0xC1 );
	// VEX.NDS.256.66.0F.WIG 64 /r VPCMPGTB ymm1,ymm2,ymm3/m256
	// VEX.NDS.256.66.0F.WIG 65 /r VPCMPGTW ymm1,ymm2,ymm3/m256
	// VEX.NDS.256.66.0F.WIG 66 /r VPCMPGTD ymm1,ymm2,ymm3/m256
	_TEST64_VEX( "c4e17d6400 vpcmpgtb ymm0,ymm0,ymmword ptr [rax]", 0xC4, 0xE1, 0x7D, 0x64, 0x00 );
	_TEST32_VEX( "c4e17d64c1 vpcmpgtb ymm0,ymm0,ymm1", 0xC4, 0xE1, 0x7D, 0x64, 0xC1 );
	_TEST64_VEX( "c4e17d6500 vpcmpgtw ymm0,ymm0,ymmword ptr [rax]", 0xC4, 0xE1, 0x7D, 0x65, 0x00 );
	_TEST32_VEX( "c4e17d65c1 vpcmpgtw ymm0,ymm0,ymm1", 0xC4, 0xE1, 0x7D, 0x65, 0xC1 );
	_TEST64_VEX( "c4e17d6600 vpcmpgtd ymm0,ymm0,ymmword ptr [rax]", 0xC4, 0xE1, 0x7D, 0x66, 0x00 );
	_TEST32_VEX( "c4e17d66c1 vpcmpgtd ymm0,ymm0,ymm1", 0xC4, 0xE1, 0x7D, 0x66, 0xC1 );

	// PCMPESTRM
	// 66 0F 3A 60 /r imm8 PCMPESTRM xmm1,xmm2/m128,imm8
	_TEST64_VEX( "660f3a6000ff pcmpestrm xmm0,oword ptr [rax],0ffh", 0x66, 0x0F, 0x3A, 0x60, 0x00, 0xFF );
	_TEST32_VEX( "660f3a60c1ff pcmpestrm xmm0,xmm1,0ffh", 0x66, 0x0F, 0x3A, 0x60, 0xC1, 0xFF );
	// VEX.128.66.0F3A.WIG 60 /r ib VPCMPESTRM xmm1,xmm2/m128,imm8
	_TEST64_VEX( "c4e3796000ff vpcmpestrm xmm0,oword ptr [rax],0ffh", 0xC4, 0xE3, 0x79, 0x60, 0x00, 0xFF );
	_TEST32_VEX( "c4e37960c1ff vpcmpestrm xmm0,xmm1,0ffh", 0xC4, 0xE3, 0x79, 0x60, 0xC1, 0xFF );

	// PCMPESTRI
	// 66 0F 3A 61 /r imm8 PCMPESTRI xmm1,xmm2/m128,imm8
	_TEST64_VEX( "660f3a6100ff pcmpestri xmm0,oword ptr [rax],0ffh", 0x66, 0x0F, 0x3A, 0x61, 0x00, 0xFF );
	_TEST32_VEX( "660f3a61c1ff pcmpestri xmm0,xmm1,0ffh", 0x66, 0x0F, 0x3A, 0x61, 0xC1, 0xFF );
	// VEX.128.66.0F3A.WIG 61 /r ib VPCMPESTRI xmm1,xmm2/m128,imm8
	_TEST64_VEX( "c4e3796100ff vpcmpestri xmm0,oword ptr [rax],0ffh", 0xC4, 0xE3, 0x79, 0x61, 0x00, 0xFF );
	_TEST32_VEX( "c4e37961c1ff vpcmpestri xmm0,xmm1,0ffh", 0xC4, 0xE3, 0x79, 0x61, 0xC1, 0xFF );

	// PCMPEQQ
	// 66 0F 38 29 /r PCMPEQQ xmm1,xmm2/m128
	_TEST64_VEX( "660f382900 pcmpeqq xmm0,oword ptr [rax]", 0x66, 0x0F, 0x38, 0x29, 0x00 );
	_TEST32_VEX( "660f3829c1 pcmpeqq xmm0,xmm1", 0x66, 0x0F, 0x38, 0x29, 0xC1 );
	// VEX.NDS.128.66.0F38.WIG 29 /r VPCMPEQQ xmm1,xmm2,xmm3/m128
	_TEST64_VEX( "c4e2792900 vpcmpeqq xmm0,xmm0,oword ptr [rax]", 0xC4, 0xE2, 0x79, 0x29, 0x00 );
	_TEST32_VEX( "c4e27929c1 vpcmpeqq xmm0,xmm0,xmm1", 0xC4, 0xE2, 0x79, 0x29, 0xC1 );
	// VEX.NDS.256.66.0F38.WIG 29 /r VPCMPEQQ ymm1,ymm2,ymm3/m256
	_TEST64_VEX( "c4e27d2900 vpcmpeqq ymm0,ymm0,ymmword ptr [rax]", 0xC4, 0xE2, 0x7D, 0x29, 0x00 );
	_TEST32_VEX( "c4e27d29c1 vpcmpeqq ymm0,ymm0,ymm1", 0xC4, 0xE2, 0x7D, 0x29, 0xC1 );

	// PCMPEQ
	// 0F 74 /r1 PCMPEQB mm,mm/m64
	// 0F 75 /r1 PCMPEQW mm,mm/m64
	// 0F 76 /r1 PCMPEQD mm,mm/m64
	_TEST64_VEX( "0f7400 pcmpeqb mm0,qword ptr [rax]", 0x0F, 0x74, 0x00 );
	_TEST32_VEX( "0f74c1 pcmpeqb mm0,mm1", 0x0F, 0x74, 0xC1 );
	_TEST64_VEX( "0f7500 pcmpeqw mm0,qword ptr [rax]", 0x0F, 0x75, 0x00 );
	_TEST32_VEX( "0f75c1 pcmpeqw mm0,mm1", 0x0F, 0x75, 0xC1 );
	_TEST64_VEX( "0f7600 pcmpeqd mm0,qword ptr [rax]", 0x0F, 0x76, 0x00 );
	_TEST32_VEX( "0f76c1 pcmpeqd mm0,mm1", 0x0F, 0x76, 0xC1 );
	// 66 0F 74 /r PCMPEQB xmm1,xmm2/m128
	// 66 0F 75 /r PCMPEQW xmm1,xmm2/m128
	// 66 0F 76 /r PCMPEQD xmm1,xmm2/m128
	_TEST64_VEX( "660f7400 pcmpeqb xmm0,oword ptr [rax]", 0x66, 0x0F, 0x74, 0x00 );
	_TEST32_VEX( "660f74c1 pcmpeqb xmm0,xmm1", 0x66, 0x0F, 0x74, 0xC1 );
	_TEST64_VEX( "660f7500 pcmpeqw xmm0,oword ptr [rax]", 0x66, 0x0F, 0x75, 0x00 );
	_TEST32_VEX( "660f75c1 pcmpeqw xmm0,xmm1", 0x66, 0x0F, 0x75, 0xC1 );
	_TEST64_VEX( "660f7600 pcmpeqd xmm0,oword ptr [rax]", 0x66, 0x0F, 0x76, 0x00 );
	_TEST32_VEX( "660f76c1 pcmpeqd xmm0,xmm1", 0x66, 0x0F, 0x76, 0xC1 );
	// VEX.NDS.128.66.0F.WIG 74 /r VPCMPEQB xmm1,xmm2,xmm3/m128
	// VEX.NDS.128.66.0F.WIG 75 /r VPCMPEQW xmm1,xmm2,xmm3/m128
	// VEX.NDS.128.66.0F.WIG 76 /r VPCMPEQD xmm1,xmm2,xmm3/m128
	_TEST64_VEX( "c4e1797400 vpcmpeqb xmm0,xmm0,oword ptr [rax]", 0xC4, 0xE1, 0x79, 0x74, 0x00 );
	_TEST32_VEX( "c4e17974c1 vpcmpeqb xmm0,xmm0,xmm1", 0xC4, 0xE1, 0x79, 0x74, 0xC1 );
	_TEST64_VEX( "c4e1797500 vpcmpeqw xmm0,xmm0,oword ptr [rax]", 0xC4, 0xE1, 0x79, 0x75, 0x00 );
	_TEST32_VEX( "c4e17975c1 vpcmpeqw xmm0,xmm0,xmm1", 0xC4, 0xE1, 0x79, 0x75, 0xC1 );
	_TEST64_VEX( "c4e1797600 vpcmpeqd xmm0,xmm0,oword ptr [rax]", 0xC4, 0xE1, 0x79, 0x76, 0x00 );
	_TEST32_VEX( "c4e17976c1 vpcmpeqd xmm0,xmm0,xmm1", 0xC4, 0xE1, 0x79, 0x76, 0xC1 );
	// VEX.NDS.256.66.0F.WIG 74 /r VPCMPEQB ymm1,ymm2,ymm3/m256
	// VEX.NDS.256.66.0F.WIG 75 /r VPCMPEQW ymm1,ymm2,ymm3/m256
	// VEX.NDS.256.66.0F.WIG 76 /r VPCMPEQD ymm1,ymm2,ymm3/m256
	_TEST64_VEX( "c4e17d7400 vpcmpeqb ymm0,ymm0,ymmword ptr [rax]", 0xC4, 0xE1, 0x7D, 0x74, 0x00 );
	_TEST32_VEX( "c4e17d74c1 vpcmpeqb ymm0,ymm0,ymm1", 0xC4, 0xE1, 0x7D, 0x74, 0xC1 );
	_TEST64_VEX( "c4e17d7500 vpcmpeqw ymm0,ymm0,ymmword ptr [rax]", 0xC4, 0xE1, 0x7D, 0x75, 0x00 );
	_TEST32_VEX( "c4e17d75c1 vpcmpeqw ymm0,ymm0,ymm1", 0xC4, 0xE1, 0x7D, 0x75, 0xC1 );
	_TEST64_VEX( "c4e17d7600 vpcmpeqd ymm0,ymm0,ymmword ptr [rax]", 0xC4, 0xE1, 0x7D, 0x76, 0x00 );
	_TEST32_VEX( "c4e17d76c1 vpcmpeqd ymm0,ymm0,ymm1", 0xC4, 0xE1, 0x7D, 0x76, 0xC1 );

	// PCLMULQDQ
	// 66 0F 3A 44 /r ib PCLMULQDQ xmm1,xmm2/m128,imm8
	_TEST64_VEX( "660f3a4400ff pclmulqdq xmm0,oword ptr [rax],0ffh", 0x66, 0x0F, 0x3A, 0x44, 0x00, 0xFF );
	_TEST32_VEX( "660f3a44c1ff pclmulqdq xmm0,xmm1,0ffh", 0x66, 0x0F, 0x3A, 0x44, 0xC1, 0xFF );
	// VEX.NDS.128.66.0F3A 44 /r ib VPCLMULQDQ xmm1,xmm2,xmm3/m128,imm8
	_TEST64_VEX( "c4e3794400ff vpclmulqdq xmm0,xmm0,oword ptr [rax],0ffh", 0xC4, 0xE3, 0x79, 0x44, 0x00, 0xFF );
	_TEST32_VEX( "c4e37944c1ff vpclmulqdq xmm0,xmm0,xmm1,0ffh", 0xC4, 0xE3, 0x79, 0x44, 0xC1, 0xFF );

	// PBLENDW
	// 66 0F 3A 0E /r ib PBLENDW xmm1,xmm2/m128,imm8
	_TEST64_VEX( "660f3a0e00ff pblendw xmm0,oword ptr [rax],0ffh", 0x66, 0x0F, 0x3A, 0x0E, 0x00, 0xFF );
	_TEST32_VEX( "660f3a0ec1ff pblendw xmm0,xmm1,0ffh", 0x66, 0x0F, 0x3A, 0x0E, 0xC1, 0xFF );
	// VEX.NDS.128.66.0F3A 0E /r ib VPBLENDW xmm1,xmm2,xmm3/m128,imm8
	_TEST64_VEX( "c4e3790e00ff vpblendw xmm0,xmm0,oword ptr [rax],0ffh", 0xC4, 0xE3, 0x79, 0x0E, 0x00, 0xFF );
	_TEST32_VEX( "c4e3790ec1ff vpblendw xmm0,xmm0,xmm1,0ffh", 0xC4, 0xE3, 0x79, 0x0E, 0xC1, 0xFF );
	// VEX.NDS.256.66.0F3A.WIG 0E /r ib VPBLENDW ymm1,ymm2,ymm3/m256,imm8
	_TEST64_VEX( "c4e37d0e00ff vpblendw ymm0,ymm0,ymmword ptr [rax],0ffh", 0xC4, 0xE3, 0x7D, 0x0E, 0x00, 0xFF );
	_TEST32_VEX( "c4e37d0ec1ff vpblendw ymm0,ymm0,ymm1,0ffh", 0xC4, 0xE3, 0x7D, 0x0E, 0xC1, 0xFF );

	// VPBLENDD
	// VEX.NDS.128.66.0F3A.W0 02 /r ib VPBLENDD xmm1,xmm2,xmm3/m128,imm8
	_TEST64_VEX( "c4e3790200ff vpblendd xmm0,xmm0,oword ptr [rax],0ffh", 0xC4, 0xE3, 0x79, 0x02, 0x00, 0xFF );
	_TEST32_VEX( "c4e37902c1ff vpblendd xmm0,xmm0,xmm1,0ffh", 0xC4, 0xE3, 0x79, 0x02, 0xC1, 0xFF );
	// VEX.NDS.256.66.0F3A.W0 02 /r ib VPBLENDD ymm1,ymm2,ymm3/m256,imm8
	_TEST64_VEX( "c4e37d0200ff vpblendd ymm0,ymm0,ymmword ptr [rax],0ffh", 0xC4, 0xE3, 0x7D, 0x02, 0x00, 0xFF );
	_TEST32_VEX( "c4e37d02c1ff vpblendd ymm0,ymm0,ymm1,0ffh", 0xC4, 0xE3, 0x7D, 0x02, 0xC1, 0xFF );

	// PBLENDVB
	// 66 0F 38 10 /r PBLENDVB xmm1,xmm2/m128,<XMM0>
	_TEST32( "660f38101401 pblendvb xmm2,oword ptr [ecx+eax],xmm0", 0x66, 0x0F, 0x38, 0x10, 0x14, 0x01, 0xFF );
	_TEST64( "660f38101401 pblendvb xmm2,oword ptr [rcx+rax],xmm0", 0x66, 0x0F, 0x38, 0x10, 0x14, 0x01, 0xFF );
	// VEX.NDS.128.66.0F3A 4C /r /is4 VPBLENDVB xmm1,xmm2,xmm3/m128,xmm4
	_TEST32_VEX( "c4c3414c1401 vpblendvb xmm2,xmm7,oword ptr [ecx+eax],xmm2", 0xC4, 0xC3, 0x41, 0x4C, 0x14, 0x01, 0x20 );
	_TEST32_VEX( "c4c3694c1401 vpblendvb xmm2,xmm2,oword ptr [ecx+eax],xmm2", 0xC4, 0xC3, 0x69, 0x4C, 0x14, 0x01, 0x20 );
	_TEST64_VEX( "c4c3694c1401 vpblendvb xmm2,xmm2,oword ptr [r9+rax],xmm10", 0xC4, 0xC3, 0x69, 0x4C, 0x14, 0x01, 0xA0 );
	// VEX.NDS.256.66.0F3A.W0 4C /r /is4 VPBLENDVB ymm1,ymm2,ymm3/m256,ymm4
	_TEST32_VEX( "c4c3454c1401 vpblendvb ymm2,ymm7,ymmword ptr [ecx+eax],ymm2", 0xC4, 0xC3, 0x45, 0x4C, 0x14, 0x01, 0x20 );
	_TEST64_VEX( "c4c36d4c1401 vpblendvb ymm2,ymm2,ymmword ptr [r9+rax],ymm10", 0xC4, 0xC3, 0x6D, 0x4C, 0x14, 0x01, 0xA0 );

	// PAVGB
	// 0F E0 /r1 PAVGB mm1,mm2/m64
	_TEST64_VEX( "0fe000 pavgb mm0,qword ptr [rax]", 0x0F, 0xE0, 0x00 );
	_TEST32_VEX( "0fe0c1 pavgb mm0,mm1", 0x0F, 0xE0, 0xC1 );
	// 0F E3 /r1 PAVGW mm1,mm2/m64
	_TEST64_VEX( "0fe300 pavgw mm0,qword ptr [rax]", 0x0F, 0xE3, 0x00 );
	_TEST32_VEX( "0fe3c1 pavgw mm0,mm1", 0x0F, 0xE3, 0xC1 );
	// 66 0F E0, /r PAVGB xmm1,xmm2/m128
	_TEST64_VEX( "660fe000 pavgb xmm0,oword ptr [rax]", 0x66, 0x0F, 0xE0, 0x00 );
	_TEST32_VEX( "660fe0c1 pavgb xmm0,xmm1", 0x66, 0x0F, 0xE0, 0xC1 );
	// 66 0F E3 /r PAVGW xmm1,xmm2/m128
	_TEST64_VEX( "660fe300 pavgw xmm0,oword ptr [rax]", 0x66, 0x0F, 0xE3, 0x00 );
	_TEST32_VEX( "660fe3c1 pavgw xmm0,xmm1", 0x66, 0x0F, 0xE3, 0xC1 );
	// VEX.NDS.128.66.0F.WIG E0 /r VPAVGB xmm1,xmm2,xmm3/m128
	// VEX.NDS.128.66.0F.WIG E3 /r VPAVGW xmm1,xmm2,xmm3/m128
	_TEST64_VEX( "c4e179e000 vpavgb xmm0,xmm0,oword ptr [rax]", 0xC4, 0xE1, 0x79, 0xE0, 0x00 );
	_TEST32_VEX( "c4e179e0c1 vpavgb xmm0,xmm0,xmm1", 0xC4, 0xE1, 0x79, 0xE0, 0xC1 );
	_TEST64_VEX( "c4e179e300 vpavgw xmm0,xmm0,oword ptr [rax]", 0xC4, 0xE1, 0x79, 0xE3, 0x00 );
	_TEST32_VEX( "c4e179e3c1 vpavgw xmm0,xmm0,xmm1", 0xC4, 0xE1, 0x79, 0xE3, 0xC1 );

	// PAUSE
	// F3 90 PAUSE
	_TEST64( "f390 pause", 0xF3, 0x90 );

	// PANDN
	// 0F DF /r PANDN mm,mm/m64
	_TEST64_VEX( "0fdf00 pandn mm0,qword ptr [rax]", 0x0F, 0xDF, 0x00 );
	_TEST32_VEX( "0fdfc1 pandn mm0,mm1", 0x0F, 0xDF, 0xC1 );
	// 66 0F DF /r PANDN xmm1,xmm2/m128
	_TEST64_VEX( "660fdf00 pandn xmm0,oword ptr [rax]", 0x66, 0x0F, 0xDF, 0x00 );
	_TEST32_VEX( "660fdfc1 pandn xmm0,xmm1", 0x66, 0x0F, 0xDF, 0xC1 );
	// VEX.NDS.128.66.0F.WIG DF /r VPANDN xmm1,xmm2,xmm3/m128
	_TEST64_VEX( "c4e169df00 vpandn xmm0,xmm2,oword ptr [rax]", 0xC4, 0xE1, 0x69, 0xDF, 0x00 );
	_TEST32_VEX( "c4e169dfc1 vpandn xmm0,xmm2,xmm1", 0xC4, 0xE1, 0x69, 0xDF, 0xC1 );
	// VEX.NDS.256.66.0F.WIG DF /r VPANDN ymm1,ymm2,ymm3/m256
	_TEST64_VEX( "c4e16ddf00 vpandn ymm0,ymm2,ymmword ptr [rax]", 0xC4, 0xE1, 0x6D, 0xDF, 0x00 );
	_TEST32_VEX( "c4e16ddfc1 vpandn ymm0,ymm2,ymm1", 0xC4, 0xE1, 0x6D, 0xDF, 0xC1 );

	// PAND
	// 0F DB /r PAND mm,mm/m64
	_TEST64_VEX( "0fdb00 pand mm0,qword ptr [rax]", 0x0F, 0xDB, 0x00 );
	_TEST32_VEX( "0fdbc1 pand mm0,mm1", 0x0F, 0xDB, 0xC1 );
	// 66 0F DB /r PAND xmm1,xmm2/m128
	_TEST64_VEX( "660fdb00 pand xmm0,oword ptr [rax]", 0x66, 0x0F, 0xDB, 0x00 );
	_TEST32_VEX( "660fdbc1 pand xmm0,xmm1", 0x66, 0x0F, 0xDB, 0xC1 );
	// VEX.NDS.128.66.0F.WIG DB /r VPAND xmm1,xmm2,xmm3/m128
	_TEST64_VEX( "c4e169db00 vpand xmm0,xmm2,oword ptr [rax]", 0xC4, 0xE1, 0x69, 0xDB, 0x00 );
	_TEST32_VEX( "c4e169dbc1 vpand xmm0,xmm2,xmm1", 0xC4, 0xE1, 0x69, 0xDB, 0xC1 );
	// VEX.NDS.256.66.0F.WIG DB /r VPAND ymm1,ymm2,ymm3/m256
	_TEST64_VEX( "c4e16ddb00 vpand ymm0,ymm2,ymmword ptr [rax]", 0xC4, 0xE1, 0x6D, 0xDB, 0x00 );
	_TEST32_VEX( "c4e16ddbc1 vpand ymm0,ymm2,ymm1", 0xC4, 0xE1, 0x6D, 0xDB, 0xC1 );

	// PALIGNR
	// 0F 3A 0F PALIGNR mm1,mm2/m64,imm8
	_TEST64_VEX( "0f3a0f00ff palignr mm0,qword ptr [rax],0ffh", 0x0F, 0x3A, 0x0F, 0x00, 0xFF );
	_TEST32_VEX( "0f3a0fc1ff palignr mm0,mm1,0ffh", 0x0F, 0x3A, 0x0F, 0xC1, 0xFF );
	// 66 0F 3A 0F PALIGNR xmm1,xmm2/m128,imm8
	_TEST64_VEX( "660f3a0f00ff palignr xmm0,oword ptr [rax],0ffh", 0x66, 0x0F, 0x3A, 0x0F, 0x00, 0xFF );
	_TEST32_VEX( "660f3a0fc1ff palignr xmm0,xmm1,0ffh", 0x66, 0x0F, 0x3A, 0x0F, 0xC1, 0xFF );
	// VEX.NDS.128.66.0F3A.WIG 0F /r ib VPALIGNR xmm1,xmm2,xmm3/m128,imm8
	_TEST64_VEX( "c4e3790f00ff vpalignr xmm0,xmm0,oword ptr [rax],0ffh", 0xC4, 0xE3, 0x79, 0x0F, 0x00, 0xFF );
	_TEST32_VEX( "c4e3790fc1ff vpalignr xmm0,xmm0,xmm1,0ffh", 0xC4, 0xE3, 0x79, 0x0F, 0xC1, 0xFF );
	// VEX.NDS.256.66.0F3A.WIG 0F /r ib VPALIGNR ymm1,ymm2,ymm3/m256,imm8
	_TEST64_VEX( "c4e37d0f00ff vpalignr ymm0,ymm0,ymmword ptr [rax],0ffh", 0xC4, 0xE3, 0x7D, 0x0F, 0x00, 0xFF );
	_TEST32_VEX( "c4e37d0fc1ff vpalignr ymm0,ymm0,ymm1,0ffh", 0xC4, 0xE3, 0x7D, 0x0F, 0xC1, 0xFF );

	// PADDUS
	// 0F DC /r1 PADDUSB mm,mm/m64
	_TEST64_VEX( "0fdc00 paddusb mm0,qword ptr [rax]", 0x0F, 0xDC, 0x00 );
	_TEST32_VEX( "0fdcc1 paddusb mm0,mm1", 0x0F, 0xDC, 0xC1 );
	// 0F DD /r1 PADDUSW mm,mm/m64
	_TEST64_VEX( "0fdd00 paddusw mm0,qword ptr [rax]", 0x0F, 0xDD, 0x00 );
	_TEST32_VEX( "0fddc1 paddusw mm0,mm1", 0x0F, 0xDD, 0xC1 );
	// 66 0F DC /r PADDUSB xmm1,xmm2/m128
	_TEST64_VEX( "660fdc00 paddusb xmm0,oword ptr [rax]", 0x66, 0x0F, 0xDC, 0x00 );
	_TEST32_VEX( "660fdcc1 paddusb xmm0,xmm1", 0x66, 0x0F, 0xDC, 0xC1 );
	// 66 0F DD /r PADDUSW xmm1,xmm2/m128
	_TEST64_VEX( "660fdd00 paddusw xmm0,oword ptr [rax]", 0x66, 0x0F, 0xDD, 0x00 );
	_TEST32_VEX( "660fddc1 paddusw xmm0,xmm1", 0x66, 0x0F, 0xDD, 0xC1 );
	// VEX.NDS.128.66.0F.WIG DC /r VPADDUSB xmm1,xmm2,xmm3/m128
	// VEX.NDS.128.66.0F.WIG DD /r VPADDUSW xmm1,xmm2,xmm3/m128
	_TEST64_VEX( "c4e179dc00 vpaddusb xmm0,xmm0,oword ptr [rax]", 0xC4, 0xE1, 0x79, 0xDC, 0x00 );
	_TEST32_VEX( "c4e179dcc1 vpaddusb xmm0,xmm0,xmm1", 0xC4, 0xE1, 0x79, 0xDC, 0xC1 );
	_TEST64_VEX( "c4e179dd00 vpaddusw xmm0,xmm0,oword ptr [rax]", 0xC4, 0xE1, 0x79, 0xDD, 0x00 );
	_TEST32_VEX( "c4e179ddc1 vpaddusw xmm0,xmm0,xmm1", 0xC4, 0xE1, 0x79, 0xDD, 0xC1 );
	// VEX.NDS.256.66.0F.WIG DC /r VPADDUSB ymm1,ymm2,ymm3/m256
	// VEX.NDS.256.66.0F.WIG DD /r VPADDUSW ymm1,ymm2,ymm3/m256
	_TEST64_VEX( "c4e17ddc00 vpaddusb ymm0,ymm0,ymmword ptr [rax]", 0xC4, 0xE1, 0x7D, 0xDC, 0x00 );
	_TEST32_VEX( "c4e17ddcc1 vpaddusb ymm0,ymm0,ymm1", 0xC4, 0xE1, 0x7D, 0xDC, 0xC1 );
	_TEST64_VEX( "c4e17ddd00 vpaddusw ymm0,ymm0,ymmword ptr [rax]", 0xC4, 0xE1, 0x7D, 0xDD, 0x00 );
	_TEST32_VEX( "c4e17dddc1 vpaddusw ymm0,ymm0,ymm1", 0xC4, 0xE1, 0x7D, 0xDD, 0xC1 );

	// PADDS
	// 0F EC /r1 PADDSB mm,mm/m64
	_TEST64_VEX( "0fec00 paddsb mm0,qword ptr [rax]", 0x0F, 0xEC, 0x00 );
	_TEST32_VEX( "0fecc1 paddsb mm0,mm1", 0x0F, 0xEC, 0xC1 );
	// 0F ED /r1 PADDSW mm,mm/m64
	_TEST64_VEX( "0fed00 paddsw mm0,qword ptr [rax]", 0x0F, 0xED, 0x00 );
	_TEST32_VEX( "0fedc1 paddsw mm0,mm1", 0x0F, 0xED, 0xC1 );
	// 66 0F EC /r PADDSB xmm1,xmm2/m128
	_TEST64_VEX( "660fec00 paddsb xmm0,oword ptr [rax]", 0x66, 0x0F, 0xEC, 0x00 );
	_TEST32_VEX( "660fecc1 paddsb xmm0,xmm1", 0x66, 0x0F, 0xEC, 0xC1 );
	// 66 0F ED /r PADDSW xmm1,xmm2/m128
	_TEST64_VEX( "660fed00 paddsw xmm0,oword ptr [rax]", 0x66, 0x0F, 0xED, 0x00 );
	_TEST32_VEX( "660fedc1 paddsw xmm0,xmm1", 0x66, 0x0F, 0xED, 0xC1 );
	// VEX.NDS.128.66.0F.WIG EC /r VPADDSB xmm1,xmm2,xmm3/m128
	// VEX.NDS.128.66.0F.WIG ED /r VPADDSW xmm1,xmm2,xmm3/m128
	_TEST64_VEX( "c4e179ec00 vpaddsb xmm0,xmm0,oword ptr [rax]", 0xC4, 0xE1, 0x79, 0xEC, 0x00 );
	_TEST32_VEX( "c4e179ecc1 vpaddsb xmm0,xmm0,xmm1", 0xC4, 0xE1, 0x79, 0xEC, 0xC1 );
	_TEST64_VEX( "c4e179ed00 vpaddsw xmm0,xmm0,oword ptr [rax]", 0xC4, 0xE1, 0x79, 0xED, 0x00 );
	_TEST32_VEX( "c4e179edc1 vpaddsw xmm0,xmm0,xmm1", 0xC4, 0xE1, 0x79, 0xED, 0xC1 );
	// VEX.NDS.256.66.0F.WIG EC /r VPADDSB ymm1,ymm2,ymm3/m256
	// VEX.NDS.256.66.0F.WIG ED /r VPADDSW ymm1,ymm2,ymm3/m256
	_TEST64_VEX( "c4e17dec00 vpaddsb ymm0,ymm0,ymmword ptr [rax]", 0xC4, 0xE1, 0x7D, 0xEC, 0x00 );
	_TEST32_VEX( "c4e17decc1 vpaddsb ymm0,ymm0,ymm1", 0xC4, 0xE1, 0x7D, 0xEC, 0xC1 );
	_TEST64_VEX( "c4e17ded00 vpaddsw ymm0,ymm0,ymmword ptr [rax]", 0xC4, 0xE1, 0x7D, 0xED, 0x00 );
	_TEST32_VEX( "c4e17dedc1 vpaddsw ymm0,ymm0,ymm1", 0xC4, 0xE1, 0x7D, 0xED, 0xC1 );


	// PADD
	// 0F FC /r1 PADDB mm,mm/m64
	// 0F FD /r1 PADDW mm,mm/m64
	// 0F FE /r1 PADDD mm,mm/m64
	_TEST64_VEX( "0ffc00 paddb mm0,qword ptr [rax]", 0x0F, 0xFC, 0x00 );
	_TEST32_VEX( "0ffcc1 paddb mm0,mm1", 0x0F, 0xFC, 0xC1 );
	_TEST64_VEX( "0ffd00 paddw mm0,qword ptr [rax]", 0x0F, 0xFD, 0x00 );
	_TEST32_VEX( "0ffdc1 paddw mm0,mm1", 0x0F, 0xFD, 0xC1 );
	_TEST64_VEX( "0ffe00 paddd mm0,qword ptr [rax]", 0x0F, 0xFE, 0x00 );
	_TEST32_VEX( "0ffec1 paddd mm0,mm1", 0x0F, 0xFE, 0xC1 );
	// 66 0F FC /r PADDB xmm1,xmm2/m128
	// 66 0F FD /r PADDW xmm1,xmm2/m128
	// 66 0F FE /r PADDD xmm1,xmm2/m128
	_TEST64_VEX( "660ffc00 paddb xmm0,oword ptr [rax]", 0x66, 0x0F, 0xFC, 0x00 );
	_TEST32_VEX( "660ffcc1 paddb xmm0,xmm1", 0x66, 0x0F, 0xFC, 0xC1 );
	_TEST64_VEX( "660ffd00 paddw xmm0,oword ptr [rax]", 0x66, 0x0F, 0xFD, 0x00 );
	_TEST32_VEX( "660ffdc1 paddw xmm0,xmm1", 0x66, 0x0F, 0xFD, 0xC1 );
	_TEST64_VEX( "660ffe00 paddd xmm0,oword ptr [rax]", 0x66, 0x0F, 0xFE, 0x00 );
	_TEST32_VEX( "660ffec1 paddd xmm0,xmm1", 0x66, 0x0F, 0xFE, 0xC1 );
	// VEX.NDS.128.66.0F.WIG FC /r VPADDB xmm1,xmm2,xmm3/m128
	// VEX.NDS.128.66.0F.WIG FD /r VPADDW xmm1,xmm2,xmm3/m128
	// VEX.NDS.128.66.0F.WIG FE /r VPADDD xmm1,xmm2,xmm3/m128
	_TEST64_VEX( "c4e179fc00 vpaddb xmm0,xmm0,oword ptr [rax]", 0xC4, 0xE1, 0x79, 0xFC, 0x00 );
	_TEST32_VEX( "c4e179fcc1 vpaddb xmm0,xmm0,xmm1", 0xC4, 0xE1, 0x79, 0xFC, 0xC1 );
	_TEST64_VEX( "c4e179fd00 vpaddw xmm0,xmm0,oword ptr [rax]", 0xC4, 0xE1, 0x79, 0xFD, 0x00 );
	_TEST32_VEX( "c4e179fdc1 vpaddw xmm0,xmm0,xmm1", 0xC4, 0xE1, 0x79, 0xFD, 0xC1 );
	_TEST64_VEX( "c4e179fe00 vpaddd xmm0,xmm0,oword ptr [rax]", 0xC4, 0xE1, 0x79, 0xFE, 0x00 );
	_TEST32_VEX( "c4e179fec1 vpaddd xmm0,xmm0,xmm1", 0xC4, 0xE1, 0x79, 0xFE, 0xC1 );
	// VEX.NDS.256.66.0F.WIG FC /r VPADDB ymm1,ymm2,ymm3/m256
	// VEX.NDS.256.66.0F.WIG FD /r VPADDW ymm1,ymm2,ymm3/m256
	// VEX.NDS.256.66.0F.WIG FE /r VPADDD ymm1,ymm2,ymm3/m256
	// VEX.NDS.256.66.0F.WIG D4 /r VPADDQ ymm1,ymm2,ymm3/m256
	_TEST64_VEX( "c4e17dfc00 vpaddb ymm0,ymm0,ymmword ptr [rax]", 0xC4, 0xE1, 0x7D, 0xFC, 0x00 );
	_TEST32_VEX( "c4e17dfcc1 vpaddb ymm0,ymm0,ymm1", 0xC4, 0xE1, 0x7D, 0xFC, 0xC1 );
	_TEST64_VEX( "c4e17dfd00 vpaddw ymm0,ymm0,ymmword ptr [rax]", 0xC4, 0xE1, 0x7D, 0xFD, 0x00 );
	_TEST32_VEX( "c4e17dfdc1 vpaddw ymm0,ymm0,ymm1", 0xC4, 0xE1, 0x7D, 0xFD, 0xC1 );
	_TEST64_VEX( "c4e17dfe00 vpaddd ymm0,ymm0,ymmword ptr [rax]", 0xC4, 0xE1, 0x7D, 0xFE, 0x00 );
	_TEST32_VEX( "c4e17dfec1 vpaddd ymm0,ymm0,ymm1", 0xC4, 0xE1, 0x7D, 0xFE, 0xC1 );
	_TEST64_VEX( "c4e17dd400 vpaddq ymm0,ymm0,ymmword ptr [rax]", 0xC4, 0xE1, 0x7D, 0xD4, 0x00 );
	_TEST32_VEX( "c4e17dd4c1 vpaddq ymm0,ymm0,ymm1", 0xC4, 0xE1, 0x7D, 0xD4, 0xC1 );


	// PACKUSW
	// 0F 67 /r1 PACKUSWB mm,mm/m64
	_TEST64_VEX( "0f6700 packuswb mm0,qword ptr [rax]", 0x0F, 0x67, 0x00 );
	_TEST32_VEX( "0f67c1 packuswb mm0,mm1", 0x0F, 0x67, 0xC1 );
	// 66 0F 67 /r PACKUSWB xmm1,xmm2/m128
	_TEST64_VEX( "660f6700 packuswb xmm0,oword ptr [rax]", 0x66, 0x0F, 0x67, 0x00 );
	_TEST32_VEX( "660f67c1 packuswb xmm0,xmm1", 0x66, 0x0F, 0x67, 0xC1 );
	// VEX.NDS.128.66.0F.WIG 67 /r VPACKUSWB xmm1,xmm2,xmm3/m128
	_TEST64_VEX( "c4e1616700 vpackuswb xmm0,xmm3,oword ptr [rax]", 0xC4, 0xE1, 0x61, 0x67, 0x00 );
	_TEST32_VEX( "c4e16167c1 vpackuswb xmm0,xmm3,xmm1", 0xC4, 0xE1, 0x61, 0x67, 0xC1 );
	// VEX.NDS.256.66.0F.WIG 67 /r VPACKUSWB ymm1,ymm2,ymm3/m256
	_TEST64_VEX( "c4e1656700 vpackuswb ymm0,ymm3,ymmword ptr [rax]", 0xC4, 0xE1, 0x65, 0x67, 0x00 );
	_TEST32_VEX( "c4e16567c1 vpackuswb ymm0,ymm3,ymm1", 0xC4, 0xE1, 0x65, 0x67, 0xC1 );

	// PACKUSD
	// 66 0F 38 2B /r PACKUSDW xmm1, xmm2/m128
	_TEST64_VEX( "660f382b00 packusdw xmm0,oword ptr [rax]", 0x66, 0x0F, 0x38, 0x2B, 0x00 );
	_TEST32_VEX( "660f382bc1 packusdw xmm0,xmm1", 0x66, 0x0F, 0x38, 0x2B, 0xC1 );
	// VEX.NDS.128.66.0F38.WIG 2B /r VPACKUSDW xmm1,xmm2,xmm3/m128
	_TEST64_VEX( "c4e2612b00 vpackusdw xmm0,xmm3,oword ptr [rax]", 0xC4, 0xE2, 0x61, 0x2B, 0x00 );
	_TEST32_VEX( "c4e2612bc1 vpackusdw xmm0,xmm3,xmm1", 0xC4, 0xE2, 0x61, 0x2B, 0xC1 );
	// VEX.NDS.256.66.0F38.WIG 2B /r VPACKUSDW ymm1,ymm2,ymm3/m256
	_TEST64_VEX( "c4e2652b00 vpackusdw ymm0,ymm3,ymmword ptr [rax]", 0xC4, 0xE2, 0x65, 0x2B, 0x00 );
	_TEST32_VEX( "c4e2652bc1 vpackusdw ymm0,ymm3,ymm1", 0xC4, 0xE2, 0x65, 0x2B, 0xC1 );

	// PACKSS
	// 0F 63 /r1 PACKSSWB mm1, mm2/m64
	_TEST64_VEX( "0f6300 packsswb mm0,qword ptr [rax]", 0x0F, 0x63, 0x00 );
	_TEST32_VEX( "0f63c1 packsswb mm0,mm1", 0x0F, 0x63, 0xC1 );
	// 0F 6B /r1 PACKSSDW mm1, mm2/m64
	_TEST64_VEX( "0f6b00 packssdw mm0,qword ptr [rax]", 0x0F, 0x6B, 0x00 );
	_TEST32_VEX( "0f6bc1 packssdw mm0,mm1", 0x0F, 0x6B, 0xC1 );
	// 66 0F 63 /r PACKSSWB xmm1, xmm2/m128
	// 66 0F 6B /r PACKSSDW xmm1, xmm2/m128
	_TEST64_VEX( "660f6300 packsswb xmm0,oword ptr [rax]", 0x66, 0x0F, 0x63, 0x00 );
	_TEST32_VEX( "660f63c1 packsswb xmm0,xmm1", 0x66, 0x0F, 0x63, 0xC1 );
	_TEST64_VEX( "660f6b00 packssdw xmm0,oword ptr [rax]", 0x66, 0x0F, 0x6b, 0x00 );
	_TEST32_VEX( "660f6bc1 packssdw xmm0,xmm1", 0x66, 0x0F, 0x6b, 0xC1 );
	// VEX.NDS.128.66.0F.WIG 63 /r VPACKSSWB xmm1,xmm2, xmm3/m128
	// VEX.NDS.128.66.0F.WIG 6B /r VPACKSSDW xmm1,xmm2, xmm3/m128
	_TEST64_VEX( "c4e1616300 vpacksswb xmm0,xmm3,oword ptr [rax]", 0xC4, 0xE1, 0x61, 0x63, 0x00 );
	_TEST32_VEX( "c4e16163c1 vpacksswb xmm0,xmm3,xmm1", 0xC4, 0xE1, 0x61, 0x63, 0xC1 );
	_TEST64_VEX( "c4e1616b00 vpackssdw xmm0,xmm3,oword ptr [rax]", 0xC4, 0xE1, 0x61, 0x6b, 0x00 );
	_TEST32_VEX( "c4e1616bc1 vpackssdw xmm0,xmm3,xmm1", 0xC4, 0xE1, 0x61, 0x6b, 0xC1 );
	// VEX.NDS.256.66.0F.WIG 63 /r VPACKSSWB ymm1,ymm2,ymm3/m256
	// VEX.NDS.256.66.0F.WIG 6B /r VPACKSSDW ymm1,ymm2,ymm3/m256
	_TEST64_VEX( "c4e1656300 vpacksswb ymm0,ymm3,ymmword ptr [rax]", 0xC4, 0xE1, 0x65, 0x63, 0x00 );
	_TEST32_VEX( "c4e16563c1 vpacksswb ymm0,ymm3,ymm1", 0xC4, 0xE1, 0x65, 0x63, 0xC1 );
	_TEST64_VEX( "c4e1656b00 vpackssdw ymm0,ymm3,ymmword ptr [rax]", 0xC4, 0xE1, 0x65, 0x6b, 0x00 );
	_TEST32_VEX( "c4e1656bc1 vpackssdw ymm0,ymm3,ymm1", 0xC4, 0xE1, 0x65, 0x6b, 0xC1 );

	// PABS
	// 0F 38 1C /r1 PABSB mm1,mm2/m64
	// 0F 38 1D /r1 PABSW mm1,mm2/m64
	// 0F 38 1E /r1 PABSD mm1,mm2/m64
	_TEST64_VEX( "0f381c00 pabsb mm0,qword ptr [rax]", 0x0F, 0x38, 0x1C, 0x00 );
	_TEST32_VEX( "0f381cc1 pabsb mm0,mm1", 0x0F, 0x38, 0x1C, 0xC1 );
	_TEST64_VEX( "0f381d00 pabsw mm0,qword ptr [rax]", 0x0F, 0x38, 0x1D, 0x00 );
	_TEST32_VEX( "0f381dc1 pabsw mm0,mm1", 0x0F, 0x38, 0x1D, 0xC1 );
	_TEST64_VEX( "0f381e00 pabsd mm0,qword ptr [rax]", 0x0F, 0x38, 0x1E, 0x00 );
	_TEST32_VEX( "0f381ec1 pabsd mm0,mm1", 0x0F, 0x38, 0x1E, 0xC1 );
	// 66 0F 38 1C /r PABSB xmm1,xmm2/m128
	// 66 0F 38 1D /r PABSW xmm1,xmm2/m128
	// 66 0F 38 1E /r PABSD xmm1,xmm2/m128
	_TEST64_VEX( "660f381c00 pabsb xmm0,oword ptr [rax]", 0x66, 0x0F, 0x38, 0x1C, 0x00 );
	_TEST32_VEX( "660f381cc1 pabsb xmm0,xmm1", 0x66, 0x0F, 0x38, 0x1C, 0xC1 );
	_TEST64_VEX( "660f381d00 pabsw xmm0,oword ptr [rax]", 0x66, 0x0F, 0x38, 0x1D, 0x00 );
	_TEST32_VEX( "660f381dc1 pabsw xmm0,xmm1", 0x66, 0x0F, 0x38, 0x1D, 0xC1 );
	_TEST64_VEX( "660f381e00 pabsd xmm0,oword ptr [rax]", 0x66, 0x0F, 0x38, 0x1E, 0x00 );
	_TEST32_VEX( "660f381ec1 pabsd xmm0,xmm1", 0x66, 0x0F, 0x38, 0x1E, 0xC1 );
	// VEX.128.66.0F38 1C /r VPABSB xmm1,xmm2/m128
	// VEX.128.66.0F38 1D /r VPABSW xmm1,xmm2/m128
	// VEX.128.66.0F38 1E /r VPABSD xmm1,xmm2/m128
	_TEST64_VEX( "c4e2791c00 vpabsb xmm0,oword ptr [rax]", 0xC4, 0xE2, 0x79, 0x1C, 0x00 );
	_TEST32_VEX( "c4e2791cc1 vpabsb xmm0,xmm1", 0xC4, 0xE2, 0x79, 0x1C, 0xC1 );
	_TEST64_VEX( "c4e2791d00 vpabsw xmm0,oword ptr [rax]", 0xC4, 0xE2, 0x79, 0x1D, 0x00 );
	_TEST32_VEX( "c4e2791dc1 vpabsw xmm0,xmm1", 0xC4, 0xE2, 0x79, 0x1D, 0xC1 );
	_TEST64_VEX( "c4e2791e00 vpabsd xmm0,oword ptr [rax]", 0xC4, 0xE2, 0x79, 0x1E, 0x00 );
	_TEST32_VEX( "c4e2791ec1 vpabsd xmm0,xmm1", 0xC4, 0xE2, 0x79, 0x1E, 0xC1 );
	// VEX.256.66.0F38.WIG 1C /r VPABSB ymm1, ymm2/m256
	// VEX.256.66.0F38.WIG 1D /r VPABSW ymm1, ymm2/m256
	// VEX.256.66.0F38.WIG 1E /r VPABSD ymm1, ymm2/m256
	_TEST64_VEX( "c4e27d1c00 vpabsb ymm0,ymmword ptr [rax]", 0xC4, 0xE2, 0x7D, 0x1C, 0x00 );
	_TEST32_VEX( "c4e27d1cc1 vpabsb ymm0,ymm1", 0xC4, 0xE2, 0x7D, 0x1C, 0xC1 );
	_TEST64_VEX( "c4e27d1d00 vpabsw ymm0,ymmword ptr [rax]", 0xC4, 0xE2, 0x7D, 0x1D, 0x00 );
	_TEST32_VEX( "c4e27d1dc1 vpabsw ymm0,ymm1", 0xC4, 0xE2, 0x7D, 0x1D, 0xC1 );
	_TEST64_VEX( "c4e27d1e00 vpabsd ymm0,ymmword ptr [rax]", 0xC4, 0xE2, 0x7D, 0x1E, 0x00 );
	_TEST32_VEX( "c4e27d1ec1 vpabsd ymm0,ymm1", 0xC4, 0xE2, 0x7D, 0x1E, 0xC1 );

	// OUTS
	// 6E OUTS DX, m8 NP Valid Valid Output byte from memory location specified in DS:(E)SI or RSI to I/O port specified in DX.
	_TEST32( "6e outs dx,byte ptr [edi]", 0x6e );
	_TEST64( "6e outs dx,byte ptr [rdi]", 0x6e );
	_TEST64( "676e outs dx,byte ptr [edi]", 0x67, 0x6e );
	// 6F OUTS DX, m16 NP Valid Valid Output word from memory location specified in DS:(E)SI or RSI to I/O port specified in DX.
	// 6F OUTS DX, m32 NP Valid Valid Output doubleword from memory location specified in DS:(E)SI or RSI to I/O port specified in DX.
	_TEST32( "6f outs dx,dword ptr [edi]", 0x6f );
	_TEST64( "6f outs dx,dword ptr [rdi]", 0x6f );
	_TEST64( "676f outs dx,dword ptr [edi]", 0x67, 0x6f );
	_TEST64( "67666f outs dx,word ptr [edi]", 0x67, 0x66, 0x6f );
	_TEST64( "486f outs dx,dword ptr [rdi]", 0x48, 0x6f );

	// E6 ib OUT imm8, AL I Valid Valid Output byte in AL to I/O port address imm8.
	// E7 ib OUT imm8, AX I Valid Valid Output word in AX to I/O port address imm8.
	// E7 ib OUT imm8, EAX I Valid Valid Output doubleword in EAX to I/O port address imm8.
	_TEST64( "66e620 out 20h,al", 0x66, 0xE6, 0x20 );
	_TEST32( "e720 out 20h,eax", 0xE7, 0x20 );
	_TEST32( "66e720 out 20h,ax", 0x66, 0xE7, 0x20 );
	_TEST64( "48e720 out 20h,eax", 0x48, 0xE7, 0x20 );
	// EE OUT DX, AL NP Valid Valid Output byte in AL to I/O port address in DX.
	// EF OUT DX, AX NP Valid Valid Output word in AX to I/O port address in DX.
	// EF OUT DX, EAX NP Valid Valid Output doubleword in EAX to I/O port address in DX.
	_TEST32( "ee out dx,al", 0xEE, 0x20 );
	_TEST64( "66ee out dx,al", 0x66, 0xEE, 0x20 );
	_TEST32( "ef out dx,eax", 0xEF, 0x20 );
	_TEST32( "66ef out dx,ax", 0x66, 0xEF, 0x20 );
	_TEST64( "48ef out dx,eax", 0x48, 0xEF, 0x20 );

	// ORPS
	// 0F 56 /r ORPS xmm1, xmm2/m128
	_TEST32( "0f5610 orps xmm2,oword ptr [eax]", 0x0F, 0x56, 0x10 );
	_TEST32( "0f56d8 orps xmm3,xmm0", 0x0F, 0x56, 0xD8 );
	_TEST64( "0f5610 orps xmm2,oword ptr [rax]", 0x0F, 0x56, 0x10 );
	// VEX.NDS.128.0F 56 /r VORPS xmm1,xmm2,xmm3/m128
	// VEX.NDS.256.0F 56 /r VORPS ymm1,ymm2,ymm3/m256
	_TEST64_VEX( "c4e17056d8 vorps xmm3,xmm1,xmm0", 0xC4, 0xE1, 0x70, 0x56, 0xD8 );
	_TEST32_VEX( "c4e17c56d8 vorps ymm3,ymm0,ymm0", 0xC4, 0xE1, 0x7C, 0x56, 0xD8 );
	_TEST32_VEX( "c4e1645618 vorps ymm3,ymm3,ymmword ptr [eax]", 0xC4, 0xE1, 0x64, 0x56, 0x18 );

	// ORPD
	// 66 0F 56 /r ORPD xmm1,xmm2/m128
	_TEST32( "660f5610 orpd xmm2,oword ptr [eax]", 0x66, 0x0F, 0x56, 0x10 );
	_TEST32( "660f56d8 orpd xmm3,xmm0", 0x66, 0x0F, 0x56, 0xD8 );
	_TEST64( "660f5610 orpd xmm2,oword ptr [rax]", 0x66, 0x0F, 0x56, 0x10 );
	// VEX.NDS.128.66.0F 56 /r VORPD xmm1,xmm2,xmm3/m128
	// VEX.NDS.256.66.0F 56 /r VORPD ymm1,ymm2,ymm3/m256
	_TEST64_VEX( "c4e17156d8 vorpd xmm3,xmm1,xmm0", 0xC4, 0xE1, 0x71, 0x56, 0xD8 );
	_TEST32_VEX( "c4e17d56d8 vorpd ymm3,ymm0,ymm0", 0xC4, 0xE1, 0x7D, 0x56, 0xD8 );
	_TEST32_VEX( "c4e1655618 vorpd ymm3,ymm3,ymmword ptr [eax]", 0xC4, 0xE1, 0x65, 0x56, 0x18 );

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
	// VEX.NDS.128.F3.0F 59 /r VMULSS xmm1,xmm2,xmm3/m32
	_TEST64_VEX( "c4e16259d8 vmulss xmm3,xmm3,xmm0", 0xC4, 0xE1, 0x62, 0x59, 0xD8 );
	_TEST32_VEX( "c4e14259d8 vmulss xmm3,xmm7,xmm0", 0xC4, 0xE1, 0x42, 0x59, 0xD8 );
	_TEST32_VEX( "c4e17a5918 vmulss xmm3,xmm0,dword ptr [eax]", 0xC4, 0xE1, 0x7A, 0x59, 0x18 );

	// MULSD
	//F2 0F 59 /r MULSD xmm1,xmm2/m64
	_TEST32( "f20f5910 mulsd xmm2,qword ptr [eax]", 0xF2, 0x0F, 0x59, 0x10 );
	_TEST32( "f20f59d8 mulsd xmm3,xmm0", 0xF2, 0x0F, 0x59, 0xD8 );
	_TEST64( "f20f5910 mulsd xmm2,qword ptr [rax]", 0xF2, 0x0F, 0x59, 0x10 );
	// VEX.NDS.128.F2.0F 59 /r VMULSD xmm1,xmm2,xmm3/m64
	_TEST64_VEX( "c4e16359d8 vmulsd xmm3,xmm3,xmm0", 0xC4, 0xE1, 0x63, 0x59, 0xD8 );
	_TEST32_VEX( "c4e14359d8 vmulsd xmm3,xmm7,xmm0", 0xC4, 0xE1, 0x43, 0x59, 0xD8 );
	_TEST32_VEX( "c4e17b5918 vmulsd xmm3,xmm0,qword ptr [eax]", 0xC4, 0xE1, 0x7B, 0x59, 0x18 );

	// MULPS
	// 0F 59 /r MULPS xmm1,xmm2/m128
	_TEST32( "0f5910 mulps xmm2,oword ptr [eax]", 0x0F, 0x59, 0x10 );
	_TEST32( "0f59d8 mulps xmm3,xmm0", 0x0F, 0x59, 0xD8 );
	_TEST64( "0f5910 mulps xmm2,oword ptr [rax]", 0x0F, 0x59, 0x10 );
	// VEX.NDS.128.0F 59 /r VMULPS xmm1,xmm2,xmm3/m128
	// VEX.NDS.256.0F 59 /r VMULPS ymm1,ymm2,ymm3/m256
	_TEST64_VEX( "c4e17859d8 vmulps xmm3,xmm0,xmm0", 0xC4, 0xE1, 0x78, 0x59, 0xD8 );
	_TEST32_VEX( "c4e17c59d8 vmulps ymm3,ymm0,ymm0", 0xC4, 0xE1, 0x7C, 0x59, 0xD8 );
	_TEST32_VEX( "c4e1645918 vmulps ymm3,ymm3,ymmword ptr [eax]", 0xC4, 0xE1, 0x64, 0x59, 0x18 );

	// MULPD
	// 66 0F 59 /r MULPD xmm1,xmm2/m128
	_TEST32( "660f5910 mulpd xmm2,oword ptr [eax]", 0x66, 0x0F, 0x59, 0x10 );
	_TEST32( "660f59d8 mulpd xmm3,xmm0", 0x66, 0x0F, 0x59, 0xD8 );
	_TEST64( "660f5910 mulpd xmm2,oword ptr [rax]", 0x66, 0x0F, 0x59, 0x10 );
	// VEX.NDS.128.66.0F 59 /r VMULPD xmm1,xmm2,xmm3/m128
	// VEX.NDS.256.66.0F 59 /r VMULPD ymm1,ymm2,ymm3/m256
	_TEST64_VEX( "c4e17959d8 vmulpd xmm3,xmm0,xmm0", 0xC4, 0xE1, 0x79, 0x59, 0xD8 );
	_TEST32_VEX( "c4e17d59d8 vmulpd ymm3,ymm0,ymm0", 0xC4, 0xE1, 0x7D, 0x59, 0xD8 );
	_TEST32_VEX( "c4e1655918 vmulpd ymm3,ymm3,ymmword ptr [eax]", 0xC4, 0xE1, 0x65, 0x59, 0x18 );

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
	// VEX.NDS.128.66.0F3A 42 /r ib VMPSADBW xmm1,xmm2,xmm3/m128,imm8
	_TEST32_VEX( "c4e34942140120 vmpsadbw xmm2,xmm6,oword ptr [ecx+eax],20h", 0xC4, 0xE3, 0x49, 0x42, 0x14, 0x01, 0x20 );
	_TEST64_VEX( "c4e34942140120 vmpsadbw xmm2,xmm6,oword ptr [rcx+rax],20h", 0xC4, 0xE3, 0x49, 0x42, 0x14, 0x01, 0x20 );
	// VEX.NDS.256.66.0F3A.WIG 42 /r ib VMPSADBW ymm1,ymm2,ymm3/m256,imm8
	_TEST32_VEX( "c4e34d42140120 vmpsadbw ymm2,ymm6,ymmword ptr [ecx+eax],20h", 0xC4, 0xE3, 0x4D, 0x42, 0x14, 0x01, 0x20 );
	_TEST64_VEX( "c4e34d42140120 vmpsadbw ymm2,ymm6,ymmword ptr [rcx+rax],20h", 0xC4, 0xE3, 0x4D, 0x42, 0x14, 0x01, 0x20 );


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
	// VEX.128.0F 10 /r VMOVUPS xmm1,xmm2/m128
	// VEX.256.0F 10 /r VMOVUPS ymm1,ymm2/m256
	_TEST64_VEX( "c4e17810d8 vmovups xmm3,xmm0", 0xC4, 0xE1, 0x78, 0x10, 0xD8 );
	_TEST32_VEX( "c4e17810d8 vmovups xmm3,xmm0", 0xC4, 0xE1, 0x78, 0x10, 0xD8 );
	_TEST32_VEX( "c4e1781000 vmovups xmm0,oword ptr [eax]", 0xC4, 0xE1, 0x78, 0x10, 0x00 );
	// VEX.128.0F 11 /r VMOVUPS xmm2/m128,xmm1
	// VEX.256.0F 11 /r VMOVUPS ymm2/m256,ymm1
	_TEST64_VEX( "c4e17811d8 vmovups xmm0,xmm3", 0xC4, 0xE1, 0x78, 0x11, 0xD8 );
	_TEST32_VEX( "c4e17811d8 vmovups xmm0,xmm3", 0xC4, 0xE1, 0x78, 0x11, 0xD8 );
	_TEST32_VEX( "c4e1781100 vmovups oword ptr [eax],xmm0", 0xC4, 0xE1, 0x78, 0x11, 0x00 );

	// MOVUPD
	// 66 0F 10 /r MOVUPD xmm1,xmm2/m128
	_TEST32( "660f1010 movupd xmm2,oword ptr [eax]", 0x66, 0x0F, 0x10, 0x10 );
	_TEST32( "660f10d8 movupd xmm3,xmm0", 0x66, 0x0F, 0x10, 0xD8 );
	_TEST64( "660f1010 movupd xmm2,oword ptr [rax]", 0x66, 0x0F, 0x10, 0x10 );
	// 66 0F 11 /r MOVUPD xmm2/m128,xmm
	_TEST32( "660f1110 movupd oword ptr [eax],xmm2", 0x66, 0x0F, 0x11, 0x10 );
	_TEST32( "660f11d8 movupd xmm0,xmm3", 0x66, 0x0F, 0x11, 0xD8 );
	_TEST64( "660f1110 movupd oword ptr [rax],xmm2", 0x66, 0x0F, 0x11, 0x10 );
	// VEX.128.66.0F 10 /r VMOVUPD xmm1,xmm2/m128
	// VEX.256.66.0F 10 /r VMOVUPD ymm1,ymm2/m256
	_TEST64_VEX( "c4e17910d8 vmovupd xmm3,xmm0", 0xC4, 0xE1, 0x79, 0x10, 0xD8 );
	_TEST32_VEX( "c4e17910d8 vmovupd xmm3,xmm0", 0xC4, 0xE1, 0x79, 0x10, 0xD8 );
	_TEST32_VEX( "c4e1791000 vmovupd xmm0,oword ptr [eax]", 0xC4, 0xE1, 0x79, 0x10, 0x00 );
	// VEX.128.66.0F 11 /r VMOVUPD xmm2/m128,xmm1
	// VEX.256.66.0F 11 /r VMOVUPD ymm2/m256,ymm1
	_TEST64_VEX( "c4e17911d8 vmovupd xmm0,xmm3", 0xC4, 0xE1, 0x79, 0x11, 0xD8 );
	_TEST32_VEX( "c4e17911d8 vmovupd xmm0,xmm3", 0xC4, 0xE1, 0x79, 0x11, 0xD8 );
	_TEST32_VEX( "c4e1791100 vmovupd oword ptr [eax],xmm0", 0xC4, 0xE1, 0x79, 0x11, 0x00 );

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
	// VEX.NDS.128.F3.0F 10 /r VMOVSS xmm1,xmm2,xmm3
	_TEST32_VEX( "c4e16210c8 vmovss xmm1,xmm3,xmm0", 0xC4, 0xE1, 0x62, 0x10, 0xC8 );
	_TEST64_VEX( "c4e16210c8 vmovss xmm1,xmm3,xmm0", 0xC4, 0xE1, 0x62, 0x10, 0xC8 );
	// VEX.NDS.128.F3.0F 11 /r VMOVSS xmm1,xmm2,xmm3
	_TEST32_VEX( "c4e16211c8 vmovss xmm0,xmm3,xmm1", 0xC4, 0xE1, 0x62, 0x11, 0xC8 );
	_TEST64_VEX( "c4e16211c8 vmovss xmm0,xmm3,xmm1", 0xC4, 0xE1, 0x62, 0x11, 0xC8 );
	// VEX.128.F3.0F 10 /r VMOVSS xmm1,m32
	_TEST32_VEX( "c4e17a1000 vmovss xmm0,dword ptr [eax]", 0xC4, 0xE1, 0x7A, 0x10, 0x00 );
	// VEX.128.F3.0F 11 /r VMOVSS m32,xmm1
	_TEST32_VEX( "c4e17a1100 vmovss dword ptr [eax],xmm0", 0xC4, 0xE1, 0x7A, 0x11, 0x00 );

	// MOVSLDUP
	// F3 0F 12 /r MOVSLDUP xmm1,xmm2/m128
	_TEST32( "f30f1210 movsldup xmm2,oword ptr [eax]", 0xF3, 0x0F, 0x12, 0x10 );
	_TEST32( "f30f12d8 movsldup xmm3,xmm0", 0xF3, 0x0F, 0x12, 0xD8 );
	_TEST64( "f30f1210 movsldup xmm2,oword ptr [rax]", 0xF3, 0x0F, 0x12, 0x10 );
	// VEX.128.F3.0F 12 /r VMOVSLDUP xmm1,xmm2/m128
	// VEX.256.F3.0F 12 /r VMOVSLDUP ymm1,ymm2/m256
	_TEST64_VEX( "c4e17a12d8 vmovsldup xmm3,xmm0", 0xC4, 0xE1, 0x7A, 0x12, 0xD8 );
	_TEST32_VEX( "c4e17e1200 vmovsldup ymm0,ymmword ptr [eax]", 0xC4, 0xE1, 0x7E, 0x12, 0x00 );

	// MOVSHDUP
	// F3 0F 16 /r MOVSHDUP xmm1,xmm2/m128
	_TEST32( "f30f1610 movshdup xmm2,oword ptr [eax]", 0xF3, 0x0F, 0x16, 0x10 );
	_TEST32( "f30f16d8 movshdup xmm3,xmm0", 0xF3, 0x0F, 0x16, 0xD8 );
	_TEST64( "f30f1610 movshdup xmm2,oword ptr [rax]", 0xF3, 0x0F, 0x16, 0x10 );
	// VEX.128.F3.0F 16 /r VMOVSHDUP xmm1,xmm2/m128
	// VEX.256.F3.0F 16 /r VMOVSHDUP ymm1,ymm2/m256
	_TEST64_VEX( "c4e17a16d8 vmovshdup xmm3,xmm0", 0xC4, 0xE1, 0x7A, 0x16, 0xD8 );
	_TEST32_VEX( "c4e17e1600 vmovshdup ymm0,ymmword ptr [eax]", 0xC4, 0xE1, 0x7E, 0x16, 0x00 );

	// MOVSD
	// F2 0F 10 /r MOVSD xmm1,xmm2/m64
	_TEST32( "f20f1010 movsd xmm2,qword ptr [eax]", 0xF2, 0x0F, 0x10, 0x10 );
	_TEST32( "f20f10d8 movsd xmm3,xmm0", 0xF2, 0x0F, 0x10, 0xD8 );
	_TEST64( "f20f1010 movsd xmm2,qword ptr [rax]", 0xF2, 0x0F, 0x10, 0x10 );
	// F2 0F 11 /r MOVSD xmm2/m64, xmm1
	_TEST32( "f20f1110 movsd qword ptr [eax],xmm2", 0xF2, 0x0F, 0x11, 0x10 );
	_TEST32( "f20f11d8 movsd xmm0,xmm3", 0xF2, 0x0F, 0x11, 0xD8 );
	_TEST64( "f20f1110 movsd qword ptr [rax],xmm2", 0xF2, 0x0F, 0x11, 0x10 );
	// TODO: Sprawdzic, poniewaz instruckje sa identyczne, skad assembler mial by wiedziec
	// ktora wybrac? Moze jakis blad w dokuemtnacji. Najprawdopodobniej chiodzi o zrodlo i destination,
	// w pierwzym przypadku R - R/M a w drugim pewnie R/M - R. Tak czy inaczej dziwne...
	// VEX.NDS.128.F2.0F 10 /r VMOVSD xmm1, xmm2, xmm3
	_TEST32_VEX( "c4e16310c8 vmovsd xmm1,xmm3,xmm0", 0xC4, 0xE1, 0x63, 0x10, 0xC8 );
	_TEST64_VEX( "c4e16310c8 vmovsd xmm1,xmm3,xmm0", 0xC4, 0xE1, 0x63, 0x10, 0xC8 );
	// VEX.NDS.128.F2.0F 11 /r VMOVSD xmm1, xmm2, xmm3
	_TEST32_VEX( "c4e16311c8 vmovsd xmm0,xmm3,xmm1", 0xC4, 0xE1, 0x63, 0x11, 0xC8 );
	_TEST64_VEX( "c4e16311c8 vmovsd xmm0,xmm3,xmm1", 0xC4, 0xE1, 0x63, 0x11, 0xC8 );
	// VEX.128.F2.0F 10 /r VMOVSD xmm1, m64
	_TEST32_VEX( "c4e17b1000 vmovsd xmm0,qword ptr [eax]", 0xC4, 0xE1, 0x7B, 0x10, 0x00 );
	// VEX.128.F2.0F 11 /r VMOVSD m64, xmm1
	_TEST32_VEX( "c4e17b1100 vmovsd qword ptr [eax],xmm0", 0xC4, 0xE1, 0x7B, 0x11, 0x00 );

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
	// VEX.128.F3.0F 7E /r VMOVQ xmm1,xmm2
	// VEX.128.F3.0F 7E /r VMOVQ xmm1,m64
	_TEST32_VEX( "c4e17a7e00 vmovq xmm0,qword ptr [eax]", 0xC4, 0xE1, 0x7A, 0x7E, 0x00 );
	_TEST32_VEX( "c4e17a7ec0 vmovq xmm0,xmm0", 0xC4, 0xE1, 0x7A, 0x7E, 0xC0 );
	// VEX.128.66.0F D6 /r VMOVQ xmm1/m64,xmm2
	_TEST32_VEX( "c4e17ad600 vmovq qword ptr [eax],xmm0", 0xC4, 0xE1, 0x7A, 0xD6, 0x00 );
	_TEST32_VEX( "c4e17ad6c0 vmovq xmm0,xmm0", 0xC4, 0xE1, 0x7A, 0xD6, 0xC0 );

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
	// VEX.128.0F 2B /r VMOVNTPS m128, xmm1
	_TEST64_VEX( "c4e1782b00 vmovntps oword ptr [rax],xmm0", 0xC4, 0xE1, 0x78, 0x2B, 0x00 );
	_TEST32_VEX( "c4e1782b00 vmovntps oword ptr [eax],xmm0", 0xC4, 0xE1, 0x78, 0x2B, 0x00 );

	// MOVNTPD
	// 66 0F 2B /r MOVNTPD m128,xmm
	_TEST32( "660f2b00 movntpd oword ptr [eax],xmm0", 0x66, 0x0F, 0x2B, 0x00 );
	_TEST64( "660f2b00 movntpd oword ptr [rax],xmm0", 0x66, 0x0F, 0x2B, 0x00 );
	_TEST64( "66480f2b00 movntpd oword ptr [rax],xmm0", 0x66, 0x48, 0x0F, 0x2B, 0x00 );
	// VEX.128.66.0F 2B /r VMOVNTPD m128, xmm1
	_TEST64_VEX( "c4e1792b00 vmovntpd oword ptr [rax],xmm0", 0xC4, 0xE1, 0x79, 0x2B, 0x00 );

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
	// VEX.128.66.0F E7 /r VMOVNTDQ m128,xmm1
	_TEST64_VEX( "c4e179e700 vmovntdq oword ptr [rax],xmm0", 0xC4, 0xE1, 0x79, 0xE7, 0x00 );

	// MOVNTDQA
	// 66 0F 38 2A /r MOVNTDQA xmm1, m128
	_TEST32( "660f382a00 movntdqa xmm0,oword ptr [eax]", 0x66, 0x0F, 0x38, 0x2A, 0x00 );
	_TEST64( "660f382a00 movntdqa xmm0,oword ptr [rax]", 0x66, 0x0F, 0x38, 0x2A, 0x00 );
	_TEST64( "66480f382a00 movntdqa xmm0,oword ptr [rax]", 0x66, 0x48, 0x0F, 0x38, 0x2A, 0x00 );
	// VEX.128.66.0F38 2A /r VMOVNTDQA xmm1,m128
	_TEST64_VEX( "c4e2792a00 vmovntdqa xmm0,oword ptr [rax]", 0xC4, 0xE2, 0x79, 0x2A, 0x00 );
	// VEX.256.66.0F38.WIG 2A /r VMOVNTDQA ymm1,m256
	_TEST64_VEX( "c4e27d2a00 vmovntdqa ymm0,ymmword ptr [rax]", 0xC4, 0xE2, 0x7D, 0x2A, 0x00 );

	// MOVMSKPS
	// 0F 50 /r MOVMSKPS reg,xmm
	_TEST32( "0f50d0 movmskps edx,xmm0", 0x0F, 0x50, 0xD0 );
	_TEST32( "0f50d8 movmskps ebx,xmm0", 0x0F, 0x50, 0xD8 );
	_TEST64( "0f50d0 movmskps rdx,xmm0", 0x0F, 0x50, 0xD0 );
	_TEST64( "480f50d0 movmskps rdx,xmm0", 0x48, 0x0F, 0x50, 0xD0 );
	// VEX.128.0F 50 /r VMOVMSKPS reg,xmm2
	// VEX.256.0F 50 /r VMOVMSKPS reg,ymm2
	_TEST32_VEX( "c4e17850d0 vmovmskps edx,xmm0", 0xC4, 0xE1, 0x78, 0x50, 0xD0 );
	_TEST32_VEX( "c4e17850d8 vmovmskps ebx,xmm0", 0xC4, 0xE1, 0x78, 0x50, 0xD8 );
	_TEST64_VEX( "c4e17c50d0 vmovmskps rdx,ymm0", 0xC4, 0xE1, 0x7C, 0x50, 0xD0 );
	_TEST64_VEX( "c4e17c50d0 vmovmskps rdx,ymm0", 0xC4, 0xE1, 0x7C, 0x50, 0xD0 );
	_TEST32_VEX( "c4e17c50d8 vmovmskps ebx,ymm0", 0xC4, 0xE1, 0x7C, 0x50, 0xD8 );

	// MOVMSKPD
	// 66 0F 50 /r MOVMSKPD reg, xmm
	_TEST32( "660f50d0 movmskpd edx,xmm0", 0x66, 0x0F, 0x50, 0xD0 );
	_TEST32( "660f50d8 movmskpd ebx,xmm0", 0x66, 0x0F, 0x50, 0xD8 );
	_TEST64( "660f50d0 movmskpd rdx,xmm0", 0x66, 0x0F, 0x50, 0xD0 );
	_TEST64( "66480f50d0 movmskpd rdx,xmm0", 0x66, 0x48, 0x0F, 0x50, 0xD0 );
	// VEX.128.66.0F 50 /r VMOVMSKPD reg, xmm2
	// VEX.256.66.0F 50 /r VMOVMSKPD reg, ymm2
	_TEST32_VEX( "c4e17950d0 vmovmskpd edx,xmm0", 0xC4, 0xE1, 0x79, 0x50, 0xD0 );
	_TEST32_VEX( "c4e17950d8 vmovmskpd ebx,xmm0", 0xC4, 0xE1, 0x79, 0x50, 0xD8 );
	_TEST64_VEX( "c4e17d50d0 vmovmskpd rdx,ymm0", 0xC4, 0xE1, 0x7D, 0x50, 0xD0 );
	_TEST64_VEX( "c4e17d50d0 vmovmskpd rdx,ymm0", 0xC4, 0xE1, 0x7D, 0x50, 0xD0 );
	_TEST32_VEX( "c4e17d50d8 vmovmskpd ebx,ymm0", 0xC4, 0xE1, 0x7D, 0x50, 0xD8 );

	// MOVLPS
	// 0F 12 /r MOVLPS xmm, m64
	_TEST32( "0f1200 movlps xmm0,qword ptr [eax]", 0x0F, 0x12, 0x00 );
	_TEST64( "0f1200 movlps xmm0,qword ptr [rax]", 0x0F, 0x12, 0x00 );
	_TEST64( "480f1200 movlps xmm0,qword ptr [rax]", 0x48, 0x0F, 0x12, 0x00 );
	// 0F 13 /r MOVLPS m64, xmm
	_TEST32( "0f1300 movlps qword ptr [eax],xmm0", 0x0F, 0x13, 0x00 );
	_TEST64( "0f1300 movlps qword ptr [rax],xmm0",  0x0F, 0x13, 0x00 );
	_TEST64( "480f1300 movlps qword ptr [rax],xmm0", 0x48, 0x0F, 0x13, 0x00 );
	// VEX.NDS.128.0F 12 /r VMOVLPS xmm2, xmm1, m64
	_TEST32_VEX( "c5f01210 vmovlps xmm2,xmm1,qword ptr [eax]", 0xC5, 0xF0, 0x12, 0x10 );
	_TEST64_VEX( "c4e1501200 vmovlps xmm0,xmm5,qword ptr [rax]", 0xC4, 0xE1, 0x50, 0x12, 0x00 );
	// VEX.128.0F 13/r VMOVLPS m64, xmm1
	_TEST64_VEX( "c4e1781300 vmovlps qword ptr [rax],xmm0", 0xC4, 0xE1, 0x78, 0x13, 0x00 );

	// MOVLPD
	// 66 0F 12 /r MOVLPD xmm, m64
	_TEST32( "660f1200 movlpd xmm0,qword ptr [eax]", 0x66, 0x0F, 0x12, 0x00 );
	_TEST64( "660f1200 movlpd xmm0,qword ptr [rax]", 0x66, 0x0F, 0x12, 0x00 );
	_TEST64( "66480f1200 movlpd xmm0,qword ptr [rax]", 0x66, 0x48, 0x0F, 0x12, 0x00 );
	// 66 0F 13 /r MOVLPD m64,xmm
	_TEST32( "660f1300 movlpd qword ptr [eax],xmm0", 0x66, 0x0F, 0x13, 0x00 );
	_TEST64( "660f1300 movlpd qword ptr [rax],xmm0", 0x66, 0x0F, 0x13, 0x00 );
	_TEST64( "66480f1300 movlpd qword ptr [rax],xmm0", 0x66, 0x48, 0x0F, 0x13, 0x00 );
	// VEX.NDS.128.66.0F 12 /r VMOVLPD xmm2,xmm1,m64
	_TEST32_VEX( "c5f11210 vmovlpd xmm2,xmm1,qword ptr [eax]", 0xC5, 0xF1, 0x12, 0x10 );
	_TEST64_VEX( "c4e1511200 vmovlpd xmm0,xmm5,qword ptr [rax]", 0xC4, 0xE1, 0x51, 0x12, 0x00 );
	// VEX.128.66.0F 13 /r VMOVLPD m64,xmm1
	_TEST64_VEX( "c4e1791300 vmovlpd qword ptr [rax],xmm0", 0xC4, 0xE1, 0x79, 0x13, 0x00 );

	// MOVLHPS
	// 0F 16 /r MOVLHPS xmm1, xmm2 A Valid Valid Move two packed singleprecision floating-point values from low quadword of xmm2 to high quadword of xmm1.
	_TEST32( "0f16d0 movlhps xmm2,xmm0", 0x0F, 0x16, 0xD0 );
	_TEST32( "0f16d8 movlhps xmm3,xmm0", 0x0F, 0x16, 0xD8 );
	_TEST64( "0f16d0 movlhps xmm2,xmm0", 0x0F, 0x16, 0xD0 );
	_TEST64( "480f16d0 movlhps xmm2,xmm0", 0x48, 0x0F, 0x16, 0xD0 );
	// VEX.NDS.128.0F 16 /r VMOVLHPS xmm1,xmm2,xmm3
	// TODO: WinDBG, sprawdzic.
	_TEST32_VEX( "c5d016d0 vmovlhps xmm2,xmm5,xmm0", 0xC5, 0xD0, 0x16, 0xD0 );
	_TEST64_VEX( "c4e14816c0 vmovlhps xmm0,xmm6,xmm0", 0xC4, 0xE1, 0x48, 0x16, 0xC0 );

	// MOVHPS
	// 0F 16 /r MOVHPS xmm, m64 A Valid Valid Move two packed singleprecision floating-point values from m64 to high quadword of xmm.
	_TEST32( "0f1608 movhps xmm1,qword ptr [eax]", 0x0F, 0x16, 0x08 );
	_TEST64( "0f1608 movhps xmm1,qword ptr [rax]", 0x0F, 0x16, 0x08 );
	_TEST64( "480f1600 movhps xmm0,qword ptr [rax]", 0x48, 0x0F, 0x16, 0x00 );
	// 0F 17 /r MOVHPS m64, xmm B Valid Valid Move two packed singleprecision floating-point values from high quadword of xmm to m64.
	_TEST32( "0f1708 movhps qword ptr [eax],xmm1", 0x0F, 0x17, 0x08 );
	_TEST64( "0f1708 movhps qword ptr [rax],xmm1", 0x0F, 0x17, 0x08 );
	_TEST64( "480f1700 movhps qword ptr [rax],xmm0", 0x48, 0x0F, 0x17, 0x00 );
	// VEX.NDS.128.0F 16 /r VMOVHPS xmm2,xmm1,m64
	_TEST32_VEX( "c5f01610 vmovhps xmm2,xmm1,qword ptr [eax]", 0xC5, 0xF0, 0x16, 0x10 );
	_TEST64_VEX( "c4e1501600 vmovhps xmm0,xmm5,qword ptr [rax]", 0xC4, 0xE1, 0x50, 0x16, 0x00 );
	// VEX.128.0F 17 /r VMOVHPS m64,xmm1
	_TEST64_VEX( "c4e1781700 vmovhps qword ptr [rax],xmm0", 0xC4, 0xE1, 0x78, 0x17, 0x00 );

	// MOVHPD
	// 66 0F 16 /r MOVHPD xmm, m64 A Valid Valid Move double-precision floating-point value from m64 to high quadword of xmm.
	_TEST32( "660f1608 movhpd xmm1,qword ptr [eax]", 0x66, 0x0F, 0x16, 0x08 );
	_TEST64( "660f1608 movhpd xmm1,qword ptr [rax]", 0x66, 0x0F, 0x16, 0x08 );
	_TEST64( "66480f1600 movhpd xmm0,qword ptr [rax]", 0x66, 0x48, 0x0F, 0x16, 0x00 );
	// 66 0F 17 /r MOVHPD m64, xmm B Valid Valid Move double-precision floating-point value from high quadword of xmm to m64.
	_TEST32( "660f1708 movhpd qword ptr [eax],xmm1", 0x66, 0x0F, 0x17, 0x08 );
	_TEST64( "660f1708 movhpd qword ptr [rax],xmm1", 0x66, 0x0F, 0x17, 0x08 );
	_TEST64( "66480f1700 movhpd qword ptr [rax],xmm0", 0x66, 0x48, 0x0F, 0x17, 0x00 );
	// VEX.NDS.128.66.0F 16 /r VMOVHPD xmm2,xmm1,m64
	_TEST32_VEX( "c5f11610 vmovhpd xmm2,xmm1,qword ptr [eax]", 0xC5, 0xF1, 0x16, 0x10 );
	_TEST64_VEX( "c4e1511600 vmovhpd xmm0,xmm5,qword ptr [rax]", 0xC4, 0xE1, 0x51, 0x16, 0x00 );
	// VEX128.66.0F 17/r VMOVHPD m64, xmm1
	_TEST64_VEX( "c4e1791700 vmovhpd qword ptr [rax],xmm0", 0xC4, 0xE1, 0x79, 0x17, 0x00 );

	// MOVHLPS
	// 0F 12 /r MOVHLPS xmm1, xmm2 A Valid Valid Move two packed singleprecision floating-point values from high quadword of xmm2 to low quadword of xmm1.
	_TEST32( "0f12d0 movhlps xmm2,xmm0", 0x0F, 0x12, 0xD0 );
	_TEST32( "0f12d8 movhlps xmm3,xmm0", 0x0F, 0x12, 0xD8 );
	_TEST64( "0f12d0 movhlps xmm2,xmm0", 0x0F, 0x12, 0xD0 );
	_TEST64( "480f12d0 movhlps xmm2,xmm0", 0x48, 0x0F, 0x12, 0xD0 );
	// VEX.NDS.128.0F 12 /r VMOVHLPS xmm1, xmm2, xmm3
	_TEST32_VEX( "c4e17812d8 vmovhlps xmm3,xmm0,xmm0", 0xC4, 0xE1, 0x78, 0x12, 0xD8 );
	_TEST64_VEX( "c4e17812d9 vmovhlps xmm3,xmm0,xmm1", 0xC4, 0xE1, 0x78, 0x12, 0xD9 );
	_TEST64_VEX( "c4e10012d9 vmovhlps xmm3,xmm15,xmm1", 0xC4, 0xE1, 0x00, 0x12, 0xD9 );

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
	// VEX.128.66.0F 6F /r VMOVDQA xmm1,xmm2/m128
	// VEX.256.66.0F 6F /r VMOVDQA ymm1,ymm2/m256
	_TEST64_VEX( "c4e1796fd8 vmovdqa xmm3,xmm0", 0xC4, 0xE1, 0x79, 0x6F, 0xD8 );
	_TEST32_VEX( "c4e17d6f00 vmovdqa ymm0,ymmword ptr [eax]", 0xC4, 0xE1, 0x7D, 0x6F, 0x00 );
	// VEX.128.66.0F 7F /r VMOVDQA xmm2/m128,xmm1
	// VEX.256.66.0F 7F /r VMOVDQA ymm2/m256,ymm1
	_TEST32_VEX( "c4e1797fd8 vmovdqa xmm0,xmm3", 0xC4, 0xE1, 0x79, 0x7F, 0xD8 );
	_TEST64_VEX( "c4e17d7f00 vmovdqa ymmword ptr [rax],ymm0", 0xC4, 0xE1, 0x7D, 0x7F, 0x00 );

	// MOVDDUP
	// F2 0F 12 /r MOVDDUP xmm1, xmm2/m64 A Valid Valid Move one double-precision floating-point value from the lower 64-bit operand in xmm2/m64 to xmm1 and duplicate.
	_TEST32( "f20f1210 movddup xmm2,qword ptr [eax]", 0xF2, 0x0F, 0x12, 0x10 );
	_TEST32( "f20f12d8 movddup xmm3,xmm0", 0xF2, 0x0F, 0x12, 0xD8 );
	_TEST64( "f20f1210 movddup xmm2,qword ptr [rax]", 0xF2, 0x0F, 0x12, 0x10 );
	// VEX.128.F2.0F 12 /r VMOVDDUP xmm1,xmm2/m64
	// VEX.256.F2.0F 12 /r VMOVDDUP ymm1,ymm2/m256
	_TEST64_VEX( "c4e17b12d8 vmovddup xmm3,xmm0", 0xC4, 0xE1, 0x7B, 0x12, 0xD8 );
	_TEST32_VEX( "c4e17b1200 vmovddup xmm0,qword ptr [eax]", 0xC4, 0xE1, 0x7B, 0x12, 0x00 );
	_TEST32_VEX( "c4e17f12d8 vmovddup ymm3,ymm0", 0xC4, 0xE1, 0x7F, 0x12, 0xD8 );
	_TEST64_VEX( "c4e17f1200 vmovddup ymm0,ymmword ptr [rax]", 0xC4, 0xE1, 0x7F, 0x12, 0x00 );
	// VEX.128.F3.0F 6F /r VMOVDQU xmm1,xmm2/m128
	// VEX.256.F3.0F 6F /r VMOVDQU ymm1,ymm2/m256
	_TEST64_VEX( "c4e17a6fd8 vmovdqu xmm3,xmm0", 0xC4, 0xE1, 0x7A, 0x6F, 0xD8 );
	_TEST32_VEX( "c4e17e6f00 vmovdqu ymm0,ymmword ptr [eax]", 0xC4, 0xE1, 0x7E, 0x6F, 0x00 );
	// VEX.128.F3.0F 7F /r VMOVDQU xmm2/m128,xmm1
	// VEX.256.F3.0F 7F /r VMOVDQU ymm2/m256,ymm1
	_TEST32_VEX( "c4e17a7fd8 vmovdqu xmm0,xmm3", 0xC4, 0xE1, 0x7A, 0x7F, 0xD8 );
	_TEST64_VEX( "c4e17e7f00 vmovdqu ymmword ptr [rax],ymm0", 0xC4, 0xE1, 0x7E, 0x7F, 0x00 );


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
	// VEX.128.66.0F.W0 6E /r VMOVD xmm1,r32/m32
	_TEST32_VEX( "c4e1796e1401 vmovd xmm2,dword ptr [ecx+eax]", 0xC4, 0xE1, 0x79, 0x6E, 0x14, 0x01 );
	// VEX.128.66.0F.W1 6E /r VMOVQ xmm1,r64/m64
	_TEST64_VEX( "c4e1f96e1401 vmovq xmm2,qword ptr [rcx+rax]", 0xC4, 0xE1, 0xF9, 0x6E, 0x14, 0x01 );
	// VEX.128.66.0F.W0 7E /r VMOVD r32/m32,xmm1
	_TEST32_VEX( "c4e1797e1401 vmovd dword ptr [ecx+eax],xmm2", 0xC4, 0xE1, 0x79, 0x7E, 0x14, 0x01 );
	// VEX.128.66.0F.W1 7E /r VMOVQ r64/m64,xmm1
	_TEST64_VEX( "c4e1f97e1401 vmovq qword ptr [rcx+rax],xmm2", 0xC4, 0xE1, 0xF9, 0x7E, 0x14, 0x01 );

	// MOV (DR)
	// 0F 21/r MOV r32, DR0�DR7 A N.E. Valid Move debug register to r32
	_TEST32( "0f21d0 mov eax,dr2", 0x0F, 0x21, 0xD0 );
	_TEST32( "660f21d0 mov eax,dr2", 0x66, 0x0F, 0x21, 0xD0 );
	// 0F 21/r MOV r64, DR0�DR7 A Valid N.E. Move extended debug register to r64.
	_TEST64( "660f21d0 mov rax,dr2", 0x66, 0x0F, 0x21, 0xD0 );
	_TEST64( "480f21d0 mov rax,dr2", 0x48, 0x0F, 0x21, 0xD0 );
	_TEST64( "0f21d0 mov rax,dr2", 0x0F, 0x21, 0xD0 );
	// 0F 23 /r MOV DR0�DR7, r32 A N.E. Valid Move r32 to debug register
	_TEST32( "0f23d0 mov dr2,eax", 0x0F, 0x23, 0xD0 );
	_TEST32( "660f23d0 mov dr2,eax", 0x66, 0x0F, 0x23, 0xD0 );
	// 0F 23 /r MOV DR0�DR7, r64 A Valid N.E. Move r64 to extended debug register.
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
	// 0F 20/r MOV r32, CR0�CR7 A N.E. Valid Move control register to r32
	// 0F 20/r MOV r64, CR0�CR7 A Valid N.E. Move extended control register to r64.
	_TEST32( "0f20d0 mov eax,cr2", 0x0F, 0x20, 0xD0 );
	_TEST32( "660f20d0 mov eax,cr2", 0x66, 0x0F, 0x20, 0xD0 );
	// REX.R + 0F 20 /0 MOV r64, CR8 A Valid N.E. Move extended CR8 to r64.1
	_TEST64( "660f20d0 mov rax,cr2", 0x66, 0x0F, 0x20, 0xD0 );
	_TEST64( "480f20d0 mov rax,cr2", 0x48, 0x0F, 0x20, 0xD0 );
	_TEST64( "0f20d0 mov rax,cr2", 0x0F, 0x20, 0xD0 );
	// 0F 22 /r MOV CR0�CR7, r32 A N.E. Valid Move r32 to control register
	// 0F 22 /r MOV CR0�CR7, r64 A Valid N.E. Move r64 to extended control register.
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
	// VEX.128.0F 28 /r VMOVAPS xmm1,xmm2/m128
	// VEX.256.0F 28 /r VMOVAPS ymm1,ymm2/m256
	_TEST64_VEX( "c4e17828d8 vmovaps xmm3,xmm0", 0xC4, 0xE1, 0x78, 0x28, 0xD8 );
	_TEST32_VEX( "c4e17828d8 vmovaps xmm3,xmm0", 0xC4, 0xE1, 0x78, 0x28, 0xD8 );
	_TEST32_VEX( "c4e17c28d8 vmovaps ymm3,ymm0", 0xC4, 0xE1, 0x7C, 0x28, 0xD8 );
	_TEST32_VEX( "c4e1782800 vmovaps xmm0,oword ptr [eax]", 0xC4, 0xE1, 0x78, 0x28, 0x00 );
	// VEX.128.0F 29 /r VMOVAPS xmm2/m128,xmm1
	// VEX.256.0F 29 /r VMOVAPS ymm2/m256,ymm1
	_TEST64_VEX( "c4e17829d8 vmovaps xmm0,xmm3", 0xC4, 0xE1, 0x78, 0x29, 0xD8 );
	_TEST32_VEX( "c4e17829d8 vmovaps xmm0,xmm3", 0xC4, 0xE1, 0x78, 0x29, 0xD8 );
	_TEST32_VEX( "c4e1782900 vmovaps oword ptr [eax],xmm0", 0xC4, 0xE1, 0x78, 0x29, 0x00 );
	_TEST32_VEX( "c4e17c2900 vmovaps ymmword ptr [eax],ymm0", 0xC4, 0xE1, 0x7C, 0x29, 0x00 );

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
	// VEX.128.66.0F 28 /r VMOVAPD xmm1,xmm2/m128
	// VEX.256.66.0F 28 /r VMOVAPD ymm1,ymm2/m256
	_TEST64_VEX( "c4e17928d8 vmovapd xmm3,xmm0", 0xC4, 0xE1, 0x79, 0x28, 0xD8 );
	_TEST32_VEX( "c4e17928d8 vmovapd xmm3,xmm0", 0xC4, 0xE1, 0x79, 0x28, 0xD8 );
	_TEST32_VEX( "c4e1792800 vmovapd xmm0,oword ptr [eax]", 0xC4, 0xE1, 0x79, 0x28, 0x00 );
	// VEX.128.66.0F 29 /r VMOVAPD xmm2/m128,xmm1
	// VEX.256.66.0F 29 /r VMOVAPD ymm2/m256,ymm1
	_TEST64_VEX( "c4e17929d8 vmovapd xmm0,xmm3", 0xC4, 0xE1, 0x79, 0x29, 0xD8 );
	_TEST32_VEX( "c4e17929d8 vmovapd xmm0,xmm3", 0xC4, 0xE1, 0x79, 0x29, 0xD8 );
	_TEST32_VEX( "c4e1792900 vmovapd oword ptr [eax],xmm0", 0xC4, 0xE1, 0x79, 0x29, 0x00 );

	// MONITOR
	_TEST64( "0f01c8 monitor rax,rcx,rdx", 0x0F, 0x01, 0xC8 );
	_TEST32( "0f01c8 monitor eax,ecx,edx", 0x0F, 0x01, 0xC8 );

	// MINSD
	_TEST64( "f30f5d4020 minss xmm0,dword ptr [rax+0000000000000020h]", 0xF3, 0x0F, 0x5D, 0x40, 0x20 );
	_TEST32( "f30f5dc2 minss xmm0,xmm2", 0xF3, 0x0F, 0x5D, 0xC2 );
	_TEST32( "f30f5d4020 minss xmm0,dword ptr [eax+00000020h]", 0xF3, 0x0F, 0x5D, 0x40, 0x20 );
	// VEX.NDS.128.F3.0F 5D /r VMINSS xmm1,xmm2,xmm3/m32
	_TEST64_VEX( "c4e17a5dd8 vminss xmm3,xmm0,xmm0", 0xC4, 0xE1, 0x7A, 0x5D, 0xD8 );
	_TEST32_VEX( "c4e17a5dd8 vminss xmm3,xmm0,xmm0", 0xC4, 0xE1, 0x7A, 0x5D, 0xD8 );

	// MINSD
	_TEST64( "f20f5d4020 minsd xmm0,qword ptr [rax+0000000000000020h]", 0xF2, 0x0F, 0x5D, 0x40, 0x20 );
	_TEST32( "f20f5dc2 minsd xmm0,xmm2", 0xF2, 0x0F, 0x5D, 0xC2 );
	_TEST32( "f20f5d4020 minsd xmm0,qword ptr [eax+00000020h]", 0xF2, 0x0F, 0x5D, 0x40, 0x20 );
	// VEX.NDS.128.F2.0F 5D /r VMINSD xmm1, xmm2, xmm3/m64
	_TEST64_VEX( "c4e17b5dd8 vminsd xmm3,xmm0,xmm0", 0xC4, 0xE1, 0x7B, 0x5D, 0xD8 );
	_TEST32_VEX( "c4e17b5dd8 vminsd xmm3,xmm0,xmm0", 0xC4, 0xE1, 0x7B, 0x5D, 0xD8 );
	_TEST32_VEX( "c4e1635d18 vminsd xmm3,xmm3,qword ptr [eax]", 0xC4, 0xE1, 0x63, 0x5D, 0x18 );

	// MINPS
	_TEST64( "0f5d4020 minps xmm0,oword ptr [rax+0000000000000020h]", 0x0F, 0x5D, 0x40, 0x20 );
	_TEST32( "0f5dc2 minps xmm0,xmm2", 0x0F, 0x5D, 0xC2 );
	_TEST32( "0f5d4020 minps xmm0,oword ptr [eax+00000020h]", 0x0F, 0x5D, 0x40, 0x20 );
	// VEX.NDS.128.0F 5D /r VMINPS xmm1,xmm2,xmm3/m128
	// VEX.NDS.256.0F 5D /r VMINPS ymm1,ymm2,ymm3/m256
	_TEST64_VEX( "c4e1785dd8 vminps xmm3,xmm0,xmm0", 0xC4, 0xE1, 0x78, 0x5D, 0xD8 );
	_TEST32_VEX( "c4e17c5dd8 vminps ymm3,ymm0,ymm0", 0xC4, 0xE1, 0x7C, 0x5D, 0xD8 );
	_TEST32_VEX( "c4e1645d18 vminps ymm3,ymm3,ymmword ptr [eax]", 0xC4, 0xE1, 0x64, 0x5D, 0x18 );

	// MINPD
	_TEST64( "660f5d4020 minpd xmm0,oword ptr [rax+0000000000000020h]", 0x66, 0x0F, 0x5D, 0x40, 0x20 );
	_TEST32( "660f5dc2 minpd xmm0,xmm2", 0x66, 0x0F, 0x5D, 0xC2 );
	_TEST32( "660f5d4020 minpd xmm0,oword ptr [eax+00000020h]", 0x66, 0x0F, 0x5D, 0x40, 0x20 );
	// VEX.NDS.128.66.0F 5D /r VMINPD xmm1,xmm2,xmm3/m128
	// VEX.NDS.256.66.0F 5D /r VMINPD ymm1,ymm2,ymm3/m256
	_TEST64_VEX( "c4e1795dd8 vminpd xmm3,xmm0,xmm0", 0xC4, 0xE1, 0x79, 0x5D, 0xD8 );
	_TEST32_VEX( "c4e17d5dd8 vminpd ymm3,ymm0,ymm0", 0xC4, 0xE1, 0x7D, 0x5D, 0xD8 );
	_TEST32_VEX( "c4e1655d18 vminpd ymm3,ymm3,ymmword ptr [eax]", 0xC4, 0xE1, 0x65, 0x5D, 0x18 );

	// MFENCE
	_TEST32( "0faef0 mfence", 0x0F, 0xAE, 0xF0 );
	_TEST64( "0faef0 mfence",0x0F, 0xAE, 0xF0 );

	// MAXSS
	_TEST64( "f30f5f4020 maxss xmm0,dword ptr [rax+0000000000000020h]", 0xF3, 0x0F, 0x5F, 0x40, 0x20 );
	_TEST32( "f30f5fc2 maxss xmm0,xmm2", 0xF3, 0x0F, 0x5F, 0xC2 );
	_TEST32( "f30f5f4020 maxss xmm0,dword ptr [eax+00000020h]", 0xF3, 0x0F, 0x5F, 0x40, 0x20 );
	// VEX.NDS.128.F3.0F 5F /r VMAXSS xmm1, xmm2, xmm3/m32
	_TEST64_VEX( "c4e1625fd8 vmaxss xmm3,xmm3,xmm0", 0xC4, 0xE1, 0x62, 0x5F, 0xD8 );
	_TEST32_VEX( "c4e1425fd8 vmaxss xmm3,xmm7,xmm0", 0xC4, 0xE1, 0x42, 0x5F, 0xD8 );
	_TEST32_VEX( "c4e17a5f18 vmaxss xmm3,xmm0,dword ptr [eax]", 0xC4, 0xE1, 0x7A, 0x5F, 0x18 );

	// MAXSD
	_TEST64( "f20f5f4020 maxsd xmm0,qword ptr [rax+0000000000000020h]", 0xF2, 0x0F, 0x5F, 0x40, 0x20 );
	_TEST32( "f20f5fc2 maxsd xmm0,xmm2", 0xF2, 0x0F, 0x5F, 0xC2 );
	_TEST32( "f20f5f4020 maxsd xmm0,qword ptr [eax+00000020h]", 0xF2, 0x0F, 0x5F, 0x40, 0x20 );
	// VEX.NDS.128.F2.0F 5F /r VMAXSD xmm1,xmm2,xmm3/m64
	_TEST64_VEX( "c4e1635fd8 vmaxsd xmm3,xmm3,xmm0", 0xC4, 0xE1, 0x63, 0x5F, 0xD8 );
	_TEST32_VEX( "c4e1435fd8 vmaxsd xmm3,xmm7,xmm0", 0xC4, 0xE1, 0x43, 0x5F, 0xD8 );
	_TEST32_VEX( "c4e17b5f18 vmaxsd xmm3,xmm0,qword ptr [eax]", 0xC4, 0xE1, 0x7B, 0x5F, 0x18 );

	// MAXPS
	_TEST64( "0f5f4020 maxps xmm0,oword ptr [rax+0000000000000020h]", 0x0F, 0x5F, 0x40, 0x20 );
	_TEST32( "0f5fc2 maxps xmm0,xmm2", 0x0F, 0x5F, 0xC2 );
	_TEST32( "0f5f4020 maxps xmm0,oword ptr [eax+00000020h]", 0x0F, 0x5F, 0x40, 0x20 );
	// VEX.NDS.128.0F 5F /r VMAXPS xmm1,xmm2,xmm3/m128
	// VEX.NDS.256.0F 5F /r VMAXPS ymm1,ymm2,ymm3/m256
	_TEST64_VEX( "c4e1785fd8 vmaxps xmm3,xmm0,xmm0", 0xC4, 0xE1, 0x78, 0x5F, 0xD8 );
	_TEST32_VEX( "c4e17c5fd8 vmaxps ymm3,ymm0,ymm0", 0xC4, 0xE1, 0x7C, 0x5F, 0xD8 );
	_TEST32_VEX( "c4e1645f18 vmaxps ymm3,ymm3,ymmword ptr [eax]", 0xC4, 0xE1, 0x64, 0x5F, 0x18 );

	// MAXPD
	_TEST64( "660f5f4020 maxpd xmm0,oword ptr [rax+0000000000000020h]", 0x66, 0x0F, 0x5F, 0x40, 0x20 );
	_TEST32( "660f5fc2 maxpd xmm0,xmm2", 0x66, 0x0F, 0x5F, 0xC2 );
	_TEST32( "660f5f4020 maxpd xmm0,oword ptr [eax+00000020h]", 0x66, 0x0F, 0x5F, 0x40, 0x20 );
	// VEX.NDS.128.66.0F 5F /r VMAXPD xmm1,xmm2,xmm3/m128
	// VEX.NDS.256.66.0F 5F /r VMAXPD ymm1,ymm2,ymm3/m256
	_TEST64_VEX( "c4e1795fd8 vmaxpd xmm3,xmm0,xmm0", 0xC4, 0xE1, 0x79, 0x5F, 0xD8 );
	_TEST32_VEX( "c4e17d5fd8 vmaxpd ymm3,ymm0,ymm0", 0xC4, 0xE1, 0x7D, 0x5F, 0xD8 );
	_TEST32_VEX( "c4e1655f18 vmaxpd ymm3,ymm3,ymmword ptr [eax]", 0xC4, 0xE1, 0x65, 0x5F, 0x18 );

	// MASKMOVDQU
	_TEST64( "0ff7d8 maskmovq mm3,mm0", 0x0F, 0xF7, 0xD8 );
	_TEST32( "0ff7e0 maskmovq mm4,mm0", 0x0F, 0xF7, 0xE0 );
	_TEST32( "FAIL", 0x0F, 0xF7, 0x40, 0x20 );
	// VEX.128.66.0F F7 /r VMASKMOVDQU xmm1,xmm2
	_TEST64_VEX( "c4e179f7d8 vmaskmovdqu xmm3,mm0", 0xC4, 0xE1, 0x79, 0xF7, 0xD8 );
	_TEST32_VEX( "c4e179f7d8 vmaskmovdqu xmm3,mm0", 0xC4, 0xE1, 0x79, 0xF7, 0xD8 );

	// VMASKMOVPS/VMASKMOVPD
	// VEX.NDS.128.66.0F38 2C /r VMASKMOVPS xmm1,xmm2,m128
	// VEX.NDS.256.66.0F38 2C /r VMASKMOVPS ymm1,ymm2,m256
	_TEST64_VEX( "c4e2692c18 vmaskmovps xmm3,xmm2,oword ptr [rax]", 0xC4, 0xE2, 0x69, 0x2C, 0x18 );
	_TEST32_VEX( "c4e26d2c18 vmaskmovps ymm3,ymm2,ymmword ptr [eax]", 0xC4, 0xE2, 0x6D, 0x2C, 0x18 );
	// VEX.NDS.128.66.0F38 2D /r VMASKMOVPD xmm1,xmm2,m128
	// VEX.NDS.256.66.0F38 2D /r VMASKMOVPD ymm1,ymm2,m256
	_TEST64_VEX( "c4e2692d18 vmaskmovpd xmm3,xmm2,oword ptr [rax]", 0xC4, 0xE2, 0x69, 0x2D, 0x18 );
	_TEST32_VEX( "c4e26d2d18 vmaskmovpd ymm3,ymm2,ymmword ptr [eax]", 0xC4, 0xE2, 0x6D, 0x2D, 0x18 );
	// VEX.NDS.128.66.0F38 2E /r VMASKMOVPS m128,xmm1,xmm2
	// VEX.NDS.256.66.0F38 2E /r VMASKMOVPS m256,ymm1,ymm2
	_TEST64_VEX( "c4e2692e18 vmaskmovps oword ptr [rax],xmm2,xmm3", 0xC4, 0xE2, 0x69, 0x2E, 0x18 );
	_TEST32_VEX( "c4e26d2e18 vmaskmovps ymmword ptr [eax],ymm2,ymm3", 0xC4, 0xE2, 0x6D, 0x2E, 0x18 );
	// VEX.NDS.128.66.0F38 2F /r VMASKMOVPD m128,xmm1,xmm2
	// VEX.NDS.256.66.0F38 2F /r VMASKMOVPD m256,ymm1,ymm2
	_TEST64_VEX( "c4e2692f18 vmaskmovpd oword ptr [rax],xmm2,xmm3", 0xC4, 0xE2, 0x69, 0x2F, 0x18 );
	_TEST32_VEX( "c4e26d2f18 vmaskmovpd ymmword ptr [eax],ymm2,ymm3", 0xC4, 0xE2, 0x6D, 0x2F, 0x18 );

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

	// VLDMXCSR
	// VEX.128.0F AE /2 VLDMXCSR m32
	_TEST64_VEX( "c4c178ae10 vldmxcsr dword ptr [r8]", 0xC4, 0xC1, 0x78, 0xAE, 0x10 );
	_TEST32_VEX( "c4e178ae10 vldmxcsr dword ptr [eax]", 0xC4, 0xE1, 0x78, 0xAE, 0x10 );
	_TEST32_VEX( "c5f8ae10 vldmxcsr dword ptr [eax]", 0xC5, 0xF8, 0xAE, 0x10 );

	// LDMXCSR
	_TEST32( "0fae5020 ldmxcsr dword ptr [eax+00000020h]", 0x0F, 0xAE, 0x50, 0x20 );
	_TEST64( "0fae5020 ldmxcsr dword ptr [rax+0000000000000020h]", 0x0F, 0xAE, 0x50, 0x20 );

	// LDDQU
	_TEST32( "f20ff06820 lddqu xmm5,[eax+00000020h]", 0xF2, 0x0F, 0xF0, 0x68, 0x20 );
	_TEST64( "f20ff06820 lddqu xmm5,[rax+0000000000000020h]", 0xF2, 0x0F, 0xF0, 0x68, 0x20 );
	// VEX.128.F2.0F F0 /r VLDDQU xmm1, m128
	// VEX.256.F2.0F F0 /r VLDDQU ymm1, m256
	_TEST64_VEX( "c4417bf000 vlddqu xmm8,oword ptr [r8]", 0xC4, 0x41, 0x7B, 0xF0, 0x00, 0x20 );
	_TEST32_VEX( "c4e17ff000 vlddqu ymm0,ymmword ptr [eax]", 0xC4, 0xE1, 0x7F, 0xF0, 0x00, 0x20 );

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

	// VINSERTF128
	// VEX.NDS.256.66.0F3A 18 /r ib VINSERTF128 ymm1,ymm2,xmm3/m128,imm8
	_TEST64_VEX( "c4430d180020 vinsertf128 ymm8,ymm14,oword ptr [r8],20h", 0xC4, 0x43, 0x0D, 0x18, 0x00, 0x20 );
	_TEST32_VEX( "c4e34d180020 vinsertf128 ymm0,ymm6,oword ptr [eax],20h", 0xC4, 0xE3, 0x4D, 0x18, 0x00, 0x20 );
	_TEST32_VEX( "c4e34d18c020 vinsertf128 ymm0,ymm6,xmm0,20h", 0xC4, 0xE3, 0x4D, 0x18, 0xC0, 0x20 );

	// INSERTPS
	_TEST32( "660f3a212040 insertps xmm4,dword ptr [eax],40h", 0x66, 0x0F, 0x3A, 0x21, 0x20, 0x40 );
	_TEST64( "660f3a212040 insertps xmm4,dword ptr [rax],40h", 0x66, 0x0F, 0x3A, 0x21, 0x20, 0x40 );
	// VEX.NDS.128.66.0F3A 21 /r ib VINSERTPS xmm1,xmm2,xmm3/m32,imm8
	_TEST64_VEX( "c44309210020 vinsertps xmm8,xmm14,dword ptr [r8],20h", 0xC4, 0x43, 0x09, 0x21, 0x00, 0x20 );
	_TEST32_VEX( "c4e349210020 vinsertps xmm0,xmm6,dword ptr [eax],20h", 0xC4, 0xE3, 0x49, 0x21, 0x00, 0x20 );
	_TEST32_VEX( "c4e34921c020 vinsertps xmm0,xmm6,xmm0,20h", 0xC4, 0xE3, 0x49, 0x21, 0xC0, 0x20 );

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
	// F2 0F 7D /r HSUBPS xmm1, xmm2/m128
	_TEST64( "f20f7d4020 hsubps xmm0,oword ptr [rax+0000000000000020h]", 0xF2, 0x0F, 0x7D, 0x40, 0x20 );
	_TEST32( "f20f7d4020 hsubps xmm0,oword ptr [eax+00000020h]", 0xF2, 0x0F, 0x7D, 0x40, 0x20 );
	// VEX.NDS.128.F2.0F 7D /r VHSUBPS xmm1,xmm2,xmm3/m128
	// VEX.NDS.256.F2.0F 7D /r VHSUBPS ymm1,ymm2,ymm3/m256
	_TEST64_VEX( "c4410f7d1401 vhsubps ymm10,ymm14,ymmword ptr [r9+rax]", 0xC4, 0x41, 0x0F, 0x7D, 0x14, 0x01 );
	_TEST32_VEX( "c4c1437d1401 vhsubps xmm2,xmm7,oword ptr [ecx+eax]", 0xC4, 0xC1, 0x43, 0x7D, 0x14, 0x01 );
	_TEST32_VEX( "c4c16b7d1401 vhsubps xmm2,xmm2,oword ptr [ecx+eax]", 0xC4, 0xC1, 0x6B, 0x7D, 0x14, 0x01 );

	// HSUBPD
	_TEST64( "660f7d4020 hsubpd xmm0,oword ptr [rax+0000000000000020h]", 0x66, 0x0F, 0x7D, 0x40, 0x20 );
	_TEST32( "660f7d4020 hsubpd xmm0,oword ptr [eax+00000020h]", 0x66, 0x0F, 0x7D, 0x40, 0x20 );
	// VEX.NDS.128.66.0F 7D /r VHSUBPD xmm1,xmm2,xmm3/m128
	// VEX.NDS.256.66.0F 7D /r VHSUBPD ymm1,ymm2,ymm3/m256
	_TEST64_VEX( "c4410d7d1401 vhsubpd ymm10,ymm14,ymmword ptr [r9+rax]", 0xC4, 0x41, 0x0D, 0x7D, 0x14, 0x01 );
	_TEST32_VEX( "c4c1417d1401 vhsubpd xmm2,xmm7,oword ptr [ecx+eax]", 0xC4, 0xC1, 0x41, 0x7D, 0x14, 0x01 );
	_TEST32_VEX( "c4c1697d1401 vhsubpd xmm2,xmm2,oword ptr [ecx+eax]", 0xC4, 0xC1, 0x69, 0x7D, 0x14, 0x01 );

	// HLT
	_TEST64( "f4 hlt", 0xF4 );
	_TEST32( "f4 hlt", 0xF4 );

	// HADDPS
	_TEST64( "f20f7c4020 haddps xmm0,oword ptr [rax+0000000000000020h]", 0xF2, 0x0F, 0x7C, 0x40, 0x20 );
	_TEST32( "f20f7c4020 haddps xmm0,oword ptr [eax+00000020h]", 0xF2, 0x0F, 0x7C, 0x40, 0x20 );
	// VEX.NDS.128.F2.0F 7C /r VHADDPS xmm1,xmm2,xmm3/m128
	// VEX.NDS.256.F2.0F 7C /r VHADDPS ymm1,ymm2,ymm3/m256
	_TEST64_VEX( "c4410f7c1401 vhaddps ymm10,ymm14,ymmword ptr [r9+rax]", 0xC4, 0x41, 0x0F, 0x7C, 0x14, 0x01 );
	_TEST32_VEX( "c4c1437c1401 vhaddps xmm2,xmm7,oword ptr [ecx+eax]", 0xC4, 0xC1, 0x43, 0x7C, 0x14, 0x01 );
	_TEST32_VEX( "c4c16b7c1401 vhaddps xmm2,xmm2,oword ptr [ecx+eax]", 0xC4, 0xC1, 0x6B, 0x7C, 0x14, 0x01 );

	// HADDPD
	_TEST64( "660f7c4020 haddpd xmm0,oword ptr [rax+0000000000000020h]", 0x66, 0x0F, 0x7C, 0x40, 0x20 );
	_TEST32( "660f7c4020 haddpd xmm0,oword ptr [eax+00000020h]", 0x66, 0x0F, 0x7C, 0x40, 0x20 );
	// VEX.NDS.128.66.0F 7C /r VHADDPD xmm1,xmm2,xmm3/m128
	// VEX.NDS.256.66.0F 7C /r VHADDPD ymm1,ymm2,ymm3/m256
	_TEST64_VEX( "c4410d7c1401 vhaddpd ymm10,ymm14,ymmword ptr [r9+rax]", 0xC4, 0x41, 0x0D, 0x7C, 0x14, 0x01 );
	_TEST32_VEX( "c4c1417c1401 vhaddpd xmm2,xmm7,oword ptr [ecx+eax]", 0xC4, 0xC1, 0x41, 0x7C, 0x14, 0x01 );
	_TEST32_VEX( "c4c1697c1401 vhaddpd xmm2,xmm2,oword ptr [ecx+eax]", 0xC4, 0xC1, 0x69, 0x7C, 0x14, 0x01 );

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
	// VEX.128.66.0F3A 17 /r ib VEXTRACTPS r/m32, xmm1, imm8
	_TEST32_VEX( "c4e37917140120 vextractps dword ptr [ecx+eax],xmm2,20h", 0xC4, 0xE3, 0x79, 0x17, 0x14, 0x01, 0x20 );
	_TEST64_VEX( "c4e37917c020 vextractps eax,xmm0,20h", 0xC4, 0xE3, 0x79, 0x17, 0xC0, 0x20 );

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
	// VEX.NDS.128.66.0F3A 41 /r ib VDPPD xmm1,xmm2,xmm3/m128,imm8
	_TEST32_VEX( "c4e34941140120 vdppd xmm2,xmm6,oword ptr [ecx+eax],20h", 0xC4, 0xE3, 0x49, 0x41, 0x14, 0x01, 0x20 );
	_TEST64_VEX( "c4e34941140120 vdppd xmm2,xmm6,oword ptr [rcx+rax],20h", 0xC4, 0xE3, 0x49, 0x41, 0x14, 0x01, 0x20 );

	// DPPS
	_TEST32( "660f3a401401ff dpps xmm2,oword ptr [ecx+eax],0ffh", 0x66, 0x0F, 0x3A, 0x40, 0x14, 0x01, 0xFF );
	_TEST64( "660f3a401401ff dpps xmm2,oword ptr [rcx+rax],0ffh", 0x66, 0x0F, 0x3A, 0x40, 0x14, 0x01, 0xFF );
	// VEX.NDS.128.66.0F3A 40 /r ib VDPPS xmm1,xmm2,xmm3/m128,imm8
	// VEX.NDS.256.66.0F3A 40 /r ib VDPPS ymm1,ymm2,ymm3/m256,imm8
	_TEST32_VEX( "c4e34940140120 vdpps xmm2,xmm6,oword ptr [ecx+eax],20h", 0xC4, 0xE3, 0x49, 0x40, 0x14, 0x01, 0x20 );
	_TEST64_VEX( "c4e34940140120 vdpps xmm2,xmm6,oword ptr [rcx+rax],20h", 0xC4, 0xE3, 0x49, 0x40, 0x14, 0x01, 0x20 );

	// VEX.256.66.0F3A 19 /r ib VEXTRACTF128 xmm1/m128,ymm2,imm8
	_TEST32_VEX( "c4e37d19140120 vextractf128 oword ptr [ecx+eax],ymm2,20h", 0xC4, 0xE3, 0x7D, 0x19, 0x14, 0x01, 0x20 );
	_TEST64_VEX( "c4e37d19c020 vextractf128 xmm0,ymm0,20h", 0xC4, 0xE3, 0x7D, 0x19, 0xC0, 0x20 );

	// DIVSD
	_TEST64( "f20f5e4020 divsd xmm0,qword ptr [rax+0000000000000020h]", 0xF2, 0x0F, 0x5E, 0x40, 0x20 );
	_TEST32( "f20f5ec2 divsd xmm0,xmm2", 0xF2, 0x0F, 0x5E, 0xC2 );
	_TEST32( "f20f5e4020 divsd xmm0,qword ptr [eax+00000020h]", 0xF2, 0x0F, 0x5E, 0x40, 0x20 );
	// VEX.NDS.128.F2.0F 5E /r VDIVSD xmm1, xmm2, xmm3/m64
	_TEST32_VEX( "c4e14b5e1401 vdivsd xmm2,xmm6,qword ptr [ecx+eax]", 0xC4, 0xE1, 0x4B, 0x5E, 0x14, 0x01 );
	_TEST64_VEX( "c4e14b5e1401 vdivsd xmm2,xmm6,qword ptr [rcx+rax]", 0xC4, 0xE1, 0x4B, 0x5E, 0x14, 0x01 );

	// DIVSS
	_TEST64( "f30f5e4020 divss xmm0,dword ptr [rax+0000000000000020h]", 0xF3, 0x0F, 0x5E, 0x40, 0x20 );
	_TEST32( "f30f5ec2 divss xmm0,xmm2", 0xF3, 0x0F, 0x5E, 0xC2 );
	_TEST32( "f30f5e4020 divss xmm0,dword ptr [eax+00000020h]", 0xF3, 0x0F, 0x5E, 0x40, 0x20 );
	// VEX.NDS.128.F3.0F 5E /r VDIVSS xmm1, xmm2, xmm3/m32
	_TEST32_VEX( "c4e14a5e1401 vdivss xmm2,xmm6,dword ptr [ecx+eax]", 0xC4, 0xE1, 0x4A, 0x5E, 0x14, 0x01 );
	_TEST64_VEX( "c4e14a5e1401 vdivss xmm2,xmm6,dword ptr [rcx+rax]", 0xC4, 0xE1, 0x4A, 0x5E, 0x14, 0x01 );

	// DIVPD
	_TEST32( "660f5e1401 divpd xmm2,oword ptr [ecx+eax]", 0x66, 0x0F, 0x5E, 0x14, 0x01 );
	_TEST64( "660f5e1401 divpd xmm2,oword ptr [rcx+rax]", 0x66, 0x0F, 0x5E, 0x14, 0x01 );
	// VEX.NDS.128.66.0F 5E /r VDIVPD xmm1, xmm2, xmm3/m128
	// VEX.NDS.256.66.0F 5E /r VDIVPD ymm1, ymm2, ymm3/m256
	_TEST64_VEX( "c4410d5e1401 vdivpd ymm10,ymm14,ymmword ptr [r9+rax]", 0xC4, 0x41, 0x0D, 0x5E, 0x14, 0x01 );
	_TEST32_VEX( "c4c1415e1401 vdivpd xmm2,xmm7,oword ptr [ecx+eax]", 0xC4, 0xC1, 0x41, 0x5E, 0x14, 0x01 );
	_TEST32_VEX( "c4c1695e1401 vdivpd xmm2,xmm2,oword ptr [ecx+eax]", 0xC4, 0xC1, 0x69, 0x5E, 0x14, 0x01 );

	// DIVPS
	_TEST32( "0f5e1401 divps xmm2,oword ptr [ecx+eax]", 0x0F, 0x5E, 0x14, 0x01 );
	_TEST64( "0f5e1401 divps xmm2,oword ptr [rcx+rax]", 0x0F, 0x5E, 0x14, 0x01 );
	// VEX.NDS.128.0F 5E /r VDIVPS xmm1, xmm2, xmm3/m128
	// VEX.NDS.256.0F 5E /r VDIVPS ymm1, ymm2, ymm3/m256
	_TEST64_VEX( "c4410c5e1401 vdivps ymm10,ymm14,ymmword ptr [r9+rax]", 0xC4, 0x41, 0x0C, 0x5E, 0x14, 0x01 );
	_TEST32_VEX( "c4c1405e1401 vdivps xmm2,xmm7,oword ptr [ecx+eax]", 0xC4, 0xC1, 0x40, 0x5E, 0x14, 0x01 );
	_TEST32_VEX( "c4c1685e1401 vdivps xmm2,xmm2,oword ptr [ecx+eax]", 0xC4, 0xC1, 0x68, 0x5E, 0x14, 0x01 );

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
	// VEX.128.F3.0F.W0 2C /r VCVTTSS2SI r32, xmm1/m32
	_TEST32_VEX( "c4e17a2c1401 vcvttss2si edx,dword ptr [ecx+eax]", 0xC4, 0xE1, 0x7A, 0x2C, 0x14, 0x01 );
	_TEST64_VEX( "c4e17a2c1401 vcvttss2si edx,dword ptr [rcx+rax]", 0xC4, 0xE1, 0x7A, 0x2C, 0x14, 0x01 );
	// VEX.128.F3.0F.W1 2C /r VCVTTSS2SI r64, xmm1/m32
	_TEST64_VEX( "c4e17e2c1401 cvttss2si edx,dword ptr [rcx+rax]", 0xC4, 0xE1, 0x7E, 0x2C, 0x14, 0x01 );

	// CVTTSD2SI
	_TEST64( "f2480f2cc2 cvttsd2si rax,xmm2", 0xF2, 0x48, 0x0F, 0x2C, 0xC2 );
	_TEST64( "f20f2c4020 cvttsd2si eax,qword ptr [rax+0000000000000020h]", 0xF2, 0x0F, 0x2C, 0x40, 0x20 );
	_TEST32( "f20f2cc2 cvttsd2si eax,xmm2", 0xF2, 0x0F, 0x2C, 0xC2 );
	_TEST32( "f20f2c4020 cvttsd2si eax,qword ptr [eax+00000020h]", 0xF2, 0x0F, 0x2C, 0x40, 0x20 );
	_TEST64( "f20f2c4020 cvttsd2si eax,qword ptr [rax+0000000000000020h]", 0xF2, 0x0F, 0x2C, 0x40, 0x20 );
	_TEST64( "f20f2cc2 cvttsd2si eax,xmm2", 0xF2, 0x0F, 0x2C, 0xC2 );
	// VEX.128.F2.0F.W0 2C /r VCVTTSD2SI r32, xmm1/m64
	_TEST32_VEX( "c4e17b2c1401 vcvttsd2si edx,qword ptr [ecx+eax]", 0xC4, 0xE1, 0x7B, 0x2C, 0x14, 0x01 );
	_TEST64_VEX( "c4e17b2c1401 vcvttsd2si edx,qword ptr [rcx+rax]", 0xC4, 0xE1, 0x7B, 0x2C, 0x14, 0x01 );
	// VEX.128.F2.0F.W1 2C /r VCVTTSD2SI r64, xmm1/m64
	_TEST64_VEX( "c4e1fb2c1401 vcvttsd2si rdx,qword ptr [rcx+rax]", 0xC4, 0xE1, 0xFB, 0x2C, 0x14, 0x01 );

	// CVTTPS2PI
	_TEST64( "0f2c4020 cvttps2pi mm0,qword ptr [rax+0000000000000020h]", 0x0F, 0x2C, 0x40, 0x20 );
	_TEST32( "0f2cc2 cvttps2pi mm0,xmm2", 0x0F, 0x2C, 0xC2 );
	_TEST32( "0f2c4020 cvttps2pi mm0,qword ptr [eax+00000020h]", 0x0F, 0x2C, 0x40, 0x20 );

	// CVTTPS2DQ
	_TEST64( "f30f5b4020 cvttps2dq xmm0,oword ptr [rax+0000000000000020h]", 0xF3, 0x0F, 0x5B, 0x40, 0x20 );
	_TEST32( "f30f5bc2 cvttps2dq xmm0,xmm2", 0xF3, 0x0F, 0x5B, 0xC2 );
	_TEST32( "f30f5b4020 cvttps2dq xmm0,oword ptr [eax+00000020h]", 0xF3, 0x0F, 0x5B, 0x40, 0x20 );
	// VEX.128.F3.0F 5B /r VCVTTPS2DQ xmm1, xmm2/m128
	// VEX.256.F3.0F 5B /r VCVTTPS2DQ ymm1, ymm2/m256
	_TEST32_VEX( "c4e17a5b1401 vcvttps2dq xmm2,oword ptr [ecx+eax]", 0xC4, 0xE1, 0x7A, 0x5B, 0x14, 0x01 );
	_TEST64_VEX( "c4e17e5b1401 vcvttps2dq ymm2,ymmword ptr [rcx+rax]", 0xC4, 0xE1, 0x7E, 0x5B, 0x14, 0x01 );

	// CVTTPD2PI
	_TEST64( "660f2c4020 cvttpd2pi mm0,oword ptr [rax+0000000000000020h]", 0x66, 0x0F, 0x2C, 0x40, 0x20 );
	_TEST32( "660f2cc2 cvttpd2pi mm0,xmm2", 0x66, 0x0F, 0x2C, 0xC2 );
	_TEST32( "660f2c4020 cvttpd2pi mm0,oword ptr [eax+00000020h]", 0x66, 0x0F, 0x2C, 0x40, 0x20 );

	// CVTTPD2DQ
	_TEST64( "660fe64020 cvttpd2dq xmm0,oword ptr [rax+0000000000000020h]", 0x66, 0x0F, 0xE6, 0x40, 0x20 );
	_TEST32( "660fe6c2 cvttpd2dq xmm0,xmm2", 0x66, 0x0F, 0xE6, 0xC2 );
	_TEST32( "660fe64020 cvttpd2dq xmm0,oword ptr [eax+00000020h]", 0x66, 0x0F, 0xE6, 0x40, 0x20 );
	// VEX.128.66.0F E6 /r VCVTTPD2DQ xmm1, xmm2/m128
	// VEX.256.66.0F E6 /r VCVTTPD2DQ xmm1, ymm2/m256
	_TEST32_VEX( "c4e179e61401 vcvttpd2dq xmm2,oword ptr [ecx+eax]", 0xC4, 0xE1, 0x79, 0xE6, 0x14, 0x01 );
	_TEST64_VEX( "c4e17de61401 vcvttpd2dq ymm2,ymmword ptr [rcx+rax]", 0xC4, 0xE1, 0x7D, 0xE6, 0x14, 0x01 );

	// CVTSS2SI
	_TEST64( "f3480f2dc2 cvtss2si rax,xmm2", 0xF3, 0x48, 0x0F, 0x2D, 0xC2 );
	_TEST64( "f30f2d4020 cvtss2si eax,dword ptr [rax+0000000000000020h]", 0xF3, 0x0F, 0x2D, 0x40, 0x20 );
	_TEST32( "f30f2dc2 cvtss2si eax,xmm2", 0xF3, 0x0F, 0x2D, 0xC2 );
	_TEST32( "f30f2d4020 cvtss2si eax,dword ptr [eax+00000020h]", 0xF3, 0x0F, 0x2D, 0x40, 0x20 );
	_TEST64( "f30f2d4020 cvtss2si eax,dword ptr [rax+0000000000000020h]", 0xF3, 0x0F, 0x2D, 0x40, 0x20 );
	_TEST64( "f30f2dc2 cvtss2si eax,xmm2", 0xF3, 0x0F, 0x2D, 0xC2 );
	// VEX.128.F3.0F.W0 2D /r VCVTSS2SI r32, xmm1/m32
	_TEST32_VEX( "c4e17a2d1401 vcvtss2si edx,dword ptr [ecx+eax]", 0xC4, 0xE1, 0x7A, 0x2D, 0x14, 0x01 );
	_TEST64_VEX( "c4e17a2d1401 vcvtss2si edx,dword ptr [rcx+rax]", 0xC4, 0xE1, 0x7A, 0x2D, 0x14, 0x01 );
	// VEX.128.F3.0F.W1 2D /r VCVTSS2SI r64, xmm1/m32
	_TEST64_VEX( "c4e1fa2d1401 vcvtss2si rdx,dword ptr [rcx+rax]", 0xC4, 0xE1, 0xFA, 0x2D, 0x14, 0x01 );

	// CVTSS2SD
	_TEST64( "f30f5a4020 cvtss2sd xmm0,dword ptr [rax+0000000000000020h]", 0xF3, 0x0F, 0x5A, 0x40, 0x20 );
	_TEST32( "f30f5ac2 cvtss2sd xmm0,xmm2", 0xF3, 0x0F, 0x5A, 0xC2 );
	_TEST32( "f30f5a4020 cvtss2sd xmm0,dword ptr [eax+00000020h]", 0xF3, 0x0F, 0x5A, 0x40, 0x20 );
	// VEX.NDS.128.F3.0F 5A /r VCVTSS2SD xmm1, xmm2, xmm3/m32
	_TEST32_VEX( "c4e1725a1401 vcvtss2sd xmm2,xmm1,dword ptr [ecx+eax]", 0xC4, 0xE1, 0x72, 0x5A, 0x14, 0x01 );
	_TEST64_VEX( "c4e1625a1401 vcvtss2sd xmm2,xmm3,dword ptr [rcx+rax]", 0xC4, 0xE1, 0x62, 0x5A, 0x14, 0x01 );

	// CVTSI2SS
	_TEST64( "f3480f2ac2 cvtsi2ss xmm0,rdx", 0xF3, 0x48, 0x0F, 0x2A, 0xC2 );
	_TEST64( "f30f2a4020 cvtsi2ss xmm0,dword ptr [rax+0000000000000020h]", 0xF3, 0x0F, 0x2A, 0x40, 0x20 );
	_TEST32( "f30f2ac2 cvtsi2ss xmm0,edx", 0xF3, 0x0F, 0x2A, 0xC2 );
	_TEST32( "f30f2a4020 cvtsi2ss xmm0,dword ptr [eax+00000020h]", 0xF3, 0x0F, 0x2A, 0x40, 0x20 );
	_TEST64( "f30f2a4020 cvtsi2ss xmm0,dword ptr [rax+0000000000000020h]", 0xF3, 0x0F, 0x2A, 0x40, 0x20 );
	_TEST64( "f30f2ac2 cvtsi2ss xmm0,edx", 0xF3, 0x0F, 0x2A, 0xC2 );
	// VEX.NDS.128.F3.0F.W0 2A /r VCVTSI2SS xmm1, xmm2, r/m32
	_TEST32_VEX( "c4e1422a1401 vcvtsi2ss xmm2,xmm7,dword ptr [ecx+eax]", 0xC4, 0xE1, 0x42, 0x2A, 0x14, 0x01 );
	_TEST64_VEX( "c4e1422a1401 vcvtsi2ss xmm2,xmm7,dword ptr [rcx+rax]", 0xC4, 0xE1, 0x42, 0x2A, 0x14, 0x01 );
	// VEX.NDS.128.F3.0F.W1 2A /r VCVTSI2SS xmm1, xmm2, r/m64
	_TEST64_VEX( "c4e1c22a1401 vcvtsi2ss xmm2,xmm7,qword ptr [rcx+rax]", 0xC4, 0xE1, 0xC2, 0x2A, 0x14, 0x01 );

	// CVTSI2SD
	_TEST64( "f20f2a4020 cvtsi2sd xmm0,dword ptr [rax+0000000000000020h]", 0xF2, 0x0F, 0x2A, 0x40, 0x20 );
	_TEST32( "f20f2ac2 cvtsi2sd xmm0,edx", 0xF2, 0x0F, 0x2A, 0xC2 );
	_TEST32( "f20f2a4020 cvtsi2sd xmm0,dword ptr [eax+00000020h]", 0xF2, 0x0F, 0x2A, 0x40, 0x20 );
	_TEST64( "f20f2a4020 cvtsi2sd xmm0,dword ptr [rax+0000000000000020h]", 0xF2, 0x0F, 0x2A, 0x40, 0x20 );
	_TEST64( "f20f2ac2 cvtsi2sd xmm0,edx", 0xF2, 0x0F, 0x2A, 0xC2 );
	_TEST64( "f2480f2ac2 cvtsi2sd xmm0,rdx", 0xF2, 0x48, 0x0F, 0x2A, 0xC2 );
	// VEX.NDS.128.F2.0F.W0 2A /r VCVTSI2SD xmm1, xmm2, r/m32
	_TEST32_VEX( "c4e1432a1401 vcvtsi2sd xmm2,xmm7,dword ptr [ecx+eax]", 0xC4, 0xE1, 0x43, 0x2A, 0x14, 0x01 );
	_TEST64_VEX( "c4e1432a1401 vcvtsi2sd xmm2,xmm7,dword ptr [rcx+rax]", 0xC4, 0xE1, 0x43, 0x2A, 0x14, 0x01 );
	// VEX.NDS.128.F2.0F.W1 2A /r VCVTSI2SD xmm1, xmm2, r/m64
	_TEST64_VEX( "c4e1c32a1401 vcvtsi2sd xmm2,xmm7,qword ptr [rcx+rax]", 0xC4, 0xE1, 0xC3, 0x2A, 0x14, 0x01 );

	// CVTSD2SS
	_TEST64( "f20f5a4020 cvtsd2ss xmm0,qword ptr [rax+0000000000000020h]", 0xF2, 0x0F, 0x5A, 0x40, 0x20 );
	_TEST32( "f20f5ac2 cvtsd2ss xmm0,xmm2", 0xF2, 0x0F, 0x5A, 0xC2 );
	_TEST32( "f20f5a4020 cvtsd2ss xmm0,qword ptr [eax+00000020h]", 0xF2, 0x0F, 0x5A, 0x40, 0x20 );
	// VEX.NDS.128.F2.0F 5A /r VCVTSD2SS xmm1,xmm2,xmm3/m64
	_TEST32_VEX( "c4e14b5a1401 vcvtsd2ss xmm2,xmm6,qword ptr [ecx+eax]", 0xC4, 0xE1, 0x4B, 0x5A, 0x14, 0x01 );
	_TEST64_VEX( "c4e14b5a1401 vcvtsd2ss xmm2,xmm6,qword ptr [rcx+rax]", 0xC4, 0xE1, 0x4B, 0x5A, 0x14, 0x01 );

	// CVTSD2SI
	_TEST64( "f20f2d4020 cvtsd2si eax,qword ptr [rax+0000000000000020h]", 0xF2, 0x0F, 0x2D, 0x40, 0x20 );
	_TEST32( "f20f2dc2 cvtsd2si eax,xmm2", 0xF2, 0x0F, 0x2D, 0xC2 );
	_TEST32( "f20f2d4020 cvtsd2si eax,qword ptr [eax+00000020h]", 0xF2, 0x0F, 0x2D, 0x40, 0x20 );
	_TEST64( "f2480f2d4020 cvtsd2si rax,qword ptr [rax+0000000000000020h]", 0xF2, 0x48, 0x0F, 0x2D, 0x40, 0x20 );
	// VEX.128.F2.0F.W0 2D /r VCVTSD2SI r32, xmm1/m64
	_TEST32_VEX( "c4e17b2d1401 vcvtsd2si edx,qword ptr [ecx+eax]", 0xC4, 0xE1, 0x7B, 0x2D, 0x14, 0x01 );
	_TEST64_VEX( "c4e17b2d1401 vcvtsd2si edx,qword ptr [rcx+rax]", 0xC4, 0xE1, 0x7B, 0x2D, 0x14, 0x01 );
	// VEX.128.F2.0F.W1 2D /r VCVTSD2SI r64, xmm1/m64
	_TEST64_VEX( "c4e1fb2d1401 vcvtsd2si rdx,qword ptr [rcx+rax]", 0xC4, 0xE1, 0xFB, 0x2D, 0x14, 0x01 );

	// CVTPS2PI
	_TEST64( "0f2d4020 cvtps2pi mm0,qword ptr [rax+0000000000000020h]", 0x0F, 0x2D, 0x40, 0x20 );
	_TEST32( "0f2dc2 cvtps2pi mm0,xmm2", 0x0F, 0x2D, 0xC2 );
	_TEST32( "0f2d4020 cvtps2pi mm0,qword ptr [eax+00000020h]", 0x0F, 0x2D, 0x40, 0x20 );

	// CVTPS2PD
	_TEST64( "0f5a4020 cvtps2pd xmm0,qword ptr [rax+0000000000000020h]", 0x0F, 0x5A, 0x40, 0x20 );
	_TEST32( "0f5ac2 cvtps2pd xmm0,xmm2", 0x0F, 0x5A, 0xC2 );
	_TEST32( "0f5a4020 cvtps2pd xmm0,qword ptr [eax+00000020h]", 0x0F, 0x5A, 0x40, 0x20 );
	// VEX.128.0F 5A /r VCVTPS2PD xmm1, xmm2/m64
	// VEX.256.0F 5A /r VCVTPS2PD ymm1, xmm2/m128
	_TEST32_VEX( "c4e1785a1401 vcvtps2pd xmm2,oword ptr [ecx+eax]", 0xC4, 0xE1, 0x78, 0x5A, 0x14, 0x01 );
	_TEST64_VEX( "c4e17c5a1401 vcvtps2pd ymm2,ymmword ptr [rcx+rax]", 0xC4, 0xE1, 0x7C, 0x5A, 0x14, 0x01 );

	// CVTPS2DQ
	_TEST64( "660f5b4020 cvtps2dq xmm0,oword ptr [rax+0000000000000020h]", 0x66, 0x0F, 0x5B, 0x40, 0x20 );
	_TEST32( "660f5bc2 cvtps2dq xmm0,xmm2", 0x66, 0x0F, 0x5B, 0xC2 );
	_TEST32( "660f5b4020 cvtps2dq xmm0,oword ptr [eax+00000020h]", 0x66, 0x0F, 0x5B, 0x40, 0x20 );
	// VEX.128.66.0F 5B /r VCVTPS2DQ xmm1, xmm2/m128
	// VEX.256.66.0F 5B /r VCVTPS2DQ ymm1, ymm2/m256
	_TEST32_VEX( "c4e1795b1401 vcvtps2dq xmm2,oword ptr [ecx+eax]", 0xC4, 0xE1, 0x79, 0x5B, 0x14, 0x01 );
	_TEST64_VEX( "c4e17d5b1401 vcvtps2dq ymm2,ymmword ptr [rcx+rax]", 0xC4, 0xE1, 0x7D, 0x5B, 0x14, 0x01 );

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
	// VEX.128.F2.0F E6 /r VCVTPD2DQ xmm1, xmm2/m128
	// VEX.256.F2.0F E6 /r VCVTPD2DQ xmm1, ymm2/m256
	_TEST32_VEX( "c4e17be61401 vcvtpd2dq xmm2,oword ptr [ecx+eax]", 0xC4, 0xE1, 0x7B, 0xE6, 0x14, 0x01 );
	_TEST64_VEX( "c4e17fe61401 vcvtpd2dq ymm2,ymmword ptr [rcx+rax]", 0xC4, 0xE1, 0x7F, 0xE6, 0x14, 0x01 );

	// CVTPD2PS
	// 66 0F 5A /r CVTPD2PS xmm1,xmm2/m128 A Valid Valid Convert two packed doubleprecision floating-point values in xmm2/m128 to two packed single-precision floating-point values in xmm1.
	_TEST64( "660f5a4020 cvtpd2ps xmm0,oword ptr [rax+0000000000000020h]", 0x66, 0x0F, 0x5A, 0x40, 0x20 );
	_TEST32( "660f5ac2 cvtpd2ps xmm0,xmm2", 0x66, 0x0F, 0x5A, 0xC2 );
	_TEST32( "660f5a4020 cvtpd2ps xmm0,oword ptr [eax+00000020h]", 0x66, 0x0F, 0x5A, 0x40, 0x20 );
	// VEX.128.66.0F 5A /r VCVTPD2PS xmm1, xmm2/m128
	// VEX.256.66.0F 5A /r VCVTPD2PS xmm1, ymm2/m256
	_TEST32_VEX( "c4e1795a1401 vcvtpd2ps xmm2,oword ptr [ecx+eax]", 0xC4, 0xE1, 0x79, 0x5A, 0x14, 0x01 );
	_TEST64_VEX( "c4e17d5a1401 vcvtpd2ps ymm2,ymmword ptr [rcx+rax]", 0xC4, 0xE1, 0x7D, 0x5A, 0x14, 0x01 );

	// CVTDQ2PS
	_TEST64( "0f5b4020 cvtdq2ps xmm0,oword ptr [rax+0000000000000020h]", 0x0F, 0x5b, 0x40, 0x20 );
	_TEST32( "0f5bc2 cvtdq2ps xmm0,xmm2", 0x0F, 0x5b, 0xC2 );
	_TEST32( "0f5b4020 cvtdq2ps xmm0,oword ptr [eax+00000020h]", 0x0F, 0x5b, 0x40, 0x20 );
	// VEX.128.0F 5B /r VCVTDQ2PS xmm1, xmm2/m128
	// VEX.256.0F 5B /r VCVTDQ2PS ymm1, ymm2/m256
	_TEST32_VEX( "c4e1785b1401 vcvtdq2ps xmm2,oword ptr [ecx+eax]", 0xC4, 0xE1, 0x78, 0x5B, 0x14, 0x01 );
	_TEST64_VEX( "c4e17c5b1401 vcvtdq2ps ymm2,ymmword ptr [rcx+rax]", 0xC4, 0xE1, 0x7C, 0x5B, 0x14, 0x01 );

	// CVTDQ2PD
	_TEST64( "f30fe64020 cvtdq2pd xmm0,qword ptr [rax+0000000000000020h]", 0xF3, 0x0F, 0xE6, 0x40, 0x20, 0x50 );
	_TEST32( "f30fe6c2 cvtdq2pd xmm0,xmm2", 0xF3, 0x0F, 0xE6, 0xC2 );
	_TEST32( "f30fe64020 cvtdq2pd xmm0,qword ptr [eax+00000020h]", 0xF3, 0x0F, 0xE6, 0x40, 0x20, 0x50 );
	// VEX.128.F3.0F E6 /r VCVTDQ2PD xmm1, xmm2/m64
	_TEST32_VEX( "c4e17ae61401 vcvtdq2pd xmm2,qword ptr [ecx+eax]", 0xC4, 0xE1, 0x7A, 0xE6, 0x14, 0x01 );
	_TEST64_VEX( "c4417ae61401 vcvtdq2pd xmm10,qword ptr [r9+rax]", 0xC4, 0x41, 0x7A, 0xE6, 0x14, 0x01 );
	// VEX.256.F3.0F E6 /r VCVTDQ2PD ymm1, xmm2/m128
	_TEST32_VEX( "c4e17ee61401 vcvtdq2pd ymm2,oword ptr [ecx+eax]", 0xC4, 0xE1, 0x7E, 0xE6, 0x14, 0x01 );
	_TEST64_VEX( "c4417ee61401 vcvtdq2pd ymm10,oword ptr [r9+rax]", 0xC4, 0x41, 0x7E, 0xE6, 0x14, 0x01 );

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
	// VEX.128.0F 2F /r VCOMISS xmm1, xmm2/m32
	_TEST32_VEX( "c4e1782f1401 vcomiss xmm2,qword ptr [ecx+eax]", 0xC4, 0xE1, 0x78, 0x2F, 0x14, 0x01 );
	_TEST64_VEX( "c441782f1401 vcomiss xmm10,qword ptr [r9+rax]", 0xC4, 0x41, 0x78, 0x2F, 0x14, 0x01 );

	// COMISD
	_TEST64( "660f2fc2 comisd xmm0,xmm2", 0x66, 0x0F, 0x2F, 0xC2, 0x40, 0x20, 0x50 );
	_TEST64( "660f2f4020 comisd xmm0,qword ptr [rax+0000000000000020h]", 0x66, 0x0F, 0x2F, 0x40, 0x20, 0x50 );
	_TEST32( "660f2fc2 comisd xmm0,xmm2", 0x66, 0x0F, 0x2F, 0xC2 );
	_TEST32( "660f2f4020 comisd xmm0,qword ptr [eax+00000020h]", 0x66, 0x0F, 0x2F, 0x40, 0x20, 0x50 );
	// VEX.128.66.0F 2F /r VCOMISD xmm1, xmm2/m64
	_TEST32_VEX( "c4e1792f1401 vcomisd xmm2,qword ptr [ecx+eax]", 0xC4, 0xE1, 0x79, 0x2F, 0x14, 0x01 );
	_TEST64_VEX( "c441792f1401 vcomisd xmm10,qword ptr [r9+rax]", 0xC4, 0x41, 0x79, 0x2F, 0x14, 0x01 );

	// CMPPD
	_TEST32( "660fc21401ff cmppd xmm2,oword ptr [ecx+eax],0ffh", 0x66, 0x0F, 0xC2, 0x14, 0x01, 0xFF );
	_TEST64( "660fc21401ff cmppd xmm2,oword ptr [rcx+rax],0ffh", 0x66, 0x0F, 0xC2, 0x14, 0x01, 0xFF );
	// VEX.NDS.128.66.0F C2 /r ib VCMPPD xmm1, xmm2, xmm3/m128, imm8
	// VEX.NDS.256.66.0F C2 /r ib VCMPPD ymm1, ymm2, ymm3/m256, imm8
	_TEST64_VEX( "c4410dc2140120 vcmppd ymm10,ymm14,ymmword ptr [r9+rax],20h", 0xC4, 0x41, 0x0D, 0xC2, 0x14, 0x01, 0x20 );
	_TEST32_VEX( "c4c141c2140120 vcmppd xmm2,xmm7,oword ptr [ecx+eax],20h", 0xC4, 0xC1, 0x41, 0xC2, 0x14, 0x01, 0x20 );
	_TEST32_VEX( "c4c169c2140120 vcmppd xmm2,xmm2,oword ptr [ecx+eax],20h", 0xC4, 0xC1, 0x69, 0xC2, 0x14, 0x01, 0x20 );

	// CMPPS
	_TEST32( "0fc21401ff cmpps xmm2,oword ptr [ecx+eax],0ffh", 0x0F, 0xC2, 0x14, 0x01, 0xFF );
	_TEST64( "0fc21401ff cmpps xmm2,oword ptr [rcx+rax],0ffh", 0x0F, 0xC2, 0x14, 0x01, 0xFF );
	// VEX.NDS.128.0F C2 /r ib VCMPPS xmm1, xmm2, xmm3/m128, imm8
	// VEX.NDS.256.0F C2 /r ib VCMPPS ymm1, ymm2, ymm3/m256, imm8
	_TEST64_VEX( "c4410cc2140120 vcmpps ymm10,ymm14,ymmword ptr [r9+rax],20h", 0xC4, 0x41, 0x0C, 0xC2, 0x14, 0x01, 0x20 );
	_TEST64_VEX( "c4c108c2140120 vcmpps xmm2,xmm14,oword ptr [r9+rax],20h", 0xC4, 0xC1, 0x08, 0xC2, 0x14, 0x01, 0x20 );
	_TEST32_VEX( "c4c168c2140120 vcmpps xmm2,xmm2,oword ptr [ecx+eax],20h", 0xC4, 0xC1, 0x68, 0xC2, 0x14, 0x01, 0x20 );

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

	// TODO: Testy dla CMP,

	// CMPSS
	// dodac support dla mmword i odkomentowac.
	_TEST64( "f30fc2402050 cmpss xmm0,dword ptr [rax+0000000000000020h],50h", 0xF3, 0x0F, 0xC2, 0x40, 0x20, 0x50 );
	_TEST32( "f30fc2402050 cmpss xmm0,dword ptr [eax+00000020h],50h", 0xF3, 0x0F, 0xC2, 0x40, 0x20, 0x50 );
	// VEX.NDS.128.F3.0F C2 /r ib VCMPSS xmm1, xmm2, xmm3/m32, imm8
	_TEST32_VEX( "c4e142c2140120 vcmpss xmm2,xmm7,dword ptr [ecx+eax],20h", 0xC4, 0xE1, 0x42, 0xC2, 0x14, 0x01, 0x20 );
	_TEST64_VEX( "c4410ac2140120 vcmpss xmm10,xmm14,dword ptr [r9+rax],20h", 0xC4, 0x41, 0x0A, 0xC2, 0x14, 0x01, 0x20 );

	// CMPSD
	_TEST32( "f20fc2402050 cmpsd xmm0,qword ptr [eax+00000020h],50h", 0xF2, 0x0F, 0xC2, 0x40, 0x20, 0x50 );
	_TEST64( "f20fc2402050 cmpsd xmm0,qword ptr [rax+0000000000000020h],50h", 0xF2, 0x0F, 0xC2, 0x40, 0x20, 0x50 );
	// VEX.NDS.128.F2.0F C2 /r ib VCMPSD xmm1, xmm2, xmm3/m64, imm8
	_TEST32_VEX( "c4e143c2140120 vcmpsd xmm2,xmm7,qword ptr [ecx+eax],20h", 0xC4, 0xE1, 0x43, 0xC2, 0x14, 0x01, 0x20 );
	_TEST64_VEX( "c4410bc2140120 vcmpsd xmm10,xmm14,qword ptr [r9+rax],20h", 0xC4, 0x41, 0x0B, 0xC2, 0x14, 0x01, 0x20 );

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
	// 66 0F 58 /r ADDPD xmm1, xmm2/m128
	_TEST32( "660f581401 addpd xmm2,oword ptr [ecx+eax]", 0x66, 0x0F, 0x58, 0x14, 0x01 );
	_TEST64( "660f581401 addpd xmm2,oword ptr [rcx+rax]", 0x66, 0x0F, 0x58, 0x14, 0x01 );
	// VADDPD
	// VEX.NDS.128.66.0F 58 /r VADDPD xmm1,xmm2, xmm3/m128
	// VAX.X
	_TEST64_VEX( "c4010d581401 vaddpd ymm10,ymm14,ymmword ptr [r9+r8]", 0xC4, 0x01, 0x0D, 0x58, 0x14, 0x01 );
	// VAX.R VAX.B (3 byte VAX prefix.)
	_TEST64_VEX( "c4410d581401 vaddpd ymm10,ymm14,ymmword ptr [r9+rax]", 0xC4, 0x41, 0x0D, 0x58, 0x14, 0x01 );
	_TEST64_VEX( "c4c109581401 vaddpd xmm2,xmm14,oword ptr [r9+rax]", 0xC4, 0xC1, 0x09, 0x58, 0x14, 0x01 );
	_TEST32_VEX( "c4c169581401 vaddpd xmm2,xmm2,oword ptr [ecx+eax]", 0xC4, 0xC1, 0x69, 0x58, 0x14, 0x01 );
	// VAX.mmmm
	_TEST32_VEX( "c4c16d581401 vaddpd ymm2,ymm2,ymmword ptr [ecx+eax]", 0xC4, 0xC1, 0x6D, 0x58, 0x14, 0x01 );
	// VAX.L (0)
	_TEST32_VEX( "c5f9581401 vaddpd xmm2,xmm0,oword ptr [ecx+eax]", 0xC5, 0xF9, 0x58, 0x14, 0x01 );
	/// VAX.R (2 byte VAX prefix.)
	_TEST64_VEX( "c55d581401 vaddpd ymm10,ymm4,ymmword ptr [rcx+rax]", 0xC5, 0x5D, 0x58, 0x14, 0x01 );
	// VAX.vvvv, VAX.L(1), VAX.pp
	_TEST32_VEX( "c5fd581401 vaddpd ymm2,ymm0,ymmword ptr [ecx+eax]", 0xC5, 0xFD, 0x58, 0x14, 0x01 );

	// ADDPS
	_TEST32( "0f581401 addps xmm2,oword ptr [ecx+eax]", 0x0F, 0x58, 0x14, 0x01 );
	_TEST64( "0f581401 addps xmm2,oword ptr [rcx+rax]", 0x0F, 0x58, 0x14, 0x01 );

	// ADDSD
	_TEST32( "f20f581401 addsd xmm2,qword ptr [ecx+eax]", 0xF2, 0x0F, 0x58, 0x14, 0x01 );
	_TEST64( "f20f581401 addsd xmm2,qword ptr [rcx+rax]", 0xF2, 0x0F, 0x58, 0x14, 0x01 );
	// VADDSD
	_TEST32_VEX( "c4e153581401 vaddsd xmm2,xmm5,qword ptr [ecx+eax]", 0xC4, 0xE1, 0x53, 0x58, 0x14, 0x01 );
	_TEST32_VEX( "c5db581401 vaddsd xmm2,xmm4,qword ptr [ecx+eax]", 0xC5, 0xDB, 0x58, 0x14, 0x01 );
	// TODO: W tym przypadku powinno zdekodowa� do FAIL, a wybiera inna instrukcj� poniewa� instrukcja ta nie posiada mandatory opcodes.
	// Trzeba b�dzie jakos obs�ugiwa� instrukcje ktotre nie wymagaja manadatory opcode, zeby nie byly wybierane, jak
	// jakis mandatory opcode wystepuje.
	// _TEST32_VEX( "FAIL", 0xC5, 0xDF, 0x58, 0x14, 0x01 );


	// ADDSS
	_TEST32( "f30f581401 addss xmm2,dword ptr [ecx+eax]", 0xF3, 0x0F, 0x58, 0x14, 0x01 );
	_TEST64( "f30f581401 addss xmm2,dword ptr [rcx+rax]", 0xF3, 0x0F, 0x58, 0x14, 0x01 );
	// VEX.NDS.128.F3.0F 58 /r VADDSS xmm1,xmm2, xmm3/m32
	_TEST32_VEX( "c4e152581401 vaddss xmm2,xmm5,dword ptr [ecx+eax]", 0xC4, 0xE1, 0x52, 0x58, 0x14, 0x01 );
	_TEST32_VEX( "c5da581401 vaddss xmm2,xmm4,dword ptr [ecx+eax]", 0xC5, 0xDA, 0x58, 0x14, 0x01 );

	// ADDSUBPD
	_TEST32( "660fd01401 addsubpd xmm2,oword ptr [ecx+eax]", 0x66, 0x0F, 0xD0, 0x14, 0x01 );
	_TEST64( "660fd01401 addsubpd xmm2,oword ptr [rcx+rax]", 0x66, 0x0F, 0xD0, 0x14, 0x01 );
	// VEX.NDS.128.66.0F D0 /r VADDSUBPD xmm1,xmm2,xmm3/m128
	// VEX.NDS.256.66.0F D0 /r VADDSUBPD ymm1, ymm2,ymm3/m256
	_TEST64_VEX( "c4410dd01401 vaddsubpd ymm10,ymm14,ymmword ptr [r9+rax]", 0xC4, 0x41, 0x0D, 0xD0, 0x14, 0x01 );
	_TEST32_VEX( "c4c141d01401 vaddsubpd xmm2,xmm7,oword ptr [ecx+eax]", 0xC4, 0xC1, 0x41, 0xD0, 0x14, 0x01 );
	_TEST32_VEX( "c4c169d01401 vaddsubpd xmm2,xmm2,oword ptr [ecx+eax]", 0xC4, 0xC1, 0x69, 0xD0, 0x14, 0x01 );

	// ADDSUBPS
	_TEST32( "f20fd01401 addsubps xmm2,oword ptr [ecx+eax]", 0xf2, 0x0F, 0xD0, 0x14, 0x01 );
	_TEST64( "f20fd01401 addsubps xmm2,oword ptr [rcx+rax]", 0xf2, 0x0F, 0xD0, 0x14, 0x01 );
	// VEX.NDS.128.F2.0F D0 /r VADDSUBPS xmm1,xmm2,xmm3/m128
	// VEX.NDS.256.F2.0F D0 /r VADDSUBPS ymm1, ymm2,ymm3/m256
	_TEST64_VEX( "c4410fd01401 vaddsubps ymm10,ymm14,ymmword ptr [r9+rax]", 0xC4, 0x41, 0x0F, 0xD0, 0x14, 0x01 );
	_TEST64_VEX( "c4c10bd01401 vaddsubps xmm2,xmm14,oword ptr [r9+rax]", 0xC4, 0xC1, 0x0B, 0xD0, 0x14, 0x01 );
	_TEST32_VEX( "c4c16bd01401 vaddsubps xmm2,xmm2,oword ptr [ecx+eax]", 0xC4, 0xC1, 0x6B, 0xD0, 0x14, 0x01 );
	_TEST32_VEX( "c5cbd01401 vaddsubps xmm2,xmm6,oword ptr [ecx+eax]", 0xC5, 0xCB, 0xD0, 0x14, 0x01 );

	// AESDEC
	_TEST32( "660f38de1401 aesdec xmm2,oword ptr [ecx+eax]", 0x66, 0x0F, 0x38, 0xDE, 0x14, 0x01 );
	_TEST64( "660f38de1401 aesdec xmm2,oword ptr [rcx+rax]", 0x66, 0x0F, 0x38, 0xDE, 0x14, 0x01 );
	// VEX.NDS.128.66.0F38.WIG DE /r VAESDEC xmm1,xmm2,xmm3/m128
	_TEST32_VEX( "c4e261de00 vaesdec xmm0,xmm3,oword ptr [eax]", 0xC4, 0xE2, 0x61, 0xDE, 0x00 );
	_TEST32_VEX( "c4e261dec0 vaesdec xmm0,xmm3,xmm0", 0xC4, 0xE2, 0x61, 0xDE, 0xC0 );
	_TEST64_VEX( "c4e261de00 vaesdec xmm0,xmm3,oword ptr [rax]", 0xC4, 0xE2, 0x61, 0xDE, 0x00 );

	// AESDECLAST
	_TEST32( "660f38df1401 aesdeclast xmm2,oword ptr [ecx+eax]", 0x66, 0x0F, 0x38, 0xDF, 0x14, 0x01 );
	_TEST64( "660f38df1401 aesdeclast xmm2,oword ptr [rcx+rax]", 0x66, 0x0F, 0x38, 0xDF, 0x14, 0x01 );
	// VEX.NDS.128.66.0F38.WIG DF /r VAESDECLAST xmm1,xmm2,xmm3/m128
	_TEST32_VEX( "c4e261df00 vaesdeclast xmm0,xmm3,oword ptr [eax]", 0xC4, 0xE2, 0x61, 0xDF, 0x00 );
	_TEST32_VEX( "c4e261dfc0 vaesdeclast xmm0,xmm3,xmm0", 0xC4, 0xE2, 0x61, 0xDF, 0xC0 );
	_TEST64_VEX( "c4e261df00 vaesdeclast xmm0,xmm3,oword ptr [rax]", 0xC4, 0xE2, 0x61, 0xDF, 0x00 );

	// AESENC
	_TEST32( "660f38dc1401 aesenc xmm2,oword ptr [ecx+eax]", 0x66, 0x0F, 0x38, 0xDC, 0x14, 0x01 );
	_TEST64( "660f38dc1401 aesenc xmm2,oword ptr [rcx+rax]", 0x66, 0x0F, 0x38, 0xDC, 0x14, 0x01 );
	// VEX.NDS.128.66.0F38.WIG DC /r VAESENC xmm1, xmm2, xmm3/m128
	_TEST32_VEX( "c4e261dc00 vaesenc xmm0,xmm3,oword ptr [eax]", 0xC4, 0xE2, 0x61, 0xDC, 0x00 );
	_TEST32_VEX( "c4e261dcc0 vaesenc xmm0,xmm3,xmm0", 0xC4, 0xE2, 0x61, 0xDC, 0xC0 );
	_TEST64_VEX( "c4e261dc00 vaesenc xmm0,xmm3,oword ptr [rax]", 0xC4, 0xE2, 0x61, 0xDC, 0x00 );

	// AESENCLAST
	_TEST32( "660f38dd1401 aesenclast xmm2,oword ptr [ecx+eax]", 0x66, 0x0F, 0x38, 0xDD, 0x14, 0x01 );
	_TEST64( "660f38dd1401 aesenclast xmm2,oword ptr [rcx+rax]", 0x66, 0x0F, 0x38, 0xDD, 0x14, 0x01 );
	// VEX.NDS.128.66.0F38.WIG DD /r VAESENCLAST xmm1,xmm2,xmm3/m128
	_TEST32_VEX( "c4e261dd00 vaesenclast xmm0,xmm3,oword ptr [eax]", 0xC4, 0xE2, 0x61, 0xDD, 0x00 );
	_TEST32_VEX( "c4e261ddc0 vaesenclast xmm0,xmm3,xmm0", 0xC4, 0xE2, 0x61, 0xDD, 0xC0 );
	_TEST64_VEX( "c4e261dd00 vaesenclast xmm0,xmm3,oword ptr [rax]", 0xC4, 0xE2, 0x61, 0xDD, 0x00 );

	// AESIMC
	_TEST32( "660f38db1401 aesimc xmm2,oword ptr [ecx+eax]", 0x66, 0x0F, 0x38, 0xDB, 0x14, 0x01 );
	_TEST64( "660f38db1401 aesimc xmm2,oword ptr [rcx+rax]", 0x66, 0x0F, 0x38, 0xDB, 0x14, 0x01 );
	// VEX.128.66.0F38.WIG DB /r VAESIMC xmm1, xmm2/m128
	_TEST32_VEX( "c4e261db00 vaesimc xmm0,xmm3,oword ptr [eax]", 0xC4, 0xE2, 0x61, 0xDB, 0x00 );
	_TEST32_VEX( "c4e261dbc0 vaesimc xmm0,xmm3,xmm0", 0xC4, 0xE2, 0x61, 0xDB, 0xC0 );
	_TEST64_VEX( "c4e261db00 vaesimc xmm0,xmm3,oword ptr [rax]", 0xC4, 0xE2, 0x61, 0xDB, 0x00 );

	// AESKEYGENASSIST
	_TEST32( "660f3adf1401ff aeskeygenassist xmm2,oword ptr [ecx+eax],0ffh", 0x66, 0x0F, 0x3a, 0xDF, 0x14, 0x01, 0xFF );
	_TEST64( "660f3adf1401ff aeskeygenassist xmm2,oword ptr [rcx+rax],0ffh", 0x66, 0x0F, 0x3a, 0xDF, 0x14, 0x01, 0xFF );
	// VEX.128.66.0F3A.WIG DF /r ib VAESKEYGENASSIST xmm1,xmm2/m128,imm8
	_TEST32_VEX( "c4e379df00ff vaeskeygenassist xmm0,oword ptr [eax],0ffh", 0xC4, 0xE3, 0x79, 0xDF, 0x00, 0xFF );
	_TEST32_VEX( "c4e379dfc0ff vaeskeygenassist xmm0,xmm0,0ffh", 0xC4, 0xE3, 0x79, 0xDF, 0xC0, 0xFF );

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
	// VEX.NDS.128.66.0F 54 /r VANDPD xmm1,xmm2,xmm3/m128
	// VEX.NDS.256.66.0F 54 /r VANDPD ymm1,ymm2,ymm3/m256
	_TEST64_VEX( "c4410d541401 vandpd ymm10,ymm14,ymmword ptr [r9+rax]", 0xC4, 0x41, 0x0D, 0x54, 0x14, 0x01 );
	_TEST32_VEX( "c4c141541401 vandpd xmm2,xmm7,oword ptr [ecx+eax]", 0xC4, 0xC1, 0x41, 0x54, 0x14, 0x01 );
	_TEST32_VEX( "c4c169541401 vandpd xmm2,xmm2,oword ptr [ecx+eax]", 0xC4, 0xC1, 0x69, 0x54, 0x14, 0x01 );
	_TEST32_VEX( "c5c9541401 vandpd xmm2,xmm6,oword ptr [ecx+eax]", 0xC5, 0xC9, 0x54, 0x14, 0x01 );

	// ANDPS
	_TEST32( "0f541401 andps xmm2,oword ptr [ecx+eax]", 0x0F, 0x54, 0x14, 0x01 );
	_TEST64( "0f541401 andps xmm2,oword ptr [rcx+rax]", 0x0F, 0x54, 0x14, 0x01 );
	// VEX.NDS.128.0F 54 /r VANDPS xmm1,xmm2, xmm3/m128
	// VEX.NDS.256.0F 54 /r VANDPS ymm1, ymm2, ymm3/m256
	_TEST64_VEX( "c4410c541401 vandps ymm10,ymm14,ymmword ptr [r9+rax]", 0xC4, 0x41, 0x0C, 0x54, 0x14, 0x01 );
	_TEST32_VEX( "c4c140541401 vandps xmm2,xmm7,oword ptr [ecx+eax]", 0xC4, 0xC1, 0x40, 0x54, 0x14, 0x01 );
	_TEST32_VEX( "c4c168541401 vandps xmm2,xmm2,oword ptr [ecx+eax]", 0xC4, 0xC1, 0x68, 0x54, 0x14, 0x01 );
	_TEST32_VEX( "c5c8541401 vandps xmm2,xmm6,oword ptr [ecx+eax]", 0xC5, 0xC8, 0x54, 0x14, 0x01 );

	// ANDNPD
	_TEST32( "660f551401 andnpd xmm2,oword ptr [ecx+eax]", 0x66, 0x0F, 0x55, 0x14, 0x01 );
	_TEST64( "660f551401 andnpd xmm2,oword ptr [rcx+rax]", 0x66, 0x0F, 0x55, 0x14, 0x01 );
	// VEX.NDS.128.66.0F 55 /r VANDNPD xmm1,xmm2,xmm3/m128
	// VEX.NDS.256.66.0F 55 /r VANDNPD ymm1,ymm2,ymm3/m256
	_TEST64_VEX( "c4410d551401 vandnpd ymm10,ymm14,ymmword ptr [r9+rax]", 0xC4, 0x41, 0x0D, 0x55, 0x14, 0x01 );
	_TEST32_VEX( "c4c141551401 vandnpd xmm2,xmm7,oword ptr [ecx+eax]", 0xC4, 0xC1, 0x41, 0x55, 0x14, 0x01 );
	_TEST32_VEX( "c4c169551401 vandnpd xmm2,xmm2,oword ptr [ecx+eax]", 0xC4, 0xC1, 0x69, 0x55, 0x14, 0x01 );
	_TEST32_VEX( "c5c9551401 vandnpd xmm2,xmm6,oword ptr [ecx+eax]", 0xC5, 0xC9, 0x55, 0x14, 0x01 );

	// ANDNPS
	_TEST32( "0f551401 andnps xmm2,oword ptr [ecx+eax]", 0x0F, 0x55, 0x14, 0x01 );
	_TEST64( "0f551401 andnps xmm2,oword ptr [rcx+rax]", 0x0F, 0x55, 0x14, 0x01 );
	// VEX.NDS.128.0F 55 /r VANDNPS xmm1,xmm2,xmm3/m128
	// VEX.NDS.256.0F 55 /r VANDNPS ymm1,ymm2,ymm3/m256
	_TEST64_VEX( "c4410c551401 vandnps ymm10,ymm14,ymmword ptr [r9+rax]", 0xC4, 0x41, 0x0C, 0x55, 0x14, 0x01 );
	_TEST32_VEX( "c4c140551401 vandnps xmm2,xmm7,oword ptr [ecx+eax]", 0xC4, 0xC1, 0x40, 0x55, 0x14, 0x01 );
	_TEST32_VEX( "c4c168551401 vandnps xmm2,xmm2,oword ptr [ecx+eax]", 0xC4, 0xC1, 0x68, 0x55, 0x14, 0x01 );
	_TEST32_VEX( "c5c8551401 vandnps xmm2,xmm6,oword ptr [ecx+eax]", 0xC5, 0xC8, 0x55, 0x14, 0x01 );

	// ARPL
	_TEST32( "631401 arpl word ptr [ecx+eax],dx", 0x63, 0x14, 0x01 );
	_TEST32( "66631401 arpl word ptr [ecx+eax],dx", 0x66, 0x63, 0x14, 0x01 );
	_TEST32( "676314 arpl word ptr [si],dx", 0x67, 0x63, 0x14, 0x01 );
	_TEST64( "FAIL", 0x63, 0xdf );

	// BLENDPD
	_TEST32( "660f3a0d1401ff blendpd xmm2,oword ptr [ecx+eax],0ffh", 0x66, 0x0F, 0x3a, 0x0D, 0x14, 0x01, 0xFF );
	_TEST64( "660f3a0d1401ff blendpd xmm2,oword ptr [rcx+rax],0ffh", 0x66, 0x0F, 0x3a, 0x0D, 0x14, 0x01, 0xFF );
	// VEX.NDS.128.66.0F3A 0D /r ib VBLENDPD xmm1,xmm2,xmm3/m128,imm8
	// VEX.NDS.256.66.0F3A 0D /r ib VBLENDPD ymm1,ymm2,ymm3/m256,imm8
	_TEST64_VEX( "c4430d0d140120 vblendpd ymm10,ymm14,ymmword ptr [r9+rax],20h", 0xC4, 0x43, 0x0D, 0x0D, 0x14, 0x01, 0x20 );
	_TEST32_VEX( "c4c3410d140120 vblendpd xmm2,xmm7,oword ptr [ecx+eax],20h", 0xC4, 0xC3, 0x41, 0x0D, 0x14, 0x01, 0x20 );
	_TEST32_VEX( "c4c3690d140120 vblendpd xmm2,xmm2,oword ptr [ecx+eax],20h", 0xC4, 0xC3, 0x69, 0x0D, 0x14, 0x01, 0x20 );

	// BLENDPS
	_TEST32( "660f3a0c1401ff blendps xmm2,oword ptr [ecx+eax],0ffh", 0x66, 0x0F, 0x3a, 0x0C, 0x14, 0x01, 0xFF );
	_TEST64( "660f3a0c1401ff blendps xmm2,oword ptr [rcx+rax],0ffh", 0x66, 0x0F, 0x3a, 0x0C, 0x14, 0x01, 0xFF );
	// VEX.NDS.128.66.0F3A 0C /r ib VBLENDPS xmm1,xmm2,xmm3/m128,imm8
	// VEX.NDS.256.66.0F3A 0C /r ib VBLENDPS ymm1,ymm2,ymm3/m256,imm8
	_TEST64_VEX( "c4430d0c140120 vblendps ymm10,ymm14,ymmword ptr [r9+rax],20h", 0xC4, 0x43, 0x0D, 0x0C, 0x14, 0x01, 0x20 );
	_TEST32_VEX( "c4c3410c140120 vblendps xmm2,xmm7,oword ptr [ecx+eax],20h", 0xC4, 0xC3, 0x41, 0x0C, 0x14, 0x01, 0x20 );
	_TEST32_VEX( "c4c3690c140120 vblendps xmm2,xmm2,oword ptr [ecx+eax],20h", 0xC4, 0xC3, 0x69, 0x0C, 0x14, 0x01, 0x20 );

	// BLENDVPD
	_TEST32( "660f38151401 blendvpd xmm2,oword ptr [ecx+eax],xmm0", 0x66, 0x0F, 0x38, 0x15, 0x14, 0x01, 0xFF );
	_TEST64( "660f38151401 blendvpd xmm2,oword ptr [rcx+rax],xmm0", 0x66, 0x0F, 0x38, 0x15, 0x14, 0x01, 0xFF );
	// VEX.NDS.128.66.0F3A 4B /r /is4 VBLENDVPD xmm1, xmm2, xmm3/m128, xmm4
	// VEX.NDS.256.66.0F3A 4B /r /is4 VBLENDVPD ymm1, ymm2, ymm3/m256, ymm4
	_TEST64_VEX( "c4430d4b1401 vblendvpd ymm10,ymm14,ymmword ptr [r9+rax],ymm2", 0xC4, 0x43, 0x0D, 0x4B, 0x14, 0x01, 0x20 );
	_TEST32_VEX( "c4c3414b1401 vblendvpd xmm2,xmm7,oword ptr [ecx+eax],xmm2", 0xC4, 0xC3, 0x41, 0x4B, 0x14, 0x01, 0x20 );
	_TEST32_VEX( "c4c3694b1401 vblendvpd xmm2,xmm2,oword ptr [ecx+eax],xmm2", 0xC4, 0xC3, 0x69, 0x4B, 0x14, 0x01, 0xA0 );

	// BLENDVPS
	_TEST32( "660f38141401 blendvps xmm2,oword ptr [ecx+eax],xmm0", 0x66, 0x0F, 0x38, 0x14, 0x14, 0x01, 0xFF );
	_TEST64( "660f38141401 blendvps xmm2,oword ptr [rcx+rax],xmm0", 0x66, 0x0F, 0x38, 0x14, 0x14, 0x01, 0xFF );
	// VEX.NDS.128.66.0F3A 4A /r /is4 VBLENDVPS xmm1, xmm2, xmm3/m128, xmm4
	// VEX.NDS.256.66.0F3A 4A /r /is4 VBLENDVPS ymm1, ymm2, ymm3/m256, ymm4
	_TEST64_VEX( "c4430d4a1401 vblendvps ymm10,ymm14,ymmword ptr [r9+rax],ymm2", 0xC4, 0x43, 0x0D, 0x4A, 0x14, 0x01, 0x20 );
	_TEST32_VEX( "c4c3414a1401 vblendvps xmm2,xmm7,oword ptr [ecx+eax],xmm2", 0xC4, 0xC3, 0x41, 0x4A, 0x14, 0x01, 0x20 );
	_TEST32_VEX( "c4c3694a1401 vblendvps xmm2,xmm2,oword ptr [ecx+eax],xmm2", 0xC4, 0xC3, 0x69, 0x4A, 0x14, 0x01, 0xA0 );

	// VBROADCASTSS
	// VEX.128.66.0F38 18 /r VBROADCASTSS xmm1, m32
	// VEX.256.66.0F38 18 /r VBROADCASTSS ymm1, m32
	_TEST32_VEX( "c4e249181401 vbroadcastss xmm2,dword ptr [ecx+eax]", 0xC4, 0xE2, 0x49, 0x18, 0x14, 0x01 );
	_TEST32_VEX( "c4e24d181401 vbroadcastss ymm2,dword ptr [ecx+eax]", 0xC4, 0xE2, 0x4D, 0x18, 0x14, 0x01 );
	// VEX.256.66.0F38 19 /r VBROADCASTSD ymm1, m64
	_TEST32_VEX( "FAIL", 0xC4, 0xE2, 0x49, 0x19, 0x14, 0x01 );
	_TEST32_VEX( "c4e27d191401 vbroadcastsd ymm2,qword ptr [ecx+eax]", 0xC4, 0xE2, 0x7D, 0x19, 0x14, 0x01 );
	// VEX.256.66.0F38.W0 1A /r VBROADCASTF128 ymm1,m128
	_TEST32_VEX( "c4e27d1a1401 vbroadcastf128 ymm2,oword ptr [ecx+eax]", 0xC4, 0xE2, 0x7D, 0x1A, 0x14, 0x01 );
	// VEX.256.66.0F38.W0 5A /r VBROADCASTI128 ymm1,m128
	_TEST32_VEX( "c4e27d5a1401 vbroadcasti128 ymm2,oword ptr [ecx+eax]", 0xC4, 0xE2, 0x7D, 0x5A, 0x14, 0x01 );
	// VEX.128.66.0F38.W0 18 /r VBROADCASTSS xmm1,xmm2
	// VEX.256.66.0F38.W0 18 /r VBROADCASTSS ymm1,xmm2
	_TEST32_VEX( "c4e27918c1 vbroadcastss xmm0,xmm1", 0xC4, 0xE2, 0x79, 0x18, 0xC1 );
	_TEST32_VEX( "c4e27d18c1 vbroadcastss ymm0,xmm1", 0xC4, 0xE2, 0x7D, 0x18, 0xC1 );
	// VEX.256.66.0F38.W0 19 /r VBROADCASTSD ymm1,xmm2
	_TEST32_VEX( "c4e27d19c1 vbroadcastsd ymm0,xmm1", 0xC4, 0xE2, 0x7D, 0x19, 0xC1 );

	// VEX.128.66.0F38.W0 78 /r VPBROADCASTB xmm1,xmm2/m8
	// VEX.256.66.0F38.W0 78 /r VPBROADCASTB ymm1,xmm2/m8
	_TEST32_VEX( "c4e2797800 vpbroadcastb xmm0,byte ptr [eax]", 0xC4, 0xE2, 0x79, 0x78, 0x00 );
	_TEST32_VEX( "c4e27d7800 vpbroadcastb ymm0,byte ptr [eax]", 0xC4, 0xE2, 0x7D, 0x78, 0x00 );
	_TEST64_VEX( "c4e27978c1 vpbroadcastb xmm0,xmm1", 0xC4, 0xE2, 0x79, 0x78, 0xC1 );
	_TEST64_VEX( "c4e27d78c1 vpbroadcastb ymm0,ymm1", 0xC4, 0xE2, 0x7D, 0x78, 0xC1 );
	// VEX.128.66.0F38.W0 79 /r VPBROADCASTW xmm1,xmm2/m16
	// VEX.256.66.0F38.W0 79 /r VPBROADCASTW ymm1,xmm2/m16
	_TEST32_VEX( "c4e2797900 vpbroadcastw xmm0,word ptr [eax]", 0xC4, 0xE2, 0x79, 0x79, 0x00 );
	_TEST32_VEX( "c4e27d7900 vpbroadcastw ymm0,word ptr [eax]", 0xC4, 0xE2, 0x7D, 0x79, 0x00 );
	_TEST64_VEX( "c4e27979c1 vpbroadcastw xmm0,xmm1", 0xC4, 0xE2, 0x79, 0x79, 0xC1 );
	_TEST64_VEX( "c4e27d79c1 vpbroadcastw ymm0,ymm1", 0xC4, 0xE2, 0x7D, 0x79, 0xC1 );
	// VEX.128.66.0F38.W0 58 /r VPBROADCASTD xmm1,xmm2/m32
	// VEX.256.66.0F38.W0 58 /r VPBROADCASTD ymm1,xmm2/m32
	_TEST32_VEX( "c4e2795800 vpbroadcastd xmm0,dword ptr [eax]", 0xC4, 0xE2, 0x79, 0x58, 0x00 );
	_TEST32_VEX( "c4e27d5800 vpbroadcastd ymm0,dword ptr [eax]", 0xC4, 0xE2, 0x7D, 0x58, 0x00 );
	_TEST64_VEX( "c4e27958c1 vpbroadcastd xmm0,xmm1", 0xC4, 0xE2, 0x79, 0x58, 0xC1 );
	_TEST64_VEX( "c4e27d58c1 vpbroadcastd ymm0,ymm1", 0xC4, 0xE2, 0x7D, 0x58, 0xC1 );
	// VEX.128.66.0F38.W0 59 /r VPBROADCASTQ xmm1,xmm2/m64
	// VEX.256.66.0F38.W0 59 /r VPBROADCASTQ ymm1,xmm2/m64
	_TEST32_VEX( "c4e2795900 vpbroadcastq xmm0,qword ptr [eax]", 0xC4, 0xE2, 0x79, 0x59, 0x00 );
	_TEST32_VEX( "c4e27d5900 vpbroadcastq ymm0,qword ptr [eax]", 0xC4, 0xE2, 0x7D, 0x59, 0x00 );
	_TEST64_VEX( "c4e27959c1 vpbroadcastq xmm0,xmm1", 0xC4, 0xE2, 0x79, 0x59, 0xC1 );
	_TEST64_VEX( "c4e27d59c1 vpbroadcastq ymm0,ymm1", 0xC4, 0xE2, 0x7D, 0x59, 0xC1 );

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

void test_code( int isVEX, int is32, uint8_t code[], int size, char *mnemonic ) {

	struct ira_disassemble_info info;
	info.address = code;
	info.size = size;
	info.address_size_attribute = 0;
	info.operand_size_attribute = 0;
	info.mode = is32 ? IRA_MOD_32BIT : IRA_MOD_64BIT;
	info.config.flags = 0;
	if( isVEX ) {
		info.config.flags |= _IRA_CF_ENABLE_VAX;
	}

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


