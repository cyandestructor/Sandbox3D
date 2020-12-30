#include "jasspch.h"
#include "OpenGLTexture2D.h"

#include "stb_image.h"

#include <glad/glad.h>

namespace Jass {

	OpenGLTexture2D::OpenGLTexture2D(unsigned int width, unsigned int height) :
		m_width(width), m_height(height)
	{
		JASS_PROFILE_FUNCTION();

		m_textureFormats.InternalFormat = GL_RGBA8;
		m_textureFormats.Format = GL_RGBA;
		
		glCreateTextures(GL_TEXTURE_2D, 1, &m_rendererID);
		glTextureStorage2D(m_rendererID, 1, m_textureFormats.InternalFormat, m_width, m_height);

		glTextureParameteri(m_rendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_rendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}

	OpenGLTexture2D::OpenGLTexture2D(const std::string& filepath) :
		m_filepath(filepath)
	{
		JASS_PROFILE_FUNCTION();

		int width, height, channels;
		stbi_uc* data = nullptr;
		// Load the image in the way OpenGL expects
		{
			JASS_PROFILE_SCOPE("stbi Load");
			stbi_set_flip_vertically_on_load(1);
			data = stbi_load(filepath.c_str(), &width, &height, &channels, 0);
		}

		if (data) {
			m_width = (unsigned int)width;
			m_height = (unsigned int)height;

			m_textureFormats = OpenGLTexture2D::SelectFormats(channels);

			glCreateTextures(GL_TEXTURE_2D, 1, &m_rendererID);
			glTextureStorage2D(m_rendererID, 1, m_textureFormats.InternalFormat, m_width, m_height);

			glTextureParameteri(m_rendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTextureParameteri(m_rendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			glTextureSubImage2D(m_rendererID, 0, 0, 0, m_width, m_height, m_textureFormats.Format, GL_UNSIGNED_BYTE, data);

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
		JASS_PROFILE_FUNCTION();

		glBindTextureUnit(slot, m_rendererID);
	}

	void OpenGLTexture2D::SetData(const void* data, unsigned int size)
	{
		JASS_CORE_ASSERT(size == m_width * m_height * GetBPP(m_textureFormats),
			"Data size do not match with the texture properties");

		glTextureSubImage2D(m_rendererID, 0, 0, 0, m_width, m_height,
			m_textureFormats.Format, GL_UNSIGNED_BYTE, data);
	}

	bool OpenGLTexture2D::IsEqual(const ITexture& other) const
	{
		auto& otherTexture = static_cast<const OpenGLTexture2D&>(other);
		return this->m_rendererID == otherTexture.m_rendererID;
	}

	OpenGLTexture2D::Formats OpenGLTexture2D::SelectFormats(unsigned int channels)
	{
		Formats formats;

		switch (channels)
		{
			case 3:
				formats.InternalFormat = GL_RGB8;
				formats.Format = GL_RGB;
				break;
			case 4:
				formats.InternalFormat = GL_RGBA8;
				formats.Format = GL_RGBA;
				break;
			default:
				JASS_CORE_ASSERT(false, "Unsupported number of channels");
				break;
		}

		JASS_CORE_ASSERT(formats.InternalFormat && formats.Format, "Format could not be specified");

		return formats;
	}

	unsigned int OpenGLTexture2D::GetBPP(const Formats& formats)
	{
		switch (formats.Format)
		{
			case GL_RGB:
				return 3;
			case GL_RGBA:
				return 4;
		}

		JASS_CORE_ASSERT(false, "Unknow data format");
		return 0;
	}

}
