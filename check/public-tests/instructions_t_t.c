/*
 * FCML - Free Code Manipulation Library.
 * Copyright (C) 2010-2014 Slawomir Wojtasiak
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
#include "instructions_t_t.h"
#include "instructions_base_t.h"

fcml_bool fcml_tf_instructions_t_suite_init(void) {
	return FCML_TRUE;
}

fcml_bool fcml_tf_instructions_t_suite_cleanup(void) {
	return FCML_TRUE;
}

void fcml_tf_instruction_TEST(void) {

    FCML_I32_M( "test al,20h", 2, FCML_MI( 0xf6, 0xc0, 0x20 ), FCML_MI( 0xa8, 0x20 ) );
    FCML_I64_M( "test al,20h", 2, FCML_MI( 0xf6, 0xc0, 0x20 ), FCML_MI( 0xa8, 0x20 ) );

    FCML_A64( "testb $0x20,%al", 0xf6, 0xc0, 0x20 );

    FCML_I32_M( "test eax,00104020h", 2, FCML_MI( 0xf7, 0xc0, 0x20, 0x40, 0x10, 0x00 ), FCML_MI( 0xa9, 0x20, 0x40, 0x10, 0x00 ) );
    FCML_I32_M( "test ax,0020h", 2, FCML_MI( 0x66, 0xf7, 0xc0, 0x20, 0x00 ), FCML_MI( 0x66, 0xa9, 0x20, 0x00 ) );

    FCML_A64_M( "test $0x0000000000104020,%rax", 2, FCML_MI( 0x48, 0xf7, 0xc0, 0x20, 0x40, 0x10, 0x00 ), FCML_MI( 0x48, 0xa9, 0x20, 0x40, 0x10, 0x00 ) );
    FCML_A64_M( "test $0x4020,%ax", 2, FCML_MI( 0x66, 0xf7, 0xc0, 0x20, 0x40 ), FCML_MI( 0x66, 0xa9, 0x20, 0x40 ) );
    FCML_A64_M( "test $0x00104020,%eax", 2, FCML_MI( 0xf7, 0xc0, 0x20, 0x40, 0x10, 0x00 ), FCML_MI( 0xa9, 0x20, 0x40, 0x10, 0x00 ) );

    FCML_I64_M( "test rax,0ffffffffff104020h", 2, FCML_MI( 0x48, 0xf7, 0xc0, 0x20, 0x40, 0x10, 0xff ), FCML_MI( 0x48, 0xa9, 0x20, 0x40, 0x10, 0xff ) );

    FCML_I32( "test byte ptr [eax],0ffh", 0xF6, 0x00, 0xFF );
    FCML_I64_D( "test byte ptr [rax],0ffh", 0x48, 0xF6, 0x00, 0xFF );

    FCML_A64( "testb $0xff,(%rax)", 0xf6, 0x00, 0xff );

    FCML_I32( "test dword ptr [eax],0ff001040h", 0xF7, 0x00, 0x40, 0x10, 0x00, 0xFF );
    FCML_I32( "test word ptr [eax],0ff00h", 0x66, 0xF7, 0x00, 0x00, 0xff );

    FCML_A64( "testl $0xff001040,(%rax)", 0xf7, 0x00, 0x40, 0x10, 0x00, 0xff );
    FCML_A64( "testw $0x1040,(%rax)", 0x66, 0xf7, 0x00, 0x40, 0x10 );

    FCML_A64( "testq $0x0000000000001040,(%rax)", 0x48, 0xf7, 0x00, 0x40, 0x10, 0x00, 0x00 );

    FCML_I64( "test qword ptr [rax],0000000011ff1040h", 0x48, 0xF7, 0x00, 0x40, 0x10, 0xFF, 0x11 );

    FCML_I32( "test byte ptr [eax],al", 0x84, 0x00 );
    FCML_I64_D( "test byte ptr [rax],al", 0x48, 0x84, 0x00 );

    FCML_I32( "test word ptr [eax],ax", 0x66, 0x85, 0x00 );
    FCML_I64( "test qword ptr [rax],rax", 0x48, 0x85, 0x00 );
}

void fcml_tf_instruction_TZCNT(void) {

    FCML_I32( "tzcnt eax,dword ptr [eax]", 0xF3, 0x0F, 0xBC, 0x00 );
    FCML_I32( "tzcnt ax,word ptr [eax]", 0x66, 0xF3, 0x0F, 0xBC, 0x00 );
    FCML_I32( "tzcnt ax,ax", 0x66, 0xF3, 0x0F, 0xBC, 0xC0 );
    FCML_I64( "tzcnt rax,qword ptr [rax]", 0xF3, 0x48, 0x0F, 0xBC, 0x00 );

    FCML_A64( "tzcnt (%rax),%eax", 0xf3, 0x0f, 0xbc, 0x00 );
    FCML_A64( "tzcnt (%rax),%ax", 0x66, 0xf3, 0x0f, 0xbc, 0x00 );
    FCML_A64( "tzcnt %ax,%ax", 0x66, 0xf3, 0x0f, 0xbc, 0xc0 );
    FCML_A64( "tzcnt (%rax),%rax", 0xf3, 0x48, 0x0f, 0xbc, 0x00 );
}

void fcml_tf_instruction_TZMSK(void) {

    FCML_I32( "tzmsk ebx,dword ptr [eax]", 0x8F, 0xE9, 0x60, 0x01, 0x20 );
    FCML_I32( "tzmsk ebx,eax", 0x8F, 0xE9, 0x60, 0x01, 0xE0 );

    FCML_I64( "tzmsk rbx,qword ptr [rax]", 0x8F, 0xE9, 0xE0, 0x01, 0x20 );
    FCML_I64( "tzmsk rbx,rax", 0x8F, 0xE9, 0xE0, 0x01, 0xE0 );

    FCML_A64( "tzmsk (%rax),%ebx", 0x8f, 0xe9, 0x60, 0x01, 0x20 );
    FCML_A64( "tzmsk %eax,%ebx", 0x8f, 0xe9, 0x60, 0x01, 0xe0 );
    FCML_A64( "tzmsk (%rax),%rbx", 0x8f, 0xe9, 0xe0, 0x01, 0x20 );
    FCML_A64( "tzmsk %rax,%rbx", 0x8f, 0xe9, 0xe0, 0x01, 0xe0 );
}

void fcml_tf_instruction_T1MSKC(void) {

    FCML_I32( "t1mskc ebx,dword ptr [eax]", 0x8F, 0xE9, 0x60, 0x01, 0x38 );
    FCML_I32( "t1mskc ebx,eax", 0x8F, 0xE9, 0x60, 0x01, 0xF8 );

    FCML_I64( "t1mskc rbx,qword ptr [rax]", 0x8F, 0xE9, 0xE0, 0x01, 0x38 );
    FCML_I64( "t1mskc rbx,rax", 0x8F, 0xE9, 0xE0, 0x01, 0xF8 );

    FCML_A64( "t1mskc (%rax),%ebx", 0x8f, 0xe9, 0x60, 0x01, 0x38 );
    FCML_A64( "t1mskc %eax,%ebx", 0x8f, 0xe9, 0x60, 0x01, 0xf8 );
    FCML_A64( "t1mskc (%rax),%rbx", 0x8f, 0xe9, 0xe0, 0x01, 0x38 );
    FCML_A64( "t1mskc %rax,%rbx", 0x8f, 0xe9, 0xe0, 0x01, 0xf8 );
}

fcml_stf_test_case fctl_ti_instructions_t[] = {
	{ "fcml_tf_instruction_TEST", fcml_tf_instruction_TEST },
	{ "fcml_tf_instruction_TZCNT", fcml_tf_instruction_TZCNT },
	{ "fcml_tf_instruction_TZMSK", fcml_tf_instruction_TZMSK },
	{ "fcml_tf_instruction_T1MSKC", fcml_tf_instruction_T1MSKC },
	FCML_STF_NULL_TEST
};

fcml_stf_test_suite fctl_si_instructions_t = {
	"suite-fctl_ti_instructions_t", fcml_tf_instructions_t_suite_init, fcml_tf_instructions_t_suite_cleanup, fctl_ti_instructions_t
};

