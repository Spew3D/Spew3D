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

#ifndef SPEW3D_MATH3D_H_
#define SPEW3D_MATH3D_H_

typedef struct spew3d_pos {
    double x, y, z;
} spew3d_pos;

typedef struct spew3d_rotation {
    double hori, verti, roll;
} spew3d_rotation;


static inline void spew3d_math3d_add(
        spew3d_pos *p, spew3d_pos *p2
        ) {
    p->x += p2->x;
    p->y += p2->y;
    p->z += p2->z;
}

static inline void spew3d_math3d_rotate(
        spew3d_pos *p, spew3d_rotation *r
        ) {
    /// Rotate a given pos around its origin by the given degrees.
    /// Positive angle gives CW (clockwise) rotation.
    /// X is forward (into screen), Y is left, Z is up.

    double roth = (r->hori / 180.0) * M_PI;
    double rotv = (r->verti / 180.0) * M_PI;
    double rotr = (r->roll / 180.0) * M_PI;
    double newx, newy, newz;

    // Roll angle:
    newy = (p->y) * cos(rotr) + (p->z) * sin(rotr);
    newz = (p->z) * cos(rotr) - (p->y) * sin(rotr);
    p->z = newz;
    p->y = newy;

    // Vertical angle:
    newz = (p->z) * cos(rotv) + (p->x) * sin(rotv);
    newx = (p->x) * cos(rotv) - (p->z) * sin(rotv);
    p->x = newx;
    p->z = newz;

    // Horizontal angle:
    newy = (p->y) * cos(roth) + (p->x) * sin(roth);
    newx = (p->x) * cos(roth) - (p->y) * sin(roth);
    p->x = newx;
    p->y = newy;
}

#endif  // SPEW3D_MATH3D_H_
