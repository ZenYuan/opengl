#shader vertex
#version 330 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 TexCoords;

out VS_OUT
{
	vec3 position;
	vec3 normal;
	vec2 texCoors;
	vec4 lightSpace;
} vs_out;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 light_vp;

void main()
{
	gl_Position = projection * view * model * vec4(position, 1.0);
	vs_out.normal = normalize(transpose(inverse(mat3(model))) * normal);
	vs_out.texCoors = TexCoords;
	vs_out.position = vec3(model * vec4(position, 1.0));
	vs_out.lightSpace = light_vp * vec4(vs_out.position, 1.0);
	
};


#shader fragment
#version 330 core

in VS_OUT
{
	vec3 position;
	vec3 normal;
	vec2 texCoors;
	vec4 lightSpace;
} fs_in;


uniform sampler2D sceneTexSampler;
uniform sampler2D depthTexSampler;

/*view 空间*/
uniform vec3 lightpos;
uniform vec3 eyepos;


/*判断是否处在shadow中*/
float isShadow(vec4 LightSpace)
{
	//获取lightspce下的笛卡尔坐标系的position,ps的顶点已经经过裁剪
	//vec3 position = fs_in.lightSpace.xyz / fs_in.lightSpace.w;
	vec3 position = LightSpace.xyz / LightSpace.w;
	//归一化【0，1】便于纹理采样
	position = position * 0.5 + 0.5;
	float depth = texture(depthTexSampler, position.xy).r + 0.05;
	if (depth <= position.z)
		return 1.0;
	return 0.0;
}

void main()
{
	float lightIntensity = 1.0;
	
	vec3 lightDir = normalize(lightpos - fs_in.position);
	float ambient = 0.3 * lightIntensity;
	float diffuse = lightIntensity * max(dot(lightDir, fs_in.normal), 0.0);
	
	vec3 eyeDir = normalize(eyepos - fs_in.position);
	vec3 halfvec = normalize(eyeDir + lightDir);
	float specular = lightIntensity * pow(max(dot(halfvec, fs_in.normal), 0.0), 64.0);
	
	//当前positon在lightspace的深度
	float shadow = isShadow(fs_in.lightSpace);
	
	vec4 color = texture(sceneTexSampler, fs_in.texCoors);
	gl_FragColor = (ambient + (1.0 - shadow) * (diffuse + specular)) * color;
};


