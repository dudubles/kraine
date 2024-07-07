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
Path: renderer/coords.c

Date: 07/07/2024

Author: Dudubles

Description:
=================================================*/

#include "cglm/mat4.h"
#include "glad/glad.h"
#include "kraine/renderer.h"
#include <stdio.h>
#include <string.h>

mat4 *CalculateMVP(Camera *camera, Model *model) {

  // Calculate mvp (projection matrix * view matrix * model matrix)
  mat4 mvp;
  glm_mat4_mulN(
      (mat4 *[]){
          &camera->projection,
          &camera->view,
          &model->transform,
      },
      3, mvp);

  // Allocate new value
  mat4 *retMvp = (mat4 *)malloc(sizeof(mvp));
  memcpy(retMvp, &mvp, sizeof(mvp));

  return retMvp;
}

void UploadMVP(mat4 *mvp, unsigned int shader) {

  // Get uniform location
  int mvpLoc = glGetUniformLocation(shader, "mvp");

  // Debug any errors
  if (mvpLoc < 0) {
    printf("[ERROR] : Error while trying to get uniform: mvp\n");
    return;
  }

  // Set uniform
  glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, mvp[0][0]);
}
