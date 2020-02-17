#shader vertex
#version 330 core

layout(location = 0 ) in vec4 positions;

void main()
{
gl_Position = positions;
};

#shader fragment
#version 330 core

layout( location = 0 ) out vec4 color;

void main()
{
color = vec4( 1, 20/256f, 147/256f, 1.0);
};

