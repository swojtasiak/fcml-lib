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

#include "fcml_disp8_n.h"

fcml_uint32_t fcml_fn_disp8_n_for_vector_len(fcml_uint32_t vector_len,
        fcml_uint32_t n128, fcml_uint32_t n256, fcml_uint32_t n512) {
    switch (vector_len) {
    case FCML_DS_128:
        return n128;
    case FCML_DS_256:
        return n256;
    case FCML_DS_512:
        return n512;
    default:
        return 0;
    }
}

fcml_uint32_t fcml_fn_d8n_calculate_n(fcml_uint32_t tuple_type,
        fcml_bool evex_b, fcml_uint32_t input_size, fcml_uint32_t vl) {

    fcml_uint32_t n = 0;

    switch (tuple_type) {

    case FCML_TT_FV:
        if (evex_b) {
            switch (input_size) {
            case FCML_DS_32:
                n = 4;
                break;
            case FCML_DS_64:
                n = 8;
                break;
            }
        } else if (input_size == FCML_DS_32 || input_size == FCML_DS_64) {
            n = fcml_fn_disp8_n_for_vector_len(vl, 16, 32, 64);
        }
        break;

    case FCML_TT_HV:
        if (evex_b) {
            switch (input_size) {
            case FCML_DS_32:
                n = 4;
                break;
            case FCML_DS_64:
                n = 8;
                break;
            }
        } else if (input_size == FCML_DS_32 || input_size == FCML_DS_64) {
            n = fcml_fn_disp8_n_for_vector_len(vl, 8, 16, 32);
        }
        break;

    case FCML_TT_FVM:
        n = fcml_fn_disp8_n_for_vector_len(vl, 16, 32, 64);
        break;

    case FCML_TT_T1S:
        switch (input_size) {
        case FCML_DS_8:
            n = 1;
            break;
        case FCML_DS_16:
            n = 2;
            break;
        case FCML_DS_32:
            n = 4;
            break;
        case FCML_DS_64:
            n = 8;
            break;
        }
        break;

    case FCML_TT_T1F:
        switch (input_size) {
        case FCML_DS_32:
            n = 4;
            break;
        case FCML_DS_64:
            n = 8;
            break;
        }
        break;

    case FCML_TT_T2:
        switch (input_size) {
        case FCML_DS_32:
            n = 8;
            break;
        case FCML_DS_64:
            n = fcml_fn_disp8_n_for_vector_len(vl, 0, 16, 16);
            break;
        }
        break;

    case FCML_TT_T4:
        switch (input_size) {
        case FCML_DS_32:
            n = fcml_fn_disp8_n_for_vector_len(vl, 0, 16, 16);
            break;
        case FCML_DS_64:
            n = fcml_fn_disp8_n_for_vector_len(vl, 0, 0, 32);
            break;
        }
        break;

    case FCML_TT_T8:
        if (input_size == FCML_DS_32) {
            n = fcml_fn_disp8_n_for_vector_len(vl, 0, 0, 32);
        }
        break;

    case FCML_TT_HVM:
        n = fcml_fn_disp8_n_for_vector_len(vl, 8, 16, 32);
        break;

    case FCML_TT_QVM:
        n = fcml_fn_disp8_n_for_vector_len(vl, 4, 8, 16);
        break;

    case FCML_TT_OVM:
        n = fcml_fn_disp8_n_for_vector_len(vl, 2, 4, 8);
        break;

    case FCML_TT_M128:
        n = 16;
        break;

    case FCML_TT_T1x4:
        n = 16;
        break;

    case FCML_TT_DUP:
        n = fcml_fn_disp8_n_for_vector_len(vl, 8, 32, 64);
        break;

    }

    return n;
}
