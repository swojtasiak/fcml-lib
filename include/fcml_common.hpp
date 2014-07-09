#ifndef FCML_INT_COMMON_HPP_
#define FCML_INT_COMMON_HPP_

#include <stdlib.h>
#include <string.h>
#include <iterator>
#include <new>
#include <iostream>
#include <stdexcept>

#include "fcml_types.h"
#include "fcml_common.h"
#include "fcml_errors.h"
#include "fcml_intel_dialect.h"
#include "fcml_gas_dialect.h"

namespace fcml {

template<typename T>
class WrapperPtr {
public:
    WrapperPtr() {
        _wrapped = NULL;
    }
    WrapperPtr( T *wrapped ) {
        _wrapped = wrapped;
    }
    WrapperPtr( const T &wrapped ) {
        _wrapped = &wrapped;
    }
    WrapperPtr& operator=( const WrapperPtr &ptr ) {
        if ( &ptr != this ) {
            // Remove currently managed object.
            if( _wrapped ) {
                delete _wrapped;
            }
            _wrapped = ptr._wrapped;
        }
        return *this;
    }
    ~WrapperPtr() {
        if(_wrapped) {
            delete _wrapped;
        }
    }
    T *getWrapped() {
        return _wrapped;
    }
    T *operator*() const {
        return _wrapped;
    }
private:
    T *_wrapped;
};

class Env {
public:
    static fcml_string StrDup( fcml_string str ) {
        if( !str ) {
            return NULL;
        }
        fcml_string newStr = strdup(str);
        if( !newStr ) {
            throw std::bad_alloc();
        }
        return newStr;
    }
    static void StrFree( fcml_string str ) {
        free(str);
    }
};

/**
 *  Base exception for all exceptions exposed by FCML library.
 */
class BaseException {
public:
    BaseException( fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR ) {
        this->_msg = NULL;
        this->_error = error;
    }
    BaseException( const fcml_string msg, fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR ) {
        this->_msg = msg;
        this->_error = error;
    }
    BaseException( const BaseException &cpy ) {
        this->_msg = cpy._msg;
        this->_error = cpy._error;
    }
    BaseException& operator=( const BaseException &exc ) {
        if ( &exc != this ) {
            this->_msg = exc._msg;
            this->_error = exc._error;
        }
        return *this;
    }
public:
    const fcml_string GetMsg() {
        return _msg;
    }
    fcml_ceh_error GetError() {
        return _error;
    }
private:
    void* operator new( size_t size ) {
        return ::operator new( size );
    }
private:
    fcml_string _msg;
    fcml_ceh_error _error;
};

/**
 *  Component can not be initialized correctly.
 */
class InitException: public BaseException {
public:
    InitException( const fcml_string msg, fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR ) :
            BaseException( msg, error ) {
    }
};

/**
 *  Component can not be initialized correctly.
 */
class OperationNotSupportedException: public BaseException {
public:
    OperationNotSupportedException( fcml_string msg ) :
            BaseException( msg ) {
    }
    OperationNotSupportedException() {
    }
};

class NonCopyable {
protected:
    NonCopyable() {
    }
private:
    NonCopyable( const NonCopyable &cpy ) {
        throw OperationNotSupportedException();
    }
    NonCopyable& operator=( const NonCopyable &exc ) {
        throw OperationNotSupportedException();
    }
};

/**
 * Wraps a structure by its pointer or holds the deep-copy of the whole structure.
 * This container is useful when we need to return a wrapped structure but we
 * do not want to copy anything if it is not necessary yet. For example we can wrap an
 * assembling result and return the result in the form of C++ object but we still
 * work on the original structure, nothing is copied there. Doing so we can save space and
 * time. Notice that object can be still copied when needed and in such a cache a deep-copy
 * of the whole structure is made anyway.
 */
template<class T>
class StructureWrapper {
public:
    /**
     * It just allocates space for the wrapped structure and cleans it.
     */
    StructureWrapper() {
        _owner = FCML_TRUE;
        _wrapped = new T();
        memset( _wrapped, 0, sizeof(T) );
    }
    /**
     * Wraps the given structure without copying and allocating anything.
     * Remember that this rule is not propagated when such an object
     * is an argument while objects are copied. It means that every obiect
     * constructed using this one will always deep-copy the wrapped structure.
     */
    StructureWrapper( T *wrapped ) {
        if( !wrapped ) {
            throw std::invalid_argument("Pointer to the wrapping structure can not be null!");
        }
        _owner = FCML_FALSE;
        _wrapped = wrapped;
    }
    /**
     * Passing a structure by reference always means that we would like to make a
     * deep-copy and then wrapp the result, not the source structure itself. Notice that
     * you have to implement deep-copy logic in the derived class if it is needed.
     * @param wrapped Structure to be copied and wrapped.
     */
    StructureWrapper( T &wrapped ) {
        _owner = FCML_TRUE;
        _wrapped = new T();
        *_wrapped = wrapped;
    }
    /**
     * Copy constructor always makes the deep-copy of the source object.
     * It really doesn't matter if the source object is a reference or
     * pointer based one.
     */
    StructureWrapper( const StructureWrapper &cpy ) {
        _owner = FCML_TRUE;
        _wrapped = new T();
        *_wrapped = *cpy._wrapped;
    }
    /**
     * Wraps given pointer unallocating the managed structure first,
     * but only if it holds a copy. This is a conterpart to the pointer
     * based constructor above.
     */
    StructureWrapper& operator=( const T *wrapped ) {
        if( !wrapped ) {
            throw std::invalid_argument("Pointer to the wrapping structure can not be null!");
        }
        if( wrapped != this->_wrapped ) {
            if( _owner && _wrapped ) {
                StructureFree();
                delete _wrapped;
            }
            _wrapped = wrapped;
            _owner = FCML_FALSE;
            // Wrapped object has changed, so all related references need to be updated.
            updateReferences();
        }
        return *this;
    }
    /**
     * Make a deep-copy of the given object unallocating
     * the managed structure, but only if it holds a copy.
     */
    StructureWrapper& operator=( const StructureWrapper &wrapper ) {
        if( &wrapper != this ) {
            if( !_wrapped ) {
                _wrapped = new T();
            } else {
                StructureFree();
            }
            *_wrapped = *wrapper._wrapped;
            StructureCopy(wrapper._wrapped);
            // Wrapped object has changed, so all related references need to be updated.
            updateReferences();

        }
        return *this;
    }
    /**
     * A simple "equal" just by pointers.
     */
    bool operator==( const StructureWrapper& other ) {
        return ( _wrapped == other._wrapped );
    }
    /**
     * A simple "not equal" just by pointers.
     */
    bool operator!=( const StructureWrapper& other ) {
        return ( _wrapped != other._wrapped );
    }
    /**
     * Deep-frees owned structure.
     */
    virtual ~StructureWrapper() {
        if( _wrapped && _owner ) {
            delete _wrapped;
        }
        _wrapped = NULL;
    }
protected:
    virtual void updateReferences();
    virtual void StructureCopy(T *source) { }
    virtual void StructureFree() { }
public:
    T &getStruct() {
        return *_wrapped;
    }
protected:
    fcml_bool _owner;
    T* _wrapped;
};

class EntryPoint: public StructureWrapper<fcml_st_entry_point> {
public:

    EntryPoint( fcml_ip instruction_pointer, fcml_en_operating_mode operating_mode = FCML_OM_32_BIT, fcml_usize asa = FCML_DS_UNDEF, fcml_usize osa = FCML_DS_UNDEF ) {
        _wrapped->op_mode = operating_mode;
        _wrapped->address_size_attribute = asa;
        _wrapped->operand_size_attribute = osa;
        _wrapped->ip = instruction_pointer;
    }

    EntryPoint(fcml_st_entry_point *wrapped) : StructureWrapper(wrapped) {}
    EntryPoint(fcml_st_entry_point &wrapped) : StructureWrapper(wrapped) {}

    fcml_usize getAddressSizeAttribute() const {
        return _wrapped->address_size_attribute;
    }

    void setAddressSizeAttribute( fcml_usize addressSizeAttribute ) {
        _wrapped->address_size_attribute = addressSizeAttribute;
    }

    fcml_ip getIp() const {
        return _wrapped->ip;
    }

    void setIp( fcml_ip ip ) {
        this->_wrapped->ip = ip;
    }

    fcml_en_operating_mode getOpMode() const {
        return _wrapped->op_mode;
    }

    void setOpMode( fcml_en_operating_mode opMode ) {
        _wrapped->op_mode = opMode;
    }

    fcml_usize getOperandSizeAttribute() const {
        return _wrapped->operand_size_attribute;
    }

    void setOperandSizeAttribute( fcml_usize operandSizeAttribute ) {
        _wrapped->operand_size_attribute = operandSizeAttribute;
    }

    void incrementIp( fcml_ip value ) {
        this->_wrapped->ip += value;
    }
};

class Integer: public StructureWrapper<fcml_st_integer> {
public:

    Integer() {
    }
    Integer(fcml_st_integer *wrapped) : StructureWrapper(wrapped) {
    }
    Integer(fcml_st_integer &wrapped) : StructureWrapper(wrapped) {
    }
    Integer(const Integer &cpy) : StructureWrapper(cpy) {
    }

public:

    fcml_int16_t getInt16() const {
        return _wrapped->int16;
    }

    void setInt16( fcml_int16_t int16 ) {
        this->_wrapped->int16 = int16;
    }

    fcml_int32_t getInt32() const {
        return _wrapped->int32;
    }

    void setInt32( fcml_int32_t int32 ) {
        this->_wrapped->int32 = int32;
    }

    fcml_int64_t getInt64() const {
        return _wrapped->int64;
    }

    void setInt64( fcml_int64_t int64 ) {
        this->_wrapped->int64 = int64;
    }

    fcml_int8_t getInt8() const {
        return _wrapped->int8;
    }

    void setInt8( fcml_int8_t int8 ) {
        this->_wrapped->int8 = int8;
    }

    fcml_bool getIsSigned() const {
        return _wrapped->is_signed;
    }

    void setIsSigned( fcml_bool isSigned ) {
        _wrapped->is_signed = isSigned;
    }

    fcml_usize getSize() const {
        return _wrapped->size;
    }

    void setSize( fcml_usize size ) {
        this->_wrapped->size = size;
    }

};

class Register: public StructureWrapper<fcml_st_register> {
public:

    Register() {
    }
    Register(fcml_st_register *wrapped) : StructureWrapper(wrapped) {
    }
    Register(fcml_st_register &wrapped) : StructureWrapper(wrapped) {
    }
    Register(const Register &cpy) : StructureWrapper(cpy) {
    }

public:

    fcml_uint8_t getReg() const {
        return _wrapped->reg;
    }

    void setReg( fcml_uint8_t reg ) {
        this->_wrapped->reg = reg;
    }

    fcml_usize getSize() const {
        return _wrapped->size;
    }

    void setSize( fcml_usize size ) {
        this->_wrapped->size = size;
    }

    fcml_en_register getType() const {
        return _wrapped->type;
    }

    void setType( fcml_en_register type ) {
        this->_wrapped->type = type;
    }

    fcml_bool getX64Exp() const {
        return _wrapped->x64_exp;
    }

    void setX64Exp( fcml_bool x64Exp ) {
        _wrapped->x64_exp = x64Exp;
    }

};


class FarPointer: public StructureWrapper<fcml_st_far_pointer> {
public:

    FarPointer() {
    }
    FarPointer(fcml_st_far_pointer *wrapped) : StructureWrapper(wrapped) {
    }
    FarPointer(fcml_st_far_pointer &wrapped) : StructureWrapper(wrapped) {
    }
    FarPointer(const FarPointer &cpy) : StructureWrapper(cpy) {
    }

public:

    fcml_usize getOffsetSize() const {
        return _wrapped->offset_size;
    }

    void setOffsetSize( fcml_usize offsetSize ) {
        _wrapped->offset_size = offsetSize;
    }

    fcml_int16_t getOffset16() const {
        return _wrapped->offset16;
    }

    void setOffset16( fcml_int16_t offset16 ) {
        this->_wrapped->offset16 = offset16;
    }

    fcml_int32_t getOffset32() const {
        return _wrapped->offset32;
    }

    void setOffset32( fcml_int32_t offset32 ) {
        this->_wrapped->offset32 = offset32;
    }

    fcml_uint16_t getSegment() const {
        return _wrapped->segment;
    }

    void setSegment( fcml_uint16_t segment ) {
        this->_wrapped->segment = segment;
    }

};

class SegmentSelector: public StructureWrapper<fcml_st_segment_selector> {
public:
    SegmentSelector() : _segmentSelector(&_wrapped->segment_selector) {
    }
    SegmentSelector(fcml_st_segment_selector *wrapped) : StructureWrapper(wrapped), _segmentSelector(&_wrapped->segment_selector) {
    }
    SegmentSelector(fcml_st_segment_selector &wrapped) : StructureWrapper(wrapped), _segmentSelector(&_wrapped->segment_selector) {
    }
    SegmentSelector(const SegmentSelector &cpy) : StructureWrapper(cpy), _segmentSelector(&_wrapped->segment_selector) {
    }
public:
    fcml_bool getIsDefaultReg() const {
        return _wrapped->is_default_reg;
    }

    void setIsDefaultReg( fcml_bool isDefaultReg ) {
        _wrapped->is_default_reg = isDefaultReg;
    }
protected:
    void updateReferences() {
        _segmentSelector = &_wrapped->segment_selector;
    }
private:
    Register _segmentSelector;
};

class EffectiveAddress: public StructureWrapper<fcml_st_effective_address> {
public:
    EffectiveAddress() : _baseRegister(&_wrapped->base), _indexRegister(&_wrapped->index), _displacement(&_wrapped->displacement) {
    }
    EffectiveAddress(fcml_st_effective_address *wrapped) : StructureWrapper(wrapped), _baseRegister(&_wrapped->base), _indexRegister(&_wrapped->index), _displacement(&_wrapped->displacement) {
    }
    EffectiveAddress(fcml_st_effective_address &wrapped) : StructureWrapper(wrapped), _baseRegister(&_wrapped->base), _indexRegister(&_wrapped->index), _displacement(&_wrapped->displacement) {
    }
    EffectiveAddress(const EffectiveAddress &cpy) : StructureWrapper(cpy), _baseRegister(&_wrapped->base), _indexRegister(&_wrapped->index), _displacement(&_wrapped->displacement) {
    }
public:

    const Register& getBase() const {
        return _baseRegister;
    }

    void setBase( const Register& baseRegister ) {
        _baseRegister = baseRegister;
    }

    const Integer& getDisplacement() const {
        return _displacement;
    }

    void setDisplacement( const Integer& displacement ) {
        _displacement = displacement;
    }

    const Register& getIndex() const {
        return _indexRegister;
    }

    void setIndex( const Register& indexRegister ) {
        _indexRegister = indexRegister;
    }

    fcml_uint8_t getScale() const {
        return _wrapped->scale_factor;
    }

    void setScale( fcml_uint8_t scaleFactor ) {
        _wrapped->scale_factor = scaleFactor;
    }

protected:
    void updateReferences() {
        _baseRegister = &_wrapped->base;
        _indexRegister = &_wrapped->index;
        _displacement = &_wrapped->displacement;
    }
private:
    Register _baseRegister;
    Register _indexRegister;
    Integer _displacement;
};

class Offset: public StructureWrapper<fcml_st_offset> {
public:
    Offset() {
    }
    Offset(fcml_st_offset *wrapped) : StructureWrapper(wrapped) {
    }
    Offset(fcml_st_offset &wrapped) : StructureWrapper(wrapped) {
    }
    Offset(const Offset &cpy) : StructureWrapper(cpy) {
    }

public:

    fcml_bool getIsSigned() const {
        return _wrapped->is_signed;
    }

    void setIsSigned( fcml_bool isSigned ) {
        _wrapped->is_signed = isSigned;
    }

    fcml_int16_t getOff16() const {
        return _wrapped->off16;
    }

    void setOff16( fcml_int16_t off16 ) {
        this->_wrapped->off16 = off16;
    }

    fcml_int32_t getOff32() const {
        return _wrapped->off32;
    }

    void setOff32( fcml_int32_t off32 ) {
        this->_wrapped->off32 = off32;
    }

    fcml_int64_t getOff64() const {
        return _wrapped->off64;
    }

    void setOff64( fcml_int64_t off64 ) {
        this->_wrapped->off64 = off64;
    }

    fcml_usize getSize() const {
        return _wrapped->size;
    }

    void setSize( fcml_usize size ) {
        this->_wrapped->size = size;
    }
};

class Address: public StructureWrapper<fcml_st_address> {
public:
    Address() : _segmentSelector(&_wrapped->segment_selector), _effectiveAddress(&_wrapped->effective_address), _offset(&_wrapped->offset) {
    }
    Address(fcml_st_address *wrapped) : StructureWrapper(wrapped), _segmentSelector(&_wrapped->segment_selector), _effectiveAddress(&_wrapped->effective_address), _offset(&_wrapped->offset) {
    }
    Address(fcml_st_address &wrapped) : StructureWrapper(wrapped), _segmentSelector(&_wrapped->segment_selector), _effectiveAddress(&_wrapped->effective_address), _offset(&_wrapped->offset) {
    }
    Address(const Address &cpy) : StructureWrapper(cpy), _segmentSelector(&_wrapped->segment_selector), _effectiveAddress(&_wrapped->effective_address), _offset(&_wrapped->offset){
    }
protected:
    void updateReferences() {
        _segmentSelector = &_wrapped->segment_selector;
        _effectiveAddress = &_wrapped->effective_address;
        _offset = &_wrapped->offset;
    }
private:
    SegmentSelector _segmentSelector;
    EffectiveAddress _effectiveAddress;
    Offset _offset;
};

class Operand: public StructureWrapper<fcml_st_operand> {
public:
    Operand() : _immediate(&_wrapped->immediate), _farPointer(&_wrapped->far_pointer), _register(&_wrapped->reg) {
    }
    Operand(fcml_st_operand *wrapped) : StructureWrapper(wrapped), _immediate(&_wrapped->immediate), _farPointer(&_wrapped->far_pointer), _register(&_wrapped->reg) {
    }
    Operand(fcml_st_operand &wrapped) : StructureWrapper(wrapped), _immediate(&_wrapped->immediate), _farPointer(&_wrapped->far_pointer), _register(&_wrapped->reg) {
    }
    Operand(const Operand &cpy) : StructureWrapper(cpy), _immediate(&_wrapped->immediate), _farPointer(&_wrapped->far_pointer), _register(&_wrapped->reg) {
    }
protected:
    void updateReferences() {
        _immediate = &_wrapped->immediate;
        _farPointer = &_wrapped->far_pointer;
        _register = &_wrapped->reg;
    }
private:
    Integer _immediate;
    FarPointer _farPointer;
    Register _register;
};

class Instruction: public StructureWrapper<fcml_st_instruction> {
public:
    Instruction() {
        updateReferences();
    }
    Instruction(fcml_st_instruction *wrapped) : StructureWrapper(wrapped) {
        updateReferences();
    }
    Instruction(fcml_st_instruction &wrapped) : StructureWrapper(wrapped) {
        StructureCopy(&wrapped);
        updateReferences();
    }
    Instruction(const Instruction &cpy) : StructureWrapper(cpy) {
        StructureCopy(cpy._wrapped);
        updateReferences();
    }
    ~Instruction() {
        StructureFree();
    }
public:

    Operand& operator[](int i) {
        if( i < 0 || i >=  5 ) {
            throw std::out_of_range("No such error info available.");
        }
        return **_operands[i];
    }

    Operand& getOperand(int i) {
        return (*this)[i];
    }

    const fcml_st_condition& getCondition() const {
        return _wrapped->condition;
    }

    void setCondition( const fcml_st_condition& condition ) {
        this->_wrapped->condition = condition;
    }

    fcml_hints getHints() const {
        return _wrapped->hints;
    }

    void setHints( fcml_hints hints ) {
        this->_wrapped->hints = hints;
    }

    fcml_bool getIsConditional() const {
        return _wrapped->is_conditional;
    }

    void setIsConditional( fcml_bool isConditional ) {
        _wrapped->is_conditional = isConditional;
    }

    fcml_char* getMnemonic() const {
        return _wrapped->mnemonic;
    }

    void setMnemonic( fcml_char* mnemonic ) {
        this->_wrapped->mnemonic = mnemonic;
    }

    fcml_int getOperandsCount() const {
        return _wrapped->operands_count;
    }

    void setOperandsCount( fcml_int operandsCount ) {
        _wrapped->operands_count = operandsCount;
    }

    fcml_prefixes getPrefixes() const {
        return _wrapped->prefixes;
    }

    void setPrefixes( fcml_prefixes prefixes ) {
        this->_wrapped->prefixes = prefixes;
    }

protected:

    void updateReferences() {
        for( int i = 0; i < FCML_OPERANDS_COUNT; i++ ) {
            _operands[i] = new Operand( &_wrapped->operands[i] );
        }
    }

    void StructureCopy(fcml_st_instruction *source) {
        _wrapped->mnemonic = ( source->mnemonic ) ? Env::StrDup(source->mnemonic) : NULL;
    }

    void StructureFree() {
        // Free duplicated mnemonic.
        if( _wrapped->mnemonic ) {
            Env::StrFree(_wrapped->mnemonic);
        }
    }

private:
    // All operands are stored here.
    WrapperPtr<Operand> _operands[5];
};

class Dialect : public NonCopyable {
protected:
    Dialect() {
        _dialect = NULL;
    }
    virtual ~Dialect() {
        if( _dialect ) {
            ::fcml_fn_dialect_free( _dialect );
            _dialect = NULL;
        }
    }
public:
    fcml_st_dialect *GetDialect() {
        return _dialect;
    }
protected:
    void SetDialect( fcml_st_dialect *dialect ) {
        this->_dialect = dialect;
    }
private:
    fcml_st_dialect *_dialect;
};

class IntelDialect: public Dialect {
public:
    IntelDialect( fcml_uint32_t flags = FCML_INTEL_DIALECT_CF_DEFAULT ) {
        fcml_st_dialect *dialect;
        fcml_ceh_error error = ::fcml_fn_dialect_init_intel( flags, &dialect );
        if ( error ) {
            throw InitException( FCML_TEXT( "Can not initialize the Intel dialect." ), error );
        }
        SetDialect( dialect );
    }
    virtual ~IntelDialect() {
    }
};

class GASDialect: public Dialect {
public:
    GASDialect( fcml_uint32_t flags = FCML_GAS_DIALECT_CF_DEFAULT ) {
        fcml_st_dialect *dialect;
        fcml_ceh_error error = ::fcml_fn_dialect_init_gas( flags, &dialect );
        if ( error ) {
            throw InitException( FCML_TEXT( "Can not initialize the AT&T dialect." ), error );
        }
        SetDialect( dialect );
    }
    virtual ~GASDialect() {
    }
};

}

#endif //FCML_INT_COMMON_HPP_
