#include "CRectangle.h"
#include "Constants.h"
#include "SFMLRectangleAdapter.h"
#include <iomanip>
#include <sstream>

double roundToHundredths(double value);

CRectangle::CRectangle(CPoint leftTop, double width, double height, uint32_t outlineColor, uint32_t fillColor)
{
	this->leftTop = leftTop;
	this->width = width;
	this->height = height;

	this->outlineColor = outlineColor;
	this->fillColor = fillColor;
}

double CRectangle::GetArea() const
{
	double result = width * height;
	return roundToHundredths(result);
}

double CRectangle::GetPerimeter() const
{
	double result = 2 * (width + height);
	return roundToHundredths(result);
}

std::string CRectangle::ToString() const
{
	std::ostringstream oss;
	oss << Constants::TYPE_RECTANGLE << ":" << Constants::POINT_POS << "(" << leftTop.x << ", " << leftTop.y << ")"
		<< Constants::WIDTH_INFO << width
		<< Constants::HEIGHT_INFO << height
		<< Constants::AREA_INFO << GetArea()
		<< Constants::PERIMETR_INFO << GetPerimeter()
		<< Constants::OUTLINECOLOR_INFO << std::hex << std::setfill('0') << std::setw(Constants::HALFBITES_COUNT) << (outlineColor & Constants::RGBMask)
		<< Constants::FILLCOLOR_INFO << std::hex << std::setfill('0') << std::setw(Constants::HALFBITES_COUNT) << (fillColor & Constants::RGBMask);
	return oss.str();
}

std::string CRectangle::GetShapeType() const
{
	return Constants::TYPE_RECTANGLE;
}

/*uint32_t CRectangle::GetOutlineColor() const
{
	return outlineColor;
}

uint32_t CRectangle::GetFillColor() const
{
	return fillColor;
}*/

CPoint CRectangle::GetLeftTop() const
{
	return leftTop;
}

CPoint CRectangle::GetRightBottom() const
{
	return CPoint(leftTop.x + width, leftTop.y + height);
}

double CRectangle::GetWidth() const
{
	return width;
}

double CRectangle::GetHeight() const
{
	return height;
}

bool CRectangle::IsInside(const CPoint& point) const
{
	bool isInsideX = (point.x >= GetLeftTop().x && point.x <= GetRightBottom().x);
	bool isInsideY = (point.y >= GetLeftTop().y && point.y <= GetRightBottom().y);

	return isInsideX && isInsideY;
}

sf::FloatRect CRectangle::GetBoundingBox() const
{
	float left = std::min(leftTop.x, GetRightBottom().x);
	float top = std::min(leftTop.y, GetRightBottom().y);
	float width = std::abs(GetRightBottom().x - leftTop.x);
	float height = std::abs(GetRightBottom().y - leftTop.y);

	return sf::FloatRect(sf::Vector2(left, top), sf::Vector2(width, height));
}

void CRectangle::Move(float dx, float dy)
{
	leftTop.x += dx;
	leftTop.y += dy;
}

std::unique_ptr<IShapeAdapter> CRectangle::CreateAdapter() const
{
	return std::make_unique<SFMLRectangleAdapter>();
}

/*void CRectangle::Draw(ICanvas& canvas) const {
	CPoint rightTop(leftTop.x + width, leftTop.y);
	CPoint rightBottom(leftTop.x + width, leftTop.y + height);
	CPoint leftBottom(leftTop.x, leftTop.y + height);
	std::vector<CPoint> points = { leftTop, rightTop, rightBottom, leftBottom };
	canvas.DrawPolygon(points, fillColor);
	canvas.DrawLine(leftTop, rightTop, outlineColor);
	canvas.DrawLine(rightTop, rightBottom, outlineColor);
	canvas.DrawLine(rightBottom, leftBottom, outlineColor);
	canvas.DrawLine(leftBottom, leftTop, outlineColor);

	rectangle.setSize({ static_cast<float>(width), static_cast<float>(height) });

	sf::Color Fcolor((fillColor << 8) | 0x000000FF);
	sf::Color Ocolor((outlineColor << 8) | 0x000000FF);
	rectangle.setFillColor(Fcolor);
	rectangle.setOutlineThickness(1.f);
	rectangle.setOutlineColor(Ocolor);

	rectangle.setPosition({ static_cast<float>(leftTop.x), static_cast<float>(leftTop.y) });

	canvas.Draw(rectangle);
}*/