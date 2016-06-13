#ifndef OPENGL_TUTORIAL_SHADER_H_
#define OPENGL_TUTORIAL_SHADER_H
#include "GL/glew.h"


// Load all shaders from their corresponding paths.
// Returns a GL pointer to a shader program.
GLuint CreateShaderProgram(const GLchar* vertexPath, const GLchar* fragmentPath);

#endif