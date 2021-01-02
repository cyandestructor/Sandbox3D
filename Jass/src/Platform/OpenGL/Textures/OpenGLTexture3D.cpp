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

		for (unsigned int i = 0; i < filenames.size(); i++)
		{
			auto imageData = ProcessImage(filenames[i]);
			auto textureFormats = OpenGLTexture3D::SelectFormats(imageData.Channels);

			if (imageData.Data)
			{
				glTexImage2D(
					GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
					0, textureFormats.InternalFormat, imageData.Width, imageData.Height, 0,
					textureFormats.Format, GL_UNSIGNED_BYTE, imageData.Data
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

	void OpenGLTexture3D::FreeImage(ImageData image)
	{
		stbi_image_free(image.Data);
	}

	OpenGLTexture3D::Formats OpenGLTexture3D::SelectFormats(unsigned int channels)
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

	unsigned int OpenGLTexture3D::GetBPP(const Formats& formats)
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