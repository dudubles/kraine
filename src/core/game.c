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
#include "kraine/core.h"
#include "kraine/renderer.h"
#include <GLFW/glfw3.h>
#include <cglm/call.h>
#include <pthread.h>

/*
==============================================================================

Typedefs & vars

==============================================================================
*/

unsigned int initialized = 0;

typedef void (*callback)(void);

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

//============================================================================

void AutoResize(GLFWwindow *window, int width, int height);

void *GameThread(void *windowIn) {

  GLFWwindow *window = (GLFWwindow *)windowIn; // Cast type to glfwwindow

  while (!glfwWindowShouldClose(window)) {

    // Call every OnUpdate() function
    for (size_t i = 0; i < onUpdateCallbackIndex; i++) {
      onUpdateCallbackList[i]();
    }

    // Check if scene can be drawn
    if (bindedScene->bindedCamera == NULL) {
      continue;
    }

    // Clear screen and then update & draw each gameobject using the binded
    // camera & shaders
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (size_t i = 0; i < bindedScene->gameObjectsIndex; i++) {
      GameObject *gameObject = &bindedScene->gameObjectsList[i];

      UpdateGameObject(gameObject);

      // Check if gameObject can be drawn.
      if (gameObject->transform != NULL && gameObject->model != NULL) {

        // Calculate its projection to the camera & bind to shader
        mat4 mvpRes;
        CalculateMVP(bindedScene->bindedCamera->renderCamera, gameObject->model,
                     &mvpRes);
        UploadMVP(&mvpRes, bindedShader);

        // Finally draw it
        DrawModel(gameObject->model);
      }
    }

    // End of new frame
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}

void GameInit(const char *title, int width, int height) {

  if (initialized == 1) {
    return;
  }

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

  Scene defaultScene;
  GameCamera defaultCam;

  bindedScene = &defaultScene;

  pthread_t windowID;
  pthread_create(&windowID, NULL, GameThread, NULL);
  pthread_detach(windowID);

  initialized = 1;
}
