/*
 * ira_ren.h
 *
 *  Created on: 12-12-2010
 *      Author: Slawomir Wojtasiak
 */

#ifndef IRA_REN_INTEL_H_
#define IRA_REN_INTEL_H_

#include "ira.h"
#include "ira_ren_utils.h"

void ira_format_intel_instruction( char *buffer, int size, struct ira_disassemble_result *result, struct ira_format_info *format_info );

#endif /* IRA_REN_INTEL_H_ */
