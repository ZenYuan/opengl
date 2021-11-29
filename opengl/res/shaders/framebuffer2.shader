#shader vertex
#version 330 core
layout(location = 0) in vec2 position;
layout(location = 1) in vec2 texCoord;

out vec2 u_texCoord;
//uniform mat4 u_mvp;

void main()
{
	u_texCoord = texCoord;
	gl_Position = vec4(position, 0.0, 1.0);
}

#shader fragment
#version 330 core

in vec2 u_texCoord;
uniform sampler2D texsample;

void main()
{
	gl_FragColor = texture(texsample, u_texCoord);
}
