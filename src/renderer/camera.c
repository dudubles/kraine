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
Path: renderer/camera.c

Date: 07/03/2024

Author: Dudubles

Description:
=================================================*/

#include "cglm/call.h"
#include "cglm/cam.h"
#include "cglm/types.h"
#include "cglm/util.h"
#include "cglm/vec3.h"
#include "glad/glad.h"
#include "kraine/renderer.h"

Camera CreateCamera() {

  // Initialize camera and its values
  Camera retcam;
  glm_mat4_identity(retcam.projection);
  glm_mat4_identity(retcam.view);

  // Setup camera default projection
  glm_perspective(glm_rad(45.0f), (float)1280 / (float)720, 0.1f, 100.0f,
                  retcam.projection); // Setting up with 45.0 FOV and aspect
                                      // ratio of 16:9 (1280 / 720)

  // Setup camera default location (position: 0,0,0)
  glm_translate(retcam.view, (vec3){0.0f, 0.0f, 0.0f});

  return retcam;
}
