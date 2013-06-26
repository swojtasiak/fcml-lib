/*
 * fcml_ceh.h
 *
 *  Created on: 10-03-2013
 *      Author: tAs
 */

#ifndef FCML_CEH_H_
#define FCML_CEH_H_

#include "fcml_types.h"

/* Global error codes. */

#define FCML_CEH_GEC_NO_ERROR					0
#define FCML_CEH_GEC_UNKNOWN_ERROR				1
#define FCML_CEH_GEC_OUT_OF_MEMORY				2
#define FCML_CEH_GEC_DATA_ERROR					3
#define FCML_CEH_GEC_INTERNAL_BUG				4
#define FCML_CEH_GEC_INVALID_INPUT				5
#define FCML_CEH_GEC_NO_SPACE_LEFT				6
#define FCML_CEH_GEC_NOT_INITIALIZED			7
#define FCML_CEH_GEC_EOF						8
#define FCML_CEH_GEC_VALUE_OUT_OF_RANGE			9
#define FCML_CEH_GEC_ILLEGAL_STATE_EXCEPTION	10
#define FCML_CEH_GEC_NOT_SUPPORTED				11

typedef fcml_uint16_t fcml_ceh_error;

struct fcml_st_coll_list;

#define FCML_CEH_USER_ERROR_CODE_BASE	2000

typedef fcml_uint16_t fcml_ceh_error_code;

typedef enum fcml_en_ceh_error_level {
	FCML_EN_CEH_EL_WARN,
	FCML_EN_CEH_EL_ERROR,
	FCML_EN_CEH_EL_FATAL
} fcml_en_ceh_error_level;

typedef struct fcml_st_ceh_error_info {
	struct fcml_st_ceh_error_info *next_error;
	fcml_string message;
	fcml_ceh_error_code code;
	fcml_en_ceh_error_level level;
} fcml_st_ceh_error_info;

typedef struct fcml_st_ceh_error_container {
	fcml_st_ceh_error_info *errors;
	fcml_st_ceh_error_info *last_error;
} fcml_st_ceh_error_container;

fcml_st_ceh_error_container *fcml_fn_ceh_alloc_error_container();
void fcml_fn_ceh_free_error_container( fcml_st_ceh_error_container *error_container );
fcml_st_ceh_error_info *fcml_fn_ceh_alloc_error_info( const fcml_string message, fcml_ceh_error_code code, fcml_en_ceh_error_level level );
void fcml_fn_ceh_free_error_info( fcml_st_ceh_error_info *error_info );
fcml_st_ceh_error_info *fcml_fn_ceh_add_error( fcml_st_ceh_error_container **error_container, const fcml_string message, fcml_ceh_error_code code, fcml_en_ceh_error_level level );

#endif /* FCML_CEH_H_ */
