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

struct ira_intel_format_info {
	// Displacement.
	int show_zero_displacement;
	int show_extended_displacement;
	// If true immediate data is displayed as hex string.
	int immediate_hex_display;
	// If immediate data is displayed as decimal this
	// flag can be used to display signed values.
	int immediate_signed;
	// Flags indicating if whether instruction code should be shown or not.
	int show_instruction_code;
};

void ira_format_intel_instruction( char *buffer, int size, struct ira_disassemble_result *result, struct ira_intel_format_info *format_info );

#endif /* IRA_REN_INTEL_H_ */
