#include "EditorLayer.h"

#include <Jass/Core/EntryPoint.h>

namespace Jass {

	class JassEditor : public Application {

	public:
		JassEditor()
		{
			PushLayer(new EditorLayer());
		}

		~JassEditor()
		{

		}

	};

	Application* CreateApplication() {
		return new JassEditor();
	}

}