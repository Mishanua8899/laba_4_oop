#pragma once
#include "ISolidShape.h"
#include "IShapeAdapter.h"
#include "CPoint.h"
#include "SFML/Graphics.hpp"
class CCircle : public ISolidShape
{
public:
    CCircle(CPoint center, double radius, uint32_t outlineColor, uint32_t fillColor);
    double GetArea() const override;
    double GetPerimeter() const override;
    std::string ToString() const override;
    std::string GetShapeType() const override;

    //void Draw(ICanvas& canvas) const override;

    bool IsInside(const CPoint& point) const override;
    sf::FloatRect GetBoundingBox() const override;
    void Move(float dx, float dy) override;

    CPoint GetCenter() const;
    double GetRadius() const;

    std::unique_ptr<IShapeAdapter> CreateAdapter() const;

private:
    CPoint center;
    double radius;

    //mutable sf::CircleShape circle;
};