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
		m_ClearColor{ColorRGB(0,0,1)},
		m_ClearDepthFlag{true}{}

	Camera::~Camera(){}

	const glm::mat4 & Camera::GetProjectionMatrix(const int & scrWidth, const int & scrHeight)
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

	void Camera::SetTransformMatrix(const glm::mat4& mat)
	{
		m_TransformMat = mat;
		m_ViewMat = glm::inverse(m_TransformMat);
	}

	void Camera::AddRenderTarget(RenderTarget* target)
	{
		m_RenderTargetList.Add(target);
	}

	RenderTarget* Camera::GetRenderTarget(int index)
	{
		if (m_RenderTargetList.Count() == 0) return nullptr;
		if (index >= m_RenderTargetList.Count()) return nullptr;
		return m_RenderTargetList[index];
	}

	RenderTarget* Camera::FindRenderTarget(int id)
	{
		RenderTarget** r = m_RenderTargetList.Find([id](RenderTarget*  o) { return (id == o->GetID()); });
		return *r;
	}

	int Camera::RenderTargetCount()
	{
		return m_RenderTargetList.Count();
	}

	bool Camera::TryBindRenderTarget(int index)
	{
		if (m_RenderTargetList.Count() == 0) return false;
		if (index >= m_RenderTargetList.Count()) return false;
		m_RenderTargetList[index]->Bind();
		return true;
	}
}
