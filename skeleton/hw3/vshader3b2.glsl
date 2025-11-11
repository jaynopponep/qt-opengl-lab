#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Color; // keep this so VAO bindings match

uniform mat4 u_View;
uniform mat4 u_Projection;

void main()
{
    gl_Position = u_Projection * u_View * vec4(a_Position, 1.0);
}
