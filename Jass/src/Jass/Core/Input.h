#ifndef JASS_INPUT_H
#define JASS_INPUT_H

#include "Core.h"

namespace Jass {

	enum class CursorMode
	{
		Normal, Hidden, Disabled
	};

	class JASS_API Input {

	public:
		static bool IsKeyPressed(int keycode);

		static void SetCursorMode(CursorMode mode);

		static bool IsMouseButtonPressed(int button);
		static std::pair<float, float> GetMousePos();

	};

}

#endif // !JASS_INPUT_H
