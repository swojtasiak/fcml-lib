/*
 * FCML - Free Code Manipulation Library.
 * Copyright (C) 2010-2014 Slawomir Wojtasiak
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

/** @file fcml_renderer.hpp
 * C++ wrapper for FCML renderer.
 *
 * @copyright Copyright (C) 2010-2014 Slawomir Wojtasiak. All rights reserved.
 * This project is released under the GNU Lesser General Public License.
 */

#ifndef FCML_RENDERER_HPP_
#define FCML_RENDERER_HPP_

#include "fcml_common.hpp"
#include "fcml_disassembler.hpp"
#include "fcml_renderer.h"

namespace fcml {

/**
 *  Component can not be initialized correctly.
 */
class RenderingFailedException: public BaseException {
public:
    RenderingFailedException( const fcml_cstring &msg, fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR ) :
        BaseException( msg,  error ){
    }
};

/** Renderer configuration.
 *
 * It's a counterpart to the fcml_st_render_config structure.
 * @since 1.1.0
 */
class RenderConfig {
public:

    /**
     * Creates an empty renderer configuration.
     * @since 1.1.0
     */
    RenderConfig() :
        _throwExceptionOnError(true),
        _renderFlags(0),
        _preferedMnemonicPadding(FCML_REND_DEFAULT_MNEMONIC_PADDING),
        _preferedCodePadding(FCML_REND_DEFAULT_CODE_PADDING) {
    }

    /**
     * Creates a renderer configuration for given renderer flags.
     *
     * @param renderFlags The renderer flags.
     * @since 1.1.0
     */
    RenderConfig( fcml_uint32_t renderFlags ) :
        _throwExceptionOnError(true),
        _renderFlags(renderFlags),
        _preferedMnemonicPadding(0),
        _preferedCodePadding(0) {
    }

    /** @since 1.1.0 */
    fcml_uint16_t getPreferedCodePadding() const {
        return _preferedCodePadding;
    }

    /** @since 1.1.0 */
    void setPreferedCodePadding(fcml_uint16_t preferedCodePadding) {
        _preferedCodePadding = preferedCodePadding;
    }

    /** @since 1.1.0 */
    fcml_uint16_t getPreferedMnemonicPadding() const {
        return _preferedMnemonicPadding;
    }

    /** @since 1.1.0 */
    void setPreferedMnemonicPadding(fcml_uint16_t preferedMnemonicPadding) {
        _preferedMnemonicPadding = preferedMnemonicPadding;
    }

    /** @since 1.1.0 */
    fcml_uint32_t getRenderFlags() const {
        return _renderFlags;
    }

    /** @since 1.1.0 */
    void setRenderFlags(fcml_uint32_t renderFlags) {
        _renderFlags = renderFlags;
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

    /** Throws exception in case of error. */
    bool _throwExceptionOnError;
    /** Flags which allows to control rendering process. */
    fcml_uint32_t _renderFlags;
    /** Preferred mnemonic padding in characters. */
    fcml_uint16_t _preferedMnemonicPadding;
    /** Preferred code padding in HEX bytes (2 characters on one byte.). */
    fcml_uint16_t _preferedCodePadding;

};

/**
 * Converts objects to their structures counterparts.
 * @since 1.1.0
 * @remarks Internal API, not intended to be used outside.
 */
class RenderTypeConverter {
public:

    static void convert( const RenderConfig &src, fcml_st_render_config &dest ) {
        dest.prefered_code_padding = src.getPreferedCodePadding();
        dest.prefered_mnemonic_padding = src.getPreferedMnemonicPadding();
        dest.render_flags = src.getRenderFlags();
    }

};

/** Renderer wrapper.
 * @since 1.1.0
 */
class Renderer: protected DialectAware {
public:

    /**
     * Creates a renderer instance for the given dialect.
     *
     * @param dialect The dialect instance.
     * @since 1.1.0
     */
    Renderer( Dialect &dialect ) :
        _dialect( dialect ) {
    }

    /**
     * Renders a disassembled instruction.
     *
     * @param renderConfig A renderer configuration.
     * @param assemblerResult The disassembler result.
     * @param[out] result The rendered instruction.
     * @throw RenderingFailedException Rendering failed.
     * @return The error code.
     */
    fcml_ceh_error render( const RenderConfig &renderConfig, DisassemblerResult &assemblerResult, fcml_cstring &result ) {

        result.clear();

        fcml_st_render_config render_config;
        RenderTypeConverter::convert( renderConfig, render_config );

        fcml_st_disassembler_result disassembler_result;
        DisassemblerTypeConverter::convert( assemblerResult, disassembler_result );

        fcml_char buffer[FCML_REND_MAX_BUFF_LEN];

        fcml_ceh_error error = ::fcml_fn_render( extractDialect( _dialect ), &render_config, buffer, FCML_REND_MAX_BUFF_LEN, &disassembler_result );

        DisassemblerTypeConverter::free( disassembler_result );

        if( error && renderConfig.isThrowExceptionOnError() ) {
            throw RenderingFailedException( FCML_TEXT( "Can not render instruction." ), error );
        }

        result = buffer;

        return error;
    }

private:

    /** The dialect instance associated with the renderer. */
    Dialect &_dialect;

};

}

#endif /* FCML_RENDERER_HPP_ */
