#pragma once
#include "RAUtils.h"
#include "Component.h"
#include "RenderTarget.h"
namespace RA_FRAMEWORK
{
	class Scene;
	using OnRenderCallback = void(*)(RenderTarget* target, Texture* destination);
	enum class ProjectionType
	{
		ORTHO = 0,
		PERSPECTIVE = 1
	};
	class Entity;
	class Camera : public Component
	{
	private:
		static Mat4					s_IdentityMat;
		Mat4						m_ProjectionMat;
		Mat4						m_TransformMat;
		Mat4						m_ViewMat;
		Vec3						m_NoParrentPos;
		Vec3						m_NoParrentRotation;
		float						m_FOV;
		float						m_Near;
		float						m_Far;
		ProjectionType				m_ProjectionType;
		bool						m_Active;
		RENDER_MASK					m_Mask;
		ClearMode					m_ClearMode;
		ColorRGB					m_ClearColor;
		bool						m_ClearDepthFlag;
		RenderTarget*				p_RenderTarget;  
		Texture*					p_Destination;
		OnRenderCallback			m_RenderCallback;
	public:
		Camera(const ProjectionType& projection, const float& fovDeg, const float& fnear, const float& ffar);
		Camera(const Camera&)				= delete;
		Camera &operator=(const Camera&)	= delete;
		virtual ~Camera();
	public:
		float			GetFOV()const							{ return m_FOV; }
		float			GetNear()const							{ return  m_Near; }
		float			GetFar()const							{ return m_Far; }
		ProjectionType	GetProjectionType()const				{ return m_ProjectionType; }
		const Vec4&		GetWorldPosition()const					{ return m_TransformMat * Vec4(0, 0, 0, 1); }
		const Vec3&		GetLocalPosition()const					{ return m_NoParrentPos; }
		const Vec3&		GetLocalRotation()const					{ return m_NoParrentRotation; }
		const Mat4&		GetWorldMatrix()const					{ return m_TransformMat; }
		const Mat4&		GetViewMatrix()const					{ return m_ViewMat; }
		void			SetActive(bool active)					{ m_Active = active; }
		bool			isActive()const							{ return  m_Active; }
		void			SetClearMode(ClearMode mode)			{ m_ClearMode = mode; }
		void			SetClearColor(const ColorRGB& color)	{ m_ClearColor = color; }
		void			SetClearDepthFlag(bool clearDepth)		{ m_ClearDepthFlag = clearDepth; }
		ClearMode		GetClearMode()							{ return m_ClearMode; }
		bool			GetClearDepthFlag()						{ return m_ClearDepthFlag; }
		const ColorRGB& GetClearColor()							{ return m_ClearColor; }
		void SetRenderCallback(const OnRenderCallback caallback) { m_RenderCallback = caallback; }
	public:
		const Mat4&		GetProjectionMatrix(const int& scrWidth, const int& scrHeight);
		const Mat4&		SetTransformMatrix(const Vec3& translation, const Vec3& rotation);
		void			SetTransformMatrix(const glm::mat4& mat);
	public:
		void			SetRenderTarget(RenderTarget* target);
		void			SetTextureDestination(Texture* destination);
		RenderTarget*	GetRenderTarget();
		void            OnRender();
	};
}

