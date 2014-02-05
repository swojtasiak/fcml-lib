/*
 * instructions.c
 *
 *  Created on: 01-06-2013
 *      Author: tAs
 */

#include <fcml_assembler.h>
#include "instructions_v_t.h"
#include "instructions_base_t.h"

void fcml_tf_instructions_v_suite_init(void) {
}

void fcml_tf_instructions_v_suite_cleanup(void) {
}

void fcml_tf_instruction_VBROADCASTSS(void) {
    /* VEX.128.66.0F38 18 /r VBROADCASTSS xmm1, m32*/
    /* VEX.256.66.0F38 18 /r VBROADCASTSS ymm1, m32*/
    FCML_I32( "vbroadcastss xmm2,dword ptr [ecx+eax]", 0xc4, 0xe2, 0x79, 0x18, 0x14, 0x01 );
    FCML_I32( "vbroadcastss ymm2,dword ptr [ecx+eax]", 0xc4, 0xe2, 0x7d, 0x18, 0x14, 0x01 );
    /* VEX.256.66.0F38 19 /r VBROADCASTSD ymm1, m64*/
    FCML_I32_FAILED( "FAIL", 0xC4, 0xE2, 0x49, 0x19, 0x14, 0x01 );
    FCML_I32( "vbroadcastsd ymm2,mmword ptr [ecx+eax]", 0xC4, 0xE2, 0x7D, 0x19, 0x14, 0x01 );
    /* VEX.256.66.0F38.W0 1A /r VBROADCASTF128 ymm1,m128*/
    FCML_I32( "vbroadcastf128 ymm2,oword ptr [ecx+eax]", 0xC4, 0xE2, 0x7D, 0x1A, 0x14, 0x01 );
    /* VEX.256.66.0F38.W0 5A /r VBROADCASTI128 ymm1,m128*/
    FCML_I32( "vbroadcasti128 ymm2,oword ptr [ecx+eax]", 0xC4, 0xE2, 0x7D, 0x5A, 0x14, 0x01 );
    /* VEX.128.66.0F38.W0 18 /r VBROADCASTSS xmm1,xmm2*/
    /* VEX.256.66.0F38.W0 18 /r VBROADCASTSS ymm1,xmm2*/
    FCML_I32( "vbroadcastss xmm0,xmm1", 0xC4, 0xE2, 0x79, 0x18, 0xC1 );
    FCML_I32( "vbroadcastss ymm0,xmm1", 0xC4, 0xE2, 0x7D, 0x18, 0xC1 );
    /* VEX.256.66.0F38.W0 19 /r VBROADCASTSD ymm1,xmm2*/
    FCML_I32( "vbroadcastsd ymm0,xmm1", 0xC4, 0xE2, 0x7D, 0x19, 0xC1 );
    /* GAS*/
    FCML_A64( "vbroadcastss (%rcx,%rax),%xmm2", 0xc4, 0xe2, 0x79, 0x18, 0x14, 0x01 );
    FCML_A64( "vbroadcastss (%rcx,%rax),%ymm2", 0xc4, 0xe2, 0x7d, 0x18, 0x14, 0x01 );
    FCML_A64( "vbroadcastsd (%rcx,%rax),%ymm2", 0xc4, 0xe2, 0x7d, 0x19, 0x14, 0x01 );
    FCML_A64( "vbroadcastf128 (%rcx,%rax),%ymm2", 0xc4, 0xe2, 0x7d, 0x1a, 0x14, 0x01 );
    FCML_A64( "vbroadcasti128 (%rcx,%rax),%ymm2", 0xc4, 0xe2, 0x7d, 0x5a, 0x14, 0x01 );
    FCML_A64( "vbroadcastss %xmm1,%xmm0", 0xc4, 0xe2, 0x79, 0x18, 0xc1 );
    FCML_A64( "vbroadcastss %xmm1,%ymm0", 0xc4, 0xe2, 0x7d, 0x18, 0xc1 );
    FCML_A64( "vbroadcastsd %xmm1,%ymm0", 0xc4, 0xe2, 0x7d, 0x19, 0xc1 );
}

void fcml_tf_instruction_VPBROADCASTB(void) {
    /* VEX.128.66.0F38.W0 78 /r VPBROADCASTB xmm1,xmm2/m8*/
    /* VEX.256.66.0F38.W0 78 /r VPBROADCASTB ymm1,xmm2/m8*/
    FCML_I32( "vpbroadcastb xmm0,byte ptr [eax]", 0xC4, 0xE2, 0x79, 0x78, 0x00 );
    FCML_I32( "vpbroadcastb ymm0,byte ptr [eax]", 0xC4, 0xE2, 0x7D, 0x78, 0x00 );
    FCML_I64( "vpbroadcastb xmm0,xmm1", 0xC4, 0xE2, 0x79, 0x78, 0xC1 );
    FCML_I64( "vpbroadcastb ymm0,xmm1", 0xC4, 0xE2, 0x7D, 0x78, 0xC1 );
    /* VEX.128.66.0F38.W0 79 /r VPBROADCASTW xmm1,xmm2/m16*/
    /* VEX.256.66.0F38.W0 79 /r VPBROADCASTW ymm1,xmm2/m16*/
    FCML_I32( "vpbroadcastw xmm0,word ptr [eax]", 0xC4, 0xE2, 0x79, 0x79, 0x00 );
    FCML_I32( "vpbroadcastw ymm0,word ptr [eax]", 0xC4, 0xE2, 0x7D, 0x79, 0x00 );
    FCML_I64( "vpbroadcastw xmm0,xmm1", 0xC4, 0xE2, 0x79, 0x79, 0xC1 );
    FCML_I64( "vpbroadcastw ymm0,xmm1", 0xC4, 0xE2, 0x7D, 0x79, 0xC1 );
    /* VEX.128.66.0F38.W0 58 /r VPBROADCASTD xmm1,xmm2/m32*/
    /* VEX.256.66.0F38.W0 58 /r VPBROADCASTD ymm1,xmm2/m32*/
    FCML_I32( "vpbroadcastd xmm0,dword ptr [eax]", 0xC4, 0xE2, 0x79, 0x58, 0x00 );
    FCML_I32( "vpbroadcastd ymm0,dword ptr [eax]", 0xC4, 0xE2, 0x7D, 0x58, 0x00 );
    FCML_I64( "vpbroadcastd xmm0,xmm1", 0xC4, 0xE2, 0x79, 0x58, 0xC1 );
    FCML_I64( "vpbroadcastd ymm0,xmm1", 0xC4, 0xE2, 0x7D, 0x58, 0xC1 );
    /* VEX.128.66.0F38.W0 59 /r VPBROADCASTQ xmm1,xmm2/m64*/
    /* VEX.256.66.0F38.W0 59 /r VPBROADCASTQ ymm1,xmm2/m64*/
    FCML_I32( "vpbroadcastq xmm0,mmword ptr [eax]", 0xC4, 0xE2, 0x79, 0x59, 0x00 );
    FCML_I32( "vpbroadcastq ymm0,mmword ptr [eax]", 0xC4, 0xE2, 0x7D, 0x59, 0x00 );
    FCML_I64( "vpbroadcastq xmm0,xmm1", 0xC4, 0xE2, 0x79, 0x59, 0xC1 );
    FCML_I64( "vpbroadcastq ymm0,xmm1", 0xC4, 0xE2, 0x7D, 0x59, 0xC1 );
    /* GAS*/
    FCML_A64( "vpbroadcastb %xmm1,%xmm0", 0xc4, 0xe2, 0x79, 0x78, 0xc1 );
    FCML_A64( "vpbroadcastb %xmm1,%ymm0", 0xc4, 0xe2, 0x7d, 0x78, 0xc1 );
    FCML_A64( "vpbroadcastw %xmm1,%xmm0", 0xc4, 0xe2, 0x79, 0x79, 0xc1 );
    FCML_A64( "vpbroadcastw %xmm1,%ymm0", 0xc4, 0xe2, 0x7d, 0x79, 0xc1 );
    FCML_A64( "vpbroadcastd %xmm1,%xmm0", 0xc4, 0xe2, 0x79, 0x58, 0xc1 );
    FCML_A64( "vpbroadcastd %xmm1,%ymm0", 0xc4, 0xe2, 0x7d, 0x58, 0xc1 );
    FCML_A64( "vpbroadcastq %xmm1,%xmm0", 0xc4, 0xe2, 0x79, 0x59, 0xc1 );
    FCML_A64( "vpbroadcastq %xmm1,%ymm0", 0xc4, 0xe2, 0x7d, 0x59, 0xc1 );
    FCML_A64( "vpbroadcastb (%rax),%xmm0", 0xc4, 0xe2, 0x79, 0x78, 0x00 );
    FCML_A64( "vpbroadcastb (%rax),%ymm0", 0xc4, 0xe2, 0x7d, 0x78, 0x00 );
}

void fcml_tf_instruction_VEXTRACTF128(void) {
    /* VEX.256.66.0F3A 19 /r ib VEXTRACTF128 xmm1/m128,ymm2,imm8*/
    FCML_I32( "vextractf128 xmmword ptr [ecx+eax],ymm2,20h", 0xC4, 0xE3, 0x7D, 0x19, 0x14, 0x01, 0x20 );
    FCML_I64( "vextractf128 xmm0,ymm0,20h", 0xC4, 0xE3, 0x7D, 0x19, 0xC0, 0x20 );
    /* GAS*/
    FCML_A64( "vextractf128 $0x20,%ymm2,(%rcx,%rax)", 0xc4, 0xe3, 0x7d, 0x19, 0x14, 0x01, 0x20 );
    FCML_A64( "vextractf128 $0x20,%ymm0,%xmm0", 0xc4, 0xe3, 0x7d, 0x19, 0xc0, 0x20 );
}

void fcml_tf_instruction_VINSERTF128(void) {
    /* VEX.NDS.256.66.0F3A 18 /r ib VINSERTF128 ymm1,ymm2,xmm3/m128,imm8*/
    FCML_I64( "vinsertf128 ymm8,ymm14,xmmword ptr [r8],20h", 0xC4, 0x43, 0x0D, 0x18, 0x00, 0x20 );
    FCML_I32( "vinsertf128 ymm0,ymm6,xmmword ptr [eax],20h", 0xC4, 0xE3, 0x4D, 0x18, 0x00, 0x20 );
    FCML_I32( "vinsertf128 ymm0,ymm6,xmm0,20h", 0xC4, 0xE3, 0x4D, 0x18, 0xC0, 0x20 );
    /* GAS*/
    FCML_A64( "vinsertf128 $0x20,(%r8),%ymm14,%ymm8", 0xc4, 0x43, 0x0d, 0x18, 0x00, 0x20 );
    FCML_A64( "vinsertf128 $0x20,%xmm0,%ymm6,%ymm0", 0xc4, 0xe3, 0x4d, 0x18, 0xc0, 0x20 );
}

void fcml_tf_instruction_VMASKMOVPS_VMASKMOVPD(void) {
    /* VEX.NDS.128.66.0F38 2C /r VMASKMOVPS xmm1,xmm2,m128*/
    /* VEX.NDS.256.66.0F38 2C /r VMASKMOVPS ymm1,ymm2,m256*/
    FCML_I64( "vmaskmovps xmm3,xmm2,xmmword ptr [rax]", 0xC4, 0xE2, 0x69, 0x2C, 0x18 );
    FCML_I32( "vmaskmovps ymm3,ymm2,ymmword ptr [eax]", 0xC4, 0xE2, 0x6D, 0x2C, 0x18 );
    /* GAS*/
    FCML_A64( "vmaskmovps (%rax),%xmm2,%xmm3", 0xc4, 0xe2, 0x69, 0x2c, 0x18 );
    /* VEX.NDS.128.66.0F38 2D /r VMASKMOVPD xmm1,xmm2,m128*/
    /* VEX.NDS.256.66.0F38 2D /r VMASKMOVPD ymm1,ymm2,m256*/
    FCML_I64( "vmaskmovpd xmm3,xmm2,xmmword ptr [rax]", 0xC4, 0xE2, 0x69, 0x2D, 0x18 );
    FCML_I32( "vmaskmovpd ymm3,ymm2,ymmword ptr [eax]", 0xC4, 0xE2, 0x6D, 0x2D, 0x18 );
    /* GAS*/
    FCML_A64( "vmaskmovpd (%rax),%xmm2,%xmm3", 0xc4, 0xe2, 0x69, 0x2d, 0x18 );
    /* VEX.NDS.128.66.0F38 2E /r VMASKMOVPS m128,xmm1,xmm2*/
    /* VEX.NDS.256.66.0F38 2E /r VMASKMOVPS m256,ymm1,ymm2*/
    FCML_I64( "vmaskmovps xmmword ptr [rax],xmm2,xmm3", 0xC4, 0xE2, 0x69, 0x2E, 0x18 );
    FCML_I32( "vmaskmovps ymmword ptr [eax],ymm2,ymm3", 0xC4, 0xE2, 0x6D, 0x2E, 0x18 );
    /* GAS*/
    FCML_A64( "vmaskmovps %xmm3,%xmm2,(%rax)", 0xc4, 0xe2, 0x69, 0x2e, 0x18 );
    /* VEX.NDS.128.66.0F38 2F /r VMASKMOVPD m128,xmm1,xmm2*/
    /* VEX.NDS.256.66.0F38 2F /r VMASKMOVPD m256,ymm1,ymm2*/
    FCML_I64( "vmaskmovpd xmmword ptr [rax],xmm2,xmm3", 0xC4, 0xE2, 0x69, 0x2F, 0x18 );
    FCML_I32( "vmaskmovpd ymmword ptr [eax],ymm2,ymm3", 0xC4, 0xE2, 0x6D, 0x2F, 0x18 );
    /* GAS*/
    FCML_A64( "vmaskmovpd %xmm3,%xmm2,(%rax)", 0xc4, 0xe2, 0x69, 0x2f, 0x18 );
}

void fcml_tf_instruction_VPMASKMOVD_VPMASKMOVQ(void) {
    /* VEX.NDS.128.66.0F38.W0 8C /r VPMASKMOVD xmm1,xmm2,m128*/
    /* VEX.NDS.256.66.0F38.W0 8C /r VPMASKMOVD ymm1,ymm2,m256*/
    /* VEX.NDS.128.66.0F38.W1 8C /r VPMASKMOVQ xmm1,xmm2,m128*/
    /* VEX.NDS.256.66.0F38.W1 8C /r VPMASKMOVQ ymm1,ymm2,m256*/
    FCML_I64( "vpmaskmovd xmm3,xmm2,xmmword ptr [rax]", 0xC4, 0xE2, 0x69, 0x8C, 0x18 );
    FCML_I32( "vpmaskmovd ymm3,ymm2,ymmword ptr [eax]", 0xC4, 0xE2, 0x6D, 0x8C, 0x18 );
    FCML_I64( "vpmaskmovq xmm3,xmm2,xmmword ptr [rax]", 0xC4, 0xE2, 0xE9, 0x8C, 0x18 );
    FCML_I64( "vpmaskmovq ymm3,ymm2,ymmword ptr [rax]", 0xC4, 0xE2, 0xED, 0x8C, 0x18 );
    /* GAS*/
    FCML_A64( "vpmaskmovq (%rax),%xmm2,%xmm3", 0xc4, 0xe2, 0xe9, 0x8c, 0x18 );
    FCML_A64( "vpmaskmovq (%rax),%ymm2,%ymm3", 0xc4, 0xe2, 0xed, 0x8c, 0x18 );
    /* VEX.NDS.128.66.0F38.W0 8E /r VPMASKMOVD m128,xmm1,xmm2*/
    /* VEX.NDS.256.66.0F38.W0 8E /r VPMASKMOVD m256,ymm1,ymm2*/
    /* VEX.NDS.128.66.0F38.W1 8E /r VPMASKMOVQ m128,xmm1,xmm2*/
    /* VEX.NDS.256.66.0F38.W1 8E /r VPMASKMOVQ m256,ymm1,ymm2*/
    FCML_I64( "vpmaskmovd xmmword ptr [rax],xmm2,xmm3", 0xC4, 0xE2, 0x69, 0x8E, 0x18 );
    FCML_I32( "vpmaskmovd ymmword ptr [eax],ymm2,ymm3", 0xC4, 0xE2, 0x6D, 0x8E, 0x18 );
    FCML_I64( "vpmaskmovq xmmword ptr [rax],xmm2,xmm3", 0xC4, 0xE2, 0xE9, 0x8E, 0x18 );
    FCML_I64( "vpmaskmovq ymmword ptr [rax],ymm2,ymm3", 0xC4, 0xE2, 0xED, 0x8E, 0x18 );
    /* GAS*/
    FCML_A64( "vpmaskmovq %xmm3,%xmm2,(%rax)", 0xc4, 0xe2, 0xe9, 0x8e, 0x18 );
    FCML_A64( "vpmaskmovq %ymm3,%ymm2,(%rax)", 0xc4, 0xe2, 0xed, 0x8e, 0x18 );
}

void fcml_tf_instruction_VPBLENDD(void) {
    /* VEX.NDS.128.66.0F3A.W0 02 /r ib VPBLENDD xmm1,xmm2,xmm3/m128,imm8*/
    FCML_I64( "vpblendd xmm0,xmm0,xmmword ptr [rax],0ffh", 0xC4, 0xE3, 0x79, 0x02, 0x00, 0xFF );
    FCML_I32( "vpblendd xmm0,xmm0,xmm1,0ffh", 0xC4, 0xE3, 0x79, 0x02, 0xC1, 0xFF );
    /* VEX.NDS.256.66.0F3A.W0 02 /r ib VPBLENDD ymm1,ymm2,ymm3/m256,imm8*/
    FCML_I64( "vpblendd ymm0,ymm0,ymmword ptr [rax],0ffh", 0xC4, 0xE3, 0x7D, 0x02, 0x00, 0xFF );
    FCML_I32( "vpblendd ymm0,ymm0,ymm1,0ffh", 0xC4, 0xE3, 0x7D, 0x02, 0xC1, 0xFF );
    /* GAS*/
    FCML_A64( "vpblendd $0xff,(%rax),%xmm0,%xmm0", 0xc4, 0xe3, 0x79, 0x02, 0x00, 0xff );
    FCML_A64( "vpblendd $0xff,%xmm1,%xmm0,%xmm0", 0xc4, 0xe3, 0x79, 0x02, 0xc1, 0xff );
    FCML_A64( "vpblendd $0xff,(%rax),%ymm0,%ymm0", 0xc4, 0xe3, 0x7d, 0x02, 0x00, 0xff );
    FCML_A64( "vpblendd $0xff,%ymm1,%ymm0,%ymm0", 0xc4, 0xe3, 0x7d, 0x02, 0xc1, 0xff );
}

void fcml_tf_instruction_VCVTPH2PS(void) {
    /* VEX.128.66.0F38.W0 13 /r VCVTPH2PS xmm1,xmm2/m64 RM V/V F16C Convert four packed half precision (16-bit) floating-point values in xmm2/m64 to packed single-precision floating-point value in xmm1.*/
    FCML_I32( "vcvtph2ps xmm0,mmword ptr [eax]", 0xC4, 0xE2, 0x79, 0x13, 0x00 );
    FCML_I32( "vcvtph2ps xmm0,xmm0", 0xC4, 0xE2, 0x79, 0x13, 0xC0 );
    /* VEX.256.66.0F38.W0 13 /r VCVTPH2PS ymm1,xmm2/m128 RM V/V F16C Convert eight packed half precision (16-bit) floating-point values in xmm2/m128 to packed single-precision floating-point value in ymm1.*/
    FCML_I32( "vcvtph2ps ymm0,xmmword ptr [eax]", 0xC4, 0xE2, 0x7D, 0x13, 0x00 );
    FCML_I64( "vcvtph2ps ymm0,xmm0", 0xC4, 0xE2, 0x7D, 0x13, 0xC0 );
    /* GAS*/
    FCML_A64( "vcvtph2ps (%rax),%xmm0", 0xc4, 0xe2, 0x79, 0x13, 0x00 );
    FCML_A64( "vcvtph2ps %xmm0,%xmm0", 0xc4, 0xe2, 0x79, 0x13, 0xc0 );
    FCML_A64( "vcvtph2ps (%rax),%ymm0", 0xc4, 0xe2, 0x7d, 0x13, 0x00 );
    FCML_A64( "vcvtph2ps %xmm0,%ymm0", 0xc4, 0xe2, 0x7d, 0x13, 0xc0 );
}

void fcml_tf_instruction_VCVTPS2PH(void) {
    /* VEX.128.66.0F3A.W0.1D /r VCVTPS2PH xmm1/m64,xmm2,imm8 ib MR V/V F16C Convert four packed single-precision floating-point value in xmm2 to packed halfprecision (16-bit) floating-point value in xmm1/mem. Imm8 provides rounding controls.*/
    FCML_I32( "vcvtps2ph mmword ptr [eax],xmm0,0ffh", 0xC4, 0xE3, 0x79, 0x1D, 0x00, 0xFF );
    FCML_I32( "vcvtps2ph xmm0,xmm0,0ffh", 0xC4, 0xE3, 0x79, 0x1D, 0xC0, 0xFF );
    /* VEX.256.66.0F3A.W0 1D /r VCVTPS2PH xmm1/m128,ymm2,imm8 ib MR V/V F16C Convert eight packed single-precision floating-point value in ymm2 to packed half-precision (16-bit) floating-point value in xmm1/mem. Imm8 provides rounding controls.*/
    FCML_I32( "vcvtps2ph xmmword ptr [eax],ymm0,0ffh", 0xC4, 0xE3, 0x7D, 0x1D, 0x00, 0xFF );
    FCML_I64( "vcvtps2ph xmm0,ymm0,0ffh", 0xC4, 0xE3, 0x7D, 0x1D, 0xC0, 0xFF );
    /* GAS*/
    FCML_A64( "vcvtps2ph $0xff,%xmm0,(%rax)", 0xc4, 0xe3, 0x79, 0x1d, 0x00, 0xff );
    FCML_A64( "vcvtps2ph $0xff,%xmm0,%xmm0", 0xc4, 0xe3, 0x79, 0x1d, 0xc0, 0xff );
    FCML_A64( "vcvtps2ph $0xff,%ymm0,(%rax)", 0xc4, 0xe3, 0x7d, 0x1d, 0x00, 0xff );
    FCML_A64( "vcvtps2ph $0xff,%ymm0,%xmm0", 0xc4, 0xe3, 0x7d, 0x1d, 0xc0, 0xff );
}

void fcml_tf_instruction_VERR(void) {
    /* 0F 00 /4 VERR r/m16 M Valid Valid Set ZF=1 if segment specified with r/m16 can be read.*/
    FCML_I32( "verr word ptr [eax]", 0x0F, 0x00, 0x20 );
    FCML_I32( "verr ax", 0x0F, 0x00, 0xE0 );
    FCML_I32( "verr ax", 0x66, 0x0F, 0x00, 0xE0 );
    FCML_I64( "verr word ptr [rax]", 0x0F, 0x00, 0x20 );
    /* 0F 00 /5 VERW r/m16 M Valid Valid Set ZF=1 if segment specified with r/m16 can be written.*/
    FCML_I32( "verw word ptr [eax]", 0x0F, 0x00, 0x28 );
    FCML_I32( "verw ax", 0x0F, 0x00, 0xE8 );
    FCML_I32( "verw ax", 0x66, 0x0F, 0x00, 0xE8 );
    FCML_I64( "verw word ptr [rax]", 0x0F, 0x00, 0x28 );
    /* GAS*/
    FCML_A64( "verr (%rax)", 0x0f, 0x00, 0x20 );
    FCML_A64( "verw (%rax)", 0x0f, 0x00, 0x28 );
}

void fcml_tf_instruction_VMLOAD(void) {
    /* VMLOAD rAX 0F 01 DA Load additional state from VMCB.*/
    FCML_I32( "vmload eax", 0x0F, 0x01, 0xDA );
    FCML_I32( "vmload ax", 0x67, 0x0F, 0x01, 0xDA );
    FCML_I64( "vmload rax", 0x0F, 0x01, 0xDA );
    FCML_I64( "vmload eax", 0x67, 0x0F, 0x01, 0xDA );
    /* GAS*/
    FCML_A32( "vmload %eax", 0x0F, 0x01, 0xDA );
    FCML_A32_A( "vmload", 0x0F, 0x01, 0xDA );
}

void fcml_tf_instruction_VMMCALL(void) {
    /* VMMCALL 0F 01 D9 Explicit communication with the VMM.*/
    FCML_I32( "vmmcall", 0x0F, 0x01, 0xD9 );
    FCML_I64( "vmmcall", 0x0F, 0x01, 0xD9 );
    /* GAS*/
    FCML_A64( "vmmcall", 0x0f, 0x01, 0xd9 );
}

void fcml_tf_instruction_VMRUN(void) {
    /* VMRUN rAX 0F 01 D8 Performs a world-switch to guest.*/
    FCML_I32( "vmrun eax", 0x0F, 0x01, 0xD8 );
    FCML_I32( "vmrun ax", 0x67, 0x0F, 0x01, 0xD8 );
    FCML_I64( "vmrun rax", 0x0F, 0x01, 0xD8 );
    FCML_I64( "vmrun eax", 0x67, 0x0F, 0x01, 0xD8 );
    /* GAS*/
    FCML_A64( "vmrun %rax", 0x0f, 0x01, 0xd8 );
    FCML_A64_A( "vmrun", 0x0f, 0x01, 0xd8 );
}

void fcml_tf_instruction_VMSAVE(void) {
    /* VMSAVE rAX 0F 01 DB Save additional guest state to VMCB.*/
    FCML_I32( "vmsave eax", 0x0F, 0x01, 0xDB );
    FCML_I32( "vmsave ax", 0x67, 0x0F, 0x01, 0xDB );
    FCML_I64( "vmsave rax", 0x0F, 0x01, 0xDB );
    FCML_I64( "vmsave eax", 0x67, 0x0F, 0x01, 0xDB );
    /* GAS*/
    FCML_A32( "vmsave %eax", 0x0F, 0x01, 0xDB );
    FCML_A32_A( "vmsave", 0x0F, 0x01, 0xDB );
}

void fcml_tf_instruction_VPERMILPD(void) {
    /* VEX.NDS.128.66.0F38.W0 0D /r VPERMILPD xmm1,xmm2,xmm3/m128 RVM V/V AVX Permute double-precision floating-point values in xmm2 using controls from xmm3/mem and store result in xmm1.*/
    /* VEX.NDS.256.66.0F38.W0 0D /r VPERMILPD ymm1,ymm2,ymm3/m256 RVM V/V AVX Permute double-precision floating-point values in ymm2 using controls from ymm3/mem and store result in ymm1.*/
    FCML_I32( "vpermilpd xmm0,xmm6,xmmword ptr [eax]", 0xC4, 0xE2, 0x49, 0x0D, 0x00 );
    FCML_I32( "vpermilpd xmm0,xmm6,xmm0", 0xC4, 0xE2, 0x49, 0x0D, 0xC0 );
    FCML_I64( "vpermilpd ymm0,ymm6,ymmword ptr [rax]", 0xC4, 0xE2, 0x4D, 0x0D, 0x00 );
    /* VEX.128.66.0F3A.W0 05 /r ib VPERMILPD xmm1,xmm2/m128,imm8 RMI V/V AVX Permute double-precision floating-point values in xmm2/mem using controls from imm8.*/
    /* VEX.256.66.0F3A.W0 05 /r ib VPERMILPD ymm1,ymm2/m256,imm8 RMI V/V AVX Permute double-precision floating-point values in ymm2/mem using controls from imm8.*/
    FCML_I32( "vpermilpd xmm0,xmmword ptr [eax],0ffh", 0xc4, 0xe3, 0x79, 0x05, 0x00, 0xff );
    FCML_I32( "vpermilpd xmm0,xmm0,0ffh", 0xc4, 0xe3, 0x79, 0x05, 0xc0, 0xff );
    FCML_I64( "vpermilpd ymm0,ymmword ptr [rax],0ffh", 0xc4, 0xe3, 0x7d, 0x05, 0x00, 0xff );
    /* GAS*/
    FCML_A64( "vpermilpd (%rax),%xmm6,%xmm0", 0xc4, 0xe2, 0x49, 0x0d, 0x00 );
    FCML_A64( "vpermilpd %xmm0,%xmm6,%xmm0", 0xc4, 0xe2, 0x49, 0x0d, 0xc0 );
    FCML_A64( "vpermilpd (%rax),%ymm6,%ymm0", 0xc4, 0xe2, 0x4d, 0x0d, 0x00 );
    FCML_A64( "vpermilpd $0xff,(%rax),%xmm0", 0xc4, 0xe3, 0x79, 0x05, 0x00, 0xff );
    FCML_A64( "vpermilpd $0xff,%xmm0,%xmm0", 0xc4, 0xe3, 0x79, 0x05, 0xc0, 0xff );
    FCML_A64( "vpermilpd $0xff,(%rax),%ymm0", 0xc4, 0xe3, 0x7d, 0x05, 0x00, 0xff );
}

void fcml_tf_instruction_VPERMILPS(void) {
    /* VEX.NDS.128.66.0F38.W0 0C /r VPERMILPS xmm1,xmm2,xmm3/m128 RVM V/V AVX Permute single-precision floating-point values in xmm2 using controls from xmm3/mem and store result in xmm1.*/
    /* VEX.NDS.256.66.0F38.W0 0C /r VPERMILPS ymm1,ymm2,ymm3/m256 RVM V/V AVX Permute single-precision floating-point values in ymm2 using controls from ymm3/mem and store result in ymm1.*/
    FCML_I32( "vpermilps xmm0,xmm6,xmmword ptr [eax]", 0xC4, 0xE2, 0x49, 0x0C, 0x00 );
    FCML_I32( "vpermilps xmm0,xmm6,xmm0", 0xC4, 0xE2, 0x49, 0x0C, 0xC0 );
    FCML_I64( "vpermilps ymm0,ymm6,ymmword ptr [rax]", 0xC4, 0xE2, 0x4D, 0x0C, 0x00 );
    /* VEX.128.66.0F3A.W0 04 /r ib VPERMILPS xmm1,xmm2/m128,imm8 RMI V/V AVX Permute single-precision floating-point values in xmm2/mem using controls from imm8 and store result in xmm1.*/
    /* VEX.256.66.0F3A.W0 04 /r ib VPERMILPS ymm1,ymm2/m256,imm8 RMI V/V AVX Permute single-precision floating-point values in ymm2/mem using controls from imm8 and store result in ymm1.*/
    FCML_I32( "vpermilps xmm0,xmmword ptr [eax],0ffh", 0xc4, 0xe3, 0x79, 0x04, 0x00, 0xff );
    FCML_I32( "vpermilps xmm0,xmm0,0ffh", 0xc4, 0xe3, 0x79, 0x04, 0xc0, 0xff );
    FCML_I64( "vpermilps ymm0,ymmword ptr [rax],0ffh", 0xc4, 0xe3, 0x7d, 0x04, 0x00, 0xff );
    /* GAS*/
    FCML_A64( "vpermilps (%rax),%xmm6,%xmm0", 0xc4, 0xe2, 0x49, 0x0c, 0x00 );
    FCML_A64( "vpermilps %xmm0,%xmm6,%xmm0", 0xc4, 0xe2, 0x49, 0x0c, 0xc0 );
    FCML_A64( "vpermilps (%rax),%ymm6,%ymm0", 0xc4, 0xe2, 0x4d, 0x0c, 0x00 );
    FCML_A64( "vpermilps $0xff,(%rax),%xmm0", 0xc4, 0xe3, 0x79, 0x04, 0x00, 0xff );
    FCML_A64( "vpermilps $0xff,%xmm0,%xmm0", 0xc4, 0xe3, 0x79, 0x04, 0xc0, 0xff );
    FCML_A64( "vpermilps $0xff,(%rax),%ymm0", 0xc4, 0xe3, 0x7d, 0x04, 0x00, 0xff );
}

void fcml_tf_instruction_VPSLLVD(void) {
    /* VEX.NDS.128.66.0F38.W0 47 /r VPSLLVD xmm1,xmm2,xmm3/m128*/
    /* VEX.NDS.256.66.0F38.W0 47 /r VPSLLVD ymm1,ymm2,ymm3/m256*/
    FCML_I32( "vpsllvd xmm0,xmm6,xmmword ptr [eax]", 0xC4, 0xE2, 0x49, 0x47, 0x00 );
    FCML_I32( "vpsllvd ymm0,ymm6,ymmword ptr [eax]", 0xC4, 0xE2, 0x4D, 0x47, 0x00 );
    FCML_I32( "vpsllvd ymm0,ymm6,ymm0", 0xC4, 0xE2, 0x4D, 0x47, 0xC0 );
    /* VEX.NDS.128.66.0F38.W1 47 /r VPSLLVQ xmm1,xmm2,xmm3/m128*/
    /* VEX.NDS.256.66.0F38.W1 47 /r VPSLLVQ ymm1,ymm2,ymm3/m256*/
    FCML_I64( "vpsllvq xmm0,xmm6,xmmword ptr [rax]", 0xC4, 0xE2, 0xC9, 0x47, 0x00 );
    FCML_I64( "vpsllvq ymm0,ymm6,ymmword ptr [rax]", 0xC4, 0xE2, 0xCD, 0x47, 0x00 );
    FCML_I64( "vpsllvq ymm0,ymm6,ymm0", 0xC4, 0xE2, 0xCD, 0x47, 0xC0 );
    /* GAS*/
    FCML_A64( "vpsllvd (%rax),%xmm6,%xmm0", 0xc4, 0xe2, 0x49, 0x47, 0x00 );
    FCML_A64( "vpsllvd (%rax),%ymm6,%ymm0", 0xc4, 0xe2, 0x4d, 0x47, 0x00 );
    FCML_A64( "vpsllvd %ymm0,%ymm6,%ymm0", 0xc4, 0xe2, 0x4d, 0x47, 0xc0 );
    FCML_A64( "vpsllvq (%rax),%xmm6,%xmm0", 0xc4, 0xe2, 0xc9, 0x47, 0x00 );
    FCML_A64( "vpsllvq (%rax),%ymm6,%ymm0", 0xc4, 0xe2, 0xcd, 0x47, 0x00 );
    FCML_A64( "vpsllvq %ymm0,%ymm6,%ymm0", 0xc4, 0xe2, 0xcd, 0x47, 0xc0 );
}

void fcml_tf_instruction_VPSRLVD(void) {
    /* VEX.NDS.128.66.0F38.W0 45 /r VPSRLVD xmm1,xmm2,xmm3/m128*/
    /* VEX.NDS.256.66.0F38.W0 45 /r VPSRLVD ymm1,ymm2,ymm3/m256*/
    FCML_I32( "vpsrlvd xmm0,xmm6,xmmword ptr [eax]", 0xC4, 0xE2, 0x49, 0x45, 0x00 );
    FCML_I32( "vpsrlvd ymm0,ymm6,ymmword ptr [eax]", 0xC4, 0xE2, 0x4D, 0x45, 0x00 );
    FCML_I32( "vpsrlvd ymm0,ymm6,ymm0", 0xC4, 0xE2, 0x4D, 0x45, 0xC0 );
    /* VEX.NDS.128.66.0F38.W1 45 /r VPSRLVQ xmm1,xmm2,xmm3/m128*/
    /* VEX.NDS.256.66.0F38.W1 45 /r VPSRLVQ ymm1,ymm2,ymm3/m256*/
    FCML_I64( "vpsrlvq xmm0,xmm6,xmmword ptr [rax]", 0xC4, 0xE2, 0xC9, 0x45, 0x00 );
    FCML_I64( "vpsrlvq ymm0,ymm6,ymmword ptr [rax]", 0xC4, 0xE2, 0xCD, 0x45, 0x00 );
    FCML_I64( "vpsrlvq ymm0,ymm6,ymm0", 0xC4, 0xE2, 0xCD, 0x45, 0xC0 );
    /* GAS*/
    FCML_A64( "vpsrlvd (%rax),%xmm6,%xmm0", 0xc4, 0xe2, 0x49, 0x45, 0x00 );
    FCML_A64( "vpsrlvd (%rax),%ymm6,%ymm0", 0xc4, 0xe2, 0x4d, 0x45, 0x00 );
    FCML_A64( "vpsrlvd %ymm0,%ymm6,%ymm0", 0xc4, 0xe2, 0x4d, 0x45, 0xc0 );
    FCML_A64( "vpsrlvq (%rax),%xmm6,%xmm0", 0xc4, 0xe2, 0xc9, 0x45, 0x00 );
    FCML_A64( "vpsrlvq (%rax),%ymm6,%ymm0", 0xc4, 0xe2, 0xcd, 0x45, 0x00 );
    FCML_A64( "vpsrlvq %ymm0,%ymm6,%ymm0", 0xc4, 0xe2, 0xcd, 0x45, 0xc0 );
}

void fcml_tf_instruction_VPSRAVD(void) {
    /* VEX.NDS.128.66.0F38.W0 46 /r VPSRAVD xmm1,xmm2,xmm3/m128*/
    /* VEX.NDS.256.66.0F38.W0 46 /r VPSRAVD ymm1,ymm2,ymm3/m256*/
    FCML_I32( "vpsravd xmm0,xmm6,xmmword ptr [eax]", 0xC4, 0xE2, 0x49, 0x46, 0x00 );
    FCML_I32( "vpsravd ymm0,ymm6,ymmword ptr [eax]", 0xC4, 0xE2, 0x4D, 0x46, 0x00 );
    FCML_I32( "vpsravd ymm0,ymm6,ymm0", 0xC4, 0xE2, 0x4D, 0x46, 0xC0 );
    /* GAS*/
    FCML_A64( "vpsravd (%rax),%xmm6,%xmm0", 0xc4, 0xe2, 0x49, 0x46, 0x00 );
    FCML_A64( "vpsravd (%rax),%ymm6,%ymm0", 0xc4, 0xe2, 0x4d, 0x46, 0x00 );
    FCML_A64( "vpsravd %ymm0,%ymm6,%ymm0", 0xc4, 0xe2, 0x4d, 0x46, 0xc0 );
}

void fcml_tf_instruction_VPERMD(void) {
    /* VEX.NDS.256.66.0F38.W0 36 /r VPERMD ymm1,ymm2,ymm3/m256*/
    FCML_I32( "vpermd ymm0,ymm6,ymmword ptr [eax]", 0xC4, 0xE2, 0x4D, 0x36, 0x00 );
    FCML_I32( "vpermd ymm0,ymm6,ymm0", 0xC4, 0xE2, 0x4D, 0x36, 0xC0 );
    FCML_I64( "vpermd ymm0,ymm6,ymmword ptr [rax]", 0xC4, 0xE2, 0x4D, 0x36, 0x00 );
    /* GAS*/
    FCML_A64( "vpermd (%rax),%ymm6,%ymm0", 0xc4, 0xe2, 0x4d, 0x36, 0x00 );
    FCML_A64( "vpermd %ymm0,%ymm6,%ymm0", 0xc4, 0xe2, 0x4d, 0x36, 0xc0 );
    FCML_A64( "vpermd (%rax),%ymm6,%ymm0", 0xc4, 0xe2, 0x4d, 0x36, 0x00 );
}

void fcml_tf_instruction_VPERMPD(void) {
    /* VEX.256.66.0F3A.W1 01 /r ib VPERMPD ymm1,ymm2/m256,imm8*/
    FCML_I64( "vpermpd ymm0,ymmword ptr [rax],0ffh", 0xC4, 0xE3, 0xFD, 0x01, 0x00, 0xFF );
    FCML_I64( "vpermpd ymm0,ymm0,0ffh", 0xC4, 0xE3, 0xFD, 0x01, 0xC0, 0xFF );
    /* GAS*/
    FCML_A64( "vpermpd $0xff,(%rax),%ymm0", 0xc4, 0xe3, 0xfd, 0x01, 0x00, 0xff );
    FCML_A64( "vpermpd $0xff,%ymm0,%ymm0", 0xc4, 0xe3, 0xfd, 0x01, 0xc0, 0xff );
}

void fcml_tf_instruction_VPERMQ(void) {
    /* VEX.256.66.0F3A.W1 00 /r ib VPERMQ ymm1,ymm2/m256,imm8*/
    FCML_I64( "vpermq ymm0,ymmword ptr [rax],0ffh", 0xC4, 0xE3, 0xFD, 0x00, 0x00, 0xFF );
    FCML_I64( "vpermq ymm0,ymm0,0ffh", 0xC4, 0xE3, 0xFD, 0x00, 0xC0, 0xFF );
    /* GAS*/
    FCML_A64( "vpermq $0xff,(%rax),%ymm0", 0xc4, 0xe3, 0xfd, 0x00, 0x00, 0xff );
    FCML_A64( "vpermq $0xff,%ymm0,%ymm0", 0xc4, 0xe3, 0xfd, 0x00, 0xc0, 0xff );
}

void fcml_tf_instruction_VPERMPS(void) {
    /* VEX.NDS.256.66.0F38.W0 16 /r VPERMPS ymm1,ymm2,ymm3/m256*/
    FCML_I32( "vpermps ymm0,ymm6,ymmword ptr [eax]", 0xC4, 0xE2, 0x4D, 0x16, 0x00 );
    FCML_I32( "vpermps ymm0,ymm6,ymm0", 0xC4, 0xE2, 0x4D, 0x16, 0xC0 );
    FCML_I64( "vpermps ymm0,ymm6,ymmword ptr [rax]", 0xC4, 0xE2, 0x4D, 0x16, 0x00 );
    /* GAS*/
    FCML_A64( "vpermps (%rax),%ymm6,%ymm0", 0xc4, 0xe2, 0x4d, 0x16, 0x00 );
    FCML_A64( "vpermps %ymm0,%ymm6,%ymm0", 0xc4, 0xe2, 0x4d, 0x16, 0xc0 );
    FCML_A64( "vpermps (%rax),%ymm6,%ymm0", 0xc4, 0xe2, 0x4d, 0x16, 0x00 );
}

void fcml_tf_instruction_VPERM2F128(void) {
    /* VEX.NDS.256.66.0F3A.W0 06 /r ib VPERM2F128 ymm1,ymm2,ymm3/m256,imm8 RVMI V/V AVX Permute 128-bit floating-point fields in ymm2 and ymm3/mem using controls from imm8 and store result in ymm1.*/
    FCML_I32( "vperm2f128 ymm0,ymm6,ymmword ptr [eax],0ffh", 0xC4, 0xE3, 0x4D, 0x06, 0x00, 0xFF );
    FCML_I32( "vperm2f128 ymm0,ymm6,ymm0,0ffh", 0xC4, 0xE3, 0x4D, 0x06, 0xC0, 0xFF );
    FCML_I64( "vperm2f128 ymm0,ymm6,ymmword ptr [rax],0ffh", 0xC4, 0xE3, 0x4D, 0x06, 0x00, 0xFF );
    /* GAS*/
    FCML_A64( "vperm2f128 $0xff,(%rax),%ymm6,%ymm0", 0xc4, 0xe3, 0x4d, 0x06, 0x00, 0xff );
    FCML_A64( "vperm2f128 $0xff,%ymm0,%ymm6,%ymm0", 0xc4, 0xe3, 0x4d, 0x06, 0xc0, 0xff );
    FCML_A64( "vperm2f128 $0xff,(%rax),%ymm6,%ymm0", 0xc4, 0xe3, 0x4d, 0x06, 0x00, 0xff );
}

void fcml_tf_instruction_VPERM2I128(void) {
    /* VEX.NDS.256.66.0F3A.W0 46 /r ib VPERM2I128 ymm1,ymm2,ymm3/m256,imm8*/
    FCML_I32( "vperm2i128 ymm0,ymm6,ymmword ptr [eax],0ffh", 0xC4, 0xE3, 0x4D, 0x46, 0x00, 0xFF );
    FCML_I32( "vperm2i128 ymm0,ymm6,ymm0,0ffh", 0xC4, 0xE3, 0x4D, 0x46, 0xC0, 0xFF );
    FCML_I64( "vperm2i128 ymm0,ymm6,ymmword ptr [rax],0ffh", 0xC4, 0xE3, 0x4D, 0x46, 0x00, 0xFF );
    /* GAS*/
    FCML_A64( "vperm2i128 $0xff,(%rax),%ymm6,%ymm0", 0xc4, 0xe3, 0x4d, 0x46, 0x00, 0xff );
    FCML_A64( "vperm2i128 $0xff,%ymm0,%ymm6,%ymm0", 0xc4, 0xe3, 0x4d, 0x46, 0xc0, 0xff );
    FCML_A64( "vperm2i128 $0xff,(%rax),%ymm6,%ymm0", 0xc4, 0xe3, 0x4d, 0x46, 0x00, 0xff );
}

void fcml_tf_instruction_VEXTRACTI128(void) {
    /* VEX.256.66.0F3A.W0 39 /r ib VEXTRACTI128 xmm1/m128,ymm2,imm8*/
    FCML_I32( "vextracti128 xmmword ptr [eax],ymm0,0ffh", 0xC4, 0xE3, 0x7D, 0x39, 0x00, 0xFF );
    FCML_I64( "vextracti128 xmm0,ymm0,0ffh", 0xC4, 0xE3, 0x7D, 0x39, 0xC0, 0xFF );
    /* GAS*/
    FCML_A64( "vextracti128 $0xff,%ymm0,(%rax)", 0xc4, 0xe3, 0x7d, 0x39, 0x00, 0xff );
    FCML_A64( "vextracti128 $0xff,%ymm0,%xmm0", 0xc4, 0xe3, 0x7d, 0x39, 0xc0, 0xff );
}

void fcml_tf_instruction_VINSERTI128(void) {
    /* VEX.NDS.256.66.0F3A.W0 38 /r ib VINSERTI128 ymm1,ymm2,xmm3/m128,imm8*/
    FCML_I32( "vinserti128 ymm0,ymm6,xmmword ptr [eax],0ffh", 0xC4, 0xE3, 0x4D, 0x38, 0x00, 0xFF );
    FCML_I32( "vinserti128 ymm0,ymm6,xmm0,0ffh", 0xC4, 0xE3, 0x4D, 0x38, 0xC0, 0xFF );
    FCML_I64( "vinserti128 ymm0,ymm6,xmmword ptr [rax],0ffh", 0xC4, 0xE3, 0x4D, 0x38, 0x00, 0xFF );
    /* GAS*/
    FCML_A64( "vinserti128 $0xff,(%rax),%ymm6,%ymm0", 0xc4, 0xe3, 0x4d, 0x38, 0x00, 0xff );
    FCML_A64( "vinserti128 $0xff,%xmm0,%ymm6,%ymm0", 0xc4, 0xe3, 0x4d, 0x38, 0xc0, 0xff );
    FCML_A64( "vinserti128 $0xff,(%rax),%ymm6,%ymm0", 0xc4, 0xe3, 0x4d, 0x38, 0x00, 0xff );
}

void fcml_tf_instruction_VTESTPS(void) {
    /* VEX.128.66.0F38.W0 0E /r VTESTPS xmm1,xmm2/m128 RM V/V AVX Set ZF and CF depending on sign bit AND and ANDN of packed single-precision floatingpoint sources.*/
    /* VEX.256.66.0F38.W0 0E /r VTESTPS ymm1,ymm2/m256 RM V/V AVX Set ZF and CF depending on sign bit AND and ANDN of packed single-precision floatingpoint sources.*/
    FCML_I64( "vtestps xmm1,xmm0", 0xC4, 0xE2, 0x79, 0x0E, 0xC8 );
    FCML_I32( "vtestps xmm1,xmm0", 0xC4, 0xE2, 0x79, 0x0E, 0xC8 );
    FCML_I32( "vtestps xmm0,xmmword ptr [eax]", 0xC4, 0xE2, 0x79, 0x0E, 0x00 );
    FCML_I32( "vtestps ymm0,ymmword ptr [eax]", 0xC4, 0xE2, 0x7D, 0x0E, 0x00 );
    /* VEX.128.66.0F38.W0 0F /r VTESTPD xmm1,xmm2/m128 RM V/V AVX Set ZF and CF depending on sign bit AND and ANDN of packed double-precision floatingpoint sources.*/
    /* VEX.256.66.0F38.W0 0F /r VTESTPD ymm1,ymm2/m256 RM V/V AVX Set ZF and CF depending on sign bit AND and ANDN of packed double-precision floatingpoint sources.*/
    FCML_I64( "vtestpd xmm0,xmm0", 0xC4, 0xE2, 0x79, 0x0f, 0xC0 );
    FCML_I32( "vtestpd xmm0,xmm0", 0xC4, 0xE2, 0x79, 0x0f, 0xC0 );
    FCML_I32( "vtestpd xmm0,xmmword ptr [eax]", 0xC4, 0xE2, 0x79, 0x0F, 0x00 );
    FCML_I32( "vtestpd ymm0,ymmword ptr [eax]", 0xC4, 0xE2, 0x7D, 0x0F, 0x00 );
    /* GAS*/
    FCML_A64( "vtestps %xmm0,%xmm1", 0xc4, 0xe2, 0x79, 0x0e, 0xc8 );
    FCML_A64( "vtestps (%rax),%xmm0", 0xc4, 0xe2, 0x79, 0x0e, 0x00 );
    FCML_A64( "vtestps (%rax),%ymm0", 0xc4, 0xe2, 0x7d, 0x0e, 0x00 );
    FCML_A64( "vtestpd %xmm0,%xmm0", 0xc4, 0xe2, 0x79, 0x0f, 0xc0 );
    FCML_A64( "vtestpd (%rax),%xmm0", 0xc4, 0xe2, 0x79, 0x0f, 0x00 );
    FCML_A64( "vtestpd (%rax),%ymm0", 0xc4, 0xe2, 0x7d, 0x0f, 0x00 );
}

void fcml_tf_instruction_VGATHERDPD(void) {
    /* VEX.DDS.128.66.0F38.W1 92 /r VGATHERDPD xmm1, vm32x, xmm2*/
    /* VEX.DDS.256.66.0F38.W1 92 /r VGATHERDPD ymm1, vm32x, ymm2*/
    FCML_I64( "vgatherdpd xmm0,dword ptr [rax+xmm5],xmm0", 0xC4, 0xE2, 0xF9, 0x92, 0x04, 0x28 );
    /* Check if VSIB index register size is appropriately checked.*/
    FCML_I64_D_FAILED( "vgatherdpd xmm0,dword ptr [rax+ymm5],xmm0", 0xC4, 0xE2, 0xF9, 0x92, 0x04, 0x28 );
    FCML_I64_A_FAILED( "vgatherdpd xmm0,dword ptr [rax+ymm5],xmm0", 0xC4, 0xE2, 0xF9, 0x92, 0x04, 0x28 );
    FCML_I64( "vgatherdpd ymm0,dword ptr [rax+xmm5],ymm0", 0xC4, 0xE2, 0xFD, 0x92, 0x04, 0x28 );
    /* VEX.DDS.128.66.0F38.W1 93 /r VGATHERQPD xmm1, vm64x, xmm2*/
    /* VEX.DDS.256.66.0F38.W1 93 /r VGATHERQPD ymm1, vm64y, ymm2*/
    FCML_I64( "vgatherqpd xmm0,qword ptr [rax+xmm5],xmm0", 0xC4, 0xE2, 0xF9, 0x93, 0x04, 0x28 );
    FCML_I64( "vgatherqpd ymm0,qword ptr [rax+ymm5],ymm0", 0xC4, 0xE2, 0xFD, 0x93, 0x04, 0x28 );
    /* GAS*/
    FCML_A64( "vgatherdpd %xmm0,(%rax,%xmm5),%xmm0", 0xc4, 0xe2, 0xf9, 0x92, 0x04, 0x28 );
    FCML_A64( "vgatherdpd %xmm0,(%rax,%xmm5),%xmm0", 0xc4, 0xe2, 0xf9, 0x92, 0x04, 0x28 );
    FCML_A64( "vgatherdpd %xmm0,(%rax,%xmm5),%xmm0", 0xc4, 0xe2, 0xf9, 0x92, 0x04, 0x28 );
    FCML_A64( "vgatherdpd %ymm0,(%rax,%xmm5),%ymm0", 0xc4, 0xe2, 0xfd, 0x92, 0x04, 0x28 );
    FCML_A64( "vgatherqpd %xmm0,(%rax,%xmm5),%xmm0", 0xc4, 0xe2, 0xf9, 0x93, 0x04, 0x28 );
    FCML_A64( "vgatherqpd %ymm0,(%rax,%ymm5),%ymm0", 0xc4, 0xe2, 0xfd, 0x93, 0x04, 0x28 );
}

void fcml_tf_instruction_VGATHERDPS(void) {
    /* VEX.DDS.128.66.0F38.W0 92 /r VGATHERDPS xmm1,vm32x,xmm2*/
    /* VEX.DDS.256.66.0F38.W0 92 /r VGATHERDPS ymm1,vm32y,ymm2*/
    FCML_I32( "vgatherdps xmm0,dword ptr [eax+xmm5],xmm0", 0xC4, 0xE2, 0x79, 0x92, 0x04, 0x28 );
    FCML_I32( "vgatherdps ymm0,dword ptr [eax+ymm5],ymm0", 0xC4, 0xE2, 0x7D, 0x92, 0x04, 0x28 );
    /* VEX.DDS.128.66.0F38.W0 93 /r VGATHERQPS xmm1,vm64x,xmm2*/
    /* VEX.DDS.256.66.0F38.W0 93 /r VGATHERQPS xmm1,vm64y,xmm2*/
    FCML_I32( "vgatherqps xmm0,qword ptr [eax+xmm5],xmm0", 0xC4, 0xE2, 0x79, 0x93, 0x04, 0x28 );
    FCML_I32( "vgatherqps xmm0,qword ptr [eax+ymm5],xmm0", 0xC4, 0xE2, 0x7D, 0x93, 0x04, 0x28 );
    /* GAS*/
    FCML_A64( "vgatherdps %xmm0,(%rax,%xmm5),%xmm0", 0xc4, 0xe2, 0x79, 0x92, 0x04, 0x28 );
    FCML_A64( "vgatherdps %ymm0,(%rax,%ymm5),%ymm0", 0xc4, 0xe2, 0x7d, 0x92, 0x04, 0x28 );
    FCML_A64( "vgatherqps %xmm0,(%rax,%xmm5),%xmm0", 0xc4, 0xe2, 0x79, 0x93, 0x04, 0x28 );
    FCML_A64( "vgatherqps %xmm0,(%rax,%ymm5),%xmm0", 0xc4, 0xe2, 0x7d, 0x93, 0x04, 0x28 );
}

void fcml_tf_instruction_VPGATHERDD(void) {
    /* VEX.DDS.128.66.0F38.W0 90 /r VPGATHERDD xmm1,vm32x,xmm2*/
    /* VEX.DDS.256.66.0F38.W0 90 /r VPGATHERDD ymm1,vm32y,ymm2*/
    FCML_I32( "vpgatherdd xmm0,dword ptr [eax+xmm5],xmm0", 0xC4, 0xE2, 0x79, 0x90, 0x04, 0x28 );
    FCML_I32( "vpgatherdd ymm0,dword ptr [eax+ymm5],ymm0", 0xC4, 0xE2, 0x7D, 0x90, 0x04, 0x28 );
    /* VEX.DDS.128.66.0F38.W0 91 /r VPGATHERQD xmm1,vm64x,xmm2*/
    /* VEX.DDS.256.66.0F38.W0 91 /r VPGATHERQD xmm1,vm64y,xmm2*/
    FCML_I32( "vpgatherqd xmm0,qword ptr [eax+xmm5],xmm0", 0xC4, 0xE2, 0x79, 0x91, 0x04, 0x28 );
    FCML_I32( "vpgatherqd xmm0,qword ptr [eax+ymm5],xmm0", 0xC4, 0xE2, 0x7D, 0x91, 0x04, 0x28 );
    /* GAS*/
    FCML_A64( "vpgatherdd %xmm0,(%rax,%xmm5),%xmm0", 0xc4, 0xe2, 0x79, 0x90, 0x04, 0x28 );
    FCML_A64( "vpgatherdd %ymm0,(%rax,%ymm5),%ymm0", 0xc4, 0xe2, 0x7d, 0x90, 0x04, 0x28 );
    FCML_A64( "vpgatherqd %xmm0,(%rax,%xmm5),%xmm0", 0xc4, 0xe2, 0x79, 0x91, 0x04, 0x28 );
    FCML_A64( "vpgatherqd %xmm0,(%rax,%ymm5),%xmm0", 0xc4, 0xe2, 0x7d, 0x91, 0x04, 0x28 );
}

void fcml_tf_instruction_VPGATHERDQ(void) {
    /* VEX.DDS.128.66.0F38.W1 90 /r VPGATHERDQ xmm1,vm32x,xmm2*/
    /* VEX.DDS.256.66.0F38.W1 90 /r VPGATHERDQ ymm1,vm32x,ymm2*/
    FCML_I64( "vpgatherdq xmm0,dword ptr [rax+xmm5],xmm0", 0xC4, 0xE2, 0xF9, 0x90, 0x04, 0x28 );
    FCML_I64( "vpgatherdq ymm0,dword ptr [rax+xmm5],ymm0", 0xC4, 0xE2, 0xFD, 0x90, 0x04, 0x28 );
    /* VEX.DDS.128.66.0F38.W1 91 /r VPGATHERQQ xmm1,vm64x,xmm2*/
    /* VEX.DDS.256.66.0F38.W1 91 /r VPGATHERQQ ymm1,vm64y,ymm2*/
    FCML_I64( "vpgatherqq xmm0,qword ptr [rax+xmm5],xmm0", 0xC4, 0xE2, 0xF9, 0x91, 0x04, 0x28 );
    FCML_I64( "vpgatherqq ymm0,qword ptr [rax+ymm5],ymm0", 0xC4, 0xE2, 0xFD, 0x91, 0x04, 0x28 );
    /* GAS*/
    FCML_A64( "vpgatherdq %xmm0,(%rax,%xmm5),%xmm0", 0xc4, 0xe2, 0xf9, 0x90, 0x04, 0x28 );
    FCML_A64( "vpgatherdq %ymm0,(%rax,%xmm5),%ymm0", 0xc4, 0xe2, 0xfd, 0x90, 0x04, 0x28 );
    FCML_A64( "vpgatherqq %xmm0,(%rax,%xmm5),%xmm0", 0xc4, 0xe2, 0xf9, 0x91, 0x04, 0x28 );
    FCML_A64( "vpgatherqq %ymm0,(%rax,%ymm5),%ymm0", 0xc4, 0xe2, 0xfd, 0x91, 0x04, 0x28 );
}

void fcml_tf_instruction_VZEROALL(void) {
    /* VEX.256.0F.WIG 77 VZEROALL NP V/V AVX Zero all YMM registers.*/
    FCML_I64( "vzeroall", 0xc5, 0xfc, 0x77 );
    FCML_I32( "vzeroall", 0xc5, 0xfc, 0x77 );
    /* GAS*/
    FCML_A32( "vzeroall", 0xc5, 0xfc, 0x77 );
    FCML_A64( "vzeroall", 0xc5, 0xfc, 0x77 );
}

void fcml_tf_instruction_VZEROUPPER(void) {
    /* VEX.128.0F.WIG 77 VZEROUPPER NP V/V AVX Zero upper 128 bits of all YMM registers.*/
    FCML_I64( "vzeroupper", 0xc5, 0xf8, 0x77 );
    FCML_I32( "vzeroupper", 0xc5, 0xf8, 0x77 );
    /* GAS*/
    FCML_A32( "vzeroupper", 0xc5, 0xf8, 0x77 );
    FCML_A64( "vzeroupper", 0xc5, 0xf8, 0x77 );
}

void fcml_tf_instruction_VFMADDPD(void) {
    /* VEX.DDS.128.66.0F38.W1 98 /r VFMADD132PD xmm0,xmm1,xmm2/m128*/
    /* VEX.DDS.256.66.0F38.W1 98 /r VFMADD132PD ymm0,ymm1,ymm2/m256*/
    FCML_I64( "vfmadd132pd xmm0,xmm3,xmmword ptr [rax]", 0xC4, 0xE2, 0xE1, 0x98, 0x00 );
    FCML_I64( "vfmadd132pd ymm0,ymm3,ymmword ptr [rax]", 0xC4, 0xE2, 0xE5, 0x98, 0x00 );
    FCML_I64( "vfmadd132pd ymm0,ymm3,ymm0", 0xC4, 0xE2, 0xE5, 0x98, 0xC0 );
    /* VEX.DDS.128.66.0F38.W1 A8 /r VFMADD213PD xmm0,xmm1,xmm2/m128*/
    /* VEX.DDS.256.66.0F38.W1 A8 /r VFMADD213PD ymm0,ymm1,ymm2/m256*/
    FCML_I64( "vfmadd213pd xmm0,xmm3,xmmword ptr [rax]", 0xC4, 0xE2, 0xE1, 0xA8, 0x00 );
    FCML_I64( "vfmadd213pd ymm0,ymm3,ymmword ptr [rax]", 0xC4, 0xE2, 0xE5, 0xA8, 0x00 );
    FCML_I64( "vfmadd213pd ymm0,ymm3,ymm0", 0xC4, 0xE2, 0xE5, 0xA8, 0xC0 );
    /* VEX.DDS.128.66.0F38.W1 B8 /r VFMADD231PD xmm0,xmm1,xmm2/m128*/
    /* VEX.DDS.256.66.0F38.W1 B8 /r VFMADD231PD ymm0,ymm1,ymm2/m256*/
    FCML_I64( "vfmadd231pd xmm0,xmm3,xmmword ptr [rax]", 0xC4, 0xE2, 0xE1, 0xB8, 0x00 );
    FCML_I64( "vfmadd231pd ymm0,ymm3,ymmword ptr [rax]", 0xC4, 0xE2, 0xE5, 0xB8, 0x00 );
    FCML_I64( "vfmadd231pd ymm0,ymm3,ymm0", 0xC4, 0xE2, 0xE5, 0xB8, 0xC0 );
    /* VFMADDPD xmm1, xmm2, xmm3/mem128, xmm4 C4 RXB.00011 0.src.0.01 69 /r /is4*/
    /* VFMADDPD ymm1, ymm2, ymm3/mem256, ymm4 C4 RXB.00011 0.src.1.01 69 /r /is4*/
    FCML_I32( "vfmaddpd xmm2,xmm5,xmmword ptr [ecx+eax],xmm2", 0xC4, 0xE3, 0x51, 0x69, 0x14, 0x01, 0x20 );
    FCML_I64( "vfmaddpd ymm2,ymm5,ymmword ptr [rcx+rax],ymm2", 0xC4, 0xE3, 0x55, 0x69, 0x14, 0x01, 0x20 );
    FCML_I64_M( "vfmaddpd ymm0,ymm5,ymm0,ymm2", 2, FCML_MI( 0xc4, 0xe3, 0xd5, 0x69, 0xc2, 0x00 ), FCML_MI( 0xc4, 0xe3, 0x55, 0x69, 0xc0, 0x20 ) );
    /* VFMADDPD xmm1, xmm2, xmm3, xmm4/mem128 C4 RXB.00011 1.src.0.01 69 /r /is4*/
    /* VFMADDPD ymm1, ymm2, ymm3, ymm4/mem256 C4 RXB.00011 1.src.1.01 69 /r /is4*/
    FCML_I64( "vfmaddpd xmm2,xmm5,xmm2,xmmword ptr [rcx+rax]", 0xC4, 0xE3, 0xD1, 0x69, 0x14, 0x01, 0x20 );
    FCML_I64( "vfmaddpd ymm2,ymm5,ymm2,ymmword ptr [rcx+rax]", 0xC4, 0xE3, 0xD5, 0x69, 0x14, 0x01, 0x20 );
    FCML_I64_M( "vfmaddpd ymm0,ymm5,ymm2,ymm0", 2, FCML_MI( 0xc4, 0xe3, 0xd5, 0x69, 0xc0, 0x20 ), FCML_MI( 0xc4, 0xe3, 0x55, 0x69, 0xc2, 0x00 ) );
    /* GAS*/
    FCML_A64( "vfmadd132pd (%rax),%xmm3,%xmm0", 0xc4, 0xe2, 0xe1, 0x98, 0x00 );
    FCML_A64( "vfmadd132pd (%rax),%ymm3,%ymm0", 0xc4, 0xe2, 0xe5, 0x98, 0x00 );
    FCML_A64( "vfmadd132pd %ymm0,%ymm3,%ymm0", 0xc4, 0xe2, 0xe5, 0x98, 0xc0 );
    FCML_A64( "vfmadd213pd (%rax),%xmm3,%xmm0", 0xc4, 0xe2, 0xe1, 0xa8, 0x00 );
    FCML_A64( "vfmadd213pd (%rax),%ymm3,%ymm0", 0xc4, 0xe2, 0xe5, 0xa8, 0x00 );
    FCML_A64( "vfmadd213pd %ymm0,%ymm3,%ymm0", 0xc4, 0xe2, 0xe5, 0xa8, 0xc0 );
    FCML_A64( "vfmadd231pd (%rax),%xmm3,%xmm0", 0xc4, 0xe2, 0xe1, 0xb8, 0x00 );
    FCML_A64( "vfmadd231pd (%rax),%ymm3,%ymm0", 0xc4, 0xe2, 0xe5, 0xb8, 0x00 );
    FCML_A64( "vfmadd231pd %ymm0,%ymm3,%ymm0", 0xc4, 0xe2, 0xe5, 0xb8, 0xc0 );
    FCML_A64( "vfmaddpd %xmm2,(%rcx,%rax),%xmm5,%xmm2", 0xc4, 0xe3, 0x51, 0x69, 0x14, 0x01, 0x20 );
    FCML_A64( "vfmaddpd %ymm2,(%rcx,%rax),%ymm5,%ymm2", 0xc4, 0xe3, 0x55, 0x69, 0x14, 0x01, 0x20 );
    FCML_A64( "vfmaddpd (%rcx,%rax),%xmm2,%xmm5,%xmm2", 0xc4, 0xe3, 0xd1, 0x69, 0x14, 0x01, 0x20 );
    FCML_A64( "vfmaddpd (%rcx,%rax),%ymm2,%ymm5,%ymm2", 0xc4, 0xe3, 0xd5, 0x69, 0x14, 0x01, 0x20 );
    FCML_A64_M( "vfmaddpd %ymm2,%ymm0,%ymm5,%ymm0", 2, FCML_MI( 0xc4, 0xe3, 0xd5, 0x69, 0xc2, 0x00 ), FCML_MI( 0xc4, 0xe3, 0x55, 0x69, 0xc0, 0x20 ) );
    FCML_A64_M( "vfmaddpd %ymm2,%ymm0,%ymm5,%ymm0", 2, FCML_MI( 0xc4, 0xe3, 0xd5, 0x69, 0xc2, 0x00 ), FCML_MI( 0xc4, 0xe3, 0x55, 0x69, 0xc0, 0x20 ) );
    FCML_A64_M( "vfmaddpd %ymm0,%ymm2,%ymm5,%ymm0", 2, FCML_MI( 0xc4, 0xe3, 0xd5, 0x69, 0xc0, 0x20 ), FCML_MI( 0xc4, 0xe3, 0x55, 0x69, 0xc2, 0x00 ) );
    FCML_A64_M( "vfmaddpd %ymm0,%ymm2,%ymm5,%ymm0", 2, FCML_MI( 0xc4, 0xe3, 0xd5, 0x69, 0xc0, 0x20 ), FCML_MI( 0xc4, 0xe3, 0x55, 0x69, 0xc2, 0x00 ) );
}

void fcml_tf_instruction_VFMADDPS(void) {
    /* VEX.DDS.128.66.0F38.W0 98 /r VFMADD132PS xmm0,xmm1,xmm2/m128*/
    /* VEX.DDS.256.66.0F38.W0 98 /r VFMADD132PS ymm0,ymm1,ymm2/m256*/
    FCML_I32( "vfmadd132ps xmm0,xmm3,xmmword ptr [eax]", 0xC4, 0xE2, 0x61, 0x98, 0x00 );
    FCML_I64( "vfmadd132ps ymm0,ymm3,ymmword ptr [rax]", 0xC4, 0xE2, 0x65, 0x98, 0x00 );
    FCML_I32( "vfmadd132ps ymm0,ymm3,ymm0", 0xC4, 0xE2, 0x65, 0x98, 0xC0 );
    /* VEX.DDS.128.66.0F38.W0 A8 /r VFMADD213PS xmm0,xmm1,xmm2/m128*/
    /* VEX.DDS.256.66.0F38.W0 A8 /r VFMADD213PS ymm0,ymm1,ymm2/m256*/
    FCML_I32( "vfmadd213ps xmm0,xmm3,xmmword ptr [eax]", 0xC4, 0xE2, 0x61, 0xA8, 0x00 );
    FCML_I64( "vfmadd213ps ymm0,ymm3,ymmword ptr [rax]", 0xC4, 0xE2, 0x65, 0xA8, 0x00 );
    FCML_I32( "vfmadd213ps ymm0,ymm3,ymm0", 0xC4, 0xE2, 0x65, 0xA8, 0xC0 );
    /* VEX.DDS.128.66.0F38.W0 B8 /r VFMADD231PS xmm0,xmm1,xmm2/m128*/
    /* VEX.DDS.256.66.0F38.W0 B8 /r VFMADD231PS ymm0,ymm1,ymm2/m256*/
    FCML_I32( "vfmadd231ps xmm0,xmm3,xmmword ptr [eax]", 0xC4, 0xE2, 0x61, 0xB8, 0x00 );
    FCML_I64( "vfmadd231ps ymm0,ymm3,ymmword ptr [rax]", 0xC4, 0xE2, 0x65, 0xB8, 0x00 );
    FCML_I32( "vfmadd231ps ymm0,ymm3,ymm0", 0xC4, 0xE2, 0x65, 0xB8, 0xC0 );
    /* VFMADDPS xmm1, xmm2, xmm3/mem128, xmm4 C4 RXB.00011 0.src.0.01 68 /r /is4*/
    /* VFMADDPS ymm1, ymm2, ymm3/mem256, ymm4 C4 RXB.00011 0.src.1.01 68 /r /is4*/
    FCML_I64( "vfmaddps xmm2,xmm5,xmmword ptr [rcx+rax],xmm2", 0xC4, 0xE3, 0x51, 0x68, 0x14, 0x01, 0x20 );
    FCML_I64( "vfmaddps ymm2,ymm5,ymmword ptr [rcx+rax],ymm2", 0xC4, 0xE3, 0x55, 0x68, 0x14, 0x01, 0x20 );
    FCML_I64_M( "vfmaddps ymm0,ymm5,ymm0,ymm2", 2, FCML_MI( 0xc4, 0xe3, 0xd5, 0x68, 0xc2, 0x00 ), FCML_MI( 0xc4, 0xe3, 0x55, 0x68, 0xc0, 0x20 ) );
    /* VFMADDPS xmm1, xmm2, xmm3, xmm4/mem128 C4 RXB.00011 1.src.0.01 68 /r /is4*/
    /* VFMADDPS ymm1, ymm2, ymm3, ymm4/mem256 C4 RXB.00011 1.src.1.01 68 /r /is4*/
    FCML_I64( "vfmaddps xmm2,xmm5,xmm2,xmmword ptr [rcx+rax]", 0xC4, 0xE3, 0xD1, 0x68, 0x14, 0x01, 0x20 );
    FCML_I64( "vfmaddps ymm2,ymm5,ymm2,ymmword ptr [rcx+rax]", 0xC4, 0xE3, 0xD5, 0x68, 0x14, 0x01, 0x20 );
    FCML_I64_M( "vfmaddps ymm0,ymm5,ymm0,ymm2", 2, FCML_MI( 0xc4, 0xe3, 0xd5, 0x68, 0xc2, 0x00 ), FCML_MI( 0xc4, 0xe3, 0x55, 0x68, 0xc0, 0x20 ) );
    /* GAS*/
    FCML_A64( "vfmadd132ps (%rax),%xmm3,%xmm0", 0xc4, 0xe2, 0x61, 0x98, 0x00 );
    FCML_A64( "vfmadd132ps (%rax),%ymm3,%ymm0", 0xc4, 0xe2, 0x65, 0x98, 0x00 );
    FCML_A64( "vfmadd132ps %ymm0,%ymm3,%ymm0", 0xc4, 0xe2, 0x65, 0x98, 0xc0 );
    FCML_A64( "vfmadd213ps (%rax),%xmm3,%xmm0", 0xc4, 0xe2, 0x61, 0xa8, 0x00 );
    FCML_A64( "vfmadd213ps (%rax),%ymm3,%ymm0", 0xc4, 0xe2, 0x65, 0xa8, 0x00 );
    FCML_A64( "vfmadd213ps %ymm0,%ymm3,%ymm0", 0xc4, 0xe2, 0x65, 0xa8, 0xc0 );
    FCML_A64( "vfmadd231ps (%rax),%xmm3,%xmm0", 0xc4, 0xe2, 0x61, 0xb8, 0x00 );
    FCML_A64( "vfmadd231ps (%rax),%ymm3,%ymm0", 0xc4, 0xe2, 0x65, 0xb8, 0x00 );
    FCML_A64( "vfmadd231ps %ymm0,%ymm3,%ymm0", 0xc4, 0xe2, 0x65, 0xb8, 0xc0 );
    FCML_A64( "vfmaddps %xmm2,(%rcx,%rax),%xmm5,%xmm2", 0xc4, 0xe3, 0x51, 0x68, 0x14, 0x01, 0x20 );
    FCML_A64( "vfmaddps %ymm2,(%rcx,%rax),%ymm5,%ymm2", 0xc4, 0xe3, 0x55, 0x68, 0x14, 0x01, 0x20 );
    FCML_A64( "vfmaddps (%rcx,%rax),%xmm2,%xmm5,%xmm2", 0xc4, 0xe3, 0xd1, 0x68, 0x14, 0x01, 0x20 );
    FCML_A64( "vfmaddps (%rcx,%rax),%ymm2,%ymm5,%ymm2", 0xc4, 0xe3, 0xd5, 0x68, 0x14, 0x01, 0x20 );
}

void fcml_tf_instruction_VFMADDSD(void) {
    /* VEX.DDS.LIG.128.66.0F38.W1 99 /r VFMADD132SD xmm0,xmm1,xmm2/m64*/
    FCML_I64( "vfmadd132sd xmm0,xmm3,mmword ptr [rax]", 0xC4, 0xE2, 0xE1, 0x99, 0x00 );
    FCML_I64( "vfmadd132sd xmm0,xmm3,xmm0", 0xC4, 0xE2, 0xE1, 0x99, 0xC0 );
    /* VEX.DDS.LIG.128.66.0F38.W1 A9 /r VFMADD213SD xmm0,xmm1,xmm2/m64*/
    FCML_I64( "vfmadd213sd xmm0,xmm3,mmword ptr [rax]", 0xC4, 0xE2, 0xE1, 0xA9, 0x00 );
    FCML_I64( "vfmadd213sd xmm0,xmm3,xmm0", 0xC4, 0xE2, 0xE1, 0xA9, 0xC0 );
    /* VEX.DDS.LIG.128.66.0F38.W1 B9 /r VFMADD231SD xmm0,xmm1,xmm2/m64*/
    FCML_I64( "vfmadd231sd xmm0,xmm3,mmword ptr [rax]", 0xC4, 0xE2, 0xE1, 0xB9, 0x00 );
    FCML_I64( "vfmadd231sd xmm0,xmm3,xmm0", 0xC4, 0xE2, 0xE1, 0xB9, 0xC0 );
    /* VFMADDSD xmm1, xmm2, xmm3/mem128, xmm4 C4 RXB.00011 0.src.X.01 6B /r /is4*/
    /* VFMADDSD xmm1, xmm2, xmm3, xmm4/mem128 C4 RXB.00011 1.src.X.01 6B /r /is4*/
    FCML_I64( "vfmaddsd xmm2,xmm5,xmmword ptr [rcx+rax],xmm2", 0xC4, 0xE3, 0x51, 0x6B, 0x14, 0x01, 0x20 );
    FCML_I64_M( "vfmaddsd xmm0,xmm5,xmm0,xmm2", 2, FCML_MI( 0xc4, 0xe3, 0xd1, 0x6b, 0xc2, 0x00 ), FCML_MI( 0xc4, 0xe3, 0x51, 0x6b, 0xc0, 0x20 ) );
    FCML_I64( "vfmaddsd xmm2,xmm5,xmm2,xmmword ptr [rcx+rax]", 0xC4, 0xE3, 0xD1, 0x6B, 0x14, 0x01, 0x20 );
    FCML_I64_M( "vfmaddsd xmm0,xmm5,xmm2,xmm0", 2, FCML_MI( 0xc4, 0xe3, 0xd1, 0x6b, 0xc0, 0x20 ), FCML_MI( 0xc4, 0xe3, 0x51, 0x6b, 0xc2, 0x00 ) );
    /* GAS*/
    FCML_A64( "vfmadd132sd (%rax),%xmm3,%xmm0", 0xc4, 0xe2, 0xe1, 0x99, 0x00 );
    FCML_A64( "vfmadd132sd %xmm0,%xmm3,%xmm0", 0xc4, 0xe2, 0xe1, 0x99, 0xc0 );
    FCML_A64( "vfmadd213sd (%rax),%xmm3,%xmm0", 0xc4, 0xe2, 0xe1, 0xa9, 0x00 );
    FCML_A64( "vfmadd213sd %xmm0,%xmm3,%xmm0", 0xc4, 0xe2, 0xe1, 0xa9, 0xc0 );
    FCML_A64( "vfmadd231sd (%rax),%xmm3,%xmm0", 0xc4, 0xe2, 0xe1, 0xb9, 0x00 );
    FCML_A64( "vfmadd231sd %xmm0,%xmm3,%xmm0", 0xc4, 0xe2, 0xe1, 0xb9, 0xc0 );
    FCML_A64( "vfmaddsd %xmm2,(%rcx,%rax),%xmm5,%xmm2", 0xc4, 0xe3, 0x51, 0x6b, 0x14, 0x01, 0x20 );
}

void fcml_tf_instruction_VFMADDSS(void) {
    /* VEX.DDS.LIG.128.66.0F38.W0 99 /r VFMADD132SS xmm0,xmm1,xmm2/m32*/
    FCML_I32( "vfmadd132ss xmm0,xmm3,dword ptr [eax]", 0xC4, 0xE2, 0x61, 0x99, 0x00 );
    FCML_I64( "vfmadd132ss xmm0,xmm3,xmm0", 0xC4, 0xE2, 0x61, 0x99, 0xC0 );
    /* VEX.DDS.LIG.128.66.0F38.W0 A9 /r VFMADD213SS xmm0,xmm1,xmm2/m32*/
    FCML_I32( "vfmadd213ss xmm0,xmm3,dword ptr [eax]", 0xC4, 0xE2, 0x61, 0xA9, 0x00 );
    FCML_I64( "vfmadd213ss xmm0,xmm3,xmm0", 0xC4, 0xE2, 0x61, 0xA9, 0xC0 );
    /* VEX.DDS.LIG.128.66.0F38.W0 B9 /r VFMADD231SS xmm0,xmm1,xmm2/m32*/
    FCML_I32( "vfmadd231ss xmm0,xmm3,dword ptr [eax]", 0xC4, 0xE2, 0x61, 0xB9, 0x00 );
    FCML_I64( "vfmadd231ss xmm0,xmm3,xmm0", 0xC4, 0xE2, 0x61, 0xB9, 0xC0 );
    /* VFMADDSS xmm1, xmm2, xmm3/mem32, xmm4 C4 RXB.00011 0.src.X.01 6A /r /is4*/
    /* VFMADDSS xmm1, xmm2, xmm3, xmm4/mem32 C4 RXB.00011 1.src.X.01 6A /r /is4*/
    FCML_I64( "vfmaddss xmm2,xmm5,dword ptr [rcx+rax],xmm2", 0xC4, 0xE3, 0x51, 0x6A, 0x14, 0x01, 0x20 );
    FCML_I64_M( "vfmaddss xmm0,xmm5,xmm0,xmm2", 2, FCML_MI( 0xc4, 0xe3, 0xd1, 0x6a, 0xc2, 0x00 ), FCML_MI( 0xc4, 0xe3, 0x51, 0x6a, 0xc0, 0x20 ) );
    FCML_I64( "vfmaddss xmm2,xmm5,xmm2,dword ptr [rcx+rax]", 0xC4, 0xE3, 0xD1, 0x6A, 0x14, 0x01, 0x20 );
    FCML_I64_M( "vfmaddss xmm0,xmm5,xmm2,xmm0", 2, FCML_MI( 0xc4, 0xe3, 0xd1, 0x6a, 0xc0, 0x20 ), FCML_MI( 0xc4, 0xe3, 0x51, 0x6a, 0xc2, 0x00 ) );
    /* GAS*/
    FCML_A64( "vfmadd132ss (%rax),%xmm3,%xmm0", 0xc4, 0xe2, 0x61, 0x99, 0x00 );
    FCML_A64( "vfmadd132ss %xmm0,%xmm3,%xmm0", 0xc4, 0xe2, 0x61, 0x99, 0xc0 );
    FCML_A64( "vfmadd213ss (%rax),%xmm3,%xmm0", 0xc4, 0xe2, 0x61, 0xa9, 0x00 );
    FCML_A64( "vfmadd213ss %xmm0,%xmm3,%xmm0", 0xc4, 0xe2, 0x61, 0xa9, 0xc0 );
    FCML_A64( "vfmadd231ss (%rax),%xmm3,%xmm0", 0xc4, 0xe2, 0x61, 0xb9, 0x00 );
    FCML_A64( "vfmadd231ss %xmm0,%xmm3,%xmm0", 0xc4, 0xe2, 0x61, 0xb9, 0xc0 );
    FCML_A64( "vfmaddss %xmm2,(%rcx,%rax),%xmm5,%xmm2", 0xc4, 0xe3, 0x51, 0x6a, 0x14, 0x01, 0x20 );
}

void fcml_tf_instruction_VFMADDSUBPD(void) {
    /* VEX.DDS.128.66.0F38.W1 96 /r VFMADDSUB132PD xmm0,xmm1,xmm2/m128*/
    /* VEX.DDS.256.66.0F38.W1 96 /r VFMADDSUB132PD ymm0,ymm1,ymm2/m256*/
    FCML_I64( "vfmaddsub132pd xmm0,xmm3,xmmword ptr [rax]", 0xC4, 0xE2, 0xE1, 0x96, 0x00 );
    FCML_I64( "vfmaddsub132pd ymm0,ymm3,ymmword ptr [rax]", 0xC4, 0xE2, 0xE5, 0x96, 0x00 );
    FCML_I64( "vfmaddsub132pd ymm0,ymm3,ymm0", 0xC4, 0xE2, 0xE5, 0x96, 0xC0 );
    /* VEX.DDS.128.66.0F38.W1 A6 /r VFMADDSUB213PD xmm0,xmm1,xmm2/m128*/
    /* VEX.DDS.256.66.0F38.W1 A6 /r VFMADDSUB213PD ymm0,ymm1,ymm2/m256*/
    FCML_I64( "vfmaddsub213pd xmm0,xmm3,xmmword ptr [rax]", 0xC4, 0xE2, 0xE1, 0xA6, 0x00 );
    FCML_I64( "vfmaddsub213pd ymm0,ymm3,ymmword ptr [rax]", 0xC4, 0xE2, 0xE5, 0xA6, 0x00 );
    FCML_I64( "vfmaddsub213pd ymm0,ymm3,ymm0", 0xC4, 0xE2, 0xE5, 0xA6, 0xC0 );
    /* VEX.DDS.128.66.0F38.W1 B6 /r VFMADDSUB231PD xmm0,xmm1,xmm2/m128*/
    /* VEX.DDS.256.66.0F38.W1 B6 /r VFMADDSUB231PD ymm0,ymm1,ymm2/m256*/
    FCML_I64( "vfmaddsub231pd xmm0,xmm3,xmmword ptr [rax]", 0xC4, 0xE2, 0xE1, 0xB6, 0x00 );
    FCML_I64( "vfmaddsub231pd ymm0,ymm3,ymmword ptr [rax]", 0xC4, 0xE2, 0xE5, 0xB6, 0x00 );
    FCML_I64( "vfmaddsub231pd ymm0,ymm3,ymm0", 0xC4, 0xE2, 0xE5, 0xB6, 0xC0 );
    /* VFMADDSUBPD xmm1, xmm2, xmm3/mem128, xmm4 C4 RXB.00011 0.src.0.01 5D /r /is4*/
    /* VFMADDSUBPD ymm1, ymm2, ymm3/mem256, ymm4 C4 RXB.00011 0.src.1.01 5D /r /is4*/
    FCML_I32( "vfmaddsubpd xmm2,xmm5,xmmword ptr [ecx+eax],xmm2", 0xC4, 0xE3, 0x51, 0x5D, 0x14, 0x01, 0x20 );
    FCML_I64( "vfmaddsubpd ymm2,ymm5,ymmword ptr [rcx+rax],ymm2", 0xC4, 0xE3, 0x55, 0x5D, 0x14, 0x01, 0x20 );
    FCML_I64_M( "vfmaddsubpd ymm0,ymm5,ymm0,ymm2", 2, FCML_MI( 0xc4, 0xe3, 0xd5, 0x5d, 0xc2, 0x00 ), FCML_MI( 0xc4, 0xe3, 0x55, 0x5d, 0xc0, 0x20 ) );
    /* VFMADDSUBPD xmm1, xmm2, xmm3, xmm4/mem128 C4 RXB.00011 1.src.0.01 5D /r /is4*/
    /* VFMADDSUBPD ymm1, ymm2, ymm3, ymm4/mem256 C4 RXB.00011 1.src.1.01 5D /r /is4*/
    FCML_I64( "vfmaddsubpd xmm2,xmm5,xmm2,xmmword ptr [rcx+rax]", 0xC4, 0xE3, 0xD1, 0x5D, 0x14, 0x01, 0x20 );
    FCML_I64( "vfmaddsubpd ymm2,ymm5,ymm2,ymmword ptr [rcx+rax]", 0xC4, 0xE3, 0xD5, 0x5D, 0x14, 0x01, 0x20 );
    FCML_I64_M( "vfmaddsubpd ymm0,ymm5,ymm2,ymm0", 2, FCML_MI( 0xc4, 0xe3, 0xd5, 0x5d, 0xc0, 0x20 ), FCML_MI( 0xc4, 0xe3, 0x55, 0x5d, 0xc2, 0x00 ) );
    /* GAS*/
    FCML_A64( "vfmaddsub132pd (%rax),%xmm3,%xmm0", 0xc4, 0xe2, 0xe1, 0x96, 0x00 );
    FCML_A64( "vfmaddsub132pd (%rax),%ymm3,%ymm0", 0xc4, 0xe2, 0xe5, 0x96, 0x00 );
    FCML_A64( "vfmaddsub132pd %ymm0,%ymm3,%ymm0", 0xc4, 0xe2, 0xe5, 0x96, 0xc0 );
    FCML_A64( "vfmaddsub213pd (%rax),%xmm3,%xmm0", 0xc4, 0xe2, 0xe1, 0xa6, 0x00 );
    FCML_A64( "vfmaddsub213pd (%rax),%ymm3,%ymm0", 0xc4, 0xe2, 0xe5, 0xa6, 0x00 );
    FCML_A64( "vfmaddsub213pd %ymm0,%ymm3,%ymm0", 0xc4, 0xe2, 0xe5, 0xa6, 0xc0 );
    FCML_A64( "vfmaddsub231pd (%rax),%xmm3,%xmm0", 0xc4, 0xe2, 0xe1, 0xb6, 0x00 );
    FCML_A64( "vfmaddsub231pd (%rax),%ymm3,%ymm0", 0xc4, 0xe2, 0xe5, 0xb6, 0x00 );
    FCML_A64( "vfmaddsub231pd %ymm0,%ymm3,%ymm0", 0xc4, 0xe2, 0xe5, 0xb6, 0xc0 );
    FCML_A64( "vfmaddsubpd %xmm2,(%rcx,%rax),%xmm5,%xmm2", 0xc4, 0xe3, 0x51, 0x5d, 0x14, 0x01, 0x20 );
    FCML_A64( "vfmaddsubpd %ymm2,(%rcx,%rax),%ymm5,%ymm2", 0xc4, 0xe3, 0x55, 0x5d, 0x14, 0x01, 0x20 );
}

void fcml_tf_instruction_VFMADDSUBPS(void) {
    /* VEX.DDS.128.66.0F38.W0 96 /r VFMADDSUB132PS xmm0,xmm1,xmm2/m128*/
    /* VEX.DDS.256.66.0F38.W0 96 /r VFMADDSUB132PS ymm0,ymm1,ymm2/m256*/
    FCML_I32( "vfmaddsub132ps xmm0,xmm3,xmmword ptr [eax]", 0xC4, 0xE2, 0x61, 0x96, 0x00 );
    FCML_I64( "vfmaddsub132ps ymm0,ymm3,ymmword ptr [rax]", 0xC4, 0xE2, 0x65, 0x96, 0x00 );
    FCML_I32( "vfmaddsub132ps ymm0,ymm3,ymm0", 0xC4, 0xE2, 0x65, 0x96, 0xC0 );
    /* VEX.DDS.128.66.0F38.W0 A6 /r VFMADDSUB213PS xmm0,xmm1,xmm2/m128*/
    /* VEX.DDS.256.66.0F38.W0 A6 /r VFMADDSUB213PS ymm0,ymm1,ymm2/m256*/
    FCML_I32( "vfmaddsub213ps xmm0,xmm3,xmmword ptr [eax]", 0xC4, 0xE2, 0x61, 0xA6, 0x00 );
    FCML_I64( "vfmaddsub213ps ymm0,ymm3,ymmword ptr [rax]", 0xC4, 0xE2, 0x65, 0xA6, 0x00 );
    FCML_I32( "vfmaddsub213ps ymm0,ymm3,ymm0", 0xC4, 0xE2, 0x65, 0xA6, 0xC0 );
    /* VEX.DDS.128.66.0F38.W0 B6 /r VFMADDSUB231PS xmm0,xmm1,xmm2/m128*/
    /* VEX.DDS.256.66.0F38.W0 B6 /r VFMADDSUB231PS ymm0,ymm1,ymm2/m256*/
    FCML_I32( "vfmaddsub231ps xmm0,xmm3,xmmword ptr [eax]", 0xC4, 0xE2, 0x61, 0xB6, 0x00 );
    FCML_I64( "vfmaddsub231ps ymm0,ymm3,ymmword ptr [rax]", 0xC4, 0xE2, 0x65, 0xB6, 0x00 );
    FCML_I32( "vfmaddsub231ps ymm0,ymm3,ymm0", 0xC4, 0xE2, 0x65, 0xB6, 0xC0 );
    /* VFMADDSUBPS xmm1, xmm2, xmm3/mem128, xmm4 C4 RXB.00011 0.src.0.01 5C /r /is4*/
    /* VFMADDSUBPS ymm1, ymm2, ymm3/mem256, ymm4 C4 RXB.00011 0.src.1.01 5C /r /is4*/
    FCML_I64( "vfmaddsubps xmm2,xmm5,xmmword ptr [rcx+rax],xmm2", 0xC4, 0xE3, 0x51, 0x5C, 0x14, 0x01, 0x20 );
    FCML_I64( "vfmaddsubps ymm2,ymm5,ymmword ptr [rcx+rax],ymm2", 0xC4, 0xE3, 0x55, 0x5C, 0x14, 0x01, 0x20 );
    FCML_I64_M( "vfmaddsubps ymm0,ymm5,ymm0,ymm2", 2, FCML_MI( 0xc4, 0xe3, 0xd5, 0x5c, 0xc2, 0x00 ), FCML_MI( 0xc4, 0xe3, 0x55, 0x5c, 0xc0, 0x20 ) );
    /* VFMADDSUBPS xmm1, xmm2, xmm3, xmm4/mem128 C4 RXB.00011 1.src.0.01 5C /r /is4*/
    /* VFMADDSUBPS ymm1, ymm2, ymm3, ymm4/mem256 C4 RXB.00011 1.src.1.01 5C /r /is4*/
    FCML_I64( "vfmaddsubps xmm2,xmm5,xmm2,xmmword ptr [rcx+rax]", 0xC4, 0xE3, 0xD1, 0x5C, 0x14, 0x01, 0x20 );
    FCML_I64( "vfmaddsubps ymm2,ymm5,ymm2,ymmword ptr [rcx+rax]", 0xC4, 0xE3, 0xD5, 0x5C, 0x14, 0x01, 0x20 );
    FCML_I64_M( "vfmaddsubps ymm0,ymm5,ymm2,ymm0", 2, FCML_MI( 0xc4, 0xe3, 0xd5, 0x5c, 0xc0, 0x20 ), FCML_MI( 0xc4, 0xe3, 0x55, 0x5c, 0xc2, 0x00 ) );
    /* GAS*/
    FCML_A64( "vfmaddsub132ps (%rax),%xmm3,%xmm0", 0xc4, 0xe2, 0x61, 0x96, 0x00 );
    FCML_A64( "vfmaddsub132ps (%rax),%ymm3,%ymm0", 0xc4, 0xe2, 0x65, 0x96, 0x00 );
    FCML_A64( "vfmaddsub132ps %ymm0,%ymm3,%ymm0", 0xc4, 0xe2, 0x65, 0x96, 0xc0 );
    FCML_A64( "vfmaddsub213ps (%rax),%xmm3,%xmm0", 0xc4, 0xe2, 0x61, 0xa6, 0x00 );
    FCML_A64( "vfmaddsub213ps (%rax),%ymm3,%ymm0", 0xc4, 0xe2, 0x65, 0xa6, 0x00 );
    FCML_A64( "vfmaddsub213ps %ymm0,%ymm3,%ymm0", 0xc4, 0xe2, 0x65, 0xa6, 0xc0 );
    FCML_A64( "vfmaddsub231ps (%rax),%xmm3,%xmm0", 0xc4, 0xe2, 0x61, 0xb6, 0x00 );
    FCML_A64( "vfmaddsub231ps (%rax),%ymm3,%ymm0", 0xc4, 0xe2, 0x65, 0xb6, 0x00 );
    FCML_A64( "vfmaddsub231ps %ymm0,%ymm3,%ymm0", 0xc4, 0xe2, 0x65, 0xb6, 0xc0 );
    FCML_A64( "vfmaddsubps %xmm2,(%rcx,%rax),%xmm5,%xmm2", 0xc4, 0xe3, 0x51, 0x5c, 0x14, 0x01, 0x20 );
    FCML_A64( "vfmaddsubps %ymm2,(%rcx,%rax),%ymm5,%ymm2", 0xc4, 0xe3, 0x55, 0x5c, 0x14, 0x01, 0x20 );
}

void fcml_tf_instruction_VFMSUBADDPD(void) {
    /* VEX.DDS.128.66.0F38.W1 97 /r VFMSUBADD132PD xmm0,xmm1,xmm2/m128*/
    /* VEX.DDS.256.66.0F38.W1 97 /r VFMSUBADD132PD ymm0,ymm1,ymm2/m256*/
    FCML_I64( "vfmsubadd132pd xmm0,xmm3,xmmword ptr [rax]", 0xC4, 0xE2, 0xE1, 0x97, 0x00 );
    FCML_I64( "vfmsubadd132pd ymm0,ymm3,ymmword ptr [rax]", 0xC4, 0xE2, 0xE5, 0x97, 0x00 );
    FCML_I64( "vfmsubadd132pd ymm0,ymm3,ymm0", 0xC4, 0xE2, 0xE5, 0x97, 0xC0 );
    /* VEX.DDS.128.66.0F38.W1 A7 /r VFMSUBADD213PD xmm0,xmm1,xmm2/m128*/
    /* VEX.DDS.256.66.0F38.W1 A7 /r VFMSUBADD213PD ymm0,ymm1,ymm2/m256*/
    FCML_I64( "vfmsubadd213pd xmm0,xmm3,xmmword ptr [rax]", 0xC4, 0xE2, 0xE1, 0xA7, 0x00 );
    FCML_I64( "vfmsubadd213pd ymm0,ymm3,ymmword ptr [rax]", 0xC4, 0xE2, 0xE5, 0xA7, 0x00 );
    FCML_I64( "vfmsubadd213pd ymm0,ymm3,ymm0", 0xC4, 0xE2, 0xE5, 0xA7, 0xC0 );
    /* VEX.DDS.128.66.0F38.W1 B7 /r VFMSUBADD231PD xmm0,xmm1,xmm2/m128*/
    /* VEX.DDS.256.66.0F38.W1 B7 /r VFMSUBADD231PD ymm0,ymm1,ymm2/m256*/
    FCML_I64( "vfmsubadd231pd xmm0,xmm3,xmmword ptr [rax]", 0xC4, 0xE2, 0xE1, 0xB7, 0x00 );
    FCML_I64( "vfmsubadd231pd ymm0,ymm3,ymmword ptr [rax]", 0xC4, 0xE2, 0xE5, 0xB7, 0x00 );
    FCML_I64( "vfmsubadd231pd ymm0,ymm3,ymm0", 0xC4, 0xE2, 0xE5, 0xB7, 0xC0 );
    /* VFMSUBADDPD xmm1, xmm2, xmm3/mem128, xmm4 C4 RXB.00011 0.src.0.01 5F /r /is4*/
    /* VFMSUBADDPD ymm1, ymm2, ymm3/mem256, ymm4 C4 RXB.00011 0.src.1.01 5F /r /is4*/
    FCML_I32( "vfmsubaddpd xmm2,xmm5,xmmword ptr [ecx+eax],xmm2", 0xC4, 0xE3, 0x51, 0x5F, 0x14, 0x01, 0x20 );
    FCML_I64( "vfmsubaddpd ymm2,ymm5,ymmword ptr [rcx+rax],ymm2", 0xC4, 0xE3, 0x55, 0x5F, 0x14, 0x01, 0x20 );
    FCML_I64_M( "vfmsubaddpd ymm0,ymm5,ymm0,ymm2", 2, FCML_MI( 0xc4, 0xe3, 0xd5, 0x5f, 0xc2, 0x00 ), FCML_MI( 0xc4, 0xe3, 0x55, 0x5f, 0xc0, 0x20 ) );
    /* VFMSUBADDPD xmm1, xmm2, xmm3, xmm4/mem128 C4 RXB.00011 1.src.0.01 5F /r /is4*/
    /* VFMSUBADDPD ymm1, ymm2, ymm3, ymm4/mem256 C4 RXB.00011 1.src.1.01 5F /r /is4*/
    FCML_I64( "vfmsubaddpd xmm2,xmm5,xmm2,xmmword ptr [rcx+rax]", 0xC4, 0xE3, 0xD1, 0x5F, 0x14, 0x01, 0x20 );
    FCML_I64( "vfmsubaddpd ymm2,ymm5,ymm2,ymmword ptr [rcx+rax]", 0xC4, 0xE3, 0xD5, 0x5F, 0x14, 0x01, 0x20 );
    FCML_I64_M( "vfmsubaddpd ymm0,ymm5,ymm2,ymm0", 2, FCML_MI( 0xc4, 0xe3, 0xd5, 0x5f, 0xc0, 0x20 ), FCML_MI( 0xc4, 0xe3, 0x55, 0x5f, 0xc2, 0x00 ) );
    /* GAS*/
    FCML_A64( "vfmsubadd132pd (%rax),%xmm3,%xmm0", 0xc4, 0xe2, 0xe1, 0x97, 0x00 );
    FCML_A64( "vfmsubadd132pd (%rax),%ymm3,%ymm0", 0xc4, 0xe2, 0xe5, 0x97, 0x00 );
    FCML_A64( "vfmsubadd132pd %ymm0,%ymm3,%ymm0", 0xc4, 0xe2, 0xe5, 0x97, 0xc0 );
    FCML_A64( "vfmsubadd213pd (%rax),%xmm3,%xmm0", 0xc4, 0xe2, 0xe1, 0xa7, 0x00 );
    FCML_A64( "vfmsubadd213pd (%rax),%ymm3,%ymm0", 0xc4, 0xe2, 0xe5, 0xa7, 0x00 );
    FCML_A64( "vfmsubadd213pd %ymm0,%ymm3,%ymm0", 0xc4, 0xe2, 0xe5, 0xa7, 0xc0 );
    FCML_A64( "vfmsubadd231pd (%rax),%xmm3,%xmm0", 0xc4, 0xe2, 0xe1, 0xb7, 0x00 );
    FCML_A64( "vfmsubadd231pd (%rax),%ymm3,%ymm0", 0xc4, 0xe2, 0xe5, 0xb7, 0x00 );
    FCML_A64( "vfmsubadd231pd %ymm0,%ymm3,%ymm0", 0xc4, 0xe2, 0xe5, 0xb7, 0xc0 );
    FCML_A64( "vfmsubaddpd %xmm2,(%rcx,%rax),%xmm5,%xmm2", 0xc4, 0xe3, 0x51, 0x5f, 0x14, 0x01, 0x20 );
    FCML_A64( "vfmsubaddpd %ymm2,(%rcx,%rax),%ymm5,%ymm2", 0xc4, 0xe3, 0x55, 0x5f, 0x14, 0x01, 0x20 );
}

void fcml_tf_instruction_VFMSUBADDPS(void) {
    /* VEX.DDS.128.66.0F38.W0 97 /r VFMSUBADD132PS xmm0,xmm1,xmm2/m128*/
    /* VEX.DDS.256.66.0F38.W0 97 /r VFMSUBADD132PS ymm0,ymm1,ymm2/m256*/
    FCML_I32( "vfmsubadd132ps xmm0,xmm3,xmmword ptr [eax]", 0xC4, 0xE2, 0x61, 0x97, 0x00 );
    FCML_I64( "vfmsubadd132ps ymm0,ymm3,ymmword ptr [rax]", 0xC4, 0xE2, 0x65, 0x97, 0x00 );
    FCML_I32( "vfmsubadd132ps ymm0,ymm3,ymm0", 0xC4, 0xE2, 0x65, 0x97, 0xC0 );
    /* VEX.DDS.128.66.0F38.W0 A7 /r VFMSUBADD213PS xmm0,xmm1,xmm2/m128*/
    /* VEX.DDS.256.66.0F38.W0 A7 /r VFMSUBADD213PS ymm0,ymm1,ymm2/m256*/
    FCML_I32( "vfmsubadd213ps xmm0,xmm3,xmmword ptr [eax]", 0xC4, 0xE2, 0x61, 0xA7, 0x00 );
    FCML_I64( "vfmsubadd213ps ymm0,ymm3,ymmword ptr [rax]", 0xC4, 0xE2, 0x65, 0xA7, 0x00 );
    FCML_I32( "vfmsubadd213ps ymm0,ymm3,ymm0", 0xC4, 0xE2, 0x65, 0xA7, 0xC0 );
    /* VEX.DDS.128.66.0F38.W0 B7 /r VFMSUBADD231PS xmm0,xmm1,xmm2/m128*/
    /* VEX.DDS.256.66.0F38.W0 B7 /r VFMSUBADD231PS ymm0,ymm1,ymm2/m256*/
    FCML_I32( "vfmsubadd231ps xmm0,xmm3,xmmword ptr [eax]", 0xC4, 0xE2, 0x61, 0xB7, 0x00 );
    FCML_I64( "vfmsubadd231ps ymm0,ymm3,ymmword ptr [rax]", 0xC4, 0xE2, 0x65, 0xB7, 0x00 );
    FCML_I32( "vfmsubadd231ps ymm0,ymm3,ymm0", 0xC4, 0xE2, 0x65, 0xB7, 0xC0 );
    /* VFMSUBADDPS xmm1, xmm2, xmm3/mem128, xmm4 C4 RXB.00011 0.src.0.01 5E /r /is4*/
    /* VFMSUBADDPS ymm1, ymm2, ymm3/mem256, ymm4 C4 RXB.00011 0.src.1.01 5E /r /is4*/
    FCML_I64( "vfmsubaddps xmm2,xmm5,xmmword ptr [rcx+rax],xmm2", 0xC4, 0xE3, 0x51, 0x5E, 0x14, 0x01, 0x20 );
    FCML_I64( "vfmsubaddps ymm2,ymm5,ymmword ptr [rcx+rax],ymm2", 0xC4, 0xE3, 0x55, 0x5E, 0x14, 0x01, 0x20 );
    FCML_I64_M( "vfmsubaddps ymm0,ymm5,ymm0,ymm2", 2, FCML_MI( 0xc4, 0xe3, 0xd5, 0x5e, 0xc2, 0x00 ), FCML_MI( 0xc4, 0xe3, 0x55, 0x5e, 0xc0, 0x20 ) );
    /* VFMSUBADDPS xmm1, xmm2, xmm3, xmm4/mem128 C4 RXB.00011 1.src.0.01 5E /r /is4*/
    /* VFMSUBADDPS ymm1, ymm2, ymm3, ymm4/mem256 C4 RXB.00011 1.src.1.01 5E /r /is4*/
    FCML_I64( "vfmsubaddps xmm2,xmm5,xmm2,xmmword ptr [rcx+rax]", 0xC4, 0xE3, 0xD1, 0x5E, 0x14, 0x01, 0x20 );
    FCML_I64( "vfmsubaddps ymm2,ymm5,ymm2,ymmword ptr [rcx+rax]", 0xC4, 0xE3, 0xD5, 0x5E, 0x14, 0x01, 0x20 );
    FCML_I64_M( "vfmsubaddps ymm0,ymm5,ymm2,ymm0", 2, FCML_MI( 0xc4, 0xe3, 0xd5, 0x5e, 0xc0, 0x20 ), FCML_MI( 0xc4, 0xe3, 0x55, 0x5e, 0xc2, 0x00 ) );
    /* GAS*/
    FCML_A64( "vfmsubadd132ps (%rax),%xmm3,%xmm0", 0xc4, 0xe2, 0x61, 0x97, 0x00 );
    FCML_A64( "vfmsubadd132ps (%rax),%ymm3,%ymm0", 0xc4, 0xe2, 0x65, 0x97, 0x00 );
    FCML_A64( "vfmsubadd132ps %ymm0,%ymm3,%ymm0", 0xc4, 0xe2, 0x65, 0x97, 0xc0 );
    FCML_A64( "vfmsubadd213ps (%rax),%xmm3,%xmm0", 0xc4, 0xe2, 0x61, 0xa7, 0x00 );
    FCML_A64( "vfmsubadd213ps (%rax),%ymm3,%ymm0", 0xc4, 0xe2, 0x65, 0xa7, 0x00 );
    FCML_A64( "vfmsubadd213ps %ymm0,%ymm3,%ymm0", 0xc4, 0xe2, 0x65, 0xa7, 0xc0 );
    FCML_A64( "vfmsubadd231ps (%rax),%xmm3,%xmm0", 0xc4, 0xe2, 0x61, 0xb7, 0x00 );
    FCML_A64( "vfmsubadd231ps (%rax),%ymm3,%ymm0", 0xc4, 0xe2, 0x65, 0xb7, 0x00 );
    FCML_A64( "vfmsubadd231ps %ymm0,%ymm3,%ymm0", 0xc4, 0xe2, 0x65, 0xb7, 0xc0 );
    FCML_A64( "vfmsubaddps %xmm2,(%rcx,%rax),%xmm5,%xmm2", 0xc4, 0xe3, 0x51, 0x5e, 0x14, 0x01, 0x20 );
    FCML_A64( "vfmsubaddps %ymm2,(%rcx,%rax),%ymm5,%ymm2", 0xc4, 0xe3, 0x55, 0x5e, 0x14, 0x01, 0x20 );
}

void fcml_tf_instruction_VFMSUBPD(void) {
    /* VEX.DDS.128.66.0F38.W1 9A /r VFMSUB132PD xmm0,xmm1,xmm2/m128*/
    /* VEX.DDS.256.66.0F38.W1 9A /r VFMSUB132PD ymm0,ymm1,ymm2/m256*/
    FCML_I64( "vfmsub132pd xmm0,xmm3,xmmword ptr [rax]", 0xC4, 0xE2, 0xE1, 0x9A, 0x00 );
    FCML_I64( "vfmsub132pd ymm0,ymm3,ymmword ptr [rax]", 0xC4, 0xE2, 0xE5, 0x9A, 0x00 );
    FCML_I64( "vfmsub132pd ymm0,ymm3,ymm0", 0xC4, 0xE2, 0xE5, 0x9A, 0xC0 );
    /* VEX.DDS.128.66.0F38.W1 AA /r VFMSUB213PD xmm0,xmm1,xmm2/m128*/
    /* VEX.DDS.256.66.0F38.W1 AA /r VFMSUB213PD ymm0,ymm1,ymm2/m256*/
    FCML_I64( "vfmsub213pd xmm0,xmm3,xmmword ptr [rax]", 0xC4, 0xE2, 0xE1, 0xAA, 0x00 );
    FCML_I64( "vfmsub213pd ymm0,ymm3,ymmword ptr [rax]", 0xC4, 0xE2, 0xE5, 0xAA, 0x00 );
    FCML_I64( "vfmsub213pd ymm0,ymm3,ymm0", 0xC4, 0xE2, 0xE5, 0xAA, 0xC0 );
    /* VEX.DDS.128.66.0F38.W1 BA /r VFMSUB231PD xmm0,xmm1,xmm2/m128*/
    /* VEX.DDS.256.66.0F38.W1 BA /r VFMSUB231PD ymm0,ymm1,ymm2/m256*/
    FCML_I64( "vfmsub231pd xmm0,xmm3,xmmword ptr [rax]", 0xC4, 0xE2, 0xE1, 0xBA, 0x00 );
    FCML_I64( "vfmsub231pd ymm0,ymm3,ymmword ptr [rax]", 0xC4, 0xE2, 0xE5, 0xBA, 0x00 );
    FCML_I64( "vfmsub231pd ymm0,ymm3,ymm0", 0xC4, 0xE2, 0xE5, 0xBA, 0xC0 );
    /* VFMSUBPD xmm1, xmm2, xmm3/mem128, xmm4 C4 RXB.00011 0.src.0.01 6D /r /is4*/
    /* VFMSUBPD ymm1, ymm2, ymm3/mem256, ymm4 C4 RXB.00011 0.src.1.01 6D /r /is4*/
    FCML_I32( "vfmsubpd xmm2,xmm5,xmmword ptr [ecx+eax],xmm2", 0xC4, 0xE3, 0x51, 0x6D, 0x14, 0x01, 0x20 );
    FCML_I64( "vfmsubpd ymm2,ymm5,ymmword ptr [rcx+rax],ymm2", 0xC4, 0xE3, 0x55, 0x6D, 0x14, 0x01, 0x20 );
    FCML_I64_M( "vfmsubpd ymm0,ymm5,ymm0,ymm2", 2, FCML_MI( 0xc4, 0xe3, 0xd5, 0x6d, 0xc2, 0x00 ), FCML_MI( 0xc4, 0xe3, 0x55, 0x6d, 0xc0, 0x20 ) );
    /* VFMSUBPD xmm1, xmm2, xmm3, xmm4/mem128 C4 RXB.00011 1.src.0.01 6D /r /is4*/
    /* VFMSUBPD ymm1, ymm2, ymm3, ymm4/mem256 C4 RXB.00011 1.src.1.01 6D /r /is4*/
    FCML_I64( "vfmsubpd xmm2,xmm5,xmm2,xmmword ptr [rcx+rax]", 0xC4, 0xE3, 0xD1, 0x6D, 0x14, 0x01, 0x20 );
    FCML_I64( "vfmsubpd ymm2,ymm5,ymm2,ymmword ptr [rcx+rax]", 0xC4, 0xE3, 0xD5, 0x6D, 0x14, 0x01, 0x20 );
    FCML_I64_M( "vfmsubpd ymm0,ymm5,ymm2,ymm0", 2, FCML_MI( 0xc4, 0xe3, 0xd5, 0x6d, 0xc0, 0x20 ), FCML_MI( 0xc4, 0xe3, 0x55, 0x6d, 0xc2, 0x00 ) );
    /* GAS*/
    FCML_A64( "vfmsub132pd (%rax),%xmm3,%xmm0", 0xc4, 0xe2, 0xe1, 0x9a, 0x00 );
    FCML_A64( "vfmsub132pd (%rax),%ymm3,%ymm0", 0xc4, 0xe2, 0xe5, 0x9a, 0x00 );
    FCML_A64( "vfmsub132pd %ymm0,%ymm3,%ymm0", 0xc4, 0xe2, 0xe5, 0x9a, 0xc0 );
    FCML_A64( "vfmsub213pd (%rax),%xmm3,%xmm0", 0xc4, 0xe2, 0xe1, 0xaa, 0x00 );
    FCML_A64( "vfmsub213pd (%rax),%ymm3,%ymm0", 0xc4, 0xe2, 0xe5, 0xaa, 0x00 );
    FCML_A64( "vfmsub213pd %ymm0,%ymm3,%ymm0", 0xc4, 0xe2, 0xe5, 0xaa, 0xc0 );
    FCML_A64( "vfmsub231pd (%rax),%xmm3,%xmm0", 0xc4, 0xe2, 0xe1, 0xba, 0x00 );
    FCML_A64( "vfmsub231pd (%rax),%ymm3,%ymm0", 0xc4, 0xe2, 0xe5, 0xba, 0x00 );
    FCML_A64( "vfmsub231pd %ymm0,%ymm3,%ymm0", 0xc4, 0xe2, 0xe5, 0xba, 0xc0 );
    FCML_A64( "vfmsubpd %xmm2,(%rcx,%rax),%xmm5,%xmm2", 0xc4, 0xe3, 0x51, 0x6d, 0x14, 0x01, 0x20 );
    FCML_A64( "vfmsubpd %ymm2,(%rcx,%rax),%ymm5,%ymm2", 0xc4, 0xe3, 0x55, 0x6d, 0x14, 0x01, 0x20 );
}

void fcml_tf_instruction_VFMSUBPS(void) {
    /* VEX.DDS.128.66.0F38.W0 9A /r VFMSUB132PS xmm0,xmm1,xmm2/m128*/
    /* VEX.DDS.256.66.0F38.W0 9A /r VFMSUB132PS ymm0,ymm1,ymm2/m256*/
    FCML_I32( "vfmsub132ps xmm0,xmm3,xmmword ptr [eax]", 0xC4, 0xE2, 0x61, 0x9A, 0x00 );
    FCML_I64( "vfmsub132ps ymm0,ymm3,ymmword ptr [rax]", 0xC4, 0xE2, 0x65, 0x9A, 0x00 );
    FCML_I32( "vfmsub132ps ymm0,ymm3,ymm0", 0xC4, 0xE2, 0x65, 0x9A, 0xC0 );
    /* VEX.DDS.128.66.0F38.W0 AA /r VFMSUB213PS xmm0,xmm1,xmm2/m128*/
    /* VEX.DDS.256.66.0F38.W0 AA /r VFMSUB213PS ymm0,ymm1,ymm2/m256*/
    FCML_I32( "vfmsub213ps xmm0,xmm3,xmmword ptr [eax]", 0xC4, 0xE2, 0x61, 0xAA, 0x00 );
    FCML_I64( "vfmsub213ps ymm0,ymm3,ymmword ptr [rax]", 0xC4, 0xE2, 0x65, 0xAA, 0x00 );
    FCML_I32( "vfmsub213ps ymm0,ymm3,ymm0", 0xC4, 0xE2, 0x65, 0xAA, 0xC0 );
    /* VEX.DDS.128.66.0F38.W0 BA /r VFMSUB231PS xmm0,xmm1,xmm2/m128*/
    /* VEX.DDS.256.66.0F38.W0 BA /r VFMSUB231PS ymm0,ymm1,ymm2/m256*/
    FCML_I32( "vfmsub231ps xmm0,xmm3,xmmword ptr [eax]", 0xC4, 0xE2, 0x61, 0xBA, 0x00 );
    FCML_I64( "vfmsub231ps ymm0,ymm3,ymmword ptr [rax]", 0xC4, 0xE2, 0x65, 0xBA, 0x00 );
    FCML_I32( "vfmsub231ps ymm0,ymm3,ymm0", 0xC4, 0xE2, 0x65, 0xBA, 0xC0 );
    /* VFMSUBPS xmm1, xmm2, xmm3/mem128, xmm4 C4 RXB.00011 0.src.0.01 6C /r /is4*/
    /* VFMSUBPS ymm1, ymm2, ymm3/mem256, ymm4 C4 RXB.00011 0.src.1.01 6C /r /is4*/
    FCML_I64( "vfmsubps xmm2,xmm5,xmmword ptr [rcx+rax],xmm2", 0xC4, 0xE3, 0x51, 0x6C, 0x14, 0x01, 0x20 );
    FCML_I64( "vfmsubps ymm2,ymm5,ymmword ptr [rcx+rax],ymm2", 0xC4, 0xE3, 0x55, 0x6C, 0x14, 0x01, 0x20 );
    FCML_I64_M( "vfmsubps ymm0,ymm5,ymm0,ymm2", 2, FCML_MI( 0xc4, 0xe3, 0xd5, 0x6c, 0xc2, 0x00 ), FCML_MI( 0xc4, 0xe3, 0x55, 0x6c, 0xc0, 0x20 ) );
    /* VFMSUBPS xmm1, xmm2, xmm3, xmm4/mem128 C4 RXB.00011 1.src.0.01 6C /r /is4*/
    /* VFMSUBPS ymm1, ymm2, ymm3, ymm4/mem256 C4 RXB.00011 1.src.1.01 6C /r /is4*/
    FCML_I64( "vfmsubps xmm2,xmm5,xmm2,xmmword ptr [rcx+rax]", 0xC4, 0xE3, 0xD1, 0x6C, 0x14, 0x01, 0x20 );
    FCML_I64( "vfmsubps ymm2,ymm5,ymm2,ymmword ptr [rcx+rax]", 0xC4, 0xE3, 0xD5, 0x6C, 0x14, 0x01, 0x20 );
    FCML_I64_M( "vfmsubps ymm0,ymm5,ymm2,ymm0", 2, FCML_MI( 0xc4, 0xe3, 0xd5, 0x6c, 0xc0, 0x20 ), FCML_MI( 0xc4, 0xe3, 0x55, 0x6c, 0xc2, 0x00 ) );
    /* GAS*/
    FCML_A64( "vfmsub132ps (%rax),%xmm3,%xmm0", 0xc4, 0xe2, 0x61, 0x9a, 0x00 );
    FCML_A64( "vfmsub132ps (%rax),%ymm3,%ymm0", 0xc4, 0xe2, 0x65, 0x9a, 0x00 );
    FCML_A64( "vfmsub132ps %ymm0,%ymm3,%ymm0", 0xc4, 0xe2, 0x65, 0x9a, 0xc0 );
    FCML_A64( "vfmsub213ps (%rax),%xmm3,%xmm0", 0xc4, 0xe2, 0x61, 0xaa, 0x00 );
    FCML_A64( "vfmsub213ps (%rax),%ymm3,%ymm0", 0xc4, 0xe2, 0x65, 0xaa, 0x00 );
    FCML_A64( "vfmsub213ps %ymm0,%ymm3,%ymm0", 0xc4, 0xe2, 0x65, 0xaa, 0xc0 );
    FCML_A64( "vfmsub231ps (%rax),%xmm3,%xmm0", 0xc4, 0xe2, 0x61, 0xba, 0x00 );
    FCML_A64( "vfmsub231ps (%rax),%ymm3,%ymm0", 0xc4, 0xe2, 0x65, 0xba, 0x00 );
    FCML_A64( "vfmsub231ps %ymm0,%ymm3,%ymm0", 0xc4, 0xe2, 0x65, 0xba, 0xc0 );
    FCML_A64( "vfmsubps %xmm2,(%rcx,%rax),%xmm5,%xmm2", 0xc4, 0xe3, 0x51, 0x6c, 0x14, 0x01, 0x20 );
    FCML_A64( "vfmsubps %ymm2,(%rcx,%rax),%ymm5,%ymm2", 0xc4, 0xe3, 0x55, 0x6c, 0x14, 0x01, 0x20 );
}

void fcml_tf_instruction_VFMSUBSD(void) {
    /* VEX.DDS.LIG.128.66.0F38.W1 9B /r VFMSUB132SD xmm0,xmm1,xmm2/m64*/
    FCML_I64( "vfmsub132sd xmm0,xmm3,mmword ptr [rax]", 0xC4, 0xE2, 0xE1, 0x9B, 0x00 );
    FCML_I64( "vfmsub132sd xmm0,xmm3,xmm0", 0xC4, 0xE2, 0xE1, 0x9B, 0xC0 );
    /* VEX.DDS.LIG.128.66.0F38.W1 AB /r VFMSUB213SD xmm0,xmm1,xmm2/m64*/
    FCML_I64( "vfmsub213sd xmm0,xmm3,mmword ptr [rax]", 0xC4, 0xE2, 0xE1, 0xAB, 0x00 );
    FCML_I64( "vfmsub213sd xmm0,xmm3,xmm0", 0xC4, 0xE2, 0xE1, 0xAB, 0xC0 );
    /* VEX.DDS.LIG.128.66.0F38.W1 BB /r VFMSUB231SD xmm0,xmm1,xmm2/m64*/
    FCML_I64( "vfmsub231sd xmm0,xmm3,mmword ptr [rax]", 0xC4, 0xE2, 0xE1, 0xBB, 0x00 );
    FCML_I64( "vfmsub231sd xmm0,xmm3,xmm0", 0xC4, 0xE2, 0xE1, 0xBB, 0xC0 );
    /* VFMSUBSD xmm1, xmm2, xmm3/mem64, xmm4 C4 RXB.00011 0.src.X.01 6F /r /is4*/
    /* VFMSUBSD xmm1, xmm2, xmm3, xmm4/mem64 C4 RXB.00011 1.src.X.01 6F /r /is4*/
    FCML_I32( "vfmsubsd xmm2,xmm5,mmword ptr [ecx+eax],xmm2", 0xC4, 0xE3, 0x51, 0x6F, 0x14, 0x01, 0x20 );
    FCML_I64_M( "vfmsubsd xmm0,xmm5,xmm0,xmm2", 2, FCML_MI( 0xc4, 0xe3, 0xd1, 0x6f, 0xc2, 0x00 ), FCML_MI( 0xc4, 0xe3, 0x51, 0x6f, 0xc0, 0x20 ) );
    FCML_I64( "vfmsubsd xmm2,xmm5,xmm2,mmword ptr [rcx+rax]", 0xC4, 0xE3, 0xD1, 0x6F, 0x14, 0x01, 0x20 );
    FCML_I64_M( "vfmsubsd xmm0,xmm5,xmm2,xmm0", 2, FCML_MI( 0xc4, 0xe3, 0xd1, 0x6f, 0xc0, 0x20 ), FCML_MI( 0xc4, 0xe3, 0x51, 0x6f, 0xc2, 0x00 ) );
    /* GAS*/
    FCML_A64( "vfmsub132sd (%rax),%xmm3,%xmm0", 0xc4, 0xe2, 0xe1, 0x9b, 0x00 );
    FCML_A64( "vfmsub132sd %xmm0,%xmm3,%xmm0", 0xc4, 0xe2, 0xe1, 0x9b, 0xc0 );
    FCML_A64( "vfmsub213sd (%rax),%xmm3,%xmm0", 0xc4, 0xe2, 0xe1, 0xab, 0x00 );
    FCML_A64( "vfmsub213sd %xmm0,%xmm3,%xmm0", 0xc4, 0xe2, 0xe1, 0xab, 0xc0 );
    FCML_A64( "vfmsub231sd (%rax),%xmm3,%xmm0", 0xc4, 0xe2, 0xe1, 0xbb, 0x00 );
    FCML_A64( "vfmsub231sd %xmm0,%xmm3,%xmm0", 0xc4, 0xe2, 0xe1, 0xbb, 0xc0 );
    FCML_A64( "vfmsubsd %xmm2,(%rcx,%rax),%xmm5,%xmm2", 0xc4, 0xe3, 0x51, 0x6f, 0x14, 0x01, 0x20 );
}

void fcml_tf_instruction_VFMSUBSS(void) {
    /* VEX.DDS.LIG.128.66.0F38.W0 9B /r VFMSUB132SS xmm0,xmm1,xmm2/m32*/
    FCML_I32( "vfmsub132ss xmm0,xmm3,dword ptr [eax]", 0xC4, 0xE2, 0x61, 0x9B, 0x00 );
    FCML_I64( "vfmsub132ss xmm0,xmm3,xmm0", 0xC4, 0xE2, 0x61, 0x9B, 0xC0 );
    /* VEX.DDS.LIG.128.66.0F38.W0 AB /r VFMSUB213SS xmm0,xmm1,xmm2/m32*/
    FCML_I32( "vfmsub213ss xmm0,xmm3,dword ptr [eax]", 0xC4, 0xE2, 0x61, 0xAB, 0x00 );
    FCML_I64( "vfmsub213ss xmm0,xmm3,xmm0", 0xC4, 0xE2, 0x61, 0xAB, 0xC0 );
    /* VEX.DDS.LIG.128.66.0F38.W0 BB /r VFMSUB231SS xmm0,xmm1,xmm2/m32*/
    FCML_I32( "vfmsub231ss xmm0,xmm3,dword ptr [eax]", 0xC4, 0xE2, 0x61, 0xBB, 0x00 );
    FCML_I64( "vfmsub231ss xmm0,xmm3,xmm0", 0xC4, 0xE2, 0x61, 0xBB, 0xC0 );
    /* VFMSUBSS xmm1, xmm2, xmm3/mem32, xmm4 C4 RXB.00011 0.src.X.01 6E /r /is4*/
    /* VFMSUBSS xmm1, xmm2, xmm3, xmm4/mem32 C4 RXB.00011 1.src.X.01 6E /r /is4*/
    FCML_I64( "vfmsubss xmm2,xmm5,dword ptr [rcx+rax],xmm2", 0xC4, 0xE3, 0x51, 0x6E, 0x14, 0x01, 0x20 );
    FCML_I64_M( "vfmsubss xmm0,xmm5,xmm0,xmm2", 2, FCML_MI( 0xc4, 0xe3, 0xd1, 0x6e, 0xc2, 0x00 ), FCML_MI( 0xc4, 0xe3, 0x51, 0x6e, 0xc0, 0x20 ) );
    FCML_I64( "vfmsubss xmm2,xmm5,xmm2,dword ptr [rcx+rax]", 0xC4, 0xE3, 0xD1, 0x6E, 0x14, 0x01, 0x20 );
    FCML_I64_M( "vfmsubss xmm0,xmm5,xmm2,xmm0", 2, FCML_MI( 0xc4, 0xe3, 0xd1, 0x6e, 0xc0, 0x20 ), FCML_MI( 0xc4, 0xe3, 0x51, 0x6e, 0xc2, 0x00 ) );
    /* GAS*/
    FCML_A64( "vfmsub132ss (%rax),%xmm3,%xmm0", 0xc4, 0xe2, 0x61, 0x9b, 0x00 );
    FCML_A64( "vfmsub132ss %xmm0,%xmm3,%xmm0", 0xc4, 0xe2, 0x61, 0x9b, 0xc0 );
    FCML_A64( "vfmsub213ss (%rax),%xmm3,%xmm0", 0xc4, 0xe2, 0x61, 0xab, 0x00 );
    FCML_A64( "vfmsub213ss %xmm0,%xmm3,%xmm0", 0xc4, 0xe2, 0x61, 0xab, 0xc0 );
    FCML_A64( "vfmsub231ss (%rax),%xmm3,%xmm0", 0xc4, 0xe2, 0x61, 0xbb, 0x00 );
    FCML_A64( "vfmsub231ss %xmm0,%xmm3,%xmm0", 0xc4, 0xe2, 0x61, 0xbb, 0xc0 );
    FCML_A64( "vfmsubss %xmm2,(%rcx,%rax),%xmm5,%xmm2", 0xc4, 0xe3, 0x51, 0x6e, 0x14, 0x01, 0x20 );
}

void fcml_tf_instruction_VFNMADDPD(void) {
    /* VEX.DDS.128.66.0F38.W1 9C /r VFNMADD132PD xmm0,xmm1,xmm2/m128*/
    /* VEX.DDS.256.66.0F38.W1 9C /r VFNMADD132PD ymm0,ymm1,ymm2/m256*/
    FCML_I64( "vfnmadd132pd xmm0,xmm3,xmmword ptr [rax]", 0xC4, 0xE2, 0xE1, 0x9C, 0x00 );
    FCML_I64( "vfnmadd132pd ymm0,ymm3,ymmword ptr [rax]", 0xC4, 0xE2, 0xE5, 0x9C, 0x00 );
    FCML_I64( "vfnmadd132pd ymm0,ymm3,ymm0", 0xC4, 0xE2, 0xE5, 0x9C, 0xC0 );
    /* VEX.DDS.128.66.0F38.W1 AC /r VFNMADD213PD xmm0,xmm1,xmm2/m128*/
    /* VEX.DDS.256.66.0F38.W1 AC /r VFNMADD213PD ymm0,ymm1,ymm2/m256*/
    FCML_I64( "vfnmadd213pd xmm0,xmm3,xmmword ptr [rax]", 0xC4, 0xE2, 0xE1, 0xAC, 0x00 );
    FCML_I64( "vfnmadd213pd ymm0,ymm3,ymmword ptr [rax]", 0xC4, 0xE2, 0xE5, 0xAC, 0x00 );
    FCML_I64( "vfnmadd213pd ymm0,ymm3,ymm0", 0xC4, 0xE2, 0xE5, 0xAC, 0xC0 );
    /* VEX.DDS.128.66.0F38.W1 BC /r VFNMADD231PD xmm0,xmm1,xmm2/m128*/
    /* VEX.DDS.256.66.0F38.W1 BC /r VFNMADD231PD ymm0,ymm1,ymm2/m256*/
    FCML_I64( "vfnmadd231pd xmm0,xmm3,xmmword ptr [rax]", 0xC4, 0xE2, 0xE1, 0xBC, 0x00 );
    FCML_I64( "vfnmadd231pd ymm0,ymm3,ymmword ptr [rax]", 0xC4, 0xE2, 0xE5, 0xBC, 0x00 );
    FCML_I64( "vfnmadd231pd ymm0,ymm3,ymm0", 0xC4, 0xE2, 0xE5, 0xBC, 0xC0 );
    /* VFNMADDPD xmm1, xmm2, xmm3/mem128, xmm4 C4 RXB.00011 0.src.0.01 79 /r /is4*/
    /* VFNMADDPD ymm1, ymm2, ymm3/mem256, ymm4 C4 RXB.00011 0.src.1.01 79 /r /is4*/
    FCML_I32( "vfnmaddpd xmm2,xmm5,xmmword ptr [ecx+eax],xmm2", 0xC4, 0xE3, 0x51, 0x79, 0x14, 0x01, 0x20 );
    FCML_I64( "vfnmaddpd ymm2,ymm5,ymmword ptr [rcx+rax],ymm2", 0xC4, 0xE3, 0x55, 0x79, 0x14, 0x01, 0x20 );
    FCML_I64_M( "vfnmaddpd ymm0,ymm5,ymm0,ymm2", 2, FCML_MI( 0xc4, 0xe3, 0xd5, 0x79, 0xc2, 0x00 ), FCML_MI( 0xc4, 0xe3, 0x55, 0x79, 0xc0, 0x20 ) );
    /* VFNMADDPD xmm1, xmm2, xmm3, xmm4/mem128 C4 RXB.00011 1.src.0.01 79 /r /is4*/
    /* VFNMADDPD ymm1, ymm2, ymm3, ymm4/mem256 C4 RXB.00011 1.src.1.01 79 /r /is4*/
    FCML_I64( "vfnmaddpd xmm2,xmm5,xmm2,xmmword ptr [rcx+rax]", 0xC4, 0xE3, 0xD1, 0x79, 0x14, 0x01, 0x20 );
    FCML_I64( "vfnmaddpd ymm2,ymm5,ymm2,ymmword ptr [rcx+rax]", 0xC4, 0xE3, 0xD5, 0x79, 0x14, 0x01, 0x20 );
    FCML_I64_M( "vfnmaddpd ymm0,ymm5,ymm2,ymm0", 2, FCML_MI( 0xc4, 0xe3, 0xd5, 0x79, 0xc0, 0x20 ), FCML_MI( 0xc4, 0xe3, 0x55, 0x79, 0xc2, 0x00 ) );
    /* GAS*/
    FCML_A64( "vfnmadd132pd (%rax),%xmm3,%xmm0", 0xc4, 0xe2, 0xe1, 0x9c, 0x00 );
    FCML_A64( "vfnmadd132pd (%rax),%ymm3,%ymm0", 0xc4, 0xe2, 0xe5, 0x9c, 0x00 );
    FCML_A64( "vfnmadd132pd %ymm0,%ymm3,%ymm0", 0xc4, 0xe2, 0xe5, 0x9c, 0xc0 );
    FCML_A64( "vfnmadd213pd (%rax),%xmm3,%xmm0", 0xc4, 0xe2, 0xe1, 0xac, 0x00 );
    FCML_A64( "vfnmadd213pd (%rax),%ymm3,%ymm0", 0xc4, 0xe2, 0xe5, 0xac, 0x00 );
    FCML_A64( "vfnmadd213pd %ymm0,%ymm3,%ymm0", 0xc4, 0xe2, 0xe5, 0xac, 0xc0 );
    FCML_A64( "vfnmadd231pd (%rax),%xmm3,%xmm0", 0xc4, 0xe2, 0xe1, 0xbc, 0x00 );
    FCML_A64( "vfnmadd231pd (%rax),%ymm3,%ymm0", 0xc4, 0xe2, 0xe5, 0xbc, 0x00 );
    FCML_A64( "vfnmadd231pd %ymm0,%ymm3,%ymm0", 0xc4, 0xe2, 0xe5, 0xbc, 0xc0 );
    FCML_A64( "vfnmaddpd %xmm2,(%rcx,%rax),%xmm5,%xmm2", 0xc4, 0xe3, 0x51, 0x79, 0x14, 0x01, 0x20 );
    FCML_A64( "vfnmaddpd %ymm2,(%rcx,%rax),%ymm5,%ymm2", 0xc4, 0xe3, 0x55, 0x79, 0x14, 0x01, 0x20 );
}

void fcml_tf_instruction_VFNMADDPS(void) {
    /* VEX.DDS.128.66.0F38.W0 9C /r VFNMADD132PS xmm0,xmm1,xmm2/m128*/
    /* VEX.DDS.256.66.0F38.W0 9C /r VFNMADD132PS ymm0,ymm1,ymm2/m256*/
    FCML_I32( "vfnmadd132ps xmm0,xmm3,xmmword ptr [eax]", 0xC4, 0xE2, 0x61, 0x9C, 0x00 );
    FCML_I64( "vfnmadd132ps ymm0,ymm3,ymmword ptr [rax]", 0xC4, 0xE2, 0x65, 0x9C, 0x00 );
    FCML_I32( "vfnmadd132ps ymm0,ymm3,ymm0", 0xC4, 0xE2, 0x65, 0x9C, 0xC0 );
    /* VEX.DDS.128.66.0F38.W0 AC /r VFNMADD213PS xmm0,xmm1,xmm2/m128*/
    /* VEX.DDS.256.66.0F38.W0 AC /r VFNMADD213PS ymm0,ymm1,ymm2/m256*/
    FCML_I32( "vfnmadd213ps xmm0,xmm3,xmmword ptr [eax]", 0xC4, 0xE2, 0x61, 0xAC, 0x00 );
    FCML_I64( "vfnmadd213ps ymm0,ymm3,ymmword ptr [rax]", 0xC4, 0xE2, 0x65, 0xAC, 0x00 );
    FCML_I32( "vfnmadd213ps ymm0,ymm3,ymm0", 0xC4, 0xE2, 0x65, 0xAC, 0xC0 );
    /* VEX.DDS.128.66.0F38.W0 BC /r VFNMADD231PS xmm0,xmm1,xmm2/m128*/
    /* VEX.DDS.256.66.0F38.W0 BC /r VFNMADD231PS ymm0,ymm1,ymm2/m256*/
    FCML_I32( "vfnmadd231ps xmm0,xmm3,xmmword ptr [eax]", 0xC4, 0xE2, 0x61, 0xBC, 0x00 );
    FCML_I64( "vfnmadd231ps ymm0,ymm3,ymmword ptr [rax]", 0xC4, 0xE2, 0x65, 0xBC, 0x00 );
    FCML_I32( "vfnmadd231ps ymm0,ymm3,ymm0", 0xC4, 0xE2, 0x65, 0xBC, 0xC0 );
    /* VFNMADDPS xmm1, xmm2, xmm3/mem128, xmm4 C4 RXB.00011 0.src.0.01 78 /r /is4*/
    /* VFNMADDPS ymm1, ymm2, ymm3/mem256, ymm4 C4 RXB.00011 0.src.1.01 78 /r /is4*/
    FCML_I64( "vfnmaddps xmm2,xmm5,xmmword ptr [rcx+rax],xmm2", 0xC4, 0xE3, 0x51, 0x78, 0x14, 0x01, 0x20 );
    FCML_I64( "vfnmaddps ymm2,ymm5,ymmword ptr [rcx+rax],ymm2", 0xC4, 0xE3, 0x55, 0x78, 0x14, 0x01, 0x20 );
    FCML_I64_M( "vfnmaddps ymm0,ymm5,ymm0,ymm2", 2, FCML_MI( 0xc4, 0xe3, 0xd5, 0x78, 0xc2, 0x00 ), FCML_MI( 0xc4, 0xe3, 0x55, 0x78, 0xc0, 0x20 ) );
    /* VFNMADDPS xmm1, xmm2, xmm3, xmm4/mem128 C4 RXB.00011 1.src.0.01 78 /r /is4*/
    /* VFNMADDPS ymm1, ymm2, ymm3, ymm4/mem256 C4 RXB.00011 1.src.1.01 78 /r /is4*/
    FCML_I64( "vfnmaddps xmm2,xmm5,xmm2,xmmword ptr [rcx+rax]", 0xC4, 0xE3, 0xD1, 0x78, 0x14, 0x01, 0x20 );
    FCML_I64( "vfnmaddps ymm2,ymm5,ymm2,ymmword ptr [rcx+rax]", 0xC4, 0xE3, 0xD5, 0x78, 0x14, 0x01, 0x20 );
    FCML_I64_M( "vfnmaddps ymm0,ymm5,ymm2,ymm0", 2, FCML_MI( 0xc4, 0xe3, 0xd5, 0x78, 0xc0, 0x20 ), FCML_MI( 0xc4, 0xe3, 0x55, 0x78, 0xc2, 0x00 ) );
    /* GAS*/
    FCML_A64( "vfnmadd132ps (%rax),%xmm3,%xmm0", 0xc4, 0xe2, 0x61, 0x9c, 0x00 );
    FCML_A64( "vfnmadd132ps (%rax),%ymm3,%ymm0", 0xc4, 0xe2, 0x65, 0x9c, 0x00 );
    FCML_A64( "vfnmadd132ps %ymm0,%ymm3,%ymm0", 0xc4, 0xe2, 0x65, 0x9c, 0xc0 );
    FCML_A64( "vfnmadd213ps (%rax),%xmm3,%xmm0", 0xc4, 0xe2, 0x61, 0xac, 0x00 );
    FCML_A64( "vfnmadd213ps (%rax),%ymm3,%ymm0", 0xc4, 0xe2, 0x65, 0xac, 0x00 );
    FCML_A64( "vfnmadd213ps %ymm0,%ymm3,%ymm0", 0xc4, 0xe2, 0x65, 0xac, 0xc0 );
    FCML_A64( "vfnmadd231ps (%rax),%xmm3,%xmm0", 0xc4, 0xe2, 0x61, 0xbc, 0x00 );
    FCML_A64( "vfnmadd231ps (%rax),%ymm3,%ymm0", 0xc4, 0xe2, 0x65, 0xbc, 0x00 );
    FCML_A64( "vfnmadd231ps %ymm0,%ymm3,%ymm0", 0xc4, 0xe2, 0x65, 0xbc, 0xc0 );
    FCML_A64( "vfnmaddps %xmm2,(%rcx,%rax),%xmm5,%xmm2", 0xc4, 0xe3, 0x51, 0x78, 0x14, 0x01, 0x20 );
    FCML_A64( "vfnmaddps %ymm2,(%rcx,%rax),%ymm5,%ymm2", 0xc4, 0xe3, 0x55, 0x78, 0x14, 0x01, 0x20 );
}

void fcml_tf_instruction_VFNMADDSD(void) {
    /* VEX.DDS.LIG.128.66.0F38.W1 9D /r VFNMADD132SD xmm0,xmm1,xmm2/m64*/
    FCML_I64( "vfnmadd132sd xmm0,xmm3,mmword ptr [rax]", 0xC4, 0xE2, 0xE1, 0x9D, 0x00 );
    FCML_I64( "vfnmadd132sd xmm0,xmm3,xmm0", 0xC4, 0xE2, 0xE1, 0x9D, 0xC0 );
    /* VEX.DDS.LIG.128.66.0F38.W1 AD /r VFNMADD213SD xmm0,xmm1,xmm2/m64*/
    FCML_I64( "vfnmadd213sd xmm0,xmm3,mmword ptr [rax]", 0xC4, 0xE2, 0xE1, 0xAD, 0x00 );
    FCML_I64( "vfnmadd213sd xmm0,xmm3,xmm0", 0xC4, 0xE2, 0xE1, 0xAD, 0xC0 );
    /* VEX.DDS.LIG.128.66.0F38.W1 BD /r VFNMADD231SD xmm0,xmm1,xmm2/m64*/
    FCML_I64( "vfnmadd231sd xmm0,xmm3,mmword ptr [rax]", 0xC4, 0xE2, 0xE1, 0xBD, 0x00 );
    FCML_I64( "vfnmadd231sd xmm0,xmm3,xmm0", 0xC4, 0xE2, 0xE1, 0xBD, 0xC0 );
    /* VFNMADDSD xmm1, xmm2, xmm3/mem64, xmm4 C4 RXB.00011 0.src.X.01 7B /r /is4*/
    /* VFNMADDSD xmm1, xmm2, xmm3, xmm4/mem64 C4 RXB.00011 1.src.X.01 7B /r /is4*/
    FCML_I32( "vfnmaddsd xmm2,xmm5,mmword ptr [ecx+eax],xmm2", 0xC4, 0xE3, 0x51, 0x7B, 0x14, 0x01, 0x20 );
    FCML_I64_M( "vfnmaddsd xmm0,xmm5,xmm0,xmm2", 2, FCML_MI( 0xc4, 0xe3, 0xd1, 0x7b, 0xc2, 0x00 ), FCML_MI( 0xc4, 0xe3, 0x51, 0x7b, 0xc0, 0x20 ) );
    FCML_I64( "vfnmaddsd xmm2,xmm5,xmm2,mmword ptr [rcx+rax]", 0xC4, 0xE3, 0xD1, 0x7B, 0x14, 0x01, 0x20 );
    FCML_I64_M( "vfnmaddsd xmm0,xmm5,xmm2,xmm0", 2, FCML_MI( 0xc4, 0xe3, 0xd1, 0x7b, 0xc0, 0x20 ), FCML_MI( 0xc4, 0xe3, 0x51, 0x7b, 0xc2, 0x00 ) );
    /* GAS*/
    FCML_A64( "vfnmadd132sd (%rax),%xmm3,%xmm0", 0xc4, 0xe2, 0xe1, 0x9d, 0x00 );
    FCML_A64( "vfnmadd132sd %xmm0,%xmm3,%xmm0", 0xc4, 0xe2, 0xe1, 0x9d, 0xc0 );
    FCML_A64( "vfnmadd213sd (%rax),%xmm3,%xmm0", 0xc4, 0xe2, 0xe1, 0xad, 0x00 );
    FCML_A64( "vfnmadd213sd %xmm0,%xmm3,%xmm0", 0xc4, 0xe2, 0xe1, 0xad, 0xc0 );
    FCML_A64( "vfnmadd231sd (%rax),%xmm3,%xmm0", 0xc4, 0xe2, 0xe1, 0xbd, 0x00 );
    FCML_A64( "vfnmadd231sd %xmm0,%xmm3,%xmm0", 0xc4, 0xe2, 0xe1, 0xbd, 0xc0 );
    FCML_A64( "vfnmaddsd %xmm2,(%rcx,%rax),%xmm5,%xmm2", 0xc4, 0xe3, 0x51, 0x7b, 0x14, 0x01, 0x20 );
}

void fcml_tf_instruction_VFNMADDSS(void) {
    /* VEX.DDS.LIG.128.66.0F38.W0 9D /r VFNMADD132SS xmm0,xmm1,xmm2/m32*/
    FCML_I32( "vfnmadd132ss xmm0,xmm3,dword ptr [eax]", 0xC4, 0xE2, 0x61, 0x9D, 0x00 );
    FCML_I64( "vfnmadd132ss xmm0,xmm3,xmm0", 0xC4, 0xE2, 0x61, 0x9D, 0xC0 );
    /* VEX.DDS.LIG.128.66.0F38.W0 AD /r VFNMADD213SS xmm0,xmm1,xmm2/m32*/
    FCML_I32( "vfnmadd213ss xmm0,xmm3,dword ptr [eax]", 0xC4, 0xE2, 0x61, 0xAD, 0x00 );
    FCML_I64( "vfnmadd213ss xmm0,xmm3,xmm0", 0xC4, 0xE2, 0x61, 0xAD, 0xC0 );
    /* VEX.DDS.LIG.128.66.0F38.W0 BD /r VFNMADD231SS xmm0,xmm1,xmm2/m32*/
    FCML_I32( "vfnmadd231ss xmm0,xmm3,dword ptr [eax]", 0xC4, 0xE2, 0x61, 0xBD, 0x00 );
    FCML_I64( "vfnmadd231ss xmm0,xmm3,xmm0", 0xC4, 0xE2, 0x61, 0xBD, 0xC0 );
    /* VFNMADDSS xmm1, xmm2, xmm3/mem32, xmm4 C4 RXB.00011 0.src.X.01 7A /r /is4*/
    /* VFNMADDSS xmm1, xmm2, xmm3, xmm4/mem32 C4 RXB.00011 1.src.X.01 7A /r /is4*/
    FCML_I64( "vfnmaddss xmm2,xmm5,dword ptr [rcx+rax],xmm2", 0xC4, 0xE3, 0x51, 0x7A, 0x14, 0x01, 0x20 );
    FCML_I64_M( "vfnmaddss xmm0,xmm5,xmm0,xmm2", 2, FCML_MI( 0xc4, 0xe3, 0xd1, 0x7a, 0xc2, 0x00 ), FCML_MI( 0xc4, 0xe3, 0x51, 0x7a, 0xc0, 0x20 ) );
    FCML_I64( "vfnmaddss xmm2,xmm5,xmm2,dword ptr [rcx+rax]", 0xC4, 0xE3, 0xD1, 0x7A, 0x14, 0x01, 0x20 );
    FCML_I64_M( "vfnmaddss xmm0,xmm5,xmm2,xmm0", 2, FCML_MI( 0xc4, 0xe3, 0xd1, 0x7a, 0xc0, 0x20 ), FCML_MI( 0xc4, 0xe3, 0x51, 0x7a, 0xc2, 0x00 ) );
    /* GAS*/
    FCML_A64( "vfnmadd132ss (%rax),%xmm3,%xmm0", 0xc4, 0xe2, 0x61, 0x9d, 0x00 );
    FCML_A64( "vfnmadd132ss %xmm0,%xmm3,%xmm0", 0xc4, 0xe2, 0x61, 0x9d, 0xc0 );
    FCML_A64( "vfnmadd213ss (%rax),%xmm3,%xmm0", 0xc4, 0xe2, 0x61, 0xad, 0x00 );
    FCML_A64( "vfnmadd213ss %xmm0,%xmm3,%xmm0", 0xc4, 0xe2, 0x61, 0xad, 0xc0 );
    FCML_A64( "vfnmadd231ss (%rax),%xmm3,%xmm0", 0xc4, 0xe2, 0x61, 0xbd, 0x00 );
    FCML_A64( "vfnmadd231ss %xmm0,%xmm3,%xmm0", 0xc4, 0xe2, 0x61, 0xbd, 0xc0 );
    FCML_A64( "vfnmaddss %xmm2,(%rcx,%rax),%xmm5,%xmm2", 0xc4, 0xe3, 0x51, 0x7a, 0x14, 0x01, 0x20 );
}

void fcml_tf_instruction_VFNMSUBPD(void) {
    /* VEX.DDS.128.66.0F38.W1 9E /r VFNMSUB132PD xmm0,xmm1,xmm2/m128*/
    /* VEX.DDS.256.66.0F38.W1 9E /r VFNMSUB132PD ymm0,ymm1,ymm2/m256*/
    FCML_I64( "vfnmsub132pd xmm0,xmm3,xmmword ptr [rax]", 0xC4, 0xE2, 0xE1, 0x9E, 0x00 );
    FCML_I64( "vfnmsub132pd ymm0,ymm3,ymmword ptr [rax]", 0xC4, 0xE2, 0xE5, 0x9E, 0x00 );
    FCML_I64( "vfnmsub132pd ymm0,ymm3,ymm0", 0xC4, 0xE2, 0xE5, 0x9E, 0xC0 );
    /* VEX.DDS.128.66.0F38.W1 AE /r VFNMSUB213PD xmm0,xmm1,xmm2/m128*/
    /* VEX.DDS.256.66.0F38.W1 AE /r VFNMSUB213PD ymm0,ymm1,ymm2/m256*/
    FCML_I64( "vfnmsub213pd xmm0,xmm3,xmmword ptr [rax]", 0xC4, 0xE2, 0xE1, 0xAE, 0x00 );
    FCML_I64( "vfnmsub213pd ymm0,ymm3,ymmword ptr [rax]", 0xC4, 0xE2, 0xE5, 0xAE, 0x00 );
    FCML_I64( "vfnmsub213pd ymm0,ymm3,ymm0", 0xC4, 0xE2, 0xE5, 0xAE, 0xC0 );
    /* VEX.DDS.128.66.0F38.W1 BE /r VFNMSUB231PD xmm0,xmm1,xmm2/m128*/
    /* VEX.DDS.256.66.0F38.W1 BE /r VFNMSUB231PD ymm0,ymm1,ymm2/m256*/
    FCML_I64( "vfnmsub231pd xmm0,xmm3,xmmword ptr [rax]", 0xC4, 0xE2, 0xE1, 0xBE, 0x00 );
    FCML_I64( "vfnmsub231pd ymm0,ymm3,ymmword ptr [rax]", 0xC4, 0xE2, 0xE5, 0xBE, 0x00 );
    FCML_I64( "vfnmsub231pd ymm0,ymm3,ymm0", 0xC4, 0xE2, 0xE5, 0xBE, 0xC0 );
    /* VFNMSUBPD xmm1, xmm2, xmm3/mem128, xmm4 C4 RXB.00011 0.src.0.01 7D /r /is4*/
    /* VFNMSUBPD ymm1, ymm2, ymm3/mem256, ymm4 C4 RXB.00011 0.src.1.01 7D /r /is4*/
    FCML_I32( "vfnmsubpd xmm2,xmm5,xmmword ptr [ecx+eax],xmm2", 0xC4, 0xE3, 0x51, 0x7D, 0x14, 0x01, 0x20 );
    FCML_I64( "vfnmsubpd ymm2,ymm5,ymmword ptr [rcx+rax],ymm2", 0xC4, 0xE3, 0x55, 0x7D, 0x14, 0x01, 0x20 );
    FCML_I64_M( "vfnmsubpd ymm0,ymm5,ymm0,ymm2", 2, FCML_MI( 0xc4, 0xe3, 0xd5, 0x7d, 0xc2, 0x00 ), FCML_MI( 0xc4, 0xe3, 0x55, 0x7d, 0xc0, 0x20 ) );
    /* VFNMSUBPD xmm1, xmm2, xmm3, xmm4/mem128 C4 RXB.00011 1.src.0.01 7D /r /is4*/
    /* VFNMSUBPD ymm1, ymm2, ymm3, ymm4/mem256 C4 RXB.00011 1.src.1.01 7D /r /is4*/
    FCML_I64( "vfnmsubpd xmm2,xmm5,xmm2,xmmword ptr [rcx+rax]", 0xC4, 0xE3, 0xD1, 0x7D, 0x14, 0x01, 0x20 );
    FCML_I64( "vfnmsubpd ymm2,ymm5,ymm2,ymmword ptr [rcx+rax]", 0xC4, 0xE3, 0xD5, 0x7D, 0x14, 0x01, 0x20 );
    FCML_I64_M( "vfnmsubpd ymm0,ymm5,ymm2,ymm0", 2, FCML_MI( 0xc4, 0xe3, 0xd5, 0x7d, 0xc0, 0x20 ), FCML_MI( 0xc4, 0xe3, 0x55, 0x7d, 0xc2, 0x00 ) );
    /* GAS*/
    FCML_A64( "vfnmsub132pd (%rax),%xmm3,%xmm0", 0xc4, 0xe2, 0xe1, 0x9e, 0x00 );
    FCML_A64( "vfnmsub132pd (%rax),%ymm3,%ymm0", 0xc4, 0xe2, 0xe5, 0x9e, 0x00 );
    FCML_A64( "vfnmsub132pd %ymm0,%ymm3,%ymm0", 0xc4, 0xe2, 0xe5, 0x9e, 0xc0 );
    FCML_A64( "vfnmsub213pd (%rax),%xmm3,%xmm0", 0xc4, 0xe2, 0xe1, 0xae, 0x00 );
    FCML_A64( "vfnmsub213pd (%rax),%ymm3,%ymm0", 0xc4, 0xe2, 0xe5, 0xae, 0x00 );
    FCML_A64( "vfnmsub213pd %ymm0,%ymm3,%ymm0", 0xc4, 0xe2, 0xe5, 0xae, 0xc0 );
    FCML_A64( "vfnmsub231pd (%rax),%xmm3,%xmm0", 0xc4, 0xe2, 0xe1, 0xbe, 0x00 );
    FCML_A64( "vfnmsub231pd (%rax),%ymm3,%ymm0", 0xc4, 0xe2, 0xe5, 0xbe, 0x00 );
    FCML_A64( "vfnmsub231pd %ymm0,%ymm3,%ymm0", 0xc4, 0xe2, 0xe5, 0xbe, 0xc0 );
    FCML_A64( "vfnmsubpd %xmm2,(%rcx,%rax),%xmm5,%xmm2", 0xc4, 0xe3, 0x51, 0x7d, 0x14, 0x01, 0x20 );
    FCML_A64( "vfnmsubpd %ymm2,(%rcx,%rax),%ymm5,%ymm2", 0xc4, 0xe3, 0x55, 0x7d, 0x14, 0x01, 0x20 );
}

void fcml_tf_instruction_VFNMSUBPS(void) {
    /* VEX.DDS.128.66.0F38.W0 9E /r VFNMSUB132PS xmm0,xmm1,xmm2/m128*/
    /* VEX.DDS.256.66.0F38.W0 9E /r VFNMSUB132PS ymm0,ymm1,ymm2/m256*/
    FCML_I32( "vfnmsub132ps xmm0,xmm3,xmmword ptr [eax]", 0xC4, 0xE2, 0x61, 0x9E, 0x00 );
    FCML_I64( "vfnmsub132ps ymm0,ymm3,ymmword ptr [rax]", 0xC4, 0xE2, 0x65, 0x9E, 0x00 );
    FCML_I32( "vfnmsub132ps ymm0,ymm3,ymm0", 0xC4, 0xE2, 0x65, 0x9E, 0xC0 );
    /* VEX.DDS.128.66.0F38.W0 AE /r VFNMSUB213PS xmm0,xmm1,xmm2/m128*/
    /* VEX.DDS.256.66.0F38.W0 AE /r VFNMSUB213PS ymm0,ymm1,ymm2/m256*/
    FCML_I32( "vfnmsub213ps xmm0,xmm3,xmmword ptr [eax]", 0xC4, 0xE2, 0x61, 0xAE, 0x00 );
    FCML_I64( "vfnmsub213ps ymm0,ymm3,ymmword ptr [rax]", 0xC4, 0xE2, 0x65, 0xAE, 0x00 );
    FCML_I32( "vfnmsub213ps ymm0,ymm3,ymm0", 0xC4, 0xE2, 0x65, 0xAE, 0xC0 );
    /* VEX.DDS.128.66.0F38.W0 BE /r VFNMSUB231PS xmm0,xmm1,xmm2/m128*/
    /* VEX.DDS.256.66.0F38.W0 BE /r VFNMSUB231PS ymm0,ymm1,ymm2/m256*/
    FCML_I32( "vfnmsub231ps xmm0,xmm3,xmmword ptr [eax]", 0xC4, 0xE2, 0x61, 0xBE, 0x00 );
    FCML_I64( "vfnmsub231ps ymm0,ymm3,ymmword ptr [rax]", 0xC4, 0xE2, 0x65, 0xBE, 0x00 );
    FCML_I32( "vfnmsub231ps ymm0,ymm3,ymm0", 0xC4, 0xE2, 0x65, 0xBE, 0xC0 );
    /* VFNMSUBPS xmm1, xmm2, xmm3/mem128, xmm4 C4 RXB.00011 0.src.0.01 7C /r /is4*/
    /* VFNMSUBPS ymm1, ymm2, ymm3/mem256, ymm4 C4 RXB.00011 0.src.1.01 7C /r /is4*/
    FCML_I64( "vfnmsubps xmm2,xmm5,xmmword ptr [rcx+rax],xmm2", 0xC4, 0xE3, 0x51, 0x7C, 0x14, 0x01, 0x20 );
    FCML_I64( "vfnmsubps ymm2,ymm5,ymmword ptr [rcx+rax],ymm2", 0xC4, 0xE3, 0x55, 0x7C, 0x14, 0x01, 0x20 );
    FCML_I64_M( "vfnmsubps ymm0,ymm5,ymm0,ymm2", 2, FCML_MI( 0xc4, 0xe3, 0xd5, 0x7c, 0xc2, 0x00 ), FCML_MI( 0xc4, 0xe3, 0x55, 0x7c, 0xc0, 0x20 ) );
    /* VFNMSUBPS xmm1, xmm2, xmm3, xmm4/mem128 C4 RXB.00011 1.src.0.01 7C /r /is4*/
    /* VFNMSUBPS ymm1, ymm2, ymm3, ymm4/mem256 C4 RXB.00011 1.src.1.01 7C /r /is4*/
    FCML_I64( "vfnmsubps xmm2,xmm5,xmm2,xmmword ptr [rcx+rax]", 0xC4, 0xE3, 0xD1, 0x7C, 0x14, 0x01, 0x20 );
    FCML_I64( "vfnmsubps ymm2,ymm5,ymm2,ymmword ptr [rcx+rax]", 0xC4, 0xE3, 0xD5, 0x7C, 0x14, 0x01, 0x20 );
    FCML_I64_M( "vfnmsubps ymm0,ymm5,ymm2,ymm0", 2, FCML_MI( 0xc4, 0xe3, 0xd5, 0x7c, 0xc0, 0x20 ), FCML_MI( 0xc4, 0xe3, 0x55, 0x7c, 0xc2, 0x00 ) );
    /* GAS*/
    FCML_A64( "vfnmsub132ps (%rax),%xmm3,%xmm0", 0xc4, 0xe2, 0x61, 0x9e, 0x00 );
    FCML_A64( "vfnmsub132ps (%rax),%ymm3,%ymm0", 0xc4, 0xe2, 0x65, 0x9e, 0x00 );
    FCML_A64( "vfnmsub132ps %ymm0,%ymm3,%ymm0", 0xc4, 0xe2, 0x65, 0x9e, 0xc0 );
    FCML_A64( "vfnmsub213ps (%rax),%xmm3,%xmm0", 0xc4, 0xe2, 0x61, 0xae, 0x00 );
    FCML_A64( "vfnmsub213ps (%rax),%ymm3,%ymm0", 0xc4, 0xe2, 0x65, 0xae, 0x00 );
    FCML_A64( "vfnmsub213ps %ymm0,%ymm3,%ymm0", 0xc4, 0xe2, 0x65, 0xae, 0xc0 );
    FCML_A64( "vfnmsub231ps (%rax),%xmm3,%xmm0", 0xc4, 0xe2, 0x61, 0xbe, 0x00 );
    FCML_A64( "vfnmsub231ps (%rax),%ymm3,%ymm0", 0xc4, 0xe2, 0x65, 0xbe, 0x00 );
    FCML_A64( "vfnmsub231ps %ymm0,%ymm3,%ymm0", 0xc4, 0xe2, 0x65, 0xbe, 0xc0 );
    FCML_A64( "vfnmsubps %xmm2,(%rcx,%rax),%xmm5,%xmm2", 0xc4, 0xe3, 0x51, 0x7c, 0x14, 0x01, 0x20 );
    FCML_A64( "vfnmsubps %ymm2,(%rcx,%rax),%ymm5,%ymm2", 0xc4, 0xe3, 0x55, 0x7c, 0x14, 0x01, 0x20 );
}

void fcml_tf_instruction_VFNMSUBSD(void) {
    /* VEX.DDS.LIG.128.66.0F38.W1 9F /r VFNMSUB132SD xmm0,xmm1,xmm2/m64*/
    FCML_I64( "vfnmsub132sd xmm0,xmm3,mmword ptr [rax]", 0xC4, 0xE2, 0xE1, 0x9F, 0x00 );
    FCML_I64( "vfnmsub132sd xmm0,xmm3,xmm0", 0xC4, 0xE2, 0xE1, 0x9F, 0xC0 );
    /* VEX.DDS.LIG.128.66.0F38.W1 AF /r VFNMSUB213SD xmm0,xmm1,xmm2/m64*/
    FCML_I64( "vfnmsub213sd xmm0,xmm3,mmword ptr [rax]", 0xC4, 0xE2, 0xE1, 0xAF, 0x00 );
    FCML_I64( "vfnmsub213sd xmm0,xmm3,xmm0", 0xC4, 0xE2, 0xE1, 0xAF, 0xC0 );
    /* VEX.DDS.LIG.128.66.0F38.W1 BF /r VFNMSUB231SD xmm0,xmm1,xmm2/m64*/
    FCML_I64( "vfnmsub231sd xmm0,xmm3,mmword ptr [rax]", 0xC4, 0xE2, 0xE1, 0xBF, 0x00 );
    FCML_I64( "vfnmsub231sd xmm0,xmm3,xmm0", 0xC4, 0xE2, 0xE1, 0xBF, 0xC0 );
    /* VFNMSUBSD xmm1, xmm2, xmm3/mem64, xmm4 C4 RXB.00011 0.src.X.01 7F /r /is4*/
    /* VFNMSUBSD xmm1, xmm2, xmm3, xmm4/mem64 C4 RXB.00011 1.src.X.01 7F /r /is4*/
    FCML_I32( "vfnmsubsd xmm2,xmm5,mmword ptr [ecx+eax],xmm2", 0xC4, 0xE3, 0x51, 0x7F, 0x14, 0x01, 0x20 );
    FCML_I64_M( "vfnmsubsd xmm0,xmm5,xmm0,xmm2", 2, FCML_MI( 0xc4, 0xe3, 0xd1, 0x7f, 0xc2, 0x00 ), FCML_MI( 0xc4, 0xe3, 0x51, 0x7f, 0xc0, 0x20 ) );
    FCML_I64( "vfnmsubsd xmm2,xmm5,xmm2,mmword ptr [rcx+rax]", 0xC4, 0xE3, 0xD1, 0x7F, 0x14, 0x01, 0x20 );
    FCML_I64_M( "vfnmsubsd xmm0,xmm5,xmm2,xmm0", 2, FCML_MI( 0xc4, 0xe3, 0xd1, 0x7f, 0xc0, 0x20 ), FCML_MI( 0xc4, 0xe3, 0x51, 0x7f, 0xc2, 0x00 ) );
    /* GAS*/
    FCML_A64( "vfnmsub132sd (%rax),%xmm3,%xmm0", 0xc4, 0xe2, 0xe1, 0x9f, 0x00 );
    FCML_A64( "vfnmsub132sd %xmm0,%xmm3,%xmm0", 0xc4, 0xe2, 0xe1, 0x9f, 0xc0 );
    FCML_A64( "vfnmsub213sd (%rax),%xmm3,%xmm0", 0xc4, 0xe2, 0xe1, 0xaf, 0x00 );
    FCML_A64( "vfnmsub213sd %xmm0,%xmm3,%xmm0", 0xc4, 0xe2, 0xe1, 0xaf, 0xc0 );
    FCML_A64( "vfnmsub231sd (%rax),%xmm3,%xmm0", 0xc4, 0xe2, 0xe1, 0xbf, 0x00 );
    FCML_A64( "vfnmsub231sd %xmm0,%xmm3,%xmm0", 0xc4, 0xe2, 0xe1, 0xbf, 0xc0 );
    FCML_A64( "vfnmsubsd %xmm2,(%rcx,%rax),%xmm5,%xmm2", 0xc4, 0xe3, 0x51, 0x7f, 0x14, 0x01, 0x20 );
}

void fcml_tf_instruction_VFNMSUBSS(void) {
    /* VEX.DDS.LIG.128.66.0F38.W0 9F /r VFNMSUB132SS xmm0,xmm1,xmm2/m32*/
    FCML_I32( "vfnmsub132ss xmm0,xmm3,dword ptr [eax]", 0xC4, 0xE2, 0x61, 0x9F, 0x00 );
    FCML_I64( "vfnmsub132ss xmm0,xmm3,xmm0", 0xC4, 0xE2, 0x61, 0x9F, 0xC0 );
    /* VEX.DDS.LIG.128.66.0F38.W0 AF /r VFNMSUB213SS xmm0,xmm1,xmm2/m32*/
    FCML_I32( "vfnmsub213ss xmm0,xmm3,dword ptr [eax]", 0xC4, 0xE2, 0x61, 0xAF, 0x00 );
    FCML_I64( "vfnmsub213ss xmm0,xmm3,xmm0", 0xC4, 0xE2, 0x61, 0xAF, 0xC0 );
    /* VEX.DDS.LIG.128.66.0F38.W0 BF /r VFNMSUB231SS xmm0,xmm1,xmm2/m32*/
    FCML_I32( "vfnmsub231ss xmm0,xmm3,dword ptr [eax]", 0xC4, 0xE2, 0x61, 0xBF, 0x00 );
    FCML_I64( "vfnmsub231ss xmm0,xmm3,xmm0", 0xC4, 0xE2, 0x61, 0xBF, 0xC0 );
    /* VFNMSUBSS xmm1, xmm2, xmm3/mem32, xmm4 C4 RXB.00011 0.src.X.01 7E /r /is4*/
    /* VFNMSUBSS xmm1, xmm2, xmm3, xmm4/mem32 C4 RXB.00011 1.src.X.01 7E /r /is4*/
    FCML_I64( "vfnmsubss xmm2,xmm5,dword ptr [rcx+rax],xmm2", 0xC4, 0xE3, 0x51, 0x7E, 0x14, 0x01, 0x20 );
    FCML_I64_M( "vfnmsubss xmm0,xmm5,xmm0,xmm2", 2, FCML_MI( 0xc4, 0xe3, 0xd1, 0x7e, 0xc2, 0x00 ), FCML_MI( 0xc4, 0xe3, 0x51, 0x7e, 0xc0, 0x20 ) );
    FCML_I64( "vfnmsubss xmm2,xmm5,xmm2,dword ptr [rcx+rax]", 0xC4, 0xE3, 0xD1, 0x7E, 0x14, 0x01, 0x20 );
    FCML_I64_M( "vfnmsubss xmm0,xmm5,xmm2,xmm0", 2, FCML_MI( 0xc4, 0xe3, 0xd1, 0x7e, 0xc0, 0x20 ), FCML_MI( 0xc4, 0xe3, 0x51, 0x7e, 0xc2, 0x00 ) );
    /* GAS*/
    FCML_A64( "vfnmsub132ss (%rax),%xmm3,%xmm0", 0xc4, 0xe2, 0x61, 0x9f, 0x00 );
    FCML_A64( "vfnmsub132ss %xmm0,%xmm3,%xmm0", 0xc4, 0xe2, 0x61, 0x9f, 0xc0 );
    FCML_A64( "vfnmsub213ss (%rax),%xmm3,%xmm0", 0xc4, 0xe2, 0x61, 0xaf, 0x00 );
    FCML_A64( "vfnmsub213ss %xmm0,%xmm3,%xmm0", 0xc4, 0xe2, 0x61, 0xaf, 0xc0 );
    FCML_A64( "vfnmsub231ss (%rax),%xmm3,%xmm0", 0xc4, 0xe2, 0x61, 0xbf, 0x00 );
    FCML_A64( "vfnmsub231ss %xmm0,%xmm3,%xmm0", 0xc4, 0xe2, 0x61, 0xbf, 0xc0 );
    FCML_A64( "vfnmsubss %xmm2,(%rcx,%rax),%xmm5,%xmm2", 0xc4, 0xe3, 0x51, 0x7e, 0x14, 0x01, 0x20 );
}

void fcml_tf_instruction_VFRCZPD(void) {
    /* VFRCZPD xmm1, xmm2/mem128 8F RXB.01001 0.1111.0.00 81 /r*/
    /* VFRCZPD ymm1, ymm2/mem256 8F RXB.01001 0.1111.1.00 81 /r*/
    FCML_I32( "vfrczpd xmm0,xmmword ptr [eax]", 0x8F, 0xE9, 0x78, 0x81, 0x00 );
    FCML_I32( "vfrczpd xmm0,xmm1", 0x8F, 0xE9, 0x78, 0x81, 0xC1 );
    FCML_I32( "vfrczpd ymm0,ymmword ptr [eax]", 0x8F, 0xE9, 0x7C, 0x81, 0x00 );
    FCML_I32( "vfrczpd ymm0,ymm1", 0x8F, 0xE9, 0x7C, 0x81, 0xC1 );
    FCML_I64( "vfrczpd xmm0,xmmword ptr [rax]", 0x8F, 0xE9, 0x78, 0x81, 0x00 );
    FCML_I64( "vfrczpd ymm0,ymmword ptr [rax]", 0x8F, 0xE9, 0x7C, 0x81, 0x00 );
    /* GAS*/
    FCML_A64( "vfrczpd (%rax),%xmm0", 0x8f, 0xe9, 0x78, 0x81, 0x00 );
    FCML_A64( "vfrczpd %xmm1,%xmm0", 0x8f, 0xe9, 0x78, 0x81, 0xc1 );
    FCML_A64( "vfrczpd (%rax),%ymm0", 0x8f, 0xe9, 0x7c, 0x81, 0x00 );
    FCML_A64( "vfrczpd %ymm1,%ymm0", 0x8f, 0xe9, 0x7c, 0x81, 0xc1 );
    FCML_A64( "vfrczpd (%rax),%xmm0", 0x8f, 0xe9, 0x78, 0x81, 0x00 );
    FCML_A64( "vfrczpd (%rax),%ymm0", 0x8f, 0xe9, 0x7c, 0x81, 0x00 );
}

void fcml_tf_instruction_VFRCZPS(void) {
    /* VFRCZPS xmm1, xmm2/mem128 8F RXB.01001 0.1111.0.00 80 /r*/
    /* VFRCZPS ymm1, ymm2/mem256 8F RXB.01001 0.1111.1.00 80 /r*/
    FCML_I32( "vfrczps xmm0,xmmword ptr [eax]", 0x8F, 0xE9, 0x78, 0x80, 0x00 );
    FCML_I32( "vfrczps xmm0,xmm1", 0x8F, 0xE9, 0x78, 0x80, 0xC1 );
    FCML_I32( "vfrczps ymm0,ymmword ptr [eax]", 0x8F, 0xE9, 0x7C, 0x80, 0x00 );
    FCML_I32( "vfrczps ymm0,ymm1", 0x8F, 0xE9, 0x7C, 0x80, 0xC1 );
    FCML_I64( "vfrczps xmm0,xmmword ptr [rax]", 0x8F, 0xE9, 0x78, 0x80, 0x00 );
    FCML_I64( "vfrczps ymm0,ymmword ptr [rax]", 0x8F, 0xE9, 0x7C, 0x80, 0x00 );
    /* GAS*/
    FCML_A64( "vfrczps (%rax),%xmm0", 0x8f, 0xe9, 0x78, 0x80, 0x00 );
    FCML_A64( "vfrczps %xmm1,%xmm0", 0x8f, 0xe9, 0x78, 0x80, 0xc1 );
    FCML_A64( "vfrczps (%rax),%ymm0", 0x8f, 0xe9, 0x7c, 0x80, 0x00 );
    FCML_A64( "vfrczps %ymm1,%ymm0", 0x8f, 0xe9, 0x7c, 0x80, 0xc1 );
    FCML_A64( "vfrczps (%rax),%xmm0", 0x8f, 0xe9, 0x78, 0x80, 0x00 );
    FCML_A64( "vfrczps (%rax),%ymm0", 0x8f, 0xe9, 0x7c, 0x80, 0x00 );
}

void fcml_tf_instruction_VFRCZSD(void) {
    /* VFRCZSD xmm1,xmm2/mem64 8F RXB.01001 0.1111.0.00 83 /r*/
    FCML_I32( "vfrczsd xmm0,mmword ptr [eax]", 0x8F, 0xE9, 0x78, 0x83, 0x00 );
    FCML_I32( "vfrczsd xmm0,xmm1", 0x8F, 0xE9, 0x78, 0x83, 0xC1 );
    FCML_I64( "vfrczsd xmm0,mmword ptr [rax]", 0x8F, 0xE9, 0x78, 0x83, 0x00 );
    FCML_I64( "vfrczsd xmm0,xmm1", 0x8F, 0xE9, 0x78, 0x83, 0xC1 );
    /* GAS*/
    FCML_A64( "vfrczsd (%rax),%xmm0", 0x8f, 0xe9, 0x78, 0x83, 0x00 );
    FCML_A64( "vfrczsd %xmm1,%xmm0", 0x8f, 0xe9, 0x78, 0x83, 0xc1 );
}

void fcml_tf_instruction_VFRCZSS(void) {
    /* VFRCZSS xmm1, xmm2/mem32 8F RXB.01001 0.1111.0.00 82 /r*/
    FCML_I32( "vfrczss xmm0,dword ptr [eax]", 0x8F, 0xE9, 0x78, 0x82, 0x00 );
    FCML_I32( "vfrczss xmm0,xmm1", 0x8F, 0xE9, 0x78, 0x82, 0xC1 );
    FCML_I64( "vfrczss xmm0,dword ptr [rax]", 0x8F, 0xE9, 0x78, 0x82, 0x00 );
    FCML_I64( "vfrczss xmm0,xmm1", 0x8F, 0xE9, 0x78, 0x82, 0xC1 );
    /* GAS*/
    FCML_A64( "vfrczss (%rax),%xmm0", 0x8f, 0xe9, 0x78, 0x82, 0x00 );
    FCML_A64( "vfrczss %xmm1,%xmm0", 0x8f, 0xe9, 0x78, 0x82, 0xc1 );
}

void fcml_tf_instruction_VPCMOV(void) {
    /* VPCMOV xmm1, xmm2, xmm3/mem128, xmm4 8F RXB.01000 0.src.0.00 A2 /r ib*/
    /* VPCMOV ymm1, ymm2, ymm3/mem256, ymm4 8F RXB.01000 0.src.1.00 A2 /r ib*/
    FCML_I64( "vpcmov xmm2,xmm5,xmmword ptr [rcx+rax],xmm2", 0x8F, 0xE8, 0x50, 0xA2, 0x14, 0x01, 0x20 );
    FCML_I64( "vpcmov ymm2,ymm5,ymmword ptr [rcx+rax],ymm2", 0x8F, 0xE8, 0x54, 0xA2, 0x14, 0x01, 0x20 );
    FCML_I64_M( "vpcmov ymm0,ymm5,ymm0,ymm2", 2, FCML_MI( 0x8f, 0xe8, 0xd4, 0xa2, 0xc2, 0x00 ), FCML_MI( 0x8f, 0xe8, 0x54, 0xa2, 0xc0, 0x20 ) );
    /* VPCMOV xmm1, xmm2, xmm3, xmm4/mem128 8F RXB.01000 1.src.0.00 A2 /r ib*/
    /* VPCMOV ymm1, ymm2, ymm3, ymm4/mem256 8F RXB.01000 1.src.1.00 A2 /r ib*/
    FCML_I64( "vpcmov xmm2,xmm5,xmm2,xmmword ptr [rcx+rax]", 0x8F, 0xE8, 0xD0, 0xA2, 0x14, 0x01, 0x20 );
    FCML_I64( "vpcmov ymm2,ymm5,ymm2,ymmword ptr [rcx+rax]", 0x8F, 0xE8, 0xD4, 0xA2, 0x14, 0x01, 0x20 );
    FCML_I64_M( "vpcmov ymm0,ymm5,ymm2,ymm0", 2, FCML_MI( 0x8f, 0xe8, 0xd4, 0xa2, 0xc0, 0x20 ), FCML_MI( 0x8f, 0xe8, 0x54, 0xa2, 0xc2, 0x00 ) );
    /* GAS*/
    FCML_A64( "vpcmov %xmm2,(%rcx,%rax),%xmm5,%xmm2", 0x8f, 0xe8, 0x50, 0xa2, 0x14, 0x01, 0x20 );
    FCML_A64( "vpcmov %ymm2,(%rcx,%rax),%ymm5,%ymm2", 0x8f, 0xe8, 0x54, 0xa2, 0x14, 0x01, 0x20 );
    FCML_A64( "vpcmov (%rcx,%rax),%xmm2,%xmm5,%xmm2", 0x8f, 0xe8, 0xd0, 0xa2, 0x14, 0x01, 0x20 );
    FCML_A64( "vpcmov (%rcx,%rax),%ymm2,%ymm5,%ymm2", 0x8f, 0xe8, 0xd4, 0xa2, 0x14, 0x01, 0x20 );
}

void fcml_tf_instruction_VPCOM(void) {
    /* VPCOMB xmm1, xmm2, xmm3/mem128, imm8 8F RXB.01000 0.src.0.00 CC /r ib*/
    FCML_I32( "vpcomb xmm2,xmm5,xmmword ptr [ecx+eax],00h", 0x8F, 0xE8, 0x50, 0xCC, 0x14, 0x01, 0x00 );
    FCML_I64_A_FAILED( "vpcomb xmm0,xmm5,xmm0,20h", 0x8F, 0xE8, 0x50, 0xCC, 0xC0, 0x20 );
    FCML_I32_A( "vpcomltb xmm2,xmm5,xmmword ptr [ecx+eax]", 0x8F, 0xE8, 0x50, 0xCC, 0x14, 0x01, 0x00 );
    FCML_I32_A( "vpcomleb xmm2,xmm5,xmmword ptr [ecx+eax]", 0x8F, 0xE8, 0x50, 0xCC, 0x14, 0x01, 0x01 );
    FCML_I32_A( "vpcomgtb xmm2,xmm5,xmmword ptr [ecx+eax]", 0x8F, 0xE8, 0x50, 0xCC, 0x14, 0x01, 0x02 );
    FCML_I32_A( "vpcomgeb xmm2,xmm5,xmmword ptr [ecx+eax]", 0x8F, 0xE8, 0x50, 0xCC, 0x14, 0x01, 0x03 );
    FCML_I32_A( "vpcomeqb xmm2,xmm5,xmmword ptr [ecx+eax]", 0x8F, 0xE8, 0x50, 0xCC, 0x14, 0x01, 0x04 );
    FCML_I32_A( "vpcomneqb xmm2,xmm5,xmmword ptr [ecx+eax]", 0x8F, 0xE8, 0x50, 0xCC, 0x14, 0x01, 0x05 );
    FCML_I32_A( "vpcomfalseb xmm2,xmm5,xmmword ptr [ecx+eax]", 0x8F, 0xE8, 0x50, 0xCC, 0x14, 0x01, 0x06 );
    FCML_I32_A( "vpcomtrueb xmm2,xmm5,xmmword ptr [ecx+eax]", 0x8F, 0xE8, 0x50, 0xCC, 0x14, 0x01, 0x07 );
    /* GAS*/
    FCML_A64_A( "vpcomltb (%rcx,%rax),%xmm5,%xmm2", 0x8f, 0xe8, 0x50, 0xcc, 0x14, 0x01, 0x00 );
    FCML_A64( "vpcomb $0x00,(%rcx,%rax),%xmm5,%xmm2", 0x8f, 0xe8, 0x50, 0xcc, 0x14, 0x01, 0x00 );
    FCML_A64( "vpcomb $0x01,(%rcx,%rax),%xmm5,%xmm2", 0x8f, 0xe8, 0x50, 0xcc, 0x14, 0x01, 0x01 );
    FCML_A64( "vpcomb $0x02,(%rcx,%rax),%xmm5,%xmm2", 0x8f, 0xe8, 0x50, 0xcc, 0x14, 0x01, 0x02 );
    /* VPCOMW xmm1, xmm2, xmm3/mem128, imm8 8F RXB.01000 0.src.0.00 CD /r ib*/
    FCML_I32( "vpcomw xmm2,xmm5,xmmword ptr [ecx+eax],00h", 0x8F, 0xE8, 0x50, 0xCD, 0x14, 0x01, 0x00 );
    FCML_I64_A_FAILED( "vpcomw xmm0,xmm5,xmm0,20h", 0x8F, 0xE8, 0x50, 0xCD, 0xC0, 0x20 );
    FCML_I32_A( "vpcomltw xmm2,xmm5,xmmword ptr [ecx+eax]", 0x8F, 0xE8, 0x50, 0xCD, 0x14, 0x01, 0x00 );
    FCML_I32_A( "vpcomlew xmm2,xmm5,xmmword ptr [ecx+eax]", 0x8F, 0xE8, 0x50, 0xCD, 0x14, 0x01, 0x01 );
    FCML_I32_A( "vpcomgtw xmm2,xmm5,xmmword ptr [ecx+eax]", 0x8F, 0xE8, 0x50, 0xCD, 0x14, 0x01, 0x02 );
    FCML_I32_A( "vpcomgew xmm2,xmm5,xmmword ptr [ecx+eax]", 0x8F, 0xE8, 0x50, 0xCD, 0x14, 0x01, 0x03 );
    FCML_I32_A( "vpcomeqw xmm2,xmm5,xmmword ptr [ecx+eax]", 0x8F, 0xE8, 0x50, 0xCD, 0x14, 0x01, 0x04 );
    FCML_I32_A( "vpcomneqw xmm2,xmm5,xmmword ptr [ecx+eax]", 0x8F, 0xE8, 0x50, 0xCD, 0x14, 0x01, 0x05 );
    FCML_I32_A( "vpcomfalsew xmm2,xmm5,xmmword ptr [ecx+eax]", 0x8F, 0xE8, 0x50, 0xCD, 0x14, 0x01, 0x06 );
    FCML_I32_A( "vpcomtruew xmm2,xmm5,xmmword ptr [ecx+eax]", 0x8F, 0xE8, 0x50, 0xCD, 0x14, 0x01, 0x07 );
    /* GAS*/
    FCML_A64( "vpcomw $0x00,(%rcx,%rax),%xmm5,%xmm2", 0x8f, 0xe8, 0x50, 0xcd, 0x14, 0x01, 0x00 );
    FCML_A64( "vpcomw $0x01,(%rcx,%rax),%xmm5,%xmm2", 0x8f, 0xe8, 0x50, 0xcd, 0x14, 0x01, 0x01 );
    FCML_A64( "vpcomw $0x02,(%rcx,%rax),%xmm5,%xmm2", 0x8f, 0xe8, 0x50, 0xcd, 0x14, 0x01, 0x02 );
    /* VPCOMD xmm1, xmm2, xmm3/mem128, imm8 8F RXB.01000 0.src.0.00 CE /r ib*/
    FCML_I32( "vpcomd xmm2,xmm5,xmmword ptr [ecx+eax],00h", 0x8F, 0xE8, 0x50, 0xCE, 0x14, 0x01, 0x00 );
    FCML_I64_A_FAILED( "vpcomd xmm0,xmm5,xmm0,20h", 0x8F, 0xE8, 0x50, 0xCE, 0xC0, 0x20 );
    FCML_I32_A( "vpcomltd xmm2,xmm5,xmmword ptr [ecx+eax]", 0x8F, 0xE8, 0x50, 0xCE, 0x14, 0x01, 0x00 );
    FCML_I32_A( "vpcomled xmm2,xmm5,xmmword ptr [ecx+eax]", 0x8F, 0xE8, 0x50, 0xCE, 0x14, 0x01, 0x01 );
    FCML_I32_A( "vpcomgtd xmm2,xmm5,xmmword ptr [ecx+eax]", 0x8F, 0xE8, 0x50, 0xCE, 0x14, 0x01, 0x02 );
    FCML_I32_A( "vpcomged xmm2,xmm5,xmmword ptr [ecx+eax]", 0x8F, 0xE8, 0x50, 0xCE, 0x14, 0x01, 0x03 );
    FCML_I32_A( "vpcomeqd xmm2,xmm5,xmmword ptr [ecx+eax]", 0x8F, 0xE8, 0x50, 0xCE, 0x14, 0x01, 0x04 );
    FCML_I32_A( "vpcomneqd xmm2,xmm5,xmmword ptr [ecx+eax]", 0x8F, 0xE8, 0x50, 0xCE, 0x14, 0x01, 0x05 );
    FCML_I32_A( "vpcomfalsed xmm2,xmm5,xmmword ptr [ecx+eax]", 0x8F, 0xE8, 0x50, 0xCE, 0x14, 0x01, 0x06 );
    FCML_I32_A( "vpcomtrued xmm2,xmm5,xmmword ptr [ecx+eax]", 0x8F, 0xE8, 0x50, 0xCE, 0x14, 0x01, 0x07 );
    /* GAS*/
    FCML_A64( "vpcomd $0x00,(%rcx,%rax),%xmm5,%xmm2", 0x8f, 0xe8, 0x50, 0xce, 0x14, 0x01, 0x00 );
    FCML_A64( "vpcomd $0x01,(%rcx,%rax),%xmm5,%xmm2", 0x8f, 0xe8, 0x50, 0xce, 0x14, 0x01, 0x01 );
    FCML_A64( "vpcomd $0x02,(%rcx,%rax),%xmm5,%xmm2", 0x8f, 0xe8, 0x50, 0xce, 0x14, 0x01, 0x02 );
    /* VPCOMQ xmm1, xmm2, xmm3/mem128, imm8 8F RXB.01000 0.src.0.00 CF /r ib*/
    FCML_I32( "vpcomq xmm2,xmm5,xmmword ptr [ecx+eax],00h", 0x8F, 0xE8, 0x50, 0xCF, 0x14, 0x01, 0x00 );
    FCML_I64_A_FAILED( "vpcomq xmm0,xmm5,xmm0,20h", 0x8F, 0xE8, 0x50, 0xCF, 0xC0, 0x20 );
    FCML_I32_A( "vpcomltq xmm2,xmm5,xmmword ptr [ecx+eax]", 0x8F, 0xE8, 0x50, 0xCF, 0x14, 0x01, 0x00 );
    FCML_I32_A( "vpcomleq xmm2,xmm5,xmmword ptr [ecx+eax]", 0x8F, 0xE8, 0x50, 0xCF, 0x14, 0x01, 0x01 );
    FCML_I32_A( "vpcomgtq xmm2,xmm5,xmmword ptr [ecx+eax]", 0x8F, 0xE8, 0x50, 0xCF, 0x14, 0x01, 0x02 );
    FCML_I32_A( "vpcomgeq xmm2,xmm5,xmmword ptr [ecx+eax]", 0x8F, 0xE8, 0x50, 0xCF, 0x14, 0x01, 0x03 );
    FCML_I32_A( "vpcomeqq xmm2,xmm5,xmmword ptr [ecx+eax]", 0x8F, 0xE8, 0x50, 0xCF, 0x14, 0x01, 0x04 );
    FCML_I32_A( "vpcomneqq xmm2,xmm5,xmmword ptr [ecx+eax]", 0x8F, 0xE8, 0x50, 0xCF, 0x14, 0x01, 0x05 );
    FCML_I32_A( "vpcomfalseq xmm2,xmm5,xmmword ptr [ecx+eax]", 0x8F, 0xE8, 0x50, 0xCF, 0x14, 0x01, 0x06 );
    FCML_I32_A( "vpcomtrueq xmm2,xmm5,xmmword ptr [ecx+eax]", 0x8F, 0xE8, 0x50, 0xCF, 0x14, 0x01, 0x07 );
    /* GAS*/
    FCML_A64( "vpcomq $0x00,(%rcx,%rax),%xmm5,%xmm2", 0x8f, 0xe8, 0x50, 0xcf, 0x14, 0x01, 0x00 );
    FCML_A64( "vpcomq $0x01,(%rcx,%rax),%xmm5,%xmm2", 0x8f, 0xe8, 0x50, 0xcf, 0x14, 0x01, 0x01 );
    FCML_A64( "vpcomq $0x02,(%rcx,%rax),%xmm5,%xmm2", 0x8f, 0xe8, 0x50, 0xcf, 0x14, 0x01, 0x02 );
}

void fcml_tf_instruction_VPCOMU(void) {
    /* VPCOMUB xmm1, xmm2, xmm3/mem128, imm8 8F RXB.01000 0.src.0.00 EC /r ib*/
    FCML_I32( "vpcomub xmm2,xmm5,xmmword ptr [ecx+eax],00h", 0x8F, 0xE8, 0x50, 0xEC, 0x14, 0x01, 0x00 );
    FCML_I64_A_FAILED( "vpcomub xmm0,xmm5,xmm0,20h", 0x8F, 0xE8, 0x50, 0xEC, 0xC0, 0x20 );
    FCML_I32_A( "vpcomltub xmm2,xmm5,xmmword ptr [ecx+eax]", 0x8F, 0xE8, 0x50, 0xEC, 0x14, 0x01, 0x00 );
    FCML_I32_A( "vpcomleub xmm2,xmm5,xmmword ptr [ecx+eax]", 0x8F, 0xE8, 0x50, 0xEC, 0x14, 0x01, 0x01 );
    FCML_I32_A( "vpcomgtub xmm2,xmm5,xmmword ptr [ecx+eax]", 0x8F, 0xE8, 0x50, 0xEC, 0x14, 0x01, 0x02 );
    FCML_I32_A( "vpcomgeub xmm2,xmm5,xmmword ptr [ecx+eax]", 0x8F, 0xE8, 0x50, 0xEC, 0x14, 0x01, 0x03 );
    FCML_I32_A( "vpcomequb xmm2,xmm5,xmmword ptr [ecx+eax]", 0x8F, 0xE8, 0x50, 0xEC, 0x14, 0x01, 0x04 );
    FCML_I32_A( "vpcomnequb xmm2,xmm5,xmmword ptr [ecx+eax]", 0x8F, 0xE8, 0x50, 0xEC, 0x14, 0x01, 0x05 );
    FCML_I32_A( "vpcomfalseub xmm2,xmm5,xmmword ptr [ecx+eax]", 0x8F, 0xE8, 0x50, 0xEC, 0x14, 0x01, 0x06 );
    FCML_I32_A( "vpcomtrueub xmm2,xmm5,xmmword ptr [ecx+eax]", 0x8F, 0xE8, 0x50, 0xEC, 0x14, 0x01, 0x07 );
    /* GAS*/
    FCML_A64( "vpcomub $0x00,(%rcx,%rax),%xmm5,%xmm2", 0x8f, 0xe8, 0x50, 0xec, 0x14, 0x01, 0x00 );
    FCML_A64( "vpcomub $0x01,(%rcx,%rax),%xmm5,%xmm2", 0x8f, 0xe8, 0x50, 0xec, 0x14, 0x01, 0x01 );
    FCML_A64( "vpcomub $0x02,(%rcx,%rax),%xmm5,%xmm2", 0x8f, 0xe8, 0x50, 0xec, 0x14, 0x01, 0x02 );
    FCML_A64( "vpcomub $0x03,(%rcx,%rax),%xmm5,%xmm2", 0x8f, 0xe8, 0x50, 0xec, 0x14, 0x01, 0x03 );
    /* VPCOMUD xmm1, xmm2, xmm3/mem128, imm8 8F RXB.01000 0.src.0.00 EE /r ib*/
    FCML_I32( "vpcomud xmm2,xmm5,xmmword ptr [ecx+eax],00h", 0x8F, 0xE8, 0x50, 0xEE, 0x14, 0x01, 0x00 );
    FCML_I64_A_FAILED( "vpcomud xmm0,xmm5,xmm0,20h", 0x8F, 0xE8, 0x50, 0xEE, 0xC0, 0x20 );
    FCML_I32_A( "vpcomltud xmm2,xmm5,xmmword ptr [ecx+eax]", 0x8F, 0xE8, 0x50, 0xEE, 0x14, 0x01, 0x00 );
    FCML_I32_A( "vpcomleud xmm2,xmm5,xmmword ptr [ecx+eax]", 0x8F, 0xE8, 0x50, 0xEE, 0x14, 0x01, 0x01 );
    FCML_I32_A( "vpcomgtud xmm2,xmm5,xmmword ptr [ecx+eax]", 0x8F, 0xE8, 0x50, 0xEE, 0x14, 0x01, 0x02 );
    FCML_I32_A( "vpcomgeud xmm2,xmm5,xmmword ptr [ecx+eax]", 0x8F, 0xE8, 0x50, 0xEE, 0x14, 0x01, 0x03 );
    FCML_I32_A( "vpcomequd xmm2,xmm5,xmmword ptr [ecx+eax]", 0x8F, 0xE8, 0x50, 0xEE, 0x14, 0x01, 0x04 );
    FCML_I32_A( "vpcomnequd xmm2,xmm5,xmmword ptr [ecx+eax]", 0x8F, 0xE8, 0x50, 0xEE, 0x14, 0x01, 0x05 );
    FCML_I32_A( "vpcomfalseud xmm2,xmm5,xmmword ptr [ecx+eax]", 0x8F, 0xE8, 0x50, 0xEE, 0x14, 0x01, 0x06 );
    FCML_I32_A( "vpcomtrueud xmm2,xmm5,xmmword ptr [ecx+eax]", 0x8F, 0xE8, 0x50, 0xEE, 0x14, 0x01, 0x07 );
    /* GAS*/
    FCML_A64( "vpcomud $0x00,(%rcx,%rax),%xmm5,%xmm2", 0x8f, 0xe8, 0x50, 0xee, 0x14, 0x01, 0x00 );
    FCML_A64( "vpcomud $0x01,(%rcx,%rax),%xmm5,%xmm2", 0x8f, 0xe8, 0x50, 0xee, 0x14, 0x01, 0x01 );
    FCML_A64( "vpcomud $0x02,(%rcx,%rax),%xmm5,%xmm2", 0x8f, 0xe8, 0x50, 0xee, 0x14, 0x01, 0x02 );
    FCML_A64( "vpcomud $0x03,(%rcx,%rax),%xmm5,%xmm2", 0x8f, 0xe8, 0x50, 0xee, 0x14, 0x01, 0x03 );
    /* VPCOMUQ xmm1, xmm2, xmm3/mem128, imm8 8F RXB.01000 0.src.0.00 EF /r ib*/
    FCML_I32( "vpcomuq xmm2,xmm5,xmmword ptr [ecx+eax],00h", 0x8F, 0xE8, 0x50, 0xEF, 0x14, 0x01, 0x00 );
    FCML_I64_A_FAILED( "vpcomuq xmm0,xmm5,xmm0,20h", 0x8F, 0xE8, 0x50, 0xEF, 0xC0, 0x20 );
    FCML_I32_A( "vpcomltuq xmm2,xmm5,xmmword ptr [ecx+eax]", 0x8F, 0xE8, 0x50, 0xEF, 0x14, 0x01, 0x00 );
    FCML_I32_A( "vpcomleuq xmm2,xmm5,xmmword ptr [ecx+eax]", 0x8F, 0xE8, 0x50, 0xEF, 0x14, 0x01, 0x01 );
    FCML_I32_A( "vpcomgtuq xmm2,xmm5,xmmword ptr [ecx+eax]", 0x8F, 0xE8, 0x50, 0xEF, 0x14, 0x01, 0x02 );
    FCML_I32_A( "vpcomgeuq xmm2,xmm5,xmmword ptr [ecx+eax]", 0x8F, 0xE8, 0x50, 0xEF, 0x14, 0x01, 0x03 );
    FCML_I32_A( "vpcomequq xmm2,xmm5,xmmword ptr [ecx+eax]", 0x8F, 0xE8, 0x50, 0xEF, 0x14, 0x01, 0x04 );
    FCML_I32_A( "vpcomnequq xmm2,xmm5,xmmword ptr [ecx+eax]", 0x8F, 0xE8, 0x50, 0xEF, 0x14, 0x01, 0x05 );
    FCML_I32_A( "vpcomfalseuq xmm2,xmm5,xmmword ptr [ecx+eax]", 0x8F, 0xE8, 0x50, 0xEF, 0x14, 0x01, 0x06 );
    FCML_I32_A( "vpcomtrueuq xmm2,xmm5,xmmword ptr [ecx+eax]", 0x8F, 0xE8, 0x50, 0xEF, 0x14, 0x01, 0x07 );
    /* GAS*/
    FCML_A64( "vpcomuq $0x00,(%rcx,%rax),%xmm5,%xmm2", 0x8f, 0xe8, 0x50, 0xef, 0x14, 0x01, 0x00 );
    FCML_A64( "vpcomuq $0x01,(%rcx,%rax),%xmm5,%xmm2", 0x8f, 0xe8, 0x50, 0xef, 0x14, 0x01, 0x01 );
    FCML_A64( "vpcomuq $0x02,(%rcx,%rax),%xmm5,%xmm2", 0x8f, 0xe8, 0x50, 0xef, 0x14, 0x01, 0x02 );
    FCML_A64( "vpcomuq $0x03,(%rcx,%rax),%xmm5,%xmm2", 0x8f, 0xe8, 0x50, 0xef, 0x14, 0x01, 0x03 );
    /* VPCOMUW xmm1, xmm2, xmm3/mem128, imm8 8F RXB.01000 0.src.0.00 ED /r ib*/
    FCML_I32( "vpcomuw xmm2,xmm5,xmmword ptr [ecx+eax],00h", 0x8F, 0xE8, 0x50, 0xED, 0x14, 0x01, 0x00 );
    FCML_I64_A_FAILED( "vpcomuw xmm0,xmm5,xmm0,20h", 0x8F, 0xE8, 0x50, 0xED, 0xC0, 0x20 );
    FCML_I32_A( "vpcomltuw xmm2,xmm5,xmmword ptr [ecx+eax]", 0x8F, 0xE8, 0x50, 0xED, 0x14, 0x01, 0x00 );
    FCML_I32_A( "vpcomleuw xmm2,xmm5,xmmword ptr [ecx+eax]", 0x8F, 0xE8, 0x50, 0xED, 0x14, 0x01, 0x01 );
    FCML_I32_A( "vpcomgtuw xmm2,xmm5,xmmword ptr [ecx+eax]", 0x8F, 0xE8, 0x50, 0xED, 0x14, 0x01, 0x02 );
    FCML_I32_A( "vpcomgeuw xmm2,xmm5,xmmword ptr [ecx+eax]", 0x8F, 0xE8, 0x50, 0xED, 0x14, 0x01, 0x03 );
    FCML_I32_A( "vpcomequw xmm2,xmm5,xmmword ptr [ecx+eax]", 0x8F, 0xE8, 0x50, 0xED, 0x14, 0x01, 0x04 );
    FCML_I32_A( "vpcomnequw xmm2,xmm5,xmmword ptr [ecx+eax]", 0x8F, 0xE8, 0x50, 0xED, 0x14, 0x01, 0x05 );
    FCML_I32_A( "vpcomfalseuw xmm2,xmm5,xmmword ptr [ecx+eax]", 0x8F, 0xE8, 0x50, 0xED, 0x14, 0x01, 0x06 );
    FCML_I32_A( "vpcomtrueuw xmm2,xmm5,xmmword ptr [ecx+eax]", 0x8F, 0xE8, 0x50, 0xED, 0x14, 0x01, 0x07 );
    /* GAS*/
    FCML_A64( "vpcomuw $0x00,(%rcx,%rax),%xmm5,%xmm2", 0x8f, 0xe8, 0x50, 0xed, 0x14, 0x01, 0x00 );
    FCML_A64( "vpcomuw $0x01,(%rcx,%rax),%xmm5,%xmm2", 0x8f, 0xe8, 0x50, 0xed, 0x14, 0x01, 0x01 );
    FCML_A64( "vpcomuw $0x02,(%rcx,%rax),%xmm5,%xmm2", 0x8f, 0xe8, 0x50, 0xed, 0x14, 0x01, 0x02 );
    FCML_A64( "vpcomuw $0x03,(%rcx,%rax),%xmm5,%xmm2", 0x8f, 0xe8, 0x50, 0xed, 0x14, 0x01, 0x03 );
}

void fcml_tf_instruction_VPHADDBD(void) {
    /* VPHADDBD xmm1, xmm2/mem128 8F RXB.01001 0.1111.0.00 C2 /r*/
    FCML_I32( "vphaddbd xmm0,xmmword ptr [eax]", 0x8F, 0xE9, 0x78, 0xC2, 0x00 );
    FCML_I32( "vphaddbd xmm0,xmm1", 0x8F, 0xE9, 0x78, 0xC2, 0xC1 );
    /* GAS*/
    FCML_A64( "vphaddbd (%rax),%xmm0", 0x8f, 0xe9, 0x78, 0xc2, 0x00 );
    FCML_A64( "vphaddbd %xmm1,%xmm0", 0x8f, 0xe9, 0x78, 0xc2, 0xc1 );
}

void fcml_tf_instruction_VPHADDBW(void) {
    /* VPHADDBW xmm1, xmm2/mem128 8F RXB.01001 0.1111.0.00 C1 /r*/
    FCML_I32( "vphaddbw xmm0,xmmword ptr [eax]", 0x8F, 0xE9, 0x78, 0xC1, 0x00 );
    FCML_I32( "vphaddbw xmm0,xmm1", 0x8F, 0xE9, 0x78, 0xC1, 0xC1 );
    /* GAS*/
    FCML_A64( "vphaddbw (%rax),%xmm0", 0x8f, 0xe9, 0x78, 0xc1, 0x00 );
    FCML_A64( "vphaddbw %xmm1,%xmm0", 0x8f, 0xe9, 0x78, 0xc1, 0xc1 );
}

void fcml_tf_instruction_VPHADDBQ(void) {
    /* VPHADDBQ xmm1, xmm2/mem128 8F RXB.01001 0.1111.0.00 C3 /r*/
    FCML_I32( "vphaddbq xmm0,xmmword ptr [eax]", 0x8F, 0xE9, 0x78, 0xC3, 0x00 );
    FCML_I32( "vphaddbq xmm0,xmm1", 0x8F, 0xE9, 0x78, 0xC3, 0xC1 );
    /* GAS*/
    FCML_A64( "vphaddbq (%rax),%xmm0", 0x8f, 0xe9, 0x78, 0xc3, 0x00 );
    FCML_A64( "vphaddbq %xmm1,%xmm0", 0x8f, 0xe9, 0x78, 0xc3, 0xc1 );
}

void fcml_tf_instruction_VPHADDDQ(void) {
    /* VPHADDDQ xmm1, xmm2/mem128 8F RXB.01001 0.1111.0.00 CB /r*/
    FCML_I32( "vphadddq xmm0,xmmword ptr [eax]", 0x8F, 0xE9, 0x78, 0xCB, 0x00 );
    FCML_I32( "vphadddq xmm0,xmm1", 0x8F, 0xE9, 0x78, 0xCB, 0xC1 );
    /* GAS*/
    FCML_A64( "vphadddq (%rax),%xmm0", 0x8f, 0xe9, 0x78, 0xcb, 0x00 );
    FCML_A64( "vphadddq %xmm1,%xmm0", 0x8f, 0xe9, 0x78, 0xcb, 0xc1 );
}

void fcml_tf_instruction_VPHADDUBD(void) {
    /* VPHADDUBD xmm1, xmm2/mem128 8F RXB.01001 0.1111.0.00 D2 /r*/
    FCML_I32( "vphaddubd xmm0,xmmword ptr [eax]", 0x8F, 0xE9, 0x78, 0xD2, 0x00 );
    FCML_I32( "vphaddubd xmm0,xmm1", 0x8F, 0xE9, 0x78, 0xD2, 0xC1 );
    /* GAS*/
    FCML_A64( "vphaddubd (%rax),%xmm0", 0x8f, 0xe9, 0x78, 0xd2, 0x00 );
    FCML_A64( "vphaddubd %xmm1,%xmm0", 0x8f, 0xe9, 0x78, 0xd2, 0xc1 );
}

void fcml_tf_instruction_VPHADDUBQ(void) {
    /* VPHADDUBQ xmm1, xmm2/mem128 8F RXB.01001 0.1111.0.00 D3 /r*/
    FCML_I32( "vphaddubq xmm0,xmmword ptr [eax]", 0x8F, 0xE9, 0x78, 0xD3, 0x00 );
    FCML_I32( "vphaddubq xmm0,xmm1", 0x8F, 0xE9, 0x78, 0xD3, 0xC1 );
    /* GAS*/
    FCML_A64( "vphaddubq (%rax),%xmm0", 0x8f, 0xe9, 0x78, 0xd3, 0x00 );
    FCML_A64( "vphaddubq %xmm1,%xmm0", 0x8f, 0xe9, 0x78, 0xd3, 0xc1 );
}

void fcml_tf_instruction_VPHADDUBW(void) {
    /* VPHADDUBWD xmm1, xmm2/mem128 8F RXB.01001 0.1111.0.00 D1 /r*/
    FCML_I32( "vphaddubw xmm0,xmmword ptr [eax]", 0x8F, 0xE9, 0x78, 0xD1, 0x00 );
    FCML_I32( "vphaddubw xmm0,xmm1", 0x8F, 0xE9, 0x78, 0xD1, 0xC1 );
    /* GAS*/
    FCML_A64( "vphaddubw (%rax),%xmm0", 0x8f, 0xe9, 0x78, 0xd1, 0x00 );
    FCML_A64( "vphaddubw %xmm1,%xmm0", 0x8f, 0xe9, 0x78, 0xd1, 0xc1 );
}

void fcml_tf_instruction_VPHADDUDQ(void) {
    /* VPHADDUDQ xmm1, xmm2/mem128 8F RXB.01001 0.1111.0.00 DB /r*/
    FCML_I32( "vphaddudq xmm0,xmmword ptr [eax]", 0x8F, 0xE9, 0x78, 0xDB, 0x00 );
    FCML_I32( "vphaddudq xmm0,xmm1", 0x8F, 0xE9, 0x78, 0xDB, 0xC1 );
    /* GAS*/
    FCML_A64( "vphaddudq (%rax),%xmm0", 0x8f, 0xe9, 0x78, 0xdb, 0x00 );
    FCML_A64( "vphaddudq %xmm1,%xmm0", 0x8f, 0xe9, 0x78, 0xdb, 0xc1 );
}

void fcml_tf_instruction_VPHADDUWD(void) {
    /* VPHADDUWD xmm1, xmm2/mem128 8F RXB.01001 0.1111.0.00 D6 /r*/
    FCML_I32( "vphadduwd xmm0,xmmword ptr [eax]", 0x8F, 0xE9, 0x78, 0xD6, 0x00 );
    FCML_I32( "vphadduwd xmm0,xmm1", 0x8F, 0xE9, 0x78, 0xD6, 0xC1 );
    /* GAS*/
    FCML_A64( "vphadduwd (%rax),%xmm0", 0x8f, 0xe9, 0x78, 0xd6, 0x00 );
    FCML_A64( "vphadduwd %xmm1,%xmm0", 0x8f, 0xe9, 0x78, 0xd6, 0xc1 );
}

void fcml_tf_instruction_VPHADDUWQ(void) {
    /* VPHADDUWQ xmm1, xmm2/mem128 8F RXB.01001 0.1111.0.00 D7 /r*/
    FCML_I32( "vphadduwq xmm0,xmmword ptr [eax]", 0x8F, 0xE9, 0x78, 0xD7, 0x00 );
    FCML_I32( "vphadduwq xmm0,xmm1", 0x8F, 0xE9, 0x78, 0xD7, 0xC1 );
    /* GAS*/
    FCML_A64( "vphadduwq (%rax),%xmm0", 0x8f, 0xe9, 0x78, 0xd7, 0x00 );
    FCML_A64( "vphadduwq %xmm1,%xmm0", 0x8f, 0xe9, 0x78, 0xd7, 0xc1 );
}

void fcml_tf_instruction_VPHADDWD(void) {
    /* VPHADDWD xmm1, xmm2/mem128 8F RXB.01001 0.1111.0.00 C6 /r*/
    FCML_I32( "vphaddwd xmm0,xmmword ptr [eax]", 0x8F, 0xE9, 0x78, 0xC6, 0x00 );
    FCML_I32( "vphaddwd xmm0,xmm1", 0x8F, 0xE9, 0x78, 0xC6, 0xC1 );
    /* GAS*/
    FCML_A64( "vphaddwd (%rax),%xmm0", 0x8f, 0xe9, 0x78, 0xc6, 0x00 );
    FCML_A64( "vphaddwd %xmm1,%xmm0", 0x8f, 0xe9, 0x78, 0xc6, 0xc1 );
}

void fcml_tf_instruction_VPHADDWQ(void) {
    /* VPHADDWQ xmm1, xmm2/mem128 8F RXB.01001 0.1111.0.00 C7 /r*/
    FCML_I32( "vphaddwq xmm0,xmmword ptr [eax]", 0x8F, 0xE9, 0x78, 0xC7, 0x00 );
    FCML_I32( "vphaddwq xmm0,xmm1", 0x8F, 0xE9, 0x78, 0xC7, 0xC1 );
    /* GAS*/
    FCML_A64( "vphaddwq (%rax),%xmm0", 0x8f, 0xe9, 0x78, 0xc7, 0x00 );
    FCML_A64( "vphaddwq %xmm1,%xmm0", 0x8f, 0xe9, 0x78, 0xc7, 0xc1 );
}

void fcml_tf_instruction_VPHSUBBW(void) {
    /* VPHSUBBW xmm1, xmm2/mem128 8F RXB.01001 0.1111.0.00 E1 /r*/
    FCML_I32( "vphsubbw xmm0,xmmword ptr [eax]", 0x8F, 0xE9, 0x78, 0xE1, 0x00 );
    FCML_I32( "vphsubbw xmm0,xmm1", 0x8F, 0xE9, 0x78, 0xE1, 0xC1 );
    /* GAS*/
    FCML_A64( "vphsubbw (%rax),%xmm0", 0x8f, 0xe9, 0x78, 0xe1, 0x00 );
    FCML_A64( "vphsubbw %xmm1,%xmm0", 0x8f, 0xe9, 0x78, 0xe1, 0xc1 );
}

void fcml_tf_instruction_VPHSUBDQ(void) {
    /* VPHSUBDQ xmm1, xmm2/mem128 8F RXB.01001 0.1111.0.00 E3 /r*/
    FCML_I32( "vphsubdq xmm0,xmmword ptr [eax]", 0x8F, 0xE9, 0x78, 0xE3, 0x00 );
    FCML_I32( "vphsubdq xmm0,xmm1", 0x8F, 0xE9, 0x78, 0xE3, 0xC1 );
    /* GAS*/
    FCML_A64( "vphsubdq (%rax),%xmm0", 0x8f, 0xe9, 0x78, 0xe3, 0x00 );
    FCML_A64( "vphsubdq %xmm1,%xmm0", 0x8f, 0xe9, 0x78, 0xe3, 0xc1 );
}

void fcml_tf_instruction_VPHSUBWD(void) {
    /* VPHSUBWD xmm1, xmm2/mem128 8F RXB.01001 0.1111.0.00 E2 /r*/
    FCML_I32( "vphsubwd xmm0,xmmword ptr [eax]", 0x8F, 0xE9, 0x78, 0xE2, 0x00 );
    FCML_I32( "vphsubwd xmm0,xmm1", 0x8F, 0xE9, 0x78, 0xE2, 0xC1 );
    /* GAS*/
    FCML_A64( "vphsubwd (%rax),%xmm0", 0x8f, 0xe9, 0x78, 0xe2, 0x00 );
    FCML_A64( "vphsubwd %xmm1,%xmm0", 0x8f, 0xe9, 0x78, 0xe2, 0xc1 );
}

void fcml_tf_instruction_VPMACSDD(void) {
    /* VPMACSDD xmm1, xmm2, xmm3/mem128, xmm4 8F RXB.01000 0.src.0.00 9E /r ib*/
    FCML_I32( "vpmacsdd xmm2,xmm5,xmmword ptr [ecx+eax],xmm2", 0x8F, 0xE8, 0x50, 0x9E, 0x14, 0x01, 0x20 );
    FCML_I64( "vpmacsdd xmm0,xmm5,xmm0,xmm2", 0x8F, 0xE8, 0x50, 0x9E, 0xC0, 0x20 );
    /* GAS*/
    FCML_A64( "vpmacsdd %xmm2,(%rcx,%rax),%xmm5,%xmm2", 0x8f, 0xe8, 0x50, 0x9e, 0x14, 0x01, 0x20 );
    FCML_A64( "vpmacsdd %xmm2,%xmm0,%xmm5,%xmm0", 0x8f, 0xe8, 0x50, 0x9e, 0xc0, 0x20 );
}

void fcml_tf_instruction_VPMACSDQH(void) {
    /* VPMACSDQH xmm1, xmm2, xmm3/mem128, xmm4 8F RXB.01000 0.src.0.00 9F /r ib*/
    FCML_I32( "vpmacsdqh xmm2,xmm5,xmmword ptr [ecx+eax],xmm2", 0x8F, 0xE8, 0x50, 0x9F, 0x14, 0x01, 0x20 );
    FCML_I64( "vpmacsdqh xmm0,xmm5,xmm0,xmm2", 0x8F, 0xE8, 0x50, 0x9F, 0xC0, 0x20 );
    /* GAS*/
    FCML_A64( "vpmacsdqh %xmm2,(%rcx,%rax),%xmm5,%xmm2", 0x8f, 0xe8, 0x50, 0x9f, 0x14, 0x01, 0x20 );
    FCML_A64( "vpmacsdqh %xmm2,%xmm0,%xmm5,%xmm0", 0x8f, 0xe8, 0x50, 0x9f, 0xc0, 0x20 );
}

void fcml_tf_instruction_VPMACSDQL(void) {
    /* VPMACSDQL xmm1, xmm2, xmm3/mem128, xmm4 8F RXB.01000 0.src.0.00 97 /r ib*/
    FCML_I32( "vpmacsdql xmm2,xmm5,xmmword ptr [ecx+eax],xmm2", 0x8F, 0xE8, 0x50, 0x97, 0x14, 0x01, 0x20 );
    FCML_I64( "vpmacsdql xmm0,xmm5,xmm0,xmm2", 0x8F, 0xE8, 0x50, 0x97, 0xC0, 0x20 );
    /* GAS*/
    FCML_A64( "vpmacsdql %xmm2,(%rcx,%rax),%xmm5,%xmm2", 0x8f, 0xe8, 0x50, 0x97, 0x14, 0x01, 0x20 );
    FCML_A64( "vpmacsdql %xmm2,%xmm0,%xmm5,%xmm0", 0x8f, 0xe8, 0x50, 0x97, 0xc0, 0x20 );
}

void fcml_tf_instruction_VPMACSSDD(void) {
    /* VPMACSSDD xmm1, xmm2, xmm3/mem128, xmm4 8F RXB.01000 X.src.0.00 8E /r ib*/
    FCML_I32( "vpmacssdd xmm2,xmm5,xmmword ptr [ecx+eax],xmm2", 0x8F, 0xE8, 0x50, 0x8E, 0x14, 0x01, 0x20 );
    FCML_I64( "vpmacssdd xmm0,xmm5,xmm0,xmm2", 0x8F, 0xE8, 0x50, 0x8E, 0xC0, 0x20 );
    /* GAS*/
    FCML_A64( "vpmacssdd %xmm2,(%rcx,%rax),%xmm5,%xmm2", 0x8f, 0xe8, 0x50, 0x8e, 0x14, 0x01, 0x20 );
    FCML_A64( "vpmacssdd %xmm2,%xmm0,%xmm5,%xmm0", 0x8f, 0xe8, 0x50, 0x8e, 0xc0, 0x20 );
}

void fcml_tf_instruction_VPMACSSDQH(void) {
    /* VPMACSSDQH xmm1, xmm2, xmm3/mem128, xmm4 8F RXB.01000 0.src.0.00 8F /r ib*/
    FCML_I32( "vpmacssdqh xmm2,xmm5,xmmword ptr [ecx+eax],xmm2", 0x8F, 0xE8, 0x50, 0x8F, 0x14, 0x01, 0x20 );
    FCML_I64( "vpmacssdqh xmm0,xmm5,xmm0,xmm2", 0x8F, 0xE8, 0x50, 0x8F, 0xC0, 0x20 );
    /* GAS*/
    FCML_A64( "vpmacssdqh %xmm2,(%rcx,%rax),%xmm5,%xmm2", 0x8f, 0xe8, 0x50, 0x8f, 0x14, 0x01, 0x20 );
    FCML_A64( "vpmacssdqh %xmm2,%xmm0,%xmm5,%xmm0", 0x8f, 0xe8, 0x50, 0x8f, 0xc0, 0x20 );
}

void fcml_tf_instruction_VPMACSSDQL(void) {
    /* VPMACSSDQL xmm1, xmm2, xmm3/mem128, xmm4 8F RXB.01000 0.src.0.00 87 /r ib*/
    FCML_I32( "vpmacssdql xmm2,xmm5,xmmword ptr [ecx+eax],xmm2", 0x8F, 0xE8, 0x50, 0x87, 0x14, 0x01, 0x20 );
    FCML_I64( "vpmacssdql xmm0,xmm5,xmm0,xmm2", 0x8F, 0xE8, 0x50, 0x87, 0xC0, 0x20 );
    /* GAS*/
    FCML_A64( "vpmacssdql %xmm2,(%rcx,%rax),%xmm5,%xmm2", 0x8f, 0xe8, 0x50, 0x87, 0x14, 0x01, 0x20 );
    FCML_A64( "vpmacssdql %xmm2,%xmm0,%xmm5,%xmm0", 0x8f, 0xe8, 0x50, 0x87, 0xc0, 0x20 );
}

void fcml_tf_instruction_VPMACSSWD(void) {
    /* VPMACSSWD xmm1, xmm2, xmm3/mem128, xmm4 8F RXB.01000 0.src.0.00 86 /r ib*/
    FCML_I32( "vpmacsswd xmm2,xmm5,xmmword ptr [ecx+eax],xmm2", 0x8F, 0xE8, 0x50, 0x86, 0x14, 0x01, 0x20 );
    FCML_I64( "vpmacsswd xmm0,xmm5,xmm0,xmm2", 0x8F, 0xE8, 0x50, 0x86, 0xC0, 0x20 );
    /* GAS*/
    FCML_A64( "vpmacsswd %xmm2,(%rcx,%rax),%xmm5,%xmm2", 0x8f, 0xe8, 0x50, 0x86, 0x14, 0x01, 0x20 );
    FCML_A64( "vpmacsswd %xmm2,%xmm0,%xmm5,%xmm0", 0x8f, 0xe8, 0x50, 0x86, 0xc0, 0x20 );
}

void fcml_tf_instruction_VPMACSSWW(void) {
	/* VPMACSSWW xmm1, xmm2, xmm3/mem128, xmm4 8F RXB.01000 X.src.0.00 85 /r ib*/
    FCML_I32( "vpmacssww xmm2,xmm5,xmmword ptr [ecx+eax],xmm2", 0x8F, 0xE8, 0x50, 0x85, 0x14, 0x01, 0x20 );
    FCML_I64( "vpmacssww xmm0,xmm5,xmm0,xmm2", 0x8F, 0xE8, 0x50, 0x85, 0xC0, 0x20 );
    /* GAS*/
    FCML_A64( "vpmacssww %xmm2,(%rcx,%rax),%xmm5,%xmm2", 0x8f, 0xe8, 0x50, 0x85, 0x14, 0x01, 0x20 );
    FCML_A64( "vpmacssww %xmm2,%xmm0,%xmm5,%xmm0", 0x8f, 0xe8, 0x50, 0x85, 0xc0, 0x20 );
}

void fcml_tf_instruction_VPMACSWD(void) {
    /* VPMACSWD xmm1, xmm2, xmm3/mem128, xmm4 8F RXB.01000 0.src.0.00 96 /r ib*/
    FCML_I32( "vpmacswd xmm2,xmm5,xmmword ptr [ecx+eax],xmm2", 0x8F, 0xE8, 0x50, 0x96, 0x14, 0x01, 0x20 );
    FCML_I64( "vpmacswd xmm0,xmm5,xmm0,xmm2", 0x8F, 0xE8, 0x50, 0x96, 0xC0, 0x20 );
    /* GAS*/
    FCML_A64( "vpmacswd %xmm2,(%rcx,%rax),%xmm5,%xmm2", 0x8f, 0xe8, 0x50, 0x96, 0x14, 0x01, 0x20 );
    FCML_A64( "vpmacswd %xmm2,%xmm0,%xmm5,%xmm0", 0x8f, 0xe8, 0x50, 0x96, 0xc0, 0x20 );
}

void fcml_tf_instruction_VPMACSWW(void) {
    /* VPMACSWW xmm1, xmm2, xmm3/mem128, xmm4 8F RXB.01000 0.src.0.00 95 /r ib*/
    FCML_I32( "vpmacsww xmm2,xmm5,xmmword ptr [ecx+eax],xmm2", 0x8F, 0xE8, 0x50, 0x95, 0x14, 0x01, 0x20 );
    FCML_I64( "vpmacsww xmm0,xmm5,xmm0,xmm2", 0x8F, 0xE8, 0x50, 0x95, 0xC0, 0x20 );
    /* GAS*/
    FCML_A64( "vpmacsww %xmm2,(%rcx,%rax),%xmm5,%xmm2", 0x8f, 0xe8, 0x50, 0x95, 0x14, 0x01, 0x20 );
    FCML_A64( "vpmacsww %xmm2,%xmm0,%xmm5,%xmm0", 0x8f, 0xe8, 0x50, 0x95, 0xc0, 0x20 );
}

void fcml_tf_instruction_VPMADCSSWD(void) {
    /* VPMADCSSWD xmm1, xmm2, xmm3/mem128, xmm4 8F RXB.01000 0.src.0.00 A6 /r ib*/
    FCML_I32( "vpmadcsswd xmm2,xmm5,xmmword ptr [ecx+eax],xmm2", 0x8F, 0xE8, 0x50, 0xA6, 0x14, 0x01, 0x20 );
    FCML_I64( "vpmadcsswd xmm0,xmm5,xmm0,xmm2", 0x8F, 0xE8, 0x50, 0xA6, 0xC0, 0x20 );
    /* GAS*/
    FCML_I32( "vpmadcsswd xmm2,xmm5,xmmword ptr [ecx+eax],xmm2", 0x8F, 0xE8, 0x50, 0xA6, 0x14, 0x01, 0x20 );
    FCML_I64( "vpmadcsswd xmm0,xmm5,xmm0,xmm2", 0x8F, 0xE8, 0x50, 0xA6, 0xC0, 0x20 );
}

void fcml_tf_instruction_VPMADCSWD(void) {
    /* VPMADCSWD xmm1, xmm2, xmm3/mem128, xmm4 8F RXB.01000 0.src.0.00 B6 /r ib*/
    FCML_I32( "vpmadcswd xmm2,xmm5,xmmword ptr [ecx+eax],xmm2", 0x8F, 0xE8, 0x50, 0xB6, 0x14, 0x01, 0x20 );
    FCML_I64( "vpmadcswd xmm0,xmm5,xmm0,xmm2", 0x8F, 0xE8, 0x50, 0xB6, 0xC0, 0x20 );
    /* GAS*/
    FCML_A64( "vpmadcswd %xmm2,(%rcx,%rax),%xmm5,%xmm2", 0x8f, 0xe8, 0x50, 0xb6, 0x14, 0x01, 0x20 );
    FCML_A64( "vpmadcswd %xmm2,%xmm0,%xmm5,%xmm0", 0x8f, 0xe8, 0x50, 0xb6, 0xc0, 0x20 );
}

void fcml_tf_instruction_VPPERM(void) {
    /* VPPERM xmm1, xmm2, xmm3/mem128, xmm4 8F RXB.01000 0.src.0.00 A3 /r ib*/
    FCML_I32( "vpperm xmm2,xmm5,xmmword ptr [ecx+eax],xmm2", 0x8F, 0xE8, 0x50, 0xA3, 0x14, 0x01, 0x20 );
    FCML_I64_M( "vpperm xmm0,xmm5,xmm0,xmm2", 2, FCML_MI( 0x8f, 0xe8, 0xd0, 0xa3, 0xc2, 0x00 ), FCML_MI( 0x8f, 0xe8, 0x50, 0xa3, 0xc0, 0x20 ) );
    /* VPPERM xmm1, xmm2, xmm3, xmm4/mem128 8F RXB.01000 1.src.0.00 A3 /r ib*/
    FCML_I64( "vpperm xmm2,xmm5,xmm2,xmmword ptr [rcx+rax]", 0x8F, 0xE8, 0xD0, 0xA3, 0x14, 0x01, 0x20 );
    FCML_I64_M( "vpperm xmm0,xmm5,xmm2,xmm0", 2, FCML_MI( 0x8f, 0xe8, 0xd0, 0xa3, 0xc0, 0x20 ), FCML_MI( 0x8f, 0xe8, 0x50, 0xa3, 0xc2, 0x00 ) );
    /* GAS*/
    FCML_A64( "vpperm %xmm2,(%rcx,%rax),%xmm5,%xmm2", 0x8f, 0xe8, 0x50, 0xa3, 0x14, 0x01, 0x20 );
    FCML_A64( "vpperm (%rcx,%rax),%xmm2,%xmm5,%xmm2", 0x8f, 0xe8, 0xd0, 0xa3, 0x14, 0x01, 0x20 );
}

void fcml_tf_instruction_VPROTD(void) {
    /* VPROTD xmm1, xmm2/mem128, xmm3 8F RXB.01001 0.src.0.00 92 /r*/
    FCML_I64( "vprotd xmm2,xmmword ptr [rcx+rax],xmm5", 0x8F, 0xE9, 0x50, 0x92, 0x14, 0x01 );
    FCML_I64_M( "vprotd xmm0,xmm0,xmm5", 2, FCML_MI( 0x8f, 0xe9, 0xf8, 0x92, 0xc5 ), FCML_MI( 0x8f, 0xe9, 0x50, 0x92, 0xc0 ) );
    /* VPROTD xmm1, xmm2, xmm3/mem128 8F RXB.01001 1.src.0.00 92 /r*/
    FCML_I64( "vprotd xmm2,xmm5,xmmword ptr [rcx+rax]", 0x8F, 0xE9, 0xD0, 0x92, 0x14, 0x01 );
    FCML_I64_M( "vprotd xmm0,xmm5,xmm0", 2, FCML_MI( 0x8f, 0xe9, 0xd0, 0x92, 0xc0 ), FCML_MI( 0x8f, 0xe9, 0x78, 0x92, 0xc5 ) );
    /* VPROTD xmm1, xmm2/mem128, imm8 8F RXB.01000 0.1111.0.00 C2 /r ib*/
    FCML_I32( "vprotd xmm2,xmmword ptr [ecx+eax],20h", 0x8F, 0xE8, 0x78, 0xC2, 0x14, 0x01, 0x20 );
    FCML_I64( "vprotd xmm0,xmm0,20h", 0x8F, 0xE8, 0x78, 0xC2, 0xC0, 0x20 );
    /* GAS*/
    FCML_A64( "vprotd %xmm5,(%rcx,%rax),%xmm2", 0x8f, 0xe9, 0x50, 0x92, 0x14, 0x01 );
    FCML_A64( "vprotd (%rcx,%rax),%xmm5,%xmm2", 0x8f, 0xe9, 0xd0, 0x92, 0x14, 0x01 );
    FCML_A64( "vprotd $0x20,(%rcx,%rax),%xmm2", 0x8f, 0xe8, 0x78, 0xc2, 0x14, 0x01, 0x20 );
    FCML_A64( "vprotd $0x20,%xmm0,%xmm0", 0x8f, 0xe8, 0x78, 0xc2, 0xc0, 0x20 );
}

void fcml_tf_instruction_VPROTB(void) {
    /* VPROTB xmm1, xmm2/mem128, xmm3 8F RXB.01001 0.src.0.00 90 /r*/
    FCML_I32( "vprotb xmm2,xmmword ptr [ecx+eax],xmm5", 0x8F, 0xE9, 0x50, 0x90, 0x14, 0x01 );
    FCML_I64_M( "vprotb xmm0,xmm0,xmm5", 2, FCML_MI( 0x8f, 0xe9, 0xf8, 0x90, 0xc5 ), FCML_MI( 0x8f, 0xe9, 0x50, 0x90, 0xc0 ) );
    /* VPROTB xmm1, xmm2, xmm3/mem128 8F RXB.01001 1.src.0.00 90 /r*/
    FCML_I64( "vprotb xmm2,xmm5,xmmword ptr [rcx+rax]", 0x8F, 0xE9, 0xD0, 0x90, 0x14, 0x01 );
    FCML_I64_M( "vprotb xmm0,xmm5,xmm0", 2, FCML_MI( 0x8f, 0xe9, 0xd0, 0x90, 0xc0 ), FCML_MI( 0x8f, 0xe9, 0x78, 0x90, 0xc5 ) );
    /* VPROTB xmm1, xmm2/mem128, imm8 8F RXB.01000 0.1111.0.00 C0 /r ib*/
    FCML_I32( "vprotb xmm2,xmmword ptr [ecx+eax],20h", 0x8F, 0xE8, 0x78, 0xC0, 0x14, 0x01, 0x20 );
    FCML_I64( "vprotb xmm0,xmm0,20h", 0x8F, 0xE8, 0x78, 0xC0, 0xC0, 0x20 );
    /* GAS*/
    FCML_A64( "vprotb %xmm5,(%rcx,%rax),%xmm2", 0x8f, 0xe9, 0x50, 0x90, 0x14, 0x01 );
    FCML_A64( "vprotb (%rcx,%rax),%xmm5,%xmm2", 0x8f, 0xe9, 0xd0, 0x90, 0x14, 0x01 );
    FCML_A64( "vprotb $0x20,(%rcx,%rax),%xmm2", 0x8f, 0xe8, 0x78, 0xc0, 0x14, 0x01, 0x20 );
    FCML_A64( "vprotb $0x20,%xmm0,%xmm0", 0x8f, 0xe8, 0x78, 0xc0, 0xc0, 0x20 );
}

void fcml_tf_instruction_VPROTQ(void) {
    /* VPROTQ xmm1, xmm2/mem128, xmm3 8F RXB.01001 0.src.0.00 93 /r*/
    FCML_I32( "vprotq xmm2,xmmword ptr [ecx+eax],xmm5", 0x8F, 0xE9, 0x50, 0x93, 0x14, 0x01 );
    FCML_I64_M( "vprotq xmm0,xmm0,xmm5", 2, FCML_MI( 0x8f, 0xe9, 0xf8, 0x93, 0xc5 ), FCML_MI( 0x8f, 0xe9, 0x50, 0x93, 0xc0 ) );
    /* VPROTQ xmm1, xmm2, xmm3/mem128 8F RXB.01001 1.src.0.00 93 /r*/
    FCML_I64( "vprotq xmm2,xmm5,xmmword ptr [rcx+rax]", 0x8F, 0xE9, 0xD0, 0x93, 0x14, 0x01 );
    FCML_I64_M( "vprotq xmm0,xmm5,xmm0", 2, FCML_MI( 0x8f, 0xe9, 0xd0, 0x93, 0xc0 ), FCML_MI( 0x8f, 0xe9, 0x78, 0x93, 0xc5 ) );
    /* VPROTQ xmm1, xmm2/mem128, imm8 8F RXB.01000 0.1111.0.00 C3 /r ib*/
    FCML_I32( "vprotq xmm2,xmmword ptr [ecx+eax],20h", 0x8F, 0xE8, 0x78, 0xC3, 0x14, 0x01, 0x20 );
    FCML_I64( "vprotq xmm0,xmm0,20h", 0x8F, 0xE8, 0x78, 0xC3, 0xC0, 0x20 );
    /* GAS*/
    FCML_A64( "vprotq %xmm5,(%rcx,%rax),%xmm2", 0x8f, 0xe9, 0x50, 0x93, 0x14, 0x01 );
    FCML_A64( "vprotq (%rcx,%rax),%xmm5,%xmm2", 0x8f, 0xe9, 0xd0, 0x93, 0x14, 0x01 );
    FCML_A64( "vprotq $0x20,(%rcx,%rax),%xmm2", 0x8f, 0xe8, 0x78, 0xc3, 0x14, 0x01, 0x20 );
    FCML_A64( "vprotq $0x20,%xmm0,%xmm0", 0x8f, 0xe8, 0x78, 0xc3, 0xc0, 0x20 );
}

void fcml_tf_instruction_VPROTW(void) {
    /* VPROTW xmm1, xmm2/mem128, xmm3 8F RXB.01001 0.src.0.00 91 /r*/
    FCML_I32( "vprotw xmm2,xmmword ptr [ecx+eax],xmm5", 0x8F, 0xE9, 0x50, 0x91, 0x14, 0x01 );
    FCML_I64_M( "vprotw xmm0,xmm0,xmm5", 2, FCML_MI( 0x8f, 0xe9, 0xf8, 0x91, 0xc5 ), FCML_MI( 0x8f, 0xe9, 0x50, 0x91, 0xc0 ) );
    /* VPROTW xmm1, xmm2, xmm3/mem128 8F RXB.01001 1.src.0.00 91 /r*/
    FCML_I64( "vprotw xmm2,xmm5,xmmword ptr [rcx+rax]", 0x8F, 0xE9, 0xD0, 0x91, 0x14, 0x01 );
    FCML_I64_M( "vprotw xmm0,xmm5,xmm0", 2, FCML_MI( 0x8f, 0xe9, 0xd0, 0x91, 0xc0 ), FCML_MI( 0x8f, 0xe9, 0x78, 0x91, 0xc5 ) );
    /* VPROTW xmm1, xmm2/mem128, imm8 8F RXB.01000 0.1111.0.00 C1 /r ib*/
    FCML_I32( "vprotw xmm2,xmmword ptr [ecx+eax],20h", 0x8F, 0xE8, 0x78, 0xC1, 0x14, 0x01, 0x20 );
    FCML_I64( "vprotw xmm0,xmm0,20h", 0x8F, 0xE8, 0x78, 0xC1, 0xC0, 0x20 );
    /* GAS*/
    FCML_A64( "vprotw %xmm5,(%rcx,%rax),%xmm2", 0x8f, 0xe9, 0x50, 0x91, 0x14, 0x01 );
    FCML_A64( "vprotw (%rcx,%rax),%xmm5,%xmm2", 0x8f, 0xe9, 0xd0, 0x91, 0x14, 0x01 );
    FCML_A64( "vprotw $0x20,(%rcx,%rax),%xmm2", 0x8f, 0xe8, 0x78, 0xc1, 0x14, 0x01, 0x20 );
    FCML_A64( "vprotw $0x20,%xmm0,%xmm0", 0x8f, 0xe8, 0x78, 0xc1, 0xc0, 0x20 );
}

void fcml_tf_instruction_VPSHAB(void) {
    /* VPSHAB xmm1, xmm2/mem128, xmm3 8F RXB.01001 0.src.0.00 98 /r*/
    FCML_I32( "vpshab xmm2,xmmword ptr [ecx+eax],xmm5", 0x8F, 0xE9, 0x50, 0x98, 0x14, 0x01 );
    FCML_I64_M( "vpshab xmm0,xmm0,xmm5", 2, FCML_MI( 0x8f, 0xe9, 0xf8, 0x98, 0xc5 ), FCML_MI( 0x8f, 0xe9, 0x50, 0x98, 0xc0 ) );
    /* VPSHAB xmm1, xmm2, xmm3/mem128 8F RXB.01001 1.src.0.00 98 /r*/
    FCML_I64( "vpshab xmm2,xmm5,xmmword ptr [rcx+rax]", 0x8F, 0xE9, 0xD0, 0x98, 0x14, 0x01 );
    FCML_I64_M( "vpshab xmm0,xmm5,xmm0", 2, FCML_MI( 0x8f, 0xe9, 0xd0, 0x98, 0xc0 ), FCML_MI( 0x8f, 0xe9, 0x78, 0x98, 0xc5 ) );
    /* GAS*/
    FCML_A64( "vpshab %xmm5,(%rcx,%rax),%xmm2", 0x8f, 0xe9, 0x50, 0x98, 0x14, 0x01 );
    FCML_A64( "vpshab (%rcx,%rax),%xmm5,%xmm2", 0x8f, 0xe9, 0xd0, 0x98, 0x14, 0x01 );
    FCML_A64_M( "vpshab %xmm5,%xmm0,%xmm0", 2, FCML_MI( 0x8f, 0xe9, 0xf8, 0x98, 0xc5 ), FCML_MI( 0x8f, 0xe9, 0x50, 0x98, 0xc0 ) );
    FCML_A64_M( "vpshab %xmm0,%xmm5,%xmm0", 2, FCML_MI( 0x8f, 0xe9, 0xd0, 0x98, 0xc0 ), FCML_MI( 0x8f, 0xe9, 0x78, 0x98, 0xc5 ) );
}

void fcml_tf_instruction_VPSHAD(void) {
    /* VPSHAD xmm1, xmm2/mem128, xmm3 8F RXB.01001 0.src.0.00 9A /r*/
    FCML_I32( "vpshad xmm2,xmmword ptr [ecx+eax],xmm5", 0x8F, 0xE9, 0x50, 0x9A, 0x14, 0x01 );
    FCML_I64_M( "vpshad xmm0,xmm0,xmm5", 2, FCML_MI( 0x8f, 0xe9, 0xf8, 0x9a, 0xc5 ), FCML_MI( 0x8f, 0xe9, 0x50, 0x9A, 0xc0 ) );
    /* VPSHAD xmm1, xmm2, xmm3/mem128 8F RXB.01001 1.src.0.00 9A /r*/
    FCML_I64( "vpshad xmm2,xmm5,xmmword ptr [rcx+rax]", 0x8F, 0xE9, 0xD0, 0x9a, 0x14, 0x01 );
    FCML_I64_M( "vpshad xmm0,xmm5,xmm0", 2, FCML_MI( 0x8f, 0xe9, 0xd0, 0x9a, 0xc0 ), FCML_MI( 0x8f, 0xe9, 0x78, 0x9A, 0xc5 ) );
    /* GAS*/
    FCML_A64( "vpshad %xmm5,(%rcx,%rax),%xmm2", 0x8f, 0xe9, 0x50, 0x9a, 0x14, 0x01 );
    FCML_A64( "vpshad (%rcx,%rax),%xmm5,%xmm2", 0x8f, 0xe9, 0xd0, 0x9a, 0x14, 0x01 );
}

void fcml_tf_instruction_VPSHAQ(void) {
    /* VPSHAQ xmm1, xmm2/mem128, xmm3 8F RXB.01001 0.src.0.00 9B /r*/
    FCML_I32( "vpshaq xmm2,xmmword ptr [ecx+eax],xmm5", 0x8F, 0xE9, 0x50, 0x9B, 0x14, 0x01 );
    FCML_I64_M( "vpshaq xmm0,xmm0,xmm5", 2, FCML_MI( 0x8f, 0xe9, 0xf8, 0x9b, 0xc5 ), FCML_MI( 0x8f, 0xe9, 0x50, 0x9b, 0xc0 ) );
    /* VPSHAQ xmm1, xmm2, xmm3/mem128 8F RXB.01001 1.src.0.00 9B /r*/
    FCML_I64( "vpshaq xmm2,xmm5,xmmword ptr [rcx+rax]", 0x8F, 0xE9, 0xD0, 0x9B, 0x14, 0x01 );
    FCML_I64_M( "vpshaq xmm0,xmm5,xmm0", 2, FCML_MI( 0x8f, 0xe9, 0xd0, 0x9b, 0xc0 ), FCML_MI( 0x8f, 0xe9, 0x78, 0x9b, 0xc5 ) );
    /* GAS*/
    FCML_A64( "vpshaq %xmm5,(%rcx,%rax),%xmm2", 0x8f, 0xe9, 0x50, 0x9b, 0x14, 0x01 );
    FCML_A64( "vpshaq (%rcx,%rax),%xmm5,%xmm2", 0x8f, 0xe9, 0xd0, 0x9b, 0x14, 0x01 );
}

void fcml_tf_instruction_VPSHAW(void) {
    /* VPSHAW xmm1, xmm2/mem128, xmm3 8F RXB.01001 0.src.0.00 99 /r*/
    FCML_I32( "vpshaw xmm2,xmmword ptr [ecx+eax],xmm5", 0x8F, 0xE9, 0x50, 0x99, 0x14, 0x01 );
    FCML_I64_M( "vpshaw xmm0,xmm0,xmm5", 2, FCML_MI( 0x8f, 0xe9, 0xf8, 0x99, 0xc5 ), FCML_MI( 0x8f, 0xe9, 0x50, 0x99, 0xc0 ) );
    /* VPSHAW xmm1, xmm2, xmm3/mem128 8F RXB.01001 1.src.0.00 99 /r*/
    FCML_I64( "vpshaw xmm2,xmmword ptr [rcx+rax],xmm5", 0x8F, 0xE9, 0x50, 0x99, 0x14, 0x01 );
    FCML_I64_M( "vpshaw xmm0,xmm0,xmm5", 2, FCML_MI( 0x8f, 0xe9, 0xf8, 0x99, 0xc5 ), FCML_MI( 0x8f, 0xe9, 0x50, 0x99, 0xc0 ) );
    /* GAS*/
    FCML_A64( "vpshaw %xmm5,(%rcx,%rax),%xmm2", 0x8f, 0xe9, 0x50, 0x99, 0x14, 0x01 );
    FCML_A64( "vpshaw %xmm5,(%rcx,%rax),%xmm2", 0x8f, 0xe9, 0x50, 0x99, 0x14, 0x01 );
}

void fcml_tf_instruction_VPSHLB(void) {
    /* VPSHLB xmm1, xmm2/mem128, xmm3 8F RXB.01001 0.src.0.00 94 /r*/
    FCML_I32( "vpshlb xmm2,xmmword ptr [ecx+eax],xmm5", 0x8F, 0xE9, 0x50, 0x94, 0x14, 0x01 );
    FCML_I64_M( "vpshlb xmm0,xmm0,xmm5", 2, FCML_MI( 0x8f, 0xe9, 0xf8, 0x94, 0xc5 ), FCML_MI( 0x8f, 0xe9, 0x50, 0x94, 0xc0 ) );
    /* VPSHLB xmm1, xmm2, xmm3/mem128 8F RXB.01001 1.src.0.00 94 /r*/
    FCML_I64( "vpshlb xmm2,xmmword ptr [rcx+rax],xmm5", 0x8F, 0xE9, 0x50, 0x94, 0x14, 0x01 );
    FCML_I64_M( "vpshlb xmm0,xmm0,xmm5", 2, FCML_MI( 0x8f, 0xe9, 0xf8, 0x94, 0xc5 ), FCML_MI( 0x8f, 0xe9, 0x50, 0x94, 0xc0 ) );
    /* GAS*/
    FCML_A64( "vpshlb %xmm5,(%rcx,%rax),%xmm2", 0x8f, 0xe9, 0x50, 0x94, 0x14, 0x01 );
    FCML_A64( "vpshlb %xmm5,(%rcx,%rax),%xmm2", 0x8f, 0xe9, 0x50, 0x94, 0x14, 0x01 );
}

void fcml_tf_instruction_VPSHLD(void) {
    /* VPSHLD xmm1, xmm3/mem128, xmm2 8F RXB.01001 0.src.0.00 96 /r*/
    FCML_I32( "vpshld xmm2,xmmword ptr [ecx+eax],xmm5", 0x8F, 0xE9, 0x50, 0x96, 0x14, 0x01 );
    FCML_I64_M( "vpshld xmm0,xmm0,xmm5", 2, FCML_MI( 0x8f, 0xe9, 0xf8, 0x96, 0xc5 ), FCML_MI( 0x8f, 0xe9, 0x50, 0x96, 0xc0 ) );
    /* VPSHLD xmm1, xmm2, xmm3/mem128 8F RXB.01001 1.src.0.00 96 /r*/
    FCML_I64( "vpshld xmm2,xmm5,xmmword ptr [rcx+rax]", 0x8F, 0xE9, 0xD0, 0x96, 0x14, 0x01 );
    FCML_I64_M( "vpshld xmm0,xmm5,xmm0", 2, FCML_MI( 0x8f, 0xe9, 0xd0, 0x96, 0xc0 ), FCML_MI( 0x8f, 0xe9, 0x78, 0x96, 0xc5 ) );
    /* GAS*/
    FCML_A64( "vpshld %xmm5,(%rcx,%rax),%xmm2", 0x8f, 0xe9, 0x50, 0x96, 0x14, 0x01 );
    FCML_A64( "vpshld (%rcx,%rax),%xmm5,%xmm2", 0x8f, 0xe9, 0xd0, 0x96, 0x14, 0x01 );
}

void fcml_tf_instruction_VPSHLQ(void) {
    /* VPSHLQ xmm1, xmm3/mem128, xmm2 8F RXB.01001 0.src.0.00 97 /r*/
    FCML_I32( "vpshlq xmm2,xmmword ptr [ecx+eax],xmm5", 0x8F, 0xE9, 0x50, 0x97, 0x14, 0x01 );
    FCML_I64_M( "vpshlq xmm0,xmm0,xmm5", 2, FCML_MI( 0x8f, 0xe9, 0xf8, 0x97, 0xc5 ), FCML_MI( 0x8f, 0xe9, 0x50, 0x97, 0xc0 ) );
    /* VPSHLQ xmm1, xmm2, xmm3/mem128 8F RXB.01001 1.src.0.00 97 /r*/
    FCML_I64( "vpshlq xmm2,xmm5,xmmword ptr [rcx+rax]", 0x8F, 0xE9, 0xD0, 0x97, 0x14, 0x01 );
    FCML_I64_M( "vpshlq xmm0,xmm5,xmm0", 2, FCML_MI( 0x8f, 0xe9, 0xd0, 0x97, 0xc0 ), FCML_MI( 0x8f, 0xe9, 0x78, 0x97, 0xc5 ) );
    /* GAS*/
    FCML_A64( "vpshlq %xmm5,(%rcx,%rax),%xmm2", 0x8f, 0xe9, 0x50, 0x97, 0x14, 0x01 );
    FCML_A64( "vpshlq (%rcx,%rax),%xmm5,%xmm2", 0x8f, 0xe9, 0xd0, 0x97, 0x14, 0x01 );
}

void fcml_tf_instruction_VPSHLW(void) {
    /* VPSHLW xmm1, xmm3/mem128, xmm2 8F RXB.01001 0.src.0.00 95 /r*/
    FCML_I32( "vpshlw xmm2,xmmword ptr [ecx+eax],xmm5", 0x8F, 0xE9, 0x50, 0x95, 0x14, 0x01 );
    FCML_I64_M( "vpshlw xmm0,xmm0,xmm5", 2, FCML_MI( 0x8f, 0xe9, 0xf8, 0x95, 0xc5 ), FCML_MI( 0x8f, 0xe9, 0x50, 0x95, 0xc0 ) );
    /* VPSHLW xmm1, xmm2, xmm3/mem128 8F RXB.01001 1.src.0.00 95 /r*/
    FCML_I64( "vpshlw xmm2,xmm5,xmmword ptr [rcx+rax]", 0x8F, 0xE9, 0xD0, 0x95, 0x14, 0x01 );
    FCML_I64_M( "vpshlw xmm0,xmm5,xmm0", 2, FCML_MI( 0x8f, 0xe9, 0xd0, 0x95, 0xc0 ), FCML_MI( 0x8f, 0xe9, 0x78, 0x95, 0xc5 ) );
    /* GAS*/
    FCML_A64( "vpshlw %xmm5,(%rcx,%rax),%xmm2", 0x8f, 0xe9, 0x50, 0x95, 0x14, 0x01 );
    FCML_A64( "vpshlw (%rcx,%rax),%xmm5,%xmm2", 0x8f, 0xe9, 0xd0, 0x95, 0x14, 0x01 );
}

void fcml_tf_instruction_VMPTRLD(void) {
    /* 0F C7 /6 VMPTRLD m64 Loads the current VMCS pointer from memory.*/
    FCML_I64( "vmptrld qword ptr [rdx]", 0x0F, 0xC7, 0x32 );
    FCML_I64( "vmptrld qword ptr [edx]", 0x67, 0x0F, 0xC7, 0x32 );
    FCML_I64_A_FAILED( "vmptrld edx", 0x67, 0x0F, 0xC7, 0xF2 );
    FCML_I64_D_FAILED( "vmptrld edx", 0x67, 0x0F, 0xC7, 0xF2 );
    FCML_I32_FAILED( "vmptrld qword ptr [edx]", 0x0F, 0xC7, 0x32 );
    /* GAS*/
    FCML_A64( "vmptrld (%rdx)", 0x0f, 0xc7, 0x32 );
    FCML_A64( "vmptrld (%edx)", 0x67, 0x0f, 0xc7, 0x32 );
}

void fcml_tf_instruction_VMPTRST(void) {
    /* 0F C7 /7 VMPTRST m64 Stores the current VMCS pointer into memory.*/
    FCML_I64( "vmptrst qword ptr [rdx]", 0x0F, 0xC7, 0x3A );
    FCML_I64( "vmptrst qword ptr [edx]", 0x67, 0x0F, 0xC7, 0x3A );
    FCML_I64_A_FAILED( "vmptrst edx", 0x67, 0x0F, 0xC7, 0xFA );
    FCML_I32_FAILED( "vmptrst qword ptr [edx]", 0x0F, 0xC7, 0x3A );
    /* GAS*/
    FCML_A64( "vmptrst (%rdx)", 0x0f, 0xc7, 0x3a );
    FCML_A64( "vmptrst (%edx)", 0x67, 0x0f, 0xc7, 0x3a );
}

void fcml_tf_instruction_VMCLEAR(void) {
    /* 0F C7 /7 VMPTRST m64 Stores the current VMCS pointer into memory.*/
    FCML_I64( "vmclear qword ptr [rdx]", 0x66, 0x0F, 0xC7, 0x3A );
    FCML_I64( "vmclear qword ptr [edx]", 0x67, 0x66, 0x0F, 0xC7, 0x3A );
    FCML_I64_A_FAILED( "vmclear edx", 0x67, 0x66, 0x0F, 0xC7, 0xFA );
    FCML_I32_FAILED( "vmclear qword ptr [edx]", 0x66, 0x0F, 0xC7, 0x3A );
    /* GAS*/
    FCML_A64( "vmptrst (%rdx)", 0x0f, 0xc7, 0x3a );
    FCML_A64( "vmptrst (%edx)", 0x67, 0x0f, 0xc7, 0x3a );
}

void fcml_tf_instruction_VMREAD(void) {
    /* 0F 78 VMREAD r/m64, r64 Reads a specified VMCS field (in 64-bit mode).*/
    /* 0F 78 VMREAD r/m32, r32 Reads a specified VMCS field (outside 64-bit mode).*/
    FCML_I64( "vmread qword ptr [rdx],rdi", 0x0F, 0x78, 0x3A );
    FCML_I64( "vmread rdx,rdi", 0x0F, 0x78, 0xFA );
    FCML_I32( "vmread dword ptr [edx],edi", 0x0F, 0x78, 0x3A );
    FCML_I32( "vmread edx,edi", 0x0F, 0x78, 0xFA );
    /* GAS*/
    FCML_A64( "vmread %rdi,(%rdx)", 0x0f, 0x78, 0x3a );
}

void fcml_tf_instruction_VMWRITE(void) {
    /* 0F 79 VMWRITE r64, r/m64 Writes a specified VMCS field (in 64-bit mode)*/
    /* 0F 79 VMWRITE r32, r/m32 Writes a specified VMCS field (outside 64-bit mode)*/
    FCML_I64( "vmwrite rdi,qword ptr [rdx]", 0x0F, 0x79, 0x3A );
    FCML_I64( "vmwrite rdi,rdx", 0x0F, 0x79, 0xFA );
    FCML_I32( "vmwrite edi,dword ptr [edx]", 0x0F, 0x79, 0x3A );
    FCML_I32( "vmwrite edi,edx", 0x0F, 0x79, 0xFA );
    /* GAS*/
    FCML_A64( "vmwrite (%rdx),%rdi", 0x0f, 0x79, 0x3a );
    FCML_A64( "vmwrite %rdx,%rdi", 0x0f, 0x79, 0xfa );
    FCML_A64( "vmwrite (%rdx),%rdi", 0x0f, 0x79, 0x3a );
    FCML_A64( "vmwrite %rdx,%rdi", 0x0f, 0x79, 0xfa );
}

void fcml_tf_instruction_VMLAUNCH(void) {
    /* 0F 01 C2 VMLAUNCH Launch virtual machine managed by current VMCS.*/
    FCML_I64( "vmlaunch", 0x0F, 0x01, 0xC2 );
    FCML_I32_FAILED( "vmlaunch", 0x0F, 0x01, 0xC2 );
    /* GAS*/
    FCML_A64( "vmlaunch", 0x0f, 0x01, 0xc2 );
}

void fcml_tf_instruction_VMRESUME(void) {
    /* 0F 01 C3 VMRESUME Resume virtual machine managed by current VMCS.*/
    FCML_I64( "vmresume", 0x0F, 0x01, 0xC3 );
    FCML_I32_FAILED( "vmresume", 0x0F, 0x01, 0xC3 );
    /* GAS*/
    FCML_A64( "vmresume", 0x0f, 0x01, 0xc3 );
}

void fcml_tf_instruction_VMXON(void) {
    /* 0F C7 /7 VMPTRST m64 Stores the current VMCS pointer into memory.*/
    FCML_I64( "vmxon qword ptr [rdx]", 0xF3, 0x0F, 0xC7, 0x32 );
    FCML_I64( "vmxon qword ptr [edx]", 0x67, 0xF3, 0x0F, 0xC7, 0x32 );
    FCML_I64_A_FAILED( "vmxon edx", 0x67, 0xF3, 0x0F, 0xC7, 0xF2 );
    FCML_I32_FAILED( "vmxon qword ptr [edx]", 0xF3, 0x0F, 0xC7, 0x32 );
    /* GAS*/
    FCML_A64( "vmxon (%rdx)", 0xf3, 0x0f, 0xc7, 0x32 );
    FCML_A64( "vmxon (%edx)", 0x67, 0xf3, 0x0f, 0xc7, 0x32 );
}

void fcml_tf_instruction_VMXOFF(void) {
    /* 0F 01 C4 VMXOFF Leaves VMX operation.*/
    FCML_I64( "vmxoff", 0x0F, 0x01, 0xC4 );
    FCML_I32_FAILED( "vmxoff", 0x0F, 0x01, 0xC4 );
    /* GAS*/
    FCML_A64( "vmxoff", 0x0f, 0x01, 0xc4 );
}

void fcml_tf_instruction_VMCALL(void) {
    /* 0F 01 C1 VMCALL Call to VM monitor by causing VM exit.*/
    FCML_I64( "vmcall", 0x0F, 0x01, 0xC1 );
    FCML_I32_FAILED( "vmcall", 0x0F, 0x01, 0xC1 );
    /* GAS*/
    FCML_A64( "vmcall", 0x0f, 0x01, 0xc1 );
}

void fcml_tf_instruction_VMFUNC(void) {
    /* 0F 01 D4 VMFUNC Invoke VM function specified in EAX.*/
    FCML_I64( "vmfunc", 0x0F, 0x01, 0xD4 );
    FCML_I32_FAILED( "vmfunc", 0x0F, 0x01, 0xD4 );
    /* GAS*/
    FCML_A64( "vmfunc", 0x0f, 0x01, 0xd4 );
}

void fcml_tf_instruction_VPERMIL2PS(void) {
	/* VPERMIL2PS.*/
	FCML_I32( "vpermil2ps xmm0,xmm4,xmmword ptr [ecx],xmm7,01h", 0xC4, 0xE3, 0x59, 0x48, 0x01, 0x71 );
	FCML_I64( "vpermil2ps xmm0,xmm4,xmm7,xmmword ptr [rcx],01h", 0xC4, 0xE3, 0xD9, 0x48, 0x01, 0x71 );
	FCML_I32( "vpermil2ps ymm0,ymm4,ymmword ptr [ecx],ymm7,01h", 0xC4, 0xE3, 0x5D, 0x48, 0x01, 0x71 );
	FCML_I64( "vpermil2ps ymm0,ymm4,ymm7,ymmword ptr [rcx],01h", 0xC4, 0xE3, 0xDD, 0x48, 0x01, 0x71 );
	FCML_I64( "vpermil2ps ymm0,ymm4,ymm15,ymmword ptr [rcx],01h", 0xC4, 0xE3, 0xDD, 0x48, 0x01, 0xF1 );
	FCML_I64_M( "vpermil2ps ymm0,ymm4,ymm15,ymm1,01h", 2, FCML_MI( 0xc4, 0xe3, 0xdd, 0x48, 0xc1, 0xf1 ), FCML_MI( 0xc4, 0xc3, 0x5d, 0x48, 0xc7, 0x11 ) );
}

void fcml_tf_instruction_VPERMIL2PD(void) {
	/* VPERMIL2PD.*/
	FCML_I32( "vpermil2pd xmm0,xmm4,xmmword ptr [ecx],xmm7,01h", 0xC4, 0xE3, 0x59, 0x49, 0x01, 0x71 );
	FCML_I64( "vpermil2pd xmm0,xmm4,xmm7,xmmword ptr [rcx],01h", 0xC4, 0xE3, 0xD9, 0x49, 0x01, 0x71 );
	FCML_I32( "vpermil2pd ymm0,ymm4,ymmword ptr [ecx],ymm7,01h", 0xC4, 0xE3, 0x5D, 0x49, 0x01, 0x71 );
	FCML_I64( "vpermil2pd ymm0,ymm4,ymm7,ymmword ptr [rcx],01h", 0xC4, 0xE3, 0xDD, 0x49, 0x01, 0x71 );
	FCML_I64( "vpermil2pd ymm0,ymm4,ymm15,ymmword ptr [rcx],01h", 0xC4, 0xE3, 0xDD, 0x49, 0x01, 0xF1 );
	FCML_I64_M( "vpermil2pd ymm0,ymm4,ymm15,ymm1,01h", 2, FCML_MI( 0xc4, 0xe3, 0xdd, 0x49, 0xc1, 0xf1 ), FCML_MI( 0xc4, 0xc3, 0x5d, 0x49, 0xc7, 0x11 ) );
}

fcml_stf_test_case fctl_ti_instructions_v[] = {
	{ "fcml_tf_instruction_VBROADCASTSS", fcml_tf_instruction_VBROADCASTSS },
	{ "fcml_tf_instruction_VPBROADCASTB", fcml_tf_instruction_VPBROADCASTB },
	{ "fcml_tf_instruction_VEXTRACTF128", fcml_tf_instruction_VEXTRACTF128 },
	{ "fcml_tf_instruction_VINSERTF128", fcml_tf_instruction_VINSERTF128 },
	{ "fcml_tf_instruction_VMASKMOVPS_VMASKMOVPD", fcml_tf_instruction_VMASKMOVPS_VMASKMOVPD },
	{ "fcml_tf_instruction_VPMASKMOVD_VPMASKMOVQ", fcml_tf_instruction_VPMASKMOVD_VPMASKMOVQ },
	{ "fcml_tf_instruction_VPBLENDD", fcml_tf_instruction_VPBLENDD },
	{ "fcml_tf_instruction_VCVTPH2PS", fcml_tf_instruction_VCVTPH2PS },
	{ "fcml_tf_instruction_VCVTPS2PH", fcml_tf_instruction_VCVTPS2PH },
	{ "fcml_tf_instruction_VERR", fcml_tf_instruction_VERR },
	{ "fcml_tf_instruction_VMLOAD", fcml_tf_instruction_VMLOAD },
	{ "fcml_tf_instruction_VMMCALL", fcml_tf_instruction_VMMCALL },
	{ "fcml_tf_instruction_VMRUN", fcml_tf_instruction_VMRUN },
	{ "fcml_tf_instruction_VMSAVE", fcml_tf_instruction_VMSAVE },
	{ "fcml_tf_instruction_VPERMILPD", fcml_tf_instruction_VPERMILPD },
	{ "fcml_tf_instruction_VPERMILPS", fcml_tf_instruction_VPERMILPS },
	{ "fcml_tf_instruction_VPSLLVD", fcml_tf_instruction_VPSLLVD },
	{ "fcml_tf_instruction_VPSRLVD", fcml_tf_instruction_VPSRLVD },
	{ "fcml_tf_instruction_VPSRAVD", fcml_tf_instruction_VPSRAVD },
	{ "fcml_tf_instruction_VPERMD", fcml_tf_instruction_VPERMD },
	{ "fcml_tf_instruction_VPERMPD", fcml_tf_instruction_VPERMPD },
	{ "fcml_tf_instruction_VPERMQ", fcml_tf_instruction_VPERMQ },
	{ "fcml_tf_instruction_VPERMPS", fcml_tf_instruction_VPERMPS },
	{ "fcml_tf_instruction_VPERM2F128", fcml_tf_instruction_VPERM2F128 },
	{ "fcml_tf_instruction_VPERM2I128", fcml_tf_instruction_VPERM2I128 },
	{ "fcml_tf_instruction_VEXTRACTI128", fcml_tf_instruction_VEXTRACTI128 },
	{ "fcml_tf_instruction_VINSERTI128", fcml_tf_instruction_VINSERTI128 },
	{ "fcml_tf_instruction_VTESTPS", fcml_tf_instruction_VTESTPS },
	{ "fcml_tf_instruction_VGATHERDPD", fcml_tf_instruction_VGATHERDPD },
	{ "fcml_tf_instruction_VGATHERDPS", fcml_tf_instruction_VGATHERDPS },
	{ "fcml_tf_instruction_VPGATHERDD", fcml_tf_instruction_VPGATHERDD },
	{ "fcml_tf_instruction_VPGATHERDQ", fcml_tf_instruction_VPGATHERDQ },
	{ "fcml_tf_instruction_VZEROALL", fcml_tf_instruction_VZEROALL },
	{ "fcml_tf_instruction_VZEROUPPER", fcml_tf_instruction_VZEROUPPER },
	{ "fcml_tf_instruction_VFMADDPD", fcml_tf_instruction_VFMADDPD },
	{ "fcml_tf_instruction_VFMADDPS", fcml_tf_instruction_VFMADDPS },
	{ "fcml_tf_instruction_VFMADDSD", fcml_tf_instruction_VFMADDSD },
	{ "fcml_tf_instruction_VFMADDSS", fcml_tf_instruction_VFMADDSS },
	{ "fcml_tf_instruction_VFMADDSUBPD", fcml_tf_instruction_VFMADDSUBPD },
	{ "fcml_tf_instruction_VFMADDSUBPS", fcml_tf_instruction_VFMADDSUBPS },
	{ "fcml_tf_instruction_VFMSUBADDPD", fcml_tf_instruction_VFMSUBADDPD },
	{ "fcml_tf_instruction_VFMSUBADDPS", fcml_tf_instruction_VFMSUBADDPS },
	{ "fcml_tf_instruction_VFMSUBPD", fcml_tf_instruction_VFMSUBPD },
	{ "fcml_tf_instruction_VFMSUBPS", fcml_tf_instruction_VFMSUBPS },
	{ "fcml_tf_instruction_VFMSUBSD", fcml_tf_instruction_VFMSUBSD },
	{ "fcml_tf_instruction_VFMSUBSS", fcml_tf_instruction_VFMSUBSS },
	{ "fcml_tf_instruction_VFNMADDPD", fcml_tf_instruction_VFNMADDPD },
	{ "fcml_tf_instruction_VFNMADDPS", fcml_tf_instruction_VFNMADDPS },
	{ "fcml_tf_instruction_VFNMADDSD", fcml_tf_instruction_VFNMADDSD },
	{ "fcml_tf_instruction_VFNMADDSS", fcml_tf_instruction_VFNMADDSS },
	{ "fcml_tf_instruction_VFNMSUBPD", fcml_tf_instruction_VFNMSUBPD },
	{ "fcml_tf_instruction_VFNMSUBPS", fcml_tf_instruction_VFNMSUBPS },
	{ "fcml_tf_instruction_VFNMSUBSD", fcml_tf_instruction_VFNMSUBSD },
	{ "fcml_tf_instruction_VFNMSUBSS", fcml_tf_instruction_VFNMSUBSS },
	{ "fcml_tf_instruction_VFRCZPD", fcml_tf_instruction_VFRCZPD },
	{ "fcml_tf_instruction_VFRCZPS", fcml_tf_instruction_VFRCZPS },
	{ "fcml_tf_instruction_VFRCZSD", fcml_tf_instruction_VFRCZSD },
	{ "fcml_tf_instruction_VFRCZSS", fcml_tf_instruction_VFRCZSS },
	{ "fcml_tf_instruction_VPCMOV", fcml_tf_instruction_VPCMOV },
	{ "fcml_tf_instruction_VPCOMU", fcml_tf_instruction_VPCOMU },
	{ "fcml_tf_instruction_VPCOM", fcml_tf_instruction_VPCOM },
	{ "fcml_tf_instruction_VPHADDBD", fcml_tf_instruction_VPHADDBD },
	{ "fcml_tf_instruction_VPHADDBW", fcml_tf_instruction_VPHADDBW },
	{ "fcml_tf_instruction_VPHADDBQ", fcml_tf_instruction_VPHADDBQ },
	{ "fcml_tf_instruction_VPHADDDQ", fcml_tf_instruction_VPHADDDQ },
	{ "fcml_tf_instruction_VPHADDUBD", fcml_tf_instruction_VPHADDUBD },
	{ "fcml_tf_instruction_VPHADDUBQ", fcml_tf_instruction_VPHADDUBQ },
	{ "fcml_tf_instruction_VPHADDUBW", fcml_tf_instruction_VPHADDUBW },
	{ "fcml_tf_instruction_VPHADDUDQ", fcml_tf_instruction_VPHADDUDQ },
	{ "fcml_tf_instruction_VPHADDUWD", fcml_tf_instruction_VPHADDUWD },
	{ "fcml_tf_instruction_VPHADDUWQ", fcml_tf_instruction_VPHADDUWQ },
	{ "fcml_tf_instruction_VPHADDWD", fcml_tf_instruction_VPHADDWD },
	{ "fcml_tf_instruction_VPHADDWQ", fcml_tf_instruction_VPHADDWQ },
	{ "fcml_tf_instruction_VPHSUBBW", fcml_tf_instruction_VPHSUBBW },
	{ "fcml_tf_instruction_VPHSUBDQ", fcml_tf_instruction_VPHSUBDQ },
	{ "fcml_tf_instruction_VPHSUBWD", fcml_tf_instruction_VPHSUBWD },
	{ "fcml_tf_instruction_VPMACSDD", fcml_tf_instruction_VPMACSDD },
	{ "fcml_tf_instruction_VPMACSDQH", fcml_tf_instruction_VPMACSDQH },
	{ "fcml_tf_instruction_VPMACSDQL", fcml_tf_instruction_VPMACSDQL },
	{ "fcml_tf_instruction_VPMACSSDD", fcml_tf_instruction_VPMACSSDD },
	{ "fcml_tf_instruction_VPMACSSDQH", fcml_tf_instruction_VPMACSSDQH },
	{ "fcml_tf_instruction_VPMACSSDQL", fcml_tf_instruction_VPMACSSDQL },
	{ "fcml_tf_instruction_VPMACSSWD", fcml_tf_instruction_VPMACSSWD },
	{ "fcml_tf_instruction_VPMACSSWW", fcml_tf_instruction_VPMACSSWW },
	{ "fcml_tf_instruction_VPMACSWD", fcml_tf_instruction_VPMACSWD },
	{ "fcml_tf_instruction_VPMACSWW", fcml_tf_instruction_VPMACSWW },
	{ "fcml_tf_instruction_VPMADCSSWD", fcml_tf_instruction_VPMADCSSWD },
	{ "fcml_tf_instruction_VPMADCSWD", fcml_tf_instruction_VPMADCSWD },
	{ "fcml_tf_instruction_VPPERM", fcml_tf_instruction_VPPERM },
	{ "fcml_tf_instruction_VPROTD", fcml_tf_instruction_VPROTD },
	{ "fcml_tf_instruction_VPROTB", fcml_tf_instruction_VPROTB },
	{ "fcml_tf_instruction_VPROTQ", fcml_tf_instruction_VPROTQ },
	{ "fcml_tf_instruction_VPROTW", fcml_tf_instruction_VPROTW },
	{ "fcml_tf_instruction_VPSHAB", fcml_tf_instruction_VPSHAB },
	{ "fcml_tf_instruction_VPSHAD", fcml_tf_instruction_VPSHAD },
	{ "fcml_tf_instruction_VPSHAQ", fcml_tf_instruction_VPSHAQ },
	{ "fcml_tf_instruction_VPSHAW", fcml_tf_instruction_VPSHAW },
	{ "fcml_tf_instruction_VPSHLB", fcml_tf_instruction_VPSHLB },
	{ "fcml_tf_instruction_VPSHLD", fcml_tf_instruction_VPSHLD },
	{ "fcml_tf_instruction_VPSHLQ", fcml_tf_instruction_VPSHLQ },
	{ "fcml_tf_instruction_VPSHLW", fcml_tf_instruction_VPSHLW },
	{ "fcml_tf_instruction_VMPTRLD", fcml_tf_instruction_VMPTRLD },
	{ "fcml_tf_instruction_VMPTRST", fcml_tf_instruction_VMPTRST },
	{ "fcml_tf_instruction_VMCLEAR", fcml_tf_instruction_VMCLEAR },
	{ "fcml_tf_instruction_VMREAD", fcml_tf_instruction_VMREAD },
	{ "fcml_tf_instruction_VMWRITE", fcml_tf_instruction_VMWRITE },
	{ "fcml_tf_instruction_VMLAUNCH", fcml_tf_instruction_VMLAUNCH },
	{ "fcml_tf_instruction_VMRESUME", fcml_tf_instruction_VMRESUME },
	{ "fcml_tf_instruction_VMXON", fcml_tf_instruction_VMXON },
	{ "fcml_tf_instruction_VMXOFF", fcml_tf_instruction_VMXOFF },
	{ "fcml_tf_instruction_VMCALL", fcml_tf_instruction_VMCALL },
	{ "fcml_tf_instruction_VMFUNC", fcml_tf_instruction_VMFUNC },
	{ "fcml_tf_instruction_VPERMIL2PS", fcml_tf_instruction_VPERMIL2PS },
	{ "fcml_tf_instruction_VPERMIL2PD", fcml_tf_instruction_VPERMIL2PD },
	FCML_STF_NULL_TEST
};

fcml_stf_test_suite fctl_si_instructions_v = {
	"suite-fctl_ti_instructions_v", fcml_tf_instructions_v_suite_init, fcml_tf_instructions_v_suite_cleanup, fctl_ti_instructions_v
};


