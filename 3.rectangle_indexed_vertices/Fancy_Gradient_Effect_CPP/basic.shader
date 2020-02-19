#shader vertex
#version 450 core

layout( location = 0 ) in vec4 positions;
layout( location = 1 ) in vec3 aColor;



out vec3 ourColor;

void main()
{
	gl_Position = positions;
	ourColor = aColor;
};

#shader fragment
#version 450 core

out vec4 FragColor;
in vec3 ourColor;

void main()
{
	FragColor = vec4(ourColor, 1.0);
};