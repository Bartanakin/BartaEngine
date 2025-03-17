#version 410

out vec4 vFragColor;
in vec4 vertex_color;

void main() {
    vFragColor = vertex_color;
}
