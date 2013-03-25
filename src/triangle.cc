#include "triangle.h"

#include <GL/glew.h>

#include "shader.h"

namespace e {

static const GLfloat g_vertex_buffer_data[] = {
  -1.0f, -1.0f, 0.0f,
   1.0f, -1.0f, 0.0f,
   0.0f,  1.0f, 0.0f,
};

static GLuint vertexbuffer = 0;
static GLuint posId;
static GLuint mvpId;

static Shader* shader = NULL;

static glm::mat4 model(1.0f);

static void Init() {
  glGenBuffers(1, &vertexbuffer);
  glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

  shader = new Shader("data/triangle.vs", "data/triangle.fs");
  shader->Load();
  posId = shader->GetAttribLocation("pos");
  mvpId = shader->GetUniformLocation("mvp");
}

Triangle::Triangle() {
}

Triangle::~Triangle() {
  if (shader != NULL) {
    delete shader;
    shader = NULL;
  }
}

void Triangle::Update() {
  if (vertexbuffer == 0) {
    Init();
  }
}

void Triangle::Draw(glm::mat4 vp) {
  glm::mat4 mvp = vp * model;

  // 1rst attribute buffer : vertices
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
  glVertexAttribPointer(
     posId,              // attribute 0. No particular reason for 0, but must match the layout in the shader.
     3,                  // size
     GL_FLOAT,           // type
     GL_FALSE,           // normalized?
     0,                  // stride
     (void*)0            // array buffer offset
  );
  glUniformMatrix4fv(mvpId, 1, GL_FALSE, &mvp[0][0]);

  glUseProgram(shader->program());

  // Draw the triangle !
  glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle

  glDisableVertexAttribArray(0);
}

}

