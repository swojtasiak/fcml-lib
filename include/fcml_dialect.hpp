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

/** @file fcml_dialect.hpp
 * C++ wrapper for the base dialect.
 *
 * @copyright Copyright (C) 2010-2020 Slawomir Wojtasiak. All rights reserved.
 * This project is released under the GNU Lesser General Public License.
 */

#ifndef FCML_DIALECT_HPP_
#define FCML_DIALECT_HPP_

#include "fcml_common.hpp"

#include "fcml_dialect.h"

namespace fcml {

/**
 * An abstract dialect. It's a base class for all supported dialects.
 * @since 1.1.0
 * @remarks This class is thread-safe.
 */
class Dialect: public NonCopyable {
protected:

    /**
     * Default constructor.
     * @since 1.1.0
     */
    Dialect() {
        _dialect = NULL;
    }

    /**
     * Virtual destructor.
     * @since 1.1.0
     */
    virtual ~Dialect() {
        if (_dialect) {
            ::fcml_fn_dialect_free(_dialect);
            _dialect = NULL;
        }
    }

protected:

    friend class DialectAware;

    /**
     * Gets the wrapped FCML dialect.
     *
     * @return The wrapped FCML dialect.
     * @since 1.1.0
     */
    fcml_st_dialect* getDialect() const {
        return _dialect;
    }

    /**
     * Sets a new dialect for the wrapper.
     *
     * @param dialect The new dialect for the wrapper.
     * @since 1.1.0
     */
    void setDialect(fcml_st_dialect *dialect) {
        this->_dialect = dialect;
    }

private:

    /** Wrapped dialect */
    fcml_st_dialect *_dialect;

};

/** Inherit from this class in order to get access to the native FCML
 * dialect structure.
 * @since 1.1.0
 */
class DialectAware {
public:

    /**
     * Default constructor.
     * @since 1.1.0
     */
    DialectAware() {
    }

    /**
     * Virtual destructor.
     * @since 1.1.0
     */
    virtual ~DialectAware() {
    }

    /**
     * Extracts the native FCML dialect from the dialect object.
     *
     * @param dialect The wrapper.
     * @return The wrapped FCML dialect.
     * @since 1.1.0
     */
    fcml_st_dialect* extractDialect(const Dialect &dialect) const {
        return dialect.getDialect();
    }
};

}

#endif /* FCML_DIALECT_HPP_ */
