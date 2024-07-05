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

#include "cglm/affine-pre.h"
#include "glad/glad.h"
#include "renderer.h"
#include <cstring>
#include <stdlib.h>

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

Model CreateCube() {
  // Create cube mesh
  Mesh retMesh;
  retMesh.vertList = (Vertex *)malloc(36 * sizeof(Vertex));

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

  Model retModel;
  retModel.mesh = retMesh;

  // Set default coordinates (0,0,0)
  mat4 defaultLocation = {
      1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
      1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
  };
  glm_translate(defaultLocation, (vec3){0.0f, 0.0f, 0.0f});

  memcpy(retModel.transform.modelSpace, defaultLocation,
         sizeof(defaultLocation));

  return retModel;
}
