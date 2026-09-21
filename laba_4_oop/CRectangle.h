#pragma once
#include "ISolidShape.h"
#include "CPoint.h"
#include "ICanvasDrawable.h"
#include "SFML/Graphics.hpp"
class CRectangle : public ISolidShape, public ICanvasDrawable
{
public:
    CRectangle(CPoint leftTop, double width, double height, uint32_t outlineColor, uint32_t fillColor);
    double GetArea() const override;
    double GetPerimeter() const override;
    std::string ToString() const override;

    std::string GetShapeType() const override;

    void Draw(ICanvas& canvas) const override;

    CPoint GetLeftTop() const;
    CPoint GetRightBottom() const;   
    double GetWidth() const;
    double GetHeight() const;

private:
    CPoint leftTop;
    double width;
    double height;

    mutable sf::RectangleShape rectangle;
};