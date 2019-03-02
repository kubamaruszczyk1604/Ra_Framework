#pragma once
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
	int GetID() { return m_ID; }
public:
	virtual void Bind() = 0;

};

