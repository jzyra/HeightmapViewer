#version 150 core

in vec3 in_Vertex;
in vec3 in_Color;
uniform mat4 projection;
uniform mat4 modelview;
out vec3 color;

void main() {
    gl_Position = projection * modelview * vec4(vec3(in_Vertex.x, in_Vertex.y*0.30, in_Vertex.z), 1.0);
    color = vec3(in_Vertex.y/255, in_Vertex.y/255, in_Vertex.y/255);
}
