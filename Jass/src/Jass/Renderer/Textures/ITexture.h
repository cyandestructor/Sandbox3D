#ifndef ITEXTURE_H_JASS
#define ITEXTURE_H_JASS

namespace Jass {

	class ITexture {

		friend bool operator==(const ITexture& a, const ITexture& b);

	public:
		virtual ~ITexture() = default;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		virtual void Bind(unsigned int slot = 0) const = 0;
		
		virtual void SetData(const void* data, unsigned int size) = 0;
	protected:
		virtual bool IsEqual(const ITexture& other) const = 0;

	};

}

#endif // !ITEXTURE_H_JASS
