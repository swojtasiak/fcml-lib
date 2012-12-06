#ifndef IRA_INT_H_INCLUDED
#define IRA_INT_H_INCLUDED

#include <stdint.h>
#include <stdio.h>
#include "ira.h"

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

/* Size attribute types */

// TODO: Pytanie czy to faktycznie jest potrzebne? Wyaje sie troche nadmiarowe. Patrz: common and operand size encoding.
/*enum SizeAttributeType {
 IRA_SAT_ASA,
 IRA_SAT_OSA,
 IRA_SAT_UNDEFINED
 };*/

/* Structures used to store information about memory. */

struct ira_memory_stream {
	void *base_address; /* Base address of memory. */
	uint32_t offset; /* Offset. */
	uint32_t size; /* Size. */
};

/* Methods used for streaming. */

enum ira_seek_type {
	IRA_START = 0, IRA_END, IRA_CURRENT
};

void _ira_stream_seek(struct ira_memory_stream *stream, uint32_t offset,
		enum ira_seek_type type);

uint8_t _ira_stream_read(struct ira_memory_stream *stream, int *result);

uint8_t _ira_stream_peek(struct ira_memory_stream *stream, int *result);

/* Gets size of the data to read. */
uint32_t _ira_stream_size(struct ira_memory_stream *stream);

/* Reads specified number of bytes from stream and stores them in given buffer. */
int _ira_stream_read_bytes(struct ira_memory_stream *stream, void *buffer,
		int size);

/* ModRM decoding. */

struct ira_decoded_mod_rm {
	// Set to _IRA_TRUE if ModRM exists and addressing has been decoded for the current instruction.
	uint8_t decoded_addressing;
	// Set to _IRA_TRUE if ModRM exists and register has been decoded for the current instruction.
	uint8_t decoded_reg;
	// ModRM byte.
	n_byte raw_mod_rm;
	// SIB byte.
	n_byte raw_sib;
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
	struct ira_memory_stream *stream;
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

/* Structure that can be used to pass register type to operand decoding function. */
struct ira_reg_type_args {
	// Attribute used to calculate register size, if calculation is needed.
	// TODO: Dlaczego camel casE?
	// TODO: Zmineic na _IRA_OSktory umozliwia zakodowanie konkretnej wielkosci jak i EOSA/EASA.
	// enum SizeAttributeType size_attribute_type;
	// Register details.
	struct ira_register reg;
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

/* Structure that can be used to pass immediate value type/size to operand decoding function. */
struct ira_immediate_type_args {
	// Immediate value type.
	enum ira_immediate_data_type immediate_data_type;
};

/* Structure that can be used to pass explicit immediate value to operand decoding function. */
struct ira_explicit_immediate_type_args {
	// Immediate value type.
	enum ira_immediate_data_type immediate_data_type;
	// Immediate value.
	union ira_immediate_data_value immediate_data;
};

typedef uint16_t (*ira_operand_size_provider)(struct ira_diss_context *context);

/* Structure that can be used to pass register type and its size to operand decoding function. */
struct ira_modrm_decoding_args {
	// Register type.
	enum ira_register_type reg_type;
	// Allows to dynamically calculate memory operand size.
	ira_operand_size_provider memory_operand_size_provider;
	// Memory operand size.
	uint16_t memory_operand_size;
	// Allows to dynamically calculate register operand size.
	ira_operand_size_provider register_operand_size_provider;
	// Register operand size.
	uint16_t register_operand_size;
	// Flags.
	uint8_t flags;
};

/* Structure used to decode  */
struct ira_modm_decoding_args {
	// Size directive provider.
	ira_operand_size_provider operand_size_provider;
	// Explicit addressing size.
	uint16_t operand_size;
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
};

struct ira_diss_tree_instruction_decoding {
	/* Pointer to the next decoding. There is no need to provide additional structure for one directional list */
	struct ira_diss_tree_instruction_decoding *next_instruction_decoding;
	/* Opcodes. */
	uint8_t opcodes[3];
	/* Instruction mnemonic */
	char *mnemonic;
	/* Flags that describe prefixes usage. */
	uint16_t prefixes_flags;
	/* Flags that describe some details of opcodes. */
	uint32_t opcode_flags;
	/* Instruction decoder. */
	ira_instruction_decoder instruction_decoder;
	/* Function used to decode instruction operands. */
	struct ira_operand_decoding operand_decodings[4];
	/* Instruction decoding order, for information purpose only. */
	int order;
};

struct ira_diss_tree_instruction_details {
};

extern struct ira_diss_tree_opcode* _ira_disassemblation_tree[256];

struct ira_instruction_opcode_decoder {

};

/* Structures used to describe instructions. */

struct ira_opcode_desc {
	char *mnemonic_override; // Mnemonic, if there is another mnemonic available for this opcode.
	uint16_t allowed_prefixes; // Flags describing allowed prefixes.
	uint32_t opcode_flags; // Some flags that contains various information about opcode.
	uint8_t opcode[3]; // Opcode bytes.
	uint32_t opperand_1; // Addressing of first instruction operand.
	uint32_t opperand_2; // Second etc.
	uint32_t opperand_3;
	uint32_t opperand_4;
};

struct ira_instruction_desc {
	// Mnemonic.
	char *mnemonic;
	// tODO: Dodac na koncu.
	/*// Instruction group.
	 uint16_t instruction_group;
	 */
	// Type of the instruction.
	uint8_t instruction_type;
	// Number of opcodes' descriptions.
	uint8_t opcode_desc_count;
	// Opcodes' descriptions.
	struct ira_opcode_desc *opcodes;
};

/* Segment registers encoding. */

#define _IRA_SEG_ALLOW_OVERRIDE		0x80
#define _IRA_SEG_DENY_OVERRIDE		0x00
#define _IRA_SEG_ENCODE_REGISTER( reg_num, override )		( reg_num | override )
#define _IRA_SEG_DECODE_IS_OVERRIDE_ALLOWED( encoded )		( _IRA_SEG_ALLOW_OVERRIDE & encoded )
#define _IRA_SEG_DECODE_REGISTER( encoded )					( encoded & ~_IRA_SEG_ALLOW_OVERRIDE )

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
#define _IRA_VEX_VVVV(x)			(~( ( x & 0x78 ) >> 3 ) & 0x00F)
#define _IRA_VEX_PP(x)				( x & 0x03 )

/* Prefixes flags. */

// TODO: nadmiarowy! zobacz EOSA restrictions! wywalic, tylko gmatwa (ale czy aby napewno, czasami REX.W podownie jak VEX.W mo¿e spelniac inna role niz tylko zmiaa EOSA.) narazie zostawic, sprawzic po zakonczeniu implementacji disassemlera.
#define _IRA_PREFIX_W_1(x)					_IRA_GET_BIT(x,3)
#define _IRA_PREFIX_W_0(x)					_IRA_GET_BIT(x,4)
#define _IRA_PREFIX_VEX_L_1(x)				_IRA_GET_BIT(x,5)
#define _IRA_PREFIX_VEX_L_0(x)				_IRA_GET_BIT(x,6)
#define _IRA_PREFIX_VEX_REQ(x)				_IRA_GET_BIT(x,7)
#define _IRA_PREFIX_VEX_VVVV(x)				_IRA_GET_BIT(x,8)
#define _IRA_PREFIX_VEX_L_IGNORE_OS(x)		_IRA_GET_BIT(x,9)
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

/* Instruction types. */

#define _IRA_IT_IA			0x00

/* Operands encoding */

#define _IRA_OPERANDS_SIZEOF(x)	( sizeof( x ) / sizeof( struct ira_opcode_desc ) )

#define _IA_INSTRUCTION(x,y) { x, _IRA_IT_IA, _IRA_OPERANDS_SIZEOF(y), y }

// Source operand (Reads).
#define _IRA_READ	0x00000000

// Destination operand (Writes).
#define _IRA_WRITE	0x80000000

#define _IRA_NA	0x00000000

// todo: zmienic to na jedno parametryzowane makro, ktore jako parametr przyjmie wielkosc wartosci natychmiastowej.
#define _IRA_OPERAND_IB						0x01000000
// imm8 sign extended to effective operand size attribute.
#define _IRA_OPERAND_IB_EX_EOSA				0x02000000
#define _IRA_OPERAND_IW						0x03000000
#define _IRA_OPERAND_IW_EX_EOSA				0x04000000
#define _IRA_OPERAND_ID						0x05000000
// imm32 sign extended to effective operand size attribute.
#define _IRA_OPERAND_ID_EX_EOSA				0x06000000
#define _IRA_OPERAND_IO						0x07000000
#define _IRA_OPERAND_IO_EOSA				0x08000000
// Immediate value with size calculated using EOSA.
#define _IRA_OPERAND_IMM_EOSA				0x09000000

// todo: wywalic to, mamy explicit register, tylko komplikutje model opisu trybow adreowania.
#define _IRA_OPERAND_REG_ACCUMULATOR_8		0x0A000000
#define _IRA_OPERAND_REG_ACCUMULATOR_OSA	0x0B000000
#define _IRA_OPERAND_REG_ACCUMULATOR_8_W	( _IRA_OPERAND_REG_ACCUMULATOR_8   | _IRA_WRITE )
#define _IRA_OPERAND_REG_ACCUMULATOR_OSA_W	( _IRA_OPERAND_REG_ACCUMULATOR_OSA | _IRA_WRITE )

// Base for ModRM based operands.
#define _IRA_MODRM_BASE 					0x0C000000

/* Operands for ModRM encoding. */

#define _IRA_RM_8		0
#define _IRA_R_8		1
#define _IRA_RM_16		2
#define _IRA_R_16		3
#define _IRA_RM_32		4
#define _IRA_R_32		5
#define _IRA_RM_64		6
#define _IRA_R_64		7
#define _IRA_RM			8
#define _IRA_R			9
#define _IRA_RM_MMX		10
#define _IRA_R_MMX		11
#define _IRA_RM_XMM_128	12
#define _IRA_R_XMM_128	13
#define _IRA_RM_XMM_64	14
#define _IRA_R_XMM_64	15
#define _IRA_RM_XMM_32	16
#define _IRA_R_XMM_32	17
// m16&16, m32&32.
#define _IRA_OSA_MM		18
// m8-m128
#define _IRA_M_8		19
#define _IRA_M_16		20
#define _IRA_M_32		21
#define _IRA_M_64		22
#define _IRA_M_80		23
#define _IRA_M_128		24
#define _IRA_M_14_28	25
#define _IRA_M_94_108	26
#define _IRA_M_512B		27
#define _IRA_M_UNDEF	28
// TODO: RAczej SIMD a nie XMM, jako ze mamy XMM i YMM.
#define _IRA_RM_XMM_L	29
#define _IRA_R_XMM_L	30

/* ModRM based operands. */

#define _IRA_MODRM(x) ( _IRA_MODRM_BASE + x )

// todo: czy to nie ejst nadmiarowe? sprobowal przepisac na parametryzowane makra.
#define _IRA_OPERAND_MODRM_RM_8			_IRA_MODRM(_IRA_RM_8)
#define _IRA_OPERAND_MODRM_RM_8_W		( _IRA_OPERAND_MODRM_RM_8 | _IRA_WRITE )
#define _IRA_OPERAND_MODRM_RM_16		_IRA_MODRM(_IRA_RM_16)
#define _IRA_OPERAND_MODRM_RM_16_W		( _IRA_OPERAND_MODRM_RM_16 | _IRA_WRITE )
#define _IRA_OPERAND_MODRM_RM_32		_IRA_MODRM(_IRA_RM_32)
#define _IRA_OPERAND_MODRM_RM_32_W		( _IRA_OPERAND_MODRM_RM_32 | _IRA_WRITE )
#define _IRA_OPERAND_MODRM_RM_64		_IRA_MODRM(_IRA_RM_64)
#define _IRA_OPERAND_MODRM_RM_64_W		( _IRA_OPERAND_MODRM_RM_64 | _IRA_WRITE )
#define _IRA_OPERAND_MODRM_RM			_IRA_MODRM(_IRA_RM)
#define _IRA_OPERAND_MODRM_RM_W			( _IRA_OPERAND_MODRM_RM | _IRA_WRITE )
#define _IRA_OPERAND_MODRM_R_8			_IRA_MODRM(_IRA_R_8)
#define _IRA_OPERAND_MODRM_R_8_W		( _IRA_OPERAND_MODRM_R_8 | _IRA_WRITE )
#define _IRA_OPERAND_MODRM_R_16			_IRA_MODRM(_IRA_R_16)
#define _IRA_OPERAND_MODRM_R_16_W		( _IRA_OPERAND_MODRM_R_16 | _IRA_WRITE )
#define _IRA_OPERAND_MODRM_R_32			_IRA_MODRM(_IRA_R_32)
#define _IRA_OPERAND_MODRM_R_32_W		( _IRA_OPERAND_MODRM_R_32 | _IRA_WRITE )
#define _IRA_OPERAND_MODRM_R_64			_IRA_MODRM(_IRA_R_64)
#define _IRA_OPERAND_MODRM_R_64_W		( _IRA_OPERAND_MODRM_R_64 | _IRA_WRITE )
#define _IRA_OPERAND_MODRM_R		_IRA_MODRM(_IRA_R)
#define _IRA_OPERAND_MODRM_R_W		( _IRA_OPERAND_MODRM_R | _IRA_WRITE )
#define _IRA_OPERAND_MODRM_MM_OSA		_IRA_MODRM(_IRA_OSA_MM)
#define _IRA_OPERAND_MODRM_M_8			_IRA_MODRM(_IRA_M_8)
#define _IRA_OPERAND_MODRM_M_8_W		(_IRA_OPERAND_MODRM_M_8 | _IRA_WRITE)
#define _IRA_OPERAND_MODRM_M_16			_IRA_MODRM(_IRA_M_16)
#define _IRA_OPERAND_MODRM_M_16_W		(_IRA_OPERAND_MODRM_M_16 | _IRA_WRITE)
#define _IRA_OPERAND_MODRM_M_32			_IRA_MODRM(_IRA_M_32)
#define _IRA_OPERAND_MODRM_M_32_W		(_IRA_OPERAND_MODRM_M_32 | _IRA_WRITE)
#define _IRA_OPERAND_MODRM_M_64			_IRA_MODRM(_IRA_M_64)
#define _IRA_OPERAND_MODRM_M_64_W		(_IRA_OPERAND_MODRM_M_64 | _IRA_WRITE)
#define _IRA_OPERAND_MODRM_M_80			_IRA_MODRM(_IRA_M_80)
#define _IRA_OPERAND_MODRM_M_80_W		(_IRA_OPERAND_MODRM_M_80 | _IRA_WRITE)
#define _IRA_OPERAND_MODRM_M_128		_IRA_MODRM(_IRA_M_128)
#define _IRA_OPERAND_MODRM_M_128_W		(_IRA_OPERAND_MODRM_M_128 | _IRA_WRITE)
#define _IRA_OPERAND_MODRM_M_14_28		_IRA_MODRM(_IRA_M_14_28)
#define _IRA_OPERAND_MODRM_M_14_28_W	(_IRA_OPERAND_MODRM_M_14_28 | _IRA_WRITE)
#define _IRA_OPERAND_MODRM_M_94_108		_IRA_MODRM(_IRA_M_94_108)
#define _IRA_OPERAND_MODRM_M_94_108_W	(_IRA_OPERAND_MODRM_M_94_108 | _IRA_WRITE)
#define _IRA_OPERAND_MODRM_M_512B		_IRA_MODRM(_IRA_M_512B)
#define _IRA_OPERAND_MODRM_M_512B_W	(_IRA_OPERAND_MODRM_M_512B | _IRA_WRITE)
#define _IRA_OPERAND_MODRM_M_UNDEF		_IRA_MODRM(_IRA_M_UNDEF)
#define _IRA_OPERAND_MODRM_M_UNDEF_W	(_IRA_OPERAND_MODRM_M_UNDEF | _IRA_WRITE)

// todo: nie implicit tylko explicit
// todo: dodac kodowanie wilkosci rejestru na podstawie encoded operand size.
// Implicit registers with size determined by operand-size-attribute.
#define _IRA_EXPLICIT_REG_BASE_OSA						0x0D000000
#define _IRA_EXPLICIT_REG_OSA(reg_type,reg_num)			( _IRA_EXPLICIT_REG_BASE_OSA | reg_type << 4 | reg_num )

// Implicit registers with size determined by address-size-attribute.
#define _IRA_EXPLICIT_REG_BASE_ASA						0x0E000000
#define _IRA_EXPLICIT_REG_ASA(reg_type,reg_num)			( _IRA_EXPLICIT_REG_BASE_ASA | reg_type << 4 | reg_num )

#define _IRA_EXPLICIT_REG_BASE							0x0F000000
#define _IRA_EXPLICIT_REG(reg_type, reg_num, reg_size)	( _IRA_EXPLICIT_REG_BASE | reg_type << 20 | reg_num << 16 | reg_size )

// Register field in opcode byte.
#define _IRA_OPERAND_OPCODE_REG_BASE					0x10000000
#define _IRA_OPERAND_OPCODE_REG(reg_type, reg_size)	( _IRA_OPERAND_OPCODE_REG_BASE | reg_type << 16 | reg_size)

// Relative addressing.
#define _IRA_OPERAND_IMMEDIATE_DIS_RELATIVE_EOSA	0x11000000

// rel8
#define _IRA_OPERAND_IMMEDIATE_DIS_RELATIVE_R_8		0x12000000

// Far pointers.
#define _IRA_OPERAND_FAR_POINTER					0x13000000

// Far indirect pointer.
#define _IRA_OPERAND_FAR_POINTER_INDIRECT			0x14000000

// Addressing by explicit GPR register. (Used by CMPS for instance.)
#define _IRA_EXPLICIT_GPS_REG_ADDRESSING_BASE		0x15000000
#define _IRA_EXPLICIT_GPS_REG_ADDRESSING(reg_num, encoded_operand_size, encoded_segment_register)	( _IRA_EXPLICIT_GPS_REG_ADDRESSING_BASE | reg_num << 16 | encoded_operand_size << 8 | encoded_segment_register )

// It allows defining explicit IMM8 operand type. See INT instruction.
#define _IRA_EXPLICIT_OPERAND_IB_BASE				0x16000000
#define _IRA_EXPLICIT_OPERAND_IB(value)				( _IRA_EXPLICIT_OPERAND_IB_BASE | value )

// todo: Mozna sie zastanowic nad dodaniem flag M, R zeby mona bylo wybierac tryb adreacji rm/r/m
// Allows to encode all common ModR/M based addressing modes using only one macro.

#define _IRA_RMF_R		0x01
#define _IRA_RMF_M		0x02
#define _IRA_RMF_RM		( _IRA_RMF_R | _IRA_RMF_M )
// TODO: Zastanowic sie czy do sterowania flagami nie da ie wykorzystac nowych bitow MOD3 ModNot3 zamiast bezposredniego ich podawania.
#define _IRA_OPERAND_RM_BASE						0x17000000
#define _IRA_OPERAND_RM(reg_type, encoded_register_operand_size, encoded_memory_operand_size, flags )		( _IRA_OPERAND_RM_BASE | encoded_memory_operand_size << 16 | encoded_register_operand_size << 8 | reg_type << 4 | flags )
#define _IRA_OPERAND_RM_W(reg_type, encoded_register_operand_size, encoded_memory_operand_size, flags )		( _IRA_OPERAND_RM(reg_type, encoded_register_operand_size, encoded_memory_operand_size, flags) | _IRA_WRITE )

// TODO: do usuniecia, wytarczy _IRA_OPERAND_RM z flaga: _IRA_RMF_M
#define _IRA_OPERAND_M_BASE							0x18000000
#define _IRA_OPERAND_M( memory_operand_size )		( _IRA_OPERAND_M_BASE | memory_operand_size )

#define _IRA_OPERAND_R_BASE									0x19000000
#define _IRA_OPERAND_R( reg_type, register_operand_size )	( _IRA_OPERAND_R_BASE | ( register_operand_size << 4 ) | reg_type )

#define _IRA_OPERAND_SEGMENT_RELATIVE_OFFSET_BASE	0x1A000000
#define _IRA_OPERAND_SEGMENT_RELATIVE_OFFSET( operand_size, encoded_segment_register )	( _IRA_OPERAND_SEGMENT_RELATIVE_OFFSET_BASE | operand_size << 8 | encoded_segment_register )

#define _IRA_VEX_VVVV_REG							0x1B000000

#define _IRA_OPERAND_IS4							0x1C000000

// Shorthands
#define _IRA_OPERAND_MODRM_RM_MMX		_IRA_OPERAND_RM(IRA_REG_SIMD, _IRA_EOS_MMWORD, _IRA_EOS_MMWORD, _IRA_RMF_RM )
#define _IRA_OPERAND_MODRM_RM_MMX_W		( _IRA_OPERAND_MODRM_RM_MMX | _IRA_WRITE )
#define _IRA_OPERAND_MODRM_R_MMX		_IRA_OPERAND_R(IRA_REG_SIMD, _IRA_OS_MMWORD )
#define _IRA_OPERAND_MODRM_R_MMX_W		( _IRA_OPERAND_MODRM_R_MMX | _IRA_WRITE )
#define _IRA_OPERAND_MODRM_RM_XMM_128	_IRA_OPERAND_RM(IRA_REG_SIMD, _IRA_EOS_XMMWORD, _IRA_EOS_XMMWORD, _IRA_RMF_RM )
#define _IRA_OPERAND_MODRM_RM_XMM_128_W	( _IRA_OPERAND_MODRM_RM_XMM_128 | _IRA_WRITE )
#define _IRA_OPERAND_MODRM_RM_XMM_64	_IRA_OPERAND_RM(IRA_REG_SIMD, _IRA_EOS_XMMWORD, _IRA_EOS_QWORD, _IRA_RMF_RM )
#define _IRA_OPERAND_MODRM_RM_XMM_64_W	( _IRA_OPERAND_MODRM_RM_XMM_64 | _IRA_WRITE )
#define _IRA_OPERAND_MODRM_RM_XMM_32	_IRA_OPERAND_RM(IRA_REG_SIMD, _IRA_EOS_XMMWORD, _IRA_EOS_DWORD, _IRA_RMF_RM )
#define _IRA_OPERAND_MODRM_RM_XMM_32_W	( _IRA_OPERAND_MODRM_RM_XMM_32 | _IRA_WRITE )
#define _IRA_OPERAND_MODRM_R_XMM		_IRA_OPERAND_R(IRA_REG_SIMD, _IRA_OS_XMMWORD )
#define _IRA_OPERAND_MODRM_R_XMM_W		( _IRA_OPERAND_MODRM_R_XMM | _IRA_WRITE )
#define _IRA_OPERAND_MODRM_RM_SIMD		_IRA_OPERAND_RM(IRA_REG_SIMD, _IRA_EOS_EOSA, _IRA_EOS_EOSA, _IRA_RMF_RM )
#define _IRA_OPERAND_MODRM_RM_SIMD_W	( _IRA_OPERAND_MODRM_RM_SIMD | _IRA_WRITE )
#define _IRA_OPERAND_MODRM_RM_SIMD_128	_IRA_OPERAND_RM(IRA_REG_SIMD, _IRA_EOS_EOSA, _IRA_EOS_OWORD, _IRA_RMF_RM )
#define _IRA_OPERAND_MODRM_RM_SIMD_128_W	( _IRA_OPERAND_MODRM_RM_SIMD_128 | _IRA_WRITE )
#define _IRA_OPERAND_MODRM_RM_SIMD_64	_IRA_OPERAND_RM(IRA_REG_SIMD, _IRA_EOS_EOSA, _IRA_EOS_QWORD, _IRA_RMF_RM )
#define _IRA_OPERAND_MODRM_RM_SIMD_64_W	( _IRA_OPERAND_MODRM_RM_SIMD_64 | _IRA_WRITE )
#define _IRA_OPERAND_MODRM_RM_SIMD_32	_IRA_OPERAND_RM(IRA_REG_SIMD, _IRA_EOS_EOSA, _IRA_EOS_DWORD, _IRA_RMF_RM )
#define _IRA_OPERAND_MODRM_RM_SIMD_32_W	( _IRA_OPERAND_MODRM_RM_SIMD_32 | _IRA_WRITE )
#define _IRA_OPERAND_MODRM_R_SIMD		_IRA_OPERAND_R(IRA_REG_SIMD, _IRA_OS_EOSA )
#define _IRA_OPERAND_MODRM_R_SIMD_W		( _IRA_OPERAND_MODRM_R_SIMD | _IRA_WRITE )
#define _IRA_OPERAND_MODRM_M_SIMD		_IRA_OPERAND_RM(IRA_NO_REG, _IRA_EOS_UNDEFINED, _IRA_EOS_EOSA, _IRA_RMF_M )
#define _IRA_OPERAND_MODRM_M_SIMD_W		( _IRA_OPERAND_MODRM_M_SIMD | _IRA_WRITE )

/* Externals. */

extern struct ira_instruction_desc _ira_instructions_desc[];

#endif // IRA_INT_H_INCLUDED
