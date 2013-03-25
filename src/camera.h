#ifndef EARTH_CAMERA_H_
#define EARTH_CAMERA_H_

#include <glm/glm.hpp>

namespace e {

class Camera {
 public:
  Camera();
  virtual ~Camera();

  glm::mat4 Matrix();

  void LookAt(glm::vec3 const eye,
              glm::vec3 const center,
              glm::vec3 const up);

 private:
  glm::mat4 matrix_;
};

}

#endif

