#ifndef EARTH_TRIANGLE_H_
#define EARTH_TRIANGLE_H_

#include <glm/glm.hpp>

namespace e {

struct TriangleData;

class Triangle {
 public:
  Triangle();
  virtual ~Triangle();

  void Update();
  void Draw(glm::mat4 vp);

 private:
  TriangleData* data_;
};

}

#endif

