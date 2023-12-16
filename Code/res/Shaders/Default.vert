#version 410 core

layout (location = 0) in vec3 in_Position;

uniform mat4 u_view;

void main()
{
  gl_Position = u_view * vec4(in_Position, 1);
}