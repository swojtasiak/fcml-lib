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

/** @file fcml_stateful_disassembler.hpp
 * Stateful FCML disassembler implementation.
 *
 * @copyright Copyright (C) 2010-2015 Slawomir Wojtasiak. All rights reserved.
 * This project is released under the GNU Lesser General Public License.
 */

#ifndef FCML_STATEFUL_DISASSEMBLER_HPP_
#define FCML_STATEFUL_DISASSEMBLER_HPP_

#include "fcml_disassembler.hpp"
#include "fcml_renderer.hpp"

namespace fcml {

/** Stateful disassembler can be used when you have to disassemble a larger piece of code one instruction by one.
 * It also supports rendering directly using internally managed renderer.
 *
 * @since 1.1.0
 * @remarks This class isn't thread-safe.
 */
class StatefulDisassembler {
public:

    /** Creates a stateful disassembler for given FCML disassembler and context. Rendering support can be enabled optionally.
     * @param disassembler The classic FCML disassembler used to disassemble instructions.
     * @param context The disassembler context.
     * @param enableRendering Enables instruction rendering, which is disabled by default.
     */
    StatefulDisassembler( Disassembler &disassembler, DisassemblerContext &context, bool enableRendering = false ) :
        _disassembler(disassembler),
        _disassemblerContext(context) {
        _renderer = enableRendering ? new Renderer( disassembler.getDialect() ) : NULL;
        // End of line characters to be used when instructions are rendered directly to the output stream.
#if defined(_WIN32)
        _endOfLine = FCML_TEXT( "\r\n" );
#else
        _endOfLine = FCML_TEXT( "\n" );
#endif
    }

    /** Destructor. */
    virtual ~StatefulDisassembler() {
        if( _renderer ) {
            delete _renderer;
        }
    }

    /**
     * Disassembles the next instruction pointed by the disassembler state.
     * @param[out] instruction The destination instruction model.
     * @return A reference to the stateful disassembler.
     * @throws DisassemblingFailedException
     * @since 1.1.0
     */
    StatefulDisassembler& operator >>( Instruction &instruction ) {

        // IP has to be incremented automatically, instruction by instruction.
        DisassemblerConf& config = _disassemblerContext.getDisassemblerConf();
        config.setIncrementIp( true );
        config.setThrowExceptionOnError( true );

        // We don't care about error handling here, because it's disassembler
        // who is responsible for correctly handling it.
        _disassembler.disassemble( _disassemblerContext, _disassemblerResult );

        instruction = _disassemblerResult.getInstruction();

        return *this;

    }

    /**
     * Disassembles the next instruction from the buffer and renders it.
     * @param[out] instruction Destination string for the instruction.
     * @return A reference to the stateful disassembler.
     * @throws DisassemblingFailedException,
     *         IllegalStateException,
     *         RenderingFailedException
     * @since 1.1.0
     */
    StatefulDisassembler& operator >>( fcml_cstring &instruction ) {

        if( !_renderer ) {
            throw IllegalStateException( FCML_TEXT( "Rendering is disabled." ) );
        }

        // IP has to be incremented automatically, instruction by instruction.
        DisassemblerConf& config = _disassemblerContext.getDisassemblerConf();
        config.setIncrementIp( true );
        config.setThrowExceptionOnError( true );

        _disassembler.disassemble( _disassemblerContext, _disassemblerResult );

        _rendererConfig.setThrowExceptionOnError( true );

        _renderer->render( _rendererConfig, _disassemblerResult, instruction );

        return *this;

    }

    /**
     * Disassembles the next instruction from the buffer and renders it directly into the output stream.
     * @param[out] ostream The output stream.
     * @return A reference to the stateful disassembler.
     * @throws DisassemblingFailedException,
     *         IllegalStateException,
     *         RenderingFailedException
     * @since 1.1.0
     */
    StatefulDisassembler& operator >>( fcml_costream &ostream ) {

        fcml_cstring instruction;

        // Render the next instruction into a string.
        *this >> instruction;

        // Appends the instruction into an output stream.
        ostream << instruction << _endOfLine;

        return *this;

    }

    /**
     * Gets renderer configuration used by the instruction buffer.
     * @return The renderer configuration.
     * @since 1.1.0
     */
    RenderConfig& getRendererConfig() {
        return _rendererConfig;
    }

    /**
     * Gets renderer configuration used by the internally managed instruction renderer.
     * @return The renderer configuration.
     * @since 1.1.0
     */
    const RenderConfig& getRendererConfig() const {
        return _rendererConfig;
    }

    /**
     * Gets end of line characters sequence used by the renderer.
     *
     * @return End of line characters sequence used by the renderer.
     * @since 1.1.0
     */
    const fcml_cstring& getEndOfLine() const {
        return _endOfLine;
    }

    /**
     * Sets dedicated end of line characters.
     *
     * @param endOfLine A sequence of characters used as line ending.
     * @since 1.1.0
     */
    void setEndOfLine(const fcml_cstring& endOfLine) {
        _endOfLine = endOfLine;
    }

private:

    /** End of line character sequence. */
    fcml_cstring _endOfLine;
    /** Disassembler result used when disassembling instructions. */
    DisassemblerResult _disassemblerResult;
    /** The disassembler used to disassemble the code. */
    Disassembler &_disassembler;
    /** Disassembler context pointing to the machine code. */
    DisassemblerContext &_disassemblerContext;
    /** Renderer configuration used when instructions have to be rendered. */
    RenderConfig _rendererConfig;
    /** Optional renderer used only when instructions are rendered. */
    Renderer *_renderer;

};

}

#endif /* FCML_STATEFUL_DISASSEMBLER_HPP_ */
