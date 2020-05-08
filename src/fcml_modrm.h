/*
 * FCML - Free Code Manipulation Library.
 * Copyright (C) 2010-2020 Slawomir Wojtasiak
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

#ifndef FCML_MODRM_H_
#define FCML_MODRM_H_

#include <fcml_common.h>
#include <fcml_types.h>

typedef struct fcml_st_modrm {
    /* Register number specified by reg_opcode.*/
    fcml_uint8_t reg_opcode;
    /* True if register needs REX prefix to be encoded.*/
    fcml_bool reg_opcode_needs_rex;
    /* Register number specified by r/m when mod == 3.*/
    fcml_nuint8_t reg;
    /* Effective address.*/
    fcml_st_address address;
    /* True if RIP encoding is used.*/
    fcml_bool is_rip;
} fcml_st_modrm;

#endif /* FCML_MODRM_H_ */
