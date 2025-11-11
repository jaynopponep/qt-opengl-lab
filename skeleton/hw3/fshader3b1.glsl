#version 330 core

in vec2 v_TexCoord;

uniform sampler2D u_Sampler;

out vec4 FragColor;

void main()
{
    vec4 texColor = texture(u_Sampler, v_TexCoord);
    FragColor = texColor;
}
