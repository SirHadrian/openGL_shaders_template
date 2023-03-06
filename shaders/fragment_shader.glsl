#version 460 core

uniform float u_time;

#define T u_time

out vec4 FragColor;

void main(){
  FragColor = vec4(.0, .0, sin(T), 1.0f);
}
