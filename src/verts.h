#pragma once
#include <cstddef>
// Floor plane at y = 0

template <typename T, size_t N>
inline constexpr int getCount(const T (&)[N])
{
    return static_cast<int>(N);
}

namespace Verts
{
    inline constexpr float FLOOR_VERTS[] = {
        // pos
        -0.5f, 0.0f, -0.5f, 0.0f, 0.0f,
        0.5f, 0.0f, -0.5f, 1.0f, 0.0f,
        0.5f, 0.0f, 0.5f, 1.0f, 1.0f,
        -0.5f, 0.0f, 0.5f, 0.0f, 1.0f

    };

    inline constexpr float TRI_PRISM_VERTS[] = {
        // pos
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, -0.5f,
        0.0f, 0.5f, -0.25f,

        0.5f, 0.0f, 0.0f,
        0.5f, 0.0f, -0.5f,
        0.5f, 0.5f, -0.25f};

    inline constexpr float CUBE_VERTS[] = {
        // Front (+Z)
        -0.5f, -0.5f,  0.5f,   0, 0, 1,
         0.5f, -0.5f,  0.5f,   0, 0, 1,
         0.5f,  0.5f,  0.5f,   0, 0, 1,
        -0.5f,  0.5f,  0.5f,   0, 0, 1,

        // Back (-Z)
         0.5f, -0.5f, -0.5f,   0, 0, -1,
        -0.5f, -0.5f, -0.5f,   0, 0, -1,
        -0.5f,  0.5f, -0.5f,   0, 0, -1,
         0.5f,  0.5f, -0.5f,   0, 0, -1,

        // Left (-X)
        -0.5f, -0.5f, -0.5f,  -1, 0, 0,
        -0.5f, -0.5f,  0.5f,  -1, 0, 0,
        -0.5f,  0.5f,  0.5f,  -1, 0, 0,
        -0.5f,  0.5f, -0.5f,  -1, 0, 0,

        // Right (+X)
         0.5f, -0.5f,  0.5f,   1, 0, 0,
         0.5f, -0.5f, -0.5f,   1, 0, 0,
         0.5f,  0.5f, -0.5f,   1, 0, 0,
         0.5f,  0.5f,  0.5f,   1, 0, 0,

        // Bottom (-Y)
        -0.5f, -0.5f, -0.5f,   0, -1, 0,
         0.5f, -0.5f, -0.5f,   0, -1, 0,
         0.5f, -0.5f,  0.5f,   0, -1, 0,
        -0.5f, -0.5f,  0.5f,   0, -1, 0,

        // Top (+Y)
        -0.5f,  0.5f,  0.5f,   0, 1, 0,
         0.5f,  0.5f,  0.5f,   0, 1, 0,
         0.5f,  0.5f, -0.5f,   0, 1, 0,
        -0.5f,  0.5f, -0.5f,   0, 1, 0
    };

    

}

namespace Indices
{

    inline constexpr unsigned int TRI_PRISM_INDICES[] = {
        0, 1, 2,
        3, 4, 5,
        0, 2, 3,
        2, 5, 3,
        5, 2, 1,
        1, 5, 4};

    inline constexpr unsigned int FLOOR_INDICES[] = {
        0, 1, 2,
        0, 3, 2};

    inline constexpr unsigned int CUBE_INDICES[] = {
         0,  1,  2,   0,  2,  3,   // front
         4,  5,  6,   4,  6,  7,   // back
         8,  9, 10,   8, 10, 11,   // left
        12, 13, 14,  12, 14, 15,   // right
        16, 17, 18,  16, 18, 19,   // bottom
        20, 21, 22,  20, 22, 23    // top
    };
}
namespace Counts
{
    inline constexpr int FLOOR_COUNT = getCount(Indices::FLOOR_INDICES);
    inline constexpr int TRI_PRISM_COUNT = getCount(Indices::TRI_PRISM_INDICES);
    inline constexpr int CUBE_COUNT = getCount(Indices::CUBE_INDICES);
}
