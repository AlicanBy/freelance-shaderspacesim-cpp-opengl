#version 410 core

layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec3 vNormal;

out vec3 FragColor;

uniform vec3 lightPos;
uniform vec3 baseColor;

void main()
{
    vec3 normal = normalize(vNormal);
    vec3 lightDir = normalize(lightPos - vPosition);
    float diff = max(dot(normal, lightDir), 0.0);
    FragColor = diff * baseColor;
}
