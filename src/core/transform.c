/*
  mit license

  copyright (c) 2024 dudubles

  permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "software"), to deal
  in the software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the software, and to permit persons to whom the software is
  furnished to do so, subject to the following conditions:

  the above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the software.

  the software is provided "as is", without warranty of any kind, express or
  implied, including but not limited to the warranties of merchantability,
  fitness for a particular purpose and noninfringement. in no event shall the
  authors or copyright holders be liable for any claim, damages or other
  liability, whether in an action of contract, tort or otherwise, arising from,
  out of or in connection with the software or the use or other dealings in the
  software.
*/

/*=================================================
path: core/transform.c

date: 07/07/2024

author: dudubles

description:
=================================================*/

#include "cglm/cglm.h"
#include "kraine/core.h"

Transform *TemplateTransform(int x, int y, int z) {

  Vector3 position;
  position.x = 0;
  position.y = 0;
  position.z = 0;

  Vector3 rotation;
  rotation.x = 0;
  rotation.y = 0;
  rotation.z = 0;

  Vector3 scale;
  scale.x = 0;
  scale.y = 0;
  scale.z = 0;

  Transform *retTransform = (Transform *)malloc(sizeof(Transform));

  retTransform->position = position;
  retTransform->rotation = rotation;
  retTransform->scale = scale;

  return retTransform;
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
