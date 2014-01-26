/*
 * fcml_trace.h
 *
 *  Created on: 23 lip 2013
 *      Author: tAs
 */

#ifndef FCML_TRACE_H_
#define FCML_TRACE_H_

#include "stdio.h"

#ifdef FCML_DEBUG
#define FCML_TRACE(pattern, ...) { printf("%s:%d ", __FILE__,  __LINE__); printf(pattern, ##__VA_ARGS__); printf("\n");}
#define FCML_TRACE_MSG(msg) { printf("%s:%d ", __FILE__,  __LINE__); printf("%s\n", message); }
#else
#define FCML_TRACE(pattern, ...)
#define FCML_TRACE_MSG(msg)
#endif

#endif /* FCML_TRACE_H_ */
