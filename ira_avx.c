/*
 * ira_avx.c
 *
 *  Created on: 18-11-2012
 *      Author: tAs
 */

#include "ira_avx.h"

uint8_t _ira_escape_0f[] = {0x0F};
uint8_t _ira_escape_0f38[] = {0x0F, 0x38};
uint8_t _ira_escape_0f3A[] = {0x0F, 0x3A};

uint8_t *_ira_escape_opcode_table[3] = {_ira_escape_0f, _ira_escape_0f38, _ira_escape_0f3A};
uint8_t _ira_escape_size_table[] = {1,2,2};

uint8_t *_ira_avx_decode_escape_opcode_bytes( struct ira_decoding_context *decoding_context, uint8_t *number_of_opcode_bytes ) {
	struct ira_decoded_fields *prefixes_fields = &(decoding_context->prefixes_fields);
	uint8_t *escape;
	if( prefixes_fields->vex_prefix == 0xC4 ) {
		int index = prefixes_fields->mmmm - 1;
		escape = _ira_escape_opcode_table[index];
		*number_of_opcode_bytes = _ira_escape_size_table[index];
	} else if( prefixes_fields->vex_prefix == 0x8F ) {
		escape = &(prefixes_fields->mmmm);
		*number_of_opcode_bytes = 1;
	} else {
		escape = _ira_escape_0f;
		*number_of_opcode_bytes = 1;
	}
	return escape;
}

void _ira_avx_free_escape_opcode_bytes( uint8_t *escape_opcode_bytes ) {
}
