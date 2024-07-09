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

#include "cglm/affine.h"
#include "cglm/call.h"
#include "cglm/mat4.h"
#include "glad/glad.h"
#include "kraine/renderer.h"
#include "ufbx.h"
#include <stdlib.h>

void DrawModel(Model *model) {

  // Draw each mesh
  for (size_t i = 0; i < model->meshListCount; i++) {
    Mesh *mesh = &model->meshList[0];
    DrawMesh(mesh);
  }
}

Model CreateModel() {
  // Initialize model and its values
  Model retModel;
  glm_mat4_identity(retModel.transform);

  return retModel;
}

Model LoadModelFBX(const char *path) {
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
    Model error;
    return error;
  }

  // Create model for return
  Model retModel = CreateModel();

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

  // Allocate number of meshes
  retModel.meshList = (Mesh *)malloc(meshCount * sizeof(Mesh));
  retModel.meshListCount = meshCount;

  meshCount = 0;
  for (size_t i = 0; i < scene->nodes.count; i++) {
    ufbx_node *node = scene->nodes.data[i];
    if (node->is_root)
      continue;

    // Loop through each mesh
    if (node->mesh) {
      // Convert fbx mesh to kraine mesh
      Mesh mesh = FbxToMesh(node->mesh);
      retModel.meshList[meshCount] = mesh;
      meshCount++;
    }
  }

  // Set default coordinates (0,0,3)
  // FIXME: TF?? read below
  glm_translate(retModel.transform, (vec3){0.0f, 0.0f, -43.0f});

  // Set its default size (1,1,1)
  glm_scale(retModel.transform, (vec3){1.0f, 1.0f, 1.0f});

  return retModel;
}
