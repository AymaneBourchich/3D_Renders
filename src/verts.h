#pragma once
#include <cstddef>

namespace Verts
{
    inline constexpr float QuadVerts[] = {
        // pos
        -0.5f, -0.5f, 0.0f, // 0
        0.5f, -0.5f, 0.0f,  // 1
        0.5f, 0.5f, 0.0f,   // 2
        -0.5f, 0.5f, 0.0f   // 3
    };

    inline constexpr float QuadVertsColor[] = {
    // pos               // color
    -0.5f, -0.5f, 0.0f,  1.0f, 1.0f, 1.0f, 
     0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f, 
     0.5f,  0.5f, 0.0f,  0.0f, 0.0f, 0.0f, 
    -0.5f,  0.5f, 0.0f,  1.0f, 0.5f, 1.0f  

    
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
