#include "ImageLoader.h"
namespace RA_FRAMEWORK
{
	ImageLoader::ImageLoader(){}
	ImageLoader::~ImageLoader(){}

	BITMAP_DATA* ImageLoader::LoadImage(const String& path)
	{
		FREE_IMAGE_FORMAT texFormat = FreeImage_GetFileType(path.c_str(), 0);
		FIBITMAP* image = FreeImage_Load(texFormat, path.c_str());
		if (!image) return nullptr;

		FIBITMAP* temp = image;
		image = FreeImage_ConvertTo24Bits(image);
		FreeImage_Unload(temp);
		return image;
	}

	bool ImageLoader::LoadImage(const String& path, Image& output)
	{
		output.DATA = LoadImage(path);
		if (!output.DATA) return false;
		return true;
	}

	void ImageLoader::Free(BITMAP_DATA*& data)
	{
		FreeImage_Unload(data);
	}

	void ImageLoader::Free(Image& image)
	{
		FreeImage_Unload(image.DATA);
	}
}