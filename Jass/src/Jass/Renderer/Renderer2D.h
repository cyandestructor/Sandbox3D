#ifndef RENDERER2D_H_JASS
#define RENDERER2D_H_JASS

#include "Jass/Camera/OrthographicCamera.h"
#include "Jass/Renderer/Textures/Texture2D.h"

namespace Jass {

	class JASS_API Renderer2D {

	public:
		static void Init();
		static void Shutdown();
		
		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();

		static void DrawQuad(const JVec2& position, const JVec2& scale, const JVec4& color);
		static void DrawQuad(const JVec3& position, const JVec2& scale, const JVec4& color);
		static void DrawQuad(const JVec2& position, float rotation, const JVec2& scale, const JVec4& color);
		static void DrawQuad(const JVec3& position, float rotation, const JVec2& scale, const JVec4& color);
		static void DrawQuad(const JVec2& position, const JVec2& scale, const Ref<Texture2D>& texture);
		static void DrawQuad(const JVec3& position, const JVec2& scale, const Ref<Texture2D>& texture);
		static void DrawQuad(const JVec2& position, float rotation, const JVec2& scale, const Ref<Texture2D>& texture);
		static void DrawQuad(const JVec3& position, float rotation, const JVec2& scale, const Ref<Texture2D>& texture);

	};

}

#endif // !RENDERER2D_H_JASS
