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

#include "tile.h"

#include <assert.h>

#include <GL/glew.h>

#include "shader.h"

namespace e {

enum BUFFERS {
  B_VERTICES, B_INDICES,
  B_COUNT
};

struct TileData {
  int segments;

  GLuint buffers[B_COUNT];
  GLuint posId;
  GLuint mvpId;

  GLuint elements;

  Shader* shader;
  glm::mat4 model;

  bool initialized;

  TileData()
      : shader(NULL),
        model(glm::mat4(1.0f)),
        initialized(false) {
  }
};

static GLfloat* CreateVertices(const int segments, GLuint* size) {
  GLfloat div = (GLfloat)segments;

  int elements = (segments + 1) * (segments + 1) * 3;
  *size = sizeof(GLfloat) * elements;

  GLfloat* vertices = new GLfloat[elements];

  int index = 0;
  for (int y=0; y<=segments; y++) {
    for (int x=0; x<=segments; x++) {
      vertices[index++] = x / div - 0.5f;
      vertices[index++] = y / div - 0.5f;
      vertices[index++] = 0.0f;
    }
  }

  return vertices;
}

static GLuint* CreateIndices(const int segments, GLuint* size) {
  int width = segments + 1;
  int elements = (segments + 1) * 2 * segments;
  *size = sizeof(GLuint) * elements;

  GLuint* indices = new GLuint[elements];

  int index = 0;
  for (int y=0; y<segments; y++) {
    if (y % 2 == 0) {
      int start = y * width;
      for (int x=0; x<=segments; x++) {
        indices[index++] = start + x;
        indices[index++] = start + x + width;
      }
    }
    else {
      int start = (y + 1) * width - 1;
      for (int x=0; x<=segments; x++) {
        indices[index++] = start - x;
        indices[index++] = start - x + width;
      }
    }
  }

  return indices;
}

static void Init(TileData* data) {
  GLuint size;

  glGenBuffers(B_COUNT, &data->buffers[0]);

  GLfloat* vertices = CreateVertices(data->segments, &size);
  glBindBuffer(GL_ARRAY_BUFFER, data->buffers[B_VERTICES]);
  glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
  delete vertices;

  GLuint* indices = CreateIndices(data->segments, &size);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, data->buffers[B_INDICES]);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
  delete indices;

  data->elements = size;

  data->shader = new Shader("data/tile.vs", "data/tile.fs");
  data->shader->Load();
  data->posId = data->shader->GetAttribLocation("pos");
  data->mvpId = data->shader->GetUniformLocation("mvp");

  data->initialized = true;
}

static void DeInit(TileData* data) {
  glDeleteBuffers(B_COUNT, &data->buffers[0]);

  delete data->shader;
  data->shader = NULL;
}

Tile::Tile(const int segments)
    : segments_(segments) {
  assert(segments >= 2);

  data_ = new TileData();
  data_->segments = segments;
}

Tile::~Tile() {
  DeInit(data_);
  delete data_;
}

void Tile::Update() {
  if (!data_->initialized) Init(data_);
}

void Tile::Draw(glm::mat4 vp) {
  glm::mat4 mvp = vp * data_->model;

  glEnableVertexAttribArray(0);

  glUseProgram(data_->shader->program());

  glBindBuffer(GL_ARRAY_BUFFER, data_->buffers[B_VERTICES]);
  glVertexAttribPointer(data_->posId, 3, GL_FLOAT, GL_FALSE, 0, NULL);

  glUniformMatrix4fv(data_->mvpId, 1, GL_FALSE, &mvp[0][0]);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, data_->buffers[B_INDICES]);
  glDrawElements(GL_TRIANGLE_STRIP, data_->elements, GL_UNSIGNED_INT, 0);

  glDisableVertexAttribArray(0);
}

}

