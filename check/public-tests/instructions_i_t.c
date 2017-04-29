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
#include "instructions_i_t.h"
#include "instructions_base_t.h"

fcml_bool fcml_tf_instructions_i_suite_init(void) {
    return FCML_TRUE;
}

fcml_bool fcml_tf_instructions_i_suite_cleanup(void) {
    return FCML_TRUE;
}

void fcml_tf_instruction_IDIV(void) {

    FCML_I32( "idiv ax,byte ptr [ebx]", 0xF6, 0x3B );
    FCML_I32( "idiv ax,byte ptr [ebx]", 0x66, 0xF6, 0x3B );
    FCML_I64( "idiv ax,sil", 0x40, 0xF6, 0xFE );
    FCML_I64( "idiv ax,dh", 0xF6, 0xFE );

    FCML_I32( "idiv eax,dword ptr [ebx]", 0xF7, 0x3B );
    FCML_I32( "idiv ax,word ptr [ebx]", 0x66, 0xF7, 0x3B );
    FCML_I64( "idiv rax,rsi", 0x48, 0xF7, 0xFE );
    FCML_I64( "idiv eax,esi", 0xF7, 0xFE );

    FCML_A64( "idivb (%rbx),%ax", 0xf6, 0x3b );
    FCML_A64( "idivb %dh,%ax", 0xf6, 0xfe );
    FCML_A64( "idivl (%rbx),%eax", 0xf7, 0x3b );
    FCML_A64( "idivw (%rbx),%ax", 0x66, 0xf7, 0x3b );
    FCML_A64( "idivl %esi,%eax", 0xf7, 0xfe );
    FCML_A64_A( "idiv %esi,%eax", 0xf7, 0xfe );
    FCML_A64( "idivq %rsi,%rax", 0x48, 0xf7, 0xfe );
    FCML_A64_A( "idiv %rsi,%rax", 0x48, 0xf7, 0xfe );
}

void fcml_tf_instruction_IMUL(void) {

    FCML_I32( "imul byte ptr [eax+00000020h]", 0xF6, 0x68, 0x20 );
    FCML_I32( "imul byte ptr [eax+00000020h]", 0x66, 0xF6, 0x68, 0x20 );
    FCML_I64( "imul byte ptr [rax+0000000000000020h]", 0xF6, 0x68, 0x20 );
    FCML_A64( "imulb 0x0000000000000020(%rax)", 0xf6, 0x68, 0x20 );

    FCML_I32( "imul dword ptr [eax+00000020h]", 0xF7, 0x68, 0x20 );
    FCML_I32( "imul word ptr [eax+00000020h]", 0x66, 0xF7, 0x68, 0x20 );
    FCML_I64( "imul dword ptr [rax+0000000000000020h]", 0xF7, 0x68, 0x20 );
    FCML_I64( "imul word ptr [rax+0000000000000020h]", 0x66, 0xF7, 0x68, 0x20 );
    FCML_I64( "imul qword ptr [rax+0000000000000020h]", 0x48, 0xF7, 0x68, 0x20 );
    FCML_A64( "imull 0x0000000000000020(%rax)", 0xf7, 0x68, 0x20 );
    FCML_A64( "imulw 0x0000000000000020(%rax)", 0x66, 0xf7, 0x68, 0x20 );
    FCML_A64( "imulq 0x0000000000000020(%rax)", 0x48, 0xf7, 0x68, 0x20 );

    FCML_I32( "imul ebp,dword ptr [eax+00000020h]", 0x0F, 0xAF, 0x68, 0x20 );
    FCML_I32( "imul bp,word ptr [eax+00000020h]", 0x66, 0x0F, 0xAF, 0x68, 0x20 );
    FCML_I64( "imul ebp,dword ptr [rax+0000000000000020h]", 0x0F, 0xAF, 0x68, 0x20 );
    FCML_I64( "imul bp,word ptr [rax+0000000000000020h]", 0x66, 0x0F, 0xAF, 0x68, 0x20 );
    FCML_I64( "imul rbp,qword ptr [rax+0000000000000020h]", 0x48, 0x0F, 0xAF, 0x68, 0x20 );
    FCML_A64( "imull 0x0000000000000020(%rax),%ebp", 0x0f, 0xaf, 0x68, 0x20 );
    FCML_A64( "imulw 0x0000000000000020(%rax),%bp", 0x66, 0x0f, 0xaf, 0x68, 0x20 );
    FCML_A64( "imulq 0x0000000000000020(%rax),%rbp", 0x48, 0x0f, 0xaf, 0x68, 0x20 );
    FCML_A64_A( "imul 0x0000000000000020(%rax),%ebp", 0x0f, 0xaf, 0x68, 0x20 );
    FCML_A64_A( "imul 0x0000000000000020(%rax),%bp", 0x66, 0x0f, 0xaf, 0x68, 0x20 );
    FCML_A64_A( "imul 0x0000000000000020(%rax),%rbp", 0x48, 0x0f, 0xaf, 0x68, 0x20 );

    FCML_I32_M( "imul ebp,dword ptr [eax+00000020h],00000040h", 2, FCML_MI( 0x6B, 0x68, 0x20, 0x40 ), FCML_MI( 0x69, 0x68, 0x20, 0x40, 0x00, 0x00, 0x00 ) );
    FCML_I32_M( "imul bp,word ptr [eax+00000020h],0040h", 2, FCML_MI( 0x66, 0x6B, 0x68, 0x20, 0x40 ), FCML_MI( 0x66, 0x69, 0x68, 0x20, 0x40, 0x00  ) );
    FCML_I64_M( "imul ebp,dword ptr [rax+0000000000000020h],00000040h", 2, FCML_MI( 0x6B, 0x68, 0x20, 0x40 ), FCML_MI( 0x69, 0x68, 0x20, 0x40, 0x00, 0x00, 0x00 ) );
    FCML_I64_M( "imul bp,word ptr [rax+0000000000000020h],0040h", 2, FCML_MI( 0x66, 0x6B, 0x68, 0x20, 0x40 ), FCML_MI( 0x66, 0x69, 0x68, 0x20, 0x40, 0x00 ) );
    FCML_I64_M( "imul rbp,qword ptr [rax+0000000000000020h],0000000000000040h", 2, FCML_MI( 0x48, 0x6B, 0x68, 0x20, 0x40 ), FCML_MI( 0x48, 0x69, 0x68, 0x20, 0x40, 0x00, 0x00, 0x00 ) );
    FCML_A64_M( "imulq $0x0000000000000040,0x0000000000000020(%rax),%rbp", 2, FCML_MI( 0x48, 0x6B, 0x68, 0x20, 0x40 ), FCML_MI( 0x48, 0x69, 0x68, 0x20, 0x40, 0x00, 0x00, 0x00 ) );

    FCML_I32( "imul ebp,dword ptr [eax+00000020h],70605040h", 0x69, 0x68, 0x20, 0x40, 0x50, 0x60, 0x70 );
    FCML_I32( "imul bp,word ptr [eax+00000020h],5040h", 0x66, 0x69, 0x68, 0x20, 0x40, 0x50 );
    FCML_I64( "imul ebp,dword ptr [rax+0000000000000020h],70605040h", 0x69, 0x68, 0x20, 0x40, 0x50, 0x60, 0x70 );
    FCML_I64( "imul bp,word ptr [rax+0000000000000020h],5040h", 0x66, 0x69, 0x68, 0x20, 0x40, 0x50 );
    FCML_A64( "imulw $0x5040,0x0000000000000020(%rax),%bp", 0x66, 0x69, 0x68, 0x20, 0x40, 0x50 );
    FCML_A64_A( "imul $0x5040,0x0000000000000020(%rax),%bp", 0x66, 0x69, 0x68, 0x20, 0x40, 0x50 );
    /* In this case value is not sign extended to 64 bits, so can not be treated as signed!
     */
    FCML_I64_A_FAILED( "imul rbp,qword ptr [rax+0000000000000020h],0ffffffffff605040h", 0x48, 0x69, 0x68, 0x20, 0x40, 0x50, 0x60, 0xFF );
    FCML_I64_D( "imul rbp,qword ptr [rax+0000000000000020h],0ff605040h", 0x48, 0x69, 0x68, 0x20, 0x40, 0x50, 0x60, 0xFF );
    FCML_A64( "imulq $0xff605040,0x0000000000000020(%rax),%rbp", 0x48, 0x69, 0x68, 0x20, 0x40, 0x50, 0x60, 0xff );
}

void fcml_tf_instruction_IN(void) {

    FCML_I32( "in al,20h", 0xE4, 0x20 );
    FCML_I64( "in al,20h", 0x66, 0xE4, 0x20 );
    FCML_I32( "in eax,20h", 0xE5, 0x20 );
    FCML_I32( "in ax,20h", 0x66, 0xE5, 0x20 );
    FCML_I64_D( "in eax,20h", 0x48, 0xE5, 0x20 );

    FCML_I32( "in al,dx", 0xEC );
    FCML_I64( "in al,dx", 0x66, 0xEC );
    FCML_I32( "in eax,dx", 0xED );
    FCML_I32( "in ax,dx", 0x66, 0xED );
    FCML_I64_D( "in eax,dx", 0x48, 0xED );

    FCML_A64( "in $0x20,%al", 0xe4, 0x20 );
    FCML_A64( "in $0x20,%eax", 0xe5, 0x20 );
    FCML_A64( "in $0x20,%ax", 0x66, 0xe5, 0x20 );
    /* TODO: Gas also supports following form: "in (%dx),%eax" so it should be supported in the future.
     */
    FCML_A64( "in %dx,%al", 0xec );
}

void fcml_tf_instruction_INC(void) {

    FCML_I32_M( "inc eax", 2, FCML_MI( 0x40 ), FCML_MI( 0xff, 0xc0 ) );
    FCML_I32_M( "inc ax", 2, FCML_MI( 0x66, 0x40 ), FCML_MI( 0x66, 0xff, 0xc0 ) );
    FCML_I32_M( "inc ecx", 2, FCML_MI( 0x41 ), FCML_MI( 0xff, 0xc1 ) );
    FCML_I32_M( "inc cx", 2, FCML_MI( 0x66, 0x41 ), FCML_MI( 0x66, 0xff, 0xc1 ) );
    FCML_I32( "lock inc dword ptr [ebx]", 0xF0, 0xFF, 0x03 );
    FCML_I32( "xacquire lock inc dword ptr [ebx]", 0xF2, 0xF0, 0xFF, 0x03 );
    FCML_I32( "xrelease lock inc dword ptr [ebx]", 0xF3, 0xF0, 0xFF, 0x03 );
    FCML_I32( "inc word ptr [ebx]", 0x66, 0xFF, 0x03 );
    FCML_I64( "inc dword ptr [rbx]", 0xFF, 0x03 );
    FCML_I64( "inc qword ptr [rbx]", 0x48, 0xFF, 0x03 );
    FCML_I64_D( "inc word ptr [rbx]", 0x66, 0x40, 0xFF, 0x03 );
    FCML_I64( "inc r12", 0x49, 0xFF, 0xC4 );

    FCML_A64( "incw %ax", 0x66, 0xff, 0xc0 );
    FCML_A64_A( "inc %ax", 0x66, 0xff, 0xc0 );
    FCML_A64( "incl (%rax)", 0xff, 0x00 );
    FCML_A64( "incw (%rax)", 0x66, 0xff, 0x00 );
    FCML_A64( "incq (%rax)", 0x48, 0xff, 0x00 );

    FCML_I32( "lock inc byte ptr [eax]", 0xF0, 0xFE, 0x00 );
    FCML_I32( "xacquire lock inc byte ptr [eax]", 0xF2, 0xF0, 0xFE, 0x00 );
    FCML_I32( "xrelease lock inc byte ptr [eax]", 0xF3, 0xF0, 0xFE, 0x00 );
    FCML_I64( "inc byte ptr [rax]", 0xFE, 0x00 );
    FCML_I64_D( "inc byte ptr [rax]", 0x48, 0xFE, 0x00 );
    FCML_I64( "inc spl", 0x40, 0xFE, 0xC4 );

    FCML_A64( "lock incb (%rax)", 0xf0, 0xfe, 0x00 );
    FCML_A64( "incb (%rax)", 0xfe, 0x00 );
    FCML_A64( "incb %spl", 0x40, 0xfe, 0xc4 );
    FCML_A64_A( "inc %spl", 0x40, 0xfe, 0xc4 );

    FCML_I32_M( "inc eax", 2, FCML_MI( 0x40 ), FCML_MI( 0xff, 0xc0 ) );
    FCML_I32_M( "inc ecx", 2, FCML_MI( 0x41 ), FCML_MI( 0xff, 0xc1 ) );
    FCML_I32_M( "inc dx", 2, FCML_MI( 0x66, 0x42 ), FCML_MI( 0x66, 0xff, 0xc2 ) );

    FCML_A32_M( "inc %eax", 2, FCML_MI( 0x40 ), FCML_MI( 0xff, 0xc0 ) );
    FCML_A32_M( "inc %ecx", 2, FCML_MI( 0x41 ), FCML_MI( 0xff, 0xc1 ) );
    FCML_A32_M( "inc %dx", 2, FCML_MI( 0x66, 0x42 ), FCML_MI( 0x66, 0xff, 0xc2 ) );
}

void fcml_tf_instruction_INS(void) {

    FCML_I32( "rep ins byte ptr [edi],dx", 0xF3, 0x6c );
    FCML_I64( "ins byte ptr [rdi],dx", 0x6c );
    FCML_I64( "ins byte ptr [edi],dx", 0x67, 0x6c );

    FCML_I32( "rep ins dword ptr [edi],dx", 0xF3, 0x6D );
    FCML_I64( "ins dword ptr [rdi],dx", 0x6D );
    FCML_I64( "ins dword ptr [edi],dx", 0x67, 0x6D );
    FCML_I64( "ins word ptr [edi],dx", 0x66, 0x67, 0x6D );
    FCML_I64_D( "ins dword ptr [rdi],dx", 0x48, 0x6D );
    FCML_I32_A( "insb", 0x6c );
    FCML_I32_A( "insw", 0x66, 0x6D );
    FCML_I32_A( "insd", 0x6D );

    FCML_A64( "insb %dx,(%rdi)", 0x6c );
    FCML_A64( "insb %dx,(%edi)", 0x67, 0x6c );
    FCML_A64( "insl %dx,(%rdi)", 0x6d );
    FCML_A64( "insl %dx,(%edi)", 0x67, 0x6d );
    FCML_A64( "insw %dx,(%edi)", 0x66, 0x67, 0x6d );
}

void fcml_tf_instruction_INSERTPS(void) {
    FCML_I32( "insertps xmm4,dword ptr [eax],40h", 0x66, 0x0F, 0x3A, 0x21, 0x20, 0x40 );
    FCML_I64( "insertps xmm4,dword ptr [rax],40h", 0x66, 0x0F, 0x3A, 0x21, 0x20, 0x40 );

    FCML_I64( "vinsertps xmm8,xmm14,dword ptr [r8],20h", 0xC4, 0x43, 0x09, 0x21, 0x00, 0x20 );
    FCML_I32( "vinsertps xmm0,xmm6,dword ptr [eax],20h", 0xC4, 0xE3, 0x49, 0x21, 0x00, 0x20 );
    FCML_I32( "vinsertps xmm0,xmm6,xmm0,20h", 0xC4, 0xE3, 0x49, 0x21, 0xC0, 0x20 );

    FCML_A64( "insertps $0x40,(%rax),%xmm4", 0x66, 0x0f, 0x3a, 0x21, 0x20, 0x40 );
    FCML_A64( "vinsertps $0x20,(%r8),%xmm14,%xmm8", 0xc4, 0x43, 0x09, 0x21, 0x00, 0x20 );
}

void fcml_tf_instruction_INSERTQ(void) {

    FCML_I32( "insertq xmm3,xmm2,01h,02h", 0xF2, 0x0F, 0x78, 0xDA, 0x01, 0x02 );
    FCML_I64( "insertq xmm3,xmm2,01h,02h", 0xF2, 0x0F, 0x78, 0xDA, 0x01, 0x02 );

    FCML_I32( "insertq xmm3,xmm2", 0xF2, 0x0F, 0x79, 0xDA );
    FCML_I64( "insertq xmm3,xmm2", 0xF2, 0x0F, 0x79, 0xDA );

    FCML_A64( "insertq $0x02,$0x01,%xmm2,%xmm3", 0xf2, 0x0f, 0x78, 0xda, 0x01, 0x02 );
    FCML_A64( "insertq %xmm2,%xmm3", 0xf2, 0x0f, 0x79, 0xda );
}

void fcml_tf_instruction_INT(void) {
    FCML_I3264( "int3", 0xCC );
    FCML_I3264( "int 20h", 0xcd, 0x20 );
    FCML_I32( "into", 0xCE );
    FCML_I64_FAILED( "into", 0xCE );

    FCML_A64( "int3", 0xcc );
    FCML_A64( "int $0x20", 0xcd, 0x20 );
    FCML_A32( "into", 0xCE );
}

void fcml_tf_instruction_INVD(void) {
    FCML_I3264( "invd", 0x0F, 0x08 );
}

void fcml_tf_instruction_INVLPG(void) {
    FCML_I32( "invlpg [eax+00000020h]", 0x0F, 0x01, 0x78, 0x20 );
    FCML_I64( "invlpg [rax+0000000000000020h]", 0x0F, 0x01, 0x78, 0x20 );

    FCML_A64( "invlpg 0x0000000000000020(%rax)", 0x0f, 0x01, 0x78, 0x20 );
}

void fcml_tf_instruction_INVLPGA(void) {

    FCML_I32( "invlpga eax,ecx", 0x0F, 0x01, 0xDF );
    FCML_I32( "invlpga ax,ecx", 0x67, 0x0F, 0x01, 0xDF );
    FCML_I64( "invlpga rax,ecx", 0x0F, 0x01, 0xDF );
    FCML_I64( "invlpga eax,ecx", 0x67, 0x0F, 0x01, 0xDF );

    FCML_A64( "invlpga %ecx,%rax", 0x0f, 0x01, 0xdf );
    FCML_A64_A( "invlpga", 0x0f, 0x01, 0xdf );
}

void fcml_tf_instruction_INVPCID(void) {
    FCML_I32( "invpcid edx,oword ptr [eax]", 0x66, 0x0F, 0x38, 0x82, 0x10 );
    FCML_I64( "invpcid rdx,oword ptr [rax]", 0x66, 0x0F, 0x38, 0x82, 0x10 );

    FCML_A64( "invpcid (%rax),%rdx", 0x66, 0x0f, 0x38, 0x82, 0x10 );
    FCML_A64( "invpcid (%rax),%rdx", 0x66, 0x0f, 0x38, 0x82, 0x10 );
}

void fcml_tf_instruction_IRET(void) {
    FCML_I32( "iretd", 0xCF );
    FCML_I32( "iret", 0x66, 0xCF );
    FCML_I64( "iretd", 0xCF );
    FCML_I64( "iret", 0x66, 0xCF );
    FCML_I64( "iretq", 0x48, 0xCF );

    FCML_A64( "iret", 0xcf );
    FCML_A64( "iretw", 0x66, 0xcf );
    FCML_A64( "iretq", 0x48, 0xcf );
}

void fcml_tf_instruction_INVEPT(void) {
    FCML_I32( "invept esp,oword ptr [eax]", 0x66, 0x0F, 0x38, 0x80, 0x20 );
    FCML_I64( "invept rsp,oword ptr [rax]", 0x66, 0x0F, 0x38, 0x80, 0x20 );
    FCML_I32_A( "invept esp,[eax]", 0x66, 0x0F, 0x38, 0x80, 0x20 );
    FCML_I64_A( "invept rsp,[rax]", 0x66, 0x0F, 0x38, 0x80, 0x20 );

    FCML_A64( "invept (%rax),%rsp", 0x66, 0x0f, 0x38, 0x80, 0x20 );
}

void fcml_tf_instruction_INVVPID(void) {
    FCML_I32( "invvpid esp,oword ptr [eax]", 0x66, 0x0F, 0x38, 0x81, 0x20 );
    FCML_I64( "invvpid rsp,oword ptr [rax]", 0x66, 0x0F, 0x38, 0x81, 0x20 );
    FCML_I32_A( "invvpid esp,[eax]", 0x66, 0x0F, 0x38, 0x81, 0x20 );
    FCML_I64_A( "invvpid rsp,[rax]", 0x66, 0x0F, 0x38, 0x81, 0x20 );

    FCML_A64( "invvpid (%rax),%rsp", 0x66, 0x0f, 0x38, 0x81, 0x20 );
    FCML_A64( "invvpid (%rax),%rsp", 0x66, 0x0f, 0x38, 0x81, 0x20 );
}

fcml_stf_test_case fctl_ti_instructions_i[] = {
    { "fcml_tf_instruction_IDIV", fcml_tf_instruction_IDIV },
    { "fcml_tf_instruction_IMUL", fcml_tf_instruction_IMUL },
    { "fcml_tf_instruction_IN", fcml_tf_instruction_IN },
    { "fcml_tf_instruction_INC", fcml_tf_instruction_INC },
    { "fcml_tf_instruction_INS", fcml_tf_instruction_INS },
    { "fcml_tf_instruction_INSERTPS", fcml_tf_instruction_INSERTPS },
    { "fcml_tf_instruction_INSERTQ", fcml_tf_instruction_INSERTQ },
    { "fcml_tf_instruction_INT", fcml_tf_instruction_INT },
    { "fcml_tf_instruction_INVD", fcml_tf_instruction_INVD },
    { "fcml_tf_instruction_INVLPG", fcml_tf_instruction_INVLPG },
    { "fcml_tf_instruction_INVLPGA", fcml_tf_instruction_INVLPGA },
    { "fcml_tf_instruction_INVPCID", fcml_tf_instruction_INVPCID },
    { "fcml_tf_instruction_IRET", fcml_tf_instruction_IRET },
    { "fcml_tf_instruction_INVEPT", fcml_tf_instruction_INVEPT },
    { "fcml_tf_instruction_INVVPID", fcml_tf_instruction_INVVPID },
    FCML_STF_NULL_TEST
};

fcml_stf_test_suite fctl_si_instructions_i = {
    "suite-fctl_ti_instructions_i", fcml_tf_instructions_i_suite_init, fcml_tf_instructions_i_suite_cleanup, fctl_ti_instructions_i
};


