#include "jasspch.h"
#include "OpenGLTexture3D.h"

#include "stb_image.h"

#include <glad/glad.h>

namespace Jass {

	OpenGLTexture3D::OpenGLTexture3D(const std::vector<std::string>& filenames)
	{
		JASS_CORE_ASSERT(filenames.size() <= 6, "Maximum number of textures is six");
		
		glGenTextures(1, &m_rendererID);
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_rendererID);

		for (size_t i = 0; i < filenames.size(); i++)
		{
			auto imageData = ProcessImage(filenames[i]);

			if (imageData.Data)
			{
				glTexImage2D(
					GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
					0, GL_RGB, imageData.Width, imageData.Height, 0,
					GL_RGB, GL_UNSIGNED_BYTE, imageData.Data
				);
			}
			else
			{
				JASS_CORE_WARN("Failed to load the image with filepath: {0}", filenames[i]);
			}
		}

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	}

	OpenGLTexture3D::~OpenGLTexture3D()
	{
		glDeleteTextures(1, &m_rendererID);
	}

	void OpenGLTexture3D::Bind(unsigned int slot) const
	{
		JASS_PROFILE_FUNCTION();

		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_rendererID);
	}

	void OpenGLTexture3D::SetData(const void* data, unsigned int size)
	{
	}

	bool OpenGLTexture3D::IsEqual(const ITexture& other) const
	{
		auto& otherTexture = static_cast<const OpenGLTexture3D&>(other);
		return this->m_rendererID == otherTexture.m_rendererID;
	}

	OpenGLTexture3D::ImageData OpenGLTexture3D::ProcessImage(const std::string& filename)
	{
		int width, height, channels;
		stbi_uc* data = nullptr;
		// Load the image in the way OpenGL expects
		{
			JASS_PROFILE_SCOPE("stbi Load");
			stbi_set_flip_vertically_on_load(1);
			data = stbi_load(filename.c_str(), &width, &height, &channels, 0);
		}

		return { data, (unsigned int)width, (unsigned int)height, (unsigned int)channels };
	}

}