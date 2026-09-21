#include <cmath>
#include <sstream>
#include <iomanip>
#include "CCircle.h"
#include "CalcModule.h"
constexpr double PI = 3.14;

CCircle::CCircle(CPoint center, double radius, uint32_t outlineColor, uint32_t fillColor)
{
    this->center = center;
    this->radius = radius;
    this->outlineColor = outlineColor;
    this->fillColor = fillColor;
}

double CCircle::GetArea() const
{
    double result = PI * radius * radius;
    return roundToHundredths(result);
}

double CCircle::GetPerimeter() const
{
    double result = 2 * PI * radius;
    return roundToHundredths(result);
}

std::string CCircle::ToString() const
{
    std::ostringstream oss;
    oss << "circle: center (" << center.x << ", " << center.y << ")"
        << ", radius=" << radius
        << ", area=" << GetArea()
        << ", perimeter=" << GetPerimeter()
        << ", outlineColor=#" << std::hex << std::setfill('0') << std::setw(6) << (outlineColor & 0xFFFFFF)
        << ", fillColor=#" << std::hex << std::setfill('0') << std::setw(6) << (fillColor & 0xFFFFFF);
    return oss.str();
}

std::string CCircle::GetShapeType() const
{
    return "circle";
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

void CCircle::Draw(ICanvas& canvas) const {

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
}

