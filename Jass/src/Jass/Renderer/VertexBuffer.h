#ifndef JASS_VERTEXBUFFER_H
#define JASS_VERTEXBUFFER_H

#include "Jass/Core.h"
#include "DataUsageEnum.h"

namespace Jass {

	struct JASS_API VertexBufferConfig {
		float* Data;
		unsigned int Size;
		DataUsage DataUsage;
	};

	class JASS_API VertexBuffer {

	public:
		virtual ~VertexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		static VertexBuffer* Create(const VertexBufferConfig& config);

	};

}

#endif // !JASS_VERTEXBUFFER_H
