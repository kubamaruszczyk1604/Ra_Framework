#pragma once
class RenderTarget
{
protected:
	RenderTarget() {}
public:
	RenderTarget(const RenderTarget&) = delete;
	RenderTarget& operator=(const RenderTarget&) = delete;
	virtual ~RenderTarget() {}
public:
	virtual void Bind() = 0;

};

