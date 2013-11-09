/*
 * instructions.c
 *
 *  Created on: 01-06-2013
 *      Author: tAs
 */

#include "fcml_env.h"
#include "fcml_assembler.h"
#include "instructions_p_t.h"

int fcml_tf_instructions_p_suite_init(void) {
	return 0;
}

int fcml_tf_instructions_p_suite_cleanup(void) {
	return 0;
}

void fcml_tf_instruction_PABS(void) {
    // 0F 38 1C /r1 PABSB mm1,mm2/m64
    // 0F 38 1D /r1 PABSW mm1,mm2/m64
    // 0F 38 1E /r1 PABSD mm1,mm2/m64
    FCML_I64( "pabsb mm0,mmword ptr [rax]", 0x0F, 0x38, 0x1C, 0x00 );
    FCML_I32( "pabsb mm0,mm1", 0x0F, 0x38, 0x1C, 0xC1 );
    FCML_I64( "pabsw mm0,mmword ptr [rax]", 0x0F, 0x38, 0x1D, 0x00 );
    FCML_I32( "pabsw mm0,mm1", 0x0F, 0x38, 0x1D, 0xC1 );
    FCML_I64( "pabsd mm0,mmword ptr [rax]", 0x0F, 0x38, 0x1E, 0x00 );
    FCML_I32( "pabsd mm0,mm1", 0x0F, 0x38, 0x1E, 0xC1 );
    // 66 0F 38 1C /r PABSB xmm1,xmm2/m128
    // 66 0F 38 1D /r PABSW xmm1,xmm2/m128
    // 66 0F 38 1E /r PABSD xmm1,xmm2/m128
    FCML_I64( "pabsb xmm0,xmmword ptr [rax]", 0x66, 0x0F, 0x38, 0x1C, 0x00 );
    FCML_I32( "pabsb xmm0,xmm1", 0x66, 0x0F, 0x38, 0x1C, 0xC1 );
    FCML_I64( "pabsw xmm0,xmmword ptr [rax]", 0x66, 0x0F, 0x38, 0x1D, 0x00 );
    FCML_I32( "pabsw xmm0,xmm1", 0x66, 0x0F, 0x38, 0x1D, 0xC1 );
    FCML_I64( "pabsd xmm0,xmmword ptr [rax]", 0x66, 0x0F, 0x38, 0x1E, 0x00 );
    FCML_I32( "pabsd xmm0,xmm1", 0x66, 0x0F, 0x38, 0x1E, 0xC1 );
    // VEX.128.66.0F38 1C /r VPABSB xmm1,xmm2/m128
    // VEX.128.66.0F38 1D /r VPABSW xmm1,xmm2/m128
    // VEX.128.66.0F38 1E /r VPABSD xmm1,xmm2/m128
    FCML_I64( "vpabsb xmm0,xmmword ptr [rax]", 0xC4, 0xE2, 0x79, 0x1C, 0x00 );
    FCML_I32( "vpabsb xmm0,xmm1", 0xC4, 0xE2, 0x79, 0x1C, 0xC1 );
    FCML_I64( "vpabsw xmm0,xmmword ptr [rax]", 0xC4, 0xE2, 0x79, 0x1D, 0x00 );
    FCML_I32( "vpabsw xmm0,xmm1", 0xC4, 0xE2, 0x79, 0x1D, 0xC1 );
    FCML_I64( "vpabsd xmm0,xmmword ptr [rax]", 0xC4, 0xE2, 0x79, 0x1E, 0x00 );
    FCML_I32( "vpabsd xmm0,xmm1", 0xC4, 0xE2, 0x79, 0x1E, 0xC1 );
    // VEX.256.66.0F38.WIG 1C /r VPABSB ymm1, ymm2/m256
    // VEX.256.66.0F38.WIG 1D /r VPABSW ymm1, ymm2/m256
    // VEX.256.66.0F38.WIG 1E /r VPABSD ymm1, ymm2/m256
    FCML_I64( "vpabsb ymm0,ymmword ptr [rax]", 0xC4, 0xE2, 0x7D, 0x1C, 0x00 );
    FCML_I32( "vpabsb ymm0,ymm1", 0xC4, 0xE2, 0x7D, 0x1C, 0xC1 );
    FCML_I64( "vpabsw ymm0,ymmword ptr [rax]", 0xC4, 0xE2, 0x7D, 0x1D, 0x00 );
    FCML_I32( "vpabsw ymm0,ymm1", 0xC4, 0xE2, 0x7D, 0x1D, 0xC1 );
    FCML_I64( "vpabsd ymm0,ymmword ptr [rax]", 0xC4, 0xE2, 0x7D, 0x1E, 0x00 );
    FCML_I32( "vpabsd ymm0,ymm1", 0xC4, 0xE2, 0x7D, 0x1E, 0xC1 );
}

void fcml_tf_instruction_PACKSS(void) {
    // 0F 63 /r1 PACKSSWB mm1, mm2/m64
    FCML_I64( "packsswb mm0,mmword ptr [rax]", 0x0F, 0x63, 0x00 );
    FCML_I32( "packsswb mm0,mm1", 0x0F, 0x63, 0xC1 );
    // 0F 6B /r1 PACKSSDW mm1, mm2/m64
    FCML_I64( "packssdw mm0,mmword ptr [rax]", 0x0F, 0x6B, 0x00 );
    FCML_I32( "packssdw mm0,mm1", 0x0F, 0x6B, 0xC1 );
    // 66 0F 63 /r PACKSSWB xmm1, xmm2/m128
    // 66 0F 6B /r PACKSSDW xmm1, xmm2/m128
    FCML_I64( "packsswb xmm0,xmmword ptr [rax]", 0x66, 0x0F, 0x63, 0x00 );
    FCML_I32( "packsswb xmm0,xmm1", 0x66, 0x0F, 0x63, 0xC1 );
    FCML_I64( "packssdw xmm0,xmmword ptr [rax]", 0x66, 0x0F, 0x6b, 0x00 );
    FCML_I32( "packssdw xmm0,xmm1", 0x66, 0x0F, 0x6b, 0xC1 );
    // VEX.NDS.128.66.0F.WIG 63 /r VPACKSSWB xmm1,xmm2, xmm3/m128
    // VEX.NDS.128.66.0F.WIG 6B /r VPACKSSDW xmm1,xmm2, xmm3/m128
    FCML_I64( "vpacksswb xmm0,xmm3,xmmword ptr [rax]", 0xc5, 0xe1, 0x63, 0x00 );
    FCML_I32( "vpacksswb xmm0,xmm3,xmm1", 0xc5, 0xe1, 0x63, 0xc1 );
    FCML_I64( "vpackssdw xmm0,xmm3,xmmword ptr [rax]", 0xc5, 0xe1, 0x6b, 0x00 );
    FCML_I32( "vpackssdw xmm0,xmm3,xmm1", 0xc5, 0xe1, 0x6b, 0xc1 );
    // VEX.NDS.256.66.0F.WIG 63 /r VPACKSSWB ymm1,ymm2,ymm3/m256
    // VEX.NDS.256.66.0F.WIG 6B /r VPACKSSDW ymm1,ymm2,ymm3/m256
    FCML_I64( "vpacksswb ymm0,ymm3,ymmword ptr [rax]", 0xc5, 0xe5, 0x63, 0x00 );
    FCML_I64( "vpackssdw ymm0,ymm3,ymmword ptr [rax]", 0xc5, 0xe5, 0x6b, 0x00 );
    FCML_I32( "vpacksswb ymm0,ymm3,ymm1", 0xc5, 0xe5, 0x63, 0xc1 );
    FCML_I32( "vpackssdw ymm0,ymm3,ymm1", 0xc5, 0xe5, 0x6b, 0xc1 );
}

void fcml_tf_instruction_PACKUSD(void) {
    // 66 0F 38 2B /r PACKUSDW xmm1, xmm2/m128
    FCML_I64( "packusdw xmm0,xmmword ptr [rax]", 0x66, 0x0F, 0x38, 0x2B, 0x00 );
    FCML_I32( "packusdw xmm0,xmm1", 0x66, 0x0F, 0x38, 0x2B, 0xC1 );
    // VEX.NDS.128.66.0F38.WIG 2B /r VPACKUSDW xmm1,xmm2,xmm3/m128
    FCML_I64( "vpackusdw xmm0,xmm3,xmmword ptr [rax]", 0xC4, 0xE2, 0x61, 0x2B, 0x00 );
    FCML_I32( "vpackusdw xmm0,xmm3,xmm1", 0xC4, 0xE2, 0x61, 0x2B, 0xC1 );
    // VEX.NDS.256.66.0F38.WIG 2B /r VPACKUSDW ymm1,ymm2,ymm3/m256
    FCML_I64( "vpackusdw ymm0,ymm3,ymmword ptr [rax]", 0xC4, 0xE2, 0x65, 0x2B, 0x00 );
    FCML_I32( "vpackusdw ymm0,ymm3,ymm1", 0xC4, 0xE2, 0x65, 0x2B, 0xC1 );
}

void fcml_tf_instruction_PACKUSW(void) {
    // 0F 67 /r1 PACKUSWB mm,mm/m64
    FCML_I64( "packuswb mm0,mmword ptr [rax]", 0x0F, 0x67, 0x00 );
    FCML_I32( "packuswb mm0,mm1", 0x0F, 0x67, 0xC1 );
    // 66 0F 67 /r PACKUSWB xmm1,xmm2/m128
    FCML_I64( "packuswb xmm0,xmmword ptr [rax]", 0x66, 0x0F, 0x67, 0x00 );
    FCML_I32( "packuswb xmm0,xmm1", 0x66, 0x0F, 0x67, 0xC1 );
    // VEX.NDS.128.66.0F.WIG 67 /r VPACKUSWB xmm1,xmm2,xmm3/m128
    FCML_I64( "vpackuswb xmm0,xmm3,xmmword ptr [rax]", 0xc5, 0xe1, 0x67, 0x00 );
    FCML_I32( "vpackuswb xmm0,xmm3,xmm1", 0xc5, 0xe1, 0x67, 0xc1 );
    // VEX.NDS.256.66.0F.WIG 67 /r VPACKUSWB ymm1,ymm2,ymm3/m256
    FCML_I64( "vpackuswb ymm0,ymm3,ymmword ptr [rax]", 0xc5, 0xe5, 0x67, 0x00 );
    FCML_I32( "vpackuswb ymm0,ymm3,ymm1", 0xc5, 0xe5, 0x67, 0xc1 );
}

void fcml_tf_instruction_PADD(void) {
    // 0F FC /r1 PADDB mm,mm/m64
    // 0F FD /r1 PADDW mm,mm/m64
    // 0F FE /r1 PADDD mm,mm/m64
    FCML_I64( "paddb mm0,mmword ptr [rax]", 0x0F, 0xFC, 0x00 );
    FCML_I32( "paddb mm0,mm1", 0x0F, 0xFC, 0xC1 );
    FCML_I64( "paddw mm0,mmword ptr [rax]", 0x0F, 0xFD, 0x00 );
    FCML_I32( "paddw mm0,mm1", 0x0F, 0xFD, 0xC1 );
    FCML_I64( "paddd mm0,mmword ptr [rax]", 0x0F, 0xFE, 0x00 );
    FCML_I32( "paddd mm0,mm1", 0x0F, 0xFE, 0xC1 );
    // 66 0F FC /r PADDB xmm1,xmm2/m128
    // 66 0F FD /r PADDW xmm1,xmm2/m128
    // 66 0F FE /r PADDD xmm1,xmm2/m128
    FCML_I64( "paddb xmm0,xmmword ptr [rax]", 0x66, 0x0F, 0xFC, 0x00 );
    FCML_I32( "paddb xmm0,xmm1", 0x66, 0x0F, 0xFC, 0xC1 );
    FCML_I64( "paddw xmm0,xmmword ptr [rax]", 0x66, 0x0F, 0xFD, 0x00 );
    FCML_I32( "paddw xmm0,xmm1", 0x66, 0x0F, 0xFD, 0xC1 );
    FCML_I64( "paddd xmm0,xmmword ptr [rax]", 0x66, 0x0F, 0xFE, 0x00 );
    FCML_I32( "paddd xmm0,xmm1", 0x66, 0x0F, 0xFE, 0xC1 );
    // VEX.NDS.128.66.0F.WIG FC /r VPADDB xmm1,xmm2,xmm3/m128
    // VEX.NDS.128.66.0F.WIG FD /r VPADDW xmm1,xmm2,xmm3/m128
    // VEX.NDS.128.66.0F.WIG FE /r VPADDD xmm1,xmm2,xmm3/m128
    FCML_I64( "vpaddb xmm0,xmm0,xmmword ptr [rax]", 0xc5, 0xf9, 0xfc, 0x00 );
    FCML_I32( "vpaddb xmm0,xmm0,xmm1", 0xc5, 0xf9, 0xfc, 0xc1 );
    FCML_I64( "vpaddw xmm0,xmm0,xmmword ptr [rax]", 0xc5, 0xf9, 0xfd, 0x00 );
    FCML_I32( "vpaddw xmm0,xmm0,xmm1", 0xc5, 0xf9, 0xfd, 0xc1 );
    FCML_I64( "vpaddd xmm0,xmm0,xmmword ptr [rax]", 0xc5, 0xf9, 0xfe, 0x00 );
    FCML_I32( "vpaddd xmm0,xmm0,xmm1", 0xc5, 0xf9, 0xfe, 0xc1 );
    // VEX.NDS.256.66.0F.WIG FC /r VPADDB ymm1,ymm2,ymm3/m256
    // VEX.NDS.256.66.0F.WIG FD /r VPADDW ymm1,ymm2,ymm3/m256
    // VEX.NDS.256.66.0F.WIG FE /r VPADDD ymm1,ymm2,ymm3/m256
    // VEX.NDS.256.66.0F.WIG D4 /r VPADDQ ymm1,ymm2,ymm3/m256
    FCML_I64( "vpaddb ymm0,ymm0,ymmword ptr [rax]", 0xc5, 0xfd, 0xfc, 0x00 );
    FCML_I32( "vpaddb ymm0,ymm0,ymm1", 0xc5, 0xfd, 0xfc, 0xc1 );
    FCML_I64( "vpaddw ymm0,ymm0,ymmword ptr [rax]", 0xc5, 0xfd, 0xfd, 0x00 );
    FCML_I32( "vpaddw ymm0,ymm0,ymm1", 0xc5, 0xfd, 0xfd, 0xc1 );
    FCML_I64( "vpaddd ymm0,ymm0,ymmword ptr [rax]", 0xc5, 0xfd, 0xfe, 0x00 );
    FCML_I32( "vpaddd ymm0,ymm0,ymm1", 0xc5, 0xfd, 0xfe, 0xc1 );
    FCML_I64( "vpaddq ymm0,ymm0,ymmword ptr [rax]", 0xc5, 0xfd, 0xd4, 0x00 );
    FCML_I32( "vpaddq ymm0,ymm0,ymm1", 0xc5, 0xfd, 0xd4, 0xc1 );
}

void fcml_tf_instruction_PADDS(void) {
    // 0F EC /r1 PADDSB mm,mm/m64
    FCML_I64( "paddsb mm0,mmword ptr [rax]", 0x0F, 0xEC, 0x00 );
    FCML_I32( "paddsb mm0,mm1", 0x0F, 0xEC, 0xC1 );
    // 0F ED /r1 PADDSW mm,mm/m64
    FCML_I64( "paddsw mm0,mmword ptr [rax]", 0x0F, 0xED, 0x00 );
    FCML_I32( "paddsw mm0,mm1", 0x0F, 0xED, 0xC1 );
    // 66 0F EC /r PADDSB xmm1,xmm2/m128
    FCML_I64( "paddsb xmm0,xmmword ptr [rax]", 0x66, 0x0F, 0xEC, 0x00 );
    FCML_I32( "paddsb xmm0,xmm1", 0x66, 0x0F, 0xEC, 0xC1 );
    // 66 0F ED /r PADDSW xmm1,xmm2/m128
    FCML_I64( "paddsw xmm0,xmmword ptr [rax]", 0x66, 0x0F, 0xED, 0x00 );
    FCML_I32( "paddsw xmm0,xmm1", 0x66, 0x0F, 0xED, 0xC1 );
    // VEX.NDS.128.66.0F.WIG EC /r VPADDSB xmm1,xmm2,xmm3/m128
    // VEX.NDS.128.66.0F.WIG ED /r VPADDSW xmm1,xmm2,xmm3/m128
    FCML_I64( "vpaddsb xmm0,xmm0,xmmword ptr [rax]", 0xc5, 0xf9, 0xec, 0x00 );
    FCML_I32( "vpaddsb xmm0,xmm0,xmm1", 0xc5, 0xf9, 0xec, 0xc1 );
    FCML_I64( "vpaddsw xmm0,xmm0,xmmword ptr [rax]", 0xc5, 0xf9, 0xed, 0x00 );
    FCML_I32( "vpaddsw xmm0,xmm0,xmm1", 0xc5, 0xf9, 0xed, 0xc1 );
    // VEX.NDS.256.66.0F.WIG EC /r VPADDSB ymm1,ymm2,ymm3/m256
    // VEX.NDS.256.66.0F.WIG ED /r VPADDSW ymm1,ymm2,ymm3/m256
    FCML_I64( "vpaddsb ymm0,ymm0,ymmword ptr [rax]", 0xc5, 0xfd, 0xec, 0x00 );
    FCML_I32( "vpaddsb ymm0,ymm0,ymm1", 0xc5, 0xfd, 0xec, 0xc1 );
    FCML_I64( "vpaddsw ymm0,ymm0,ymmword ptr [rax]", 0xc5, 0xfd, 0xed, 0x00 );
    FCML_I32( "vpaddsw ymm0,ymm0,ymm1", 0xc5, 0xfd, 0xed, 0xc1 );
}

void fcml_tf_instruction_PADDUS(void) {
    // 0F DC /r1 PADDUSB mm,mm/m64
    FCML_I64( "paddusb mm0,mmword ptr [rax]", 0x0F, 0xDC, 0x00 );
    FCML_I32( "paddusb mm0,mm1", 0x0F, 0xDC, 0xC1 );
    // 0F DD /r1 PADDUSW mm,mm/m64
    FCML_I64( "paddusw mm0,mmword ptr [rax]", 0x0F, 0xDD, 0x00 );
    FCML_I32( "paddusw mm0,mm1", 0x0F, 0xDD, 0xC1 );
    // 66 0F DC /r PADDUSB xmm1,xmm2/m128
    FCML_I64( "paddusb xmm0,xmmword ptr [rax]", 0x66, 0x0F, 0xDC, 0x00 );
    FCML_I32( "paddusb xmm0,xmm1", 0x66, 0x0F, 0xDC, 0xC1 );
    // 66 0F DD /r PADDUSW xmm1,xmm2/m128
    FCML_I64( "paddusw xmm0,xmmword ptr [rax]", 0x66, 0x0F, 0xDD, 0x00 );
    FCML_I32( "paddusw xmm0,xmm1", 0x66, 0x0F, 0xDD, 0xC1 );
    // VEX.NDS.128.66.0F.WIG DC /r VPADDUSB xmm1,xmm2,xmm3/m128
    // VEX.NDS.128.66.0F.WIG DD /r VPADDUSW xmm1,xmm2,xmm3/m128
    FCML_I64( "vpaddusb xmm0,xmm0,xmmword ptr [rax]", 0xc5, 0xf9, 0xdc, 0x00 );
    FCML_I32( "vpaddusb xmm0,xmm0,xmm1", 0xc5, 0xf9, 0xdc, 0xc1 );
    FCML_I64( "vpaddusw xmm0,xmm0,xmmword ptr [rax]", 0xc5, 0xf9, 0xdd, 0x00 );
    FCML_I32( "vpaddusw xmm0,xmm0,xmm1", 0xc5, 0xf9, 0xdd, 0xc1 );
    // VEX.NDS.256.66.0F.WIG DC /r VPADDUSB ymm1,ymm2,ymm3/m256
    // VEX.NDS.256.66.0F.WIG DD /r VPADDUSW ymm1,ymm2,ymm3/m256
    FCML_I64( "vpaddusb ymm0,ymm0,ymmword ptr [rax]", 0xc5, 0xfd, 0xdc, 0x00 );
    FCML_I32( "vpaddusb ymm0,ymm0,ymm1", 0xc5, 0xfd, 0xdc, 0xc1 );
    FCML_I64( "vpaddusw ymm0,ymm0,ymmword ptr [rax]", 0xc5, 0xfd, 0xdd, 0x00 );
    FCML_I32( "vpaddusw ymm0,ymm0,ymm1", 0xc5, 0xfd, 0xdd, 0xc1 );
}

void fcml_tf_instruction_PADDQ(void) {
    // 0F D4 /r1 PADDQ mm1,mm2/m64
    FCML_I64( "paddq mm0,mmword ptr [rax]", 0x0F, 0xD4, 0x00 );
    FCML_I32( "paddq mm0,mm1", 0x0F, 0xD4, 0xC1 );
    // 66 0F D4 /r PADDQ xmm1,xmm2/m128
    FCML_I64( "paddq xmm0,xmmword ptr [rax]", 0x66, 0x0F, 0xD4, 0x00 );
    FCML_I32( "paddq xmm0,xmm1", 0x66, 0x0F, 0xD4, 0xC1 );
    // VEX.NDS.128.66.0F.WIG D4 /r VPADDQ xmm1,xmm2,xmm3/m128
    FCML_I64_D( "vpaddq xmm0,xmm0,xmmword ptr [rax]", 0xC4, 0xE1, 0x79, 0xD4, 0x00 );
    FCML_I32_D( "vpaddq xmm0,xmm0,xmm1", 0xC4, 0xE1, 0x79, 0xD4, 0xC1 );
    FCML_I64( "vpaddq xmm0,xmm0,xmmword ptr [rax]", 0xc5, 0xf9, 0xd4, 0x00 );
    FCML_I32( "vpaddq xmm0,xmm0,xmm1", 0xc5, 0xf9, 0xd4, 0xc1 );
}

void fcml_tf_instruction_PALIGNR(void) {
    // 0F 3A 0F PALIGNR mm1,mm2/m64,imm8
    FCML_I64( "palignr mm0,mmword ptr [rax],0ffh", 0x0F, 0x3A, 0x0F, 0x00, 0xFF );
    FCML_I32( "palignr mm0,mm1,0ffh", 0x0F, 0x3A, 0x0F, 0xC1, 0xFF );
    // 66 0F 3A 0F PALIGNR xmm1,xmm2/m128,imm8
    FCML_I64( "palignr xmm0,xmmword ptr [rax],0ffh", 0x66, 0x0F, 0x3A, 0x0F, 0x00, 0xFF );
    FCML_I32( "palignr xmm0,xmm1,0ffh", 0x66, 0x0F, 0x3A, 0x0F, 0xC1, 0xFF );
    // VEX.NDS.128.66.0F3A.WIG 0F /r ib VPALIGNR xmm1,xmm2,xmm3/m128,imm8
    FCML_I64( "vpalignr xmm0,xmm0,xmmword ptr [rax],0ffh", 0xC4, 0xE3, 0x79, 0x0F, 0x00, 0xFF );
    FCML_I32( "vpalignr xmm0,xmm0,xmm1,0ffh", 0xC4, 0xE3, 0x79, 0x0F, 0xC1, 0xFF );
    // VEX.NDS.256.66.0F3A.WIG 0F /r ib VPALIGNR ymm1,ymm2,ymm3/m256,imm8
    FCML_I64( "vpalignr ymm0,ymm0,ymmword ptr [rax],0ffh", 0xC4, 0xE3, 0x7D, 0x0F, 0x00, 0xFF );
    FCML_I32( "vpalignr ymm0,ymm0,ymm1,0ffh", 0xC4, 0xE3, 0x7D, 0x0F, 0xC1, 0xFF );
}

void fcml_tf_instruction_PAND(void) {
    // 0F DB /r PAND mm,mm/m64
    FCML_I64( "pand mm0,mmword ptr [rax]", 0x0F, 0xDB, 0x00 );
    FCML_I32( "pand mm0,mm1", 0x0F, 0xDB, 0xC1 );
    // 66 0F DB /r PAND xmm1,xmm2/m128
    FCML_I64( "pand xmm0,xmmword ptr [rax]", 0x66, 0x0F, 0xDB, 0x00 );
    FCML_I32( "pand xmm0,xmm1", 0x66, 0x0F, 0xDB, 0xC1 );
    // VEX.NDS.128.66.0F.WIG DB /r VPAND xmm1,xmm2,xmm3/m128
    FCML_I64( "vpand xmm0,xmm2,xmmword ptr [rax]", 0xc5, 0xe9, 0xdb, 0x00 );
    FCML_I32( "vpand xmm0,xmm2,xmm1", 0xc5, 0xe9, 0xdb, 0xc1 );
    // VEX.NDS.256.66.0F.WIG DB /r VPAND ymm1,ymm2,ymm3/m256
    FCML_I64( "vpand ymm0,ymm2,ymmword ptr [rax]", 0xc5, 0xed, 0xdb, 0x00 );
    FCML_I32( "vpand ymm0,ymm2,ymm1", 0xc5, 0xed, 0xdb, 0xc1 );
}

void fcml_tf_instruction_PANDN(void) {
    // 0F DF /r PANDN mm,mm/m64
    FCML_I64( "pandn mm0,mmword ptr [rax]", 0x0F, 0xDF, 0x00 );
    FCML_I32( "pandn mm0,mm1", 0x0F, 0xDF, 0xC1 );
    // 66 0F DF /r PANDN xmm1,xmm2/m128
    FCML_I64( "pandn xmm0,xmmword ptr [rax]", 0x66, 0x0F, 0xDF, 0x00 );
    FCML_I32( "pandn xmm0,xmm1", 0x66, 0x0F, 0xDF, 0xC1 );
    // VEX.NDS.128.66.0F.WIG DF /r VPANDN xmm1,xmm2,xmm3/m128
    FCML_I64( "vpandn xmm0,xmm2,xmmword ptr [rax]", 0xc5, 0xe9, 0xdf, 0x00 );
    FCML_I32( "vpandn xmm0,xmm2,xmm1", 0xc5, 0xe9, 0xdf, 0xc1 );
    // VEX.NDS.256.66.0F.WIG DF /r VPANDN ymm1,ymm2,ymm3/m256
    FCML_I64( "vpandn ymm0,ymm2,ymmword ptr [rax]", 0xc5, 0xed, 0xdf, 0x00 );
    FCML_I32( "vpandn ymm0,ymm2,ymm1", 0xc5, 0xed, 0xdf, 0xc1 );
}

void fcml_tf_instruction_PAUSE(void) {
    // F3 90 PAUSE
    FCML_I3264( "pause", 0xF3, 0x90 );
}

void fcml_tf_instruction_PAVGB(void) {
    // 0F E0 /r1 PAVGB mm1,mm2/m64
    FCML_I64( "pavgb mm0,mmword ptr [rax]", 0x0F, 0xE0, 0x00 );
    FCML_I32( "pavgb mm0,mm1", 0x0F, 0xE0, 0xC1 );
    // 0F E3 /r1 PAVGW mm1,mm2/m64
    FCML_I64( "pavgw mm0,mmword ptr [rax]", 0x0F, 0xE3, 0x00 );
    FCML_I32( "pavgw mm0,mm1", 0x0F, 0xE3, 0xC1 );
    // 66 0F E0, /r PAVGB xmm1,xmm2/m128
    FCML_I64( "pavgb xmm0,xmmword ptr [rax]", 0x66, 0x0F, 0xE0, 0x00 );
    FCML_I32( "pavgb xmm0,xmm1", 0x66, 0x0F, 0xE0, 0xC1 );
    // 66 0F E3 /r PAVGW xmm1,xmm2/m128
    FCML_I64( "pavgw xmm0,xmmword ptr [rax]", 0x66, 0x0F, 0xE3, 0x00 );
    FCML_I32( "pavgw xmm0,xmm1", 0x66, 0x0F, 0xE3, 0xC1 );
    // VEX.NDS.128.66.0F.WIG E0 /r VPAVGB xmm1,xmm2,xmm3/m128
    // VEX.NDS.128.66.0F.WIG E3 /r VPAVGW xmm1,xmm2,xmm3/m128
    FCML_I64( "vpavgb xmm0,xmm0,xmmword ptr [rax]", 0xc5, 0xf9, 0xe0, 0x00 );
    FCML_I32( "vpavgb xmm0,xmm0,xmm1", 0xc5, 0xf9, 0xe0, 0xc1 );
    FCML_I64( "vpavgw xmm0,xmm0,xmmword ptr [rax]", 0xc5, 0xf9, 0xe3, 0x00 );
    FCML_I32( "vpavgw xmm0,xmm0,xmm1", 0xc5, 0xf9, 0xe3, 0xc1 );
}

void fcml_tf_instruction_PBLENDVB(void) {
    // 66 0F 38 10 /r PBLENDVB xmm1,xmm2/m128,<XMM0>
    FCML_I32( "pblendvb xmm2,xmmword ptr [ecx+eax],xmm0", 0x66, 0x0f, 0x38, 0x10, 0x14, 0x01 );
    FCML_I64( "pblendvb xmm2,xmmword ptr [rcx+rax],xmm0", 0x66, 0x0F, 0x38, 0x10, 0x14, 0x01 );
    // VEX.NDS.128.66.0F3A 4C /r /is4 VPBLENDVB xmm1,xmm2,xmm3/m128,xmm4
    FCML_I32( "vpblendvb xmm2,xmm7,xmmword ptr [ecx+eax],xmm2", 0xc4, 0xe3, 0x41, 0x4c, 0x14, 0x01, 0x20 );
    FCML_I32( "vpblendvb xmm2,xmm2,xmmword ptr [ecx+eax],xmm2", 0xc4, 0xe3, 0x69, 0x4c, 0x14, 0x01, 0x20 );
    FCML_I64( "vpblendvb xmm2,xmm2,xmmword ptr [r9+rax],xmm10", 0xC4, 0xC3, 0x69, 0x4C, 0x14, 0x01, 0xA0 );
    // VEX.NDS.256.66.0F3A.W0 4C /r /is4 VPBLENDVB ymm1,ymm2,ymm3/m256,ymm4
    FCML_I32( "vpblendvb ymm2,ymm7,ymmword ptr [ecx+eax],ymm2", 0xc4, 0xe3, 0x45, 0x4c, 0x14, 0x01, 0x20 );
    FCML_I64( "vpblendvb ymm2,ymm2,ymmword ptr [r9+rax],ymm10", 0xC4, 0xC3, 0x6D, 0x4C, 0x14, 0x01, 0xA0 );
}

void fcml_tf_instruction_PBLENDW(void) {
    // 66 0F 3A 0E /r ib PBLENDW xmm1,xmm2/m128,imm8
    FCML_I64( "pblendw xmm0,xmmword ptr [rax],0ffh", 0x66, 0x0F, 0x3A, 0x0E, 0x00, 0xFF );
    FCML_I32( "pblendw xmm0,xmm1,0ffh", 0x66, 0x0F, 0x3A, 0x0E, 0xC1, 0xFF );
    // VEX.NDS.128.66.0F3A 0E /r ib VPBLENDW xmm1,xmm2,xmm3/m128,imm8
    FCML_I64( "vpblendw xmm0,xmm0,xmmword ptr [rax],0ffh", 0xC4, 0xE3, 0x79, 0x0E, 0x00, 0xFF );
    FCML_I32( "vpblendw xmm0,xmm0,xmm1,0ffh", 0xC4, 0xE3, 0x79, 0x0E, 0xC1, 0xFF );
    // VEX.NDS.256.66.0F3A.WIG 0E /r ib VPBLENDW ymm1,ymm2,ymm3/m256,imm8
    FCML_I64( "vpblendw ymm0,ymm0,ymmword ptr [rax],0ffh", 0xC4, 0xE3, 0x7D, 0x0E, 0x00, 0xFF );
    FCML_I32( "vpblendw ymm0,ymm0,ymm1,0ffh", 0xC4, 0xE3, 0x7D, 0x0E, 0xC1, 0xFF );
}

void fcml_tf_instruction_PCLMULQDQ(void) {
    // 66 0F 3A 44 /r ib PCLMULQDQ xmm1,xmm2/m128,imm8
    FCML_I64( "pclmulqdq xmm0,xmmword ptr [rax],0ffh", 0x66, 0x0F, 0x3A, 0x44, 0x00, 0xFF );
    FCML_I32( "pclmulqdq xmm0,xmm1,0ffh", 0x66, 0x0F, 0x3A, 0x44, 0xC1, 0xFF );
    // VEX.NDS.128.66.0F3A 44 /r ib VPCLMULQDQ xmm1,xmm2,xmm3/m128,imm8
    FCML_I64( "vpclmulqdq xmm0,xmm0,xmmword ptr [rax],0ffh", 0xC4, 0xE3, 0x79, 0x44, 0x00, 0xFF );
    FCML_I32( "vpclmulqdq xmm0,xmm0,xmm1,0ffh", 0xC4, 0xE3, 0x79, 0x44, 0xC1, 0xFF );
}

void fcml_tf_instruction_PCMPEQ(void) {
    // 0F 74 /r1 PCMPEQB mm,mm/m64
    // 0F 75 /r1 PCMPEQW mm,mm/m64
    // 0F 76 /r1 PCMPEQD mm,mm/m64
    FCML_I64( "pcmpeqb mm0,mmword ptr [rax]", 0x0F, 0x74, 0x00 );
    FCML_I32( "pcmpeqb mm0,mm1", 0x0F, 0x74, 0xC1 );
    FCML_I64( "pcmpeqw mm0,mmword ptr [rax]", 0x0F, 0x75, 0x00 );
    FCML_I32( "pcmpeqw mm0,mm1", 0x0F, 0x75, 0xC1 );
    FCML_I64( "pcmpeqd mm0,mmword ptr [rax]", 0x0F, 0x76, 0x00 );
    FCML_I32( "pcmpeqd mm0,mm1", 0x0F, 0x76, 0xC1 );
    // 66 0F 74 /r PCMPEQB xmm1,xmm2/m128
    // 66 0F 75 /r PCMPEQW xmm1,xmm2/m128
    // 66 0F 76 /r PCMPEQD xmm1,xmm2/m128
    FCML_I64( "pcmpeqb xmm0,xmmword ptr [rax]", 0x66, 0x0F, 0x74, 0x00 );
    FCML_I32( "pcmpeqb xmm0,xmm1", 0x66, 0x0F, 0x74, 0xC1 );
    FCML_I64( "pcmpeqw xmm0,xmmword ptr [rax]", 0x66, 0x0F, 0x75, 0x00 );
    FCML_I32( "pcmpeqw xmm0,xmm1", 0x66, 0x0F, 0x75, 0xC1 );
    FCML_I64( "pcmpeqd xmm0,xmmword ptr [rax]", 0x66, 0x0F, 0x76, 0x00 );
    FCML_I32( "pcmpeqd xmm0,xmm1", 0x66, 0x0F, 0x76, 0xC1 );
    // VEX.NDS.128.66.0F.WIG 74 /r VPCMPEQB xmm1,xmm2,xmm3/m128
    // VEX.NDS.128.66.0F.WIG 75 /r VPCMPEQW xmm1,xmm2,xmm3/m128
    // VEX.NDS.128.66.0F.WIG 76 /r VPCMPEQD xmm1,xmm2,xmm3/m128
    FCML_I64( "vpcmpeqb xmm0,xmm0,xmmword ptr [rax]", 0xc5, 0xf9, 0x74, 0x00 );
    FCML_I32( "vpcmpeqb xmm0,xmm0,xmm1", 0xc5, 0xf9, 0x74, 0xc1 );
    FCML_I64( "vpcmpeqw xmm0,xmm0,xmmword ptr [rax]", 0xc5, 0xf9, 0x75, 0x00 );
    FCML_I32( "vpcmpeqw xmm0,xmm0,xmm1", 0xc5, 0xf9, 0x75, 0xc1 );
    FCML_I64( "vpcmpeqd xmm0,xmm0,xmmword ptr [rax]", 0xc5, 0xf9, 0x76, 0x00 );
    FCML_I32( "vpcmpeqd xmm0,xmm0,xmm1", 0xc5, 0xf9, 0x76, 0xc1 );
    // VEX.NDS.256.66.0F.WIG 74 /r VPCMPEQB ymm1,ymm2,ymm3/m256
    // VEX.NDS.256.66.0F.WIG 75 /r VPCMPEQW ymm1,ymm2,ymm3/m256
    // VEX.NDS.256.66.0F.WIG 76 /r VPCMPEQD ymm1,ymm2,ymm3/m256
    FCML_I64( "vpcmpeqb ymm0,ymm0,ymmword ptr [rax]", 0xc5, 0xfd, 0x74, 0x00 );
    FCML_I32( "vpcmpeqb ymm0,ymm0,ymm1", 0xc5, 0xfd, 0x74, 0xc1 );
    FCML_I64( "vpcmpeqw ymm0,ymm0,ymmword ptr [rax]", 0xc5, 0xfd, 0x75, 0x00 );
    FCML_I32( "vpcmpeqw ymm0,ymm0,ymm1", 0xc5, 0xfd, 0x75, 0xc1 );
    FCML_I64( "vpcmpeqd ymm0,ymm0,ymmword ptr [rax]", 0xc5, 0xfd, 0x76, 0x00 );
    FCML_I32( "vpcmpeqd ymm0,ymm0,ymm1", 0xc5, 0xfd, 0x76, 0xc1 );
}

void fcml_tf_instruction_PCMPEQQ(void) {
    // 66 0F 38 29 /r PCMPEQQ xmm1,xmm2/m128
    FCML_I64( "pcmpeqq xmm0,xmmword ptr [rax]", 0x66, 0x0F, 0x38, 0x29, 0x00 );
    FCML_I32( "pcmpeqq xmm0,xmm1", 0x66, 0x0F, 0x38, 0x29, 0xC1 );
    // VEX.NDS.128.66.0F38.WIG 29 /r VPCMPEQQ xmm1,xmm2,xmm3/m128
    FCML_I64( "vpcmpeqq xmm0,xmm0,xmmword ptr [rax]", 0xC4, 0xE2, 0x79, 0x29, 0x00 );
    FCML_I32( "vpcmpeqq xmm0,xmm0,xmm1", 0xC4, 0xE2, 0x79, 0x29, 0xC1 );
    // VEX.NDS.256.66.0F38.WIG 29 /r VPCMPEQQ ymm1,ymm2,ymm3/m256
    FCML_I64( "vpcmpeqq ymm0,ymm0,ymmword ptr [rax]", 0xC4, 0xE2, 0x7D, 0x29, 0x00 );
    FCML_I32( "vpcmpeqq ymm0,ymm0,ymm1", 0xC4, 0xE2, 0x7D, 0x29, 0xC1 );
}

void fcml_tf_instruction_PCMPESTRI(void) {
    // 66 0F 3A 61 /r imm8 PCMPESTRI xmm1,xmm2/m128,imm8
    FCML_I64( "pcmpestri xmm0,xmmword ptr [rax],0ffh", 0x66, 0x0F, 0x3A, 0x61, 0x00, 0xFF );
    FCML_I32( "pcmpestri xmm0,xmm1,0ffh", 0x66, 0x0F, 0x3A, 0x61, 0xC1, 0xFF );
    // VEX.128.66.0F3A.WIG 61 /r ib VPCMPESTRI xmm1,xmm2/m128,imm8
    FCML_I64( "vpcmpestri xmm0,xmmword ptr [rax],0ffh", 0xC4, 0xE3, 0x79, 0x61, 0x00, 0xFF );
    FCML_I32( "vpcmpestri xmm0,xmm1,0ffh", 0xC4, 0xE3, 0x79, 0x61, 0xC1, 0xFF );
}

void fcml_tf_instruction_PCMPESTRM(void) {
    // 66 0F 3A 60 /r imm8 PCMPESTRM xmm1,xmm2/m128,imm8
    FCML_I64( "pcmpestrm xmm0,xmmword ptr [rax],0ffh", 0x66, 0x0F, 0x3A, 0x60, 0x00, 0xFF );
    FCML_I32( "pcmpestrm xmm0,xmm1,0ffh", 0x66, 0x0F, 0x3A, 0x60, 0xC1, 0xFF );
    // VEX.128.66.0F3A.WIG 60 /r ib VPCMPESTRM xmm1,xmm2/m128,imm8
    FCML_I64( "vpcmpestrm xmm0,xmmword ptr [rax],0ffh", 0xC4, 0xE3, 0x79, 0x60, 0x00, 0xFF );
    FCML_I32( "vpcmpestrm xmm0,xmm1,0ffh", 0xC4, 0xE3, 0x79, 0x60, 0xC1, 0xFF );
}

void fcml_tf_instruction_PCMPGT(void) {
    // 0F 64 /r1 PCMPGTB mm,mm/m64
    // 0F 65 /r1 PCMPGTW mm,mm/m64
    // 0F 66 /r1 PCMPGTD mm,mm/m64
    FCML_I64( "pcmpgtb mm0,mmword ptr [rax]", 0x0F, 0x64, 0x00 );
    FCML_I32( "pcmpgtb mm0,mm1", 0x0F, 0x64, 0xC1 );
    FCML_I64( "pcmpgtw mm0,mmword ptr [rax]", 0x0F, 0x65, 0x00 );
    FCML_I32( "pcmpgtw mm0,mm1", 0x0F, 0x65, 0xC1 );
    FCML_I64( "pcmpgtd mm0,mmword ptr [rax]", 0x0F, 0x66, 0x00 );
    FCML_I32( "pcmpgtd mm0,mm1", 0x0F, 0x66, 0xC1 );
    // 66 0F 64 /r PCMPGTB xmm1,xmm2/m128
    // 66 0F 65 /r PCMPGTW xmm1,xmm2/m128
    // 66 0F 66 /r PCMPGTD xmm1,xmm2/m128
    FCML_I64( "pcmpgtb xmm0,xmmword ptr [rax]", 0x66, 0x0F, 0x64, 0x00 );
    FCML_I32( "pcmpgtb xmm0,xmm1", 0x66, 0x0F, 0x64, 0xC1 );
    FCML_I64( "pcmpgtw xmm0,xmmword ptr [rax]", 0x66, 0x0F, 0x65, 0x00 );
    FCML_I32( "pcmpgtw xmm0,xmm1", 0x66, 0x0F, 0x65, 0xC1 );
    FCML_I64( "pcmpgtd xmm0,xmmword ptr [rax]", 0x66, 0x0F, 0x66, 0x00 );
    FCML_I32( "pcmpgtd xmm0,xmm1", 0x66, 0x0F, 0x66, 0xC1 );
    // VEX.NDS.128.66.0F.WIG 64 /r VPCMPGTB xmm1,xmm2,xmm3/m128
    // VEX.NDS.128.66.0F.WIG 65 /r VPCMPGTW xmm1,xmm2,xmm3/m128
    // VEX.NDS.128.66.0F.WIG 66 /r VPCMPGTD xmm1,xmm2,xmm3/m128
    FCML_I64( "vpcmpgtb xmm0,xmm0,xmmword ptr [rax]", 0xc5, 0xf9, 0x64, 0x00 );
    FCML_I32( "vpcmpgtb xmm0,xmm0,xmm1", 0xc5, 0xf9, 0x64, 0xc1 );
    FCML_I64( "vpcmpgtw xmm0,xmm0,xmmword ptr [rax]", 0xc5, 0xf9, 0x65, 0x00 );
    FCML_I32( "vpcmpgtw xmm0,xmm0,xmm1", 0xc5, 0xf9, 0x65, 0xc1 );
    FCML_I64( "vpcmpgtd xmm0,xmm0,xmmword ptr [rax]", 0xc5, 0xf9, 0x66, 0x00 );
    FCML_I32( "vpcmpgtd xmm0,xmm0,xmm1", 0xc5, 0xf9, 0x66, 0xc1 );
    // VEX.NDS.256.66.0F.WIG 64 /r VPCMPGTB ymm1,ymm2,ymm3/m256
    // VEX.NDS.256.66.0F.WIG 65 /r VPCMPGTW ymm1,ymm2,ymm3/m256
    // VEX.NDS.256.66.0F.WIG 66 /r VPCMPGTD ymm1,ymm2,ymm3/m256
    FCML_I64( "vpcmpgtb ymm0,ymm0,ymmword ptr [rax]", 0xc5, 0xfd, 0x64, 0x00 );
    FCML_I32( "vpcmpgtb ymm0,ymm0,ymm1", 0xc5, 0xfd, 0x64, 0xc1 );
    FCML_I64( "vpcmpgtw ymm0,ymm0,ymmword ptr [rax]", 0xc5, 0xfd, 0x65, 0x00 );
    FCML_I32( "vpcmpgtw ymm0,ymm0,ymm1", 0xc5, 0xfd, 0x65, 0xc1 );
    FCML_I64( "vpcmpgtd ymm0,ymm0,ymmword ptr [rax]", 0xc5, 0xfd, 0x66, 0x00 );
    FCML_I32( "vpcmpgtd ymm0,ymm0,ymm1", 0xc5, 0xfd, 0x66, 0xc1 );
}

void fcml_tf_instruction_PCMPGTQ(void) {
    // 66 0F 38 37 /r PCMPGTQ xmm1,xmm2/m128
    FCML_I64( "pcmpgtq xmm0,xmmword ptr [rax]", 0x66, 0x0F, 0x38, 0x37, 0x00 );
    FCML_I32( "pcmpgtq xmm0,xmm1", 0x66, 0x0F, 0x38, 0x37, 0xC1 );
    // VEX.NDS.128.66.0F38.WIG 37 /r VPCMPGTQ xmm1,xmm2,xmm3/m128
    FCML_I64( "vpcmpgtq xmm0,xmm0,xmmword ptr [rax]", 0xC4, 0xE2, 0x79, 0x37, 0x00 );
    FCML_I32( "vpcmpgtq xmm0,xmm0,xmm1", 0xC4, 0xE2, 0x79, 0x37, 0xC1 );
    // VEX.NDS.256.66.0F38.WIG 37 /r VPCMPGTQ ymm1,ymm2,ymm3/m256
    FCML_I64( "vpcmpgtq ymm0,ymm0,ymmword ptr [rax]", 0xC4, 0xE2, 0x7D, 0x37, 0x00 );
    FCML_I32( "vpcmpgtq ymm0,ymm0,ymm1", 0xC4, 0xE2, 0x7D, 0x37, 0xC1 );
}

void fcml_tf_instruction_PCMPISTRI(void) {
    // 66 0F 3A 63 /r imm8 PCMPISTRI xmm1,xmm2/m128,imm8
    FCML_I64( "pcmpistri xmm0,xmmword ptr [rax],0ffh", 0x66, 0x0F, 0x3A, 0x63, 0x00, 0xFF );
    FCML_I32( "pcmpistri xmm0,xmm1,0ffh", 0x66, 0x0F, 0x3A, 0x63, 0xC1, 0xFF );
    // VEX.128.66.0F3A.WIG 63 /r ib VPCMPISTRI xmm1,xmm2/m128,imm8
    FCML_I64( "vpcmpistri xmm0,xmmword ptr [rax],0ffh", 0xC4, 0xE3, 0x79, 0x63, 0x00, 0xFF );
    FCML_I32( "vpcmpistri xmm0,xmm1,0ffh", 0xC4, 0xE3, 0x79, 0x63, 0xC1, 0xFF );
}

void fcml_tf_instruction_PCMPISTRM(void) {
    // 66 0F 3A 62 /r imm8 PCMPISTRM xmm1,xmm2/m128,imm8
    FCML_I64( "pcmpistrm xmm0,xmmword ptr [rax],0ffh", 0x66, 0x0F, 0x3A, 0x62, 0x00, 0xFF );
    FCML_I32( "pcmpistrm xmm0,xmm1,0ffh", 0x66, 0x0F, 0x3A, 0x62, 0xC1, 0xFF );
    // VEX.128.66.0F3A.WIG 62 /r ib VPCMPISTRM xmm1,xmm2/m128,imm8
    FCML_I64( "vpcmpistrm xmm0,xmmword ptr [rax],0ffh", 0xC4, 0xE3, 0x79, 0x62, 0x00, 0xFF );
    FCML_I32( "vpcmpistrm xmm0,xmm1,0ffh", 0xC4, 0xE3, 0x79, 0x62, 0xC1, 0xFF );
}

void fcml_tf_instruction_PEXTRB(void) {
    // 66 0F 3A 14 /r ib PEXTRB reg/m8,xmm2,imm8
    FCML_I64( "pextrb byte ptr [rax],xmm0,0ffh", 0x66, 0x0F, 0x3A, 0x14, 0x00, 0xFF );
    FCML_I64( "pextrb rcx,xmm0,0ffh", 0x66, 0x0F, 0x3A, 0x14, 0xC1, 0xFF );
    FCML_I32( "pextrb byte ptr [eax],xmm0,0ffh", 0x66, 0x0F, 0x3A, 0x14, 0x00, 0xFF );
    FCML_I32( "pextrb ecx,xmm0,0ffh", 0x66, 0x0F, 0x3A, 0x14, 0xC1, 0xFF );
    // 66 0F 3A 16 /r ib PEXTRD r/m32, xmm2, imm8
    FCML_I64( "pextrd dword ptr [rax],xmm0,0ffh", 0x66, 0x0F, 0x3A, 0x16, 0x00, 0xFF );
    FCML_I64( "pextrd rcx,xmm0,0ffh", 0x66, 0x0F, 0x3A, 0x16, 0xC1, 0xFF );
    FCML_I32( "pextrd dword ptr [eax],xmm0,0ffh", 0x66, 0x0F, 0x3A, 0x16, 0x00, 0xFF );
    FCML_I32( "pextrd ecx,xmm0,0ffh", 0x66, 0x0F, 0x3A, 0x16, 0xC1, 0xFF );
    // 66 REX.W 0F 3A 16 /r ib PEXTRQ r/m64, xmm2, imm8
    FCML_I64( "pextrq qword ptr [rax],xmm0,0ffh", 0x66, 0x48, 0x0F, 0x3A, 0x16, 0x00, 0xFF );
    FCML_I64( "pextrq rcx,xmm0,0ffh", 0x66, 0x48, 0x0F, 0x3A, 0x16, 0xC1, 0xFF );
    // VEX.128.66.0F3A.W0 14 /r ib VPEXTRB reg/m8, xmm2, imm8
    FCML_I64( "vpextrb byte ptr [rax],xmm0,0ffh", 0xC4, 0xE3, 0x79, 0x14, 0x00, 0xFF );
    FCML_I64( "vpextrb rcx,xmm0,0ffh", 0xC4, 0xE3, 0x79, 0x14, 0xC1, 0xFF );
    FCML_I32( "vpextrb byte ptr [eax],xmm0,0ffh", 0xC4, 0xE3, 0x79, 0x14, 0x00, 0xFF );
    FCML_I32( "vpextrb ecx,xmm0,0ffh", 0xC4, 0xE3, 0x79, 0x14, 0xC1, 0xFF );
    // VEX.128.66.0F3A.W0 16 /r ib VPEXTRD r32/m32, xmm2, imm8
    FCML_I64( "vpextrd dword ptr [rax],xmm0,0ffh", 0xC4, 0xE3, 0x79, 0x16, 0x00, 0xFF );
    FCML_I64( "vpextrd rcx,xmm0,0ffh", 0xC4, 0xE3, 0x79, 0x16, 0xC1, 0xFF );
    FCML_I32( "vpextrd dword ptr [eax],xmm0,0ffh", 0xC4, 0xE3, 0x79, 0x16, 0x00, 0xFF );
    FCML_I32( "vpextrd ecx,xmm0,0ffh", 0xC4, 0xE3, 0x79, 0x16, 0xC1, 0xFF );
    // VEX.128.66.0F3A.W1 16 /r ib VPEXTRQ r64/m64, xmm2, imm8
    FCML_I64( "vpextrq qword ptr [rax],xmm0,0ffh", 0xC4, 0xE3, 0xF9, 0x16, 0x00, 0xFF );
    FCML_I64( "vpextrq rcx,xmm0,0ffh", 0xC4, 0xE3, 0xF9, 0x16, 0xC1, 0xFF );
}

void fcml_tf_instruction_PEXTRW(void) {
    // 0F C5 /r ib PEXTRW reg,mm,imm8
    FCML_I64( "pextrw rax,mm1,0ffh", 0x0F, 0xC5, 0xC1, 0xFF );
    FCML_I32( "pextrw eax,mm1,0ffh", 0x0F, 0xC5, 0xC1, 0xFF );
    // 66 0F C5 /r ib PEXTRW reg,xmm,imm8
    FCML_I64_M( "pextrw rax,xmm1,0ffh", 2, FCML_MI( 0x66, 0x0f, 0x3a, 0x15, 0xc8, 0xff ), FCML_MI( 0x66, 0x0f, 0xc5, 0xc1, 0xff ) );
    FCML_I32_M( "pextrw eax,xmm1,0ffh", 2, FCML_MI( 0x66, 0x0f, 0x3a, 0x15, 0xc8, 0xff ), FCML_MI( 0x66, 0x0f, 0xc5, 0xc1, 0xff ) );
    // 66 0F 3A 15 /r ib PEXTRW reg/m16,xmm,imm8
    FCML_I64( "pextrw word ptr [rax],xmm0,0ffh", 0x66, 0x0F, 0x3A, 0x15, 0x00, 0xFF );
    FCML_I64_M( "pextrw rcx,xmm0,0ffh", 2, FCML_MI( 0x66, 0x0f, 0x3a, 0x15, 0xc1, 0xff ), FCML_MI( 0x66, 0x0f, 0xc5, 0xc8, 0xff ) );
    FCML_I32( "pextrw word ptr [eax],xmm0,0ffh", 0x66, 0x0F, 0x3A, 0x15, 0x00, 0xFF );
    FCML_I32_M( "pextrw ecx,xmm0,0ffh", 2, FCML_MI( 0x66, 0x0f, 0x3a, 0x15, 0xc1, 0xff ), FCML_MI( 0x66, 0x0f, 0xc5, 0xc8, 0xff ) );
    // VEX.128.66.0F.W0 C5 /r ib VPEXTRW reg,xmm1,imm8
    FCML_I64_M( "vpextrw rax,xmm1,0ffh", 2, FCML_MI( 0xc4, 0xe3, 0x79, 0x15, 0xc8, 0xff ), FCML_MI( 0xc5, 0xf9, 0xc5, 0xc1, 0xff ) );
    FCML_I32_M( "vpextrw eax,xmm1,0ffh", 2, FCML_MI( 0xc4, 0xe3, 0x79, 0x15, 0xc8, 0xff ), FCML_MI( 0xc5, 0xf9, 0xc5, 0xc1, 0xff ) );
    // VEX.128.66.0F3A.W0 15 /r ib VPEXTRW reg/m16,xmm2,imm8
    FCML_I64( "vpextrw word ptr [rax],xmm0,0ffh", 0xC4, 0xE3, 0x79, 0x15, 0x00, 0xFF );
    FCML_I64_M( "vpextrw rcx,xmm0,0ffh", 2, FCML_MI( 0xc4, 0xe3, 0x79, 0x15, 0xc1, 0xff ), FCML_MI( 0xc5, 0xf9, 0xc5, 0xc8, 0xff ) );
    FCML_I32( "vpextrw word ptr [eax],xmm0,0ffh", 0xC4, 0xE3, 0x79, 0x15, 0x00, 0xFF );
    FCML_I32_M( "vpextrw ecx,xmm0,0ffh", 2, FCML_MI( 0xc4, 0xe3, 0x79, 0x15, 0xc1, 0xff ), FCML_MI( 0xc5, 0xf9, 0xc5, 0xc8, 0xff ) );
}

void fcml_tf_instruction_PHADDW(void) {
    // 0F 38 01 /r PHADDW mm1, mm2/m64
    // 0F 38 02 /r PHADDD mm1, mm2/m64
    FCML_I64( "phaddw mm0,mmword ptr [rax]", 0x0F, 0x38, 0x01, 0x00 );
    FCML_I32( "phaddw mm0,mm1", 0x0F, 0x38, 0x01, 0xC1 );
    FCML_I64( "phaddd mm0,mmword ptr [rax]", 0x0F, 0x38, 0x02, 0x00 );
    FCML_I32( "phaddd mm0,mm1", 0x0F, 0x38, 0x02, 0xC1 );
    // 66 0F 38 01 /r PHADDW xmm1, xmm2/m128
    // 66 0F 38 02 /r PHADDD xmm1, xmm2/m128
    FCML_I64( "phaddw xmm0,xmmword ptr [rax]", 0x66, 0x0F, 0x38, 0x01, 0x00 );
    FCML_I32( "phaddw xmm0,xmm1", 0x66, 0x0F, 0x38, 0x01, 0xC1 );
    FCML_I64( "phaddd xmm0,xmmword ptr [rax]", 0x66, 0x0F, 0x38, 0x02, 0x00 );
    FCML_I32( "phaddd xmm0,xmm1", 0x66, 0x0F, 0x38, 0x02, 0xC1 );
    // VEX.NDS.128.66.0F38.WIG 01 /r VPHADDW xmm1,xmm2,xmm3/m128
    // VEX.NDS.128.66.0F38.WIG 02 /r VPHADDD xmm1,xmm2,xmm3/m128
    FCML_I64( "vphaddw xmm0,xmm0,xmmword ptr [rax]", 0xC4, 0xE2, 0x79, 0x01, 0x00 );
    FCML_I32( "vphaddw xmm0,xmm0,xmm1", 0xC4, 0xE2, 0x79, 0x01, 0xC1 );
    FCML_I64( "vphaddd xmm0,xmm0,xmmword ptr [rax]", 0xC4, 0xE2, 0x79, 0x02, 0x00 );
    FCML_I32( "vphaddd xmm0,xmm0,xmm1", 0xC4, 0xE2, 0x79, 0x02, 0xC1 );
    // VEX.NDS.256.66.0F38.WIG 01 /r VPHADDW ymm1,ymm2,ymm3/m256
    // VEX.NDS.256.66.0F38.WIG 02 /r VPHADDD ymm1,ymm2,ymm3/m256
    FCML_I64( "vphaddw ymm0,ymm0,ymmword ptr [rax]", 0xC4, 0xE2, 0x7D, 0x01, 0x00 );
    FCML_I32( "vphaddw ymm0,ymm0,ymm1", 0xC4, 0xE2, 0x7D, 0x01, 0xC1 );
    FCML_I64( "vphaddd ymm0,ymm0,ymmword ptr [rax]", 0xC4, 0xE2, 0x7D, 0x02, 0x00 );
    FCML_I32( "vphaddd ymm0,ymm0,ymm1", 0xC4, 0xE2, 0x7D, 0x02, 0xC1 );
}

void fcml_tf_instruction_PHADDSW(void) {
    // 0F 38 03 /r PHADDSW mm1,mm2/m64
    FCML_I64( "phaddsw mm0,mmword ptr [rax]", 0x0F, 0x38, 0x03, 0x00 );
    FCML_I32( "phaddsw mm0,mm1", 0x0F, 0x38, 0x03, 0xC1 );
    // 66 0F 38 03 /r PHADDSW xmm1,xmm2/m128
    FCML_I64( "phaddsw xmm0,xmmword ptr [rax]", 0x66, 0x0F, 0x38, 0x03, 0x00 );
    FCML_I32( "phaddsw xmm0,xmm1", 0x66, 0x0F, 0x38, 0x03, 0xC1 );
    // VEX.NDS.128.66.0F38.WIG 03 /r VPHADDSW xmm1,xmm2,xmm3/m128
    FCML_I64( "vphaddsw xmm0,xmm0,xmmword ptr [rax]", 0xC4, 0xE2, 0x79, 0x03, 0x00 );
    FCML_I32( "vphaddsw xmm0,xmm0,xmm1", 0xC4, 0xE2, 0x79, 0x03, 0xC1 );
    // VEX.NDS.256.66.0F38.WIG 03 /r VPHADDSW ymm1,ymm2,ymm3/m256
    FCML_I64( "vphaddsw ymm0,ymm0,ymmword ptr [rax]", 0xC4, 0xE2, 0x7D, 0x03, 0x00 );
    FCML_I32( "vphaddsw ymm0,ymm0,ymm1", 0xC4, 0xE2, 0x7D, 0x03, 0xC1 );
}

void fcml_tf_instruction_PHMINPOSUW(void) {
    // 66 0F 38 41 /r PHMINPOSUW xmm1,xmm2/m128
    FCML_I64( "phminposuw xmm0,xmmword ptr [rax]", 0x66, 0x0F, 0x38, 0x41, 0x00 );
    FCML_I32( "phminposuw xmm0,xmm1", 0x66, 0x0F, 0x38, 0x41, 0xC1 );
    // VEX.128.66.0F38.WIG 41 /r VPHMINPOSUW xmm1,xmm2/m128
    FCML_I64( "vphminposuw xmm0,xmmword ptr [rax]", 0xC4, 0xE2, 0x79, 0x41, 0x00 );
    FCML_I32( "vphminposuw xmm0,xmm1", 0xC4, 0xE2, 0x79, 0x41, 0xC1 );
}

void fcml_tf_instruction_PHSUBW(void) {
    // 0F 38 05 /r1 PHSUBW mm1,mm2/m64
    // 0F 38 06 /r PHSUBD mm1,mm2/m64
    FCML_I64( "phsubw mm0,mmword ptr [rax]", 0x0F, 0x38, 0x05, 0x00 );
    FCML_I32( "phsubw mm0,mm1", 0x0F, 0x38, 0x05, 0xC1 );
    FCML_I64( "phsubd mm0,mmword ptr [rax]", 0x0F, 0x38, 0x06, 0x00 );
    FCML_I32( "phsubd mm0,mm1", 0x0F, 0x38, 0x06, 0xC1 );
    // 66 0F 38 05 /r PHSUBW xmm1,xmm2/m128
    // 66 0F 38 06 /r PHSUBD xmm1,xmm2/m128
    FCML_I64( "phsubw xmm0,xmmword ptr [rax]", 0x66, 0x0F, 0x38, 0x05, 0x00 );
    FCML_I32( "phsubw xmm0,xmm1", 0x66, 0x0F, 0x38, 0x05, 0xC1 );
    FCML_I64( "phsubd xmm0,xmmword ptr [rax]", 0x66, 0x0F, 0x38, 0x06, 0x00 );
    FCML_I32( "phsubd xmm0,xmm1", 0x66, 0x0F, 0x38, 0x06, 0xC1 );
    // VEX.NDS.128.66.0F38.WIG 05 /r VPHSUBW xmm1,xmm2,xmm3/m128
    // VEX.NDS.128.66.0F38.WIG 06 /r VPHSUBD xmm1,xmm2,xmm3/m128
    FCML_I64( "vphsubw xmm0,xmm0,xmmword ptr [rax]", 0xC4, 0xE2, 0x79, 0x05, 0x00 );
    FCML_I32( "vphsubw xmm0,xmm0,xmm1", 0xC4, 0xE2, 0x79, 0x05, 0xC1 );
    FCML_I64( "vphsubd xmm0,xmm0,xmmword ptr [rax]", 0xC4, 0xE2, 0x79, 0x06, 0x00 );
    FCML_I32( "vphsubd xmm0,xmm0,xmm1", 0xC4, 0xE2, 0x79, 0x06, 0xC1 );
    // VEX.NDS.256.66.0F38.WIG 05 /r VPHSUBW ymm1,ymm2,ymm3/m256
    // VEX.NDS.256.66.0F38.WIG 06 /r VPHSUBD ymm1,ymm2,ymm3/m256
    FCML_I64( "vphsubw ymm0,ymm0,ymmword ptr [rax]", 0xC4, 0xE2, 0x7D, 0x05, 0x00 );
    FCML_I32( "vphsubw ymm0,ymm0,ymm1", 0xC4, 0xE2, 0x7D, 0x05, 0xC1 );
    FCML_I64( "vphsubd ymm0,ymm0,ymmword ptr [rax]", 0xC4, 0xE2, 0x7D, 0x06, 0x00 );
    FCML_I32( "vphsubd ymm0,ymm0,ymm1", 0xC4, 0xE2, 0x7D, 0x06, 0xC1 );
}

void fcml_tf_instruction_PHSUBSW(void) {
    // 0F 38 07 /r1 PHSUBSW mm1,mm2/m64
    FCML_I64( "phsubsw mm0,mmword ptr [rax]", 0x0F, 0x38, 0x07, 0x00 );
    FCML_I32( "phsubsw mm0,mm1", 0x0F, 0x38, 0x07, 0xC1 );
    // 66 0F 38 07 /r PHSUBSW xmm1,xmm2/m128
    FCML_I64( "phsubsw xmm0,xmmword ptr [rax]", 0x66, 0x0F, 0x38, 0x07, 0x00 );
    FCML_I32( "phsubsw xmm0,xmm1", 0x66, 0x0F, 0x38, 0x07, 0xC1 );
    // VEX.NDS.128.66.0F38.WIG 07 /r VPHSUBSW xmm1,xmm2,xmm3/m128
    FCML_I64( "vphsubsw xmm0,xmm0,xmmword ptr [rax]", 0xC4, 0xE2, 0x79, 0x07, 0x00 );
    FCML_I32( "vphsubsw xmm0,xmm0,xmm1", 0xC4, 0xE2, 0x79, 0x07, 0xC1 );
    // VEX.NDS.256.66.0F38.WIG 07 /r VPHSUBSW ymm1,ymm2,ymm3/m256
    FCML_I64( "vphsubsw ymm0,ymm0,ymmword ptr [rax]", 0xC4, 0xE2, 0x7D, 0x07, 0x00 );
    FCML_I32( "vphsubsw ymm0,ymm0,ymm1", 0xC4, 0xE2, 0x7D, 0x07, 0xC1 );
}

void fcml_tf_instruction_PINSR(void) {
    // 66 0F 3A 20 /r ib PINSRB xmm1,r32/m8,imm8
    FCML_I64( "pinsrb xmm0,byte ptr [rax],0ffh", 0x66, 0x0F, 0x3A, 0x20, 0x00, 0xFF );
    FCML_I32( "pinsrb xmm0,ecx,0ffh", 0x66, 0x0F, 0x3A, 0x20, 0xC1, 0xFF );
    // 66 0F 3A 22 /r ib PINSRD xmm1,r/m32,imm8
    FCML_I64( "pinsrd xmm0,dword ptr [rax],0ffh", 0x66, 0x0F, 0x3A, 0x22, 0x00, 0xFF );
    FCML_I32( "pinsrd xmm0,ecx,0ffh", 0x66, 0x0F, 0x3A, 0x22, 0xC1, 0xFF );
    // 66 REX.W 0F 3A 22 /r ib PINSRQ xmm1,r/m64,imm8
    FCML_I64( "pinsrq xmm0,qword ptr [rax],0ffh", 0x66, 0x48, 0x0F, 0x3A, 0x22, 0x00, 0xFF );
    // VEX.NDS.128.66.0F3A.W0 20 /r ib VPINSRB xmm1,xmm2,r32/m8,imm8
    // VEX.NDS.128.66.0F3A.W0 22 /r ib VPINSRD xmm1,xmm2,r32/m32,imm8
    // VEX.NDS.128.66.0F3A.W1 22 /r ib VPINSRQ xmm1,xmm2,r64/m64,imm8
    FCML_I64( "vpinsrb xmm0,xmm0,byte ptr [rax],0ffh", 0xC4, 0xE3, 0x79, 0x20, 0x00, 0xFF );
    FCML_I32( "vpinsrb xmm0,xmm0,ecx,0ffh", 0xC4, 0xE3, 0x79, 0x20, 0xC1, 0xFF );
    FCML_I64( "vpinsrd xmm0,xmm0,dword ptr [rax],0ffh", 0xC4, 0xE3, 0x79, 0x22, 0x00, 0xFF );
    FCML_I32( "vpinsrd xmm0,xmm0,ecx,0ffh", 0xC4, 0xE3, 0x79, 0x22, 0xC1, 0xFF );
    FCML_I64( "vpinsrq xmm0,xmm0,qword ptr [rax],0ffh", 0xC4, 0xE3, 0xF9, 0x22, 0x00, 0xFF );
}

void fcml_tf_instruction_PINSRW(void) {
    // 0F C4 /r ib PINSRW mm,r32/m16,imm8
    FCML_I64( "pinsrw mm0,word ptr [rax],0ffh", 0x0F, 0xC4, 0x00, 0xFF );
    FCML_I32( "pinsrw mm0,ecx,0ffh", 0x0F, 0xC4, 0xC1, 0xFF );
    // 66 0F C4 /r ib PINSRW xmm,r32/m16,imm8
    FCML_I64( "pinsrw xmm0,word ptr [rax],0ffh", 0x66, 0x0F, 0xC4, 0x00, 0xFF );
    FCML_I32( "pinsrw xmm0,ecx,0ffh", 0x66, 0x0F, 0xC4, 0xC1, 0xFF );
    // VEX.NDS.128.66.0F.W0 C4 /r ib VPINSRW xmm1,xmm2,r32/m16,imm8
    FCML_I64_D( "vpinsrw xmm0,xmm0,word ptr [rax],0ffh", 0xC4, 0xE1, 0x79, 0xC4, 0x00, 0xFF );
    FCML_I64( "vpinsrw xmm0,xmm0,word ptr [rax],0ffh", 0xc5, 0xf9, 0xc4, 0x00, 0xff );
    FCML_I32_D( "vpinsrw xmm0,xmm0,ecx,0ffh", 0xC4, 0xE1, 0x79, 0xC4, 0xC1, 0xFF );
    FCML_I32( "vpinsrw xmm0,xmm0,ecx,0ffh", 0xc5, 0xf9, 0xc4, 0xc1, 0xff );
}

void fcml_tf_instruction_PMADDUBSW(void) {
    // 0F 38 04 /r PMADDUBSW mm1,mm2/m64
    FCML_I64( "pmaddubsw mm0,mmword ptr [rax]", 0x0F, 0x38, 0x04, 0x00 );
    FCML_I32( "pmaddubsw mm0,mm1", 0x0F, 0x38, 0x04, 0xC1 );
    // 66 0F 38 04 /r PMADDUBSW xmm1,xmm2/m128
    FCML_I64( "pmaddubsw xmm0,xmmword ptr [rax]", 0x66, 0x0F, 0x38, 0x04, 0x00 );
    FCML_I32( "pmaddubsw xmm0,xmm1", 0x66, 0x0F, 0x38, 0x04, 0xC1 );
    // VEX.NDS.128.66.0F38.WIG 04 /r VPMADDUBSW xmm1,xmm2,xmm3/m128
    FCML_I64( "vpmaddubsw xmm0,xmm0,xmmword ptr [rax]", 0xC4, 0xE2, 0x79, 0x04, 0x00 );
    FCML_I32( "vpmaddubsw xmm0,xmm0,xmm1", 0xC4, 0xE2, 0x79, 0x04, 0xC1 );
    // VEX.NDS.256.66.0F38.WIG 04 /r VPMADDUBSW ymm1,ymm2,ymm3/m256
    FCML_I64( "vpmaddubsw ymm0,ymm0,ymmword ptr [rax]", 0xC4, 0xE2, 0x7D, 0x04, 0x00 );
    FCML_I32( "vpmaddubsw ymm0,ymm0,ymm1", 0xC4, 0xE2, 0x7D, 0x04, 0xC1 );
}

void fcml_tf_instruction_PMADDWD(void) {
    // 0F F5 /r PMADDWD mm,mm/m64
    FCML_I64( "pmaddwd mm0,mmword ptr [rax]", 0x0F, 0xF5, 0x00 );
    FCML_I32( "pmaddwd mm0,mm1", 0x0F, 0xF5, 0xC1 );
    // 66 0F F5 /r PMADDWD xmm1,xmm2/m128
    FCML_I64( "pmaddwd xmm0,xmmword ptr [rax]", 0x66, 0x0F, 0xF5, 0x00 );
    FCML_I32( "pmaddwd xmm0,xmm1", 0x66, 0x0F, 0xF5, 0xC1 );
    // VEX.NDS.128.66.0F.WIG F5 /r VPMADDWD xmm1,xmm2,xmm3/m128
    FCML_I64( "vpmaddwd xmm0,xmm0,xmmword ptr [rax]", 0xc5, 0xf9, 0xf5, 0x00 );
    FCML_I32( "vpmaddwd xmm0,xmm0,xmm1", 0xc5, 0xf9, 0xf5, 0xc1 );
    // VEX.NDS.256.66.0F.WIG F5 /r VPMADDWD ymm1,ymm2,ymm3/m256
    FCML_I64( "vpmaddwd ymm0,ymm0,ymmword ptr [rax]", 0xc5, 0xfd, 0xf5, 0x00 );
    FCML_I32( "vpmaddwd ymm0,ymm0,ymm1", 0xc5, 0xfd, 0xf5, 0xc1 );
}

void fcml_tf_instruction_PMAXSB(void) {
    // 66 0F 38 3C /r PMAXSB xmm1,xmm2/m128
    FCML_I64( "pmaxsb xmm0,xmmword ptr [rax]", 0x66, 0x0F, 0x38, 0x3C, 0x00 );
    FCML_I32( "pmaxsb xmm0,xmm1", 0x66, 0x0F, 0x38, 0x3C, 0xC1 );
    // VEX.NDS.128.66.0F38.WIG 3C /r VPMAXSB xmm1,xmm2,xmm3/m128
    FCML_I64( "vpmaxsb xmm0,xmm0,xmmword ptr [rax]", 0xC4, 0xE2, 0x79, 0x3C, 0x00 );
    FCML_I32( "vpmaxsb xmm0,xmm0,xmm1", 0xC4, 0xE2, 0x79, 0x3C, 0xC1 );
    // VEX.NDS.256.66.0F38.WIG 3C /r VPMAXSB ymm1,ymm2,ymm3/m256
    FCML_I64( "vpmaxsb ymm0,ymm0,ymmword ptr [rax]", 0xC4, 0xE2, 0x7D, 0x3C, 0x00 );
    FCML_I32( "vpmaxsb ymm0,ymm0,ymm1", 0xC4, 0xE2, 0x7D, 0x3C, 0xC1 );
}

void fcml_tf_instruction_PMAXSD(void) {
    // 66 0F 38 3D /r PMAXSD xmm1,xmm2/m128
    FCML_I64( "pmaxsd xmm0,xmmword ptr [rax]", 0x66, 0x0F, 0x38, 0x3D, 0x00 );
    FCML_I32( "pmaxsd xmm0,xmm1", 0x66, 0x0F, 0x38, 0x3D, 0xC1 );
    // VEX.NDS.128.66.0F38.WIG 3D /r VPMAXSD xmm1,xmm2,xmm3/m128
    FCML_I64( "vpmaxsd xmm0,xmm0,xmmword ptr [rax]", 0xC4, 0xE2, 0x79, 0x3D, 0x00 );
    FCML_I32( "vpmaxsd xmm0,xmm0,xmm1", 0xC4, 0xE2, 0x79, 0x3D, 0xC1 );
    // VEX.NDS.256.66.0F38.WIG 3D /r VPMAXSD ymm1,ymm2,ymm3/m256
    FCML_I64( "vpmaxsd ymm0,ymm0,ymmword ptr [rax]", 0xC4, 0xE2, 0x7D, 0x3D, 0x00 );
    FCML_I32( "vpmaxsd ymm0,ymm0,ymm1", 0xC4, 0xE2, 0x7D, 0x3D, 0xC1 );
}

void fcml_tf_instruction_PMAXSW(void) {
    // 0F EE /r PMAXSW mm1,mm2/m64
    FCML_I64( "pmaxsw mm0,mmword ptr [rax]", 0x0F, 0xEE, 0x00 );
    FCML_I32( "pmaxsw mm0,mm1", 0x0F, 0xEE, 0xC1 );
    // 66 0F EE /r PMAXSW xmm1,xmm2/m128
    FCML_I64( "pmaxsw xmm0,xmmword ptr [rax]", 0x66, 0x0F, 0xEE, 0x00 );
    FCML_I32( "pmaxsw xmm0,xmm1", 0x66, 0x0F, 0xEE, 0xC1 );
    // VEX.NDS.128.66.0F.WIG EE /r VPMAXSW xmm1,xmm2,xmm3/m128
    FCML_I64( "vpmaxsw xmm0,xmm0,xmmword ptr [rax]", 0xc5, 0xf9, 0xee, 0x00 );
    FCML_I32( "vpmaxsw xmm0,xmm0,xmm1", 0xc5, 0xf9, 0xee, 0xc1 );
    // VEX.NDS.256.66.0F.WIG EE /r VPMAXSW ymm1,ymm2,ymm3/m256
    FCML_I64( "vpmaxsw ymm0,ymm0,ymmword ptr [rax]", 0xc5, 0xfd, 0xee, 0x00 );
    FCML_I32( "vpmaxsw ymm0,ymm0,ymm1", 0xc5, 0xfd, 0xee, 0xc1 );
}

void fcml_tf_instruction_PMAXUB(void) {
    // 0F DE /r PMAXUB mm1,mm2/m64
    FCML_I64( "pmaxub mm0,mmword ptr [rax]", 0x0F, 0xDE, 0x00 );
    FCML_I32( "pmaxub mm0,mm1", 0x0F, 0xDE, 0xC1 );
    // 66 0F DE /r PMAXUB xmm1,xmm2/m128
    FCML_I64( "pmaxub xmm0,xmmword ptr [rax]", 0x66, 0x0F, 0xDE, 0x00 );
    FCML_I32( "pmaxub xmm0,xmm1", 0x66, 0x0F, 0xDE, 0xC1 );
    // VEX.NDS.128.66.0F.WIG DE /r VPMAXUB xmm1,xmm2,xmm3/m128
    FCML_I64( "vpmaxub xmm0,xmm0,xmmword ptr [rax]", 0xc5, 0xf9, 0xde, 0x00 );
    FCML_I32( "vpmaxub xmm0,xmm0,xmm1", 0xc5, 0xf9, 0xde, 0xc1 );
    // VEX.NDS.256.66.0F.WIG DE /r VPMAXUB ymm1,ymm2,ymm3/m256
    FCML_I64( "vpmaxub ymm0,ymm0,ymmword ptr [rax]", 0xc5, 0xfd, 0xde, 0x00 );
    FCML_I32( "vpmaxub ymm0,ymm0,ymm1", 0xc5, 0xfd, 0xde, 0xc1 );
}

void fcml_tf_instruction_PMAXUD(void) {
    // 66 0F 38 3F /r PMAXUD xmm1, xmm2/m128
    FCML_I64( "pmaxud xmm0,xmmword ptr [rax]", 0x66, 0x0F, 0x38, 0x3F, 0x00 );
    FCML_I32( "pmaxud xmm0,xmm1", 0x66, 0x0F, 0x38, 0x3F, 0xC1 );
    // VEX.NDS.128.66.0F38.WIG 3F /r VPMAXUD xmm1,xmm2,xmm3/m128
    FCML_I64( "vpmaxud xmm0,xmm0,xmmword ptr [rax]", 0xC4, 0xE2, 0x79, 0x3F, 0x00 );
    FCML_I32( "vpmaxud xmm0,xmm0,xmm1", 0xC4, 0xE2, 0x79, 0x3F, 0xC1 );
    // VEX.NDS.256.66.0F38.WIG 3F /r VPMAXUD ymm1,ymm2,ymm3/m256
    FCML_I64( "vpmaxud ymm0,ymm0,ymmword ptr [rax]", 0xC4, 0xE2, 0x7D, 0x3F, 0x00 );
    FCML_I32( "vpmaxud ymm0,ymm0,ymm1", 0xC4, 0xE2, 0x7D, 0x3F, 0xC1 );
}

void fcml_tf_instruction_PMAXUW(void) {
    // 66 0F 38 3E /r PMAXUW xmm1,xmm2/m128
    FCML_I64( "pmaxuw xmm0,xmmword ptr [rax]", 0x66, 0x0F, 0x38, 0x3E, 0x00 );
    FCML_I32( "pmaxuw xmm0,xmm1", 0x66, 0x0F, 0x38, 0x3E, 0xC1 );
    // VEX.NDS.128.66.0F38.WIG 3E/r VPMAXUW xmm1,xmm2,xmm3/m128
    FCML_I64( "vpmaxuw xmm0,xmm0,xmmword ptr [rax]", 0xC4, 0xE2, 0x79, 0x3E, 0x00 );
    FCML_I32( "vpmaxuw xmm0,xmm0,xmm1", 0xC4, 0xE2, 0x79, 0x3E, 0xC1 );
    // VEX.NDS.256.66.0F38.WIG 3E /r VPMAXUW ymm1,ymm2,ymm3/m256
    FCML_I64( "vpmaxuw ymm0,ymm0,ymmword ptr [rax]", 0xC4, 0xE2, 0x7D, 0x3E, 0x00 );
    FCML_I32( "vpmaxuw ymm0,ymm0,ymm1", 0xC4, 0xE2, 0x7D, 0x3E, 0xC1 );
}

void fcml_tf_instruction_PMINSB(void) {
    // 66 0F 38 38 /r PMINSB xmm1,xmm2/m128
    FCML_I64( "pminsb xmm0,xmmword ptr [rax]", 0x66, 0x0F, 0x38, 0x38, 0x00 );
    FCML_I32( "pminsb xmm0,xmm1", 0x66, 0x0F, 0x38, 0x38, 0xC1 );
    // VEX.NDS.128.66.0F38.WIG 38 /r VPMINSB xmm1,xmm2,xmm3/m128
    FCML_I64( "vpminsb xmm0,xmm0,xmmword ptr [rax]", 0xC4, 0xE2, 0x79, 0x38, 0x00 );
    FCML_I32( "vpminsb xmm0,xmm0,xmm1", 0xC4, 0xE2, 0x79, 0x38, 0xC1 );
    // VEX.NDS.256.66.0F38.WIG 38 /r VPMINSB ymm1,ymm2,ymm3/m256
    FCML_I64( "vpminsb ymm0,ymm0,ymmword ptr [rax]", 0xC4, 0xE2, 0x7D, 0x38, 0x00 );
    FCML_I32( "vpminsb ymm0,ymm0,ymm1", 0xC4, 0xE2, 0x7D, 0x38, 0xC1 );
}

void fcml_tf_instruction_PMINSD(void) {
    // 66 0F 38 39 /r PMINSD xmm1, xmm2/m128
    FCML_I64( "pminsd xmm0,xmmword ptr [rax]", 0x66, 0x0F, 0x38, 0x39, 0x00 );
    FCML_I32( "pminsd xmm0,xmm1", 0x66, 0x0F, 0x38, 0x39, 0xC1 );
    // VEX.NDS.128.66.0F38.WIG 39 /r VPMINSD xmm1, xmm2, xmm3/m128
    FCML_I64( "vpminsd xmm0,xmm0,xmmword ptr [rax]", 0xC4, 0xE2, 0x79, 0x39, 0x00 );
    FCML_I32( "vpminsd xmm0,xmm0,xmm1", 0xC4, 0xE2, 0x79, 0x39, 0xC1 );
    // VEX.NDS.256.66.0F38.WIG 39 /r VPMINSD ymm1,ymm2,ymm3/m256
    FCML_I64( "vpminsd ymm0,ymm0,ymmword ptr [rax]", 0xC4, 0xE2, 0x7D, 0x39, 0x00 );
    FCML_I32( "vpminsd ymm0,ymm0,ymm1", 0xC4, 0xE2, 0x7D, 0x39, 0xC1 );
}

void fcml_tf_instruction_PMINSW(void) {
    // 0F EA /r PMINSW mm1,mm2/m64
    FCML_I64( "pminsw mm0,mmword ptr [rax]", 0x0F, 0xEA, 0x00 );
    FCML_I32( "pminsw mm0,mm1", 0x0F, 0xEA, 0xC1 );
    // 66 0F EA /r PMINSW xmm1,xmm2/m128
    FCML_I64( "pminsw xmm0,xmmword ptr [rax]", 0x66, 0x0F, 0xEA, 0x00 );
    FCML_I32( "pminsw xmm0,xmm1", 0x66, 0x0F, 0xEA, 0xC1 );
    // VEX.NDS.128.66.0F.WIG EA /r VPMINSW xmm1,xmm2,xmm3/m128
    FCML_I64( "vpminsw xmm0,xmm0,xmmword ptr [rax]", 0xc5, 0xf9, 0xea, 0x00 );
    FCML_I32( "vpminsw xmm0,xmm0,xmm1", 0xc5, 0xf9, 0xea, 0xc1 );
    // VEX.NDS.256.66.0F.WIG EA /r VPMINSW ymm1,ymm2,ymm3/m256
    FCML_I64( "vpminsw ymm0,ymm0,ymmword ptr [rax]", 0xc5, 0xfd, 0xea, 0x00 );
    FCML_I32( "vpminsw ymm0,ymm0,ymm1", 0xc5, 0xfd, 0xea, 0xc1 );
}

void fcml_tf_instruction_PMINUB(void) {
    // 0F DA /r PMINUB mm1,mm2/m64
    FCML_I64( "pminub mm0,mmword ptr [rax]", 0x0F, 0xDA, 0x00 );
    FCML_I32( "pminub mm0,mm1", 0x0F, 0xDA, 0xC1 );
    // 66 0F DA /r PMINUB xmm1,xmm2/m128
    FCML_I64( "pminub xmm0,xmmword ptr [rax]", 0x66, 0x0F, 0xDA, 0x00 );
    FCML_I32( "pminub xmm0,xmm1", 0x66, 0x0F, 0xDA, 0xC1 );
    // VEX.NDS.128.66.0F.WIG DA /r VPMINUB xmm1,xmm2,xmm3/m128
    FCML_I64( "vpminub xmm0,xmm0,xmmword ptr [rax]", 0xc5, 0xf9, 0xda, 0x00 );
    FCML_I32( "vpminub xmm0,xmm0,xmm1", 0xc5, 0xf9, 0xda, 0xc1 );
    // VEX.NDS.256.66.0F.WIG DA /r VPMINUB ymm1,ymm2,ymm3/m256
    FCML_I64( "vpminub ymm0,ymm0,ymmword ptr [rax]", 0xc5, 0xfd, 0xda, 0x00 );
    FCML_I32( "vpminub ymm0,ymm0,ymm1", 0xc5, 0xfd, 0xda, 0xc1 );
}

void fcml_tf_instruction_PMINUW(void) {
    // 66 0F 38 3A /r PMINUW xmm1,xmm2/m128
    FCML_I64( "pminuw xmm0,xmmword ptr [rax]", 0x66, 0x0F, 0x38, 0x3A, 0x00 );
    FCML_I32( "pminuw xmm0,xmm1", 0x66, 0x0F, 0x38, 0x3A, 0xC1 );
    // VEX.NDS.128.66.0F38.WIG 3A /r VPMINUW xmm1,xmm2,xmm3/m128
    FCML_I64( "vpminuw xmm0,xmm0,xmmword ptr [rax]", 0xC4, 0xE2, 0x79, 0x3A, 0x00 );
    FCML_I32( "vpminuw xmm0,xmm0,xmm1", 0xC4, 0xE2, 0x79, 0x3A, 0xC1 );
    // VEX.NDS.256.66.0F38.WIG 3A /r VPMINUW ymm1,ymm2,ymm3/m256
    FCML_I64( "vpminuw ymm0,ymm0,ymmword ptr [rax]", 0xC4, 0xE2, 0x7D, 0x3A, 0x00 );
    FCML_I32( "vpminuw ymm0,ymm0,ymm1", 0xC4, 0xE2, 0x7D, 0x3A, 0xC1 );
}

void fcml_tf_instruction_PMINUD(void) {
    // 66 0F 38 3B /r PMINUD xmm1,xmm2/m128
    FCML_I64( "pminud xmm0,xmmword ptr [rax]", 0x66, 0x0F, 0x38, 0x3B, 0x00 );
    FCML_I32( "pminud xmm0,xmm1", 0x66, 0x0F, 0x38, 0x3B, 0xC1 );
    // VEX.NDS.128.66.0F38.WIG 3B /r VPMINUD xmm1,xmm2,xmm3/m128
    FCML_I64( "vpminud xmm0,xmm0,xmmword ptr [rax]", 0xC4, 0xE2, 0x79, 0x3B, 0x00 );
    FCML_I32( "vpminud xmm0,xmm0,xmm1", 0xC4, 0xE2, 0x79, 0x3B, 0xC1 );
    // VEX.NDS.256.66.0F38.WIG 3B /r VPMINUD ymm1,ymm2,ymm3/m256
    FCML_I64( "vpminud ymm0,ymm0,ymmword ptr [rax]", 0xC4, 0xE2, 0x7D, 0x3B, 0x00 );
    FCML_I32( "vpminud ymm0,ymm0,ymm1", 0xC4, 0xE2, 0x7D, 0x3B, 0xC1 );
}

void fcml_tf_instruction_PMOVMSKB(void) {
    // 0F D7 /r PMOVMSKB reg,mm
    FCML_I32( "pmovmskb eax,mm1", 0x0F, 0xD7, 0xC1 );
    FCML_I64( "pmovmskb rax,mm1", 0x0F, 0xD7, 0xC1 );
    // 66 0F D7 /r PMOVMSKB reg,xmm
    FCML_I32( "pmovmskb eax,xmm1", 0x66, 0x0F, 0xD7, 0xC1 );
    FCML_I64( "pmovmskb rax,xmm1", 0x66, 0x0F, 0xD7, 0xC1 );
    // VEX.128.66.0F.WIG D7 /r VPMOVMSKB reg,xmm1
    FCML_I32( "vpmovmskb eax,xmm0", 0xc5, 0xf9, 0xd7, 0xc0 );
    FCML_I64( "vpmovmskb rcx,xmm0", 0xc5, 0xf9, 0xd7, 0xc8 );
    // VEX.256.66.0F.WIG D7 /r VPMOVMSKB reg,ymm1
    FCML_I32( "vpmovmskb ecx,ymm0", 0xc5, 0xfd, 0xd7, 0xc8 );
    FCML_I64( "vpmovmskb rax,ymm0", 0xc5, 0xfd, 0xd7, 0xc0 );
}

void fcml_tf_instruction_PMOVSX(void) {
    // 66 0f 38 20 /r PMOVSXBW xmm1,xmm2/m64
    FCML_I64( "pmovsxbw xmm0,mmword ptr [rax]", 0x66, 0x0F, 0x38, 0x20, 0x00 );
    FCML_I32( "pmovsxbw xmm0,xmm1", 0x66, 0x0F, 0x38, 0x20, 0xC1 );
    // 66 0f 38 21 /r PMOVSXBD xmm1,xmm2/m32
    FCML_I64( "pmovsxbd xmm0,dword ptr [rax]", 0x66, 0x0F, 0x38, 0x21, 0x00 );
    FCML_I32( "pmovsxbd xmm0,xmm1", 0x66, 0x0F, 0x38, 0x21, 0xC1 );
    // 66 0f 38 22 /r PMOVSXBQ xmm1,xmm2/m16
    FCML_I64( "pmovsxbq xmm0,word ptr [rax]", 0x66, 0x0F, 0x38, 0x22, 0x00 );
    FCML_I32( "pmovsxbq xmm0,xmm1", 0x66, 0x0F, 0x38, 0x22, 0xC1 );
    // 66 0f 38 23 /r PMOVSXWD xmm1,xmm2/m64
    FCML_I64( "pmovsxwd xmm0,mmword ptr [rax]", 0x66, 0x0F, 0x38, 0x23, 0x00 );
    FCML_I32( "pmovsxwd xmm0,xmm1", 0x66, 0x0F, 0x38, 0x23, 0xC1 );
    // 66 0f 38 24 /r PMOVSXWQ xmm1,xmm2/m32
    FCML_I64( "pmovsxwq xmm0,dword ptr [rax]", 0x66, 0x0F, 0x38, 0x24, 0x00 );
    FCML_I32( "pmovsxwq xmm0,xmm1", 0x66, 0x0F, 0x38, 0x24, 0xC1 );
    // 66 0f 38 25 /r PMOVSXDQ xmm1,xmm2/m64
    FCML_I64( "pmovsxdq xmm0,mmword ptr [rax]", 0x66, 0x0F, 0x38, 0x25, 0x00 );
    FCML_I32( "pmovsxdq xmm0,xmm1", 0x66, 0x0F, 0x38, 0x25, 0xC1 );
    // VEX.128.66.0F38.WIG 20 /r VPMOVSXBW xmm1,xmm2/m64
    FCML_I32( "vpmovsxbw xmm0,mmword ptr [eax]", 0xC4, 0xE2, 0x79, 0x20, 0x00 );
    FCML_I64( "vpmovsxbw xmm0,xmm1", 0xC4, 0xE2, 0x79, 0x20, 0xC1 );
    // VEX.128.66.0F38.WIG 21 /r VPMOVSXBD xmm1,xmm2/m32
    FCML_I32( "vpmovsxbd xmm0,dword ptr [eax]", 0xC4, 0xE2, 0x79, 0x21, 0x00 );
    FCML_I64( "vpmovsxbd xmm0,xmm1", 0xC4, 0xE2, 0x79, 0x21, 0xC1 );
    // VEX.128.66.0F38.WIG 22 /r VPMOVSXBQ xmm1,xmm2/m16
    FCML_I32( "vpmovsxbq xmm0,word ptr [eax]", 0xC4, 0xE2, 0x79, 0x22, 0x00 );
    FCML_I64( "vpmovsxbq xmm0,xmm1", 0xC4, 0xE2, 0x79, 0x22, 0xC1 );
    // VEX.128.66.0F38.WIG 23 /r VPMOVSXWD xmm1,xmm2/m64
    FCML_I32( "vpmovsxwd xmm0,mmword ptr [eax]", 0xC4, 0xE2, 0x79, 0x23, 0x00 );
    FCML_I64( "vpmovsxwd xmm0,xmm1", 0xC4, 0xE2, 0x79, 0x23, 0xC1 );
    // VEX.128.66.0F38.WIG 24 /r VPMOVSXWQ xmm1,xmm2/m32
    FCML_I32( "vpmovsxwq xmm0,dword ptr [eax]", 0xC4, 0xE2, 0x79, 0x24, 0x00 );
    FCML_I64( "vpmovsxwq xmm0,xmm1", 0xC4, 0xE2, 0x79, 0x24, 0xC1 );
    // VEX.128.66.0F38.WIG 25 /r VPMOVSXDQ xmm1,xmm2/m64
    FCML_I32( "vpmovsxdq xmm0,mmword ptr [eax]", 0xC4, 0xE2, 0x79, 0x25, 0x00 );
    FCML_I64( "vpmovsxdq xmm0,xmm1", 0xC4, 0xE2, 0x79, 0x25, 0xC1 );
    // VEX.256.66.0F38.WIG 20 /r VPMOVSXBW ymm1,xmm2/m128
    FCML_I32( "vpmovsxbw ymm0,xmmword ptr [eax]", 0xC4, 0xE2, 0x7D, 0x20, 0x00 );
    FCML_I64( "vpmovsxbw ymm0,xmm1", 0xC4, 0xE2, 0x7D, 0x20, 0xC1 );
    // VEX.256.66.0F38.WIG 21 /r VPMOVSXBD ymm1,xmm2/m64
    FCML_I32( "vpmovsxbd ymm0,mmword ptr [eax]", 0xC4, 0xE2, 0x7D, 0x21, 0x00 );
    FCML_I64( "vpmovsxbd ymm0,xmm1", 0xC4, 0xE2, 0x7D, 0x21, 0xC1 );
    // VEX.256.66.0F38.WIG 22 /r VPMOVSXBQ ymm1,xmm2/m32
    FCML_I32( "vpmovsxbq ymm0,dword ptr [eax]", 0xC4, 0xE2, 0x7D, 0x22, 0x00 );
    FCML_I64( "vpmovsxbq ymm0,xmm1", 0xC4, 0xE2, 0x7D, 0x22, 0xC1 );
}

void fcml_tf_instruction_PMOVZX(void) {
    // 66 0f 38 30 /r PMOVZXBW xmm1, xmm2/m64
    FCML_I64( "pmovzxbw xmm0,mmword ptr [rax]", 0x66, 0x0F, 0x38, 0x30, 0x00 );
    FCML_I32( "pmovzxbw xmm0,xmm1", 0x66, 0x0F, 0x38, 0x30, 0xC1 );
    // 66 0f 38 31 /r PMOVZXBD xmm1, xmm2/m32
    FCML_I64( "pmovzxbd xmm0,dword ptr [rax]", 0x66, 0x0F, 0x38, 0x31, 0x00 );
    FCML_I32( "pmovzxbd xmm0,xmm1", 0x66, 0x0F, 0x38, 0x31, 0xC1 );
    // 66 0f 38 32 /r PMOVZXBQ xmm1, xmm2/m16
    FCML_I64( "pmovzxbq xmm0,word ptr [rax]", 0x66, 0x0F, 0x38, 0x32, 0x00 );
    FCML_I32( "pmovzxbq xmm0,xmm1", 0x66, 0x0F, 0x38, 0x32, 0xC1 );
    // 66 0f 38 33 /r PMOVZXWD xmm1, xmm2/m64
    FCML_I64( "pmovzxwd xmm0,mmword ptr [rax]", 0x66, 0x0F, 0x38, 0x33, 0x00 );
    FCML_I32( "pmovzxwd xmm0,xmm1", 0x66, 0x0F, 0x38, 0x33, 0xC1 );
    // 66 0f 38 34 /r PMOVZXWQ xmm1, xmm2/m32
    FCML_I64( "pmovzxwq xmm0,dword ptr [rax]", 0x66, 0x0F, 0x38, 0x34, 0x00 );
    FCML_I32( "pmovzxwq xmm0,xmm1", 0x66, 0x0F, 0x38, 0x34, 0xC1 );
    // 66 0f 38 35 /r PMOVZXDQ xmm1, xmm2/m64
    FCML_I64( "pmovzxdq xmm0,mmword ptr [rax]", 0x66, 0x0F, 0x38, 0x35, 0x00 );
    FCML_I32( "pmovzxdq xmm0,xmm1", 0x66, 0x0F, 0x38, 0x35, 0xC1 );
    // VEX.128.66.0F38.WIG 30 /r VPMOVZXBW xmm1, xmm2/m64
    FCML_I32( "vpmovzxbw xmm0,mmword ptr [eax]", 0xC4, 0xE2, 0x79, 0x30, 0x00 );
    FCML_I64( "vpmovzxbw xmm0,xmm1", 0xC4, 0xE2, 0x79, 0x30, 0xC1 );
    // VEX.128.66.0F38.WIG 31 /r VPMOVZXBD xmm1, xmm2/m32
    FCML_I32( "vpmovzxbd xmm0,dword ptr [eax]", 0xC4, 0xE2, 0x79, 0x31, 0x00 );
    FCML_I64( "vpmovzxbd xmm0,xmm1", 0xC4, 0xE2, 0x79, 0x31, 0xC1 );
    // VEX.128.66.0F38.WIG 32 /r VPMOVZXBQ xmm1, xmm2/m16
    FCML_I32( "vpmovzxbq xmm0,word ptr [eax]", 0xC4, 0xE2, 0x79, 0x32, 0x00 );
    FCML_I64( "vpmovzxbq xmm0,xmm1", 0xC4, 0xE2, 0x79, 0x32, 0xC1 );
    // VEX.128.66.0F38.WIG 33 /r VPMOVZXWD xmm1, xmm2/m64
    FCML_I32( "vpmovzxwd xmm0,mmword ptr [eax]", 0xC4, 0xE2, 0x79, 0x33, 0x00 );
    FCML_I64( "vpmovzxwd xmm0,xmm1", 0xC4, 0xE2, 0x79, 0x33, 0xC1 );
    // VEX.128.66.0F38.WIG 34 /r VPMOVZXWQ xmm1, xmm2/m32
    FCML_I32( "vpmovzxwq xmm0,dword ptr [eax]", 0xC4, 0xE2, 0x79, 0x34, 0x00 );
    FCML_I64( "vpmovzxwq xmm0,xmm1", 0xC4, 0xE2, 0x79, 0x34, 0xC1 );
    // VEX.128.66.0F38.WIG 35 /r VPMOVZXDQ xmm1, xmm2/m64
    FCML_I32( "vpmovzxdq xmm0,mmword ptr [eax]", 0xC4, 0xE2, 0x79, 0x35, 0x00 );
    FCML_I64( "vpmovzxdq xmm0,xmm1", 0xC4, 0xE2, 0x79, 0x35, 0xC1 );
    // VEX.256.66.0F38.WIG 30 /r VPMOVZXBW ymm1,xmm2/m128
    FCML_I32( "vpmovzxbw ymm0,xmmword ptr [eax]", 0xC4, 0xE2, 0x7D, 0x30, 0x00 );
    FCML_I64( "vpmovzxbw ymm0,xmm1", 0xC4, 0xE2, 0x7D, 0x30, 0xC1 );
    // VEX.256.66.0F38.WIG 31 /r VPMOVZXBD ymm1,xmm2/m64
    FCML_I32( "vpmovzxbd ymm0,mmword ptr [eax]", 0xC4, 0xE2, 0x7D, 0x31, 0x00 );
    FCML_I64( "vpmovzxbd ymm0,xmm1", 0xC4, 0xE2, 0x7D, 0x31, 0xC1 );
    // VEX.256.66.0F38.WIG 32 /r VPMOVZXBQ ymm1,xmm2/m32
    FCML_I32( "vpmovzxbq ymm0,dword ptr [eax]", 0xC4, 0xE2, 0x7D, 0x32, 0x00 );
    FCML_I64( "vpmovzxbq ymm0,xmm1", 0xC4, 0xE2, 0x7D, 0x32, 0xC1 );
    // VEX.256.66.0F38.WIG 33 /r VPMOVZXWD ymm1,xmm2/m128
    FCML_I32( "vpmovzxwd ymm0,xmmword ptr [eax]", 0xC4, 0xE2, 0x7D, 0x33, 0x00 );
    FCML_I64( "vpmovzxwd ymm0,xmm1", 0xC4, 0xE2, 0x7D, 0x33, 0xC1 );
}

void fcml_tf_instruction_PMULDQ(void) {
    // 66 0F 38 28 /r PMULDQ xmm1,xmm2/m128
    FCML_I64( "pmuldq xmm0,xmmword ptr [rax]", 0x66, 0x0F, 0x38, 0x28, 0x00 );
    FCML_I32( "pmuldq xmm0,xmm1", 0x66, 0x0F, 0x38, 0x28, 0xC1 );
    // VEX.NDS.128.66.0F38.WIG 28 /r VPMULDQ xmm1,xmm2,xmm3/m128
    FCML_I64( "vpmuldq xmm0,xmm0,xmmword ptr [rax]", 0xC4, 0xE2, 0x79, 0x28, 0x00 );
    FCML_I32( "vpmuldq xmm0,xmm0,xmm1", 0xC4, 0xE2, 0x79, 0x28, 0xC1 );
    // VEX.NDS.256.66.0F38.WIG 28 /r VPMULDQ ymm1,ymm2,ymm3/m256
    FCML_I64( "vpmuldq ymm0,ymm0,ymmword ptr [rax]", 0xC4, 0xE2, 0x7D, 0x28, 0x00 );
    FCML_I32( "vpmuldq ymm0,ymm0,ymm1", 0xC4, 0xE2, 0x7D, 0x28, 0xC1 );
}

void fcml_tf_instruction_PMULHRSW(void) {
    // 0F 38 0B /r1 PMULHRSW mm1,mm2/m64
    FCML_I64( "pmulhrsw mm0,mmword ptr [rax]", 0x0F, 0x38, 0x0B, 0x00 );
    FCML_I32( "pmulhrsw mm0,mm1", 0x0F, 0x38, 0x0B, 0xC1 );
    // 66 0F 38 0B /r PMULHRSW xmm1,xmm2/m128
    FCML_I64( "pmulhrsw xmm0,xmmword ptr [rax]", 0x66, 0x0F, 0x38, 0x0B, 0x00 );
    FCML_I32( "pmulhrsw xmm0,xmm1", 0x66, 0x0F, 0x38, 0x0B, 0xC1 );
    // VEX.NDS.128.66.0F38.WIG 0B /r VPMULHRSW xmm1,xmm2,xmm3/m128
    FCML_I64( "vpmulhrsw xmm0,xmm0,xmmword ptr [rax]", 0xC4, 0xE2, 0x79, 0x0B, 0x00 );
    FCML_I32( "vpmulhrsw xmm0,xmm0,xmm1", 0xC4, 0xE2, 0x79, 0x0B, 0xC1 );
    // VEX.NDS.256.66.0F38.WIG 0B /r VPMULHRSW ymm1,ymm2,ymm3/m256
    FCML_I64( "vpmulhrsw ymm0,ymm0,ymmword ptr [rax]", 0xC4, 0xE2, 0x7D, 0x0B, 0x00 );
    FCML_I32( "vpmulhrsw ymm0,ymm0,ymm1", 0xC4, 0xE2, 0x7D, 0x0B, 0xC1 );
}

void fcml_tf_instruction_PMULHUW(void) {
    // 0F E4 /r PMULHUW mm1,mm2/m64
    FCML_I64( "pmulhuw mm0,mmword ptr [rax]", 0x0F, 0xE4, 0x00 );
    FCML_I32( "pmulhuw mm0,mm1", 0x0F, 0xE4, 0xC1 );
    // 66 0F E4 /r PMULHUW xmm1,xmm2/m128
    FCML_I64( "pmulhuw xmm0,xmmword ptr [rax]", 0x66, 0x0F, 0xE4, 0x00 );
    FCML_I32( "pmulhuw xmm0,xmm1", 0x66, 0x0F, 0xE4, 0xC1 );
    // VEX.NDS.128.66.0F.WIG E4 /r VPMULHUW xmm1,xmm2,xmm3/m128
    FCML_I64( "vpmulhuw xmm1,xmm0,xmmword ptr [rax]", 0xc5, 0xf9, 0xe4, 0x08 );
    FCML_I32( "vpmulhuw xmm0,xmm0,xmm1", 0xc5, 0xf9, 0xe4, 0xc1 );
    // VEX.NDS.256.66.0F.WIG E4 /r VPMULHUW ymm1,ymm2,ymm3/m256
    FCML_I64( "vpmulhuw ymm0,ymm0,ymmword ptr [rax]", 0xc5, 0xfd, 0xe4, 0x00 );
    FCML_I32( "vpmulhuw ymm0,ymm0,ymm1", 0xc5, 0xfd, 0xe4, 0xc1 );
}

void fcml_tf_instruction_PMULHW(void) {
    // 0F E5 /r PMULHW mm,mm/m64
    FCML_I64( "pmulhw mm0,mmword ptr [rax]", 0x0F, 0xE5, 0x00 );
    FCML_I32( "pmulhw mm0,mm1", 0x0F, 0xE5, 0xC1 );
    // 66 0F E5 /r PMULHW xmm1,xmm2/m128
    FCML_I64( "pmulhw xmm0,xmmword ptr [rax]", 0x66, 0x0F, 0xE5, 0x00 );
    FCML_I32( "pmulhw xmm0,xmm1", 0x66, 0x0F, 0xE5, 0xC1 );
    // VEX.NDS.128.66.0F.WIG E5 /r VPMULHW xmm1,xmm2,xmm3/m128
    FCML_I64( "vpmulhw xmm0,xmm0,xmmword ptr [rax]", 0xc5, 0xf9, 0xe5, 0x00 );
    FCML_I32( "vpmulhw xmm0,xmm0,xmm1", 0xc5, 0xf9, 0xe5, 0xc1 );
    // VEX.NDS.256.66.0F.WIG E5 /r VPMULHW ymm1,ymm2,ymm3/m256
    FCML_I64( "vpmulhw ymm0,ymm13,ymmword ptr [rax]", 0xc5, 0x95, 0xe5, 0x00 );
    FCML_I32( "vpmulhw ymm0,ymm0,ymm1", 0xc5, 0xfd, 0xe5, 0xc1 );
}

void fcml_tf_instruction_PMULUDQ(void) {
    // 0F F4 /r1 PMULUDQ mm1,mm2/m64
    FCML_I64( "pmuludq mm0,mmword ptr [rax]", 0x0F, 0xF4, 0x00 );
    FCML_I32( "pmuludq mm0,mm1", 0x0F, 0xF4, 0xC1 );
    // 66 0F F4 /r PMULUDQ xmm1,xmm2/m128
    FCML_I64( "pmuludq xmm0,xmmword ptr [rax]", 0x66, 0x0F, 0xF4, 0x00 );
    FCML_I32( "pmuludq xmm0,xmm1", 0x66, 0x0F, 0xF4, 0xC1 );
    // VEX.NDS.128.66.0F.WIG F4 /r VPMULUDQ xmm1,xmm2,xmm3/m128
    FCML_I64( "vpmuludq ymm8,ymm13,ymmword ptr [rax]", 0xc5, 0x15, 0xf4, 0x00 );
    FCML_I32( "vpmuludq xmm0,xmm0,xmm1", 0xc5, 0xf9, 0xf4, 0xc1 );
    // VEX.NDS.256.66.0F.WIG F4 /r VPMULUDQ ymm1,ymm2,ymm3/m256
    FCML_I64( "vpmuludq ymm0,ymm0,ymmword ptr [rax]", 0xc5, 0xfd, 0xf4, 0x00 );
    FCML_I32( "vpmuludq ymm0,ymm0,ymm1", 0xc5, 0xfd, 0xf4, 0xc1 );
}

void fcml_tf_instruction_PMULLW(void) {
    // 0F D5 /r PMULLW mm,mm/m64
    FCML_I64( "pmullw mm0,mmword ptr [rax]", 0x0F, 0xD5, 0x00 );
    FCML_I32( "pmullw mm0,mm1", 0x0F, 0xD5, 0xC1 );
    // 66 0F D5 /r PMULLW xmm1,xmm2/m128
    FCML_I64( "pmullw xmm0,xmmword ptr [rax]", 0x66, 0x0F, 0xD5, 0x00 );
    FCML_I32( "pmullw xmm0,xmm1", 0x66, 0x0F, 0xD5, 0xC1 );
    // VEX.NDS.128.66.0F.WIG D5 /r VPMULLW xmm1,xmm2,xmm3/m128
    FCML_I64( "vpmullw xmm0,xmm0,xmmword ptr [rax]", 0xc5, 0xf9, 0xd5, 0x00 );
    FCML_I32( "vpmullw xmm0,xmm0,xmm1", 0xc5, 0xf9, 0xd5, 0xc1 );
    // VEX.NDS.256.66.0F.WIG D5 /r VPMULLW ymm1,ymm2,ymm3/m256
    FCML_I64( "vpmullw ymm0,ymm0,ymmword ptr [rax]", 0xc5, 0xfd, 0xd5, 0x00 );
    FCML_I32( "vpmullw ymm0,ymm0,ymm1", 0xc5, 0xfd, 0xd5, 0xc1 );
}

void fcml_tf_instruction_PMULLD(void) {
    // 66 0F 38 40 /r PMULLD xmm1,xmm2/m128
    FCML_I64( "pmulld xmm0,xmmword ptr [rax]", 0x66, 0x0F, 0x38, 0x40, 0x00 );
    FCML_I32( "pmulld xmm0,xmm1", 0x66, 0x0F, 0x38, 0x40, 0xC1 );
    // VEX.NDS.128.66.0F38.WIG 40 /r VPMULLD xmm1,xmm2,xmm3/m128
    FCML_I64( "vpmulld xmm0,xmm0,xmmword ptr [rax]", 0xC4, 0xE2, 0x79, 0x40, 0x00 );
    FCML_I32( "vpmulld xmm0,xmm0,xmm1", 0xC4, 0xE2, 0x79, 0x40, 0xC1 );
    // VEX.NDS.256.66.0F38.WIG 40 /r VPMULLD ymm1,ymm2,ymm3/m256
    FCML_I64( "vpmulld ymm0,ymm0,ymmword ptr [rax]", 0xC4, 0xE2, 0x7D, 0x40, 0x00 );
    FCML_I32( "vpmulld ymm0,ymm0,ymm1", 0xC4, 0xE2, 0x7D, 0x40, 0xC1 );
}

void fcml_tf_instruction_POP(void) {
    // 8F /0 POP r/m16 M Valid Valid Pop top of stack into m16; increment stack pointer.
    // 8F /0 POP r/m32 M N.E. Valid Pop top of stack into m32; increment stack pointer.
    // 8F /0 POP r/m64 M Valid N.E. Pop top of stack into m64; increment stack pointer. Cannot encode 32-bit operand size.
    // 32 BIT.
    FCML_I32( "pop dword ptr [eax]", 0x8F, 0x00 );
    FCML_I32_M( "pop eax", 2, FCML_MI( 0x58 ), FCML_MI( 0x8f, 0xc0 ) );
    FCML_I32( "pop word ptr [eax]", 0x66, 0x8F, 0x00 );
    FCML_I32_M( "pop dx", 2, FCML_MI( 0x66, 0x5a ), FCML_MI( 0x66, 0x8f, 0xc2 ) );
    FCML_I32( "pop dword ptr [bx+si]", 0x67, 0x8F, 0x00 );
    FCML_I32_D( "pop ecx", 0x67, 0x8F, 0xC1 );
    FCML_I32_M( "pop ecx", 2, FCML_MI( 0x59 ), FCML_MI( 0x8f, 0xc1 ) );
    FCML_I32( "pop word ptr [bx+si]", 0x66, 0x67, 0x8F, 0x00 );
    FCML_I32_M( "pop cx", 2, FCML_MI( 0x66, 0x59 ), FCML_MI( 0x66, 0x8f, 0xc1 ) );
    // 64 BIT.
    FCML_I64( "pop qword ptr [rax]", 0x8F, 0x00 );
    FCML_I64_M( "pop rcx", 2, FCML_MI( 0x59 ), FCML_MI( 0x8f, 0xc1 ) );
    FCML_I64( "pop word ptr [rax]", 0x66, 0x8F, 0x00 );
    FCML_I64_M( "pop cx", 2, FCML_MI( 0x66, 0x59 ), FCML_MI( 0x66, 0x8f, 0xc1 ) );
    FCML_I64( "pop qword ptr [eax]", 0x67, 0x8F, 0x00 );
    FCML_I64_D( "pop rcx", 0x67, 0x8F, 0xC1 );
    FCML_I64( "pop word ptr [eax]", 0x66, 0x67, 0x8F, 0x00 );
    FCML_I64_D( "pop cx", 0x66, 0x67, 0x8F, 0xC1 );
    FCML_I64_D( "pop qword ptr [rax]", 0x48, 0x8F, 0x00 );
    FCML_I64_D( "pop rcx", 0x48, 0x8F, 0xC1 );
    // 58+ rw POP r16 O Valid Valid Pop top of stack into r16; increment stack pointer.
    // 58+ rd POP r32 O N.E. Valid Pop top of stack into r32; increment stack pointer.
    // 58+ rd POP r64 O Valid N.E. Pop top of stack into r64; increment stack pointer. Cannot encode 32-bit operand size.
    FCML_I32_M( "pop eax", 2, FCML_MI( 0x58 ), FCML_MI( 0x8f, 0xc0 ) );
    FCML_I32_M( "pop ax", 2, FCML_MI( 0x66, 0x58 ), FCML_MI( 0x66, 0x8f, 0xc0 ) );
    FCML_I32_D( "pop eax", 0x67, 0x58 );
    FCML_I64_M( "pop rax", 2, FCML_MI( 0x58 ), FCML_MI( 0x8f, 0xc0 ) );
    FCML_I64_M( "pop ax", 2, FCML_MI( 0x66, 0x58 ), FCML_MI( 0x66, 0x8f, 0xc0 ) );
    FCML_I64_D( "pop rax", 0x67, 0x58 );
    FCML_I64_D( "pop rax", 0x48, 0x58 );
    // 1F POP DS NP Invalid Valid Pop top of stack into DS; increment stack pointer.
    // 07 POP ES NP Invalid Valid Pop top of stack into ES; increment stack pointer.
    // 17 POP SS NP Invalid Valid Pop top of stack into SS; increment stack pointer.
    FCML_I32( "pop ds", 0x1F );
    FCML_I32( "pop es", 0x07 );
    FCML_I32( "pop ss", 0x17 );
    // 0F A1 POP FS NP Valid Valid Pop top of stack into FS; increment stack pointer by 16 bits.
    // 0F A1 POP FS NP N.E. Valid Pop top of stack into FS; increment stack pointer by 32 bits.
    // 0F A1 POP FS NP Valid N.E. Pop top of stack into FS; increment stack pointer by 64 bits.
    FCML_I32( "pop fs", 0x0F, 0xA1 );
    FCML_I64( "pop fs", 0x0F, 0xA1 );
    // 0F A9 POP GS NP Valid Valid Pop top of stack into GS; increment stack pointer by 16 bits.
    // 0F A9 POP GS NP N.E. Valid Pop top of stack into GS; increment stack pointer by 32 bits.
    // 0F A9 POP GS NP Valid N.E. Pop top of stack into GS; increment stack pointer by 64 bits.
    FCML_I32( "pop gs", 0x0F, 0xA9 );
    FCML_I64( "pop gs", 0x0F, 0xA9 );
}

void fcml_tf_instruction_POPA(void) {
    // 61 POPA NP Invalid Valid Pop DI, SI, BP, BX, DX, CX, and AX.
    FCML_I32( "popad", 0x61 );
    FCML_I64_FAILED( "popad", 0x61 );
    // 61 POPAD NP Invalid Valid Pop EDI, ESI, EBP, EBX, EDX, ECX, and EAX.
    FCML_I32( "popa", 0x66, 0x61 );
}

void fcml_tf_instruction_POPCNT(void) {
    // F3 0F B8 /r POPCNT r16, r/m16 RM Valid Valid POPCNT on r/m16
    FCML_I32( "popcnt ax,word ptr [eax]", 0x66, 0xF3, 0x0F, 0xB8, 0x00 );
    FCML_I32( "popcnt ax,ax", 0x66, 0xF3, 0x0F, 0xB8, 0xC0 );
    // F3 0F B8 /r POPCNT r32, r/m32 RM Valid Valid POPCNT on r/m32
    FCML_I32( "popcnt eax,dword ptr [eax]", 0xF3, 0x0F, 0xB8, 0x00 );
    // F3 REX.W 0F B8 /r POPCNT r64, r/m64 RM Valid N.E. POPCNT on r/m64
    FCML_I64( "popcnt rax,qword ptr [rax]", 0xF3, 0x48, 0x0F, 0xB8, 0x00 );
}

void fcml_tf_instruction_POPF(void) {
    // 9D POPF NP Valid Valid Pop top of stack into lower 16 bits of EFLAGS.
    FCML_I32( "popf", 0x66, 0x9D );
    FCML_I64( "popf", 0x66, 0x9D );
    // 9D POPFD NP N.E. Valid Pop top of stack into EFLAGS.
    FCML_I32( "popfd", 0x9D );
    FCML_I64_FAILED( "popfd", 0x9D );
    // REX.W + 9D POPFQ NP Valid N.E. Pop top of stack and zero-extend into RFLAGS.
    FCML_I64( "popfq", 0x48, 0x9D );
}

void fcml_tf_instruction_POR(void) {
    // 0F EB /r1 POR mm,mm/m64
    FCML_I64( "por mm0,mmword ptr [rax]", 0x0F, 0xEB, 0x00 );
    FCML_I32( "por mm0,mm1", 0x0F, 0xEB, 0xC1 );
    // 66 0F EB /r POR xmm1,xmm2/m128
    FCML_I64( "por xmm0,xmmword ptr [rax]", 0x66, 0x0F, 0xEB, 0x00 );
    FCML_I32( "por xmm0,xmm1", 0x66, 0x0F, 0xEB, 0xC1 );
    // VEX.NDS.128.66.0F.WIG EB /r VPOR xmm1,xmm2,xmm3/m128
    FCML_I64( "vpor xmm0,xmm0,xmmword ptr [rax]", 0xc5, 0xf9, 0xeb, 0x00 );
    FCML_I32( "vpor xmm0,xmm0,xmm1", 0xc5, 0xf9, 0xeb, 0xc1 );
    // VEX.NDS.256.66.0F.WIG EB /r VPOR ymm1,ymm2,ymm3/m256
    FCML_I64( "vpor ymm0,ymm0,ymmword ptr [rax]", 0xc5, 0xfd, 0xeb, 0x00 );
    FCML_I32( "vpor ymm0,ymm0,ymm1", 0xc5, 0xfd, 0xeb, 0xc1 );
}

void fcml_tf_instruction_PREFETCHT(void) {
    // 0F 18 /1 PREFETCHT0 m8 M Valid Valid Move data from m8 closer to the processor using T0 hint.
    FCML_I32( "prefetcht0 byte ptr [eax]", 0x0F, 0x18, 0x08 );
    FCML_I64( "prefetcht0 byte ptr [rax]", 0x0F, 0x18, 0x08 );
    // 0F 18 /2 PREFETCHT1 m8 M Valid Valid Move data from m8 closer to the processor using T1 hint.
    FCML_I32( "prefetcht1 byte ptr [eax]", 0x0F, 0x18, 0x10 );
    FCML_I64( "prefetcht1 byte ptr [rax]", 0x0F, 0x18, 0x10 );
    // 0F 18 /3 PREFETCHT2 m8 M Valid Valid Move data from m8 closer to the processor using T2 hint.
    FCML_I32( "prefetcht2 byte ptr [eax]", 0x0F, 0x18, 0x18 );
    FCML_I64( "prefetcht2 byte ptr [rax]", 0x0F, 0x18, 0x18 );
    // 0F 18 /0 PREFETCHNTA m8 M Valid Valid Move data from m8 closer to the processor using NTA hint.
    FCML_I32( "prefetchnta byte ptr [eax]", 0x0F, 0x18, 0x00 );
    FCML_I64( "prefetchnta byte ptr [rax]", 0x0F, 0x18, 0x00 );
}

void fcml_tf_instruction_PSADBW(void) {
    // 0F F6 /r PSADBW mm1,mm2/m64
    FCML_I64( "psadbw mm0,mmword ptr [rax]", 0x0F, 0xF6, 0x00 );
    FCML_I32( "psadbw mm0,mm1", 0x0F, 0xF6, 0xC1 );
    // 66 0F F6 /r PSADBW xmm1,xmm2/m128
    FCML_I64( "psadbw xmm0,xmmword ptr [rax]", 0x66, 0x0F, 0xF6, 0x00 );
    FCML_I32( "psadbw xmm0,xmm1", 0x66, 0x0F, 0xF6, 0xC1 );
    // VEX.NDS.128.66.0F.WIG F6 /r VPSADBW xmm1,xmm2,xmm3/m128
    FCML_I64( "vpsadbw xmm0,xmm0,xmmword ptr [rax]", 0xc5, 0xf9, 0xf6, 0x00 );
    FCML_I32( "vpsadbw xmm0,xmm0,xmm1", 0xc5, 0xf9, 0xf6, 0xc1 );
    // VEX.NDS.256.66.0F.WIG F6 /r VPSADBW ymm1,ymm2,ymm3/m256
    FCML_I64( "vpsadbw ymm0,ymm0,ymmword ptr [rax]", 0xc5, 0xfd, 0xf6, 0x00 );
    FCML_I32( "vpsadbw ymm0,ymm0,ymm1", 0xc5, 0xfd, 0xf6, 0xc1 );
}

void fcml_tf_instruction_PSHUFB(void) {
    // 0F 38 00 /r PSHUFB mm1, mm2/m64
    FCML_I64( "pshufb mm0,mmword ptr [rax]", 0x0F, 0x38, 0x00, 0x00 );
    FCML_I32( "pshufb mm0,mm1", 0x0F, 0x38, 0x00, 0xC1 );
    // 66 0F 38 00 /r PSHUFB xmm1, xmm2/m128
    FCML_I64( "pshufb xmm0,xmmword ptr [rax]", 0x66, 0x0F, 0x38, 0x00, 0x00 );
    FCML_I32( "pshufb xmm0,xmm1", 0x66, 0x0F, 0x38, 0x00, 0xC1 );
    // VEX.NDS.128.66.0F38.WIG 00 /r VPSHUFB xmm1, xmm2, xmm3/m128
    FCML_I64( "vpshufb xmm0,xmm0,xmmword ptr [rax]", 0xC4, 0xE2, 0x79, 0x00, 0x00 );
    FCML_I32( "vpshufb xmm0,xmm0,xmm1", 0xC4, 0xE2, 0x79, 0x00, 0xC1 );
    // VEX.NDS.256.66.0F38.WIG 00 /r VPSHUFB ymm1,ymm2,ymm3/m256
    FCML_I64( "vpshufb ymm0,ymm0,ymmword ptr [rax]", 0xC4, 0xE2, 0x7D, 0x00, 0x00 );
    FCML_I32( "vpshufb ymm0,ymm0,ymm1", 0xC4, 0xE2, 0x7D, 0x00, 0xC1 );
}

void fcml_tf_instruction_PSHUFD(void) {
    // 66 0F 70 /r ib PSHUFD xmm1,xmm2/m128,imm8
    FCML_I64( "pshufd xmm0,xmmword ptr [rax],0ffh", 0x66, 0x0F, 0x70, 0x00, 0xFF );
    FCML_I32( "pshufd xmm0,xmm1,0ffh", 0x66, 0x0F, 0x70, 0xC1, 0xFF );
    // VEX.128.66.0F.WIG 70 /r ib VPSHUFD xmm1,xmm2/m128,imm8
    FCML_I64( "vpshufd xmm0,xmmword ptr [rax],0ffh", 0xc5, 0xf9, 0x70, 0x00, 0xff );
    FCML_I32( "vpshufd xmm0,xmm1,0ffh", 0xc5, 0xf9, 0x70, 0xc1, 0xff );
    // VEX.256.66.0F.WIG 70 /r ib VPSHUFD ymm1,ymm2/m256,imm8
    FCML_I64( "vpshufd ymm0,ymmword ptr [rax],0ffh", 0xc5, 0xfd, 0x70, 0x00, 0xff );
    FCML_I32( "vpshufd ymm0,ymm1,0ffh", 0xc5, 0xfd, 0x70, 0xc1, 0xff );
}

void fcml_tf_instruction_PSHUFHW(void) {
    // F3 0F 70 /r ib PSHUFHW xmm1,xmm2/m128,imm8
    FCML_I64( "pshufhw xmm0,xmmword ptr [rax],0ffh", 0xF3, 0x0F, 0x70, 0x00, 0xFF );
    FCML_I32( "pshufhw xmm0,xmm1,0ffh", 0xF3, 0x0F, 0x70, 0xC1, 0xFF );
    // VEX.128.F3.0F.WIG 70 /r ib VPSHUFHW xmm1,xmm2/m128,imm8
    FCML_I64( "vpshufhw xmm0,xmmword ptr [rax],0ffh", 0xc5, 0xfa, 0x70, 0x00, 0xff );
    FCML_I32( "vpshufhw xmm0,xmm1,0ffh", 0xc5, 0xfa, 0x70, 0xc1, 0xff );
    // VEX.256.F3.0F.WIG 70 /r ib VPSHUFHW ymm1,ymm2/m256,imm8
    FCML_I64( "vpshufhw ymm0,ymmword ptr [rax],0ffh", 0xc5, 0xfe, 0x70, 0x00, 0xff );
    FCML_I32( "vpshufhw ymm0,ymm1,0ffh", 0xc5, 0xfe, 0x70, 0xc1, 0xff );
}

void fcml_tf_instruction_PSHUFLW(void) {
    // F2 0F 70 /r ib PSHUFLW xmm1,xmm2/m128,imm8
    FCML_I64( "pshuflw xmm0,xmmword ptr [rax],0ffh", 0xF2, 0x0F, 0x70, 0x00, 0xFF );
    FCML_I32( "pshuflw xmm0,xmm1,0ffh", 0xF2, 0x0F, 0x70, 0xC1, 0xFF );
    // VEX.128.F2.0F.WIG 70 /r ib VPSHUFLW xmm1,xmm2/m128,imm8
    FCML_I64( "vpshuflw xmm0,xmmword ptr [rax],0ffh", 0xc5, 0xfb, 0x70, 0x00, 0xff );
    FCML_I32( "vpshuflw xmm0,xmm1,0ffh", 0xc5, 0xfb, 0x70, 0xc1, 0xff );
    // VEX.256.F2.0F.WIG 70 /r ib VPSHUFLW ymm1,ymm2/m256,imm8
    FCML_I64( "vpshuflw ymm0,ymmword ptr [rax],0ffh", 0xc5, 0xff, 0x70, 0x00, 0xff );
    FCML_I32( "vpshuflw ymm0,ymm1,0ffh", 0xc5, 0xff, 0x70, 0xc1, 0xff );
}

void fcml_tf_instruction_PSHUFW(void) {
    // 0F 70 /r ib PSHUFW mm1,mm2/m64,imm8
    FCML_I64( "pshufw mm0,mmword ptr [rax],0ffh", 0x0F, 0x70, 0x00, 0xFF );
    FCML_I32( "pshufw mm0,mm1,0ffh", 0x0F, 0x70, 0xC1, 0xFF );
}

void fcml_tf_instruction_PSIGN(void) {
    // 0F 38 08 /r PSIGNB mm1,mm2/m64
    FCML_I64( "psignb mm0,mmword ptr [rax]", 0x0F, 0x38, 0x08, 0x00 );
    FCML_I32( "psignb mm0,mm1", 0x0F, 0x38, 0x08, 0xC1 );
    // 0F 38 09 /r PSIGNW mm1,mm2/m64
    FCML_I64( "psignw mm0,mmword ptr [rax]", 0x0F, 0x38, 0x09, 0x00 );
    FCML_I32( "psignw mm0,mm1", 0x0F, 0x38, 0x09, 0xC1 );
    // 0F 38 0A /r PSIGND mm1,mm2/m64
    FCML_I64( "psignd mm0,mmword ptr [rax]", 0x0F, 0x38, 0x0A, 0x00 );
    FCML_I32( "psignd mm0,mm1", 0x0F, 0x38, 0x0A, 0xC1 );
    // 66 0F 38 08 /r PSIGNB xmm1,xmm2/m128
    FCML_I64( "psignb xmm0,xmmword ptr [rax]", 0x66, 0x0F, 0x38, 0x08, 0x00 );
    FCML_I32( "psignb xmm0,xmm1", 0x66, 0x0F, 0x38, 0x08, 0xC1 );
    // 66 0F 38 09 /r PSIGNW xmm1,xmm2/m128
    FCML_I64( "psignw xmm0,xmmword ptr [rax]", 0x66, 0x0F, 0x38, 0x09, 0x00 );
    FCML_I32( "psignw xmm0,xmm1", 0x66, 0x0F, 0x38, 0x09, 0xC1 );
    // 66 0F 38 0A /r PSIGND xmm1,xmm2/m128
    FCML_I64( "psignd xmm0,xmmword ptr [rax]", 0x66, 0x0F, 0x38, 0x0A, 0x00 );
    FCML_I32( "psignd xmm0,xmm1", 0x66, 0x0F, 0x38, 0x0A, 0xC1 );
    // VEX.NDS.128.66.0F38.WIG 08 /r VPSIGNB xmm1,xmm2,xmm3/m128
    FCML_I64( "vpsignb xmm0,xmm0,xmmword ptr [rax]", 0xC4, 0xE2, 0x79, 0x08, 0x00 );
    FCML_I32( "vpsignb xmm0,xmm0,xmm1", 0xC4, 0xE2, 0x79, 0x08, 0xC1 );
    // VEX.NDS.128.66.0F38.WIG 09 /r VPSIGNW xmm1,xmm2,xmm3/m128
    FCML_I64( "vpsignw xmm0,xmm0,xmmword ptr [rax]", 0xC4, 0xE2, 0x79, 0x09, 0x00 );
    FCML_I32( "vpsignw xmm0,xmm0,xmm1", 0xC4, 0xE2, 0x79, 0x09, 0xC1 );
    // VEX.NDS.128.66.0F38.WIG 0A /r VPSIGND xmm1,xmm2,xmm3/m128
    FCML_I64( "vpsignd xmm0,xmm0,xmmword ptr [rax]", 0xC4, 0xE2, 0x79, 0x0A, 0x00 );
    FCML_I32( "vpsignd xmm0,xmm0,xmm1", 0xC4, 0xE2, 0x79, 0x0A, 0xC1 );
    // VEX.NDS.256.66.0F38.WIG 08 /r VPSIGNB ymm1,ymm2,ymm3/m256
    FCML_I64( "vpsignb ymm0,ymm0,ymmword ptr [rax]", 0xC4, 0xE2, 0x7D, 0x08, 0x00 );
    FCML_I32( "vpsignb ymm0,ymm0,ymm1", 0xC4, 0xE2, 0x7D, 0x08, 0xC1 );
    // VEX.NDS.256.66.0F38.WIG 09 /r VPSIGNW ymm1,ymm2,ymm3/m256
    FCML_I64( "vpsignw ymm0,ymm0,ymmword ptr [rax]", 0xC4, 0xE2, 0x7D, 0x09, 0x00 );
    FCML_I32( "vpsignw ymm0,ymm0,ymm1", 0xC4, 0xE2, 0x7D, 0x09, 0xC1 );
    // VEX.NDS.256.66.0F38.WIG 0A /r VPSIGND ymm1,ymm2,ymm3/m256
    FCML_I64( "vpsignd ymm0,ymm0,ymmword ptr [rax]", 0xC4, 0xE2, 0x7D, 0x0A, 0x00 );
    FCML_I32( "vpsignd ymm0,ymm0,ymm1", 0xC4, 0xE2, 0x7D, 0x0A, 0xC1 );
}

void fcml_tf_instruction_PSLLDQ(void) {
    // 66 0F 73 /7 ib PSLLDQ xmm1,imm8
    FCML_I32( "pslldq xmm1,0ffh", 0x66, 0x0F, 0x73, 0xF9, 0xFF );
    // VEX.NDD.128.66.0F.WIG 73 /7 ib VPSLLDQ xmm1,xmm2,imm8
    FCML_I32_D( "vpslldq xmm3,xmm0,0ffh", 0xC4, 0xE1, 0x61, 0x73, 0xF8, 0xFF );
    FCML_I32( "vpslldq xmm3,xmm0,0ffh", 0xc5, 0xe1, 0x73, 0xf8, 0xff );
    // VEX.NDD.256.66.0F.WIG 73 /7 ib VPSLLDQ ymm1,ymm2,imm8
    FCML_I32_D( "vpslldq ymm3,ymm0,0ffh", 0xC4, 0xE1, 0x65, 0x73, 0xF8, 0xFF );
    FCML_I32( "vpslldq ymm3,ymm0,0ffh", 0xc5, 0xe5, 0x73, 0xf8, 0xff );
}

void fcml_tf_instruction_PSLL(void) {
    // 0F F1 /r1 PSLLW mm,mm/m64
    // 0F F2 /r1 PSLLD mm,mm/m64
    // 0F F3 /r1 PSLLQ mm,mm/m64
    FCML_I64( "psllw mm0,mmword ptr [rax]", 0x0F, 0xF1, 0x00 );
    FCML_I32( "psllw mm0,mm1", 0x0F, 0xF1, 0xC1 );
    FCML_I64( "pslld mm0,mmword ptr [rax]", 0x0F, 0xF2, 0x00 );
    FCML_I32( "pslld mm0,mm1", 0x0F, 0xF2, 0xC1 );
    FCML_I64( "psllq mm0,mmword ptr [rax]", 0x0F, 0xF3, 0x00 );
    FCML_I32( "psllq mm0,mm1", 0x0F, 0xF3, 0xC1 );
    // 66 0F F1 /r PSLLW xmm1,xmm2/m128
    // 66 0F F2 /r PSLLD xmm1,xmm2/m128
    // 66 0F F3 /r PSLLQ xmm1,xmm2/m128
    FCML_I64( "psllw xmm0,xmmword ptr [rax]", 0x66, 0x0F, 0xF1, 0x00 );
    FCML_I32( "psllw xmm0,xmm1", 0x66, 0x0F, 0xF1, 0xC1 );
    FCML_I64( "pslld xmm0,xmmword ptr [rax]", 0x66, 0x0F, 0xF2, 0x00 );
    FCML_I32( "pslld xmm0,xmm1", 0x66, 0x0F, 0xF2, 0xC1 );
    FCML_I64( "psllq xmm0,xmmword ptr [rax]", 0x66, 0x0F, 0xF3, 0x00 );
    FCML_I32( "psllq xmm0,xmm1", 0x66, 0x0F, 0xF3, 0xC1 );
    // 0F 71 /6 ib PSLLW mm,imm8
    // 0F 72 /6 ib1 PSLLD mm,imm8
    // 0F 73 /6 ib1 PSLLQ mm,imm8
    FCML_I32( "psllw mm1,0ffh", 0x0F, 0x71, 0xF1, 0xFF );
    FCML_I32( "pslld mm2,0ffh", 0x0F, 0x72, 0xF2, 0xFF );
    FCML_I32( "psllq mm3,0ffh", 0x0F, 0x73, 0xf3, 0xFF );
    // 66 0F 71 /6 ib PSLLW xmm1,imm8
    // 66 0F 72 /6 ib PSLLD xmm1,imm8
    // 66 0F 73 /6 ib PSLLQ xmm1,imm8
    FCML_I32( "psllw xmm1,0ffh", 0x66, 0x0F, 0x71, 0xF1, 0xFF );
    FCML_I32( "pslld xmm1,0ffh", 0x66, 0x0F, 0x72, 0xF1, 0xFF );
    FCML_I32( "psllq xmm1,0ffh", 0x66, 0x0F, 0x73, 0xF1, 0xFF );
    // VEX.NDS.128.66.0F.WIG F1 /r VPSLLW xmm1,xmm2,xmm3/m128
    // VEX.NDS.128.66.0F.WIG F2 /r VPSLLD xmm1,xmm2,xmm3/m128
    // VEX.NDS.128.66.0F.WIG F3 /r VPSLLQ xmm1,xmm2,xmm3/m128
    // VEX.NDS.256.66.0F.WIG F1 /r VPSLLW ymm1, ymm2, xmm3/m128
    // VEX.NDS.256.66.0F.WIG F2 /r VPSLLD ymm1, ymm2, xmm3/m128
    // VEX.NDS.256.66.0F.WIG F3 /r VPSLLQ ymm1, ymm2, xmm3/m128
    FCML_I64( "vpsllw xmm0,xmm0,xmmword ptr [rax]", 0xc5, 0xf9, 0xf1, 0x00 );
    FCML_I64( "vpsllw ymm0,ymm0,ymmword ptr [rax]", 0xc5, 0xfd, 0xf1, 0x00 );
    FCML_I32( "vpsllw xmm0,xmm0,xmm1", 0xc5, 0xf9, 0xf1, 0xc1 );
    FCML_I32( "vpsllw ymm0,ymm0,ymm1", 0xc5, 0xfd, 0xf1, 0xc1 );
    FCML_I64( "vpslld xmm0,xmm0,xmmword ptr [rax]", 0xc5, 0xf9, 0xf2, 0x00 );
    FCML_I64( "vpslld ymm0,ymm0,ymmword ptr [rax]", 0xc5, 0xfd, 0xf2, 0x00 );
    FCML_I32( "vpslld xmm0,xmm0,xmm1", 0xc5, 0xf9, 0xf2, 0xc1 );
    FCML_I32( "vpslld ymm0,ymm0,ymm1", 0xc5, 0xfd, 0xf2, 0xc1 );
    FCML_I64( "vpsllq xmm0,xmm0,xmmword ptr [rax]", 0xc5, 0xf9, 0xf3, 0x00 );
    FCML_I64( "vpsllq ymm0,ymm0,ymmword ptr [rax]", 0xc5, 0xfd, 0xf3, 0x00 );
    FCML_I32( "vpsllq xmm0,xmm0,xmm1", 0xc5, 0xf9, 0xf3, 0xc1 );
    FCML_I32( "vpsllq ymm0,ymm0,ymm1", 0xc5, 0xfd, 0xf3, 0xc1 );
    // VEX.NDD.128.66.0F.WIG 71 /6 ib VPSLLW xmm1,xmm2,imm8
    // VEX.NDD.256.66.0F.WIG 71 /6 ib VPSLLW ymm1, ymm2, imm8
    // VEX.NDD.128.66.0F.WIG 72 /6 ib VPSLLD xmm1,xmm2,imm8
    // VEX.NDD.256.66.0F.WIG 72 /6 ib VPSLLD ymm1, ymm2, imm8
    // VEX.NDD.128.66.0F.WIG 73 /6 ib VPSLLQ xmm1,xmm2,imm8
    // VEX.NDD.256.66.0F.WIG 73 /6 ib VPSLLQ ymm1, ymm2, imm8
    FCML_I3264( "vpsllw xmm3,xmm0,0ffh", 0xc5, 0xe1, 0x71, 0xf0, 0xff );
    FCML_I3264( "vpslld xmm3,xmm0,0ffh", 0xc5, 0xe1, 0x72, 0xf0, 0xff );
    FCML_I3264( "vpsllq xmm3,xmm0,0ffh", 0xc5, 0xe1, 0x73, 0xf0, 0xff );
    FCML_I3264( "vpsllw ymm3,ymm0,0ffh", 0xc5, 0xe5, 0x71, 0xf0, 0xff );
    FCML_I3264( "vpslld ymm3,ymm0,0ffh", 0xc5, 0xe5, 0x72, 0xf0, 0xff );
    FCML_I3264( "vpsllq ymm3,ymm0,0ffh", 0xc5, 0xe5, 0x73, 0xf0, 0xff );
}

void fcml_tf_instruction_PSRA(void) {
    // 0F E1 /r1 PSRAW mm,mm/m64
    // 0F E2 /r1 PSRAD mm,mm/m64
    FCML_I64( "psraw mm0,mmword ptr [rax]", 0x0F, 0xE1, 0x00 );
    FCML_I32( "psraw mm0,mm1", 0x0F, 0xE1, 0xC1 );
    FCML_I64( "psrad mm0,mmword ptr [rax]", 0x0F, 0xE2, 0x00 );
    FCML_I32( "psrad mm0,mm1", 0x0F, 0xE2, 0xC1 );
    // 66 0F E1 /r PSRAW xmm1,xmm2/m128
    // 66 0F E2 /r PSRAD xmm1,xmm2/m128
    FCML_I64( "psraw xmm0,xmmword ptr [rax]", 0x66, 0x0F, 0xE1, 0x00 );
    FCML_I32( "psraw xmm0,xmm1", 0x66, 0x0F, 0xE1, 0xC1 );
    FCML_I64( "psrad xmm0,xmmword ptr [rax]", 0x66, 0x0F, 0xE2, 0x00 );
    FCML_I32( "psrad xmm0,xmm1", 0x66, 0x0F, 0xE2, 0xC1 );
    // VEX.NDS.128.66.0F.WIG E1 /r VPSRAW xmm1,xmm2,xmm3/m128
    // VEX.NDS.128.66.0F.WIG E2 /r VPSRAD xmm1,xmm2,xmm3/m128
    FCML_I64( "vpsraw xmm0,xmm0,xmmword ptr [rax]", 0xc5, 0xf9, 0xe1, 0x00 );
    FCML_I32( "vpsraw xmm0,xmm0,xmm1", 0xc5, 0xf9, 0xe1, 0xc1 );
    FCML_I64( "vpsrad xmm0,xmm0,xmmword ptr [rax]", 0xc5, 0xf9, 0xe2, 0x00 );
    FCML_I32( "vpsrad xmm0,xmm0,xmm1", 0xc5, 0xf9, 0xe2, 0xc1 );
    // VEX.NDS.256.66.0F.WIG E1 /r VPSRAW ymm1, ymm2, xmm3/m128
    // VEX.NDS.256.66.0F.WIG E2 /r VPSRAD ymm1, ymm2, xmm3/m128
    FCML_I64( "vpsraw ymm0,ymm0,xmmword ptr [rax]", 0xc5, 0xfd, 0xe1, 0x00 );
    FCML_I32( "vpsraw ymm0,ymm0,xmm1", 0xc5, 0xfd, 0xe1, 0xc1 );
    FCML_I64( "vpsrad ymm0,ymm0,xmmword ptr [rax]", 0xc5, 0xfd, 0xe2, 0x00 );
    FCML_I32( "vpsrad ymm0,ymm0,xmm1", 0xc5, 0xfd, 0xe2, 0xc1 );
    // 0F 71 /4 ib1 PSRAW mm,imm8
    // 0F 72 /4 ib1 PSRAD mm,imm8
    FCML_I32( "psraw mm1,0ffh", 0x0F, 0x71, 0xE1, 0xFF );
    FCML_I32( "psrad mm2,0ffh", 0x0F, 0x72, 0xE2, 0xFF );
    // 66 0F 71 /4 ib PSRAW xmm1,imm8
    // 66 0F 72 /4 ib PSRAD xmm1,imm8
    FCML_I32( "psraw xmm1,0ffh", 0x66, 0x0F, 0x71, 0xE1, 0xFF );
    FCML_I32( "psrad xmm1,0ffh", 0x66, 0x0F, 0x72, 0xE1, 0xFF );
    // VEX.NDD.128.66.0F.WIG 71 /4 ib VPSRAW xmm1,xmm2,imm8
    // VEX.NDD.128.66.0F.WIG 72 /4 ib VPSRAD xmm1,xmm2,imm8
    FCML_I32( "vpsraw xmm3,xmm0,0ffh", 0xc5, 0xe1, 0x71, 0xe0, 0xff );
    FCML_I32( "vpsrad xmm3,xmm0,0ffh", 0xc5, 0xe1, 0x72, 0xe0, 0xff );
    // VEX.NDD.256.66.0F.WIG 71 /4 ib VPSRAW ymm1, ymm2, imm8
    // VEX.NDD.256.66.0F.WIG 72 /4 ib VPSRAD ymm1, ymm2, imm8
    FCML_I32( "vpsraw ymm3,ymm0,0ffh", 0xc5, 0xe5, 0x71, 0xe0, 0xff );
    FCML_I32( "vpsrad ymm3,ymm0,0ffh", 0xc5, 0xe5, 0x72, 0xe0, 0xff );
}

void fcml_tf_instruction_PSRLDQ(void) {
    // 66 0F 73 /7 ib PSLLDQ xmm1,imm8
    FCML_I32( "pslldq xmm1,0ffh", 0x66, 0x0F, 0x73, 0xF9, 0xFF );
    // VEX.NDD.128.66.0F.WIG 73 /7 ib VPSLLDQ xmm1,xmm2,imm8
    FCML_I32( "vpslldq xmm3,xmm0,0ffh", 0xc5, 0xe1, 0x73, 0xf8, 0xff );
    // VEX.NDD.256.66.0F.WIG 73 /7 ib VPSLLDQ ymm1,ymm2,imm8
    FCML_I32( "vpslldq ymm3,ymm0,0ffh", 0xc5, 0xe5, 0x73, 0xf8, 0xff );
}

void fcml_tf_instruction_PSRL(void) {
    // 0F D1 /r PSRLW mm,mm/m64
    FCML_I64( "psrlw mm0,mmword ptr [rax]", 0x0F, 0xD1, 0x00 );
    FCML_I32( "psrlw mm0,mm1", 0x0F, 0xD1, 0xC1 );
    // 0F D2 /r PSRLD mm,mm/m64
    FCML_I64( "psrld mm0,mmword ptr [rax]", 0x0F, 0xD2, 0x00 );
    FCML_I32( "psrld mm0,mm1", 0x0F, 0xD2, 0xC1 );
    // 0F D3 /r PSRLQ mm,mm/m64
    FCML_I64( "psrlq mm0,mmword ptr [rax]", 0x0F, 0xD3, 0x00 );
    FCML_I32( "psrlq mm0,mm1", 0x0F, 0xD3, 0xC1 );
    // 66 0F D1 /r PSRLW xmm1,xmm2/m128
    FCML_I64( "psrlw xmm0,xmmword ptr [rax]", 0x66, 0x0F, 0xD1, 0x00 );
    FCML_I32( "psrlw xmm0,xmm1", 0x66, 0x0F, 0xD1, 0xC1 );
    // 66 0F D2 /r PSRLD xmm1,xmm2/m128
    FCML_I64( "psrld xmm0,xmmword ptr [rax]", 0x66, 0x0F, 0xD2, 0x00 );
    FCML_I32( "psrld xmm0,xmm1", 0x66, 0x0F, 0xD2, 0xC1 );
    // 66 0F D3 /r PSRLQ xmm1,xmm2/m128
    FCML_I64( "psrlq xmm0,xmmword ptr [rax]", 0x66, 0x0F, 0xD3, 0x00 );
    FCML_I32( "psrlq xmm0,xmm1", 0x66, 0x0F, 0xD3, 0xC1 );
    // 0F 71 /2 ib PSRLW mm,imm8
    FCML_I32( "psrlw mm1,0ffh", 0x0F, 0x71, 0xD1, 0xFF );
    // 0F 72 /2 ib PSRLD mm,imm8
    FCML_I32( "psrld mm2,0ffh", 0x0F, 0x72, 0xD2, 0xFF );
    // 0F 73 /2 ib PSRLQ mm,imm8
    FCML_I32( "psrlq mm3,0ffh", 0x0F, 0x73, 0xD3, 0xFF );
    // 66 0F 71 /2 ib PSRLW xmm1,imm8
    FCML_I32( "psrlw xmm1,0ffh", 0x66, 0x0F, 0x71, 0xD1, 0xFF );
    // 66 0F 72 /2 ib PSRLD xmm1,imm8
    FCML_I32( "psrld xmm1,0ffh", 0x66, 0x0F, 0x72, 0xD1, 0xFF );
    // 66 0F 73 /2 ib PSRLQ xmm1,imm8
    FCML_I32( "psrlq xmm1,0ffh", 0x66, 0x0F, 0x73, 0xD1, 0xFF );
    // VEX.NDS.128.66.0F.WIG D1 /r VPSRLW xmm1,xmm2,xmm3/m128
    FCML_I64_D( "vpsrlw xmm0,xmm0,xmmword ptr [rax]", 0xC4, 0xE1, 0x79, 0xD1, 0x00 );
    FCML_I64( "vpsrlw xmm0,xmm0,xmmword ptr [rax]", 0xc5, 0xf9, 0xd1, 0x00 );
    FCML_I32_D( "vpsrlw xmm0,xmm0,xmm1", 0xC4, 0xE1, 0x79, 0xD1, 0xC1 );
    FCML_I32( "vpsrlw xmm0,xmm0,xmm1", 0xc5, 0xf9, 0xd1, 0xc1 );
    // VEX.NDS.256.66.0F.WIG D1 /r VPSRLW ymm1,ymm2,xmm3/m128
    FCML_I64( "vpsrlw ymm0,ymm0,xmmword ptr [rax]", 0xc5, 0xfd, 0xd1, 0x00 );
    FCML_I32( "vpsrlw ymm0,ymm0,xmm1", 0xc5, 0xfd, 0xd1, 0xc1 );
    // VEX.NDS.128.66.0F.WIG D2 /r VPSRLD xmm1,xmm2,xmm3/m128
    FCML_I64( "vpsrld xmm0,xmm0,xmmword ptr [rax]", 0xc5, 0xf9, 0xd2, 0x00 );
    FCML_I32( "vpsrld xmm0,xmm0,xmm1", 0xc5, 0xf9, 0xd2, 0xc1 );
    // VEX.NDS.256.66.0F.WIG D2 /r VPSRLD ymm1,ymm2,xmm3/m128
    FCML_I64( "vpsrld ymm0,ymm0,xmmword ptr [rax]", 0xc5, 0xfd, 0xd2, 0x00 );
    FCML_I32( "vpsrld ymm0,ymm0,xmm1", 0xc5, 0xfd, 0xd2, 0xc1 );
    // VEX.NDS.128.66.0F.WIG D3 /r VPSRLQ xmm1,xmm2,xmm3/m128
    FCML_I64( "vpsrlq xmm0,xmm0,xmmword ptr [rax]", 0xc5, 0xf9, 0xd3, 0x00 );
    FCML_I32( "vpsrlq xmm0,xmm0,xmm1", 0xc5, 0xf9, 0xd3, 0xc1 );
    // VEX.NDD.128.66.0F.WIG 71 /2 ib VPSRLW xmm1,xmm2,imm8
    FCML_I32_D( "vpsrlw xmm3,xmm0,0ffh", 0xC4, 0xE1, 0x61, 0x71, 0xD0, 0xFF );
    FCML_I32( "vpsrlw xmm3,xmm0,0ffh", 0xc5, 0xe1, 0x71, 0xd0, 0xff );
    // VEX.NDD.128.66.0F.WIG 72 /2 ib VPSRLD xmm1,xmm2,imm8
    FCML_I32_D( "vpsrld xmm3,xmm0,0ffh", 0xC4, 0xE1, 0x61, 0x72, 0xD0, 0xFF );
    FCML_I32( "vpsrld xmm3,xmm0,0ffh", 0xc5, 0xe1, 0x72, 0xd0, 0xff );
    // VEX.NDD.128.66.0F.WIG 73 /2 ib VPSRLQ xmm1,xmm2,imm8
    FCML_I32_D( "vpsrlq xmm3,xmm0,0ffh", 0xC4, 0xE1, 0x61, 0x73, 0xD0, 0xFF );
    FCML_I32( "vpsrlq xmm3,xmm0,0ffh", 0xc5, 0xe1, 0x73, 0xd0, 0xff );
    // VEX.NDD.256.66.0F.WIG 71 /2 ib VPSRLW ymm1,ymm2,imm8
    FCML_I32_D( "vpsrlw ymm3,ymm0,0ffh", 0xC4, 0xE1, 0x65, 0x71, 0xD0, 0xFF );
    FCML_I32( "vpsrlw ymm3,ymm0,0ffh", 0xc5, 0xe5, 0x71, 0xd0, 0xff );
}

void fcml_tf_instruction_PSUB(void) {
    // 0F F8 /r PSUBB mm,mm/m64
    FCML_I64( "psubb mm0,mmword ptr [rax]", 0x0F, 0xF8, 0x00 );
    FCML_I32( "psubb mm0,mm1", 0x0F, 0xF8, 0xC1 );
    // 0F F9 /r PSUBW mm,mm/m64
    FCML_I64( "psubw mm0,mmword ptr [rax]", 0x0F, 0xF9, 0x00 );
    FCML_I32( "psubw mm0,mm1", 0x0F, 0xF9, 0xC1 );
    // 0F FA /r PSUBD mm,mm/m64
    FCML_I64( "psubd mm0,mmword ptr [rax]", 0x0F, 0xFA, 0x00 );
    FCML_I32( "psubd mm0,mm1", 0x0F, 0xFA, 0xC1 );
    // 66 0F F8 /r PSUBB xmm1,xmm2/m128
    FCML_I64( "psubb xmm0,xmmword ptr [rax]", 0x66, 0x0F, 0xF8, 0x00 );
    FCML_I32( "psubb xmm0,xmm1", 0x66, 0x0F, 0xF8, 0xC1 );
    // 66 0F F9 /r PSUBW xmm1,xmm2/m128
    FCML_I64( "psubw xmm0,xmmword ptr [rax]", 0x66, 0x0F, 0xF9, 0x00 );
    FCML_I32( "psubw xmm0,xmm1", 0x66, 0x0F, 0xF9, 0xC1 );
    // 66 0F FA /r PSUBD xmm1,xmm2/m128
    FCML_I64( "psubd xmm0,xmmword ptr [rax]", 0x66, 0x0F, 0xFA, 0x00 );
    FCML_I32( "psubd xmm0,xmm1", 0x66, 0x0F, 0xFA, 0xC1 );
    // VEX.NDS.128.66.0F.WIG F8 /r VPSUBB xmm1,xmm2,xmm3/m128
    FCML_I64( "vpsubb xmm0,xmm0,xmmword ptr [rax]", 0xc5, 0xf9, 0xf8, 0x00 );
    FCML_I32( "vpsubb xmm0,xmm0,xmm1", 0xc5, 0xf9, 0xf8, 0xc1 );
    // VEX.NDS.128.66.0F.WIG F9 /r VPSUBW xmm1,xmm2,xmm3/m128
    FCML_I64( "vpsubw xmm0,xmm0,xmmword ptr [rax]", 0xc5, 0xf9, 0xf9, 0x00 );
    FCML_I32( "vpsubw xmm0,xmm0,xmm1", 0xc5, 0xf9, 0xf9, 0xc1 );
    // VEX.NDS.128.66.0F.WIG FA /r VPSUBD xmm1,xmm2,xmm3/m128
    FCML_I64( "vpsubd xmm0,xmm0,xmmword ptr [rax]", 0xc5, 0xf9, 0xfa, 0x00 );
    FCML_I32( "vpsubd xmm0,xmm0,xmm1", 0xc5, 0xf9, 0xfa, 0xc1 );
    // VEX.NDS.256.66.0F.WIG F8 /r VPSUBB ymm1,ymm2,ymm3/m256
    FCML_I64( "vpsubb ymm0,ymm0,ymmword ptr [rax]", 0xc5, 0xfd, 0xf8, 0x00 );
    FCML_I32( "vpsubb ymm0,ymm0,ymm1", 0xc5, 0xfd, 0xf8, 0xc1 );
    // VEX.NDS.256.66.0F.WIG F9 /r VPSUBW ymm1,ymm2,ymm3/m256
    FCML_I64( "vpsubw ymm0,ymm0,ymmword ptr [rax]", 0xc5, 0xfd, 0xf9, 0x00 );
    FCML_I32( "vpsubw ymm0,ymm0,ymm1", 0xc5, 0xfd, 0xf9, 0xc1 );
    // VEX.NDS.256.66.0F.WIG FA /r VPSUBD ymm1,ymm2,ymm3/m256
    FCML_I64( "vpsubd ymm0,ymm0,ymmword ptr [rax]", 0xc5, 0xfd, 0xfa, 0x00 );
    FCML_I32( "vpsubd ymm0,ymm0,ymm1", 0xc5, 0xfd, 0xfa, 0xc1 );
    // VEX.NDS.256.66.0F.WIG FB /r VPSUBQ ymm1,ymm2,ymm3/m256
    FCML_I64( "vpsubq ymm0,ymm0,ymmword ptr [rax]", 0xc5, 0xfd, 0xfb, 0x00 );
    FCML_I32( "vpsubq ymm0,ymm0,ymm1", 0xc5, 0xfd, 0xfb, 0xc1 );
}

void fcml_tf_instruction_PSUBQ(void) {
    // 0F FB /r PSUBQ mm1,mm2/m64
    FCML_I64( "psubq mm0,mmword ptr [rax]", 0x0F, 0xFB, 0x00 );
    FCML_I32( "psubq mm0,mm1", 0x0F, 0xFB, 0xC1 );
    // 66 0F FB /r PSUBQ xmm1,xmm2/m128
    FCML_I64( "psubq xmm0,xmmword ptr [rax]", 0x66, 0x0F, 0xFB, 0x00 );
    FCML_I32( "psubq xmm0,xmm1", 0x66, 0x0F, 0xFB, 0xC1 );
    // VEX.NDS.128.66.0F.WIG FB/r VPSUBQ xmm1,xmm2,xmm3/m128
    FCML_I64( "vpsubq xmm0,xmm0,xmmword ptr [rax]", 0xc5, 0xf9, 0xfb, 0x00 );
    FCML_I32( "vpsubq xmm0,xmm0,xmm1", 0xc5, 0xf9, 0xfb, 0xc1 );
}

void fcml_tf_instruction_PSUBS(void) {
    // 0F E8 /r PSUBSB mm,mm/m64
    FCML_I64( "psubsb mm0,mmword ptr [rax]", 0x0F, 0xE8, 0x00 );
    FCML_I32( "psubsb mm0,mm1", 0x0F, 0xE8, 0xC1 );
    // 0F E9 /r PSUBSW mm,mm/m64
    FCML_I64( "psubsw mm0,mmword ptr [rax]", 0x0F, 0xE9, 0x00 );
    FCML_I32( "psubsw mm0,mm1", 0x0F, 0xE9, 0xC1 );
    // 66 0F E8 /r PSUBSB xmm1,xmm2/m128
    FCML_I64( "psubsb xmm0,xmmword ptr [rax]", 0x66, 0x0F, 0xE8, 0x00 );
    FCML_I32( "psubsb xmm0,xmm1", 0x66, 0x0F, 0xE8, 0xC1 );
    // 66 0F E9 /r PSUBSW xmm1,xmm2/m128
    FCML_I64( "psubsw xmm0,xmmword ptr [rax]", 0x66, 0x0F, 0xE9, 0x00 );
    FCML_I32( "psubsw xmm0,xmm1", 0x66, 0x0F, 0xE9, 0xC1 );
    // VEX.NDS.128.66.0F.WIG E8 /r VPSUBSB xmm1,xmm2,xmm3/m128
    FCML_I64( "vpsubsb xmm0,xmm0,xmmword ptr [rax]", 0xc5, 0xf9, 0xe8, 0x00 );
    FCML_I32( "vpsubsb xmm0,xmm0,xmm1", 0xc5, 0xf9, 0xe8, 0xc1 );
    // VEX.NDS.128.66.0F.WIG E9 /r VPSUBSW xmm1,xmm2,xmm3/m128
    FCML_I64( "vpsubsw xmm0,xmm0,xmmword ptr [rax]", 0xc5, 0xf9, 0xe9, 0x00 );
    FCML_I32( "vpsubsw xmm0,xmm0,xmm1", 0xc5, 0xf9, 0xe9, 0xc1 );
    // VEX.NDS.256.66.0F.WIG E8 /r VPSUBSB ymm1,ymm2,ymm3/m256
    FCML_I64( "vpsubsb ymm0,ymm0,ymmword ptr [rax]", 0xc5, 0xfd, 0xe8, 0x00 );
    FCML_I32( "vpsubsb ymm0,ymm0,ymm1", 0xc5, 0xfd, 0xe8, 0xc1 );
    // VEX.NDS.256.66.0F.WIG E9 /r VPSUBSW ymm1,ymm2,ymm3/m256
    FCML_I64( "vpsubsw ymm0,ymm0,ymmword ptr [rax]", 0xc5, 0xfd, 0xe9, 0x00 );
    FCML_I32( "vpsubsw ymm0,ymm0,ymm1", 0xc5, 0xfd, 0xe9, 0xc1 );
}

void fcml_tf_instruction_PSUBUS(void) {
    // 0F D8 /r PSUBUSB mm,mm/m64
    FCML_I64( "psubusb mm0,mmword ptr [rax]", 0x0F, 0xD8, 0x00 );
    FCML_I32( "psubusb mm0,mm1", 0x0F, 0xD8, 0xC1 );
    // 0F D9 /r1 PSUBUSW mm,mm/m64
    FCML_I64( "psubusw mm0,mmword ptr [rax]", 0x0F, 0xD9, 0x00 );
    FCML_I32( "psubusw mm0,mm1", 0x0F, 0xD9, 0xC1 );
    // 66 0F D8 /r PSUBUSB xmm1,xmm2/m128
    FCML_I64( "psubusb xmm0,xmmword ptr [rax]", 0x66, 0x0F, 0xD8, 0x00 );
    FCML_I32( "psubusb xmm0,xmm1", 0x66, 0x0F, 0xD8, 0xC1 );
    // 66 0F D9 /r PSUBUSW xmm1,xmm2/m128
    FCML_I64( "psubusw xmm0,xmmword ptr [rax]", 0x66, 0x0F, 0xD9, 0x00 );
    FCML_I32( "psubusw xmm0,xmm1", 0x66, 0x0F, 0xD9, 0xC1 );
    // VEX.NDS.128.66.0F.WIG D8 /r VPSUBUSB xmm1,xmm2,xmm3/m128
    FCML_I64( "vpsubusb xmm0,xmm0,xmmword ptr [rax]", 0xc5, 0xf9, 0xd8, 0x00 );
    FCML_I32( "vpsubusb xmm0,xmm0,xmm1", 0xc5, 0xf9, 0xd8, 0xc1 );
    // VEX.NDS.128.66.0F.WIG D9 /r VPSUBUSW xmm1,xmm2,xmm3/m128
    FCML_I64( "vpsubusw xmm0,xmm0,xmmword ptr [rax]", 0xc5, 0xf9, 0xd9, 0x00 );
    FCML_I32( "vpsubusw xmm0,xmm0,xmm1", 0xc5, 0xf9, 0xd9, 0xc1 );
    // VEX.NDS.256.66.0F.WIG D8 /r VPSUBUSB ymm1,ymm2,ymm3/m256
    FCML_I64( "vpsubusb ymm0,ymm0,ymmword ptr [rax]", 0xc5, 0xfd, 0xd8, 0x00 );
    FCML_I32( "vpsubusb ymm0,ymm0,ymm1", 0xc5, 0xfd, 0xd8, 0xc1 );
    // VEX.NDS.256.66.0F.WIG D9 /r VPSUBUSW ymm1,ymm2,ymm3/m256
    FCML_I64( "vpsubusw ymm0,ymm0,ymmword ptr [rax]", 0xc5, 0xfd, 0xd9, 0x00 );
    FCML_I32( "vpsubusw ymm0,ymm0,ymm1", 0xc5, 0xfd, 0xd9, 0xc1 );
}

void fcml_tf_instruction_PTEST(void) {
    // 66 0F 38 17 /r PTEST xmm1,xmm2/m128
    FCML_I64( "ptest xmm0,xmmword ptr [rax]", 0x66, 0x0F, 0x38, 0x17, 0x00 );
    FCML_I32( "ptest xmm0,xmm1", 0x66, 0x0F, 0x38, 0x17, 0xC1 );
    // VEX.128.66.0F38.WIG 17 /r VPTEST xmm1,xmm2/m128
    // VEX.256.66.0F38.WIG 17 /r VPTEST ymm1,ymm2/m256
    FCML_I64( "vptest xmm3,xmm0", 0xC4, 0xE2, 0x79, 0x17, 0xD8 );
    FCML_I32( "vptest xmm3,xmm0", 0xC4, 0xE2, 0x79, 0x17, 0xD8 );
    FCML_I32( "vptest ymm0,ymmword ptr [eax]", 0xC4, 0xE2, 0x7D, 0x17, 0x00 );
}

void fcml_tf_instruction_PUNPCKLB(void) {
    // 0F 60 /r PUNPCKLBW mm,mm/m32
    FCML_I64( "punpcklbw mm0,dword ptr [rax]", 0x0F, 0x60, 0x00 );
    FCML_I32( "punpcklbw mm0,mm1", 0x0F, 0x60, 0xC1 );
    // 0F 61 /r PUNPCKLWD mm,mm/m32
    FCML_I64( "punpcklwd mm0,dword ptr [rax]", 0x0F, 0x61, 0x00 );
    FCML_I32( "punpcklwd mm0,mm1", 0x0F, 0x61, 0xC1 );
    // 0F 62 /r PUNPCKLDQ mm,mm/m32
    FCML_I64( "punpckldq mm0,dword ptr [rax]", 0x0F, 0x62, 0x00 );
    FCML_I32( "punpckldq mm0,mm1", 0x0F, 0x62, 0xC1 );
    // 66 0F 60 /r PUNPCKLBW xmm1,xmm2/m128
    FCML_I64( "punpcklbw xmm0,xmmword ptr [rax]", 0x66, 0x0F, 0x60, 0x00 );
    FCML_I32( "punpcklbw xmm0,xmm1", 0x66, 0x0F, 0x60, 0xC1 );
    // 66 0F 61 /r PUNPCKLWD xmm1,xmm2/m128
    FCML_I64( "punpcklwd xmm0,xmmword ptr [rax]", 0x66, 0x0F, 0x61, 0x00 );
    FCML_I32( "punpcklwd xmm0,xmm1", 0x66, 0x0F, 0x61, 0xC1 );
    // 66 0F 62 /r PUNPCKLDQ xmm1,xmm2/m128
    FCML_I64( "punpckldq xmm0,xmmword ptr [rax]", 0x66, 0x0F, 0x62, 0x00 );
    FCML_I32( "punpckldq xmm0,xmm1", 0x66, 0x0F, 0x62, 0xC1 );
    // 66 0F 6C /r PUNPCKLQDQ xmm1,xmm2/m128
    FCML_I64( "punpcklqdq xmm0,xmmword ptr [rax]", 0x66, 0x0F, 0x6c, 0x00 );
    FCML_I32( "punpcklqdq xmm0,xmm1", 0x66, 0x0F, 0x6c, 0xC1 );
    // VEX.NDS.128.66.0F.WIG 60/r VPUNPCKLBW xmm1,xmm2,xmm3/m128
    FCML_I64( "vpunpcklbw xmm0,xmm0,xmmword ptr [rax]", 0xc5, 0xf9, 0x60, 0x00 );
    FCML_I32( "vpunpcklbw xmm0,xmm0,xmm1", 0xc5, 0xf9, 0x60, 0xc1 );
    // VEX.NDS.128.66.0F.WIG 61/r VPUNPCKLWD xmm1,xmm2,xmm3/m128
    FCML_I64( "vpunpcklwd xmm0,xmm0,xmmword ptr [rax]", 0xc5, 0xf9, 0x61, 0x00 );
    FCML_I32( "vpunpcklwd xmm0,xmm0,xmm1", 0xc5, 0xf9, 0x61, 0xc1 );
    // VEX.NDS.128.66.0F.WIG 62/r VPUNPCKLDQ xmm1,xmm2,xmm3/m128
    FCML_I64( "vpunpckldq xmm0,xmm0,xmmword ptr [rax]", 0xc5, 0xf9, 0x62, 0x00 );
    FCML_I32( "vpunpckldq xmm0,xmm0,xmm1", 0xc5, 0xf9, 0x62, 0xc1 );
    // VEX.NDS.128.66.0F.WIG 6C/r VPUNPCKLQDQ xmm1,xmm2,xmm3/m128
    FCML_I64( "vpunpcklqdq xmm0,xmm0,xmmword ptr [rax]", 0xc5, 0xf9, 0x6c, 0x00 );
    FCML_I32( "vpunpcklqdq xmm0,xmm0,xmm1", 0xc5, 0xf9, 0x6c, 0xc1 );
    // VEX.NDS.256.66.0F.WIG 60 /r VPUNPCKLBW ymm1,ymm2,ymm3/m256
    FCML_I64( "vpunpcklbw ymm0,ymm0,ymmword ptr [rax]", 0xc5, 0xfd, 0x60, 0x00 );
    FCML_I32( "vpunpcklbw ymm0,ymm0,ymm1", 0xc5, 0xfd, 0x60, 0xc1 );
    // VEX.NDS.256.66.0F.WIG 61 /r VPUNPCKLWD ymm1,ymm2,ymm3/m256
    FCML_I64( "vpunpcklwd ymm0,ymm0,ymmword ptr [rax]", 0xc5, 0xfd, 0x61, 0x00 );
    FCML_I32( "vpunpcklwd ymm0,ymm0,ymm1", 0xc5, 0xfd, 0x61, 0xc1 );
    // VEX.NDS.256.66.0F.WIG 62 /r VPUNPCKLDQ ymm1,ymm2,ymm3/m256
    FCML_I64( "vpunpckldq ymm0,ymm0,ymmword ptr [rax]", 0xc5, 0xfd, 0x62, 0x00 );
    FCML_I32( "vpunpckldq ymm0,ymm0,ymm1", 0xc5, 0xfd, 0x62, 0xc1 );
    // VEX.NDS.256.66.0F.WIG 6C /r VPUNPCKLQDQ ymm1,ymm2,ymm3/m256
    FCML_I64( "vpunpcklqdq ymm0,ymm0,ymmword ptr [rax]", 0xc5, 0xfd, 0x6c, 0x00 );
    FCML_I32( "vpunpcklqdq ymm0,ymm0,ymm1", 0xc5, 0xfd, 0x6c, 0xc1 );
}

void fcml_tf_instruction_PUNPCKHB(void) {
    // 0F 68 /r PUNPCKHBW mm,mm/m64
    FCML_I64( "punpckhbw mm0,mmword ptr [rax]", 0x0F, 0x68, 0x00 );
    FCML_I32( "punpckhbw mm0,mm1", 0x0F, 0x68, 0xC1 );
    // 0F 69 /r PUNPCKHWD mm,mm/m64
    FCML_I64( "punpckhwd mm0,mmword ptr [rax]", 0x0F, 0x69, 0x00 );
    FCML_I32( "punpckhwd mm0,mm1", 0x0F, 0x69, 0xC1 );
    // 0F 6A /r PUNPCKHDQ mm,mm/m64
    FCML_I64( "punpckhdq mm0,mmword ptr [rax]", 0x0F, 0x6A, 0x00 );
    FCML_I32( "punpckhdq mm0,mm1", 0x0F, 0x6A, 0xC1 );
    // 66 0F 68 /r PUNPCKHBW xmm1,xmm2/m128
    FCML_I64( "punpckhbw xmm0,xmmword ptr [rax]", 0x66, 0x0F, 0x68, 0x00 );
    FCML_I32( "punpckhbw xmm0,xmm1", 0x66, 0x0F, 0x68, 0xC1 );
    // 66 0F 69 /r PUNPCKHWD xmm1,xmm2/m128
    FCML_I64( "punpckhwd xmm0,xmmword ptr [rax]", 0x66, 0x0F, 0x69, 0x00 );
    FCML_I32( "punpckhwd xmm0,xmm1", 0x66, 0x0F, 0x69, 0xC1 );
    // 66 0F 6A /r PUNPCKHDQ xmm1,xmm2/m128
    FCML_I64( "punpckhdq xmm0,xmmword ptr [rax]", 0x66, 0x0F, 0x6A, 0x00 );
    FCML_I32( "punpckhdq xmm0,xmm1", 0x66, 0x0F, 0x6A, 0xC1 );
    // 66 0F 6D /r PUNPCKHQDQ xmm1,xmm2/m128
    FCML_I64( "punpckhqdq xmm0,xmmword ptr [rax]", 0x66, 0x0F, 0x6D, 0x00 );
    FCML_I32( "punpckhqdq xmm0,xmm1", 0x66, 0x0F, 0x6D, 0xC1 );
    // VEX.NDS.128.66.0F.WIG 68/r VPUNPCKHBW xmm1,xmm2,xmm3/m128
    FCML_I64( "vpunpckhbw xmm0,xmm0,xmmword ptr [rax]", 0xc5, 0xf9, 0x68, 0x00 );
    FCML_I32( "vpunpckhbw xmm0,xmm0,xmm1", 0xc5, 0xf9, 0x68, 0xc1 );
    // VEX.NDS.128.66.0F.WIG 69/r VPUNPCKHWD xmm1,xmm2,xmm3/m128
    FCML_I64( "vpunpckhwd xmm0,xmm0,xmmword ptr [rax]", 0xc5, 0xf9, 0x69, 0x00 );
    FCML_I32( "vpunpckhwd xmm0,xmm0,xmm1", 0xc5, 0xf9, 0x69, 0xc1 );
    // VEX.NDS.128.66.0F.WIG 6A/r VPUNPCKHDQ xmm1,xmm2,xmm3/m128
    FCML_I64( "vpunpckhdq xmm0,xmm0,xmmword ptr [rax]", 0xc5, 0xf9, 0x6a, 0x00 );
    FCML_I32( "vpunpckhdq xmm0,xmm0,xmm1", 0xc5, 0xf9, 0x6a, 0xc1 );
    // VEX.NDS.128.66.0F.WIG 6D/r VPUNPCKHQDQ xmm1,xmm2,xmm3/m128
    FCML_I64( "vpunpckhqdq xmm0,xmm0,xmmword ptr [rax]", 0xc5, 0xf9, 0x6d, 0x00 );
    FCML_I32( "vpunpckhqdq xmm0,xmm0,xmm1", 0xc5, 0xf9, 0x6d, 0xc1 );
    // VEX.NDS.256.66.0F.WIG 68 /r VPUNPCKHBW ymm1,ymm2,ymm3/m256
    FCML_I64( "vpunpckhbw ymm0,ymm0,ymmword ptr [rax]", 0xc5, 0xfd, 0x68, 0x00 );
    FCML_I32( "vpunpckhbw ymm0,ymm0,ymm1", 0xc5, 0xfd, 0x68, 0xc1 );
    // VEX.NDS.256.66.0F.WIG 69 /r VPUNPCKHWD ymm1,ymm2,ymm3/m256
    FCML_I64( "vpunpckhwd ymm0,ymm0,ymmword ptr [rax]", 0xc5, 0xfd, 0x69, 0x00 );
    FCML_I32( "vpunpckhwd ymm0,ymm0,ymm1", 0xc5, 0xfd, 0x69, 0xc1 );
    // VEX.NDS.256.66.0F.WIG 6A /r VPUNPCKHDQ ymm1,ymm2,ymm3/m256
    FCML_I64( "vpunpckhdq ymm0,ymm0,ymmword ptr [rax]", 0xc5, 0xfd, 0x6a, 0x00 );
    FCML_I32( "vpunpckhdq ymm0,ymm0,ymm1", 0xc5, 0xfd, 0x6a, 0xc1 );
    // VEX.NDS.256.66.0F.WIG 6D /r VPUNPCKHQDQ ymm1,ymm2,ymm3/m256
    FCML_I64( "vpunpckhqdq ymm0,ymm0,ymmword ptr [rax]", 0xc5, 0xfd, 0x6d, 0x00 );
    FCML_I32( "vpunpckhqdq ymm0,ymm0,ymm1", 0xc5, 0xfd, 0x6d, 0xc1 );
}

void fcml_tf_instruction_PUSH(void) {
    // FF /6 PUSH r/m16 M Valid Valid Push r/m16.
    // FF /6 PUSH r/m32 M N.E. Valid Push r/m32.
    // FF /6 PUSH r/m64 M Valid N.E. Push r/m64.
    // 32 BIT.
    FCML_I32( "push dword ptr [eax]", 0xFF, 0x30 );
    FCML_I32_M( "push ecx", 2, FCML_MI( 0x51 ), FCML_MI( 0xff, 0xf1 ) );
    FCML_I32( "push word ptr [eax]", 0x66, 0xFF, 0x30 );
    FCML_I32_M( "push cx", 2, FCML_MI( 0x66, 0x51 ), FCML_MI( 0x66, 0xff, 0xf1 ) );
    FCML_I32( "push dword ptr [bx+si]", 0x67, 0xFF, 0x30 );
    FCML_I32_D( "push ecx", 0x67, 0xFF, 0xF1 );
    FCML_I32( "push word ptr [bx+si]", 0x66, 0x67, 0xFF, 0x30 );
    FCML_I32_D( "push cx", 0x66, 0x67, 0xFF, 0xF1 );
    // 64 BIT.
    FCML_I64( "push qword ptr [rax]", 0xFF, 0x30 );
    FCML_I64_M( "push rcx", 2, FCML_MI( 0x51 ), FCML_MI( 0xff, 0xf1 ) );
    FCML_I64( "push word ptr [rax]", 0x66, 0xFF, 0x30 );
    FCML_I64_M( "push cx", 2, FCML_MI( 0x66, 0x51 ), FCML_MI( 0x66, 0xff, 0xf1 ) );
    FCML_I64( "push qword ptr [eax]", 0x67, 0xFF, 0x30 );
    FCML_I64_D( "push rcx", 0x67, 0xFF, 0xF1 );
    FCML_I64( "push word ptr [eax]", 0x66, 0x67, 0xFF, 0x30 );
    FCML_I64_D( "push cx", 0x66, 0x67, 0xFF, 0xF1 );
    FCML_I64_D( "push qword ptr [rax]", 0x48, 0xFF, 0x30 );
    FCML_I64_D( "push rcx", 0x48, 0xFF, 0xF1 );
    // 50+rw PUSH r16 O Valid Valid Push r16.
    // 50+rd PUSH r32 O N.E. Valid Push r32.
    // 50+rd PUSH r64 O Valid N.E. Push r64.
    FCML_I32_M( "push eax", 2, FCML_MI( 0x50 ), FCML_MI( 0xff, 0xf0 ) );
    FCML_I32_M( "push ax", 2, FCML_MI( 0x66, 0x50 ), FCML_MI( 0x66, 0xff, 0xf0 ) );
    FCML_I32_D( "push eax", 0x67, 0x50 );
    FCML_I64_M( "push rax", 2, FCML_MI( 0x50 ), FCML_MI( 0xff, 0xf0 ) );
    FCML_I64_M( "push ax", 2, FCML_MI( 0x66, 0x50 ), FCML_MI( 0x66, 0xff, 0xf0 ) );
    FCML_I64_D( "push rax", 0x67, 0x50 );
    FCML_I64_D( "push rax", 0x48, 0x50 );
    // 6A PUSH imm8 I Valid Valid Push imm8.
    // 68 PUSH imm16 I Valid Valid Push imm16.
    // 68 PUSH imm32 I Valid Valid Push imm32.
    // TODO: Should be checked with disassembler other than WinDBG.
    FCML_I32_M( "push 0ffffffffh", 2, FCML_MI( 0x68, 0xff, 0xff, 0xff, 0xff ), FCML_MI( 0x6a, 0xff ) );
    FCML_I32_M( "push 00000020h", 3, FCML_MI( 0x68, 0x20, 0x00, 0x00, 0x00 ), FCML_MI( 0x66, 0x68, 0x20, 0x00 ), FCML_MI( 0x6a, 0x20 ) );
    FCML_I32_M( "push 0ffffh", 3, FCML_MI( 0x66, 0x68, 0xff, 0xff ), FCML_MI( 0x68, 0xff, 0xff, 0x00, 0x00 ), FCML_MI( 0x66, 0x6a, 0xff ) );
    FCML_I32( "push 50402020h", 0x68, 0x20, 0x20, 0x40, 0x50 );
    FCML_I32( "push 11ff20ffh", 0x68, 0xFF, 0x20, 0xFF, 0x11 );
    FCML_I32_M( "push 11ffh", 2, FCML_MI( 0x66, 0x68, 0xff, 0x11 ), FCML_MI( 0x68, 0xff, 0x11, 0x00, 0x00 ) );
    FCML_I64_M( "push 11ffh", 2, FCML_MI( 0x66, 0x68, 0xff, 0x11 ), FCML_MI( 0x68, 0xff, 0x11, 0x00, 0x00 ) );
    FCML_I64( "push 221111ffh", 0x68, 0xFF, 0x11, 0x11, 0x22 );
    FCML_I64_D( "push 00000000221111ffh", 0x48, 0x68, 0xFF, 0x11, 0x11, 0x22 );
    FCML_I64( "push 221111ffh", 0x68, 0xff, 0x11, 0x11, 0x22 );
    FCML_I64( "push 0ff1111ffh", 0x68, 0xFF, 0x11, 0x11, 0xFF );
    FCML_I64( "push 0ffffffffff1111ffh", 0x48, 0x68, 0xFF, 0x11, 0x11, 0xFF );
    // 0E PUSH CS NP Invalid Valid Push CS.
    // 16 PUSH SS NP Invalid Valid Push SS.
    // 1E PUSH DS NP Invalid Valid Push DS.
    // 06 PUSH ES NP Invalid Valid Push ES.
    FCML_I32( "push cs", 0x0e );
    FCML_I32( "push ss", 0x16 );
    FCML_I32( "push ds", 0x1e );
    FCML_I32( "push es", 0x06 );
    FCML_I64_FAILED( "push cs", 0x0e );
    FCML_I64_FAILED( "push ss", 0x16 );
    FCML_I64_FAILED( "push ds", 0x1e );
    FCML_I64_FAILED( "push es", 0x06 );
    // 0F A0 PUSH FS NP Valid Valid Push FS.
    // 0F A8 PUSH GS NP Valid Valid Push GS.
    FCML_I32( "push fs", 0x0f, 0xa0 );
    FCML_I32( "push gs", 0x0f, 0xa8 );
    FCML_I64( "push fs", 0x0f, 0xa0 );
    FCML_I64( "push gs", 0x0f, 0xa8 );
}

void fcml_tf_instruction_PUSHA(void) {
    // 60 PUSHA NP Invalid Valid Push AX, CX, DX, BX, original SP, BP, SI, and DI.
    // 60 PUSHAD NP Invalid Valid Push EAX, ECX, EDX, EBX, original ESP, EBP, ESI, and EDI.
    FCML_I32( "pushad", 0x60 );
    FCML_I64_FAILED( "pushad", 0x60 );
    FCML_I32( "pusha", 0x66, 0x60 );
}

void fcml_tf_instruction_PUSHF(void) {
    // 9C PUSHF NP Valid Valid Push lower 16 bits of EFLAGS.
    FCML_I32( "pushf", 0x66, 0x9C );
    FCML_I64( "pushf", 0x66, 0x9C );
    // 9C PUSHFD NP N.E. Valid Push EFLAGS.
    FCML_I32( "pushfd", 0x9C );
    FCML_I64_FAILED( "pushfd", 0x9C );
    // 9C PUSHFQ NP Valid N.E. Push RFLAGS.
    FCML_I64( "pushfq", 0x48, 0x9C );
}

void fcml_tf_instruction_PXOR(void) {
    // 0F EF /r PXOR mm,mm/m64
    FCML_I64( "pxor mm0,mmword ptr [rax]", 0x0F, 0xEF, 0x00 );
    FCML_I32( "pxor mm0,mm1", 0x0F, 0xEF, 0xC1 );
    // 66 0F EF /r PXOR xmm1,xmm2/m128
    FCML_I64( "pxor xmm0,xmmword ptr [rax]", 0x66, 0x0F, 0xEF, 0x00 );
    FCML_I32( "pxor xmm0,xmm1", 0x66, 0x0F, 0xEF, 0xC1 );
    // VEX.NDS.128.66.0F.WIG EF /r VPXOR xmm1,xmm2,xmm3/m128
    FCML_I64( "vpxor xmm0,xmm0,xmmword ptr [rax]", 0xc5, 0xf9, 0xef, 0x00 );
    FCML_I32( "vpxor xmm0,xmm0,xmm1", 0xc5, 0xf9, 0xef, 0xc1 );
    // VEX.NDS.256.66.0F.WIG EF /r VPXOR ymm1,ymm2,ymm3/m256
    FCML_I64( "vpxor ymm0,ymm0,ymmword ptr [rax]", 0xc5, 0xfd, 0xef, 0x00 );
    FCML_I32( "vpxor ymm0,ymm0,ymm1", 0xc5, 0xfd, 0xef, 0xc1 );
}

void fcml_tf_instruction_PAVGUSB(void) {
    // PAVGUSB mmreg1, mmreg2/mem64 0F 0Fh / BFh Average of unsigned packed 8-bit values
    FCML_I32( "pavgusb mm0,mmword ptr [eax]", 0x0F, 0x0F, 0xBF, 0x00 );
    FCML_I64( "pavgusb mm0,mm1", 0x0F, 0x0F, 0xBF, 0xC1 );
}

void fcml_tf_instruction_PF2ID(void) {
    // PF2ID mmreg1, mmreg2/mem64 0Fh 0Fh / 1Dh Converts packed floating-point operand to packed 32-bit integer
    FCML_I32( "pf2id mm0,mmword ptr [eax]", 0x0F, 0x0F, 0x1D, 0x00 );
    FCML_I64( "pf2id mm0,mm1", 0x0F, 0x0F, 0x1D, 0xC1 );
}

void fcml_tf_instruction_PFACC(void) {
    // PFACC mmreg1, mmreg2/mem64 0Fh 0Fh / AEh Floating-point accumulate
    FCML_I32( "pfacc mm0,mmword ptr [eax]", 0x0F, 0x0F, 0xAE, 0x00 );
    FCML_I64( "pfacc mm0,mm1", 0x0F, 0x0F, 0xAE, 0xC1 );
}

void fcml_tf_instruction_PFADD(void) {
    // PFADD mmreg1, mmreg2/mem64 0Fh 0Fh / 9Eh Packed, floating-point addition
    FCML_I32( "pfadd mm0,mmword ptr [eax]", 0x0F, 0x0F, 0x9E, 0x00 );
    FCML_I64( "pfadd mm0,mm1", 0x0F, 0x0F, 0x9E, 0xC1 );
}

void fcml_tf_instruction_PFCMPEQ(void) {
    // PFCMPEQ mmreg1, mmreg2/mem64 0Fh 0Fh / B0h Packed floating-point comparison, equal to
    FCML_I32( "pfcmpeq mm0,mmword ptr [eax]", 0x0F, 0x0F, 0xB0, 0x00 );
    FCML_I64( "pfcmpeq mm0,mm1", 0x0F, 0x0F, 0xB0, 0xC1 );
}

void fcml_tf_instruction_PFCMPGE(void) {
    // PFCMPGE mmreg1, mmreg2/mem64 0Fh 0Fh / 90h Packed floating-point comparison, greater than or equal to
    FCML_I32( "pfcmpge mm0,mmword ptr [eax]", 0x0F, 0x0F, 0x90, 0x00 );
    FCML_I64( "pfcmpge mm0,mm1", 0x0F, 0x0F, 0x90, 0xC1 );
}

void fcml_tf_instruction_PFCMPGT(void) {
    // PFCMPGT mmreg1, mmreg2/mem64 0Fh 0Fh / A0h Packed floating-point comparison, greater than
    FCML_I32( "pfcmpgt mm0,mmword ptr [eax]", 0x0F, 0x0F, 0xA0, 0x00 );
    FCML_I64( "pfcmpgt mm0,mm1", 0x0F, 0x0F, 0xA0, 0xC1 );
}

void fcml_tf_instruction_PFMAX(void) {
    // PFMAX mmreg1, mmreg2/mem64 0Fh 0Fh / A4h Packed floating-point maximum
    FCML_I32( "pfmax mm0,mmword ptr [eax]", 0x0F, 0x0F, 0xA4, 0x00 );
    FCML_I64( "pfmax mm0,mm1", 0x0F, 0x0F, 0xA4, 0xC1 );
}

void fcml_tf_instruction_PFMIN(void) {
    // PFMIN mmreg1, mmreg2/mem64 0Fh 0Fh / 94h Packed floating-point minimum
    FCML_I32( "pfmin mm0,mmword ptr [eax]", 0x0F, 0x0F, 0x94, 0x00 );
    FCML_I64( "pfmin mm0,mm1", 0x0F, 0x0F, 0x94, 0xC1 );
}

void fcml_tf_instruction_PFMUL(void) {
    // PFMUL mmreg1, mmreg2/mem64 0Fh 0Fh / B4h Packed floating-point multiplication
    FCML_I32( "pfmul mm0,mmword ptr [eax]", 0x0F, 0x0F, 0xB4, 0x00 );
    FCML_I64( "pfmul mm0,mm1", 0x0F, 0x0F, 0xB4, 0xC1 );
}

void fcml_tf_instruction_PFRCP(void) {
    // PFRCP mmreg1, mmreg2/mem64 0Fh 0Fh / 96h Floating-point reciprocal approximation
    FCML_I32( "pfrcp mm0,mmword ptr [eax]", 0x0F, 0x0F, 0x96, 0x00 );
    FCML_I64( "pfrcp mm0,mm1", 0x0F, 0x0F, 0x96, 0xC1 );
}

void fcml_tf_instruction_PFRCPIT1(void) {
    // PFRCPIT1 mmreg1, mmreg2/mem64 0Fh 0Fh / A6h Packed floating-point reciprocal, first iteration step
    FCML_I32( "pfrcpit1 mm0,mmword ptr [eax]", 0x0F, 0x0F, 0xA6, 0x00 );
    FCML_I64( "pfrcpit1 mm0,mm1", 0x0F, 0x0F, 0xA6, 0xC1 );
}

void fcml_tf_instruction_PFRCPIT2(void) {
    // PFRCPIT2 mmreg1, mmreg2/mem64 0Fh 0Fh / B6h Packed floating-point reciprocal/reciprocal square root, second iteration step
    FCML_I32( "pfrcpit2 mm0,mmword ptr [eax]", 0x0F, 0x0F, 0xB6, 0x00 );
    FCML_I64( "pfrcpit2 mm0,mm1", 0x0F, 0x0F, 0xB6, 0xC1 );
}

void fcml_tf_instruction_PFRSQIT1(void) {
    // PFRSQIT1 mmreg1, mmreg2/mem64 0Fh 0Fh / A7h Packed floating-point reciprocal square root, first iteration step
    FCML_I32( "pfrsqit1 mm0,mmword ptr [eax]", 0x0F, 0x0F, 0xA7, 0x00 );
    FCML_I64( "pfrsqit1 mm0,mm1", 0x0F, 0x0F, 0xA7, 0xC1 );
}

void fcml_tf_instruction_PFRSQRT(void) {
    // PFRSQRT mmreg1, mmreg2/mem64 0Fh 0Fh / 97h Floating-point reciprocal square root approximation
    FCML_I32( "pfrsqrt mm0,mmword ptr [eax]", 0x0F, 0x0F, 0x97, 0x00 );
    FCML_I64( "pfrsqrt mm0,mm1", 0x0F, 0x0F, 0x97, 0xC1 );
}

void fcml_tf_instruction_PFSUB(void) {
    // PFSUB mmreg1, mmreg2/mem64 0Fh 0Fh / 9Ah Packed floating-point subtraction
    FCML_I32( "pfsub mm0,mmword ptr [eax]", 0x0F, 0x0F, 0x9A, 0x00 );
    FCML_I64( "pfsub mm0,mm1", 0x0F, 0x0F, 0x9A, 0xC1 );
}

void fcml_tf_instruction_PFSUBR(void) {
    // PFSUBR mmreg1, mmreg2/mem64 0Fh 0Fh / AAh Packed floating-point reverse subtraction
    FCML_I32( "pfsubr mm0,mmword ptr [eax]", 0x0F, 0x0F, 0xAA, 0x00 );
    FCML_I64( "pfsubr mm0,mm1", 0x0F, 0x0F, 0xAA, 0xC1 );
}

void fcml_tf_instruction_PI2FD(void) {
    // PI2FD mmreg1, mmreg2/mem64 0Fh 0Fh / 0Dh Packed 32-bit integer to floating-point conversion
    FCML_I32( "pi2fd mm0,mmword ptr [eax]", 0x0F, 0x0F, 0x0D, 0x00 );
    FCML_I64( "pi2fd mm0,mm1", 0x0F, 0x0F, 0x0D, 0xC1 );
}

void fcml_tf_instruction_PMULHRW(void) {
    // PMULHRW mmreg1, mmreg2/mem64 0F 0Fh/B7h Multiply signed packed 16-bit values with rounding and store the high 16 bits.
    FCML_I32( "pmulhrw mm0,mmword ptr [eax]", 0x0F, 0x0F, 0xB7, 0x00 );
    FCML_I64( "pmulhrw mm0,mm1", 0x0F, 0x0F, 0xB7, 0xC1 );
}

void fcml_tf_instruction_PREFETCH(void) {
    // PREFETCH(W) mem8 0F 0Dh Prefetch processor cache line into L1 data cache (Dcache)
    FCML_I32( "prefetch byte ptr [eax]", 0x0F, 0x0D, 0x00 );
    FCML_I64( "prefetchw byte ptr [rax]", 0x0F, 0x0D, 0x08 );
}

void fcml_tf_instruction_PF2IW(void) {
    // PF2IW mmreg1, mmreg2/mem64 0Fh 0Fh / 1Ch Packed floating-point to integer word conversion with PF2IW sign extend
    FCML_I32( "pf2iw mm0,mmword ptr [eax]", 0x0F, 0x0F, 0xC1, 0x00 );
    FCML_I64( "pf2iw mm0,mm1", 0x0F, 0x0F, 0xC1, 0xC1 );
}

void fcml_tf_instruction_PFNACC(void) {
    // PFNACC mmreg1, mmreg2/mem64 0Fh 0Fh / 8Ah Packed floating-point negative accumulate
    FCML_I32( "pfnacc mm0,mmword ptr [eax]", 0x0F, 0x0F, 0x8A, 0x00 );
    FCML_I64( "pfnacc mm0,mm1", 0x0F, 0x0F, 0x8A, 0xC1 );
}

void fcml_tf_instruction_PFPNACC(void) {
    // PFPNACC mmreg1, mmreg2/mem64 0Fh 0Fh / 8Eh Packed floating-point mixed positive-negative accumulate
    FCML_I32( "pfpnacc mm0,mmword ptr [eax]", 0x0F, 0x0F, 0x8E, 0x00 );
    FCML_I64( "pfpnacc mm0,mm1", 0x0F, 0x0F, 0x8E, 0xC1 );
}

void fcml_tf_instruction_PI2FW(void) {
    // PI2FW mmreg1, mmreg2/mem64 0Fh 0Fh / 0Ch Packed 16-bit integer to floating-point conversion
    FCML_I32( "pi2fw mm0,mmword ptr [eax]", 0x0F, 0x0F, 0x0C, 0x00 );
    FCML_I64( "pi2fw mm0,mm1", 0x0F, 0x0F, 0x0C, 0xC1 );
}

void fcml_tf_instruction_PSWAPD(void) {
    // PSWAPD mmreg1, mmreg2/mem64 0Fh 0Fh / BBh Packed swap doubleword
    FCML_I32( "pswapd mm0,mmword ptr [eax]", 0x0F, 0x0F, 0xBB, 0x00 );
    FCML_I64( "pswapd mm0,mm1", 0x0F, 0x0F, 0xBB, 0xC1 );
}

void fcml_tf_instruction_PDEP(void) {
    // VEX.NDS.LZ.F2.0F38.W0 F5 /r PDEP r32a, r32b, r/m32
    FCML_I32( "pdep eax,edi,dword ptr [eax]", 0xC4, 0xE2, 0x43, 0xF5, 0x00 );
    FCML_I32( "pdep eax,edi,eax", 0xC4, 0xE2, 0x43, 0xF5, 0xC0 );
    // VEX.NDS.LZ.F2.0F38.W1 F5 /r PDEP r64a, r64b, r/m64
    FCML_I64( "pdep rax,rdi,qword ptr [rax]", 0xC4, 0xE2, 0xC3, 0xF5, 0x00 );
    FCML_I64( "pdep rax,rdi,rax", 0xC4, 0xE2, 0xC3, 0xF5, 0xC0 );
}

void fcml_tf_instruction_PEXT(void) {
    // VEX.NDS.LZ.F3.0F38.W0 F5 /r PEXT r32a, r32b, r/m32
    FCML_I32( "pext eax,edi,dword ptr [eax]", 0xC4, 0xE2, 0x42, 0xF5, 0x00 );
    FCML_I32( "pext eax,edi,eax", 0xC4, 0xE2, 0x42, 0xF5, 0xC0 );
    // VEX.NDS.LZ.F3.0F38.W1 F5 /r PEXT r64a, r64b, r/m64
    FCML_I64( "pext rax,rdi,qword ptr [rax]", 0xC4, 0xE2, 0xC2, 0xF5, 0x00 );
    FCML_I64( "pext rax,rdi,rax", 0xC4, 0xE2, 0xC2, 0xF5, 0xC0 );
}

CU_TestInfo fctl_ti_instructions_p[] = {
    { "fcml_tf_instruction_PABS", fcml_tf_instruction_PABS },
    { "fcml_tf_instruction_PACKSS", fcml_tf_instruction_PACKSS },
    { "fcml_tf_instruction_PACKUSD", fcml_tf_instruction_PACKUSD },
    { "fcml_tf_instruction_PACKUSW", fcml_tf_instruction_PACKUSW },
    { "fcml_tf_instruction_PADD", fcml_tf_instruction_PADD },
    { "fcml_tf_instruction_PADDS", fcml_tf_instruction_PADDS },
    { "fcml_tf_instruction_PADDUS", fcml_tf_instruction_PADDUS },
    { "fcml_tf_instruction_PADDQ", fcml_tf_instruction_PADDQ },
    { "fcml_tf_instruction_PALIGNR", fcml_tf_instruction_PALIGNR },
    { "fcml_tf_instruction_PAND", fcml_tf_instruction_PAND },
    { "fcml_tf_instruction_PANDN", fcml_tf_instruction_PANDN },
    { "fcml_tf_instruction_PAUSE", fcml_tf_instruction_PAUSE },
    { "fcml_tf_instruction_PAVGB", fcml_tf_instruction_PAVGB },
    { "fcml_tf_instruction_PBLENDVB", fcml_tf_instruction_PBLENDVB },
    { "fcml_tf_instruction_PBLENDW", fcml_tf_instruction_PBLENDW },
    { "fcml_tf_instruction_PCLMULQDQ", fcml_tf_instruction_PCLMULQDQ },
    { "fcml_tf_instruction_PCMPEQ", fcml_tf_instruction_PCMPEQ },
    { "fcml_tf_instruction_PCMPEQQ", fcml_tf_instruction_PCMPEQQ },
    { "fcml_tf_instruction_PCMPESTRI", fcml_tf_instruction_PCMPESTRI },
    { "fcml_tf_instruction_PCMPESTRM", fcml_tf_instruction_PCMPESTRM },
    { "fcml_tf_instruction_PCMPGT", fcml_tf_instruction_PCMPGT },
    { "fcml_tf_instruction_PCMPGTQ", fcml_tf_instruction_PCMPGTQ },
    { "fcml_tf_instruction_PCMPISTRI", fcml_tf_instruction_PCMPISTRI },
    { "fcml_tf_instruction_PCMPISTRM", fcml_tf_instruction_PCMPISTRM },
    { "fcml_tf_instruction_PEXTRB", fcml_tf_instruction_PEXTRB },
    { "fcml_tf_instruction_PEXTRW", fcml_tf_instruction_PEXTRW },
    { "fcml_tf_instruction_PHADDW", fcml_tf_instruction_PHADDW },
    { "fcml_tf_instruction_PHADDSW", fcml_tf_instruction_PHADDSW },
    { "fcml_tf_instruction_PHMINPOSUW", fcml_tf_instruction_PHMINPOSUW },
    { "fcml_tf_instruction_PHSUBW", fcml_tf_instruction_PHSUBW },
    { "fcml_tf_instruction_PHSUBSW", fcml_tf_instruction_PHSUBSW },
    { "fcml_tf_instruction_PINSR", fcml_tf_instruction_PINSR },
    { "fcml_tf_instruction_PINSRW", fcml_tf_instruction_PINSRW },
    { "fcml_tf_instruction_PMADDUBSW", fcml_tf_instruction_PMADDUBSW },
    { "fcml_tf_instruction_PMADDWD", fcml_tf_instruction_PMADDWD },
    { "fcml_tf_instruction_PMAXSB", fcml_tf_instruction_PMAXSB },
    { "fcml_tf_instruction_PMAXSW", fcml_tf_instruction_PMAXSW },
    { "fcml_tf_instruction_PMAXSD", fcml_tf_instruction_PMAXSD },
    { "fcml_tf_instruction_PMAXUB", fcml_tf_instruction_PMAXUB },
    { "fcml_tf_instruction_PMAXUW", fcml_tf_instruction_PMAXUW },
    { "fcml_tf_instruction_PMAXUD", fcml_tf_instruction_PMAXUD },
    { "fcml_tf_instruction_PMINSB", fcml_tf_instruction_PMINSB },
    { "fcml_tf_instruction_PMINSW", fcml_tf_instruction_PMINSW },
    { "fcml_tf_instruction_PMINSD", fcml_tf_instruction_PMINSD },
    { "fcml_tf_instruction_PMINUB", fcml_tf_instruction_PMINUB },
    { "fcml_tf_instruction_PMINUW", fcml_tf_instruction_PMINUW },
    { "fcml_tf_instruction_PMINUD", fcml_tf_instruction_PMINUD },
    { "fcml_tf_instruction_PMOVMSKB", fcml_tf_instruction_PMOVMSKB },
    { "fcml_tf_instruction_PMOVSX", fcml_tf_instruction_PMOVSX },
    { "fcml_tf_instruction_PMOVZX", fcml_tf_instruction_PMOVZX },
    { "fcml_tf_instruction_PMULDQ", fcml_tf_instruction_PMULDQ },
    { "fcml_tf_instruction_PMULHRSW", fcml_tf_instruction_PMULHRSW },
    { "fcml_tf_instruction_PMULHUW", fcml_tf_instruction_PMULHUW },
    { "fcml_tf_instruction_PMULHW", fcml_tf_instruction_PMULHW },
    { "fcml_tf_instruction_PMULUDQ", fcml_tf_instruction_PMULUDQ },
    { "fcml_tf_instruction_PMULLW", fcml_tf_instruction_PMULLW },
    { "fcml_tf_instruction_PMULLD", fcml_tf_instruction_PMULLD },
    { "fcml_tf_instruction_POP", fcml_tf_instruction_POP },
    { "fcml_tf_instruction_POPA", fcml_tf_instruction_POPA },
    { "fcml_tf_instruction_POPCNT", fcml_tf_instruction_POPCNT },
    { "fcml_tf_instruction_POPF", fcml_tf_instruction_POPF },
    { "fcml_tf_instruction_POR", fcml_tf_instruction_POR },
    { "fcml_tf_instruction_PREFETCHT", fcml_tf_instruction_PREFETCHT },
    { "fcml_tf_instruction_PSADBW", fcml_tf_instruction_PSADBW },
    { "fcml_tf_instruction_PSHUFB", fcml_tf_instruction_PSHUFB },
    { "fcml_tf_instruction_PSHUFD", fcml_tf_instruction_PSHUFD },
    { "fcml_tf_instruction_PSHUFHW", fcml_tf_instruction_PSHUFHW },
    { "fcml_tf_instruction_PSHUFLW", fcml_tf_instruction_PSHUFLW },
    { "fcml_tf_instruction_PSHUFW", fcml_tf_instruction_PSHUFW },
    { "fcml_tf_instruction_PSIGN", fcml_tf_instruction_PSIGN },
    { "fcml_tf_instruction_PSLLDQ", fcml_tf_instruction_PSLLDQ },
    { "fcml_tf_instruction_PSLL", fcml_tf_instruction_PSLL },
    { "fcml_tf_instruction_PSRA", fcml_tf_instruction_PSRA },
    { "fcml_tf_instruction_PSRLDQ", fcml_tf_instruction_PSRLDQ },
    { "fcml_tf_instruction_PSRL", fcml_tf_instruction_PSRL },
    { "fcml_tf_instruction_PSUB", fcml_tf_instruction_PSUB },
    { "fcml_tf_instruction_PSUBQ", fcml_tf_instruction_PSUBQ },
    { "fcml_tf_instruction_PSUBS", fcml_tf_instruction_PSUBS },
    { "fcml_tf_instruction_PSUBUS", fcml_tf_instruction_PSUBUS },
    { "fcml_tf_instruction_PTEST", fcml_tf_instruction_PTEST },
    { "fcml_tf_instruction_PUNPCKLB", fcml_tf_instruction_PUNPCKLB },
    { "fcml_tf_instruction_PUNPCKHB", fcml_tf_instruction_PUNPCKHB },
    { "fcml_tf_instruction_PUSH", fcml_tf_instruction_PUSH },
    { "fcml_tf_instruction_PUSHA", fcml_tf_instruction_PUSHA },
    { "fcml_tf_instruction_PUSHF", fcml_tf_instruction_PUSHF },
    { "fcml_tf_instruction_PXOR", fcml_tf_instruction_PXOR },
    { "fcml_tf_instruction_PAVGUSB", fcml_tf_instruction_PAVGUSB },
    { "fcml_tf_instruction_PF2ID", fcml_tf_instruction_PF2ID },
    { "fcml_tf_instruction_PFACC", fcml_tf_instruction_PFACC },
    { "fcml_tf_instruction_PFADD", fcml_tf_instruction_PFADD },
    { "fcml_tf_instruction_PFCMPEQ", fcml_tf_instruction_PFCMPEQ },
    { "fcml_tf_instruction_PFCMPGE", fcml_tf_instruction_PFCMPGE },
    { "fcml_tf_instruction_PFCMPGT", fcml_tf_instruction_PFCMPGT },
    { "fcml_tf_instruction_PFMAX", fcml_tf_instruction_PFMAX },
    { "fcml_tf_instruction_PFMIN", fcml_tf_instruction_PFMIN },
    { "fcml_tf_instruction_PFMUL", fcml_tf_instruction_PFMUL },
    { "fcml_tf_instruction_PFRCP", fcml_tf_instruction_PFRCP },
    { "fcml_tf_instruction_PFRCPIT1", fcml_tf_instruction_PFRCPIT1 },
    { "fcml_tf_instruction_PFRCPIT2", fcml_tf_instruction_PFRCPIT2 },
    { "fcml_tf_instruction_PFRSQIT1", fcml_tf_instruction_PFRSQIT1 },
    { "fcml_tf_instruction_PFRSQRT", fcml_tf_instruction_PFRSQRT },
    { "fcml_tf_instruction_PFSUB", fcml_tf_instruction_PFSUB },
    { "fcml_tf_instruction_PFSUBR", fcml_tf_instruction_PFSUBR },
    { "fcml_tf_instruction_PI2FD", fcml_tf_instruction_PI2FD },
    { "fcml_tf_instruction_PMULHRW", fcml_tf_instruction_PMULHRW },
    { "fcml_tf_instruction_PREFETCH", fcml_tf_instruction_PREFETCH },
    { "fcml_tf_instruction_PF2IW", fcml_tf_instruction_PF2IW },
    { "fcml_tf_instruction_PFNACC", fcml_tf_instruction_PFNACC },
    { "fcml_tf_instruction_PFPNACC", fcml_tf_instruction_PFPNACC },
    { "fcml_tf_instruction_PI2FW", fcml_tf_instruction_PI2FW },
    { "fcml_tf_instruction_PSWAPD", fcml_tf_instruction_PSWAPD },
    { "fcml_tf_instruction_PDEP", fcml_tf_instruction_PDEP },
    { "fcml_tf_instruction_PEXT", fcml_tf_instruction_PEXT },
    CU_TEST_INFO_NULL,
};

CU_SuiteInfo fctl_si_instructions_p[] = {
    { "suite-fctl_ti_instructions_p", fcml_tf_instructions_p_suite_init, fcml_tf_instructions_p_suite_cleanup, fctl_ti_instructions_p },
    CU_SUITE_INFO_NULL,
};
