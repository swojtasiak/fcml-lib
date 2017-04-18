/*
 * FCML - Free Code Manipulation Library.
 * Copyright (C) 2017 Slawomir Wojtasiak
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
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301
 * USA
 */

#ifndef SRC_FCML_DISP8_N_H_
#define SRC_FCML_DISP8_N_H_

#include "fcml_common.h"

/**
 * Decodes N size for disp8 * N displacement.
 *
 * If "input_size" is equal to 0 it means that input size is not available.
 *
 * Returns 0 if N is unknown.
 */
fcml_uint32_t fcml_fn_d8n_calculate_n(fcml_uint32_t tuple_type,
        fcml_bool evex_b, fcml_uint32_t input_size, fcml_uint32_t vector_len);

#endif /* SRC_FCML_DISP8_N_H_ */
