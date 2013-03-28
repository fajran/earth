#include "earth.h"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "shader.h"
#include "camera.h"
#include "triangle.h"
#include "cube.h"

namespace e {

static Camera camera(glm::perspective(45.0f, 4.0f/3.0f, 0.1f, 100.0f));

static Triangle* triangle = NULL;
static Cube* cube = NULL;

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

  camera.SetPosition(glm::vec3(0, 0, 10));
  camera.SetScale(glm::vec3(2, 2, 2));
  camera.SetRotation(glm::vec3(0, 0, 0));
}

void Earth::Update() {
  triangle->Update();
  cube->Update();
}

void Earth::Render() {
  glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  triangle->Draw(camera.Matrix());
  cube->Draw(camera.Matrix());
}

}

