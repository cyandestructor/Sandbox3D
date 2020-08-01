#ifndef OPENGLINDEXBUFFER_H
#define OPENGLINDEXBUFFER_H

#include "Jass/Renderer/IndexBuffer.h"

namespace Jass {

	class JASS_API OpenGLIndexBuffer : public IndexBuffer {

	public:
		OpenGLIndexBuffer(const IndexBufferConfig& config);

		virtual ~OpenGLIndexBuffer();
		
		virtual	inline unsigned int GetCount() const override { return m_count; }

		virtual void Bind() const override;
		virtual void Unbind() const override;

	private:
		unsigned int m_rendererID = 0;
		unsigned int m_count;

		static unsigned int GLDataUsage(DataUsage usage);

	};

}

#endif // !JASS_OPENGLINDEXBUFFER_H
