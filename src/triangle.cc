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

#include "triangle.h"

#include <GL/glew.h>

#include "shader.h"

namespace e {

static const GLfloat g_vertex_buffer_data[] = {
  -1.0f, -1.0f, 0.0f,
   1.0f, -1.0f, 0.0f,
   0.0f,  1.0f, 0.0f,
};

static const GLfloat color_data[] = {
  1.0f, 0.0f, 0.0f, 1.0f,
  0.0f, 1.0f, 0.0f, 1.0f,
  0.0f, 0.0f, 1.0f, 1.0f
};

struct TriangleData {
  GLuint vbo[2];
  GLuint posId;
  GLuint colorId;
  GLuint mvpId;

  Shader* shader;
  glm::mat4 model;
  glm::mat4 matrix;

  bool initialized;

  TriangleData() : shader(NULL), initialized(false) {
  }
};

static void Init(TriangleData* data) {
  glGenBuffers(2, &data->vbo[0]);

  glBindBuffer(GL_ARRAY_BUFFER, data->vbo[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

  glBindBuffer(GL_ARRAY_BUFFER, data->vbo[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(color_data), color_data, GL_STATIC_DRAW);

  data->shader = new Shader("data/triangle.vs", "data/triangle.fs");
  data->shader->Load();
  data->posId = data->shader->GetAttribLocation("pos");
  data->colorId = data->shader->GetAttribLocation("color");
  data->mvpId = data->shader->GetUniformLocation("mvp");

  data->initialized = true;
}

Triangle::Triangle() {
  data_ = new TriangleData();
  data_->model = glm::mat4(1.0f);
}

Triangle::~Triangle() {
  if (data_->shader != NULL) {
    delete data_->shader;
    data_->shader = NULL;
  }
  delete data_;
}

void Triangle::Apply(glm::mat4 matrix) {
  data_->matrix = matrix * data_->model;
}

void Triangle::Update() {
  if (!data_->initialized) {
    Init(data_);
  }
}

glm::mat4 Triangle::Matrix() {
  return data_->matrix;
}

void Triangle::Draw() {
  // 1rst attribute buffer : vertices
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glUseProgram(data_->shader->program());

  glBindBuffer(GL_ARRAY_BUFFER, data_->vbo[0]);
  glVertexAttribPointer(
     data_->posId,       // attribute 0. No particular reason for 0, but must match the layout in the shader.
     3,                  // size
     GL_FLOAT,           // type
     GL_FALSE,           // normalized?
     0,                  // stride
     (void*)0            // array buffer offset
  );
  glBindBuffer(GL_ARRAY_BUFFER, data_->vbo[1]);
  glVertexAttribPointer(
    data_->colorId,
    4,
    GL_FLOAT,
    GL_FALSE,
    0,
    (void*)0
  );
  glUniformMatrix4fv(data_->mvpId, 1, GL_FALSE, &data_->matrix[0][0]);

  // Draw the triangle !
  glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle

  glDisableVertexAttribArray(1);
  glDisableVertexAttribArray(0);
}

}

