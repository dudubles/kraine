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

#include "cglm/affine-pre.h"
#include "cglm/cam.h"
#include "cglm/types.h"
#include "cglm/util.h"
#include "renderer.h"
#include <string.h>

void SetCameraDefault3D(Camera *camera) {

  // Setup the default view matrix (default coordinates)
  mat4 defaultView = {
      1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
      1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
  };
  glm_translate(defaultView, (vec3){0.0f, 0.0f, -3.0f});

  memcpy(camera->viewSpace, defaultView, sizeof(defaultView));

  // By default we are gonna set the perspective matrix
  glm_perspective(glm_rad(45.0f), 800.0f / 600.0f, 0.1f, 100.0f,
                  camera->projection);
}
