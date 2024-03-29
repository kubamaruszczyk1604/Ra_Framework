#include "Camera.h"
namespace RA_FRAMEWORK
{
	Mat4 Camera::s_IdentityMat{ Mat4(1.0) };

	Camera::Camera(const ProjectionType& projection, const float& fovDeg, const float& fnear, const float& ffar) :
		Component("comp_camera", ComponentType::CAMERA_COMPONENT),
		m_ProjectionMat(s_IdentityMat),
		m_TransformMat(s_IdentityMat),
		m_ViewMat(s_IdentityMat),
		m_ProjectionType(projection),
		m_FOV(fovDeg),
		m_Near(fnear),
		m_Far(ffar),
		m_Active(true),
		m_Mask{RENDER_MASK_ELEMENT::RENDERABLE},
		m_ClearMode{ClearMode::COLOR},
		m_ClearColor{0.2,0.0,1.0},
		m_ClearColor2(1.0,0.4,0.0),
		m_GradientInfo(1.0,-1.0,3.0),
		m_ClearDepthFlag{true}{}

	Camera::~Camera(){}

	const glm::mat4& Camera::GetProjectionMatrix(const int & scrWidth, const int & scrHeight)
	{
		if (m_ProjectionType == ProjectionType::PERSPECTIVE)
		{
			m_ProjectionMat = glm::perspectiveFovLH(glm::radians(m_FOV),
				static_cast<float>(scrWidth),
				static_cast<float>(scrHeight),
				m_Near,
				m_Far);
		}
		else
		{
			m_ProjectionMat = s_IdentityMat;
		}

		return m_ProjectionMat;
	}

	const Mat4& Camera::SetTransformMatrix(const Vec3& translation, const Vec3& rotation)
	{
		// not implemented
		return m_TransformMat;
	}

	void Camera::SetTransformMatrix(const Mat4& mat)
	{
		m_TransformMat = mat;
		m_ViewMat = glm::inverse(m_TransformMat);
	}

	void Camera::GetProjectionForSkybox(const int & scrWidth, const int & scrHeight, Mat4 & mat)
	{
		mat = glm::perspectiveFovLH(glm::radians(m_FOV),
			static_cast<float>(scrWidth),
			static_cast<float>(scrHeight),
			0.01f,
			2.0f);
	}

	void Camera::SetRenderTarget(RenderTarget* target)
	{
		p_RenderTarget = target;
	}

	RenderTarget* Camera::GetRenderTarget()
	{
		return p_RenderTarget;
	}


	bool Camera::OnRender()
	{
		if (m_RenderCallback)
		{
			m_RenderCallback(this, p_RenderTarget, p_RenderTarget->GetPostProcessTexture());
			return true;
		}
		return false;
	}
}
