#shader vertex
#version 330 core
layout(location = 0) in vec4 position;

uniform mat4 u_mvp;

void main()
{
	gl_Position = u_mvp * position;
};

#shader fragment
#version 330 core

float near = 0.1;
float far = 100.0;

float LinearizeDepth(float depth)
{
	float z = depth * 2.0 - 1.0; // back to NDC 
	return (2.0 * near * far) / (far + near - z * (far - near));
}

void main()
{
	gl_FragColor = vec4(vec3(LinearizeDepth(gl_FragCoord.z)/ far), 1.0);
};
