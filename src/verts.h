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

}
