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
Path: renderer/mesh.c

Date: 07/02/2024

Author: Dudubles

Description:
=================================================*/

#include "glad/glad.h"
#include "kraine/renderer.h"
#include "stdio.h"
#include "ufbx.h"
#include <stdlib.h>

void DrawMesh(Mesh *mesh) {

  // Debugging
  if (mesh->vertListCount <= 0) {
    printf("[ERROR] : Trying to draw mesh with 0 vertices result ignored\n");
    return;
  }

  glBindVertexArray(mesh->VAO);
  glDrawElements(GL_TRIANGLES, mesh->indicesListCount * sizeof(unsigned int),
                 GL_UNSIGNED_INT, 0);
}

void SetupGLBuffers(Mesh *mesh) {
  // Generate VAO (Just wraps VBO and EBO in one)
  glGenVertexArrays(1, &mesh->VAO);

  // Generate buffers that opengl will read
  glGenBuffers(1, &mesh->VBO);
  glGenBuffers(1, &mesh->EBO);

  // Insert data inside buffers
  glBindVertexArray(mesh->VAO);

  glBindBuffer(GL_ARRAY_BUFFER, mesh->VBO);
  glBufferData(GL_ARRAY_BUFFER, mesh->vertListCount * sizeof(Vertex),
               &mesh->vertList[0], GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,
               mesh->indicesListCount * sizeof(unsigned int),
               &mesh->indicesList[0], GL_STATIC_DRAW);

  // | LAYOUT 0 | Vertices positions
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);

  // | LAYOUT 1 | Texture coordinates
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                        (void *)(3 * sizeof(float)));

  // Just in case
  glBindVertexArray(0);
}

Vertex CreateVertex(float x, float y, float z, float texC1, float texC2) {
  Vertex ret;
  ret.position[0] = x;
  ret.position[1] = y;
  ret.position[2] = z;

  ret.texCoord[0] = texC1;
  ret.texCoord[1] = texC2;

  return ret;
}

Mesh FbxToMesh(ufbx_mesh *mesh) {

  // Init mesh
  Mesh retMesh;

  // Initialize dynamic arrays
  retMesh.vertList = (Vertex *)malloc(mesh->vertices.count * sizeof(Vertex));
  retMesh.vertListCount = mesh->vertices.count;
  retMesh.indicesList =
      (unsigned int *)malloc(mesh->vertex_indices.count * sizeof(unsigned int));
  retMesh.indicesListCount = mesh->vertex_indices.count;

  // Transform each vertex
  for (size_t i = 0; i < mesh->vertices.count; i++) {

    // Transform vertex
    ufbx_vec3 curVertex = mesh->vertices.data[i];
    Vertex transVertex = CreateVertex((float)curVertex.x, (float)curVertex.y,
                                      (float)curVertex.z, 1.0f, 1.0f);
    // Assign vertex
    retMesh.vertList[i] = transVertex;
  }

  // Add indices
  for (size_t i = 0; i < mesh->vertex_indices.count; i++) {
    retMesh.indicesList[i] = mesh->vertex_indices.data[i];
  }

  SetupGLBuffers(&retMesh);

  return retMesh;
}
