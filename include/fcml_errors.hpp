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

/** @file fcml_errors.hpp
 * C++ wrapper for the FCML errors handling.
 *
 * @copyright Copyright (C) 2010-2015 Slawomir Wojtasiak. All rights reserved.
 * This project is released under the GNU Lesser General Public License.
 */

#ifndef FCML_ERRORS_HPP_
#define FCML_ERRORS_HPP_

#include <vector>

#include "fcml_types.h"
#include "fcml_errors.h"
#include "fcml_common.hpp"

namespace fcml {

/**
 * Contains an error message together with error level and error code.
 * @since 1.1.0
 */
class ErrorInfo {
public:

    /** Error level.
     * @since 1.1.0
     */
	enum ErrorLevel {
		EL_ERROR,
		EL_WARN
	};

public:

	/**
	 * Default constructor.
	 * @since 1.1.0
	 */
	ErrorInfo() :
	    _code( FCML_CEH_GEC_NO_ERROR ),
	    _level( EL_ERROR ) {
	}

	/**
	 * Creates an error for given message and optional error code and level.
	 * @param message The error message.
	 * @param code The error code.
	 * @param level The error level.
	 * @since 1.1.0
	 */
	ErrorInfo( const fcml_cstring &message, fcml_ceh_error code = FCML_CEH_GEC_NO_ERROR, ErrorLevel level = EL_ERROR ) :
		_message( message ),
		_code( code ),
		_level( level ) {
	}

public:

	/**
	 * Gets error code.
	 * @return The error code.
	 * @since 1.1.0
	 */
	fcml_ceh_error getCode() const {
		return _code;
	}

	/**
	 * Sets a new error code.
	 * @param code The new error code.
	 * @since 1.1.0
	 */
	void setCode(fcml_ceh_error code) {
		_code = code;
	}

	/**
	 * Gets error level.
	 * @return The error level.
	 * @since 1.1.0
	 */
	ErrorLevel getLevel() const {
		return _level;
	}

	/**
	 * Sets error level.
	 * @param level The error level.
	 * @since 1.1.0
	 */
	void setLevel(ErrorLevel level) {
		_level = level;
	}

	/**
	 * Gets error message.
	 * @return The error message.
	 * @since 1.1.0
	 */
	const fcml_cstring& getMessage() const {
		return _message;
	}

	/**
	 * Sets error message.
	 * @param message The error message.
	 * @since 1.1.0
	 */
	void setMessage(const fcml_cstring& message) {
		_message = message;
	}

private:

	/** Error message. */
	fcml_cstring _message;
	/** Error code */
	fcml_ceh_error _code;
	/** Error level. */
	ErrorLevel _level;

};

/**
 * Wraps multiple errors into one component.
 * @since 1.1.0
 */
class ErrorContainer {
public:

    /**
     * Default constructor.
     * @since 1.1.0
     */
	ErrorContainer() :
	    _isWarn(false),
	    _isError(false) {
	}

	/**
	 * Gets number of errors in the container.
	 * @return The number of errors.
	 * @since 1.1.0
	 */
	fcml_usize getSize() const {
		return static_cast<fcml_usize>( _errorInfos.size() );
	}

	/**
	 * Gets an error at given index.
	 * @param index The error index.
	 * @return The error at given index.
	 * @throw BadArgumentException If index is out of bound.
	 * @since 1.1.0
	 */
	const ErrorInfo& operator[]( fcml_usize index ) const {
		checkVectorAccess( index );
		return _errorInfos[index];
	}

	/**
     * Gets an error at given index.
     * @param index The error index.
     * @return The error at given index.
     * @since 1.1.0
     */
	ErrorInfo& operator[]( fcml_usize index ) {
		checkVectorAccess( index );
		return _errorInfos[index];
	}

	/**
	 * Adds a new error into the container.
	 * @param errorInfo The new error to add.
	 * @since 1.1.0
	 */
	void addErrorInfo( const ErrorInfo &errorInfo ) {
		_errorInfos.push_back(errorInfo);
		switch( errorInfo.getLevel() ) {
		case ErrorInfo::EL_ERROR:
			_isError = true;
			break;
		case ErrorInfo::EL_WARN:
			_isWarn = true;
			break;
		}
	}

	/**
	 * Returns true if there is any error in the container.
	 * @return True if there is any error in the container.
	 * @since 1.1.0
	 */
	bool isError() const {
		return _isError;
	}

	/**
     * Returns true if there is any warning in the container.
     * @return True if there is any warning in the container.
     * @since 1.1.0
     */
	bool isWarn() const {
		return _isWarn;
	}

	/**
	 * Gets true if there is any error or warning in the container.
	 * @return True if there is any error or warning in the container.
	 * @since 1.1.0
	 */
	bool isEmpty() const {
		return _errorInfos.empty();
	}

	/**
	 * Returns the first error from the container.
	 * @return The first error.
	 * @throw IllegalStateException Container is empty.
	 * @since 1.1.0
	 */
	const ErrorInfo& getFirstError() const {
		if( isEmpty() ) {
			throw IllegalStateException( FCML_TEXT( "Container is empty." ) );
		}
		return _errorInfos[0];
	}

	/**
     * Returns the first error from the container.
     * @return The first error.
     * @throw IllegalStateException Container is empty.
     * @since 1.1.0
     */
	ErrorInfo& getFirstError() {
		if( isEmpty() ) {
			throw IllegalStateException( FCML_TEXT( "Container is empty." ) );
		}
		return _errorInfos[0];
	}

	/**
     * Returns the first error message from the container.
     * @return The first error message.
     * @since 1.1.0
     */
	fcml_cstring getFirstErrorMessage() const {
		fcml_cstring message;
		try {
			const ErrorInfo &errorInfo = getFirstError();
			message = errorInfo.getMessage();
		} catch( IllegalStateException &exc ) {
		}
		return message;
	}

	/**
	 * Prepares an error message basing on the first error in the container.
	 * @param message A prefix for the destination error message.
	 * @return Error message.
	 * @since 1.1.0
	 */
	fcml_cstring prepareErrorMessage( const fcml_cstring &message ) const {
		const fcml_cstring errorMessage = getFirstErrorMessage();
		if( errorMessage.empty() ) {
			return message + FCML_TEXT('.');
		} else {
			return message + FCML_TEXT(": ") + errorMessage;
		}
	}

	/**
	 * Cleans all errors and warnings.
	 * @since 1.1.0
	 */
	void clean() {
		_errorInfos.clear();
		_isWarn = false;
		_isError = false;
	}

private:

	/**
	 * Checks bounds of the index.
	 * @param index The index to check.
	 * @throw BadArgumentException Index out of bound.
	 * @since 1.1.0
	 */
	void checkVectorAccess( fcml_usize index ) const {
		if( index >= _errorInfos.size() ) {
			throw BadArgumentException( FCML_TEXT( "Index exceeds the allowed number of error info structures." ) );
		}
	}

private:
	/** Error messages. */
	std::vector<ErrorInfo> _errorInfos;
	/* Sets if there is any warning in the container. */
	bool _isWarn;
	/* Sets if there is any error in the container. */
	bool _isError;
};

/**
 * Types converter.
 * @since 1.1.0
 */
class ErrorTypeConverter {
public:

	static void convert( const fcml_st_ceh_error_container &src, ErrorContainer &dest ) {
		fcml_st_ceh_error_info *error = src.errors;
		while( error ) {
			ErrorInfo::ErrorLevel level = ( error->level == FCML_EN_CEH_EL_ERROR ) ? ErrorInfo::EL_ERROR : ErrorInfo::EL_WARN;
			dest.addErrorInfo( ErrorInfo( error->message, error->code, level ) );
			error = error->next_error;
		}
	}

};

/**
 *  Base class for all exceptions that are aware of ErrorContainer.
 *  @since 1.1.0
 */
class ErrorContainerAwareException: public BaseException {
public:

    /**
     * Creates an error container aware exception instance and sets basic information for it.
     * @param msg An error message.
     * @param errorContainer An error container for exception.
     * @param error An optional FCML error code.
     * @since 1.1.0
     */
	ErrorContainerAwareException( const fcml_cstring &msg, const ErrorContainer &errorContainer, fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR ) :
            BaseException( msg, error ), _errorContainer( errorContainer ) {
    }

	/**
	 * Gets a reference to an error container associated with the exception.
	 * @return The error container.
	 * @since 1.1.0
	 */
	const ErrorContainer& getErrorContainer() const {
		return _errorContainer;
	}

	/**
	 * Sets a new error container for the exception.
	 * @param errorContainer The new error container to be set for the exception.
	 * @since 1.1.0
	 */
	void setErrorContainer(const ErrorContainer& errorContainer) {
		_errorContainer = errorContainer;
	}

private:

	/** A container for errors. */
	ErrorContainer _errorContainer;

};

}

#endif  // FCML_ERRORS_HPP_
