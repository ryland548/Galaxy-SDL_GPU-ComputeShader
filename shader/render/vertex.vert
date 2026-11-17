#version 450

struct Particle {
    vec3 position;
    vec4 color;
    float size;
};

layout(set = 0, binding = 0) readonly buffer ParticleBuffer {
    Particle particles[];
};

layout(set = 1, binding = 0) uniform PushConstants {
    mat4 camMatrix;
    vec3 camRight;
    vec3 camUp;
} pushConstants;

vec3 vertices[6] = vec3[](
    vec3(-0.08, -0.08, 0.0),
    vec3(-0.08,  0.08, 0.0),
    vec3( 0.08,  0.08, 0.0),
    vec3(-0.08, -0.08, 0.0),
    vec3( 0.08,  0.08, 0.0),
    vec3( 0.08, -0.08, 0.0)
);

layout(location = 0) out vec4 outColor;

void main() {
    uint index = gl_VertexIndex / 6;
    uint vertexIndex = gl_VertexIndex % 6;

    Particle particle = particles[index];
    vec3 corner = vertices[vertexIndex];

    vec3 worldPos = particle.position + (pushConstants.camRight * corner.x * particle.size) + (pushConstants.camUp * corner.y * particle.size);
    gl_Position = pushConstants.camMatrix * vec4(worldPos, 1.0);

    outColor = particle.color;
}
