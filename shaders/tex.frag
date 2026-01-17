#version 410 core

in vec2 vUV;
out vec4 FragColor;

uniform sampler2D uTex;
uniform vec3 uAmbient;
uniform float uAmbientIntensity;

void main()
{
    vec3 color = texture(uTex, vUV).rgb;
    FragColor = vec4(color * uAmbient * uAmbientIntensity, 1.0);
}
