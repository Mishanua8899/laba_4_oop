#include "CCanvas.h"

CCanvas::CCanvas(sf::RenderWindow& window) : window(window) {}

void CCanvas::DrawLine(CPoint from, CPoint to, uint32_t lineColor)
{
	sf::VertexArray line(sf::PrimitiveType::Lines, 2);
	sf::Color color((lineColor << 8) | 0x000000FF);

	line[0].position = sf::Vector2f(static_cast<float>(from.x), static_cast<float>(from.y));
	line[0].color = color;

	line[1].position = sf::Vector2f(static_cast<float>(to.x), static_cast<float>(to.y));
	line[1].color = color;

	window.draw(line);
}

void CCanvas::DrawCircle(CPoint center, double radius, uint32_t lineColor)
{
	sf::CircleShape circle(static_cast<float>(radius));
	//circleþ(sf::Vector2(static_cast<float>(center.x), static_cast<float>(center.y)));
	double centerX = center.x - radius;
	double centerY = center.y - radius;
	circle.setPosition(sf::Vector2f(static_cast<float>(centerX), static_cast<float>(centerY)));
	circle.setFillColor(sf::Color::Transparent);
	circle.setOutlineThickness(1.0f);

	sf::Color color((lineColor << 8) | 0x000000FF);
	circle.setOutlineColor(color);
	window.draw(circle);
}

void CCanvas::FillCircle(CPoint center, double radius, uint32_t fillColor)
{
	sf::CircleShape circle(static_cast<float>(radius));
	double centerX = center.x - radius;
	double centerY = center.y - radius;
	circle.setPosition(sf::Vector2f(static_cast<float>(centerX), static_cast<float>(centerY)));
	sf::Color color((fillColor << 8) | 0x000000FF);
	circle.setFillColor(color);
	circle.setOutlineThickness(0.f);

	window.draw(circle);
}

void CCanvas::FillPolygon(std::vector<CPoint> points, uint32_t fillColor)
{
	if (points.size() < 3) return; 

	sf::ConvexShape polygon;
	polygon.setPointCount(points.size());
	for (size_t i = 0; i < points.size(); ++i)
	{
		polygon.setPoint(i, sf::Vector2f(static_cast<float>(points[i].x), static_cast<float>(points[i].y)));
	}

	sf::Color color((fillColor << 8) | 0x000000FF);
	polygon.setFillColor(color);
	polygon.setOutlineThickness(0.f); 

	window.draw(polygon);
}