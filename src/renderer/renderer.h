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
Path: renderer/renderer.h

Date: 06/30/2024

Author: Dudubles

Description:
================================================*/

#pragma once

#include "cglm/types.h"

#ifndef KRAINE_RENDERER

typedef struct Vertex {

  float position[3];
  float texCoord[2];
} Vertex;

typedef struct Mesh {

  // Dynamic arrays
  Vertex *vertList;
  int vertListSize;
  unsigned int *indicesList;

  // Buffers and their IDs
  unsigned int VAO;
  unsigned int VBO;
  unsigned int EBO;
} Mesh;

typedef struct Transform {

  mat4 modelSpace; // Model space (coords of the model)
} Transform;

typedef struct Model {

  Mesh mesh;
  Transform transform;
} Model;

typedef struct Camera {

  unsigned int bindedShader;
  mat4 viewSpace;  // Camera coordinates
  mat4 projection; // Projection matrix, DEFAULT: Perspective
} Camera;

void SetCameraDefault3D(Camera *camera);

void PrepareCamForDraw(Camera *camera);

void DrawModel(Model *model);

void SetupGLBuffers(Mesh *mesh);

Model CreateCube();

unsigned int LoadTexFromFile(char *path);

unsigned int LoadShaders(const char *vPath, const char *fPath);

#endif // !KRAINE_RENDERER
