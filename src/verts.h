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

    inline constexpr float CubeVerts[] = {
        // pos
        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, 0.5f, -0.5f,
        -0.5f, 0.5f, -0.5f,
        -0.5f, -0.5f, 0.5f,
        0.5f, -0.5f, 0.5f,
        0.5f, 0.5f, 0.5f,
        -0.5f, 0.5f, 0.5f};

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
