#ifndef BUFFER_LAYOUT_H_JASS
#define BUFFER_LAYOUT_H_JASS

#include "jasspch.h"
#include "Jass/Core/Core.h"

namespace Jass {

	enum class ShaderDataType {
		None = 0, Float, Float2, Float3, Float4, Int, Int2, Int3, Int4, Mat3, Mat4, Bool
	};

	static unsigned int ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
			case ShaderDataType::Float:
			case ShaderDataType::Int:
				return 4;
			case ShaderDataType::Float2:
			case ShaderDataType::Int2:
				return 4 * 2;
			case ShaderDataType::Float3:
			case ShaderDataType::Int3:
				return 4 * 3;
			case ShaderDataType::Float4:
			case ShaderDataType::Int4:
				return 4 * 4;
			case ShaderDataType::Mat3:
				return 4 * 3 * 3;
			case ShaderDataType::Mat4:
				return 4 * 4 * 4;
			case ShaderDataType::Bool:
				return 1;
		}

		JASS_CORE_ASSERT(false, "Unknown Shader Data type");
		return 0;
	}

	struct JASS_API BufferElement {
		
		ShaderDataType Type;
		std::string Name;
		bool Normalized;
		unsigned int Size;
		unsigned int Offset;

		BufferElement(ShaderDataType type, const std::string& name, bool normalized = false) :
			Type(type), Name(name), Normalized(normalized), Size(ShaderDataTypeSize(type)), Offset(0) {}

		unsigned int GetElementCount() const
		{
			switch (Type)
			{
				case ShaderDataType::Float:
				case ShaderDataType::Int:
				case ShaderDataType::Bool:
					return 1;
				case ShaderDataType::Float2:
				case ShaderDataType::Int2:
					return 2;
				case ShaderDataType::Float3:
				case ShaderDataType::Int3:
					return 3;
				case ShaderDataType::Float4:
				case ShaderDataType::Int4:
					return 4;
				case ShaderDataType::Mat3:
					return 3 * 3;
				case ShaderDataType::Mat4:
					return 4 * 4;
			}

			JASS_CORE_ASSERT(false, "Unknown Shader Data type");
			return 0;
		}

	};

	class JASS_API BufferLayout {

	public:
		BufferLayout(const std::initializer_list<BufferElement>& elements) :
			m_elements(elements)
		{
			CalculateOffsetAndStride();
		}

		BufferLayout() {}

		const unsigned int GetStride() const { return m_stride; }
		const std::vector<BufferElement>& GetElements() const { return m_elements; }

		std::vector<BufferElement>::iterator begin() { return m_elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return m_elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_elements.end(); }

	private:
		std::vector<BufferElement> m_elements;
		unsigned int m_stride = 0;

		void CalculateOffsetAndStride() {
			unsigned int offset = 0;
			for (auto& element : m_elements) {
				element.Offset = offset;
				offset += element.Size;
				m_stride += element.Size;
			}
		}

	};

}

#endif // !BUFFER_LAYOUT_H_JASS
