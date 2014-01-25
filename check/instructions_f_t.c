/*
 * instructions.c
 *
 *  Created on: 01-06-2013
 *      Author: tAs
 */

#include <fcml_env.h>
#include <fcml_assembler.h>
#include "instructions_e_t.h"
#include "instructions_base_t.h"

void fcml_tf_instructions_f_suite_init(void) {
}

void fcml_tf_instructions_f_suite_cleanup(void) {
}

void fcml_tf_instruction_F2XM1(void) {
    FCML_I3264( "f2xm1", 0xD9, 0xF0 );
    FCML_A64( "f2xm1", 0xd9, 0xf0 );
}

void fcml_tf_instruction_FABS(void) {
    FCML_I3264( "fabs", 0xD9, 0xE1 );
    FCML_A64( "fabs", 0xd9, 0xe1 );
}

void fcml_tf_instruction_FADD(void) {
    FCML_I64( "fadd dword ptr [rax+0000000000000020h]", 0xD8, 0x40, 0x20 );
    FCML_I32( "fadd dword ptr [eax+00000020h]", 0xD8, 0x40, 0x20 );
    FCML_I64( "fadd qword ptr [rax+0000000000000020h]", 0xDC, 0x40, 0x20 );
    FCML_I32( "fadd qword ptr [eax+00000020h]", 0xDC, 0x40, 0x20 );

    FCML_I3264_M( "fadd st(0),st(0)", 2, FCML_MI( 0xD8, 0xC0 ), FCML_MI( 0xdc, 0xc0 ) );
    FCML_I32( "fadd st(0),st(1)", 0xD8, 0xC1 );
    FCML_I32( "fadd st(0),st(2)", 0xD8, 0xC2 );
    FCML_I32( "fadd st(0),st(3)", 0xD8, 0xC3 );
    FCML_I32( "fadd st(0),st(4)", 0xD8, 0xC4 );
    FCML_I32( "fadd st(0),st(5)", 0xD8, 0xC5 );
    FCML_I32( "fadd st(0),st(6)", 0xD8, 0xC6 );
    FCML_I32( "fadd st(0),st(7)", 0xD8, 0xC7 );

    FCML_A64_A( "fadds 0x0000000000000020(%rax)", 0xd8, 0x40, 0x20 );
    FCML_A64_A( "faddl 0x0000000000000020(%rax)", 0xdc, 0x40, 0x20 );
    FCML_A64( "fadd %st(1),%st(0)", 0xd8, 0xc1 );
    FCML_A64( "fadd %st(0),%st(1)", 0xdc, 0xc1 );

    FCML_I64( "fadd st(1),st(0)", 0xDC, 0xC1 );
    FCML_I32( "fadd st(1),st(0)", 0xDC, 0xC1 );

    FCML_I64( "faddp st(1),st(0)", 0xDE, 0xC1 );
    FCML_A64( "faddp %st(0),%st(1)", 0xde, 0xc1 );
    FCML_I32( "faddp st(1),st(0)", 0xDE, 0xC1 );

    FCML_I3264_A( "faddp", 0xDE, 0xC1 );
    FCML_A3264_A( "faddp", 0xDE, 0xC1 );

    FCML_I64( "fiadd dword ptr [rax+0000000000000020h]", 0xDA, 0x40, 0x20 );
    FCML_I32( "fiadd dword ptr [eax+00000020h]", 0xDA, 0x40, 0x20 );
    FCML_I64( "fiadd word ptr [rax+0000000000000020h]", 0xDE, 0x40, 0x20 );
    FCML_I32( "fiadd word ptr [eax+00000020h]", 0xDE, 0x40, 0x20 );
    FCML_A64( "fiaddl 0x0000000000000020(%rax)", 0xda, 0x40, 0x20 );
    FCML_A64( "fiadd 0x0000000000000020(%rax)", 0xde, 0x40, 0x20 );
}

void fcml_tf_instruction_FBLD(void) {
    FCML_I64( "fbld tbyte ptr [rax+0000000000000020h]", 0xDf, 0x60, 0x20 ) ;
    FCML_A64( "fbld 0x0000000000000020(%rax)", 0xdf, 0x60, 0x20 );
    FCML_I32( "fbld tbyte ptr [eax+00000020h]", 0xDf, 0x60, 0x20 );
}

void fcml_tf_instruction_FBSTP(void) {
    FCML_I64( "fbstp tbyte ptr [rax+0000000000000020h]", 0xDf, 0x70, 0x20 ) ;
    FCML_A64( "fbstp 0x0000000000000020(%rax)", 0xdf, 0x70, 0x20 );
    FCML_I32( "fbstp tbyte ptr [eax+00000020h]", 0xDf, 0x70, 0x20 );
}

void fcml_tf_instruction_FCHS(void) {
    FCML_I3264( "fchs", 0xD9, 0xE0 ) ;
    FCML_A64( "fchs", 0xd9, 0xe0 );
}

void fcml_tf_instruction_FNCLEX(void) {
    FCML_I64( "fclex", 0x9B, 0xDB, 0xE2 );
    FCML_I32( "fclex", 0x9B, 0xDB, 0xE2 );
    FCML_I64( "fnclex", 0xDB, 0xE2 );
    FCML_I32( "fnclex", 0xDB, 0xE2 );
    FCML_A64( "fclex", 0x9b, 0xdb, 0xe2 );
    FCML_A64( "fnclex", 0xdb, 0xe2 );
}

void fcml_tf_instruction_FCMOV(void) {

    /* FCMOVNU*/
    FCML_I64( "fcmovnu st(0),st(1)", 0xDB, 0xD9 );
    FCML_I32( "fcmovnu st(0),st(1)", 0xDB, 0xD9 );

    /* FCMOVNBE*/
    FCML_I64( "fcmovnbe st(0),st(1)", 0xDB, 0xD1 );
    FCML_I32( "fcmovnbe st(0),st(1)", 0xDB, 0xD1 );

    /* FCMOVNE*/
    FCML_I64( "fcmovne st(0),st(1)", 0xDB, 0xC9 );
    FCML_I32( "fcmovne st(0),st(1)", 0xDB, 0xC9 );

    /* FCMOVNB*/
    FCML_I64( "fcmovnb st(0),st(1)", 0xDB, 0xC1 );
    FCML_I32( "fcmovnb st(0),st(1)", 0xDB, 0xC1 );

    /* FCMOVU*/
    FCML_I64( "fcmovu st(0),st(1)", 0xDA, 0xD9 );
    FCML_I32( "fcmovu st(0),st(1)", 0xDA, 0xD9);

    /* FCMOVBE*/
    FCML_I64( "fcmovbe st(0),st(1)", 0xDA, 0xD1 );
    FCML_I32( "fcmovbe st(0),st(1)", 0xDA, 0xD1 );

    /* FCMOVB*/
    FCML_I64( "fcmovb st(0),st(1)", 0xDA, 0xC1 );
    FCML_I32( "fcmovb st(0),st(1)", 0xDA, 0xC1 );

    /* FCMOVE*/
    FCML_I64( "fcmove st(0),st(1)", 0xDA, 0xC9 );
    FCML_I32( "fcmove st(0),st(1)", 0xDA, 0xC9 );

    FCML_A64( "fcmovnu %st(1),%st(0)", 0xdb, 0xd9 );
    FCML_A64( "fcmovnbe %st(1),%st(0)", 0xdb, 0xd1 );
    FCML_A64( "fcmovne %st(1),%st(0)", 0xdb, 0xc9 );
    FCML_A64( "fcmovnb %st(1),%st(0)", 0xdb, 0xc1 );
    FCML_A64( "fcmovu %st(1),%st(0)", 0xda, 0xd9 );
    FCML_A64( "fcmovbe %st(1),%st(0)", 0xda, 0xd1 );
    FCML_A64( "fcmovb %st(1),%st(0)", 0xda, 0xc1 );
    FCML_A64( "fcmove %st(1),%st(0)", 0xda, 0xc9 );

}

void fcml_tf_instruction_FCOM(void) {
    /* D8 /2 FCOM m32fp*/
    FCML_I64( "fcom dword ptr [rax]", 0xD8, 0x10 );
    FCML_I32( "fcom dword ptr [eax]", 0xD8, 0x10 );
    /* D8 /3 FCOMP m32fp*/
    FCML_I64( "fcomp dword ptr [rax]", 0xD8, 0x18 );
    FCML_I32( "fcomp dword ptr [eax]", 0xD8, 0x18 );
    /* DC /2 FCOM m64fp*/
    FCML_I64( "fcom qword ptr [rax]", 0xDC, 0x10 );
    FCML_I32( "fcom qword ptr [eax]", 0xDC, 0x10 );
    /* DC /3 FCOMP m64fp*/
    FCML_I64( "fcomp qword ptr [rax]", 0xDC, 0x18 );
    FCML_I32( "fcomp qword ptr [eax]", 0xDC, 0x18 );
    /* D8 D0+i FCOM ST(i)*/
    FCML_I64( "fcom st(0)", 0xD8, 0xD0 );
    FCML_I64( "fcom st(1)", 0xD8, 0xD1 );
    FCML_I32( "fcom st(0)", 0xD8, 0xD0 );
    FCML_I32( "fcom st(1)", 0xD8, 0xD1 );
    /* D8 D8+i FCOMP ST(i)*/
    FCML_I64( "fcomp st(0)", 0xD8, 0xD8 );
    FCML_I64( "fcomp st(1)", 0xD8, 0xD9 );
    FCML_I32( "fcomp st(0)", 0xD8, 0xD8 );
    FCML_I32( "fcomp st(1)", 0xD8, 0xD9 );
    /* DE D9 FCOMPP*/
    FCML_I32( "fcompp", 0xDE, 0xD9 );
    FCML_I64( "fcompp", 0xDE, 0xD9 );
    /* D8 D1 FCOM*/
    /* D8 D9 FCOMP*/
    FCML_I32_A( "fcom", 0xD8, 0xD1 );
    FCML_I32_A( "fcomp", 0xD8, 0xD9 );

    /* GAS*/
    FCML_A64( "fcoms (%rax)", 0xd8, 0x10 );
    FCML_A64( "fcomps (%rax)", 0xd8, 0x18 );
    FCML_A64( "fcoml (%rax)", 0xdc, 0x10 );
    FCML_A64( "fcompl (%rax)", 0xdc, 0x18 );
    FCML_A64( "fcom %st(1)", 0xd8, 0xd1 );
    FCML_A64( "fcomp %st(1)", 0xd8, 0xd9 );
    FCML_A64( "fcompp", 0xde, 0xd9 );
    FCML_A64( "add %cl,(%rdi)", 0x00, 0x0f );
    FCML_A32_A( "fcom", 0xD8, 0xD1 );
    FCML_A32_A( "fcomp", 0xD8, 0xD9 );
}

void fcml_tf_instruction_FCOMI(void) {
    /* FCOMI*/
    FCML_I64( "fcomi st(0),st(1)", 0xDB, 0xF1 );
    FCML_I32( "fcomi st(0),st(1)", 0xDB, 0xF1 );
    /* FCOMIP*/
    FCML_I64( "fcomip st(0),st(1)", 0xDF, 0xF1 );
    FCML_I32( "fcomip st(0),st(1)", 0xDF, 0xF1 );
    /* FUCOMI*/
    FCML_I64( "fucomi st(0),st(1)", 0xDB, 0xE9 );
    FCML_I32( "fucomi st(0),st(1)", 0xDB, 0xE9 );
    /* FUCOMIP*/
    FCML_I64( "fucomip st(0),st(1)", 0xDF, 0xE9 );
    FCML_I32( "fucomip st(0),st(1)", 0xDF, 0xE9 );

    FCML_A64( "fcomi %st(1),%st(0)", 0xdb, 0xf1 );
    FCML_A64( "fcomip %st(1),%st(0)", 0xdf, 0xf1 );
    FCML_A64( "fucomi %st(1),%st(0)", 0xdb, 0xe9 );
    FCML_A64( "fucomip %st(1),%st(0)", 0xdf, 0xe9 );
}

void fcml_tf_instruction_FCOS(void) {
    FCML_I3264( "fcos", 0xD9, 0xFF );
    FCML_A64( "fcos", 0xd9, 0xff );
}

void fcml_tf_instruction_FDECSTP(void) {
    FCML_I3264( "fdecstp", 0xD9, 0xf6 );
    FCML_A64( "fdecstp", 0xd9, 0xf6 );
}

/*

VS:
00401000 D8 78 00         fdivr       dword ptr [eax]
00401003 D8 70 00         fdiv        dword ptr [eax]
00401006 DA 78 00         fidivr      dword ptr [eax]
00401009 DA 70 00         fidiv       dword ptr [eax]

GAS:
fdivrs 0x0(%rax) - 0xd8, 0x78, 0x00
fdivs 0x0(%rax) - 0xd8, 0x70, 0x00
fidivrl 0x0(%rax) - 0xda, 0x78, 0x00
fidivl 0x0(%rax) - 0xda, 0x70, 0x00


 */

void fcml_tf_instruction_FDIV(void) {
    FCML_I64( "fdiv dword ptr [rax+0000000000000020h]", 0xD8, 0x70, 0x20 );
    FCML_I32( "fdiv dword ptr [eax+00000020h]", 0xD8, 0x70, 0x20 );
    FCML_I64( "fdiv qword ptr [rax+0000000000000020h]", 0xDC, 0x70, 0x20 );
    FCML_I32( "fdiv qword ptr [eax+00000020h]", 0xDC, 0x70, 0x20 );
    FCML_I3264( "fdiv st(0),st(1)", 0xD8, 0xF1 );
    FCML_I3264( "fdiv st(1),st(0)", 0xDC, 0xF9 );
    FCML_I3264( "fdiv st(1),st(0)", 0xDC, 0xF9 );
    FCML_I32( "fdivp st(1),st(0)", 0xDE, 0xF9 );
    FCML_I64( "fidiv dword ptr [rax+0000000000000020h]", 0xDA, 0x70, 0x20 );
    FCML_I32( "fidiv dword ptr [eax+00000020h]", 0xDA, 0x70, 0x20 );
    FCML_I64( "fidiv word ptr [rax+0000000000000020h]", 0xDE, 0x70, 0x20 );
    FCML_I32( "fidiv word ptr [eax+00000020h]", 0xDE, 0x70, 0x20 );
    /* DE F9 FDIVP*/
    FCML_I3264_A( "fdivp", 0xDE, 0xF9 );
    /*GAC*/
    FCML_A64( "fdivs 0x0000000000000020(%rax)", 0xd8, 0x70, 0x20 );
    FCML_A64( "fdivl 0x0000000000000020(%rax)", 0xdc, 0x70, 0x20 );
    FCML_A64( "fdiv %st(1),%st(0)", 0xd8, 0xf1 );
    FCML_A64( "fdivr %st(0),%st(1)", 0xdc, 0xf9 );
    FCML_A64( "fidivl 0x0000000000000020(%rax)", 0xda, 0x70, 0x20 );
    FCML_A64( "fidiv 0x0000000000000020(%rax)", 0xde, 0x70, 0x20 );
    FCML_A64( "fdivrp %st(0),%st(1)", 0xde, 0xf9 );
}

void fcml_tf_instruction_FDIVR(void) {
    FCML_I32( "fdivr dword ptr [eax]", 0xD8, 0x38 );
    FCML_I64( "fdivr dword ptr [rax+0000000000000020h]", 0xD8, 0x78, 0x20 );
    FCML_I32( "fdivr dword ptr [eax+00000020h]", 0xD8, 0x78, 0x20 );
    FCML_I64( "fdivr qword ptr [rax+0000000000000020h]", 0xDC, 0x78, 0x20 );
    FCML_I32( "fdivr qword ptr [eax+00000020h]", 0xDC, 0x78, 0x20 );
    FCML_I32( "fdivr st(0),st(1)", 0xD8, 0xF9 );
    FCML_I64( "fdivr st(0),st(1)", 0xD8, 0xF9 );
    FCML_I64( "fdivr st(1),st(0)", 0xDC, 0xF1 );
    FCML_I32( "fdivr st(1),st(0)", 0xDC, 0xF1 );
    FCML_I64( "fdivrp st(1),st(0)", 0xDE, 0xF1 );
    FCML_I32( "fdivrp st(1),st(0)", 0xDE, 0xF1 );
    FCML_I64( "fidivr dword ptr [rax+0000000000000020h]", 0xDA, 0x78, 0x20 );
    FCML_I32( "fidivr dword ptr [eax+00000020h]", 0xDA, 0x78, 0x20 );
    FCML_I64( "fidivr word ptr [rax+0000000000000020h]", 0xDE, 0x78, 0x20 );
    FCML_I32( "fidivr word ptr [eax+00000020h]", 0xDE, 0x78, 0x20 );
    /* DE F1 FDIVRP*/
    FCML_I3264_A( "fdivrp", 0xDE, 0xF1 );
    /* GAS*/
    FCML_A64( "fdivrs 0x0000000000000020(%rax)", 0xd8, 0x78, 0x20 );
    FCML_A64( "fdivrl 0x0000000000000020(%rax)", 0xdc, 0x78, 0x20 );
    FCML_A64( "fdivr %st(1),%st(0)", 0xd8, 0xf9 );
    FCML_A64( "fdiv %st(0),%st(1)", 0xdc, 0xf1 );
    FCML_A64( "fdivp %st(0),%st(1)", 0xde, 0xf1 );
    FCML_A64( "fidivrl 0x0000000000000020(%rax)", 0xda, 0x78, 0x20 );
    FCML_A64( "fidivr 0x0000000000000020(%rax)", 0xde, 0x78, 0x20 );
    FCML_A64( "fdivp %st(0),%st(1)", 0xde, 0xf1 );
}

void fcml_tf_instruction_FFREE(void) {
    FCML_I3264( "ffree st(1)", 0xDD, 0xC1 );
    FCML_A64( "ffree %st(1)", 0xdd, 0xc1 );
}

void fcml_tf_instruction_FICOM(void) {
    FCML_I32( "ficom word ptr [eax+00000040h]", 0xDE, 0x50, 0x40 );
    FCML_I64( "ficom word ptr [rax+0000000000000040h]", 0xDE, 0x50, 0x40 );
    FCML_I32( "ficom dword ptr [eax+00000040h]", 0xDA, 0x50, 0x40 );
    FCML_I64( "ficom dword ptr [rax+0000000000000040h]", 0xDA, 0x50, 0x40 );
    FCML_I32( "ficomp word ptr [eax+00000040h]", 0xDE, 0x58, 0x40 );
    FCML_I64( "ficomp word ptr [rax+0000000000000040h]", 0xDE, 0x58, 0x40 );
    FCML_I32( "ficomp dword ptr [eax+00000040h]", 0xDA, 0x58, 0x40 );
    FCML_I64( "ficomp dword ptr [rax+0000000000000040h]", 0xDA, 0x58, 0x40 );
    /* GAS*/
    FCML_A64( "ficom 0x0000000000000040(%rax)", 0xde, 0x50, 0x40 );
    FCML_A64( "ficoml 0x0000000000000040(%rax)", 0xda, 0x50, 0x40 );
    FCML_A64( "ficomp 0x0000000000000040(%rax)", 0xde, 0x58, 0x40 );
    FCML_A64( "ficompl 0x0000000000000040(%rax)", 0xda, 0x58, 0x40 );
}

void fcml_tf_instruction_FILD(void) {
    FCML_I32( "fild word ptr [eax+00000040h]", 0xDF, 0x40, 0x40 );
    FCML_I64( "fild word ptr [rax+0000000000000040h]", 0xDF, 0x40, 0x40 );
    FCML_I32( "fild dword ptr [eax+00000040h]", 0xDB, 0x40, 0x40 );
    FCML_I64( "fild dword ptr [rax+0000000000000040h]", 0xDB, 0x40, 0x40 );
    FCML_I32( "fild qword ptr [eax+00000040h]", 0xDF, 0x68, 0x40 );
    FCML_I64( "fild qword ptr [rax+0000000000000040h]", 0xDF, 0x68, 0x40 );
    /* GAS*/
    FCML_A64( "fild 0x0000000000000040(%rax)", 0xdf, 0x40, 0x40 );
    FCML_A64( "fildl 0x0000000000000040(%rax)", 0xdb, 0x40, 0x40 );
    FCML_A64( "fildll 0x0000000000000040(%rax)", 0xdf, 0x68, 0x40 );
}

void fcml_tf_instruction_FINCSTP(void) {
    FCML_I32( "fincstp", 0xD9, 0xF7 );
    FCML_I64( "fincstp", 0xD9, 0xF7 );
    FCML_A64( "fincstp", 0xd9, 0xf7 );
}

void fcml_tf_instruction_FINIT_FNINIT(void) {
    FCML_I32( "finit", 0x9B, 0xDB, 0xE3 );
    FCML_I64( "fninit", 0xDB, 0xE3 );
    FCML_A64( "finit", 0x9b, 0xdb, 0xe3 );
    FCML_A64( "fninit", 0xdb, 0xe3 );
}

void fcml_tf_instruction_FIST_FISTP(void) {
    FCML_I32( "fist word ptr [eax+00000020h]", 0xDF, 0x50, 0x20 );
    FCML_I64( "fist word ptr [rax+0000000000000020h]", 0xDF, 0x50, 0x20 );
    FCML_I32( "fist dword ptr [eax+00000020h]", 0xDB, 0x50, 0x20 );
    FCML_I64( "fist dword ptr [rax+0000000000000020h]", 0xDB, 0x50, 0x20 );
    FCML_I32( "fistp word ptr [eax+00000020h]", 0xDF, 0x58, 0x20 );
    FCML_I64( "fistp word ptr [rax+0000000000000020h]", 0xDF, 0x58, 0x20 );
    FCML_I32( "fistp dword ptr [eax+00000020h]", 0xDB, 0x58, 0x20 );
    FCML_I64( "fistp dword ptr [rax+0000000000000020h]", 0xDB, 0x58, 0x20 );
    FCML_I32( "fistp qword ptr [eax+00000020h]", 0xDF, 0x78, 0x20 );
    FCML_I64( "fistp qword ptr [rax+0000000000000020h]", 0xDF, 0x78, 0x20 );
    /* GAS*/
    FCML_A64( "fist 0x0000000000000020(%rax)", 0xdf, 0x50, 0x20 );
    FCML_A64( "fistl 0x0000000000000020(%rax)", 0xdb, 0x50, 0x20 );
    FCML_A64( "fistp 0x0000000000000020(%rax)", 0xdf, 0x58, 0x20 );
    FCML_A64( "fistpll 0x0000000000000020(%rax)", 0xdf, 0x78, 0x20 );
}

void fcml_tf_instruction_FLD(void) {
    FCML_I32( "fld dword ptr [eax+00000020h]", 0xD9, 0x40, 0x20 );
    FCML_I64( "fld dword ptr [rax+0000000000000020h]", 0xD9, 0x40, 0x20 );
    FCML_I32( "fld qword ptr [eax+00000020h]", 0xDD, 0x40, 0x20 );
    FCML_I64( "fld qword ptr [rax+0000000000000020h]", 0xDD, 0x40, 0x20 );
    FCML_I32( "fld tbyte ptr [eax+00000020h]", 0xDB, 0x68, 0x20 );
    FCML_I64( "fld tbyte ptr [rax+0000000000000020h]", 0xDB, 0x68, 0x20 );
    FCML_I32( "fld st(1)", 0xD9, 0xC1 );
    FCML_I64( "fld st(1)", 0xD9, 0xC1 );
    /* GAS*/
    FCML_A64( "flds 0x0000000000000020(%rax)", 0xd9, 0x40, 0x20 );
    FCML_A64( "fldl 0x0000000000000020(%rax)", 0xdd, 0x40, 0x20 );
    FCML_A64( "fldt 0x0000000000000020(%rax)", 0xdb, 0x68, 0x20 );
    FCML_A64( "fld %st(1)", 0xd9, 0xc1 );
}

void fcml_tf_instruction_FLDx(void) {
    FCML_I32( "fld1", 0xD9, 0xE8 );
    FCML_I64( "fld1", 0xD9, 0xE8 );
    FCML_I32( "fldl2t", 0xD9, 0xE9 );
    FCML_I64( "fldl2t", 0xD9, 0xE9 );
    FCML_I32( "fldl2e", 0xD9, 0xEA );
    FCML_I64( "fldl2e", 0xD9, 0xEA );
    FCML_I32( "fldpi", 0xD9, 0xEB );
    FCML_I64( "fldpi", 0xD9, 0xEB );
    FCML_I32( "fldlg2", 0xD9, 0xEC );
    FCML_I64( "fldlg2", 0xD9, 0xEC );
    FCML_I32( "fldln2", 0xD9, 0xED );
    FCML_I64( "fldln2", 0xD9, 0xED );
    FCML_I32( "fldz", 0xD9, 0xEE );
    FCML_I64( "fldz", 0xD9, 0xEE );
    /* GAS*/
    FCML_A64( "fld1", 0xd9, 0xe8 );
    FCML_A64( "fldl2t", 0xd9, 0xe9 );
    FCML_A64( "fldl2e", 0xd9, 0xea );
    FCML_A64( "fldpi", 0xd9, 0xeb );
    FCML_A64( "fldlg2", 0xd9, 0xec );
    FCML_A64( "fldln2", 0xd9, 0xed );
    FCML_A64( "fldz", 0xd9, 0xee );
}

void fcml_tf_instruction_FLDCW(void) {
    FCML_I32( "fldcw word ptr [eax+00000040h]", 0xD9, 0x68, 0x40 );
    FCML_I64( "fldcw word ptr [rax+0000000000000040h]", 0xD9, 0x68, 0x40 );
    FCML_A64( "fldcw 0x0000000000000040(%rax)", 0xd9, 0x68, 0x40 );
}

void fcml_tf_instruction_FLDENV(void) {
    FCML_I64( "fldenv 28byte ptr [rax+0000000000000020h]", 0xD9, 0x60, 0x20 );
    FCML_I32( "fldenv 28byte ptr [eax+00000020h]", 0xD9, 0x60, 0x20 );
    FCML_I32( "fldenv 14byte ptr [eax+00000020h]", 0x66, 0xD9, 0x60, 0x20 );
    FCML_A64( "fldenv 0x0000000000000020(%rax)", 0xd9, 0x60, 0x20 );
    FCML_A64( "fldenvs 0x0000000000000020(%rax)", 0x66, 0xd9, 0x60, 0x20 );
}

void fcml_tf_instruction_FMUL_FMULP_FIMUL(void) {
    FCML_I64( "fmul dword ptr [rax+0000000000000020h]", 0xD8, 0x48, 0x20 );
    FCML_I32( "fmul dword ptr [eax+00000020h]", 0xD8, 0x48, 0x20 );
    FCML_I64( "fmul qword ptr [rax+0000000000000020h]", 0xDC, 0x48, 0x20 );
    FCML_I32( "fmul qword ptr [eax+00000020h]", 0xDC, 0x48, 0x20 );
    FCML_I32( "fmul st(0),st(1)", 0xD8, 0xc9 );
    FCML_I64( "fmul st(0),st(1)", 0xD8, 0xc9 );
    FCML_I64( "fmul st(1),st(0)", 0xDC, 0xc9 );
    FCML_I32( "fmul st(1),st(0)", 0xDC, 0xc9 );
    FCML_I64( "fmulp st(1),st(0)", 0xDE, 0xc9 );
    FCML_I32( "fmulp st(1),st(0)", 0xDE, 0xc9 );
    FCML_I64( "fimul dword ptr [rax+0000000000000020h]", 0xDA, 0x48, 0x20 );
    FCML_I32( "fimul dword ptr [eax+00000020h]", 0xDA, 0x48, 0x20 );
    FCML_I64( "fimul word ptr [rax+0000000000000020h]", 0xDE, 0x48, 0x20 );
    FCML_I32( "fimul word ptr [eax+00000020h]", 0xDE, 0x48, 0x20 );
    /* DE C9 FMULP*/
    FCML_I32_A( "fmulp", 0xDE, 0xC9 );
    /* GAS*/
    FCML_A64( "fmuls 0x0000000000000020(%rax)", 0xd8, 0x48, 0x20 );
    FCML_A64( "fmull 0x0000000000000020(%rax)", 0xdc, 0x48, 0x20 );
    FCML_A64( "fmul %st(1),%st(0)", 0xd8, 0xc9 );
    FCML_A64( "fmul %st(0),%st(1)", 0xdc, 0xc9 );
    FCML_A64( "fmulp %st(0),%st(1)", 0xde, 0xc9 );
    FCML_A64( "fimull 0x0000000000000020(%rax)", 0xda, 0x48, 0x20 );
    FCML_A64( "fimul 0x0000000000000020(%rax)", 0xde, 0x48, 0x20 );
    FCML_A64( "fmulp %st(0),%st(1)", 0xde, 0xc9 );
}

void fcml_tf_instruction_FNOP(void) {
    FCML_I3264( "fnop", 0xD9, 0xD0 );
    FCML_A64( "fnop", 0xd9, 0xd0 );
}

void fcml_tf_instruction_FPATAN(void) {
    FCML_I3264( "fpatan", 0xD9, 0xF3 );
    FCML_A64( "fpatan", 0xd9, 0xf3 );
}

void fcml_tf_instruction_FPREM(void) {
    FCML_I3264( "fprem", 0xD9, 0xF8 );
    FCML_A64( "fprem", 0xd9, 0xf8 );
}

void fcml_tf_instruction_FPREM1(void) {
    FCML_I3264( "fprem1", 0xD9, 0xF5 );
    FCML_A64( "fprem1", 0xd9, 0xf5 );
}

void fcml_tf_instruction_FPTAN(void) {
    FCML_I3264( "fptan", 0xD9, 0xF2 );
    FCML_A64( "fptan", 0xd9, 0xf2 );
}

void fcml_tf_instruction_FRNDINT(void) {
    FCML_I3264( "frndint", 0xD9, 0xFc );
    FCML_A64( "frndint", 0xd9, 0xfc );
}

void fcml_tf_instruction_FRSTOR(void) {
    FCML_I64( "frstor 108byte ptr [rax+0000000000000020h]", 0xDD, 0x60, 0x20 );
    FCML_I32( "frstor 108byte ptr [eax+00000020h]", 0xDD, 0x60, 0x20 );
    FCML_I32( "frstor 94byte ptr [eax+00000020h]", 0x66, 0xDD, 0x60, 0x20 );
    FCML_A64( "frstor 0x0000000000000020(%rax)", 0xdd, 0x60, 0x20 );
    FCML_A64( "frstors 0x0000000000000020(%rax)", 0x66, 0xdd, 0x60, 0x20 );
}

void fcml_tf_instruction_FSAVE_FNSAVE(void) {
    FCML_I64( "fsave 108byte ptr [rax+0000000000000020h]", 0x9B, 0xDD, 0x70, 0x20 );
    FCML_I32( "fsave 108byte ptr [eax+00000020h]", 0x9B, 0xDD, 0x70, 0x20  );
    FCML_I32( "fsave 94byte ptr [eax+00000020h]", 0x66, 0x9B, 0xDD, 0x70, 0x20  );
    FCML_I64( "fnsave 108byte ptr [rax+0000000000000020h]", 0xDD, 0x70, 0x20 );
    FCML_I64( "fnsave 94byte ptr [rax+0000000000000020h]", 0x66, 0xDD, 0x70, 0x20 );
    FCML_I32( "fnsave 108byte ptr [eax+00000020h]", 0xDD, 0x70, 0x20 );
    /* GAS*/
    FCML_A64( "fsave 0x0000000000000020(%rax)", 0x9b, 0xdd, 0x70, 0x20 );
    FCML_A64( "fsaves 0x0000000000000020(%rax)", 0x66, 0x9b, 0xdd, 0x70, 0x20 );
    FCML_A64( "fnsave 0x0000000000000020(%rax)", 0xdd, 0x70, 0x20 );
    FCML_A64( "fnsaves 0x0000000000000020(%rax)", 0x66, 0xdd, 0x70, 0x20 );
}

void fcml_tf_instruction_FSCALE(void) {
    FCML_I3264( "fscale", 0xD9, 0xFD );
    FCML_A64( "fscale", 0xd9, 0xfd );
}

void fcml_tf_instruction_FSIN(void) {
    FCML_I3264( "fsin", 0xD9, 0xFE );
    FCML_A64( "fsin", 0xd9, 0xfe );
}

void fcml_tf_instruction_FSINCOS(void) {
    FCML_I3264( "fsincos", 0xD9, 0xFB );
    FCML_A64( "fsincos", 0xd9, 0xfb );
}

void fcml_tf_instruction_FSQRT(void) {
    FCML_I3264( "fsqrt", 0xD9, 0xFA );
    FCML_A64( "fsqrt", 0xd9, 0xfa );
}

void fcml_tf_instruction_FST_FSTP(void) {
    FCML_I64( "fst dword ptr [rax+0000000000000020h]", 0xD9, 0x50, 0x20 );
    FCML_I32( "fst dword ptr [eax+00000020h]", 0xD9, 0x50, 0x20 );
    FCML_I64( "fst qword ptr [rax+0000000000000020h]", 0xDD, 0x50, 0x20 );
    FCML_I32( "fst qword ptr [eax+00000020h]", 0xDD, 0x50, 0x20 );
    FCML_I64( "fst st(1)", 0xDD, 0xD1 );
    FCML_I32( "fst st(1)", 0xDD, 0xD1 );
    FCML_I64( "fstp dword ptr [rax+0000000000000020h]", 0xD9, 0x58, 0x20 );
    FCML_I32( "fstp dword ptr [eax+00000020h]", 0xD9, 0x58, 0x20 );
    FCML_I64( "fstp qword ptr [rax+0000000000000020h]", 0xDD, 0x58, 0x20 );
    FCML_I32( "fstp qword ptr [eax+00000020h]", 0xDD, 0x58, 0x20 );
    FCML_I64( "fstp tbyte ptr [rax+0000000000000020h]", 0xDB, 0x78, 0x20 );
    FCML_I32( "fstp tbyte ptr [eax+00000020h]", 0xDB, 0x78, 0x20 );
    FCML_I64( "fstp st(1)", 0xDD, 0xD9 );
    FCML_I32( "fstp st(1)", 0xDD, 0xD9 );
    /* GAS*/
    FCML_A64( "fsts 0x0000000000000020(%rax)", 0xd9, 0x50, 0x20 );
    FCML_A64( "fstl 0x0000000000000020(%rax)", 0xdd, 0x50, 0x20 );
    FCML_A64( "fst %st(1)", 0xdd, 0xd1 );
    FCML_A64( "fstps 0x0000000000000020(%rax)", 0xd9, 0x58, 0x20 );
    FCML_A64( "fstpl 0x0000000000000020(%rax)", 0xdd, 0x58, 0x20 );
    FCML_A64( "fstpt 0x0000000000000020(%rax)", 0xdb, 0x78, 0x20 );
    FCML_A64( "fstp %st(1)", 0xdd, 0xd9 );
}

void fcml_tf_instruction_FSTENV_FNSTENV(void) {
	FCML_I64( "fstenv 28byte ptr [rax+0000000000000020h]", 0x9B, 0xD9, 0x70, 0x20 );
	FCML_I32( "fstenv 28byte ptr [eax+00000020h]", 0x9B, 0xD9, 0x70, 0x20 );
	FCML_I32( "fstenv 14byte ptr [eax+00000020h]", 0x66, 0x9B, 0xD9, 0x70, 0x20 );
	FCML_I64( "fnstenv 28byte ptr [rax+0000000000000020h]", 0xD9, 0x70, 0x20 );
	FCML_I64( "fnstenv 14byte ptr [rax+0000000000000020h]", 0x66, 0xD9, 0x70, 0x20 );
	FCML_I32( "fnstenv 28byte ptr [eax+00000020h]", 0xD9, 0x70, 0x20 );
	/* GAS*/
	FCML_A64( "fstenv 0x0000000000000020(%rax)", 0x9b, 0xd9, 0x70, 0x20 );
	FCML_A64( "fstenvs 0x0000000000000020(%rax)", 0x66, 0x9b, 0xd9, 0x70, 0x20 );
	FCML_A64( "fnstenv 0x0000000000000020(%rax)", 0xd9, 0x70, 0x20 );
	FCML_A64( "fnstenvs 0x0000000000000020(%rax)", 0x66, 0xd9, 0x70, 0x20 );
}

void fcml_tf_instruction_FSTCW_FNSTCW(void) {
    FCML_I64( "fstcw word ptr [rax+0000000000000020h]", 0x9B, 0xD9, 0x78, 0x20 );
    FCML_I32( "fstcw word ptr [eax+00000020h]",0x9B, 0xD9, 0x78, 0x20 );
    FCML_I64( "fnstcw word ptr [rax+0000000000000020h]", 0xD9, 0x78, 0x20 );
    FCML_I32( "fnstcw word ptr [eax+00000020h]", 0xD9, 0x78, 0x20 );
    FCML_A64( "fstcw 0x0000000000000020(%rax)", 0x9b, 0xd9, 0x78, 0x20 );
    FCML_A64( "fnstcw 0x0000000000000020(%rax)", 0xd9, 0x78, 0x20 );
}

void fcml_tf_instruction_FSTSW_FNSTSW(void) {
    FCML_I64( "fstsw word ptr [rax+0000000000000020h]", 0x9B, 0xDD, 0x78, 0x20 );
    FCML_I32( "fstsw word ptr [eax+00000020h]", 0x9B, 0xDD, 0x78, 0x20 );
    FCML_I64( "fstsw ax", 0x9B, 0xDF, 0xE0 );
    FCML_I32( "fstsw ax", 0x9B, 0xDF, 0xE0  );
    FCML_I64( "fnstsw word ptr [rax+0000000000000020h]", 0xDD, 0x78, 0x20 );
    FCML_I32( "fnstsw word ptr [eax+00000020h]", 0xDD, 0x78, 0x20  );
    FCML_I64( "fnstsw ax", 0xDF, 0xE0 );
    FCML_I32( "fnstsw ax", 0xDF, 0xE0  );
    /* GAS*/
    FCML_A64( "fstsw 0x0000000000000020(%rax)", 0x9b, 0xdd, 0x78, 0x20 );
    FCML_A64( "fstsw %ax", 0x9b, 0xdf, 0xe0 );
    FCML_A64( "fnstsw 0x0000000000000020(%rax)", 0xdd, 0x78, 0x20 );
    FCML_A64( "fnstsw %ax", 0xdf, 0xe0 );
}

void fcml_tf_instruction_FSUB_FSUBP_FISUB(void) {
    FCML_I64( "fsub dword ptr [rax+0000000000000020h]", 0xD8, 0x60, 0x20 );
    FCML_I32( "fsub dword ptr [eax+00000020h]", 0xD8, 0x60, 0x20 );
    FCML_I64( "fsub qword ptr [rax+0000000000000020h]", 0xDC, 0x60, 0x20 );
    FCML_I32( "fsub qword ptr [eax+00000020h]", 0xDC, 0x60, 0x20 );
    FCML_I32( "fsub st(0),st(1)", 0xD8, 0xe1 );
    FCML_I64( "fsub st(0),st(1)", 0xD8, 0xe1 );
    FCML_I64( "fsub st(1),st(0)", 0xDC, 0xe9 );
    FCML_I32( "fsub st(1),st(0)", 0xDC, 0xe9 );
    FCML_I64( "fsubp st(1),st(0)", 0xDE, 0xe9 );
    FCML_I32( "fsubp st(1),st(0)", 0xDE, 0xe9 );
    FCML_I64( "fisub dword ptr [rax+0000000000000020h]", 0xDA, 0x60, 0x20 );
    FCML_I32( "fisub dword ptr [eax+00000020h]", 0xDA, 0x60, 0x20 );
    FCML_I64( "fisub word ptr [rax+0000000000000020h]", 0xDE, 0x60, 0x20 );
    FCML_I32( "fisub word ptr [eax+00000020h]", 0xDE, 0x60, 0x20 );
    /* DE E9 FSUBP*/
    FCML_I3264_A( "fsubp", 0xDE, 0xE9 );
    /* GAS*/
    FCML_A64( "fsubs 0x0000000000000020(%rax)", 0xd8, 0x60, 0x20 );
    FCML_A64( "fsubl 0x0000000000000020(%rax)", 0xdc, 0x60, 0x20 );
    FCML_A64( "fsub %st(1),%st(0)", 0xd8, 0xe1 );
    /* FCML_A64( "fsub %st(0),%st(1)", 0xdc, 0xe9 );*/
    /* SVR3.2 compatible by default.*/
    FCML_A64( "fsubr %st(0),%st(1)", 0xdc, 0xe9 );
    FCML_A64( "fsubrp %st(0),%st(1)", 0xde, 0xe9 );
    FCML_A64( "fisubl 0x0000000000000020(%rax)", 0xda, 0x60, 0x20 );
    FCML_A64( "fisub 0x0000000000000020(%rax)", 0xde, 0x60, 0x20 );
}

void fcml_tf_instruction_FSUBR_FSUBRP_FISUBR(void) {
    FCML_I64( "fsubr dword ptr [rax+0000000000000020h]", 0xD8, 0x68, 0x20 );
    FCML_I32( "fsubr dword ptr [eax+00000020h]", 0xD8, 0x68, 0x20 );
    FCML_I64( "fsubr qword ptr [rax+0000000000000020h]", 0xDC, 0x68, 0x20 );
    FCML_I32( "fsubr qword ptr [eax+00000020h]", 0xDC, 0x68, 0x20 );
    FCML_I32( "fsubr st(0),st(1)", 0xD8, 0xe9 );
    FCML_I64( "fsubr st(0),st(1)", 0xD8, 0xe9 );
    FCML_I64( "fsubr st(1),st(0)", 0xDC, 0xe1 );
    FCML_I32( "fsubr st(1),st(0)", 0xDC, 0xe1 );
    FCML_I64( "fsubrp st(1),st(0)", 0xDE, 0xe1 );
    FCML_I32( "fsubrp st(1),st(0)", 0xDE, 0xe1 );
    FCML_I64( "fisubr dword ptr [rax+0000000000000020h]", 0xDA, 0x68, 0x20 );
    FCML_I32( "fisubr dword ptr [eax+00000020h]", 0xDA, 0x68, 0x20 );
    FCML_I64( "fisubr word ptr [rax+0000000000000020h]", 0xDE, 0x68, 0x20 );
    FCML_I32( "fisubr word ptr [eax+00000020h]", 0xDE, 0x68, 0x20 );
    /* DE E1 FSUBRP*/
    FCML_I3264_A( "fsubrp", 0xDE, 0xE1 );
    /* GAS*/
    FCML_A64( "fsubrs 0x0000000000000020(%rax)", 0xd8, 0x68, 0x20 );
    FCML_A64( "fsubrl 0x0000000000000020(%rax)", 0xdc, 0x68, 0x20 );
    FCML_A64( "fsubr %st(1),%st(0)", 0xd8, 0xe9 );
    /* FCML_A64( "fsubr %st(0),%st(1)", 0xdc, 0xe1 );*/
    /* SVR3.2 compatible by default.*/
    FCML_A64( "fsub %st(0),%st(1)", 0xdc, 0xe1 );
    FCML_A64( "fsubp %st(0),%st(1)", 0xde, 0xe1 );
    FCML_A64( "fisubrl 0x0000000000000020(%rax)", 0xda, 0x68, 0x20 );
    FCML_A64( "fisubr 0x0000000000000020(%rax)", 0xde, 0x68, 0x20 );
}

void fcml_tf_instruction_FTST(void) {
    FCML_I3264( "ftst", 0xD9, 0xE4 );
}

void fcml_tf_instruction_FUCOM_FUCOMP_FUCOMPP(void) {
    FCML_I3264( "fucom st(1)", 0xDD, 0xE1 );
    FCML_I3264( "fucomp st(1)", 0xDD, 0xE9 );
    /* DD E1 FUCOM*/
    FCML_I3264_A( "fucom", 0xDD, 0xE1 );
    /* DD E9 FUCOMP*/
    FCML_I3264_A( "fucomp", 0xDD, 0xE9 );
    /* DA E9 FUCOMPP*/
    FCML_I3264( "fucompp", 0xDA, 0xE9 );
    /* GAS*/
    FCML_A64( "fucom %st(1)", 0xdd, 0xe1 );
    FCML_A64( "fucomp %st(1)", 0xdd, 0xe9 );
    FCML_A64( "fucompp", 0xda, 0xe9 );

}

void fcml_tf_instruction_FXAM(void) {
    FCML_I3264( "fxam", 0xD9, 0xE5 );
    FCML_A64( "fxam", 0xd9, 0xe5 );
}

void fcml_tf_instruction_FXCH(void) {
    FCML_I3264( "fxch st(1)", 0xD9, 0xC9 );
    FCML_I3264( "fxch st(2)", 0xD9, 0xCA );
    /* D9 C9 FXCH*/
    FCML_I3264_A( "fxch", 0xD9, 0xC9 );
    /* GAS*/
    FCML_A64( "fxch %st(1)", 0xd9, 0xc9 );
    FCML_A64( "fxch %st(2)", 0xd9, 0xca );
    FCML_A64_A( "fxch", 0xD9, 0xC9 );
}

void fcml_tf_instruction_FXRSTOR(void) {
    /* 0F AE /5 XRSTOR mem M Valid Valid Restore processor extended states from memory. The states are specified by EDX:EAX*/
    /* REX.W+ 0F AE /5 XRSTOR64 mem M Valid N.E. Restore processor extended states from memory. The states are specified by EDX:EAX*/
    FCML_I64( "xrstor [rax]", 0x0F, 0xAE, 0x28 );
    FCML_I32( "xrstor [eax]", 0x0F, 0xAE, 0x28 );
    FCML_I64( "xrstor [rax]", 0x66, 0x0F, 0xAE, 0x28 );
    FCML_I32( "xrstor [eax]", 0x66, 0x0F, 0xAE, 0x28 );
    FCML_I64( "xrstor64 [rax]", 0x48, 0x0F, 0xAE, 0x28 );
    /* GAS*/
    FCML_A64( "xrstor (%rax)", 0x0f, 0xae, 0x28 );
    FCML_A64( "xrstor64 (%rax)", 0x48, 0x0f, 0xae, 0x28 );
}

void fcml_tf_instruction_FXRSAVE(void) {
    FCML_I64( "fxsave [rax+0000000000000020h]", 0x0F, 0xAE, 0x40, 0x20 );
    FCML_I32( "fxsave [eax+00000020h]", 0x0F, 0xAE, 0x40, 0x20 );
    FCML_I64_D( "fxsave [rax+0000000000000020h]", 0x66, 0x0F, 0xAE, 0x40, 0x20 );
    FCML_I32_D( "fxsave [eax+00000020h]", 0x66, 0x0F, 0xAE, 0x40, 0x20 );
    FCML_I64( "fxsave64 [rax+0000000000000020h]", 0x48, 0x0F, 0xAE, 0x40, 0x20 );
    /* GAS*/
    FCML_A64( "fxsave 0x0000000000000020(%rax)", 0x0f, 0xae, 0x40, 0x20 );
    FCML_A64( "fxsave64 0x0000000000000020(%rax)", 0x48, 0x0f, 0xae, 0x40, 0x20 );
}

void fcml_tf_instruction_FXTRACT(void) {
    FCML_I3264( "fxtract", 0xD9, 0xF4 );
    FCML_A64( "fxtract", 0xd9, 0xf4 );
}

void fcml_tf_instruction_FYL2X(void) {
    FCML_I3264( "fyl2x", 0xD9, 0xF1 );
    FCML_A64( "fyl2x", 0xd9, 0xf1 );
}

void fcml_tf_instruction_FYL2XP1(void) {
    FCML_I3264( "fyl2xp1", 0xD9, 0xF9 );
    FCML_A64( "fyl2xp1", 0xd9, 0xf9 );
}

void fcml_tf_instruction_FEMMS(void) {
    FCML_I3264( "femms", 0x0F, 0x0E );
    FCML_A64( "femms", 0x0f, 0x0e );
}

void fcml_tf_instruction_FISTTP(void) {
	FCML_I32( "fisttp word ptr [eax+00000020h]", 0xDF, 0x48, 0x20 );
	FCML_I64( "fisttp word ptr [rax+0000000000000020h]", 0xDF, 0x48, 0x20 );
	FCML_I32( "fisttp dword ptr [eax+00000020h]", 0xDB, 0x48, 0x20 );
	FCML_I64( "fisttp dword ptr [rax+0000000000000020h]", 0xDB, 0x48, 0x20 );
	FCML_I32( "fisttp qword ptr [eax+00000020h]", 0xDD, 0x48, 0x20 );
	FCML_I64( "fisttp qword ptr [rax+0000000000000020h]", 0xDD, 0x48, 0x20 );
	/* GAS*/
	FCML_A64( "fisttp 0x0000000000000020(%rax)", 0xdf, 0x48, 0x20 );
	FCML_A64( "fisttpl 0x0000000000000020(%rax)", 0xdb, 0x48, 0x20 );
	FCML_A64( "fisttpll 0x0000000000000020(%rax)", 0xdd, 0x48, 0x20 );
}

fcml_stf_test_case fctl_ti_instructions_f[] = {
	{ "fcml_tf_instruction_F2XM1", fcml_tf_instruction_F2XM1 },
	{ "fcml_tf_instruction_FABS", fcml_tf_instruction_FABS },
	{ "fcml_tf_instruction_FADD", fcml_tf_instruction_FADD },
	{ "fcml_tf_instruction_FBLD", fcml_tf_instruction_FBLD },
	{ "fcml_tf_instruction_FBSTP", fcml_tf_instruction_FBSTP },
	{ "fcml_tf_instruction_FCHS", fcml_tf_instruction_FCHS },
	{ "fcml_tf_instruction_FNCLEX", fcml_tf_instruction_FNCLEX },
	{ "fcml_tf_instruction_FCMOV", fcml_tf_instruction_FCMOV },
	{ "fcml_tf_instruction_FCOM", fcml_tf_instruction_FCOM },
	{ "fcml_tf_instruction_FCOMI", fcml_tf_instruction_FCOMI },
	{ "fcml_tf_instruction_FCOS", fcml_tf_instruction_FCOS },
	{ "fcml_tf_instruction_FDECSTP", fcml_tf_instruction_FDECSTP },
	{ "fcml_tf_instruction_FDIV", fcml_tf_instruction_FDIV },
	{ "fcml_tf_instruction_FDIVR", fcml_tf_instruction_FDIVR },
	{ "fcml_tf_instruction_FFREE", fcml_tf_instruction_FFREE },
	{ "fcml_tf_instruction_FICOM", fcml_tf_instruction_FICOM },
	{ "fcml_tf_instruction_FILD", fcml_tf_instruction_FILD },
	{ "fcml_tf_instruction_FINCSTP", fcml_tf_instruction_FINCSTP },
	{ "fcml_tf_instruction_FINIT_FNINIT", fcml_tf_instruction_FINIT_FNINIT },
	{ "fcml_tf_instruction_FIST_FISTP", fcml_tf_instruction_FIST_FISTP },
	{ "fcml_tf_instruction_FLD", fcml_tf_instruction_FLD },
	{ "fcml_tf_instruction_FLDx", fcml_tf_instruction_FLDx },
	{ "fcml_tf_instruction_FLDCW", fcml_tf_instruction_FLDCW },
	{ "fcml_tf_instruction_FLDENV", fcml_tf_instruction_FLDENV },
	{ "fcml_tf_instruction_FMUL_FMULP_FIMUL", fcml_tf_instruction_FMUL_FMULP_FIMUL },
	{ "fcml_tf_instruction_FNOP", fcml_tf_instruction_FNOP },
	{ "fcml_tf_instruction_FPATAN", fcml_tf_instruction_FPATAN },
	{ "fcml_tf_instruction_FPREM", fcml_tf_instruction_FPREM },
	{ "fcml_tf_instruction_FPREM1", fcml_tf_instruction_FPREM1 },
	{ "fcml_tf_instruction_FPTAN", fcml_tf_instruction_FPTAN },
	{ "fcml_tf_instruction_FRNDINT", fcml_tf_instruction_FRNDINT },
	{ "fcml_tf_instruction_FRSTOR", fcml_tf_instruction_FRSTOR },
	{ "fcml_tf_instruction_FSAVE_FNSAVE", fcml_tf_instruction_FSAVE_FNSAVE },
	{ "fcml_tf_instruction_FSCALE", fcml_tf_instruction_FSCALE },
	{ "fcml_tf_instruction_FSIN", fcml_tf_instruction_FSIN },
	{ "fcml_tf_instruction_FSINCOS", fcml_tf_instruction_FSINCOS },
	{ "fcml_tf_instruction_FSQRT", fcml_tf_instruction_FSQRT },
	{ "fcml_tf_instruction_FST_FSTP", fcml_tf_instruction_FST_FSTP },
	{ "fcml_tf_instruction_FSTENV_FNSTENV", fcml_tf_instruction_FSTENV_FNSTENV },
	{ "fcml_tf_instruction_FSTCW_FNSTCW", fcml_tf_instruction_FSTCW_FNSTCW },
	{ "fcml_tf_instruction_FSTSW_FNSTSW", fcml_tf_instruction_FSTSW_FNSTSW },
	{ "fcml_tf_instruction_FSUB_FSUBP_FISUB", fcml_tf_instruction_FSUB_FSUBP_FISUB },
	{ "fcml_tf_instruction_FSUBR_FSUBRP_FISUBR", fcml_tf_instruction_FSUBR_FSUBRP_FISUBR },
	{ "fcml_tf_instruction_FTST", fcml_tf_instruction_FTST },
	{ "fcml_tf_instruction_FUCOM_FUCOMP_FUCOMPP", fcml_tf_instruction_FUCOM_FUCOMP_FUCOMPP },
	{ "fcml_tf_instruction_FXAM", fcml_tf_instruction_FXAM },
	{ "fcml_tf_instruction_FXCH", fcml_tf_instruction_FXCH },
	{ "fcml_tf_instruction_FXRSTOR", fcml_tf_instruction_FXRSTOR },
	{ "fcml_tf_instruction_FXRSAVE", fcml_tf_instruction_FXRSAVE },
	{ "fcml_tf_instruction_FXTRACT", fcml_tf_instruction_FXTRACT },
	{ "fcml_tf_instruction_FYL2X", fcml_tf_instruction_FYL2X },
	{ "fcml_tf_instruction_FYL2XP1", fcml_tf_instruction_FYL2XP1 },
	{ "fcml_tf_instruction_FEMMS", fcml_tf_instruction_FEMMS },
	{ "fcml_tf_instruction_FISTTP", fcml_tf_instruction_FISTTP },
	FCML_STF_NULL_TEST
};

fcml_stf_test_suite fctl_si_instructions_f = {
	"suite-fctl_ti_instructions_f", fcml_tf_instructions_f_suite_init, fcml_tf_instructions_f_suite_cleanup, fctl_ti_instructions_f
};

