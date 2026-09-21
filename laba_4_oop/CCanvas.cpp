#include "CCanvas.h"

CCanvas::CCanvas(sf::RenderWindow& window) : window(window) {}

void CCanvas::Draw(const sf::Drawable& figure) {
	window.draw(figure);
}
