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

		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
		virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;

		virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const override
		{
			return m_vertexBuffers;
		}

		virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const override
		{
			return m_indexBuffer;
		}

	private:
		unsigned int m_rendererID;
		std::vector<std::shared_ptr<VertexBuffer>> m_vertexBuffers;
		std::shared_ptr<IndexBuffer> m_indexBuffer;

	};

}

#endif // !OPENGL_VERTEX_ARRAY_H_JASS
