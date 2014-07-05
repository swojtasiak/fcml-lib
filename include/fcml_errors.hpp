#ifndef FCML_ASM_ERRORS_HPP_
#define FCML_ASM_ERRORS_HPP_

#include <iterator>
#include <vector>

#include "fcml_types.h"
#include "fcml_errors.h"
#include "fcml_common.hpp"

namespace fcml {

class ErrorInfo : public StructureWrapper<fcml_st_ceh_error_info> {
public:

    ErrorInfo(fcml_st_ceh_error_info &wrapped) {
        _wrapped = wrapped;
        _wrapped->message = Env::StrDup(_wrapped->message);
    }

    ErrorInfo( const ErrorInfo &cpy ) {
        _wrapped = cpy._wrapped;
        _wrapped->message = Env::StrDup(_wrapped->message);
    }

    ErrorInfo& operator=( const ErrorInfo &wrapper ) {
        if( &wrapper != this ) {
            _wrapped = wrapper._wrapped;
            _wrapped->message = Env::StrDup(_wrapped->message);
        }
        return *this;
    }

    ~ErrorInfo() {
        Env::StrFree(_wrapped->message);
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

    ErrorContainer(fcml_st_ceh_error_container &wrapped) {
        // Deep copy the whole structure and populate the vector with error info.
        fcml_st_ceh_error_info **next = &(_wrapped->errors);
        fcml_st_ceh_error_info *errorInfo = wrapped.errors;
        while( errorInfo ) {
            *next = copyErrorInfo( errorInfo );
            _wrapped->last_error = *next;
            next = &((*next)->next_error);
            _errorInfos.push_back(*errorInfo);
            errorInfo = errorInfo->next_error;
        }
        *next = NULL;
    }

    std::vector<ErrorInfo>& getErrors() {
        return _errorInfos;
    }

    fcml_usize getSize() {
        return _errorInfos.size();
    }

    ErrorInfo& operator[](fcml_usize num) {
        return _errorInfos[num];
    }

private:
    fcml_st_ceh_error_info *copyErrorInfo(fcml_st_ceh_error_info *info) {
        fcml_st_ceh_error_info *copy = new fcml_st_ceh_error_info;
        *copy = *info;
        copy->message = Env::StrDup(copy->message);
        return copy;
    }

private:
    std::vector<ErrorInfo> _errorInfos;
};

}

#endif
