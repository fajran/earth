#version 330 core

attribute vec3 pos;
uniform mat4 mvp;

void main() {
  gl_Position = mvp * vec4(pos, 1.0);
}

