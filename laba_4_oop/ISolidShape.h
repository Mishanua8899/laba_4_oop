#pragma once
#include "IShape.h"
class ISolidShape : public IShape
{
public:
    virtual ~ISolidShape() = default;
    virtual uint32_t GetFillColor() const { return fillColor; };
protected:
    uint32_t fillColor;
};
