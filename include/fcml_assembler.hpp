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

/** @file fcml_assembler.hpp
 * C++ wrapper for FCML assembler.
 *
 * @copyright Copyright (C) 2010-2015 Slawomir Wojtasiak. All rights reserved.
 * This project is released under the GNU Lesser General Public License.
 */

#ifndef FCML_ASSEMBLER_HPP_
#define FCML_ASSEMBLER_HPP_

#include <vector>
#include <ostream>

#include "fcml_assembler.h"

#include "fcml_common.hpp"
#include "fcml_errors.hpp"
#include "fcml_dialect.hpp"

namespace fcml {

/**
 *  Assembling failed.
 *  @since 1.1.0
 */
class AssemblingFailedException: public ErrorContainerAwareException {
public:
    AssemblingFailedException( const fcml_cstring msg, ErrorContainer errorContainer = ErrorContainer(), fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR ) :
        ErrorContainerAwareException( msg, errorContainer, error ){
    }
};

/** Describes an assembled instruction.
 * @since 1.1.0
 */
class AssembledInstruction {
public:

    /**
     * Creates an assembled instruction basing on given code buffer and errors.
     *
     * @param buffer Pointer to the machine code buffer.
     * @param len Number of machine code bytes.
     * @param errorContainer Potential warnings related to the assembled instruction.
     * @since 1.1.0
     *
     */
    AssembledInstruction( const fcml_uint8_t *buffer, fcml_usize len, const ErrorContainer &errorContainer ) {
        set( buffer, len, errorContainer );
    }

    /**
     * Copy constructor.
     * @since 1.1.0
     */
    AssembledInstruction( const AssembledInstruction& cpy ) {
        set( cpy._code, cpy._codeLength, cpy._warningContainer );
    }

    /**
     * Copies one instruction into another.
     *
     * @param cpy The source instruction.
     * @return A reference to the destination instruction.
     * @since 1.1.0
     */
    AssembledInstruction& operator=( const AssembledInstruction &cpy ) {
        if ( &cpy != this ) {
            if( this->_code ) {
                delete [] this->_code;
            }
            set( cpy._code, cpy._codeLength, cpy._warningContainer );
        }
        return *this;
    }

    /**
     * @since 1.1.0
     */
    virtual ~AssembledInstruction() {
        if( _code ) {
            delete [] _code;
            _code = NULL;
        }
    }

public:

    /**
     * Gets pointer to machine code buffer.
     *
     * @return Pointer to machine code buffer.
     * @since 1.1.0
     */
    const fcml_uint8_t* getCode() const {
        return _code;
    }

    /**
     * Gets number of bytes in the buffer.
     *
     * @return Number of bytes in the buffer.
     * @since 1.1.0
     */
    fcml_usize getCodeLength() const {
        return _codeLength;
    }

    /**
     * Gets reference to the errors container.
     *
     * @return A reference to the errors container.
     * @since 1.1.0
     */
    const ErrorContainer& getWarningContainer() const {
        return _warningContainer;
    }

private:

    /**
     * Fills the assembled instruction with new data.
     *
     * @param buffer The code buffer.
     * @param len The code buffer lenght.
     * @param warnings The warnings container.
     * @since 1.1.0
     */
    void set( const fcml_uint8_t *buffer, fcml_usize len, const ErrorContainer warnigns ) {
        _warningContainer = warnigns;
        if( len > 0 ) {
            _code = new fcml_uint8_t[len];
            for( fcml_usize i = 0; i < len; i++ ) {
                _code[i] = buffer[i];
            }
        } else {
            _code = NULL;
        }
        _codeLength = len;
    }

private:

    /** Warnings related to this instruction. */
    ErrorContainer _warningContainer;

    /** Pointer to the instruction machine code. */
    fcml_uint8_t *_code;

    /** Number of machine code bytes in the array above. */
    fcml_usize _codeLength;

};

class Assembler;

/** Assembler result. */
class AssemblerResult {
public:

    /**
     * @since 1.1.0
     */
    AssemblerResult() :
        _chosenInstructionIndex(-1) {
    }

public:

    /**
     * Gets instruction chosen by the assembler as the preferred one.
     *
     * @return Preferred instruction.
     * @since 1.1.0
     */
    const AssembledInstruction* getChosenInstruction() const {
        if( _chosenInstructionIndex == -1 ) {
            return NULL;
        }
        return &(_assembledInstructions[ _chosenInstructionIndex ]);
    }

    /**
     * Gets errors container.
     *
     * @return Errors container.
     * @since 1.1.0
     */
    const ErrorContainer& getErrorContainer() const {
        return _errorContainer;
    }

    /**
     * Gets number of instructions alternatives available in the result.
     *
     * @return Number of available instructions.
     * @since 1.1.0
     */
    fcml_usize getSize() const {
		return static_cast<fcml_usize>(_assembledInstructions.size());
    }

    /**
     * Gets pointer to the chosen instruction.
     *
     * @return Pointer to the chosen instruction.
     * @since 1.1.0
     */
    operator const AssembledInstruction*() const {
        if( _chosenInstructionIndex == -1 ) {
            return NULL;
        }
        return &(_assembledInstructions[_chosenInstructionIndex]);
    }

    /**
     * Gets an assembled instruction reference by its index.
     *
     * @return The assembled instruction for given index.
     * @throw BadArgumentException Array index out of bound.
     * @since 1.1.0
     */
    const AssembledInstruction& operator[] ( fcml_usize index ) const {
        if( index > _assembledInstructions.size() ) {
            throw BadArgumentException(FCML_TEXT("Array index out of bound."), FCML_CEH_GEC_VALUE_OUT_OF_RANGE);
        }
        return _assembledInstructions[index];
    }

    /**
     * Copies machine code of the chosen instruction to the output stream.
     *
     * @param[out] out Output stream.
     * @param result Assembler result.
     * @return Output stream from the parameter.
     * @since 1.1.0
     */
    friend std::basic_ostream<fcml_uint8_t>& operator<< ( std::basic_ostream<fcml_uint8_t> &out, const AssemblerResult &result ) {
        const AssembledInstruction *assembled = result.getChosenInstruction();
        if( assembled ) {
            // If chosen instruction is not available, do not
            // stream anything. It's not so common, because
            // instructions choosers are obliged to chose something.
            if( assembled->getCode() && assembled->getCodeLength() > 0 ) {
                out.write( assembled->getCode(), assembled->getCodeLength() );
            }
        }
        return out;
    }

    /**
     * Clears assembler result by removing all assembled instructions, errors and reseting the chosen instruction.
     * @since 1.1.0
     */
    void clear() {
        _errorContainer.clean();
        _assembledInstructions.clear();
        _chosenInstructionIndex = -1;
    }

protected:

    friend Assembler;

    void setErrorContainer(const ErrorContainer& errorContainer) {
        _errorContainer = errorContainer;
    }

    std::vector<AssembledInstruction>& getAssembledInstructions() {
        return _assembledInstructions;
    }

    void setChoosenInstructionIndex( fcml_int index ) {
        _chosenInstructionIndex = index;
    }

private:

    /** Assembling errors. */
    ErrorContainer _errorContainer;
    /** All assembled instructions are going here. */
    std::vector<AssembledInstruction> _assembledInstructions;
    /** Index for the chosen instruction. */
    fcml_int _chosenInstructionIndex;

};

/** Assembler configuration.
 * For more information about the flags, see fcml_st_assembler_conf structure documentation.
 * @since 1.1.0
 */
class AssemblerConf {
public:

    /**
     * @since 1.1.0
     */
    AssemblerConf() :
        _throwExceptionOnError(true),
        _incrementIp(true),
        _enableErrorMessages(true),
        _chooseSibEncoding(false),
        _chooseAbsEncoding(false),
        _forceRexPrefix(false),
        _forceThreeByteVEX(false),
        _noBranchPrediction(false),
        _optimizer(NULL),
        _optimizerFlags(0),
        _chooser(NULL) {
    }

public:

    /**
     * @since 1.1.0
     */
    bool isChooseAbsEncoding() const {
        return _chooseAbsEncoding;
    }

    /**
     * @since 1.1.0
     */
    void setChooseAbsEncoding(bool chooseAbsEncoding) {
        _chooseAbsEncoding = chooseAbsEncoding;
    }

    /**
     * @since 1.1.0
     */
    fcml_fnp_asm_instruction_chooser getChooser() const {
        return _chooser;
    }

    /**
     * @since 1.1.0
     */
    void setChooser(fcml_fnp_asm_instruction_chooser chooser) {
        _chooser = chooser;
    }

    /**
     * @since 1.1.0
     */
    bool isChooseSibEncoding() const {
        return _chooseSibEncoding;
    }

    /**
     * @since 1.1.0
     */
    void setChooseSibEncoding(bool chooseSibEncoding) {
        _chooseSibEncoding = chooseSibEncoding;
    }

    /**
     * @since 1.1.0
     */
    bool isEnableErrorMessages() const {
        return _enableErrorMessages;
    }

    /**
     * @since 1.1.0
     */
    void setEnableErrorMessages(bool enableErrorMessages) {
        _enableErrorMessages = enableErrorMessages;
    }

    /**
     * @since 1.1.0
     */
    bool isForceRexPrefix() const {
        return _forceRexPrefix;
    }

    /**
     * @since 1.1.0
     */
    void setForceRexPrefix(bool forceRexPrefix) {
        _forceRexPrefix = forceRexPrefix;
    }

    /**
     * @since 1.1.0
     */
    bool isForceThreeByteVex() const {
        return _forceThreeByteVEX;
    }

    /**
     * @since 1.1.0
     */
    void setForceThreeByteVex(bool forceThreeByteVex) {
        _forceThreeByteVEX = forceThreeByteVex;
    }

    /**
     * @since 1.1.0
     */
    bool isIncrementIp() const {
        return _incrementIp;
    }

    /**
     * @since 1.1.0
     */
    void setIncrementIp(bool incrementIp) {
        _incrementIp = incrementIp;
    }

    /**
     * @since 1.1.0
     */
    fcml_fnp_asm_optimizer getOptimizer() const {
        return _optimizer;
    }

    /**
     * @since 1.1.0
     */
    void setOptimizer(fcml_fnp_asm_optimizer optimizer) {
        _optimizer = optimizer;
    }

    /**
     * @since 1.1.0
     */
    fcml_uint16_t getOptimizerFlags() const {
        return _optimizerFlags;
    }

    /**
     * @since 1.1.0
     */
    void setOptimizerFlags(fcml_uint16_t optimizerFlags) {
        _optimizerFlags = optimizerFlags;
    }

    /**
     * Returns true if exception should be thrown when assembling fails.
     *
     * @return True if exception is the preferred way of error handling in case of failure.
     * @since 1.1.0
     */
    bool isThrowExceptionOnError() const {
        return _throwExceptionOnError;
    }

    /**
     * Sets the way how the error handling is done.
     *
     * @param throwExceptionOnError True if exception should be thrown in case of failure.
     * @since 1.1.0
     */
    void setThrowExceptionOnError(bool throwExceptionOnError) {
        _throwExceptionOnError = throwExceptionOnError;
    }

private:
    bool _throwExceptionOnError;
    bool _incrementIp;
    bool _enableErrorMessages;
    bool _chooseSibEncoding;
    bool _chooseAbsEncoding;
    bool _forceRexPrefix;
    bool _forceThreeByteVEX;
    bool _noBranchPrediction;
    fcml_fnp_asm_optimizer _optimizer;
    fcml_uint16_t _optimizerFlags;
    fcml_fnp_asm_instruction_chooser _chooser;
};

/** Assembler context.
 *
 * It is a counterpart to the fcml_st_assembler_context structure.
 * @since 1.1.0
 */
class AssemblerContext {

public:

    /**
     * @since 1.1.0
     */
    AssemblerContext() {
    }

    /**
     * Creates an entry point instance for given operating mode and optional instruction pointer.
     *
     * @param operatingMode The processor operating mode.
     * @param ip The instruction pointer.
     * @since 1.1.0
     */
    AssemblerContext( EntryPoint::OperatingMode operatingMode, fcml_ip ip = 0 ) :
        _entryPoint( operatingMode, ip ) {
    }

public:

    /**
     * Gets constant assembler configuration associated with the context.
     *
     * @return Assembler configuration.
     * @since 1.1.0
     */
    const AssemblerConf& getConfig() const {
        return _config;
    }

    /**
     * Gets assembler configuration associated with the context.
     *
     * @return Assembler configuration.
     * @since 1.1.0
     */
    AssemblerConf& getConfig() {
        return _config;
    }

    /**
     * Copies given configuration to the instance associated with the context.
     * Deep copy is performed, so passed object not need to be maintained as
     * long as the context is used.
     *
     * @param config Configuration that is copied to the context.
     * @since 1.1.0
     */
    void setConfig(const AssemblerConf &config) {
        _config = config;
    }

    /**
     * Gets reference to the constant entry point instance associated with the context.
     *
     * @return Reference to the constant entry point.
     * @since 1.1.0
     */
    const EntryPoint& getEntryPoint() const {
        return _entryPoint;
    }

    /**
     * Gets reference to the entry point instance associated with the context.
     *
     * @return Reference to the entry point.
     * @since 1.1.0
     */
    EntryPoint& getEntryPoint() {
        return _entryPoint;
    }
    /**
     * Copies given entry point to the instance associated with the context.
     * Deep copy is performed, so passed object not need to be maintained as
     * long as the context is used.
     *
     * @param entryPoint The entry point.
     * @since 1.1.0
     */
    void setEntryPoint(const EntryPoint &entryPoint) {
        _entryPoint = entryPoint;
    }

    /**
     * Sets instruction pointer directly into the entry point.
     *
     * @param ip The new IP.
     * @since 1.1.0
     */
    void setIP( fcml_ip ip ) {
        _entryPoint.setIP(ip);
    }

    /**
     * Increments entry point by given number of bytes.
     *
     * @param ip Number of bytes the instruction pointer has to be incremented by.
     * @since 1.1.0
     */
    void incrementIP( fcml_ip ip ) {
        _entryPoint.incrementIP( ip );
    }

    /**
     * Sets processor operating mode directly into the entry point.
     *
     * @param operatingMode Processor operating mode to be set.
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

private:

    /** Entry point associated with the context. */
    EntryPoint _entryPoint;
    /** Assembler configuration associated with the context. */
    AssemblerConf _config;

};

/** Converts objects to their structures counterparts.
 * @since 1.1.0
 * @remarks Internal API, not intended to be used outside.
 */
class AssemblerTypeConverter {
public:

    static void convert( const fcml_st_assembler_context &src, AssemblerContext &dest ) {
        // Converts assembler configuration and entry point. Both of them
        // have dedicated conversion methods.
        convert( src.configuration, dest.getConfig() );
        TypeConverter::convert( src.entry_point, dest.getEntryPoint() );
    }

    static void convert( const AssemblerContext &src, fcml_st_assembler_context &dest ) {
        // Converts assembler configuration and entry point. Both of them
        // have dedicated conversion methods.
        convert( src.getConfig(), dest.configuration );
        TypeConverter::convert( src.getEntryPoint(), dest.entry_point );
    }

    static void convert( const fcml_st_assembler_conf &src, AssemblerConf &dest ) {
		dest.setChooseAbsEncoding( FCML_TO_CPP_BOOL( src.choose_abs_encoding ) );
        dest.setChooseSibEncoding( FCML_TO_CPP_BOOL( src.choose_sib_encoding ) );
        dest.setChooser( src.chooser );
        dest.setEnableErrorMessages( FCML_TO_CPP_BOOL( src.enable_error_messages ) );
        dest.setForceRexPrefix( FCML_TO_CPP_BOOL( src.force_rex_prefix ) );
        dest.setForceThreeByteVex( FCML_TO_CPP_BOOL( src.force_three_byte_VEX ) );
        dest.setIncrementIp( FCML_TO_CPP_BOOL( src.increment_ip ) );
        dest.setOptimizer( src.optimizer );
        dest.setOptimizerFlags( src.optimizer_flags );
    }

    static void convert( const AssemblerConf &src, fcml_st_assembler_conf &dest ) {
        dest.choose_abs_encoding = src.isChooseAbsEncoding();
        dest.choose_sib_encoding = src.isChooseSibEncoding();
        dest.chooser = src.getChooser();
        dest.enable_error_messages = src.isEnableErrorMessages();
        dest.force_rex_prefix = src.isForceRexPrefix();
        dest.force_three_byte_VEX = src.isForceThreeByteVex();
        dest.increment_ip = src.isIncrementIp();
        dest.optimizer = src.getOptimizer();
        dest.optimizer_flags = src.getOptimizerFlags();
    }

};

/**
 * An assembler wrapper.
 * As you can see the assembler instance is managed internally and is not exposed outside.
 * @since 1.1.0
 * @remarks This class is thread-safe.
 */
class Assembler: public NonCopyable, protected DialectAware {
public:

    /**
     * Creates an assembler instance for given dialect.
     *
     * @param dialect The dialect for the assembler instance.
     * @throw InitException Cannot initialize the assembler.
     * @since 1.1.0
     */
    Assembler(Dialect &dialect) :
            _dialect(dialect) {
        fcml_ceh_error error = ::fcml_fn_assembler_init( extractDialect( dialect ), &_assembler);
        if (error) {
            throw InitException(FCML_TEXT("Cannot initialize the assembler."), error);
        }
    }

    /**
     * @since 1.1.0
     */
    virtual ~Assembler() {
        if (_assembler) {
            ::fcml_fn_assembler_free(_assembler);
            _assembler = NULL;
        }
    }

public:

    /**
     * Assembles given generic instruction model.
     *
     * @param ctx The assembler context.
     * @param instruction The generic instruction model to be assembled.
     * @param[out] result Assembler result.
     * @throw AssemblingFailedException Thrown if assembling fails and AssemblerConf.isThrowExceptionOnError returns true.
     * @return Error code.
     * @since 1.1.0
     */
    fcml_ceh_error assemble( AssemblerContext &ctx, const Instruction &instruction, AssemblerResult &result ) {

        // Prepare assembler context.
        fcml_st_assembler_context context;
        AssemblerTypeConverter::convert( ctx, context );

        context.assembler = _assembler;

        // Prepare instruction.
        fcml_st_instruction inst;
        TypeConverter::convert( instruction, inst );

        // Prepare assembler result.
        fcml_st_assembler_result res;
        ::fcml_fn_assembler_result_prepare( &res );

        fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

        try {

            result.clear();

            error = ::fcml_fn_assemble( &context, &inst, &res );

            // Free instruction mnemonic.
            TypeConverter::free( inst );

            // Failed or not, convert assembler errors.
            ErrorContainer errorContainer;
            ErrorTypeConverter::convert( res.errors, errorContainer );

            // Prepares assembler result.
            result.setErrorContainer( errorContainer );

            if( error && ctx.getConfig().isThrowExceptionOnError() ) {
                ::fcml_fn_assembler_result_free( &res );
                throw AssemblingFailedException( FCML_TEXT("Assembling failed."), errorContainer, error );
            }

            if( !error ) {

                std::vector<AssembledInstruction> &assembledInstructions = result.getAssembledInstructions();

                assembledInstructions.clear();

                if( res.number_of_instructions > 0 ) {
                    ErrorContainer instructionWarnings;
                    fcml_int i = 0;
                    fcml_st_assembled_instruction *next_instruction = res.instructions;
                    while( next_instruction ) {
                        fcml_st_ceh_error_container &instruction_warnings = next_instruction->warnings;
                        ErrorTypeConverter::convert( instruction_warnings, instructionWarnings );
                        AssembledInstruction assembledInstruction( next_instruction->code, next_instruction->code_length, instructionWarnings );
                        assembledInstructions.push_back( assembledInstruction );
                        if( next_instruction == res.chosen_instruction ) {
                            result.setChoosenInstructionIndex(i);
                        }
                        next_instruction = next_instruction->next;
                        i++;
                    }
                }

                // Convert it back to the context because it might have been
                // modified during assembling process (IP incrementing etc).
                TypeConverter::convert( context.entry_point, ctx.getEntryPoint() );

            }

            ::fcml_fn_assembler_result_free( &res );

        } catch( std::exception &exc ) {
            // If anything failed, free assembler results.
            TypeConverter::free( inst );
            ::fcml_fn_assembler_result_free( &res );
            throw exc;
        }

        return error;
    }

    /**
     * Gets dialect associated with the assembler.
     * @return The dialect instance associated with the assembler.
     * @since 1.1.0
     */
    Dialect& getDialect() const {
        return _dialect;
    }

private:

    // A dialect used by the assembler.
    Dialect &_dialect;

    // An initialized assembler instance.
    fcml_st_assembler *_assembler;

};

/** Iterates over machine code bytes from assembled instructions.
 * @since 1.1.0
 */
class CodeIterator: public Iterator<fcml_uint8_t> {
public:

    /**
     * Creates a code iterator instance.
     * @param assembledInstructions Assembled instructions.
     * @since 1.1.0
     */
    CodeIterator( std::vector<AssembledInstruction> &assembledInstructions ) :
        _buffer(NULL),
        _len(0),
        _pos(0),
        _iterator(assembledInstructions.begin()),
        _assembledInstructions(assembledInstructions) {
    }

    /**
     * @since 1.1.0
     */
    virtual ~CodeIterator() {
    }

    /**
     * Gets true if there is an another element in the iterator.
     *
     * @return True if there is another byte in the iterator.
     * @since 1.1.0
     */
    bool hasNext() {
        if( _buffer && _pos >= _len ) {
            _buffer = NULL;
        }
        if( !_buffer ) {
            if( _iterator == _assembledInstructions.end() ) {
                return false;
            }
            AssembledInstruction &current = *_iterator++;
            _buffer = current.getCode();
            _len = current.getCodeLength();
            _pos = 0;
        }
        return true;
    }

    /**
     * Gets the next element from the iterator.
     *
     * @return Next machine code byte.
     * @throw IllegalStateException If iterator is empty.
     * @since 1.1.0
     */
    fcml_uint8_t next() {
        if( ( !_buffer || _pos >= _len ) && !hasNext() ) {
            throw IllegalStateException( FCML_TEXT( "No more elements in the iterator." ) );
        }
        return _buffer[_pos++];
    }

private:

    /** Code of the current instruction iterator points to. */
    const fcml_uint8_t *_buffer;
    /** Code length in bytes. */
    fcml_usize _len;
    /** Position in the code buffer */
    fcml_usize _pos;
    /** Assembled instructions iterator. */
    std::vector<AssembledInstruction>::iterator _iterator;
    /** Vector with assembled instructions. */
    std::vector<AssembledInstruction> &_assembledInstructions;

};

}

#endif //FCML_ASSEMBLER_HPP_
