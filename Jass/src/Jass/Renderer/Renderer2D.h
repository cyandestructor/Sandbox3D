#ifndef RENDERER2D_H_JASS
#define RENDERER2D_H_JASS

#include "Jass/Camera/OrthographicCamera.h"

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

	};

}

#endif // !RENDERER2D_H_JASS
