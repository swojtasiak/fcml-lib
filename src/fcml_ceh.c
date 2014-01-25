/*
 * fcml_ceh.c
 *
 *  Created on: 10-03-2013
 *      Author: tAs
 */

#include <string.h>
#include "fcml_env.h"
#include "fcml_ceh.h"

void fcml_fn_ceh_free_error_info( fcml_st_ceh_error_info *error_info ) {
	if( error_info ) {
		if( error_info->message ) {
			fcml_fn_env_str_strfree( error_info->message );
			error_info->message = NULL;
		}
		fcml_fn_env_memory_free( error_info );
	}
}

fcml_st_ceh_error_container *fcml_fn_ceh_alloc_error_container() {
	fcml_st_ceh_error_container *error_container = (fcml_st_ceh_error_container*)fcml_fn_env_memory_alloc(sizeof(fcml_st_ceh_error_container));
	if( error_container ) {
		error_container->errors = NULL;
		error_container->last_error = NULL;
	}
	return error_container;
}

void fcml_fn_ceh_free_errors_only( fcml_st_ceh_error_container *error_container ) {
	fcml_st_ceh_error_info* next = error_container->errors ;
	while( next ) {
		fcml_st_ceh_error_info* curr = next;
		next = next->next_error;
		fcml_fn_ceh_free_error_info( curr );
	}
	error_container->errors = NULL;
	error_container->last_error = NULL;
}

void fcml_fn_ceh_free_error_container( fcml_st_ceh_error_container *error_container ) {
	if( error_container ) {
		fcml_fn_ceh_free_errors_only( error_container );
		fcml_fn_env_memory_free( error_container );
	}
}

fcml_st_ceh_error_info *fcml_fn_ceh_alloc_error_info( fcml_string message, fcml_ceh_error_code code, fcml_en_ceh_error_level level ) {
	fcml_st_ceh_error_info *error_info = (fcml_st_ceh_error_info*)fcml_fn_env_memory_alloc_clear(sizeof(fcml_st_ceh_error_info));
	if( error_info ) {
		error_info->message = fcml_fn_env_str_strdup( message );
		if( !error_info->message ) {
			fcml_fn_env_memory_free( error_info );
			return NULL;
		}
		error_info->code = code;
		error_info->level = level;
	}
	return error_info;
}

fcml_st_ceh_error_info *fcml_fn_ceh_add_error( fcml_st_ceh_error_container *error_container, const fcml_string message, fcml_ceh_error_code code, fcml_en_ceh_error_level level ) {
	fcml_st_ceh_error_info *error_info;
	/* Container is null.*/
	if( !error_container ) {
		return NULL;
	}
	error_info = fcml_fn_ceh_alloc_error_info( message, code, level );
	if( !error_info ) {
		return NULL;
	}
	fcml_st_ceh_error_info *last_error = error_container->last_error;
	if( last_error ) {
		last_error->next_error = error_info;
	} else {
		error_container->errors = error_info;
	}
	error_container->last_error = error_info;
	return error_info;
}
