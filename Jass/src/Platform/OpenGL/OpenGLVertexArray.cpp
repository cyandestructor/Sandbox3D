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

	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
	{
		JASS_CORE_ASSERT(vertexBuffer != nullptr, "Vertex buffer should not be nullptr");
		JASS_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex buffer has no layout");

		glBindVertexArray(m_rendererID);
		vertexBuffer->Bind();

		unsigned int index = 0;
		for (const auto& element : vertexBuffer->GetLayout()) {
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index,
				element.GetElementCount(),
				ToGLenum(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				vertexBuffer->GetLayout().GetStride(),
				(const void*)element.Offset);
			index++;
		}

		m_vertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		JASS_CORE_ASSERT(indexBuffer != nullptr, "Index buffer should not be nullptr");
		glBindVertexArray(m_rendererID);
		indexBuffer->Bind();

		m_indexBuffer = indexBuffer;
	}

}
