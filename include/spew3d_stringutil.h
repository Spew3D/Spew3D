/* Copyright (c) 2023, ellie/@ell1e & Spew3D Team (see AUTHORS.md).

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice,
   this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.

Alternatively, at your option, this file is offered under the Apache 2
license, see accompanied LICENSE.md.
*/

#ifndef SPEW3D_STRINGUTIL_H_
#define SPEW3D_STRINGUTIL_H_

#include <stdint.h>

/** Frees any string arrays e.g. created by
 *  spew3d_stringutil_ArrayFromLines(). */
S3DEXP void spew3d_stringutil_FreeArray(char **array);

/* Reverse the bytes inside a byte buffer in-place. */
S3DEXP void spew3d_stringutil_ReverseBufBytes(
    char *buf, const uint64_t buflen
);

/* Reverse the bytes inside the string in-place. */
S3DEXP void spew3d_stringutil_ReverseBytes(char *s);

/** A helper function to read a file from disk or the integrated VFS
 *  and to split it up into a string array line by line. If null bytes
 *  are encountered, they are converted to space characters as to not
 *  terminate the C string of a line early. Returns the string array,
 *  where the last entry is NULL. Sets output_len to the entries in
 *  the array, not counting the last NULL entry. Once you are done
 *  with the array, use spew3d_stringutil_FreeArray() to free it.
 */
S3DEXP char **spew3d_stringutil_ArrayFromLines(
    const char *filepath, int vfsflags, int64_t *output_len
);

#endif  // SPEW3D_STRINGUTIL_H_

