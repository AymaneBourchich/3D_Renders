#include "shader.h"
#include "utils.h"
#include <glm/gtc/type_ptr.hpp>
GLuint compileShader(GLenum type, const char *source)
{
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    GLint ok = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &ok);
    if (!ok)
    {
        char log[2048];
        glGetShaderInfoLog(shader, sizeof(log), nullptr, log);
        std::cerr << "Shader compile error:\n"
                  << log << "\n";
    }
    return shader;
}

GLuint createProgram(const char *vertPath, const char *fragPath, const char *geoPath)
{
    std::string v = loadFile(vertPath);
    std::string f = loadFile(fragPath);
    if (v.empty() || f.empty())
        return 0;

    GLuint vs = compileShader(GL_VERTEX_SHADER, v.c_str());
    GLuint fs = compileShader(GL_FRAGMENT_SHADER, f.c_str());

    GLuint gs = 0;
    if (geoPath && geoPath[0] != '\0') // if a geometry shader path is provided
    {
        std::string g = loadFile(geoPath);
        if (!g.empty())
            gs = compileShader(GL_GEOMETRY_SHADER, g.c_str());
        else
            std::cerr << "Failed to load geometry shader: " << geoPath << "\n";
    }

    GLuint prog = glCreateProgram();
    glAttachShader(prog, vs);
    glAttachShader(prog, fs);
    if (gs != 0)
        glAttachShader(prog, gs);

    glLinkProgram(prog);

    GLint ok = 0;
    glGetProgramiv(prog, GL_LINK_STATUS, &ok);
    if (!ok)
    {
        char log[2048];
        glGetProgramInfoLog(prog, sizeof(log), nullptr, log);
        std::cerr << "Program link error:\n"
                  << log << "\n";
    }

    glDeleteShader(vs);
    glDeleteShader(fs);
    if (gs != 0)
        glDeleteShader(gs);

    return prog;
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

void setValue(GLuint program, const char *name, float value)
{
    GLint loc = glGetUniformLocation(program, name);
    glUniform1f(loc, value);
}
