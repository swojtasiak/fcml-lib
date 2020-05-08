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

#ifndef FCML_GAS_PARSER_H_
#define FCML_GAS_PARSER_H_

#include <fcml_types.h>
#include <fcml_errors.h>
#include <fcml_parser.h>

#include "fcml_parser_int.h"

fcml_ceh_error fcml_fn_gas_parse_instruction_to_ast(fcml_ip ip,
        const fcml_string mnemonic, fcml_st_parser_ast *ast);

#endif /* FCML_GAS_PARSER_H_ */
