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

#include "glad/glad.h"
#include "kraine/renderer.h"
#include "ufbx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void DrawModel(Model *model) {

  // Draw each mesh
  for (size_t i = 0; i < model->meshListCount; i++) {
    DrawMesh(model->meshList[i]);
  }
}

void InitModel(Model *dest) {
  Model res;

  // Initialize dinamyc arrays
  res.meshList = (Mesh **)malloc(sizeof(Mesh));
  res.meshListCount = 0;

  memcpy(dest, &res, sizeof(Model));
};

void SetupModel(Model *dest) {
  // Do nothing
};

void LoadModelFBX(const char *path, Model *dest) {
  printf("[DEBUG] : Loading 3D FBX Model from path: %s\n", path);

  // Load ufbx with default options
  ufbx_load_opts opts = {0};
  ufbx_error error;

  // Load file
  ufbx_scene *scene = ufbx_load_file(path, &opts, &error);

  // Debug any errors
  if (!scene) {
    printf("[ERROR] : Error while trying to load fbx file -> %s\n",
           error.description.data);
  }

  // Count number of meshes
  int meshCount = 0;
  for (size_t i = 0; i < scene->nodes.count; i++) {
    ufbx_node *node = scene->nodes.data[i];
    if (node->is_root)
      continue;

    if (node->mesh) {
      meshCount++;
    }
  }

  // Reallocate number of meshes
  dest->meshList = (Mesh **)realloc(dest->meshList, meshCount * sizeof(Mesh *));
  dest->meshListCount = meshCount;

  meshCount = 0;
  for (size_t i = 0; i < scene->nodes.count; i++) {
    ufbx_node *node = scene->nodes.data[i];
    if (node->is_root)
      continue;

    // Loop through each mesh
    if (node->mesh) {

      // Convert fbx mesh to kraine mesh
      Mesh *resMesh = (Mesh *)malloc(sizeof(Mesh));
      InitMesh(resMesh);
      FbxToMesh(node->mesh, resMesh);

      dest->meshList[meshCount] = resMesh;
      meshCount++;
    }
  }
}
