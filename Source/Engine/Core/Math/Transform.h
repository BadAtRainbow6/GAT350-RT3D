#pragma once
#include "Vector2.h"
#include "Matrix33.h"
#include "Core/Json.h"
#include <glm/glm/glm.hpp>
#include <glm/glm/gtx/transform.hpp>
#include <glm/glm/gtx/euler_angles.hpp>

namespace nc
{
	class Transform
	{
	public:
		glm::vec3 position;
		glm::vec3 rotation;
		glm::vec3 scale;

	public:
		Transform() = default;
		Transform(const glm::vec3& position, const glm::vec3& rotation = glm::vec3{ 0 }, const glm::vec3& scale = glm::vec3{ 1 }) :
			position{ position },
			rotation{ rotation },
			scale{ scale }
		{}

		glm::mat4 GetMatrix() const
		{
			glm::mat4 ms = glm::scale(scale);
			glm::mat4 mr = glm::eulerAngleYXZ(rotation.y, rotation.x, rotation.z);
			glm::mat4 mt = glm::translate(position);
			glm::mat4 mx = mt * ms; //* mr;

			return mx;
		}

		void Read(const json_t& value);
	};
}