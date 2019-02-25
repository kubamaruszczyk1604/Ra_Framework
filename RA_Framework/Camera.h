#pragma once
#include "RAUtils.h"
#include "Component.h"

namespace RA_FRAMEWORK
{
	enum class ProjectionType
	{
		ORTHO = 0,
		PERSPECTIVE = 1
	};

	class Entity;
	class Camera : public Component
	{
	private:
		static glm::mat4 s_IdentityMat;
		glm::mat4 m_ProjectionMat;
		glm::mat4 m_TransformMat;
		glm::mat4 m_ViewMat;
		glm::vec3 m_NoParrentPos;
		glm::vec3 m_NoParrentRotation;
		float m_FOV;
		float m_Near;
		float m_Far;
		ProjectionType m_ProjectionType;
		bool m_Active;
	public:
		Camera(const ProjectionType& projection, const float& fovDeg, const float& fnear, const float& ffar);
		Camera(const Camera&) = delete;
		Camera &operator=(const Camera&) = delete;
		virtual ~Camera();
	public:
		float GetFOV()const { return m_FOV; }
		float GetNear()const { return  m_Near; }
		float GetFar()const { return m_Far; }
		ProjectionType GetProjectionType()const { return m_ProjectionType; }
		const Vec4& GetWorldPosition()const { return m_TransformMat * Vec4(0, 0, 0, 1); }
		const Vec3& GetLocalPosition()const { return m_NoParrentPos; }
		const Vec3& GetLocalRotation()const { return m_NoParrentRotation; }
		const Mat4& GetWorldMatrix()const { return m_TransformMat; }
		const Mat4& GetViewMatrix()const { return m_ViewMat; }
		const Mat4& GetProjectionMatrix(const int& scrWidth, const int& scrHeight);

		void SetActive(bool active) { m_Active = active; }
		bool isActive()const { return  m_Active; }
		const Mat4& SetTransformMatrix(const Vec3& translation, const Vec3& rotation);
		void SetTransformMatrix(const glm::mat4& mat);
		

	};
}
