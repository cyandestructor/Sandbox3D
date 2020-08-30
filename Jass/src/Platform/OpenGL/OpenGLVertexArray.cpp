#include "jasspch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Jass {

	// Temporary function
	static GLenum ToGLenum(ShaderDataType type)
	{
		switch (type)
		{
			case ShaderDataType::Float:
			case ShaderDataType::Float2:
			case ShaderDataType::Float3:
			case ShaderDataType::Float4:
			case ShaderDataType::Mat3:
			case ShaderDataType::Mat4:
				return GL_FLOAT;
			case ShaderDataType::Int:
			case ShaderDataType::Int2:
			case ShaderDataType::Int3:
			case ShaderDataType::Int4:
				return GL_INT;
			case ShaderDataType::Bool:
				return GL_BOOL;
		}

		JASS_CORE_ASSERT(false, "Unknown Shader Data type");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glGenVertexArrays(1, &m_rendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_rendererID);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_rendererID);
	}

	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
	{
		JASS_PROFILE_FUNCTION();

		JASS_CORE_ASSERT(vertexBuffer != nullptr, "Vertex buffer should not be nullptr");
		JASS_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex buffer has no layout");

		glBindVertexArray(m_rendererID);
		vertexBuffer->Bind();

		unsigned int index = 0;
		for (const auto& element : vertexBuffer->GetLayout()) {
			glEnableVertexAttribArray(index);

			switch (ToGLenum(element.Type))
			{
				case GL_FLOAT:
					SetAttrib(index, element, vertexBuffer->GetLayout().GetStride());
					break;
				case GL_INT:
					SetAttribInt(index, element, vertexBuffer->GetLayout().GetStride());
					break;
				default:
					JASS_CORE_ASSERT(false, "Unsupported data type");
			}

			index++;
		}

		m_vertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
	{
		JASS_PROFILE_FUNCTION();

		JASS_CORE_ASSERT(indexBuffer != nullptr, "Index buffer should not be nullptr");
		glBindVertexArray(m_rendererID);
		indexBuffer->Bind();

		m_indexBuffer = indexBuffer;
	}

	void OpenGLVertexArray::SetAttrib(unsigned int index, const BufferElement& element, unsigned int stride)
	{
		glVertexAttribPointer(index,
			element.GetElementCount(),
			ToGLenum(element.Type),
			element.Normalized ? GL_TRUE : GL_FALSE,
			stride,
			(const void*)(uint64_t)element.Offset);
	}

	void OpenGLVertexArray::SetAttribInt(unsigned int index, const BufferElement& element, unsigned int stride)
	{
		glVertexAttribIPointer(index,
			element.GetElementCount(),
			ToGLenum(element.Type),
			stride,
			(const void*)(uint64_t)element.Offset);
	}

}
