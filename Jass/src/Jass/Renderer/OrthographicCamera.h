#ifndef ORTHOGRAPHIC_CAMERA_H_JASS
#define ORTHOGRAPHIC_CAMERA_H_JASS

#include "Camera.h"

namespace Jass {

	struct JASS_API OrthographicCameraSettings {
		glm::vec3 Position;
		glm::vec3 Rotation;
		float Left;
		float Right;
		float Top;
		float Bottom;

		OrthographicCameraSettings() :
			Position({ 0.0f,0.0f,0.0f }), Rotation({ 0.0f,0.0f,0.0f }),
			Left(-1.0f), Right(1.0f), Top(1.0f), Bottom(-1.0f) {}
		OrthographicCameraSettings(float left, float right, float bottom, float top) :
			Position({ 0.0f,0.0f,0.0f }), Rotation({ 0.0f,0.0f,0.0f }),
			Left(left), Right(right), Top(top), Bottom(bottom) {}
	};

	class JASS_API OrthographicCamera : public Camera {

	public:
		OrthographicCamera(const OrthographicCameraSettings& settings);

		virtual void SetPosition(const glm::vec3& position) override;
		virtual void SetRotation(const glm::vec3& rotation) override;
		
		inline const OrthographicCameraSettings& GetSettings() const { return m_settings; }

		inline virtual const glm::vec3& GetPosition() const override { return m_settings.Position; }
		inline virtual const glm::vec3& GetRotation() const override { return m_settings.Rotation; }

	private:
		OrthographicCameraSettings m_settings;

		void CalculateMatrices();

	};

}

#endif // !ORTHOGRAPHIC_CAMERA_H_JASS
