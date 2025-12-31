#include "camera.h"

glm::vec3 camForward(const Camera &c)
{
    float yaw = glm::radians(c.yawDeg);
    float pitch = glm::radians(c.pitchDeg);

    glm::vec3 f;
    f.x = cosf(yaw) * cosf(pitch);
    f.y = sinf(pitch);
    f.z = sinf(yaw) * cosf(pitch);
    return glm::normalize(f);
}

void updateCamera(Camera &c, float dt, bool *gKey)
{
    glm::vec3 fwd = camForward(c);
    glm::vec3 right = glm::normalize(glm::cross(fwd, glm::vec3(0.0f, 1.0f, 0.0f)));
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

    float v = c.moveSpeed * dt;

    // Movement (WASD on XZ plane relative to camera facing)
    if (gKey[GLFW_KEY_W])
        c.pos += fwd * v;
    if (gKey[GLFW_KEY_S])
        c.pos -= fwd * v;
    if (gKey[GLFW_KEY_A])
        c.pos -= right * v;
    if (gKey[GLFW_KEY_D])
        c.pos += right * v;

    // Vertical movement (R/F)
    if (gKey[GLFW_KEY_R])
        c.pos += up * v;
    if (gKey[GLFW_KEY_F])
        c.pos -= up * v;

    // Look around with arrow keys (simple, predictable)
    float ang = c.turnSpeed * dt;
    if (gKey[GLFW_KEY_LEFT])
        c.yawDeg -= ang;
    if (gKey[GLFW_KEY_RIGHT])
        c.yawDeg += ang;
    if (gKey[GLFW_KEY_UP])
        c.pitchDeg += ang;
    if (gKey[GLFW_KEY_DOWN])
        c.pitchDeg -= ang;

    // Clamp pitch to avoid flipping
    if (c.pitchDeg > 89.0f)
        c.pitchDeg = 89.0f;
    if (c.pitchDeg < -89.0f)
        c.pitchDeg = -89.0f;

    // Speed modifiers
    if (gKey[GLFW_KEY_LEFT_SHIFT])
        c.moveSpeed = 8.0f;
    else
        c.moveSpeed = 3.5f;
}