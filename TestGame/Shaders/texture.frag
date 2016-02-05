#version 150 core

// Inputs
in vec4 f_color;
in vec2 f_uv;

// Uniforms
uniform sampler2D f_sampler;

// Ouputs
out vec4 out_Color;


void main()
{
	vec4 textureColor = texture(f_sampler, f_uv);
    out_Color = textureColor * f_color;
}
