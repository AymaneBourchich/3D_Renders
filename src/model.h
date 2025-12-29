#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

glm::mat4 initModel();
void resetModel(glm::mat4 &model);
void translate(glm::mat4 &model, float x = 0, float y = 0, float z = 0);
void rotate(glm::mat4 &model, float x, float y, float z, float angle);
void scaleFully(glm::mat4 &model, float factor);
void scaleX(glm::mat4 &model, float factor);
void scaleY(glm::mat4 &model, float factor);
void scaleZ(glm::mat4 &model, float factor);
