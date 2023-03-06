#version 460 core

uniform float u_time;
uniform vec2 u_resolution;

#define T u_time
#define R u_resolution

out vec4 FragColor;

void main(){

  vec2 uv = gl_FragCoord.xy/R.xy;

  vec2 pos = uv;

  pos -= .5;
  pos.x *= R.x/R.y;

  float r = -(pos.x * pos.x + pos.y * pos.y);
  float z = sin((r+T*.2)/.02);
  
  FragColor = vec4(vec3(pos.xy, z), 1.0f);
}
