#version 410 core
out vec4 FragColor;

in vec3 vNormal;
in vec3 vWorldPos;

uniform vec3 uLightPos;
uniform vec3 uLightColor;
uniform vec3 uObjectColor;
uniform float uAmbient;

void main()
{
    vec3 N = normalize(vNormal);
    vec3 L = normalize(uLightPos - vWorldPos);

    float diff = max(dot(N, L), 0.0);

    vec3 ambient = uAmbient * uLightColor;
    vec3 diffuse = diff * uLightColor;

    vec3 color = (ambient + diffuse) * uObjectColor;
    FragColor = vec4(color, 1.0);
}
