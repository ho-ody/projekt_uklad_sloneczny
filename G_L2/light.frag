#version 330 core

in vec2 myTexture;
out vec4 FragColor;


uniform vec4 lightColor;
uniform sampler2D tex0;

void main()
{
	//outColor = texture(tex0, myTexture) * lightColor * (diffuse + ambient + specular);
	//FragColor = lightColor;
	FragColor = texture(tex0, myTexture) * lightColor;
}