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
    canvas.DrawCircle(center, radius, outlineColor);
    canvas.FillCircle(center, radius, fillColor);
}

