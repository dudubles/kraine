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
Path: renderer/model.c

Date: 07/03/2024

Author: Dudubles

Description:
=================================================*/

#include "cglm/call.h"
#include "cglm/mat4.h"
#include "glad/glad.h"
#include "kraine/renderer.h"
#include <stdlib.h>

void ModelMatrixUpdate(Model *model, unsigned int shader) {

  // Get uniform location
  int modelLoc = glGetUniformLocation(shader, "model");

  // Debug uniform location in case of any errors
  if (modelLoc < 0) {
    printf("[ERROR] : Error while trying to get uniform of model");
    return;
  }

  // Update model transform matrix (transform)
  glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &model->transform[0][0]);
}

void DrawModel(Model *model) {

  glBindVertexArray(model->mesh.VAO);

  glDrawArrays(GL_TRIANGLES, 0, model->mesh.vertListSize);
}

// This shit is just for testing (or is it?)
Vertex NewVertex(float x, float y, float z, float texC1, float texC2) {
  Vertex ret;
  ret.position[0] = x;
  ret.position[1] = y;
  ret.position[2] = z;

  ret.texCoord[0] = texC1;
  ret.texCoord[1] = texC2;

  return ret;
}

Model CreateModel() {
  // Initialize model and its values
  Model retModel;
  glm_mat4_identity(retModel.transform);

  return retModel;
}

Model CreateCube() {
  // Create cube mesh
  Mesh retMesh;
  retMesh.vertList = (Vertex *)malloc(36 * sizeof(Vertex));

  // Set cube mesh vertices
  retMesh.vertList[0] = NewVertex(-0.5f, -0.5f, -0.5f, 0.0f, 0.0f);
  retMesh.vertList[1] = NewVertex(0.5f, -0.5f, -0.5f, 1.0f, 0.0f);
  retMesh.vertList[2] = NewVertex(0.5f, 0.5f, -0.5f, 1.0f, 1.0f);
  retMesh.vertList[3] = NewVertex(0.5f, 0.5f, -0.5f, 1.0f, 1.0f);
  retMesh.vertList[4] = NewVertex(-0.5f, 0.5f, -0.5f, 0.0f, 1.0f);
  retMesh.vertList[5] = NewVertex(-0.5f, -0.5f, -0.5f, 0.0f, 0.0f);

  retMesh.vertList[6] = NewVertex(-0.5f, -0.5f, 0.5f, 0.0f, 0.0f);
  retMesh.vertList[7] = NewVertex(0.5f, -0.5f, 0.5f, 1.0f, 0.0f);
  retMesh.vertList[8] = NewVertex(0.5f, 0.5f, 0.5f, 1.0f, 1.0f);
  retMesh.vertList[9] = NewVertex(0.5f, 0.5f, 0.5f, 1.0f, 1.0f);
  retMesh.vertList[10] = NewVertex(-0.5f, 0.5f, 0.5f, 0.0f, 1.0f);
  retMesh.vertList[11] = NewVertex(-0.5f, -0.5f, 0.5f, 0.0f, 0.0f);

  retMesh.vertList[12] = NewVertex(-0.5f, 0.5f, 0.5f, 1.0f, 0.0f);
  retMesh.vertList[13] = NewVertex(-0.5f, 0.5f, -0.5f, 1.0f, 1.0f);
  retMesh.vertList[14] = NewVertex(-0.5f, -0.5f, -0.5f, 0.0f, 1.0f);
  retMesh.vertList[15] = NewVertex(-0.5f, -0.5f, -0.5f, 0.0f, 1.0f);
  retMesh.vertList[16] = NewVertex(-0.5f, -0.5f, 0.5f, 0.0f, 0.0f);
  retMesh.vertList[17] = NewVertex(-0.5f, 0.5f, 0.5f, 1.0f, 0.0f);

  retMesh.vertList[18] = NewVertex(0.5f, 0.5f, 0.5f, 1.0f, 0.0f);
  retMesh.vertList[19] = NewVertex(0.5f, 0.5f, -0.5f, 1.0f, 1.0f);
  retMesh.vertList[20] = NewVertex(0.5f, -0.5f, -0.5f, 0.0f, 1.0f);
  retMesh.vertList[21] = NewVertex(0.5f, -0.5f, -0.5f, 0.0f, 1.0f);
  retMesh.vertList[22] = NewVertex(0.5f, -0.5f, 0.5f, 0.0f, 0.0f);
  retMesh.vertList[23] = NewVertex(0.5f, 0.5f, 0.5f, 1.0f, 0.0f);

  retMesh.vertList[24] = NewVertex(-0.5f, -0.5f, -0.5f, 0.0f, 1.0f);
  retMesh.vertList[25] = NewVertex(0.5f, -0.5f, -0.5f, 1.0f, 1.0f);
  retMesh.vertList[26] = NewVertex(0.5f, -0.5f, 0.5f, 1.0f, 0.0f);
  retMesh.vertList[27] = NewVertex(0.5f, -0.5f, 0.5f, 1.0f, 0.0f);
  retMesh.vertList[28] = NewVertex(-0.5f, -0.5f, 0.5f, 0.0f, 0.0f);
  retMesh.vertList[29] = NewVertex(-0.5f, -0.5f, -0.5f, 0.0f, 1.0f);

  retMesh.vertList[30] = NewVertex(-0.5f, 0.5f, -0.5f, 0.0f, 1.0f);
  retMesh.vertList[31] = NewVertex(0.5f, 0.5f, -0.5f, 1.0f, 1.0f);
  retMesh.vertList[32] = NewVertex(0.5f, 0.5f, 0.5f, 1.0f, 0.0f);
  retMesh.vertList[33] = NewVertex(0.5f, 0.5f, 0.5f, 1.0f, 0.0f);
  retMesh.vertList[34] = NewVertex(-0.5f, 0.5f, 0.5f, 0.0f, 0.0f);
  retMesh.vertList[35] = NewVertex(-0.5f, 0.5f, -0.5f, 0.0f, 1.0f);

  retMesh.vertListSize = 36;
  SetupGLBuffers(&retMesh);

  // Setup model

  Model retModel = CreateModel();
  retModel.mesh = retMesh;

  // Set default coordinates (0,0,0)
  glm_translate(retModel.transform, (vec3){0.0f, 0.0f, 0.0f});

  return retModel;
}
