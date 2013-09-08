/*
 * fcml_common_int.c
 *
 *  Created on: 6 wrz 2013
 *      Author: tAs
 */

#include "fcml_common_int.h"

fcml_bool fcml_fn_cmi_is_attribute_size_supported( fcml_data_size supported_attribute_size, fcml_data_size attribute_size ) {
    if( supported_attribute_size == FCML_DS_UNDEF ) {
        return FCML_TRUE;
    }
    return supported_attribute_size == attribute_size;
}

void fcml_fn_cmi_set_attribute_size_flag_for_size( fcml_data_size attribute_size, fcml_st_asm_nullable_size_flags *flags ) {
    fcml_en_attribute_size_flag flag = 0;
    switch( attribute_size ) {
    case FCML_DS_16:
        flag = FCML_EN_ASF_16;
        break;
    case FCML_DS_32:
        flag = FCML_EN_ASF_32;
        break;
    case FCML_DS_64:
        flag = FCML_EN_ASF_64;
        break;
    }
    if( flag ) {
        flags->flags |= flag;
        flags->is_set = FCML_TRUE;
    }
}
