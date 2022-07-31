
#ifdef SPEW3D_IMPLEMENTATION

#include <SDL2/SDL.h>
#include <string.h>


int _internal_spew3d_geometry_AddVertexPolyAlloc(
        spew3d_geometry *geometry,
        int add_vertex, int add_polygon
        ) {
    spew3d_pos *new_vertex = realloc(
        geometry->vertex,
        sizeof(*new_vertex) *
        (geometry->vertex_count + add_vertex)
    );
    if (!new_vertex)
        return 0;
    geometry->vertex = new_vertex;
    spew3d_pos *new_normal = realloc(
        geometry->polygon_normal,
        sizeof(*new_normal) *
        (geometry->polygon_count + add_polygon * 3)
    );
    if (!new_normal)
        return 0;
    geometry->polygon_normal = new_normal;
    int32_t *new_vertexindex = realloc(
        geometry->polygon_vertexindex,
        sizeof(*new_vertexindex) *
        (geometry->polygon_count + add_polygon * 3)
    );
    if (!new_vertexindex)
        return 0;
    geometry->polygon_vertexindex = new_vertexindex;
    spew3d_material_t *new_material = realloc(
        geometry->polygon_material,
        sizeof(*new_material) *
        (geometry->polygon_count + add_polygon)
    );
    if (!new_material)
        return 0;
    geometry->polygon_material = new_material;
    spew3d_point *new_texcoord = realloc(
        geometry->polygon_texcoord,
        sizeof(*new_texcoord) *
        (geometry->polygon_count + add_polygon * 3)
    );
    if (!new_texcoord)
        return 0;
    geometry->polygon_texcoord = new_texcoord;
    spew3d_texture_t *new_texture = realloc(
        geometry->polygon_texture,
        sizeof(*new_texture) *
        (geometry->polygon_count + add_polygon)
    );
    if (!new_vertexindex)
        return 0;
    geometry->polygon_texture = new_texture;
    return 1;
}


spew3d_geometry *spew3d_geometry_Create() {
    spew3d_geometry *geometry = malloc(sizeof(*geometry));
    if (!geometry)
        return NULL;

    memset(geometry, 0, sizeof(*geometry));
    return geometry;
}


int spew3d_geometry_AddCube(
        spew3d_geometry *geometry,
        double edge_width,
        spew3d_pos *offset,
        spew3d_rotation *rotation,
        spew3d_point *side_texcoord,
        spew3d_texture_t *side_texture,
        int *side_texture_owned
        ) {
    if (!_internal_spew3d_geometry_AddVertexPolyAlloc(
            geometry, 8, 12
            )) {
        return 0;
    }

    const double halfedgewidth = (edge_width / 2.0);
    int viter = geometry->vertex_count - 8;
    const int viterstart = viter;
    while (viter < geometry->vertex_count) {
        const int relidx = (viter - viterstart);
        spew3d_pos finaloffset = {0};
        finaloffset.z = (
            (relidx >= 4) ? -halfedgewidth : halfedgewidth
        );
        finaloffset.x = (
            (relidx == 0 || relidx == 3 || relidx == 4 ||
            relidx == 7) ? halfedgewidth : -halfedgewidth
        );
        finaloffset.y = (
            (relidx == 0 || relidx == 1 || relidx == 4 ||
            relidx == 5) ? halfedgewidth : -halfedgewidth
        );
        spew3d_math3d_rotate(&finaloffset, rotation);
        spew3d_math3d_add(&finaloffset, offset);
        geometry->vertex[viter] = finaloffset;
        viter++;
    }

    const int poffset = geometry->polygon_count - 12;
    int32_t *vindex = geometry->polygon_vertexindex;
    spew3d_point *txcoord = geometry->polygon_texcoord;

    // Forward / X+ side
    vindex[poffset * 3 + 0] = 0;  // bottom left
    vindex[poffset * 3 + 1] = 5;  // top right
    vindex[poffset * 3 + 2] = 1;  // bottom right
    txcoord[poffset * 3 + 0] = side_texcoord[3];
    txcoord[poffset * 3 + 1] = side_texcoord[1];
    txcoord[poffset * 3 + 2] = side_texcoord[2];
    vindex[poffset * 3 + 3] = 0;  // bottom left
    vindex[poffset * 3 + 4] = 4;  // top left
    vindex[poffset * 3 + 5] = 5;  // top right
    txcoord[poffset * 3 + 0] = side_texcoord[3];
    txcoord[poffset * 3 + 1] = side_texcoord[0];
    txcoord[poffset * 3 + 2] = side_texcoord[1];

    // Right / Y- side
    vindex[poffset * 3 + 0] = 0;  // bottom left
    vindex[poffset * 3 + 1] = 5;  // top right
    vindex[poffset * 3 + 2] = 1;  // bottom right
    txcoord[poffset * 3 + 0] = side_texcoord[4 + 3];
    txcoord[poffset * 3 + 1] = side_texcoord[4 + 1];
    txcoord[poffset * 3 + 2] = side_texcoord[4 + 2];
    vindex[poffset * 3 + 3] = 0;  // bottom left
    vindex[poffset * 3 + 4] = 4;  // top left
    vindex[poffset * 3 + 5] = 5;  // top right
    txcoord[poffset * 3 + 0] = side_texcoord[4 + 3];
    txcoord[poffset * 3 + 1] = side_texcoord[4 + 0];
    txcoord[poffset * 3 + 2] = side_texcoord[4 + 1];

    // Backward / X- side
    vindex[poffset * 3 + 0] = 0;  // bottom left
    vindex[poffset * 3 + 1] = 5;  // top right
    vindex[poffset * 3 + 2] = 1;  // bottom right
    txcoord[poffset * 3 + 0] = side_texcoord[8 + 3];
    txcoord[poffset * 3 + 1] = side_texcoord[8 + 1];
    txcoord[poffset * 3 + 2] = side_texcoord[8 + 2];
    vindex[poffset * 3 + 3] = 0;  // bottom left
    vindex[poffset * 3 + 4] = 4;  // top left
    vindex[poffset * 3 + 5] = 5;  // top right
    txcoord[poffset * 3 + 0] = side_texcoord[8 + 3];
    txcoord[poffset * 3 + 1] = side_texcoord[8 + 0];
    txcoord[poffset * 3 + 2] = side_texcoord[8 + 1];

    // Left / Y+ side
    vindex[poffset * 3 + 0] = 0;  // bottom left
    vindex[poffset * 3 + 1] = 5;  // top right
    vindex[poffset * 3 + 2] = 1;  // bottom right
    txcoord[poffset * 3 + 0] = side_texcoord[12 + 3];
    txcoord[poffset * 3 + 1] = side_texcoord[12 + 1];
    txcoord[poffset * 3 + 2] = side_texcoord[12 + 2];
    vindex[poffset * 3 + 3] = 0;  // bottom left
    vindex[poffset * 3 + 4] = 4;  // top left
    vindex[poffset * 3 + 5] = 5;  // top right
    txcoord[poffset * 3 + 0] = side_texcoord[12 + 3];
    txcoord[poffset * 3 + 1] = side_texcoord[12 + 0];
    txcoord[poffset * 3 + 2] = side_texcoord[12 + 1];

    // Top / Z+ side
    vindex[poffset * 3 + 0] = 0;  // bottom left
    vindex[poffset * 3 + 1] = 5;  // top right
    vindex[poffset * 3 + 2] = 1;  // bottom right
    txcoord[poffset * 3 + 0] = side_texcoord[16 + 3];
    txcoord[poffset * 3 + 1] = side_texcoord[16 + 1];
    txcoord[poffset * 3 + 2] = side_texcoord[16 + 2];
    vindex[poffset * 3 + 3] = 0;  // bottom left
    vindex[poffset * 3 + 4] = 4;  // top left
    vindex[poffset * 3 + 5] = 5;  // top right
    txcoord[poffset * 3 + 0] = side_texcoord[16 + 3];
    txcoord[poffset * 3 + 1] = side_texcoord[16 + 0];
    txcoord[poffset * 3 + 2] = side_texcoord[16 + 1];

    // Down / Z- side
    vindex[poffset * 3 + 0] = 0;  // bottom left
    vindex[poffset * 3 + 1] = 5;  // top right
    vindex[poffset * 3 + 2] = 1;  // bottom right
    txcoord[poffset * 3 + 0] = side_texcoord[20 + 3];
    txcoord[poffset * 3 + 1] = side_texcoord[20 + 1];
    txcoord[poffset * 3 + 2] = side_texcoord[20 + 2];
    vindex[poffset * 3 + 3] = 0;  // bottom left
    vindex[poffset * 3 + 4] = 4;  // top left
    vindex[poffset * 3 + 5] = 5;  // top right
    txcoord[poffset * 3 + 0] = side_texcoord[20 + 3];
    txcoord[poffset * 3 + 1] = side_texcoord[20 + 0];
    txcoord[poffset * 3 + 2] = side_texcoord[20 + 1];

    return 1;
}


int spew3d_geometry_AddCubeSimple(
        spew3d_geometry *geometry,
        double edge_width,
        spew3d_texture_t texture,
        int texture_owned
        ) {
    spew3d_point coords[4 * 6];
    int texture_owned_flag[6];
    spew3d_texture_t textures[6];
    int i = 0;
    while (i < 6) {
        texture_owned_flag[i] = (texture_owned != 0);
        textures[i] = texture;

        // Top left:
        coords[i * 4 + 0].x = 0;
        coords[i * 4 + 0].y = 0;
        // Top right:
        coords[i * 4 + 1].x = 1;
        coords[i * 4 + 1].y = 0;
        // Bottom right:
        coords[i * 4 + 2].x = 1;
        coords[i * 4 + 2].y = 1;
        // Bottom left:
        coords[i * 4 + 3].x = 0;
        coords[i * 4 + 3].y = 1;

        i++;
    }
    spew3d_pos offset = {0};
    spew3d_rotation rotation = {0};

    return spew3d_geometry_AddCube(
        geometry, edge_width, &offset, &rotation,
        coords, textures, texture_owned_flag
    );
}


void spew3d_geometry_Destroy(spew3d_geometry *geometry) {
    if (!geometry)
        return;
    int32_t i = 0;
    while (i < geometry->owned_texture_count) {
        spew3d_texture_Destroy(geometry->owned_texture[i]);
        i++;
    }
    free(geometry->vertex);
    free(geometry->polygon_normal);
    free(geometry->polygon_material);
    free(geometry->polygon_vertexindex);
    free(geometry->polygon_texcoord);
    free(geometry->polygon_texture);
}

#endif  // SPEW3D_IMPLEMENTATION

