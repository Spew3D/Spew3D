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

#ifndef SPEW3D_EVENT_H_
#define SPEW3D_EVENT_H_

#include <stdint.h>

enum S3DEventKind {
    S3DEV_INVALID = 0,

    S3DEV_WINDOW_CLOSED = 1,
    S3DEV_WINDOW_RESIZED,
    S3DEV_WINDOW_USER_CLOSE_REQUEST,

    S3DEV_MOUSE_MOVE,
    S3DEV_MOUSE_BUTTON_DOWN,
    S3DEV_MOUSE_BUTTON_UP,
    S3DEV_MOUSEWHEEL_SCROLL,
    S3DEV_KEY_DOWN,
    S3DEV_KEY_UP,

    S3DEV_APP_QUIT_REQUEST = 30,

    S3DEV_INTERNAL_CMD_WIN_OPEN = 10000,
    S3DEV_INTERNAL_CMD_WIN_UPDATECANVAS,
    S3DEV_INTERNAL_CMD_DRAWPRIMITIVE_WINFILL,
    S3DEV_INTERNAL_CMD_WIN_CLOSE,
    S3DEV_INTERNAL_CMD_WIN_DESTROY,
    S3DEV_INTERNAL_CMD_TEXDELETE,
    S3DEV_INTERNAL_CMD_TEXTURELOCK_LOCKPIXELSTOFINISH,
    S3DEV_INTERNAL_CMD_SPRITEDRAW,
    S3DEV_INTERNAL_CMD_CAM3D_DRAWTOWINDOW,

    S3DEV_DUMMY = 99999
};

enum S3DMouseButton {
    S3DEV_MOUSE_BUTTON_INVALID = 0,
    S3DEV_MOUSE_BUTTON_PRIMARY = 1,
    S3DEV_MOUSE_BUTTON_SECONDARY = 2,
    S3DEV_MOUSE_BUTTON_MIDDLE = 3
};

#define S3DEV_TYPE_IS_INTERNAL(x) \
    (((int)x) >= (int)S3DEV_INTERNAL_CMD_WIN_OPEN)

typedef uint64_t s3d_texture_t;
typedef struct s3d_obj3d s3d_obj3d;
typedef uint16_t s3d_key_t;

typedef struct s3d_event {
    int kind;
    union {
        union {
            /* PUBLIC EVENTS: */
            struct window {
                uint32_t win_id;
            } window;
            struct mouse {
                uint32_t win_id;
                s3dnum_t rel_x, rel_y;
                s3dnum_t x, y;
                int button;
            } mouse;
            struct mousewheel {
                uint32_t win_id;
                s3dnum_t x, y;
            } mousewheel;
            struct key {
                uint32_t win_id;
                s3d_key_t key;
            } key;
        };
        union {
            /* INTERNAL EVENTS: */
            struct drawprimitive {
                uint32_t win_id;
                s3dnum_t red, green, blue;
            } drawprimitive;
            struct texturelock {
                s3d_texture_t tid;
                uint64_t lock_request_id;
            } texturelock;
            struct texdelete {
                s3d_texture_t tid;
            } texdelete;
            struct spritedraw {
                uint32_t win_id;
                s3d_texture_t tid;
                int32_t pixel_x, pixel_y;
                int centered;
                s3dnum_t scale, angle, tint_red, tint_green, tint_blue;
                s3dnum_t transparency;
                int withalphachannel;
            } spritedraw;
            struct cam3d {
                uint32_t win_id;
                s3d_obj3d *obj_ref;
            } cam3d;
        };
    };
} s3d_event;

typedef struct s3d_equeue s3d_equeue;

S3DEXP s3d_equeue *spew3d_event_GetMainQueue();

S3DHID s3d_equeue *_spew3d_event_GetInternalQueue();

S3DEXP s3d_equeue *spew3d_event_q_Create();

S3DEXP int spew3d_event_q_Insert(s3d_equeue *eq, const s3d_event *ev);

S3DEXP int spew3d_event_q_IsEmpty(s3d_equeue *eq);

S3DEXP int spew3d_event_q_Pop(s3d_equeue *eq, s3d_event *writeto);

S3DEXP void spew3d_event_q_Free(s3d_equeue *ev);

S3DEXP void spew3d_event_UpdateMainThread();

#endif  // SPEW3D_EVENT_H_

