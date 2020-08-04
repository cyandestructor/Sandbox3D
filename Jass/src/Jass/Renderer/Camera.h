#ifndef CAMERA_H_JASS
#define CAMERA_H_JASS

#include <glm/glm.hpp>
#include "Jass/Core.h"

namespace Jass {

	class JASS_API Camera {

	public:
		virtual ~Camera() {}

		virtual void SetPosition(const glm::vec3& position) = 0;
		virtual void SetRotation(const glm::vec3& rotation) = 0;

		virtual const glm::vec3& GetPosition() const = 0;
		virtual const glm::vec3& GetRotation() const = 0;

		inline virtual const glm::mat4& GetView() const { return m_view; }
		inline virtual const glm::mat4& GetProjection() const { return m_projection; }
		inline virtual const glm::mat4& GetViewProjection() const { return m_viewProjection; }

	protected:
		glm::mat4 m_view;
		glm::mat4 m_projection;
		glm::mat4 m_viewProjection;

	};

}

#endif // !CAMERA_H_JASS
