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

/** @file fcml_registers.cpp
 * C++ registers definitions.
 *
 * @copyright Copyright (C) 2010-2015 Slawomir Wojtasiak. All rights reserved.
 * This project is released under the GNU Lesser General Public License.
 *
 * @since 1.1.0
 */

#ifndef _FCML_CPP_REGISTERS
#define _FCML_CPP_REGISTERS

#include "fcml_registers.hpp"

namespace fcml {

	const Register UNDEF( 0, 0, Register::REG_UNDEFINED, FCML_FALSE );

    const Register AL( ::fcml_reg_AL );
    const Register AX( ::fcml_reg_AX );
    const Register EAX( ::fcml_reg_EAX );
    const Register RAX( ::fcml_reg_RAX );
    const Register MM0( ::fcml_reg_MM0 );
    const Register XMM0( ::fcml_reg_XMM0 );
    const Register YMM0( ::fcml_reg_YMM0 );

    const Register CL( ::fcml_reg_CL );
    const Register CX( ::fcml_reg_CX );
    const Register ECX( ::fcml_reg_ECX );
    const Register RCX( ::fcml_reg_RCX );
    const Register MM1( ::fcml_reg_MM1 );
    const Register XMM1( ::fcml_reg_XMM1 );
    const Register YMM1( ::fcml_reg_YMM1 );

    const Register DL( ::fcml_reg_DL );
    const Register DX( ::fcml_reg_DX );
    const Register EDX( ::fcml_reg_EDX );
    const Register RDX( ::fcml_reg_RDX );
    const Register MM2( ::fcml_reg_MM2 );
    const Register XMM2( ::fcml_reg_XMM2 );
    const Register YMM2( ::fcml_reg_YMM2 );

    const Register BL( ::fcml_reg_BL );
    const Register BX( ::fcml_reg_BX );
    const Register EBX( ::fcml_reg_EBX );
    const Register RBX( ::fcml_reg_RBX );
    const Register MM3( ::fcml_reg_MM3 );
    const Register XMM3( ::fcml_reg_XMM3 );
    const Register YMM3( ::fcml_reg_YMM3 );

    const Register AH( ::fcml_reg_AH );
    const Register SPL( ::fcml_reg_SPL );
    const Register SP( ::fcml_reg_SP );
    const Register ESP( ::fcml_reg_ESP );
    const Register RSP( ::fcml_reg_RSP );
    const Register MM4( ::fcml_reg_MM4 );
    const Register XMM4( ::fcml_reg_XMM4 );
    const Register YMM4( ::fcml_reg_YMM4 );

    const Register CH( ::fcml_reg_CH );
    const Register BPL( ::fcml_reg_BPL );
    const Register BP( ::fcml_reg_BP );
    const Register EBP( ::fcml_reg_EBP );
    const Register RBP( ::fcml_reg_RBP );
    const Register MM5( ::fcml_reg_MM5 );
    const Register XMM5( ::fcml_reg_XMM5 );
    const Register YMM5( ::fcml_reg_YMM5 );

    const Register DH( ::fcml_reg_DH );
    const Register SIL( ::fcml_reg_SIL );
    const Register SI( ::fcml_reg_SI );
    const Register ESI( ::fcml_reg_ESI );
    const Register RSI( ::fcml_reg_RSI );
    const Register MM6( ::fcml_reg_MM6 );
    const Register XMM6( ::fcml_reg_XMM6 );
    const Register YMM6( ::fcml_reg_YMM6 );

    const Register BH( ::fcml_reg_BH );
    const Register DIL( ::fcml_reg_DIL );
    const Register DI( ::fcml_reg_DI );
    const Register EDI( ::fcml_reg_EDI );
    const Register RDI( ::fcml_reg_RDI );
    const Register MM7( ::fcml_reg_MM7 );
    const Register XMM7( ::fcml_reg_XMM7 );
    const Register YMM7( ::fcml_reg_YMM7 );

    const Register R8L( ::fcml_reg_R8L );
    const Register R8W( ::fcml_reg_R8W );
    const Register R8D( ::fcml_reg_R8D );
    const Register R8( ::fcml_reg_R8 );
    const Register XMM8( ::fcml_reg_XMM8 );
    const Register YMM8( ::fcml_reg_YMM8 );

    const Register R9L( ::fcml_reg_R9L );
    const Register R9W( ::fcml_reg_R9W );
    const Register R9D( ::fcml_reg_R9D );
    const Register R9( ::fcml_reg_R9 );
    const Register XMM9( ::fcml_reg_XMM9 );
    const Register YMM9( ::fcml_reg_YMM9 );

    const Register R10L( ::fcml_reg_R10L );
    const Register R10W( ::fcml_reg_R10W );
    const Register R10D( ::fcml_reg_R10D );
    const Register R10( ::fcml_reg_R10 );
    const Register XMM10( ::fcml_reg_XMM10 );
    const Register YMM10( ::fcml_reg_YMM10 );

    const Register R11L( ::fcml_reg_R11L );
    const Register R11W( ::fcml_reg_R11W );
    const Register R11D( ::fcml_reg_R11D );
    const Register R11( ::fcml_reg_R11 );
    const Register XMM11( ::fcml_reg_XMM11 );
    const Register YMM11( ::fcml_reg_YMM11 );

    const Register R12L( ::fcml_reg_R12L );
    const Register R12W( ::fcml_reg_R12W );
    const Register R12D( ::fcml_reg_R12D );
    const Register R12( ::fcml_reg_R12 );
    const Register XMM12( ::fcml_reg_XMM12 );
    const Register YMM12( ::fcml_reg_YMM12 );

    const Register R13L( ::fcml_reg_R13L );
    const Register R13W( ::fcml_reg_R13W );
    const Register R13D( ::fcml_reg_R13D );
    const Register R13( ::fcml_reg_R13 );
    const Register XMM13( ::fcml_reg_XMM13 );
    const Register YMM13( ::fcml_reg_YMM13 );

    const Register R14L( ::fcml_reg_R14L );
    const Register R14W( ::fcml_reg_R14W );
    const Register R14D( ::fcml_reg_R14D );
    const Register R14( ::fcml_reg_R14 );
    const Register XMM14( ::fcml_reg_XMM14 );
    const Register YMM14( ::fcml_reg_YMM14 );

    const Register R15L( ::fcml_reg_R15L );
    const Register R15W( ::fcml_reg_R15W );
    const Register R15D( ::fcml_reg_R15D );
    const Register R15( ::fcml_reg_R15 );
    const Register XMM15( ::fcml_reg_XMM15 );
    const Register YMM15( ::fcml_reg_YMM15 );

    const Register ES( ::fcml_reg_ES );
    const Register CS( ::fcml_reg_CS );
    const Register SS( ::fcml_reg_SS );
    const Register DS( ::fcml_reg_DS );
    const Register FS( ::fcml_reg_FS );
    const Register GS( ::fcml_reg_GS );

    const Register ST0( ::fcml_reg_ST0 );
    const Register ST1( ::fcml_reg_ST1 );
    const Register ST2( ::fcml_reg_ST2 );
    const Register ST3( ::fcml_reg_ST3 );
    const Register ST4( ::fcml_reg_ST4 );
    const Register ST5( ::fcml_reg_ST5 );
    const Register ST6( ::fcml_reg_ST6 );
    const Register ST7( ::fcml_reg_ST7 );

    const Register CR0( ::fcml_reg_CR0 );
    const Register CR2( ::fcml_reg_CR2 );
    const Register CR3( ::fcml_reg_CR3 );
    const Register CR4( ::fcml_reg_CR4 );
    const Register CR8( ::fcml_reg_CR8 );

    const Register DR0( ::fcml_reg_DR0 );
    const Register DR1( ::fcml_reg_DR1 );
    const Register DR2( ::fcml_reg_DR2 );
    const Register DR3( ::fcml_reg_DR3 );
    const Register DR4( ::fcml_reg_DR4 );
    const Register DR5( ::fcml_reg_DR5 );
    const Register DR6( ::fcml_reg_DR6 );
    const Register DR7( ::fcml_reg_DR7 );

    const Register IP( ::fcml_reg_IP );
    const Register EIP( ::fcml_reg_EIP );
    const Register RIP( ::fcml_reg_RIP );

}

#endif
