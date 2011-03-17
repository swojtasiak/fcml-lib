#ifndef IRA_H_INCLUDED
#define IRA_H_INCLUDED

#include <stdint.h>

#define _IRA_OPERANDS_COUNT						4
#define _IRA_PREFIXES_COUNT						12

/* Registers */

#define _IRA_REG_AL		0
#define _IRA_REG_AX		0
#define _IRA_REG_EAX	0
#define _IRA_REG_RAX	0
#define _IRA_REG_MM0	0
#define _IRA_REG_XMM0	0

#define _IRA_REG_CL		1
#define _IRA_REG_CX		1
#define _IRA_REG_ECX	1
#define _IRA_REG_RCX	1
#define _IRA_REG_MM1	1
#define _IRA_REG_XMM1	1

#define _IRA_REG_DL		2
#define _IRA_REG_DX		2
#define _IRA_REG_EDX	2
#define _IRA_REG_RDX	2
#define _IRA_REG_MM2	2
#define _IRA_REG_XMM2	2

#define _IRA_REG_BL		3
#define _IRA_REG_BX		3
#define _IRA_REG_EBX	3
#define _IRA_REG_RBX	3
#define _IRA_REG_MM3	3
#define _IRA_REG_XMM3	3

#define _IRA_REG_AH		4
#define _IRA_REG_SP		4
#define _IRA_REG_ESP	4
#define _IRA_REG_RSP	4
#define _IRA_REG_MM4	4
#define _IRA_REG_XMM4	4

#define _IRA_REG_CH		5
#define _IRA_REG_BP		5
#define _IRA_REG_EBP	5
#define _IRA_REG_RBP	5
#define _IRA_REG_MM5	5
#define _IRA_REG_XMM5	5

#define _IRA_REG_DH		6
#define _IRA_REG_SI		6
#define _IRA_REG_ESI	6
#define _IRA_REG_RSI	6
#define _IRA_REG_MM6	6
#define _IRA_REG_XMM6	6

#define _IRA_REG_BH		7
#define _IRA_REG_DI		7
#define _IRA_REG_EDI	7
#define _IRA_REG_RDI	7
#define _IRA_REG_MM7	7
#define _IRA_REG_XMM7	7

#define _IRA_REG_R8L	8
#define _IRA_REG_R8W	8
#define _IRA_REG_R8D	8
#define _IRA_REG_R8		8
#define _IRA_REG_XMM8	8

#define _IRA_REG_R9L	9
#define _IRA_REG_R9W	9
#define _IRA_REG_R9D	9
#define _IRA_REG_R9		9
#define _IRA_REG_XMM9	9

#define _IRA_REG_R10L	10
#define _IRA_REG_R10W	10
#define _IRA_REG_R10D	10
#define _IRA_REG_R10	10
#define _IRA_REG_XMM10	10

#define _IRA_REG_R11L	11
#define _IRA_REG_R11W	11
#define _IRA_REG_R11D	11
#define _IRA_REG_R11	11
#define _IRA_REG_XMM11	11

#define _IRA_REG_R12L	12
#define _IRA_REG_R12W	12
#define _IRA_REG_R12D	12
#define _IRA_REG_R12	12
#define _IRA_REG_XMM12	12

#define _IRA_REG_R13L	13
#define _IRA_REG_R13W	13
#define _IRA_REG_R13D	13
#define _IRA_REG_R13	13
#define _IRA_REG_XMM13	13

#define _IRA_REG_R14L	14
#define _IRA_REG_R14W	14
#define _IRA_REG_R14D	14
#define _IRA_REG_R14	14
#define _IRA_REG_XMM14	14

#define _IRA_REG_R15L	15
#define _IRA_REG_R15W	15
#define _IRA_REG_R15D	15
#define _IRA_REG_R15	15
#define _IRA_REG_XMM15	15

enum ira_operation_mode {
	IRA_MOD_16BIT,
	IRA_MOD_32BIT,
	// IA32/IA32e.
	IRA_MOD_64BIT
};

enum ira_result_code {
	RC_OK = 0,
	RC_ERROR_ILLEGAL_OPERATION_MODE,
	RC_ERROR_ILLEGAL_ADDRESS_ATTRIBUTE_SIZE,
	// When disassembler is not able to disassemble instruction due to incomplete data in stream.
	RC_ERROR_INSTRUCTION_INCOMPLETE,
	RC_ERROR_OUT_OF_MEMORY,
	RC_ERROR_UNEXPECTED_INTERNAL_ERROR
};

enum ira_operand_type {
	IRA_NONE = 0,
	IRA_IMMEDIATE_ADDRESS,
	IRA_IMMEDIATE_DATA_8,
	IRA_IMMEDIATE_DATA_16,
	IRA_IMMEDIATE_DATA_32,
	IRA_IMMEDIATE_DATA_64,
	IRA_GPR
};

enum ira_register_type {
	IRA_NO_REG = 0,
	IRA_REG_GPR_8,
	IRA_REG_GPR_16,
	IRA_REG_GPR_32,
	IRA_REG_GPR_64,
	IRA_REG_MMX,
	IRA_REG_XMM,
	IRA_REG_GPR
};

/* Common structure to describe register. */
struct ira_register {
	// Type of the register encoded in next field.
	enum ira_register_type reg_type;
	// Register.
	int reg;
};

/* Constants describing allowed values of operand size attribute. */
#define _IRA_OSA_16		16
#define _IRA_OSA_32		32
#define _IRA_OSA_64		64

/* Constants describing allowed values of address size attribute. */
#define _IRA_ASA_16		16
#define _IRA_ASA_32		32
#define _IRA_ASA_64		64

struct ira_disassemble_info {
	/* Architecture. */
	enum ira_operation_mode mode;
	/* Operand size attribute. */
	uint16_t operand_size_attribute;
	/* Address size attribute. */
	uint16_t address_size_attribute;
	/* Address of the code to disassemble. */
	void *address;
	/* Size of the data to disassemble. */
	uint32_t size;
};

union ira_immediate_data {
	uint8_t immediate_8;
	uint16_t immediate_16;
	uint32_t immediate_32;
	uint64_t immediate_64;
};

enum ira_displacement_type {
	IRA_NO_DISPLACEMENT,
	IRA_DISPLACEMENT_8 = 8,
	IRA_DISPLACEMENT_16 = 16,
	IRA_DISPLACEMENT_32 = 32,
};

/* Size of the displacement after sign extending. */
enum ira_displacement_extension_size {
	IRA_DISPLACEMENT_EXT_SIZE_16 = 16,
	IRA_DISPLACEMENT_EXT_SIZE_32 = 32,
	IRA_DISPLACEMENT_EXT_SIZE_64 = 64
};

union ira_displacement_value {
	uint8_t displacement_8;
	uint16_t displacement_16;
	uint32_t displacement_32;
};

struct ira_displacement {
	// Size of the displacement value.
	enum ira_displacement_type displacement_type;
	// Size of the displacement after sign extending.
	enum ira_displacement_extension_size extension_size;
	// Displacement value.
	union ira_displacement_value displacement;
};

struct ira_instruction_operand {
	/* Type of operand. */
	enum ira_operand_type operand_type;
	/* Place for immediate data. */
	union ira_immediate_data immediate;
};

struct ira_instruction_prefix {
	/* Prefix itself. */
	uint8_t prefix;
	/* Type of prefix, see enumeration above. */
	uint8_t prefix_type;
	/* 1 if prefix can be treated as mandatory one. */
	uint8_t mandatory_prefix;
};

struct ira_disassemble_result {
	/* Disassemblation result code. */
	enum ira_result_code code;
	/* Mnemonic */
	char *mnemonic;
	// Number of prefixes.
	uint8_t prefixes_count;
	// Prefixes.
	struct ira_instruction_prefix prefixes[_IRA_PREFIXES_COUNT];
	// Number of opcode bytes.
	uint8_t opcodes_count;
	// Opcode bytes without mandatory prefixes.
	uint8_t opcodes[3];
	/* Disassembled operands. */
	struct ira_instruction_operand operands[_IRA_OPERANDS_COUNT];
};

void ira_init(void);

void ira_disassemble(struct ira_disassemble_info *info,
		struct ira_disassemble_result *result);

void ira_deinit(void);

#endif // IRA_H_INCLUDED
