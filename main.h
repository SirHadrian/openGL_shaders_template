#pragma once
// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void process_input(GLFWwindow *window, GLuint *shader_program);
char *get_shader(char *shader_file);
void die(const char *error);
void compile_shaders(const GLuint *const shader_program);
