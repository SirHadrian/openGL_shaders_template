#version 460 core
layout(location = 0) out vec4 FragColor;

in vec3 color;
in vec2 texCoord;

uniform sampler2D tex0;
// Load texture
// vec4 text = texture(tex0, texCoord * vec2(-1., 1.));

uniform float         u_time;
uniform vec2          u_resolution;
uniform vec2          u_mouse;

#define T             u_time
#define R             u_resolution
#define FC            gl_FragCoord
#define M             u_mouse

#define PI            3.14159265359
#define S(a, b, x)    smoothstep(a, b, x)

#define CELL_SIZE     1.
#define LINE_SIZE     0.01

vec3
drawGrid(vec2 uv)
{
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

void
main()
{
  vec2 uv = FC.xy / R.xy;
  uv -= .5;
  uv.x *= R.x / R.y;

  vec3 color = vec3(0.);

  color.rg = uv;

  FragColor = vec4(color, 1.);
}
