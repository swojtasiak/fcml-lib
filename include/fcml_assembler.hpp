#ifndef FCML_ASSEMBLER_HPP_
#define FCML_ASSEMBLER_HPP_

#include "fcml_assembler.h"

#include "fcml_common.hpp"

namespace fcml {

/**
 * A simple wrapper just to set up default values.
 */
struct AssemblerConf: public StructureWrapper<fcml_st_assembler_conf> {

    AssemblerConf() {
    }

    fcml_bool getChooseAbsEncoding() const {
        return _wrapped.choose_abs_encoding;
    }

    void setChooseAbsEncoding( fcml_bool chooseAbsEncoding ) {
        _wrapped.choose_abs_encoding = chooseAbsEncoding;
    }

    fcml_bool getChooseSibEncoding() const {
        return _wrapped.choose_sib_encoding;
    }

    void setChooseSibEncoding( fcml_bool chooseSibEncoding ) {
        _wrapped.choose_sib_encoding = chooseSibEncoding;
    }

    fcml_fnp_asm_instruction_chooser getChooser() const {
        return _wrapped.chooser;
    }

    void setChooser( fcml_fnp_asm_instruction_chooser chooser ) {
        this->_wrapped.chooser = chooser;
    }

    fcml_bool getEnableErrorMessages() const {
        return _wrapped.enable_error_messages;
    }

    void setEnableErrorMessages( fcml_bool enableErrorMessages ) {
        _wrapped.enable_error_messages = enableErrorMessages;
    }

    fcml_bool getForceRexPrefix() const {
        return _wrapped.force_rex_prefix;
    }

    void setForceRexPrefix( fcml_bool forceRexPrefix ) {
        _wrapped.force_rex_prefix = forceRexPrefix;
    }

    fcml_bool getForceThreeByteVex() const {
        return _wrapped.force_three_byte_VEX;
    }

    void setForceThreeByteVex( fcml_bool forceThreeByteVex ) {
        _wrapped.force_three_byte_VEX = forceThreeByteVex;
    }

    fcml_bool getIncrementIp() const {
        return _wrapped.increment_ip;
    }

    void setIncrementIp( fcml_bool incrementIp ) {
        _wrapped.increment_ip = incrementIp;
    }

    fcml_fnp_asm_optimizer getOptimizer() const {
        return _wrapped.optimizer;
    }

    void setOptimizer( fcml_fnp_asm_optimizer optimizer ) {
        this->_wrapped.optimizer = optimizer;
    }

    fcml_uint16_t getOptimizerFlags() const {
        return _wrapped.optimizer_flags;
    }

    void setOptimizerFlags( fcml_uint16_t optimizerFlags ) {
        _wrapped.optimizer_flags = optimizerFlags;
    }

};

class AssemblerResult : public StructureWrapper<fcml_st_assembler_result> {
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
    Assembler( Dialect &dialect, EntryPoint &entryPoint ) :
            _entryPoint( entryPoint ) {
        _context.assembler = NULL;
        _context.entry_point = _entryPoint.GetStruct();
        _context.configuration = _assemblerConf.GetStruct();
        fcml_ceh_error error = fcml_fn_assembler_init( dialect.GetDialect(), &_context.assembler );
        if ( error ) {
            throw InitException( FCML_TEXT( "Can not initialize the assembler." ), error );
        }
    }
    virtual ~Assembler() {
        if ( _context.assembler ) {
            fcml_fn_assembler_free (_context.assembler);
            _context.assembler = NULL;
        }
    }
public:

public:
    AssemblerConf &GetAssemblerConf() {
        return _assemblerConf;
    }
private:
    EntryPoint &_entryPoint;
    AssemblerConf _assemblerConf;
    fcml_st_assembler_context _context;
};

}

#endif //FCML_ASSEMBLER_HPP_
