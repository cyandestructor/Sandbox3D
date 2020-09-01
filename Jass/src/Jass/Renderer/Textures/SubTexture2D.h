#ifndef SUBTEXTURE2D_H_JASS
#define SUBTEXTURE2D_H_JASS

#include "Texture2D.h"
#include "Jass/JMath/JMath.h"

namespace Jass {

	class JASS_API SubTexture2D {

	public:
		SubTexture2D(const Ref<Texture2D>& texture, const JVec2& min, const JVec2& max);

		const Ref<Texture2D>& GetTexture() const { return m_texture; }
		const std::array<JVec2, 4>& GetTextureCoords() const { return m_texCoords; }

		static Ref<SubTexture2D> Create(const Ref<Texture2D>& texture, const JVec2& offset, const JVec2& subtextureSize);

	private:
		Ref<Texture2D> m_texture;
		std::array<JVec2, 4> m_texCoords;

	};

}

#endif // !SUBTEXTURE2D_H_JASS
