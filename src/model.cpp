#include "model.h"

glm::mat4 initModel()
{
    return glm::mat4(1.0f);
}
void resetModel(glm::mat4 &model)
{
    model = glm::mat4(1.0f);
}
void translate(glm::mat4 &model, float x, float y, float z)
{
    model = glm::translate(model, glm::vec3(x, y, z));
}
void rotate(glm::mat4 &model, float x, float y, float z, float angle)
{
    model = glm::rotate(model, glm::radians(angle), glm::vec3(x, y, z));
}
void scaleFully(glm::mat4 &model, float factor)
{
    model = glm::scale(model, glm::vec3(factor, factor, factor));
}
void scaleX(glm::mat4 &model, float factor)
{
    model = glm::scale(model, glm::vec3(factor, 1, 1));
}
void scaleY(glm::mat4 &model, float factor)
{
    model = glm::scale(model, glm::vec3(1, factor, 1));
}
void scaleZ(glm::mat4 &model, float factor)
{
    model = glm::scale(model, glm::vec3(1, 1, factor));
}
