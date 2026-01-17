#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "consts.h"
#include <iostream>

GLuint compileShader(GLenum type, const char* source);
GLuint createProgram(const char* vertPath, const char* fragPath, const char* geoPath = "");
void setMat4(GLuint program, const char *name, const glm::mat4 &m);
void setVec3(GLuint program, const char *name, const glm::vec3 &v);
void setValue(GLuint program, const char *name, float value); 
void setMVP(GLuint program, const glm::mat4 &model, const glm::mat4 &view, const glm::mat4 &proj);
void setAmbientColor(GLuint program, const glm::vec3 &color, float intensity);