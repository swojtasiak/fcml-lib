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

#if _WIN32 || __CYGWIN__
#define LIB_CALL   __stdcall
#ifdef DLL_EXPORT
#define LIB_EXPORT __declspec(dllexport)
#else
#ifdef LIBFCML_DLL_IMPORT
#define LIB_EXPORT __declspec(dllimport)
#endif
#endif
#endif

#ifndef LIB_EXPORT
#define LIB_EXPORT
#endif

#ifndef LIB_CALL
#define LIB_CALL
#endif

#endif /* FCML_LIB_EXPORT_H_ */
