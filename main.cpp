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

static inline void framebuffer_size_callback(GLFWwindow *, int w, int h)
{
    gFbW = (w > 0) ? w : 1;
    gFbH = (h > 0) ? h : 1;
    glViewport(0, 0, gFbW, gFbH);
}

static inline void key_callback(GLFWwindow *window, int key, int, int action, int)
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

static inline void initOpenGL(GLFWwindow *window)
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

static inline float updateRotation(float speedDegPerSec, float dt, float &angleDeg)
{
    angleDeg += speedDegPerSec * dt;
    if (angleDeg > 360.0f)
        angleDeg -= 360.0f; // wrap around
    return angleDeg;
}
static inline float getIntensity(double now)
{
    float glow = 0.5f + 0.5f * sinf(float(now) * 4.0f);
    return 0.5f + glow * 2.0f;
}

static inline void setUpTextureShader(GLuint program, glm::mat4 &view, glm::mat4 &proj)
{
    setValue(program, "uTex", 0);
    setView(program, view);
    setProj(program, proj);
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

    //------------------------------------------------------------------------------------------------------//

    GLuint cubeVAO = 0, cubeVBO = 0, cubeEBO = 0;
    setupVAO(cubeVAO, cubeVBO, cubeEBO, Verts::CUBE_VERTS, Indices::CUBE_INDICES);

    GLuint headVAO = 0, headVBO = 0, headEBO = 0;
    setupVAO(headVAO, headVBO, headEBO, Verts::HEAD_VERTS, Indices::HEAD_INDICES);

    GLuint eyeVAO = 0, eyeVBO = 0, eyeEBO = 0;
    setupVAO(headVAO, headVBO, headEBO, Verts::HEAD_VERTS, Indices::HEAD_INDICES);

    GLuint triPrismVAO = 0, triPrismVBO = 0, triPrismEBO = 0;
    setupVAO(triPrismVAO, triPrismVBO, triPrismEBO, Verts::TRI_PRISM_VERTS, Indices::TRI_PRISM_INDICES);

    GLuint texCubeVAO = 0, texCubeVBO = 0, texCubeEBO = 0;
    setupVAOTextured(texCubeVAO, texCubeVBO, texCubeEBO, Verts::CUBE_VERTS_UV, Indices::CUBE_INDICES);

    GLuint texFaceVAO = 0, texFaceVBO = 0, texFaceEBO = 0;
    setupVAOTextured(texFaceVAO, texFaceVBO, texFaceEBO, Verts::FACE_VERTS, Indices::FACE_INDICES);

    GLuint texFloorVAO = 0, texFloorVBO = 0, texFloorEBO = 0;
    setupVAOTextured(texFloorVAO, texFloorVBO, texFloorEBO, Verts::FLOOR_VERTS, Indices::FLOOR_INDICES);

    //-----------------------------------------------------------------------------------------------------------//

    GLuint cubeTex = loadTexture("textures/chess.jpg");
    GLuint floorTex = loadTexture("textures/floor.jpg");
    GLuint robotTex = loadTexture("textures/circuit.jpg");

    GLuint simpleProgram = createProgram("shaders/simple.vert", "shaders/simple.frag");
    GLuint texProgram = createProgram("shaders/tex.vert", "shaders/tex.frag");
    GLuint lightProgram = createProgram("shaders/light.vert", "shaders/light.frag");
    double lastTime = glfwGetTime();
    //-------------------------------------------------------------------------------------------------------------------//

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

        //-----------------------Shader setup----------------------------//
        setAmbientColor(texProgram, Color::RED, 0.3);
        setAmbientColor(lightProgram, Color::RED, getIntensity(now));
        setValue(texProgram, "uTex", 0);
        setView(texProgram, view);
        setProj(texProgram, proj);
        setView(simpleProgram, view);
        setProj(simpleProgram, proj);
        setView(lightProgram, view);
        setProj(lightProgram, proj);
        setColor(lightProgram, Color::WHITE);
        //------------------------Main drawing loop----------------------------//
        glm::mat4 floor = initModel();
        scaleFully(floor, 100);
        drawMeshTextured(texProgram, texFloorVAO, floorTex, Counts::FACE_COUNT, floor);

        glm::mat4 model = initModel();
        scaleX(model, 3);
        drawMesh(lightProgram, triPrismVAO, Counts::TRI_PRISM_COUNT, model);
        // -------------------------------------------------------------//
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}
