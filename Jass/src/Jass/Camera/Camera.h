#ifndef CAMERA_H_JASS
#define CAMERA_H_JASS

#include "Jass/JMath/JMath.h"
#include "Jass/Core/Core.h"

namespace Jass {

	class JASS_API Camera {

	public:
		virtual ~Camera() {}

		virtual void SetPosition(const JVec3& position) = 0;
		virtual void SetRotation(const JVec3& rotation) = 0;

		virtual const JVec3& GetPosition() const = 0;
		virtual const JVec3& GetRotation() const = 0;

		inline virtual const JMat4& GetView() const { return m_view; }
		inline virtual const JMat4& GetProjection() const { return m_projection; }
		inline virtual const JMat4& GetViewProjection() const { return m_viewProjection; }

	protected:
		JMat4 m_view = JMat4(1.0f);
		JMat4 m_projection = JMat4(1.0f);
		JMat4 m_viewProjection = JMat4(1.0f);

	};

}

#endif // !CAMERA_H_JASS
