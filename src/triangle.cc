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

  Shader* shader = NULL;
  glm::mat4 model;

  bool initialized;

  TriangleData() : initialized(false) {
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

void Triangle::Update() {
  if (!data_->initialized) {
    Init(data_);
  }
}

void Triangle::Draw(glm::mat4 vp) {
  glm::mat4 mvp = vp * data_->model;

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
  glUniformMatrix4fv(data_->mvpId, 1, GL_FALSE, &mvp[0][0]);

  // Draw the triangle !
  glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle

  glDisableVertexAttribArray(1);
  glDisableVertexAttribArray(0);
}

}

