/*
 * FCML - Free Code Manipulation Library.
 * Copyright (C) 2010-2015 Slawomir Wojtasiak
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include <fcml_assembler.h>
#include "instructions_x_t.h"
#include "instructions_base_t.h"

fcml_bool fcml_tf_instructions_x_suite_init(void) {
	return FCML_TRUE;
}

fcml_bool fcml_tf_instructions_x_suite_cleanup(void) {
	return FCML_TRUE;
}

void fcml_tf_instruction_XADD(void) {

    FCML_I64_D( "xadd byte ptr [rax],dl", 0x48, 0x0F, 0xC0, 0x10 );
    FCML_I32( "xadd byte ptr [eax],dl", 0x0F, 0xC0, 0x10 );
    FCML_I32( "lock xadd byte ptr [eax],dl", 0xF0, 0x0F, 0xC0, 0x10 );
    FCML_I32( "xacquire lock xadd byte ptr [eax],dl", 0xF2, 0xF0, 0x0F, 0xC0, 0x10 );
    FCML_I32( "xrelease lock xadd byte ptr [eax],dl", 0xF3, 0xF0, 0x0F, 0xC0, 0x10 );

    FCML_A64( "xadd %dl,(%rax)", 0x0f, 0xc0, 0x10 );
    FCML_A64( "lock xadd %dl,(%rax)", 0xf0, 0x0f, 0xc0, 0x10 );
    FCML_A64( "xacquire lock xadd %dl,(%rax)", 0xf2, 0xf0, 0x0f, 0xc0, 0x10 );
    FCML_A64( "add %cl,(%rdi)", 0x00, 0x0f );

    FCML_I64( "xadd qword ptr [rax],rdx", 0x48, 0x0F, 0xC1, 0x10 );
    FCML_I32( "xadd dword ptr [eax],edx", 0x0F, 0xC1, 0x10 );
    FCML_I32( "lock xadd word ptr [eax],dx", 0xF0, 0x66, 0x0F, 0xC1, 0x10 );
    FCML_I32( "xacquire lock xadd word ptr [eax],dx", 0xF2, 0xF0, 0x66, 0x0F, 0xC1, 0x10 );
    FCML_I32( "xrelease lock xadd word ptr [eax],dx", 0xF3, 0xF0, 0x66, 0x0F, 0xC1, 0x10 );

    FCML_A64( "xadd %dl,(%rax)", 0x0f, 0xc0, 0x10 );
    FCML_A64( "lock xadd %dl,(%rax)", 0xf0, 0x0f, 0xc0, 0x10 );
    FCML_A64( "xacquire lock xadd %dl,(%rax)", 0xf2, 0xf0, 0x0f, 0xc0, 0x10 );
    FCML_A64( "xadd %rdx,(%rax)", 0x48, 0x0f, 0xc1, 0x10 );
    FCML_A64( "xadd %edx,(%rax)", 0x0f, 0xc1, 0x10 );
    FCML_A64( "lock xadd %dx,(%rax)", 0xf0, 0x66, 0x0f, 0xc1, 0x10 );
    FCML_A64( "xacquire lock xadd %dx,(%rax)", 0xf2, 0xf0, 0x66, 0x0f, 0xc1, 0x10 );
}

void fcml_tf_instruction_XCHG(void) {

    FCML_I3264_M( "xchg eax,ecx", 3, FCML_MI( 0x87, 0xc8 ), FCML_MI( 0x87, 0xc1 ), FCML_MI( 0x91 ) );
    FCML_I64_M( "xchg ax,cx", 3, FCML_MI( 0x66, 0x87, 0xc8 ), FCML_MI( 0x66, 0x87, 0xc1 ), FCML_MI( 0x66, 0x91 ) );
    FCML_I64_M( "xchg rax,rcx", 3, FCML_MI( 0x48, 0x87, 0xc8 ), FCML_MI( 0x48, 0x87, 0xc1 ), FCML_MI( 0x48, 0x91 ) );

    FCML_A64_M( "xchg %ecx,%eax", 3, FCML_MI( 0x87, 0xc8 ), FCML_MI( 0x87, 0xc1 ), FCML_MI( 0x91 ) );

    FCML_I32( "xacquire xchg byte ptr [eax],al", 0xF2, 0x86, 0x00 );
	FCML_I32( "xacquire lock xchg byte ptr [eax],al", 0xF2, 0xF0, 0x86, 0x00 );
    FCML_I32( "lock xchg byte ptr [eax],al", 0xF0, 0x86, 0x00 );
    FCML_I32( "xchg al,al", 0x86, 0xc0 );
    FCML_I32_M( "xchg bl,al", 2, FCML_MI( 0x86, 0xc3 ), FCML_MI( 0x86, 0xd8 ) );

    FCML_A64( "lock xchg %al,(%rax)", 0xf0, 0x86, 0x00 );

    FCML_I32( "lock xchg dword ptr [eax],eax", 0xF0, 0x87, 0x00 );
    FCML_I32_M( "xchg eax,ecx", 3, FCML_MI( 0x87, 0xc8 ), FCML_MI( 0x87, 0xc1 ), FCML_MI( 0x91 ) );
    FCML_I32_M( "xchg eax,eax", 2, FCML_MI( 0x87, 0xc0 ), FCML_MI( 0x90 ) );
    FCML_I32_M( "xchg ax,ax", 2, FCML_MI( 0x66, 0x87, 0xc0 ), FCML_MI( 0x66, 0x90 ) );

    FCML_A32_M( "xchg %ecx,%eax", 3, FCML_MI( 0x87, 0xc8 ), FCML_MI( 0x87, 0xc1 ), FCML_MI( 0x91 ) );
}

void fcml_tf_instruction_XGETBV(void) {

    FCML_I32( "xgetbv", 0x0F, 0x01, 0xD0 );
    FCML_I64( "xgetbv", 0x0F, 0x01, 0xD0 );

    FCML_A64( "xgetbv", 0x0f, 0x01, 0xd0 );
    FCML_A64( "xgetbv", 0x0f, 0x01, 0xd0 );
}

void fcml_tf_instruction_XLAT(void) {

    FCML_I32( "xlat byte ptr [ebx]", 0xD7 );
    FCML_I32( "xlat byte ptr [bx]", 0x67, 0xD7 );
    FCML_I32_A( "xlatb", 0xD7 );

    FCML_A64( "xlat (%rbx)", 0xd7 );
    FCML_A64_A( "xlatb (%rbx)", 0xd7 );
    FCML_A64_A( "xlatb", 0xd7 );
    FCML_A64_A( "xlat", 0xd7 );
}

void fcml_tf_instruction_XOR(void) {

    FCML_I32_M( "xor al,0ffh", 2, FCML_MI( 0x80, 0xf0, 0xff ), FCML_MI( 0x34, 0xff ) );
    FCML_I32_A_FAILED( "xor al,0ffh", 0xF0, 0x80, 0xf0, 0xff );

    FCML_I32_M( "xor ax,11ffh", 2, FCML_MI( 0x66, 0x81, 0xf0, 0xff, 0x11 ), FCML_MI( 0x66, 0x35, 0xff, 0x11 ) );

    FCML_I64_M( "xor rax,00000000227711ffh", 2, FCML_MI( 0x48, 0x81, 0xf0, 0xff, 0x11, 0x77, 0x22 ), FCML_MI( 0x48, 0x35, 0xff, 0x11, 0x77, 0x22 ) );

    FCML_I32( "lock xor byte ptr [eax],11h", 0xF0, 0x80, 0x30, 0x11 );
    FCML_I32( "xacquire lock xor byte ptr [eax],11h", 0xF2, 0xF0, 0x80, 0x30, 0x11 );
    FCML_I32( "xrelease lock xor byte ptr [eax],11h", 0xF3, 0xF0, 0x80, 0x30, 0x11 );

    FCML_I64( "xor byte ptr [rax],30h", 0x80, 0x30, 0x30 );

    FCML_I64( "lock xor dword ptr [rax],22ffff30h", 0xF0, 0x81, 0x30, 0x30, 0xff, 0xff, 0x22 );
    FCML_I64( "xacquire lock xor dword ptr [rax],22ffff30h", 0xF2, 0xF0, 0x81, 0x30, 0x30, 0xff, 0xff, 0x22 );
    FCML_I64( "xrelease lock xor dword ptr [rax],22ffff30h", 0xF3, 0xF0, 0x81, 0x30, 0x30, 0xff, 0xff, 0x22 );
    FCML_I64( "xor qword ptr [rax],0ffffffffffffff30h", 0x48, 0x81, 0x30, 0x30, 0xff, 0xff, 0xff  );

    FCML_I64_M( "lock xor dword ptr [rax],00000030h", 2, FCML_MI( 0xF0, 0x83, 0x30, 0x30 ), FCML_MI( 0xF0, 0x81, 0x30, 0x30, 0x00, 0x00, 0x00 ) );
    FCML_I64_M( "xacquire lock xor dword ptr [rax],00000030h", 2, FCML_MI( 0xF2, 0xF0, 0x83, 0x30, 0x30 ), FCML_MI( 0xF2, 0xF0, 0x81, 0x30, 0x30, 0x00, 0x00, 0x00 ) );
    FCML_I64_M( "xrelease lock xor dword ptr [rax],00000030h", 2, FCML_MI( 0xF3, 0xF0, 0x83, 0x30, 0x30 ), FCML_MI( 0xF3, 0xF0, 0x81, 0x30, 0x30, 0x00, 0x00, 0x00 ) );
    FCML_I64_M( "xor word ptr [rax],0030h", 2, FCML_MI( 0x66, 0x83, 0x30, 0x30 ), FCML_MI( 0x66, 0x81, 0x30, 0x30, 0x00 ) );
    FCML_I64_M( "xor qword ptr [rax],0000000000000030h", 2, FCML_MI( 0x48, 0x83, 0x30, 0x30 ), FCML_MI( 0x48, 0x81, 0x30, 0x30, 0x00, 0x00, 0x00 ) );

    FCML_I64( "lock xor byte ptr [rax],dh", 0xF0, 0x30, 0x30 );
    FCML_I64( "xacquire lock xor byte ptr [rax],dh", 0xF2, 0xF0, 0x30, 0x30 );
    FCML_I64( "xrelease lock xor byte ptr [rax],dh", 0xF3, 0xF0, 0x30, 0x30 );
    FCML_I64( "xor byte ptr [rax],sil", 0x40, 0x30, 0x30 );

    FCML_I64( "lock xor dword ptr [rax],esi", 0xF0, 0x31, 0x30  );
    FCML_I64( "xacquire lock xor dword ptr [rax],esi", 0xF2, 0xF0, 0x31, 0x30  );
    FCML_I64( "xrelease lock xor dword ptr [rax],esi", 0xF3, 0xF0, 0x31, 0x30  );
    FCML_I64( "xor word ptr [rax],si", 0x66, 0x31, 0x30 );
    FCML_I64( "xor qword ptr [rax],rsi", 0x48, 0x31, 0x30  );

    FCML_I64( "xor dh,byte ptr [rax]", 0x32, 0x30  );
    FCML_I64( "xor dh,byte ptr [rax]", 0x66, 0x32, 0x30 );
    FCML_I64( "xor sil,byte ptr [rax]", 0x40, 0x32, 0x30 );

    FCML_I64( "xor esi,dword ptr [rax]", 0x33, 0x30  );
    FCML_I64( "xor si,word ptr [rax]", 0x66, 0x33, 0x30 );
    FCML_I64( "xor rsi,qword ptr [rax]", 0x48, 0x33, 0x30  );

    FCML_A64( "lock xorl $0x22ffff30,(%rax)", 0xf0, 0x81, 0x30, 0x30, 0xff, 0xff, 0x22 );
    FCML_A64( "xacquire lock xorl $0x22ffff30,(%rax)", 0xf2, 0xf0, 0x81, 0x30, 0x30, 0xff, 0xff, 0x22 );
    FCML_A64( "xrelease lock xorl $0x22ffff30,(%rax)", 0xf3, 0xf0, 0x81, 0x30, 0x30, 0xff, 0xff, 0x22 );
    FCML_A64( "xorq $0xffffffffffffff30,(%rax)", 0x48, 0x81, 0x30, 0x30, 0xff, 0xff, 0xff );
    FCML_A64( "xor (%rax),%dh", 0x32, 0x30 );
}

void fcml_tf_instruction_XORPD(void) {

    FCML_I64( "xorpd xmm0,xmmword ptr [rax+0000000000000020h]", 0x66, 0x0F, 0x57, 0x40, 0x20 );
    FCML_I32( "xorpd xmm0,xmmword ptr [eax+00000020h]", 0x66, 0x0F, 0x57, 0x40, 0x20 );

    FCML_I64( "vxorpd ymm10,ymm14,ymmword ptr [r9+rax]", 0xC4, 0x41, 0x0D, 0x57, 0x14, 0x01 );
    FCML_I32( "vxorpd xmm2,xmm7,xmmword ptr [ecx+eax]", 0xc5, 0xc1, 0x57, 0x14, 0x01 );
    FCML_I32( "vxorpd xmm2,xmm2,xmmword ptr [ecx+eax]", 0xc5, 0xe9, 0x57, 0x14, 0x01 );

    FCML_A64( "xorpd 0x0000000000000020(%rax),%xmm0", 0x66, 0x0f, 0x57, 0x40, 0x20 );
    FCML_A64( "xorpd 0x0000000000000020(%rax),%xmm0", 0x66, 0x0f, 0x57, 0x40, 0x20 );
    FCML_A64( "vxorpd (%r9,%rax),%ymm14,%ymm10", 0xc4, 0x41, 0x0d, 0x57, 0x14, 0x01 );
    FCML_A64( "vxorpd (%rcx,%rax),%xmm7,%xmm2", 0xc5, 0xc1, 0x57, 0x14, 0x01 );
    FCML_A64( "vxorpd (%rcx,%rax),%xmm2,%xmm2", 0xc5, 0xe9, 0x57, 0x14, 0x01 );
}

void fcml_tf_instruction_XORPS(void) {

    FCML_I64( "xorps xmm0,xmmword ptr [rax+0000000000000020h]", 0x0F, 0x57, 0x40, 0x20 );
    FCML_I32( "xorps xmm0,xmmword ptr [eax+00000020h]", 0x0F, 0x57, 0x40, 0x20 );

    FCML_I64( "vxorps ymm10,ymm14,ymmword ptr [r9+rax]", 0xC4, 0x41, 0x0C, 0x57, 0x14, 0x01 );
    FCML_I32( "vxorps xmm2,xmm7,xmmword ptr [ecx+eax]", 0xc5, 0xc0, 0x57, 0x14, 0x01 );
    FCML_I32( "vxorps xmm2,xmm2,xmmword ptr [ecx+eax]", 0xc5, 0xe8, 0x57, 0x14, 0x01 );

    FCML_A64( "xorps 0x0000000000000020(%rax),%xmm0", 0x0f, 0x57, 0x40, 0x20 );
    FCML_A64( "vxorps (%r9,%rax),%ymm14,%ymm10", 0xc4, 0x41, 0x0c, 0x57, 0x14, 0x01 );
    FCML_A64( "vxorps (%rcx,%rax),%xmm7,%xmm2", 0xc5, 0xc0, 0x57, 0x14, 0x01 );
    FCML_A64( "vxorps (%rcx,%rax),%xmm2,%xmm2", 0xc5, 0xe8, 0x57, 0x14, 0x01 );
}

void fcml_tf_instruction_XRSTOR(void) {

    FCML_I64( "xrstor [rax]", 0x0F, 0xAE, 0x28 );
    FCML_I32( "xrstor [eax]", 0x0F, 0xAE, 0x28 );
    FCML_I64( "xrstor [rax]", 0x66, 0x0F, 0xAE, 0x28 );
    FCML_I32( "xrstor [eax]", 0x66, 0x0F, 0xAE, 0x28 );
    FCML_I64( "xrstor64 [rax]", 0x48, 0x0F, 0xAE, 0x28 );

    FCML_A64( "xrstor (%rax)", 0x0f, 0xae, 0x28 );
    FCML_A64( "xrstor64 (%rax)", 0x48, 0x0f, 0xae, 0x28 );
}

void fcml_tf_instruction_XSAVE(void) {

    FCML_I64( "xsave [rax]", 0x0F, 0xAE, 0x20 );
    FCML_I32( "xsave [eax]", 0x0F, 0xAE, 0x20 );
    FCML_I64( "xsave [rax]", 0x66, 0x0F, 0xAE, 0x20 );
    FCML_I32( "xsave [eax]", 0x66, 0x0F, 0xAE, 0x20 );
    FCML_I64( "xsave64 [rax]", 0x48, 0x0F, 0xAE, 0x20 );

    FCML_A64( "xsave (%rax)", 0x0f, 0xae, 0x20 );
    FCML_A64( "xsave64 (%rax)", 0x48, 0x0f, 0xae, 0x20 );
}

void fcml_tf_instruction_XSAVEOPT(void) {

    FCML_I64( "xsaveopt [rax]", 0x0F, 0xAE, 0x30 );
    FCML_I32( "xsaveopt [eax]", 0x0F, 0xAE, 0x30 );
    FCML_I64( "xsaveopt [rax]", 0x66, 0x0F, 0xAE, 0x30 );
    FCML_I32( "xsaveopt [eax]", 0x66, 0x0F, 0xAE, 0x30 );
    FCML_I64( "xsaveopt64 [rax]", 0x48, 0x0F, 0xAE, 0x30 );

    FCML_A64( "xsaveopt (%rax)", 0x0f, 0xae, 0x30 );
    FCML_A64( "xsaveopt64 (%rax)", 0x48, 0x0f, 0xae, 0x30 );
}

void fcml_tf_instruction_XSETBV(void) {

    FCML_I64( "xsetbv", 0x0F, 0x01, 0xD1 );
    FCML_I32( "xsetbv", 0x0F, 0x01, 0xD1 );

    FCML_A64( "xsetbv", 0x0f, 0x01, 0xd1 );
}

void fcml_tf_instruction_XABORT(void) {

    FCML_I3264( "xabort 20h", 0xC6, 0xF8, 0x20 );

    FCML_A64( "xabort $0x20", 0xc6, 0xf8, 0x20 );
}

void fcml_tf_instruction_XBEGIN(void) {

    FCML_I32( "xbegin 1045h",  0x66, 0xC7, 0xF8, 0x40, 0x00 );
    FCML_I32( "xbegin 0ff701006h", 0xC7, 0xF8, 0x00, 0x00, 0x30, 0xFF );
    FCML_I32( "xbegin 00401005h", 0xC7, 0xF8, 0xFF, 0xFF, 0xFF, 0xFF );
    FCML_I64_A_FAILED( "xbegin 0000800500401006h", 0xC7, 0xF8, 0x00, 0x00, 0x00, 0x00 );
    FCML_I64( "xbegin 0000800000401005h", 0xC7, 0xF8, 0xFF, 0xFF, 0xFF, 0xFF );

    FCML_A64( "xbegin 0x0000800000401005", 0xc7, 0xf8, 0xff, 0xff, 0xff, 0xff );
}

void fcml_tf_instruction_XEND(void) {

    FCML_I32( "xend", 0x0F, 0x01, 0xD5 );
    FCML_I64( "xend", 0x0F, 0x01, 0xD5 );

    FCML_A64( "xend", 0x0f, 0x01, 0xd5 );
    FCML_A64( "xend", 0x0f, 0x01, 0xd5 );
}

void fcml_tf_instruction_XTEST(void) {

    FCML_I32( "xtest", 0x0F, 0x01, 0xD6 );
    FCML_I64( "xtest", 0x0F, 0x01, 0xD6 );

    FCML_A64( "xtest", 0x0f, 0x01, 0xd6 );
    FCML_A64( "xtest", 0x0f, 0x01, 0xd6 );
}

fcml_stf_test_case fctl_ti_instructions_x[] = {
	{ "fcml_tf_instruction_XADD", fcml_tf_instruction_XADD },
	{ "fcml_tf_instruction_XCHG", fcml_tf_instruction_XCHG },
	{ "fcml_tf_instruction_XGETBV", fcml_tf_instruction_XGETBV },
	{ "fcml_tf_instruction_XLAT", fcml_tf_instruction_XLAT },
	{ "fcml_tf_instruction_XOR", fcml_tf_instruction_XOR },
	{ "fcml_tf_instruction_XORPD", fcml_tf_instruction_XORPD },
	{ "fcml_tf_instruction_XORPS", fcml_tf_instruction_XORPS },
	{ "fcml_tf_instruction_XRSTOR", fcml_tf_instruction_XRSTOR },
	{ "fcml_tf_instruction_XSAVE", fcml_tf_instruction_XSAVE },
	{ "fcml_tf_instruction_XSAVEOPT", fcml_tf_instruction_XSAVEOPT },
	{ "fcml_tf_instruction_XSETBV", fcml_tf_instruction_XSETBV },
	{ "fcml_tf_instruction_XABORT", fcml_tf_instruction_XABORT },
	{ "fcml_tf_instruction_XBEGIN", fcml_tf_instruction_XBEGIN },
	{ "fcml_tf_instruction_XEND", fcml_tf_instruction_XEND },
	{ "fcml_tf_instruction_XTEST", fcml_tf_instruction_XTEST },
	FCML_STF_NULL_TEST
};

fcml_stf_test_suite fctl_si_instructions_x = {
	"suite-fctl_ti_instructions_x", fcml_tf_instructions_x_suite_init, fcml_tf_instructions_x_suite_cleanup, fctl_ti_instructions_x
};



