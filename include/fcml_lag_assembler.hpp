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

/** @file fcml_lag_assembler.hpp
 * C++ wrapper for the Multi-pass FCML assembler.
 *
 * @copyright Copyright (C) 2010-2015 Slawomir Wojtasiak. All rights reserved.
 * This project is released under the GNU Lesser General Public License.
 */

#ifndef FCML_LAG_ASSEMBLER_HPP_
#define FCML_LAG_ASSEMBLER_HPP_

#include "fcml_assembler.hpp"
#include "fcml_symbols.hpp"

#include "fcml_lag_assembler.h"

namespace fcml {

/** Assembler result which contains all assembled instructions. */
class MultiPassAssemblerResult {
public:

    /**
     * Default constructor.
     * @since 1.1.0
     */
    MultiPassAssemblerResult() {
    }

    /**
     * Virtual destructor.
     * @since 1.1.0
     */
    virtual ~MultiPassAssemblerResult() {
    }

public:

    /**
     * Gets error container.
     *
     * @return Error container.
     * @since 1.1.0
     */
    const ErrorContainer& getErrorContainer() const {
        return _errorContainer;
    }

    /**
     * Gets number of assembled instructions.
     * @return Number of assembled instructions.
     * @since 1.1.0
     */
    fcml_usize getSize() const {
        return _assembledInstructions.size();
    }

    /**
     * Gets one assembled instruction by its index.
     *
     * @param index The index of the assembled instruction.
     * @return One assembled instruction at given index.
     * @throw BadArgumentException
     * @since 1.1.0
     */
    const AssembledInstruction& operator[] ( fcml_usize index ) const {
        if( index > _assembledInstructions.size() ) {
            throw BadArgumentException(FCML_TEXT("Array index out of bound."), FCML_CEH_GEC_VALUE_OUT_OF_RANGE);
        }
        return _assembledInstructions[index];
    }

    /**
     * Gets constant vector of all assembled instructions.
     *
     * @return Assembled instructions.
     * @since 1.1.0
     */
    const std::vector<AssembledInstruction>& getAssembledInstructions() const {
        return _assembledInstructions;
    }

    /**
     * Gets iterator which allows to iterate through the whole machine code byte by byte.
     *
     * @return Iterator instance.
     * @since 1.1.0
     */
    CodeIterator getCodeIterator() {
        return CodeIterator( _assembledInstructions );
    }

    /**
     * Clears the result. Remember not to use the CodeIterator after the result is cleared up.
     * @since 1.1.0
     */
    void clear() {
        _errorContainer.clean();
        _assembledInstructions.clear();
    }

protected:

    /** Only the assembler can modify these objects. */
    friend class MultiPassAssembler;

    /**
     * Gets vector of all assembled instructions.
     *
     * @return Assembled instructions.
     * @since 1.1.0
     */
    std::vector<AssembledInstruction>& getAssembledInstructions() {
        return _assembledInstructions;
    }

    /**
     * Sets new error container for the result.
     *
     * @param errorContainer The new error container to be set.
     * @since 1.1.0
     */
    void setErrorContainer(const ErrorContainer& errorContainer) {
        _errorContainer = errorContainer;
    }

private:

    /** Errors container. */
    ErrorContainer _errorContainer;
    /** Vector of all assembled instructions. */
    std::vector<AssembledInstruction> _assembledInstructions;

};

/** Assembler context.
 * @since 1.1.0
 */
class MultiPassAssemblerContext {

public:

    /**
     * Default constructor.
     * @since 1.1.0
     */
    MultiPassAssemblerContext() :
        _symbolTable( NULL ) {
    }

    /**
     * Creates assembler context for given operating mode and instruction pointer.
     * @param operatingMode The operating mode.
     * @param ip The instruction pointer.
     * @since 1.1.0
     */
    MultiPassAssemblerContext( EntryPoint::OperatingMode operatingMode, fcml_ip ip = 0 ) :
        _entryPoint( operatingMode, ip ),
        _symbolTable( NULL ) {
    }

public:

    /**
     * Gets constant reference to assembler configuration.
     *
     * @return Assembler configuration.
     * @since 1.1.0
     */
    const AssemblerConf& getConfig() const {
        return _config;
    }

    /**
     * Gets reference to the assembler configuration.
     *
     * @return Assembler configuration.
     * @since 1.1.0
     */
    AssemblerConf& getConfig() {
        return _config;
    }

    /**
     * Sets a new assembler configuration.
     *
     * @return Assembler configuration.
     * @since 1.1.0
     */
    void setConfig(const AssemblerConf& config) {
        _config = config;
    }

    /**
     * Gets constant reference to the entry point.
     *
     * @return Entry point.
     * @since 1.1.0
     */
    const EntryPoint& getEntryPoint() const {
        return _entryPoint;
    }

    /**
     * Gets reference to the entry point.
     *
     * @return Entry point.
     * @since 1.1.0
     */
    EntryPoint& getEntryPoint() {
        return _entryPoint;
    }

    /**
     * Sets a new entry point.
     *
     * @param entryPoint Entry point to be set.
     * @since 1.1.0
     */
    void setEntryPoint(const EntryPoint& entryPoint) {
        _entryPoint = entryPoint;
    }

    /**
     * Sets a new instruction pointer.
     *
     * @param ip A new instruction pointer.
     * @since 1.1.0
     */
    void setIP( fcml_ip ip ) {
        _entryPoint.setIP(ip);
    }

    /**
     * Increments the instruction pointer by given number of bytes.
     *
     * @param ip The number of bytes the instruction pointer should be incremented by.
     * @since 1.1.0
     */
    void incrementIP( fcml_ip ip ) {
        _entryPoint.incrementIP( ip );
    }

    /**
     * Sets a new processor operating mode for the entry point.
     *
     * @param operatingMode The new operating mode.
     * @since 1.1.0
     */
    void setOperatingMode( EntryPoint::OperatingMode operatingMode ) {
        _entryPoint.setOpMode( operatingMode );
    }

    /**
     * Sets a new address size attribute for the entry point.
     *
     * @param addressSizeAttribute The address size attribute.
     * @since 1.1.0
     */
    void setAddressSizeAttribute( fcml_usize addressSizeAttribute ) {
       _entryPoint.setAddressSizeAttribute( addressSizeAttribute );
    }

    /**
     * Sets a new operand size attribute for the entry point.
     *
     * @param operandSizeAttribute The operand size attribute.
     * @since 1.1.0
     */
    void setOperandSizeAttribute( fcml_usize operandSizeAttribute ) {
       _entryPoint.setOperandSizeAttribute( operandSizeAttribute );
    }

    /**
     * Gets a pointer to the constant symbol table stored in the context.
     *
     * @return The pointer to the symbol table.
     * @since 1.1.0
     */
    const SymbolTable* getSymbolTable() const {
        return _symbolTable;
    }

    /**
     * Gets a pointer to the symbol table stored in the context.
     *
     * @return The pointer to the symbol table.
     * @since 1.1.0
     */
    SymbolTable* getSymbolTable() {
        return _symbolTable;
    }

    /**
     * Sets a new symbol table for the context.
     *
     * @param symbolTable The new symbol table to be set.
     * @since 1.1.0
     */
    void setSymbolTable( SymbolTable* symbolTable ) {
        _symbolTable = symbolTable;
    }

private:
    /** The entry point. */
    EntryPoint _entryPoint;
    /** The assembler configuration. */
    AssemblerConf _config;
    /** The symbol table assigned to the context. */
    SymbolTable *_symbolTable;
};

/**
 * An assembler wrapper, as you can see the assembler context is managed internally and
 * is not exposed outside.
 */
class MultiPassAssembler: public NonCopyable, protected DialectAware, protected SymbolTableAware {
public:

    /**
     * Creates multi-pass assembler for a dialect.
     * @param dialect The dialect for the assembler.
     * @throw InitException Cannot initialize the assembler.
     * @since 1.1.0
     */
    MultiPassAssembler(Dialect &dialect) :
            _dialect(dialect) {
        fcml_ceh_error error = ::fcml_fn_assembler_init( extractDialect( dialect ), &_assembler);
        if (error) {
            throw InitException(FCML_TEXT("Cannot initialize the assembler."), error);
        }
    }

    /**
     * Virtual destructor.
     * @since 1.1.0
     */
    virtual ~MultiPassAssembler() {
        if (_assembler) {
            ::fcml_fn_assembler_free(_assembler);
            _assembler = NULL;
        }
    }

public:

    /**
     * Assembles given instruction model.
     *
     * @param ctx Assembler context.
     * @param instructions A pointer to the NULL terminated array of the instructions.
     * @param[out] result Assembler result.
     * @throw AssemblingFailedException Assembler failed.
     * @return Error code.
     * @since 1.1.0
     */
    fcml_ceh_error assemble( MultiPassAssemblerContext &ctx, const fcml_string *instructions, MultiPassAssemblerResult &result ) {

        /* Prepare assembler context. */
        fcml_st_lag_assembler_context context = {0};

        AssemblerTypeConverter::convert( ctx.getConfig(), context.configuration );
        TypeConverter::convert( ctx.getEntryPoint(), context.entry_point );

        SymbolTable *symbolTable = ctx.getSymbolTable();
        context.symbol_table = symbolTable ? extractSymbolTable( *symbolTable ) : NULL;
        context.assembler = _assembler;

        /* Prepare assembler result. */
        fcml_st_lag_assembler_result res;
        ::fcml_fn_lag_assembler_result_prepare( &res );

        fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

        try {

            result.clear();

            error = ::fcml_fn_lag_assemble( &context, instructions, &res );

            /* Failed or not, convert assembler errors. */

            ErrorContainer errorContainer;
            ErrorTypeConverter::convert( res.errors, errorContainer );

            /* Prepares assembler result. */

            result.setErrorContainer( errorContainer );

            if( error && ctx.getConfig().isThrowExceptionOnError() ) {
                ::fcml_fn_lag_assembler_result_free( &res );
                throw AssemblingFailedException( errorContainer.prepareErrorMessage( FCML_TEXT("Assembling failed") ), errorContainer, error );
            }

            if( !error ) {

                std::vector<AssembledInstruction> &assembledInstructions = result.getAssembledInstructions();

                assembledInstructions.clear();

                ErrorContainer instructionWarnings;
                fcml_st_assembled_instruction *next_instruction = res.instructions;
                while( next_instruction ) {
                    fcml_st_ceh_error_container &instruction_warnings = next_instruction->warnings;
                    ErrorTypeConverter::convert( instruction_warnings, instructionWarnings );
                    const AssembledInstruction assembledInstruction( next_instruction->code, next_instruction->code_length, instructionWarnings );
                    assembledInstructions.push_back( assembledInstruction );
                    next_instruction = next_instruction->next;
                }

                // Convert it back to the context because it might have been
                // modified during assembling process (IP incrementation etc).
                TypeConverter::convert( context.entry_point, ctx.getEntryPoint() );

            }

            ::fcml_fn_lag_assembler_result_free( &res );

        } catch( std::exception &exc ) {
            // If anything failed, free assembler results.
            ::fcml_fn_lag_assembler_result_free( &res );
            throw exc;
        }

        return error;
    }

private:

    // The dialect used by the assembler.
    Dialect &_dialect;
    // The initialized assembler instance used by the wrapper.
    fcml_st_assembler *_assembler;

};

}

#endif /* FCML_LAG_ASSEMBLER_HPP_ */
