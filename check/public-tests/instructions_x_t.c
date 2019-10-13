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
    FCML_A64( "xorpd 0x0000000000000020(%rax),%xmm0", 0x66, 0x0f, 0x57, 0x40, 0x20 );
    FCML_A64( "xorpd 0x0000000000000020(%rax),%xmm0", 0x66, 0x0f, 0x57, 0x40, 0x20 );

    /* xmm1, xmm2, m128 */
    FCML_A64_M("vxorpd (%rax),%xmm7,%xmm15", 2, FCML_MI(0x62, 0x71, 0xc5, 0x08, 0x57, 0x38), FCML_MI(0xc5, 0x41, 0x57, 0x38));
    FCML_I64_M("vxorpd xmm15,xmm7,xmmword ptr [rax]", 2, FCML_MI(0x62, 0x71, 0xc5, 0x08, 0x57, 0x38), FCML_MI(0xc5, 0x41, 0x57, 0x38));
    FCML_A32_M("vxorpd (%eax),%xmm6,%xmm7", 2, FCML_MI(0x62, 0xf1, 0xcd, 0x08, 0x57, 0x38), FCML_MI(0xc5, 0xc9, 0x57, 0x38));
    FCML_I32_M("vxorpd xmm7,xmm6,xmmword ptr [eax]", 2, FCML_MI(0x62, 0xf1, 0xcd, 0x08, 0x57, 0x38), FCML_MI(0xc5, 0xc9, 0x57, 0x38));
    /* ymm1, ymm2, m256 */
    FCML_A64_M("vxorpd (%rax),%ymm7,%ymm15", 2, FCML_MI(0x62, 0x71, 0xc5, 0x28, 0x57, 0x38), FCML_MI(0xc5, 0x45, 0x57, 0x38));
    FCML_I64_M("vxorpd ymm15,ymm7,ymmword ptr [rax]", 2, FCML_MI(0x62, 0x71, 0xc5, 0x28, 0x57, 0x38), FCML_MI(0xc5, 0x45, 0x57, 0x38));
    FCML_A32_M("vxorpd (%eax),%ymm5,%ymm7", 2, FCML_MI(0x62, 0xf1, 0xd5, 0x28, 0x57, 0x38), FCML_MI(0xc5, 0xd5, 0x57, 0x38));
    FCML_I32_M("vxorpd ymm7,ymm5,ymmword ptr [eax]", 2, FCML_MI(0x62, 0xf1, 0xd5, 0x28, 0x57, 0x38), FCML_MI(0xc5, 0xd5, 0x57, 0x38));
    /* zmm1, zmm2, m512 */
    FCML_A64("vxorpd (%rax),%zmm7,%zmm15", 0x62, 0x71, 0xc5, 0x48, 0x57, 0x38);
    FCML_I64("vxorpd zmm15,zmm7,zmmword ptr [rax]", 0x62, 0x71, 0xc5, 0x48, 0x57, 0x38);
    FCML_A32("vxorpd (%eax),%zmm3,%zmm7", 0x62, 0xf1, 0xe5, 0x48, 0x57, 0x38);
    FCML_I32("vxorpd zmm7,zmm3,zmmword ptr [eax]", 0x62, 0xf1, 0xe5, 0x48, 0x57, 0x38);
    /* xmm1, xmm2, xmm3 */
    FCML_A64_M("vxorpd %xmm1,%xmm7,%xmm15", 2, FCML_MI(0x62, 0x71, 0xc5, 0x08, 0x57, 0xf9), FCML_MI(0xc5, 0x41, 0x57, 0xf9));
    FCML_I64_M("vxorpd xmm15,xmm7,xmm1", 2, FCML_MI(0x62, 0x71, 0xc5, 0x08, 0x57, 0xf9), FCML_MI(0xc5, 0x41, 0x57, 0xf9));
    FCML_A32_M("vxorpd %xmm1,%xmm2,%xmm7", 2, FCML_MI(0x62, 0xf1, 0xed, 0x08, 0x57, 0xf9), FCML_MI(0xc5, 0xe9, 0x57, 0xf9));
    FCML_I32_M("vxorpd xmm7,xmm2,xmm1", 2, FCML_MI(0x62, 0xf1, 0xed, 0x08, 0x57, 0xf9), FCML_MI(0xc5, 0xe9, 0x57, 0xf9));
    /* ymm1, ymm2, ymm3 */
    FCML_A64_M("vxorpd %ymm6,%ymm7,%ymm14", 2, FCML_MI(0x62, 0x71, 0xc5, 0x28, 0x57, 0xf6), FCML_MI(0xc5, 0x45, 0x57, 0xf6));
    FCML_I64_M("vxorpd ymm14,ymm7,ymm6", 2, FCML_MI(0x62, 0x71, 0xc5, 0x28, 0x57, 0xf6), FCML_MI(0xc5, 0x45, 0x57, 0xf6));
    FCML_A32_M("vxorpd %ymm5,%ymm3,%ymm6", 2, FCML_MI(0x62, 0xf1, 0xe5, 0x28, 0x57, 0xf5), FCML_MI(0xc5, 0xe5, 0x57, 0xf5));
    FCML_I32_M("vxorpd ymm6,ymm3,ymm5", 2, FCML_MI(0x62, 0xf1, 0xe5, 0x28, 0x57, 0xf5), FCML_MI(0xc5, 0xe5, 0x57, 0xf5));
    /* zmm1, zmm2, zmm3 */
    FCML_A64("vxorpd %zmm4,%zmm15,%zmm6", 0x62, 0xf1, 0x85, 0x48, 0x57, 0xf4);
    FCML_I64("vxorpd zmm6,zmm15,zmm4", 0x62, 0xf1, 0x85, 0x48, 0x57, 0xf4);
    FCML_A32("vxorpd %zmm4,%zmm6,%zmm6", 0x62, 0xf1, 0xcd, 0x48, 0x57, 0xf4);
    FCML_I32("vxorpd zmm6,zmm6,zmm4", 0x62, 0xf1, 0xcd, 0x48, 0x57, 0xf4);
    /* disp8 */
    FCML_I32("vxorpd zmm1,zmm2,zmmword ptr [esp+00000200h]", 0x62, 0xf1, 0xed, 0x48, 0x57, 0x4c, 0x24, 0x08);
    FCML_A32("vxorpd 0x00000200(%esp),%zmm2,%zmm1", 0x62, 0xf1, 0xed, 0x48, 0x57, 0x4c, 0x24, 0x08);
    FCML_I64("vxorpd zmm1,zmm2,zmmword ptr [rsp+0000000000000200h]", 0x62, 0xf1, 0xed, 0x48, 0x57, 0x4c, 0x24, 0x08);
    FCML_A64("vxorpd 0x0000000000000200(%rsp),%zmm2,%zmm1", 0x62, 0xf1, 0xed, 0x48, 0x57, 0x4c, 0x24, 0x08);
    FCML_I32_M("vxorpd ymm1,ymm2,ymmword ptr [esp+00000100h]", 2, FCML_MI(0x62, 0xf1, 0xed, 0x28, 0x57, 0x4c, 0x24, 0x08), FCML_MI(0xc5, 0xed, 0x57, 0x8c, 0x24, 0x00, 0x01, 0x00, 0x00));
    FCML_A32_M("vxorpd 0x00000100(%esp),%ymm2,%ymm1", 2, FCML_MI(0x62, 0xf1, 0xed, 0x28, 0x57, 0x4c, 0x24, 0x08), FCML_MI(0xc5, 0xed, 0x57, 0x8c, 0x24, 0x00, 0x01, 0x00, 0x00));
    FCML_I64_M("vxorpd ymm1,ymm2,ymmword ptr [rsp+0000000000000100h]", 2, FCML_MI(0x62, 0xf1, 0xed, 0x28, 0x57, 0x4c, 0x24, 0x08), FCML_MI(0xc5, 0xed, 0x57, 0x8c, 0x24, 0x00, 0x01, 0x00, 0x00));
    FCML_A64_M("vxorpd 0x0000000000000100(%rsp),%ymm2,%ymm1", 2, FCML_MI(0x62, 0xf1, 0xed, 0x28, 0x57, 0x4c, 0x24, 0x08), FCML_MI(0xc5, 0xed, 0x57, 0x8c, 0x24, 0x00, 0x01, 0x00, 0x00));
    FCML_I32_M("vxorpd xmm1,xmm2,xmmword ptr [esp+00000080h]", 2, FCML_MI(0x62, 0xf1, 0xed, 0x08, 0x57, 0x4c, 0x24, 0x08), FCML_MI(0xc5, 0xe9, 0x57, 0x8c, 0x24, 0x80, 0x00, 0x00, 0x00));
    FCML_A32_M("vxorpd 0x00000080(%esp),%xmm2,%xmm1", 2, FCML_MI(0x62, 0xf1, 0xed, 0x08, 0x57, 0x4c, 0x24, 0x08), FCML_MI(0xc5, 0xe9, 0x57, 0x8c, 0x24, 0x80, 0x00, 0x00, 0x00));
    FCML_I64_M("vxorpd xmm1,xmm2,xmmword ptr [rsp+0000000000000080h]", 2, FCML_MI(0x62, 0xf1, 0xed, 0x08, 0x57, 0x4c, 0x24, 0x08), FCML_MI(0xc5, 0xe9, 0x57, 0x8c, 0x24, 0x80, 0x00, 0x00, 0x00));
    FCML_A64_M("vxorpd 0x0000000000000080(%rsp),%xmm2,%xmm1", 2, FCML_MI(0x62, 0xf1, 0xed, 0x08, 0x57, 0x4c, 0x24, 0x08), FCML_MI(0xc5, 0xe9, 0x57, 0x8c, 0x24, 0x80, 0x00, 0x00, 0x00));
    /* {k}{z} */
    FCML_A64("vxorpd (%r9,%r8),%xmm14,%xmm10{%k4}{z}", 0x62, 0x11, 0x8d, 0x8c, 0x57, 0x14, 0x01);
    FCML_I64("vxorpd xmm10{k4}{z},xmm14,xmmword ptr [r9+r8]", 0x62, 0x11, 0x8d, 0x8c, 0x57, 0x14, 0x01);
    FCML_A32("vxorpd (%ecx,%eax),%xmm7,%xmm2{%k5}{z}", 0x62, 0xf1, 0xc5, 0x8d, 0x57, 0x14, 0x01);
    FCML_I32("vxorpd xmm2{k5}{z},xmm7,xmmword ptr [ecx+eax]", 0x62, 0xf1, 0xc5, 0x8d, 0x57, 0x14, 0x01);
    FCML_A64("vxorpd (%r9,%r8),%ymm14,%ymm10{%k4}{z}", 0x62, 0x11, 0x8d, 0xac, 0x57, 0x14, 0x01);
    FCML_I64("vxorpd ymm10{k4}{z},ymm14,ymmword ptr [r9+r8]", 0x62, 0x11, 0x8d, 0xac, 0x57, 0x14, 0x01);
    FCML_A32("vxorpd (%ecx,%eax),%ymm7,%ymm2{%k5}{z}", 0x62, 0xf1, 0xc5, 0xad, 0x57, 0x14, 0x01);
    FCML_I32("vxorpd ymm2{k5}{z},ymm7,ymmword ptr [ecx+eax]", 0x62, 0xf1, 0xc5, 0xad, 0x57, 0x14, 0x01);
    FCML_A64("vxorpd (%r9,%r8),%zmm14,%zmm10{%k4}{z}", 0x62, 0x11, 0x8d, 0xcc, 0x57, 0x14, 0x01);
    FCML_I64("vxorpd zmm10{k4}{z},zmm14,zmmword ptr [r9+r8]", 0x62, 0x11, 0x8d, 0xcc, 0x57, 0x14, 0x01);
    FCML_A32("vxorpd (%ecx,%eax),%zmm7,%zmm2{%k5}{z}", 0x62, 0xf1, 0xc5, 0xcd, 0x57, 0x14, 0x01);
    FCML_I32("vxorpd zmm2{k5}{z},zmm7,zmmword ptr [ecx+eax]", 0x62, 0xf1, 0xc5, 0xcd, 0x57, 0x14, 0x01);
    /* {k} */
    FCML_A64("vxorpd (%r9,%r8),%xmm14,%xmm10{%k4}", 0x62, 0x11, 0x8d, 0x0c, 0x57, 0x14, 0x01);
    FCML_I64("vxorpd xmm10{k4},xmm14,xmmword ptr [r9+r8]", 0x62, 0x11, 0x8d, 0x0c, 0x57, 0x14, 0x01);
    FCML_A32("vxorpd (%ecx,%eax),%xmm7,%xmm2{%k5}", 0x62, 0xf1, 0xc5, 0x0d, 0x57, 0x14, 0x01);
    FCML_I32("vxorpd xmm2{k5},xmm7,xmmword ptr [ecx+eax]", 0x62, 0xf1, 0xc5, 0x0d, 0x57, 0x14, 0x01);
    FCML_A64("vxorpd (%r9,%r8),%ymm14,%ymm10{%k4}", 0x62, 0x11, 0x8d, 0x2c, 0x57, 0x14, 0x01);
    FCML_I64("vxorpd ymm10{k4},ymm14,ymmword ptr [r9+r8]", 0x62, 0x11, 0x8d, 0x2c, 0x57, 0x14, 0x01);
    FCML_A32("vxorpd (%ecx,%eax),%ymm7,%ymm2{%k5}", 0x62, 0xf1, 0xc5, 0x2d, 0x57, 0x14, 0x01);
    FCML_I32("vxorpd ymm2{k5},ymm7,ymmword ptr [ecx+eax]", 0x62, 0xf1, 0xc5, 0x2d, 0x57, 0x14, 0x01);
    FCML_A64("vxorpd (%r9,%r8),%zmm14,%zmm10{%k4}", 0x62, 0x11, 0x8d, 0x4c, 0x57, 0x14, 0x01);
    FCML_I64("vxorpd zmm10{k4},zmm14,zmmword ptr [r9+r8]", 0x62, 0x11, 0x8d, 0x4c, 0x57, 0x14, 0x01);
    FCML_A32("vxorpd (%ecx,%eax),%zmm7,%zmm2{%k5}", 0x62, 0xf1, 0xc5, 0x4d, 0x57, 0x14, 0x01);
    FCML_I32("vxorpd zmm2{k5},zmm7,zmmword ptr [ecx+eax]", 0x62, 0xf1, 0xc5, 0x4d, 0x57, 0x14, 0x01);
    /* bcast */
    FCML_I64("vxorpd zmm31,zmm21,mmword ptr [rsi]{1to8}", 0x62, 0x61, 0xd5, 0x50, 0x57, 0x3e);
    FCML_A64("vxorpd (%rsi){1to8},%zmm21,%zmm31", 0x62, 0x61, 0xd5, 0x50, 0x57, 0x3e);
    FCML_I64("vxorpd ymm31,ymm21,mmword ptr [rsi]{1to4}", 0x62, 0x61, 0xd5, 0x30, 0x57, 0x3e);
    FCML_A64("vxorpd (%rsi){1to4},%ymm21,%ymm31", 0x62, 0x61, 0xd5, 0x30, 0x57, 0x3e);
    FCML_I64("vxorpd xmm31,xmm21,mmword ptr [rsi]{1to2}", 0x62, 0x61, 0xd5, 0x10, 0x57, 0x3e);
    FCML_A64("vxorpd (%rsi){1to2},%xmm21,%xmm31", 0x62, 0x61, 0xd5, 0x10, 0x57, 0x3e);
    FCML_A32("vxorpd (%esi){1to8},%zmm2,%zmm1", 0x62, 0xf1, 0xed, 0x58, 0x57, 0x0e);
    FCML_I32("vxorpd zmm1,zmm2,mmword ptr [esi]{1to8}", 0x62, 0xf1, 0xed, 0x58, 0x57, 0x0e);
    /* {k}{z}{bcast} */
    FCML_A64("vxorpd (%rsi){1to4},%ymm21,%ymm31{%k7}{z}", 0x62, 0x61, 0xd5, 0xb7, 0x57, 0x3e);
    FCML_I64("vxorpd ymm31{k7}{z},ymm21,mmword ptr [rsi]{1to4}", 0x62, 0x61, 0xd5, 0xb7, 0x57, 0x3e);
    /* {bcast} disp8 */
    FCML_I32("vxorpd zmm1,zmm2,mmword ptr [esp+00000040h]{1to8}", 0x62, 0xf1, 0xed, 0x58, 0x57, 0x4c, 0x24, 0x08);
    FCML_A32("vxorpd 0x00000040(%esp){1to8},%zmm2,%zmm1", 0x62, 0xf1, 0xed, 0x58, 0x57, 0x4c, 0x24, 0x08);
    FCML_I64("vxorpd zmm1,zmm2,mmword ptr [rsp+0000000000000040h]{1to8}", 0x62, 0xf1, 0xed, 0x58, 0x57, 0x4c, 0x24, 0x08);
    FCML_A64("vxorpd 0x0000000000000040(%rsp){1to8},%zmm2,%zmm1", 0x62, 0xf1, 0xed, 0x58, 0x57, 0x4c, 0x24, 0x08);
    FCML_I32("vxorpd ymm1,ymm2,mmword ptr [esp+00000040h]{1to4}", 0x62, 0xf1, 0xed, 0x38, 0x57, 0x4c, 0x24, 0x08);
    FCML_A32("vxorpd 0x00000040(%esp){1to4},%ymm2,%ymm1", 0x62, 0xf1, 0xed, 0x38, 0x57, 0x4c, 0x24, 0x08);
    FCML_I64("vxorpd ymm1,ymm2,mmword ptr [rsp+0000000000000040h]{1to4}", 0x62, 0xf1, 0xed, 0x38, 0x57, 0x4c, 0x24, 0x08);
    FCML_A64("vxorpd 0x0000000000000040(%rsp){1to4},%ymm2,%ymm1", 0x62, 0xf1, 0xed, 0x38, 0x57, 0x4c, 0x24, 0x08);
    FCML_I32("vxorpd xmm1,xmm2,mmword ptr [esp+00000040h]{1to2}", 0x62, 0xf1, 0xed, 0x18, 0x57, 0x4c, 0x24, 0x08);
    FCML_A32("vxorpd 0x00000040(%esp){1to2},%xmm2,%xmm1", 0x62, 0xf1, 0xed, 0x18, 0x57, 0x4c, 0x24, 0x08);
    FCML_I64("vxorpd xmm1,xmm2,mmword ptr [rsp+0000000000000040h]{1to2}", 0x62, 0xf1, 0xed, 0x18, 0x57, 0x4c, 0x24, 0x08);
    FCML_A64("vxorpd 0x0000000000000040(%rsp){1to2},%xmm2,%xmm1", 0x62, 0xf1, 0xed, 0x18, 0x57, 0x4c, 0x24, 0x08);
}

void fcml_tf_instruction_XORPS(void) {
    FCML_I64( "xorps xmm0,xmmword ptr [rax+0000000000000020h]", 0x0F, 0x57, 0x40, 0x20 );
    FCML_I32( "xorps xmm0,xmmword ptr [eax+00000020h]", 0x0F, 0x57, 0x40, 0x20 );
    FCML_A64( "xorps 0x0000000000000020(%rax),%xmm0", 0x0f, 0x57, 0x40, 0x20 );
    /* xmm1, xmm2, m128 */
    FCML_A64_M("vxorps (%rax),%xmm7,%xmm15", 2, FCML_MI(0x62, 0x71, 0x44, 0x08, 0x57, 0x38), FCML_MI(0xc5, 0x40, 0x57, 0x38));
    FCML_I64_M("vxorps xmm15,xmm7,xmmword ptr [rax]", 2, FCML_MI(0x62, 0x71, 0x44, 0x08, 0x57, 0x38), FCML_MI(0xc5, 0x40, 0x57, 0x38));
    FCML_A32_M("vxorps (%eax),%xmm6,%xmm7", 2, FCML_MI(0x62, 0xf1, 0x4c, 0x08, 0x57, 0x38), FCML_MI(0xc5, 0xc8, 0x57, 0x38));
    FCML_I32_M("vxorps xmm7,xmm6,xmmword ptr [eax]", 2, FCML_MI(0x62, 0xf1, 0x4c, 0x08, 0x57, 0x38), FCML_MI(0xc5, 0xc8, 0x57, 0x38));
    /* ymm1, ymm2, m256 */
    FCML_A64_M("vxorps (%rax),%ymm7,%ymm15", 2, FCML_MI(0x62, 0x71, 0x44, 0x28, 0x57, 0x38), FCML_MI(0xc5, 0x44, 0x57, 0x38));
    FCML_I64_M("vxorps ymm15,ymm7,ymmword ptr [rax]", 2, FCML_MI(0x62, 0x71, 0x44, 0x28, 0x57, 0x38), FCML_MI(0xc5, 0x44, 0x57, 0x38));
    FCML_A32_M("vxorps (%eax),%ymm5,%ymm7", 2, FCML_MI(0x62, 0xf1, 0x54, 0x28, 0x57, 0x38), FCML_MI(0xc5, 0xd4, 0x57, 0x38));
    FCML_I32_M("vxorps ymm7,ymm5,ymmword ptr [eax]", 2, FCML_MI(0x62, 0xf1, 0x54, 0x28, 0x57, 0x38), FCML_MI(0xc5, 0xd4, 0x57, 0x38));
    /* zmm1, zmm2, m512 */
    FCML_A64("vxorps (%rax),%zmm7,%zmm15", 0x62, 0x71, 0x44, 0x48, 0x57, 0x38);
    FCML_I64("vxorps zmm15,zmm7,zmmword ptr [rax]", 0x62, 0x71, 0x44, 0x48, 0x57, 0x38);
    FCML_A32("vxorps (%eax),%zmm3,%zmm7", 0x62, 0xf1, 0x64, 0x48, 0x57, 0x38);
    FCML_I32("vxorps zmm7,zmm3,zmmword ptr [eax]", 0x62, 0xf1, 0x64, 0x48, 0x57, 0x38);
    /* xmm1, xmm2, xmm3 */
    FCML_A64_M("vxorps %xmm1,%xmm7,%xmm15", 2, FCML_MI(0x62, 0x71, 0x44, 0x08, 0x57, 0xf9), FCML_MI(0xc5, 0x40, 0x57, 0xf9));
    FCML_I64_M("vxorps xmm15,xmm7,xmm1", 2, FCML_MI(0x62, 0x71, 0x44, 0x08, 0x57, 0xf9), FCML_MI(0xc5, 0x40, 0x57, 0xf9));
    FCML_A32_M("vxorps %xmm1,%xmm2,%xmm7", 2, FCML_MI(0x62, 0xf1, 0x6c, 0x08, 0x57, 0xf9), FCML_MI(0xc5, 0xe8, 0x57, 0xf9));
    FCML_I32_M("vxorps xmm7,xmm2,xmm1", 2, FCML_MI(0x62, 0xf1, 0x6c, 0x08, 0x57, 0xf9), FCML_MI(0xc5, 0xe8, 0x57, 0xf9));
    /* ymm1, ymm2, ymm3 */
    FCML_A64_M("vxorps %ymm6,%ymm7,%ymm14", 2, FCML_MI(0x62, 0x71, 0x44, 0x28, 0x57, 0xf6), FCML_MI(0xc5, 0x44, 0x57, 0xf6));
    FCML_I64_M("vxorps ymm14,ymm7,ymm6", 2, FCML_MI(0x62, 0x71, 0x44, 0x28, 0x57, 0xf6), FCML_MI(0xc5, 0x44, 0x57, 0xf6));
    FCML_A32_M("vxorps %ymm5,%ymm3,%ymm6", 2, FCML_MI(0x62, 0xf1, 0x64, 0x28, 0x57, 0xf5), FCML_MI(0xc5, 0xe4, 0x57, 0xf5));
    FCML_I32_M("vxorps ymm6,ymm3,ymm5", 2, FCML_MI(0x62, 0xf1, 0x64, 0x28, 0x57, 0xf5), FCML_MI(0xc5, 0xe4, 0x57, 0xf5));
    /* zmm1, zmm2, zmm3 */
    FCML_A64("vxorps %zmm4,%zmm15,%zmm6", 0x62, 0xf1, 0x04, 0x48, 0x57, 0xf4);
    FCML_I64("vxorps zmm6,zmm15,zmm4", 0x62, 0xf1, 0x04, 0x48, 0x57, 0xf4);
    FCML_A32("vxorps %zmm4,%zmm6,%zmm6", 0x62, 0xf1, 0x4c, 0x48, 0x57, 0xf4);
    FCML_I32("vxorps zmm6,zmm6,zmm4", 0x62, 0xf1, 0x4c, 0x48, 0x57, 0xf4);
    /* disp8 */
    FCML_I32("vxorps zmm1,zmm2,zmmword ptr [esp+00000200h]", 0x62, 0xf1, 0x6c, 0x48, 0x57, 0x4c, 0x24, 0x08);
    FCML_A32("vxorps 0x00000200(%esp),%zmm2,%zmm1", 0x62, 0xf1, 0x6c, 0x48, 0x57, 0x4c, 0x24, 0x08);
    FCML_I64("vxorps zmm1,zmm2,zmmword ptr [rsp+0000000000000200h]", 0x62, 0xf1, 0x6c, 0x48, 0x57, 0x4c, 0x24, 0x08);
    FCML_A64("vxorps 0x0000000000000200(%rsp),%zmm2,%zmm1", 0x62, 0xf1, 0x6c, 0x48, 0x57, 0x4c, 0x24, 0x08);
    FCML_I32_M("vxorps ymm1,ymm2,ymmword ptr [esp+00000100h]", 2, FCML_MI(0x62, 0xf1, 0x6c, 0x28, 0x57, 0x4c, 0x24, 0x08), FCML_MI(0xc5, 0xec, 0x57, 0x8c, 0x24, 0x00, 0x01, 0x00, 0x00));
    FCML_A32_M("vxorps 0x00000100(%esp),%ymm2,%ymm1", 2, FCML_MI(0x62, 0xf1, 0x6c, 0x28, 0x57, 0x4c, 0x24, 0x08), FCML_MI(0xc5, 0xec, 0x57, 0x8c, 0x24, 0x00, 0x01, 0x00, 0x00));
    FCML_I64_M("vxorps ymm1,ymm2,ymmword ptr [rsp+0000000000000100h]", 2, FCML_MI(0x62, 0xf1, 0x6c, 0x28, 0x57, 0x4c, 0x24, 0x08), FCML_MI(0xc5, 0xec, 0x57, 0x8c, 0x24, 0x00, 0x01, 0x00, 0x00));
    FCML_A64_M("vxorps 0x0000000000000100(%rsp),%ymm2,%ymm1", 2, FCML_MI(0x62, 0xf1, 0x6c, 0x28, 0x57, 0x4c, 0x24, 0x08), FCML_MI(0xc5, 0xec, 0x57, 0x8c, 0x24, 0x00, 0x01, 0x00, 0x00));
    FCML_I32_M("vxorps xmm1,xmm2,xmmword ptr [esp+00000080h]", 2, FCML_MI(0x62, 0xf1, 0x6c, 0x08, 0x57, 0x4c, 0x24, 0x08), FCML_MI(0xc5, 0xe8, 0x57, 0x8c, 0x24, 0x80, 0x00, 0x00, 0x00));
    FCML_A32_M("vxorps 0x00000080(%esp),%xmm2,%xmm1", 2, FCML_MI(0x62, 0xf1, 0x6c, 0x08, 0x57, 0x4c, 0x24, 0x08), FCML_MI(0xc5, 0xe8, 0x57, 0x8c, 0x24, 0x80, 0x00, 0x00, 0x00));
    FCML_I64_M("vxorps xmm1,xmm2,xmmword ptr [rsp+0000000000000080h]", 2, FCML_MI(0x62, 0xf1, 0x6c, 0x08, 0x57, 0x4c, 0x24, 0x08), FCML_MI(0xc5, 0xe8, 0x57, 0x8c, 0x24, 0x80, 0x00, 0x00, 0x00));
    FCML_A64_M("vxorps 0x0000000000000080(%rsp),%xmm2,%xmm1", 2, FCML_MI(0x62, 0xf1, 0x6c, 0x08, 0x57, 0x4c, 0x24, 0x08), FCML_MI(0xc5, 0xe8, 0x57, 0x8c, 0x24, 0x80, 0x00, 0x00, 0x00));
    /* {k}{z} */
    FCML_A64("vxorps (%r9,%r8),%xmm14,%xmm10{%k4}{z}", 0x62, 0x11, 0x0c, 0x8c, 0x57, 0x14, 0x01);
    FCML_I64("vxorps xmm10{k4}{z},xmm14,xmmword ptr [r9+r8]", 0x62, 0x11, 0x0c, 0x8c, 0x57, 0x14, 0x01);
    FCML_A32("vxorps (%ecx,%eax),%xmm7,%xmm2{%k5}{z}", 0x62, 0xf1, 0x44, 0x8d, 0x57, 0x14, 0x01);
    FCML_I32("vxorps xmm2{k5}{z},xmm7,xmmword ptr [ecx+eax]", 0x62, 0xf1, 0x44, 0x8d, 0x57, 0x14, 0x01);
    FCML_A64("vxorps (%r9,%r8),%ymm14,%ymm10{%k4}{z}", 0x62, 0x11, 0x0c, 0xac, 0x57, 0x14, 0x01);
    FCML_I64("vxorps ymm10{k4}{z},ymm14,ymmword ptr [r9+r8]", 0x62, 0x11, 0x0c, 0xac, 0x57, 0x14, 0x01);
    FCML_A32("vxorps (%ecx,%eax),%ymm7,%ymm2{%k5}{z}", 0x62, 0xf1, 0x44, 0xad, 0x57, 0x14, 0x01);
    FCML_I32("vxorps ymm2{k5}{z},ymm7,ymmword ptr [ecx+eax]", 0x62, 0xf1, 0x44, 0xad, 0x57, 0x14, 0x01);
    FCML_A64("vxorps (%r9,%r8),%zmm14,%zmm10{%k4}{z}", 0x62, 0x11, 0x0c, 0xcc, 0x57, 0x14, 0x01);
    FCML_I64("vxorps zmm10{k4}{z},zmm14,zmmword ptr [r9+r8]", 0x62, 0x11, 0x0c, 0xcc, 0x57, 0x14, 0x01);
    FCML_A32("vxorps (%ecx,%eax),%zmm7,%zmm2{%k5}{z}", 0x62, 0xf1, 0x44, 0xcd, 0x57, 0x14, 0x01);
    FCML_I32("vxorps zmm2{k5}{z},zmm7,zmmword ptr [ecx+eax]", 0x62, 0xf1, 0x44, 0xcd, 0x57, 0x14, 0x01);
    /* {k} */
    FCML_A64("vxorps (%r9,%r8),%xmm14,%xmm10{%k4}", 0x62, 0x11, 0x0c, 0x0c, 0x57, 0x14, 0x01);
    FCML_I64("vxorps xmm10{k4},xmm14,xmmword ptr [r9+r8]", 0x62, 0x11, 0x0c, 0x0c, 0x57, 0x14, 0x01);
    FCML_A32("vxorps (%ecx,%eax),%xmm7,%xmm2{%k5}", 0x62, 0xf1, 0x44, 0x0d, 0x57, 0x14, 0x01);
    FCML_I32("vxorps xmm2{k5},xmm7,xmmword ptr [ecx+eax]", 0x62, 0xf1, 0x44, 0x0d, 0x57, 0x14, 0x01);
    FCML_A64("vxorps (%r9,%r8),%ymm14,%ymm10{%k4}", 0x62, 0x11, 0x0c, 0x2c, 0x57, 0x14, 0x01);
    FCML_I64("vxorps ymm10{k4},ymm14,ymmword ptr [r9+r8]", 0x62, 0x11, 0x0c, 0x2c, 0x57, 0x14, 0x01);
    FCML_A32("vxorps (%ecx,%eax),%ymm7,%ymm2{%k5}", 0x62, 0xf1, 0x44, 0x2d, 0x57, 0x14, 0x01);
    FCML_I32("vxorps ymm2{k5},ymm7,ymmword ptr [ecx+eax]", 0x62, 0xf1, 0x44, 0x2d, 0x57, 0x14, 0x01);
    FCML_A64("vxorps (%r9,%r8),%zmm14,%zmm10{%k4}", 0x62, 0x11, 0x0c, 0x4c, 0x57, 0x14, 0x01);
    FCML_I64("vxorps zmm10{k4},zmm14,zmmword ptr [r9+r8]", 0x62, 0x11, 0x0c, 0x4c, 0x57, 0x14, 0x01);
    FCML_A32("vxorps (%ecx,%eax),%zmm7,%zmm2{%k5}", 0x62, 0xf1, 0x44, 0x4d, 0x57, 0x14, 0x01);
    FCML_I32("vxorps zmm2{k5},zmm7,zmmword ptr [ecx+eax]", 0x62, 0xf1, 0x44, 0x4d, 0x57, 0x14, 0x01);
    /* bcast */
    FCML_I64("vxorps zmm31,zmm21,dword ptr [rsi]{1to16}", 0x62, 0x61, 0x54, 0x50, 0x57, 0x3e);
    FCML_A64("vxorps (%rsi){1to16},%zmm21,%zmm31", 0x62, 0x61, 0x54, 0x50, 0x57, 0x3e);
    FCML_I64("vxorps ymm31,ymm21,dword ptr [rsi]{1to8}", 0x62, 0x61, 0x54, 0x30, 0x57, 0x3e);
    FCML_A64("vxorps (%rsi){1to8},%ymm21,%ymm31", 0x62, 0x61, 0x54, 0x30, 0x57, 0x3e);
    FCML_I64("vxorps xmm31,xmm21,dword ptr [rsi]{1to4}", 0x62, 0x61, 0x54, 0x10, 0x57, 0x3e);
    FCML_A64("vxorps (%rsi){1to4},%xmm21,%xmm31", 0x62, 0x61, 0x54, 0x10, 0x57, 0x3e);
    FCML_A32("vxorps (%esi){1to16},%zmm2,%zmm1", 0x62, 0xf1, 0x6c, 0x58, 0x57, 0x0e);
    FCML_I32("vxorps zmm1,zmm2,dword ptr [esi]{1to16}", 0x62, 0xf1, 0x6c, 0x58, 0x57, 0x0e);
    /* {k}{z}{bcast} */
    FCML_A64("vxorps (%rsi){1to8},%ymm21,%ymm31{%k7}{z}", 0x62, 0x61, 0x54, 0xb7, 0x57, 0x3e);
    FCML_I64("vxorps ymm31{k7}{z},ymm21,dword ptr [rsi]{1to8}", 0x62, 0x61, 0x54, 0xb7, 0x57, 0x3e);
    /* {bcast} disp8 */
    FCML_I32("vxorps zmm1,zmm2,dword ptr [esp+00000020h]{1to16}", 0x62, 0xf1, 0x6c, 0x58, 0x57, 0x4c, 0x24, 0x08);
    FCML_A32("vxorps 0x00000020(%esp){1to16},%zmm2,%zmm1", 0x62, 0xf1, 0x6c, 0x58, 0x57, 0x4c, 0x24, 0x08);
    FCML_I64("vxorps zmm1,zmm2,dword ptr [rsp+0000000000000020h]{1to16}", 0x62, 0xf1, 0x6c, 0x58, 0x57, 0x4c, 0x24, 0x08);
    FCML_A64("vxorps 0x0000000000000020(%rsp){1to16},%zmm2,%zmm1", 0x62, 0xf1, 0x6c, 0x58, 0x57, 0x4c, 0x24, 0x08);
    FCML_I32("vxorps ymm1,ymm2,dword ptr [esp+00000020h]{1to8}", 0x62, 0xf1, 0x6c, 0x38, 0x57, 0x4c, 0x24, 0x08);
    FCML_A32("vxorps 0x00000020(%esp){1to8},%ymm2,%ymm1", 0x62, 0xf1, 0x6c, 0x38, 0x57, 0x4c, 0x24, 0x08);
    FCML_I64("vxorps ymm1,ymm2,dword ptr [rsp+0000000000000020h]{1to8}", 0x62, 0xf1, 0x6c, 0x38, 0x57, 0x4c, 0x24, 0x08);
    FCML_A64("vxorps 0x0000000000000020(%rsp){1to8},%ymm2,%ymm1", 0x62, 0xf1, 0x6c, 0x38, 0x57, 0x4c, 0x24, 0x08);
    FCML_I32("vxorps xmm1,xmm2,dword ptr [esp+00000020h]{1to4}", 0x62, 0xf1, 0x6c, 0x18, 0x57, 0x4c, 0x24, 0x08);
    FCML_A32("vxorps 0x00000020(%esp){1to4},%xmm2,%xmm1", 0x62, 0xf1, 0x6c, 0x18, 0x57, 0x4c, 0x24, 0x08);
    FCML_I64("vxorps xmm1,xmm2,dword ptr [rsp+0000000000000020h]{1to4}", 0x62, 0xf1, 0x6c, 0x18, 0x57, 0x4c, 0x24, 0x08);
    FCML_A64("vxorps 0x0000000000000020(%rsp){1to4},%xmm2,%xmm1", 0x62, 0xf1, 0x6c, 0x18, 0x57, 0x4c, 0x24, 0x08);
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



