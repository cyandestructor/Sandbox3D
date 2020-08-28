#include "jasspch.h"
#include "OpenGLVertexBuffer.h"

#include <glad/glad.h>

namespace Jass {

	OpenGLVertexBuffer::OpenGLVertexBuffer(const VertexBufferConfig& config)
	{
		JASS_PROFILE_FUNCTION();

		glGenBuffers(1, &m_rendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
		glBufferData(GL_ARRAY_BUFFER, config.Size, config.Data, GLDataUsage(config.DataUsage));
	}

	OpenGLVertexBuffer::OpenGLVertexBuffer(unsigned int size)
	{
		JASS_PROFILE_FUNCTION();

		glGenBuffers(1, &m_rendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
		glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glDeleteBuffers(1, &m_rendererID);
	}

	void OpenGLVertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
	}

	void OpenGLVertexBuffer::Unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void OpenGLVertexBuffer::SetData(const void* data, unsigned int size)
	{
		JASS_PROFILE_FUNCTION();
		
		glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
	}

	unsigned int OpenGLVertexBuffer::GLDataUsage(DataUsage usage)
	{
		switch (usage)
		{
			case DataUsage::StreamDraw:
				return GL_STREAM_DRAW;
				break;
			case DataUsage::StreamRead:
				return GL_STREAM_READ;
				break;
			case DataUsage::StreamCopy:
				return GL_STREAM_COPY;
				break;
			case DataUsage::StaticDraw:
				return GL_STATIC_DRAW;
				break;
			case DataUsage::StaticRead:
				return GL_STATIC_READ;
				break;
			case DataUsage::StaticCopy:
				return GL_STATIC_COPY;
				break;
			case DataUsage::DynamicDraw:
				return GL_DYNAMIC_DRAW;
				break;
			case DataUsage::DynamicRead:
				return GL_DYNAMIC_READ;
				break;
			case DataUsage::DynamicCopy:
				return GL_DYNAMIC_COPY;
				break;
		}

		JASS_CORE_ASSERT(false, "Unknown Data Usage");
		return 0;
	}

}