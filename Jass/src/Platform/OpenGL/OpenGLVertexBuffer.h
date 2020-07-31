#ifndef JASS_OPENGLVERTEXBUFFER_H
#define JASS_OPENGLVERTEXBUFFER_H

#include "Jass/Renderer/VertexBuffer.h"

namespace Jass {

	class JASS_API OpenGLVertexBuffer : public VertexBuffer {

	public:
		OpenGLVertexBuffer(const VertexBufferConfig& config);
		virtual ~OpenGLVertexBuffer();

		virtual void Bind() const;
		virtual void Unbind() const;
	private:
		unsigned int m_rendererID = 0;

		static unsigned int GLDataUsage(DataUsage usage);

	};

}

#endif // !JASS_OPENGLVERTEXBUFFER_H
