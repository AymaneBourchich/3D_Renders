#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>

struct Camera
{
    glm::vec3 pos = glm::vec3(0.0f, 3.0f, 3.0f); // starting position
    float yawDeg = -100.0f;                      // points diagonally toward origin along -X/-Z
    float pitchDeg = -45.0f;                     // 45° downward
    float moveSpeed = 3.5f;                      // units per second
    float turnSpeed = 90.0f;                     // degrees per second
};

glm::vec3 camForward(const Camera &c);
void updateCamera(Camera &c, float dt, bool *gKey);