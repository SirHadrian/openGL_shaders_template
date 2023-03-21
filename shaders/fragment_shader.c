#version 460 core
layout(location = 0) out vec4 FragColor;

uniform float u_time;
uniform vec2 u_resolution;
uniform vec2 u_mouse;

#define T u_time
#define R u_resolution
#define FC gl_FragCoord
#define M u_mouse

#define PI 3.14159265359

void main() {

  vec2 uv = FC.xy / R.xy;

  vec3 color = vec3(0);

  color.rg += uv;

  FragColor = vec4(color, 1.);
}
