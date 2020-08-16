#ifndef JASS_IINPUT_H
#define JASS_INPUT_H

#include "jasspch.h"
#include "Core.h"

namespace Jass {

	class JASS_API Input {

	public:
		static inline bool IsKeyPressed(int keycode) { return s_instance->IntIsKeyPressed(keycode); }

		static inline bool IsMouseButtonPressed(int button) {
			return s_instance->IntIsMouseButtonPressed(button);
		}
		static inline std::pair<float, float> GetMousePos() { return s_instance->IntGetMousePos(); }

	protected:
		virtual bool IntIsKeyPressed(int keycode) = 0;

		virtual bool IntIsMouseButtonPressed(int button) = 0;
		virtual std::pair<float, float> IntGetMousePos() = 0;

	private:
		static std::unique_ptr<Input> s_instance;

	};

}

#endif // !JASS_IINPUT_H
