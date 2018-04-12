#version 400 core

layout(location = 0) in vec3 quadVertices;
layout(location = 1) in vec4 position;
layout(location = 2) in vec4 color;
out vec2 uv;
out vec4 particleColor;

// Transformation matrices
uniform mat4 p;
uniform mat4 v;
uniform mat4 particleScale;
uniform mat4 particlePosition;

void main() {
    uv = quadVertices.xy;
    float size = position.w;
    particleColor = color/255.f;
    vec4 vertexPosition = p*v*vec4(quadVertices, 1)*size;
    vec4 center = position;
    // vec4 center = p*v*particlePosition*position * 50.f;
    //vec4 vertexPosition = particleScale*v*p*vec4(quadVertices, 1);
    //vec4 center = particlePosition*v*p*position * 5.f;
    gl_Position = p*v*vec4(vertexPosition.xyz + center.xyz, 1.0);
}
