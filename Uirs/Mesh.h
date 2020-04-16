#pragma once
#include "VAO.h"
class Mesh {
	VBO vb;
	VAO va;

public:
	Mesh(float* data, unsigned size, VAO::Layout la) {
		vb = VBO(data, size);
		va = VAO();
		va.addLayout(la, vb);
	}

	void draw(Shader& shad, int count) {
		shad.bind();
		va.bind();
		glDrawArrays(GL_TRIANGLES, 0, count);
	}
};