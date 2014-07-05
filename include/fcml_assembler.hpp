#ifndef FCML_ASSEMBLER_HPP_
#define FCML_ASSEMBLER_HPP_

#include "fcml_assembler.h"

#include "fcml_common.hpp"

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
    EntryPoint &GetEntryPoint() {
        return _entryPoint;
    }
    AssemblerConf &GetAssemblerConf() {
        return _assemblerConfig;
    }
private:
    // Configuration wrapper.
    AssemblerConf _assemblerConfig;
    // Entry point wrapper.
    EntryPoint _entryPoint;
};

class AssemblerResult: public StructureWrapper<fcml_st_assembler_result> {
public:
    AssemblerResult() {
    }
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
    AssemblerResult &assemble( AssemblerContext &ctx, AssemblerResult &result ) {
        return result;
    }
private:
    // A dialect used by the assembler.
    Dialect &_dialect;
    // An initialized assembler instance.
    fcml_st_assembler *_assembler;
};

}

#endif //FCML_ASSEMBLER_HPP_
