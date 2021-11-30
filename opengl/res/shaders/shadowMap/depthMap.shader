#shader vertex
#version 330 core
layout(location = 0) in vec3 position;

uniform mat4 light_vp;
uniform mat4 model;
void main()
{
	gl_Position = light_vp * model * vec4(position, 1.0);
};

#shader fragment
#version 330 core

void main()
{
};


