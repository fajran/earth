attribute vec3 pos;
attribute vec4 color;
uniform mat4 mvp;

varying vec4 vcolor;

void main() {
  gl_Position = mvp * vec4(pos, 1.0);
  vcolor = color;
}

