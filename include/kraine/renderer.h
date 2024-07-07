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
Path: kraine/renderer.h

Date: 06/30/2024

Author: Dudubles

Description:
================================================*/

#pragma once

#include "cglm/types.h"
#include "ufbx.h"

#ifndef KRAINE_RENDERER

/*
==============================================================================

Mesh & vertices

==============================================================================
*/

typedef struct Vertex {

  float position[3];
  float texCoord[2];
} Vertex;

typedef struct Mesh {

  // Dynamic arrays
  Vertex *vertList;
  int vertListCount;
  unsigned int *indicesList;
  int indicesListCount;

  // Buffers and their IDs
  unsigned int VAO;
  unsigned int VBO;
  unsigned int EBO;
} Mesh;

void SetupGLBuffers(Mesh *mesh);

void DrawMesh(Mesh *mesh);

Vertex CreateVertex(float x, float y, float z, float texC1, float texC2);

// Converts UFBX mesh to Kraine Mesh
Mesh FbxToMesh(ufbx_mesh *mesh);

/*
==============================================================================

Models

==============================================================================
*/

typedef struct Model {

  // Dynamic arrays
  Mesh *meshList;
  int meshListCount;

  mat4 transform; // Model space transform matrix (Move, rotate etc...)
} Model;

void DrawModel(Model *model);

Model LoadModelFBX(const char *path);

Model CreateModel();

Model CreateCube();

/*
==============================================================================

Textures

==============================================================================
*/

unsigned int LoadTexFromFile(char *path);

/*
==============================================================================

Camera

==============================================================================
*/

typedef struct Camera {

  mat4 view;       // Camera space transform matrix (Move, rotate etc...)
  mat4 projection; // Projection matrix (By default its in perspective for 3D)
} Camera;

Camera CreateCamera();

/*
==============================================================================

Shaders

==============================================================================
*/

unsigned int ShaderFromFiles(const char *vPath, const char *fPath);

/*
==============================================================================

Coordinates System

==============================================================================
*/

void CalculateMVP(Camera *camera, Model *model, mat4 *dest);

void UploadMVP(mat4 *pvm, unsigned int shader);

//============================================================================

#endif // !KRAINE_RENDERER
