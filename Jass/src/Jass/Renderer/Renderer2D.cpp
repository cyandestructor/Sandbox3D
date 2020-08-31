#include "jasspch.h"
#include "Renderer2D.h"

#include "RenderCommand.h"
#include "Shaders/ShaderLibrary.h"
#include "Shaders/Shader.h"

namespace Jass {

	struct QuadVertex {
		JVec3 Position;
		JVec4 Color;
		JVec2 TexCoord;
		int TexIndex;
		float TileFactor;
	};

	struct Renderer2DData {
		// TODO: Change Ref with Scope
		Ref<Shader> ColorTextureShader;
		Ref<Texture2D> WhiteTexture;
		Ref<VertexArray> VertexArray;
		Ref<VertexBuffer> VertexBuffer;

		static constexpr unsigned int MaxQuads = 20000;
		static constexpr unsigned int MaxVertices = MaxQuads * 4;
		static constexpr unsigned int MaxIndices = MaxQuads * 6;

		unsigned int QuadIndexCount = 0;

		std::vector<QuadVertex> QuadVertices;

		static constexpr unsigned int MaxTextureSlots = 32;
		std::array<Ref<Texture2D>, MaxTextureSlots> TextureSlots;
		unsigned int TextureSlotIndex = 1;	// 0 is reserved for White Texture

		std::array<JVec4, 4> QuadVertexPositions = { {
				{ -0.5f, -0.5f, 0.0f, 1.0f },
				{ 0.5f, -0.5f, 0.0f, 1.0f },
				{ 0.5f, 0.5f, 0.0f, 1.0f },
				{ -0.5f, 0.5f, 0.0f, 1.0f }
		} };

		std::array<JVec2, 4> QuadTexCoords = { {
				{ 0.0f, 0.0f },
				{ 1.0f, 0.0f },
				{ 1.0f, 1.0f },
				{ 0.0f, 1.0f }
		} };

		// Statistics
		Renderer2D::Statistics Statistics;

	};

	static Renderer2DData s_data;

	void Renderer2D::Init()
	{
		JASS_PROFILE_FUNCTION();

		s_data.ColorTextureShader = Shader::Create("assets/shaders/ColorTexture.glsl");
		s_data.ColorTextureShader->Bind();

		// Assign samplers for texture slots and load them into the shader
		int samplers[Renderer2DData::MaxTextureSlots];
		for (unsigned int i = 0; i < Renderer2DData::MaxTextureSlots; i++)
			samplers[i] = i;

		s_data.ColorTextureShader->SetIntArray("u_textures", samplers, Renderer2DData::MaxTextureSlots);

		// Create a default white texture
		s_data.WhiteTexture = Texture2D::Create(1, 1);
		uint32_t texData = 0xffffffff;
		s_data.WhiteTexture->SetData(&texData, sizeof(uint32_t));
		s_data.TextureSlots[0] = s_data.WhiteTexture;
		// ------------------------------

		s_data.VertexArray = Jass::VertexArray::Create();

		// Pre-allocate memory for vertices
		s_data.QuadVertices.reserve(Renderer2DData::MaxVertices);

		s_data.VertexBuffer = Jass::VertexBuffer::Create(Renderer2DData::MaxVertices * sizeof(QuadVertex));
		s_data.VertexBuffer->SetLayout({
			Jass::BufferElement(Jass::ShaderDataType::Float3,"a_position"),
			Jass::BufferElement(Jass::ShaderDataType::Float4,"a_color"),
			Jass::BufferElement(Jass::ShaderDataType::Float2,"a_texCoords"),
			Jass::BufferElement(Jass::ShaderDataType::Int,"a_texIndex"),
			Jass::BufferElement(Jass::ShaderDataType::Float,"a_tileFactor")
			});

		s_data.VertexArray->AddVertexBuffer(s_data.VertexBuffer);

		auto indices = std::make_unique<unsigned int[]>(Renderer2DData::MaxIndices);

		// Generate the indices
		unsigned int offset = 0;
		for (size_t i = 0; i < (size_t)Renderer2DData::MaxIndices; i += 6)
		{
			indices[i + 0] = offset + 0;
			indices[i + 1] = offset + 1;
			indices[i + 2] = offset + 2;
		
			indices[i + 3] = offset + 2;
			indices[i + 4] = offset + 3;
			indices[i + 5] = offset + 0;

			offset += 4;
		}

		auto indexBuffer = Jass::IndexBuffer::Create({ indices.get(),Renderer2DData::MaxIndices,Jass::DataUsage::StaticDraw });

		s_data.VertexArray->SetIndexBuffer(indexBuffer);
		indices.reset();
	}

	void Renderer2D::Shutdown()
	{
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		JASS_PROFILE_FUNCTION();

		s_data.ColorTextureShader->Bind();
		s_data.ColorTextureShader->SetMat4("u_viewProjection", camera.GetViewProjection());

		InitBatch();
	}

	void Renderer2D::EndScene()
	{
		unsigned int dataSize = (unsigned int)s_data.QuadVertices.size() * sizeof(QuadVertex);
		s_data.VertexBuffer->SetData(&s_data.QuadVertices[0], dataSize);

		Flush();
	}

	void Renderer2D::Flush()
	{
		for (unsigned int i = 0; i < s_data.TextureSlotIndex; i++)
			s_data.TextureSlots[i]->Bind(i);

		RenderCommand::DrawIndexed(s_data.VertexArray, s_data.QuadIndexCount);
		s_data.Statistics.DrawCalls++;
	}

	void Renderer2D::DrawQuad(const JVec2& position, const JVec2& size, const JVec4& color)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, color);
	}

	void Renderer2D::DrawQuad(const JVec3& position, const JVec2& size, const JVec4& color)
	{
		JASS_PROFILE_FUNCTION();

		AddQuad(position, size, color, 0, 1.0f);
	}

	void Renderer2D::DrawRotatedQuad(const JVec2& position, float rotation, const JVec2& size, const JVec4& color)
	{
		DrawRotatedQuad({ position.x, position.y, 0.0f }, rotation, size, color);
	}

	void Renderer2D::DrawRotatedQuad(const JVec3& position, float rotation, const JVec2& size, const JVec4& color)
	{
		JASS_PROFILE_FUNCTION();

		AddRotatedQuad(position, size, rotation, color, 0, 1.0f);
	}

	void Renderer2D::DrawQuad(const JVec2& position, const JVec2& size, const Ref<Texture2D>& texture, float tileFactor, const JVec4& tintColor)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, texture, tileFactor, tintColor);
	}

	void Renderer2D::DrawQuad(const JVec3& position, const JVec2& size, const Ref<Texture2D>& texture, float tileFactor, const JVec4& tintColor)
	{
		JASS_PROFILE_FUNCTION();

		unsigned int textureIndex = SetTextureIndex(texture);

		AddQuad(position, size, tintColor, textureIndex, tileFactor);
	}

	void Renderer2D::DrawRotatedQuad(const JVec2& position, float rotation, const JVec2& size, const Ref<Texture2D>& texture, float tileFactor, const JVec4& tintColor)
	{
		DrawRotatedQuad({ position.x, position.y, 0.0f }, rotation, size, texture, tileFactor, tintColor);
	}

	void Renderer2D::DrawRotatedQuad(const JVec3& position, float rotation, const JVec2& size, const Ref<Texture2D>& texture, float tileFactor, const JVec4& tintColor)
	{
		JASS_PROFILE_FUNCTION();

		unsigned int textureIndex = SetTextureIndex(texture);

		AddRotatedQuad(position, size, rotation, tintColor, textureIndex, tileFactor);
	}

	void Renderer2D::DrawQuad(const QuadTransformation& transformation, const JVec4& color)
	{
		if (transformation.Rotation == 0.0f)
			DrawQuad(transformation.Position, transformation.Size, color);
		else
			DrawRotatedQuad(transformation.Position, transformation.Rotation, transformation.Size, color);
	}

	void Renderer2D::DrawQuad(const QuadTransformation& transformation, const TextureProps& textureProperties)
	{
		if (transformation.Rotation == 0.0f) {
			if (textureProperties.Texture != nullptr) {
				DrawQuad(transformation.Position, transformation.Size,
					textureProperties.Texture, textureProperties.TileFactor, textureProperties.TintColor);
			}
			else {
				DrawQuad(transformation.Position, transformation.Size, textureProperties.TintColor);
			}
		}
		else {
			if (textureProperties.Texture != nullptr) {
				DrawRotatedQuad(transformation.Position, transformation.Rotation, transformation.Size,
					textureProperties.Texture, textureProperties.TileFactor, textureProperties.TintColor);
			}
			else {
				DrawRotatedQuad(transformation.Position, transformation.Rotation, transformation.Size, textureProperties.TintColor);
			}
		}
	}

	Renderer2D::Statistics Renderer2D::GetStatistics()
	{
		return s_data.Statistics;
	}

	void Renderer2D::ResetStatistics()
	{
		memset(&s_data.Statistics, 0, sizeof(Renderer2D::Statistics));
	}

	void Renderer2D::AddQuad(const JVec3& position, const JVec2& size, const JVec4& color, unsigned int texIndex, float tileFactor)
	{
		if (s_data.QuadIndexCount >= Renderer2DData::MaxIndices)
			FlushAndReset();
		
		QuadVertex quadVertex;

		JMat4 transformation = Translate(JMat4(1.0f), position);
		transformation = Scale(transformation, { size.x, size.y, 1.0f });

		for (unsigned int i = 0; i < 4; i++) {
			quadVertex.Position = transformation * s_data.QuadVertexPositions[i];
			quadVertex.Color = color;
			quadVertex.TexCoord = s_data.QuadTexCoords[i];
			quadVertex.TexIndex = texIndex;
			quadVertex.TileFactor = tileFactor;
			s_data.QuadVertices.push_back(quadVertex);
		}

		s_data.QuadIndexCount += 6;

		s_data.Statistics.TotalQuads++;
	}

	void Renderer2D::AddRotatedQuad(const JVec3& position, const JVec2& size, float rotation, const JVec4& color, unsigned int texIndex, float tileFactor)
	{
		if (s_data.QuadIndexCount >= Renderer2DData::MaxIndices)
			FlushAndReset();

		QuadVertex quadVertex;

		JMat4 transformation = Translate(JMat4(1.0f), position);
		transformation = Rotate(transformation, rotation, { 0.0f, 0.0f, 1.0f });
		transformation = Scale(transformation, { size.x, size.y, 1.0f });

		for (unsigned int i = 0; i < 4; i++) {
			quadVertex.Position = transformation * s_data.QuadVertexPositions[i];
			quadVertex.Color = color;
			quadVertex.TexCoord = s_data.QuadTexCoords[i];
			quadVertex.TexIndex = texIndex;
			quadVertex.TileFactor = tileFactor;
			s_data.QuadVertices.push_back(quadVertex);
		}

		s_data.QuadIndexCount += 6;

		s_data.Statistics.TotalQuads++;
	}

	unsigned int Renderer2D::SetTextureIndex(const Ref<Texture2D>& texture)
	{
		unsigned int textureIndex = 0;

		// Check if the texture has already been saved
		for (unsigned int i = 1; i < s_data.TextureSlotIndex; i++) {
			if (*s_data.TextureSlots[i] == *texture) {
				textureIndex = i;
				break;
			}
		}

		if (!textureIndex) {
			textureIndex = s_data.TextureSlotIndex;
			s_data.TextureSlots[s_data.TextureSlotIndex] = texture;
			s_data.TextureSlotIndex++;
		}

		return textureIndex;
	}

	void Renderer2D::InitBatch()
	{
		s_data.QuadVertices.clear();
		s_data.QuadIndexCount = 0;

		s_data.TextureSlotIndex = 1;
	}

	void Renderer2D::FlushAndReset()
	{
		EndScene();
		InitBatch();
	}

}
