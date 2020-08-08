#ifndef VERTEX_ARRAY_H_JASS
#define VERTEX_ARRAY_H_JASS

#include "VertexBuffer.h"
#include "IndexBuffer.h"

namespace Jass {

	class JASS_API VertexArray {

	public:
		virtual ~VertexArray() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) = 0;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) = 0;

		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const = 0;
		virtual const Ref<IndexBuffer>& GetIndexBuffer() const = 0;

		static VertexArray* Create();

	};

}

#endif // !VERTEX_ARRAY_H_JASS
