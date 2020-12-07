#ifndef PERSPECTIVE_CAMERA_H_JASS
#define PERSPECTIVE_CAMERA_H_JASS

#include "Camera.h"

namespace Jass {

	struct JASS_API PerspectiveCameraSettings {
		JVec3 Position;
		JVec3 Rotation;
		float FOV;
		float ViewportWidth;
		float ViewportHeight;
		float Near;
		float Far;

		PerspectiveCameraSettings() :
			Position({ 0.0f,0.0f,0.0f }), Rotation({ 0.0f,0.0f,0.0f }),
			FOV(45.0f), ViewportWidth(1280.0f), ViewportHeight(720.0f), Near(0.1f), Far(100.0f) {}
	};

	class JASS_API PerspectiveCamera : public Camera {

	public:
		PerspectiveCamera(const PerspectiveCameraSettings& settings = PerspectiveCameraSettings());

		virtual void SetPosition(const JVec3& position) override;
		virtual void SetRotation(const JVec3& rotation) override;

		const JVec3& GetUpVector() const { return m_upVector; }

		void LookAtTarget(const JVec3& target);

		void SetProjection(float fov, float width, float height, float pNear, float pFar);

		inline const PerspectiveCameraSettings& GetSettings() const { return m_settings; }

		inline virtual const JVec3& GetPosition() const override { return m_settings.Position; }
		inline virtual const JVec3& GetRotation() const override { return m_settings.Rotation; }

	private:
		PerspectiveCameraSettings m_settings;
		JVec3 m_upVector = { 0.0f, 1.0f, 0.0f };

		void CalculateMatrices();

	};

}

#endif // !PERSPECTIVE_CAMERA_H_JASS