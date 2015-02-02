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

/** @file fcml_gas_dialect.hpp
 * C++ wrapper for the AT&T dialect.
 *
 * @copyright Copyright (C) 2010-2015 Slawomir Wojtasiak. All rights reserved.
 * This project is released under the GNU Lesser General Public License.
 */

#ifndef FCML_GAS_DIALECT_HPP_
#define FCML_GAS_DIALECT_HPP_

#include "fcml_dialect.hpp"

#include "fcml_gas_dialect.h"

namespace fcml {

/** Wraps the AT&T dialect.
 * @since 1.1.0
 */
class GASDialect: public Dialect {
public:
    /**
     * Creates AT&T dialect.
     *
     * @param flags Optional flags.
     * @since 1.1.0
     */
    GASDialect( fcml_uint32_t flags = FCML_GAS_DIALECT_CF_DEFAULT ) {
        fcml_st_dialect *dialect;
        fcml_ceh_error error = ::fcml_fn_dialect_init_gas( flags, &dialect );
        if ( error ) {
            throw InitException( FCML_TEXT( "Can not initialize the AT&T dialect." ), error );
        }
        setDialect( dialect );
    }
    /**
     * Virtual destructor.
     * @since 1.1.0
     */
    virtual ~GASDialect() {
    }
};

}

#endif /* FCML_GAS_DIALECT_HPP_ */
