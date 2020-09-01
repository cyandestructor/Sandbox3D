#include "jasspch.h"
#include "SubTexture2D.h"

namespace Jass {

	SubTexture2D::SubTexture2D(const Ref<Texture2D>& texture, const JVec2& min, const JVec2& max) :
		m_texture(texture)
	{
		m_texCoords[0] = min;
		m_texCoords[1] = { max.x, min.y };
		m_texCoords[2] = max;
		m_texCoords[3] = { min.x, max.y };
	}

	Ref<SubTexture2D> SubTexture2D::Create(const Ref<Texture2D>& texture, const JVec2& offset, const JVec2& subtextureSize)
	{
		JVec2 min = { offset.x / texture->GetWidth(), offset.y / texture->GetHeight() };
		JVec2 max = { (offset.x + subtextureSize.x) / texture->GetWidth(), (offset.y + subtextureSize.y) / texture->GetHeight() };

		return MakeRef<SubTexture2D>(texture, min, max);
	}

}

