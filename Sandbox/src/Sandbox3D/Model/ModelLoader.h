#ifndef MODEL_LOADER_H
#define MODEL_LOADER_H

#include "Mesh.h"

class ModelLoader {

public:
	static Mesh LoadFromFile(const std::string& filename);

private:
	static void ReadFile(const std::string& filename, std::vector<MeshVertex>& vertices, std::vector<unsigned int>& indices);
};

#endif // !MODEL_LOADER_H
