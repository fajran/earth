// Copyright (C) 2013  Fajran Iman Rusadi
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

#include "earth.h"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "shader.h"
#include "camera.h"
#include "triangle.h"
#include "cube.h"
#include "tile.h"

namespace e {

static Camera camera(glm::perspective(45.0f, 4.0f/3.0f, 0.1f, 100.0f));

static Triangle* triangle = NULL;
static Cube* cube = NULL;
static Tile* tile = NULL;

Earth::Earth() {
}

Earth::~Earth() {
  if (triangle != NULL) {
    delete triangle;
  }
  if (cube != NULL) delete cube;
}

void Earth::Init() {
  triangle = new Triangle();
  cube = new Cube();
  tile = new Tile(8);

  camera.SetPosition(glm::vec3(0, 0, 10));
  camera.SetScale(glm::vec3(2, 2, 2));
  camera.SetRotation(glm::vec3(0, 0, 0));
}

void Earth::Update() {
  triangle->Update();
  cube->Update();
  tile->Update();
}

void Earth::Render() {
  glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  triangle->Draw(camera.Matrix());
  cube->Draw(camera.Matrix());
  tile->Draw(camera.Matrix());
}

}

