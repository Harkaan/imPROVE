#version 150 core

// Inputs
in vec3 v_position;
in vec4 v_color;
in vec2 v_uv;

// Uniforms
uniform mat4 projection;
uniform mat4 modelview;

// Outputs
out vec4 f_color;
out vec2 f_uv;


void main()
{
    gl_Position = projection * modelview * vec4(v_position, 1.0);
	f_color = v_color;
    f_uv = vec2(v_uv.x, 1.0 - v_uv.y);
}
