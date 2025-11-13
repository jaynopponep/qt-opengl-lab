#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TexCoord;

uniform mat4 u_View;
uniform mat4 u_Projection;

out vec2 v_TexCoord;

void main()
{
    // Force the uniforms to be used so they're not optimized out
    mat4 VP = u_Projection * u_View;

    gl_Position = VP * vec4(a_Position, 1.0);
    v_TexCoord  = a_TexCoord;
}
