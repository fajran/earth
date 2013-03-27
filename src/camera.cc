#include "camera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace e {

Camera::Camera(glm::mat4 const projection)
    : projection_(projection),
      view_(glm::mat4(1.0f)),
      position_(glm::vec3(0.0f, 0.0f, 0.0f)),
      rotation_(glm::mat4(1.0f)),
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

void Camera::SetRotation(glm::mat4 const rotation) {
  rotation_ = rotation;
  dirty_ = true;
};

void Camera::SetRotation(glm::vec3 const angles) {
  glm::mat4 rotation(1.0f);
  rotation = glm::rotate(rotation, angles.x, glm::vec3(1, 0, 0));
  rotation = glm::rotate(rotation, angles.y, glm::vec3(0, 1, 0));
  rotation = glm::rotate(rotation, angles.z, glm::vec3(0, 0, 1));

  rotation_ = rotation;
  dirty_ = true;
}

void Camera::SetScale(glm::vec3 const scale) {
  scale_ = scale;
  dirty_ = true;
}

void Camera::UpdateMatrix() {
  glm::mat4 scale_inv(1.0f / scale_.x, 0, 0, 0,
                      0, 1.0f / scale_.y, 0, 0,
                      0, 0, 1.0f / scale_.z, 0,
                      0, 0, 0, 1);
  glm::mat4 translation_inv(1, 0, 0, 0,
                            0, 1, 0, 0,
                            0, 0, 1, 0,
                            -position_.x, -position_.y, -position_.z, 1);
  glm::mat4 rotation_inv = glm::transpose(rotation_); // orthogonal matrix

  view_ = scale_inv * rotation_inv * translation_inv;
  matrix_ = projection_ * view_;
}

}

