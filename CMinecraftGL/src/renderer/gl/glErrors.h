#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <exception>
#define DEBUG
#ifdef DEBUG
#define ASSERT(x) if (!(x)) throw std::runtime_error("OpenGL Error");
#define glCall(x) glClearLog(); x; ASSERT(glCatchError(__FUNCTION__, __FILE__, __LINE__, #x));
#else
#define ASSERT(x) if (!(x))
#define glCall(x) x
#endif
void glClearLog();
bool glCatchError(const char *function, const char *file, int lineno, const char *code);