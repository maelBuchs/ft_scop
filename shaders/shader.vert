#version 450

layout(binding = 0) uniform UniformBufferObject {
  mat4 model;
  mat4 view;
  mat4 proj;
}
ubo;

layout(location = 0) in vec3 inPosition; // <-- vec3 au lieu de vec2
layout(location = 1) in vec3 inColor;

layout(location = 0) out vec3 fragColor;

out gl_PerVertex { vec4 gl_Position; };

void main() {
  gl_Position = ubo.proj * ubo.view * ubo.model *
                vec4(inPosition, 1.0); // <-- vec4 avec w=1.0
  fragColor = inColor;
}
