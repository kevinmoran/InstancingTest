#version 410

in vec4 quad_colour;

out vec4 frag_colour;

void main () {
	frag_colour = quad_colour;
}