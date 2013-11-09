/*
 * instructions.c
 *
 *  Created on: 01-06-2013
 *      Author: tAs
 */

#include "fcml_env.h"
#include "fcml_assembler.h"
#include "instructions_r_t.h"

int fcml_tf_instructions_r_suite_init(void) {
	return 0;
}

int fcml_tf_instructions_r_suite_cleanup(void) {
	return 0;
}

void fcml_tf_instruction_RCL(void) {
    // D0 /2 RCL r/m8, 1
    // REX + D0 /2 RCL r/m8, 1
    FCML_I32_M( "rcl byte ptr [eax],01h", 2, FCML_MI( 0xc0, 0x10, 0x01 ), FCML_MI( 0xd0, 0x10 ) );
    FCML_I3264_M( "rcl al,01h", 2, FCML_MI( 0xc0, 0xd0, 0x01 ), FCML_MI( 0xd0, 0xd0 ) );
    // D2 /2 RCL r/m8, CL
    // REX + D2 /2 RCL r/m8, CL
    FCML_I32( "rcl byte ptr [eax],cl", 0xD2, 0x10 );
    FCML_I32( "rcl al,cl", 0xD2, 0xD0 );
    FCML_I64_D( "rcl al,cl", 0x48, 0xD2, 0xD0 );
    // C0 /2 ib RCL r/m8, imm8
    // REX + C0 /2 ib RCL r/m8, imm8
    FCML_I32( "rcl byte ptr [eax],0ffh", 0xC0, 0x10, 0xFF );
    FCML_I32( "rcl byte ptr [eax],0ffh", 0xc0, 0x10, 0xff );
    FCML_I32( "rcl al,0ffh", 0xC0, 0xD0, 0xFF );
    FCML_I64_D( "rcl al,0ffh", 0x48, 0xC0, 0xD0, 0xFF );
    // D1 /2 RCL r/m16, 1
    // D1 /2 RCL r/m32, 1
    // REX.W + D1 /2 RCL r/m64, 1
    FCML_I32_M( "rcl dword ptr [eax],01h", 2, FCML_MI( 0xc1, 0x10, 0x01 ), FCML_MI( 0xd1, 0x10 ) );
    FCML_I32_M( "rcl eax,01h", 2, FCML_MI( 0xc1, 0xd0, 0x01 ), FCML_MI( 0xd1, 0xd0 ) );
    FCML_I64_D( "rcl rax,01h", 0x48, 0xD1, 0xD0 );
    // D3 /2 RCL r/m16, CL
    // D3 /2 RCL r/m32, CL
    // REX.W + D3 /2 RCL r/m64, CL
    FCML_I32( "rcl dword ptr [eax],cl", 0xD3, 0x10 );
    FCML_I32( "rcl eax,cl", 0xD3, 0xD0 );
    FCML_I64_D( "rcl rax,cl", 0x48, 0xD3, 0xD0 );
    // C1 /2 ib RCL r/m16, imm8
    // C1 /2 ib RCL r/m32, imm8
    // REX.W + C1 /2 ib RCL r/m64, imm8
    FCML_I32( "rcl dword ptr [eax],0ffh", 0xC1, 0x10, 0xff );
    FCML_I32( "rcl eax,0ffh", 0xC1, 0xD0, 0xff );
    FCML_I64_D( "rcl rax,0ffh", 0x48, 0xC1, 0xD0, 0xff );
}

void fcml_tf_instruction_RCR(void) {
    // D0 /3 RCR r/m8, 1
    // REX + D0 /3 RCR r/m8, 1
    FCML_I32_M( "rcr byte ptr [eax],01h", 2, FCML_MI( 0xc0, 0x18, 0x01 ), FCML_MI( 0xd0, 0x18 ) );
    FCML_I32_M( "rcr al,01h", 2, FCML_MI( 0xc0, 0xd8, 0x01 ), FCML_MI( 0xd0, 0xd8 ) );
    FCML_I64_M( "rcr al,01h", 2, FCML_MI( 0xc0, 0xd8, 0x01 ), FCML_MI( 0xd0, 0xd8 ) );
    // D2 /3 RCR r/m8, CL
    // REX + D2 /3 RCR r/m8, CL
    FCML_I32( "rcr byte ptr [eax],cl", 0xD2, 0x18 );
    FCML_I32( "rcr al,cl", 0xD2, 0xD8 );
    FCML_I64_D( "rcr al,cl", 0x48, 0xD2, 0xD8 );
    // C0 /3 ib RCR r/m8, imm8
    // REX + C0 /3 ib RCR r/m8, imm8
    FCML_I32( "rcr byte ptr [eax],0ffh", 0xC0, 0x18, 0xFF );
    FCML_I32( "rcr al,0ffh", 0xC0, 0xD8, 0xFF );
    FCML_I64_D( "rcr al,0ffh", 0x48, 0xC0, 0xD8, 0xFF );
    // D1 /3 RCR r/m16, 1
    // D1 /3 RCR r/m32, 1
    // REX.W + D1 /3 RCR r/m64, 1
    FCML_I32_M( "rcr dword ptr [eax],01h", 2, FCML_MI( 0xc1, 0x18, 0x01 ), FCML_MI( 0xd1, 0x18 ) );
    FCML_I32_M( "rcr eax,01h", 2, FCML_MI( 0xc1, 0xd8, 0x01 ), FCML_MI( 0xd1, 0xd8 ) );
    FCML_I64_D( "rcr rax,01h", 0x48, 0xD1, 0xD8 );
    // D3 /3 RCR r/m16, CL
    // D3 /3 RCR r/m32, CL
    // REX.W + D3 /3 RCR r/m64, CL
    FCML_I32( "rcr dword ptr [eax],cl", 0xD3, 0x18 );
    FCML_I32( "rcr eax,cl", 0xD3, 0xD8 );
    FCML_I64_D( "rcr rax,cl", 0x48, 0xD3, 0xD8 );
    // C1 /3 ib RCR r/m16, imm8
    // C1 /3 ib RCR r/m32, imm8
    // REX.W + C1 /3 ib RCR r/m64, imm8
    FCML_I32( "rcr dword ptr [eax],0ffh", 0xC1, 0x18, 0xff );
    FCML_I32( "rcr eax,0ffh", 0xC1, 0xD8, 0xff );
    FCML_I64( "rcr rax,0ffh", 0x48, 0xC1, 0xD8, 0xff );
}

void fcml_tf_instruction_ROL(void) {
    // D0 /0 ROL r/m8, 1
    // REX + D0 /0 ROL r/m8, 1
    FCML_I32_M( "rol byte ptr [eax],01h", 2, FCML_MI( 0xc0, 0x00, 0x01 ), FCML_MI( 0xd0, 0x00 ) );
    FCML_I32_M( "rol al,01h", 2, FCML_MI( 0xc0, 0xc0, 0x01 ), FCML_MI( 0xd0, 0xc0 ) );
    FCML_I64_D( "rol al,01h", 0x48, 0xD0, 0xC0 );
    // D2 /0 ROL r/m8, CL
    // REX + D2 /0 ROL r/m8, CL
    FCML_I32( "rol byte ptr [eax],cl", 0xD2, 0x00 );
    FCML_I32( "rol al,cl", 0xD2, 0xC0 );
    FCML_I64_D( "rol al,cl", 0x48, 0xD2, 0xC0 );
    // C0 /0 ib ROL r/m8, imm8
    // REX + C0 /0 ib ROL r/m8, imm8
    FCML_I32( "rol byte ptr [eax],0ffh", 0xC0, 0x00, 0xFF );
    FCML_I32( "rol al,0ffh", 0xC0, 0xC0, 0xFF );
    FCML_I64_D( "rol al,0ffh", 0x48, 0xC0, 0xC0, 0xFF );
    // D1 /0 ROL r/m16, 1
    // D1 /0 ROL r/m32, 1
    // REX.W + D1 /0 ROL r/m64, 1
    FCML_I32_M( "rol dword ptr [eax],01h", 2, FCML_MI( 0xc1, 0x00, 0x01 ), FCML_MI( 0xd1, 0x00 ) );
    FCML_I32_M( "rol eax,01h", 2, FCML_MI( 0xc1, 0xc0, 0x01 ), FCML_MI( 0xd1, 0xc0 ) );
    FCML_I64_D( "rol rax,01h", 0x48, 0xD1, 0xC0 );
    // D3 /0 ROL r/m16, CL
    // D3 /0 ROL r/m32, CL
    // REX.W + D3 /0 ROL r/m64, CL
    FCML_I32( "rol dword ptr [eax],cl", 0xD3, 0x00 );
    FCML_I32( "rol eax,cl", 0xD3, 0xC0 );
    FCML_I64_D( "rol rax,cl", 0x48, 0xD3, 0xC0 );
    // C1 /0 ib ROL r/m16, imm8
    // C1 /0 ib ROL r/m32, imm8
    // C1 /0 ib ROL r/m64, imm8
    FCML_I32( "rol dword ptr [eax],0ffh", 0xC1, 0x00, 0xff );
    FCML_I32( "rol eax,0ffh", 0xC1, 0xC0, 0xff );
    FCML_I64( "rol rax,0ffh", 0x48, 0xC1, 0xC0, 0xff );
}

void fcml_tf_instruction_ROR(void) {
    // D0 /1 ROR r/m8, 1
    // REX + D0 /1 ROR r/m8, 1
    FCML_I32_M( "ror byte ptr [eax],01h", 2, FCML_MI( 0xc0, 0x08, 0x01 ), FCML_MI( 0xd0, 0x08 ) );
    FCML_I32_M( "ror al,01h", 2, FCML_MI( 0xc0, 0xc8, 0x01 ), FCML_MI( 0xd0, 0xc8 ) );
    FCML_I64_D( "ror al,01h", 0x48, 0xD0, 0xC8 );
    // D2 /1 ROR r/m8, CL
    // REX + D2 /1 ROR r/m8, CL
    FCML_I32( "ror byte ptr [eax],cl", 0xD2, 0x08 );
    FCML_I32( "ror al,cl", 0xD2, 0xC8 );
    FCML_I64_D( "ror al,cl", 0x48, 0xD2, 0xC8 );
    // C0 /1 ib ROR r/m8, imm8
    // REX + C0 /1 ib ROR r/m8, imm8
    FCML_I32( "ror byte ptr [eax],0ffh", 0xC0, 0x08, 0xFF );
    FCML_I32( "ror al,0ffh", 0xC0, 0xC8, 0xFF );
    FCML_I64_D( "ror al,0ffh", 0x48, 0xC0, 0xC8, 0xFF );
    // D1 /1 ROR r/m16, 1
    // D1 /1 ROR r/m32, 1
    // REX.W + D1 /1 ROR r/m64, 1
    FCML_I32_M( "ror dword ptr [eax],01h", 2, FCML_MI( 0xc1, 0x08, 0x01 ), FCML_MI( 0xd1, 0x08 ) );
    FCML_I32_M( "ror eax,01h", 2, FCML_MI( 0xc1, 0xc8, 0x01 ), FCML_MI( 0xd1, 0xc8 ) );
    FCML_I64_M( "ror rax,01h", 2, FCML_MI( 0x48, 0xc1, 0xc8, 0x01 ), FCML_MI( 0x48, 0xd1, 0xc8 ) );
    // D3 /1 ROR r/m16, CL
    // D3 /1 ROR r/m32, CL
    // REX.W + D3 /1 ROR r/m64, CL
    FCML_I32( "ror dword ptr [eax],cl", 0xD3, 0x08 );
    FCML_I32( "ror eax,cl", 0xD3, 0xC8 );
    FCML_I64( "ror rax,cl", 0x48, 0xD3, 0xC8 );
    // C1 /1 ib ROR r/m16, imm8
    // C1 /1 ib ROR r/m32, imm8
    // REX.W + C1 /1 ib ROR r/m64, imm8
    FCML_I32( "ror dword ptr [eax],0ffh", 0xC1, 0x08, 0xff );
    FCML_I32( "ror eax,0ffh", 0xC1, 0xC8, 0xff );
    FCML_I64( "ror rax,0ffh", 0x48, 0xC1, 0xC8, 0xff );
}

void fcml_tf_instruction_RCPPS(void) {
    // 0F 53 /r RCPPS xmm1,xmm2/m128
    FCML_I64( "rcpps xmm0,xmmword ptr [rax]", 0x0F, 0x53, 0x00 );
    FCML_I32( "rcpps xmm0,xmm1", 0x0F, 0x53, 0xC1 );
    // VEX.128.0F.WIG 53 /r VRCPPS xmm1, xmm2/m128
    // VEX.256.0F.WIG 53 /r VRCPPS ymm1, ymm2/m256
    FCML_I32( "vrcpps xmm2,xmmword ptr [eax]", 0xc5, 0xf8, 0x53, 0x10 );
    // long_form hint test.
    FCML_I32_A( "vrcpps long_form xmm2,xmmword ptr [eax]", 0xc4, 0xe1, 0x78, 0x53, 0x10 );
    FCML_I64( "vrcpps ymm2,ymmword ptr [rax]", 0xc5, 0xfc, 0x53, 0x10 );
}

void fcml_tf_instruction_RCPSS(void) {
    // F3 0F 53 /r RCPSS xmm1,xmm2/m32
    FCML_I32( "rcpss xmm2,dword ptr [eax]", 0xF3, 0x0F, 0x53, 0x10 );
    FCML_I32( "rcpss xmm3,xmm0", 0xF3, 0x0F, 0x53, 0xD8 );
    FCML_I64( "rcpss xmm2,dword ptr [rax]", 0xF3, 0x0F, 0x53, 0x10 );
    // VEX.NDS.LIG.F3.0F.WIG 53 /r VRCPSS xmm1,xmm2,xmm3/m32
    FCML_I64( "vrcpss xmm3,xmm3,xmm0", 0xc5, 0xe2, 0x53, 0xd8 );
    FCML_I32( "vrcpss xmm3,xmm7,xmm0", 0xc5, 0xc2, 0x53, 0xd8 );
    FCML_I32( "vrcpss xmm3,xmm0,dword ptr [eax]", 0xc5, 0xfa, 0x53, 0x18 );
}

void fcml_tf_instruction_RDFSBASE(void) {
    // F3 0F AE /0 RDFSBASE r32
    // REX.W + F3 0F AE /0 RDFSBASE r64
    FCML_I32_FAILED( "rdfsbase eax", 0x66, 0xF3, 0x0F, 0xAE, 0xC0 );
    FCML_I64( "rdfsbase eax", 0xF3, 0x0F, 0xAE, 0xC0 );
    FCML_I64_D( "rdfsbase eax", 0x66, 0xF3, 0x0F, 0xAE, 0xC0 );
    FCML_I64( "rdfsbase rax", 0xF3, 0x48, 0x0F, 0xAE, 0xC0 );
    // F3 0F AE /1 RDGSBASE r32
    // REX.W + F3 0F AE /1 RDGSBASE r64
    FCML_I32_FAILED( "rdgsbase eax", 0xF3, 0x0F, 0xAE, 0xC8 );
    FCML_I64( "rdgsbase eax", 0xF3, 0x0F, 0xAE, 0xC8 );
    FCML_I64_D( "rdgsbase eax", 0x66, 0xF3, 0x0F, 0xAE, 0xC8 );
    FCML_I64( "rdgsbase rax", 0xF3, 0x48, 0x0F, 0xAE, 0xC8 );
}

void fcml_tf_instruction_RDRAND(void) {
    // 0F C7 /6 RDRAND r16
    FCML_I32( "rdrand ax", 0x66, 0x0F, 0xC7, 0xF0 );
    FCML_I64( "rdrand ax", 0x66, 0x0F, 0xC7, 0xF0 );
    // 0F C7 /6 RDRAND r32
    FCML_I32( "rdrand eax", 0x0F, 0xC7, 0xF0 );
    FCML_I64( "rdrand eax", 0x0F, 0xC7, 0xF0 );
    // REX.W + 0F C7 /6 RDRAND r64
    FCML_I64( "rdrand rax", 0x48, 0x0F, 0xC7, 0xF0 );
}

void fcml_tf_instruction_RDTSCP(void) {
    // 0F 01 F9 RDTSCP
    FCML_I32( "rdtscp", 0x0f, 0x01, 0xf9 );
    FCML_I64( "rdtscp", 0x0f, 0x01, 0xf9 );
}

void fcml_tf_instruction_RDTSC(void) {
    // 0F 31 RDTSC
    FCML_I3264( "rdtsc", 0x0F, 0x31 );
}

void fcml_tf_instruction_RDPMC(void) {
    // 0F 33 RDPMC
    FCML_I3264( "rdpmc", 0x0F, 0x33 );
}

void fcml_tf_instruction_RDMSR(void) {
    // 0F 32 RDMSR
    FCML_I3264( "rdmsr", 0x0F, 0x32 );
}

void fcml_tf_instruction_RET(void) {
    // C3 RET
    // CB RET
    FCML_I3264( "ret", 0xC3 );
    FCML_I3264( "retf", 0xCB );
    // C2 iw RET imm16
    // CA iw RET imm16
    FCML_I3264( "ret 0ffffh", 0xC2, 0xFF, 0xFF );
    FCML_I3264( "retf 0ffffh", 0xCA, 0xFF, 0xFF );
}

void fcml_tf_instruction_ROUNDPD(void) {
    // 66 0F 3A 09 /r ib ROUNDPD xmm1,xmm2/m128,imm8
    FCML_I64( "roundpd xmm0,xmmword ptr [rax],0ffh", 0x66, 0x0F, 0x3A, 0x09, 0x00, 0xFF );
    FCML_I32( "roundpd xmm0,xmm1,0ffh", 0x66, 0x0F, 0x3A, 0x09, 0xC1, 0xFF );
    // VEX.128.66.0F3A.WIG 09 /r ib VROUNDPD xmm1,xmm2/m128,imm8
    // VEX.256.66.0F3A.WIG 09 /r ib VROUNDPD ymm1,ymm2/m256,imm8
    FCML_I64( "vroundpd xmm3,xmm0,0ffh", 0xC4, 0xE3, 0x79, 0x09, 0xD8, 0xFF );
    FCML_I32( "vroundpd xmm3,xmm0,0ffh", 0xC4, 0xE3, 0x79, 0x09, 0xD8, 0xFF );
    FCML_I32( "vroundpd ymm0,ymmword ptr [eax],0ffh", 0xC4, 0xE3, 0x7D, 0x09, 0x00, 0xFF );
}

void fcml_tf_instruction_ROUNDPS(void) {
    // 66 0F 3A 08 /r ib ROUNDPS xmm1,xmm2/m128,imm8
    FCML_I64( "roundps xmm0,xmmword ptr [rax],0ffh", 0x66, 0x0F, 0x3A, 0x08, 0x00, 0xFF );
    FCML_I32( "roundps xmm0,xmm1,0ffh", 0x66, 0x0F, 0x3A, 0x08, 0xC1, 0xFF );
    // VEX.128.66.0F3A.WIG 08 /r ib VROUNDPS xmm1,xmm2/m128,imm8
    // VEX.256.66.0F3A.WIG 08 /r ib VROUNDPS ymm1,ymm2/m256,imm8
    FCML_I64( "vroundps xmm3,xmm0,0ffh", 0xC4, 0xE3, 0x79, 0x08, 0xD8, 0xFF );
    FCML_I32( "vroundps xmm3,xmm0,0ffh", 0xC4, 0xE3, 0x79, 0x08, 0xD8, 0xFF );
    FCML_I32( "vroundps ymm0,ymmword ptr [eax],0ffh", 0xC4, 0xE3, 0x7D, 0x08, 0x00, 0xFF );
}

void fcml_tf_instruction_ROUNDSD(void) {
    // 66 0F 3A 0B /r ib ROUNDSD xmm1,xmm2/m64,imm8
    FCML_I64( "roundsd xmm0,mmword ptr [rax],0ffh", 0x66, 0x0F, 0x3A, 0x0B, 0x00, 0xFF );
    FCML_I32( "roundsd xmm0,xmm1,0ffh", 0x66, 0x0F, 0x3A, 0x0B, 0xC1, 0xFF );
    // VEX.NDS.LIG.66.0F3A.WIG 0B /r ib VROUNDSD xmm1,xmm2,xmm3/m64,imm8
    FCML_I64( "vroundsd xmm3,xmm0,xmm0,0ffh", 0xC4, 0xE3, 0x79, 0x0B, 0xD8, 0xFF );
    FCML_I32( "vroundsd xmm3,xmm3,xmm0,0ffh", 0xC4, 0xE3, 0x61, 0x0B, 0xD8, 0xFF );
}

void fcml_tf_instruction_ROUNDSS(void) {
    // 66 0F 3A 0A /r ib ROUNDSS xmm1,xmm2/m32,imm8
    FCML_I64( "roundss xmm0,dword ptr [rax],0ffh", 0x66, 0x0F, 0x3A, 0x0A, 0x00, 0xFF );
    FCML_I32( "roundss xmm0,xmm1,0ffh", 0x66, 0x0F, 0x3A, 0x0A, 0xC1, 0xFF );
    // VEX.NDS.LIG.66.0F3A.WIG 0A ib VROUNDSS xmm1,xmm2,xmm3/m32,imm8
    FCML_I64( "vroundss xmm3,xmm0,xmm0,0ffh", 0xC4, 0xE3, 0x79, 0x0A, 0xD8, 0xFF );
    FCML_I32( "vroundss xmm3,xmm6,xmm0,0ffh", 0xC4, 0xE3, 0x49, 0x0A, 0xD8, 0xFF );
}

void fcml_tf_instruction_RSM(void) {
    // 0F AA RSM NP Invalid Valid Resume operation of interrupted program.
    FCML_I32( "rsm", 0x0F, 0xAA );
    FCML_I64_FAILED( "rsm", 0x0F, 0xAA );
}

void fcml_tf_instruction_RSQRTPS(void) {
    // 0F 52 /r RSQRTPS xmm1,xmm2/m128
    FCML_I64( "rsqrtps xmm0,xmmword ptr [rax]", 0x0F, 0x52, 0x00 );
    FCML_I32( "rsqrtps xmm0,xmm1", 0x0F, 0x52, 0xC1 );
    // VEX.128.0F.WIG 52 /r VRSQRTPS xmm1,xmm2/m128
    // VEX.256.0F.WIG 52 /r VRSQRTPS ymm1,ymm2/m256
    FCML_I3264( "vrsqrtps xmm3,xmm0", 0xc5, 0xf8, 0x52, 0xd8 );
    FCML_I32( "vrsqrtps ymm0,ymmword ptr [eax]", 0xc5, 0xfc, 0x52, 0x00 );
}

void fcml_tf_instruction_RSQRTSS(void) {
    // F3 0F 52 /r RSQRTSS xmm1,xmm2/m32
    FCML_I64( "rsqrtss xmm0,dword ptr [rax]", 0xF3, 0x0F, 0x52, 0x00 );
    FCML_I32( "rsqrtss xmm0,xmm1", 0xF3, 0x0F, 0x52, 0xC1 );
    // VEX.NDS.LIG.F3.0F.WIG 52 /r VRSQRTSS xmm1,xmm2,xmm3/m32
    FCML_I64( "vrsqrtss xmm0,xmm6,dword ptr [rax]", 0xc5, 0xca, 0x52, 0x00 );
    FCML_I32( "vrsqrtss xmm3,xmm6,xmm0", 0xc5, 0xca, 0x52, 0xd8 );
}

void fcml_tf_instruction_RORX(void) {
    // VEX.LZ.F2.0F3A.W0 F0 /r ib RORX r32, r/m32, imm8
    FCML_I32_D( "rorx eax,dword ptr [eax],01h", 0xC4, 0xE2, 0x43, 0xF0, 0x00, 0x01 );
    FCML_I32( "rorx eax,dword ptr [eax],01h", 0xc4, 0xe2, 0x7b, 0xf0, 0x00, 0x01 );
    FCML_I32_D( "rorx eax,eax,01h", 0xC4, 0xE2, 0x43, 0xF0, 0xC0, 0x01 );
    FCML_I32( "rorx eax,eax,01h", 0xc4, 0xe2, 0x7b, 0xf0, 0xc0, 0x01 );
    // VEX.LZ.F2.0F3A.W1 F0 /r ib RORX r64, r/m64, imm8
    FCML_I64_D( "rorx rax,qword ptr [rax],01h", 0xC4, 0xE2, 0xC3, 0xF0, 0x00, 0x01 );
    FCML_I64( "rorx rax,qword ptr [rax],01h", 0xc4, 0xe2, 0xfb, 0xf0, 0x00, 0x01 );
    FCML_I64_D( "rorx rax,rax,01h", 0xC4, 0xE2, 0xC3, 0xF0, 0xC0, 0x01 );
    FCML_I64( "rorx rax,rax,01h", 0xc4, 0xe2, 0xfb, 0xf0, 0xc0, 0x01 );
}

void fcml_tf_instruction_RDSEED(void) {
    // 0F C7 /7 RDSEED r16
    FCML_I32( "rdseed ax", 0x66, 0x0F, 0xC7, 0xF8 );
    FCML_I64( "rdseed ax", 0x66, 0x0F, 0xC7, 0xF8 );
    // 0F C7 /7 RDSEED r32
    FCML_I32( "rdseed eax", 0x0F, 0xC7, 0xF8 );
    FCML_I64( "rdseed eax", 0x0F, 0xC7, 0xF8 );
    // REX.W + 0F C7 /7 RDSEED r64
    FCML_I64( "rdseed rax", 0x48, 0x0F, 0xC7, 0xF8 );
}

CU_TestInfo fctl_ti_instructions_r[] = {
    { "fcml_tf_instruction_RCL", fcml_tf_instruction_RCL },
    { "fcml_tf_instruction_RCR", fcml_tf_instruction_RCR },
    { "fcml_tf_instruction_ROL", fcml_tf_instruction_ROL },
    { "fcml_tf_instruction_ROR", fcml_tf_instruction_ROR },
    { "fcml_tf_instruction_RCPPS", fcml_tf_instruction_RCPPS },
    { "fcml_tf_instruction_RCPSS", fcml_tf_instruction_RCPSS },
    { "fcml_tf_instruction_RDFSBASE", fcml_tf_instruction_RDFSBASE },
    { "fcml_tf_instruction_RDRAND", fcml_tf_instruction_RDRAND },
    { "fcml_tf_instruction_RDTSCP", fcml_tf_instruction_RDTSCP },
    { "fcml_tf_instruction_RDTSC", fcml_tf_instruction_RDTSC },
    { "fcml_tf_instruction_RDPMC", fcml_tf_instruction_RDPMC },
    { "fcml_tf_instruction_RDMSR", fcml_tf_instruction_RDMSR },
    { "fcml_tf_instruction_RET", fcml_tf_instruction_RET },
    { "fcml_tf_instruction_ROUNDPD", fcml_tf_instruction_ROUNDPD },
    { "fcml_tf_instruction_ROUNDPS", fcml_tf_instruction_ROUNDPS },
    { "fcml_tf_instruction_ROUNDSD", fcml_tf_instruction_ROUNDSD },
    { "fcml_tf_instruction_ROUNDSS", fcml_tf_instruction_ROUNDSS },
    { "fcml_tf_instruction_RSM", fcml_tf_instruction_RSM },
    { "fcml_tf_instruction_RSQRTPS", fcml_tf_instruction_RSQRTPS },
    { "fcml_tf_instruction_RSQRTSS", fcml_tf_instruction_RSQRTSS },
    { "fcml_tf_instruction_RORX", fcml_tf_instruction_RORX },
    { "fcml_tf_instruction_RDSEED", fcml_tf_instruction_RDSEED },
    CU_TEST_INFO_NULL,
};

CU_SuiteInfo fctl_si_instructions_r[] = {
    { "suite-fctl_ti_instructions_r", fcml_tf_instructions_r_suite_init, fcml_tf_instructions_r_suite_cleanup, fctl_ti_instructions_r },
    CU_SUITE_INFO_NULL,
};
