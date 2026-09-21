#include <sstream>
#include <iomanip>
#include "CRectangle.h"
#include "CalcModule.h"

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
    oss << "rectangle: left top (" << leftTop.x << ", " << leftTop.y << ")"
        << ", width=" << width
        << ", height=" << height
        << ", area=" << GetArea()
        << ", perimeter=" << GetPerimeter()
        << ", outlineColor=#" << std::hex << std::setfill('0') << std::setw(6) << (outlineColor & 0xFFFFFF)
        << ", fillColor=#" << std::hex << std::setfill('0') << std::setw(6) << (fillColor & 0xFFFFFF);
    return oss.str();
}

std::string CRectangle::GetShapeType() const
{
    return "rectangle";
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

void CRectangle::Draw(ICanvas& canvas) const {
    /*CPoint rightTop(leftTop.x + width, leftTop.y);
    CPoint rightBottom(leftTop.x + width, leftTop.y + height);
    CPoint leftBottom(leftTop.x, leftTop.y + height);
    std::vector<CPoint> points = { leftTop, rightTop, rightBottom, leftBottom };
    canvas.DrawPolygon(points, fillColor);
    canvas.DrawLine(leftTop, rightTop, outlineColor);
    canvas.DrawLine(rightTop, rightBottom, outlineColor);
    canvas.DrawLine(rightBottom, leftBottom, outlineColor);
    canvas.DrawLine(leftBottom, leftTop, outlineColor);*/

    rectangle.setSize({ static_cast<float>(width), static_cast<float>(height) });

    sf::Color Fcolor((fillColor << 8) | 0x000000FF);
    sf::Color Ocolor((outlineColor << 8) | 0x000000FF);
    rectangle.setFillColor(Fcolor);
    rectangle.setOutlineThickness(1.f);
    rectangle.setOutlineColor(Ocolor);

    rectangle.setPosition({ static_cast<float>(leftTop.x), static_cast<float>(leftTop.y) });

    canvas.Draw(rectangle);
}