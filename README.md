# Sandbox3D

Sandbox3D is a simple 3D graphics demo application based on [Jass Engine], specially made for educational purposes.

## Features

* OBJ 3D Model loader based on [tinyobjloader]
* GUI Dialogs based on [Dear ImGui]
* Phong shading Materials
* Diffuse Textures and Normal mapping
* Skybox
* Terrain loaded from Height Map
* Spherical and Cylindrical Billboards
* Built-in Water Shader with Reflection and Refraction
* Keyboard and Mouse Input
* Gamepad Support

## Examples

The repository has some examples that are useful to learn how to use some of the built-in features, as well as how to use basic features of the [Jass Engine].

The code in the examples has useful comments, but there are some things that are explained only in some files, so for a better understanding of the examples, follow this order to read and test the code:

1. Model loading
2. Transformations
3. Terrain loading
4. Skybox loading
5. Billboard loading
6. Water loading

## Getting started

### You will need

* Visual Studio 2017 or 2019 recommended
* Support for OpenGL 4.5+
* **Download the example models** from [this] link

### Steps

1. Clone the repository: `git clone --recursive https://github.com/cyandestructor/Sandbox3D.git`
2. Extract the Example models zip file on Sandbox/assets
3. Open the Jass.sln file and run

### How to check the examples

1. The code of the examples is on Sandbox/src/Examples (Feel free to read and modify)
2. On Sandbox/src look for the SandboxApp.cpp file, looks more or less like this:
```c++
#include <Jass.h>
#include <Jass/Core/EntryPoint.h>

#include "Examples/ModelLoading/ModelLoading.h"
//#include "Examples/Transformations/Transformations.h"
//#include "Examples/TerrainLoading/TerrainLoading.h"
//#include "Examples/SkyboxLoading/SkyboxLoading.h"
//#include "Examples/BillboardLoading/BillboardLoading.h"
//#include "Examples/WaterLoading/WaterLoading.h"
//#include "Sandbox3D/Sandbox3D.h"

/* ... */
class Sandbox : public Jass::Application {

public:
	Sandbox() {
		PushLayer(new ModelLoading);
		//PushLayer(new Transformations);
		//PushLayer(new TerrainLoading);
		//PushLayer(new SkyboxLoading);
		//PushLayer(new BillboardLoading);
		//PushLayer(new WaterLoading);
		//PushLayer(new Sandbox3D);
	}

	~Sandbox() {

	}

};

Jass::Application* Jass::CreateApplication() {
	return new Sandbox();
}
```
4. Comment the active example `#include` and `PushLayer()` call, and uncomment the one of the example you want. **Make sure to only push one layer at a time**. There is more info on the file itself.

## Gallery

![Model transformations example](https://github.com/cyandestructor/Sandbox3D/blob/master/Assets/demo_image_1.png?raw=true)
![Sandbox3D scene](https://github.com/cyandestructor/Sandbox3D/blob/master/Assets/demo_image_3.png?raw=true)
![Sandbox3D scene](https://github.com/cyandestructor/Sandbox3D/blob/master/Assets/demo_image_2.png?raw=true)

[Jass Engine]: https://github.com/cyandestructor/Jass
[tinyobjloader]: https://github.com/tinyobjloader/tinyobjloader
[Dear ImGui]: https://github.com/ocornut/imgui
[this]: https://www.dropbox.com/sh/oo66dn1ojok97im/AABW8sWzlgekw6xzMe5WjATVa?dl=0
