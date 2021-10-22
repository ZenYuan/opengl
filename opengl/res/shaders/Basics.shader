#shader vertex
#version 330 core
layout(location = 0) in vec4 position;
layout(location = 1) in vec2 TexCoords;

out vec2 u_TexCoords;
uniform mat4 u_mvp;
void main()
{
	gl_Position = u_mvp * position;
	u_TexCoords = TexCoords;
};

#shader fragment
#version 330 core

out vec4 color;
uniform int outline;
uniform sampler2D texSampler0;
uniform sampler2D texSampler1;
in vec2 u_TexCoords;

void main()
{
	//vec4 texColor = mix(texture(texSampler0, u_TexCoords), texture(texSampler1, u_TexCoords), 0.3);
	vec4 texColor = vec4(0.04, 0.28, 0.26, 1.0);
	if (1 == outline)
	{
		texColor = vec4(0.04, 0.28, 0.26, 1.0);
	}
	else if (2 == outline)
	{
		texColor = texture(texSampler0, u_TexCoords);
	}
	gl_FragColor = texColor;
};


