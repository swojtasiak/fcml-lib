/*
 * instructions.c
 *
 *  Created on: 01-06-2013
 *      Author: tAs
 */

#include "fcml_env.h"
#include "fcml_assembler.h"
#include "instructions_b_t.h"

int fcml_tf_instructions_b_suite_init(void) {
	return 0;
}

int fcml_tf_instructions_b_suite_cleanup(void) {
	return 0;
}

void fcml_tf_instruction_BLENDPD(void) {
	FCML_I32( "blendpd xmm2,oword ptr [ecx+eax],0ffh", 0x66, 0x0F, 0x3a, 0x0D, 0x14, 0x01, 0xFF );
	FCML_I64( "blendpd xmm2,oword ptr [rcx+rax],0ffh", 0x66, 0x0F, 0x3a, 0x0D, 0x14, 0x01, 0xFF );
	// VEX.NDS.128.66.0F3A 0D /r ib VBLENDPD xmm1,xmm2,xmm3/m128,imm8
	// VEX.NDS.256.66.0F3A 0D /r ib VBLENDPD ymm1,ymm2,ymm3/m256,imm8
	FCML_I64( "vblendpd ymm10,ymm14,ymmword ptr [r9+rax],20h", 0xC4, 0x43, 0x0D, 0x0D, 0x14, 0x01, 0x20 );
	FCML_I32_D( "vblendpd xmm2,xmm7,oword ptr [ecx+eax],20h", 0xC4, 0xC3, 0x41, 0x0D, 0x14, 0x01, 0x20 ); // REX.B ignored in 32bit mode.
	FCML_I32_D( "vblendpd xmm2,xmm2,oword ptr [ecx+eax],20h", 0xC4, 0xC3, 0x69, 0x0D, 0x14, 0x01, 0x20 ); // REX.B ignored in 32bit mode.
	FCML_I32( "vblendpd xmm2,xmm7,oword ptr [ecx+eax],20h", 0xC4, 0xE3, 0x41, 0x0D, 0x14, 0x01, 0x20 );
	FCML_I32( "vblendpd xmm2,xmm2,oword ptr [ecx+eax],20h", 0xC4, 0xE3, 0x69, 0x0D, 0x14, 0x01, 0x20 );
}

void fcml_tf_instruction_BLENDPS(void) {
	FCML_I32( "blendps xmm2,oword ptr [ecx+eax],0ffh", 0x66, 0x0F, 0x3a, 0x0C, 0x14, 0x01, 0xFF );
	FCML_I64( "blendps xmm2,oword ptr [rcx+rax],0ffh", 0x66, 0x0F, 0x3a, 0x0C, 0x14, 0x01, 0xFF );
	// VEX.NDS.128.66.0F3A 0C /r ib VBLENDPS xmm1,xmm2,xmm3/m128,imm8
	// VEX.NDS.256.66.0F3A 0C /r ib VBLENDPS ymm1,ymm2,ymm3/m256,imm8
	FCML_I64( "vblendps ymm10,ymm14,ymmword ptr [r9+rax],20h", 0xC4, 0x43, 0x0D, 0x0C, 0x14, 0x01, 0x20 );
	FCML_I32( "vblendps xmm2,xmm7,oword ptr [ecx+eax],20h", 0xC4, 0xE3, 0x41, 0x0C, 0x14, 0x01, 0x20 );
	FCML_I32( "vblendps xmm2,xmm2,oword ptr [ecx+eax],20h", 0xC4, 0xE3, 0x69, 0x0C, 0x14, 0x01, 0x20 );
}

void fcml_tf_instruction_BLENDVPD(void) {
	FCML_I32( "blendvpd xmm2,oword ptr [ecx+eax],xmm0", 0x66, 0x0F, 0x38, 0x15, 0x14, 0x01 );
	FCML_I64( "blendvpd xmm2,oword ptr [rcx+rax],xmm0", 0x66, 0x0F, 0x38, 0x15, 0x14, 0x01 );
	// VEX.NDS.128.66.0F3A 4B /r /is4 VBLENDVPD xmm1, xmm2, xmm3/m128, xmm4
	// VEX.NDS.256.66.0F3A 4B /r /is4 VBLENDVPD ymm1, ymm2, ymm3/m256, ymm4
	FCML_I64( "vblendvpd ymm10,ymm14,ymmword ptr [r9+rax],ymm2", 0xC4, 0x43, 0x0D, 0x4B, 0x14, 0x01, 0x20 );
	FCML_I32( "vblendvpd xmm2,xmm7,oword ptr [ecx+eax],xmm2", 0xC4, 0xE3, 0x41, 0x4B, 0x14, 0x01, 0x20 );
	FCML_I32_D( "vblendvpd xmm2,xmm2,oword ptr [ecx+eax],xmm2", 0xC4, 0xE3, 0x69, 0x4B, 0x14, 0x01, 0xA0 );
	FCML_I32( "vblendvpd xmm2,xmm2,oword ptr [ecx+eax],xmm2", 0xC4, 0xE3, 0x69, 0x4B, 0x14, 0x01, 0x20 );
}

void fcml_tf_instruction_BLENDVPS(void) {
	FCML_I32( "blendvps xmm2,oword ptr [ecx+eax],xmm0", 0x66, 0x0F, 0x38, 0x14, 0x14, 0x01 );
	FCML_I64( "blendvps xmm2,oword ptr [rcx+rax],xmm0", 0x66, 0x0F, 0x38, 0x14, 0x14, 0x01 );
	// VEX.NDS.128.66.0F3A 4A /r /is4 VBLENDVPS xmm1, xmm2, xmm3/m128, xmm4
	// VEX.NDS.256.66.0F3A 4A /r /is4 VBLENDVPS ymm1, ymm2, ymm3/m256, ymm4
	FCML_I64( "vblendvps ymm10,ymm14,ymmword ptr [r9+rax],ymm2", 0xC4, 0x43, 0x0D, 0x4A, 0x14, 0x01, 0x20 );
	FCML_I32( "vblendvps xmm2,xmm7,oword ptr [ecx+eax],xmm2", 0xC4, 0xE3, 0x41, 0x4A, 0x14, 0x01, 0x20 );
	FCML_I32_D( "vblendvps xmm2,xmm2,oword ptr [ecx+eax],xmm2", 0xC4, 0xC3, 0x69, 0x4A, 0x14, 0x01, 0xA0 );
	FCML_I32( "vblendvps xmm2,xmm2,oword ptr [ecx+eax],xmm2", 0xC4, 0xE3, 0x69, 0x4A, 0x14, 0x01, 0x20 );
}

void fcml_tf_instruction_BOUND(void) {
	FCML_I32( "bound esi,qword ptr [eax]", 0x62, 0x30 );
	FCML_I32( "bound si,dword ptr [eax]", 0x66, 0x62, 0x30 );
	FCML_I32( "bound si,dword ptr [bx+si]", 0x66, 0x67, 0x62, 0x30 );
	// Not supported in 64.
	FCML_I64_FAILED( "bound si,dword ptr [eax]", 0x62, 0x30 );
	// Addressing not supported, only memory addressing is allowed here.
	FCML_I64_FAILED( "bound si,dword ptr eax", 0x62, 0xc0 );
}

void fcml_tf_instruction_BSF(void) {
	FCML_I32( "bsf esp,dword ptr [ebp+04030201h]", 0x0f, 0xbc, 0xa5, 0x01, 0x02, 0x03, 04 );
	FCML_I32( "bsf sp,word ptr [di+0201h]", 0x66, 0x67, 0x0f, 0xbc, 0xa5, 0x01, 0x02 );
	FCML_I32( "bsf esp,dword ptr [di+0201h]", 0x67, 0x0f, 0xbc, 0xa5, 0x01, 0x02 );
	FCML_I64( "bsf r12,qword ptr [r9+rcx*4+0000000000000001h]", 0x4D, 0x0f, 0xbc, 0x64, 0x89, 0x01 );
}

void fcml_tf_instruction_BSR(void) {
	// We can only assemble BSR instructions, because they are always disassembled to BSF.
	FCML_I32_A( "bsr esp,dword ptr [ebp+04030201h]", 0x0f, 0xbc, 0xa5, 0x01, 0x02, 0x03, 04 );
	FCML_I32_A( "bsr sp,word ptr [di+0201h]", 0x66, 0x67, 0x0f, 0xbc, 0xa5, 0x01, 0x02 );
	FCML_I32_A( "bsr esp,dword ptr [di+0201h]", 0x67, 0x0f, 0xbc, 0xa5, 0x01, 0x02 );
	FCML_I64_A( "bsr r12,qword ptr [r9+rcx*4+0000000000000001h]", 0x4D, 0x0f, 0xbc, 0x64, 0x89, 0x01 );
}

void fcml_tf_instruction_BSWAP(void) {

	FCML_I3264( "bswap eax", 0x0f, 0xc8 );
	FCML_I3264( "bswap ecx", 0x0f, 0xc9 );
	FCML_I3264( "bswap edx", 0x0f, 0xca );
	FCML_I3264( "bswap ebx", 0x0f, 0xcb );
	FCML_I3264( "bswap esp", 0x0f, 0xcc );
	FCML_I3264( "bswap ebp", 0x0f, 0xcd );
	FCML_I3264( "bswap esi", 0x0f, 0xce );
	FCML_I3264( "bswap edi", 0x0f, 0xcf );

	FCML_I3264_D( "bswap eax", 0x66, 0x0f, 0xc8 );
	FCML_I3264_D( "bswap ecx", 0x66, 0x0f, 0xc9 );
	FCML_I3264_D( "bswap edx", 0x66, 0x0f, 0xca );
	FCML_I3264_D( "bswap ebx", 0x66, 0x0f, 0xcb );
	FCML_I3264_D( "bswap esp", 0x66, 0x0f, 0xcc );
	FCML_I3264_D( "bswap ebp", 0x66, 0x0f, 0xcd );
	FCML_I3264_D( "bswap esi", 0x66, 0x0f, 0xce );
	FCML_I3264_D( "bswap edi", 0x66, 0x0f, 0xcf );

	// only REX.R
	FCML_I64( "bswap r8", 0x49, 0x0f, 0xc8 );
	FCML_I64( "bswap r9", 0x49, 0x0f, 0xc9 );
	FCML_I64( "bswap r10", 0x49, 0x0f, 0xca );
	FCML_I64( "bswap r11", 0x49, 0x0f, 0xcb );
	FCML_I64( "bswap r12", 0x49, 0x0f, 0xcc );
	FCML_I64( "bswap r13", 0x49, 0x0f, 0xcd );
	FCML_I64( "bswap r14", 0x49, 0x0f, 0xce );
	FCML_I64( "bswap r15", 0x49, 0x0f, 0xcf );
}

void fcml_tf_instruction_BT(void) {
	// 0F A3 BT r/m16, r16 A Valid Valid Store selected bit in CF flag.
	// 0F A3 BT r/m32, r32 A Valid Valid Store selected bit in CF flag.
	// REX.W + 0F A3 BT r/m64, r64 A Valid N.E. Store selected bit in CF flag.
	FCML_I32( "bt dword ptr [esi],eax", 0x0F, 0xA3, 0x06 );
	FCML_I32( "bt word ptr [esi],ax", 0x66, 0x0F, 0xA3, 0x06 );
	FCML_I32( "bt dword ptr [0201h],eax", 0x67, 0x0F, 0xA3, 0x06, 0x01, 0x02 );
	// 0F BA /4 ib BT r/m16, imm8 B Valid Valid Store selected bit in CF flag.
	// 0F BA /4 ib BT r/m32, imm8 B Valid Valid Store selected bit in CF flag.
	// REX.W + 0F BA /4 ib BT r/m64, imm8 B Valid N.E. Store selected bit in CF flag.
	// EOS=32 EAS=64 (displacement extended to 64 bits)
	FCML_I64( "bt dword ptr [rdi+0000000004030201h],05h", 0x0F, 0xBA, 0xA7, 0x01, 0x02, 0x03, 0x4, 0x05 );
	// EOS=32 EAS=32 (displacement is not extended because EAS is 32)
	FCML_I64( "bt dword ptr [edi+04030201h],05h", 0x67, 0x0F, 0xBA, 0xA7, 0x01, 0x02, 0x03, 0x4, 0x05 );
	// EOS=64 EAS=64
	FCML_I64( "bt qword ptr [rdi+0000000004030201h],05h", 0x48, 0x0F, 0xBA, 0xA7, 0x01, 0x02, 0x03, 0x4, 0x05 );
	// EOS=64 EAS=64
	FCML_I64( "bt qword ptr [rdi+0000000004030201h],0ffh", 0x48, 0x0F, 0xBA, 0xA7, 0x01, 0x02, 0x03, 0x4, 0xff );
}

void fcml_tf_instruction_BTC(void) {
	// 0F BB BTC r/m16, r16 A Valid Valid Store selected bit in CF flag and complement.
	// 0F BB BTC r/m32, r32 A Valid Valid Store selected bit in CF flag and complement.
	// REX.W + 0F BB BTC r/m64, r64 A Valid N.E. Store selected bit in CF flag and complement.
	FCML_I32( "btc dword ptr [esi],eax", 0x0F, 0xBB, 0x06 );
	FCML_I32( "btc word ptr [esi],ax", 0x66, 0x0F, 0xBB, 0x06 );
	FCML_I32( "btc dword ptr [0201h],eax", 0x67, 0x0F, 0xBB, 0x06, 0x01, 0x02 );
	// 0F BA /7 ib BTC r/m16, imm8 B Valid Valid Store selected bit in CF flag and complement.
	// 0F BA /7 ib BTC r/m32, imm8 B Valid Valid Store selected bit in CF flag and complement.
	// REX.W + 0F BA /7 ib BTC r/m64, imm8 B Valid N.E. Store selected bit in CF flag and complement.
	// EOS=32 EAS=64 (displacement extended to 64 bits)
	FCML_I64( "btc dword ptr [rdi+0000000004030201h],05h", 0x0F, 0xBA, 0xBF, 0x01, 0x02, 0x03, 0x4, 0x05 );
	// EOS=32 EAS=32 (displacement is not extended because EAS is 32)
	FCML_I64( "btc dword ptr [edi+04030201h],05h", 0x67, 0x0F, 0xBA, 0xBF, 0x01, 0x02, 0x03, 0x4, 0x05 );
	// EOS=64 EAS=64
	FCML_I64( "btc qword ptr [rdi+0000000004030201h],05h", 0x48, 0x0F, 0xBA, 0xBF, 0x01, 0x02, 0x03, 0x4, 0x05 );
	// EOS=64 EAS=64
	FCML_I64( "btc qword ptr [rdi+0000000004030201h],0ffh", 0x48, 0x0F, 0xBA, 0xBF, 0x01, 0x02, 0x03, 0x4, 0xff );
}

void fcml_tf_instruction_BTR(void) {
	// 0F B3 BTR r/m16, r16 A Valid Valid Store selected bit in CF flag and clear.
	// 0F B3 BTR r/m32, r32 A Valid Valid Store selected bit in CF flag and clear.
	// REX.W + 0F B3 BTR r/m64, r64 A Valid N.E. Store selected bit in CF flag and clear.
	FCML_I32( "btr dword ptr [esi],eax", 0x0F, 0xB3, 0x06 );
	FCML_I32( "btr word ptr [esi],ax", 0x66, 0x0F, 0xB3, 0x06 );
	FCML_I32( "btr dword ptr [0201h],eax", 0x67, 0x0F, 0xB3, 0x06, 0x01, 0x02 );
	// 0F BA /6 ib BTR r/m16, imm8 B Valid Valid Store selected bit in CF flag and clear.
	// 0F BA /6 ib BTR r/m32, imm8 B Valid Valid Store selected bit in CF flag and clear.
	// REX.W + 0F BA /6 ib BTR r/m64, imm8 B Valid N.E. Store selected bit in CF flag and clear.
	// EOS=32 EAS=64 (displacement extended to 64 bits)
	FCML_I64( "btr dword ptr [rdi+0000000004030201h],05h", 0x0F, 0xBA, 0xB7, 0x01, 0x02, 0x03, 0x4, 0x05 );
	// EOS=32 EAS=32 (displacement is not extended because EAS is 32)
	FCML_I64( "btr dword ptr [edi+04030201h],05h", 0x67, 0x0F, 0xBA, 0xB7, 0x01, 0x02, 0x03, 0x4, 0x05 );
	// EOS=64 EAS=64
	FCML_I64( "btr qword ptr [rdi+0000000004030201h],05h", 0x48, 0x0F, 0xBA, 0xB7, 0x01, 0x02, 0x03, 0x4, 0x05 );
	// EOS=64 EAS=64
	FCML_I64( "btr qword ptr [rdi+0000000004030201h],0ffh", 0x48, 0x0F, 0xBA, 0xB7, 0x01, 0x02, 0x03, 0x4, 0xff );
}

void fcml_tf_instruction_BTS(void) {
	// 0F AB BTS r/m16, r16 A Valid Valid Store selected bit in CF flag and set.
	// 0F AB BTS r/m32, r32 A Valid Valid Store selected bit in CF flag and set.
	// REX.W + 0F AB BTS r/m64, r64 A Valid N.E. Store selected bit in CF flag and set.
	FCML_I32( "bts dword ptr [esi],eax", 0x0F, 0xAB, 0x06 );
	FCML_I32( "bts word ptr [esi],ax", 0x66, 0x0F, 0xAB, 0x06 );
	FCML_I32( "bts dword ptr [0201h],eax", 0x67, 0x0F, 0xAB, 0x06, 0x01, 0x02 );
	// 0F BA /5 ib BTS r/m16, imm8 B Valid Valid Store selected bit in CF flag and set.
	// 0F BA /5 ib BTS r/m32, imm8 B Valid Valid Store selected bit in CF flag and set.
	// REX.W + 0F BA /5 ib BTS r/m64, imm8 B Valid N.E. Store selected bit in CF flag and set.
	// EOS=32 EAS=64 (displacement extended to 64 bits)
	FCML_I64( "bts dword ptr [rdi+0000000004030201h],05h", 0x0F, 0xBA, 0xAF, 0x01, 0x02, 0x03, 0x4, 0x05 );
	// EOS=32 EAS=32 (displacement is not extended because EAS is 32)
	FCML_I64( "bts dword ptr [edi+04030201h],05h", 0x67, 0x0F, 0xBA, 0xAF, 0x01, 0x02, 0x03, 0x4, 0x05 );
	// EOS=64 EAS=64
	FCML_I64( "bts qword ptr [rdi+0000000004030201h],05h", 0x48, 0x0F, 0xBA, 0xAF, 0x01, 0x02, 0x03, 0x4, 0x05 );
	// EOS=64 EAS=64
	FCML_I64( "bts qword ptr [rdi+0000000004030201h],0ffh", 0x48, 0x0F, 0xBA, 0xAF, 0x01, 0x02, 0x03, 0x4, 0xff );
}

void fcml_tf_instruction_BEXR(void) {
	// VEX.NDS1.LZ.0F38.W0 F7 /r BEXR r32a, r/m32, r32b
	FCML_I32( "bexr eax,dword ptr [eax],edi", 0xC4, 0xE2, 0x40, 0xF7, 0x00 );
	FCML_I32( "bexr eax,eax,edi", 0xC4, 0xE2, 0x40, 0xF7, 0xC0 );
	// VEX.NDS1.LZ.0F38.W1 F7 /r BEXR r64a, r/m64, r64b
	FCML_I32( "bexr rax,qword ptr [eax],rdi", 0xC4, 0xE2, 0xC0, 0xF7, 0x00 );
	FCML_I32( "bexr rax,rax,rdi", 0xC4, 0xE2, 0xC0, 0xF7, 0xC0 );
}

void fcml_tf_instruction_BEXTR(void) {
	// BEXTR reg32, reg/mem32, imm32 8F RXB.0A 0.1111.0.00 10 /r /id
	FCML_I32( "bextr eax,dword ptr [eax],04030201h", 0x8F, 0xEA, 0x78, 0x10, 0x00, 0x01, 0x02, 0x03, 0x04 );
	FCML_I32( "bextr eax,eax,04030201h", 0x8F, 0xEA, 0x78, 0x10, 0xC0, 0x01, 0x02, 0x03, 0x04 );
	// BEXTR reg64, reg/mem64, imm32 8F RXB.0A 1.1111.0.00 10 /r /id
	FCML_I64( "bextr rax,qword ptr [rax],04030201h", 0x8F, 0xEA, 0xF8, 0x10, 0x00, 0x01, 0x02, 0x03, 0x04 );
	FCML_I64( "bextr rax,rax,04030201h", 0x8F, 0xEA, 0xF8, 0x10, 0xC0, 0x01, 0x02, 0x03, 0x04 );
}

void fcml_tf_instruction_BLCFILL(void) {
	// BLCFILL reg32, reg/mem32 8F RXB.09 0.dest.0.00 01 /1
	FCML_I32( "blcfill ebx,dword ptr [eax]", 0x8F, 0xE9, 0x60, 0x01, 0x08 );
	FCML_I32( "blcfill ebx,eax", 0x8F, 0xE9, 0x60, 0x01, 0xC8 );
	// BLCFILL reg64, reg/mem64 8F RXB.09 1.dest.0.00 01 /1
	FCML_I32( "blcfill rbx,qword ptr [eax]", 0x8F, 0xE9, 0xE0, 0x01, 0x08 );
	FCML_I32( "blcfill rbx,rax", 0x8F, 0xE9, 0xE0, 0x01, 0xC8 );
}

void fcml_tf_instruction_BLCI(void) {
	// BLCI reg32, reg/mem32 8F RXB.09 0.dest.0.00 02 /6
	FCML_I32( "blci ebx,dword ptr [eax]", 0x8F, 0xE9, 0x60, 0x02, 0x30 );
	FCML_I32( "blci ebx,eax", 0x8F, 0xE9, 0x60, 0x02, 0xF0 );
	// BLCI reg64, reg/mem64 8F RXB.09 1.dest.0.00 02 /6
	FCML_I32( "blci rbx,qword ptr [eax]", 0x8F, 0xE9, 0xE0, 0x02, 0x30 );
	FCML_I32( "blci rbx,rax", 0x8F, 0xE9, 0xE0, 0x02, 0xF0 );
}

void fcml_tf_instruction_BLCIC(void) {
	// BLCIC reg32, reg/mem32 8F RXB.09 0.dest.0.00 01 /5
	FCML_I32( "blcic ebx,dword ptr [eax]", 0x8F, 0xE9, 0x60, 0x01, 0x28 );
	FCML_I32( "blcic ebx,eax", 0x8F, 0xE9, 0x60, 0x01, 0xE8 );
	// BLCIC reg64, reg/mem64 8F RXB.09 1.dest.0.00 01 /5
	FCML_I32( "blcic rbx,qword ptr [eax]", 0x8F, 0xE9, 0xE0, 0x01, 0x28 );
	FCML_I32( "blcic rbx,rax", 0x8F, 0xE9, 0xE0, 0x01, 0xE8 );
}

void fcml_tf_instruction_BLCMSK(void) {
	// BLCMSK reg32, reg/mem32 8F RXB.09 0.dest.0.00 02 /1
	FCML_I32( "blcmsk ebx,dword ptr [eax]", 0x8F, 0xE9, 0x60, 0x02, 0x08 );
	FCML_I32( "blcmsk ebx,eax", 0x8F, 0xE9, 0x60, 0x02, 0xC8 );
	// BLCMSK reg64, reg/mem64 8F RXB.09 1.dest.0.00 02 /1
	FCML_I32( "blcmsk rbx,qword ptr [eax]", 0x8F, 0xE9, 0xE0, 0x02, 0x08 );
	FCML_I32( "blcmsk rbx,rax", 0x8F, 0xE9, 0xE0, 0x02, 0xC8 );
}

void fcml_tf_instruction_BLCS(void) {
	// BLCS reg32, reg/mem32 8F RXB.09 0.dest.0.00 01 /3
	FCML_I32( "blcs ebx,dword ptr [eax]", 0x8F, 0xE9, 0x60, 0x01, 0x18 );
	FCML_I32( "blcs ebx,eax", 0x8F, 0xE9, 0x60, 0x01, 0xD8 );
	// BLCS reg64, reg/mem64 8F RXB.09 1.dest.0.00 01 /3
	FCML_I32( "blcs rbx,qword ptr [eax]", 0x8F, 0xE9, 0xE0, 0x01, 0x18 );
	FCML_I32( "blcs rbx,rax", 0x8F, 0xE9, 0xE0, 0x01, 0xD8 );
}

void fcml_tf_instruction_BLSFILL(void) {
	// BLSFILL reg32, reg/mem32 8F RXB.09 0.dest.0.00 01 /2
	FCML_I32( "blsfill ebx,dword ptr [eax]", 0x8F, 0xE9, 0x60, 0x01, 0x10 );
	FCML_I32( "blsfill ebx,eax", 0x8F, 0xE9, 0x60, 0x01, 0xD0 );
	// BLSFILL reg64, reg/mem64 8F RXB.09 1.dest.0.00 01 /2
	FCML_I32( "blsfill rbx,qword ptr [eax]", 0x8F, 0xE9, 0xE0, 0x01, 0x10 );
	FCML_I32( "blsfill rbx,rax", 0x8F, 0xE9, 0xE0, 0x01, 0xD0 );
}

void fcml_tf_instruction_BLSI(void) {
	// VEX.NDD.LZ.0F38.W0 F3 /3 BLSI r32, r/m32
	FCML_I32( "blsi edi,dword ptr [eax]", 0xC4, 0xE2, 0x40, 0xF3, 0x18 );
	FCML_I32( "blsi edi,eax", 0xC4, 0xE2, 0x40, 0xF3, 0xD8 );
	// VEX.NDD.LZ.0F38.W1 F3 /3 BLSI r64, r/m64
	FCML_I32( "blsi rdi,qword ptr [eax]", 0xC4, 0xE2, 0xC0, 0xF3, 0x18 );
	FCML_I32( "blsi rdi,rax", 0xC4, 0xE2, 0xC0, 0xF3, 0xD8 );
}

void fcml_tf_instruction_BLSIC(void) {
	// BLSIC reg32, reg/mem32 8F RXB.09 0.dest.0.00 01 /6
	FCML_I32( "blsic ebx,dword ptr [eax]", 0x8F, 0xE9, 0x60, 0x01, 0x30 );
	FCML_I32( "blsic ebx,eax", 0x8F, 0xE9, 0x60, 0x01, 0xF0 );
	// BLSIC reg64, reg/mem64 8F RXB.09 1.dest.0.00 01 /6
	FCML_I32( "blsic rbx,qword ptr [eax]", 0x8F, 0xE9, 0xE0, 0x01, 0x30 );
	FCML_I32( "blsic rbx,rax", 0x8F, 0xE9, 0xE0, 0x01, 0xF0 );
}

void fcml_tf_instruction_BLSMSK(void) {
	// VEX.NDD.LZ.0F38.W0 F3 /2 BLSMSK r32, r/m32
	FCML_I32( "blsmsk edi,dword ptr [eax]", 0xC4, 0xE2, 0x40, 0xF3, 0x10 );
	FCML_I32( "blsmsk edi,eax", 0xC4, 0xE2, 0x40, 0xF3, 0xD0 );
	// VEX.NDD.LZ.0F38.W1 F3 /2 BLSMSK r64, r/m64
	FCML_I32( "blsmsk rdi,qword ptr [eax]", 0xC4, 0xE2, 0xC0, 0xF3, 0x10 );
	FCML_I32( "blsmsk rdi,rax", 0xC4, 0xE2, 0xC0, 0xF3, 0xD0 );
}

void fcml_tf_instruction_BLSR(void) {
	// VEX.NDD.LZ.0F38.W0 F3 /1 BLSR r32, r/m32
	FCML_I32( "blsr edi,dword ptr [eax]", 0xC4, 0xE2, 0x40, 0xF3, 0x08 );
	FCML_I32( "blsr edi,eax", 0xC4, 0xE2, 0x40, 0xF3, 0xC8 );
	// VEX.NDD.LZ.0F38.W1 F3 /1 BLSR r64, r/m64
	FCML_I32( "blsr rdi,qword ptr [eax]", 0xC4, 0xE2, 0xC0, 0xF3, 0x08 );
	FCML_I32( "blsr rdi,rax", 0xC4, 0xE2, 0xC0, 0xF3, 0xC8 );
}

void fcml_tf_instruction_BZHI(void) {
	// VEX.NDS1.LZ.0F38.W0 F5 /r BZHI r32a, r/m32, r32b
	FCML_I32( "bzhi eax,dword ptr [eax],edi", 0xC4, 0xE2, 0x40, 0xF5, 0x00 );
	FCML_I32( "bzhi eax,eax,edi", 0xC4, 0xE2, 0x40, 0xF5, 0xC0 );
	// VEX.NDS1.LZ.0F38.W1 F5 /r BZHI r64a, r/m64, r64b
	FCML_I32( "bzhi rax,qword ptr [eax],rdi", 0xC4, 0xE2, 0xC0, 0xF5, 0x00 );
	FCML_I32( "bzhi rax,rax,rdi", 0xC4, 0xE2, 0xC0, 0xF5, 0xC0 );
}

CU_TestInfo fctl_ti_instructions_b[] = {
    { "fcml_tf_instruction_BLENDPD", fcml_tf_instruction_BLENDPD },
    { "fcml_tf_instruction_BLENDPS", fcml_tf_instruction_BLENDPS },
    { "fcml_tf_instruction_BLENDVPD", fcml_tf_instruction_BLENDVPD },
    { "fcml_tf_instruction_BLENDVPS", fcml_tf_instruction_BLENDVPS },
    { "fcml_tf_instruction_BOUND", fcml_tf_instruction_BOUND },
    { "fcml_tf_instruction_BSF", fcml_tf_instruction_BSF },
    { "fcml_tf_instruction_BSR", fcml_tf_instruction_BSR },
    { "fcml_tf_instruction_BSWAP", fcml_tf_instruction_BSWAP },
    { "fcml_tf_instruction_BT", fcml_tf_instruction_BT },
    { "fcml_tf_instruction_BTC", fcml_tf_instruction_BTC },
    { "fcml_tf_instruction_BTR", fcml_tf_instruction_BTR },
    { "fcml_tf_instruction_BTS", fcml_tf_instruction_BTS },
    { "fcml_tf_instruction_BEXR", fcml_tf_instruction_BEXR },
    { "fcml_tf_instruction_BEXTR", fcml_tf_instruction_BEXTR },
    { "fcml_tf_instruction_BLCFILL", fcml_tf_instruction_BLCFILL },
    { "fcml_tf_instruction_BLCI", fcml_tf_instruction_BLCI },
    { "fcml_tf_instruction_BLCIC", fcml_tf_instruction_BLCIC },
    { "fcml_tf_instruction_BLCMSK", fcml_tf_instruction_BLCMSK },
    { "fcml_tf_instruction_BLCS", fcml_tf_instruction_BLCS },
    { "fcml_tf_instruction_BLSFILL", fcml_tf_instruction_BLSFILL },
    { "fcml_tf_instruction_BLSI", fcml_tf_instruction_BLSI },
    { "fcml_tf_instruction_BLSIC", fcml_tf_instruction_BLSIC },
    { "fcml_tf_instruction_BLSMSK", fcml_tf_instruction_BLSMSK },
    { "fcml_tf_instruction_BLSR", fcml_tf_instruction_BLSR },
    { "fcml_tf_instruction_BZHI", fcml_tf_instruction_BZHI },
    CU_TEST_INFO_NULL,
};

CU_SuiteInfo fctl_si_instructions_b[] = {
    { "suite-fctl_ti_instructions_b", fcml_tf_instructions_b_suite_init, fcml_tf_instructions_b_suite_cleanup, fctl_ti_instructions_b },
    CU_SUITE_INFO_NULL,
};
