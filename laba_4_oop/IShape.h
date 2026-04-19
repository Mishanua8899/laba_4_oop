#pragma once
#include <string>
#include <cstdint>
#include "ICanvasDrawable.h"
class IShape : public ICanvasDrawable
{
public:
    virtual ~IShape() = default;
    virtual double GetArea() const = 0;
    virtual double GetPerimeter() const = 0;
    virtual std::string ToString() const = 0;
    virtual uint32_t GetOutlineColor() const { return outlineColor; };
    virtual std::string GetShapeType() const = 0;
protected:
    uint32_t outlineColor;
};

