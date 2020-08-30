#include "jasspch.h"
#include "ITexture.h"

namespace Jass {

	bool operator==(const ITexture& a, const ITexture& b)
	{
		return typeid(a) == typeid(b) && a.IsEqual(b);
	}

}
