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

#include "kraine/core.h"
#include "kraine/renderer.h"
#include "string.h"

void InitGameObject(unsigned int type, GameObject *dest) {
  GameObject res;

  // Initialize values
  res.type = type;

  // Initialize optional values
  if (type == GAMEOBJECT_3D) {
    res.transform = (Transform *)malloc(sizeof(Transform));
    res.model = (Model *)malloc(sizeof(Model));

    InitTransform(res.transform);
    InitModel(res.model);
  }

  memcpy(dest, &res, sizeof(GameObject));
};

void SetupGameObject(unsigned int type, GameObject *dest) {
  if (type == GAMEOBJECT_3D) {
    SetupTransform(dest->transform);
    SetupModel(dest->model);
  }
}

void GameObject3D(const char *path, GameObject *dest) {

  // Create game object
  LoadModelFBX(path, dest->model);
}

void DestroyGameObject(GameObject *object) {
  // TODO: DestroyGameObject
}

void UpdateGameObject(GameObject *object) {
  // TODO: UpdateGameObject
}
