#pragma once
#include <glm.hpp>

namespace dae
{
	class Transform final
	{
	public:
		Transform();
		Transform(float x, float y, float z = 0.f);
		Transform(const glm::vec2& position);
		Transform(const glm::vec3& position);

		void SetPosition(float x, float y, float z);
		void SetPosition(const glm::vec3& position);

		const glm::vec3& GetPosition() const { return m_position; };

		// Operator to add and subtract transforms lol
		Transform operator+(const Transform& other) const;
		Transform operator-(const Transform& other) const;
	private:
		glm::vec3 m_position;
	};
}
