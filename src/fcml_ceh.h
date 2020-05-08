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

#ifndef FCML_CEH_H_
#define FCML_CEH_H_

#include <fcml_types.h>
#include <fcml_errors.h>

void fcml_fn_ceh_move_errors(fcml_st_ceh_error_container *destination,
        fcml_st_ceh_error_container *source);

void fcml_fn_ceh_free_errors_only(fcml_st_ceh_error_container *error_container);

void fcml_fn_ceh_free_errors_only_with_level(
        fcml_st_ceh_error_container *error_container,
        fcml_en_ceh_error_level level);

fcml_st_ceh_error_info *fcml_fn_ceh_add_error(
        fcml_st_ceh_error_container *error_container,
        const fcml_string message, fcml_ceh_error code,
        fcml_en_ceh_error_level level );

#endif /* FCML_CEH_H_ */
