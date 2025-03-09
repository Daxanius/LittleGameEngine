#pragma once
#include <glm.hpp>

namespace dae
{
	class Transform final
	{
	public:
		Transform();
		Transform(float x, float y, float z = 0.f);

		void SetPosition(float x, float y, float z);
		void SetPosition(glm::vec3 position);

		const glm::vec3& GetPosition() const { return m_position; };

		// Operator to add and subtract transforms lol
		Transform operator+(const Transform& other) const;
		Transform operator-(const Transform& other) const;
	private:
		glm::vec3 m_position;
	};
}
