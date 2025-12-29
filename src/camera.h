#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>

struct Camera
{
    glm::vec3 pos = glm::vec3(0.0f, 1.8f, 4.0f);
    float yawDeg = -90.0f;   // -90 so forward initially points toward -Z
    float pitchDeg = -10.0f; // slight downward
    float moveSpeed = 3.5f;  // units per second
    float turnSpeed = 90.0f; // degrees per second
};

glm::vec3 camForward(const Camera &c);
void updateCamera(Camera &c, float dt, bool *gKey);