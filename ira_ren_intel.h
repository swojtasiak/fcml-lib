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

enum ira_conditional_suffix_group {
	_IRA_CONDITIONAL_SUFFIX_GROUP_0,
	_IRA_CONDITIONAL_SUFFIX_GROUP_1
};

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
	// Show extended immediate value.
	int show_extended_immediate;
	// Group of conditional suffixes.
	enum ira_conditional_suffix_group conditional_suffix_group;
	// Show mnemonics for carry flags.
	int show_conditional_mnemonics_for_carry_flag;
};

void ira_format_intel_instruction( char *buffer, int size, struct ira_disassemble_result *result, struct ira_intel_format_info *format_info );

#endif /* IRA_REN_INTEL_H_ */
