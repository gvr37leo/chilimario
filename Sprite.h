#pragma once
#include "Image.h"
#include "SpriteRenderer.h"
#include "Rect.h"

struct Sprite{
	Image* image;
	SpriteRenderer* renderer;

	Sprite(){}

	Sprite(Image* image, SpriteRenderer* renderer){
		this->image = image;
		this->renderer = renderer;
	}

	void draw(Graphics& gfx, V2i pos){
		
		Recti r = Recti::fromsize(pos, image->size);

		r.loop2d([&](V2i* abs, V2i* rel) {
			V3i c = image->GetPixel(rel->x, rel->y);
			renderer->process(&c, *rel);
			gfx.PutPixel(abs->x, abs->y, c.r,c.g,c.b);
		});

	}
};