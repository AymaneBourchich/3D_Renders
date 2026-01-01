#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "model.h"
#include "utils.h"
void drawHead(GLuint program, GLuint vao, int vertexCount, const glm::mat4 &proj, glm::mat4 &view, glm::mat4 &model, const glm::vec3 &color)
{
    glUseProgram(program);
    translate(model, 0.0, 0.2, -1.0);
    scaleX(model, 3);
    scaleY(model, 2);
    drawMesh(program, vao, vertexCount, proj, view, model, color);
}

void drawRightEye(GLuint program, GLuint vao, int vertexCount, const glm::mat4 &proj, glm::mat4 &view, glm::mat4 &model, const glm::vec3 &color)
{
    glUseProgram(program);
    translate(model, 0, 0, -0.45);
    scaleFully(model, 2.0);
    drawMesh(program, vao, vertexCount, proj, view, model, color);
}
void drawLeftEye(GLuint program, GLuint vao, int vertexCount, const glm::mat4 &proj, glm::mat4 &view, glm::mat4 &model, const glm::vec3 &color)
{
    glUseProgram(program);
    translate(model, -0.1, 0, -0.45);
    rotate(model, 0, 1, 0, 180.0f);
    scaleFully(model, 2.0);
    drawMesh(program, vao, vertexCount, proj, view, model, color);
}
void drawFloor(GLuint program, GLuint vao, int vertexCount, const glm::mat4 &proj, glm::mat4 &view, glm::mat4 &model, const glm::vec3 &color)
{
    glUseProgram(program);
    translate(model, 0, -2, 0);
    scaleFully(model, 10);
    drawMesh(program, vao, vertexCount, proj, view, model, color);
}
void drawLaser(GLuint program, GLuint vao, int vertexCount, const glm::mat4 &proj, glm::mat4 &view, glm::mat4 &model, const glm::vec3 &color)
{
    glUseProgram(program);
    rotate(model, 1, 0, 0, 270);
    translate(model, 0, 3, 0);
    drawMesh(program, vao, 4, proj, view, model, Color::Red);
}

void drawScope(GLuint program, GLuint vao, int vertexCount, const glm::mat4 &proj, glm::mat4 &view, glm::mat4 &model, const glm::vec3 &color)
{
    glUseProgram(program);
    rotate(model, 1, 0, 0, 90);
    scaleFully(model, 2);
    drawMesh(program, vao, Verts::ScopeHexVertexCount, proj, view, model, color);
}
