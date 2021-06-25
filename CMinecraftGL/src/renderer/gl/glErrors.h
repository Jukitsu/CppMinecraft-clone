#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>
#include <iostream>
#define DEBUG
#ifdef DEBUG
#define ASSERT(x) if (!(x)) __debugbreak();
#else
#define ASSERT(x) if (!(x));
#endif
#define glCall(x) glClearLog(); x; ASSERT(glCatchError(__FUNCTION__, __FILE__, __LINE__, #x));

void glClearLog();
bool glCatchError(const char* function, const char* file, int lineno, const char* code);