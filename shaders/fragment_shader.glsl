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
  
  FragColor = vec4(pos, .0, 1.0f);
}
