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

#include "kraine/core.h"
#include <stdlib.h>
#include <string.h>

void InitTransform(Transform *dest) {
  // Do nothing
  dest->position[0] = 0.0f;
  dest->position[1] = 0.0f;
  dest->position[2] = 0.0f;

  dest->rotation[0] = 0.0f;
  dest->rotation[1] = 0.0f;
  dest->rotation[2] = 0.0f;

  dest->scale[0] = 100.0f;
  dest->scale[1] = 100.0f;
  dest->scale[2] = 100.0f;
}

void SetupTransform(Transform *dest) {

  // Setup default values
}

void GetTransformMat(Transform *transform, mat4 *dest) {

  // Position
  glm_translate(*dest, transform->position);

  // Rotation
  glm_rotate(*dest, transform->rotation[2],
             (vec3){0, 0, 1}); // Rotate around z-axis
  glm_rotate(*dest, transform->rotation[1],
             (vec3){0, 1, 0}); // Rotate around y-axis
  glm_rotate(*dest, transform->rotation[0],
             (vec3){1, 0, 0}); // Rotate around x-axis

  // Scale
  glm_scale(*dest, transform->scale);
}
