/*
 * FCML - Free Code Manipulation Library.
 * Copyright (C) 2010-2014 Slawomir Wojtasiak
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

/** @file fcml_parser.hpp
 * C++ wrapper for instruction parser.
 *
 * @copyright Copyright (C) 2010-2014 Slawomir Wojtasiak. All rights reserved.
 * This project is released under the GNU Lesser General Public License.
 */

#ifndef FCML_PARSER_HPP_
#define FCML_PARSER_HPP_

#include "fcml_common.hpp"
#include "fcml_symbols.hpp"
#include "fcml_errors.hpp"
#include "fcml_dialect.hpp"

#include "fcml_parser.h"

namespace fcml {

/**
 * Something failed while parsing.
 * @since 1.1.0
 */
class ParsingFailedException: public ErrorContainerAwareException {
public:
    ParsingFailedException( const fcml_cstring msg, ErrorContainer &errorContainer, fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR ) :
        ErrorContainerAwareException( msg, errorContainer, error ){
    }
};

/** Parser configuration.
 * @since 1.1.0
 */
class ParserConfig {
public:

    /**
     * Default constructor.
     * @since 1.1.0
     */
    ParserConfig() :
        _throwExceptionOnError(true),
        _ignoreUndefinedSymbols(false),
        _disableSymbolsDeclaration(true),
        _overrideLabels(false),
        _allocSymbolTableIfNeeded(false),
        _enableErrorMessages(true) {
    }

    /** @since 1.1.0 */
    bool isAllocSymbolTableIfNeeded() const {
        return _allocSymbolTableIfNeeded;
    }

    /** @since 1.1.0 */
    void setAllocSymbolTableIfNeeded(bool allocSymbolTableIfNeeded) {
        _allocSymbolTableIfNeeded = allocSymbolTableIfNeeded;
    }

    /** @since 1.1.0 */
    bool isDisableSymbolsDeclaration() const {
        return _disableSymbolsDeclaration;
    }

    /** @since 1.1.0 */
    void setDisableSymbolsDeclaration(bool disableSymbolsDeclaration) {
        _disableSymbolsDeclaration = disableSymbolsDeclaration;
    }

    /** @since 1.1.0 */
    bool isEnableErrorMessages() const {
        return _enableErrorMessages;
    }

    /** @since 1.1.0 */
    void setEnableErrorMessages(bool enableErrorMessages) {
        _enableErrorMessages = enableErrorMessages;
    }

    /** @since 1.1.0 */
    bool isIgnoreUndefinedSymbols() const {
        return _ignoreUndefinedSymbols;
    }

    /** @since 1.1.0 */
    void setIgnoreUndefinedSymbols(bool ignoreUndefinedSymbols) {
        _ignoreUndefinedSymbols = ignoreUndefinedSymbols;
    }

    /** @since 1.1.0 */
    bool isOverrideLabels() const {
        return _overrideLabels;
    }

    /** @since 1.1.0 */
    void setOverrideLabels(bool overrideLabels) {
        _overrideLabels = overrideLabels;
    }

    /**
     * Gets true if exception should be thrown in case of error.
     * @return True if exception should be thrown in case of error.
     * @since 1.1.0
     */
    bool isThrowExceptionOnError() const {
        return _throwExceptionOnError;
    }

    /**
     * Sets exception on error flag. Has to be set to true if exception should be thrown in case of error.
     * @param throwExceptionOnError True if exception should be thrown in case of error.
     * @since 1.1.0
     */
    void setThrowExceptionOnError(bool throwExceptionOnError) {
        _throwExceptionOnError = throwExceptionOnError;
    }

private:
    bool _throwExceptionOnError;
    bool _ignoreUndefinedSymbols;
    bool _disableSymbolsDeclaration;
    bool _overrideLabels;
    bool _allocSymbolTableIfNeeded;
    bool _enableErrorMessages;
};

/** Parser context.
 * @since 1.1.0
 */
class ParserContext {
public:

    /**
     * Creates a parser context instance for optional instruction pointer.
     *
     * @param ip The instruction pointer.
     * @since 1.1.0
     */
    ParserContext( fcml_ip ip = 0 ) :
        _ip(ip),
        _symbolTable(NULL) {
    }

    /**
     * Creates a parser context for given symbol table and optional instruction pointer.
     *
     * @param symbolTable The symbol table.
     * @param ip The instruction pointer.
     * @since 1.1.0
     */
    ParserContext( SymbolTable *symbolTable, fcml_ip ip = 0 ) :
        _ip(ip),
        _symbolTable(symbolTable) {
    }

public:

    /**
     * Gets the parser configuration associated with the context.
     *
     * @return The parser configuration associated with the context.
     * @since 1.1.0
     */
    const ParserConfig& getConfig() const {
        return _config;
    }

    /**
     * Gets the parser configuration associated with the context.
     *
     * @return The parser configuration associated with the context.
     * @since 1.1.0
     */
    ParserConfig& getConfig() {
        return _config;
    }

    /**
     * Gets the instruction pointer.
     *
     * @return The instruction pointer.
     * @since 1.1.0
     */
    fcml_ip getIp() const {
        return _ip;
    }

    /**
     * Gets a new instruction pointer.
     *
     * @param ip The new instruction pointer.
     * @since 1.1.0
     */
    void setIp(fcml_ip ip) {
        _ip = ip;
    }

    /**
     * Increments instruction pointer by given number of bytes.
     *
     * @param ip The number of bytes the instruction pointer has to be incremented by.
     * @since 1.1.0
     */
    void incrementIP( fcml_ip ip ) {
        _ip += ip;
    }

    /**
     * Gets the symbol table associated with the context.
     *
     * @return The symbol table.
     * @since 1.1.0
     */
    const SymbolTable* getSymbolTable() const {
        return _symbolTable;
    }

    /**
     * Gets the symbol table associated with the context.
     *
     * @return The symbol table.
     * @since 1.1.0
     */
    SymbolTable* getSymbolTable() {
        return _symbolTable;
    }

    /**
     * Sets a symbol table for the instruction.
     *
     * @param symbolTable The symbol table for the parser context.
     * @since 1.1.0
     */
    void setSymbolTable(SymbolTable* symbolTable) {
        _symbolTable = symbolTable;
    }

private:

    /** The instruction pointer used by declared labels. */
    fcml_ip _ip;
    /** The parser configuration. */
    ParserConfig _config;
    /** The symbol table. */
    SymbolTable *_symbolTable;

};

/** Parser result.
 * @since 1.1.0
 */
class ParserResult {
public:

    /**
     * Creates an empty parser result.
     * @since 1.1.0
     */
    ParserResult() {
    }

    /**
     * Gets errors container with parsing errors.
     *
     * @return Errors container.
     * @since 1.1.0
     */
    const ErrorContainer& getErrors() const {
        return _errors;
    }

    /**
     * Gets the parsed instruction.
     *
     * @return The parsed instruction.
     * @since 1.1.0
     */
    const Instruction& getInstruction() const {
        return _instruction;
    }

    /**
     * Gets declared symbol is there is any.
     * @return Gets symbol if there is any.
     * @since 1.1.0
     */
    const Nullable<Symbol> &getSymbol() const {
        return _symbol;
    }

    /**
     * Cleans the parser result.
     * @since 1.1.0
     */
    void clean() {
        _errors.clean();
        _symbol.setNotNull(false);
        _symbol.setValue(Symbol());
    }

protected:

    friend class Parser;

    /**
     * Sets error container for the context.
     * @param errors A new error container.
     * @since 1.1.0
     */
    void setErrors(const ErrorContainer& errors) {
        _errors = errors;
    }

    /**
     * Sets an instruction for the container.
     * @param instruction The instruction.
     * @since 1.1.0
     */
    void setInstruction(const Instruction& instruction) {
        _instruction = instruction;
    }

    /**
     * Sets symbol.
     * @param symbol The symbol.
     * @since 1.1.0
     */
    void setSymbol(const Nullable<Symbol>& symbol) {
        _symbol = symbol;
    }

private:

    /** Errors container. */
    ErrorContainer _errors;
    /** Gets declared symbol. Take into account that it can be 'empty'. */
    Nullable<Symbol> _symbol;
    /** The parsed instruction. */
    Instruction _instruction;

};

/**
 * Converts objects to their structures counterparts.
 * @since 1.1.0
 * @remarks Internal API, not intended to be used outside.
 */
class ParserTypeConverter {
public:

    static void convert( ParserConfig &src, fcml_st_parser_config &dest ) {
        dest.alloc_symbol_table_if_needed = src.isAllocSymbolTableIfNeeded();
        dest.disable_symbols_declaration = src.isDisableSymbolsDeclaration();
        dest.enable_error_messages = src.isEnableErrorMessages();
        dest.ignore_undefined_symbols = src.isIgnoreUndefinedSymbols();
        dest.override_labels = src.isOverrideLabels();
    }

};

/** Parser wrapper.
 * @since 1.1.0
 */
class Parser: protected DialectAware, protected SymbolTableAware {
public:

    /**
     * Creates a parser instance for the given dialect.
     *
     * @param dialect The dialect instance.
     * @since 1.1.0
     */
    Parser( const Dialect &dialect ) :
        _dialect(dialect) {
    }

    /**
     * Parses instruction given in the parameters.
     *
     * @param ctx Parser context.
     * @param instruction Instruction mnemonic.
     * @param[out] parserResult Instruction result.
     * @return Error code.
     * @throw ParsingFailedException Parsing failed.
     * @since 1.1.0
     */
    fcml_ceh_error parse( ParserContext &ctx, const fcml_cstring &instruction, ParserResult &parserResult ) {

        // Prepare parser context.
        fcml_st_parser_context context = {0};
        ParserTypeConverter::convert( ctx.getConfig(), context.configuration );
        context.ip = ctx.getIp();
        SymbolTable *symbolTable = ctx.getSymbolTable();
        context.symbol_table = ( symbolTable ) ? extractSymbolTable( *symbolTable ) : NULL;
        context.dialect = extractDialect( _dialect );

        fcml_st_parser_result parser_result;
        ::fcml_fn_parser_result_prepare( &parser_result );

        try {

            parserResult.clean();

            // Prepare instruction.
            fcml_ceh_error error = ::fcml_fn_parse( &context, instruction.c_str(), &parser_result );

            ErrorContainer errorContainer;
            ErrorTypeConverter::convert( parser_result.errors, errorContainer );

            parserResult.setErrors( errorContainer );

            if( !error && !parser_result.instruction ) {
                // Just in case, it should never happen.
                error = FCML_CEH_GEC_INTERNAL_ERROR;
            }

            if( error && ctx.getConfig().isThrowExceptionOnError() ) {
                ::fcml_fn_parser_result_free( &parser_result );
                throw ParsingFailedException( errorContainer.prepareErrorMessage( FCML_TEXT("Parsing failed") ), errorContainer, error );
            }

            if( !error ) {

                Instruction parsedInstruction;
                TypeConverter::convert( *(parser_result.instruction), parsedInstruction );

                parserResult.setInstruction( parsedInstruction );
                parserResult.setSymbol( parser_result.symbol ? Symbol( parser_result.symbol->symbol, parser_result.symbol->value ) : Symbol() );

            }

            ::fcml_fn_parser_result_free( &parser_result );

        } catch( std::exception &exc ) {
            // If anything failed, free assembler results.
            ::fcml_fn_parser_result_free( &parser_result );
            throw exc;
        }

        return FCML_CEH_GEC_NO_ERROR;
    }

private:

    /** The dialect for the parser. */
    const Dialect &_dialect;

};

}

#endif /* FCML_PARSER_HPP_ */
