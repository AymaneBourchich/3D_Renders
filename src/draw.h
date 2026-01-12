#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>

void drawMesh(GLuint program, GLuint &vao, int indexCount, const glm::mat4 &proj, const glm::mat4 &view, const glm::mat4 &model, bool debug = false);
void drawMeshTextured(GLuint program, GLuint &vao, GLuint texture, int indexCount, const glm::mat4 &proj, const glm::mat4 &view, const glm::mat4 &model);