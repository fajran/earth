#include "earth.h"

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "shader.h"

namespace e {



// An array of 3 vectors which represents 3 vertices
static const GLfloat g_vertex_buffer_data[] = {
  -1.0f, -1.0f, 0.0f,
   1.0f, -1.0f, 0.0f,
   0.0f,  1.0f, 0.0f,
};

static GLuint vertexbuffer;
static GLuint posId;
static GLuint mvpId;

static glm::mat4 mvp;

static Shader* shader = NULL;

Earth::Earth() {
}

Earth::~Earth() {
  if (shader != NULL) {
    delete shader;
    shader = NULL;
  }
}

void Earth::Init() {
  // This will identify our vertex buffer

  // Generate 1 buffer, put the resulting identifier in vertexbuffer
  glGenBuffers(1, &vertexbuffer);

  // The following commands will talk about our 'vertexbuffer' buffer
  glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

  // Give our vertices to OpenGL.
  glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

  shader = new Shader("data/triangle.vs", "data/triangle.fs");
  shader->Load();
  posId = shader->GetAttribLocation("pos");
  mvpId = shader->GetUniformLocation("mvp");

  mvp = glm::mat4(1.0f);
}

void Earth::Update() {
}

void Earth::Render() {
  glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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

