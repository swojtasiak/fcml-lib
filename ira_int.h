#ifndef IRA_INT_H_INCLUDED
#define IRA_INT_H_INCLUDED

#include <stdint.h>
#include <stdio.h>
#include "ira.h"

#include "fcml_stream.h"
#include "fcml_common.h"
#include "fcml_mnemonic_parser.h"

#define _IRA_TRUE 1
#define _IRA_FALSE 0

/* Internal error codes */

#define _IRA_INT_ERROR_NO_ERROR						0x00
#define _IRA_INT_ERROR_CODE_UNEXPECTED_EOS			0x01
#define _IRA_INT_ERROR_OUT_OF_MEMORY				0x02
#define _IRA_INT_ERROR_ILLEGAL_ARGUMENT				0x03
#define _IRA_INT_ERROR_ILLEGAL_ADDRESSING			0x04

#define _IRA_INT_ERROR_INSTRUCTION_NOT_ENCODABLE	0x05
#define _IRA_INT_ERROR_SYNTAX_NOT_SUPPORTED			0x06
#define _IRA_INT_ERROR_ILLEGAL_INSTRUCTION			0x07
#define _IRA_INT_ERROR_ILLEGAL_STATE_EXCEPTION      0x08

/* Size attribute types */

// TODO: Pytanie czy to faktycznie jest potrzebne? Wyaje sie troche nadmiarowe. Patrz: common and operand size encoding.
/*enum SizeAttributeType {
 IRA_SAT_ASA,
 IRA_SAT_OSA,
 IRA_SAT_UNDEFINED
 };*/

/* ModRM decoding. */

struct ira_decoded_mod_rm {
    // True if XMM/MM memory location is used.
    fcml_bool multimedia_operand;
	// Set to _IRA_TRUE if ModRM exists and addressing has been decoded for the current instruction.
	uint8_t decoded_addressing;
	// Set to _IRA_TRUE if ModRM exists and register has been decoded for the current instruction.
	uint8_t decoded_reg;
	// ModRM byte.
	n_byte raw_mod_rm;
	// SIB byte.
	n_byte raw_sib;
	fcml_bool rip;
	fcml_uint64_t rip_address;
	// REX prefix.
	// n_byte raw_rex;
	// Base register.
	struct ira_register base_reg;
	// Index register.
	struct ira_register index_reg;
	// Scale factor value for 32 and 64 bit addressing modes.
	n_byte scale;
	// Displacement value.
	struct ira_displacement displacement;
	// Register decoded if "mod" = 3.
	struct ira_register reg;
	// Register operand encoded in "reg" field of the ModRM.
	struct ira_register operand_reg;
};

// Holds decoded fields from VEX and REX prefixes. Used only to optimize access to VEX/REX
// prefix fields by avoiding iteration through prefixes array any time when VEX/REX
// interpretation is needed.
struct ira_decoded_fields {
	uint8_t is_rex;
	uint8_t is_xop;
	uint8_t is_vex;
	uint8_t vex_prefix;
	uint8_t r;
	uint8_t x;
	uint8_t b;
	uint8_t w;
	uint8_t l;
	uint8_t mmmm;
	uint8_t vvvv;
	uint8_t pp;
};

/* Disassemblation context. */

struct ira_decoding_context {
	// Chosen instruction decoding.
	struct ira_diss_tree_instruction_decoding *instruction;
	// Operand size attribute.
	uint8_t effective_operand_size_attribute;
	// Address size attribute.
	uint8_t effective_address_size_attribute;
	// Decoded prefixes.
	struct ira_instruction_prefix prefixes[_IRA_PREFIXES_COUNT];
	// Base opcode bytes without opcode fields applied.
	uint8_t base_opcodes[3];
	// Opcode bytes without mandatory prefixes.
	uint8_t opcodes[3];
	// Number of opcode bytes.
	uint8_t opcodes_count;
	// Position of the opcode fields in the byte. To be more precise it's a bit shift.
	uint8_t opcode_fields_pos;
	// Primary opcode byte.
	uint8_t primary_opcode_index;
	// Number of prefixes decoded for instruction.
	uint8_t instruction_prefix_count;
	// Decoded prefixes fields.
	struct ira_decoded_fields prefixes_fields;
	// Decoded ModRM.
	struct ira_decoded_mod_rm mod_rm;
	// Instruction size. This value is only available during post processing.
	int32_t instruction_size;
};

struct ira_diss_context {
	// Disassembler configuration.
	struct ira_disassembler_config *config;
	// Architecture.
	enum ira_operation_mode mode;
	// Operand size attribute.
	uint8_t operand_size_attribute;
	// Address size attribute.
	uint8_t address_size_attribute;
	// Context that is shared by methods taking part in the decoding process.
	struct ira_decoding_context decoding_context;
	// Stream.
	fcml_st_memory_stream *stream;
	// Instruction pointer.
	union ira_instruction_pointer instruction_pointer;
};

/* Returns 1 is there is given prefix found for given instruction. */
int _ira_diss_context_is_prefix_available(struct ira_diss_context *context, uint8_t prefix, uint8_t mandatory );

/* Gets REX prefix. */
uint8_t _ira_diss_context_get_REX_prefix(struct ira_diss_context *context, int *found);

/* Decoding arguments. */

/* Addressing by given register */
struct ira_reg_addressing_arg {
	// Base register.
	struct ira_register reg;
	// Number of bytes address points to.
	uint8_t encoded_operand_size;
	// Encoded segment selector.
	uint8_t encoded_segment_selector;
};

/* Structure that can be used to pass condition type to operand decoding function. */
struct ira_condition_type_args {
	// Condition type.
	enum ira_condition_type condition_type;
};

// TODO: Zastanowic sie nad kilkoma generycznymi aterybutami typów i wykorzystaniem kontenera i kompozycji do przekazywania typow do dekoderów, mogli bysmy zrezygnowac z dedykowanych struktur, dla ulatwinia kopozycja moze zawierac od razu pola dla wszystkich dotepnych typow argumentowe.

/* Generic structure used to store size of the operand. */
struct ira_seg_relative_offset_args {
	// Number of bytes address points to.
	uint16_t offset_size;
	// Encoded segment selector.
	uint8_t encoded_segment_selector;
};


/* Structure that can be used to pass explicit immediate value to operand decoding function. */
struct ira_explicit_immediate_type_args {
	// Immediate value type.
	enum ira_immediate_data_type immediate_data_type;
	// Immediate value.
	union ira_immediate_data_value immediate_data;
};

typedef uint16_t (*ira_operand_size_provider)(struct ira_diss_context *context);




/* Structure used to decode  */
struct ira_modm_decoding_args {
	// Size directive provider.
	ira_operand_size_provider operand_size_provider;
	// Explicit addressing size.
	uint16_t operand_size;
	// VSIB used.
	uint8_t is_vsib;
	// Encoded vector index register.
	uint8_t vir;
};

/* Disassemblation tree. */

struct ira_diss_tree_opcode {
	struct ira_diss_tree_opcode* opcodes[256];
	struct ira_diss_tree_instruction_decoding *instructions;
};

/* Operand wrapper. */

typedef int (*ira_instruction_operand_handler)(
		struct ira_diss_context *context,
		struct ira_instruction_operand *operand,
		struct ira_instruction_operand *istruction_operands[4]);

struct ira_instruction_operand_wrapper {
	// Instruction operand.
	struct ira_instruction_operand operand;
	// Optional post processor, that can be registered by decoder.
	ira_instruction_operand_handler post_processor;
};

/* Decoders responsible for instruction disassemblation. */
typedef int (*ira_instruction_decoder)(struct ira_diss_context *context,
		struct ira_diss_tree_instruction_decoding *instruction,
		struct ira_disassemble_result *result);

/* Decoders responsible for operand disassemblation. */
typedef int (*ira_operand_decoder)(struct ira_diss_context *context,
		struct ira_instruction_operand_wrapper *operand, void *args);

struct ira_operand_decoding {
	// Operand access mode.
	enum ira_access_mode access_mode;
	// Operand decoder.
	ira_operand_decoder decoder;
	// Optional arguments passed to operand decoder.
	void *args;
	// Optional hints, is operand adds any.
	fcml_hints hints;
};

struct ira_diss_tree_instruction_decoding {
	/* Pointer to the next decoding. There is no need to provide additional structure for one directional list */
	struct ira_diss_tree_instruction_decoding *next_instruction_decoding;
	/* Opcodes. */
	uint8_t opcodes[3];
	/* Instruction mnemonic */
	fcml_st_mp_mnemonic_set *mnemonics;
	/* Flags that describe prefixes usage. */
	uint16_t prefixes_flags;
	/* Flags that describe some details of opcodes. */
	uint32_t opcode_flags;
	/* Instruction decoder. */
	ira_instruction_decoder instruction_decoder;
	/* Function used to decode instruction operands. */
	struct ira_operand_decoding operand_decodings[FCML_OPERANDS_COUNT];
	/* Instruction decoding order, for information purpose only. */
	int order;
};

struct ira_diss_tree_instruction_details {
};

extern struct ira_diss_tree_opcode* _ira_disassemblation_tree[256];

struct ira_instruction_opcode_decoder {

};


/* Macro for bit manipulations. */

#define _IRA_GET_BIT(x,y)	( ( x >> y ) & 0x01 )

/* ModR/M decoding. */

#define _IRA_MODRM_MOD(x)			( x >> 6 )
#define _IRA_MODRM_REG_OPCODE(x)	( ( x & 0x38 ) >> 3 )
#define _IRA_MODRM_RM(x)			( x & 0x07 )

/* SIB decoding */

#define _IRA_SIB_SS(x)				( x >> 6 )
#define _IRA_SIB_INDEX(x)			( ( x & 0x38 ) >> 3 )
#define _IRA_SIB_BASE(x)			( x & 0x07 )

/* REX decoding */

#define _IRA_REX_W(x)				_IRA_GET_BIT(x, 3)
#define _IRA_REX_R(x)				_IRA_GET_BIT(x, 2)
#define _IRA_REX_X(x)				_IRA_GET_BIT(x, 1)
#define _IRA_REX_B(x)				_IRA_GET_BIT(x, 0)

/* REX decoding */

#define _IRA_VEX_W(x)				_IRA_GET_BIT(x, 7)
// R,X and B are stored in 1's complement form.
#define _IRA_VEX_R(x)				!_IRA_GET_BIT(x, 7)
#define _IRA_VEX_X(x)				!_IRA_GET_BIT(x, 6)
#define _IRA_VEX_B(x)				!_IRA_GET_BIT(x, 5)
#define _IRA_VEX_L(x)				_IRA_GET_BIT(x, 2)
#define _IRA_VEX_MMMM(x)			( x & 0x1F )
#define _IRA_VEX_VVVV(x)			( ~( ( x & 0x78 ) >> 3 ) & 0x00F )
#define _IRA_VEX_PP(x)				( x & 0x03 )

/* Prefixes flags. */

#define _IRA_PREFIX_W_1(x)					_IRA_GET_BIT(x,3)
#define _IRA_PREFIX_W_0(x)					_IRA_GET_BIT(x,4)
#define _IRA_PREFIX_VEX_L_1(x)				_IRA_GET_BIT(x,5)
#define _IRA_PREFIX_VEX_L_0(x)				_IRA_GET_BIT(x,6)
#define _IRA_PREFIX_VEX_REQ(x)				_IRA_GET_BIT(x,7)
#define _IRA_PREFIX_VEX_VVVV(x)				_IRA_GET_BIT(x,8)
#define _IRA_PREFIX_VEX_L_IGNORE_OS(x)		_IRA_GET_BIT(x,9)
#define _IRA_PREFIX_XOP_REQ(x)				_IRA_GET_BIT(x,10)
#define _IRA_PREFIX_MANDATORY_66(x) 		_IRA_GET_BIT(x,12)
#define _IRA_PREFIX_MANDATORY_F2(x) 		_IRA_GET_BIT(x,13)
#define _IRA_PREFIX_MANDATORY_F3(x) 		_IRA_GET_BIT(x,14)

/* TTTN - Conditional instructions. */

#define _IRA_TTTN_IS_NEGATION(opcode)		(opcode & 0x01)

/* Opcode flags. */

#define _IRA_REG_FIELD_SIZE								3
#define _IRA_CONDITION_FIELD_SIZE						4
#define _IRA_REG_FIELD_POS								0

#define _IRA_REG_FIELD_NUMBER_OF_REGISTERS				8
#define _IRA_REG_FIELD_NUMBER_OF_CONDITIONS				16

//#define _IRA_ENCODE_OPCODE_FLAGS_OPCODE_EXT( opcode_flags, ext )	( x | ( ext << 11 ) )

#define _IRA_OPCODE_FLAGS_OPCODE_FIELD_REG(x)			( x & 0x00000001 )
#define _IRA_OPCODE_FLAGS_OPCODE_FIELD_TTTN(x)			( x & 0x00000040 )
#define _IRA_OPCODE_FLAGS_POS(x)						( ( x & 0x00000700 ) >> 8 )
#define _IRA_OPCODE_FLAGS_OPCODE_EXT(x)					( ( x & 0x00007800 ) >> 11 )
#define _IRA_OPCODE_FLAGS_OPCODE_IS_MODRM(x) 			_IRA_GET_BIT(x,15)
#define _IRA_OPCODE_FLAGS_OPCODE_IS_EXT(x) 				_IRA_GET_BIT(x,16)
#define _IRA_OPCODE_FLAGS_MODRM_R(x)	 				_IRA_GET_BIT(x,17)
#define _IRA_OPCODE_FLAGS_OPCODE_NUM(x) 				( ( x & 0x000C0000 ) >> 18 )
#define _IRA_OPCODE_FLAGS_PRIMARY_OPCODE(x) 			( ( x & 0x00300000 ) >> 20 )
#define _IRA_OPCODE_FLAGS_64_BIT_MODE_SUPPORTED(x)		( x & 0x00800000 )
#define _IRA_OPCODE_FLAGS_16_32_BIT_MODE_SUPPORTED(x)	( x & 0x00400000 )
#define _IRA_OPCODE_FLAGS_EOSA_16(x)					( x & 0x01000000 )
#define _IRA_OPCODE_FLAGS_EOSA_32(x)					( x & 0x02000000 )
#define _IRA_OPCODE_FLAGS_EOSA_64(x)					( x & 0x04000000 )
#define _IRA_OPCODE_FLAGS_IS_EOSA_RESTRICTION(x)		( x & 0x07000000 )
#define _IRA_OPCODE_FLAGS_EASA_16(x)					( x & 0x08000000 )
#define _IRA_OPCODE_FLAGS_EASA_32(x)					( x & 0x10000000 )
#define _IRA_OPCODE_FLAGS_EASA_64(x)					( x & 0x20000000 )
#define _IRA_OPCODE_FLAGS_IS_EASA_RESTRICTION(x)		( x & 0x38000000 )
#define _IRA_OPCODE_FLAGS_FORCE_64BITS_EOSA(x)			( x & 0x40000000 )
#define _IRA_OPCODE_FLAGS_MODRM_M(x)	 				_IRA_GET_BIT(x,31)


#endif // IRA_INT_H_INCLUDED
