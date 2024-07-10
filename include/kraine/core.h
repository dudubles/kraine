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
Path: kraine/core.h

Date: 07/07/2024

Author: Dudubles

Description:
=================================================*/

#include "kraine/renderer.h"

#ifndef KRAINE_CORE

/*
==============================================================================

Transform Components

==============================================================================
*/

typedef struct Vector3 {

  // Properties
  float x, y, z;

} Vector3;

typedef struct Transform {

  // Properties
  Vector3 position;
  Vector3 rotation;
  Vector3 scale;

} Transform;

Transform *TemplateTransform(int x, int y, int z);

/*
==============================================================================

Game Objects

==============================================================================
*/

#define GAMEOBJECT_CUSTOM 0
#define GAMEOBJECT_3D 1

typedef struct GameObject {

  // Components
  Model *model;
  Transform *transform;

  // Properties
  unsigned int type;

} GameObject;

GameObject *CreateGameObject(unsigned int type);

GameObject *GameObject3D(const char *path);

void UpdateTransform(GameObject *object); // Defined in transform.c

void UpdateGameObject(GameObject *object);

void DestroyGameObject(GameObject *object);

/*
==============================================================================

Game Camera

==============================================================================
*/

#define GAMECAMERA_PERSPECTIVE 0

typedef struct GameCamera {

  // Components
  Camera *renderCamera;
  Transform *transform;

  // Properties
  unsigned int projection;

} GameCamera;

GameCamera *CreateGameCamera(unsigned int projection);

void UpdateGameCamera(GameCamera *camera);

void DestroyGameCamera(GameCamera *camera);

/*
==============================================================================

Scene

==============================================================================
*/

typedef struct Scene {

  // Properties

  GameCamera *bindedCamera;

  // Dynamic arrays

  GameObject *gameObjectsList;
  int gameObjectsIndex;

} Scene;

void AddToScene(GameObject *gameObject);

/*
==============================================================================

Game logic

==============================================================================
*/

void GameInit(const char *title, int width, int height);

//============================================================================

#endif // !KRAINE_CORE
