/*
 * FCML - Free Code Manipulation Library.
 * Copyright (C) 2010-2019 Slawomir Wojtasiak
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

/** @file fcml_disassembler.hpp
 * C++ wrapper for the FCML disassembler.
 *
 * @copyright Copyright (C) 2010-2017 Slawomir Wojtasiak. All rights reserved.
 * This project is released under the GNU Lesser General Public License.
 */

#ifndef FCML_DISASSEMBLER_HPP_
#define FCML_DISASSEMBLER_HPP_

#include <string.h>

#include "fcml_disassembler.h"

#include "fcml_common.hpp"
#include "fcml_errors.hpp"
#include "fcml_dialect.hpp"

namespace fcml {

/**
 *  Component can not be initialized correctly.
 *  @since 1.1.0
 */
class DisassemblingFailedException: public ErrorContainerAwareException {
public:
    DisassemblingFailedException( const fcml_cstring &msg, const ErrorContainer &errorContainer, fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR ) :
        ErrorContainerAwareException( msg, errorContainer, error ){
    }
};

/** Disassembler configuration.
 *
 * It's counterpart to the fcml_st_disassembler_conf structure.
 * @since 1.1.0
 */
class DisassemblerConf {
public:

    /**
     * Default constructor.
     * @since 1.1.0
     */
    DisassemblerConf() :
        _throwExceptionOnError(true),
        _incrementIP(true),
        _enableErrorMessages(true),
        _carryFlagConditionalSuffix(false),
        _conditionalGroup(false),
        _shortForms(false),
        _extendDispToASA(false),
        _failIfUnknownInstruction(false) {
    }

    /** @since 1.1.0 */
    bool isCarryFlagConditionalSuffix() const {
        return _carryFlagConditionalSuffix;
    }

    /** @since 1.1.0 */
    void setCarryFlagConditionalSuffix(bool carryFlagConditionalSuffix) {
        _carryFlagConditionalSuffix = carryFlagConditionalSuffix;
    }

    /** @since 1.1.0 */
    fcml_uint8_t getConditionalGroup() const {
        return _conditionalGroup;
    }

    /** @since 1.1.0 */
    void setConditionalGroup(fcml_uint8_t conditionalGroup) {
        _conditionalGroup = conditionalGroup;
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
    bool isExtendDispToAsa() const {
        return _extendDispToASA;
    }

    /** @since 1.1.0 */
    void setExtendDispToAsa(bool extendDispToAsa) {
        _extendDispToASA = extendDispToAsa;
    }

    /** @since 1.1.0 */
    bool isFailIfUnknownInstruction() const {
        return _failIfUnknownInstruction;
    }

    /** @since 1.1.0 */
    void setFailIfUnknownInstruction(bool failIfUnknownInstruction) {
        _failIfUnknownInstruction = failIfUnknownInstruction;
    }

    /** @since 1.1.0 */
    bool isIncrementIp() const {
        return _incrementIP;
    }

    /** @since 1.1.0 */
    void setIncrementIp(bool incrementIp) {
        _incrementIP = incrementIp;
    }

    /** @since 1.1.0 */
    bool isShortForms() const {
        return _shortForms;
    }

    /** @since 1.1.0 */
    void setShortForms(bool shortForms) {
        _shortForms = shortForms;
    }

    /**
     * Returns true if exception should be thrown when disassembling fails.
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
    bool _incrementIP;
    bool _enableErrorMessages;
    bool _carryFlagConditionalSuffix;
    fcml_uint8_t _conditionalGroup;
    bool _shortForms;
    bool _extendDispToASA;
    bool _failIfUnknownInstruction;

};

/** Disassembler context.
 * @since 1.1.0
 */
class DisassemblerContext {
public:

    /**
     * Creates empty disassembler context.
     * @since 1.1.0
     */
    DisassemblerContext() :
        _code(NULL),
        _codeLength(0) {
    }

    /**
     * Creates disassembler context for given piece of machine code.
     *
     * @param code A buffer with the machine code.
     * @param codeLength Size of the buffer in bytes.
     * @since 1.1.0
     */
    DisassemblerContext( fcml_ptr code, fcml_usize codeLength ) :
        _code(code),
        _codeLength(codeLength) {
    }

public:

    /**
     * Gets pointer to the machine code buffer.
     *
     * @return A pointer to the machine code.
     * @since 1.1.0
     */
    fcml_ptr getCode() const {
        return _code;
    }

    /**
     * Sets a new buffer with machine code for the context.
     *
     * @param code The new code buffer.
     * @since 1.1.0
     */
    void setCode(fcml_ptr code) {
        _code = code;
    }

    /**
     * Gets length of the buffer in bytes.
     *
     * @return Size of the buffer.
     * @since 1.1.0
     */
    fcml_usize getCodeLength() const {
        return _codeLength;
    }

    /**
     * Sets length of the code buffer in bytes.
     *
     * @param codeLength Size of the code.
     * @since 1.1.0
     */
    void setCodeLength(fcml_usize codeLength) {
        _codeLength = codeLength;
    }

    /**
     * Gets a reference to the configuration object associated with the context.
     *
     * @return The disassembler configuration.
     * @since 1.1.0
     */
    const DisassemblerConf& getDisassemblerConf() const {
        return _disassemblerConf;
    }

    /**
     * Gets a reference to the configuration object associated with the context.
     *
     * @return The disassembler configuration.
     * @since 1.1.0
     */
    DisassemblerConf& getDisassemblerConf() {
        return _disassemblerConf;
    }

    /**
     * Sets a new disassembler configuration for the context.
     *
     * @param disassemblerConf The new disassembler configuration.
     * @since 1.1.0
     */
    void setDisassemblerConf(DisassemblerConf disassemblerConf) {
        _disassemblerConf = disassemblerConf;
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
     * @param entryPoint The entry point which is copied to the context.
     * @since 1.1.0
     */
    void setEntryPoint(const EntryPoint& entryPoint) {
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
    /** Disassembler configuration. */
    DisassemblerConf _disassemblerConf;
    /** Entry point. */
    EntryPoint _entryPoint;
    /** Code buffer. */
    fcml_ptr _code;
    /** Code length. */
    fcml_usize _codeLength;
};

/** Instruction prefix.
 * @since 1.1.0
 */
class InstructionPrefixDetails {
public:

    /** Type of the instruction prefix.
     * @since 1.1.0
     */
    enum PrefixType {
        PT_GROUP_UNKNOWN = FCML_PT_GROUP_UNKNOWN,
        PT_GROUP_1 = FCML_PT_GROUP_1,
        PT_GROUP_2 = FCML_PT_GROUP_2,
        PT_GROUP_3 = FCML_PT_GROUP_3,
        PT_GROUP_4 = FCML_PT_GROUP_4,
        PT_REX = FCML_PT_REX,
        PT_VEX = FCML_PT_VEX,
        PT_XOP = FCML_PT_XOP,
        PT_EVEX = FCML_PT_EVEX
    };

    /**
     * Returns true if it's a mandatory prefix.
     *
     * @return True if it's a mandatory prefix.
     * @since 1.1.0
     */
    bool isMandatoryPrefix() const {
        return _mandatoryPrefix;
    }

    /**
     * Sets mandatory prefix flag for the prefix.
     *
     * @param mandatoryPrefix Set to true in order to make the prefix mandatory one.
     * @since 1.1.0
     */
    void setMandatoryPrefix(bool mandatoryPrefix) {
        _mandatoryPrefix = mandatoryPrefix;
    }

    /**
     * Gets the prefix byte.
     *
     * @return The prefix byte.
     * @since 1.1.0
     */
    fcml_uint8_t getPrefix() const {
        return _prefix;
    }

    /**
     * Sets the prefix byte.
     *
     * @param prefix The prefix byte.
     * @since 1.1.0
     */
    void setPrefix(fcml_uint8_t prefix) {
        _prefix = prefix;
    }

    /**
     * Gets the prefix type.
     *
     * @return The prefix byte.
     * @since 1.1.0
     */
    PrefixType getPrefixType() const {
        return _prefixType;
    }

    /**
     * Sets a new prefix type.
     *
     * @param prefixType The prefix byte to be set.
     * @since 1.1.0
     */
    void setPrefixType(PrefixType prefixType) {
        _prefixType = prefixType;
    }

    /**
     * Gets the second and third bytes of the XOP/VEX prefix.
     *
     * @return A pointer to the VEX/XOP bytes.
     * @since 2.0.0
     */
    const fcml_uint8_t* getAvxBytes() const {
        return _AvxBytes;
    }

    /**
     * Gets the second and third bytes of the XOP/VEX prefix.
     *
     * @return A pointer to the VEX/XOP bytes.
     * @since 2.0.0
     */
    fcml_uint8_t* getAvxBytes() {
        return _AvxBytes;
    }

private:
    /** The first byte of the prefix. */
    fcml_uint8_t _prefix;
    /** Tye type of the prefix. */
    PrefixType _prefixType;
    /** True if the prefix is a mandatory one. */
    bool _mandatoryPrefix;
    /** The second and third byte of the AVX prefix.
     * since 2.0.0
     */
    fcml_uint8_t _AvxBytes[3];
};

/** Prefixes details.
 * @since 1.1.0
 */
class PrefixesDetails {
public:

    /**
     * Default constructor.
     * @since 1.1.0
     */
    PrefixesDetails() :
        _prefixesCount(0),
        _prefixesBytesCount(0),
        _isBranch(false),
        _isNobranch(false),
        _isLock(false),
        _isRep(false),
        _isRepne(false),
        _isXrelease(false),
        _isXacquire(false),
        _isVex(false),
        _isEvex(false),
        _isXop(false),
        _isAvx(false),
        _isRex(false),
        _AvxPrefixFirstByte(false),
        _R(0),
        _RPrim(0),
        _X(0),
        _B(0),
        _W(0),
        _L(0),
        _LPrim(0),
        _mmmm(0),
        _vvvv(0),
        _VPrim(0),
        _pp(0),
        _aaa(0),
        _b(false),
        _z(false) {
    }

    /**
     * Gets reference to the instruction prefix at given index.
     * @param index Number of the prefix.
     * @return The instruction prefix for given index.
     * @throw IllegalArgumentException Index out of bound.
     * @since 1.1.0
     */
    const InstructionPrefixDetails& operator[](fcml_usize index) const {
        if( index >= FCML_DASM_PREFIXES_COUNT ) {
            throw IllegalArgumentException( FCML_TEXT( "Index out of bound." ) );
        }
        return _prefixes[index];
    }

    /**
     * Gets reference to the instruction prefix at given index.
     * @param index Number of the prefix.
     * @return The instruction prefix for given index.
     * @throw IllegalArgumentException Index out of bound.
     * @since 1.1.0
     */
    InstructionPrefixDetails& operator[](fcml_usize index) {
        if( index >= FCML_DASM_PREFIXES_COUNT ) {
            throw IllegalArgumentException( FCML_TEXT( "Index out of bound." ) );
        }
        return _prefixes[index];
    }

    /**
     * Gets b flag.
     *
     * @return The B flag.
     * @since 1.1.0
     */
    fcml_uint8_t getB() const {
        return _B;
    }

    /**
     * Sets B flag.
     *
     * @param b The B flag.
     * @since 1.1.0
     */
    void setB(fcml_uint8_t B) {
        _B = B;
    }

    /**
     * Gets true if branch prefix is available.
     *
     * @return True if branch prefix is available.
     * @since 1.1.0
     */
    bool isBranch() const {
        return _isBranch;
    }

    /**
     * Sets branch prefix availability.
     *
     * @param isBranch True if branch prefix is available.
     * @since 1.1.0
     */
    void setBranch(bool isBranch) {
        _isBranch = isBranch;
    }

    /**
     * Gets true if lock prefix is available.
     *
     * @return True if lock prefix is available.
     * @since 1.1.0
     */
    bool isLock() const {
        return _isLock;
    }

    /**
     * Sets lock prefix availability.
     *
     * @param isLock True if lock prefix is available.
     * @since 1.1.0
     */
    void setLock(bool isLock) {
        _isLock = isLock;
    }

    /**
     * Gets true if no-branch prefix is available.
     *
     * @return True if no-branch prefix is available.
     * @since 1.1.0
     */
    bool isNobranch() const {
        return _isNobranch;
    }

    /**
     * Sets no-branch prefix availability.
     *
     * @param isNobranch True if no-branch prefix is available.
     * @since 1.1.0
     */
    void setNobranch(bool isNobranch) {
        _isNobranch = isNobranch;
    }

    /**
     * Gets true if Rep prefix is available.
     *
     * @return True if Rep prefix is available.
     * @since 1.1.0
     */
    bool isRep() const {
        return _isRep;
    }

    /**
     * Sets Rep prefix availability.
     *
     * @param isRep True if Rep prefix is available.
     * @since 1.1.0
     */
    void setRep(bool isRep) {
        _isRep = isRep;
    }

    /**
     * Gets true if Repne prefix is available.
     *
     * @return True if Repne prefix is available.
     * @since 1.1.0
     */
    bool isRepne() const {
        return _isRepne;
    }

    /**
     * Sets Repne prefix availability.
     *
     * @param isRepne True if branch prefix is available.
     * @since 1.1.0
     */
    void setRepne(bool isRepne) {
        _isRepne = isRepne;
    }

    /**
     * Gets true if Rex prefix is available.
     *
     * @return True if Rex prefix is available.
     * @since 1.1.0
     */
    bool isRex() const {
        return _isRex;
    }

    /**
     * Sets REX prefix availability.
     *
     * @param isRex True if REX prefix is available.
     * @since 1.1.0
     */
    void setRex(bool isRex) {
        _isRex = isRex;
    }

    /**
     * Gets true if Vex prefix is available.
     *
     * @return True if Vex prefix is available.
     * @since 1.1.0
     */
    bool isVex() const {
        return _isVex;
    }

    /**
     * Sets VEX prefix availability.
     *
     * @param isVex True if VEX prefix is available.
     * @since 1.1.0
     */
    void setVex(bool isVex) {
        _isVex = isVex;
    }

    /**
     * Sets EVEX prefix availability.
     *
     * @param isEvex True if EVEX prefix is available.
     * @since 2.0.0
     */
    void setEvex(bool isEvex) {
        _isEvex = isEvex;
    }

    /**
     * Gets true if EVEX prefix is available.
     *
     * @return True if EVEX prefix is available.
     * @since 2.0.0
     */
    bool isEvex() const {
        return _isEvex;
    }

    /**
     * Gets true if xacquire prefix is available.
     *
     * @return True if xacquire prefix is available.
     * @since 1.1.0
     */
    bool isXacquire() const {
        return _isXacquire;
    }

    /**
     * Sets xacquire prefix availability.
     *
     * @param isXacquire True if xacquire prefix is available.
     * @since 1.1.0
     */
    void setXacquire(bool isXacquire) {
        _isXacquire = isXacquire;
    }

    /**
     * Gets true if XOP prefix is available.
     *
     * @return True if XOP prefix is available.
     * @since 1.1.0
     */
    bool isXop() const {
        return _isXop;
    }

    /**
     * Sets XOP prefix availability.
     *
     * @param isXop True if XOP prefix is available.
     * @since 1.1.0
     */
    void setXop(bool isXop) {
        _isXop = isXop;
    }

    /**
     * Gets true if any AVX prefix is available.
     *
     * @return True if any AVX prefix is available.
     * @since 2.0.0
     */
    bool isAvx() const {
        return _isAvx;
    }

    /**
     * Sets XOP prefix availability.
     *
     * @param isXop True if XOP prefix is available.
     * @since 2.0.0
     */
    void setAvx(bool isAvx) {
        _isAvx = isAvx;
    }


    /**
     * Gets true if xrelease prefix is available.
     *
     * @return True if xrelease prefix is available.
     * @since 1.1.0
     */
    bool isXrelease() const {
        return _isXrelease;
    }

    /**
     * Sets xrelease prefix availability.
     *
     * @param isXrelease True if xrelease prefix is available.
     * @since 1.1.0
     */
    void setXrelease(bool isXrelease) {
        _isXrelease = isXrelease;
    }

    /**
     * Gets L flag.
     *
     * @return The L flag.
     * @since 1.1.0
     */
    fcml_uint8_t getL() const {
        return _L;
    }

    /**
     * Sets L flag.
     *
     * @param l The L flag.
     * @since 1.1.0
     */
    void setL(fcml_uint8_t L) {
        _L = L;
    }

    /**
     * Gets L' flag.
     *
     * @return The L' flag.
     * @since 2.0.0
     */
    fcml_uint8_t getLPrim() const {
        return _LPrim;
    }

    /**
     * Sets L' flag.
     *
     * @param l The L' flag.
     * @since 2.0.0
     */
    void setLPrim(fcml_uint8_t lPrim) {
        _LPrim = lPrim;
    }


    /**
     * Gets MMMM field.
     *
     * @return MMMM field.
     * @since 1.1.0
     */
    fcml_uint8_t getMmmm() const {
        return _mmmm;
    }

    /**
     * Sets MMMM field.
     *
     * @param mmmm MMMM field.
     * @since 1.1.0
     */
    void setMmmm(fcml_uint8_t mmmm) {
        _mmmm = mmmm;
    }

    /**
     * Gets PP field.
     *
     * @return The PP field.
     * @since 1.1.0
     */
    fcml_uint8_t getPp() const {
        return _pp;
    }

    /**
     * Sets PP field.
     *
     * @param pp PP field.
     * @since 1.1.0
     */
    void setPp(fcml_uint8_t pp) {
        _pp = pp;
    }

    /**
     * Gets a reference to the prefix of the given index.
     *
     * @param index Index for the prefix.
     * @return The prefix at given index.
     * @throw BadArgumentException Array index out of bound.
     * @since 1.1.0
     */
    const InstructionPrefixDetails& getPrefixes( fcml_usize index ) const {
        if( index > FCML_DASM_PREFIXES_COUNT ) {
            throw BadArgumentException(FCML_TEXT("Array index out of bound."), FCML_CEH_GEC_VALUE_OUT_OF_RANGE);
        }
        return _prefixes[index];
    }

    /**
     * Gets a reference to the prefix of the given index.
     *
     * @param index Index for the prefix.
     * @return The prefix at given index.
     * @throw BadArgumentException Array index out of bound.
     * @since 1.1.0
     */
    InstructionPrefixDetails& getPrefixes( fcml_usize index ) {
        if( index > FCML_DASM_PREFIXES_COUNT ) {
            throw BadArgumentException(FCML_TEXT("Array index out of bound."), FCML_CEH_GEC_VALUE_OUT_OF_RANGE);
        }
        return _prefixes[index];
    }

    /**
     * Gets number of bytes interpreted to be prefixes.
     *
     * @return Number of prefixes bytes.
     * @since 1.1.0
     */
    fcml_int getPrefixesBytesCount() const {
        return _prefixesBytesCount;
    }

    /**
     * Sets number of prefixes bytes available for the instruction.
     *
     * @param prefixesBytesCount Number of the prefixes bytes.
     * @since 1.1.0
     */
    void setPrefixesBytesCount(fcml_int prefixesBytesCount) {
        _prefixesBytesCount = prefixesBytesCount;
    }

    /**
     * Gets number of prefixes available for the instruction.
     *
     * @return Number of the prefixes for the instruction.
     * @since 1.1.0
     */
    fcml_int getPrefixesCount() const {
        return _prefixesCount;
    }

    /**
     * Sets number of prefixes available for the instruction.
     *
     * @param prefixesCount Number of the available prefixes.
     * @since 1.1.0
     */
    void setPrefixesCount(fcml_int prefixesCount) {
        _prefixesCount = prefixesCount;
    }

    /**
     * Gets R flag.
     *
     * @return The R flag.
     * @since 1.1.0
     */
    fcml_uint8_t getR() const {
        return _R;
    }

    /**
     * Sets R flag.
     *
     * @param r The R flag.
     * @since 1.1.0
     */
    void setR(fcml_uint8_t r) {
        _R = r;
    }

    /**
     * Gets R' flag.
     *
     * @return The R' flag.
     * @since 2.0.0
     */
    fcml_uint8_t getRPrim() const {
        return _RPrim;
    }

    /**
     * Sets R' flag.
     *
     * @param rPrim The R' flag.
     * @since 2.0.0
     */
    void setRPrim(fcml_uint8_t rPrim) {
        _RPrim = rPrim;
    }

    /**
     * Gets the first byte of the AVX prefix.
     *
     * @return The first byte of the AVX prefix.
     * @since 2.0.0
     */
    fcml_uint8_t getAvxFirstByte() const {
        return _AvxPrefixFirstByte;
    }

    /**
     * Sets a first byte of the XOP/VEX prefix.
     *
     * @param avxFirstByte The first AVX prefix byte.
     * @since 2.0.0
     */
    void setAvxFirstByte(fcml_uint8_t avxFirstByte) {
        _AvxPrefixFirstByte = avxFirstByte;
    }

    /**
     * Gets VVVV field of the XOP/VEX prefix.
     *
     * @return VVVV field of the XOP/VEX prefix.
     * @since 1.1.0
     */
    fcml_uint8_t getVvvv() const {
        return _vvvv;
    }

    /**
     * Sets VVVV field of the XOP/VEX prefix.
     *
     * @param vvvv The VVVV field.
     * @since 1.1.0
     */
    void setVvvv(fcml_uint8_t vvvv) {
        _vvvv = vvvv;
    }

    /**
     * Gets 'aaa' field of the EVEX prefix.
     *
     * @return aaa field of the EVEX prefix.
     * @since 2.0.0
     */
    fcml_uint8_t getAaa() const {
        return _aaa;
    }

    /**
     * Sets 'aaa' field of the EVEX prefix.
     *
     * @param aaa The 'aaa' field.
     * @since 1.1.0
     */
    void setAaa(fcml_uint8_t aaa) {
        _aaa = aaa;
    }

    /**
      * Gets V' flag.
      *
      * @return The V' flag.
      * @since 2.0.0
      */
     fcml_uint8_t getVPrim() const {
         return _VPrim;
     }

     /**
      * Sets V' flag.
      *
      * @param vPrim The V' flag.
      * @since 2.0.0
      */
     void setVPrim(fcml_uint8_t vPrim) {
         _VPrim = vPrim;
     }

    /**
     * Gets W flag.
     *
     * @return The W flag.
     * @since 1.1.0
     */
    fcml_uint8_t getW() const {
        return _W;
    }

    /**
     * Sets W flag.
     *
     * @param w The W flag.
     * @since 1.1.0
     */
    void setW(fcml_uint8_t W) {
        _W = W;
    }

    /**
     * Gets X flag.
     *
     * @return The X flag.
     * @since 1.1.0
     */
    fcml_uint8_t getX() const {
        return _X;
    }

    /**
     * Sets X flag.
     *
     * @param x The X flag.
     * @since 1.1.0
     */
    void setX(fcml_uint8_t X) {
        _X = X;
    }

    /**
     * Gets EVEX.b bit.
     *
     * @return The EVEX.b bit.
     * @since 2.0.0
     */
    bool getBcast() const {
        return _b;
    }

    /**
     * Sets EVEX.b bit.
     *
     * @param b The EVEX.b bit.
     * @since 2.0.0
     */
    void setBcast(bool b) {
        _b = b;
    }

    /**
     * Gets EVEX.z bit.
     *
     * @return The EVEX.z bit.
     * @since 2.0.0
     */
    bool getZ() const {
        return _z;
    }

    /**
     * Sets EVEX.z bit.
     *
     * @param z The EVEX.z bit.
     * @since 2.0.0
     */
    void setZ(bool z) {
        _z = z;
    }

private:
    /** Array with decoded prefixes. */
    InstructionPrefixDetails _prefixes[FCML_DASM_PREFIXES_COUNT];
    /** Number of decoded prefixes. */
    fcml_int _prefixesCount;
    /** Number of bytes used by all decoded prefixes. */
    fcml_int _prefixesBytesCount;
    /** FCML_TRUE if branch prefix exists. */
    bool _isBranch;
    /** FCML_TRUE if nobranch prefix exists. */
    bool _isNobranch;
    /** FCML_TRUE if lock explicit prefix exists. */
    bool _isLock;
    /** FCML_TRUE if rep explicit prefix exists. */
    bool _isRep;
    /** FCML_TRUE if repne explicit prefix exists. */
    bool _isRepne;
    /** FCML_TRUE if xrelease explicit prefix exists. */
    bool _isXrelease;
    /** FCML_TRUE if xacquire explicit prefix exists. */
    bool _isXacquire;
    /** FCML_TRUE if VEX prefix exists. */
    bool _isVex;
    /** FCML_TRUE if EVEX prefix exists.
     * since 2.0.0
     */
    bool _isEvex;
    /** FCML_TRUE if XOP prefix exists. */
    bool _isXop;
    /** FCML_TRUE if any AVX prefix exists.
     * @since 2.0.0
     */
    bool _isAvx;
    /** FCML_TRUE if REX prefix exists. */
    bool _isRex;
    /** Various fields encoded inside decoded prefixes.
     * since 2.0.0
     */
    fcml_uint8_t _AvxPrefixFirstByte;
    /** R field of REX,XOP,VEX or EVEX prefix. */
    fcml_uint8_t _R;
    /** R' field of EVEX prefix.
     * since 2.0.0
     */
    fcml_uint8_t _RPrim;
    /** X field of REX,XOP,VEX or EVEX prefix. */
    fcml_uint8_t _X;
    /** B field of REX,XOP,VEX or EVEX prefix. */
    fcml_uint8_t _B;
    /** W field of REX,XOP,VEX or EVEX prefix. */
    fcml_uint8_t _W;
    /** L field of XOP, VEX or EVEX prefix. */
    fcml_uint8_t _L;
    /** L' field of EVEX prefix.
     * since 2.0.0
     */
    fcml_uint8_t _LPrim;
    /** m-mmmm field of XOP or VEX prefix. */
    fcml_uint8_t _mmmm;
    /** vvvv field of XOP or VEX prefix. */
    fcml_uint8_t _vvvv;
    /** V' field of EVEX prefix.
     * since 2.0.0
     */
    fcml_uint8_t _VPrim;
    /** pp field of XOP or VEX prefix. */
    fcml_uint8_t _pp;
    /** aaa field of EVEX prefix.
     * since 2.0.0
     */
    fcml_uint8_t _aaa;
    /** EVEX.b bit.
     * since 2.0.0
     */
    bool _b;
    /** EVEX.z bit.
     * since 2.0.0
     */
    bool _z;
};

/** Operand details.
 * @since 1.1.0
 */
class OperandDetails {
public:

    /** @since 1.1.0 */
    enum AccessMode {
        /** Undefined mode. */
        AM_ACCESS_MODE_UNDEFINED = FCML_AM_ACCESS_MODE_UNDEFINED,
        /** Operand is read by instruction. */
        AM_READ = FCML_AM_READ,
        /** Operand is set by instruction */
        AM_WRITE = FCML_AM_WRITE,
        /** Operand is read but can be also set. */
        AM_READ_WRITE = AM_READ | AM_WRITE
    };

    /**
     * Creates default operand details with an undefined access mode.
     * @since 1.1.0
     */
    OperandDetails() :
        _accessMode( AM_ACCESS_MODE_UNDEFINED ) {
    }

    /**
     * Creates operand details for given access mode.
     *
     * @param accessMode Access mode.
     * @since 1.1.0
     */
    OperandDetails( AccessMode accessMode ) :
        _accessMode( accessMode ) {
    }

    /**
     * Gets access mode for the operand.
     *
     * @return Access mode.
     * @since 1.1.0
     */
    AccessMode getAccessMode() const {
        return _accessMode;
    }

    /**
     * Sets an access mode for the operand.
     *
     * @param accessMode The access mode for the operand.
     * @since 1.1.0
     */
    void setAccessMode(AccessMode accessMode) {
        _accessMode = accessMode;
    }

private:
    /** Operan's access mode. */
    AccessMode _accessMode;
};

/** ModRM details.
 * @since 1.1.0
 */
class DecodedModRMDetails {
public:

    /**
     * Creates an empty ModR/M details.
     * @since 1.1.0
     */
    DecodedModRMDetails() :
        _isRip(false) {
    }

    /**
     * Gets true if RIP byte is available.
     *
     * @return True if RIP byte is available.
     * @since 1.1.0
     */
    bool isRip() const {
        return _isRip;
    }

    /**
     * Sets RIP byte availability.
     *
     * @param isRip True if RIP byte is available.
     * @since 1.1.0
     */
    void setRip( bool isRip ) {
        _isRip = isRip;
    }

    /**
     * Gets ModR/M nullable byte.
     *
     * @return ModR/M nullable byte.
     * @since 1.1.0
     */
    const Nullable<fcml_uint8_t>& getModRM() const {
        return _modRM;
    }

    /**
     * Gets ModR/M nullable byte.
     *
     * @return ModR/M nullable byte.
     * @since 1.1.0
     */
    Nullable<fcml_uint8_t>& getModRM() {
        return _modRM;
    }

    /**
     * Sets ModR/M nullable byte.
     *
     * @param modRM ModR/M nullable byte.
     * @since 1.1.0
     */
    void setModRM( const Nullable<fcml_uint8_t> &modRM ) {
        _modRM = modRM;
    }

    /**
     * Gets SIB nullable byte.
     *
     * @return SIB nullable byte.
     * @since 1.1.0
     */
    const Nullable<fcml_uint8_t>& getSib() const {
        return _sib;
    }

    /**
     * Gets SIB nullable byte.
     *
     * @return SIB nullable byte.
     * @since 1.1.0
     */
    Nullable<fcml_uint8_t>& getSib() {
        return _sib;
    }

    /**
     * Sets SIB nullable byte.
     *
     * @param sib The SIB nullable byte.
     * @since 1.1.0
     */
    void setSib( const Nullable<fcml_uint8_t> &sib ) {
        _sib = sib;
    }

    /**
     * Gets constant N (see AVX-512 compressed disp8).
     *
     * @return N as nullable value.
     * @since 2.0.0
     */
    const Nullable<fcml_uint32_t>& getN() const {
        return _N;
    }

    /**
     * Gets N (see compressed AVX-512 disp8).
     *
     * @return N nullable value.
     * @since 2.0.0
     */
    Nullable<fcml_uint32_t>& getN() {
        return _N;
    }

    /**
     * Sets N (see compressed AVX-512 disp8).
     *
     * @param N N nullable value.
     * @since 2.0.0
     */
    void setN(const Nullable<fcml_uint32_t> &N) {
        _N = N;
    }

    /**
     * Gets constant raw displacement.
     *
     * @return Displacement.
     * @since 2.0.0
     */
    const Integer& getDisplacement() const {
        return _displacement;
    }

    /**
     * Gets raw displacement.
     *
     * @return Displacement.
     * @since 2.0.0
     */
    Integer& getDisplacement() {
        return _displacement;
    }

    /**
     * Sets displacement.
     *
     * @param displacement Displacement.
     * @since 2.0.0
     */
    void setDisplacement(const Integer &displacement) {
        _displacement = displacement;
    }

private:
    /** ModR/M byte if exists.*/
    Nullable<fcml_uint8_t> _modRM;
    /** SIB byte if exists.*/
    Nullable<fcml_uint8_t> _sib;
    /** True if RIP encoding is used by decoded instruction. This flag is used only in 64 bit mode. */
    bool _isRip;
    /** Raw displacement.
     * since 2.0.0
     */
    Integer _displacement;
    /* N from AVX-512 compressed disp8.
     * since 2.0.0
     */
    Nullable<fcml_uint32_t> _N;
};

/** Additional details about an instruction.
 * @since 1.1.0
 */
class InstructionDetails {
public:

    /**
     * Gets address mode/instruction form. This information is used
     * internally and is rather useless in day to day usage, but if
     * you are interested in it do not hesitate to take a look at
     * the manual.
     *
     * @return Instruction form.
     * @since 1.1.0
     */
    fcml_uint16_t getAddrMode() const {
        return _addrMode;
    }

    /**
     * Sets instruction form.
     *
     * @param addrMode Addressing mode.
     * @since 1.1.0
     */
    void setAddrMode(fcml_uint16_t addrMode) {
        _addrMode = addrMode;
    }

    /**
     * Gets instruction code. See fcml_en_instruction for more details.
     *
     * @return Instruction code.
     * @since 1.1.0
     */
    fcml_en_instruction getInstruction() const {
        return _instruction;
    }

    /**
     * Gets a new instruction code for the instruction.
     *
     * @param instruction The new instruction code.
     * @since 1.1.0
     */
    void setInstruction(fcml_en_instruction instruction) {
        _instruction = instruction;
    }

    /**
     * Gets a pointer to the instruction code. See fcml_en_instruction for more details.
     *
     * @return The pointer to the instruction code.
     * @since 1.1.0
     */
    const fcml_uint8_t* getInstructionCode() const {
        return _instructionCode;
    }

    /**
     * Gets a pointer to the instruction code. See fcml_en_instruction for more details.
     *
     * @return The pointer to the instruction code.
     * @since 1.1.0
     */
    fcml_uint8_t* getInstructionCode() {
        return _instructionCode;
    }

    /**
     * Gets instruction group. See fcml_instructions.h for all available groups.
     *
     * @return The instruction group.
     * @since 1.1.0
     */
    fcml_uint64_t getInstructionGroup() const {
        return _instructionGroup;
    }

    /**
     * Sets an instruction group. See fcml_instructions.h for all available groups.
     *
     * @param instructionGroup The instruction group.
     * @since 1.1.0
     */
    void setInstructionGroup(fcml_uint64_t instructionGroup) {
        _instructionGroup = instructionGroup;
    }

    /**
     * Instruction size in bytes.
     *
     * @return Size of the instruction in bytes.
     * @since 1.1.0
     */
    fcml_usize getInstructionSize() const {
        return _instructionSize;
    }

    /**
     * Sets the instruction size in bytes.
     *
     * @param instructionSize The instruction size.
     * @since 1.1.0
     */
    void setInstructionSize(fcml_usize instructionSize) {
        _instructionSize = instructionSize;
    }

    /**
     * Gets true if it's a shortcut instruction.
     *
     * @return True if it's a shortcut instruction.
     * @since 1.1.0
     */
    bool isShortcut() const {
        return _isShortcut;
    }

    /**
     * Marks the instruction as a shortcut.
     *
     * @param isShortcut True if it's a shortcut instruction.
     * @since 1.1.0
     */
    void setShortcut(bool isShortcut) {
        _isShortcut = isShortcut;
    }

    /**
     * Gets ModR/M instruction details.
     *
     * @return ModR/M details.
     * @since 1.1.0
     */
    const DecodedModRMDetails& getModRmDetails() const {
        return _modRMDetails;
    }

    /**
     * Gets ModR/M instruction details.
     *
     * @return ModR/M details.
     * @since 1.1.0
     */
    DecodedModRMDetails& getModRmDetails() {
        return _modRMDetails;
    }

    /**
     * Sets a new instruction details for the instruction.
     *
     * @param modRmDetails The new instruction details.
     * @since 1.1.0
     */
    void setModRmDetails(const DecodedModRMDetails& modRmDetails) {
        _modRMDetails = modRmDetails;
    }

    /**
     * Gets opcode field 'S'.
     *
     * @return 'S' opcode field.
     * @since 1.1.0
     */
    bool isOpcodeFieldSBit() const {
        return _opcodeFieldSBit;
    }

    /**
     * Sets 'S' field of the opcode byte.
     *
     * @param opcodeFieldSBit 'S' opcode byte field.
     * @since 1.1.0
     */
    void setOpcodeFieldSBit(bool opcodeFieldSBit) {
        _opcodeFieldSBit = opcodeFieldSBit;
    }

    /**
     * Gets opcode field 'W'.
     *
     * @return 'W' opcode field.
     * @since 1.1.0
     */
    bool isOpcodeFieldWBit() const {
        return _opcodeFieldWBit;
    }

    /**
     * Sets 'W' field of the opcode byte.
     *
     * @param opcodeFieldWBit 'W' opcode byte field.
     * @since 1.1.0
     */
    void setOpcodeFieldWBit(bool opcodeFieldWBit) {
        _opcodeFieldWBit = opcodeFieldWBit;
    }

    /**
     * Gets the operand details for given index.
     *
     * @param index Index of the instruction details.
     * @return The operand details for the given index.
     * @throw BadArgumentException Array index out of bound.
     * @since 1.1.0
     */
    const OperandDetails& getOperandDetails( fcml_usize index ) const {
        if( index > FCML_OPERANDS_COUNT ) {
            throw BadArgumentException(FCML_TEXT("Array index out of bound."), FCML_CEH_GEC_VALUE_OUT_OF_RANGE);
        }
        return _operandDetails[index];
    }

    /**
     * Gets the operand details for given index.
     *
     * @param index Index of the instruction details.
     * @return The operand details for the given index.
     * @throw BadArgumentException Array index out of bound.
     * @since 1.1.0
     */
    OperandDetails& getOperandDetails( fcml_usize index ) {
        if( index > FCML_OPERANDS_COUNT ) {
            throw BadArgumentException(FCML_TEXT("Array index out of bound."), FCML_CEH_GEC_VALUE_OUT_OF_RANGE);
        }
        return _operandDetails[index];
    }

    /**
     * Gets instruction prefixes details.
     *
     * @return The instruction prefix details.
     * @since 1.1.0
     */
    const PrefixesDetails& getPrefixesDetails() const {
        return _prefixesDetails;
    }

    /**
     * Gets instruction prefixes details.
     *
     * @return The instruction prefix details.
     * @since 1.1.0
     */
    PrefixesDetails& getPrefixesDetails() {
        return _prefixesDetails;
    }

    /**
     * Sets a new instruction prefixes details.
     *
     * @param prefixesDetails The new prefixes details.
     * @since 1.1.0
     */
    void setPrefixesDetails(const PrefixesDetails& prefixesDetails) {
        _prefixesDetails = prefixesDetails;
    }

    /**
     * Gets pseudo operation code.
     *
     * @return The pseudo operation associated with the instruction.
     * @since 1.1.0
     */
    fcml_en_pseudo_operations getPseudoOp() const {
        return _pseudoOp;
    }

    /**
     * Sets pseudo operation for the instruction.
     *
     * @param pseudoOp The pseudo operation.
     * @since 1.1.0
     */
    void setPseudoOp(fcml_en_pseudo_operations pseudoOp) {
        _pseudoOp = pseudoOp;
    }

    /**
     * Gets true is it's a pseudo operation.
     *
     * @return True if the instruction is a pseudo operation.
     * @since 1.1.0
     */
    bool isPseudoOp() const {
        return _isPseudoOp;
    }

    /**
     * Sets pseudo operation flag.
     *
     * @param isPseudoOp True if the instruction is a pseudo operation.
     * @since 1.1.0
     */
    void setIsPseudoOp(bool isPseudoOp) {
        _isPseudoOp = isPseudoOp;
    }

    /**
     * Gets avx-512 tuple type.
     * @since 2.0.0
     */
    fcml_uint8_t getTupleType() const {
        return _tupleType;
    }

    /**
     * Sets avx-512 tuple type.
     *
     * @param isPseudoOp True if the instruction is a pseudo operation.
     * @since 2.0.0
     */
    void setTupleType(fcml_uint8_t tupleType) {
       _tupleType = tupleType;
    }

private:

    /**
     * True if this is a shortcut.
     * A good example of such instruction is 'cmpsb' as opposed to 'cmps byte ptr [si],byte ptr [di]'.
     * It is very important to take this information into consideration when instruction
     * models are analyzed because there is no operands in the GIM for shortcuts.
     */
    bool _isShortcut;
    /**
     * True if given instruction is a short form of pseudo-ops instructions. See 'vcmpunordsd' for instance.
     */
    bool _isPseudoOp;
    /**
     *  Code of the disassembled instruction.
     */
    fcml_uint8_t _instructionCode[FCML_INSTRUCTION_SIZE];
    /**
     *  Instruction size in bytes.
     */
    fcml_usize _instructionSize;
    /**
     *  Some additional information about decoded instruction prefixes.
     */
    PrefixesDetails _prefixesDetails;
    /**
     * All disassembler specific information about operands going there.
     */
    OperandDetails _operandDetails[FCML_OPERANDS_COUNT];
    /**
     * Details about decoded ModR/M and SIB bytes.
     */
    DecodedModRMDetails _modRMDetails;
    /** Opcode field 's'.
     * This is set only for informational purpose only and you should not use it for any critical functionality.
     */
    bool _opcodeFieldSBit;
    /** Opcode field 'w'.
     * This is set only for informational purpose only and you should not use it for any critical functionality.
     */
    bool _opcodeFieldWBit;
    /**
     * Instruction code/number. @see fcml_instructions.h header file.
     */
    fcml_en_instruction _instruction;
    /**
     * Pseudo operation code.
     */
    fcml_en_pseudo_operations _pseudoOp;
    /**
     *  Code of the instruction form/addressing mode of the instruction above.
     */
    fcml_uint16_t _addrMode;
    /**
     * Instruction group.
     */
    fcml_uint64_t _instructionGroup;
    /**
     * Tuple type used by avx-512 instructions to calculate disp8.
     */
    fcml_uint8_t _tupleType;
};

/** Disassembler result.
 *
 * It's a counterpart to the fcml_st_disassembler_result structure.
 * @since 1.1.0
 */
class DisassemblerResult {

public:

    /**
     * Gets errors container with errors related to the failed disassembling process.
     *
     * @return The error container.
     * @since 1.1.0
     */
    const ErrorContainer& getErrorContainer() const {
        return _errorContainer;
    }

    /**
     * Gets errors container with errors related to the failed disassembling process.
     *
     * @return The error container.
     * @since 1.1.0
     */
    const Instruction& getInstruction() const {
        return _instruction;
    }

    /**
     * Gets instruction details associated with the instruction.
     *
     * @return The instruction details.
     * @since 1.1.0
     */
    const InstructionDetails& getInstructionDetails() const {
        return _instructionDetails;
    }

    /**
     * Cleans the disassembling result.
     * @since 1.1.0
     */
    void clean() {
        _errorContainer.clean();
        _instructionDetails = InstructionDetails();
        _instruction = Instruction();
    }

protected:

    friend class Disassembler;
    friend class DisassemblerTypeConverter;

    /**
     * Gets mutable instruction details.
     * @return Instruction details.
     * @since 1.1.0
     */
    InstructionDetails& getInstructionDetailsInternal() {
        return _instructionDetails;
    }

    /**
     * Sets new instruction details for the disassembler.
     * @param instructionDetails The instruction details.
     * @since 1.1.0
     */
    void setInstructionDetails(const InstructionDetails& instructionDetails) {
        _instructionDetails = instructionDetails;
    }

    /**
     * Gets mutable instruction.
     * @return The mutable instruction.
     * @since 1.1.0
     */
    Instruction& getInstructionInternal() {
        return _instruction;
    }

    /**
     * Sets a new instruction for the result.
     * @param instruction The instruction to be copied to the result.
     * @since 1.1.0
     */
    void setInstruction(const Instruction& instruction) {
        _instruction = instruction;
    }

    /**
     * Sets error container.
     * @param errorContainer The error container.
     * @since 1.1.0
     */
    void setErrorContainer(const ErrorContainer& errorContainer) {
        _errorContainer = errorContainer;
    }

private:

    /** Errors container */
    ErrorContainer _errorContainer;
    /** Instruction details. */
    InstructionDetails _instructionDetails;
    /** The disassembled instruction. */
    Instruction _instruction;

};

/**
 * Converts objects to their structures counterparts.
 * @since 1.1.0
 * @remarks Internal API, not intended to be used outside.
 */
class DisassemblerTypeConverter {

protected:

    friend class Disassembler;
    friend class Renderer;

    static void convert( const DisassemblerContext &src, fcml_st_disassembler_context &dest ) {
        dest.code = src.getCode();
        dest.code_length = src.getCodeLength();
        TypeConverter::convert( src.getEntryPoint(), dest.entry_point );
        convert( src.getDisassemblerConf(), dest.configuration );
    }

    static void convert( const DisassemblerConf &src, fcml_st_disassembler_conf &dest ) {
        dest.conditional_group = src.getConditionalGroup();
        dest.carry_flag_conditional_suffix = src.isCarryFlagConditionalSuffix();
        dest.enable_error_messages = src.isEnableErrorMessages();
        dest.extend_disp_to_asa = src.isExtendDispToAsa();
        dest.fail_if_unknown_instruction = src.isFailIfUnknownInstruction();
        dest.increment_ip = src.isIncrementIp();
        dest.short_forms = src.isShortForms();
    }

    static void convert(const fcml_st_decoded_modrm_details &src,
            DecodedModRMDetails &dest) {
        dest.setRip(FCML_TO_CPP_BOOL(src.is_rip));
        Nullable<fcml_uint8_t> modRM;
        modRM.setNotNull(FCML_TO_CPP_BOOL(src.is_modrm));
        modRM.setValue(src.modrm);
        Nullable<fcml_uint8_t> &sib = dest.getSib();
        sib.setNotNull(FCML_TO_CPP_BOOL(src.sib.is_not_null));
        sib.setValue( src.sib.value );
        TypeConverter::convert(src.displacement.displacement,
                        dest.getDisplacement());
        Nullable<fcml_uint32_t> N;
        N.setNotNull(FCML_TO_CPP_BOOL(src.displacement.N.is_not_null));
        N.setValue(src.displacement.N.value);
        dest.setN(N);
    }

    static void convert( const DecodedModRMDetails &src, fcml_st_decoded_modrm_details &dest ) {
        dest.is_modrm = src.getModRM().isNotNull();
        dest.is_rip = src.isRip();
        dest.modrm = src.getModRM().getValue();
        fcml_nuint8_t &sib = dest.sib;
        sib.is_not_null = src.getSib().isNotNull();
        sib.value = src.getSib().getValue();
        TypeConverter::convert(src.getDisplacement(),
                dest.displacement.displacement);
        dest.displacement.N.is_not_null = src.getN().isNotNull();
        dest.displacement.N.value = src.getN().getValue();
    }

    static void convert( const fcml_st_operand_details &src, OperandDetails &dest ) {
        dest.setAccessMode( static_cast<OperandDetails::AccessMode>( src.access_mode ) );
    }

    static void convert( const OperandDetails &src, fcml_st_operand_details &dest ) {
        dest.access_mode = static_cast<fcml_en_access_mode>( src.getAccessMode() );
    }

    static void convert(const fcml_st_instruction_prefix &src,
            InstructionPrefixDetails &dest) {
        dest.setMandatoryPrefix(FCML_TO_CPP_BOOL(src.mandatory_prefix));
        dest.setPrefix(src.prefix);
        dest.setPrefixType(dest.getPrefixType());
        ::memcpy(dest.getAvxBytes(), src.avx_bytes,
                sizeof(src.avx_bytes));
    }

    static void convert( const InstructionPrefixDetails &src, fcml_st_instruction_prefix &dest ) {
        dest.mandatory_prefix = src.isMandatoryPrefix();
        dest.prefix = src.getPrefix();
        dest.prefix_type = static_cast<fcml_en_prefix_types>( src.getPrefixType() );
        ::memcpy( dest.avx_bytes, src.getAvxBytes(), 2 );
    }

    static void convert(const fcml_st_prefixes_details src,
            PrefixesDetails &dest) {
        for(int i = 0; i < FCML_DASM_PREFIXES_COUNT; i++) {
            convert(src.prefixes[i], dest.getPrefixes(i));
        }
        dest.setPrefixesCount(src.prefixes_count);
        dest.setPrefixesBytesCount(src.prefixes_bytes_count);
        dest.setBranch(FCML_TO_CPP_BOOL( src.is_branch));
        dest.setNobranch(FCML_TO_CPP_BOOL( src.is_nobranch));
        dest.setLock(FCML_TO_CPP_BOOL( src.is_lock));
        dest.setRep(FCML_TO_CPP_BOOL(src.is_rep));
        dest.setRepne(FCML_TO_CPP_BOOL(src.is_repne));
        dest.setXrelease(FCML_TO_CPP_BOOL(src.is_xrelease));
        dest.setXacquire(FCML_TO_CPP_BOOL(src.is_xacquire));
        dest.setVex(FCML_TO_CPP_BOOL(src.is_vex));
        dest.setEvex(FCML_TO_CPP_BOOL(src.is_evex));
        dest.setXop(FCML_TO_CPP_BOOL(src.is_xop));
        dest.setAvx(FCML_TO_CPP_BOOL(src.is_avx));
        dest.setRex(FCML_TO_CPP_BOOL(src.is_rex));
        dest.setAvxFirstByte(src.avx_first_byte);
        dest.setR(src.R);
        dest.setRPrim(src.R_prim);
        dest.setX(src.X);
        dest.setB(src.B);
        dest.setW(src.W);
        dest.setL(src.L);
        dest.setLPrim(src.L_prim);
        dest.setMmmm(src.mmmm);
        dest.setVvvv(src.vvvv);
        dest.setVPrim(src.V_prim);
        dest.setPp(src.pp);
        dest.setAaa(src.aaa);
        dest.setBcast(src.b);
        dest.setZ(src.z);
    }

    static void convert(const PrefixesDetails src,
            fcml_st_prefixes_details &dest) {
        for(int i = 0; i < FCML_DASM_PREFIXES_COUNT; i++) {
            convert(src.getPrefixes(i), dest.prefixes[i]);
        }
        dest.prefixes_count  = src.getPrefixesCount();
        dest.prefixes_bytes_count  = src.getPrefixesBytesCount();
        dest.is_branch  = src.isBranch();
        dest.is_nobranch  = src.isNobranch();
        dest.is_lock  = src.isLock();
        dest.is_rep  = src.isRep();
        dest.is_repne  = src.isRepne();
        dest.is_xrelease  = src.isXrelease();
        dest.is_xacquire  = src.isXacquire();
        dest.is_vex  = src.isVex();
        dest.is_xop  = src.isXop();
        dest.is_avx  = src.isAvx();
        dest.is_evex  = src.isEvex();
        dest.is_rex  = src.isRex();
        dest.avx_first_byte  = src.getAvxFirstByte();
        dest.R  = src.getR();
        dest.R_prim  = src.getRPrim();
        dest.X  = src.getX();
        dest.B  = src.getB();
        dest.W  = src.getW();
        dest.L  = src.getL();
        dest.L_prim  = src.getLPrim();
        dest.mmmm  = src.getMmmm();
        dest.vvvv  = src.getVvvv();
        dest.V_prim  = src.getVPrim();
        dest.pp  = src.getPp();
        dest.aaa  = src.getAaa();
        dest.b  = src.getBcast();
        dest.z  = src.getZ();
    }

    static void convert( const fcml_st_instruction_details &src, InstructionDetails &dest ) {
        dest.setTupleType( src.tuple_type );
        dest.setAddrMode( src.addr_mode );
        dest.setInstruction( src.instruction );
        dest.setInstructionGroup( src.instruction_group );
        dest.setInstructionSize( src.instruction_size );
        dest.setOpcodeFieldSBit( FCML_TO_CPP_BOOL( src.opcode_field_s_bit ) );
        dest.setOpcodeFieldWBit( FCML_TO_CPP_BOOL( src.opcode_field_w_bit ) );
        dest.setIsPseudoOp( FCML_TO_CPP_BOOL( src.is_pseudo_op ) );
        dest.setPseudoOp( src.pseudo_op );
        dest.setShortcut( FCML_TO_CPP_BOOL( src.is_shortcut ) );
        convert( src.modrm_details, dest.getModRmDetails() );
        for( int i = 0; i < FCML_OPERANDS_COUNT; i++ ) {
            convert( src.operand_details[i], dest.getOperandDetails(i) );
        }
        convert( src.prefixes_details, dest.getPrefixesDetails() );
    }

    static void convert( const InstructionDetails &src, fcml_st_instruction_details &dest ) {
        dest.tuple_type = src.getTupleType();
        dest.addr_mode = src.getAddrMode();
        dest.instruction = src.getInstruction();
        dest.instruction_group = src.getInstructionGroup();
        dest.instruction_size = src.getInstructionSize();
        dest.opcode_field_s_bit = src.isOpcodeFieldSBit();
        dest.opcode_field_w_bit = src.isOpcodeFieldWBit();
        dest.is_pseudo_op = src.isPseudoOp();
        dest.pseudo_op = src.getPseudoOp();
        dest.is_shortcut = src.isShortcut();
        convert( src.getModRmDetails(), dest.modrm_details );
        for( int i = 0; i < FCML_OPERANDS_COUNT; i++ ) {
            convert( src.getOperandDetails(i), dest.operand_details[i] );
        }
        convert( src.getPrefixesDetails(), dest.prefixes_details );
    }

    static void convert( const fcml_st_disassembler_result &src, DisassemblerResult &dest ) {
        TypeConverter::convert( src.instruction, dest.getInstructionInternal() );
        convert( src.instruction_details, dest.getInstructionDetailsInternal() );
    }

    static void convert( const DisassemblerResult &src, fcml_st_disassembler_result &dest ) {
        TypeConverter::convert( src.getInstruction(), dest.instruction );
        convert( src.getInstructionDetails(), dest.instruction_details );
    }

    static void free( fcml_st_disassembler_result &src ) {
        TypeConverter::free( src.instruction );
    }

};

/** Disassembler wrapper.
 * @since 1.1.0
 */
class Disassembler : public NonCopyable, protected DialectAware {
public:

    /**
     * Creates a disassembler instance for the given dialect.
     *
     * @param dialect The dialect for the disassembler.
     * @throw InitException Cannot initialize the disassembler.
     * @since 1.1.0
     */
    Disassembler(Dialect &dialect) :
            _dialect(dialect) {
        fcml_ceh_error error = ::fcml_fn_disassembler_init( extractDialect( dialect ), &_disassembler);
        if (error) {
            throw InitException(FCML_TEXT("Cannot initialize the disassembler."), error);
        }
    }

    /**
     * Destructor.
     * @since 1.1.0
     */
    virtual ~Disassembler() {
        if (_disassembler) {
            ::fcml_fn_disassembler_free(_disassembler);
            _disassembler = NULL;
        }
    }

public:

    /**
     * Disassembled the next instruction from the context.
     *
     * @param ctx Context describing the next instruction to disassemble.
     * @param[out] disassemblerResult Disassembler result.
     * @throw DisassemblingFailedException Disassemblation failed.
     * @return Error code.
     * @since 1.1.0
     */
    fcml_ceh_error disassemble( DisassemblerContext &ctx, DisassemblerResult &disassemblerResult ) {

        fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

        fcml_st_disassembler_context context;
        DisassemblerTypeConverter::convert( ctx, context );

        context.disassembler = _disassembler;

        /* Prepare assembler result. */
        fcml_st_disassembler_result disassembler_result;
        ::fcml_fn_disassembler_result_prepare( &disassembler_result );

        try {

            disassemblerResult.clean();

            error = ::fcml_fn_disassemble( &context, &disassembler_result );

            ErrorContainer errorContainer;
            ErrorTypeConverter::convert( disassembler_result.errors, errorContainer );

            disassemblerResult.setErrorContainer( errorContainer );

            if( error && ctx.getDisassemblerConf().isThrowExceptionOnError() ) {
                ::fcml_fn_disassembler_result_free( &disassembler_result );
                throw DisassemblingFailedException( FCML_TEXT("Assembling failed."), errorContainer, error );
            }

            if( !error ) {

                // Convert result.
                DisassemblerTypeConverter::convert( disassembler_result, disassemblerResult );

                ctx.getEntryPoint().setIP( context.entry_point.ip );
                ctx.setCode( context.code );
                ctx.setCodeLength( context.code_length );

            }

            ::fcml_fn_disassembler_result_free( &disassembler_result );

        } catch( std::exception &exc ) {
            // If anything failed, free assembler results.
            ::fcml_fn_disassembler_result_free( &disassembler_result );
            throw exc;
        }

        return error;
    }

    /**
     * Gets dialect associated with the disassembler.
     * @return The dialect instance associated with the disassembler.
     * @since 1.1.0
     */
    Dialect& getDialect() const {
        return _dialect;
    }

private:

    /** The dialect associated with the disassembler. */
    Dialect &_dialect;
    /** The disassembler instance. */
    fcml_st_disassembler *_disassembler;

};

}

#endif //FCML_DISASSEMBLER_HPP_

