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
Path: core/gameobj.c

Date: 07/07/2024

Author: Dudubles

Description:  Object.c manages all the logic of
              gameobjects
=================================================*/

#include "cglm/call.h"
#include "cglm/mat4.h"
#include "cglm/types.h"
#include "kraine/core.h"
#include "kraine/renderer.h"
#include "string.h"

void UpdateTransform(GameObject *object);

void DestroyGameObject() {
  // TODO: DestroyGameObject
}

void UpdateGameObject(GameObject *object) {

  // Check if the object can be drawn, if so update everything needed to draw
  // (THIS DOESNT DRAW IT)
  if (object->model != NULL) {

    // Update its position, rotation and scale
    UpdateTransform(object);
  }
}

void UpdateTransform(GameObject *object) {

  // Initialize result variable
  mat4 transformRes;
  glm_mat4_identity(transformRes);

  // Update position
  glm_translate(transformRes, (vec3){
                                  object->transform->position.x,
                                  object->transform->position.y,
                                  object->transform->position.z,
                              });

  // Update rotation angle on X axis
  glm_rotate(transformRes, glm_rad(object->transform->rotation.x),
             (vec3){
                 1.0f,
                 0.0f,
                 0.0f,
             });

  // Update rotation angle on Y axis
  glm_rotate(transformRes, glm_rad(object->transform->rotation.y),
             (vec3){
                 0.0f,
                 1.0f,
                 0.0f,
             });

  // Update rotation angle on Z axis
  glm_rotate(transformRes, glm_rad(object->transform->rotation.z),
             (vec3){
                 0.0f,
                 0.0f,
                 1.0f,
             });

  // Update its scale
  glm_scale(transformRes, (vec3){
                              object->transform->scale.x,
                              object->transform->scale.y,
                              object->transform->scale.z,
                          });

  // Store result inside model (basically update it)
  memcpy(object->model->transform, transformRes, sizeof(transformRes));
}
