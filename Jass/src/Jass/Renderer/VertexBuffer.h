#ifndef JASS_VERTEXBUFFER_H
#define JASS_VERTEXBUFFER_H

#include "DataUsageEnum.h"
#include "BufferLayout.h"

namespace Jass {

	struct JASS_API VertexBufferConfig {
		const void* Data;
		unsigned int Size;
		DataUsage DataUsage;
	};

	class JASS_API VertexBuffer {

	public:
		virtual ~VertexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetLayout(const BufferLayout& layout) = 0;
		virtual const BufferLayout& GetLayout() const = 0;

		virtual void SetData(const void* data, unsigned int size) = 0;

		static Ref<VertexBuffer> Create(const VertexBufferConfig& config);
		static Ref<VertexBuffer> Create(unsigned int size);

	};

}

#endif // !JASS_VERTEXBUFFER_H
