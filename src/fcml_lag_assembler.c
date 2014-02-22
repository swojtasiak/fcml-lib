/*
 * fcml_lag_assembler.c
 *
 *  Created on: Feb 22, 2014
 *      Author: tas
 */

#include <fcml_lag_assembler.h>
#include "fcml_env.h"

void LIB_CALL fcml_fn_lag_assembler_result_prepare( fcml_st_lag_assembler_result *result ) {
	if( result ) {
		fcml_fn_env_memory_clear( result, sizeof( fcml_st_lag_assembler_result ) );
	}
}

fcml_ceh_error LIB_CALL fcml_fn_lag_assemble( fcml_st_assembler_context *context, const fcml_string *source_code, fcml_st_lag_assembler_result *result ) {
	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
	return error;
}

void LIB_CALL fcml_fn_lag_assembler_result_free( fcml_st_lag_assembler_result *result ) {

}



