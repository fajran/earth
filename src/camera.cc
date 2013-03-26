#include "camera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace e {

Camera::Camera(glm::mat4 const projection)
    : projection_(projection),
      view_(glm::mat4(1.0f)),
      position_(glm::vec3(0.0f, 0.0f, 0.0f)),
      rotation_(glm::vec3(0.0f, 0.0f, 0.0f)),
      scale_(glm::vec3(1.0f, 1.0f, 1.0f)),
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

void Camera::SetPosition(glm::vec3 const position) {
  position_ = position;
  dirty_ = true;
}

void Camera::SetRotation(glm::vec3 const rotation) {
  rotation_ = rotation;
  dirty_ = true;
}

void Camera::SetScale(glm::vec3 const scale) {
  scale_ = scale;
  dirty_ = true;
}

void Camera::UpdateMatrix() {
  glm::mat4 scale = glm::scale(glm::mat4(1.0f), scale_);
  glm::mat4 translation = glm::translate(glm::mat4(1.0f), position_);
  glm::mat4 rotation(1.0f);
  rotation = glm::rotate(rotation, rotation_.x, glm::vec3(1, 0, 0));
  rotation = glm::rotate(rotation, rotation_.y, glm::vec3(0, 1, 0));
  rotation = glm::rotate(rotation, rotation_.z, glm::vec3(0, 0, 1));

  camera_matrix_ = translation * rotation * scale;

  // TODO optimize the inverse
  view_ = glm::inverse(camera_matrix_);

  matrix_ = projection_ * view_;
}

}

