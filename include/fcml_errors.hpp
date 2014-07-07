#ifndef FCML_ASM_ERRORS_HPP_
#define FCML_ASM_ERRORS_HPP_

#include <iterator>
#include <vector>
#include <stdexcept>

#include "fcml_types.h"
#include "fcml_errors.h"
#include "fcml_common.hpp"

namespace fcml {

class ErrorInfo : public StructureWrapper<fcml_st_ceh_error_info> {
public:

    ErrorInfo() {
    }

    ErrorInfo(fcml_st_ceh_error_info &wrapped) : StructureWrapper(wrapped) {
        StructureCopy(&wrapped);
    }

    ErrorInfo(fcml_st_ceh_error_info *wrapped) : StructureWrapper(wrapped) {
    }

    ErrorInfo( const ErrorInfo &cpy ) : StructureWrapper(cpy) {
        StructureCopy(cpy._wrapped);
    }

    virtual ~ErrorInfo() {
        if( _wrapped && _owner ) {
            StructureFree();
        }
    }

    void StructureCopy(fcml_st_ceh_error_info *source) {
        _wrapped->message = ( source->message ) ? Env::StrDup(source->message) : NULL;
    }

    void StructureFree() {
        if( _wrapped->message ) {
            Env::StrFree(_wrapped->message);
        }
    }

    fcml_ceh_error getCode() const {
        return _wrapped->code;
    }

    void setCode( fcml_ceh_error code ) {
        this->_wrapped->code = code;
    }

    fcml_en_ceh_error_level getLevel() const {
        return _wrapped->level;
    }

    void setLevel( fcml_en_ceh_error_level level ) {
        this->_wrapped->level = level;
    }

    fcml_string getMessage() const {
        return _wrapped->message;
    }

    void setMessage( fcml_string message ) {
        this->_wrapped->message = message;
    }

};

class ErrorContainer : public StructureWrapper<fcml_st_ceh_error_container> {
public:

    ErrorContainer(fcml_st_ceh_error_container &wrapped) : StructureWrapper(wrapped) {
        StructureCopy(&wrapped);
        prepareWrappers();
    }
    ErrorContainer(fcml_st_ceh_error_container *wrapped) : StructureWrapper(wrapped) {
        prepareWrappers();
    }
    ErrorContainer( const ErrorContainer &cpy ) : StructureWrapper(cpy) {
        StructureCopy(cpy._wrapped);
        prepareWrappers();
    }

    virtual ~ErrorContainer() {
        freeErrorInfos();
        if(_wrapped && _owner) {
            StructureFree();
        }
    }

public:

    ErrorInfo& getFirstError() {
        if( _errorInfos.size() <= 0 ) {
            throw std::out_of_range("No such error info available.");
        }
        return *_errorInfos[0];
    }

    ErrorInfo& operator[] (int x) {
        if( x < 0 || x >=  static_cast<int>( _errorInfos.size() ) ) {
            throw std::out_of_range("No such error info available.");
        }
        return *_errorInfos[x];
    }

    bool isEmpty() {
        return _errorInfos.size() == 0;
    }

    fcml_usize getSize() {
        return _errorInfos.size();
    }

protected:

    /**
     * Deep copy of the error container.
     */
    void StructureCopy(fcml_st_ceh_error_container *source) {
        fcml_st_ceh_error_info **next = &(_wrapped->errors);
        fcml_st_ceh_error_info *errorInfo = source->errors;
        while( errorInfo ) {
            *next = copyErrorInfo( errorInfo );
            _wrapped->last_error = *next;
            next = &((*next)->next_error);
            errorInfo = errorInfo->next_error;
        }
        *next = NULL;
    }

    /**
     * Deletes all error info structures and the container itself.
     */
    void StructureFree() {
        fcml_st_ceh_error_info *errors = _wrapped->errors;
        while( errors ) {
            fcml_st_ceh_error_info *next = errors->next_error;
            Env::StrFree(errors->message);
            delete errors;
            errors = next;
        }
    }

private:

    void prepareWrappers() {
        if( _wrapped ) {
           freeErrorInfos();
           try {
               fcml_st_ceh_error_info *error = _wrapped->errors;
               while( error ) {
                   _errorInfos.push_back(new ErrorInfo(error));
                   error = error->next_error;
               }
           } catch (const std::exception& ex) {
               // Something failed so free the allocated memory.
               freeErrorInfos();
               throw ex;
           }
       }
    }

    void freeErrorInfos() {
        for( std::vector<ErrorInfo*>::iterator i = _errorInfos.begin(); i != _errorInfos.end(); i++ ) {
            delete *i;
        }
        _errorInfos.clear();
    }

    /**
     * Makes deep copy of the given structure.
     *
     * @param info Structure to be copied.
     * @return Copied structure.
     */
    fcml_st_ceh_error_info *copyErrorInfo(fcml_st_ceh_error_info *info) {
        fcml_st_ceh_error_info *copy = new fcml_st_ceh_error_info;
        *copy = *info;
        copy->message = Env::StrDup(copy->message);
        return copy;
    }

private:
    std::vector<ErrorInfo*> _errorInfos;
};

}

#endif
