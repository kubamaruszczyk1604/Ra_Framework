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
	};

	class SkyBox
	{
	public:
		static bool ReadDesc(const String& raskyFile, SkyBoxDesc& outDesc);
		SkyBox() {}
	public:
		
		virtual ~SkyBox() {}

		virtual bool Load(const String& raskyFile, String& outStatus) = 0;
		virtual Texture* GetTexture() = 0;

	};

	bool SkyBox::ReadDesc(const String& raskyFile, SkyBoxDesc& outDesc)
	{
		std::ifstream ifs(raskyFile);
		if (!ifs.is_open()) return false;
		int counter = 0;
		String buffer;
		while (ifs >> buffer)
		{
			if (buffer == "RIGHT")			{ ifs >> outDesc.RIGHT; counter++; }
			else if (buffer == "LEFT")		{ ifs >> outDesc.LEFT; counter++;}
			else if (buffer == "TOP")		{ ifs >> outDesc.TOP; counter++; }
			else if (buffer == "BOTTOM")	{ ifs >> outDesc.BOTTOM; counter++; }
			else if (buffer == "FRONT")		{ ifs >> outDesc.FRONT; counter++; }
			else if (buffer == "BACK")		{ ifs >> outDesc.BACK; counter++; }
		}
		if (counter != 6) return false;
		String path = raskyFile;
		for (int i = (raskyFile.length() - 1); i > 0; --i)
		{
			if (raskyFile[i] == '/') { path = raskyFile.substr(0, i); break; }
		}
		
		outDesc.RIGHT = path + "/faces/" + outDesc.RIGHT;
		outDesc.LEFT= path + "/faces/" + outDesc.LEFT;
		outDesc.TOP = path + "/faces/" + outDesc.TOP;
		outDesc.BOTTOM= path + "/faces/" + outDesc.BOTTOM;
		outDesc.FRONT = path + "/faces/" + outDesc.FRONT;
		outDesc.BACK= path + "/faces/" + outDesc.BACK;
		ifs.close();
		return true;
	}

}