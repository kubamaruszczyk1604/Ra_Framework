#pragma once
#include "RATypes.h"
#include "Texture.h"
#include <iostream>
#include <fstream>
namespace RA_FRAMEWORK
{
	struct SkyBoxDesc
	{
		String RIGHT;
		String LEFT;
		String TOP;
		String BOTTOM;
		String FRONT;
		String BACK;


		String&  GetFace(uint i)
		{
			switch (i)
			{
			case 0:
				return RIGHT;
			case 1:
				return LEFT;
			case 2:
				return TOP;
			case 3:
				return BOTTOM;
			case 4:
				return FRONT;
			case 5:
				return BACK;
			default:
				return const_cast<String&>(s_ERROR);
			}
		}

	private:
		static const String s_ERROR;
		
	};

	class SkyBox
	{
	public:
		static bool ReadDesc(const String& raskyFile, SkyBoxDesc& outDesc);
		SkyBox() {}
	public:
		
		virtual ~SkyBox() {}

		virtual bool Load(const String& raskyFile, String& outStatus) = 0;
		virtual void Bind() = 0;
		virtual void Unbind() = 0;

	};

	

}