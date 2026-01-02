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
        // Front (red)
        -0.5f, -0.5f, 0.5f, 1, 0, 0,
        0.5f, -0.5f, 0.5f, 1, 0, 0,
        0.5f, 0.5f, 0.5f, 1, 0, 0,
        -0.5f, 0.5f, 0.5f, 1, 0, 0,

        // Back (green)
        -0.5f, -0.5f, -0.5f, 0, 1, 0,
        0.5f, -0.5f, -0.5f, 0, 1, 0,
        0.5f, 0.5f, -0.5f, 0, 1, 0,
        -0.5f, 0.5f, -0.5f, 0, 1, 0,

        // Left (blue)
        -0.5f, -0.5f, -0.5f, 0, 0, 1,
        -0.5f, -0.5f, 0.5f, 0, 0, 1,
        -0.5f, 0.5f, 0.5f, 0, 0, 1,
        -0.5f, 0.5f, -0.5f, 0, 0, 1,

        // Right (yellow)
        0.5f, -0.5f, -0.5f, 1, 1, 0,
        0.5f, -0.5f, 0.5f, 1, 1, 0,
        0.5f, 0.5f, 0.5f, 1, 1, 0,
        0.5f, 0.5f, -0.5f, 1, 1, 0,

        // Top (magenta)
        -0.5f, 0.5f, -0.5f, 1, 0, 1,
        0.5f, 0.5f, -0.5f, 1, 0, 1,
        0.5f, 0.5f, 0.5f, 1, 0, 1,
        -0.5f, 0.5f, 0.5f, 1, 0, 1,

        // Bottom (cyan)
        -0.5f, -0.5f, -0.5f, 0, 1, 1,
        0.5f, -0.5f, -0.5f, 0, 1, 1,
        0.5f, -0.5f, 0.5f, 0, 1, 1,
        -0.5f, -0.5f, 0.5f, 0, 1, 1};

}
namespace Indices
{
    inline constexpr unsigned int QuadIndices[] = {
        0, 1, 2,
        0, 2, 3};

    inline constexpr unsigned int CubeIndices[] = {
        // Front face
        0, 1, 2, 2, 3, 0,

        // Back face
        4, 5, 6, 6, 7, 4,

        // Left face
        8, 9, 10, 10, 11, 8,

        // Right face
        12, 13, 14, 14, 15, 12,

        // Top face
        16, 17, 18, 18, 19, 16,

        // Bottom face
        20, 21, 22, 22, 23, 20};
}

namespace Counts
{
    inline constexpr int QuadIndexCount = 6;
    inline constexpr int CubeIndexCount = 36;
}
