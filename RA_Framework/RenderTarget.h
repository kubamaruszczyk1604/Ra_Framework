#pragma once
#include"Texture.h"
class RenderTarget
{
protected:
	int m_ID;
protected:
	RenderTarget(int id): m_ID{id} {}
public:
	RenderTarget(const RenderTarget&) = delete;
	RenderTarget& operator=(const RenderTarget&) = delete;
	virtual ~RenderTarget() {}
public:
	int GetID()const { return m_ID; }
public:
	virtual void Bind() = 0;
	virtual bool IsScreen() = 0;
	virtual bool IsOK() = 0;
};

