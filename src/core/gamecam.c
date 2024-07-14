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
Path: core/gamecam.c

Date: 07/07/2024

Author: Dudubles

Description:
=================================================*/

#include "cglm/mat4.h"
#include "kraine/core.h"
#include <stdlib.h>

void InitGameCamera(GameCamera *dest) {
  GameCamera res;

  // Initialize values
  InitTransform(&res.transform);
  res.projection = 0;

  memcpy(dest, &res, sizeof(GameCamera));
};

void SetupGameCamera(unsigned int projection, GameCamera *dest) {
  dest->projection = projection;
  SetupTransform(&dest->transform);
};

void GetProjectionMat(GameCamera *camera, mat4 *dest) {

  if (camera->projection == GAMECAMERA_PERSPECTIVE) {
    // FIXME: Default values below
    glm_perspective(45.0f, (float)1280 / (float)720, 0.1f, 100.0f, *dest);
  }
}

void UpdateGameCamera(GameCamera *camera) {
  // TODO: UpdateGameCamera
}
