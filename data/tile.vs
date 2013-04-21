attribute vec3 pos;
uniform mat4 mvp;

varying vec2 texcoord;

void main() {
  texcoord = pos.xy;
  gl_Position = mvp * vec4(pos, 1.0);
}

