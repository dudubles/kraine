/*
  MIT License

  Copyright (c) 2024 Dudubles

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/

/*=================================================
Path: main.c

Date: 06/30/2024

Author: Dudubles

Description: This is just to test some shi
=================================================*/

#include <glad/glad.h>
// Fuck you clangd
#include "kraine/renderer.h"
#include <GLFW/glfw3.h>
#include <cglm/call.h>
#include <stdio.h>

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

int main() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow *window =
      glfwCreateWindow(800, 600, "Kraine Engine [TEST]", NULL, NULL);
  if (window == NULL) {
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    return -1;
  }

  unsigned int shaderProgram = ShaderFromFiles(
      "c:/users/tiago/desktop/kraine/resource/shader/vertex.glsl",
      "C:/Users/tiago/Desktop/Kraine/resource/shader/fragment.glsl");

  unsigned int myTexture = LoadTexFromFile(
      (char *)"c:/users/tiago/desktop/kraine/resource/textures/wall.jpg");

  Model cubex = CreateCube();
  Camera cam = CreateCamera();

  glUseProgram(shaderProgram);

  glEnable(GL_DEPTH_TEST); // Enable depth
  glfwSwapInterval(
      1); // enably vsync so it doesnt take up 50% cpu (also smooth draw calls)

  while (!glfwWindowShouldClose(window)) {
    CameraMatrixUpdate(&cam, shaderProgram);

    glm_rotate(cubex.transform, 0.03f * glm_rad(50.0f),
               (vec3){0.5f, 1.0f, 0.0f});

    ModelMatrixUpdate(&cubex, shaderProgram);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBindTexture(GL_TEXTURE_2D, myTexture);
    DrawModel(&cubex);
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  /* TEST: glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);*/
  glDeleteProgram(shaderProgram);

  glfwTerminate();
  return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}
