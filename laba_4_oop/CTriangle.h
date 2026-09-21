#pragma once
#include "ISolidShape.h"
#include "CPoint.h"
#include "ICanvasDrawable.h"
#include "SFML/Graphics.hpp"
class CTriangle : public ISolidShape, public ICanvasDrawable
{
public:
    CTriangle(CPoint v1, CPoint v2, CPoint v3, uint32_t outlineColor, uint32_t fillColor);
    double GetArea() const override;
    double GetPerimeter() const override;
    std::string ToString() const override;
    std::string GetShapeType() const override;

    void Draw(ICanvas& canvas) const override;

    CPoint GetVertex1() const;
    CPoint GetVertex2() const;
    CPoint GetVertex3() const;

private:
    CPoint vertex1;
    CPoint vertex2;
    CPoint vertex3;

    mutable sf::ConvexShape triangle;
};