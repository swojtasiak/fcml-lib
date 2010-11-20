/*
 * ira_def.c
 *
 *  Created on: 19-11-2010
 *      Author: tAs
 */

#include "ira_int.h"

struct opcode_desc _ira_opcode_desc_AAA[] = {
	{ NULL, 0x0000, 0x00000000, 0, { 0x00, 0x00, 0x00 }, _IRA_NA, _IRA_NA, _IRA_NA, _IRA_NA }
};

struct opcode_desc _ira_opcode_desc_AAD[] = {
	{ NULL, 0x0000, 0x00000000, 0, { 0x00, 0x00, 0x00 }, _IRA_NA, _IRA_NA, _IRA_NA, _IRA_NA }
};

struct instruction_desc _instructions_desc[] = {
		{ "AAA", 1, _ira_opcode_desc_AAA },
		{ "AAD", 1, _ira_opcode_desc_AAD }
};


