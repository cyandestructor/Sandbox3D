#include "jasspch.h"
#include "OpenGLTexture2D.h"

#include "stb_image.h"

#include <glad/glad.h>

namespace Jass {

	OpenGLTexture2D::OpenGLTexture2D(const std::string& filepath) :
		m_filepath(filepath)
	{
		int width, height, channels;
		// Load the image in the way OpenGL expects
		stbi_set_flip_vertically_on_load(1);
		stbi_uc* data = stbi_load(filepath.c_str(), &width, &height, &channels, 0);

		if (data) {
			m_width = (unsigned int)width;
			m_height = (unsigned int)height;

			glCreateTextures(GL_TEXTURE_2D, 1, &m_rendererID);
			glTextureStorage2D(m_rendererID, 1, GL_RGB8, m_width, m_height);

			glTextureParameteri(m_rendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTextureParameteri(m_rendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

			glTextureSubImage2D(m_rendererID, 0, 0, 0, m_width, m_height, GL_RGB, GL_UNSIGNED_BYTE, data);

			stbi_image_free(data);
		}
		else {
			JASS_CORE_WARN("Failed to load the image with filepath: {0}", filepath);
		}
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_rendererID);
	}

	void OpenGLTexture2D::Bind(unsigned int slot /*= 0*/) const
	{
		glBindTextureUnit(slot, m_rendererID);
	}

}
