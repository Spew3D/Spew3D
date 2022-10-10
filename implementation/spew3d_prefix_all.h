/* Spew3D is Copyright 2022 ell1e et al.

Permission is hereby granted, free of charge, to any person
obtaining a copy of this software and associated documentation
files (the "Software"), to deal in the Software without
restriction, including without limitation the rights to use,
copy, modify, merge, publish, distribute, sublicense, and/or
sell copies of the Software, and to permit persons to whom
the Software is furnished to do so, subject to the following
conditions:

The above copyright notice and this permission notice shall
be included in all copies or substantial portions of the
Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY
KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS
OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

// Some stuff that will be put at the start of spew3d.h before
// all external modules.

// XXX: Header-guard intentionally missing!

#if !defined(S3DEXP) && !defined(SPEW3D_OPTION_DISABLE_DLLEXPORT)
#if (defined(_WIN32) || defined(_WIN64))
#define S3DEXP __declspec(dllexport)
#if defined(__MINGW32__) || defined(__MINGW64__)
#define S3DHID __attribute__ ((visibility ("hidden")))
#endif
#else
#define S3DEXP __attribute__ ((visibility ("default")))
#define S3DHID __attribute__ ((visibility ("hidden")))
#endif
#endif

// Try to ensure 64bit file handling:
#define _FILE_OFFSET_BITS 64
#ifndef __USE_LARGEFILE64
#define __USE_LARGEFILE64 1
#endif
#ifndef _LARGEFILE64_SOURCE
#define _LARGEFILE64_SOURCE
#endif
#define _LARGEFILE_SOURCE

// For <stb/stb_image.h>:
#define STBI_NO_STDIO
#ifdef SPEW3D_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#endif

// For <miniz/miniz.h>:
#define MINIZ_NO_ZLIB_APIS
#define MINIZ_NO_ZLIB_COMPATIBLE_NAMES

// Some debug options:
#define DEBUG_SPEW3D_FS
#define DEBUG_SPEW3D_VFS
#define DEBUG_SPEW3D_TEXTURE


