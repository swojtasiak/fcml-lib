/*
 * instructions.c
 *
 *  Created on: 01-06-2013
 *      Author: tAs
 */

#include "fcml_env.h"
#include "fcml_assembler.h"
#include "instructions_n_t.h"

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
    FCML_I32( "vpmovmskb eax,xmm0", 0xC4, 0xE1, 0x79, 0xD7, 0xC1 );
    FCML_I64( "vpmovmskb rax,xmm0", 0xC4, 0xE1, 0x79, 0xD7, 0xC1 );
    // VEX.256.66.0F.WIG D7 /r VPMOVMSKB reg,ymm1
    FCML_I32( "vpmovmskb eax,ymm0", 0xC4, 0xE1, 0x7D, 0xD7, 0xC1 );
    FCML_I64( "vpmovmskb rax,ymm0", 0xC4, 0xE1, 0x7D, 0xD7, 0xC1 );
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
    CU_TEST_INFO_NULL,
};

CU_SuiteInfo fctl_si_instructions_p[] = {
    { "suite-fctl_ti_instructions_p", fcml_tf_instructions_p_suite_init, fcml_tf_instructions_p_suite_cleanup, fctl_ti_instructions_p },
    CU_SUITE_INFO_NULL,
};
