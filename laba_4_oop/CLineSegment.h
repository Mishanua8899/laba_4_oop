#pragma once
#include "IShape.h"
#include "CPoint.h"
#include "ICanvasDrawable.h"
#include "SFML/Graphics.hpp"
class CLineSegment : public IShape, public ICanvasDrawable
{
public:
    CLineSegment(CPoint startPoint, CPoint endPoint, uint32_t outlineColor);
    double GetArea() const override;
    double GetPerimeter() const override;
    std::string ToString() const override;
    std::string GetShapeType() const override;

    void Draw(ICanvas& canvas) const override;

    CPoint GetStartPoint() const;
    CPoint GetEndPoint() const;

private:
    CPoint startPoint;
    CPoint endPoint;

    mutable sf::VertexArray line;
};


