#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>

std::string loadFile(const char *path);
GLuint loadTexture(const char *path);

static void setMat4(GLuint program, const char *name, const glm::mat4 &m);
static void setVec3(GLuint program, const char *name, const glm::vec3 &v);
void drawMesh(GLuint program, GLuint vao, int vertexCount, const glm::mat4 &proj, const glm::mat4 &view, const glm::mat4 &model, const glm::vec3 &color);
void drawMeshIndexedColored(GLuint program, GLuint vao, int indexCount, const glm::mat4 &proj, const glm::mat4 &view, const glm::mat4 &model);
void drawMeshIndexedTextured(GLuint program, GLuint vao, GLuint texture, int indexCount, const glm::mat4 &proj, const glm::mat4 &view, const glm::mat4 &model);