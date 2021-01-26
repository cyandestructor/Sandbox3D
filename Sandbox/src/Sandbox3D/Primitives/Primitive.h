#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "../Model/Mesh.h"

class Primitive {

public:
	virtual Mesh Generate() = 0;

};

#endif // !PRIMITIVE_H
