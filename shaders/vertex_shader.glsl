#version 410

layout(location=0) in  vec4 a_vertex_position;
layout(location=1) in  vec4 a_vertex_color;

out vec4 vertex_color;

void main() {
    gl_Position = a_vertex_position;
    vertex_color = a_vertex_color;
}