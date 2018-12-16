#include "MainWindow.h"
#include "Game.h"
#include "Vector.h"
#include "Rect.h"
#include "Image.h"
#include "Sprite.h"
#include "SpriteRenderer.h"
#include "Utils.h"

Image image;
Image textatlas;
std::vector<Image> textimages;
Sprite sprite;
std::map<char, int> ascimap;



Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd )
{
	image = Image("images/rgb.bmp");
	textatlas = Image("images/text.bmp");
	sprite = Sprite(&image, new SpriteRenderer());
	textimages = textatlas.slice({ 20,20 }, {39,1});

	for (int i = 0; i < 26; i++) {
		ascimap['a' + i] = i + 0;
		ascimap['A' + i] = i + 0;
	}
	for (int i = 0; i < 10; i++) {
		ascimap['0' + i] = i + 29;
	}
	ascimap[' '] = 26;
	ascimap[','] = 27;
	ascimap['.'] = 28;
}

void Game::Go()
{
	gfx.BeginFrame();
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{

}

void Game::ComposeFrame()
{
	
}

