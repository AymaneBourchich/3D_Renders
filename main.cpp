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

static inline void setUpSimpleShader(GLuint program, glm::mat4 &view, glm::mat4 &proj, const glm::vec3 &color)
{
    setView(program, view);
    setProj(program, proj);
    setColor(program, color);
}

static inline void setUpTextureShader(GLuint program, glm::mat4 &view, glm::mat4 &proj,
                                      const glm::vec3 &color, float intensity)
{
    setValue(program, "uTex", 0);
    setView(program, view);
    setProj(program, proj);
    setAmbientColor(program, color, intensity);
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
    GLuint triPrismVAO = 0, triPrismVBO = 0, triPrismEBO = 0;
    setupVAO(triPrismVAO, triPrismVBO, triPrismEBO, Verts::TRI_PRISM_VERTS, Indices::TRI_PRISM_INDICES);

    GLuint texFloorVAO = 0, texFloorVBO = 0, texFloorEBO = 0;
    setupVAOTextured(texFloorVAO, texFloorVBO, texFloorEBO, Verts::FLOOR_VERTS, Indices::FLOOR_INDICES);

    GLuint cubeVAO, cubeVBO, cubeEBO;

    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &cubeVBO);
    glGenBuffers(1, &cubeEBO);

    glBindVertexArray(cubeVAO);

    // VBO
    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(Verts::CUBE_VERTS),
                 Verts::CUBE_VERTS,
                 GL_STATIC_DRAW);

    // EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 sizeof(Indices::CUBE_INDICES),
                 Indices::CUBE_INDICES,
                 GL_STATIC_DRAW);

    // position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
                          6 * sizeof(float),
                          (void *)0);
    glEnableVertexAttribArray(0);

    // normal
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
                          6 * sizeof(float),
                          (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    //-----------------------------------------------------------------------------------------------------------//

    GLuint cubeTex = loadTexture("textures/chess.jpg");
    GLuint floorTex = loadTexture("textures/hex-floor.jpg");
    GLuint robotTex = loadTexture("textures/circuit.jpg");

    GLuint simpleProgram = createProgram("shaders/simple.vert", "shaders/simple.frag");
    GLuint texProgram = createProgram("shaders/tex.vert", "shaders/tex.frag");
    GLuint lightProgram = createProgram("shaders/light.vert", "shaders/light.frag");
    GLuint diffuseProgram = createProgram("shaders/diffuse.vert", "shaders/diffuse.frag");
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
        setUpTextureShader(texProgram, view, proj, Color::WHITE, 0.3);
        setUpSimpleShader(simpleProgram, view, proj, Color::MAGENTA);

        setView(diffuseProgram, view);
        setProj(diffuseProgram, proj);
        setVec3(diffuseProgram, "uLightPos", glm::vec3(3.0f, 3.0f, 1.0f));
        setVec3(diffuseProgram, "uLightColor", glm::vec3(1.0f));
        setVec3(diffuseProgram, "uObjectColor", glm::vec3(1.0f, 0.5f, 0.2f));
        setValue(diffuseProgram, "uAmbient", 0.2f);

        //------------------------Main drawing loop----------------------------//
        glm::mat4 floor = initModel();
        scaleFully(floor, 100);
        drawMeshTextured(texProgram, texFloorVAO, floorTex, Counts::FLOOR_COUNT, floor);

        glm::mat4 cube = initModel();
        translate(cube, 0, 1, 0);
        drawMesh(diffuseProgram, cubeVAO, Counts::CUBE_COUNT, cube);

        // -------------------------------------------------------------//
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}
