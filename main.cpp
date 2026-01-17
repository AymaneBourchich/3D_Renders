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

    GLuint cubeVAO = 0, cubeVBO = 0, cubeEBO = 0;
    generateArrays(cubeVAO, cubeVBO, cubeEBO);
    uploadVerts(cubeVAO, cubeVBO, cubeEBO, Verts::CUBE_VERTS,
                sizeof(Verts::CUBE_VERTS), Indices::CUBE_INDICES, Counts::CUBE_COUNT);

    GLuint headVAO = 0, headVBO = 0, headEBO = 0;
    generateArrays(headVAO, headVBO, headEBO);
    uploadVerts(headVAO, headVBO, headEBO, Verts::HEAD_VERTS,
                sizeof(Verts::HEAD_VERTS), Indices::HEAD_INDICES, Counts::HEAD_COUNT);

    GLuint eyeVAO = 0, eyeVBO = 0, eyeEBO = 0;
    generateArrays(eyeVAO, eyeVBO, eyeEBO);
    uploadVerts(eyeVAO, eyeVBO, eyeEBO, Verts::EYE_VERTS,
                sizeof(Verts::EYE_VERTS), Indices::EYE_INDICES, Counts::EYE_COUNT);

    GLuint texCubeVAO = 0, texCubeVBO = 0, texCubeEBO = 0;
    generateArrays(texCubeVAO, texCubeVBO, texCubeEBO);
    uploadVertsTextured(texCubeVAO, texCubeVBO, texCubeEBO,
                        Verts::CUBE_VERTS_UV, sizeof(Verts::CUBE_VERTS_UV), Indices::CUBE_INDICES, Counts::CUBE_COUNT);

    GLuint texFaceVAO = 0, texFaceVBO = 0, texFaceEBO = 0;
    generateArrays(texFaceVAO, texFaceVBO, texFaceEBO);
    uploadVertsTextured(texFaceVAO, texFaceVBO, texFaceEBO,
                        Verts::FACE_VERTS, sizeof(Verts::FACE_VERTS), Indices::FACE_INDICES, Counts::FACE_COUNT);

    GLuint texFloorVAO = 0, texFloorVBO = 0, texFloorEBO = 0;
    generateArrays(texFloorVAO, texFloorVBO, texFloorEBO);
    uploadVertsTextured(texFloorVAO, texFloorVBO, texFloorEBO,
                        Verts::FLOOR_VERTS, sizeof(Verts::FLOOR_VERTS), Indices::FLOOR_INDICES, Counts::FLOOR_COUNT);
    //---------------- End VAO-VBO-EBO------------------//

    GLuint cubeTex = loadTexture("textures/chess.jpg");
    GLuint floorTex = loadTexture("textures/floor.jpg");
    GLuint robotTex = loadTexture("textures/circuit.jpg");

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

        glm::mat4 floor = initModel();
        scaleFully(floor, 100);
        drawMeshTextured(texProgram, texFloorVAO, floorTex, Counts::FACE_COUNT, proj, view, floor);

        glm::mat4 cube = initModel();
        translate(cube, 0, 0.5, 0);
        drawMesh(simpleProgram, cubeVAO, Counts::CUBE_COUNT, proj, view, cube);

        // ------End manual drawing loop--------------------//
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}
