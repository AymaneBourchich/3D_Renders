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

    glTexImage2D(GL_TEXTURE_2D, 0, format, w, h, 0, format, GL_UNSIGNED_BYTE, data);

    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(data);
    return tex;
}

