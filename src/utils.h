#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <GL/glew.h>

std::string loadFile(const char *path);
GLuint loadTexture(const char *path);