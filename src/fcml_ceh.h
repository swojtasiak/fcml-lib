/*
 * fcml_ceh.h
 *
 *  Created on: 10-03-2013
 *      Author: tAs
 */

#ifndef FCML_CEH_H_
#define FCML_CEH_H_

#include "fcml_types.h"
#include <fcml_errors.h>

fcml_st_ceh_error_container *fcml_fn_ceh_alloc_error_container();
void fcml_fn_ceh_free_errors_only( fcml_st_ceh_error_container *error_container );
void fcml_fn_ceh_free_errors_only_with_level( fcml_st_ceh_error_container *error_container, fcml_en_ceh_error_level level );
void fcml_fn_ceh_free_error_container( fcml_st_ceh_error_container *error_container );
fcml_st_ceh_error_info *fcml_fn_ceh_add_error( fcml_st_ceh_error_container *error_container, const fcml_string message, fcml_ceh_error code, fcml_en_ceh_error_level level );

#endif /* FCML_CEH_H_ */
