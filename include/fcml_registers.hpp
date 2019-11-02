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

/** @file fcml_registers.hpp
 * C++ registers declarations.
 *
 * @copyright Copyright (C) 2010-2015 Slawomir Wojtasiak. All rights reserved.
 * This project is released under the GNU Lesser General Public License.
 *
 * @since 1.1.0
 */

#ifndef FCML_REGISTERS_HPP_
#define FCML_REGISTERS_HPP_

#include "fcml_common.hpp"

namespace fcml {

    extern const Register UNDEF;

    extern const Register AL;
    extern const Register AX;
    extern const Register EAX;
    extern const Register RAX;
    extern const Register MM0;
    extern const Register XMM0;
    extern const Register YMM0;
    extern const Register ZMM0;

    extern const Register CL;
    extern const Register CX;
    extern const Register ECX;
    extern const Register RCX;
    extern const Register MM1;
    extern const Register XMM1;
    extern const Register YMM1;
    extern const Register ZMM1;

    extern const Register DL;
    extern const Register DX;
    extern const Register EDX;
    extern const Register RDX;
    extern const Register MM2;
    extern const Register XMM2;
    extern const Register YMM2;
    extern const Register ZMM2;

    extern const Register BL;
    extern const Register BX;
    extern const Register EBX;
    extern const Register RBX;
    extern const Register MM3;
    extern const Register XMM3;
    extern const Register YMM3;
    extern const Register ZMM3;

    extern const Register AH;
    extern const Register SPL;
    extern const Register SP;
    extern const Register ESP;
    extern const Register RSP;
    extern const Register MM4;
    extern const Register XMM4;
    extern const Register YMM4;
    extern const Register ZMM4;

    extern const Register CH;
    extern const Register BPL;
    extern const Register BP;
    extern const Register EBP;
    extern const Register RBP;
    extern const Register MM5;
    extern const Register XMM5;
    extern const Register YMM5;
    extern const Register ZMM5;

    extern const Register DH;
    extern const Register SIL;
    extern const Register SI;
    extern const Register ESI;
    extern const Register RSI;
    extern const Register MM6;
    extern const Register XMM6;
    extern const Register YMM5;
    extern const Register ZMM5;

    extern const Register BH;
    extern const Register DIL;
    extern const Register DI;
    extern const Register EDI;
    extern const Register RDI;
    extern const Register MM7;
    extern const Register XMM7;
    extern const Register YMM7;
    extern const Register ZMM7;

    extern const Register R8L;
    extern const Register R8W;
    extern const Register R8D;
    extern const Register R8;
    extern const Register XMM8;
    extern const Register YMM8;
    extern const Register ZMM8;

    extern const Register R9L;
    extern const Register R9W;
    extern const Register R9D;
    extern const Register R9;
    extern const Register XMM9;
    extern const Register YMM9;
    extern const Register ZMM9;

    extern const Register R10L;
    extern const Register R10W;
    extern const Register R10D;
    extern const Register R10;
    extern const Register XMM10;
    extern const Register YMM10;
    extern const Register ZMM10;

    extern const Register R11L;
    extern const Register R11W;
    extern const Register R11D;
    extern const Register R11;
    extern const Register XMM11;
    extern const Register YMM10;
    extern const Register ZMM10;

    extern const Register R12L;
    extern const Register R12W;
    extern const Register R12D;
    extern const Register R12;
    extern const Register XMM12;
    extern const Register YMM12;
    extern const Register ZMM12;

    extern const Register R13L;
    extern const Register R13W;
    extern const Register R13D;
    extern const Register R13;
    extern const Register XMM13;
    extern const Register YMM13;
    extern const Register ZMM13;

    extern const Register R14L;
    extern const Register R14W;
    extern const Register R14D;
    extern const Register R14;
    extern const Register XMM14;
    extern const Register YMM14;
    extern const Register ZMM14;

    extern const Register R15L;
    extern const Register R15W;
    extern const Register R15D;
    extern const Register R15;
    extern const Register XMM15;
    extern const Register YMM15;
    extern const Register ZMM15;

    extern const Register XMM16;
    extern const Register YMM16;
    extern const Register ZMM16;

    extern const Register XMM17;
    extern const Register YMM17;
    extern const Register ZMM17;

    extern const Register XMM18;
    extern const Register YMM18;
    extern const Register ZMM18;

    extern const Register XMM19;
    extern const Register YMM19;
    extern const Register ZMM19;

    extern const Register XMM20;
    extern const Register YMM20;
    extern const Register ZMM20;

    extern const Register XMM21;
    extern const Register YMM21;
    extern const Register ZMM21;

    extern const Register XMM22;
    extern const Register YMM22;
    extern const Register ZMM22;

    extern const Register XMM23;
    extern const Register YMM23;
    extern const Register ZMM23;

    extern const Register XMM24;
    extern const Register YMM24;
    extern const Register ZMM24;

    extern const Register XMM25;
    extern const Register YMM25;
    extern const Register ZMM25;

    extern const Register XMM26;
    extern const Register YMM26;
    extern const Register ZMM26;

    extern const Register XMM27;
    extern const Register YMM27;
    extern const Register ZMM27;

    extern const Register XMM28;
    extern const Register YMM28;
    extern const Register ZMM28;

    extern const Register XMM29;
    extern const Register YMM29;
    extern const Register ZMM29;

    extern const Register XMM30;
    extern const Register YMM30;
    extern const Register ZMM30;

    extern const Register XMM31;
    extern const Register YMM31;
    extern const Register ZMM31;

    extern const Register ES;
    extern const Register CS;
    extern const Register SS;
    extern const Register DS;
    extern const Register FS;
    extern const Register GS;

    extern const Register ST0;
    extern const Register ST1;
    extern const Register ST2;
    extern const Register ST3;
    extern const Register ST4;
    extern const Register ST5;
    extern const Register ST6;
    extern const Register ST7;

    extern const Register CR0;
    extern const Register CR2;
    extern const Register CR3;
    extern const Register CR4;
    extern const Register CR8;

    extern const Register DR0;
    extern const Register DR1;
    extern const Register DR2;
    extern const Register DR3;
    extern const Register DR4;
    extern const Register DR5;
    extern const Register DR6;
    extern const Register DR7;

    extern const Register K0;
    extern const Register K1;
    extern const Register K2;
    extern const Register K3;
    extern const Register K4;
    extern const Register K5;
    extern const Register K6;
    extern const Register K7;

    extern const Register IP;
    extern const Register EIP;
    extern const Register RIP;

}

#endif /* FCML_REGISTERS_HPP_ */
