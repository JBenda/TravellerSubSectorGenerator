// ConsoleApplication1.cpp : Defines the entry point for the console application.
//
#include "Bezirk.h"
#include "SFML\Graphics.hpp"
#define PI 3.14159265
const int dim[] = { 8, 10 };
const float a = 40;			//size of hex edge
const float h = a * sqrt(3) / 2.f;
const float dw = PI / 3.f;
const float dx = 1.5f * a;
const float dy = h;
int select[] = { -1, -1 };
sf::Vector2f topLeft(a,h);
void drawBezirk(Bezirk *bez, sf::RenderWindow & window)
{
	sf::ConvexShape hex(6);
	for(int i = 0; i < 6; ++i)
		hex.setPoint(i, sf::Vector2f(cos((float)i * dw) * a, sin((float)i * dw) * a));
	hex.setOutlineColor(sf::Color::Black);
	hex.setOutlineThickness(1);
	hex.setFillColor(sf::Color::Green);

	for (int j = 0; j < dim[1]; ++j)
	{
		for (int i = 0; i < dim[0]; ++i)
		{
			if (i == select[0] && j == select[1])
				hex.setFillColor(sf::Color::Blue);
			else if (bez->isSystem(i, j))
				hex.setFillColor(sf::Color::Green);
			else
				hex.setFillColor(sf::Color::Black);
			hex.setPosition(topLeft + sf::Vector2f(i * dx, j * 2.f * h + (i%2 == 0 ? 0.f : dy)));
			window.draw(hex);
		}
	}
}
int main()
{
	bool ifChange = true;
	const uint32_t v[] = { 0xa56301b9, 0x0dc5caae, 0xe132fa51 };
	Xorshift128::instance()->setValues(v[0], v[1], v[2]);
	Bezirk *bezirk;
	bezirk = new Bezirk(dim[0], dim[1],0);


	sf::RenderWindow window(sf::VideoMode(a + dim[0]*dx, (2 * dim[1] + 1) * h), "SFML works!");
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
				pos.x -= topLeft.x;
				pos.y -= topLeft.y;
				select[0] = pos.x / dx;
				select[1] = pos.y / (2 * dy);
				sf::Vector2i d(pos.x - select[0] * dx, pos.y - select[1] * 2 * dy - (select[0]%2 == 0 ? 0 : dy));
				int dV = d.x*d.x + d.y*d.y;
				select[0] ++;
				d = sf::Vector2i(pos.x - select[0] * dx, pos.y - select[1] * 2 * dy - (select[0] % 2 == 0 ? 0 : dy));
				if (dV < d.x*d.x + d.y*d.y)
					select[0] -= 1;
				else
					dV = d.x*d.x + d.y*d.y;
				if (select[0] % 2 == 0)
				{
					std::cout << "ww" << std::endl;
					select[1] ++;
					d = sf::Vector2i(pos.x - select[0] * dx, pos.y - select[1] * 2 * dy - (select[0] % 2 == 0 ? 0 : dy));
					if (dV < d.x*d.x + d.y*d.y)
						select[1] --;
				}
				else
				{
					select[1] ++;
					select[0] --;
					d = sf::Vector2i(pos.x - select[0] * dx, pos.y - select[1] * 2 * dy - (select[0] % 2 == 0 ? 0 : dy));
					if (dV < d.x*d.x + d.y*d.y)
					{
						select[0] += 2;
						d = sf::Vector2i(pos.x - select[0] * dx, pos.y - select[1] * 2 * dy - (select[0] % 2 == 0 ? 0 : dy));
						if (dV < d.x*d.x + d.y*d.y)
						{
							select[0] --;
							select[1] --;
						}
					}

				}
				std::cout << select[0] << ":" << select[1] << "  d=" << d.x*d.x + d.y*d.y << "  dV=" << dV << std::endl;
			}
		}
			window.clear();
			drawBezirk(bezirk, window);
			window.display();
	}
	return 0;
}

