#ifndef OPENGL_TEXTURE2D_H_JASS
#define OPENGL_TEXTURE2D_H_JASS

#include "Jass/Renderer/Textures/Texture2D.h"

namespace Jass {

	class OpenGLTexture2D : public Texture2D {

	public:
		OpenGLTexture2D(unsigned int width, unsigned int height);
		OpenGLTexture2D(const std::string& filepath);
		virtual ~OpenGLTexture2D();

		virtual unsigned int GetWidth() const override { return m_width; }
		virtual unsigned int GetHeight() const override { return m_height; }

		virtual void Bind(unsigned int slot = 0) const override;

		virtual void SetData(const void* data, unsigned int size) override;

	private:
		std::string m_filepath;
		unsigned int m_width = 0;
		unsigned int m_height = 0;
		unsigned int m_rendererID = 0;

		struct Formats {
			unsigned int InternalFormat = 0;
			unsigned int Format = 0;
		};

		Formats m_textureFormats;

		static Formats SelectFormats(unsigned int channels);
		static unsigned int GetBPP(const Formats& formats);

	};

}

#endif // !OPENGL_TEXTURE2D_H_JASS
