#ifndef __M_IMG_H__
#define __M_IMG_H__

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "../_morisa.h"
#include "m_img.h"
#include "m_log.h"

MORISA_NAMESPACE_BEGIN

GLenum get_format(int channels)
{
	if (channels == 1)
		return GL_RED;
	else if (channels == 3)
		return GL_RGB;
	else if (channels == 4)
		return GL_RGBA;
	return GL_RGB;
}

unsigned m_load_img2D(const char* path, bool flip_verticlal = true)
{
	unsigned texture;
	glGenTextures(1, &texture);

	stbi_set_flip_vertically_on_load(flip_verticlal);
	int width, height, channels;
	unsigned char* data = stbi_load(path, &width, &height, &channels, 0);
	if (data)
	{
		GLenum format = get_format(channels);

		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
		return texture;
	}
	else
	{
		stbi_image_free(data);
#ifdef USE_LOG
		m_log("Failed to load texture!");
		m_log(path);
#endif 
		return 0;
	}
}

unsigned m_load_img3D(const char* paths[], const size_t N = 6, bool flip_verticlal = false)
{
	unsigned texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture);

	stbi_set_flip_vertically_on_load(flip_verticlal);
	int width, height, channels;
	for (int i = 0; i < N; i++)
	{
		unsigned char* data = stbi_load(paths[i], &width, &height, &channels, 0);
		if (data)
		{
			GLenum format = get_format(channels);
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
		}
		else
		{
			stbi_image_free(data);
#ifdef USE_LOG
			m_log("Failed to load texture!");
			m_log(paths[i]);
#endif 
		}
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	return texture;
}

MORISA_NAMESPACE_END
#endif
