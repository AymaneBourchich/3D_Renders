// main.cpp
#include "src/utils.h"
#include "src/shader.h"
#include "src/verts.h"
#include "src/camera.h"
#include "src/model.h"
#include "src/consts.h"
#include "src/vao.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

// ------------------------------------------------------------
// Camera + input
// ------------------------------------------------------------
static Camera gCam;
bool gKey[1024] = {false};

static int gFbW = 800;
static int gFbH = 600;

void framebuffer_size_callback(GLFWwindow *, int w, int h)
{
    gFbW = (w > 0) ? w : 1;
    gFbH = (h > 0) ? h : 1;
    glViewport(0, 0, gFbW, gFbH);
}

void key_callback(GLFWwindow *window, int key, int, int action, int)
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

void initOpenGL(GLFWwindow *window)
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

    initOpenGL(window);
    glEnable(GL_POLYGON_OFFSET_LINE);
    glPolygonOffset(-1.0f, -1.0f);

    GLuint cubeVAO, cubeVBO;
    generateArrays(cubeVAO, cubeVBO);
    uploadVerts(cubeVAO, cubeVBO, Verts::Cube, sizeof(Verts::Cube));

    GLuint eyeVAO = 0, eyeVBO = 0;
    generateArrays(eyeVAO, eyeVBO);
    uploadVerts(eyeVAO, eyeVBO, Verts::Triangle, sizeof(Verts::Triangle));

    GLuint laserVAO = 0, laserVBO = 0;
    generateArrays(laserVAO, laserVBO);
    uploadVerts(laserVAO, laserVBO, Verts::laserQuad, sizeof(Verts::laserQuad));

    GLuint floorVAO = 0, floorVBO = 0;
    glGenVertexArrays(1, &floorVAO);
    glGenBuffers(1, &floorVBO);
    uploadVertsTextured(floorVAO, floorVBO, Verts::Floor, sizeof(Verts::Floor));
    GLuint floorTex = loadTexture("floor.jpg");

    GLuint texProgram = createProgram("shaders/tex.vert", "shaders/tex.frag");
    GLuint geoProgram = createProgram("shaders/geo.vert", "shaders/geo.frag");
    double lastTime = glfwGetTime();

    while (!glfwWindowShouldClose(window))
    {
        double now = glfwGetTime();
        float dt = float(now - lastTime);
        lastTime = now;

        glfwPollEvents();
        updateCamera(gCam, dt, gKey);

        glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::vec3 fwd = camForward(gCam);
        glm::mat4 view = glm::lookAt(gCam.pos, gCam.pos + fwd, glm::vec3(0, 1, 0));
        glm::mat4 proj = glm::perspective(glm::radians(60.0f), float(gFbW) / float(gFbH), 0.1f, 100.0f);
        glUseProgram(geoProgram);

        // glm::mat4 laser = initModel();
        // translate(laser, 0.0f, 0.0f, -2.0f);

        // drawMesh(
        //     geoProgram,
        //     laserVAO,
        //     4,
        //     proj,
        //     view,
        //     laser,
        //     Color::Red);

        float t = (float)now;

        const float rotSpeedDeg = 20.0f;
        float angleDeg = rotSpeedDeg * (float)now;
        glUseProgram(texProgram);

        glm::mat4 root = initModel();
        // translate(root, 0.0f, 0.0f, -1.0f);
        rotate(root, 0.0f, 1.0f, 0.0f, angleDeg); // rotate whole entity

        // glm::mat4 floor = root;
        // scaleFully(floor, 10);
        // drawMesh(texProgram, floorVAO, 6, proj, view, floor, Color::Red);
        glUseProgram(geoProgram);

        // glm::mat4 laser = initModel();

        glm::mat4 body = root;
        translate(body, 0, 0.2, -1);
        scaleX(body, 3);
        scaleY(body, 2);
        drawMesh(geoProgram, cubeVAO, Verts::CubeVertexCount, proj, view, body, Color::Black);

        glm::mat4 eye1 = root;
        translate(eye1, 0, 0, -0.45);
        scaleFully(eye1, 2.0);
        drawMesh(geoProgram, eyeVAO, Verts::TriangleVertexCount, proj, view, eye1, Color::Red);

        glm::mat4 eye2 = root;
        translate(eye2, -0.1, 0, -0.45);
        rotate(eye2, 0, 1, 0, 180.0f);
        scaleFully(eye2, 2.0);
        drawMesh(geoProgram, eyeVAO, Verts::TriangleVertexCount, proj, view, eye2, Color::Red);

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}
