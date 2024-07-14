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
path: core/scene.c

date: 07/07/2024

author: dudubles

description:
=================================================*/

#include "kraine/core.h"
#include <stdlib.h>

void InitScene(Scene *dest) {
  Scene res;

  // Initialize values
  res.bindedCamera = (GameCamera *)malloc(sizeof(GameCamera));
  InitGameCamera(res.bindedCamera);

  // Setup dinamyc arrays
  res.gameObjectsList = (GameObject **)malloc(sizeof(GameObject *));
  res.gameObjectsIndex = 0;

  memcpy(dest, &res, sizeof(Scene));
}

void SetupScene(Scene *dest) {
  // FIXME: Default values applied
  SetupGameCamera(GAMECAMERA_PERSPECTIVE, dest->bindedCamera);
}

void AddToScene(Scene *scene, GameObject *gameObject) {
  scene->gameObjectsIndex++;

  scene->gameObjectsList = (GameObject **)realloc(
      scene->gameObjectsList, scene->gameObjectsIndex * sizeof(GameObject **));

  scene->gameObjectsList[scene->gameObjectsIndex - 1] = gameObject;
}
