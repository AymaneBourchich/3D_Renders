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
}
namespace Counts
{
    inline constexpr int FLOOR_COUNT = getCount(Indices::FLOOR_INDICES);
    inline constexpr int TRI_PRISM_COUNT = getCount(Indices::TRI_PRISM_INDICES);
}
