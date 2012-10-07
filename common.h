/*
 * common.h
 *
 *  Created on: 07-10-2012
 *      Author: Slawomir Wojtasiak
 */

#ifndef COMMON_H_
#define COMMON_H_

#include <inttypes.h>

#include "ira.h"

/* Constants. */

/* Size directives */

#define _IRA_OS_BYTE		8
#define _IRA_OS_WORD		16
#define _IRA_OS_DWORD		32
#define _IRA_OS_FWORD		48
#define _IRA_OS_QWORD		64
#define _IRA_OS_MMWORD		64
#define _IRA_OS_TBYTE		80
#define _IRA_OS_OWORD		128
#define _IRA_OS_XMMWORD		128

/* Methods. */

unit8_t _ira_common_decode_size_directive();

#endif /* COMMON_H_ */
