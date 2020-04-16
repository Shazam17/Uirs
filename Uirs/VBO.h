#pragma once
#include <GLFW/glew.h>

class VBO {
	unsigned id;

public:
	VBO() {
		id = -1;
	}
	VBO(float* data, unsigned size) {
		glCreateBuffers(1, &id);
		glBindBuffer(GL_ARRAY_BUFFER, id);
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	}

	void bind() {
		glBindBuffer(GL_ARRAY_BUFFER, id);
	}
	void unBind() {
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
};