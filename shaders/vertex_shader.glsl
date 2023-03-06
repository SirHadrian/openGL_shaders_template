#version 460 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColors;

out vec4 custom_color;

void main(){
  gl_Position = vec4(aPos, 1.0 );
  custom_color = vec4(aColors, 1.0f);
}
