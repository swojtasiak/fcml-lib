#ifndef FCML_ASSEMBLER_HPP_
#define FCML_ASSEMBLER_HPP_

#include <vector>

#include "fcml_assembler.h"

#include "fcml_common.hpp"
#include "fcml_errors.hpp"

namespace fcml {

/**
 * A simple wrapper just to set up default values.
 */
struct AssemblerConf: public StructureWrapper<fcml_st_assembler_conf> {

    AssemblerConf() {}

    /**
     * Wraps the given structure into the object.
     */
    AssemblerConf( fcml_st_assembler_conf *wrapped ) : StructureWrapper(wrapped) { }

    /**
     * Wraps a copy of the given structure into the object.
     */
    AssemblerConf( fcml_st_assembler_conf &wrapped ) : StructureWrapper(wrapped) { }

    fcml_bool getChooseAbsEncoding() const {
        return _wrapped->choose_abs_encoding;
    }

    void setChooseAbsEncoding( fcml_bool chooseAbsEncoding ) {
        _wrapped->choose_abs_encoding = chooseAbsEncoding;
    }

    fcml_bool getChooseSibEncoding() const {
        return _wrapped->choose_sib_encoding;
    }

    void setChooseSibEncoding( fcml_bool chooseSibEncoding ) {
        _wrapped->choose_sib_encoding = chooseSibEncoding;
    }

    fcml_fnp_asm_instruction_chooser getChooser() const {
        return _wrapped->chooser;
    }

    void setChooser( fcml_fnp_asm_instruction_chooser chooser ) {
        this->_wrapped->chooser = chooser;
    }

    fcml_bool getEnableErrorMessages() const {
        return _wrapped->enable_error_messages;
    }

    void setEnableErrorMessages( fcml_bool enableErrorMessages ) {
        _wrapped->enable_error_messages = enableErrorMessages;
    }

    fcml_bool getForceRexPrefix() const {
        return _wrapped->force_rex_prefix;
    }

    void setForceRexPrefix( fcml_bool forceRexPrefix ) {
        _wrapped->force_rex_prefix = forceRexPrefix;
    }

    fcml_bool getForceThreeByteVex() const {
        return _wrapped->force_three_byte_VEX;
    }

    void setForceThreeByteVex( fcml_bool forceThreeByteVex ) {
        _wrapped->force_three_byte_VEX = forceThreeByteVex;
    }

    fcml_bool getIncrementIp() const {
        return _wrapped->increment_ip;
    }

    void setIncrementIp( fcml_bool incrementIp ) {
        _wrapped->increment_ip = incrementIp;
    }

    fcml_fnp_asm_optimizer getOptimizer() const {
        return _wrapped->optimizer;
    }

    void setOptimizer( fcml_fnp_asm_optimizer optimizer ) {
        this->_wrapped->optimizer = optimizer;
    }

    fcml_uint16_t getOptimizerFlags() const {
        return _wrapped->optimizer_flags;
    }

    void setOptimizerFlags( fcml_uint16_t optimizerFlags ) {
        _wrapped->optimizer_flags = optimizerFlags;
    }

};

class AssembledInstruction: public StructureWrapper<fcml_st_assembled_instruction> {
public:
    AssembledInstruction( fcml_st_assembled_instruction *wrapped ) : StructureWrapper( wrapped ) {
    }
};

class AssemblerResult: public StructureWrapper<fcml_st_assembler_result> {
public:
    AssemblerResult() : _errorContainer(&(_wrapped->errors)), _managed(false) {
        fcml_fn_assembler_result_prepare( _wrapped );
        prepareAssembledInstructions();
    }
    ~AssemblerResult() {
        cleanAssemblerResult();
        if( _managed ) {
            fcml_fn_assembler_result_free( _wrapped );
        }
    }

    // Assembler is allowed to call setManaged.
    friend class Assembler;

public:

    AssembledInstruction &operator[](int i) {
        if( i < 0 || i >= static_cast<int>(_assembledInstructions.size())) {
            throw std::out_of_range("No such an assembled instruction available.");
        }
        WrapperPtr<AssembledInstruction> &wrapperPtr = _assembledInstructions[i];
        return *wrapperPtr.getWrapped();
    }

    fcml_usize getNumberOfInstructions() {
        return _wrapped->number_of_instructions;
    }

    const AssembledInstruction *getChoosenInstruction() const {
        return _choosenInstruction;
    }

    const ErrorContainer &getErrorContainer() const {
        return _errorContainer;
    }

    void cleanAssemblerResult() {
        if( _wrapped && _managed ) {
            fcml_fn_assembler_result_free( _wrapped );
        }
    }

protected:

    void setManaged() {
        // Update assembled insteruction list.
        prepareAssembledInstructions();
        // Update errors container.
        _errorContainer = &(_wrapped->errors);
        // Result structure is managed now and have to be freed when needed.
        _managed = FCML_TRUE;
    }

private:
    void prepareAssembledInstructions() {
        _assembledInstructions.clear();
        if( _wrapped->number_of_instructions ) {
            fcml_st_assembled_instruction *instruction = _wrapped->instructions;
            while( instruction ) {
                AssembledInstruction *current = new AssembledInstruction(instruction);
                _assembledInstructions.push_back( current );
                if( instruction == _wrapped->chosen_instruction ) {
                    _choosenInstruction = current;
                }
                instruction = instruction->next;
            }
        }
    }
private:
    // Array of assembled instructions.
    std::vector< WrapperPtr<AssembledInstruction> > _assembledInstructions;
    // Pointer to the chosen instruction container.
    AssembledInstruction *_choosenInstruction;
    // Wraps original errors container.
    ErrorContainer _errorContainer;
    // True if it holds managed structure which should be freed when object is destroyed.
    bool _managed;
};

class Assembler;

/**
 * Holds a state used by the assembler to perform the assembling process. Thanks to the
 * class assemblers are thread-safe and do not need to store any states. take into account
 * that this class does not manage the assembler instance available in the original structure. It's
 * because the appropriate assembler is set just before the assembler is being called.
 */
struct AssemblerContext: public StructureWrapper<fcml_st_assembler_context> {
public:
    AssemblerContext() :
            _assemblerConfig( &_wrapped->configuration ), _entryPoint( &_wrapped->entry_point ) {
    }
    AssemblerContext(EntryPoint &entryPoint) :
            _assemblerConfig( &_wrapped->configuration ), _entryPoint( &_wrapped->entry_point ) {
        // Override the default entry point. The structures are copied here.
        _entryPoint = entryPoint;
    }
public:
    EntryPoint &getEntryPoint() {
        return _entryPoint;
    }
    AssemblerConf &getAssemblerConf() {
        return _assemblerConfig;
    }
protected:
    friend class Assembler;
    void setAssembler( fcml_st_assembler *assembler ) {
        _wrapped->assembler = assembler;
    }
private:
    // Configuration wrapper.
    AssemblerConf _assemblerConfig;
    // Entry point wrapper.
    EntryPoint _entryPoint;
};

/**
 * An assembler wrapper, as you can see the assembler context is managed internally and
 * is not exposed outside.
 */
class Assembler: public NonCopyable {
public:
    Assembler( Dialect &dialect ) : _dialect(dialect) {
        fcml_ceh_error error = ::fcml_fn_assembler_init( dialect.GetDialect(), &_assembler );
        if ( error ) {
            throw InitException( FCML_TEXT( "Can not initialize the assembler." ), error );
        }
    }
    virtual ~Assembler() {
        if ( _assembler ) {
            ::fcml_fn_assembler_free( _assembler );
            _assembler = NULL;
        }
    }
public:
    fcml_ceh_error assemble( AssemblerContext &ctx, Instruction &instruction, AssemblerResult &result ) {
        ctx.setAssembler(_assembler);
        fcml_ceh_error error =  ::fcml_fn_assemble(&ctx.getStruct(), &instruction.getStruct(), &result.getStruct() );
        result.setManaged();
        return error;
    }
private:
    // A dialect used by the assembler.
    Dialect &_dialect;
    // An initialized assembler instance.
    fcml_st_assembler *_assembler;
};

}

#endif //FCML_ASSEMBLER_HPP_
