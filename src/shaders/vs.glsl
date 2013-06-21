#version 330

in vec3 position;

uniform float gScale;

void main()
{
	gl_Position = vec4(0.5 * position.x, 0.25 * position.y, position.z, 1.0);
}