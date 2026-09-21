#pragma once
#include "ISolidShape.h"
#include "CPoint.h"
#include "ICanvasDrawable.h"
#include "SFML/Graphics.hpp"
class CCircle : public ISolidShape, public ICanvasDrawable
{
public:
    CCircle(CPoint center, double radius, uint32_t outlineColor, uint32_t fillColor);
    double GetArea() const override;
    double GetPerimeter() const override;
    std::string ToString() const override;
    std::string GetShapeType() const override;

    void Draw(ICanvas& canvas) const override;

    CPoint GetCenter() const;
    double GetRadius() const;

private:
    CPoint center;
    double radius;

    mutable sf::CircleShape circle;
};