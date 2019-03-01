#pragma once
#include "RATypes.h"
#include "FreeImage.h"
#pragma comment(lib, "FreeImage.lib")
namespace RA_FRAMEWORK
{
	using BITMAP_DATA = FIBITMAP;
	struct Image
	{
		BITMAP_DATA* DATA = nullptr;
		bool HAS_TRANSPARENCY = true;
		int GetWidth() 
		{ 
			if(DATA) return FreeImage_GetWidth(DATA); 
			return 0;
		}
		int GetHeight() 
		{
			if(DATA) return FreeImage_GetHeight(DATA); 
			return 0;
		}
		RAbyte* GetPixels()
		{ 
			if(DATA) return (RAbyte*)FreeImage_GetBits(DATA); 
			return nullptr;
		}	
	};

	class ImageLoader
	{
	public:
		ImageLoader();
		virtual ~ImageLoader();
		ImageLoader(const ImageLoader&) = delete;
		ImageLoader& operator=(const ImageLoader) = delete;
	public:
		BITMAP_DATA* Load(const String& path, bool transparent = true);
		bool Load(const String& path, Image& output, bool alphaChannel = true);
		void Free(BITMAP_DATA*& data);
		void Free(Image& image);
	};
}