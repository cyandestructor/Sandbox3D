#ifndef ORTHOGRAPHIC_CAMERA_H_JASS
#define ORTHOGRAPHIC_CAMERA_H_JASS

#include "Camera.h"

namespace Jass {

	struct JASS_API OrthographicCameraSettings {
		JVec3 Position;
		JVec3 Rotation;
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
		OrthographicCamera(const OrthographicCameraSettings& settings = OrthographicCameraSettings());

		virtual void SetPosition(const JVec3& position) override;
		virtual void SetRotation(const JVec3& rotation) override;
		
		inline const OrthographicCameraSettings& GetSettings() const { return m_settings; }

		inline virtual const JVec3& GetPosition() const override { return m_settings.Position; }
		inline virtual const JVec3& GetRotation() const override { return m_settings.Rotation; }

	private:
		OrthographicCameraSettings m_settings;

		void CalculateMatrices();

	};

}

#endif // !ORTHOGRAPHIC_CAMERA_H_JASS
