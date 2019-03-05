#pragma once
#include "RATypes.h"
#include "Stopwatch.h"
#include "KLMList.h"
#include "RABuiltInShaders.h"
namespace RA_FRAMEWORK
{
	template<class T_KEY, class T_VAL>
	bool QueryMap(T_KEY key, T_VAL& output, const std::unordered_map<T_KEY, T_VAL>& map)
	{
		auto itemPair = map.find(key);
		if (itemPair != std::end(map))
		{
			output = itemPair->second;
			return true;
		}
		return false;
	};

	template<class T>
	void RemoveFromVecByValue(std::vector<T>& vec, const T& value)
	{
		vec.erase(std::remove(vec.begin(), vec.end(), value), vec.end());
	}

	inline float RandomRange(float low, float high)
	{
		return  low + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (high - low)));
	}

	inline bool IsApproxEqual(const float& a, const float& b, float epsilon)
	{
		return (fabs(b - a) < epsilon);
	};

	inline bool IsApproxEqual(const double& a, const double& b, double epsilon)
	{
		return (fabs(b - a) < epsilon);
	};

	inline void PrintVec(const Vec3& vec)
	{
		std::cout << "x=" << vec.x << "  y=" << vec.y << "  z=" << vec.z << std::endl;
	}

	inline void PrintCol(const ColorRGBA& col)
	{
		std::cout << "r=" << col.r << "  g=" << col.g << "  b=" << col.b << "  a=" << col.a << std::endl;
	}

	inline void DEBUG(const std::string& line)
	{
		std::cout << "DEBUG: " << line << std::endl;
	}

	inline void PRINTL(const std::string& line)
	{
		std::cout << line << std::endl;
	}

	inline std::string ToString(int value)
	{
		return std::to_string(value);
	}

	inline std::string ToString(float value)
	{
		return std::to_string(value);
	}

	inline std::string ToString(double value)
	{
		return std::to_string(value);
	}

	inline std::string ToString(const Vec3& vec)
	{
		return   "x=" + std::to_string(vec.x) +
			"  y=" + std::to_string(vec.y) +
			"  z=" + std::to_string(vec.z);
	}

	inline std::string ToString(const Vec4& vec)
	{
		return   "x=" + std::to_string(vec.x) +
			"  y=" + std::to_string(vec.y) +
			"  z=" + std::to_string(vec.z) +
			"  w=" + std::to_string(vec.w);
	}

	inline std::string ColourToString(const ColorRGBA& colour)
	{
		return   "r=" + std::to_string(colour.r) +
			"  g=" + std::to_string(colour.g) +
			"  b=" + std::to_string(colour.b) +
			"  a=" + std::to_string(colour.a);
	}

	inline void WaitForKeypress()
	{
		_getch();
	}

	inline float ToRadians(const float& degrees)
	{
		return glm::radians(degrees);
	}

	inline float ToDegrees(const float& radinas)
	{
		return glm::degrees(radinas);
	}

	inline Mat4 RotateMatX(const Mat4& matrix, const float& degrees)
	{
		return glm::rotate(matrix, degrees, Vec3(1, 0, 0));
	}

	inline Mat4 RotateMatY(const Mat4& matrix, const float& degrees)
	{
		return glm::rotate(matrix, degrees, Vec3(0, 1, 0));
	}

	inline Mat4 RotateMatZ(const Mat4& matrix, const float& degrees)
	{
		return glm::rotate(matrix, degrees, Vec3(0, 0, 1));
	}

	inline float Lerp(const float a, const float b, const float t)
	{
		return a * (1.0f - t) + b * t;
	}

	inline Vec2 Lerp(const Vec2& a, const Vec2& b, const float t)
	{
		return a * (1.0f - t) + b * t;
	}

	inline Vec3 Lerp(const Vec3& a, const Vec3& b,const float t)
	{
		return a * (1.0f - t) + b * t;
	}

	inline Vec4 Lerp(const Vec4& a, const Vec4& b, float t)
	{
		return a * (1.0f - t) + b * t;
	}

	inline void AddToMask(RENDER_MASK& mask, RENDER_MASK_ELEMENT element)
	{
		mask |= element;
	}

	inline void RemoveFromMask(RENDER_MASK& mask, RENDER_MASK_ELEMENT element)
	{
		mask &= (~element);
	}

	inline bool CheckMask(RENDER_MASK& mask, RENDER_MASK_ELEMENT element)
	{
		return (bool)(mask&element);
	}

	inline void Dec2Bin(unsigned mask)
	{
		String s;
		while (mask > 0)
		{
			s += " " + std::to_string(mask % 2);
			mask /= 2;
		}
		std::reverse(s.begin(), s.end());
		std::cout << s << std::endl;
	}

	inline void PrintMask(unsigned mask, unsigned places)
	{
		while (places>0)
		{
			const bool on = (bool)(mask & (1 << (places-1)));
			std::cout << on << " ";

			places--;
		}
		std::cout << std::endl;
	}

	//same as print mask but impeleneted with logically -slower than PrintMask()
	/*inline void Dec2Bin(unsigned mask, unsigned places)
	{
		int div = pow(2, places);
		while (div > 0)
		{
			int r = mask / div;
			std::cout << r << " ";
			if (r > 0) mask -= div;
			div /= 2;
		}
		std::cout << std::endl;
	}*/
}
