#ifndef TEXTURE3D_H_JASS
#define TEXTURE3D_H_JASS

#include "Jass/Core/Core.h"
#include "ITexture.h"

namespace Jass {

	class JASS_API Texture3D : public ITexture {

	public:
		virtual ~Texture3D() = default;

		static Ref<Texture3D> Create(const std::vector<std::string>& filenames);
	};

}

#endif // !TEXTURE3D_H_JASS
