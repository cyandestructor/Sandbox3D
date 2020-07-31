#include "jasspch.h"
#include "OpenGLIndexBuffer.h"

#include <glad/glad.h>

namespace Jass {

	OpenGLIndexBuffer::OpenGLIndexBuffer(const IndexBufferConfig& config) :
		m_count(config.Count)
	{
		glGenBuffers(1, &m_rendererID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, config.Count * sizeof(unsigned int), 
			config.Data, GLDataUsage(config.DataUsage));
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		glDeleteBuffers(1, &m_rendererID);
	}

	void OpenGLIndexBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID);
	}

	void OpenGLIndexBuffer::Unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	unsigned int OpenGLIndexBuffer::GLDataUsage(DataUsage usage)
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
		default:
			break;
		}
	}

}
