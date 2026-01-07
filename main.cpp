// main.cpp
#include "src/utils.h"
#include "src/shader.h"
#include "src/verts.h"
#include "src/camera.h"
#include "src/model.h"
#include "src/consts.h"
#include "src/vao.h"
#include "src/draw.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

static Camera gCam;
bool gKey[1024] = {false};

static int gFbW = 800;
static int gFbH = 600;

static void framebuffer_size_callback(GLFWwindow *, int w, int h)
{
    gFbW = (w > 0) ? w : 1;
    gFbH = (h > 0) ? h : 1;
    glViewport(0, 0, gFbW, gFbH);
}

static void key_callback(GLFWwindow *window, int key, int, int action, int)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);

    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
            gKey[key] = true;
        if (action == GLFW_RELEASE)
            gKey[key] = false;
    }
}

static void initOpenGL(GLFWwindow *window)
{
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
        throw std::runtime_error("GLEW init failed");

    glGetError();
    glEnable(GL_DEPTH_TEST);

    int w, h;
    glfwGetFramebufferSize(window, &w, &h);
    framebuffer_size_callback(window, w, h);
}

static float updateRotation(float speedDegPerSec, float dt, float &angleDeg)
{
    angleDeg += speedDegPerSec * dt;
    if (angleDeg > 360.0f)
        angleDeg -= 360.0f; // wrap around
    return angleDeg;
}

int main()
{
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWmonitor *monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode *mode = glfwGetVideoMode(monitor);
    GLFWwindow *window = glfwCreateWindow(
        mode->width,
        mode->height,
        "Single Cube",
        monitor, // fullscreen
        nullptr);

    if (!window)
        return -1;

    glfwWindowHint(GLFW_STENCIL_BITS, 8);
    initOpenGL(window);
    glEnable(GL_POLYGON_OFFSET_LINE);
    glPolygonOffset(-1.0f, -1.0f);
    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

    //----------------------

    GLuint quadVAO = 0, quadVBO = 0, quadEBO = 0;
    generateArraysIndexed(quadVAO, quadVBO, quadEBO);
    uploadVertsIndexed(quadVAO, quadVBO, quadEBO, Verts::QuadVerts, sizeof(Verts::QuadVerts), Indices::QuadIndices, Counts::QuadIndexCount);

    GLuint cubeVAO = 0, cubeVBO = 0, cubeEBO = 0;
    generateArraysIndexed(cubeVAO, cubeVBO, cubeEBO);
    uploadVertsIndexed(cubeVAO, cubeVBO, cubeEBO, Verts::CubeVerts, sizeof(Verts::CubeVerts), Indices::CubeIndices, Counts::CubeIndexCount);

    GLuint floorTex = loadTexture("floor.jpg");
    GLuint simpleProgram = createProgram("shaders/simple.vert", "shaders/simple.frag", "shaders/simple.geom");
    GLuint texProgram = createProgram("shaders/tex.vert", "shaders/tex.frag");
    GLuint geoProgram = createProgram("shaders/geo.vert", "shaders/geo.frag");
    double lastTime = glfwGetTime();

    //----------------------

    while (!glfwWindowShouldClose(window))
    {
        glfwWindowHint(GLFW_STENCIL_BITS, 8);

        double now = glfwGetTime();
        float dt = float(now - lastTime);
        lastTime = now;
        static float angle = 0.0f;

        angle = updateRotation(80.0f, dt, angle);

        glm::mat4 root = initModel();
        // rotate(root, 1.0f, 1.0f, 0.0f, angle);
        // rotate(root, 1.0f, 0.0f, 0.0f, angle);

        glfwPollEvents();
        updateCamera(gCam, dt, gKey);

        glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        glm::vec3 fwd = camForward(gCam);
        glm::mat4 view = glm::lookAt(gCam.pos, gCam.pos + fwd, glm::vec3(0, 1, 0));
        glm::mat4 proj = glm::perspective(glm::radians(60.0f), float(gFbW) / float(gFbH), 0.1f, 100.0f);

        glm::mat4 model = root;
        scaleFully(model, 2);
        drawMeshIndexedColored(simpleProgram, cubeVAO, Counts::CubeIndexCount, proj, view, model);


        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}
