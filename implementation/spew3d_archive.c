

#ifdef SPEW_IMPLEMENTATION

#define _FILE_OFFSET_BITS 64
#ifndef __USE_LARGEFILE64
#define __USE_LARGEFILE64 1
#endif
#ifndef _LARGEFILE64_SOURCE
#define _LARGEFILE64_SOURCE
#endif
#define _LARGEFILE_SOURCE
#if defined(_WIN32) || defined(_WIN64)
#define fseek64 _fseeki64
#define ftell64 _ftelli64
#else
#define fseek64 fseeko64
#define ftell64 ftello64
#endif

#include <stdio.h>
#undef MZ_FILE
#define MZ_FILE FILE
#include <errno.h>
#include <stdint.h>
#include <stdlib.h>


#endif  // SPEW_IMPLEMENTATION

