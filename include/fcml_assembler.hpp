#ifndef FCML_ASSEMBLER_HPP_
#define FCML_ASSEMBLER_HPP_

#include "fcml_assembler.h"

#include "fcml_common.hpp"

namespace fcml {
/**
 * A simple wrapper just to set up default values.
 */
struct AssemblerConf: public fcml_st_assembler_conf {
    AssemblerConf() {
        increment_ip = FCML_FALSE;
        enable_error_messages = FCML_FALSE;
        choose_sib_encoding = FCML_FALSE;
        choose_abs_encoding = FCML_FALSE;
        force_rex_prefix = FCML_FALSE;
        force_three_byte_VEX = FCML_FALSE;
        optimizer = NULL;
        optimizer_flags = 0;
        chooser = NULL;
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
        _context.entry_point = _entryPoint;
        _context.configuration = AssemblerConf();
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
