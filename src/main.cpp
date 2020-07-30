// ConsoleApplication1.cpp : Defines the entry point for the console application.
//
#include "Bezirk.h"
#include "DetailScreen.h"
#include "SFML/Graphics.hpp"
#include "SFML/System/Clock.hpp"

#include <math.h>


constexpr std::array<int, 2> dim = { 8, 10 };
constexpr float a = 40;			//size of hex edge
constexpr float h = a * (float)sqrt(3) / 2.f;
constexpr float dw = PI<float> / 3.f;
constexpr float dx = 1.5f * a;
constexpr float dy = h;
constexpr std::array<float, 2> N_UP_RIGHT = {0.8660254037844387f, -0.5f};
constexpr std::array<float, 2> N_DOWN_RIGHT = {0.8660254037844387f, 0.5f};
constexpr std::array<float, 2> N_UP_LEFT = {-0.8660254037844387f, -0.5f};
constexpr std::array<float, 2> N_DOWN_LEFT = {-0.8660254037844387f, 0.5f};
std::array<int, 2> selected = { -1, -1 };
sf::Vector2f topLeft(a,h);
sf::Font font;

void loadStuff()
{
	font.loadFromFile("ariblk.ttf");
}

std::array<int, 2> tileUnderMouse(const sf::Vector2f& topLeft, const sf::RenderWindow& window) {
    sf::Vector2i pxpos(sf::Mouse::getPosition(window));
    sf::Vector2f pos = window.mapPixelToCoords(pxpos);
    pos.x -= topLeft.x;
    pos.y -= topLeft.y;
    std::cout << "click: " << pos.x << ", " << pos.y << std::endl;
    const int x = static_cast<int>(pos.x / a);
    std::array<int, 2> res = {-1, -1};
    res[0] = (2*x) / 3;

    // right/left side
    const int place = x % 3;
    std::cout << "x " << x << ", " << place;
    if(place == 0 || place == 2) {
      res[1] = static_cast<int>((pos.y + h)/ (2.f*h));


      sf::Vector2f center(x*a, res[1]*2.f*h);
      if (place == 0) {
        center.x += a;
      } else {
        res[0] += 1;
      }
      pos -= center;
      if (place == 0 && pos.y < 0) {
        if ( pos.x * N_UP_RIGHT[0] + pos.y * N_UP_RIGHT[1] > 0) {
          res[0] += 1;
          res[1] -= 1;
        }
      } else if (place == 0){
        if (pos.x * N_DOWN_RIGHT[0] + pos.y * N_DOWN_RIGHT[1] > 0) {
          res[0] += 1;
        }
      } else if (pos.y < 0) {
        if (pos.x * N_UP_LEFT[0] + pos.y * N_UP_LEFT[1] > 0) {
          res[0] -= 1;
          res[1] -= 1;
        }
      } else {
        if ( pos.x * N_DOWN_LEFT[0] + pos.y * N_DOWN_LEFT[1] > 0) {
          res[0] -= 1;
        }
      }
    }
    // corridor case
    else  {
      res[0] += 1;
      res[1] = static_cast<int>(pos.y / (2.f*h));
    }
    return res;
}

int main()
{
	const uint32_t v[] = { 0xa56301b9, 0x0dc5caae, 0xeff2fa51 };
	Xorshift128::instance()->setValues(v[0], v[1], v[2]);
    std::unique_ptr<Bezirk> bezirk = std::make_unique<Bezirk>(dim[0], dim[1], 0);

	loadStuff();
	sf::RenderWindow window(sf::VideoMode(a + static_cast<int>(dim[0]*dx) * 2, static_cast<int>(2 * dim[1] + 1) * h), "SFML works!");

	sf::Image im;
	sf::Texture lastScreen;
	lastScreen.create(window.getSize().x, window.getSize().y);
	// sf::Sprite sp;
    DetailScreen detailScreen(
      font,
      sf::Vector2f(dim[0]*dx + dx, 0),
      sf::Vector2f(dim[0]*dx - dx, (2*dim[1] + 1)*h),
      "."
    );
	window.setFramerateLimit(10);
    window.clear();
    bezirk->draw(window,topLeft, dx,dy, dw, h, a,font, selected.data(), dim.data());
    detailScreen.draw(window);
    window.display();

    sf::Clock clock;
	while (window.isOpen())
	{
        sf::Time dt = clock.restart();
        detailScreen.animationUpdate(dt.asSeconds());

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::MouseButtonPressed)
			{
                selected = tileUnderMouse(topLeft, window);

                if(const System* sys;
                  (sys =
                    bezirk->getSystemAt(
                      selected[0],
                      selected[1]
                    )) != nullptr) {
                  detailScreen.setSystem(*sys);
                }
			}
		}
        window.clear();
        bezirk->draw(window,topLeft, dx,dy, dw, h, a,font, selected.data(), dim.data());
        detailScreen.draw(window);
        window.display();
	}
	return 0;
}

