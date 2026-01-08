#version 410 core

in vec2 vUV;
out vec4 FragColor;

uniform sampler2D uTex;
uniform vec3 uAmbient;

void main()
{
    vec3 color = texture(uTex, vUV).rgb;
    FragColor = vec4(color * uAmbient, 1.0);
}
