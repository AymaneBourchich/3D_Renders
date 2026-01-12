#pragma once
#include <cstddef>

namespace Verts
{
    inline constexpr float QuadVerts[] = {
        // pos
        -5000.0f, -5000.0f, 0.0f,
        5000.0f, -5000.0f, 0.0f,
        5000.0f, 5000.0f, 0.0f,
        -5000.0f, 5000.0f, 0.0f};
    inline constexpr float QuadVertsUV[] = {
        // pos
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
        -0.5f, 0.5f, 0.0f, 0.0f, 1.0f};

    // positions duplicated per face
    inline constexpr float CubeVerts[] = {
        // Front
        -0.5f, -0.5f, 0.5f,
        0.5f, -0.5f, 0.5f,
        0.5f, 0.5f, 0.5f,
        -0.5f, 0.5f, 0.5f,

        // Back
        0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, 0.5f, -0.5f,
        0.5f, 0.5f, -0.5f,

        // Left
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, 0.5f,
        -0.5f, 0.5f, 0.5f,
        -0.5f, 0.5f, -0.5f,

        // Right
        0.5f, -0.5f, 0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, 0.5f, -0.5f,
        0.5f, 0.5f, 0.5f,

        // Top
        -0.5f, 0.5f, 0.5f,
        0.5f, 0.5f, 0.5f,
        0.5f, 0.5f, -0.5f,
        -0.5f, 0.5f, -0.5f,

        // Bottom
        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, 0.5f,
        -0.5f, -0.5f, 0.5f};

    inline constexpr float CubeVertsUV[] = {
        // Front face (+Z)
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,

        // Back face (-Z)
        0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 0.0f, 1.0f,

        // Left face (-X)
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
        -0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,

        // Right face (+X)
        0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 1.0f,

        // Top face (+Y)
        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,

        // Bottom face (-Y)
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 1.0f};

    inline constexpr float HeadVerts[] = {
        -0.5f, -0.5f, 0.0f, // 0
        -0.0f, -0.75f, 0.0f, // 1
        0.5f, -0.5f, 0.0f, // 2
        0.5f, 0.5f, 0.0f, // 3
        0.0f, 0.25f, 0.0f, // 4
        -0.5f, 0.5f, 0.0f, // 5 

        -0.5f, -0.5f, -0.5f, // 6
        -0.0f, -0.75f, -0.5f, // 7 
        0.5f, -0.5f, -0.5f, // 8 
        0.5f, 0.5f, -0.5f, // 9 
        0.0f, 0.25f, -0.5f, // 10 
        -0.5f, 0.5f, -0.5f // 11

    };

    inline constexpr float EyeVerts[] = {
        -0.5f, 0.25f, 0.0f, // 0
        0.0f, -0.25f, 0.0f, // 1
        0.5f, 0.25f, 0.0f, // 2
        0.f, 0.0f, 0.0f // 3

    };

}
namespace Indices
{
    inline constexpr unsigned int QuadIndices[] = {
        0, 1, 2,
        0, 2, 3};

    inline constexpr unsigned int EyeIndices[] = {
        0, 1, 3,
        3, 1, 2};

    inline constexpr unsigned int HeadIndices[] = {
        0, 1, 2,
        0, 4, 2,
        4, 2, 3,
        5, 0, 4,

        6, 7, 8,
        6, 10, 8,
        10, 8, 9,
        11, 10, 6,

        6, 0, 7,
        0, 1, 7,
        7, 1, 2,
        7, 2, 8,

        11, 6, 0,
        11, 0, 5,

        3, 2, 8,
        3, 8, 9,

        11, 5, 10,
        10, 5, 4,
        10, 4, 3,
        10, 3, 9

    };

    inline constexpr unsigned int CubeIndices[] = {
        // Front
        0, 1, 2,
        0, 2, 3,

        // Back
        4, 5, 6,
        4, 6, 7,

        // Left
        8, 9, 10,
        8, 10, 11,

        // Right
        12, 13, 14,
        12, 14, 15,

        // Top
        16, 17, 18,
        16, 18, 19,

        // Bottom
        20, 21, 22,
        20, 22, 23};

}

namespace Counts
{
    inline constexpr int QuadIndexCount = sizeof(Indices::QuadIndices) / sizeof(Indices::QuadIndices[0]);
    inline constexpr int CubeIndexCount = sizeof(Indices::CubeIndices) / sizeof(Indices::CubeIndices[0]);
    inline constexpr int HeadCount = sizeof(Indices::HeadIndices) / sizeof(Indices::HeadIndices[0]);
    inline constexpr int EyeCount = sizeof(Indices::EyeIndices) / sizeof(Indices::EyeIndices[0]);
}
