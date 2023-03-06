#pragma once
#include "main.h"

int main() {

  const int HEIGHT = 600;
  const int WIDTH = 800;

  const char *TITLE = "Learn OpengGL";

  if (!glfwInit()) {
    fprintf(stderr, "Could not initialize GLFW\n");
    die();
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, TITLE, NULL, NULL);

  if (!window) {
    fprintf(stderr, "Failed to create GLFW window\n");
    glfwTerminate();
    die();
  }

  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    fprintf(stderr, "Failed to initialize GLAD\n");
    die();
  }

  glViewport(0, 0, WIDTH, HEIGHT);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  char *vertex_shader_source = get_shader("shaders/vertex_shader.glsl");

  GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
  glCompileShader(vertex_shader);

  int success;
  char info_log[512];
  glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);

  if (!success) {
    glGetShaderInfoLog(vertex_shader, 512, NULL, info_log);
    fprintf(stderr, "Vertex shader compilation error: %s\n", info_log);
    die();
  }

  free(vertex_shader_source);

  char *fragment_shader_source = get_shader("shaders/fragment_shader.glsl");

  GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
  glCompileShader(fragment_shader);

  glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);

  if (!success) {
    glGetShaderInfoLog(fragment_shader, 512, NULL, info_log);
    fprintf(stderr, "Fragment shader compilation error: %s\n", info_log);
    die();
  }

  free(fragment_shader_source);

  GLuint shader_program = glCreateProgram();
  glAttachShader(shader_program, vertex_shader);
  glAttachShader(shader_program, fragment_shader);
  glLinkProgram(shader_program);

  glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shader_program, 512, NULL, info_log);
    fprintf(stderr, "Shader program linking error: %s\n", info_log);
    die();
  }

  glDeleteShader(vertex_shader);
  glDeleteShader(fragment_shader);

  float vertices[] = {
      // positions
      // colors
      0.5f,  -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom right
      -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom left
      0.0f,  0.5f,  0.0f, 0.0f, 0.0f, 1.0f  // top
  };

  unsigned int indices[] = {
      // note that we start from 0!
      0, 1, 3, // first Triangle
      1, 2, 3  // second Triangle
  };

  GLuint VAO, VBO, EBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
               GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                        (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glBindVertexArray(0);

  // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  while (!glfwWindowShouldClose(window)) {

    process_input(window);

    // Render
    glClearColor(0.2f, 0.3f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    float time = glfwGetTime();
    float green = (sin(time) / 2.0f) + 0.5f;
    GLuint vertex_color_location =
        glGetUniformLocation(shader_program, "custom_color");

    glUseProgram(shader_program);
    glUniform4f(vertex_color_location, 0.0f, green, 0.0f, 1.0f);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);

  glDeleteProgram(shader_program);

  glfwTerminate();
  return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

void process_input(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, TRUE);
}

char *get_shader(char *shader_file) {

  FILE *file = fopen(shader_file, "r");
  if (!file) {
    fprintf(stderr, "Could not open the shader file\n");
    die();
  }

  fseek(file, 0, SEEK_END);
  unsigned int length = ftell(file);
  fseek(file, 0, SEEK_SET);

  char *shader_string = (char *)malloc(sizeof(char) * (length + 1));
  if (!shader_string) {
    fprintf(stderr, "Could not alocate memory for file contents");
    die();
  }

  char cursor;
  unsigned int index = 0;

  while ((cursor = fgetc(file)) != EOF) {
    shader_string[index] = cursor;
    index++;
  }

  shader_string[index] = '\0';

  fclose(file);

  return shader_string;
}

void die() { exit(EXIT_FAILURE); }
