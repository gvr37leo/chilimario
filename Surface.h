#pragma once

#include "Colors.h"
#include <string>
#include <vector>
#include "Rect.h"

class Surface
{
public:
	Surface(const std::string& filename);
	Surface(int width, int height);
	Surface(Surface&& donor);
	Surface(const Surface&) = default;
	Surface& operator=(Surface&& rhs);
	Surface& operator=(const Surface&) = default;
	Surface() = default;
	void PutPixel(unsigned int x, unsigned int y, Color c)
	{
		pixels[y * GetWidth() + x] = c;
	}
	Color GetPixel(unsigned int x, unsigned int y) const
	{
		return pixels[y * GetWidth() + x];
	}
	int GetWidth() const;
	int GetHeight() const;
	const Color* Data() const;
private:
	std::vector<Color> pixels;
	int width = 0;
	int height = 0;
};