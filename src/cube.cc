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

static GLuint indices[] = {
  0, 2, 1, 1, 0, 3, // bottom
  1, 6, 5, 6, 1, 2, // right
  0, 5, 4, 5, 0, 1, // front
  0, 7, 3, 7, 0, 4, // left
  3, 6, 2, 6, 3, 7, // back
  4, 6, 7, 6, 4, 5  // top
};

enum BUFFERS {
  B_VERTICES, B_INDICES,
  B_COUNT
};

struct CubeData {
  GLuint buffers[B_COUNT];
  Shader* shader;

  GLuint posId;
  GLuint mvpId;

  glm::mat4 model;

  bool initialized;

  CubeData()
      : model(glm::mat4(1.0f)),
        initialized(false) {
  }
};

static void Init(CubeData* data) {
  glGenBuffers(B_COUNT, &data->buffers[0]);

  glBindBuffer(GL_ARRAY_BUFFER, data->buffers[B_VERTICES]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, data->buffers[B_INDICES]);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
               GL_STATIC_DRAW);

  data->shader = new Shader("data/cube.vs", "data/cube.fs");
  data->shader->Load();

  data->posId = data->shader->GetAttribLocation("pos");
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

void Cube::Update() {
  if (!data_->initialized) Init(data_);
  data_->model = glm::rotate(data_->model, 1.0f, glm::vec3(0.1, 0.2, 0.3));
}

void Cube::Draw(glm::mat4 vp) {
  glm::mat4 mvp = vp * data_->model;

  glEnableVertexAttribArray(0);

  glUseProgram(data_->shader->program());

  glBindBuffer(GL_ARRAY_BUFFER, data_->buffers[B_VERTICES]);
  glVertexAttribPointer(data_->posId, 3, GL_FLOAT, GL_FALSE, 0, NULL);

  glUniformMatrix4fv(data_->mvpId, 1, GL_FALSE, &mvp[0][0]);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, data_->buffers[B_INDICES]);
  glDrawElements(GL_TRIANGLES, 3 * 2 * 6, GL_UNSIGNED_INT, 0);

  glDisableVertexAttribArray(0);
}

}

