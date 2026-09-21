#pragma once
#include "SFML/Graphics.hpp"
#include "ICanvas.h"
class CCanvas : public ICanvas
{
public:
	CCanvas(sf::RenderWindow& window);
	void Draw(const sf::Drawable& figure) override;
private: 
	sf::RenderWindow& window;
};
