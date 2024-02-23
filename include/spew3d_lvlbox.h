/* Copyright (c) 2020-2024, ellie/@ell1e & Spew3D Team (see AUTHORS.md).

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

#ifndef SPEW3D_LVLBOX_H_
#define SPEW3D_LVLBOX_H_

#define LVLBOX_CHUNK_SIZE 6
#define LVLBOX_TILE_SIZE 1.0
#define LVLBOX_DEFAULT_TILE_HEIGHT 2.0

typedef struct s3d_resourceload_job s3d_resourceload_job;
typedef uint64_t s3d_texture_t;

typedef struct s3d_lvlbox_texinfo {
    char *name;
    int vfs_flags;
    s3d_texture_t id;
    s3dnum_t scale_x, scale_y;
    s3dnum_t scroll_speed_x, scroll_speed_y;
} s3d_lvlbox_texinfo;

typedef struct s3d_lvlbox_fenceinfo {
    int fence_set, fence_hasalpha, fence_passable;
    double fence_height;
    s3d_lvlbox_texinfo fence_tex;
} s3d_lvlbox_fenceinfo;

typedef struct s3d_lvlbox_wallinfo {
    s3d_lvlbox_texinfo main_tex;

    int has_top_part;
    s3d_lvlbox_texinfo top_part_tex;

    s3d_lvlbox_fenceinfo fence;

    int has_bottom_part;
    s3d_lvlbox_texinfo bottom_part_tex;
} s3d_lvlbox_wallinfo;

typedef struct s3d_lvlbox_vertsegment {
    s3d_lvlbox_texinfo floor_tex;
    s3dnum_t floor_z[4];

    s3d_lvlbox_wallinfo wall[4];
    s3d_lvlbox_wallinfo ceilingwall[4];

    s3d_lvlbox_texinfo ceiling_tex;
    s3dnum_t ceiling_z[4];
} s3d_lvlbox_vertsegment;

typedef struct s3d_lvlbox_tile {
    int occupied;

    s3d_lvlbox_vertsegment *segment;
    int segment_count;
} s3d_lvlbox_tile;

typedef struct s3d_lvlbox_chunk {
    s3d_lvlbox_tile tile[LVLBOX_CHUNK_SIZE *
        LVLBOX_CHUNK_SIZE];
} s3d_lvlbox_chunk;

typedef struct s3d_lvlbox {
    s3d_pos offset;

    s3d_lvlbox_chunk *chunk;
    uint32_t chunk_count, chunk_extent_x;

    void *_internal;
} s3d_lvlbox;

S3DEXP s3d_lvlbox *spew3d_lvlbox_New(
    const char *default_tex, int default_tex_vfs_flags
);

S3DEXP void spew3d_lvlbox_Destroy(
    s3d_lvlbox *lvlbox
);

S3DEXP int32_t spew3d_lvlbox_WorldPosToChunkIndex(
    s3d_lvlbox *lvlbox, s3d_pos pos, int ignore_lvlbox_offset
);

S3DEXP int spew3d_lvlbox_WorldPosToTilePos(
    s3d_lvlbox *lvlbox, s3d_pos pos, int ignore_lvlbox_offset,
    int32_t *out_chunk_idx, int32_t *out_tile_idx,
    s3d_pos *out_tile_lower_bound,
    s3d_pos *out_tile_pos_offset,
    int32_t *out_segment_no
);

S3DEXP double spew3d_lvlbox_TileFloorHeightAtInSegment(
    s3d_lvlbox *lvlbox, s3d_pos local_pos,
    int32_t chunk_idx,
    int32_t tile_idx, int segment_no
);

S3DEXP int spew3d_lvlbox_ExpandToPosition(
    s3d_lvlbox *box, s3d_pos pos
);

S3DEXP int spew3d_lvlbox_SetFloorTextureAt(
    s3d_lvlbox *lvlbox, s3d_pos pos,
    const char *texname, int vfsflags
);

S3DEXP s3d_resourceload_job *spew3d_lvlbox_FromMapFile(
    const char *map_file_path, int map_file_vfs_flags,
    int create_file_if_missing
);

S3DEXP s3d_lvlbox *spew3d_lvlbox_FromMapFileFinalize(
    s3d_resourceload_job *job
);

S3DEXP s3d_resourceload_job *spew3d_lvlbox_ToMapFile(
    s3d_lvlbox *lvlbox,
    const char *map_file_path, int map_file_vfs_flags
);

S3DEXP char *spew3d_lvlbox_ToString(
    s3d_lvlbox *lvlbox, uint32_t *out_slen
);

S3DEXP s3d_lvlbox *spew3d_lvlbox_FromString(
    const char *s, uint32_t slen
);

#endif  // SPEW3D_LVLBOX_H_
