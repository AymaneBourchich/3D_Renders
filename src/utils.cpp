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
GLuint loadTexture(const char* path)
{
    int w, h, channels;

    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(path, &w, &h, &channels, 0);
    if (!data)
        throw std::runtime_error("Failed to load texture");

    GLenum format = 0;
    GLenum internal = 0;

    if (channels == 4) {
        format   = GL_RGBA;
        internal = GL_RGBA8;
    }
    else if (channels == 3) {
        format   = GL_RGB;
        internal = GL_RGB8;
    }
    else if (channels == 2) {
        format   = GL_RG;
        internal = GL_RG8;
    }
    else if (channels == 1) {
        format   = GL_RED;
        internal = GL_R8;
    }
    else {
        stbi_image_free(data);
        throw std::runtime_error("Unsupported image format");
    }

    GLuint tex = 0;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        internal,
        w,
        h,
        0,
        format,
        GL_UNSIGNED_BYTE,
        data
    );

    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(data);
    glBindTexture(GL_TEXTURE_2D, 0);

    return tex;
}


