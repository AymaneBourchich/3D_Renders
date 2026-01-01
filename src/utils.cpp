#include "utils.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
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
GLuint loadTexture(const char *path)
{
    int w, h, channels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(path, &w, &h, &channels, 0);
    if (!data)
        throw std::runtime_error("Failed to load texture");

    GLenum format = (channels == 4) ? GL_RGBA : (channels == 3) ? GL_RGB
                                                                : GL_RED;

    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);

    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        format,
        w, h,
        0,
        format,
        GL_UNSIGNED_BYTE,
        data);

    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(data);
    return tex;
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

void drawMesh(GLuint program, GLuint vao, int vertexCount, const glm::mat4 &proj, const glm::mat4 &view, const glm::mat4 &model, const glm::vec3 &color)
{
    glm::mat4 mvp = proj * view * model;
    setMat4(program, "uMVP", mvp);
    setVec3(program, "uColor", color);

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, vertexCount);
}
void drawMeshIndexedColored(GLuint program, GLuint vao, int indexCount, const glm::mat4 &proj, const glm::mat4 &view, const glm::mat4 &model)
{
    // Compute and send MVP
    glUseProgram(program);
    glm::mat4 mvp = proj * view * model;
    setMat4(program, "uMVP", mvp);

    // Bind VAO and draw using indices
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
