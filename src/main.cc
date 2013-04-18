// Copyright (C) 2013  Fajran Iman Rusadi
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

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
  earth.Init();

  while (glfwGetWindowParam(GLFW_OPENED)
         && glfwGetKey(GLFW_KEY_ESC) != GLFW_PRESS) {

    earth.Update();
    earth.Render();
    glfwSwapBuffers();
  }

  return 0;
}

