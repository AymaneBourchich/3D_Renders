#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>

static void setMat4(GLuint program, const char *name, const glm::mat4 &m);
static void setVec3(GLuint program, const char *name, const glm::vec3 &v);
void drawMesh(GLuint program, GLuint& vao, int indexCount, const glm::mat4 &proj, const glm::mat4 &view, const glm::mat4 &model);
void drawMeshTextured(GLuint program, GLuint& vao, GLuint texture, int indexCount, const glm::mat4 &proj, const glm::mat4 &view, const glm::mat4 &model);