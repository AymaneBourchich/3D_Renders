#pragma once
#include <cstddef>

namespace Verts
{
    inline constexpr float QuadVerts[] = {
        // pos
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.5f, 0.5f, 0.0f,
        -0.5f, 0.5f, 0.0f};

    inline constexpr float QuadVertsColor[] = {

        -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f,
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.0f, 1.0f, 0.5f, 1.0f};

    inline constexpr float CubeVertsColor[] = {
        // pos                // color
        -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, // 0: red
        0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,  // 1: green
        0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 1.0f,   // 2: blue
        -0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f,  // 3: black
        -0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 1.0f,  // 4: magenta
        0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 1.0f,   // 5: cyan
        0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f,    // 6: grey
        -0.5f, 0.5f, 0.5f, 0.0f, 0.5f, 0.25f   // 7: orange
    };

}
namespace Indices
{
    inline constexpr unsigned int QuadIndices[] = {
        0, 1, 2,
        0, 2, 3};

    inline constexpr unsigned int CubeIndices[] = {
        // back face
        0, 1, 2,
        0, 2, 3,
        // front face
        4, 5, 6,
        4, 6, 7,
        // left face
        4, 0, 3,
        4, 3, 7,
        // right face
        1, 5, 6,
        1, 6, 2,
        // bottom face
        4, 5, 1,
        4, 1, 0,
        // top face
        3, 2, 6,
        3, 6, 7};
}

namespace Counts
{
    inline constexpr int QuadIndexCount = 6;
    inline constexpr int CubeIndexCount = 36;
}
