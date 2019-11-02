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

/** @file fcml_stateful_assembler.hpp
 * Stateful FCML assembler implementation.
 *
 * @copyright Copyright (C) 2010-2015 Slawomir Wojtasiak. All rights reserved.
 * This project is released under the GNU Lesser General Public License.
 */

#ifndef FCML_STATEFUL_ASSEMBLER_HPP_
#define FCML_STATEFUL_ASSEMBLER_HPP_

#include <vector>

#include "fcml_assembler.hpp"
#include "fcml_parser.hpp"

namespace fcml {

/**
 * It's a stateful assembler which can be used to assemble instructions one by
 * one on the fly. By default is works with the general instruction models as
 * well as with instruction builders, but it can be also configured to parse
 * whole statements using internally managed parser. It holds it's own state,
 * so it's not necessary to update instruction pointer etc while it's working.
 * Assembled instructions are placed inside a dedicated vector, but generated
 * machine code is accessing
 * directly by the dedicated CodeIterator.
 *
 * @since 1.1.0
 * @remarks This class isn't thread-safe.
 */
class StatefulAssembler {
public:

    /** Used only to indicate the need of the flush operation. */
    class SAFlush {
    };

    /**
     * Creates a stateful assembler for the given assembler and assembler
     * context. Bear in mind that assembler and context are not copied in
     * any way and have to be valid as long as the stateful assembler in in
     * use. Parsing support can be enabled optionally using the third parameter.
     *
     * @param assembler The assembled that will be used to assemble the code.
     * @param context The assembler context.
     * @param enableParser Enables parsing support.
     * @since 1.1.0
     */
    StatefulAssembler(Assembler &assembler, AssemblerContext &context,
            bool enableParser = false) :
            _instructionBuilder(IB(FCML_TEXT("")), false),
            _assembler(assembler),
            _context(context),
            _codeLength(0) {
        // Create parser if needed.
        _parser = enableParser ? new Parser(assembler.getDialect()) : NULL;
    }

    /** Destructor.
     * @since 1.1.0
     */
    virtual ~StatefulAssembler() {
        if (_parser) {
            delete _parser;
        }
    }

    /**
     * Adds instruction builder to the stateful assembler. Such a instruction
     * builder will be used then to assemble an instruction it represents.
     * Before any operation is performed, pending instruction is flushed if
     * there is any available.
     *
     * @param ib The instruction builder to be flushed.
     * @return The stateful assembler itself.
     * @throw AssemblingFailedException
     * @since 1.1.0
     */
    StatefulAssembler& operator <<(const IB &ib) {
        return add(ib);
    }

    /**
     * Adds instruction builder to the stateful assembler. Such a instruction
     * builder will be used then to assemble an instruction it represents.
     * Before any operation is performed, pending instruction is flushed if
     * there is any available.
     *
     * @param ib The instruction builder to be flushed.
     * @return The stateful assembler itself.
     * @throw AssemblingFailedException
     * @since 1.1.0
     */
    StatefulAssembler& add(const IB &ib) {
        flush();
        _instructionBuilder.setNotNull(true);
        _instructionBuilder.setValue(ib);
        return *this;
    }

    /**
     * Creates an instruction builder for the given mnemonic.
     *
     * @param mnemonic The instruction mnemonic.
     * @return The stateful assembler itself.
     * @throw AssemblingFailedException, ParsingFailedException
     * @since 1.1.0
     */
    StatefulAssembler& operator <<(const fcml_cstring &mnemonic) {
        return inst(mnemonic);
    }

    /**
     * Creates an instruction builder for the given mnemonic.
     *
     * @param mnemonic The instruction mnemonic.
     * @return The stateful assembler itself.
     * @throw AssemblingFailedException, ParsingFailedException
     * @since 1.1.0
     */
    StatefulAssembler& inst(const fcml_cstring &mnemonic) {
        flush();
        if (_parser) {
            // Parse instruction and then pass it to the assembler.
            _parserContext.setIp(_context.getEntryPoint().getIP());
            ParserConfig &config = _parserContext.getConfig();
            config.setThrowExceptionOnError(true);
            _parser->parse(_parserContext, mnemonic, _parserResult);
            *this << _parserResult.getInstruction();
        } else {
            // Parser is not available, so treat this string as a full
            // instruction which have to be parsed.
            _instructionBuilder.setNotNull(true);
            _instructionBuilder.setValue(IB(mnemonic));
        }
        return *this;
    }

    /**
     * Adds the new register operand to the instruction builder associated
     * with the buffer.
     *
     * @param reg The register.
     * @return The stateful assembler itself.
     * @throw IllegalStateException
     * @since 1.1.0
     */
    StatefulAssembler& operator <<(const Register &reg) {
        return op(Operand(reg));
    }

    /**
     * Adds the new immediate operand to the instruction builder associated
     * with the buffer.
     *
     * @param imm The immediate value.
     * @return The stateful assembler itself.
     * @throw IllegalStateException
     * @since 1.1.0
     */
    StatefulAssembler& operator <<(const Integer &imm) {
        return op(Operand(imm));
    }

    /**
     * Adds the new address operand to the instruction builder associated
     * with the buffer.
     *
     * @param address The address.
     * @return The stateful assembler itself.
     * @throw IllegalStateException
     * @since 1.1.0
     */
    StatefulAssembler& operator <<(const Address &address) {
        return op(Operand(address));
    }

    /**
     * Adds the new far pointer operand to the instruction builder associated
     * with the buffer.
     *
     * @param pointer The far pointer.
     * @return The stateful assembler itself.
     * @throw IllegalStateException
     * @since 1.1.0
     */
    StatefulAssembler& operator <<(const FarPointer &pointer) {
        return op(Operand(pointer));
    }

    /**
     * Adds an operand to the instruction builder associated with the buffer.
     *
     * @param operand The operand to be added.
     * @return The stateful assembler itself.
     * @throw IllegalStateException
     * @since 1.1.0
     */
    StatefulAssembler& operator <<(const Operand &operand) {
        return op(operand);
    }

    /**
     * Adds an operand to the instruction builder associated with the buffer.
     *
     * @param operand The operand to be added..
     * @return The stateful assembler itself.
     * @throw IllegalStateException
     * @since 1.1.0
     */
    StatefulAssembler& op(const Operand &operand) {
        if (!_instructionBuilder.isNotNull()) {
            throw IllegalStateException(
                    FCML_TEXT("No instruction builder available."));
        }
        IB &ib = _instructionBuilder.getValue();
        ib.op(operand);
        return *this;
    }

    /**
     * Adds the new register operand to the instruction builder associated
     * with the buffer.
     *
     * @param reg The register.
     * @return The stateful assembler itself.
     * @throw IllegalStateException
     * @since 1.1.0
     */
    StatefulAssembler& op(const Register &reg) {
        return op(Operand(reg));
    }

    /**
     * Adds the new immediate operand to the instruction builder associated
     * with the buffer.
     *
     * @param imm The immediate value.
     * @return The stateful assembler itself.
     * @throw IllegalStateException
     * @since 1.1.0
     */
    StatefulAssembler& op(const Integer &imm) {
        return op(Operand(imm));
    }

    /**
     * Adds the new address operand to the instruction builder associated
     * with the buffer.
     *
     * @param address The address.
     * @return The stateful assembler itself.
     * @throw IllegalStateException
     * @since 1.1.0
     */
    StatefulAssembler& op(const Address &address) {
        return op(Operand(address));
    }

    /**
     * Adds the new far pointer operand to the instruction builder associated
     * with the buffer.
     *
     * @param pointer The far pointer.
     * @return The stateful assembler itself.
     * @throw IllegalStateException
     * @since 1.1.0
     */
    StatefulAssembler& op(const FarPointer &pointer) {
        return op(Operand(pointer));
    }

    /**
     * Flushes the instruction builder.
     * @param indic Flush indicator.
     * @return The stateful assembler itself.
     * @throw AssemblingFailedException
     * @since 1.1.0
     */
    StatefulAssembler& operator <<(const SAFlush &indic) {
        flush();
        return *this;
    }

    /**
     * Assembles an instruction in the given instruction builder.
     *
     * @param instruction Instruction to be assembled.
     * @return Stateful assembler.
     * @throw AssemblingFailedException
     * @since 1.1.0
     */
    StatefulAssembler& operator <<(const Instruction &instruction) {
        return inst(instruction);
    }

    /**
     * Adds a prefix to the instruction being built.
     * @param prefix The prefix to be added.
     * @return The instruction builder with the new prefix set for it.
     * @since 1.1.0
     */
    StatefulAssembler& operator <<(const InstructionPrefix &prefix) {
        return set(prefix);
    }

    /**
     * Adds an instruction level hint to the instruction being built.
     * @param hint The hint to be added.
     * @return The instruction builder with the new hint added to it.
     * @since 1.1.0
     */
    StatefulAssembler& operator <<(const InstructionHint &hint) {
        return set(hint);
    }

    /**
     * Adds an operand level hint to the instruction being built.
     * @param hint The hint to be added.
     * @return The instruction builder with the new hint added to it.
     * @since 1.1.0
     */
    StatefulAssembler& operator <<(const OperandHint &hint) {
        return set(hint);
    }

    /**
     * Adds a prefix to the instruction being built.
     * @param prefix The prefix to be added.
     * @return The instruction builder with the new prefix set for it.
     * @since 1.1.0
     */
    StatefulAssembler& set(const InstructionPrefix &prefix) {
        if (!_instructionBuilder.isNotNull()) {
            throw IllegalStateException(
                    FCML_TEXT("No instruction builder available."));
        }
        _instructionBuilder.getValue() << prefix;
        return *this;
    }

    /**
     * Adds an instruction level hint to the instruction being built.
     * @param hint The hint to be added.
     * @return The instruction builder with the new hint added to it.
     * @since 1.1.0
     */
    StatefulAssembler& set(const InstructionHint &hint) {
        if (!_instructionBuilder.isNotNull()) {
            throw IllegalStateException(
                    FCML_TEXT("No instruction builder available."));
        }
        _instructionBuilder.getValue() << hint;
        return *this;
    }

    /**
     * Adds an operand level hint to the instruction being built.
     * @param hint The hint to be added.
     * @return The instruction builder with the new hint added to it.
     * @since 1.1.0
     */
    StatefulAssembler& set(const OperandHint &hint) {
        if (!_instructionBuilder.isNotNull()) {
            throw IllegalStateException(
                    FCML_TEXT("No instruction builder available."));
        }
        _instructionBuilder.getValue() << hint;
        return *this;
    }

    /**
     * Assembles an instruction in the given instruction builder.
     *
     * @param instruction Instruction to be assembled.
     * @return Stateful assembler.
     * @throw AssemblingFailedException
     * @since 1.1.0
     */
    StatefulAssembler& inst(const Instruction &instruction) {

        // Flush pending instruction if there is any.
        flush();

        // Just in case.
        AssemblerConf &config = _context.getConfig();
        config.setIncrementIp(true);
        config.setThrowExceptionOnError(true);

        // Assembler the instruction.
        _assembler.assemble(_context, instruction, _result);

        // Store the chosen assembled instruction for future use.
        const AssembledInstruction *assembledInstruction =
                _result.getChosenInstruction();
        if (assembledInstruction) {
            _assembledInstructions.push_back(*assembledInstruction);
            _codeLength += assembledInstruction->getCodeLength();
        } else {
            throw AssemblingFailedException(
                    FCML_TEXT("Chosen instruction hasn't been set. It seems "
                            "that the instruction chooser isn't working "
                            "correctly."));
        }

        return *this;
    }

    /**
     * Gets iterator which allows to iterate through the whole machine
     * code byte by byte.
     *
     * @return Iterator instance.
     * @since 1.1.0
     */
    CodeIterator getCodeIterator() {
        flush();
        return CodeIterator(_assembledInstructions);
    }

    /**
     * Gets all chosen assembled instructions.
     *
     * @return All assembled instructions available in the buffer.
     * @since 1.1.0
     */
    std::vector<AssembledInstruction>& getAssembledInstructions() {
        flush();
        return _assembledInstructions;
    }

    /**
     * Gets the code length of all assembled instructions available.
     *
     * @return The code length.
     * @since 1.1.0
     */
    fcml_usize getCodeLength() {
        flush();
        return _codeLength;
    }

    /**
     * Assembles all pending instructions.
     * @since 1.1.0
     * @throw AssemblingFailedException
     */
    void flush() {
        if (_instructionBuilder.isNotNull()) {
            // Build an instruction using the instruction builder.
            Instruction instruction = _instructionBuilder.getValue().build();
            // And clean the builder, is everything succeed.
            _instructionBuilder.setNotNull(false);
            // Assemble the instruction.
            *this << instruction;
        }
    }

    /**
     * Creates flush indicated for "shift" operators.
     * @return Flush indicator.
     * @since 1.1.0
     */
    static SAFlush FLUSH() {
        return SAFlush();
    }

    /** Gets configuration used by parser if parsing is supported.
     * @return Parser configuration.
     */
    const ParserConfig& getParserConfig() const {
        return _parserContext.getConfig();
    }

    /** Gets configuration used by parser if parsing is supported.
     * @return Parser configuration.
     * @since 1.1.0
     */
    ParserConfig& getParserConfig() {
        return _parserContext.getConfig();
    }

    /**
     * Gets symbol table used together with the parser.
     * @return The symbol table used by the parser.
     * @since 1.1.0
     */
    const SymbolTable* getSymbolTable() const {
        return _parserContext.getSymbolTable();
    }

    /**
     * Gets symbol table used together with the parser.
     * @return The symbol table used by the parser.
     * @since 1.1.0
     */
    SymbolTable* getSymbolTable() {
        return _parserContext.getSymbolTable();
    }

    /**
     * Sets a new symbol table for the parser.
     * @param symbolTable The new symbol table.
     * @since 1.1.0
     */
    void setSymbolTable(SymbolTable *symbolTable) {
        _parserContext.setSymbolTable(symbolTable);
    }

private:

    /** An instruction parser. */
    Parser *_parser;
    /** Parser result used when parsing is supported. */
    ParserResult _parserResult;
    /** Parser context. */
    ParserContext _parserContext;
    /** A disassembled result used by the assembler when needed. */
    AssemblerResult _result;
    /** Currently used instruction builder. */
    Nullable<IB> _instructionBuilder;
    /* Assembler used to assemble code. */
    Assembler &_assembler;
    /** Assembler context. */
    AssemblerContext &_context;
    // Assembled instructions.
    std::vector<AssembledInstruction> _assembledInstructions;
    /** Length of the code assembled so far. */
    fcml_usize _codeLength;

};

}

#endif /* FCML_STATEFUL_ASSEMBLER_HPP_ */
