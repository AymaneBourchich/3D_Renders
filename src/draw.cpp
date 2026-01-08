#include "draw.h"

static void setMat4(GLuint program, const char *name, const glm::mat4 &m)
{
    GLint loc = glGetUniformLocation(program, name);
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(m));
}

static void setVec3(GLuint program, const char *name, const glm::vec3 &v)
{
    GLint loc = glGetUniformLocation(program, name);
    glUniform3f(loc, v.x, v.y, v.z);
}

void drawMesh(GLuint program, GLuint& vao, int indexCount, const glm::mat4 &proj, const glm::mat4 &view, const glm::mat4 &model)
{
    glUseProgram(program);
    glm::mat4 mvp = proj * view * model;
    setMat4(program, "uMVP", mvp);

    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void drawMeshTextured(GLuint program, GLuint& vao, GLuint texture, int indexCount, const glm::mat4 &proj, const glm::mat4 &view, const glm::mat4 &model)
{
    glUseProgram(program);

    glm::mat4 mvp = proj * view * model;
    setMat4(program, "uMVP", mvp);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glUniform1i(glGetUniformLocation(program, "uTex"), 0);

    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    glBindTexture(GL_TEXTURE_2D, 0);
}
