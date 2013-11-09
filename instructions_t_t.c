/*
 * instructions.c
 *
 *  Created on: 01-06-2013
 *      Author: tAs
 */

#include "fcml_env.h"
#include "fcml_assembler.h"
#include "instructions_t_t.h"

int fcml_tf_instructions_t_suite_init(void) {
	return 0;
}

int fcml_tf_instructions_t_suite_cleanup(void) {
	return 0;
}

void fcml_tf_instruction_TEST(void) {
    // A8 ib TEST AL, imm8 I Valid Valid AND imm8 with AL; set SF, ZF, PF according to result.
    FCML_I32_M( "test al,20h", 2, FCML_MI( 0xf6, 0xc0, 0x20 ), FCML_MI( 0xa8, 0x20 ) );
    FCML_I64_M( "test al,20h", 2, FCML_MI( 0xf6, 0xc0, 0x20 ), FCML_MI( 0xa8, 0x20 ) );
    // A9 iw TEST AX, imm16 I Valid Valid AND imm16 with AX; set SF, ZF, PF according to result.
    // A9 id TEST EAX, imm32 I Valid Valid AND imm32 with EAX; set SF, ZF, PF according to result.
    FCML_I32_M( "test eax,00104020h", 2, FCML_MI( 0xf7, 0xc0, 0x20, 0x40, 0x10, 0x00 ), FCML_MI( 0xa9, 0x20, 0x40, 0x10, 0x00 ) );
    FCML_I32_M( "test ax,0020h", 2, FCML_MI( 0x66, 0xf7, 0xc0, 0x20, 0x00 ), FCML_MI( 0x66, 0xa9, 0x20, 0x00 ) );
    // REX.W + A9 id TEST RAX, imm32 I Valid N.E. AND imm32 sign-extended to 64-bits with RAX; set SF, ZF, PF according to result.
    FCML_I64_M( "test rax,0ffffffffff104020h", 2, FCML_MI( 0x48, 0xf7, 0xc0, 0x20, 0x40, 0x10, 0xff ), FCML_MI( 0x48, 0xa9, 0x20, 0x40, 0x10, 0xff ) );
    // F6 /0 ib TEST r/m8, imm8 MI Valid Valid AND imm8 with r/m8; set SF, ZF, PF according to result.
    // REX + F6 /0 ib TEST r/m8*, imm8 MI Valid N.E. AND imm8 with r/m8; set SF, ZF, PF according to result.
    FCML_I32( "test byte ptr [eax],0ffh", 0xF6, 0x00, 0xFF );
    FCML_I64_D( "test byte ptr [rax],0ffh", 0x48, 0xF6, 0x00, 0xFF );
    // F7 /0 iw TEST r/m16, imm16 MI Valid Valid AND imm16 with r/m16; set SF, ZF, PF according to result.
    // F7 /0 id TEST r/m32, imm32 MI Valid Valid AND imm32 with r/m32; set SF, ZF, PF according to result.
    FCML_I32( "test dword ptr [eax],0ff001040h", 0xF7, 0x00, 0x40, 0x10, 0x00, 0xFF );
    FCML_I32( "test word ptr [eax],0ff00h", 0x66, 0xF7, 0x00, 0x00, 0xff );
    // REX.W + F7 /0 id TEST r/m64, imm32 MI Valid N.E. AND imm32 sign-extended to 64-bits with r/m64; set SF, ZF, PF according to result.
    FCML_I64( "test qword ptr [rax],0000000011ff1040h", 0x48, 0xF7, 0x00, 0x40, 0x10, 0xFF, 0x11 );
    // 84 /r TEST r/m8, r8 MR Valid Valid AND r8 with r/m8; set SF, ZF, PF according to result.
    // REX + 84 /r TEST r/m8*, r8* MR Valid N.E. AND r8 with r/m8; set SF, ZF, PF according to result.
    FCML_I32( "test byte ptr [eax],al", 0x84, 0x00 );
    FCML_I64_D( "test byte ptr [rax],al", 0x48, 0x84, 0x00 );
    // 85 /r TEST r/m16, r16 MR Valid Valid AND r16 with r/m16; set SF, ZF, PF according to result.
    // 85 /r TEST r/m32, r32 MR Valid Valid AND r32 with r/m32; set SF, ZF, PF according to result.
    // REX.W + 85 /r TEST r/m64, r64 MR Valid N.E. AND r64 with r/m64; set SF, ZF, PF according to result.
    FCML_I32( "test word ptr [eax],ax", 0x66, 0x85, 0x00 );
    FCML_I64( "test qword ptr [rax],rax", 0x48, 0x85, 0x00 );
}

void fcml_tf_instruction_TZCNT(void) {
    // F3 0F BC /r TZCNT r16, r/m16
    // F3 0F BC /r TZCNT r32, r/m32
    // REX.W + F3 0F BC /r TZCNT r64, r/m64
    FCML_I32( "tzcnt eax,dword ptr [eax]", 0xF3, 0x0F, 0xBC, 0x00 );
    FCML_I32( "tzcnt ax,word ptr [eax]", 0x66, 0xF3, 0x0F, 0xBC, 0x00 );
    FCML_I32( "tzcnt ax,ax", 0x66, 0xF3, 0x0F, 0xBC, 0xC0 );
    FCML_I64( "tzcnt rax,qword ptr [rax]", 0xF3, 0x48, 0x0F, 0xBC, 0x00 );
}

void fcml_tf_instruction_TZMSK(void) {
    // TZMSK reg32, reg/mem32 8F RXB.09 0.dest.0.00 01 /4
    FCML_I32( "tzmsk ebx,dword ptr [eax]", 0x8F, 0xE9, 0x60, 0x01, 0x20 );
    FCML_I32( "tzmsk ebx,eax", 0x8F, 0xE9, 0x60, 0x01, 0xE0 );
    // TZMSK reg64, reg/mem64 8F RXB.09 1.dest.0.00 01 /4
    FCML_I64( "tzmsk rbx,qword ptr [rax]", 0x8F, 0xE9, 0xE0, 0x01, 0x20 );
    FCML_I64( "tzmsk rbx,rax", 0x8F, 0xE9, 0xE0, 0x01, 0xE0 );
}

void fcml_tf_instruction_T1MSKC(void) {
    // T1MSKC reg32, reg/mem32 8F RXB.09 0.dest.0.00 01 /7
    FCML_I32( "t1mskc ebx,dword ptr [eax]", 0x8F, 0xE9, 0x60, 0x01, 0x38 );
    FCML_I32( "t1mskc ebx,eax", 0x8F, 0xE9, 0x60, 0x01, 0xF8 );
    // T1MSKC reg64, reg/mem64 8F RXB.09 1.dest.0.00 01 /7
    FCML_I64( "t1mskc rbx,qword ptr [rax]", 0x8F, 0xE9, 0xE0, 0x01, 0x38 );
    FCML_I64( "t1mskc rbx,rax", 0x8F, 0xE9, 0xE0, 0x01, 0xF8 );
}

CU_TestInfo fctl_ti_instructions_t[] = {
    { "fcml_tf_instruction_TEST", fcml_tf_instruction_TEST },
    { "fcml_tf_instruction_TZCNT", fcml_tf_instruction_TZCNT },
    { "fcml_tf_instruction_TZMSK", fcml_tf_instruction_TZMSK },
    { "fcml_tf_instruction_T1MSKC", fcml_tf_instruction_T1MSKC },
    CU_TEST_INFO_NULL,
};

CU_SuiteInfo fctl_si_instructions_t[] = {
    { "suite-fctl_ti_instructions_t", fcml_tf_instructions_t_suite_init, fcml_tf_instructions_t_suite_cleanup, fctl_ti_instructions_t },
    CU_SUITE_INFO_NULL,
};
