#ifndef FCML_INT_COMMON_H_
#define FCML_INT_COMMON_H_

#include "fcml_types.h"
#include "fcml_common.h"
#include "fcml_errors.h"
#include "fcml_intel_dialect.h"
#include "fcml_gas_dialect.h"

namespace fcml {

/**
 *  Base exception for all exceptions exposed by FCML library.
 */
class BaseException {
public:
    BaseException( fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR ) {
        this->_msg = NULL;
        this->_error = error;
    }
    BaseException( fcml_string msg, fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR ) {
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
    fcml_string GetMsg() {
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
    InitException( fcml_string msg, fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR ) :
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

class IntelDialect {
public:
    IntelDialect( fcml_uint32_t flags = FCML_INTEL_DIALECT_CF_DEFAULT ) :
            _dialect( NULL ) {
        fcml_ceh_error error = fcml_fn_dialect_init_intel( flags, &_dialect );
        if ( error ) {
            throw InitException( FCML_TEXT( "Can not initialize the Intel dialect." ), error );
        }
    }
    virtual ~IntelDialect() {
        if ( _dialect ) {
            fcml_fn_dialect_free( _dialect );
            _dialect = NULL;
        }
    }
public:
    fcml_st_dialect *GetDialect() {
        return _dialect;
    }
private:
    IntelDialect( const IntelDialect &cpy ) :
            _dialect( cpy._dialect ) {
        // Not supported.
        throw OperationNotSupportedException();
    }
    IntelDialect& operator=( const BaseException &exc ) {
        throw OperationNotSupportedException();
    }
private:
    fcml_st_dialect *_dialect;
};

}

#endif //FCML_INT_COMMON_H_
