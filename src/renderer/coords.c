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

#include "glad/glad.h"
#include "kraine/renderer.h"
#include <cglm/call.h>
#include <cglm/cglm.h>
#include <stdio.h>
#include <stdlib.h>

void CalculateMVP(mat4 *projection, mat4 *view, mat4 *model, mat4 *dest) {
  glm_mat4_mul(*projection, *view, *dest);
  glm_mat4_mul(*dest, *model, *dest);
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
