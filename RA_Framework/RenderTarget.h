#pragma once
class RenderTarget
{
public:
	RenderTarget() {}
	RenderTarget(const RenderTarget&) = delete;
	RenderTarget& operator=(const RenderTarget&) = delete;
	virtual ~RenderTarget() {}

};

