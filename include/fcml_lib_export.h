/*
 * fcml_lib_export.h
 *
 *  Created on: Feb 3, 2014
 *      Author: tas
 */

#ifndef FCML_LIB_EXPORT_H_
#define FCML_LIB_EXPORT_H_

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#ifdef _WIN32 || __CYGWIN__
#if FCML_BUILD_LIB
#define LIB_EXPORT __stdcall __declspec(dllexport)
#else
#define LIB_EXPORT __stdcall __declspec(dllimport)
#endif
#else
#define LIB_EXPORT
#endif

#endif /* FCML_LIB_EXPORT_H_ */
