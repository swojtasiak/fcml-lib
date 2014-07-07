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
