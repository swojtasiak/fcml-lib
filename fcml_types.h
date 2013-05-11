/*
 * fcml_types.h
 *
 *  Created on: 02-03-2013
 *      Author: tAs
 */

#ifndef FCML_TYPES_H_
#define FCML_TYPES_H_

#include <stddef.h>
#include <stdint.h>

typedef uint8_t fcml_bool;
typedef int8_t fcml_int8_t;
typedef uint8_t fcml_uint8_t;
typedef int16_t fcml_int16_t;
typedef uint16_t fcml_uint16_t;
typedef int32_t fcml_int32_t;
typedef uint32_t fcml_uint32_t;
typedef int64_t fcml_int64_t;
typedef uint64_t fcml_uint64_t;

typedef char fcml_char;
typedef char* fcml_string;
typedef float fcml_float;
typedef uint8_t fcml_data_size;
typedef void* fcml_ptr;

typedef unsigned int fcml_usize;
typedef int fcml_size;

#define FCML_TRUE   1
#define FCML_FALSE   0

/*Signed integers.*/
#define FCML_INT32_MAX	INT32_MAX
#define FCML_INT32_MIN	INT32_MIN

/*Unsigned integers.*/
#define FCML_UINT8_MAX	UINT8_MAX
#define FCML_UINT16_MAX	UINT16_MAX
#define FCML_UINT32_MAX	UINT32_MAX

#endif /* FCML_TYPES_H_ */
