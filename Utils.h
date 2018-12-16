#pragma once
#include "Sprite.h";
#include <map>
#include "Graphics.h"

void drawString(V2i pos, std::string string, std::map<char, int> map, std::vector<Image> images, Graphics& gfx) {
	Sprite sprite(&images[0], new SpriteRenderer());
	for (int i = 0; i < string.size(); i++) {
		Image image = images[map[string[i]]];
		sprite.image = &image;
		sprite.draw(gfx, { pos.x + i * image.size.x, pos.y });
	}
}
