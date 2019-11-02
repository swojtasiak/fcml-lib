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

/** @file fcml_symbols.hpp
 * C++ API for symbols handling. Currently used only by parsers.
 *
 * @copyright Copyright (C) 2010-2015 Slawomir Wojtasiak. All rights reserved.
 * This project is released under the GNU Lesser General Public License.
 */

#ifndef FCML_SYMBOLS_HPP_
#define FCML_SYMBOLS_HPP_

#include <new>

#include "fcml_common.hpp"
#include "fcml_symbols.h"

namespace fcml {

/**
 * Represents one named symbol with associated value.
 * @since 1.1.0
 */
class Symbol {
public:

    /**
     * Creates an empty symbol.
     * @since 1.1.0
     */
    Symbol() :
            _value(0) {
    }

    /**
     * Creates a symbol instance for the given name and value.
     *
     * @param name The symbol name.
     * @param value The symbol value.
     * @since 1.1.0
     */
    Symbol(const fcml_cstring &name, fcml_int64_t value) :
            _name(name), _value(value) {
    }

    /**
     * Gets symbol value.
     * @since 1.1.0
     */
    operator fcml_uint64_t() const {
        return _value;
    }

    /**
     * Gets symbol value.
     * @since 1.1.0
     */
    operator fcml_int64_t() const {
        return static_cast<fcml_int64_t>(_value);
    }

    /**
     * Gets true if symbol is empty.
     *
     * @return True if symbol is empty.
     * @since 1.1.0
     */
    bool isEmpty() const {
        return _name.empty();
    }

    /**
     * Gets the symbol name.
     *
     * @return The symbol name.
     * @since 1.1.0
     */
    const fcml_cstring& getName() const {
        return _name;
    }

    /**
     * Gets the symbol value.
     *
     * @return The symbol value.
     * @since 1.1.0
     */
    fcml_uint64_t getValue() const {
        return _value;
    }

    /**
     * Sets a new symbol name.
     *
     * @param name The symbol name.
     * @since 1.1.0
     */
    void setName(const fcml_cstring &name) {
        _name = name;
    }

    /**
     * Sets a new symbol value.
     *
     * @param value The symbol value.
     * @since 1.1.0
     */
    void setValue(fcml_uint64_t value) {
        _value = value;
    }

private:

    // Symbol name.
    fcml_cstring _name;
    // Symbol value.
    fcml_uint64_t _value;

};

/* Due to the performance purposes and the way symbol table is managed
 * internally, it has to be wrapped directly without doing any conversions
 * when needed.
 * @since 1.1.0
 */
class SymbolTable: public NonCopyable {
public:

    /**
     * Creates an empty symbol table.
     * @throw InitException The symbol table can't be allocated.
     * @since 1.1.0
     */
    SymbolTable() :
            _symbolTable(NULL) {
        _symbolTable = ::fcml_fn_symbol_table_alloc();
        if (!_symbolTable) {
            throw InitException(
                    FCML_TEXT(
                            "Symbol table can not be initialized correctly."));
        }
    }

    /**
     * Destructor.
     * @since 1.1.0
     */
    virtual ~SymbolTable() {
        if (_symbolTable) {
            ::fcml_fn_symbol_table_free(_symbolTable);
            _symbolTable = NULL;
        }
    }

protected:

    friend class SymbolTableAware;

    /**
     * Gets native FCML symbol table.
     * @return  The native symbol table.
     * @since 1.1.0
     */
    fcml_st_symbol_table& getSymbolTable() {
        return _symbolTable;
    }

public:

    /**
     * Adds a new symbol to the table.
     *
     * @param symbolName The symbol name.
     * @param value The symbol value.
     * @since 1.1.0
     */
    void add(const fcml_cstring &symbolName, fcml_int64_t value) {
        if (::fcml_fn_symbol_add_raw(_symbolTable, symbolName.c_str(), value)
                == FCML_CEH_GEC_OUT_OF_MEMORY) {
            throw std::bad_alloc();
        }
    }

    /**
     * Removes symbol from the table.
     *
     * @param symbolName The symbol name.
     * @since 1.1.0
     */
    void remove(const fcml_cstring &symbolName) {
        const fcml_string key = symbolName.c_str();
        ::fcml_fn_symbol_remove(_symbolTable, key);
    }

    /**
     * Gets true if there is a symbol for the given name in the table.
     *
     * @param symbolName The symbol name.
     * @return true If symbol of the name exists in the table.
     * @since 1.1.0
     */
    bool contains(const fcml_cstring &symbolName) const {
        return ::fcml_fn_symbol_get(_symbolTable, symbolName.c_str()) != NULL;
    }

    /**
     * Gets the symbol of the given name. Checks Symbol.isEmpty method of the
     * returned symbol to check if there is such a symbol.
     *
     * @param symbolName The symbol name.
     * @return The found symbol.
     * @since 1.1.0
     */
    Symbol get(const fcml_cstring &symbolName) const {
        Symbol symbol;
        fcml_st_symbol *found_symbol = ::fcml_fn_symbol_get(_symbolTable,
                symbolName.c_str());
        if (found_symbol) {
            symbol.setName(found_symbol->symbol);
            symbol.setValue(found_symbol->value);
        }
        return symbol;
    }

private:
    /** The native FCML symbol table. */
    fcml_st_symbol_table _symbolTable;
};

/**
 * Derive from this class if you really need access to the native symbol table.
 * @since 1.1.0
 */
class SymbolTableAware {
public:

    /**
     * Extracts the native symbol table for the given symbol table wrapper.
     * @param symbolTable The symbol table wrapper.
     * @since 1.1.0
     */
    fcml_st_symbol_table& extractSymbolTable(SymbolTable &symbolTable) {
        return symbolTable.getSymbolTable();
    }
};

}
#endif /* FCML_SYMBOLS_HPP_ */
