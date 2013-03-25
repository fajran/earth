#include "camera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace e {

Camera::Camera() {
  matrix_ = glm::mat4(1.0f);
}

Camera::~Camera() {
}

glm::mat4 Camera::Matrix() {
  return matrix_;
}

void Camera::LookAt(glm::vec3 const eye,
                    glm::vec3 const center,
                    glm::vec3 const up) {
  matrix_ = glm::lookAt(eye, center, up);
}

}

