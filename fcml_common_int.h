/*
 * fcml_common_int.h
 *
 *  Created on: 5 wrz 2013
 *      Author: tAs
 */

#ifndef FCML_COMMON_INT_H_
#define FCML_COMMON_INT_H_

#include "fcml_common.h"

typedef enum fcml_en_attribute_size_flag {
    FCML_EN_ASF_ANY = 0x00,
    FCML_EN_ASF_16 = 0x01,
    FCML_EN_ASF_32 = 0x02,
    FCML_EN_ASF_64 = 0x04,
    FCML_EN_ASF_ALL = FCML_EN_ASF_16 | FCML_EN_ASF_32 | FCML_EN_ASF_64
} fcml_en_attribute_size_flag;

struct fcml_st_asm_instruction_part;

typedef struct fcml_st_asm_nullable_size_flags {
    fcml_bool is_set;
    fcml_en_attribute_size_flag flags;
} fcml_st_asm_nullable_size_flags;

fcml_bool fcml_fn_cmi_is_attribute_size_supported( fcml_en_attribute_size_flag flags, fcml_data_size attribute_size );

#endif /* FCML_COMMON_INT_H_ */
