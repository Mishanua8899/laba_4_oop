#include "CTriangle.h"
#include "Constants.h"
#include "SFML/Graphics.hpp"
#include "SFMLTriangleAdapter.h"
#include <cmath>
#include <iomanip>
#include <sstream>

double roundToHundredths(double value);

CTriangle::CTriangle(CPoint vertex1, CPoint vertex2, CPoint vertex3, uint32_t outlineColor, uint32_t fillColor)
{
	this->vertex1 = vertex1;
	this->vertex2 = vertex2;
	this->vertex3 = vertex3;

	this->outlineColor = outlineColor;
	this->fillColor = fillColor;
}

double CTriangle::GetArea() const
{
	double result = 0.5 * std::abs((vertex2.x - vertex1.x) * (vertex3.y - vertex1.y) - (vertex3.x - vertex1.x) * (vertex2.y - vertex1.y));
	return roundToHundredths(result);
}

double CTriangle::GetPerimeter() const
{
	double side1 = std::pow(std::pow((vertex2.x - vertex1.x), 2) + std::pow((vertex2.y - vertex1.y), 2), 0.5);
	double side2 = std::pow(std::pow((vertex3.x - vertex2.x), 2) + std::pow((vertex3.y - vertex2.y), 2), 0.5);
	double side3 = std::pow(std::pow((vertex3.x - vertex1.x), 2) + std::pow((vertex3.y - vertex1.y), 2), 0.5);

	return roundToHundredths(side1 + side2 + side3);
}

/*uint32_t CTriangle::GetOutlineColor() const
{
	return outlineColor;
}

uint32_t CTriangle::GetFillColor() const
{
	return fillColor;
}*/

CPoint CTriangle::GetVertex1() const
{
	return vertex1;
}

CPoint CTriangle::GetVertex2() const
{
	return vertex2;
}

CPoint CTriangle::GetVertex3() const
{
	return vertex3;
}

std::string CTriangle::ToString() const
{
	std::ostringstream oss;
	oss << Constants::TYPE_TRIANGLE << ": " << Constants::VERTICES << " ("
		<< vertex1.x << ", " << vertex1.y << "), ("
		<< vertex2.x << ", " << vertex2.y << "), ("
		<< vertex3.x << ", " << vertex3.y << ")"
		<< Constants::AREA_INFO << GetArea()
		<< Constants::PERIMETR_INFO << GetPerimeter()
		<< Constants::OUTLINECOLOR_INFO << std::hex << std::setfill('0') << std::setw(Constants::HALFBITES_COUNT) << (outlineColor & Constants::RGBMask)
		<< Constants::FILLCOLOR_INFO << std::hex << std::setfill('0') << std::setw(Constants::HALFBITES_COUNT) << (fillColor & Constants::RGBMask);
	return oss.str();
}

std::string CTriangle::GetShapeType() const
{
	return Constants::TYPE_TRIANGLE;
}

bool CTriangle::IsInside(const CPoint& point) const
{

	auto sign = [](CPoint p1, CPoint p2, CPoint p3) {
		return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
	};

	float d1 = sign(point, vertex1, vertex2);
	float d2 = sign(point, vertex2, vertex3);
	float d3 = sign(point, vertex3, vertex1);

	bool hasNeg = (d1 < 0) || (d2 < 0) || (d3 < 0);
	bool hasPos = (d1 > 0) || (d2 > 0) || (d3 > 0);

	return !(hasNeg && hasPos);
}

sf::FloatRect CTriangle::GetBoundingBox() const
{
	float minX = std::min({ vertex1.x, vertex2.x, vertex3.x });
	float minY = std::min({ vertex1.y, vertex2.y, vertex3.y });
	float maxX = std::max({ vertex1.x, vertex2.x, vertex3.x });
	float maxY = std::max({ vertex1.y, vertex2.y, vertex3.y });
	return sf::FloatRect(sf::Vector2<float>(minX, minY), sf::Vector2<float>(maxX - minX, maxY - minY));
}

void CTriangle::Move(float dx, float dy)
{
	vertex1.x += dx;
	vertex1.y += dy;
	vertex2.x += dx;
	vertex2.y += dy;
	vertex3.x += dx;
	vertex3.y += dy;
}

std::unique_ptr<IShapeAdapter> CTriangle::CreateAdapter() const
{
	return std::make_unique<SFMLTriangleAdapter>();
}

/*void CTriangle::Draw(ICanvas& canvas) const {
	std::vector<CPoint> points = {vertex1, vertex2, vertex3};
	canvas.DrawPolygon(points, fillColor);
	canvas.DrawLine(vertex1, vertex2, outlineColor);
	canvas.DrawLine(vertex2, vertex3, outlineColor);
	canvas.DrawLine(vertex3, vertex1, outlineColor);


	std::vector<CPoint> vertexes{ vertex1, vertex2, vertex3 };
	sf::ConvexShape polygon;
	polygon.setPointCount(3);
	for (size_t i = 0; i < vertexes.size(); ++i)
	{
		polygon.setPoint(i, sf::Vector2f(static_cast<float>(vertexes[i].x), static_cast<float>(vertexes[i].y)));
	}

	sf::Color Fcolor((fillColor << 8) | 0x000000FF);
	sf::Color Ocolor((outlineColor << 8) | 0x000000FF);
	polygon.setFillColor(Fcolor);
	polygon.setOutlineThickness(1.f);
	polygon.setOutlineColor(Ocolor);

	canvas.Draw(polygon);
}*/
