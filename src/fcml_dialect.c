/*
 * fcml_dialect.c
 *
 *  Created on: Feb 11, 2014
 *      Author: tas
 */

#include <fcml_dialect.h>
#include "fcml_dialect_int.h"

void LIB_CALL fcml_fn_dialect_free( fcml_st_dialect *dialect ) {
	if( dialect ) {
		fcml_st_dialect_context_int *context = (fcml_st_dialect_context_int*)dialect;
		context->free_dialect( dialect );
	}
}

