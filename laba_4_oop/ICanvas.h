#pragma once
#include <vector>
#include <cstdint>
#include "CPoint.h"
#include "SFML/Graphics.hpp"
class ICanvas
{
public:
	virtual ~ICanvas() = default;
	virtual void Draw(const sf::Drawable& figure) = 0;
};