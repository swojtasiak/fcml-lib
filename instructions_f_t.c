/*
 * instructions.c
 *
 *  Created on: 01-06-2013
 *      Author: tAs
 */

#include "fcml_env.h"
#include "fcml_assembler.h"
#include "instructions_e_t.h"

int fcml_tf_instructions_f_suite_init(void) {
	return 0;
}

int fcml_tf_instructions_f_suite_cleanup(void) {
	return 0;
}

void fcml_tf_instruction_F2XM1(void) {
    FCML_I3264( "f2xm1", 0xD9, 0xF0 );
}

void fcml_tf_instruction_FABS(void) {
    FCML_I3264( "fabs", 0xD9, 0xE1 );
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


    FCML_I64( "fadd st(1),st(0)", 0xDC, 0xC1 );
    FCML_I32( "fadd st(1),st(0)", 0xDC, 0xC1 );

    FCML_I64( "faddp st(1),st(0)", 0xDE, 0xC1 );
    FCML_I32( "faddp st(1),st(0)", 0xDE, 0xC1 );

    FCML_I3264_A( "faddp", 0xDE, 0xC1 );

    FCML_I64( "fiadd dword ptr [rax+0000000000000020h]", 0xDA, 0x40, 0x20 );
    FCML_I32( "fiadd dword ptr [eax+00000020h]", 0xDA, 0x40, 0x20 );
    FCML_I64( "fiadd word ptr [rax+0000000000000020h]", 0xDE, 0x40, 0x20 );
    FCML_I32( "fiadd word ptr [eax+00000020h]", 0xDE, 0x40, 0x20 );
}

void fcml_tf_instruction_FBLD(void) {
    FCML_I64( "fbld tbyte ptr [rax+0000000000000020h]", 0xDf, 0x60, 0x20 ) ;
    FCML_I32( "fbld tbyte ptr [eax+00000020h]", 0xDf, 0x60, 0x20 );
}

void fcml_tf_instruction_FBSTP(void) {
    FCML_I64( "fbstp tbyte ptr [rax+0000000000000020h]", 0xDf, 0x70, 0x20 ) ;
    FCML_I32( "fbstp tbyte ptr [eax+00000020h]", 0xDf, 0x70, 0x20 );
}

void fcml_tf_instruction_FCHS(void) {
    FCML_I3264( "fchs", 0xD9, 0xE0 ) ;
}

void fcml_tf_instruction_FNCLEX(void) {
    FCML_I64( "fclex", 0x9B, 0xDB, 0xE2 );
    FCML_I32( "fclex", 0x9B, 0xDB, 0xE2 );
    FCML_I64( "fnclex", 0xDB, 0xE2 );
    FCML_I32( "fnclex", 0xDB, 0xE2 );
}

void fcml_tf_instruction_FCMOV(void) {

    // FCMOVNU
    FCML_I64( "fcmovnu st(0),st(1)", 0xDB, 0xD9 );
    FCML_I32( "fcmovnu st(0),st(1)", 0xDB, 0xD9 );

    // FCMOVNBE
    FCML_I64( "fcmovnbe st(0),st(1)", 0xDB, 0xD1 );
    FCML_I32( "fcmovnbe st(0),st(1)", 0xDB, 0xD1 );

    // FCMOVNE
    FCML_I64( "fcmovne st(0),st(1)", 0xDB, 0xC9 );
    FCML_I32( "fcmovne st(0),st(1)", 0xDB, 0xC9 );

    // FCMOVNB
    FCML_I64( "fcmovnb st(0),st(1)", 0xDB, 0xC1 );
    FCML_I32( "fcmovnb st(0),st(1)", 0xDB, 0xC1 );

    // FCMOVU
    FCML_I64( "fcmovu st(0),st(1)", 0xDA, 0xD9 );
    FCML_I32( "fcmovu st(0),st(1)", 0xDA, 0xD9);

    // FCMOVBE
    FCML_I64( "fcmovbe st(0),st(1)", 0xDA, 0xD1 );
    FCML_I32( "fcmovbe st(0),st(1)", 0xDA, 0xD1 );

    // FCMOVB
    FCML_I64( "fcmovb st(0),st(1)", 0xDA, 0xC1 );
    FCML_I32( "fcmovb st(0),st(1)", 0xDA, 0xC1 );

    // FCMOVE
    FCML_I64( "fcmove st(0),st(1)", 0xDA, 0xC9 );
    FCML_I32( "fcmove st(0),st(1)", 0xDA, 0xC9 );
}

void fcml_tf_instruction_FCOM(void) {
    // D8 /2 FCOM m32fp
    FCML_I64( "fcom dword ptr [rax]", 0xD8, 0x10 );
    FCML_I32( "fcom dword ptr [eax]", 0xD8, 0x10 );
    // D8 /3 FCOMP m32fp
    FCML_I64( "fcomp dword ptr [rax]", 0xD8, 0x18 );
    FCML_I32( "fcomp dword ptr [eax]", 0xD8, 0x18 );
    // DC /2 FCOM m64fp
    FCML_I64( "fcom qword ptr [rax]", 0xDC, 0x10 );
    FCML_I32( "fcom qword ptr [eax]", 0xDC, 0x10 );
    // DC /3 FCOMP m64fp
    FCML_I64( "fcomp qword ptr [rax]", 0xDC, 0x18 );
    FCML_I32( "fcomp qword ptr [eax]", 0xDC, 0x18 );
    // D8 D0+i FCOM ST(i)
    FCML_I64( "fcom st(0)", 0xD8, 0xD0 );
    FCML_I64( "fcom st(1)", 0xD8, 0xD1 );
    FCML_I32( "fcom st(0)", 0xD8, 0xD0 );
    FCML_I32( "fcom st(1)", 0xD8, 0xD1 );
    // D8 D8+i FCOMP ST(i)
    FCML_I64( "fcomp st(0)", 0xD8, 0xD8 );
    FCML_I64( "fcomp st(1)", 0xD8, 0xD9 );
    FCML_I32( "fcomp st(0)", 0xD8, 0xD8 );
    FCML_I32( "fcomp st(1)", 0xD8, 0xD9 );
    // DE D9 FCOMPP
    FCML_I32( "fcompp", 0xDE, 0xD9 );
    FCML_I32( "fcompp", 0xDE, 0xD9 );
    // D8 D1 FCOM
    // D8 D9 FCOMP
    FCML_I32_A( "fcom", 0xD8, 0xD1 );
    FCML_I32_A( "fcomp", 0xD8, 0xD9 );
}

void fcml_tf_instruction_FCOMI(void) {
    // FCOMI
    FCML_I64( "fcomi st(0),st(1)", 0xDB, 0xF1 );
    FCML_I32( "fcomi st(0),st(1)", 0xDB, 0xF1 );
    // FCOMIP
    FCML_I64( "fcomip st(0),st(1)", 0xDF, 0xF1 );
    FCML_I32( "fcomip st(0),st(1)", 0xDF, 0xF1 );
    // FUCOMI
    FCML_I64( "fucomi st(0),st(1)", 0xDB, 0xE9 );
    FCML_I32( "fucomi st(0),st(1)", 0xDB, 0xE9 );
    // FUCOMIP
    FCML_I64( "fucomip st(0),st(1)", 0xDF, 0xE9 );
    FCML_I32( "fucomip st(0),st(1)", 0xDF, 0xE9 );
}

void fcml_tf_instruction_FCOS(void) {
    FCML_I3264( "fcos", 0xD9, 0xFF );
}

void fcml_tf_instruction_FDECSTP(void) {
    FCML_I3264( "fdecstp", 0xD9, 0xf6 );
}

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
    // DE F9 FDIVP
    FCML_I3264_A( "fdivp", 0xDE, 0xF9 );
}

void fcml_tf_instruction_FDIVR(void) {
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
    // DE F1 FDIVRP
    FCML_I3264_A( "fdivrp", 0xDE, 0xF1 );
}

void fcml_tf_instruction_FFREE(void) {
    FCML_I3264( "ffree st(1)", 0xDD, 0xC1 );
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
}

void fcml_tf_instruction_FILD(void) {
    FCML_I32( "fild word ptr [eax+00000040h]", 0xDF, 0x40, 0x40 );
    FCML_I64( "fild word ptr [rax+0000000000000040h]", 0xDF, 0x40, 0x40 );
    FCML_I32( "fild dword ptr [eax+00000040h]", 0xDB, 0x40, 0x40 );
    FCML_I64( "fild dword ptr [rax+0000000000000040h]", 0xDB, 0x40, 0x40 );
    FCML_I32( "fild qword ptr [eax+00000040h]", 0xDF, 0x68, 0x40 );
    FCML_I64( "fild qword ptr [rax+0000000000000040h]", 0xDF, 0x68, 0x40 );
}

void fcml_tf_instruction_FINCSTP(void) {
    FCML_I32( "fincstp", 0xD9, 0xF7 );
    FCML_I64( "fincstp", 0xD9, 0xF7);
}

void fcml_tf_instruction_FINIT_FNINIT(void) {
    FCML_I32( "finit", 0x9B, 0xDB, 0xE3 );
    FCML_I64( "fninit", 0xDB, 0xE3 );
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
}

void fcml_tf_instruction_FLDCW(void) {
    FCML_I32( "fldcw word ptr [eax+00000040h]", 0xD9, 0x68, 0x40 );
    FCML_I64( "fldcw word ptr [rax+0000000000000040h]", 0xD9, 0x68, 0x40 );
}

void fcml_tf_instruction_FLDENV(void) {
    FCML_I64( "fldenv 28byte ptr [rax+0000000000000020h]", 0xD9, 0x60, 0x20 );
    FCML_I32( "fldenv 28byte ptr [eax+00000020h]", 0xD9, 0x60, 0x20 );
    FCML_I32( "fldenv 14byte ptr [eax+00000020h]", 0x66, 0xD9, 0x60, 0x20 );
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
    // DE C9 FMULP
    FCML_I32_A( "fmulp", 0xDE, 0xC9 );
}

void fcml_tf_instruction_FNOP(void) {
    FCML_I3264( "fnop", 0xD9, 0xD0 );
}

void fcml_tf_instruction_FPATAN(void) {
    FCML_I3264( "fpatan", 0xD9, 0xF3 );
}

void fcml_tf_instruction_FPREM(void) {
    FCML_I3264( "fprem", 0xD9, 0xF8 );
}

void fcml_tf_instruction_FPREM1(void) {
    FCML_I3264( "fprem1", 0xD9, 0xF5 );
}

void fcml_tf_instruction_FPTAN(void) {
    FCML_I3264( "fptan", 0xD9, 0xF2 );
}

void fcml_tf_instruction_FRNDINT(void) {
    FCML_I3264( "frndint", 0xD9, 0xFc );
}

void fcml_tf_instruction_FRSTOR(void) {
    FCML_I64( "frstor 108byte ptr [rax+0000000000000020h]", 0xDD, 0x60, 0x20 );
    FCML_I32( "frstor 108byte ptr [eax+00000020h]", 0xDD, 0x60, 0x20 );
    FCML_I32( "frstor 94byte ptr [eax+00000020h]", 0x66, 0xDD, 0x60, 0x20 );
}

void fcml_tf_instruction_FSAVE_FNSAVE(void) {
    FCML_I64( "fsave 108byte ptr [rax+0000000000000020h]", 0x9B, 0xDD, 0x70, 0x20 );
    FCML_I32( "fsave 108byte ptr [eax+00000020h]", 0x9B, 0xDD, 0x70, 0x20  );
    FCML_I32( "fsave 94byte ptr [eax+00000020h]", 0x66, 0x9B, 0xDD, 0x70, 0x20  );
    FCML_I64( "fnsave 108byte ptr [rax+0000000000000020h]", 0xDD, 0x70, 0x20 );
    FCML_I64( "fnsave 94byte ptr [rax+0000000000000020h]", 0x66, 0xDD, 0x70, 0x20 );
    FCML_I32( "fnsave 108byte ptr [eax+00000020h]", 0xDD, 0x70, 0x20 );
}

void fcml_tf_instruction_FSCALE(void) {
    FCML_I3264( "fscale", 0xD9, 0xFD );
}

void fcml_tf_instruction_FSIN(void) {
    FCML_I3264( "fsin", 0xD9, 0xFE );
}

void fcml_tf_instruction_FSINCOS(void) {
    FCML_I3264( "fsincos", 0xD9, 0xFB );
}

void fcml_tf_instruction_FSQRT(void) {
    FCML_I3264( "fsqrt", 0xD9, 0xFA );
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
}

void fcml_tf_instruction_FSTCW_FNSTCW(void) {
    FCML_I64( "fstcw word ptr [rax+0000000000000020h]", 0x9B, 0xD9, 0x78, 0x20 );
    FCML_I32( "fstcw word ptr [eax+00000020h]",0x9B, 0xD9, 0x78, 0x20 );
    FCML_I64( "fnstcw word ptr [rax+0000000000000020h]", 0xD9, 0x78, 0x20 );
    FCML_I32( "fnstcw word ptr [eax+00000020h]", 0xD9, 0x78, 0x20 );
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
    // DE E9 FSUBP
    FCML_I3264_A( "fsubp", 0xDE, 0xE9 );
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
    // DE E1 FSUBRP
    FCML_I3264_A( "fsubrp", 0xDE, 0xE1 );
}

void fcml_tf_instruction_FTST(void) {
    FCML_I3264( "ftst", 0xD9, 0xE4 );
}

void fcml_tf_instruction_FUCOM_FUCOMP_FUCOMPP(void) {
    FCML_I3264( "fucom st(1)", 0xDD, 0xE1 );
    FCML_I3264( "fucomp st(1)", 0xDD, 0xE9 );
    // DD E1 FUCOM
    FCML_I3264_A( "fucom", 0xDD, 0xE1 );
    // DD E9 FUCOMP
    FCML_I3264_A( "fucomp", 0xDD, 0xE9 );
    // DA E9 FUCOMPP
    FCML_I3264( "fucompp", 0xDA, 0xE9 );
}

void fcml_tf_instruction_FXAM(void) {
    FCML_I3264( "fxam", 0xD9, 0xE5 );
}

void fcml_tf_instruction_FXCH(void) {
    FCML_I3264( "fxch st(1)", 0xD9, 0xC9 );
    FCML_I3264( "fxch st(2)", 0xD9, 0xCA );
    // D9 C9 FXCH
    FCML_I3264_A( "fxch", 0xD9, 0xC9 );
}

void fcml_tf_instruction_FXRSTOR(void) {
    // 0F AE /5 XRSTOR mem M Valid Valid Restore processor extended states from memory. The states are specified by EDX:EAX
    // REX.W+ 0F AE /5 XRSTOR64 mem M Valid N.E. Restore processor extended states from memory. The states are specified by EDX:EAX
    FCML_I64( "xrstor [rax]", 0x0F, 0xAE, 0x28 );
    FCML_I32( "xrstor [eax]", 0x0F, 0xAE, 0x28 );
    FCML_I64( "xrstor [rax]", 0x66, 0x0F, 0xAE, 0x28 );
    FCML_I32( "xrstor [eax]", 0x66, 0x0F, 0xAE, 0x28 );
    FCML_I64( "xrstor64 [rax]", 0x48, 0x0F, 0xAE, 0x28 );
}

void fcml_tf_instruction_FXRSAVE(void) {
    FCML_I64( "fxsave [rax+0000000000000020h]", 0x0F, 0xAE, 0x40, 0x20 );
    FCML_I32( "fxsave [eax+00000020h]", 0x0F, 0xAE, 0x40, 0x20 );
    FCML_I64( "fxsave [rax+0000000000000020h]", 0x66, 0x0F, 0xAE, 0x40, 0x20 );
    FCML_I32( "fxsave [eax+00000020h]", 0x66, 0x0F, 0xAE, 0x40, 0x20 );
    FCML_I64( "fxsave64 [rax+0000000000000020h]", 0x48, 0x0F, 0xAE, 0x40, 0x20 );
}

void fcml_tf_instruction_FXTRACT(void) {
    FCML_I3264( "fxtract", 0xD9, 0xF4 );
}

void fcml_tf_instruction_FYL2X(void) {
    FCML_I3264( "fyl2x", 0xD9, 0xF1 );
}

void fcml_tf_instruction_FYL2XP1(void) {
    FCML_I3264( "fyl2xp1", 0xD9, 0xF9 );
}

void fcml_tf_instruction_FEMMS(void) {
    FCML_I3264( "femms", 0x0F, 0x0E );
}

CU_TestInfo fctl_ti_instructions_f[] = {
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
    CU_TEST_INFO_NULL,
};

CU_SuiteInfo fctl_si_instructions_f[] = {
    { "suite-fctl_ti_instructions_f", fcml_tf_instructions_f_suite_init, fcml_tf_instructions_f_suite_cleanup, fctl_ti_instructions_f },
    CU_SUITE_INFO_NULL,
};
