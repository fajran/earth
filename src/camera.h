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

  void LookAt(glm::vec3 const eye,
              glm::vec3 const center,
              glm::vec3 const up);

 private:
  void UpdateMatrix();

  glm::mat4 const projection_;
  glm::mat4 view_;
  glm::mat4 matrix_;

  bool dirty_;
};

}

#endif

