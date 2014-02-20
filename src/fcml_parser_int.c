/*
 * fcml_parser_int.c
 *
 *  Created on: Feb 20, 2014
 *      Author: tas
 */

#include "fcml_parser_int.h"
#include "fcml_messages.h"
#include "fcml_env.h"

fcml_ceh_error fcml_fn_parser_add_symbol_to_symbol_table( fcml_st_ceh_error_container *errors, fcml_coll_map symbol_table, fcml_st_symbol *symbol, fcml_bool allow_override ) {

	fcml_ceh_error error = FCML_COLL_ERROR_NO_ERROR;

	if( !allow_override ) {
		if( fcml_fn_coll_map_get( symbol_table, symbol->symbol ) ) {
			/* Symbol already defined. */
			fcml_char msg_buffer[FCML_PARSER_MAX_INSTRUCTION_LEN * 2];
			fcml_string msg_pattern = fcml_fn_msg_get_message( FCML_MC_SEGMENT_SYMBOL_ALREADY_DEFINED );
			fcml_fn_env_str_snprintf( msg_buffer, sizeof( msg_buffer ), msg_pattern, symbol->symbol );
			fcml_fn_ceh_add_error( errors, (const fcml_string)msg_buffer, FCML_CEH_MEC_ERROR_SYMBOL_ALREADY_DEFINED, FCML_EN_CEH_EL_ERROR );
			error = FCML_CEH_GEC_INVALID_INPUT;
		}
	}

	if( !error ) {
		fcml_int map_error = FCML_COLL_ERROR_NO_ERROR;
		fcml_fn_coll_map_put( symbol_table, symbol->symbol, symbol, &map_error );
		if( map_error ) {
			error = FCML_CEH_GEC_OUT_OF_MEMORY;
		}
	}

	if( error ) {
		fcml_fn_env_str_strfree( symbol->symbol );
		fcml_fn_env_memory_free( symbol );
	}

	return error;
}


