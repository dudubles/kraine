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

typedef float Vector3[3];

typedef struct Transform {

  // Properties
  Vector3 position;
  Vector3 rotation;
  Vector3 scale;

} Transform;

void InitTransform(Transform *dest);

void SetupTransform(Transform *dest);

void GetTransformMat(Transform *transform, mat4 *dest);

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

void InitGameObject(unsigned int type, GameObject *dest);

void SetupGameObject(unsigned int type, GameObject *dest);

void UpdateGameObject(GameObject *object);

void DestroyGameObject(GameObject *object);

void GameObject3D(const char *path, GameObject *dest);

/*
==============================================================================

Game Camera

==============================================================================
*/

#define GAMECAMERA_PERSPECTIVE 0

typedef struct GameCamera {

  // Components
  Transform transform;

  // Properties
  unsigned int projection;

} GameCamera;

void InitGameCamera(GameCamera *dest);

void SetupGameCamera(unsigned int projection, GameCamera *dest);

void GetProjectionMat(GameCamera *camera, mat4 *dest);

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

  GameObject **gameObjectsList; // List of pointers to gameobjects
  int gameObjectsIndex;

} Scene;

// CreateScene creates a default scene wich by default
// provides a 3D Perspective camera.

void InitScene(Scene *dest);

void SetupScene(Scene *dest);

void AddToScene(Scene *scene, GameObject *gameObject);

void DestroyScene(Scene *scene);

/*
==============================================================================

Game logic

==============================================================================
*/

// GameInit Initializes the game and waits for it to be exit
void GameInit(const char *title, int width, int height);

// OnUpdate takes a pointer to a void function and calls
// it on each frame once game is initialized
void OnUpdate(void *function);

// OnStart takes a pointer to a void function and calls
// it before the game is fully initialized
void OnStart(void *function);

void BindScene(Scene *scene);

void BindShader(unsigned int shader);

//============================================================================

#endif // !KRAINE_CORE
