/* Copyright (c) 2020-2022, ellie/@ell1e & Spew3D Team (see AUTHORS.md).

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

#ifdef SPEW3D_IMPLEMENTATION

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>


//#define _SPEW3D_BIGINT_DEBUG


S3DEXP int spew3d_bignum_VerifyStrFloatBuf(
        const char *v, size_t vlen
        ) {
    if (vlen == 0)
        return 0;
    if (*v == '-') {
        if (vlen <= 1)
            return 0;
        v++;
        vlen--;
    }

    int haddot = 0;
    const char *vstart = v;
    const char *vend = v + (uintptr_t)vlen;
    while (v != vend) {
        if ((*v < '0' || *v > '9') && *v != '.')
            return 0;
        if (*v == '.') {
            if (v == vstart || haddot || (v + 1 == vend))
                return 0;
            haddot = 1;
        }
        v++;
    }
    return 1;
}

S3DEXP int spew3d_bignum_VerifyStrFloat(
        const char *v) {
    return spew3d_bignum_VerifyStrFloatBuf(
        v, strlen(v)
    );
}

S3DEXP int spew3d_bignum_VerifyStrIntBuf(
        const char *v, size_t vlen
        ) {
    if (vlen == 0)
        return 0;
    if (*v == '-') {
        if (vlen <= 1)
            return 0;
        v++;
        vlen--;
    }

    const char *vend = v + (uintptr_t)vlen;
    while (v != vend) {
        if (*v < '0' || *v > '9')
            return 0;
        v++;
    }
    return 1;
}

S3DEXP int spew3d_bignum_VerifyStrInt(
        const char *v) {
    return spew3d_bignum_VerifyStrIntBuf(v, strlen(v));
}

S3DEXP int spew3d_bignum_CompareStrInts(
        const char *v1, const char *v2
        ) {
    return spew3d_bignum_CompareStrIntsBuf(
        v1, strlen(v1), v2, strlen(v2)
    );
}

S3DEXP int spew3d_bignum_CompareStrIntsBuf(
        const char *v1, size_t v1len,
        const char *v2, size_t v2len
        ) {
    assert(spew3d_bignum_VerifyStrIntBuf(v1, v1len) &&
           spew3d_bignum_VerifyStrIntBuf(v2, v2len));

    if (v1len == 2 && memcmp(v1, "-0", 2) == 0)
        return spew3d_bignum_CompareStrIntsBuf(
            v1 + 1, v1len - 1, v2, v2len);
    if (v2len == 2 && memcmp(v2, "-0", 2) == 0)
        return spew3d_bignum_CompareStrIntsBuf(
            v1, v1len, v2 + 1, v2len - 1);

    if (v1[0] == '-') {
        if (v2[0] != '-') {
            if (v1[1] != '0' ||
                    spew3d_bignum_CompareStrIntsBuf(
                        v1 + 1, v1len - 1, "0", 1) != 0
                    )
                return -1;
            return spew3d_bignum_CompareStrIntsBuf(
                "0", 1, v2, v2len
            );
        }
        return -spew3d_bignum_CompareStrIntsBuf(
            v1 + 1, v1len - 1, v2 + 1, v2len - 1
        );
    } else if (v2[0] == '-') {
        if (v2[1] != '0' ||
                spew3d_bignum_CompareStrIntsBuf(
                    "0", 1, v2 + 1, v2len - 1
                ) != 0)
            return 1;
        return spew3d_bignum_CompareStrIntsBuf(
            v1, v1len, "0", 1
        );
    }
    assert(v1[0] != '-' && v2[0] != '-');

    while (v1len > 1 && *v1 == '0') {
        v1++;
        v1len--;
    }
    while (v2len > 1 && *v2 == '0') {
        v2++;
        v2len--;
    }

    if (v1len > v2len)
        return 1;
    else if (v1len < v2len)
        return -1;

    const uint8_t *p1end = ((uint8_t*)v1) + (uintptr_t)v1len;
    const uint8_t *p1 = (uint8_t*)v1;
    const uint8_t *p2 = (uint8_t*)v2;
    while (p1 != p1end) {
        if ((*p1) > (*p2))
            return 1;
        else if ((*p1) < (*p2))
            return -1;
        p1++;
        p2++;
    }
    return 0;
}

S3DEXP int spew3d_bignum_CompareStrFloats(
        const char *v1, const char *v2
        ) {
    return spew3d_bignum_CompareStrFloatsBuf(
        v1, strlen(v1), v2, strlen(v2)
    );
}

S3DEXP int spew3d_bignum_CompareStrFloatsBuf(
        const char *v1, size_t v1len,
        const char *v2, size_t v2len
        ) {
    assert(spew3d_bignum_VerifyStrFloatBuf(v1, v1len) &&
           spew3d_bignum_VerifyStrFloatBuf(v2, v2len));

    size_t dot1 = v1len;
    size_t dot2 = v2len;
    const int iend = ((v1len > v2len) ? v1len : v2len);
    size_t i = 1;
    while (i < iend) {
        if (i < v1len && v1[i] == '.') {
            assert(dot1 == v1len);
            dot1 = i;
        }
        if (i < v2len && v2[i] == '.') {
            assert(dot2 == v2len);
            dot2 = i;
        }
        i++;
    }

    int result = spew3d_bignum_CompareStrIntsBuf(
        v1, dot1, v2, dot2
    );
    if (result != 0 || (dot1 == v1len && dot2 == v2len))
        return result;

    int v1neg = (v1[0] == '-');
    int v2neg = (v2[0] == '-');

    const char *zerobuf = "0";
    size_t zerobuflen = 1;
    if (dot1 == v1len) {
        assert(dot2 < v2len && dot2 >= 1);
        v1 = zerobuf;
        v1len = zerobuflen;
        v2 += dot2 + 1;
        v2len -= dot2 + 1;
    } else if (dot2 == v2len) {
        assert(dot1 < v1len && dot1 >= 1);
        v2 = zerobuf;
        v2len = zerobuflen;
        v1 += dot1 + 1;
        v1len -= dot1 + 1;
    } else {
        v2 += dot2 + 1;
        v2len -= dot2 + 1;
        v1 += dot1 + 1;
        v1len -= dot1 + 1;
    }

    while (v1len > 1 && v1[v1len - 1] == '0')
        v1len--;
    while (v2len > 1 && v2[v2len - 1] == '0')
        v2len--;
    size_t minlen = ((v1len < v2len) ? v1len : v2len);

    result = spew3d_bignum_CompareStrIntsBuf(
        v1, minlen, v2, minlen
    );
    if (result == 0) {
        if (v1len > v2len) {
            result = 1;
        } else if (v2len > v1len) {
            result = -1;
        } else {
            return 0;
        }
    }
    if (!v1neg && !v2neg)
        return result;
    if (v1neg && v2neg)
        return -result;
    if (v1neg)
        return -1;
    else
        return 1;
}

#endif  // SPEW3D_IMPLEMENTATION

