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
