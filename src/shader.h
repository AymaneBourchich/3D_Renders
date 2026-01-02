#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

GLuint compileShader(GLenum type, const char* source);
GLuint createProgram(const char* vertPath, const char* fragPath, const char* geoPath = "");