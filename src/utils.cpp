#include "utils.h"

std::string loadFile(const char *path)
{
    std::ifstream file(path);
    if (!file)
    {
        std::cerr << "Failed to open file: " << path << "\n";
        return "";
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}
void setMat4(GLuint program, const char *name, const glm::mat4 &m)
{
    GLint loc = glGetUniformLocation(program, name);
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(m));
}

void setVec3(GLuint program, const char *name, const glm::vec3 &v)
{
    GLint loc = glGetUniformLocation(program, name);
    glUniform3f(loc, v.x, v.y, v.z);
}



void drawMesh(GLuint program, GLuint vao, int vertexCount,
              const glm::mat4& proj,
              const glm::mat4& view,
              const glm::mat4& model,
              const glm::vec3& color)
{
    glm::mat4 mvp = proj * view * model;
    setMat4(program, "uMVP", mvp);
    setVec3(program, "uColor", color);

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, vertexCount);
}