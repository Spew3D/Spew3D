/* Copyright (c) 2024, ellie/@ell1e & Spew3D Team (see AUTHORS.md).

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

#ifndef SPEW3D_CAMERA3D_H_
#define SPEW3D_CAMERA3D_H_

#include <stdint.h>

typedef struct s3d_event s3d_event;
typedef struct s3d_window s3d_window;
typedef struct s3d_scene3d s3d_scene3d;
typedef struct s3d_rotation s3d_rotation;
typedef struct s3d_pos s3d_pos;
typedef struct s3d_point s3d_point;
typedef uint32_t s3d_material_t;
typedef uint64_t s3d_texture_t;

S3DEXP s3d_obj3d *spew3d_camera3d_CreateForScene(
    s3d_scene3d *scene
);

S3DEXP void spew3d_camera3d_RenderToWindow(
    s3d_obj3d *cam, s3d_window *win
);

S3DEXP void spew3d_camera3d_SetFOV(
    s3d_obj3d *cam, double fov
);

typedef struct s3d_renderpolygon {
    s3d_pos vertex_pos[3];
    s3d_pos vertex_pos_pixels[3];
    s3d_pos center;
    double min_depth, max_depth;
    s3d_pos vertex_normal[3];
    s3d_point vertex_texcoord[3];
    s3d_color vertex_emit[3];
    s3d_material_t polygon_material;
    s3d_texture_t polygon_texture;
    uint8_t clipped;
} s3d_renderpolygon;

S3DEXP int spew3d_camera_InternalMainThreadProcessEvent(
    s3d_event *e
);

S3DEXP void _internal_spew3d_camera3d_UpdateRenderPolyData(
    s3d_renderpolygon *rqueue,
    uint32_t index
);

#endif  // SPEW3D_CAMERA3D_H_

