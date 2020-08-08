#ifndef OPENGL_VERTEX_ARRAY_H_JASS
#define OPENGL_VERTEX_ARRAY_H_JASS

#include "Jass/Renderer/VertexArray.h"

namespace Jass {

	class JASS_API OpenGLVertexArray : public VertexArray {

	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) override;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;

		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const override
		{
			return m_vertexBuffers;
		}

		virtual const Ref<IndexBuffer>& GetIndexBuffer() const override
		{
			return m_indexBuffer;
		}

	private:
		unsigned int m_rendererID;
		std::vector<Ref<VertexBuffer>> m_vertexBuffers;
		Ref<IndexBuffer> m_indexBuffer;

	};

}

#endif // !OPENGL_VERTEX_ARRAY_H_JASS
