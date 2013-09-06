/*
 * fcml_common_int.c
 *
 *  Created on: 6 wrz 2013
 *      Author: tAs
 */

#include "fcml_common_int.h"

fcml_bool fcml_fn_cmi_is_attribute_size_supported( fcml_en_attribute_size_flag flags, fcml_data_size attribute_size ) {
    fcml_bool supported = FCML_FALSE;
    switch( attribute_size ) {
    case FCML_DS_16:
        supported = flags & FCML_EN_ASF_16;
        break;
    case FCML_DS_32:
        supported = flags & FCML_EN_ASF_32;
        break;
    case FCML_DS_64:
        supported = flags & FCML_EN_ASF_64;
        break;
    }
    return supported;
}
