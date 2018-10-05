#include "transform.h"

using namespace maths;

maths::mat4 Transform::toMatrix()
{
		maths::mat4 translationMatrix = maths::mat4::translate(m_pos.x, m_pos.y, m_pos.z);
		maths::mat4 rotationMatrix = m_rot.to_matrix();

		maths::mat4 transformationMatrix = rotationMatrix.mul(translationMatrix);

		return (transformationMatrix);
}

void Transform::rotate(maths::vec3 axis, float angle)
{
		m_rot = m_rot.mul(quat(axis, TO_RADIANS(angle)).normalize());
}
