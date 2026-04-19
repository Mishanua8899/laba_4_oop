#pragma once

#include <vector>
#include <memory>
#include "SFML/Graphics.hpp"
#include "CCanvas.h"
#include "IShape.h"

void ShowPicture(sf::RenderWindow& window, CCanvas& canvas, std::vector<std::unique_ptr<IShape>>& shapes);