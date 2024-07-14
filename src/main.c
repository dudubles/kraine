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
Path: main.c

Date: 06/30/2024

Author: Dudubles

Description: This is just to test some shi
=================================================*/

#include "kraine/core.h"
#include "kraine/renderer.h"
#include <stdio.h>

Scene newscene;
GameObject model;

void start() {
  printf("Game Started\n");

  // Create new scene
  InitScene(&newscene);
  SetupScene(&newscene);
  BindScene(&newscene);
  newscene.bindedCamera->transform.position[2] = -10.0f;

  // Create game object
  InitGameObject(GAMEOBJECT_3D, &model);
  SetupGameObject(GAMEOBJECT_3D, &model);
  GameObject3D("C:/Users/tiago/Desktop/Kraine/resource/assets/horse.fbx",
               &model);

  unsigned int texture = LoadTexFromFile(
      (char *)"C:/Users/tiago/Desktop/Kraine/resource/assets/225CE9.png");
  model.model->meshList[0]->texture = texture;

  // Add game object to the Scene
  AddToScene(&newscene, &model);
}

void update() {
  model.transform->rotation[2] = 90.0f;
  model.transform->position[2] = -100000.0f;
}

int main(int argc, char *argv[]) {

  OnUpdate((void *)&update);
  OnStart((void *)&start);

  GameInit("Kraine Engine [Test]", 800, 600);
  return 0;
}
