#pragma once
#include <cstddef>

namespace Verts
{
    // ----------------------------
    // Cube (36 vertices)
    // ----------------------------
    inline constexpr float Cube[] = {
        -0.5f, -0.5f, 0.5f, 0.5f, -0.5f, 0.5f, 0.5f, 0.5f, 0.5f,
        -0.5f, -0.5f, 0.5f, 0.5f, 0.5f, 0.5f, -0.5f, 0.5f, 0.5f,

        -0.5f, -0.5f, -0.5f, -0.5f, 0.5f, -0.5f, 0.5f, 0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f, 0.5f, 0.5f, -0.5f, 0.5f, -0.5f, -0.5f,

        0.5f, -0.5f, -0.5f, 0.5f, 0.5f, -0.5f, 0.5f, 0.5f, 0.5f,
        0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f, 0.5f, -0.5f, 0.5f,

        -0.5f, -0.5f, -0.5f, -0.5f, -0.5f, 0.5f, -0.5f, 0.5f, 0.5f,
        -0.5f, -0.5f, -0.5f, -0.5f, 0.5f, 0.5f, -0.5f, 0.5f, -0.5f,

        -0.5f, 0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f,
        -0.5f, 0.5f, -0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, -0.5f,

        -0.5f, -0.5f, -0.5f, 0.5f, -0.5f, -0.5f, 0.5f, -0.5f, 0.5f,
        -0.5f, -0.5f, -0.5f, 0.5f, -0.5f, 0.5f, -0.5f, -0.5f, 0.5f};

    inline constexpr int CubeVertexCount = 36;

    // ----------------------------
    // Triangular prism (24 vertices)
    // ----------------------------
    inline constexpr float TriPrism[] = {
        // Top
        -0.5f, 0.5f, 0.0f,
        0.5f, 0.5f, 0.0f,
        0.0f, 0.5f, 0.6f,

        // Bottom
        -0.5f, -0.5f, 0.0f,
        0.0f, -0.5f, 0.6f,
        0.5f, -0.5f, 0.0f,

        // Side AB
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.5f, 0.5f, 0.0f,

        -0.5f, -0.5f, 0.0f,
        0.5f, 0.5f, 0.0f,
        -0.5f, 0.5f, 0.0f,

        // Side BC
        0.5f, -0.5f, 0.0f,
        0.0f, -0.5f, 0.6f,
        0.0f, 0.5f, 0.6f,

        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.6f,
        0.5f, 0.5f, 0.0f,

        // Side CA
        0.0f, -0.5f, 0.6f,
        -0.5f, -0.5f, 0.0f,
        -0.5f, 0.5f, 0.0f,

        0.0f, -0.5f, 0.6f,
        -0.5f, 0.5f, 0.0f,
        0.0f, 0.5f, 0.6f};

    inline constexpr int TriPrismVertexCount = 24;

    // ----------------------------
    // Simple triangle (3 vertices)
    // ----------------------------
    inline constexpr float Triangle[] = {
        0.0f, 0.0f, 0.0f,
        0.5f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.0f};

    inline constexpr int TriangleVertexCount = 3;

    inline constexpr float Floor[] = {
        // pos                  // uv
        -0.5f, 0.0f, 0.5f, 0.0f, 1.0f,
        0.5f, 0.0f, 0.5f, 1.0f, 1.0f,
        0.5f, 0.0f, -0.5f, 1.0f, 0.0f,

        -0.5f, 0.0f, 0.5f, 0.0f, 1.0f,
        0.5f, 0.0f, -0.5f, 1.0f, 0.0f,
        -0.5f, 0.0f, -0.5f, 0.0f, 0.0f};

    inline constexpr int FloorVertexCount = 6;

    inline constexpr float laserQuad[] = {
        -0.02f, 0.0f, 0.0f,
        0.02f, 0.0f, 0.0f,
        -0.02f, 0.0f, -5.0f,
        0.02f, 0.0f, -5.0f};

    inline constexpr float ScopeHex[] = {
        // Triangle 1
        0.0f, 0.0f, 0.0f,
        0.35f, 0.0f, 0.0f,
        0.175f, 0.0f, 0.303f,

        // Triangle 2
        0.0f, 0.0f, 0.0f,
        0.175f, 0.0f, 0.303f,
        -0.175f, 0.0f, 0.303f,

        // Triangle 3
        0.0f, 0.0f, 0.0f,
        -0.175f, 0.0f, 0.303f,
        -0.35f, 0.0f, 0.0f,

        // Triangle 4
        0.0f, 0.0f, 0.0f,
        -0.35f, 0.0f, 0.0f,
        -0.175f, 0.0f, -0.303f,

        // Triangle 5
        0.0f, 0.0f, 0.0f,
        -0.175f, 0.0f, -0.303f,
        0.175f, 0.0f, -0.303f,

        // Triangle 6
        0.0f, 0.0f, 0.0f,
        0.175f, 0.0f, -0.303f,
        0.35f, 0.0f, 0.0f};

    inline constexpr int ScopeHexVertexCount = 18;

    inline constexpr float QuadVerts[] = {
        // pos
        -0.5f, -0.5f, 0.0f, // 0
        0.5f, -0.5f, 0.0f,  // 1
        0.5f, 0.5f, 0.0f,   // 2
        -0.5f, 0.5f, 0.0f   // 3
    };

}
namespace Indices
{
    inline constexpr unsigned int QuadIndices[] = {
        0, 1, 2,
        0, 2, 3};
}

namespace Counts
{
    inline constexpr int QuadVertexCount = 4;
    inline constexpr int QuadIndexCount = 6;
}
