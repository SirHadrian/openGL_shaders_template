#version 460 core

layout(location = 0) out vec4 FragColor;

uniform float u_time;
uniform vec2 u_resolution;

#define T u_time
#define R u_resolution
#define FC gl_FragCoord

float dist_line(vec2 p, vec2 a, vec2 b) {
  vec2 pa = p - a;
  vec2 ba = b - a;
  float t = clamp(dot(pa, ba) / dot(ba, ba), 0., 1.);
  return length(pa - ba * t);
}

void main() {

  vec2 uv = FC.xy / R.xy;

  uv -= .5;
  uv.x *= R.x / R.y;

  float d = dist_line(uv, vec2(0), vec2(1));
  float m = smoothstep(.1, .05, d);

  vec3 color = vec3(m);

  FragColor = vec4(color, 1.);
}
