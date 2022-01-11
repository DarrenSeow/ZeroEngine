#version 450

layout(binding = 1) uniform sampler2D texSampler;

layout(location = 0) in vec3 fragColor;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec2 fragTexCoord;

layout(location = 0) out vec4 outColor;


const vec3 ambientLightColor = vec3(0.2f,0.2f,0.2f);
const vec3 lightDir = normalize(vec3(1.0f,1.0f,1.0f));
const vec3 lightColor = vec3(0.0f,0.0f,0.0f);

void main() {
    vec3 texColor = texture(texSampler, fragTexCoord).xyz;
	float diff = max(dot(normalize(inNormal), lightDir), 0.0f);
	vec3 diffuse = diff * lightColor;

	vec3 result = (ambientLightColor + diffuse) * texColor;


	outColor = vec4(result,1.0f);
}