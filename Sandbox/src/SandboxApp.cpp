#include <Jass.h>
#include <Jass/Core/EntryPoint.h>

//#include "Sandbox3D/Sandbox3D.h"
//#include "Examples/ModelLoading/ModelLoading.h"
//#include "Examples/Transformations/Transformations.h"
//#include "Examples/TerrainLoading/TerrainLoading.h"
//#include "Examples/SkyboxLoading/SkyboxLoading.h"
#include "Examples/BillboardLoading/BillboardLoading.h"

class Sandbox : public Jass::Application {

public:
	Sandbox() {
		//PushLayer(new Sandbox3D);
		//PushLayer(new ModelLoading);
		//PushLayer(new Transformations);
		//PushLayer(new TerrainLoading);
		//PushLayer(new SkyboxLoading);
		PushLayer(new BillboardLoading);
	}

	~Sandbox() {

	}

};

Jass::Application* Jass::CreateApplication() {
	return new Sandbox();
}