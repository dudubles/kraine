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
Path: core/game.c

Date: 07/07/2024

Author: Dudubles

Description: game.c manages all the game logic
=================================================*/

#include <glad/glad.h>
// CLangd ... omg
#include "cglm/mat4.h"
#include "kraine/core.h"
#include "kraine/renderer.h"
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>

/*
==============================================================================

Typedefs & vars & runtime vars

==============================================================================
*/

bool running = 0;

typedef void (*callback)(void);

// mvp calculation vars
mat4 rtView;
mat4 rtProj;
mat4 rtModel;
mat4 mvpRes;

/*
==============================================================================

Bindings

==============================================================================
*/

unsigned int bindedShader;

Scene *bindedScene;

/*
==============================================================================

Gamedev control (callbacks)

==============================================================================
*/

callback *onUpdateCallbackList;
int onUpdateCallbackIndex;

callback *onStartCallbackList;
int onStartCallbackIndex;

//============================================================================

void TryDrawScene();

void AutoResize(GLFWwindow *window, int width, int height);

void GameInit(const char *title, int width, int height) {

  // Check if game is already running
  if (running == true) {
    return;
  }

  // Load window
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow *window =
      glfwCreateWindow(800, 600, "Kraine Engine [TEST]", NULL, NULL);

  if (window == NULL) {
    glfwTerminate();
    return;
  }

  glfwMakeContextCurrent(window);

  glfwSetFramebufferSizeCallback(window, AutoResize);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    return;
  }

  // Setup default shaders
  // FIXME: For testing we are using a whole path of my pc.
  BindShader(ShaderFromFiles(
      "c:/users/tiago/desktop/kraine/resource/shader/vertex.glsl",
      "C:/Users/tiago/Desktop/Kraine/resource/shader/fragment.glsl"));

  // Call every OnStart() function
  if (onStartCallbackIndex > 0) {
    for (size_t i = 0; i < onStartCallbackIndex; i++) {
      onStartCallbackList[i]();
    }
  }

  // Run game thread
  while (!glfwWindowShouldClose((GLFWwindow *)window)) {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Call every OnUpdate() function
    if (onUpdateCallbackIndex > 0) {
      for (size_t i = 0; i < onUpdateCallbackIndex; i++) {
        onUpdateCallbackList[i]();
      }
    }

    // Draw scene
    TryDrawScene();

    // End of new frame
    glfwSwapBuffers((GLFWwindow *)window);
    glfwPollEvents();
  }

  // Terminate window
  glfwTerminate();

  // Terminate Game
  running = false;

  return;
}

void TryDrawScene() {

  // Check if thers a binded scene
  if (bindedScene == NULL) {
    return;
  }

  // Check if scene can be drawn
  if (bindedScene->bindedCamera == NULL) {
    return;
  }

  // Check if theres even anything to draw
  if (bindedScene->gameObjectsIndex <= 0) {
    return;
  }

  // Update camera
  UpdateGameCamera(bindedScene->bindedCamera);

  // Reset mvp matrices
  glm_mat4_identity(rtModel);
  glm_mat4_identity(rtView);
  glm_mat4_identity(rtProj);
  glm_mat4_identity(mvpRes);

  // Get camera values for rendering
  GetTransformMat(&bindedScene->bindedCamera->transform, &rtView);
  glm_mat4_inv(rtView, rtView);
  GetProjectionMat(bindedScene->bindedCamera, &rtProj);

  // update & draw each gameobject using the binded shader & camera
  glUseProgram(bindedShader);

  for (size_t i = 0; i < bindedScene->gameObjectsIndex; i++) {
    GameObject *gameObject = bindedScene->gameObjectsList[i];
    if (gameObject == NULL) {
      continue;
    }

    UpdateGameObject(gameObject);

    // Check if gameObject can be drawn.
    if (gameObject->transform != NULL && gameObject->model != NULL) {

      // Calculate its projection to the camera & bind to shader
      GetTransformMat(gameObject->transform, &rtModel);
      CalculateMVP(&rtProj, &rtView, &rtModel, &mvpRes);
      UploadMVP(&mvpRes, bindedShader);

      // Finally draw it
      DrawModel(gameObject->model);
    }
  }
}

void OnUpdate(void *function) {
  callback func = (callback)function;
  onUpdateCallbackIndex++;

  onUpdateCallbackList = (callback *)realloc(
      onUpdateCallbackList, onUpdateCallbackIndex * sizeof(callback));

  onUpdateCallbackList[onUpdateCallbackIndex - 1] = func;
}

void OnStart(void *function) {
  callback func = (callback)function;
  onStartCallbackIndex++;

  onStartCallbackList = (callback *)realloc(
      onStartCallbackList, onStartCallbackIndex * sizeof(callback));

  onStartCallbackList[onStartCallbackIndex - 1] = func;
}

void BindShader(unsigned int shader) {
  bindedShader = shader;
  glUseProgram(bindedShader);
}

void BindScene(Scene *scene) { bindedScene = scene; }

void AutoResize(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}
