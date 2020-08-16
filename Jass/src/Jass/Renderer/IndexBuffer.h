#ifndef JASS_INDEXBUFFER_H
#define JASS_INDEXBUFFER_H

#include "Jass/Core/Core.h"
#include "DataUsageEnum.h"

namespace Jass {

	struct JASS_API IndexBufferConfig {
		unsigned int* Data;
		unsigned int Count;
		DataUsage DataUsage;
	};

	class JASS_API IndexBuffer {

	public:
		virtual ~IndexBuffer() {}

		virtual	unsigned int GetCount() const = 0;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		static Ref<IndexBuffer> Create(const IndexBufferConfig& config);

	};

}

#endif // !JASS_INDEXBUFFER_H
