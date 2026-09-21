#include <cmath>
#include <iomanip>
#include <sstream>
#include "CTriangle.h"
#include "CalcModule.h"

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
    oss << "triangle: vertices ("
        << vertex1.x << ", " << vertex1.y << "), ("
        << vertex2.x << ", " << vertex2.y << "), ("
        << vertex3.x << ", " << vertex3.y << ")"
        << ", area=" << GetArea()
        << ", perimeter=" << GetPerimeter()
        << ", outlineColor=#" << std::hex << std::setfill('0') << std::setw(6) << (outlineColor & 0xFFFFFF)
        << ", fillColor=#" << std::hex << std::setfill('0') << std::setw(6) << (fillColor & 0xFFFFFF);
    return oss.str();
}

std::string CTriangle::GetShapeType() const
{
    return "triangle";
}

void CTriangle::Draw(ICanvas& canvas) const {
    /*std::vector<CPoint> points = {vertex1, vertex2, vertex3};
    canvas.DrawPolygon(points, fillColor);
    canvas.DrawLine(vertex1, vertex2, outlineColor);
    canvas.DrawLine(vertex2, vertex3, outlineColor);
    canvas.DrawLine(vertex3, vertex1, outlineColor);*/
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
}