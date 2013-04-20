attribute vec3 pos;
uniform mat4 mvp;

varying vec2 texcoord;

void main() {
  texcoord = vec2(pos.xy) + vec2(0.5, 0.5);
  gl_Position = mvp * vec4(pos, 1.0);
}

