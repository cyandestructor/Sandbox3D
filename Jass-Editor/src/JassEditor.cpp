#include "EditorLayer.h"

#include <Jass/Core/EntryPoint.h>

namespace Jass {

	class JassEditor : public Application {

	public:
		JassEditor() :
			Application("Jass Editor")
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