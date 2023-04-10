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
#define S(a, b, x) smoothstep(a, b, x)

#define CELL_SIZE 1.
// If the uv space is too big the lines will disappear.
// Increase the line size to make them appear.
#define LINE_SIZE 0.011

vec3 draw_grid(vec2 uv) {

  // Draw grid.
  vec3 lines = vec3(0.);
  if (mod(uv.x, CELL_SIZE) < LINE_SIZE)
    lines.g = 1.;
  if (mod(uv.y, CELL_SIZE) < LINE_SIZE)
    lines.g = 1.;

  // Draw axes.
  if (abs(uv.x) < LINE_SIZE)
    lines.r = 1.;
  if (abs(uv.y) < LINE_SIZE)
    lines.b = 1.;

  return lines;
}

void main() {

  vec2 uv = FC.xy / R.xy;
  uv -= .5;
  uv.x *= R.x / R.y;

  uv *= 4.;

  vec3 color = vec3(0.);

  color += draw_grid(uv);

  FragColor = vec4(color, 1.);
}
