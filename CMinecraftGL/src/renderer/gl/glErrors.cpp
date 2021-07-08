#include "glErrors.h"



void glClearLog() {
	while (glGetError() != GL_NO_ERROR);
}

bool glCatchError(const char *function, const char *file, int lineno, const char *code){
	while (GLenum error = glGetError()) {
		std::cout << "[OpenGL Error Traceback] OpenGL Error at file " << file << ", line " << lineno << ", in " 
			<< function << "\n" << code << "\n" << "Error " << error << std::endl;
		return false;
	}
	return true;
}