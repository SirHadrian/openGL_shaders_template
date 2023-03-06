#version 460 core
out vec4 FragColor;
in vec4 custom_color;

void main(){
  FragColor = custom_color;
}
