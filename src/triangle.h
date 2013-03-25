#ifndef EARTH_TRIANGLE_H_
#define EARTH_TRIANGLE_H_

#include <glm/glm.hpp>

namespace e {

class Triangle {
 public:
  Triangle();
  virtual ~Triangle();

  void Update();
  void Draw(glm::mat4 vp);
};

}

#endif

