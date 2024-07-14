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

void InitMesh(Mesh *dest) {
  Mesh res;

  // Initialize values
  res.texture = 0;
  res.indicesListCount = 0;
  res.vertListCount = 0;
  res.EBO = 0;
  res.VBO = 0;
  res.VAO = 0;

  // Initialize dinamyc arrays
  res.indicesList = (unsigned int *)malloc(sizeof(unsigned int));
  res.vertList = (Vertex *)malloc(sizeof(Vertex));

  memcpy(dest, &res, sizeof(Mesh));
}

void DrawMesh(Mesh *mesh) {

  // Debugging
  if (mesh->vertListCount <= 0) {
    printf("[ERROR] : Trying to draw mesh with 0 vertices result ignored\n");
    return;
  }

  if (mesh->texture != 0) {
    glBindTexture(GL_TEXTURE_2D, mesh->texture);
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

void InitVertex(Vertex *dest) {
  Vertex res;

  // Initialize values
  res.position[0] = 0.0f;
  res.position[1] = 0.0f;
  res.position[2] = 0.0f;
  res.texCoord[0] = 0.0f;
  res.texCoord[1] = 0.0f;

  memcpy(dest, &res, sizeof(Vertex));
};

void SetupVertex(float x, float y, float z, float texC1, float texC2,
                 Vertex *dest) {
  dest->position[0] = x;
  dest->position[1] = y;
  dest->position[2] = z;

  dest->texCoord[0] = texC1;
  dest->texCoord[1] = texC2;
};

void FbxToMesh(ufbx_mesh *mesh, Mesh *dest) {
  // Initialize dynamic arrays
  dest->vertList =
      (Vertex *)realloc(dest->vertList, mesh->vertices.count * sizeof(Vertex));
  dest->vertListCount = mesh->vertices.count;
  dest->indicesList = (unsigned int *)realloc(
      dest->indicesList, mesh->vertex_indices.count * sizeof(unsigned int));
  dest->indicesListCount = mesh->vertex_indices.count;

  // Transform each vertex
  for (size_t i = 0; i < mesh->vertices.count; i++) {

    // Transform vertex
    ufbx_vec3 curVertex = mesh->vertices.data[i];
    Vertex transVertex;
    InitVertex(&transVertex);
    SetupVertex((float)curVertex.x, (float)curVertex.y, (float)curVertex.z,
                curVertex.v[0], curVertex.v[1], &transVertex);

    // Assign vertex
    dest->vertList[i] = transVertex;
  }

  // Add indices
  for (size_t i = 0; i < mesh->vertex_indices.count; i++) {
    dest->indicesList[i] = mesh->vertex_indices.data[i];
  }

  SetupGLBuffers(dest);
}
