#pragma once
#include "ISolidShape.h"
#include "IShapeAdapter.h"
#include "CPoint.h"
#include "SFML/Graphics.hpp"
class CRectangle : public ISolidShape
{
public:
    CRectangle(CPoint leftTop, double width, double height, uint32_t outlineColor, uint32_t fillColor);
    double GetArea() const override;
    double GetPerimeter() const override;
    std::string ToString() const override;

    std::string GetShapeType() const override;

    bool IsInside(const CPoint& point) const override;
    sf::FloatRect GetBoundingBox() const override;
    void Move(float dx, float dy) override;

    CPoint GetLeftTop() const;
    CPoint GetRightBottom() const;   
    double GetWidth() const;
    double GetHeight() const;

    std::unique_ptr<IShapeAdapter> CreateAdapter() const;
private:
    CPoint leftTop;
    double width;
    double height;
};