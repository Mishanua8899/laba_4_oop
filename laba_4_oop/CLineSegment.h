#pragma once
#include "IShape.h"
#include "IShapeAdapter.h"
#include "CPoint.h"
#include "SFML/Graphics.hpp"
class CLineSegment : public IShape/*, public ICanvasDrawable*/
{
public:
    CLineSegment(CPoint startPoint, CPoint endPoint, uint32_t outlineColor);
    double GetArea() const override;
    double GetPerimeter() const override;
    std::string ToString() const override;
    std::string GetShapeType() const override;

    bool IsInside(const CPoint& point) const override;
    sf::FloatRect GetBoundingBox() const override;
    void Move(float dx, float dy) override;

    CPoint GetStartPoint() const;
    CPoint GetEndPoint() const;

    std::unique_ptr<IShapeAdapter> CreateAdapter() const;
private:
    CPoint startPoint;
    CPoint endPoint;
};


