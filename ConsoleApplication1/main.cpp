// ConsoleApplication1.cpp : Defines the entry point for the console application.
//
#include "Bezirk.h"
#include <math.h>
#include "SFML/Graphics.hpp"
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
System::TradeList tl;
void drawBezirk(Bezirk *bez, sf::RenderWindow & window)
{
	sf::ConvexShape hex(6);
	sf::Text num;
	num.setCharacterSize(18);
	num.setColor(sf::Color::Blue);
	num.setFont(font);
	for(int i = 0; i < 6; ++i)
		hex.setPoint(i, sf::Vector2f(cos((float)i * dw) * a, sin((float)i * dw) * a));
	hex.setOutlineColor(sf::Color::Black);
	hex.setOutlineThickness(1);
	hex.setFillColor(sf::Color::Green);
	int pij[2];
	int sysNum = 0;
	char cBuff[20];
	hex.setOutlineThickness(2);
	hex.setOutlineColor(sf::Color::Black);
	bool isSys;
        std::vector<sf::Vertex> tradeLines;
	int buff;
        if(bez->getSystemAt(selected[0], selected[1]) != nullptr)
  	  tl = bez->getSystemAt(selected[0], selected[1])->getTradeSystems();
	for (int j = 0; j < dim[1]; ++j)
	{
		for (int i = 0; i < dim[0]; ++i)
		{
			isSys = false;
                        sf::Vector2f position = topLeft + sf::Vector2f(i * dx, j * 2.f * h + (i % 2 == 0 ? 0.f : dy));
			hex.setPosition(position);
			if (bez->isSystem(i, j))
			{
				isSys = true;
                                sprintf(cBuff, "%i", bez->getId(i, j));
				num.setString(cBuff);
				num.setPosition(hex.getPosition().x - num.getGlobalBounds().width * 0.5f,
								hex.getPosition().y - num.getGlobalBounds().height * 0.5f);
				pij[0] = i;
				pij[1] = j;
				if (i == selected[0] && j == selected[1])
				{
					hex.setFillColor(sf::Color::Blue);
				}
				else if ((buff = bez->disShortestTravPath(selected, pij)) <= 4 && buff > 0)
				{
					hex.setFillColor(sf::Color::Magenta);
					int id = bez->getSystemAt(i, j)->getId();
					if (tl != nullptr)
					{
						for (int k = 0; k < tl->size(); ++k)
							if (tl->at(k)->getId() == id)
							{
								hex.setFillColor(sf::Color::Red);
								break;
							}
					}
				}
				else
				{
						switch (bez->getSystemAt(i, j)->getTradeType())
						{
						case System::TRADE_TYPE::UNIN :hex.setFillColor(sf::Color::Cyan);
							break;
						case System::TRADE_TYPE::AGRA: hex.setFillColor(sf::Color::Green);
							break;
						case System::TRADE_TYPE::IND: hex.setFillColor(sf::Color(100, 100, 100));
							break;
						case System::TRADE_TYPE::OMNI: hex.setFillColor(sf::Color::Black);
							break;
						}
				}
					
			}
			else
				hex.setFillColor(sf::Color::White);
			window.draw(hex);
			if(isSys)
			  window.draw(num);
		}
	}
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
			drawBezirk(bezirk, window);
			window.display();
	}
	return 0;
}

