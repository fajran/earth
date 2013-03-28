#ifndef EARTH_CUBE_H_
#define EARTH_CUBE_H_

#include <glm/glm.hpp>

namespace e {

struct CubeData;

class Cube {
 public:
  Cube();
  virtual ~Cube();

  void Update();
  void Draw(glm::mat4 vp);

 private:
  CubeData* data_;
};

}

#endif

