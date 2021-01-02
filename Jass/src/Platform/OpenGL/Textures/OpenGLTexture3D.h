#ifndef OPENGLTEXTURE3D_H_JASS
#define OPENGLTEXTURE3D_H_JASS

#include "Jass/Renderer/Textures/Texture3D.h"

namespace Jass {

	class OpenGLTexture3D : public Texture3D {

	public:
		OpenGLTexture3D(const std::vector<std::string>& filenames);
		virtual ~OpenGLTexture3D();


		virtual unsigned int GetWidth() const override { return m_width; }
		virtual unsigned int GetHeight() const override { return m_height; }

		virtual void Bind(unsigned int slot = 0) const override;

		virtual void SetData(const void* data, unsigned int size) override;

	protected:
		virtual bool IsEqual(const ITexture& other) const override;
	
	private:
		std::vector<std::string> m_filenames;

		unsigned int m_width = 0;
		unsigned int m_height = 0;
		unsigned int m_rendererID = 0;

		struct ImageData {
			unsigned char* Data;
			unsigned int Width;
			unsigned int Height;
			unsigned int Channels;
		};

		ImageData ProcessImage(const std::string& filename);
		void FreeImage(ImageData image);

		struct Formats {
			unsigned int InternalFormat = 0;
			unsigned int Format = 0;
		};

		static Formats SelectFormats(unsigned int channels);
		static unsigned int GetBPP(const Formats& formats);

	};

}

#endif // !OPENGLTEXTURE3D_H_JASS
