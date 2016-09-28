#version 410

layout (location = 0) in vec2 position;
layout (location = 1) in vec2 offset;
layout (location = 2) in vec4 colour;

out vec4 quad_colour;

void main(){
    gl_Position = vec4(position + offset, 0.0, 1.0);
    quad_colour = colour;
}