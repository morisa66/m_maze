#version 330 core

in VS_OUT 
{
    vec2 texCoords;
    vec3 normal;
    vec3 fragPos;
} fs_in;

out vec4 fragColor;

uniform sampler2D texture1;

const float thresh = 0.05f;
void main()
{           
    vec4 _fragColor = texture(texture1, fs_in.texCoords);
    if(_fragColor.a < thresh)
    {
        discard;
    }
    fragColor =_fragColor;
}

