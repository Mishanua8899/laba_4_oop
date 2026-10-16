#pragma once
#include "ISolidShape.h"
#include "IShapeAdapter.h"
#include "CPoint.h"
#include "SFML/Graphics.hpp"
class CTriangle : public ISolidShape
{
public:
    CTriangle(CPoint v1, CPoint v2, CPoint v3, uint32_t outlineColor, uint32_t fillColor);
    double GetArea() const override;
    double GetPerimeter() const override;
    std::string ToString() const override;
    std::string GetShapeType() const override;

    bool IsInside(const CPoint& point) const override;
    sf::FloatRect GetBoundingBox() const override;
    void Move(float dx, float dy) override;

    CPoint GetVertex1() const;
    CPoint GetVertex2() const;
    CPoint GetVertex3() const;

    std::unique_ptr<IShapeAdapter> CreateAdapter() const;
private:
    CPoint vertex1;
    CPoint vertex2;
    CPoint vertex3;
};