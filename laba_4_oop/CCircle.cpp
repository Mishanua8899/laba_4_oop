#include "CCircle.h"
#include "Constants.h"
#include "SFMLCircleAdapter.h"
#include <cmath>
#include <iomanip>
#include <sstream>

double roundToHundredths(double value)
{
	return std::round(value * 100.0) / 100.0;
}

CCircle::CCircle(CPoint center, double radius, uint32_t outlineColor, uint32_t fillColor)
{
	this->center = center;
	this->radius = radius;
	this->outlineColor = outlineColor;
	this->fillColor = fillColor;
}

double CCircle::GetArea() const
{
	double result = Constants::PI * radius * radius;
	return roundToHundredths(result);
}

double CCircle::GetPerimeter() const
{
	double result = 2 * Constants::PI * radius;
	return roundToHundredths(result);
}

std::string CCircle::ToString() const
{
	std::ostringstream oss;
	oss << Constants::TYPE_CIRCLE << ": center (" << center.x << ", " << center.y << ")"
		<< ", radius=" << radius
		<< Constants::AREA_INFO << GetArea()
		<< Constants::PERIMETR_INFO << GetPerimeter()
		<< Constants::OUTLINECOLOR_INFO << std::hex << std::setfill('0') << std::setw(Constants::HALFBITES_COUNT) << (outlineColor & Constants::RGBMask)
		<< Constants::FILLCOLOR_INFO << std::hex << std::setfill('0') << std::setw(Constants::HALFBITES_COUNT) << (fillColor & Constants::RGBMask);
	return oss.str();
}

std::string CCircle::GetShapeType() const
{
	return Constants::TYPE_CIRCLE;
}

/*uint32_t CCircle::GetOutlineColor() const
{
	return outlineColor;
}*/

/*uint32_t CCircle::GetFillColor() const
{
	return fillColor;
}*/

CPoint CCircle::GetCenter() const
{
	return center;
}

double CCircle::GetRadius() const
{
	return radius;
}

sf::FloatRect CCircle::GetBoundingBox() const
{
	float left = center.x - radius;
	float top = center.y - radius;
	float width = 2 * radius;
	float height = 2 * radius;

	return sf::FloatRect(sf::Vector2(left, top), sf::Vector2(width, height));
}

bool CCircle::IsInside(const CPoint& point) const
{
	float dx = point.x - center.x;
	float dy = point.y - center.y;
	return (dx * dx + dy * dy) <= (radius * radius);
}

void CCircle::Move(float dx, float dy)
{
	center.x += dx;
	center.y += dy;
}

std::unique_ptr<IShapeAdapter> CCircle::CreateAdapter() const
{
	return std::make_unique<SFMLCircleAdapter>();
}

/*void CCircle::Draw(ICanvas& canvas) const {

	circle.setRadius(radius);

	double centerX = center.x - radius;
	double centerY = center.y - radius;
	circle.setPosition(sf::Vector2f(static_cast<float>(centerX), static_cast<float>(centerY)));

	sf::Color Fcolor((fillColor << 8) | 0x000000FF);
	sf::Color Ocolor((outlineColor << 8) | 0x000000FF);
	circle.setFillColor(Fcolor);
	circle.setOutlineThickness(1.f);
	circle.setOutlineColor(Ocolor);

	canvas.Draw(circle);
}*/
