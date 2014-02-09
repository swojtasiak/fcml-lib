#pragma once

// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the HSDIS_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// HSDIS_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.

#ifdef HSDIS_EXPORTS
#define HSDIS_API __declspec(dllexport)
#else
#define HSDIS_API __declspec(dllimport)
#endif

#define HSDIS_CALL  __cdecl

#ifdef __cplusplus
extern "C" {
#endif

typedef void* (*jvm_event_callback)(void *env_pv, const char *ev, void *arg);
typedef int (*jvm_printf_callback)(void *env_pv, const char *format, ...);

HSDIS_API void* HSDIS_CALL decode_instructions( void* start, void* end, jvm_event_callback, void* event_stream, jvm_printf_callback, void* printf_stream, const char* options );

#ifdef __cplusplus
}
#endif
