#version 410 core

out vec4 FragColor;

uniform vec3 uAmbient;
uniform float uAmbientIntensity;
uniform vec3 color;

void main()
{
    FragColor = vec4(color * uAmbient * uAmbientIntensity, 1.0);
}

