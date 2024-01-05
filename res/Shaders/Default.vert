#version 410 compatibility

layout (location = 0) in vec3 in_position;

uniform mat4 u_view;

void main()
{
  gl_Position = u_view * vec4(in_position, 1);
}