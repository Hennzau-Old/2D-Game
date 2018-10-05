#ifndef TRANSFORM
#define TRANSFORM

#include "maths.h"

class Transform
{
		private:
			maths::vec3 m_pos;
			maths::quat m_rot;

		public:
			Transform()
			{
					m_pos = maths::vec3();
					m_rot = maths::quat();
			}

			maths::mat4 				toMatrix();

			void 								rotate(maths::vec3 axis, float angle);

			maths::vec3 				getPosition() { return (m_pos); };
			maths::quat 				getRotation() { return (m_rot); };

			void 								setPosition(maths::vec3 pos) { m_pos = pos; };
			void 								setRotation(maths::quat rot) { m_rot = rot; };

			maths::vec3 				getForward() { return (m_rot.getForward()); }
			maths::vec3 				getUp() { return (m_rot.getUp()); }
			maths::vec3 				getRight() { return (m_rot.getRight()); }
};

#endif
