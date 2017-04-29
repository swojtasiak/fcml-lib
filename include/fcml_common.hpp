/*
 * FCML - Free Code Manipulation Library.
 * Copyright (C) 2010-2017 Slawomir Wojtasiak
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

/** @file fcml_common.hpp
 * C++ wrappers common classes.
 *
 * @copyright Copyright (C) 2010-2017 Slawomir Wojtasiak. All rights reserved.
 * This project is released under the GNU Lesser General Public License.
 */

#ifndef FCML_COMMON_HPP_
#define FCML_COMMON_HPP_

#include <stdlib.h>
#include <string.h>
#include <new>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <memory>
#include <vector>

#include "fcml_types.h"
#include "fcml_common.h"
#include "fcml_common_utils.h"
#include "fcml_errors.h"

namespace fcml {

#define FCML_TO_CPP_BOOL( x ) ( (x) ? true : false )

/**
 * By using this type definition here, it will be definitely much
 * easier to support UNICODE in future releases.
 * @since 1.1.0
 */
typedef std::basic_string<fcml_char> fcml_cstring;

/**
 * String output stream.
 * @since 1.1.0
 */
typedef std::basic_ostringstream<fcml_char> fcml_costream;

/**
 * Exposes API responsible for environment specific operations, even if standard CPP library is used
 * to implement them.
 *
 * @since 1.1.0
 * @remarks Internal API, not intended to be used outside.
 */
class Env {
public:
    /**
     * @throw std::bad_alloc
     * @since 1.1.0
     */
    static fcml_string strDup( const fcml_string str ) {
        if ( !str ) {
            return NULL;
        }
#if defined(FCML_MSCC)
		fcml_string newStr = _strdup( str );
#else
        fcml_string newStr = strdup( str );
#endif
        if ( !newStr ) {
            throw std::bad_alloc();
        }
        return newStr;
    }
    static void strFree( fcml_string str ) {
        free( str );
    }
};

/**
 * A base iterator interface.
 * @since 1.1.0
 */
template <typename T>
class Iterator {
public:

    Iterator() {}

    virtual ~Iterator() {}

    /**
     * Gets true if there is an another element in the iterator.
     */
    virtual bool hasNext() = 0;

    /**
     * Gets a next element from the iterator.
     */
    virtual T next() = 0;
};

/** Wrapper for nullable value types.
 * @since 1.1.0
 */
template<typename T>
class Nullable {
public:

    Nullable( const T& value, bool is_not_null = false ) :
        _value( value ), _is_not_null( is_not_null ) {
    }

    Nullable() :
        _is_not_null( false ) {
    }

    bool isNotNull() const {
        return _is_not_null;
    }

    void setNotNull(bool isNull) {
        _is_not_null = isNull;
    }

    T getValue() const {
        return _value;
    }

    T& getValue() {
        return _value;
    }

    void setValue(const T& value) {
        this->_value = value;
    }

public:

    /**
     * Checks if two nullable values are equal.
     *
     * @param nullable The source nullable value.
     * @return True if they are equal; otherwise false.
     * @since 2.0.0
     */
    bool operator==(const Nullable &nullable) const {
        return _value == nullable._value &&
                _is_not_null == nullable._is_not_null;
    }

    /**
     * Checks if two nullable values are not equal.
     *
     * @param nullable The source nullable value.
     * @return True if they are not equal; otherwise false.
     * @since 2.0.0
     */
    bool operator!=(const Nullable &nullable) const {
        return !(nullable == *this);
    }

private:
    /** Value. */
    T _value;
    /** Information if value is set or not. */
    bool _is_not_null;
};

/**
 *  Base exception for all exceptions exposed by FCML library.
 *  @since 1.1.0
 */
class BaseException {
public:
    BaseException( fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR ) {
        this->_error = error;
    }
    BaseException( const fcml_cstring &msg, fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR ) {
        this->_msg = msg;
        this->_error = error;
    }
    BaseException( const BaseException &cpy ) {
        this->_msg = cpy._msg;
        this->_error = cpy._error;
    }
    virtual ~BaseException() {
    }
    BaseException& operator=( const BaseException &exc ) {
        if ( &exc != this ) {
            this->_msg = exc._msg;
            this->_error = exc._error;
        }
        return *this;
    }
public:
    const fcml_cstring getMsg() const {
        return _msg;
    }
    const fcml_ceh_error& getError() const {
        return _error;
    }
private:
    void* operator new( size_t size ) {
        return ::operator new( size );
    }
private:
    /** Error message. */
    fcml_cstring _msg;
    /** Error code */
    fcml_ceh_error _error;
};

/**
 * Component can not be initialized correctly.
 * @since 1.1.0
 */
class InitException: public BaseException {
public:
    InitException( const fcml_cstring &msg, fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR ) :
            BaseException( msg, error ) {
    }
};

/**
 * Bad arguments.
 * @since 1.1.0
 */
class BadArgumentException: public BaseException {
public:
    BadArgumentException( const fcml_cstring &msg, fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR ) :
            BaseException( msg, error ) {
    }
};

/**
 *  Illegal state exception.
 *  @since 1.1.0
 */
class IllegalStateException: public BaseException {
public:
    IllegalStateException( const fcml_cstring &msg, fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR ) :
            BaseException( msg, error ) {
    }
};

/**
 *  Illegal argument exception.
 *  @since 1.1.0
 */
class IllegalArgumentException: public BaseException {
public:
    IllegalArgumentException( const fcml_cstring &msg, fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR ) :
            BaseException( msg, error ) {
    }
};

/**
 *  Operation is not supported.
 *  @since 1.1.0
 */
class OperationNotSupportedException: public BaseException {
public:
    OperationNotSupportedException( const fcml_cstring &msg ) :
            BaseException( msg ) {
    }
    OperationNotSupportedException() {
    }
};

/**
 * Object which shouldn't be copied can inherit from this class.
 * @since 1.1.0
 */
class NonCopyable {
protected:
    NonCopyable() {
    }
private:
    /**
     * @throw OperationNotSupportedException
     */
    NonCopyable( const NonCopyable &cpy ) {
        throw OperationNotSupportedException();
    }
    /**
     * @throw OperationNotSupportedException
     */
    NonCopyable& operator=( const NonCopyable &exc ) {
        throw OperationNotSupportedException();
    }
};

/** Wraps instruction prefix and prepares factory methods for the hints.
 * The static method "create" is used here just to avoid the constructor overloading
 * what can be a bit problematic because fcml_prefix is an ordinal integer type.
 * @since 1.1.0
 */
class InstructionPrefix {
private:
    /**
     * Creates an instance of the instruction prefix for the given FCML prefix.
     * @param prefix The native FCML prefix.
     * @return Instruction prefix instance.
     */
    static InstructionPrefix create( fcml_prefixes prefix ) {
        InstructionPrefix instructionPrefix;
        instructionPrefix._prefix = prefix;
        return instructionPrefix;
    }
public:
    /**
     * Creates instruction prefix: LOCK.
     * @return Created instruction prefix.
     */
    static const InstructionPrefix LOCK() {
        return create(FCML_PREFIX_LOCK);
    }
    /**
     * Creates instruction prefix: REPNE.
     * @return Created instruction prefix.
     */
    static const InstructionPrefix REPNE() {
        return create(FCML_PREFIX_REPNE);
    }
    /**
     * Creates instruction prefix: REPNZ.
     * @return Created instruction prefix.
     */
    static const InstructionPrefix REPNZ() {
        return create(FCML_PREFIX_REPNZ);
    }
    /**
     * Creates instruction prefix: REP.
     * @return Created instruction prefix.
     */
    static const InstructionPrefix REP() {
        return create(FCML_PREFIX_REP);
    }
    /**
     * Creates instruction prefix: REPE.
     * @return Created instruction prefix.
     */
    static const InstructionPrefix REPE() {
        return create(FCML_PREFIX_REPE);
    }
    /**
     * Creates instruction prefix: REPZ.
     * @return Created instruction prefix.
     */
    static const InstructionPrefix REPZ() {
        return create(FCML_PREFIX_REPZ);
    }
    /**
     * Creates instruction prefix: XACQUIRE.
     * @return Created instruction prefix.
     */
    static const InstructionPrefix XACQUIRE() {
        return create(FCML_PREFIX_XACQUIRE);
    }
    /**
     * Creates instruction prefix: XRELEASE.
     * @return Created instruction prefix.
     */
    static const InstructionPrefix XRELEASE() {
        return create(FCML_PREFIX_XRELEASE);
    }
    /**
     * Creates instruction prefix: BRANCH_HINT.
     * @return Created instruction prefix.
     */
    static const InstructionPrefix BRANCH_HINT() {
        return create(FCML_PREFIX_BRANCH_HINT);
    }
    /**
     * Creates instruction prefix: NOBRANCH_HINT.
     * @return Created instruction prefix.
     */
    static const InstructionPrefix NOBRANCH_HINT() {
        return create(FCML_PREFIX_NOBRANCH_HINT);
    }
public:
    fcml_prefixes _prefix;
};

/** Wraps instruction hint and exposes factory methods for instruction hints.
 * @since 1.1.0
 */
struct InstructionHint {
private:
    /**
     * Creates an instruction level hints for given native FCML hints.
     * @param hints The hints set.
     */
    InstructionHint(fcml_en_instruction_hints hints) :
        _hint(hints) {
    }
public:
    /**
     * Creates instruction hint: NO_HINTS.
     * @return Instruction hint.
     */
    static const InstructionHint NO_HINTS() {
        return InstructionHint(FCML_HINT_NO_HINTS);
    }
    /**
     * Creates instruction hint: NEAR_POINTER.
     * @return Instruction hint.
     */
    static const InstructionHint NEAR_POINTER() {
        return InstructionHint(FCML_HINT_NEAR_POINTER);
    }
    /**
     * Creates instruction hint: FAR_POINTER.
     * @return Instruction hint.
     */
    static const InstructionHint FAR_POINTER() {
        return InstructionHint(FCML_HINT_FAR_POINTER);
    }
    /**
     * Creates instruction hint: LONG_FORM_POINTER.
     * @return Instruction hint.
     */
    static const InstructionHint LONG_FORM_POINTER() {
        return InstructionHint(FCML_HINT_LONG_FORM_POINTER);
    }
    /**
     * Creates instruction hint: INDIRECT_POINTER.
     * @return Instruction hint.
     */
    static const InstructionHint INDIRECT_POINTER() {
        return InstructionHint(FCML_HINT_INDIRECT_POINTER);
    }
    /**
     * Creates instruction hint: DIRECT_POINTER.
     * @return Instruction hint.
     */
    static const InstructionHint DIRECT_POINTER() {
        return InstructionHint(FCML_HINT_DIRECT_POINTER);
    }
public:
    fcml_en_instruction_hints _hint;
};

/** Wraps operand hint and exposes factory methods for instruction hints.
 * @since 1.1.0
 */
struct OperandHint {
private:
    OperandHint(fcml_en_operand_hints hint) :
        _hint(hint) {
    }
public:
    /**
     * Creates operand level hint: UNDEFIEND.
     * @return Operand level hint.
     */
    static const OperandHint UNDEFIEND() {
        return OperandHint(FCML_OP_HINT_UNDEFIEND);
    }
    /**
     * Creates operand level hint: MULTIMEDIA_INSTRUCTION.
     * @return Operand level hint.
     */
    static const OperandHint MULTIMEDIA() {
        return OperandHint(FCML_OP_HINT_MULTIMEDIA_INSTRUCTION);
    }
    /**
     * Creates operand level hint: DISPLACEMENT_RELATIVE_ADDRESS.
     * @return Operand level hint.
     */
    static const OperandHint DISPLACEMENT_RELATIVE_ADDRESS() {
        return OperandHint(FCML_OP_HINT_DISPLACEMENT_RELATIVE_ADDRESS);
    }
    /**
     * Creates operand level hint: PSEUDO_OPCODE.
     * @return Operand level hint.
     */
    static const OperandHint PSEUDO_OPCODE() {
        return OperandHint(FCML_OP_HINT_PSEUDO_OPCODE);
    }
    /**
     * Creates operand level hint: ABSOLUTE_ADDRESSING.
     * @return Operand level hint.
     */
    static const OperandHint ABSOLUTE_ADDRESSING() {
        return OperandHint(FCML_OP_HINT_ABSOLUTE_ADDRESSING);
    }
    /**
     * Creates operand level hint: RELATIVE_ADDRESSING.
     * @return Operand level hint.
     */
    static const OperandHint RELATIVE_ADDRESSING() {
        return OperandHint(FCML_OP_HINT_RELATIVE_ADDRESSING);
    }
    /**
     * Creates operand level hint: SIB_ENCODING.
     * @return Operand level hint.
     */
    static const OperandHint SIB_ENCODING() {
        return OperandHint(FCML_OP_HINT_SIB_ENCODING);
    }
public:
    fcml_en_operand_hints _hint;
};

/**
 * Holds instruction pointer, processor operating mode and memory segment flags.
 * @since 1.1.0
 */
class EntryPoint {
public:

    /**
     * Supported operating modes.
     * @since 1.1.0
     */
    enum OperatingMode {
        OM_16_BIT = FCML_OM_16_BIT,
        OM_32_BIT = FCML_OM_32_BIT,
        OM_64_BIT = FCML_OM_64_BIT
    };

    /**
     * Creates an empty entry point instance.
     * @since 1.1.0
     */
    EntryPoint() :
        _opMode(OM_32_BIT),
        _addressSizeAttribute(FCML_DS_32),
        _operandSizeAttribute(FCML_DS_32),
        _ip(0) {
    }

    /**
     * Creates an entry point instance for given processor operating mode, instruction pointer and optionally size attributes.
     * @param opMode The processor operating mode.
     * @param ip The instruction pointer.
     * @param addressSizeAttribute The optional address size attribute.
     * @param operandSizeAttribute The optional operand size attribute.
     * @since 1.1.0
     */
    EntryPoint(OperatingMode opMode, fcml_ip ip = 0, fcml_usize addressSizeAttribute = FCML_DS_UNDEF, fcml_usize operandSizeAttribute = FCML_DS_UNDEF ) :
        _opMode(opMode),
        _addressSizeAttribute(addressSizeAttribute),
        _operandSizeAttribute(operandSizeAttribute),
        _ip(ip) {
    }

    virtual ~EntryPoint() {
    }

public:

    /**
     * Checks if two entry points are equal.
     *
     * @param ep The source entry point.
     * @return True if they are equal; otherwise false.
     * @since 1.1.0
     */
    bool operator==( const EntryPoint &ep ) const {
        return _opMode == ep._opMode &&
                _ip == ep._ip &&
                _operandSizeAttribute == ep._operandSizeAttribute &&
                _addressSizeAttribute == ep._addressSizeAttribute;
    }

    /**
     * Checks if two entry points are not equal.
     *
     * @param ep The source entry point.
     * @return True if they are not equal; otherwise false.
     * @since 1.1.0
     */
    bool operator!=( const EntryPoint &ep ) const {
        return !(ep == *this);
    }

public:

    /**
     * Gets address size attribute held by the entry point.
     *
     * @return Address size attribute.
     * @since 1.1.0
     */
    fcml_usize getAddressSizeAttribute() const {
        return _addressSizeAttribute;
    }

    /**
     * Sets a new address size attribute for the entry point.
     *
     * @param addressSizeAttribute The address size attribute.
     * @since 1.1.0
     */
    void setAddressSizeAttribute( fcml_usize addressSizeAttribute ) {
       _addressSizeAttribute = addressSizeAttribute;
    }

    /**
     * Gets operand size attribute held by the entry point.
     *
     * @return Operand size attribute.
     * @since 1.1.0
     */
    fcml_usize getOperandSizeAttribute() const {
        return _operandSizeAttribute;
    }

    /**
     * Sets a new operand size attribute for the entry point.
     *
     * @param operandSizeAttribute The operand size attribute.
     * @since 1.1.0
     */
    void setOperandSizeAttribute( fcml_usize operandSizeAttribute ) {
       _operandSizeAttribute = operandSizeAttribute;
    }

    /**
     * Gets instruction pointer held by the entry point.
     *
     * @return Instruction pointer.
     * @since 1.1.0
     */
    fcml_ip getIP() const {
       return _ip;
    }

    /**
     * Sets a new instruction pointer for the entry point.
     *
     * @param ip The new instruction pointer.
     * @since 1.1.0
     */
    void setIP( fcml_ip ip ) {
       _ip = ip;
    }

    /**
     * Gets processor operating mode.
     *
     * @return Processor operating mode.
     * @since 1.1.0
     */
    OperatingMode getOpMode() const {
       return _opMode;
    }

    /**
     * Sets a new processor operating mode for the entry point.
     *
     * @param opMode The new processor operating mode.
     * @since 1.1.0
     */
    void setOpMode( OperatingMode opMode ) {
       _opMode = opMode;
    }

    /**
     * Increments the instruction pointer by given number of bytes.
     *
     * @param ip Number for bytes the instruction pointer should be incremented by.
     * @since 1.1.0
     */
    void incrementIP( fcml_ip ip ) {
        _ip += ip;
    }

private:
    /** Processor operating mode */
    OperatingMode _opMode;
    /** Size of the address size attribute. */
    fcml_usize _addressSizeAttribute;
    /** Size of the operand size attribute. */
    fcml_usize _operandSizeAttribute;
    /** Instruction pointer. Content of the EIP/RIP register. */
    fcml_ip _ip;
};

/**
 * Represents integer value.
 * @since 1.1.0
 */
class Integer {
public:

    /** @since 1.1.0 */
    Integer() :
            _size( FCML_DS_64 ), _isSigned( FCML_FALSE ), _vint8( 0 ), _vint16( 0 ), _vint32( 0 ), _vint64( 0 ) {
    }

    /** @since 1.1.0 */
    Integer( fcml_int8_t value ) :
            _size( FCML_DS_8 ), _isSigned( FCML_TRUE ), _vint8( value ), _vint16( 0 ), _vint32( 0 ), _vint64( 0 ) {
    }

    /** @since 1.1.0 */
    Integer( fcml_int16_t value ) :
            _size( FCML_DS_16 ), _isSigned( FCML_TRUE ), _vint8( 0 ), _vint16( value ), _vint32( 0 ), _vint64( 0 ) {
    }

    /** @since 1.1.0 */
    Integer( fcml_int32_t value ) :
            _size( FCML_DS_32 ), _isSigned( FCML_TRUE ), _vint8( 0 ), _vint16( 0 ), _vint32( value ), _vint64( 0 ) {
    }

    /** @since 1.1.0 */
    Integer( fcml_int64_t value ) :
            _size( FCML_DS_64 ), _isSigned( FCML_TRUE ), _vint8( 0 ), _vint16( 0 ), _vint32( 0 ), _vint64( value ) {
    }

    /** @since 1.1.0 */
    Integer( fcml_uint8_t value ) :
            _size( FCML_DS_8 ), _isSigned( FCML_FALSE ), _vint8( static_cast<fcml_uint8_t>( value ) ), _vint16( 0 ), _vint32( 0 ), _vint64( 0 ) {
    }

    /** @since 1.1.0 */
    Integer( fcml_uint16_t value ) :
            _size( FCML_DS_16 ), _isSigned( FCML_FALSE ), _vint8( 0 ), _vint16( static_cast<fcml_uint16_t>( value ) ), _vint32( 0 ), _vint64( 0 ) {
    }

    /** @since 1.1.0 */
    Integer( fcml_uint32_t value ) :
            _size( FCML_DS_32 ), _isSigned( FCML_FALSE ), _vint8( 0 ), _vint16( 0 ), _vint32( static_cast<fcml_uint32_t>( value ) ), _vint64( 0 ) {
    }

    /** @since 1.1.0 */
    Integer( fcml_uint64_t value ) :
            _size( FCML_DS_64 ), _isSigned( FCML_FALSE ), _vint8( 0 ), _vint16( 0 ), _vint32( 0 ), _vint64( static_cast<fcml_uint64_t>( value ) ) {
    }

    /** @since 1.1.0 */
    virtual ~Integer() {
    }

public:

    /** @since 1.1.0 */
    fcml_int16_t getInt16() const {
        return _vint16;
    }

    /** @since 1.1.0 */
    Integer& setInt16( fcml_int16_t int16 ) {
        _vint16 = int16;
        return *this;
    }

    /** @since 1.1.0 */
    fcml_int32_t getInt32() const {
        return _vint32;
    }

    /** @since 1.1.0 */
    Integer& setInt32( fcml_int32_t int32 ) {
        _vint32 = int32;
        return *this;
    }

    /** @since 1.1.0 */
    fcml_int64_t getInt64() const {
        return _vint64;
    }

    /** @since 1.1.0 */
    Integer& setInt64( fcml_int64_t int64 ) {
        _vint64 = int64;
        return *this;
    }

    /** @since 1.1.0 */
    fcml_int8_t getInt8() const {
        return _vint8;
    }

    /** @since 1.1.0 */
    Integer& setInt8( fcml_int8_t int8 ) {
        _vint8 = int8;
        return *this;
    }

    /** @since 1.1.0 */
    fcml_bool isSigned() const {
        return _isSigned;
    }

    /** @since 1.1.0 */
    Integer& setSigned( fcml_bool isSigned ) {
        _isSigned = isSigned;
        return *this;
    }

    /** @since 1.1.0 */
    fcml_usize getSize() const {
        return _size;
    }

    /** @since 1.1.0 */
    Integer& setSize( fcml_usize size ) {
        _size = size;
        return *this;
    }

    /**
     * Checks if the integer is equal to the passed value.
     *
     * @param value The source value to be compared with the integer.
     * @return True if values are equal; otherwise false.
     * @since 1.1.0
     */
    bool operator==( const fcml_uint8_t value ) const {
        return _isSigned ? static_cast<fcml_int64_t>( *this ) == static_cast<fcml_int64_t>( value ) : static_cast<fcml_uint64_t>( *this ) == static_cast<fcml_uint64_t>( value );
    }

    /**
     * Checks if the integer is equal to the passed value.
     *
     * @param value The source value to be compared with the integer.
     * @return True if values are equal; otherwise false.
     * @since 1.1.0
     */
    bool operator==( const fcml_int8_t value ) const {
        return _isSigned ? static_cast<fcml_int64_t>( *this ) == static_cast<fcml_int64_t>( value ) : static_cast<fcml_uint64_t>( *this ) == static_cast<fcml_uint64_t>( value );
    }

    /**
     * Checks if the integer is equal to the passed value.
     *
     * @param value The source value to be compared with the integer.
     * @return True if values are equal; otherwise false.
     * @since 1.1.0
     */
    bool operator==( const fcml_uint16_t value ) const {
        return _isSigned ? static_cast<fcml_int64_t>( *this ) == static_cast<fcml_int64_t>( value ) : static_cast<fcml_uint64_t>( *this ) == static_cast<fcml_uint64_t>( value );
    }

    /**
     * Checks if the integer is equal to the passed value.
     *
     * @param value The source value to be compared with the integer.
     * @return True if values are equal; otherwise false.
     * @since 1.1.0
     */
    bool operator==( const fcml_int16_t value ) const {
        return _isSigned ? static_cast<fcml_int64_t>( *this ) == static_cast<fcml_int64_t>( value ) : static_cast<fcml_uint64_t>( *this ) == static_cast<fcml_uint64_t>( value );
    }

    /**
     * Checks if the integer is equal to the passed value.
     *
     * @param value The source value to be compared with the integer.
     * @return True if values are equal; otherwise false.
     * @since 1.1.0
     */
    bool operator==( const fcml_uint32_t value ) const {
        return _isSigned ? static_cast<fcml_int64_t>( *this ) == static_cast<fcml_int64_t>( value ) : static_cast<fcml_uint64_t>( *this ) == static_cast<fcml_uint64_t>( value );
    }

    /**
     * Checks if the integer is equal to the passed value.
     *
     * @param value The source value to be compared with the integer.
     * @return True if values are equal; otherwise false.
     * @since 1.1.0
     */
    bool operator==( const fcml_int32_t value ) const {
        return _isSigned ? static_cast<fcml_int64_t>( *this ) == static_cast<fcml_int64_t>( value ) : static_cast<fcml_uint64_t>( *this ) == static_cast<fcml_uint64_t>( value );
    }

    /**
     * Checks if the integer is equal to the passed value.
     *
     * @param value The source value to be compared with the integer.
     * @return True if values are equal; otherwise false.
     * @since 1.1.0
     */
    bool operator==( const fcml_uint64_t value ) const {
        return _isSigned ? static_cast<fcml_int64_t>( *this ) == static_cast<fcml_int64_t>( value ) : static_cast<fcml_uint64_t>( *this ) == static_cast<fcml_uint64_t>( value );
    }

    /**
     * Checks if the integer is equal to the passed value.
     *
     * @param value The source value to be compared with the integer.
     * @return True if values are equal; otherwise false.
     * @since 1.1.0
     */
    bool operator==( const fcml_int64_t value ) const {
        return _isSigned ? static_cast<fcml_int64_t>( *this ) == static_cast<fcml_int64_t>( value ) : static_cast<fcml_uint64_t>( *this ) == static_cast<fcml_uint64_t>( value );
    }

    /**
     * Checks if the integer is equal to the passed value.
     *
     * @param value The source value to be compared with the integer.
     * @return True if values are equal; otherwise false.
     * @since 1.1.0
     */
    bool operator==( const Integer &value ) const {
        return _isSigned ? static_cast<fcml_int64_t>( *this ) == static_cast<fcml_int64_t>( value ) : static_cast<fcml_uint64_t>( *this ) == static_cast<fcml_uint64_t>( value );
    }

    /**
     * Checks if the integer is not equal to the passed value.
     *
     * @param value The source value to be compared with the integer.
     * @return True if values are not equal; otherwise false.
     * @since 1.1.0
     */
    bool operator!=( const fcml_uint8_t value ) const {
        return _isSigned ? static_cast<fcml_int64_t>( *this ) != static_cast<fcml_int64_t>( value ) : static_cast<fcml_uint64_t>( *this ) != static_cast<fcml_uint64_t>( value );
    }

    /**
     * Checks if the integer is not equal to the passed value.
     *
     * @param value The source value to be compared with the integer.
     * @return True if values are not equal; otherwise false.
     * @since 1.1.0
     */
    bool operator!=( const fcml_int8_t value ) const {
        return _isSigned ? static_cast<fcml_int64_t>( *this ) != static_cast<fcml_int64_t>( value ) : static_cast<fcml_uint64_t>( *this ) != static_cast<fcml_uint64_t>( value );
    }

    /**
     * Checks if the integer is not equal to the passed value.
     *
     * @param value The source value to be compared with the integer.
     * @return True if values are not equal; otherwise false.
     * @since 1.1.0
     */
    bool operator!=( const fcml_uint16_t value ) const {
        return _isSigned ? static_cast<fcml_int64_t>( *this ) != static_cast<fcml_int64_t>( value ) : static_cast<fcml_uint64_t>( *this ) != static_cast<fcml_uint64_t>( value );
    }

    /**
     * Checks if the integer is not equal to the passed value.
     *
     * @param value The source value to be compared with the integer.
     * @return True if values are not equal; otherwise false.
     * @since 1.1.0
     */
    bool operator!=( const fcml_int16_t value ) const {
        return _isSigned ? static_cast<fcml_int64_t>( *this ) != static_cast<fcml_int64_t>( value ) : static_cast<fcml_uint64_t>( *this ) != static_cast<fcml_uint64_t>( value );
    }

    /**
     * Checks if the integer is not equal to the passed value.
     *
     * @param value The source value to be compared with the integer.
     * @return True if values are not equal; otherwise false.
     * @since 1.1.0
     */
    bool operator!=( const fcml_uint32_t value ) const {
        return _isSigned ? static_cast<fcml_int64_t>( *this ) != static_cast<fcml_int64_t>( value ) : static_cast<fcml_uint64_t>( *this ) != static_cast<fcml_uint64_t>( value );
    }

    /**
     * Checks if the integer is not equal to the passed value.
     *
     * @param value The source value to be compared with the integer.
     * @return True if values are not equal; otherwise false.
     * @since 1.1.0
     */
    bool operator!=( const fcml_int32_t value ) const {
        return _isSigned ? static_cast<fcml_int64_t>( *this ) != static_cast<fcml_int64_t>( value ) : static_cast<fcml_uint64_t>( *this ) != static_cast<fcml_uint64_t>( value );
    }

    /**
     * Checks if the integer is not equal to the passed value.
     *
     * @param value The source value to be compared with the integer.
     * @return True if values are not equal; otherwise false.
     * @since 1.1.0
     */
    bool operator!=( const fcml_uint64_t value ) const {
        return _isSigned ? static_cast<fcml_int64_t>( *this ) != static_cast<fcml_int64_t>( value ) : static_cast<fcml_uint64_t>( *this ) != static_cast<fcml_uint64_t>( value );
    }

    /**
     * Checks if the integer is not equal to the passed value.
     *
     * @param value The source value to be compared with the integer.
     * @return True if values are not equal; otherwise false.
     * @since 1.1.0
     */
    bool operator!=( const fcml_int64_t value ) const {
        return _isSigned ? static_cast<fcml_int64_t>( *this ) != static_cast<fcml_int64_t>( value ) : static_cast<fcml_uint64_t>( *this ) != static_cast<fcml_uint64_t>( value );
    }

    /**
     * Checks if the integer is not equal to the passed value.
     *
     * @param value The source value to be compared with the integer.
     * @return True if values are not equal; otherwise false.
     * @since 1.1.0
     */
    bool operator!=( const Integer &value ) const {
        return _isSigned ? static_cast<fcml_int64_t>( *this ) != static_cast<fcml_int64_t>( value ) : static_cast<fcml_uint64_t>( *this ) != static_cast<fcml_uint64_t>( value );
    }

    /**
     * A casting operator.
     * @since 1.1.0
     * @throw BadArgumentException Wrong data size.
     */
    operator fcml_int8_t() const {
        fcml_int8_t result;
        switch ( _size ) {
        case FCML_DS_8:
            result = static_cast<fcml_int8_t>( _isSigned ? _vint8 : (fcml_uint8_t)_vint8 );
            break;
        case FCML_DS_16:
            result = static_cast<fcml_int8_t>( _isSigned ? _vint16 : (fcml_uint16_t)_vint16 );
            break;
        case FCML_DS_32:
            result = static_cast<fcml_int8_t>( _isSigned ? _vint32 : (fcml_uint32_t)_vint32 );
            break;
        case FCML_DS_64:
            result = static_cast<fcml_int8_t>( _isSigned ? _vint64 : (fcml_uint64_t)_vint64 );
            break;
        default:
            throw BadArgumentException( FCML_TEXT( "Wrong size." ) );
        }
        return result;
    }
    /**
     * A casting operator.
     * @since 1.1.0
     * @throw BadArgumentException Wrong indeger size.
     */
    operator fcml_uint8_t() const {
        fcml_uint8_t result;
        switch ( _size ) {
        case FCML_DS_8:
            result = static_cast<fcml_uint8_t>( _isSigned ? _vint8 : (fcml_uint8_t)_vint8 );
            break;
        case FCML_DS_16:
            result = static_cast<fcml_uint8_t>( _isSigned ? _vint16 : (fcml_uint16_t)_vint16 );
            break;
        case FCML_DS_32:
            result = static_cast<fcml_uint8_t>( _isSigned ? _vint32 : (fcml_uint32_t)_vint32 );
            break;
        case FCML_DS_64:
            result = static_cast<fcml_uint8_t>( _isSigned ? _vint64 : (fcml_uint64_t)_vint64 );
            break;
        default:
            throw BadArgumentException( FCML_TEXT( "Wrong size." ) );
        }
        return result;
    }

    /**
     * A casting operator.
     * @since 1.1.0
     * @throw BadArgumentException Wrong integer size.
     */
    operator fcml_int16_t() const {
        fcml_int16_t result;
        switch ( _size ) {
        case FCML_DS_8:
            result = static_cast<fcml_int16_t>( _isSigned ? _vint8 : (fcml_uint8_t)_vint8 );
            break;
        case FCML_DS_16:
            result = static_cast<fcml_int16_t>( _isSigned ? _vint16 : (fcml_uint16_t)_vint16 );
            break;
        case FCML_DS_32:
            result = static_cast<fcml_int16_t>( _isSigned ? _vint32 : (fcml_uint32_t)_vint32 );
            break;
        case FCML_DS_64:
            result = static_cast<fcml_int16_t>( _isSigned ? _vint64 : (fcml_uint64_t)_vint64 );
            break;
        default:
            throw BadArgumentException( FCML_TEXT( "Wrong size." ) );
        }
        return result;
    }

    /**
     * A casting operator.
     * @since 1.1.0
     * @throw BadArgumentException Wrong integer size.
     */
    operator fcml_uint16_t() const {
        fcml_uint16_t result;
        switch ( _size ) {
        case FCML_DS_8:
            result = static_cast<fcml_uint16_t>( _isSigned ? _vint8 : (fcml_uint8_t)_vint8 );
            break;
        case FCML_DS_16:
            result = static_cast<fcml_uint16_t>( _isSigned ? _vint16 : (fcml_uint16_t)_vint16 );
            break;
        case FCML_DS_32:
            result = static_cast<fcml_uint16_t>( _isSigned ? _vint32 : (fcml_uint32_t)_vint32 );
            break;
        case FCML_DS_64:
            result = static_cast<fcml_uint16_t>( _isSigned ? _vint64 : (fcml_uint64_t)_vint64 );
            break;
        default:
            throw BadArgumentException( FCML_TEXT( "Wrong size." ) );
        }
        return result;
    }

    /**
     * A casting operator.
     * @since 1.1.0
     * @throw BadArgumentException Wrong integer size.
     */
    operator fcml_int32_t() const {
        fcml_int32_t result;
        switch ( _size ) {
        case FCML_DS_8:
            result = static_cast<fcml_int32_t>( _isSigned ? _vint8 : (fcml_uint8_t)_vint8 );
            break;
        case FCML_DS_16:
            result = static_cast<fcml_int32_t>( _isSigned ? _vint16 : (fcml_uint16_t)_vint16 );
            break;
        case FCML_DS_32:
            result = static_cast<fcml_int32_t>( _isSigned ? _vint32 : (fcml_uint32_t)_vint32 );
            break;
        case FCML_DS_64:
            result = static_cast<fcml_int32_t>( _isSigned ? _vint64 : (fcml_uint64_t)_vint64 );
            break;
        default:
            throw BadArgumentException( FCML_TEXT( "Wrong size." ) );
        }
        return result;
    }

    /**
     * A casting operator.
     * @since 1.1.0
     * @throw BadArgumentException Wrong integer size.
     */
    operator fcml_uint32_t() const {
        fcml_uint32_t result;
        switch ( _size ) {
        case FCML_DS_8:
            result = static_cast<fcml_uint32_t>( _isSigned ? _vint8 : (fcml_uint8_t)_vint8 );
            break;
        case FCML_DS_16:
            result = static_cast<fcml_uint32_t>( _isSigned ? _vint16 : (fcml_uint16_t)_vint16 );
            break;
        case FCML_DS_32:
            result = static_cast<fcml_uint32_t>( _isSigned ? _vint32 : (fcml_uint32_t)_vint32 );
            break;
        case FCML_DS_64:
            result = static_cast<fcml_uint32_t>( _isSigned ? _vint64 : (fcml_uint64_t)_vint64 );
            break;
        default:
            throw BadArgumentException( FCML_TEXT( "Wrong size." ) );
        }
        return result;
    }

    /**
     * A casting operator.
     * @since 1.1.0
     * @throw BadArgumentException Wrong integer size.
     */
    operator fcml_int64_t() const {
        fcml_int64_t result;
        switch ( _size ) {
        case FCML_DS_8:
            result = static_cast<fcml_int64_t>( _isSigned ? _vint8 : (fcml_uint8_t)_vint8 );
            break;
        case FCML_DS_16:
            result = static_cast<fcml_int64_t>( _isSigned ? _vint16 : (fcml_uint16_t)_vint16 );
            break;
        case FCML_DS_32:
            result = static_cast<fcml_int64_t>( _isSigned ? _vint32 : (fcml_uint32_t)_vint32 );
            break;
        case FCML_DS_64:
            result = static_cast<fcml_int64_t>( _isSigned ? _vint64 : (fcml_uint64_t)_vint64 );
            break;
        default:
            throw BadArgumentException( FCML_TEXT( "Wrong size." ) );
        }
        return result;
    }

    /**
     * A casting operator.
     * @since 1.1.0
     * @throw BadArgumentException Wrong integer size.
     */
    operator fcml_uint64_t() const {
        fcml_uint64_t result;
        switch ( _size ) {
        case FCML_DS_8:
            result = static_cast<fcml_uint64_t>( _isSigned ? _vint8 : (fcml_uint8_t)_vint8 );
            break;
        case FCML_DS_16:
            result = static_cast<fcml_uint64_t>( _isSigned ? _vint16 : (fcml_uint16_t)_vint16 );
            break;
        case FCML_DS_32:
            result = static_cast<fcml_uint64_t>( _isSigned ? _vint32 : (fcml_uint32_t)_vint32 );
            break;
        case FCML_DS_64:
            result = static_cast<fcml_uint64_t>( _isSigned ? _vint64 : (fcml_uint64_t)_vint64 );
            break;
        default:
            throw BadArgumentException( FCML_TEXT( "Wrong size." ) );
        }
        return result;
    }

    /**
     * Addition assignment.
     * @since 1.1.0
     */
    Integer& operator +=( const Integer &arg ) {
        plus( *this, arg );
        return ( *this );
    }

    /**
     * Multiplication assignment.
     * @since 1.1.0
     */
    Integer& operator *=( const Integer &arg ) {
        mul( *this, arg );
        return ( *this );
    }

    /**
     * Division assignment.
     * @since 1.1.0
     */
    Integer& operator /=( const Integer &arg ) {
        div( *this, arg );
        return ( *this );
    }

    /**
     * Subtraction assignment.
     * @since 1.1.0
     */
    Integer& operator -=( const Integer &arg ) {
        minus( *this, arg );
        return ( *this );
    }

    /**
     * Addition operator.
     * @since 1.1.0
     */
    Integer operator+( const Integer &src ) const {
        const Integer &thisRef = *this;
        Integer result( thisRef );
        plus( result, src );
        return result;
    }

    /**
     * Subtraction operator.
     * @since 1.1.0
     */
    Integer operator-( const Integer &src ) const {
        const Integer &thisRef = *this;
        Integer result( thisRef );
        minus( result, src );
        return result;
    }

    /**
     * Multiplication operator.
     * @since 1.1.0
     */
    Integer operator*( const Integer &src ) const {
        const Integer &thisRef = *this;
        Integer result( thisRef );
        mul( result, src );
        return result;
    }

    /**
     * Division operator.
     * @since 1.1.0
     */
    Integer operator/( const Integer &src ) const {
        const Integer &thisRef = *this;
        Integer result( thisRef );
        div( result, src );
        return result;
    }

public:

    /**
     * Factory method which creates an instance fo the Integer for given parameter.
     * @param value The value for the newly created Integer.
     * @return The created Integer instance.
     * @since 1.1.0
     */
    static Integer int8( fcml_int8_t value ) {
        return Integer( value );
    }

    /**
     * Factory method which creates an instance fo the Integer for given parameter.
     * @param value The value for the newly created Integer.
     * @return The created Integer instance.
     * @since 1.1.0
     */
    static Integer uint8( fcml_uint8_t value ) {
        return Integer( value );
    }

    /**
     * Factory method which creates an instance fo the Integer for given parameter.
     * @param value The value for the newly created Integer.
     * @return The created Integer instance.
     * @since 1.1.0
     */
    static Integer int16( fcml_int16_t value ) {
        return Integer( value );
    }

    /**
     * Factory method which creates an instance fo the Integer for given parameter.
     * @param value The value for the newly created Integer.
     * @return The created Integer instance.
     * @since 1.1.0
     */
    static Integer uint16( fcml_uint16_t value ) {
        return Integer( value );
    }

    /**
     * Factory method which creates an insatnce fo the Integer for given parameter.
     * @param value The value for the newly created Integer.
     * @return The created Integer instance.
     * @since 1.1.0
     */
    static Integer int32( fcml_int32_t value ) {
        return Integer( value );
    }

    /**
     * Factory method which creates an insatnce fo the Integer for given parameter.
     * @param value The value for the newly created Integer.
     * @return The created Integer instance.
     * @since 1.1.0
     */
    static Integer uint32( fcml_uint32_t value ) {
        return Integer( value );
    }

    /**
     * Factory method which creates an insatnce fo the Integer for given parameter.
     * @param value The value for the newly created Integer.
     * @return The created Integer instance.
     * @since 1.1.0
     */
    static Integer int64( fcml_int64_t value ) {
        return Integer( value );
    }

    /**
     * Factory method which creates an insatnce fo the Integer for given parameter.
     * @param value The value for the newly created Integer.
     * @return The created Integer instance.
     * @since 1.1.0
     */
    static Integer uint64( fcml_uint64_t value ) {
        return Integer( value );
    }

private:

    /**
     * @remark An internal API.
     * @since 1.1.0
     */
    void minus( Integer &result, const Integer &src ) const {
        callMathExpression( &doMinus, &doUMinus, result, src );
    }

    /**
     * @remark An internal API.
     * @since 1.1.0
     */
    void mul( Integer &result, const Integer &src ) const {
        callMathExpression( &doMul, &doUMul, result, src );
    }

    /**
     * @remark An internal API.
     * @since 1.1.0
     */
    void div( Integer &result, const Integer &src ) const {
        callMathExpression( &doDiv, &doUDiv, result, src );
    }

    /**
     * @remark An internal API.
     * @since 1.1.0
     */
    void plus( Integer &result, const Integer &src ) const {
        callMathExpression( &doPlus, &doUPlus, result, src );
    }

private:

    /**
     * @remark An internal API.
     * @since 1.1.0
     */
    static fcml_int64_t doPlus( fcml_int64_t thisValue, fcml_int64_t thatValue ) {
        return thisValue + thatValue;
    }

    /**
     * @remark An internal API.
     * @since 1.1.0
     */
    static fcml_int64_t doMinus( fcml_int64_t thisValue, fcml_int64_t thatValue ) {
        return thisValue - thatValue;
    }

    /**
     * @remark An internal API.
     * @since 1.1.0
     */
    static fcml_int64_t doMul( fcml_int64_t thisValue, fcml_int64_t thatValue ) {
        return thisValue * thatValue;
    }

    /**
     * @remark An internal API.
     * @since 1.1.0
     */
    static fcml_int64_t doDiv( fcml_int64_t thisValue, fcml_int64_t thatValue ) {
        return thisValue / thatValue;
    }

    /**
     * @remark An internal API.
     * @since 1.1.0
     */
    static fcml_uint64_t doUPlus( fcml_uint64_t thisValue, fcml_uint64_t thatValue ) {
        return thisValue + thatValue;
    }

    /**
     * @remark An internal API.
     * @since 1.1.0
     */
    static fcml_uint64_t doUMinus( fcml_uint64_t thisValue, fcml_uint64_t thatValue ) {
        return thisValue - thatValue;
    }

    /**
     * @remark An internal API.
     * @since 1.1.0
     */
    static fcml_uint64_t doUMul( fcml_uint64_t thisValue, fcml_uint64_t thatValue ) {
        return thisValue * thatValue;
    }

    /**
     * @remark An internal API.
     * @since 1.1.0
     */
    static fcml_uint64_t doUDiv( fcml_uint64_t thisValue, fcml_uint64_t thatValue ) {
        return thisValue / thatValue;
    }

    /**
     * @remark An internal API.
     * @since 1.1.0
     */
    void callMathExpression( fcml_int64_t (*signedExpressionFn)( fcml_int64_t thisValue, fcml_int64_t thatValue ), fcml_uint64_t (*unsignedExpressionFn)( fcml_uint64_t thisValue, fcml_uint64_t thatValue ), Integer &result, const Integer &src ) const {

        if(  _isSigned ) {

            fcml_int64_t thisValue;
            fcml_int64_t thatValue;

            // Prepare "that". It has to be converted to the same sign.
            switch( src._size ) {
            case FCML_DS_8:
                thatValue = src._isSigned ? src._vint8 : static_cast<fcml_uint8_t>( src._vint8 );
                break;
            case FCML_DS_16:
                thatValue = src._isSigned ? src._vint16 : static_cast<fcml_uint16_t>( src._vint16 );
                break;
            case FCML_DS_32:
                thatValue = src._isSigned ? src._vint32 : static_cast<fcml_uint32_t>( src._vint32 );
                break;
            case FCML_DS_64:
                thatValue = src._isSigned ? src._vint64 : static_cast<fcml_uint64_t>( src._vint64 );
                break;
            }

            // Now "this".
            switch( result._size ) {
            case FCML_DS_8:
                thisValue = result._isSigned ? result._vint8 : static_cast<fcml_uint8_t>(result._vint8 );
                thisValue = (*signedExpressionFn)( thisValue, thatValue );
                result._vint8 = static_cast<fcml_int8_t>( thisValue );
                break;
            case FCML_DS_16:
                thisValue = result._isSigned ? result._vint16 : static_cast<fcml_uint16_t>( result._vint16 );
                thisValue = (*signedExpressionFn)( thisValue, thatValue );
                result._vint16 = static_cast<fcml_int16_t>( thisValue );
                break;
            case FCML_DS_32:
                thisValue = result._isSigned ? result._vint32 : static_cast<fcml_uint32_t>( result._vint32 );
                thisValue = (*signedExpressionFn)( thisValue, thatValue );
                result._vint32 = static_cast<fcml_int32_t>( thisValue );
                break;
            case FCML_DS_64:
                thisValue = result._isSigned ? result._vint64 : static_cast<fcml_uint64_t>( result._vint64 );
                thisValue = (*signedExpressionFn)( thisValue, thatValue );
                result._vint64 = thisValue;
                break;
            }

        } else {

            fcml_uint64_t thisValue;
            fcml_uint64_t thatValue;

            // Prepare "that". It has to be converted to the same sign.
            switch( src._size ) {
            case FCML_DS_8:
                thatValue = src._isSigned ? src._vint8 : static_cast<fcml_uint8_t>( src._vint8 );
                break;
            case FCML_DS_16:
                thatValue = src._isSigned ? src._vint16 : static_cast<fcml_uint16_t>( src._vint16 );
                break;
            case FCML_DS_32:
                thatValue = src._isSigned ? src._vint32 : static_cast<fcml_uint32_t>( src._vint32 );
                break;
            case FCML_DS_64:
                thatValue = src._isSigned ? src._vint64 : static_cast<fcml_uint64_t>( src._vint64 );
                break;
            }

            // Now "this".
            switch( result._size ) {
            case FCML_DS_8:
                thisValue = result._isSigned ? result._vint8 : static_cast<fcml_uint8_t>( result._vint8 );
                thisValue = (*unsignedExpressionFn)( thisValue, thatValue );
                result._vint8 = static_cast<fcml_int8_t>( thisValue );
                break;
            case FCML_DS_16:
                thisValue = result._isSigned ? result._vint16 : static_cast<fcml_uint16_t>( result._vint16 );
                thisValue = (*unsignedExpressionFn)( thisValue, thatValue );
                result._vint16 = static_cast<fcml_int16_t>( thisValue );
                break;
            case FCML_DS_32:
                thisValue = result._isSigned ? result._vint32 : static_cast<fcml_uint32_t>( result._vint32 );
                thisValue = (*unsignedExpressionFn)( thisValue, thatValue );
                result._vint32 = static_cast<fcml_int32_t>( thisValue );
                break;
            case FCML_DS_64:
                thisValue = result._isSigned ? result._vint64 : static_cast<fcml_uint64_t>( result._vint64 );
                thisValue = (*unsignedExpressionFn)( thisValue, thatValue );
                result._vint64 = thisValue;
                break;
            }
        }

    }

private:
    fcml_usize _size;
    fcml_bool _isSigned;
    fcml_int8_t _vint8;
    fcml_int16_t _vint16;
    fcml_int32_t _vint32;
    fcml_int64_t _vint64;
};

/**
 * x86 - 64 register representation.
 * @since 1.1.0
 */
class Register {
public:

    /** Register types.
     * @since 1.1.0
     */
    enum RegisterType {
        /** Undefined register type. */
        REG_UNDEFINED = FCML_REG_UNDEFINED,
        /** General purpose register. */
        REG_GPR = FCML_REG_GPR,
        /** SIMD (SSE, MMX) register. */
        REG_SIMD = FCML_REG_SIMD,
        /** FPU register. */
        REG_FPU = FCML_REG_FPU,
        /** Segment register */
        REG_SEG = FCML_REG_SEG,
        /** Control register. */
        REG_CR = FCML_REG_CR,
        /** Debug register */
        REG_DR = FCML_REG_DR,
        /** Instruction pointer register. Used for relative RIP addressing. */
        REG_IP = FCML_REG_IP,
        /** Opmask register
         * @since 2.0.0
         */
        REG_OPMASK = FCML_REG_OPMASK
    };

    /**
     * Creates an empty register instance.
     * @since 1.1.0
     */
    Register() :
        _type(REG_UNDEFINED),
        _size(0),
        _reg(0),
        _x64_exp(FCML_FALSE) {
    }

    /**
     * Creates a register instance for given register structure.
     * @param reg The source register as the FCML structure.
     * @since 1.1.0
     */
    Register( const fcml_st_register &reg ) :
        _type(static_cast<RegisterType>( reg.type )),
        _size(reg.size),
        _reg(reg.reg),
		_x64_exp(reg.x64_exp? true : false) {
    }

    /**
     * Creates a register instance for given parameters.
     * @param reg The FCML register number.
     * @param size The register size.
     * @param type The register type.
     * @param x64_exp True if it's a 8-bit general purpose register for REX aware instruction. See manual.
     * @since 1.1.0
     */
    Register( fcml_uint8_t reg, fcml_usize size, RegisterType type = REG_GPR, fcml_bool x64_exp = FCML_FALSE ) :
        _type(type),
        _size(size),
        _reg(reg),
		_x64_exp(x64_exp?true:false) {
    }

    /**
     * @since 1.1.0
     */
    virtual ~Register() {
    }

public:

    /**
     * Gets the register number.
     * @return The register number.
     * @since 1.1.0
     */
    fcml_uint8_t getReg() const {
        return _reg;
    }

    /**
     * Sets the register number.
     * @param reg The register number.
     * @since 1.1.0
     */
    void setReg( fcml_uint8_t reg ) {
        _reg = reg;
    }

    /**
     * Gets the register size.
     * @return The register size.
     * @since 1.1.0
     */
    fcml_usize getSize() const {
        return _size;
    }

    /**
     * Sets the register size.
     * @param size The register size.
     * @since 1.1.0
     */
    void setSize( fcml_usize size ) {
        _size = size;
    }

    /**
     * Gets the register type.
     * @return The register type.
     * @since 1.1.0
     */
    RegisterType getType() const {
        return _type;
    }

    /**
     * Sets the register type.
     * @param type The register type.
     * @since 1.1.0
     */
    void setType( RegisterType type ) {
        _type = type;
    }

    /**
     * Gets true if it's a 8-bit general purpose register for REX aware instruction. See manual.
     * @return True if it's a 8-bit general purpose register for REX aware instruction. See manual..
     * @since 1.1.0
     */
    bool getX64Exp() const {
        return _x64_exp;
    }

    /**
     * Sets x64exp flag, see manual.
     * @param x64Exp The flag value.
     * @since 1.1.0
     */
    void setX64Exp( bool x64Exp ) {
        _x64_exp = x64Exp;
    }

public:

    /**
     * Compares registers.
     * @param reg The source register.
     * @return True if registers are equal.
     * @since 1.1.0
     */
    bool operator==( const Register &reg ) const {
        return _reg == reg._reg && _type == reg._type && _size == reg._size && _x64_exp == reg._x64_exp;
    }

    /**
     * Compares registers.
     * @param reg The source register.
     * @return True if registers are NOT equal.
     * @since 1.1.0
     */
    bool operator!=( const Register &reg ) const {
        return !( reg == *this );
    }

public:

    /**
     * Factory method for an undefined register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register UNDEF() {
        Register reg( 0, 0, Register::REG_UNDEFINED, FCML_FALSE );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register AL() {
        Register reg( ::fcml_reg_AL );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register AX() {
        Register reg( ::fcml_reg_AX );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register EAX() {
        Register reg( ::fcml_reg_EAX );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register RAX() {
        Register reg( ::fcml_reg_RAX );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register MM0() {
        Register reg( ::fcml_reg_MM0 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register XMM0() {
        Register reg( ::fcml_reg_XMM0 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register YMM0() {
        Register reg( ::fcml_reg_YMM0 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 2.0.0
     */
    static const Register ZMM0() {
        Register reg( ::fcml_reg_ZMM0 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register CL() {
        Register reg( ::fcml_reg_CL );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register CX() {
        Register reg( ::fcml_reg_CX );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register ECX() {
        Register reg( ::fcml_reg_ECX );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register RCX() {
        Register reg( ::fcml_reg_RCX );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register MM1() {
        Register reg( ::fcml_reg_MM1 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register XMM1() {
        Register reg( ::fcml_reg_XMM1 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register YMM1() {
        Register reg( ::fcml_reg_YMM1 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 2.0.0
     */
    static const Register ZMM1() {
        Register reg( ::fcml_reg_ZMM1 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register DL() {
        Register reg( ::fcml_reg_DL );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register DX() {
        Register reg( ::fcml_reg_DX );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register EDX() {
        Register reg( ::fcml_reg_EDX );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register RDX() {
        Register reg( ::fcml_reg_RDX );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register MM2() {
        Register reg( ::fcml_reg_MM2 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register XMM2() {
        Register reg( ::fcml_reg_XMM2 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register YMM2() {
        Register reg( ::fcml_reg_YMM2 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 2.0.0
     */
    static const Register ZMM2() {
        Register reg( ::fcml_reg_ZMM2 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register BL() {
        Register reg( ::fcml_reg_BL );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register BX() {
        Register reg( ::fcml_reg_BX );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register EBX() {
        Register reg( ::fcml_reg_EBX );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register RBX() {
        Register reg( ::fcml_reg_RBX );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register MM3() {
        Register reg( ::fcml_reg_MM3 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register XMM3() {
        Register reg( ::fcml_reg_XMM3 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register YMM3() {
        Register reg( ::fcml_reg_YMM3 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 2.0.0
     */
    static const Register ZMM3() {
        Register reg( ::fcml_reg_ZMM3 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register AH() {
        Register reg( ::fcml_reg_AH );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register SPL() {
        Register reg( ::fcml_reg_SPL );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register SP() {
        Register reg( ::fcml_reg_SP );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register ESP() {
        Register reg( ::fcml_reg_ESP );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register RSP() {
        Register reg( ::fcml_reg_RSP );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register MM4() {
        Register reg( ::fcml_reg_MM4 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register XMM4() {
        Register reg( ::fcml_reg_XMM4 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register YMM4() {
        Register reg( ::fcml_reg_YMM4 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 2.0.0
     */
    static const Register ZMM4() {
        Register reg( ::fcml_reg_ZMM4 );
        return reg;
    }


    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register CH() {
        Register reg( ::fcml_reg_CH );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register BPL() {
        Register reg( ::fcml_reg_BPL );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register BP() {
        Register reg( ::fcml_reg_BP );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register EBP() {
        Register reg( ::fcml_reg_EBP );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register RBP() {
        Register reg( ::fcml_reg_RBP );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register MM5() {
        Register reg( ::fcml_reg_MM5 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register XMM5() {
        Register reg( ::fcml_reg_XMM5 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register YMM5() {
        Register reg( ::fcml_reg_YMM5 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 2.0.0
     */
    static const Register ZMM5() {
        Register reg( ::fcml_reg_ZMM5 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register DH() {
        Register reg( ::fcml_reg_DH );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register SIL() {
        Register reg( ::fcml_reg_SIL );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register SI() {
        Register reg( ::fcml_reg_SI );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register ESI() {
        Register reg( ::fcml_reg_ESI );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register RSI() {
        Register reg( ::fcml_reg_RSI );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register MM6() {
        Register reg( ::fcml_reg_MM6 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register XMM6() {
        Register reg( ::fcml_reg_XMM6 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register YMM6() {
        Register reg( ::fcml_reg_YMM6 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 2.0.0
     */
    static const Register ZMM6() {
        Register reg( ::fcml_reg_ZMM6 );
        return reg;
    }


    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register BH() {
        Register reg( ::fcml_reg_BH );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register DIL() {
        Register reg( ::fcml_reg_DIL );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register DI() {
        Register reg( ::fcml_reg_DI );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register EDI() {
        Register reg( ::fcml_reg_EDI );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register RDI() {
        Register reg( ::fcml_reg_RDI );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register MM7() {
        Register reg( ::fcml_reg_MM7 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register XMM7() {
        Register reg( ::fcml_reg_XMM7 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register YMM7() {
        Register reg( ::fcml_reg_YMM7 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 2.0.0
     */
    static const Register ZMM7() {
        Register reg( ::fcml_reg_ZMM7 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register R8L() {
        Register reg( ::fcml_reg_R8L );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register R8W() {
        Register reg( ::fcml_reg_R8W );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register R8D() {
        Register reg( ::fcml_reg_R8D );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register R8() {
        Register reg( ::fcml_reg_R8 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register XMM8() {
        Register reg( ::fcml_reg_XMM8 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register YMM8() {
        Register reg( ::fcml_reg_YMM8 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 2.0.0
     */
    static const Register ZMM8() {
        Register reg( ::fcml_reg_ZMM8 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register R9L() {
        Register reg( ::fcml_reg_R9L );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register R9W() {
        Register reg( ::fcml_reg_R9W );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register R9D() {
        Register reg( ::fcml_reg_R9D );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register R9() {
        Register reg( ::fcml_reg_R9 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register XMM9() {
        Register reg( ::fcml_reg_XMM9 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register YMM9() {
        Register reg( ::fcml_reg_YMM9 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 2.0.0
     */
    static const Register ZMM9() {
        Register reg( ::fcml_reg_ZMM9 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register R10L() {
        Register reg( ::fcml_reg_R10L );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register R10W() {
        Register reg( ::fcml_reg_R10W );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register R10D() {
        Register reg( ::fcml_reg_R10D );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register R10() {
        Register reg( ::fcml_reg_R10 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register XMM10() {
        Register reg( ::fcml_reg_XMM10 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register YMM10() {
        Register reg( ::fcml_reg_YMM10 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 2.0.0
     */
    static const Register ZMM10() {
        Register reg( ::fcml_reg_ZMM10 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register R11L() {
        Register reg( ::fcml_reg_R11L );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register R11W() {
        Register reg( ::fcml_reg_R11W );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register R11D() {
        Register reg( ::fcml_reg_R11D );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register R11() {
        Register reg( ::fcml_reg_R11 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register XMM11() {
        Register reg( ::fcml_reg_XMM11 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register YMM11() {
        Register reg( ::fcml_reg_YMM11 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 2.0.0
     */
    static const Register ZMM11() {
        Register reg( ::fcml_reg_ZMM11 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register R12L() {
        Register reg( ::fcml_reg_R12L );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register R12W() {
        Register reg( ::fcml_reg_R12W );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register R12D() {
        Register reg( ::fcml_reg_R12D );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register R12() {
        Register reg( ::fcml_reg_R12 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register XMM12() {
        Register reg( ::fcml_reg_XMM12 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register YMM12() {
        Register reg( ::fcml_reg_YMM12 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 2.0.0
     */
    static const Register ZMM12() {
        Register reg( ::fcml_reg_ZMM12 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register R13L() {
        Register reg( ::fcml_reg_R13L );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register R13W() {
        Register reg( ::fcml_reg_R13W );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register R13D() {
        Register reg( ::fcml_reg_R13D );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register R13() {
        Register reg( ::fcml_reg_R13 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register XMM13() {
        Register reg( ::fcml_reg_XMM13 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register YMM13() {
        Register reg( ::fcml_reg_YMM13 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 2.0.0
     */
    static const Register ZMM13() {
        Register reg( ::fcml_reg_ZMM13 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register R14L() {
        Register reg( ::fcml_reg_R14L );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register R14W() {
        Register reg( ::fcml_reg_R14W );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register R14D() {
        Register reg( ::fcml_reg_R14D );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register R14() {
        Register reg( ::fcml_reg_R14 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register XMM14() {
        Register reg( ::fcml_reg_XMM14 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register YMM14() {
        Register reg( ::fcml_reg_YMM14 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 2.0.0
     */
    static const Register ZMM14() {
        Register reg( ::fcml_reg_ZMM14 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register R15L() {
        Register reg( ::fcml_reg_R15L );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register R15W() {
        Register reg( ::fcml_reg_R15W );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register R15D() {
        Register reg( ::fcml_reg_R15D );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register R15() {
        Register reg( ::fcml_reg_R15 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register XMM15() {
        Register reg( ::fcml_reg_XMM15 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register YMM15() {
        Register reg( ::fcml_reg_YMM15 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 2.0.0
     */
    static const Register ZMM15() {
        Register reg( ::fcml_reg_ZMM15 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 2.0.0
     */
    static const Register XMM16() {
        Register reg( ::fcml_reg_XMM16 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 2.0.0
     */
    static const Register YMM16() {
        Register reg( ::fcml_reg_YMM16 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 2.0.0
     */
    static const Register ZMM16() {
        Register reg( ::fcml_reg_ZMM16 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 2.0.0
     */
    static const Register XMM17() {
        Register reg( ::fcml_reg_XMM17 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 2.0.0
     */
    static const Register YMM17() {
        Register reg( ::fcml_reg_YMM17 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 2.0.0
     */
    static const Register ZMM17() {
        Register reg( ::fcml_reg_ZMM17 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 2.0.0
     */
    static const Register XMM18() {
        Register reg( ::fcml_reg_XMM18 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 2.0.0
     */
    static const Register YMM18() {
        Register reg( ::fcml_reg_YMM18 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 2.0.0
     */
    static const Register ZMM18() {
        Register reg( ::fcml_reg_ZMM18 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 2.0.0
     */
    static const Register XMM19() {
        Register reg( ::fcml_reg_XMM19 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 2.0.0
     */
    static const Register YMM19() {
        Register reg( ::fcml_reg_YMM19 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 2.0.0
     */
    static const Register ZMM19() {
        Register reg( ::fcml_reg_ZMM19 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 2.0.0
     */
    static const Register XMM20() {
        Register reg( ::fcml_reg_XMM20 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 2.0.0
     */
    static const Register YMM20() {
        Register reg( ::fcml_reg_YMM20 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 2.0.0
     */
    static const Register ZMM20() {
        Register reg( ::fcml_reg_ZMM20 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 2.0.0
     */
    static const Register XMM21() {
        Register reg( ::fcml_reg_XMM21 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 2.0.0
     */
    static const Register YMM21() {
        Register reg( ::fcml_reg_YMM21 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 2.0.0
     */
    static const Register ZMM21() {
        Register reg( ::fcml_reg_ZMM21 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 2.0.0
     */
    static const Register XMM22() {
        Register reg( ::fcml_reg_XMM22 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 2.0.0
     */
    static const Register YMM22() {
        Register reg( ::fcml_reg_YMM22 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 2.0.0
     */
    static const Register ZMM22() {
        Register reg( ::fcml_reg_ZMM22 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 2.0.0
     */
    static const Register XMM23() {
        Register reg( ::fcml_reg_XMM23 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 2.0.0
     */
    static const Register YMM23() {
        Register reg( ::fcml_reg_YMM23 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 2.0.0
     */
    static const Register ZMM23() {
        Register reg( ::fcml_reg_ZMM23 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 2.0.0
     */
    static const Register XMM24() {
        Register reg( ::fcml_reg_XMM24 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 2.0.0
     */
    static const Register YMM24() {
        Register reg( ::fcml_reg_YMM24 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 2.0.0
     */
    static const Register ZMM24() {
        Register reg( ::fcml_reg_ZMM24 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 2.0.0
     */
    static const Register XMM25() {
        Register reg( ::fcml_reg_XMM25 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 2.0.0
     */
    static const Register YMM25() {
        Register reg( ::fcml_reg_YMM25 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 2.0.0
     */
    static const Register ZMM25() {
        Register reg( ::fcml_reg_ZMM25 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 2.0.0
     */
    static const Register XMM26() {
        Register reg( ::fcml_reg_XMM26 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 2.0.0
     */
    static const Register YMM26() {
        Register reg( ::fcml_reg_YMM26 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 2.0.0
     */
    static const Register ZMM26() {
        Register reg( ::fcml_reg_ZMM26 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 2.0.0
     */
    static const Register XMM27() {
        Register reg( ::fcml_reg_XMM27 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 2.0.0
     */
    static const Register YMM27() {
        Register reg( ::fcml_reg_YMM27 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 2.0.0
     */
    static const Register ZMM27() {
        Register reg( ::fcml_reg_ZMM27 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 2.0.0
     */
    static const Register XMM28() {
        Register reg( ::fcml_reg_XMM28 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 2.0.0
     */
    static const Register YMM28() {
        Register reg( ::fcml_reg_YMM28 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 2.0.0
     */
    static const Register ZMM28() {
        Register reg( ::fcml_reg_ZMM28 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 2.0.0
     */
    static const Register XMM29() {
        Register reg( ::fcml_reg_XMM29 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 2.0.0
     */
    static const Register YMM29() {
        Register reg( ::fcml_reg_YMM29 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 2.0.0
     */
    static const Register ZMM29() {
        Register reg( ::fcml_reg_ZMM29 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 2.0.0
     */
    static const Register XMM30() {
        Register reg( ::fcml_reg_XMM30 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 2.0.0
     */
    static const Register YMM30() {
        Register reg( ::fcml_reg_YMM30 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 2.0.0
     */
    static const Register ZMM30() {
        Register reg( ::fcml_reg_ZMM30 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 2.0.0
     */
    static const Register XMM31() {
        Register reg( ::fcml_reg_XMM31 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 2.0.0
     */
    static const Register YMM31() {
        Register reg( ::fcml_reg_YMM31 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 2.0.0
     */
    static const Register ZMM31() {
        Register reg( ::fcml_reg_ZMM31 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register ES() {
        Register reg( ::fcml_reg_ES );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register CS() {
        Register reg( ::fcml_reg_CS );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register SS() {
        Register reg( ::fcml_reg_SS );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register DS() {
        Register reg( ::fcml_reg_DS );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register FS() {
        Register reg( ::fcml_reg_FS );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register GS() {
        Register reg( ::fcml_reg_GS );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register ST0() {
        Register reg( ::fcml_reg_ST0 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register ST1() {
        Register reg( ::fcml_reg_ST1 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register ST2() {
        Register reg( ::fcml_reg_ST2 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register ST3() {
        Register reg( ::fcml_reg_ST3 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register ST4() {
        Register reg( ::fcml_reg_ST4 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register ST5() {
        Register reg( ::fcml_reg_ST5 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register ST6() {
        Register reg( ::fcml_reg_ST6 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register ST7() {
        Register reg( ::fcml_reg_ST7 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register CR0() {
        Register reg( ::fcml_reg_CR0 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register CR2() {
        Register reg( ::fcml_reg_CR2 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register CR3() {
        Register reg( ::fcml_reg_CR3 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register CR4() {
        Register reg( ::fcml_reg_CR4 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register CR8() {
        Register reg( ::fcml_reg_CR8 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register DR0() {
        Register reg( ::fcml_reg_DR0 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register DR1() {
        Register reg( ::fcml_reg_DR1 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register DR2() {
        Register reg( ::fcml_reg_DR2 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register DR3() {
        Register reg( ::fcml_reg_DR3 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register DR4() {
        Register reg( ::fcml_reg_DR4 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register DR5() {
        Register reg( ::fcml_reg_DR5 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register DR6() {
        Register reg( ::fcml_reg_DR6 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register DR7() {
        Register reg( ::fcml_reg_DR7 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register IP() {
        Register reg( ::fcml_reg_IP );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register EIP() {
        Register reg( ::fcml_reg_EIP );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 1.1.0
     */
    static const Register RIP() {
        Register reg( ::fcml_reg_RIP );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 2.0.0
     */
    static const Register K0() {
        Register reg( ::fcml_reg_K0 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 2.0.0
     */
    static const Register K1() {
        Register reg( ::fcml_reg_K1 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 2.0.0
     */
    static const Register K2() {
        Register reg( ::fcml_reg_K2 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 2.0.0
     */
    static const Register K3() {
        Register reg( ::fcml_reg_K3 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 2.0.0
     */
    static const Register K4() {
        Register reg( ::fcml_reg_K4 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 2.0.0
     */
    static const Register K5() {
        Register reg( ::fcml_reg_K5 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 2.0.0
     */
    static const Register K6() {
        Register reg( ::fcml_reg_K6 );
        return reg;
    }

    /**
     * Factory method for a register.
     * @return A register instance.
     * @since 2.0.0
     */
    static const Register K7() {
        Register reg( ::fcml_reg_K7 );
        return reg;
    }

private:

    /** Register type. */
    RegisterType _type;
    /** Register size in bits. */
    fcml_usize _size;
    /** Register itself as a positive integer. @see REGISTERS_GROUP */
    fcml_uint8_t _reg;
    /** In case of SPL,BPL,SIL,DIL GPR registers has to be set to true. */
    bool _x64_exp;

};

/**
 * Describes far pointer.
 * @since 1.1.0
 */
class FarPointer {

public:

    /**
     * Creates an far pointer instance.
     * @since 1.1.0
     */
    FarPointer() :
        _segment(0),
        _offset_size(0),
        _offset16(0),
        _offset32(0) {
    }

    /**
     * Creates an far pointer instance.
     * @param segment A segment selector.
     * @param offset16 A 16-bit offset in the given segment.
     * @since 1.1.0
     */
    FarPointer( fcml_uint16_t segment, fcml_int16_t offset16 ) :
        _segment(segment),
        _offset_size(FCML_DS_16),
        _offset16(offset16),
        _offset32(0) {
    }
    /**
     * Creates an far pointer instance.
     * @param segment A segment selector.
     * @param offset32 A 32-bit offset in the given segment.
     * @since 1.1.0
     */
    FarPointer( fcml_uint16_t segment, fcml_int32_t offset32 ) :
        _segment(segment),
        _offset_size(FCML_DS_32),
        _offset16(0),
        _offset32(offset32) {
    }

    virtual ~FarPointer() {
    }

public:

    /**
     * Compares two far pointers.
     * @param fp The far pointer to be compared with the current one.
     * @return True if they are equal.
     * @since 1.1.0
     */
    bool operator==( const FarPointer &fp ) const {
        fcml_int32_t thisOffset;
        switch( _offset_size ) {
        case FCML_DS_32:
            thisOffset = _offset32;
            break;
        case FCML_DS_16:
            thisOffset = _offset16;
            break;
        }
        fcml_int32_t thatOffset;
        switch( fp._offset_size ) {
        case FCML_DS_32:
            thatOffset = fp._offset32;
            break;
        case FCML_DS_16:
            thatOffset = fp._offset16;
            break;
        }
        return thisOffset == thatOffset;
    }

    /**
     * Compares two far pointers.
     * @param fp The far pointer to be compared with the current one.
     * @return True if they are NOT equal.
     * @since 1.1.0
     */
    bool operator!=( const FarPointer &fp) const {
        return !(fp == *this);
    }

public:

    /**
     * Creates FarPointer instance for 16 bit segment and 16-bit offset.
     *
     * @param segment Segment selector.
     * @param offset 16-bit address.
     * @return FarPointer instance.
     * @since 1.1.0
     */
    static FarPointer off16( fcml_uint16_t segment, fcml_int16_t offset ) {
        return FarPointer(segment, offset);
    }

   /**
    * Creates FarPointer instance for 16 bit segment and 32-bit offset.
    *
    * @param segment Segment selector.
    * @param offset 32-bit address.
    * @return FarPointer instance.
    */
    static FarPointer off32( fcml_uint16_t segment, fcml_int32_t offset ) {
        return FarPointer(segment, offset);
    }

public:

    /**
     * Gets offset size.
     *
     * @return Offset size.
     * @since 1.1.0
     */
    fcml_usize getOffsetSize() const {
        return _offset_size;
    }

    /**
     * Sets offset size.
     *
     * @param offsetSize The new offset size to be set.
     * @since 1.1.0
     */
    void setOffsetSize( fcml_usize offsetSize ) {
        _offset_size = offsetSize;
    }

    /**
     * Gets the 16-bit offset.
     *
     * @return 16-bit offset.
     * @since 1.1.0
     */
    fcml_int16_t getOffset16() const {
        return _offset16;
    }

    /**
     * Sets 16-bit offset.
     *
     * @param offset16 Sets 16-bit offset.
     * @since 1.1.0
     */
    void setOffset16( fcml_int16_t offset16 ) {
        _offset16 = offset16;
    }

    /**
     * Gets 32-bit offset.
     *
     * @return 32-bit offset.
     * @since 1.1.0
     */
    fcml_int32_t getOffset32() const {
        return _offset32;
    }

    /**
     * Sets 32-bit offset.
     *
     * @param offset32 Sets 32-bit offset.
     * @since 1.1.0
     */
    void setOffset32( fcml_int32_t offset32 ) {
        _offset32 = offset32;
    }

    /**
     * Gets segment selector.
     *
     * @return 16-bit segment selector.
     * @since 1.1.0
     */
    fcml_uint16_t getSegment() const {
        return _segment;
    }

    /**
     * Sets segment selector.
     *
     * @param segment Segment selector.
     * @since 1.1.0
     */
    void setSegment( fcml_uint16_t segment ) {
        _segment = segment;
    }

private:

    /** 16-bit Code segment. */
    fcml_uint16_t _segment;
    /** Size of the offset. */
    fcml_usize _offset_size;
    /** 16-bit offset. */
    fcml_int16_t _offset16;
    /** 32-bit offset. */
    fcml_int32_t _offset32;

};

/**
 * Describes segment register.
 * @since 1.1.0
 */
class SegmentSelector {
public:

    /**
     * Creates an empty segment selector instance.
     * @since 1.1.0
     */
    SegmentSelector() :
        _segmentSelector(),
        _isDefaultReg(false) {
    }

    /**
     * Creates a segment selector instance for given parameters.
     * @param segmentSelector A segment register.
     * @param isDefaultReg Information if the register is the default one.
     * @since 1.1.0
     */
    SegmentSelector( const Register &segmentSelector, bool isDefaultReg = FCML_TRUE ) :
        _segmentSelector(segmentSelector),
        _isDefaultReg(isDefaultReg) {
    }

    virtual ~SegmentSelector() {
    }

public:

    /**
     * Checks if two segment selector are equal.
     * @param segmentSelector The source segment selector.
     * @return True if they are equal.
     * @since 1.1.0
     */
    bool operator==( const SegmentSelector &segmentSelector ) const {
        // It really doesn't matter if it is the default segment register in a given context.
        return segmentSelector._segmentSelector == _segmentSelector;
    }

    /**
     * Checks if two segment selector are not equal.
     * @param segmentSelector The source segment selector.
     * @return True if they are NOT equal.
     * @since 1.1.0
     */
    bool operator!=( const SegmentSelector &segmentSelector ) const {
        return !(*this == segmentSelector);
    }

    /**
     * Casting operator.
     * @return The segment register.
     * @since 1.1.0
     */
    operator Register() const {
        return _segmentSelector;
    }

    /**
     * Copies one segment selector to another.
     * @param reg The source segment selector.
     * @return The destination segment selector.
     * @since 1.1.0
     */
    SegmentSelector& operator=( const SegmentSelector &reg ) {
        if( &reg != this ) {
            _isDefaultReg = reg._isDefaultReg;
            _segmentSelector = reg._segmentSelector;
        }
        return *this;
    }

public:

    /**
     * Creates segment selector for the given register.
     *
     * @param segmentSelector Segment register.
     * @param isDefaultReg True if the register is the default one in the given context.
     * @return Prepared segment selector.
     * @since 1.1.0
     */
    static SegmentSelector seg( const Register &segmentSelector, bool isDefaultReg ) {
        return SegmentSelector( segmentSelector, isDefaultReg );
    }

public:

    /**
     * Returns true if a register stored in the segment selector is the default one
     * in the context the segment selector is used.
     *
     * @return True if register is the default one.
     * @since 1.1.0
     */
    bool isDefaultReg() const {
        return _isDefaultReg;
    }

    /**
     * Sets "default" flag for the segment selector.
     *
     * @param isDefaultReg True if the register is the default one in the given context.
     * @since 1.1.0
     */
    void setDefaultReg( bool isDefaultReg ) {
        _isDefaultReg = isDefaultReg;
    }

    /**
     * Gets constant segment register associated with the selector.
     *
     * @return Constant segment register.
     * @since 1.1.0
     */
    const Register& getSegmentSelector() const {
        return _segmentSelector;
    }

    /**
     * Gets segment register associated with the selector.
     *
     * @return Segment register.
     * @since 1.1.0
     */
    Register& getSegmentSelector() {
        return _segmentSelector;
    }

    /**
     * Sets segment register for the selector.
     *
     * @param segmentSelector Segment register.
     * @since 1.1.0
     */
    void setSegmentSelector( const Register& segmentSelector ) {
        _segmentSelector = segmentSelector;
    }

private:
    /** Segment register. */
    Register _segmentSelector;
    /** True if this is a default segment register. */
    bool _isDefaultReg;
};

/**
 * Describes effective address.
 *
 * It's a counterpart to the fcml_st_effective_address structure.
 * @since 1.1.0
 */
class EffectiveAddress {
public:

    /**
     * Creates an empry effective address.
     * @since 1.1.0
     */
    EffectiveAddress() :
        _scaleFactor(0){
    }

    /**
     * Creates an effective address instance with the displacement only.
     * @param displacement The displacement value.
     * @since 1.1.0
     */
    EffectiveAddress( const Integer &displacement ) :
        _scaleFactor(0),
        _displacement(displacement) {
    }

    /**
     * Creates an effective address instance with the base register only.
     * @param base The base register.
     * @since 1.1.0
     */
    EffectiveAddress( const Register &base ) :
        _base(base),
        _scaleFactor(0) {
    }

    /**
     * Creates an effective address instance with the base register and displacement only.
     * @param base The base register.
     * @param displacement The displacement value.
     * @since 1.1.0
     */
    EffectiveAddress( const Register &base, const Integer &displacement ) :
        _base(base),
        _scaleFactor(0),
        _displacement(displacement) {
    }

    /**
     * Creates an effective address instance with the index register, scale factor and displacement.
     * @param index The index register.
     * @param scaleFactor The scale factor value.
     * @param displacement The displacement.
     * @since 1.1.0
     */
    EffectiveAddress( const Register &index, fcml_uint8_t scaleFactor, const Integer &displacement ) :
        _index(index),
        _scaleFactor(scaleFactor),
        _displacement(displacement) {
    }

    /**
     * Creates an effective address instance with the base register and index register.
     * @param base The base register.
     * @param index The index register.
     * @since 1.1.0
     */
    EffectiveAddress( const Register &base, const Register &index ) :
        _base(base),
        _index(index),
        _scaleFactor(0) {
    }

    /**
     * Creates an effective address instance with the base register, index register and scale factor set.
     * @param base The base register.
     * @param index THe index register.
     * @param scaleFactor The scale factor.
     * @since 1.1.0
     */
    EffectiveAddress( const Register &base, const Register &index, fcml_uint8_t scaleFactor ) :
        _base(base),
        _index(index),
        _scaleFactor(scaleFactor) {
    }

    /**
     * Creates an effective address instance with the base register, index register, scale factor and displacement set.
     * @param base The base register.
     * @param index The index register.
     * @param scaleFactor The scale factor value.
     * @param displacement The displacement.
     * @since 1.1.0
     */
    EffectiveAddress( const Register &base, const Register &index, fcml_uint8_t scaleFactor, const Integer &displacement ) :
        _base(base),
        _index(index),
        _scaleFactor(scaleFactor),
        _displacement(displacement) {
    }

    /**
     * @since 1.1.0
     */
    virtual ~EffectiveAddress() {
    }

public:

    /**
     * Checks whether two effective addresses are equal or not.
     * @param address The source address to be compared.
     * @return True if they are equal.
     * @since 1.1.0
     */
    bool operator==( const EffectiveAddress &address ) const {
        if( &address == this ) {
            return true;
        }
        return _base == address._base &&
                _index == address._index &&
                _scaleFactor == address._scaleFactor &&
                _displacement == address._displacement;
    }

    /**
     * Checks whether two effective addresses are equal or not.
     * @param address The source address to be compared.
     * @return True if they are NOT equal.
     * @since 1.1.0
     */
    bool operator!=( const EffectiveAddress &address ) const {
        return !(address == *this);
    }

public:

    /**
     * Factory method which creates an effective address instance with the displacement only.
     * @param displacement The displacement value.
     * @since 1.1.0
     */
    static EffectiveAddress addr( const Integer &displacement ) {
        return EffectiveAddress( displacement );
    }

    /**
     * Factory method which creates an effective address instance with the base register only.
     * @param base The base register.
     * @since 1.1.0
     */
    static EffectiveAddress addr( const Register &base ) {
        return EffectiveAddress( base );
    }

    /**
     * Factory method which creates an effective address instance with the base register and displacement.
     * @param base The base register.
     * @param displacement The displacement value.
     * @since 1.1.0
     */
    static EffectiveAddress addr( const Register &base, const Integer &displacement ) {
        return EffectiveAddress( base, displacement );
    }

    /**
     * Factory method which creates an effective address instance with the index register, scale factor and displacement.
     * @param index The index register.
     * @param scaleFactor The scale factor.
     * @param displacement The displacement value.
     * @since 1.1.0
     */
    static EffectiveAddress addr( const Register &index, fcml_uint8_t scaleFactor, const Integer &displacement ) {
        return EffectiveAddress( index, scaleFactor, displacement );
    }

    /**
     * Factory method which creates an effective address instance with the base register and index register.
     * @param base The base register.
     * @param index The index register.
     * @since 1.1.0
     */
    static EffectiveAddress addr( const Register &base, const Register &index ) {
        return EffectiveAddress( base, index, 0 );
    }

    /**
     * Factory method which creates an effective address instance with the base register, index register and scale factor.
     * @param base The base register.
     * @param index The index register.
     * @param scaleFactor The scale factor.
     * @since 1.1.0
     */
    static EffectiveAddress addr( const Register &base, const Register &index, fcml_uint8_t scaleFactor ) {
        return EffectiveAddress( base, index, scaleFactor );
    }

    /**
     * Factory method which creates an effective address instance with the base register, index register, scale factor and displacement.
     * @param base The base register.
     * @param index The index register.
     * @param scaleFactor The scale factor.
     * @param displacement The displacement value.
     * @since 1.1.0
     */
    static EffectiveAddress addr( const Register &base, const Register &index, fcml_uint8_t scaleFactor, const Integer &displacement ) {
        return EffectiveAddress( base, index, scaleFactor, displacement );
    }

public:

    /**
     * Gets the constant base register associated with the effective address.
     *
     * @return The constant base register.
     * @since 1.1.0
     */
    const Register& getBase() const {
        return _base;
    }

    /**
     * Gets the base register associated with the effective address.
     *
     * @return The base register.
     * @since 1.1.0
     */
    Register& getBase() {
        return _base;
    }

    /**
     * Sets a new base register for the effective address.
     *
     * @param base The new base register to be set.
     * @return Effective address itself.
     * @since 1.1.0
     */
    EffectiveAddress& setBase( const Register &base ) {
        _base = base;
        return *this;
    }

    /**
     * Gets the constant displacement associated with the effective address.
     *
     * @return The constant displacement.
     * @since 1.1.0
     */
    const Integer& getDisplacement() const {
        return _displacement;
    }

    /**
     * Gets the displacement associated with the effective address.
     *
     * @return The displacement.
     * @since 1.1.0
     */
    Integer& getDisplacement() {
        return _displacement;
    }

    /**
     * Sets a new displacement value for the effective address.
     *
     * @param displacement The new displacement for effective address.
     * @return The effective address itself.
     * @since 1.1.0
     */
    EffectiveAddress& setDisplacement( const Integer &displacement ) {
        _displacement = displacement;
        return *this;
    }

    /**
     * Gets the constant index register associated with the effective address.
     *
     * @return The index register.
     * @since 1.1.0
     */
    const Register& getIndex() const {
        return _index;
    }

    /**
     * Gets the index register associated with the effective address.
     *
     * @return The index register.
     * @since 1.1.0
     */
    Register& getIndex() {
        return _index;
    }

    /**
     * Sets a new index register for the effective address.
     *
     * @param index The new index register for the effective address.
     * @return The effective address itself.
     * @since 1.1.0
     */
    EffectiveAddress& setIndex( const Register &index ) {
        _index = index;
        return *this;
    }

    /**
     * Gets a scale factor value associated with the effective address.
     *
     * @return The scale factor.
     * @since 1.1.0
     */
    fcml_uint8_t getScaleFactor() const {
        return _scaleFactor;
    }

    /**
     * Sets a new scale factor for the effective address.
     *
     * @param scaleFactor The new scale factor value.
     * @return Effective address itself.
     * @since 1.1.0
     */
    EffectiveAddress& setScaleFactor( fcml_uint8_t scaleFactor ) {
        _scaleFactor = scaleFactor;
        return *this;
    }

private:
    /** Base register. */
    Register _base;
    /** Index register. */
    Register _index;
    /** Scale factor. */
    fcml_uint8_t _scaleFactor;
    /** Displacement. */
    Integer _displacement;
};

/** Address operand.
 *
 * It's a counterpart to the fcml_st_address structure.
 * @since 1.1.0
 */
class Address {

public:

    /** Addressing type, see fcml_en_address_form enumerator.
     * @since 1.1.0
     */
    enum AddressForm {
        /** Default value set if memory addressing hasn't been configured. */
        AF_UNDEFINED = FCML_AF_UNDEFINED,
        /** Absolute offset (address). */
        AF_OFFSET = FCML_AF_OFFSET,
        /** Effective address combined from address components like base register, index registers, factor, displacement etc... */
        AF_COMBINED = FCML_AF_COMBINED
    };

    /**
     * Creates an empty address.
     * @since 1.1.0
     */
    Address() :
        _size_operator( FCML_DS_UNDEF ),
        _address_form( AF_UNDEFINED ) {
    }

    /**
     * Creates an address instance with an offset and optional size operator set.
     *
     * @param offset Offset to be set for the address.
     * @param sizeOperator The optional size operator, set to FCML_DS_UNDEF by default.
     * @since 1.1.0
     */
    Address( const Integer &offset, fcml_usize sizeOperator = FCML_DS_UNDEF ) :
        _size_operator( sizeOperator ),
        _address_form( AF_OFFSET ),
        _offset( offset ) {
    }

    /**
     * Creates an address instance with an effective address and optional size operator set.
     *
     * @param effectiveAddress The effective address to be set for the address.
     * @param sizeOperator The optional size operator, set to FCML_DS_UNDEF by default.
     * @since 1.1.0
     */
    Address( const EffectiveAddress &effectiveAddress, fcml_usize sizeOperator = FCML_DS_UNDEF ) :
        _size_operator( sizeOperator ),
        _address_form( AF_COMBINED ),
        _effective_address( effectiveAddress ) {
    }

    /**
     * Creates an address instance with an effective address, segment selector and optional size operator set.
     *
     * @param effectiveAddress The effective address to be set for the address.
     * @param segmentSelector The segment selector.
     * @param sizeOperator The optional size operator, set to FCML_DS_UNDEF by default.
     * @since 1.1.0
     */
    Address( const EffectiveAddress &effectiveAddress, const SegmentSelector &segmentSelector, fcml_usize sizeOperator = FCML_DS_UNDEF ) :
        _size_operator( sizeOperator ),
        _address_form( AF_COMBINED ),
        _segment_selector( segmentSelector ),
        _effective_address( effectiveAddress ) {
    }

    /** @since 1.1.0 */
    virtual ~Address() {
    }

public:

    /**
     * Factory method which creates an effective address instance with the displacement only.
     * @param displacement The displacement value.
     * @param sizeOperator Size operator.
     * @since 1.1.0
     */
    static Address effective( const Integer &displacement, fcml_usize sizeOperator = FCML_DS_UNDEF ) {
        return effective( EffectiveAddress( displacement ), sizeOperator );
    }

    /**
     * Factory method which creates an effective address instance with the base register only.
     * @param base The base register.
     * @param sizeOperator Size operator.
     * @since 1.1.0
     */
    static Address effective( const Register &base, fcml_usize sizeOperator = FCML_DS_UNDEF ) {
        return effective( EffectiveAddress( base ), sizeOperator );
    }

    /**
     * Factory method which creates an effective address instance with the base register and displacement.
     * @param base The base register.
     * @param displacement The displacement value.
     * @param sizeOperator Size operator.
     * @since 1.1.0
     */
    static Address effective( const Register &base, const Integer &displacement, fcml_usize sizeOperator = FCML_DS_UNDEF ) {
        return effective( EffectiveAddress( base, displacement ), sizeOperator );
    }

    /**
     * Factory method which creates an effective address instance with the index register, scale factor and displacement.
     * @param index The index register.
     * @param scaleFactor The scale factor.
     * @param displacement The displacement value.
     * @param sizeOperator Size operator.
     * @since 1.1.0
     */
    static Address effective( const Register &index, fcml_uint8_t scaleFactor, const Integer &displacement, fcml_usize sizeOperator = FCML_DS_UNDEF ) {
        return effective( EffectiveAddress( index, scaleFactor, displacement ), sizeOperator );
    }

    /**
     * Factory method which creates an effective address instance with the base register and index register.
     * @param base The base register.
     * @param index The index register.
     * @param sizeOperator Size operator.
     * @since 1.1.0
     */
    static Address effective( const Register &base, const Register &index, fcml_usize sizeOperator = FCML_DS_UNDEF ) {
        return effective( EffectiveAddress( base, index, 0 ), sizeOperator );
    }

    /**
     * Factory method which creates an effective address instance with the base register, index register and scale factor.
     * @param base The base register.
     * @param index The index register.
     * @param scaleFactor The scale factor.
     * @param sizeOperator Size operator.
     * @since 1.1.0
     */
    static Address effective( const Register &base, const Register &index, fcml_uint8_t scaleFactor, fcml_usize sizeOperator = FCML_DS_UNDEF ) {
        return effective( EffectiveAddress( base, index, scaleFactor ), sizeOperator );
    }

    /**
     * Factory method which creates an effective address instance with the base register, index register, scale factor and displacement.
     * @param base The base register.
     * @param index The index register.
     * @param scaleFactor The scale factor.
     * @param displacement The displacement value.
     * @param sizeOperator Size operator.
     * @since 1.1.0
     */
    static Address effective( const Register &base, const Register &index, fcml_uint8_t scaleFactor, const Integer &displacement, fcml_usize sizeOperator = FCML_DS_UNDEF ) {
        return effective( EffectiveAddress( base, index, scaleFactor, displacement ), sizeOperator );
    }


public:

    /**
     * Checks if two addresses are equal or not.
     * @param address The address to be compared with the current one.
     * @return True if they are equal.
     * @since 1.1.0
     */
    bool operator==( const Address &address ) const {
        if( &address == this ) {
            return true;
        }
        return _size_operator == address._size_operator &&
                _address_form == address._address_form &&
                _segment_selector == address._segment_selector &&
                _effective_address == address._effective_address &&
                _offset == address._offset;
    }

    /**
     * Checks if two addresses are equal or not.
     * @param address The address to be compared with the current one.
     * @return True if they are NOT equal.
     * @since 1.1.0
     */
    bool operator!=( const Address &address ) const {
        return !(address == *this );
    }

public:

    /**
     * Factor method which creates an instance of the address for an effective address, segment selector and optional size operator.
     *
     * @param effectiveAddress The effective address to be set for the address.
     * @param segmentSelector The segment selector.
     * @param sizeOperator The optional size operator, set to FCML_DS_UNDEF by default.
     * @return The created address instance.
     * @since 1.1.0
     */
    static Address effective( const EffectiveAddress &effectiveAddress, const SegmentSelector &segmentSelector, fcml_usize sizeOperator = FCML_DS_UNDEF ) {
        return Address( effectiveAddress, segmentSelector, sizeOperator );
    }

    /**
     * Factor method which creates an address instance with an effective address and optional size operator set.
     *
     * @param effectiveAddress The effective address to be set for the address.
     * @param sizeOperator The optional size operator, set to FCML_DS_UNDEF by default.
     * @return The created address instance.
     * @since 1.1.0
     */
    static Address effective( const EffectiveAddress &effectiveAddress, fcml_usize sizeOperator = FCML_DS_UNDEF ) {
        return Address( effectiveAddress, sizeOperator );
    }

    /**
     * Factor method which creates an address instance with an offset and optional size operator set.
     *
     * @param offset The offset to be set for the address.
     * @param sizeOperator The optional size operator, set to FCML_DS_UNDEF by default.
     * @return The created address instance.
     * @since 1.1.0
     */
    static Address offset( const Integer &offset, fcml_usize sizeOperator = FCML_DS_UNDEF ) {
        return Address( offset, sizeOperator );
    }

public:

    /**
     * Returns true if address holds effective address.
     *
     * @return Returns true if address holds effective address.
     * @since 1.1.0
     */
    bool isEffectiveAddress() const {
        return _address_form == AF_COMBINED;
    }

    /**
     * Returns true if address holds an offset only.
     *
     * @return Returns true if address holds an offset only.
     * @since 1.1.0
     */
    bool isOffset() const {
        return _address_form == AF_OFFSET;
    }

    /**
     * Gets an address form. See fcml_en_address_form for more details.
     *
     * @return The address form.
     * @since 1.1.0
     */
    AddressForm getAddressForm() const {
        return _address_form;
    }

    /**
     * Sets a new address form for the effective address.
     *
     * @param addressForm The address form to be set for the effective address.
     *
     * @return Address itself.
     * @since 1.1.0
     */
    Address& setAddressForm( AddressForm addressForm ) {
        _address_form = addressForm;
        return *this;
    }

    /**
     * Gets reference to the constant effective address associated with the address.
     *
     * @return The constant effective address.
     * @since 1.1.0
     */
    const EffectiveAddress& getEffectiveAddress() const {
        return _effective_address;
    }

    /**
     * Gets reference to the effective address associated with the address.
     *
     * @return The effective address.
     * @since 1.1.0
     */
    EffectiveAddress& getEffectiveAddress() {
        return _effective_address;
    }

    /**
     * Sets a new effective address for the address.
     *
     * @param effectiveAddress The new address to be set for the effective address.
     * @return The address itself.
     * @since 1.1.0
     */
    Address& setEffectiveAddress( const EffectiveAddress& effectiveAddress ) {
        _effective_address = effectiveAddress;
        return *this;
    }

    /**
     * Gets the constant offset associated with the address.
     *
     * @return The offset associated with the address.
     * @since 1.1.0
     */
    const Integer& getOffset() const {
        return _offset;
    }

    /**
     * Gets the offset associated with the address.
     *
     * @return The offset associated with the address.
     * @since 1.1.0
     */
    Integer& getOffset() {
        return _offset;
    }

    /**
     * Sets a new offset for the address.
     *
     * @param offset The enw offset to be set for the address.
     * @return The address itself.
     * @since 1.1.0
     */
    Address& setOffset( const Integer &offset ) {
        this->_offset = offset;
        return *this;
    }

    /**
     * Gets the constant segment selector associated with the address.
     *
     * @return The segment selector associated with the address.
     * @since 1.1.0
     */
    const SegmentSelector& getSegmentSelector() const {
        return _segment_selector;
    }

    /**
     * Gets the segment selector associated with the address.
     *
     * @return The segment selector associated with the address.
     * @since 1.1.0
     */
    SegmentSelector& getSegmentSelector() {
        return _segment_selector;
    }

    /**
     * Sets a new segment selector for the address.
     *
     * @param segmentSelector The new segment selector for the address.
     * @return The address itself.
     * @since 1.1.0
     */
    Address& setSegmentSelector( const SegmentSelector &segmentSelector ) {
        _segment_selector = segmentSelector;
        return *this;
    }

    /**
     * Gets the size operator associated with the address.
     *
     * @return The size operator.
     * @since 1.1.0
     */
    fcml_usize getSizeOperator() const {
        return _size_operator;
    }

    /**
     * Sets a new size operator for the address.
     *
     * @param sizeOperator The size operator.
     * @since 1.1.0
     */
    Address& setSizeOperator( fcml_usize sizeOperator ) {
        _size_operator = sizeOperator;
        return *this;
    }

private:

    /** Size of data accessed in memory.*/
    fcml_usize _size_operator;
    /** Memory addressing format: absolute offset/effective address. @see fcml_en_effective_address_form*/
    AddressForm _address_form;
    /** Segment register.*/
    SegmentSelector _segment_selector;
    /** Memory address for FCML_AF_COMBINED form.*/
    EffectiveAddress _effective_address;
    /** Memory address for FCML_AF_OFFSET form.*/
    Integer _offset;

};

/** Holds operand decorators.
 * @since 2.0.0
 */
class Decorators {
public:

    /**
     * Creates an empty operand decorators container.
     * @since 2.0.0
     */
    Decorators() : _z(FCML_FALSE), _operandMaskReg(Register::UNDEF()),
        _sae(FCML_FALSE) {
    }

    /**
     * Sets a new AVX-512 {z} decorator.
     *
     * @param z {z} decorator.
     * @return Decorators.
     * @since 2.0.0
     */
    Decorators& setZ(fcml_bool z) {
        _z = z;
        return *this;
    }

    /**
     * Sets a new AVX-512 {bcast} decorator.
     *
     * @param bcast Decorator value.
     * @return Decorators..
     * @since 2.0.0
     */
    Decorators& setBcast(const Nullable<fcml_uint8_t> &bcast) {
        _bcast = bcast;
        return *this;
    }

    /**
     * Sets AVX-512 opmask register for {k} decorator.
     *
     * @param opmaskReg Opmask register.
     * @since 2.0.0
     */
    Decorators& setOpmaskReg( const Register& opmaskReg ) {
        _operandMaskReg = opmaskReg;
        return *this;
    }

    /**
     * Sets AVX-512 {er} decorator.
     *
     * @param er {er} decorator.
     * @since 2.0.0
     */
    Decorators& setEr(const Nullable<fcml_uint8_t> &er) {
        _er = er;
        return *this;
    }

    /**
     * Sets AVX-512 {sae} decorator.
     *
     * @param sae {sae} decorator.
     * @since 2.0.0
     */
    Decorators& setSae(const fcml_bool sae) {
        _sae = sae;
        return *this;
    }

    /**
     * Gets AVX-512 {z} operator.
     *
     * @return {z} operator.
     * @since 2.0.0
     */
    fcml_bool isZ() const {
        return _z;
    }

    /**
     * Gets AVX-512 {bcast} decorator.
     *
     * @return Value of {bcast} decorator.
     * @since 2.0.0
     */
    const Nullable<fcml_uint8_t>& getBcast() const {
        return _bcast;
    }

    /**
     * Gets constant AVX-512 opmask register for {k} decorator.
     *
     * @return Opmask register.
     * @since 2.0.0
     */
    const Register& getOpmaskReg() const {
        return _operandMaskReg;
    }

    /**
     * Gets AVX-512 opmask register for {k} decorator.
     *
     * @return Opmask register.
     * @since 2.0.0
     */
    Register& getOpmaskReg() {
        return _operandMaskReg;
    }

    /**
     * Gets AVX-512 {er} decorator.
     *
     * @return Value of {er} decorator.
     * @since 2.0.0
     */
    const Nullable<fcml_uint8_t>& getEr() const {
        return _er;
    }

    /**
     * Gets AVX-512 {sae} decorator.
     *
     * @return True if {sae} is set.
     * @since 2.0.0
     */
    fcml_bool isSae() const {
        return _sae;
    }

public:

    /**
     * Checks if two decorators containers are equal or not.
     * @param decorators Decorators.
     * @return True if they are equal.
     * @since 2.0.0
     */
    bool operator==(const Decorators &decorators) const {
        if(&decorators == this) {
            return true;
        }
        return _z == decorators._z &&
                _bcast == decorators._bcast &&
                _operandMaskReg == decorators._operandMaskReg &&
                _er == decorators._er &&
                _sae == decorators._sae;
    }

    /**
     * Checks if two decorators are equal or not.
     * @param decorators Decorators.
     * @return True if they are NOT equal.
     * @since 2.0.0
     */
    bool operator!=(const Decorators &decorators) const {
        return !(decorators == *this);
    }

private:
    /** Broadcasting: 2, 4, 8, 16, 32, 64. */
    Nullable<fcml_uint8_t> _bcast;
    /** Zeroing masking. */
    fcml_bool _z;
    /** The 64-bit k registers are: k0 through k7. */
    Register _operandMaskReg;
    /** Embedded rounding control. */
    Nullable<fcml_uint8_t> _er;
    /** Indicates support for SAE (Suppress All Exceptions). */
    fcml_bool _sae;
};

/** Instruction operand.
 * @since 1.1.0
 */
class Operand {
public:

    /** See fcml_en_operand_type structure for more details.
     * @since 1.1.0
     */
    enum OperandType {
        /** Operand not used. */
        OT_NONE = FCML_OT_NONE,
        /** Immediate integer value. */
        OT_IMMEDIATE = FCML_OT_IMMEDIATE,
        /** Direct far pointer. */
        OT_FAR_POINTER = FCML_OT_FAR_POINTER,
        /** Memory address. */
        OT_ADDRESS = FCML_OT_ADDRESS,
        /** Processor register. */
        OT_REGISTER = FCML_OT_REGISTER,
        /** Virtual operand */
        OT_VIRTUAL = FCML_OT_VIRTUAL
    };

    /**
     * Creates an undefined operand.
     * @since 1.1.0
     */
    Operand() :
        _hints( FCML_OP_HINT_UNDEFIEND ),
        _operandType( OT_NONE ) {
    }

    /**
     * Creates an immediate value operand for given integer.
     *
     * @param imm The immediate value as integer.
     * @param hints Optional operand level hints.
     * @since 1.1.0
     */
    Operand( const Integer &imm, fcml_hints hints = FCML_OP_HINT_UNDEFIEND ) :
        _hints( hints ),
        _operandType(OT_IMMEDIATE ),
        _immediate( imm ) {
    }

    /**
     * Creates a far pointer operand for given far pointer.
     *
     * @param pointer The far pointer for the operand.
     * @param hints Optional operand level hints.
     * @since 1.1.0
     */
    Operand( const FarPointer &pointer, fcml_hints hints = FCML_OP_HINT_UNDEFIEND ) :
        _hints( hints ),
        _operandType( OT_FAR_POINTER ),
        _farPointer( pointer ) {
    }

    /**
     * Creates an address operand for given address.
     *
     * @param address The address for the created operand.
     * @param hints Optional operand level hints.
     * @since 1.1.0
     */
    Operand( const Address &address, fcml_hints hints = FCML_OP_HINT_UNDEFIEND ) :
        _hints( hints ),
        _operandType( OT_ADDRESS ),
        _address( address ) {
    }

    /**
     * Creates a new register operand for given register.
     *
     * @param reg The register for the new operand being created.
     * @param hints Optional operand level hints.
     * @since 1.1.0
     */
    Operand( const Register &reg, fcml_hints hints = FCML_OP_HINT_UNDEFIEND ) :
        _hints( hints ),
        _operandType( OT_REGISTER ),
        _register( reg ) {
    }

public:

    /**
     * Checks if two operands are equal or not.
     *
     * @param op The operand to be compared with the current one.
     * @return True if the operands are equal.
     * @since 1.1.0
     */
    bool operator==( const Operand &op ) const {
        if( &op == this ) {
            return true;
        }
        bool equal = false;
        switch( _operandType ) {
        case OT_ADDRESS:
            equal = _address == op._address;
            break;
        case OT_FAR_POINTER:
            equal = _farPointer == op._farPointer;
            break;
        case OT_IMMEDIATE:
            equal = _immediate == op._immediate;
            break;
        case OT_REGISTER:
            equal = _register == op._register;
            break;
        case OT_VIRTUAL:
            equal = true;
            break;
        case OT_NONE:
            equal = true;
            break;
        }
        return equal && op._hints == _hints && op._decorators == _decorators;
    }

    /**
     * Checks if two operands are equal or not.
     *
     * @param op The operand to be compared with the current one.
     * @return True if the operands are NOT equal.
     * @since 1.1.0
     */
    bool operator!=( const Operand &op ) const {
        return !(op == *this);
    }

public:

    /**
     * Converts operand to the undefined one.
     * @since 1.1.0
     */
    void undef() {
        _operandType = OT_NONE;
    }

    /**
     * Sets given immediate value for the operand and makes it to be an immediate operand.
     *
     * @param imm The immediate value.
     * @since 1.1.0
     */
    void imm( const Integer &imm ) {
        _operandType = OT_IMMEDIATE;
        _immediate = imm;
    }

    /**
     * Converts operand to the far pointer and sets the segment selector and offset for it.
     *
     * @param seg The segment selector.
     * @param addr Offset.
     * @since 1.1.0
     */
    void far_ptr( fcml_uint16_t seg, fcml_int16_t addr ) {
        _operandType = OT_FAR_POINTER;
        _farPointer = FarPointer( seg, addr );
    }

    /**
     * Prepares far pointer operand for given components.
     *
     * @param seg The segment selector.
     * @param addr The offset.
     * @since 1.1.0
     */
    void far_ptr( fcml_uint16_t seg, fcml_int32_t addr ) {
        _operandType = OT_FAR_POINTER;
        _farPointer = FarPointer( seg, addr );
    }

    /**
     * Prepares far pointer operand for given far pointer.
     *
     * @param pointer Far pointer to be set for the operand.
     * @since 1.1.0
     */
    void far_ptr( const FarPointer &pointer ) {
        _operandType = OT_FAR_POINTER;
        _farPointer = pointer;
    }

    /**
     * Prepares address operand for given address.
     *
     * @param address The address to be set for the operand.
     * @since 1.1.0
     */
    void addr( const Address &address ) {
        _operandType = OT_ADDRESS;
        _address = address;
    }

    /**
     * Prepares address operand for given offset.
     *
     * @param offset The offset to be set for the operand.
     * @param sizeOperator The size operator to be set for the address.
     * @since 1.1.0
     */
    void off( const Integer &offset, fcml_usize sizeOperator = FCML_DS_UNDEF ) {
        _operandType = OT_ADDRESS;
        _address = Address( offset, sizeOperator );
    }

    /**
     * Prepares an address operand for given effective address and optional size operator.
     *
     * @param effectiveAddress The effective address.
     * @param sizeOperator The size operator.
     * @since 1.1.0
     */
    void addr( const EffectiveAddress &effectiveAddress, fcml_usize sizeOperator = FCML_DS_UNDEF ) {
        _operandType = OT_ADDRESS;
        _address = Address( effectiveAddress, sizeOperator );
    }

    /**
     * Prepares address operator for given parameters.
     *
     * @param effectiveAddress The effective address.
     * @param segmentSelector The segment selector.
     * @param sizeOperator The size operator.
     * @since 1.1.0
     */
    void addr( const EffectiveAddress &effectiveAddress, const SegmentSelector &segmentSelector, fcml_usize sizeOperator = FCML_DS_UNDEF ) {
        _operandType = OT_ADDRESS;
        _address = Address( effectiveAddress, segmentSelector, sizeOperator );
    }

    /**
     * Prepares operator for the given register.
     *
     * @param reg The register for the operator.
     * @since 1.1.0
     */
    void reg( const Register &reg ) {
        _operandType = OT_REGISTER;
        _register = reg;
    }

    /**
     * Prepares an register operator for given register compounds.
     *
     * @param reg A register number.
     * @param size A register size.
     * @param type A register type.
     * @param x64_exp An optional marker for the SPL, BPL, SIL etc. registers. See manual for more information.
     * @since 1.1.0
     */
    void reg( fcml_uint8_t reg, fcml_usize size, Register::RegisterType type = Register::REG_GPR, fcml_bool x64_exp = FCML_FALSE ) {
        _operandType = OT_REGISTER;
        _register = Register( reg, size, type, x64_exp );
    }

public:

    /**
     * Returns true if operand is an immediate value operand.
     *
     * @return True if operand is an immediate value operand.
     * @since 1.1.0
     */
    bool isImm() const {
        return _operandType == OT_IMMEDIATE;
    }

    /**
     * Returns true if operand is a register operand.
     *
     * @return True if operand is a register operand.
     * @since 1.1.0
     */
    bool isReg() const {
        return _operandType == OT_REGISTER;
    }

    /**
     * Returns true if operand is an address operand.
     *
     * @return True if operand is an address operand.
     * @since 1.1.0
     */
    bool isAddr() const {
        return _operandType == OT_ADDRESS;
    }

    /**
     * Returns true if operand is a far pointer operand.
     *
     * @return True if operand is a far pointer operand.
     * @since 1.1.0
     */
    bool isFar() const {
        return _operandType == OT_FAR_POINTER;
    }

    /**
     * Gets reference to the constant address associated with the operand.
     *
     * @return The reference to the address.
     * @since 1.1.0
     */
    const Address& getAddress() const {
        return _address;
    }

    /**
     * Gets reference to the address associated with the operand.
     *
     * @return The reference to the address.
     * @since 1.1.0
     */
    Address& getAddress() {
        return _address;
    }

    /**
     * Sets a new address for the operand.
     *
     * @param address The new address.
     * @return The operand itself.
     * @since 1.1.0
     */
    Operand& setAddress( const Address &address ) {
        _address = address;
        return *this;
    }

    /**
     * Gets a reference to the constant far pointer instance associated with the address.
     *
     * @return The far pointer instance associated with the address.
     * @since 1.1.0
     */
    const FarPointer& getFarPointer() const {
        return _farPointer;
    }

    /**
     * Gets a reference to the far pointer instance associated with the address.
     *
     * @return The far pointer instance associated with the address.
     * @since 1.1.0
     */
    FarPointer& getFarPointer() {
        return _farPointer;
    }

    /**
     * Sets a new far pointer for the operand.
     *
     * @param farPointer The new far pointer instance.
     * @return The operand itself.
     * @since 1.1.0
     */
    Operand& setFarPointer( const FarPointer &farPointer ) {
        _farPointer = farPointer;
        return *this;
    }

    /**
     * Gets a reference to the constant immediate value associated with the operand.
     *
     * @return The immediate value.
     * @since 1.1.0
     */
    const Integer& getImmediate() const {
        return _immediate;
    }

    /**
     * Gets a reference to the immediate value associated with the operand.
     *
     * @return The immediate value.
     * @since 1.1.0
     */
    Integer& getImmediate() {
        return _immediate;
    }

    /**
     * Sets a new immediate value for the address.
     *
     * @param immediate The new immediate value.
     * @return The operand itself.
     * @since 1.1.0
     */
    Operand& setImmediate( const Integer &immediate ) {
        _immediate = immediate;
        return *this;
    }

    /**
     * Gets operand type.
     *
     * @return The operand type.
     * @since 1.1.0
     */
    OperandType getOperandType() const {
        return _operandType;
    }

    /**
     * Sets a new operand type.
     *
     * @param operandType The new operand type.
     * @return The operand itself.
     * @since 1.1.0
     */
    Operand& setOperandType( OperandType operandType ) {
        _operandType = operandType;
        return *this;
    }

    /**
     * Returns a reference to the constant register associated with the operand.
     *
     * @return The reference to the register associated with the operand.
     * @since 1.1.0
     */
    const Register& getRegister() const {
        return _register;
    }

    /**
     * Returns a reference to the register associated with the operand.
     *
     * @return The reference to the register associated with the operand.
     * @since 1.1.0
     */
    Register& getRegister() {
        return _register;
    }

    /**
     * Sets a new register for the operand.
     *
     * @param reg The new register.
     * @return The operand itself.
     * @since 1.1.0
     */
    Operand& setRegister( const Register &reg ) {
        this->_register = reg;
        return *this;
    }

    /**
     * Gets hits associated with the operand.
     *
     * @return The hits associated with the operand.
     * @since 1.1.0
     */
    fcml_hints getHints() const {
       return _hints;
    }

    /**
     * Sets new operand level hits for the operand.
     *
     * @param hints The new hits to be set.
     * @return The operand itself.
     * @since 1.1.0
     */
    Operand& setHints( fcml_hints hints ) {
       _hints = hints;
       return *this;
    }

    /**
     * Gets constant decorators associated with the operand.
     *
     * @return The decorators associated with the operand.
     * @since 2.0.0
     */
    const Decorators& getDecorators() const {
       return _decorators;
    }

    /**
     * Gets decorators associated with the operand.
     *
     * @return The decorators associated with the operand.
     * @since 2.0.0
     */
    Decorators& getDecorators() {
       return _decorators;
    }

    /**
     * Sets new operand decorators for the operand.
     *
     * @param decorators The new decorators to be set.
     * @return The operand itself.
     * @since 2.0.0
     */
    Operand& setDecorators(const Decorators& decorators) {
       _decorators = decorators;
       return *this;
    }

    // Hints

    /**
     * Returns information if the operand is multimedia  one or not. For more details about the
     * multimedia operand head over to the manual pages.
     *
     * @return true if it's a multimedia operand.
     * @since 1.1.0
     */
    bool isMultimedia() const {
        return _hints & FCML_OP_HINT_MULTIMEDIA_INSTRUCTION;
    }

    /**
     * Returns true if it's an displacement relative address.
     *
     * @return True if it's an displacement relative address.
     * @since 1.1.0
     */
    bool isDisRelativeAddress() const {
		return ( _hints & FCML_OP_HINT_DISPLACEMENT_RELATIVE_ADDRESS ) ? true : false;
    }

    /**
     * Returns true if it's pseudo opcode operand. More information
     * about pseudo opcodes in the manual.
     *
     * @return True if it's pseudo opcode operand.
     * @since 1.1.0
     */
    bool isPseudoOpcode() const {
		return ( _hints & FCML_OP_HINT_PSEUDO_OPCODE ) ? true : false;
    }

    /**
     * Returns true if it's an absolute offset being set in the operand.
     *
     * @return True in case of absolute addressing being used.
     * @since 1.1.0
     */
    bool isAbsoluteAddressing() const {
		return ( _hints & FCML_OP_HINT_ABSOLUTE_ADDRESSING ) ? true : false;
    }

    /**
     * Returns true is relative addressing is used.
     *
     * @return True in case of relative addressing.
     * @since 1.1.0
     */
    bool isRelativeAddressing() const {
		return ( _hints & FCML_OP_HINT_RELATIVE_ADDRESSING ) ? true : false;
    }

    /**
     * Returns true if the SIB byte is used.
     *
     * @return True if the SIB byte is used.
     * @since 1.1.0
     */
    bool isSIBEncoding() const {
		return ( _hints & FCML_OP_HINT_SIB_ENCODING ) ? true : false;
    }

public:

    /**
     * A casting operator.
     * @since 1.1.0
     */
    operator const Integer&() const {
        return _immediate;
    }

    /**
     * A casting operator.
     * @since 1.1.0
     */
    operator const FarPointer&() const {
        return _farPointer;
    }

    /**
     * A casting operator.
     * @since 1.1.0
     */
    operator const Address&() const {
        return _address;
    }

    /**
     * A casting operator.
     * @since 1.1.0
     */
    operator const Register&() const {
        return _register;
    }

private:

    /** Operand hints */
    fcml_hints _hints;
    /** Operand type */
    OperandType _operandType;
    /** Describes immediate operand */
    Integer _immediate;
    /** Describes far pointer. */
    FarPointer _farPointer;
    /** Describes address. */
    Address _address;
    /** Describes register. */
    Register _register;
    /** Operand decorators.
     * since 2.0.0
     */
    Decorators _decorators;

};

/** Operand builder.
 * A builder that exposes various factory methods that can be used to create
 * several types of the instruction operands. These methods are very simple
 * so no API documentation has been provided for now. Just take a look at
 * the source code.
 *
 * @since 1.1.0
 */
class OB {
public:

    /**
     * Factory method which builds an empty operand.
     * @return The empty operand.
     * @since 1.1.0
     */
    static Operand undef() {
        return Operand();
    }

    /**
     * Factory method which builds an immediate operand.
     * @return The immediate operand.
     * @since 1.1.0
     */
    static Operand imm( const Integer &imm ) {
        return Operand( imm );
    }

    /**
     * Factory method which builds a far pointer operand.
     * @param seg A segment selector.
     * @param addr An 16-bit offset value.
     * @return The far pointer operand.
     * @since 1.1.0
     */
    static Operand far_ptr( fcml_uint16_t seg, fcml_int16_t addr ) {
        return Operand( FarPointer( seg, addr ) );
    }

    /**
     * Factory method which builds a far pointer operand.
     * @param seg A segment selector.
     * @param addr An 32-bit offset value.
     * @return The far pointer operand.
     * @since 1.1.0
     */
    static Operand far_ptr( fcml_uint16_t seg, fcml_int32_t addr ) {
        return Operand( FarPointer( seg, addr ) );
    }

    /**
     * Factory method which builds a far pointer operand.
     * @param pointer A far pointer instance.
     * @return The far pointer operand.
     * @since 1.1.0
     */
    static Operand far_ptr( const FarPointer &pointer ) {
        return Operand( pointer );
    }

    /**
     * Factory method which builds an address operand.
     * @param address An address instance.
     * @return The address operand.
     * @since 1.1.0
     */
    static Operand addr( const Address &address ) {
        return Operand( address );
    }

    /**
     * Factory method which builds an address operand.
     * @param offset An offset instance.
     * @param sizeOperator An optional size operator.
     * @return The address operand.
     * @since 1.1.0
     */
    static Operand off( const Integer &offset, fcml_usize sizeOperator = FCML_DS_UNDEF ) {
        return Operand( Address( offset, sizeOperator ) );
    }

    /**
     * Factory method which builds an offset based address operand with byte size operator.
     * @param offset An offset instance.
     * @return The address operand.
     * @since 1.1.0
     */
    static Operand offb( const Integer &offset ) {
        return Operand( Address( offset, FCML_DS_8 ) );
    }

    /**
     * Factory method which builds an offset based address operand with word size operator.
     * @param offset An offset instance.
     * @return The address operand.
     * @since 1.1.0
     */
    static Operand offw( const Integer &offset ) {
        return Operand( Address( offset, FCML_DS_16 ) );
    }

    /**
     * Factory method which builds an offset based address operand with double word size operator.
     * @param offset An offset instance.
     * @return The address operand.
     * @since 1.1.0
     */
    static Operand offd( const Integer &offset ) {
        return Operand( Address( offset, FCML_DS_32 ) );
    }

    /**
     * Factory method which builds an offset based address operand with quadro word size operator.
     * @param offset An offset instance.
     * @return The address operand.
     * @since 1.1.0
     */
    static Operand offq( const Integer &offset ) {
        return Operand( Address( offset, FCML_DS_64 ) );
    }

    /**
     * Factory method which creates address type operand for given effective address and optional size operator.
     * @param effectiveAddress The effective address.
     * @param sizeOperator The optional size operator.
     * @return The created operator.
     * @since 1.1.0
     */
    static Operand addr( const EffectiveAddress &effectiveAddress, fcml_usize sizeOperator = FCML_DS_UNDEF ) {
        return Operand( Address( effectiveAddress, sizeOperator ) );
    }

    /**
     * Factory method which creates address type operand for given effective address and byte size operator.
     * @param effectiveAddress The effective address.
     * @return The created operator.
     * @since 1.1.0
     */
    static Operand addrb( const EffectiveAddress &effectiveAddress ) {
        return Operand( Address( effectiveAddress, FCML_DS_8 ) );
    }

    /**
     * Factory method which creates address type operand for given effective address and word size operator.
     * @param effectiveAddress The effective address.
     * @return The created operator.
     * @since 1.1.0
     */
    static Operand addrw( const EffectiveAddress &effectiveAddress ) {
        return Operand( Address( effectiveAddress, FCML_DS_16 ) );
    }

    /**
     * Factory method which creates address type operand for given effective address and double word size operator.
     * @param effectiveAddress The effective address.
     * @return The created operator.
     * @since 1.1.0
     */
    static Operand addrd( const EffectiveAddress &effectiveAddress ) {
        return Operand( Address( effectiveAddress, FCML_DS_32 ) );
    }

    /**
     * Factory method which creates address type operand for given effective address and quadro word size operator.
     * @param effectiveAddress The effective address.
     * @return The created operator.
     * @since 1.1.0
     */
    static Operand addrq( const EffectiveAddress &effectiveAddress ) {
        return Operand( Address( effectiveAddress, FCML_DS_64 ) );
    }

    /**
      * Factory method which creates address type operand for given segment selector, effective address and optional size operator.
      * @param effectiveAddress The effective address.
      * @param segmentSelector The segment selector.
      * @param sizeOperator The optional size operator.
      * @return The created operator.
      * @since 1.1.0
      */
    static Operand addr( const EffectiveAddress &effectiveAddress, const SegmentSelector &segmentSelector, fcml_usize sizeOperator = FCML_DS_UNDEF ) {
        return Operand( Address( effectiveAddress, segmentSelector, sizeOperator ) );
    }

    /**
     * Factory method which creates address type operand for given effective address and byte size operator.
     * @param effectiveAddress The effective address.
     * @param segmentSelector The segment selector.
     * @return The created operator.
     * @since 1.1.0
     */
    static Operand addrb( const EffectiveAddress &effectiveAddress, const SegmentSelector &segmentSelector ) {
        return Operand( Address( effectiveAddress, segmentSelector, FCML_DS_8 ) );
    }

    /**
     * Factory method which creates address type operand for given effective address and word size operator.
     * @param effectiveAddress The effective address.
     * @param segmentSelector The segment selector.
     * @return The created operator.
     * @since 1.1.0
     */
    static Operand addrw( const EffectiveAddress &effectiveAddress, const SegmentSelector &segmentSelector ) {
        return Operand( Address( effectiveAddress, segmentSelector, FCML_DS_16 ) );
    }

    /**
     * Factory method which creates address type operand for given effective address and double word size operator.
     * @param effectiveAddress The effective address.
     * @param segmentSelector The segment selector.
     * @return The created operator.
     * @since 1.1.0
     */
    static Operand addrd( const EffectiveAddress &effectiveAddress, const SegmentSelector &segmentSelector ) {
        return Operand( Address( effectiveAddress, segmentSelector, FCML_DS_32 ) );
    }

    /**
     * Factory method which creates address type operand for given effective address and quadro word size operator.
     * @param effectiveAddress The effective address.
     * @param segmentSelector The segment selector.
     * @return The created operator.
     * @since 1.1.0
     */
    static Operand addrq( const EffectiveAddress &effectiveAddress, const SegmentSelector &segmentSelector ) {
        return Operand( Address( effectiveAddress, segmentSelector, FCML_DS_64 ) );
    }

    /**
     * Factory method which creates an register based operator for given register.
     * @param reg The register.
     * @return The created operator.
     * @since 1.1.0
     */
    static Operand reg( const Register &reg ) {
        return Operand( reg );
    }

    /**
     * Factory method which creates an register based operator for given parameters.
     * @param reg The FCML register number.
     * @param size The register size.
     * @param type The register type.
     * @param x64_exp See manual for more information.
     * @return The created operator.
     * @since 1.1.0
     */
    static Operand reg( fcml_uint8_t reg, fcml_usize size, Register::RegisterType type = Register::REG_GPR, fcml_bool x64_exp = FCML_FALSE ) {
        return Operand( Register( reg, size, type, x64_exp ) );
    }

    /**
     * Factory method which creates an effective address based operator for a displacement and optional size operator.
     * @param displacement The displacement value.
     * @param sizeOperator The size operator.
     * @return The created operator.
     * @since 1.1.0
     */
    static Operand eff( const Integer &displacement, fcml_usize sizeOperator = FCML_DS_UNDEF ) {
        return addr( EffectiveAddress( displacement ), sizeOperator );
    }

    /**
     * Factory method which creates an effective address based operator for a displacement and byte size operator.
     * @param displacement The displacement value.
     * @return The created operator.
     * @since 1.1.0
     */
    static Operand effb( const Integer &displacement ) {
        return addr( EffectiveAddress( displacement ), FCML_DS_8 );
    }

    /**
     * Factory method which creates an effective address based operator for a displacement and word size operator.
     * @param displacement The displacement value.
     * @return The created operator.
     * @since 1.1.0
     */
    static Operand effw( const Integer &displacement ) {
        return addr( EffectiveAddress( displacement ), FCML_DS_16 );
    }

    /**
     * Factory method which creates an effective address based operator for a displacement and double word size operator.
     * @param displacement The displacement value.
     * @return The created operator.
     * @since 1.1.0
     */
    static Operand effd( const Integer &displacement ) {
        return addr( EffectiveAddress( displacement ), FCML_DS_32 );
    }

    /**
     * Factory method which creates an effective address based operator for a displacement and quadro byte size operator.
     * @param displacement The displacement value.
     * @return The created operator.
     * @since 1.1.0
     */
    static Operand effq( const Integer &displacement ) {
        return addr( EffectiveAddress( displacement ), FCML_DS_64 );
    }

    /**
     * Factory method which creates an effective address based operator for a base register and optional size operator.
     * @param base The base register.
     * @param sizeOperator The optional size operator.
     * @return The created operator.
     * @since 1.1.0
     */
    static Operand eff( const Register &base, fcml_usize sizeOperator = FCML_DS_UNDEF ) {
        return addr( EffectiveAddress( base ), sizeOperator );
    }

    /**
     * Factory method which creates an effective address based operator for a base register and byte size operator.
     * @param base The base register.
     * @return The created operator.
     * @since 1.1.0
     */
    static Operand effb( const Register &base ) {
        return addr( EffectiveAddress( base ), FCML_DS_8 );
    }

    /**
     * Factory method which creates an effective address based operator for a base register and word size operator.
     * @param base The base register.
     * @return The created operator.
     * @since 1.1.0
     */
    static Operand effw( const Register &base ) {
        return addr( EffectiveAddress( base ), FCML_DS_16 );
    }

    /**
     * Factory method which creates an effective address based operator for a base register and double word size operator.
     * @param base The base register.
     * @return The created operator.
     * @since 1.1.0
     */
    static Operand effd( const Register &base ) {
        return addr( EffectiveAddress( base ), FCML_DS_32 );
    }

    /**
     * Factory method which creates an effective address based operator for a base register and quadro word size operator.
     * @param base The base register.
     * @return The created operator.
     * @since 1.1.0
     */
    static Operand effq( const Register &base ) {
        return addr( EffectiveAddress( base ), FCML_DS_64 );
    }

    /**
     * Factory method which creates an effective address based operator for a base register, displacement and optional size operator.
     * @param base The base register.
     * @param displacement The displacement value.
     * @param sizeOperator The optional size operator.
     * @return The created operator.
     * @since 1.1.0
     */
    static Operand eff( const Register &base, const Integer &displacement, fcml_usize sizeOperator = FCML_DS_UNDEF ) {
        return addr( EffectiveAddress( base, displacement ), sizeOperator );
    }

    /**
     * Factory method which creates an effective address based operator for a base register, displacement and byte size operator.
     * @param base The base register.
     * @param displacement The displacement value.
     * @return The created operator.
     * @since 1.1.0
     */
    static Operand effb( const Register &base, const Integer &displacement ) {
        return addr( EffectiveAddress( base, displacement ), FCML_DS_8 );
    }

    /**
     * Factory method which creates an effective address based operator for a base register, displacement and word size operator.
     * @param base The base register.
     * @param displacement The displacement value.
     * @return The created operator.
     * @since 1.1.0
     */
    static Operand effw( const Register &base, const Integer &displacement ) {
        return addr( EffectiveAddress( base, displacement ), FCML_DS_16 );
    }

    /**
     * Factory method which creates an effective address based operator for a base register, displacement and double word size operator.
     * @param base The base register.
     * @param displacement The displacement value.
     * @return The created operator.
     * @since 1.1.0
     */
    static Operand effd( const Register &base, const Integer &displacement ) {
        return addr( EffectiveAddress( base, displacement ), FCML_DS_32 );
    }

    /**
     * Factory method which creates an effective address based operator for a base register, displacement and quadro word size operator.
     * @param base The base register.
     * @param displacement The displacement value.
     * @return The created operator.
     * @since 1.1.0
     */
    static Operand effq( const Register &base, const Integer &displacement ) {
        return addr( EffectiveAddress( base, displacement ), FCML_DS_64 );
    }

    /**
     * Factory method which creates an effective address based operator for an index register, scaleFactor, displacement and optional size operator.
     * @param index The index register.
     * @param scaleFactor The scale factor.
     * @param displacement The displacement value.
     * @param sizeOperator The optional size operator.
     * @return The created operator.
     * @since 1.1.0
     */
    static Operand eff( const Register &index, fcml_uint8_t scaleFactor, const Integer &displacement, fcml_usize sizeOperator = FCML_DS_UNDEF ) {
        return addr( EffectiveAddress( index, scaleFactor, displacement ), sizeOperator );
    }

    /**
     * Factory method which creates an effective address based operator for an index register, scaleFactor, displacement and byte size operator.
     * @param index The index register.
     * @param scaleFactor The scale factor.
     * @param displacement The displacement value.
     * @return The created operator.
     * @since 1.1.0
     */
    static Operand effb( const Register &index, fcml_uint8_t scaleFactor, const Integer &displacement ) {
        return addr( EffectiveAddress( index, scaleFactor, displacement ), FCML_DS_8 );
    }

    /**
     * Factory method which creates an effective address based operator for an index register, scaleFactor, displacement and word size operator.
     * @param index The index register.
     * @param scaleFactor The scale factor.
     * @param displacement The displacement value.
     * @return The created operator.
     * @since 1.1.0
     */
    static Operand effw( const Register &index, fcml_uint8_t scaleFactor, const Integer &displacement ) {
        return addr( EffectiveAddress( index, scaleFactor, displacement ), FCML_DS_16 );
    }

    /**
     * Factory method which creates an effective address based operator for an index register, scaleFactor, displacement and double word size operator.
     * @param index The index register.
     * @param scaleFactor The scale factor.
     * @param displacement The displacement value.
     * @return The created operator.
     * @since 1.1.0
     */
    static Operand effd( const Register &index, fcml_uint8_t scaleFactor, const Integer &displacement ) {
        return addr( EffectiveAddress( index, scaleFactor, displacement ), FCML_DS_32 );
    }

    /**
     * Factory method which creates an effective address based operator for an index register, scaleFactor, displacement and quadro word size operator.
     * @param index The index register.
     * @param scaleFactor The scale factor.
     * @param displacement The displacement value.
     * @return The created operator.
     * @since 1.1.0
     */
    static Operand effq( const Register &index, fcml_uint8_t scaleFactor, const Integer &displacement ) {
        return addr( EffectiveAddress( index, scaleFactor, displacement ), FCML_DS_64 );
    }

    /**
     * Factory method which creates an effective address based operator for a base register, index register and optional size operator.
     * @param base The base register.
     * @param index The index register.
     * @param sizeOperator The optional size operator.
     * @return The created operator.
     * @since 1.1.0
     */
    static Operand eff( const Register &base, const Register &index, fcml_usize sizeOperator = FCML_DS_UNDEF ) {
        return addr( EffectiveAddress( base, index ), sizeOperator );
    }

    /**
     * Factory method which creates an effective address based operator for a base register, index register and byte size operator.
     * @param base The base register.
     * @param index The index register.
     * @return The created operator.
     * @since 1.1.0
     */
    static Operand effb( const Register &base, const Register &index ) {
        return addr( EffectiveAddress( base, index ), FCML_DS_8 );
    }

    /**
     * Factory method which creates an effective address based operator for a base register, index register and word size operator.
     * @param base The base register.
     * @param index The index register.
     * @return The created operator.
     * @since 1.1.0
     */
    static Operand effw( const Register &base, const Register &index ) {
        return addr( EffectiveAddress( base, index ), FCML_DS_16 );
    }

    /**
     * Factory method which creates an effective address based operator for a base register, index register and double word size operator.
     * @param base The base register.
     * @param index The index register.
     * @return The created operator.
     * @since 1.1.0
     */
    static Operand effd( const Register &base, const Register &index ) {
        return addr( EffectiveAddress( base, index ), FCML_DS_32 );
    }

    /**
     * Factory method which creates an effective address based operator for a base register, index register and quadro word size operator.
     * @param base The base register.
     * @param index The index register.
     * @return The created operator.
     * @since 1.1.0
     */
    static Operand effq( const Register &base, const Register &index ) {
        return addr( EffectiveAddress( base, index ), FCML_DS_64 );
    }

    /**
     * Factory method which creates an effective address based operator for a base register, index register, scale factor and optional size operator.
     * @param base The base register.
     * @param index The index register.
     * @param scaleFactor The scale factor.
     * @param sizeOperator The optional size operator.
     * @return The created operator.
     * @since 1.1.0
     */
    static Operand eff( const Register &base, const Register &index, fcml_uint8_t scaleFactor, fcml_usize sizeOperator = FCML_DS_UNDEF ) {
        return addr( EffectiveAddress( base, index, scaleFactor ), sizeOperator );
    }

    /**
     * Factory method which creates an effective address based operator for a base register, index register, scale factor and byte size operator.
     * @param base The base register.
     * @param index The index register.
     * @param scaleFactor The scale factor.
     * @return The created operator.
     * @since 1.1.0
     */
    static Operand effb( const Register &base, const Register &index, fcml_uint8_t scaleFactor ) {
        return addr( EffectiveAddress( base, index, scaleFactor ), FCML_DS_8 );
    }

    /**
     * Factory method which creates an effective address based operator for a base register, index register, scale factor and word size operator.
     * @param base The base register.
     * @param index The index register.
     * @param scaleFactor The scale factor.
     * @return The created operator.
     * @since 1.1.0
     */
    static Operand effw( const Register &base, const Register &index, fcml_uint8_t scaleFactor ) {
        return addr( EffectiveAddress( base, index, scaleFactor ), FCML_DS_16 );
    }

    /**
     * Factory method which creates an effective address based operator for a base register, index register, scale factor and double word size operator.
     * @param base The base register.
     * @param index The index register.
     * @param scaleFactor The scale factor.
     * @return The created operator.
     * @since 1.1.0
     */
    static Operand effd( const Register &base, const Register &index, fcml_uint8_t scaleFactor ) {
        return addr( EffectiveAddress( base, index, scaleFactor ), FCML_DS_32 );
    }

    /**
     * Factory method which creates an effective address based operator for a base register, index register, scale factor and quadro word size operator.
     * @param base The base register.
     * @param index The index register.
     * @param scaleFactor The scale factor.
     * @return The created operator.
     * @since 1.1.0
     */
    static Operand effq( const Register &base, const Register &index, fcml_uint8_t scaleFactor ) {
        return addr( EffectiveAddress( base, index, scaleFactor ), FCML_DS_64 );
    }

    /**
     * Factory method which creates an effective address based operator for a base register, index register, scale factor and optional size operator.
     * @param base The base register.
     * @param index The index register.
     * @param scaleFactor The scale factor.
     * @param displacement The displacement value.
     * @param sizeOperator The optional size operator.
     * @return The created operator.
     * @since 1.1.0
     */
    static Operand eff( const Register &base, const Register &index, fcml_uint8_t scaleFactor, const Integer &displacement, fcml_usize sizeOperator = FCML_DS_UNDEF ) {
        return addr( EffectiveAddress( base, index, scaleFactor, displacement ), sizeOperator );
    }

    /**
     * Factory method which creates an effective address based operator for a base register, index register, scale factor and byte size operator.
     * @param base The base register.
     * @param index The index register.
     * @param scaleFactor The scale factor.
     * @param displacement The displacement value.
     * @return The created operator.
     * @since 1.1.0
     */
    static Operand effb( const Register &base, const Register &index, fcml_uint8_t scaleFactor, const Integer &displacement ) {
        return addr( EffectiveAddress( base, index, scaleFactor, displacement ), FCML_DS_8 );
    }

    /**
     * Factory method which creates an effective address based operator for a base register, index register, scale factor and word size operator.
     * @param base The base register.
     * @param index The index register.
     * @param scaleFactor The scale factor.
     * @param displacement The displacement value.
     * @return The created operator.
     * @since 1.1.0
     */
    static Operand effw( const Register &base, const Register &index, fcml_uint8_t scaleFactor, const Integer &displacement ) {
        return addr( EffectiveAddress( base, index, scaleFactor, displacement ), FCML_DS_16 );
    }

    /**
     * Factory method which creates an effective address based operator for a base register, index register, scale factor and double word size operator.
     * @param base The base register.
     * @param index The index register.
     * @param scaleFactor The scale factor.
     * @param displacement The displacement value.
     * @return The created operator.
     * @since 1.1.0
     */
    static Operand effd( const Register &base, const Register &index, fcml_uint8_t scaleFactor, const Integer &displacement ) {
        return addr( EffectiveAddress( base, index, scaleFactor, displacement ), FCML_DS_32 );
    }

    /**
     * Factory method which creates an effective address based operator for a base register, index register, scale factor and quardo word size operator.
     * @param base The base register.
     * @param index The index register.
     * @param scaleFactor The scale factor.
     * @param displacement The displacement value.
     * @return The created operator.
     * @since 1.1.0
     */
    static Operand effq( const Register &base, const Register &index, fcml_uint8_t scaleFactor, const Integer &displacement ) {
        return addr( EffectiveAddress( base, index, scaleFactor, displacement ), FCML_DS_64 );
    }

};

/** Instruction condition.
 *
 * It's counterpart to the fcml_st_condition structure.
 *
 * @since 1.1.0
 */
class Condition {

public:

    /** See fcml_st_condition for more details.
     * @since 1.1.0
     */
    enum ConditionType {
        /** 0 Overflow*/
        CONDITION_O = FCML_CONDITION_O,
        /** 1 Below*/
        CONDITION_B = FCML_CONDITION_B,
        /** 2 Equal*/
        CONDITION_E = FCML_CONDITION_E,
        /** 3 Below or equal*/
        CONDITION_BE = FCML_CONDITION_BE,
        /** 4 Sign*/
        CONDITION_S = FCML_CONDITION_S,
        /** 5 Parity*/
        CONDITION_P = FCML_CONDITION_P,
        /** 6 Less than*/
        CONDITION_L = FCML_CONDITION_L,
        /** 7 Less than or equal to*/
        CONDITION_LE = FCML_CONDITION_LE
    };

    /**
     * Creates an empty condition.
     * @since 1.1.0
     */
    Condition() :
        _conditionType(CONDITION_O),
        _isNegation(false) {
    }

    /**
     * Creates a condition for given parameters.
     *
     * @param type A condition type.
     * @param negation True in order to negate condition.
     * @since 1.1.0
     */
    Condition( ConditionType type, bool negation = false ) :
        _conditionType( type ),
        _isNegation( negation ) {
    }

public:

    /**
     * Gets true the condition is of a given type.
     * @return True the condition is of a given type.
     * @since 1.1.0
     */
    bool isO() const {
        return check( CONDITION_O );
    }

    /**
     * Factory method which creates a condition of a given type.
     * @return The condition with a type described by the method name.
     * @since 1.1.0
     */
    static const Condition O() {
       const Condition condition( CONDITION_O );
       return condition;
    }

    /**
     * Gets true the condition is of a given type.
     * @return True the condition is of a given type.
     * @since 1.1.0
     */
    bool isNO() const {
        return check( CONDITION_O, true );
    }

    /**
     * Factory method which creates a condition of a given type.
     * @return The condition with a type described by the method name.
     * @since 1.1.0
     */
    static const Condition NO() {
       const Condition condition( CONDITION_O );
       return condition;
    }

    /**
     * Gets true the condition is of a given type.
     * @return True the condition is of a given type.
     * @since 1.1.0
     */
    bool isB() const {
        return check( CONDITION_B );
    }

    /**
     * Factory method which creates a condition of a given type.
     * @return The condition with a type described by the method name.
     * @since 1.1.0
     */
    static const Condition B() {
       const Condition condition( CONDITION_B );
       return condition;
    }

    /**
     * Gets true the condition is of a given type.
     * @return True the condition is of a given type.
     * @since 1.1.0
     */
    bool isNB() const {
       return check( CONDITION_B, true );
    }

    /**
     * Factory method which creates a condition of a given type.
     * @return The condition with a type described by the method name.
     * @since 1.1.0
     */
    static const Condition NB() {
       const Condition condition( CONDITION_B, true );
       return condition;
    }

    /**
     * Gets true the condition is of a given type.
     * @return True the condition is of a given type.
     * @since 1.1.0
     */
    bool isNAE() const {
        return check( CONDITION_B );
    }

    /**
     * Factory method which creates a condition of a given type.
     * @return The condition with a type described by the method name.
     * @since 1.1.0
     */
    static const Condition NAE() {
       const Condition condition( CONDITION_B );
       return condition;
    }

    /**
     * Gets true the condition is of a given type.
     * @return True the condition is of a given type.
     * @since 1.1.0
     */
    bool isAE() const {
       return check( CONDITION_B, true );
    }

    /**
     * Factory method which creates a condition of a given type.
     * @return The condition with a type described by the method name.
     * @since 1.1.0
     */
    static const Condition AE() {
       const Condition condition( CONDITION_B, true );
       return condition;
    }

    /**
     * Gets true the condition is of a given type.
     * @return True the condition is of a given type.
     * @since 1.1.0
     */
    bool isC() const {
        return check( CONDITION_B );
    }

    /**
     * Factory method which creates a condition of a given type.
     * @return The condition with a type described by the method name.
     * @since 1.1.0
     */
    static const Condition C() {
       const Condition condition( CONDITION_B );
       return condition;
    }

    /**
     * Gets true the condition is of a given type.
     * @return True the condition is of a given type.
     * @since 1.1.0
     */
    bool isNC() const {
        return check( CONDITION_B, true );
    }

    /**
     * Factory method which creates a condition of a given type.
     * @return The condition with a type described by the method name.
     * @since 1.1.0
     */
    static const Condition NC() {
       const Condition condition( CONDITION_B, true );
       return condition;
    }

    /**
     * Gets true the condition is of a given type.
     * @return True the condition is of a given type.
     * @since 1.1.0
     */
    bool isE() const {
        return check( CONDITION_E );
    }

    /**
     * Factory method which creates a condition of a given type.
     * @return The condition with a type described by the method name.
     * @since 1.1.0
     */
    static const Condition E() {
       const Condition condition( CONDITION_E );
       return condition;
    }

    /**
     * Gets true the condition is of a given type.
     * @return True the condition is of a given type.
     * @since 1.1.0
     */
    bool isZ() const {
        return check( CONDITION_E );
    }

    /**
     * Factory method which creates a condition of a given type.
     * @return The condition with a type described by the method name.
     * @since 1.1.0
     */
    static const Condition Z() {
       const Condition condition( CONDITION_E );
       return condition;
    }

    /**
     * Gets true the condition is of a given type.
     * @return True the condition is of a given type.
     * @since 1.1.0
     */
    bool isNE() const {
        return check( CONDITION_E, true );
    }

    /**
     * Factory method which creates a condition of a given type.
     * @return The condition with a type described by the method name.
     * @since 1.1.0
     */
    static const Condition NE() {
       const Condition condition( CONDITION_E, true );
       return condition;
    }

    /**
     * Gets true the condition is of a given type.
     * @return True the condition is of a given type.
     * @since 1.1.0
     */
    bool isNZ() const {
        return check( CONDITION_E, true );
    }

    /**
     * Factory method which creates a condition of a given type.
     * @return The condition with a type described by the method name.
     * @since 1.1.0
     */
    static const Condition NZ() {
       const Condition condition( CONDITION_E, true );
       return condition;
    }

    /**
     * Gets true the condition is of a given type.
     * @return True the condition is of a given type.
     * @since 1.1.0
     */
    bool isBE() const {
        return check( CONDITION_BE );
    }

    /**
     * Factory method which creates a condition of a given type.
     * @return The condition with a type described by the method name.
     * @since 1.1.0
     */
    static const Condition BE() {
       const Condition condition( CONDITION_BE );
       return condition;
    }

    /**
     * Gets true the condition is of a given type.
     * @return True the condition is of a given type.
     * @since 1.1.0
     */
    bool isNA() const {
        return check( CONDITION_BE );
    }

    /**
     * Factory method which creates a condition of a given type.
     * @return The condition with a type described by the method name.
     * @since 1.1.0
     */
    static const Condition NA() {
       const Condition condition( CONDITION_BE );
       return condition;
    }

    /**
     * Gets true the condition is of a given type.
     * @return True the condition is of a given type.
     * @since 1.1.0
     */
    bool isNBE() const {
        return check( CONDITION_BE, true );
    }

    /**
     * Factory method which creates a condition of a given type.
     * @return The condition with a type described by the method name.
     * @since 1.1.0
     */
    static const Condition NBE() {
       const Condition condition( CONDITION_BE, true );
       return condition;
    }

    /**
     * Gets true the condition is of a given type.
     * @return True the condition is of a given type.
     * @since 1.1.0
     */
    bool isA() const {
        return check( CONDITION_BE, true );
    }

    /**
     * Factory method which creates a condition of a given type.
     * @return The condition with a type described by the method name.
     * @since 1.1.0
     */
    static const Condition A() {
       const Condition condition( CONDITION_BE, true );
       return condition;
    }

    /**
     * Gets true the condition is of a given type.
     * @return True the condition is of a given type.
     * @since 1.1.0
     */
    bool isS() const {
        return check( CONDITION_S );
    }

    /**
     * Factory method which creates a condition of a given type.
     * @return The condition with a type described by the method name.
     * @since 1.1.0
     */
    static const Condition S() {
       const Condition condition( CONDITION_S );
       return condition;
    }

    /**
     * Gets true the condition is of a given type.
     * @return True the condition is of a given type.
     * @since 1.1.0
     */
    bool isNS() const {
        return check( CONDITION_S, true );
    }

    /**
     * Factory method which creates a condition of a given type.
     * @return The condition with a type described by the method name.
     * @since 1.1.0
     */
    static const Condition NS() {
       const Condition condition( CONDITION_S, true );
       return condition;
    }

    /**
     * Gets true the condition is of a given type.
     * @return True the condition is of a given type.
     * @since 1.1.0
     */
    bool isP() const {
        return check( CONDITION_P );
    }

    /**
     * Factory method which creates a condition of a given type.
     * @return The condition with a type described by the method name.
     * @since 1.1.0
     */
    static const Condition P() {
       const Condition condition( CONDITION_P );
       return condition;
    }

    /**
     * Gets true the condition is of a given type.
     * @return True the condition is of a given type.
     * @since 1.1.0
     */
    bool isPE() const {
        return check( CONDITION_P );
    }

    /**
     * Factory method which creates a condition of a given type.
     * @return The condition with a type described by the method name.
     * @since 1.1.0
     */
    static const Condition PE() {
       const Condition condition( CONDITION_P );
       return condition;
    }

    /**
     * Gets true the condition is of a given type.
     * @return True the condition is of a given type.
     * @since 1.1.0
     */
    bool isNP() const {
        return check( CONDITION_P, true );
    }

    /**
     * Factory method which creates a condition of a given type.
     * @return The condition with a type described by the method name.
     * @since 1.1.0
     */
    static const Condition NP() {
       const Condition condition( CONDITION_P, true );
       return condition;
    }

    /**
     * Gets true the condition is of a given type.
     * @return True the condition is of a given type.
     * @since 1.1.0
     */
    bool isPO() const {
        return check( CONDITION_P, true );
    }

    /**
     * Factory method which creates a condition of a given type.
     * @return The condition with a type described by the method name.
     * @since 1.1.0
     */
    static const Condition PO() {
       const Condition condition( CONDITION_P, true );
       return condition;
    }

    /**
     * Gets true the condition is of a given type.
     * @return True the condition is of a given type.
     * @since 1.1.0
     */
    bool isL() const {
        return check( CONDITION_L );
    }

    /**
     * Factory method which creates a condition of a given type.
     * @return The condition with a type described by the method name.
     * @since 1.1.0
     */
    static const Condition L() {
       const Condition condition( CONDITION_L );
       return condition;
    }

    /**
     * Gets true the condition is of a given type.
     * @return True the condition is of a given type.
     * @since 1.1.0
     */
    bool isNGE() const {
        return check( CONDITION_L );
    }

    /**
     * Factory method which creates a condition of a given type.
     * @return The condition with a type described by the method name.
     * @since 1.1.0
     */
    static const Condition NGE() {
       const Condition condition( CONDITION_L );
       return condition;
    }

    /**
     * Gets true the condition is of a given type.
     * @return True the condition is of a given type.
     * @since 1.1.0
     */
    bool isNL() const {
        return check( CONDITION_L, true );
    }

    /**
     * Factory method which creates a condition of a given type.
     * @return The condition with a type described by the method name.
     * @since 1.1.0
     */
    static const Condition NL() {
       const Condition condition( CONDITION_L, true );
       return condition;
    }

    /**
     * Gets true the condition is of a given type.
     * @return True the condition is of a given type.
     * @since 1.1.0
     */
    bool isGE() const {
        return check( CONDITION_L, true );
    }

    /**
     * Factory method which creates a condition of a given type.
     * @return The condition with a type described by the method name.
     * @since 1.1.0
     */
    static const Condition GE() {
       const Condition condition( CONDITION_L, true );
       return condition;
    }

    /**
     * Gets true the condition is of a given type.
     * @return True the condition is of a given type.
     * @since 1.1.0
     */
    bool isLE() const {
        return check( CONDITION_LE );
    }

    /**
     * Factory method which creates a condition of a given type.
     * @return The condition with a type described by the method name.
     * @since 1.1.0
     */
    static const Condition LE() {
       const Condition condition( CONDITION_LE );
       return condition;
    }

    /**
     * Gets true the condition is of a given type.
     * @return True the condition is of a given type.
     * @since 1.1.0
     */
    bool isNG() const {
        return check( CONDITION_LE );
    }

    /**
     * Factory method which creates a condition of a given type.
     * @return The condition with a type described by the method name.
     * @since 1.1.0
     */
    static const Condition NG() {
       const Condition condition( CONDITION_LE );
       return condition;
    }

    /**
     * Gets true the condition is of a given type.
     * @return True the condition is of a given type.
     * @since 1.1.0
     */
    bool isNLE() const {
        return check( CONDITION_LE, true );
    }

    /**
     * Factory method which creates a condition of a given type.
     * @return The condition with a type described by the method name.
     * @since 1.1.0
     */
    static const Condition NLE() {
       const Condition condition( CONDITION_LE, true );
       return condition;
    }

    /**
     * Gets true the condition is of a given type.
     * @return True the condition is of a given type.
     * @since 1.1.0
     */
    bool isG() const {
        return check( CONDITION_LE, true );
    }

    /**
     * Factory method which creates a condition of a given type.
     * @return The condition with a type described by the method name.
     * @since 1.1.0
     */
    static const Condition G() {
       const Condition condition( CONDITION_LE, true );
       return condition;
    }

public:

    /**
     * Checks if two condition are equal.
     *
     * @param cond The condition to be compared to the current one.
     * @return True if they are equal.
     * @since 1.1.0
     */
    bool operator==( const Condition &cond ) const {
        return cond._conditionType == _conditionType && cond._isNegation == _isNegation;
    }

    /**
     * Checks if two condition are equal.
     *
     * @param cond The condition to be compared to the current one.
     * @return True if they are NOT equal.
     * @since 1.1.0
     */
    bool operator!=( const Condition &cond ) const {
        return !(*this == cond);
    }

public:

    /**
     * Gets a type of the condition.
     *
     * @return The type of the condition.
     * @since 1.1.0
     */
    ConditionType getConditionType() const {
        return _conditionType;
    }

    /**
     * Sets condition type.
     *
     * @param conditionType The condition type to be set.
     * @since 1.1.0
     */
    Condition& setConditionType( ConditionType conditionType ) {
        _conditionType = conditionType;
        return *this;
    }

    /**
     * Returns true if condition is negated.
     *
     * @return True if condition is negated.
     * @since 1.1.0
     */
    bool isNegation() const {
        return _isNegation;
    }

    /**
     * Sets negation flag for the condition.
     *
     * @param isNegation The negation flag.
     * @since 1.1.0
     */
    Condition& setNegation( bool isNegation ) {
        _isNegation = isNegation;
        return *this;
    }

private:

    /**
     * Checks if the condition is of given type and negation flag.
     *
     * @param type The condition type.
     * @param negation The negation flag.
     * @return True if the condition has the same type and negation set.
     * @since 1.1.0
     */
    bool check( ConditionType type, bool negation = false ) const {
        return _conditionType == type && _isNegation == negation;
    }

private:

    /* Condition type.*/
    ConditionType _conditionType;
    /* True if condition should be negated.*/
    bool _isNegation;

};

/** Describes an instruction.
 *
 * It's counterpart to the fcml_st_instruction structure.
 * @since 1.1.0
 */
class Instruction {
public:

    /**
     * Creates an empty instruction.
     * @since 1.1.0
     */
    Instruction() :
        _prefixes(0),
        _hints(FCML_HINT_NO_HINTS),
        _isConditional(false),
        _operandsCount(0) {
    }

    /**
     * Creates an empty instruction for given mnemonic.
     *
     * @param mnemonic The mnemonic for the newly created instruction.
     * @since 1.1.0
     */
    Instruction( const fcml_cstring &mnemonic ) :
        _prefixes(0),
        _hints(FCML_HINT_NO_HINTS),
        _mnemonic(mnemonic),
        _isConditional(false),
        _operandsCount(0) {
    }

public:

    /**
     * Adds a new operand to the instruction.
     *
     * @param operand The operand to be added to the instruction.
     * @throw IllegalStateException No more operands allowed.
     * @since 1.1.0
     */
    void add( const Operand &operand ) {
        if( _operandsCount == FCML_OPERANDS_COUNT ) {
            throw IllegalStateException( FCML_TEXT( "No more operands allowed." ) );
        }
        _operands[_operandsCount++] = operand;
    }

    /**
     * Sets a new oeprand for the instruction at given index.
     *
     * @param operand The operand to be set.
     * @param index The index operand should be set at.
     * @throw IllegalStateException Operand's number exceeds maximal number of operands allowed.
     * @since 1.1.0
     */
    void setOperand( const Operand &operand, fcml_int index ) {
        if( index >= FCML_OPERANDS_COUNT ) {
            throw IllegalStateException( FCML_TEXT( "Operand's number exceeds maximal number of operands allowed." ) );
        }
        _operands[index] = operand;
    }

    /**
     * Gets reference to the constant operand at given index.
     *
     * @param index The operand index.
     * @return The operand available at given index.
     * @since 1.1.0
     */
    const Operand & operator[]( fcml_int index ) const {
        checkArrayAccess(index);
        return _operands[index];
    }

    /**
     * Gets reference to the operand at given index.
     *
     * @param index The operand index.
     * @return The operand available at given index.
     * @since 1.1.0
     */
    Operand & operator[]( fcml_int index ) {
        checkArrayAccess(index);
        return _operands[index];
    }

    /**
     * Cleans the instruction by removing all operands from it.
     * @since 1.1.0
     */
    void clean() {
        for( int i = 0; i < FCML_OPERANDS_COUNT; i++ ) {
            // Clean the operand.
            _operands[i] = Operand();
        }
        _operandsCount = 0;
    }

public:

    /**
     * Gets a pointer to the constant condition associated with the instruction.
     *
     * @return A reference to the condition.
     * @since 1.1.0
     */
    const Condition& getCondition() const {
        return _condition;
    }

    /**
     * Gets a pointer to the condition associated with the instruction.
     *
     * @return A reference to the condition.
     * @since 1.1.0
     */
    Condition& getCondition() {
        return _condition;
    }

    /**
     * Sets a new condition for the instruction.
     *
     * @param condition The condition to be set for the instruction.
     * @return The instruction itself.
     * @since 1.1.0
     */
    Instruction& setCondition( const Condition &condition ) {
        _condition = condition;
        return *this;
    }

    /**
     * Gets instruction level hits associated with the instruction.
     *
     * @return The instruction level hits associated with the instruction.
     * @since 1.1.0
     */
    fcml_hints getHints() const {
        return _hints;
    }

    /**
     * Sets new instruction hints.
     *
     * @param hints The hints to be set.
     * @return The instruction itself.
     * @since 1.1.0
     */
    Instruction& setHints( fcml_hints hints ) {
        _hints = hints;
        return *this;
    }

    /**
     * Gets true if it's a conditional instruction.
     *
     * @return True in case of the conditional instruction.
     * @since 1.1.0
     */
    bool isConditional() const {
        return _isConditional;
    }

    /**
     * Sets conditional flag for the instruction.
     *
     * @param isConditional Set to true in order to mark instruction as conditional one.
     * @return The instruction itself.
     * @since 1.1.0
     */
    Instruction& setConditional( bool isConditional ) {
        _isConditional = isConditional;
        return *this;
    }

    /**
     * Gets the mnemonic associated with the instruction.
     *
     * @return The mnemonic associated with the instruction.
     * @since 1.1.0
     */
    const fcml_cstring& getMnemonic() const {
        return _mnemonic;
    }

    /**
     * Sets a new mnemonic for the instruction.
     *
     * @param mnemonic The new mnemonic.
     * @return The instruction itself.
     * @since 1.1.0
     */
    Instruction& setMnemonic( const fcml_cstring &mnemonic ) {
        _mnemonic = mnemonic;
        return *this;
    }

    /**
     * Gets number of operands associated with the instruction.
     *
     * @return The number of operands in the instruction.
     * @since 1.1.0
     */
    fcml_int getOperandsCount() const {
        return _operandsCount;
    }

    /**
     * Sets number of operands available in the instruction.
     *
     * @param operandsCount Number of operands.
     * @return The number of instructions.
     * @since 1.1.0
     */
    Instruction& setOperandsCount( fcml_int operandsCount ) {
        _operandsCount = operandsCount;
        return *this;
    }

    /**
     * Gets prefixes associated with the instruction.
     *
     * @return The prefixes.
     * @since 1.1.0
     */
    fcml_prefixes getPrefixes() const {
        return _prefixes;
    }

    /**
     * Sets a new set of prefixes for the instruction.
     *
     * @param prefixes The set of prefixes to be set for the instruction.
     * @return  The instruction itself.
     * @since 1.1.0
     */
    Instruction& setPrefixes( fcml_prefixes prefixes ) {
        _prefixes = prefixes;
        return *this;
    }

public:

    // Helper methods to identify prefixes and hints.

    /**
     * Returns true if lock prefix is set.
     * @return True if lock prefix is set.
     * @since 1.1.0
     */
    bool isLock() const {
		return ( _prefixes & FCML_PREFIX_LOCK ) ? true : false;
    }

    /**
     * Returns true if repne prefix is set.
     * @return True if repne prefix is set.
     * @since 1.1.0
     */
    bool isRepne() const {
		return ( _prefixes & FCML_PREFIX_REPNE ) ? true : false;
    }

    /**
     * Returns true if lock repnz is set.
     * @return True if lock repnz is set.
     * @since 1.1.0
     */
    bool isRepnz() const {
		return ( _prefixes & FCML_PREFIX_REPNZ ) ? true : false;
    }

    /**
     * Returns true if rep prefix is set.
     * @return True if rep prefix is set.
     * @since 1.1.0
     */
    bool isRep() const {
		return ( _prefixes & FCML_PREFIX_REP ) ? true : false;
    }

    /**
     * Returns true if repe prefix is set.
     * @return True if repe prefix is set.
     * @since 1.1.0
     */
    bool isRepe() const {
		return ( _prefixes & FCML_PREFIX_REPE ) ? true : false;
    }

    /**
     * Returns true if repz prefix is set.
     * @return True if repz prefix is set.
     * @since 1.1.0
     */
    bool isRepz() const {
		return ( _prefixes & FCML_PREFIX_REPZ ) ? true : false;
    }

    /**
     * Returns true if xacquire prefix is set.
     * @return True if xacquire prefix is set.
     * @since 1.1.0
     */
    bool isXAcquire() const {
		return ( _prefixes & FCML_PREFIX_XACQUIRE ) ? true : false;
    }

    /**
     * Returns true if xrelease prefix is set.
     * @return True if xrelease prefix is set.
     * @since 1.1.0
     */
    bool isXRelease() const {
		return ( _prefixes & FCML_PREFIX_XRELEASE ) ? true : false;
    }

    /**
     * Returns true if branch_hint prefix is set.
     * @return True if branch_hint prefix is set.
     * @since 1.1.0
     */
    bool isBranchHint() const {
		return ( _prefixes & FCML_PREFIX_BRANCH_HINT ) ? true : false;
    }

    /**
     * Returns true if no_branch_hint prefix is set.
     * @return True if no_branch_hint prefix is set.
     * @since 1.1.0
     */
    bool isNoBranchHint() const {
		return ( _prefixes & FCML_PREFIX_NOBRANCH_HINT ) ? true : false;
    }

    /**
     * Returns true if far pointer hint is set.
     * @return True if far pointer hint is set.
     * @since 1.1.0
     */
    bool isFarPointer() const {
		return ( _hints & FCML_HINT_FAR_POINTER ) ? true : false;
    }

    /**
     * Returns true if near pointer hint is set.
     * @return True if near pointer hint is set.
     * @since 1.1.0
     */
    bool isNearPointer() const {
		return ( _hints & FCML_HINT_NEAR_POINTER ) ? true : false;
    }

    /**
     * Returns true if long form pointer hint is set. See manual for more information about this hint.
     * @return True if long form pointer hint is set.
     * @since 1.1.0
     */
    bool isLongFormPointer() const {
		return ( _hints & FCML_HINT_LONG_FORM_POINTER ) ? true : false;
    }

    /**
     * Returns true if indirect pointer hint is set.
     * @return True if indirect pointer hint is set.
     * @since 1.1.0
     */
    bool isIndirectPointer() const {
		return ( _hints & FCML_HINT_INDIRECT_POINTER ) ? true : false;
    }

    /**
     * Returns true if direct pointer hint is set.
     * @return True if direct pointer hint is set.
     * @since 1.1.0
     */
    bool isDirectPointer() const {
		return ( _hints & FCML_HINT_DIRECT_POINTER ) ? true : false;
    }

private:

    /**
     * Throws if given operand index is wrong.
     * @throw BadArgumentException Index exceeds the allowed number of operands.
     * @remarks An internal API, not intended to be used outside.
     */
    void checkArrayAccess( fcml_int index) const {
        if( index < 0 || index >= FCML_OPERANDS_COUNT ) {
            throw BadArgumentException( FCML_TEXT( "Index exceeds the allowed number of operands." ) );
        }
    }

private:

    /** Describes explicit instruction prefixes. @ref PREFIX_GROUP "List of explicit prefixes." */
    fcml_prefixes _prefixes;
    /** Holds instruction level hints. */
    fcml_hints _hints;
    /** Dialect-dependent instruction mnemonic. @see fcml_en_instruction_hints */
    fcml_cstring _mnemonic;
    /** True for conditional instructions. */
    bool _isConditional;
    /** Describes condition used by assembled/disassembled conditional instruction. */
    Condition _condition;
    /** Fixed size array of instruction operands. */
    Operand _operands[FCML_OPERANDS_COUNT];
    /** Number of operands defined for instruction. */
    fcml_int _operandsCount;

};

/** An instruction builder.
 *
 * A classic builder that can be used to prepare instruction in a
 * more convenient way than doing it manually using setters.
 *
 * @since 1.1.0
 */
class IB {

public:

    /** Creates builder for the given mnemonic.
     *
     * @param mnemonic Mnemonic for the instruction being created.
     * @since 1.1.0
     */
    IB( const fcml_cstring &mnemonic ) :
        _hints(FCML_HINT_NO_HINTS),
        _prefixes(0),
        _mnemonic(mnemonic),
        _operandsCount(0) {
    }

    /**
     * Creates builder for the given mnemonic and prefixes.
     *
     * @param prefixes The prefixes for the new instruction.
     * @param mnemonic Mnemonic for the instruction being created.
     * @since 1.1.0
     */
    IB( fcml_prefixes prefixes, const fcml_cstring &mnemonic ) :
        _hints(FCML_HINT_NO_HINTS),
        _prefixes(prefixes),
        _mnemonic(mnemonic),
        _operandsCount(0) {
    }

    /**
     * Creates an instruction builder for given mnemonic and hints.
     *
     * @param mnemonic The instruction mnemonic.
     * @param hints The instruction hints.
     * @since 1.1.0
     */
    IB( const fcml_cstring &mnemonic, fcml_hints hints) :
        _hints(hints),
        _prefixes(0),
        _mnemonic(mnemonic),
        _operandsCount(0) {
    }

    /**
     * Creates an instruction builder for given prefixes, mnemonic and hints.
     *
     * @param prefixes The instruction prefixes.
     * @param mnemonic The instruction mnemonic.
     * @param hints The instruction hints.
     * @since 1.1.0
     */
    IB( fcml_prefixes prefixes, const fcml_cstring &mnemonic, fcml_hints hints ) :
        _hints(hints),
        _prefixes(prefixes),
        _mnemonic(mnemonic),
        _operandsCount(0) {
    }

    /**
     * Converts builder to the instruction instance.
     * @since 1.1.0
     * @return The built instruction.
     */
    operator Instruction() const {
        return build();
    }

    /**
     * Builds an instruction instance for the current state of the builder.
     *
     * @return The built instruction instance.
     * @since 1.1.0
     */
    Instruction build() const {
        Instruction instruction(_mnemonic);
        instruction.setHints(_hints);
        instruction.setPrefixes(_prefixes);
        instruction.setOperandsCount(_operandsCount);
        for( int i = 0; i < FCML_OPERANDS_COUNT; i++ ) {
            instruction.setOperand( _operands[i], i );
        }
        return instruction;
    }

    /**
     * Sets a next operand for the instruction.
     *
     * @param operand The next operand to be added to the instruction.
     * @throw IllegalStateException No more operands allowed.
     * @since 1.1.0
     */
    void op( const Operand &operand ) {
        if( _operandsCount == FCML_OPERANDS_COUNT ) {
            throw IllegalStateException( FCML_TEXT( "No more operands allowed." ) );
        }
        _operands[_operandsCount++] = operand;
    }

    /**
     * Factory method that can be used to create instruction builder.
     *
     * @param mnemonic The mnemonic for the instruction builder.
     * @return Instruction builder instance.
     * @since 1.1.0
     */
    static IB inst( const fcml_cstring &mnemonic ) {
        return IB(mnemonic);
    }

    // Hints.

    /**
     * Creates a hint instance described by the name of the method. Such a hint can be then used
     * together with shift operator overridden by the builder in order to set an appropriate hint
     * for the instruction being built.
     * @return The hint indicator for the builder.
     * @since 1.1.0
     */
    static const InstructionHint FAR_PTR() {
        return InstructionHint::FAR_POINTER();
    }

    /**
     * Sets a hint described by the name of the method for the instruction being built.
     * @return The instruction builder with the appropriate hint set.
     * @since 1.1.0
     */
    IB& farPtr() {
        _hints |= FCML_HINT_FAR_POINTER;
        return *this;
    }

    /**
     * Creates a hint instance described by the name of the method. Such a hint can be then used
     * together with shift operator overridden by the builder in order to set an appropriate hint
     * for the instruction being built.
     * @return The hint indicator for the builder.
     * @since 1.1.0
     */
    static const InstructionHint NEAR_PTR() {
        return InstructionHint::NEAR_POINTER();
    }

    /**
     * Sets a hint described by the name of the method for the instruction being built.
     * @return The instruction builder with the appropriate hint set.
     * @since 1.1.0
     */
    IB& nearPtr() {
        _hints |= FCML_HINT_NEAR_POINTER;
        return *this;
    }

    /**
     * Creates a hint instance described by the name of the method. Such a hint can be then used
     * together with shift operator overridden by the builder in order to set an appropriate hint
     * for the instruction being built.
     * @return The hint indicator for the builder.
     * @since 1.1.0
     */
    static const InstructionHint LONG_FORM_PTR() {
        return InstructionHint::LONG_FORM_POINTER();
    }

    /**
     * Sets a hint described by the name of the method for the instruction being built.
     * @return The instruction builder with the appropriate hint set.
     * @since 1.1.0
     */
    IB& longFormPtr() {
        _hints |= FCML_HINT_LONG_FORM_POINTER;
        return *this;
    }

    /**
     * Creates a hint instance described by the name of the method. Such a hint can be then used
     * together with shift operator overridden by the builder in order to set an appropriate hint
     * for the instruction being built.
     * @return The hint indicator for the builder.
     * @since 1.1.0
     */
    static const InstructionHint INDIRECT_PTR() {
        return InstructionHint::INDIRECT_POINTER();
    }

    /**
     * Sets a hint described by the name of the method for the instruction being built.
     * @return The instruction builder with the appropriate hint set.
     * @since 1.1.0
     */
    IB& indirectPtr() {
        _hints |= FCML_HINT_INDIRECT_POINTER;
        return *this;
    }

    /**
     * Creates a hint instance described by the name of the method. Such a hint can be then used
     * together with shift operator overridden by the builder in order to set an appropriate hint
     * for the instruction being built.
     * @return The hint indicator for the builder.
     * @since 1.1.0
     */
    static const InstructionHint DIRECT_PTR() {
        return InstructionHint::DIRECT_POINTER();
    }

    /**
     * Sets a hint described by the name of the method for the instruction being built.
     * @return The instruction builder with the appropriate hint set.
     * @since 1.1.0
     */
    IB& directPtr() {
        _hints |= FCML_HINT_DIRECT_POINTER;
        return *this;
    }

    // Prefixes.

    /**
     * Creates a prefix instance described by the name of the method. Such a prefix can be then used
     * together with the shift operator overridden by the builder in order to set an appropriate prefix
     * for the instruction being built.
     * @return The prefix indicator for the builder.
     * @since 1.1.0
     */
    static const InstructionPrefix LOCK() {
        return InstructionPrefix::LOCK();
    }

    /**
     * Sets a prefix described by the name of the method for the instruction being built.
     * @return The instruction builder with the appropriate prefix set.
     * @since 1.1.0
     */
    IB& lock() {
        _prefixes |= FCML_PREFIX_LOCK;
        return *this;
    }

    /**
     * Creates a prefix instance described by the name of the method. Such a prefix can be then used
     * together with the shift operator overridden by the builder in order to set an appropriate prefix
     * for the instruction being built.
     * @return The prefix indicator for the builder.
     * @since 1.1.0
     */
    static const InstructionPrefix REPNE() {
        return InstructionPrefix::REPNE();
    }

    /**
     * Sets a prefix described by the name of the method for the instruction being built.
     * @return The instruction builder with the appropriate prefix set.
     * @since 1.1.0
     */
    IB& repne() {
        _prefixes |= FCML_PREFIX_REPNE;
        return *this;
    }

    /**
     * Creates a prefix instance described by the name of the method. Such a prefix can be then used
     * together with the shift operator overridden by the builder in order to set an appropriate prefix
     * for the instruction being built.
     * @return The prefix indicator for the builder.
     * @since 1.1.0
     */
    static const InstructionPrefix REPNZ() {
        return InstructionPrefix::REPNZ();
    }

    /**
     * Sets a prefix described by the name of the method for the instruction being built.
     * @return The instruction builder with the appropriate prefix set.
     * @since 1.1.0
     */
    IB& repnz() {
        _prefixes |= FCML_PREFIX_REPNZ;
        return *this;
    }

    /**
     * Creates a prefix instance described by the name of the method. Such a prefix can be then used
     * together with the shift operator overridden by the builder in order to set an appropriate prefix
     * for the instruction being built.
     * @return The prefix indicator for the builder.
     * @since 1.1.0
     */
    static const InstructionPrefix REP() {
        return InstructionPrefix::REP();
    }

    /**
     * Sets a prefix described by the name of the method for the instruction being built.
     * @return The instruction builder with the appropriate prefix set.
     * @since 1.1.0
     */
    IB& rep() {
        _prefixes |= FCML_PREFIX_REP;
        return *this;
    }

    /**
     * Creates a prefix instance described by the name of the method. Such a prefix can be then used
     * together with the shift operator overridden by the builder in order to set an appropriate prefix
     * for the instruction being built.
     * @return The prefix indicator for the builder.
     * @since 1.1.0
     */
    static const InstructionPrefix REPE() {
        return InstructionPrefix::REPE();
    }

    /**
     * Sets a prefix described by the name of the method for the instruction being built.
     * @return The instruction builder with the appropriate prefix set.
     * @since 1.1.0
     */
    IB& repe() {
        _prefixes |= FCML_PREFIX_REPE;
        return *this;
    }

    /**
     * Creates a prefix instance described by the name of the method. Such a prefix can be then used
     * together with the shift operator overridden by the builder in order to set an appropriate prefix
     * for the instruction being built.
     * @return The prefix indicator for the builder.
     * @since 1.1.0
     */
    static const InstructionPrefix REPZ() {
        return InstructionPrefix::REPZ();
    }

    /**
     * Sets a prefix described by the name of the method for the instruction being built.
     * @return The instruction builder with the appropriate prefix set.
     * @since 1.1.0
     */
    IB& repz() {
        _prefixes |= FCML_PREFIX_REPZ;
        return *this;
    }

    /**
     * Creates a prefix instance described by the name of the method. Such a prefix can be then used
     * together with the shift operator overridden by the builder in order to set an appropriate prefix
     * for the instruction being built.
     * @return The prefix indicator for the builder.
     * @since 1.1.0
     */
    static const InstructionPrefix XACQUIRE() {
        return InstructionPrefix::XACQUIRE();
    }

    /**
     * Sets a prefix described by the name of the method for the instruction being built.
     * @return The instruction builder with the appropriate prefix set.
     * @since 1.1.0
     */
    IB& xacquire() {
        _prefixes |= FCML_PREFIX_XACQUIRE;
        return *this;
    }

    /**
     * Creates a prefix instance described by the name of the method. Such a prefix can be then used
     * together with the shift operator overridden by the builder in order to set an appropriate prefix
     * for the instruction being built.
     * @return The prefix indicator for the builder.
     * @since 1.1.0
     */
    static const InstructionPrefix XRELEASE() {
        return InstructionPrefix::XRELEASE();
    }

    /**
     * Sets a prefix described by the name of the method for the instruction being built.
     * @return The instruction builder with the appropriate prefix set.
     * @since 1.1.0
     */
    IB& xrelease() {
        _prefixes |= FCML_PREFIX_XRELEASE;
        return *this;
    }

    /**
     * Creates a prefix instance described by the name of the method. Such a prefix can be then used
     * together with the shift operator overridden by the builder in order to set an appropriate prefix
     * for the instruction being built.
     * @return The prefix indicator for the builder.
     * @since 1.1.0
     */
    static const InstructionPrefix BRANCH() {
        return InstructionPrefix::BRANCH_HINT();
    }

    /**
     * Sets a prefix described by the name of the method for the instruction being built.
     * @return The instruction builder with the appropriate prefix set.
     * @since 1.1.0
     */
    IB& branchHint() {
        _prefixes |= FCML_PREFIX_BRANCH_HINT;
        return *this;
    }

    /**
     * Creates a prefix instance described by the name of the method. Such a prefix can be then used
     * together with the shift operator overridden by the builder in order to set an appropriate prefix
     * for the instruction being built.
     * @return The prefix indicator for the builder.
     * @since 1.1.0
     */
    static const InstructionPrefix NO_BRANCH() {
        return InstructionPrefix::NOBRANCH_HINT();
    }

    /**
     * Sets a prefix described by the name of the method for the instruction being built.
     * @return The instruction builder with the appropriate prefix set.
     * @since 1.1.0
     */
    IB& nobranchHint() {
        _prefixes |= FCML_PREFIX_NOBRANCH_HINT;
        return *this;
    }

    /**
     * Gets multimedia hint for the operand.
     * @return The multimedia hint.
     */
    static const OperandHint OP_MULTIMEDIA_HINT() {
        return OperandHint::MULTIMEDIA();
    }

    /**
     * Gets relative address hint for the operand.
     * @return The multimedia hint.
     */
    static const OperandHint OP_RELATIVE_ADDRESSING() {
        return OperandHint::RELATIVE_ADDRESSING();
    }

    /**
     * Gets absolute hint for the operand.
     * @return The multimedia hint.
     */
    static const OperandHint OP_ABSOLUTE_ADDRESSING() {
        return OperandHint::ABSOLUTE_ADDRESSING();
    }

    /**
     * Gets SIB encoding hint for the operand.
     * @return The SIB encoding hint.
     */
    static const OperandHint OP_SIB_ENCODING() {
        return OperandHint::SIB_ENCODING();
    }

    /**
     * Marks the lastly added operand as a multimedia one.
     * @return The instruction builder itself.
     */
    IB& operandMultimediaHint() {
        set( OP_MULTIMEDIA_HINT() );
        return *this;
    }

    /**
     * Marks the lastly added address operand as a relative one.
     * @return The instruction builder itself.
     */
    IB& operandRelativeHint() {
        set( OP_MULTIMEDIA_HINT() );
        return *this;
    }

    /**
     * Marks the lastly added address operand as a absolute one.
     * @return The instruction builder itself.
     */
    IB& operandAbsoluteHint() {
        set( OP_MULTIMEDIA_HINT() );
        return *this;
    }

    /**
     * Sets preferred encoding to SIB for the lastly added ModR/M operand.
     * @return The instruction builder itself.
     */
    IB& operandSIBEncodingHint() {
        set( OP_MULTIMEDIA_HINT() );
        return *this;
    }

    // Operands.

    /**
     * Adds an immediate operand.
     * @return The immediate operand.
     * @since 1.1.0
     */
    IB& imm( const Integer &imm ) {
        sanityCheck();
        _operands[_operandsCount++].imm(imm);
        return *this;
    }

    /**
     * Adds a far pointer operand.
     * @param seg A segment selector.
     * @param addr An 16-bit offset value.
     * @return The far pointer operand.
     * @since 1.1.0
     */
    IB& far_ptr( fcml_uint16_t seg, fcml_int16_t addr ) {
        sanityCheck();
        _operands[_operandsCount++].far_ptr(seg, addr);
        return *this;
    }

    /**
     * Adds a far pointer operand.
     * @param seg A segment selector.
     * @param addr An 32-bit offset value.
     * @return The far pointer operand.
     * @since 1.1.0
     */
    IB& far_ptr( fcml_uint16_t seg, fcml_int32_t addr ) {
        sanityCheck();
        _operands[_operandsCount++].far_ptr(seg, addr);
        return *this;
    }

    /**
     * Adds a far pointer operand.
     * @param pointer A far pointer instance.
     * @return The far pointer operand.
     * @since 1.1.0
     */
    IB& far_ptr( const FarPointer &pointer ) {
        sanityCheck();
        _operands[_operandsCount++].far_ptr( pointer );
        return *this;
    }

    /**
     * Adds an address operand.
     * @param address An address instance.
     * @return The address operand.
     * @since 1.1.0
     */
    IB& addr( const Address &address ) {
        sanityCheck();
        _operands[_operandsCount++].addr(address);
        return *this;
    }

    /**
     * Adds an offset operand.
     * @param offset An offset instance.
     * @param sizeOperator An optional size operator.
     * @return The address operand.
     * @since 1.1.0
     */
    IB& off( const Integer &offset, fcml_usize sizeOperator = FCML_DS_UNDEF ) {
        sanityCheck();
        _operands[_operandsCount++].off( offset, sizeOperator );
        return *this;
    }

    /**
     * Adds an offset based address operand with byte size operator.
     * @param offset An offset instance.
     * @return The address operand.
     * @since 1.1.0
     */
    IB& offb( const Integer &offset ) {
        sanityCheck();
        _operands[_operandsCount++].off( offset, FCML_DS_8 );
        return *this;
    }

    /**
     * Adds an offset based address operand with word size operator.
     * @param offset An offset instance.
     * @return The address operand.
     * @since 1.1.0
     */
    IB& offw( const Integer &offset ) {
        sanityCheck();
        _operands[_operandsCount++].off( offset, FCML_DS_16 );
        return *this;
    }

    /**
     * Adds an offset based address operand with double word size operator.
     * @param offset An offset instance.
     * @return The address operand.
     * @since 1.1.0
     */
    IB& offd( const Integer &offset ) {
        sanityCheck();
        _operands[_operandsCount++].off( offset, FCML_DS_32 );
        return *this;
    }

    /**
     * Adds an offset based address operand with quadro word size operator.
     * @param offset An offset instance.
     * @return The address operand.
     * @since 1.1.0
     */
    IB& offq( const Integer &offset ) {
        sanityCheck();
        _operands[_operandsCount++].off( offset, FCML_DS_64 );
        return *this;
    }

    /**
     * Adds an address type operand for given effective address and optional size operator.
     * @param effectiveAddress The effective address.
     * @param sizeOperator The optional size operator.
     * @return The created operator.
     * @since 1.1.0
     */
    IB& addr( const EffectiveAddress &effectiveAddress, fcml_usize sizeOperator = FCML_DS_UNDEF ) {
        sanityCheck();
        _operands[_operandsCount++].addr( effectiveAddress, sizeOperator );
        return *this;
    }

    /**
     * Adds an address type operand for given effective address and byte size operator.
     * @param effectiveAddress The effective address.
     * @return The created operator.
     * @since 1.1.0
     */
    IB& addrb( const EffectiveAddress &effectiveAddress ) {
        sanityCheck();
        _operands[_operandsCount++].addr( effectiveAddress, FCML_DS_8 );
        return *this;
    }

    /**
     * Adds an address type operand for given effective address and word size operator.
     * @param effectiveAddress The effective address.
     * @return The created operator.
     * @since 1.1.0
     */
    IB& addrw( const EffectiveAddress &effectiveAddress ) {
        sanityCheck();
        _operands[_operandsCount++].addr( effectiveAddress, FCML_DS_16 );
        return *this;
    }

    /**
     * Adds an address type operand for given effective address and double word size operator.
     * @param effectiveAddress The effective address.
     * @return The created operator.
     * @since 1.1.0
     */
    IB& addrd( const EffectiveAddress &effectiveAddress ) {
        sanityCheck();
        _operands[_operandsCount++].addr( effectiveAddress, FCML_DS_32 );
        return *this;
    }

    /**
     * Adds an address type operand for given effective address and quadro word size operator.
     * @param effectiveAddress The effective address.
     * @return The created operator.
     * @since 1.1.0
     */
    IB& addrq( const EffectiveAddress &effectiveAddress ) {
        sanityCheck();
        _operands[_operandsCount++].addr( effectiveAddress, FCML_DS_64 );
        return *this;
    }

    /**
     * Adds an address type operand for given segment selector, effective address and optional size operator.
     * @param effectiveAddress The effective address.
     * @param segmentSelector The segment selector.
     * @param sizeOperator The optional size operator.
     * @return The created operator.
     * @since 1.1.0
     */
    IB& addr( const EffectiveAddress &effectiveAddress, const SegmentSelector &segmentSelector, fcml_usize sizeOperator = FCML_DS_UNDEF ) {
        sanityCheck();
        _operands[_operandsCount++].addr( effectiveAddress, segmentSelector, sizeOperator );
        return *this;
    }

    /**
     * Adds an address type operand for given effective address and byte size operator.
     * @param effectiveAddress The effective address.
     * @param segmentSelector The segment selector.
     * @return The created operator.
     * @since 1.1.0
     */
    IB& addrb( const EffectiveAddress &effectiveAddress, const SegmentSelector &segmentSelector ) {
        sanityCheck();
        _operands[_operandsCount++].addr( effectiveAddress, segmentSelector, FCML_DS_8 );
        return *this;
    }

    /**
     * Adds an address type operand for given effective address and byte size operator.
     * @param effectiveAddress The effective address.
     * @param segmentSelector The segment selector.
     * @return The created operator.
     * @since 1.1.0
     */
    IB& addrw( const EffectiveAddress &effectiveAddress, const SegmentSelector &segmentSelector ) {
        sanityCheck();
        _operands[_operandsCount++].addr( effectiveAddress, segmentSelector, FCML_DS_8 );
        return *this;
    }

    /**
     * Adds an address type operand for given effective address and double word size operator.
     * @param effectiveAddress The effective address.
     * @param segmentSelector The segment selector.
     * @return The created operator.
     * @since 1.1.0
     */
    IB& addrd( const EffectiveAddress &effectiveAddress, const SegmentSelector &segmentSelector ) {
        sanityCheck();
        _operands[_operandsCount++].addr( effectiveAddress, segmentSelector, FCML_DS_8 );
        return *this;
    }

    /**
     * Adds an address type operand for given effective address and quadro word size operator.
     * @param effectiveAddress The effective address.
     * @param segmentSelector The segment selector.
     * @return The created operator.
     * @since 1.1.0
     */
    IB& addrq( const EffectiveAddress &effectiveAddress, const SegmentSelector &segmentSelector ) {
        sanityCheck();
        _operands[_operandsCount++].addr( effectiveAddress, segmentSelector, FCML_DS_8 );
        return *this;
    }

    /**
     * Adds an an register based operator for given register.
     * @param reg The register.
     * @return The created operator.
     * @since 1.1.0
     */
    IB& reg( const Register &reg ) {
        sanityCheck();
        _operands[_operandsCount++].reg( reg );
        return *this;
    }

    /**
     * Adds an an register based operator for given parameters.
     * @param reg The FCML register number.
     * @param size The register size.
     * @param type The register type.
     * @param x64_exp See manual for more information.
     * @return The created operator.
     * @since 1.1.0
     */
    IB& reg( fcml_uint8_t reg, fcml_usize size, Register::RegisterType type = Register::REG_GPR, fcml_bool x64_exp = FCML_FALSE ) {
        sanityCheck();
        _operands[_operandsCount++].reg( Register( reg, size, type, x64_exp ) );
        return *this;
    }

    /**
     * Adds an an effective address based operator for a displacement and optional size operator.
     * @param displacement The displacement value.
     * @param sizeOperator The size operator.
     * @return The created operator.
     * @since 1.1.0
     */
    IB& eff( const Integer &displacement, fcml_usize sizeOperator = FCML_DS_UNDEF ) {
        next().addr( EffectiveAddress(displacement), sizeOperator );
        return *this;
    }

    /**
     * Adds an an effective address based operator for a displacement and byte size operator.
     * @param displacement The displacement value.
     * @return The created operator.
     * @since 1.1.0
     */
    IB& effb( const Integer &displacement ) {
        next().addr( EffectiveAddress(displacement), FCML_DS_8 );
        return *this;
    }

    /**
     * Adds an an effective address based operator for a displacement and word size operator.
     * @param displacement The displacement value.
     * @return The created operator.
     * @since 1.1.0
     */
    IB& effw( const Integer &displacement ) {
        next().addr( EffectiveAddress(displacement), FCML_DS_16 );
        return *this;
    }

    /**
     * Adds an an effective address based operator for a displacement and double word size operator.
     * @param displacement The displacement value.
     * @return The created operator.
     * @since 1.1.0
     */
    IB& effd( const Integer &displacement ) {
        next().addr( EffectiveAddress(displacement), FCML_DS_32 );
        return *this;
    }

    /**
     * Adds an an effective address based operator for a displacement and quadro byte size operator.
     * @param displacement The displacement value.
     * @return The created operator.
     * @since 1.1.0
     */
    IB& effq( const Integer &displacement ) {
        next().addr( EffectiveAddress(displacement), FCML_DS_64 );
        return *this;
    }

    /**
     * Adds an an effective address based operator for a base register and optional size operator.
     * @param base The base register.
     * @param sizeOperator The optional size operator.
     * @return The created operator.
     * @since 1.1.0
     */
    IB& eff( const Register &base, fcml_usize sizeOperator = FCML_DS_UNDEF ) {
        next().addr( EffectiveAddress(base), sizeOperator );
        return *this;
    }

    /**
     * Adds an an effective address based operator for a base register and byte size operator.
     * @param base The base register.
     * @return The created operator.
     * @since 1.1.0
     */
    IB& effb( const Register &base ) {
        next().addr( EffectiveAddress(base), FCML_DS_8 );
        return *this;
    }

    /**
     * Adds an an effective address based operator for a base register and word size operator.
     * @param base The base register.
     * @return The created operator.
     * @since 1.1.0
     */
    IB& effw( const Register &base ) {
        next().addr( EffectiveAddress(base), FCML_DS_16 );
        return *this;
    }

    /**
     * Adds an an effective address based operator for a base register and double word size operator.
     * @param base The base register.
     * @return The created operator.
     * @since 1.1.0
     */
    IB& effd( const Register &base ) {
        next().addr( EffectiveAddress(base), FCML_DS_32 );
        return *this;
    }

    /**
     * Adds an an effective address based operator for a base register and quadro word size operator.
     * @param base The base register.
     * @return The created operator.
     * @since 1.1.0
     */
    IB& effq( const Register &base ) {
        next().addr( EffectiveAddress(base), FCML_DS_64 );
        return *this;
    }

    /**
     * Adds an an effective address based operator for a base register, displacement and optional size operator.
     * @param base The base register.
     * @param displacement The displacement value.
     * @param sizeOperator The optional size operator.
     * @return The created operator.
     * @since 1.1.0
     */
    IB& eff( const Register &base, const Integer &displacement, fcml_usize sizeOperator = FCML_DS_UNDEF ) {
        next().addr( EffectiveAddress( base, displacement ), sizeOperator );
        return *this;
    }

    /**
     * Adds an an effective address based operator for a base register, displacement and byte size operator.
     * @param base The base register.
     * @param displacement The displacement value.
     * @return The created operator.
     * @since 1.1.0
     */
    IB& effb( const Register &base, const Integer &displacement ) {
        next().addr( EffectiveAddress( base, displacement ), FCML_DS_8 );
        return *this;
    }

    /**
     * Adds an an effective address based operator for a base register, displacement and word size operator.
     * @param base The base register.
     * @param displacement The displacement value.
     * @return The created operator.
     * @since 1.1.0
     */
    IB& effw( const Register &base, const Integer &displacement ) {
        next().addr( EffectiveAddress( base, displacement ), FCML_DS_16 );
        return *this;
    }

    /**
     * Adds an an effective address based operator for a base register, displacement and double word size operator.
     * @param base The base register.
     * @param displacement The displacement value.
     * @return The created operator.
     * @since 1.1.0
     */
    IB& effd( const Register &base, const Integer &displacement ) {
        next().addr( EffectiveAddress( base, displacement ), FCML_DS_32 );
        return *this;
    }

    /**
     * Adds an an effective address based operator for a base register, displacement and quadro word size operator.
     * @param base The base register.
     * @param displacement The displacement value.
     * @return The created operator.
     * @since 1.1.0
     */
    IB& effq( const Register &base, const Integer &displacement ) {
        next().addr( EffectiveAddress( base, displacement ), FCML_DS_64 );
        return *this;
    }

    /**
     * Adds an an effective address based operator for an index register, scaleFactor, displacement and optional size operator.
     * @param index The index register.
     * @param scaleFactor The scale factor.
     * @param displacement The displacement value.
     * @param sizeOperator The optional size operator.
     * @return The created operator.
     * @since 1.1.0
     */
    IB& eff( const Register &index, fcml_uint8_t scaleFactor, const Integer &displacement, fcml_usize sizeOperator = FCML_DS_UNDEF ) {
           next().addr( EffectiveAddress( index, scaleFactor, displacement ), sizeOperator );
           return *this;
       }

    /**
     * Adds an an effective address based operator for an index register, scaleFactor, displacement and byte size operator.
     * @param index The index register.
     * @param scaleFactor The scale factor.
     * @param displacement The displacement value.
     * @return The created operator.
     * @since 1.1.0
     */
    IB& effb( const Register &index, fcml_uint8_t scaleFactor, const Integer &displacement ) {
           next().addr( EffectiveAddress( index, scaleFactor, displacement ), FCML_DS_8 );
           return *this;
       }

    /**
     * Adds an an effective address based operator for an index register, scaleFactor, displacement and word size operator.
     * @param index The index register.
     * @param scaleFactor The scale factor.
     * @param displacement The displacement value.
     * @return The created operator.
     * @since 1.1.0
     */
    IB& effw( const Register &index, fcml_uint8_t scaleFactor, const Integer &displacement ) {
        next().addr( EffectiveAddress( index, scaleFactor, displacement ), FCML_DS_16 );
        return *this;
    }

    /**
     * Adds an an effective address based operator for an index register, scaleFactor, displacement and double word size operator.
     * @param index The index register.
     * @param scaleFactor The scale factor.
     * @param displacement The displacement value.
     * @return The created operator.
     * @since 1.1.0
     */
    IB& effd( const Register &index, fcml_uint8_t scaleFactor, const Integer &displacement ) {
        next().addr( EffectiveAddress( index, scaleFactor, displacement ), FCML_DS_32 );
        return *this;
    }

    /**
     * Adds an an effective address based operator for an index register, scaleFactor, displacement and quadro word size operator.
     * @param index The index register.
     * @param scaleFactor The scale factor.
     * @param displacement The displacement value.
     * @return The created operator.
     * @since 1.1.0
     */
    IB& effq( const Register &index, fcml_uint8_t scaleFactor, const Integer &displacement ) {
        next().addr( EffectiveAddress( index, scaleFactor, displacement ), FCML_DS_64 );
        return *this;
    }

    /**
     * Adds an an effective address based operator for a base register, index register and optional size operator.
     * @param base The base register.
     * @param index The index register.
     * @param sizeOperator The optional size operator.
     * @return The created operator.
     * @since 1.1.0
     */
    IB& eff( const Register &base, const Register &index, fcml_usize sizeOperator = FCML_DS_UNDEF ) {
        next().addr( EffectiveAddress( base, index ), sizeOperator );
        return *this;
    }

    /**
     * Adds an an effective address based operator for a base register, index register and byte size operator.
     * @param base The base register.
     * @param index The index register.
     * @return The created operator.
     * @since 1.1.0
     */
    IB& effb( const Register &base, const Register &index ) {
        next().addr( EffectiveAddress( base, index ), FCML_DS_8 );
        return *this;
    }

    /**
     * Adds an an effective address based operator for a base register, index register and word size operator.
     * @param base The base register.
     * @param index The index register.
     * @return The created operator.
     * @since 1.1.0
     */
    IB& effw( const Register &base, const Register &index ) {
        next().addr( EffectiveAddress( base, index ), FCML_DS_16 );
        return *this;
    }

    /**
     * Adds an an effective address based operator for a base register, index register and double word size operator.
     * @param base The base register.
     * @param index The index register.
     * @return The created operator.
     * @since 1.1.0
     */
    IB& effd( const Register &base, const Register &index ) {
        next().addr( EffectiveAddress( base, index ), FCML_DS_32 );
        return *this;
    }

    /**
     * Adds an an effective address based operator for a base register, index register and quadro word size operator.
     * @param base The base register.
     * @param index The index register.
     * @return The created operator.
     * @since 1.1.0
     */
    IB& effq( const Register &base, const Register &index ) {
        next().addr( EffectiveAddress( base, index ), FCML_DS_64 );
        return *this;
    }

    /**
     * Adds an an effective address based operator for a base register, index register, scale factor and optional size operator.
     * @param base The base register.
     * @param index The index register.
     * @param scaleFactor The scale factor.
     * @param sizeOperator The optional size operator.
     * @return The created operator.
     * @since 1.1.0
     */
    IB& eff( const Register &base, const Register &index, fcml_uint8_t scaleFactor, fcml_usize sizeOperator = FCML_DS_UNDEF ) {
        next().addr( EffectiveAddress( base, index, scaleFactor ), sizeOperator );
        return *this;
    }

    /**
     * Adds an an effective address based operator for a base register, index register, scale factor and byte size operator.
     * @param base The base register.
     * @param index The index register.
     * @param scaleFactor The scale factor.
     * @return The created operator.
     * @since 1.1.0
     */
    IB& effb( const Register &base, const Register &index, fcml_uint8_t scaleFactor ) {
        next().addr( EffectiveAddress( base, index, scaleFactor ), FCML_DS_8 );
        return *this;
    }

    /**
     * Adds an an effective address based operator for a base register, index register, scale factor and word size operator.
     * @param base The base register.
     * @param index The index register.
     * @param scaleFactor The scale factor.
     * @return The created operator.
     * @since 1.1.0
     */
    IB& effw( const Register &base, const Register &index, fcml_uint8_t scaleFactor ) {
        next().addr( EffectiveAddress( base, index, scaleFactor ), FCML_DS_16 );
        return *this;
    }

    /**
     * Adds an an effective address based operator for a base register, index register, scale factor and double word size operator.
     * @param base The base register.
     * @param index The index register.
     * @param scaleFactor The scale factor.
     * @return The created operator.
     * @since 1.1.0
     */
    IB& effd( const Register &base, const Register &index, fcml_uint8_t scaleFactor ) {
        next().addr( EffectiveAddress( base, index, scaleFactor ), FCML_DS_32 );
        return *this;
    }

    /**
     * Adds an an effective address based operator for a base register, index register, scale factor and quadro word size operator.
     * @param base The base register.
     * @param index The index register.
     * @param scaleFactor The scale factor.
     * @return The created operator.
     * @since 1.1.0
     */
    IB& effq( const Register &base, const Register &index, fcml_uint8_t scaleFactor ) {
        next().addr( EffectiveAddress( base, index, scaleFactor ), FCML_DS_64 );
        return *this;
    }

    /**
     * Adds an an effective address based operator for a base register, index register, scale factor and optional size operator.
     * @param base The base register.
     * @param index The index register.
     * @param scaleFactor The scale factor.
     * @param displacement The displacement value.
     * @param sizeOperator The optional size operator.
     * @return The created operator.
     * @since 1.1.0
     */
    IB& eff( const Register &base, const Register &index, fcml_uint8_t scaleFactor, const Integer &displacement, fcml_usize sizeOperator = FCML_DS_UNDEF ) {
        next().addr( EffectiveAddress( base, index, scaleFactor, displacement ), sizeOperator );
        return *this;
    }

    /**
     * Adds an an effective address based operator for a base register, index register, scale factor and byte size operator.
     * @param base The base register.
     * @param index The index register.
     * @param scaleFactor The scale factor.
     * @param displacement The displacement value.
     * @return The created operator.
     * @since 1.1.0
     */
    IB& effb( const Register &base, const Register &index, fcml_uint8_t scaleFactor, const Integer &displacement ) {
        next().addr( EffectiveAddress( base, index, scaleFactor, displacement ), FCML_DS_8 );
        return *this;
    }

    /**
     * Adds an an effective address based operator for a base register, index register, scale factor and word size operator.
     * @param base The base register.
     * @param index The index register.
     * @param scaleFactor The scale factor.
     * @param displacement The displacement value.
     * @return The created operator.
     * @since 1.1.0
     */
    IB& effw( const Register &base, const Register &index, fcml_uint8_t scaleFactor, const Integer &displacement ) {
        next().addr( EffectiveAddress( base, index, scaleFactor, displacement ), FCML_DS_16 );
        return *this;
    }

    /**
     * Adds an an effective address based operator for a base register, index register, scale factor and double word size operator.
     * @param base The base register.
     * @param index The index register.
     * @param scaleFactor The scale factor.
     * @param displacement The displacement value.
     * @return The created operator.
     * @since 1.1.0
     */
    IB& effd( const Register &base, const Register &index, fcml_uint8_t scaleFactor, const Integer &displacement ) {
        next().addr( EffectiveAddress( base, index, scaleFactor, displacement ), FCML_DS_32 );
        return *this;
    }

    /**
     * Adds an an effective address based operator for a base register, index register, scale factor and quardo word size operator.
     * @param base The base register.
     * @param index The index register.
     * @param scaleFactor The scale factor.
     * @param displacement The displacement value.
     * @return The created operator.
     * @since 1.1.0
     */
    IB& effq( const Register &base, const Register &index, fcml_uint8_t scaleFactor, const Integer &displacement ) {
        next().addr( EffectiveAddress( base, index, scaleFactor, displacement ), FCML_DS_64 );
        return *this;
    }

    /**
     * Adds an operand to the instruction being built.
     * @param operand The operand to be added.
     * @return The instruction builder with the new operand added to it.
     * @since 1.1.0
     */
    IB& operator <<(const Operand &operand) {
        next() = operand;
        return *this;
    }

    /**
     * Adds a prefix to the instruction being built.
     * @param prefix The prefix to be added.
     * @return The instruction builder with the new prefix set for it.
     * @since 1.1.0
     */
    IB& operator <<(const InstructionPrefix &prefix) {
        return set(prefix);
    }

    /**
     * Adds an instruction level hint to the instruction being built.
     * @param hint The hint to be added.
     * @return The instruction builder with the new hint added to it.
     * @since 1.1.0
     */
    IB& operator <<(const InstructionHint &hint) {
        return set( hint );
    }

    /**
     * Adds an operand level hint to the instruction being built.
     * @param hint The hint to be added.
     * @return The instruction builder with the new hint added to it.
     * @since 1.1.0
     */
    IB& operator <<(const OperandHint &hint) {
       return set( hint );
    }

    /**
     * Adds a prefix to the instruction being built.
     * @param prefix The prefix to be added.
     * @return The instruction builder with the new prefix set for it.
     * @since 1.1.0
     */
    IB& set( const InstructionPrefix &prefix ) {
        _prefixes |= prefix._prefix;
        return *this;
    }

    /**
     * Adds an instruction level hint to the instruction being built.
     * @param hint The hint to be added.
     * @return The instruction builder with the new hint added to it.
     * @since 1.1.0
     */
    IB& set( const InstructionHint &hint ) {
        _hints |= hint._hint;
        return *this;
    }

    /**
     * Adds an operand level hint to the instruction being built.
     * @param hint The hint to be added.
     * @return The instruction builder with the new hint added to it.
     * @since 1.1.0
     */
    IB& set( const OperandHint &hint ) {
        if( _operandsCount == 0 ) {
            throw IllegalStateException( FCML_TEXT( "There are no operands yet for the current instruction.." ) );
        }
        _operands[_operandsCount-1].setHints( _operands[_operandsCount-1].getHints() | hint._hint );
        return *this;
    }

private:

    /**
     * Gets the next instruction operand.
     * @return A reference to the next instruction operand.
     * @since 1.1.0
     */
    Operand& next() {
        sanityCheck();
        return _operands[_operandsCount++];
    }

    /**
     * Throws exception if there is no more space for new operands in the builder.
     * @throw IllegalStateException Operand's number exceeds maximal number of operands allowed.
     * @since 1.1.0
     */
    void sanityCheck() const {
        if( _operandsCount == FCML_OPERANDS_COUNT ) {
            throw IllegalStateException( FCML_TEXT( "Operand's number exceeds maximal number of operands allowed." ) );
        }
    }

private:

    /** Instruction hints. */
    fcml_hints _hints;
    /** Instruction prefixes.*/
    fcml_prefixes _prefixes;
    /** Instruction mnemonic. */
    fcml_cstring _mnemonic;
    /** Number of operands available in the builder. */
    fcml_int _operandsCount;
    /** Operands for the built instruction. */
    Operand _operands[FCML_OPERANDS_COUNT];

};

/** Two way conversion for common types.
 * @since 1.1.0
 * @remarks Internal API, not intended to be used outside.
 */
class TypeConverter {
public:

    static void convert( const fcml_st_entry_point &src, EntryPoint &dest ) {
        dest.setIP( src.ip );
        dest.setOpMode( static_cast<EntryPoint::OperatingMode>( src.op_mode ) );
        dest.setAddressSizeAttribute( src.address_size_attribute );
        dest.setOperandSizeAttribute( src.operand_size_attribute );
    }

    static void convert( const EntryPoint &src, fcml_st_entry_point &dest ) {
        dest.ip = src.getIP();
        dest.op_mode = static_cast<fcml_en_operating_mode>( src.getOpMode() );
        dest.address_size_attribute = src.getAddressSizeAttribute();
        dest.operand_size_attribute = src.getOperandSizeAttribute();
    }

    static void convert( const fcml_st_integer &src, Integer &dest ) {
        dest.setInt8( src.int8 );
        dest.setInt16( src.int16 );
        dest.setInt32( src.int32 );
        dest.setInt64( src.int64 );
        dest.setSigned( src.is_signed );
        dest.setSize( src.size );
    }

    static void convert( const Integer &src, fcml_st_integer &dest ) {
        dest.int8 = src.getInt8();
        dest.int16 = src.getInt16();
        dest.int32 = src.getInt32();
        dest.int64 = src.getInt64();
        dest.is_signed = src.isSigned();
        dest.size = src.getSize();
    }

    static void convert( const fcml_st_offset &src, Integer &dest ) {
        dest.setInt16( src.off16 );
        dest.setInt32( src.off32 );
        dest.setInt64( src.off64 );
        dest.setSigned( src.is_signed );
        dest.setSize( src.size );
    }

    static void convert( const Integer &src, fcml_st_offset &dest ) {
        dest.off16 = src.getSize() == FCML_DS_8 ? src.getInt8() : src.getInt16();
        dest.off32 = src.getInt32();
        dest.off64 = src.getInt64();
        dest.is_signed = src.isSigned();
        dest.size = src.getSize();
    }

    static void convert( const fcml_st_register &src, Register &dest ) {
        dest.setReg( src.reg );
        dest.setSize( src.size );
        dest.setType( static_cast<Register::RegisterType>( src.type ) );
		dest.setX64Exp( src.x64_exp ? true : false );
    }

    static void convert( const Register &src, fcml_st_register &dest ) {
        dest.reg = src.getReg();
        dest.size = src.getSize();
        dest.type = static_cast<fcml_en_register>( src.getType() );
        dest.x64_exp = src.getX64Exp();
    }

    static void convert( const fcml_st_far_pointer &src, FarPointer &dest ) {
        dest.setOffset16( src.offset16 );
        dest.setOffset32( src.offset32 );
        dest.setOffsetSize( src.offset_size );
        dest.setSegment( src.segment );
    }

    static void convert( const FarPointer &src, fcml_st_far_pointer &dest ) {
        dest.offset16 = src.getOffset16();
        dest.offset32 = src.getOffset32();
        dest.offset_size = src.getOffsetSize();
        dest.segment = src.getSegment();
    }

    static void convert( const fcml_st_segment_selector &src, SegmentSelector &dest ) {
		dest.setDefaultReg( src.is_default_reg ? true : false );
        convert( src.segment_selector, dest.getSegmentSelector() );
    }

    static void convert( const SegmentSelector &src, fcml_st_segment_selector &dest ) {
        dest.is_default_reg = src.isDefaultReg();
        convert( src.getSegmentSelector(), dest.segment_selector );
    }

    static void convert( const fcml_st_effective_address &src, EffectiveAddress &dest ) {
        convert( src.base, dest.getBase() );
        convert( src.index, dest.getIndex() );
        convert( src.displacement, dest.getDisplacement() );
        dest.setScaleFactor(src.scale_factor);
    }

    static void convert( const EffectiveAddress &src, fcml_st_effective_address &dest ) {
        convert( src.getBase(), dest.base );
        convert( src.getIndex(), dest.index );
        convert( src.getDisplacement(), dest.displacement );
        dest.scale_factor = src.getScaleFactor();
    }

    static void convert( const fcml_st_address &src, Address &dest ) {
        dest.setAddressForm( static_cast<Address::AddressForm>( src.address_form ) );
        dest.setSizeOperator( src.size_operator );
        convert( src.segment_selector, dest.getSegmentSelector() );
        convert( src.effective_address, dest.getEffectiveAddress() );
        convert( src.offset, dest.getOffset() );
    }

    static void convert( const Address &src, fcml_st_address &dest ) {
        dest.address_form = static_cast<fcml_en_effective_address_form>( src.getAddressForm() );
        dest.size_operator = src.getSizeOperator();
        convert( src.getSegmentSelector(), dest.segment_selector );
        convert( src.getEffectiveAddress(), dest.effective_address );
        convert( src.getOffset(), dest.offset );
    }

    static void convert(const fcml_st_operand &src, Operand &dest) {
        dest.setHints(src.hints);
        dest.setOperandType(static_cast<Operand::OperandType>(src.type));
        convert(src.reg, dest.getRegister());
        convert(src.address, dest.getAddress());
        convert(src.far_pointer, dest.getFarPointer());
        convert(src.immediate, dest.getImmediate());
        convert(src.decorators, dest.getDecorators());
    }

    static void convert(const Operand &src, fcml_st_operand &dest) {
        dest.hints = src.getHints();
        dest.type = static_cast<fcml_en_operand_type>(src.getOperandType());
        convert(src.getAddress(), dest.address);
        convert(src.getFarPointer(), dest.far_pointer);
        convert(src.getImmediate(), dest.immediate);
        convert(src.getRegister(), dest.reg);
        convert(src.getDecorators(), dest.decorators);
    }

    static void convert(const fcml_st_operand_decorators &src,
            Decorators &dest) {
        Nullable<fcml_uint8_t> bcast;
        bcast.setNotNull(FCML_TO_CPP_BOOL(src.bcast.is_not_null));
        bcast.setValue(src.bcast.value);
        dest.setBcast(bcast);
        Nullable<fcml_uint8_t> er;
        er.setNotNull(FCML_TO_CPP_BOOL(src.er.is_not_null));
        er.setValue(src.er.value);
        dest.setEr(er);
        dest.setZ(src.z);
        dest.setSae(src.sae);
        convert(src.operand_mask_reg, dest.getOpmaskReg());
    }

    static void convert(const Decorators &src,
            fcml_st_operand_decorators &dest) {
        dest.bcast.is_not_null = src.getBcast().isNotNull();
        dest.bcast.value = src.getBcast().getValue();
        dest.er.is_not_null = src.getEr().isNotNull();
        dest.er.value = src.getEr().getValue();
        dest.z = src.isZ();
        dest.sae = src.isSae();
        convert(src.getOpmaskReg(), dest.operand_mask_reg);
    }

    static void convert( const fcml_st_condition &src, Condition &dest ) {
        dest.setConditionType( static_cast<Condition::ConditionType>( src.condition_type ) );
		dest.setNegation( src.is_negation ? true : false );
    }

    static void convert( const Condition &src, fcml_st_condition &dest ) {
        dest.condition_type = static_cast<fcml_en_condition_type>( src.getConditionType() );
        dest.is_negation = src.isNegation();
    }

    static void convert( const fcml_st_instruction &src, Instruction &dest ) {
        dest.setMnemonic( src.mnemonic );
        convert( src.condition, dest.getCondition() );
        dest.setHints( src.hints );
        dest.setPrefixes( src.prefixes );
		dest.setConditional( src.is_conditional ? true : false );
        for( int i = 0; i < FCML_OPERANDS_COUNT; i++ ) {
            convert( src.operands[i], dest[i] );
        }
        dest.setOperandsCount(src.operands_count);
    }

    static void convert( const Instruction &src, fcml_st_instruction &dest ) {
        // Bear in mind that you are responsible for freeing mnemonic duplicated here.
        dest.mnemonic = Env::strDup( src.getMnemonic().c_str() );
        convert( src.getCondition(), dest.condition );
        dest.hints = src.getHints();
        dest.prefixes = src.getPrefixes();
        dest.is_conditional = src.isConditional();
        for( int i = 0; i < FCML_OPERANDS_COUNT; i++ ) {
            convert( src[i], dest.operands[i] );
        }
        dest.operands_count = src.getOperandsCount();
    }

    static void free( fcml_st_instruction &instruction ) {
        if( instruction.mnemonic ) {
            Env::strFree( instruction.mnemonic );
            instruction.mnemonic = NULL;
        }
    }
};

}

#endif //FCML_COMMON_HPP_
