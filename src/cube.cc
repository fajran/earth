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

#include "cube.h"

#include <GL/glew.h>

#include <glm/gtc/matrix_transform.hpp>

#include "shader.h"

namespace e {

static GLfloat vertices[] = {
  // bottom
  -0.5f, -0.5f,  0.5f,
   0.5f, -0.5f,  0.5f,
   0.5f, -0.5f, -0.5f,
  -0.5f, -0.5f, -0.5f,
  // top
  -0.5f,  0.5f,  0.5f,
   0.5f,  0.5f,  0.5f,
   0.5f,  0.5f, -0.5f,
  -0.5f,  0.5f, -0.5f,
};

static GLfloat colors[] = {
  // bottom
  1, 0, 0, 1,
  0, 1, 0, 1,
  0, 0, 1, 1,
  1, 0, 1, 1,
  // top
  0, 1, 1, 1,
  1, 1, 0, 1,
  1, 1, 1, 1,
  0, 0, 0, 1
};

static GLuint indices[] = {
  0, 2, 1, 1, 0, 3, // bottom
  1, 6, 5, 6, 1, 2, // right
  0, 5, 4, 5, 0, 1, // front
  0, 7, 3, 7, 0, 4, // left
  3, 6, 2, 6, 3, 7, // back
  4, 6, 7, 6, 4, 5  // top
};

enum BUFFERS {
  B_VERTICES, B_COLORS, B_INDICES,
  B_COUNT
};

struct CubeData {
  GLuint buffers[B_COUNT];
  Shader* shader;

  GLuint posId;
  GLuint colorId;
  GLuint mvpId;

  glm::mat4 model;
  glm::mat4 matrix;

  bool initialized;

  CubeData()
      : model(glm::mat4(1.0f)),
        matrix(glm::mat4(1.0f)),
        initialized(false) {
  }
};

static void Init(CubeData* data) {
  glGenBuffers(B_COUNT, &data->buffers[0]);

  glBindBuffer(GL_ARRAY_BUFFER, data->buffers[B_VERTICES]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ARRAY_BUFFER, data->buffers[B_COLORS]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, data->buffers[B_INDICES]);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
               GL_STATIC_DRAW);

  data->shader = new Shader("data/cube.vs", "data/cube.fs");
  data->shader->Load();

  data->posId = data->shader->GetAttribLocation("pos");
  data->colorId = data->shader->GetAttribLocation("color");
  data->mvpId = data->shader->GetUniformLocation("mvp");

  data->initialized = true;
}

static void DeInit(CubeData* data) {
  glDeleteBuffers(B_COUNT, &data->buffers[0]);

  data->shader->Unload();
  delete data->shader;
}

Cube::Cube() {
  data_ = new CubeData();
}

Cube::~Cube() {
  DeInit(data_);
  delete data_;
}

void Cube::Apply(glm::mat4 matrix) {
  data_->matrix = matrix * data_->model;
}

void Cube::Update() {
  if (!data_->initialized) Init(data_);
  data_->model = glm::rotate(data_->model, 1.0f, glm::vec3(0.1, 0.2, 0.3));
}

glm::mat4 Cube::Matrix() {
  return data_->matrix;
}

void Cube::Draw() {
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);

  glUseProgram(data_->shader->program());

  glBindBuffer(GL_ARRAY_BUFFER, data_->buffers[B_VERTICES]);
  glVertexAttribPointer(data_->posId, 3, GL_FLOAT, GL_FALSE, 0, NULL);

  glBindBuffer(GL_ARRAY_BUFFER, data_->buffers[B_COLORS]);
  glVertexAttribPointer(data_->colorId, 4, GL_FLOAT, GL_FALSE, 0, NULL);

  glUniformMatrix4fv(data_->mvpId, 1, GL_FALSE, &data_->matrix[0][0]);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, data_->buffers[B_INDICES]);
  glDrawElements(GL_TRIANGLES, 3 * 2 * 6, GL_UNSIGNED_INT, 0);

  glDisableVertexAttribArray(1);
  glDisableVertexAttribArray(0);
}

}

