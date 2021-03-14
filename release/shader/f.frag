#version 330 core

in vec3 normal;
in vec3 fragPos;
in vec2 texCoords;

uniform vec3 ambient;
uniform vec3 lightColor1;
uniform vec3 lightColor2;
uniform vec3 lightColor3;
uniform vec3 lightColor4;
uniform vec3 lightPos1;
uniform vec3 lightPos2;
uniform vec3 lightPos3;
uniform vec3 lightPos4;

out vec4 fragColor;

uniform sampler2D texture1;

vec3 GetDiffuse(vec3 _lightPos,vec3 _fragPos,vec3 _normal,vec3 _lightColor);

void main()
{
	vec3 diffuse1=GetDiffuse(lightPos1,fragPos,normal,lightColor1);
	vec3 diffuse2=GetDiffuse(lightPos2,fragPos,normal,lightColor2);
	vec3 diffuse3=GetDiffuse(lightPos3,fragPos,normal,lightColor3);
	vec3 diffuse4=GetDiffuse(lightPos4,fragPos,normal,lightColor4);
	vec3 result=ambient+diffuse1+diffuse2+diffuse3+diffuse4;

	vec3 temp;
	temp= step(vec3(0.7f,0.6f,0.5f),result);
	result=(vec3(1.0f,1.0f,1.0f)-temp)*result+temp*result*vec3(0.7,0.6,0.5);
	fragColor=vec4(result,1.0f) * texture(texture1, texCoords);
}

vec3 GetDiffuse(vec3 _lightPos,vec3 _fragPos,vec3 _normal,vec3 _lightColor)
{
	vec3 _dir=normalize(_lightPos-_fragPos);
	vec3 _diffuse =abs(min(dot(_normal,_dir),0.5))*_lightColor;
	return _diffuse;
}