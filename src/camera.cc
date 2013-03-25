#include "camera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace e {

Camera::Camera(glm::mat4 const projection)
    : projection_(projection),
      view_(glm::mat4(1.0f)),
      dirty_(true) {
}

Camera::~Camera() {
}

glm::mat4 Camera::Matrix() {
  if (dirty_) {
    UpdateMatrix();
    dirty_ = false;
  }
  return matrix_;
}

void Camera::LookAt(glm::vec3 const eye,
                    glm::vec3 const center,
                    glm::vec3 const up) {
  view_ = glm::lookAt(eye, center, up);
  dirty_ = true;
}

void Camera::UpdateMatrix() {
  matrix_ = projection_ * view_;
}

}

