#version 410 core

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

in vec3 vColor[]; // input from vertex shader
out vec3 gColor;  // output to fragment shader

uniform float uExplode;

void main()
{
    // Compute the triangle centroid in clip space
    vec3 triCentroid = (gl_in[0].gl_Position.xyz +
                     gl_in[1].gl_Position.xyz +
                     gl_in[2].gl_Position.xyz) / 3.0;

    // Emit each vertex pushed away from the centroid
    for (int i = 0; i < 3; ++i)
    {
        vec4 pos = gl_in[i].gl_Position;
        pos.xyz += (pos.xyz - triCentroid) * uExplode;

        gl_Position = pos;
        gColor = vColor[i];
        EmitVertex();
    }

    EndPrimitive();
}
