#include "earth.h"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "shader.h"
#include "camera.h"
#include "triangle.h"

namespace e {

static Camera camera(glm::perspective(45.0f, 4.0f/3.0f, 0.1f, 100.0f));

static Triangle* triangle = NULL;

Earth::Earth() {
}

Earth::~Earth() {
  if (triangle != NULL) {
    delete triangle;
  }
}

void Earth::Init() {
  triangle = new Triangle();
  camera.LookAt(glm::vec3(4, 3, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
}

void Earth::Update() {
  triangle->Update();
}

void Earth::Render() {
  glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  triangle->Draw(camera.Matrix());
}

}

