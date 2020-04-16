#pragma once
#include <GLFW/glew.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <string>

class Texture {
	unsigned id;

public:
	Texture(std::string loc) {
		int width, height,components;
		unsigned char* image = stbi_load(loc.c_str(), &width, &height, &components, STBI_rgb_alpha);
		if (image) {
			glGenTextures(1, &id);
			glBindTexture(GL_TEXTURE_2D, id);


			GLenum format;
			if (components == 1)
				format = GL_RED;
			else if (components == 3)
				format = GL_RGB;
			else if (components == 4)
				format = GL_RGBA;

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, image);
			glGenerateMipmap(GL_TEXTURE_2D);
			stbi_image_free(image);
		}
		else {
			std::cout << "error in TEXTURE LOADING" << std::endl;
		}
		
	}

	void bind(unsigned slot = 0) {
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, id);
	}
	void bind2(unsigned slot = 0) {
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, id);
	}
	void unBind(int slot) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
};