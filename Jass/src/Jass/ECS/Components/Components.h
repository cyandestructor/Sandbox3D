#ifndef COMPONENTS_H_JASS
#define COMPONENTS_H_JASS

#include "Jass/JMath/JMath.h"

namespace Jass {

	struct TransformationComponent
	{
		TransformationComponent() = default;
		TransformationComponent(const TransformationComponent& other) = default;
		TransformationComponent(const JMat4& transformation) :
			Transformation(transformation) {}

		operator JMat4& () { return Transformation; }
		operator const JMat4&() const { return Transformation; }

		JMat4 Transformation = JMat4(1.0f);
	};

	struct SpriteComponent
	{
		SpriteComponent() = default;
		SpriteComponent(const SpriteComponent& other) = default;
		SpriteComponent(const JVec4 & color) :
			Color(color) {}

		JVec4 Color = JVec4(1.0f);
	};

	struct TagComponent
	{
		TagComponent() = default;
		TagComponent(const TagComponent& other) = default;
		TagComponent(const std::string& tag) :
			Tag(tag) {}

		std::string Tag;
	};

}

#endif // !COMPONENTS_H_JASS
