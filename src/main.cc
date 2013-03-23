#include <GL/glew.h>
#include <GL/glfw.h>

#include "earth.h"

static const int WINDOW_WIDTH = 640;
static const int WINDOW_HEIGHT = 480;

int main() {
  if (!glfwInit())
    return 1;
  if (!glfwOpenWindow(WINDOW_WIDTH, WINDOW_HEIGHT,
                      8, 8, 8, 0, 24, 0, GLFW_WINDOW))
    return 2;
  if (glewInit() != GLEW_OK)
    return 3;

  e::Earth earth;

  while (glfwGetWindowParam(GLFW_OPENED)
         && glfwGetKey(GLFW_KEY_ESC) != GLFW_PRESS) {

    earth.update();
    earth.render();
    glfwSwapBuffers();
  }

  return 0;
}

