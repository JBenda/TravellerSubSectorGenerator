// ConsoleApplication1.cpp : Defines the entry point for the console application.
//
#include "Bezirk.h"
#include "SFML/Graphics.hpp"
#include <math.h>

const int dim[] = { 8, 10 };
const float a = 40;			//size of hex edge
const float h = a * (float)sqrt(3) / 2.f;
const float dw = PI / 3.f;
const float dx = 1.5f * a;
const float dy = h;
int selected[] = { -1, -1 };
sf::Vector2f topLeft(a,h);
sf::Font font;

void loadStuff()
{
	font.loadFromFile("ariblk.ttf");
}
sf::Vector2i posToPx(sf::Vector2i corner, int pos[2])
{
	return sf::Vector2i(corner.x - (int)(pos[0] * dx), corner.y - (int)(pos[1] * 2 * dy) - (pos[0] % 2 == 0 ? 0 : (int)dy));
}
int main()
{
	bool ifChange = true;
	const uint32_t v[] = { 0xa56301b9, 0x0dc5caae, 0xeff2fa51 };
	Xorshift128::instance()->setValues(v[0], v[1], v[2]);
	Bezirk *bezirk;
	bezirk = new Bezirk(dim[0], dim[1],0);

	loadStuff();
	sf::RenderWindow window(sf::VideoMode(a + (int)(dim[0]*dx), (int)(2 * dim[1] + 1) * h), "SFML works!");
	sf::Image im;
	sf::Texture lastScreen;
	lastScreen.create(window.getSize().x, window.getSize().y);
	sf::Sprite sp;
	window.setFramerateLimit(60);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::MouseButtonPressed)
			{
				sf::Vector2i pos = sf::Mouse::getPosition(window);
				pos.x -= (int)topLeft.x;
				pos.y -= (int)topLeft.y;
				selected[0] = (int)(pos.x / dx);
				selected[1] = (int)(pos.y / (2 * dy));
				sf::Vector2i d = posToPx(pos, selected);
				int dV = d.x*d.x + d.y*d.y;
				selected[0] ++;
				d = posToPx(pos, selected);
				if (dV < d.x*d.x + d.y*d.y)
					selected[0] -= 1;
				else
					dV = d.x*d.x + d.y*d.y;
				if (selected[0] % 2 == 0)
				{
					selected[1] ++;
					d = posToPx(pos, selected);
					if (dV < d.x*d.x + d.y*d.y)
						selected[1] --;
				}
				else
				{
					selected[1] ++;
					selected[0] --;
					d = posToPx(pos, selected);
					if (dV < d.x*d.x + d.y*d.y)
					{
						selected[0] += 2;
						d = posToPx(pos, selected);
						if (dV < d.x*d.x + d.y*d.y)
						{
							selected[0] --;
							selected[1] --;
						}
					}

				}
			}
		}
			window.clear();
                        bezirk->draw(window,topLeft, dx,dy, dw, h, a,font, selected, dim);
			window.display();
	}
	return 0;
}

