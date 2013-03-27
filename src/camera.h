#ifndef EARTH_CAMERA_H_
#define EARTH_CAMERA_H_

#include <glm/glm.hpp>

namespace e {

class Camera {
 public:
  Camera(glm::mat4 const projection);
  virtual ~Camera();

  glm::mat4 projection() const { return projection_; }
  glm::mat4 view() const { return view_; }

  glm::mat4 Matrix();

  void SetPosition(glm::vec3 const position);
  void SetRotation(glm::mat4 const rotation);
  void SetRotation(glm::vec3 const angles);
  void SetScale(glm::vec3 const scale);

 private:
  void UpdateMatrix();

  glm::mat4 const projection_;
  glm::mat4 view_;
  glm::mat4 matrix_;
  glm::mat4 camera_matrix_;

  glm::vec3 position_;
  glm::mat4 rotation_;
  glm::vec3 scale_;

  bool dirty_;
};

}

#endif

