/*
 * ira_def.c
 *
 *  Created on: 19-11-2010
 *      Author: Slawomir Wojtasiak
 */

#include "ira_int.h"

struct ira_opcode_desc _ira_opcode_desc_AAA[] = {
	{ NULL, 0x0001, 0x00540000, { 0x37, 0x00, 0x00 }, _IRA_NA, _IRA_NA, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_AAD[] = {
	{ NULL, 0x0001, 0x00580000, { 0xD5, 0x0A, 0x00 }, _IRA_NA, _IRA_NA, _IRA_NA, _IRA_NA },
	{ NULL, 0x0001, 0x00540000, { 0xD5, 0x00, 0x00 }, _IRA_OPERAND_IB, _IRA_NA, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_AAM[] = {
	{ NULL, 0x0001, 0x00580000, { 0xD4, 0x0A, 0x00 }, _IRA_NA, _IRA_NA, _IRA_NA, _IRA_NA },
	{ NULL, 0x0001, 0x00540000, { 0xD4, 0x00, 0x00 }, _IRA_OPERAND_IB, _IRA_NA, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_AAS[] = {
	{ NULL, 0x0001, 0x00540000, { 0x3F, 0x00, 0x00 }, _IRA_NA, _IRA_NA, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_ADC[] = {
	// 10 /r ADC r/m8, r8 A Valid Valid Add with carry byte register to r/m8.
	{ NULL, 0x01F9, 0x00D48000, { 0x10, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_8_W, _IRA_OPERAND_MODRM_R_8, _IRA_NA, _IRA_NA }
};


struct ira_instruction_desc _ira_instructions_desc[] = {
		{ "aaa", _IRA_IT_IA, 1, _ira_opcode_desc_AAA },
		{ "aad", _IRA_IT_IA, 2, _ira_opcode_desc_AAD },
		{ "aam", _IRA_IT_IA, 2, _ira_opcode_desc_AAM },
		{ "aas", _IRA_IT_IA, 1, _ira_opcode_desc_AAS },
		{ "adc", _IRA_IT_IA, 1, _ira_opcode_desc_ADC },
		{ NULL, 0, 0, NULL }
};


