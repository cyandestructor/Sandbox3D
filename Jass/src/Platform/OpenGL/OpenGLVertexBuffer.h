#ifndef JASS_OPENGLVERTEXBUFFER_H
#define JASS_OPENGLVERTEXBUFFER_H

#include "Jass/Renderer/VertexBuffer.h"

namespace Jass {

	class JASS_API OpenGLVertexBuffer : public VertexBuffer {

	public:
		OpenGLVertexBuffer(const VertexBufferConfig& config);
		virtual ~OpenGLVertexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void SetLayout(const BufferLayout& layout) override { m_layout = layout; }
		virtual const BufferLayout& GetLayout() const override { return m_layout; }


	private:
		unsigned int m_rendererID = 0;
		BufferLayout m_layout;

		static unsigned int GLDataUsage(DataUsage usage);

	};

}

#endif // !JASS_OPENGLVERTEXBUFFER_H
