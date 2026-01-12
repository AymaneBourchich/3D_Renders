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
    GLFWwindow *window = glfwCreateWindow(mode->width, mode->height, "Single Cube", monitor, nullptr);
    if (!window)
        return -1;

    initOpenGL(window);

    glEnable(GL_POLYGON_OFFSET_LINE);
    glPolygonOffset(-1.0f, -1.0f);

    //---------------- Begin VAO-VBO-EBO------------------//

    GLuint quadVAO = 0, quadVBO = 0, quadEBO = 0;
    generateArrays(quadVAO, quadVBO, quadEBO);
    uploadVerts(quadVAO, quadVBO, quadEBO, Verts::QuadVerts, sizeof(Verts::QuadVerts), Indices::QuadIndices, Counts::QuadIndexCount);

    GLuint cubeVAO = 0, cubeVBO = 0, cubeEBO = 0;
    generateArrays(cubeVAO, cubeVBO, cubeEBO);
    uploadVerts(cubeVAO, cubeVBO, cubeEBO, Verts::CubeVerts, sizeof(Verts::CubeVerts), Indices::CubeIndices, Counts::CubeIndexCount);

    GLuint faceVAO = 0, faceVBO = 0, faceEBO = 0;
    generateArrays(faceVAO, faceVBO, faceEBO);
    uploadVerts(faceVAO, faceVBO, faceEBO, Verts::HeadVerts, sizeof(Verts::HeadVerts), Indices::HeadIndices, Counts::HeadCount);

    GLuint texQuadVAO = 0, texQuadVBO = 0, texQuadEBO = 0;
    generateArrays(texQuadVAO, texQuadVBO, texQuadEBO);
    uploadVertsTextured(texQuadVAO, texQuadVBO, texQuadEBO, Verts::CubeVertsUV, sizeof(Verts::QuadVertsUV), Indices::QuadIndices, Counts::QuadIndexCount);

    GLuint texCubeVAO = 0, texCubeVBO = 0, texCubeEBO = 0;
    generateArrays(texCubeVAO, texCubeVBO, texCubeEBO);
    uploadVertsTextured(texCubeVAO, texCubeVBO, texCubeEBO, Verts::CubeVertsUV, sizeof(Verts::CubeVertsUV), Indices::CubeIndices, Counts::CubeIndexCount);

    //---------------- End VAO-VBO-EBO------------------//

    GLuint cubeTex = loadTexture("textures/chess.jpg");
    GLuint floorTex = loadTexture("textures/floor.jpg");

    GLuint simpleProgram = createProgram("shaders/simple.vert", "shaders/simple.frag");
    GLuint texProgram = createProgram("shaders/tex.vert", "shaders/tex.frag");
    double lastTime = glfwGetTime();
    //---------------- End VAO-VBO-EBO------------------//

    //----------------------

    while (!glfwWindowShouldClose(window))
    {
        glfwWindowHint(GLFW_STENCIL_BITS, 8);

        double now = glfwGetTime();
        float dt = float(now - lastTime);
        lastTime = now;
        static float angle = 0.0f;

        angle = updateRotation(30.0f, dt, angle);

        glm::mat4 root = initModel();
        translate(root, 0, 3, 0);
        rotate(root, 1.0f, 1.0f, 0.0f, angle);

        glfwPollEvents();
        updateCamera(gCam, dt, gKey);

        glClearColor(0.5f, 0.5f, 0.5f, 0.7);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        glm::vec3 fwd = camForward(gCam);
        glm::mat4 view = glm::lookAt(gCam.pos, gCam.pos + fwd, glm::vec3(0, 1, 0));
        glm::mat4 proj = glm::perspective(glm::radians(60.0f), float(gFbW) / float(gFbH), 0.1f, 100.0f);

        //------Begin Manual drawing loop--------------------//

        glm::mat4 model = initModel();
        drawMesh(simpleProgram, faceVAO, Counts::HeadCount, proj, view, model, true);

        // ------End manual drawing loop--------------------//
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}
