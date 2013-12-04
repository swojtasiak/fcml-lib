/*
 * instructions.c
 *
 *  Created on: 01-06-2013
 *      Author: tAs
 */

#include "fcml_env.h"
#include "fcml_assembler.h"
#include "instructions_i_t.h"

int fcml_tf_instructions_i_suite_init(void) {
	return 0;
}

int fcml_tf_instructions_i_suite_cleanup(void) {
	return 0;
}

void fcml_tf_instruction_IDIV(void) {
    // F6 /7 IDIV r/m8 A Valid Valid Signed divide AX by r/m8,with result stored in: AL Quotient, AH Remainder.
    // REX + F6 /7 IDIV r/m8* A Valid N.E. Signed divide AX by r/m8, with result stored in AL Quotient, AH Remainder.
    FCML_I32( "idiv ax,byte ptr [ebx]", 0xF6, 0x3B );
    FCML_I32( "idiv ax,byte ptr [ebx]", 0x66, 0xF6, 0x3B );
    FCML_I64( "idiv ax,sil", 0x40, 0xF6, 0xFE );
    FCML_I64( "idiv ax,dh", 0xF6, 0xFE );
    // F7 /7 IDIV r/m16 A Valid Valid Signed divide DX:AX by r/m16, with result stored in AX Quotient, DX Remainder.
    // F7 /7 IDIV r/m32 A Valid Valid Signed divide EDX:EAX by r/m32, with result stored in EAX Quotient, EDX Remainder.
    // REX.W + F7 /7 IDIV r/m64 A Valid N.E. Signed divide RDX:RAX by r/m64, with result stored in RAX Quotient, RDX Remainder.
    FCML_I32( "idiv eax,dword ptr [ebx]", 0xF7, 0x3B );
    FCML_I32( "idiv ax,word ptr [ebx]", 0x66, 0xF7, 0x3B );
    FCML_I64( "idiv rax,rsi", 0x48, 0xF7, 0xFE );
    FCML_I64( "idiv eax,esi", 0xF7, 0xFE );
    // GAS
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
    // F6 /5 IMUL r/m8* A Valid Valid AX AL r/m byte.
    FCML_I32( "imul byte ptr [eax+00000020h]", 0xF6, 0x68, 0x20 );
    FCML_I32( "imul byte ptr [eax+00000020h]", 0x66, 0xF6, 0x68, 0x20 );
    FCML_I64( "imul byte ptr [rax+0000000000000020h]", 0xF6, 0x68, 0x20 );
    FCML_A64( "imulb 0x0000000000000020(%rax)", 0xf6, 0x68, 0x20 );
    // F7 /5 IMUL r/m16 A Valid Valid DX:AX AX r/m word.
    // F7 /5 IMUL r/m32 A Valid Valid EDX:EAX EAX r/m32.
    // REX.W + F7 /5 IMUL r/m64 A Valid N.E. RDX:RAX RAX r/m64.
    FCML_I32( "imul dword ptr [eax+00000020h]", 0xF7, 0x68, 0x20 );
    FCML_I32( "imul word ptr [eax+00000020h]", 0x66, 0xF7, 0x68, 0x20 );
    FCML_I64( "imul dword ptr [rax+0000000000000020h]", 0xF7, 0x68, 0x20 );
    FCML_I64( "imul word ptr [rax+0000000000000020h]", 0x66, 0xF7, 0x68, 0x20 );
    FCML_I64( "imul qword ptr [rax+0000000000000020h]", 0x48, 0xF7, 0x68, 0x20 );
    FCML_A64( "imull 0x0000000000000020(%rax)", 0xf7, 0x68, 0x20 );
    FCML_A64( "imulw 0x0000000000000020(%rax)", 0x66, 0xf7, 0x68, 0x20 );
    FCML_A64( "imulq 0x0000000000000020(%rax)", 0x48, 0xf7, 0x68, 0x20 );
    // 0F AF /r IMUL r16, r/m16 B Valid Valid word register word register r/m16.
    // 0F AF /r IMUL r32, r/m32 B Valid Valid doubleword register doubleword register r/m32.
    // REX.W + 0F AF /r IMUL r64, r/m64 B Valid N.E. Quadword register Quadword register r/m64.
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
    // 6B /r ib IMUL r16, r/m16, imm8 C Valid Valid word register r/m16 sign-extended immediate byte.
    // 6B /r ib IMUL r32, r/m32, imm8 C Valid Valid doubleword register r/m32 sign-extended immediate byte.
    // REX.W + 6B /r ib IMUL r64, r/m64, imm8 C Valid N.E. Quadword register r/m64 sign-extended immediate byte.
    FCML_I32_M( "imul ebp,dword ptr [eax+00000020h],00000040h", 2, FCML_MI( 0x6B, 0x68, 0x20, 0x40 ), FCML_MI( 0x69, 0x68, 0x20, 0x40, 0x00, 0x00, 0x00 ) );
    FCML_I32_M( "imul bp,word ptr [eax+00000020h],0040h", 2, FCML_MI( 0x66, 0x6B, 0x68, 0x20, 0x40 ), FCML_MI( 0x66, 0x69, 0x68, 0x20, 0x40, 0x00  ) );
    FCML_I64_M( "imul ebp,dword ptr [rax+0000000000000020h],00000040h", 2, FCML_MI( 0x6B, 0x68, 0x20, 0x40 ), FCML_MI( 0x69, 0x68, 0x20, 0x40, 0x00, 0x00, 0x00 ) );
    FCML_I64_M( "imul bp,word ptr [rax+0000000000000020h],0040h", 2, FCML_MI( 0x66, 0x6B, 0x68, 0x20, 0x40 ), FCML_MI( 0x66, 0x69, 0x68, 0x20, 0x40, 0x00 ) );
    FCML_I64_M( "imul rbp,qword ptr [rax+0000000000000020h],0000000000000040h", 2, FCML_MI( 0x48, 0x6B, 0x68, 0x20, 0x40 ), FCML_MI( 0x48, 0x69, 0x68, 0x20, 0x40, 0x00, 0x00, 0x00 ) );
    FCML_A64_M( "imulq $0x0000000000000040,0x0000000000000020(%rax),%rbp", 2, FCML_MI( 0x48, 0x6B, 0x68, 0x20, 0x40 ), FCML_MI( 0x48, 0x69, 0x68, 0x20, 0x40, 0x00, 0x00, 0x00 ) );
    // 69 /r iw IMUL r16, r/m16, imm16 C Valid Valid word register r/m16 immediate word.
    // 69 /r id IMUL r32, r/m32, imm32 C Valid Valid doubleword register r/m32 immediate doubleword.
    // REX.W + 69 /r id IMUL r64, r/m64, imm32 C Valid N.E. Quadword register r/m64 immediate doubleword.
    FCML_I32( "imul ebp,dword ptr [eax+00000020h],70605040h", 0x69, 0x68, 0x20, 0x40, 0x50, 0x60, 0x70 );
    FCML_I32( "imul bp,word ptr [eax+00000020h],5040h", 0x66, 0x69, 0x68, 0x20, 0x40, 0x50 );
    FCML_I64( "imul ebp,dword ptr [rax+0000000000000020h],70605040h", 0x69, 0x68, 0x20, 0x40, 0x50, 0x60, 0x70 );
    FCML_I64( "imul bp,word ptr [rax+0000000000000020h],5040h", 0x66, 0x69, 0x68, 0x20, 0x40, 0x50 );
    FCML_A64( "imulw $0x5040,0x0000000000000020(%rax),%bp", 0x66, 0x69, 0x68, 0x20, 0x40, 0x50 );
    FCML_A64_A( "imul $0x5040,0x0000000000000020(%rax),%bp", 0x66, 0x69, 0x68, 0x20, 0x40, 0x50 );
    // In this case value is not sign extended to 64 bits, so can not be treated as signed!
    FCML_I64_A_FAILED( "imul rbp,qword ptr [rax+0000000000000020h],0ffffffffff605040h", 0x48, 0x69, 0x68, 0x20, 0x40, 0x50, 0x60, 0xFF );
    FCML_I64_D( "imul rbp,qword ptr [rax+0000000000000020h],0ff605040h", 0x48, 0x69, 0x68, 0x20, 0x40, 0x50, 0x60, 0xFF );
    FCML_A64( "imulq $0xff605040,0x0000000000000020(%rax),%rbp", 0x48, 0x69, 0x68, 0x20, 0x40, 0x50, 0x60, 0xff );
}

void fcml_tf_instruction_IN(void) {
    // E4 ib IN AL, imm8 A Valid Valid Input byte from imm8 I/O port address into AL.
    // E5 ib IN AX, imm8 A Valid Valid Input word from imm8 I/O port address into AX.
    // E5 ib IN EAX, imm8 A Valid Valid Input dword from imm8 I/O port address into EAX.
    FCML_I32( "in al,20h", 0xE4, 0x20 );
    FCML_I64( "in al,20h", 0x66, 0xE4, 0x20 );
    FCML_I32( "in eax,20h", 0xE5, 0x20 );
    FCML_I32( "in ax,20h", 0x66, 0xE5, 0x20 );
    FCML_I64_D( "in eax,20h", 0x48, 0xE5, 0x20 );
    // EC IN AL,DX B Valid Valid Input byte from I/O port in DX into AL.
    // ED IN AX,DX B Valid Valid Input word from I/O port in DX into AX.
    // ED IN EAX,DX B Valid Valid Input doubleword from I/O port in DX into EAX.
    FCML_I32( "in al,dx", 0xEC );
    FCML_I64( "in al,dx", 0x66, 0xEC );
    FCML_I32( "in eax,dx", 0xED );
    FCML_I32( "in ax,dx", 0x66, 0xED );
    FCML_I64_D( "in eax,dx", 0x48, 0xED );
    // GAS
    FCML_A64( "in $0x20,%al", 0xe4, 0x20 );
    FCML_A64( "in $0x20,%eax", 0xe5, 0x20 );
    FCML_A64( "in $0x20,%ax", 0x66, 0xe5, 0x20 );
    // TODO: Niespójnosć z GAS. GAS ubiera to w nawiasy: in   (%dx),%eax pewnie bedzie trzeba dodac dodatkwy tryb adrrsowania, tak aby sie assemblowaly obie formy i tyle.
    // Gas także dopuszcza obie formy, wiec bedzie ok a w zasadzie juz jest OK, ale dodajmy 2 formy.
    FCML_A64( "in %dx,%al", 0xec );
}

void fcml_tf_instruction_INC(void) {
    // FE /0 INC r/m8 A Valid Valid Increment r/m byte by 1.
    // REX + FE /0 INC r/m8* A Valid N.E. Increment r/m byte by 1.
    FCML_I32_M( "inc eax", 2, FCML_MI( 0x40 ), FCML_MI( 0xff, 0xc0 ) );
    FCML_I32_M( "inc ax", 2, FCML_MI( 0x66, 0x40 ), FCML_MI( 0x66, 0xff, 0xc0 ) );
    FCML_I32_M( "inc ecx", 2, FCML_MI( 0x41 ), FCML_MI( 0xff, 0xc1 ) );
    FCML_I32_M( "inc cx", 2, FCML_MI( 0x66, 0x41 ), FCML_MI( 0x66, 0xff, 0xc1 ) );
    // FF /0 INC r/m16 A Valid Valid Increment r/m word by 1.
    // FF /0 INC r/m32 A Valid Valid Increment r/m doubleword by 1.
    // REX.W + FF /0 INC r/m64 A Valid N.E. Increment r/m quadword by 1.
    FCML_I32( "lock inc byte ptr [eax]", 0xF0, 0xFE, 0x00 );
    FCML_I32( "xacquire lock inc byte ptr [eax]", 0xF2, 0xF0, 0xFE, 0x00 );
    FCML_I32( "xrelease lock inc byte ptr [eax]", 0xF3, 0xF0, 0xFE, 0x00 );
    FCML_I64( "inc byte ptr [rax]", 0xFE, 0x00 );
    FCML_I64_D( "inc byte ptr [rax]", 0x48, 0xFE, 0x00 );
    FCML_I64( "inc spl", 0x40, 0xFE, 0xC4 );
    // 40+ rw** INC r16 B N.E. Valid Increment word register by 1.
    // 40+ rd INC r32 B N.E. Valid Increment doubleword register by 1.
    FCML_I32( "lock inc dword ptr [ebx]", 0xF0, 0xFF, 0x03 );
    FCML_I32( "xacquire lock inc dword ptr [ebx]", 0xF2, 0xF0, 0xFF, 0x03 );
    FCML_I32( "xrelease lock inc dword ptr [ebx]", 0xF3, 0xF0, 0xFF, 0x03 );
    FCML_I32( "inc word ptr [ebx]", 0x66, 0xFF, 0x03 );
    FCML_I64( "inc dword ptr [rbx]", 0xFF, 0x03 );
    FCML_I64( "inc qword ptr [rbx]", 0x48, 0xFF, 0x03 );
    FCML_I64_D( "inc word ptr [rbx]", 0x66, 0x40, 0xFF, 0x03 );
    FCML_I64( "inc r12", 0x49, 0xFF, 0xC4 );
}

void fcml_tf_instruction_INS(void) {
    // 6C INS m8, DX A Valid Valid Input byte from I/O port specified in DX into memory location specified in ES:(E)DI or RDI.*
    FCML_I32( "rep ins byte ptr [edi],dx", 0xF3, 0x6c );
    FCML_I64( "ins byte ptr [rdi],dx", 0x6c );
    FCML_I64( "ins byte ptr [edi],dx", 0x67, 0x6c );
    // 6D INS m16, DX A Valid Valid Input word from I/O port specified in DX into memory location specified in ES:(E)DI or RDI.1
    // 6D INS m32, DX A Valid Valid Input doubleword from I/O port specified in DX into memory location specified in ES:(E)DI or RDI.1
    FCML_I32( "rep ins dword ptr [edi],dx", 0xF3, 0x6D );
    FCML_I64( "ins dword ptr [rdi],dx", 0x6D );
    FCML_I64( "ins dword ptr [edi],dx", 0x67, 0x6D );
    FCML_I64( "ins word ptr [edi],dx", 0x66, 0x67, 0x6D );
    FCML_I64_D( "ins dword ptr [rdi],dx", 0x48, 0x6D );
    FCML_I32_A( "insb", 0x6c );
    FCML_I32_A( "insw", 0x66, 0x6D );
    FCML_I32_A( "insd", 0x6D );
}

void fcml_tf_instruction_INSERTPS(void) {
    FCML_I32( "insertps xmm4,dword ptr [eax],40h", 0x66, 0x0F, 0x3A, 0x21, 0x20, 0x40 );
    FCML_I64( "insertps xmm4,dword ptr [rax],40h", 0x66, 0x0F, 0x3A, 0x21, 0x20, 0x40 );
    // VEX.NDS.128.66.0F3A 21 /r ib VINSERTPS xmm1,xmm2,xmm3/m32,imm8
    FCML_I64( "vinsertps xmm8,xmm14,dword ptr [r8],20h", 0xC4, 0x43, 0x09, 0x21, 0x00, 0x20 );
    FCML_I32( "vinsertps xmm0,xmm6,dword ptr [eax],20h", 0xC4, 0xE3, 0x49, 0x21, 0x00, 0x20 );
    FCML_I32( "vinsertps xmm0,xmm6,xmm0,20h", 0xC4, 0xE3, 0x49, 0x21, 0xC0, 0x20 );
}

void fcml_tf_instruction_INSERTQ(void) {
    // INSERTQ xmm1, xmm2, imm8, imm8 F2 0F 78 /r ib ib
    FCML_I32( "insertq xmm3,xmm2,01h,02h", 0xF2, 0x0F, 0x78, 0xDA, 0x01, 0x02 );
    FCML_I64( "insertq xmm3,xmm2,01h,02h", 0xF2, 0x0F, 0x78, 0xDA, 0x01, 0x02 );
    // INSERTQ xmm1, xmm2 F2 0F 79 /r
    FCML_I32( "insertq xmm3,xmm2", 0xF2, 0x0F, 0x79, 0xDA );
    FCML_I64( "insertq xmm3,xmm2", 0xF2, 0x0F, 0x79, 0xDA );
}

void fcml_tf_instruction_INT(void) {
    FCML_I3264_M( "int 03h", 2, FCML_MI( 0xCC ), FCML_MI( 0xCD, 0x03 ) );
    FCML_I32_M( "int 20h", 2, FCML_MI( 0xcd, 0x20 ), FCML_MI( 0xcc ) );
    FCML_I64_M( "int 20h", 2, FCML_MI( 0xcd, 0x20 ), FCML_MI( 0xcc ) );
    FCML_I64( "into", 0xCE );
    FCML_I32( "into", 0xCE );
}

void fcml_tf_instruction_INVD(void) {
    FCML_I3264( "invd", 0x0F, 0x08 );
}

void fcml_tf_instruction_INVLPG(void) {
    FCML_I32( "invlpg [eax+00000020h]", 0x0F, 0x01, 0x78, 0x20 );
    FCML_I64( "invlpg [rax+0000000000000020h]", 0x0F, 0x01, 0x78, 0x20 );
}

void fcml_tf_instruction_INVLPGA(void) {
    // INVLPGA rAX, ECX 0F 01 DF
    FCML_I32( "invlpga eax,ecx", 0x0F, 0x01, 0xDF );
    FCML_I32( "invlpga ax,ecx", 0x67, 0x0F, 0x01, 0xDF );
    FCML_I64( "invlpga rax,ecx", 0x0F, 0x01, 0xDF );
    FCML_I64( "invlpga eax,ecx", 0x67, 0x0F, 0x01, 0xDF );
}

void fcml_tf_instruction_INVPCID(void) {
    FCML_I32( "invpcid edx,oword ptr [eax]", 0x66, 0x0F, 0x38, 0x82, 0x10 );
    FCML_I64( "invpcid rdx,oword ptr [rax]", 0x66, 0x0F, 0x38, 0x82, 0x10 );
}

void fcml_tf_instruction_IRET(void) {
    FCML_I32( "iretd", 0xCF );
    FCML_I32( "iret", 0x66, 0xCF );
    FCML_I64( "iretd", 0xCF );
    FCML_I64( "iret", 0x66, 0xCF );
    FCML_I64( "iretq", 0x48, 0xCF );
}

void fcml_tf_instruction_INVEPT(void) {
    FCML_I32( "invept esp,oword ptr [eax]", 0x66, 0x0F, 0x38, 0x80, 0x20 );
    FCML_I64( "invept rsp,oword ptr [rax]", 0x66, 0x0F, 0x38, 0x80, 0x20 );
    FCML_I32_A( "invept esp,[eax]", 0x66, 0x0F, 0x38, 0x80, 0x20 );
	FCML_I64_A( "invept rsp,[rax]", 0x66, 0x0F, 0x38, 0x80, 0x20 );
    // GAS
    FCML_A64( "invept (%rax),%rsp", 0x66, 0x0f, 0x38, 0x80, 0x20 );
    FCML_A64( "invept (%rax),%rsp", 0x66, 0x0f, 0x38, 0x80, 0x20 );
}

void fcml_tf_instruction_INVVPID(void) {
    FCML_I32( "invvpid esp,oword ptr [eax]", 0x66, 0x0F, 0x38, 0x81, 0x20 );
    FCML_I64( "invvpid rsp,oword ptr [rax]", 0x66, 0x0F, 0x38, 0x81, 0x20 );
    FCML_I32_A( "invvpid esp,[eax]", 0x66, 0x0F, 0x38, 0x81, 0x20 );
	FCML_I64_A( "invvpid rsp,[rax]", 0x66, 0x0F, 0x38, 0x81, 0x20 );
	// GAS
	FCML_A64( "invvpid (%rax),%rsp", 0x66, 0x0f, 0x38, 0x81, 0x20 );
	FCML_A64( "invvpid (%rax),%rsp", 0x66, 0x0f, 0x38, 0x81, 0x20 );
}

CU_TestInfo fctl_ti_instructions_i[] = {
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
    CU_TEST_INFO_NULL,
};

CU_SuiteInfo fctl_si_instructions_i[] = {
    { "suite-fctl_ti_instructions_i", fcml_tf_instructions_i_suite_init, fcml_tf_instructions_i_suite_cleanup, fctl_ti_instructions_i },
    CU_SUITE_INFO_NULL,
};
