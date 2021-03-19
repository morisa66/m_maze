#version 330 core

in VS_OUT 
{
    vec2 texCoords;
    vec3 normal;
    vec3 fragPos;
} fs_in;

out vec4 fragColor;

uniform sampler2D texture1;

void main()
{
    fragColor = texture(texture1, fs_in.texCoords);
}

