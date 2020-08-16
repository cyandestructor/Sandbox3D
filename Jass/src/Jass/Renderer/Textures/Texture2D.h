#ifndef TEXTURE2D_H_JASS
#define TEXTURE2D_H_JASS

#include <string>

#include "Jass/Core/Core.h"
#include "ITexture.h"

namespace Jass {

	class JASS_API Texture2D : public ITexture {

	public:
		virtual ~Texture2D() = default;

		static Ref<Texture2D> Create(const std::string& filepath);

	};

}

#endif // !TEXTURE2D_H_JASS