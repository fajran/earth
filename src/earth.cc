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

#include "camera.h"
#include "tile.h"

#include "node.h"
#include "node-visitor.h"

namespace e {

struct EarthData {
  Node* root;
  NodeVisitor* visitor;

  bool initialized;

  EarthData() : initialized(false) {
    root = NULL;
  }

  void Init() {
    visitor = new NodeVisitor();

    initialized = true;
  }

  void DeInit() {
    delete visitor;
  }
};

Earth::Earth() {
  data_ = new EarthData();
}

Earth::~Earth() {
  data_->DeInit();
  // FIXME cleanup camera and tile
}

void Earth::Init() {
  Camera* camera = new Camera(glm::perspective(45.0f, 4.0f/3.0f, 0.1f, 100.0f));
  camera->SetPosition(glm::vec3(0, 0, 4));
  camera->SetScale(glm::vec3(2, 2, 2));
  camera->SetRotation(glm::vec3(0, 0, 0));
  data_->root = camera;

  Tile* tile = new Tile(8);
  camera->AddChild(tile);
}

void Earth::Update() {
  if (!data_->initialized) {
    data_->Init();
  }

  if (data_->root != NULL) {
    data_->visitor->Update(data_->root);
  }
}

void Earth::Render() {
  glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  if (data_->root != NULL) {
    data_->visitor->Draw(data_->root);
  }
}

}

