#ifndef JASS_WININPUT_H
#define JASS_WININPUT_H

#include "Jass/Input.h"

namespace Jass {

	class WinInput : public Input {

	protected:
		virtual bool IntIsKeyPressed(int keycode);

		virtual bool IntIsMouseButtonPressed(int button);
		virtual std::pair<float, float> IntGetMousePos();

	};
}

#endif // !JASS_WININPUT_H