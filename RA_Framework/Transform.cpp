#include "Transform.h"

namespace RA_FRAMEWORK
{

	Transform::Transform() :
		m_Position{ 0, 0, 0 }, 
		m_Rotation{ 0, 0, 0 }, 
		m_Scale{ 1, 1, 1 },
		m_World{Mat4(1.0)},
		m_ParentTransformStack{Mat4(1.0)} {}


	Transform::~Transform() {}
}