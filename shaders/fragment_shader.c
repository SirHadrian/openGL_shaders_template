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

// A cell size of 1. is equal with a space divizion.
#define CELL_SIZE 1.
// If the uv space is too big the lines will disappear.
// Increase the line size to make them appear.
#define LINE_SIZE 0.01

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

float N21(vec2 p) {
  p = fract(p * vec2(123.34, 345.45));
  p += dot(p, p + 34.345);
  return fract(p.x * p.y);
}

void main() {

  vec2 uv = (FC.xy - .5 * R.xy) / R.y;
  vec3 color = vec3(0.);

  color += step(.0, uv.x);

  FragColor = vec4(color, 1.);
}
