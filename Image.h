#pragma once
#include <vector>
#include "Vector.h"
#include <fstream>
#include "ChiliWin.h"

struct Image{
	
	V2i size;
	std::vector<V3i> pixels;

	Image(){}

	Image(V2i size) {
		this->size = size;
		pixels.resize(size.x * size.y);
	}

	Image(std::string filename) {
		std::ifstream file(filename, std::ios::binary);

		BITMAPFILEHEADER bmFileHeader;
		file.read(reinterpret_cast<char*>(&bmFileHeader), sizeof(bmFileHeader));

		BITMAPINFOHEADER bmInfoHeader;
		file.read(reinterpret_cast<char*>(&bmInfoHeader), sizeof(bmInfoHeader));


		const bool is32b = bmInfoHeader.biBitCount == 32;

		size.x = bmInfoHeader.biWidth;

		// test for reverse row order and control
		// y loop accordingly
		int yStart;
		int yEnd;
		int dy;
		if (bmInfoHeader.biHeight < 0)
		{
			size.y = -bmInfoHeader.biHeight;
			yStart = 0;
			yEnd = size.y;
			dy = 1;
		}
		else
		{
			size.y = bmInfoHeader.biHeight;
			yStart = size.y - 1;
			yEnd = -1;
			dy = -1;
		}

		pixels.resize(size.x * size.y);

		file.seekg(bmFileHeader.bfOffBits);
		// padding is for the case of of 24 bit depth only
		const int padding = (4 - (size.x * 3) % 4) % 4;

		for (int y = yStart; y != yEnd; y += dy)
		{
			for (int x = 0; x < size.x; x++)
			{
				PutPixel(x, y, V3i(file.get(), file.get(), file.get()));
				if (is32b)
				{
					file.seekg(1, std::ios::cur);
				}
			}
			if (!is32b)
			{
				file.seekg(padding, std::ios::cur);
			}
		}
	}

	void PutPixel(unsigned int x, unsigned int y, V3i c)
	{
		pixels[y * size.x + x] = c;
	}

	V3i GetPixel(unsigned int x, unsigned int y) const
	{
		return pixels[y * size.x + x];
	}

	std::vector<Image> slice(V2i subimagesize, V2i amount){
		std::vector<Image> result;
		result.reserve(amount.x * amount.y);

		amount.loop2d([&](V2i* pos) {
			Image newimage(subimagesize);

			subimagesize.loop2d([&](V2i* subpos){
				V2i abs = *pos->c().mul(&subimagesize)->add(subpos);
				newimage.PutPixel(subpos->x, subpos->y, GetPixel(abs.x, abs.y));
			});
			result.push_back(newimage);
		});
		return result;
	}
};