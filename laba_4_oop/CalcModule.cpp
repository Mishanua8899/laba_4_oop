#include "CalcModule.h"
#include <cmath>

double roundToHundredths(double value)
{
    return std::round(value * 100.0) / 100.0;
}

const IShape* MaxArea(const std::vector<std::unique_ptr<IShape>>& shapes)
{
    if (shapes.empty()) return nullptr;
    double maxArea = 0;
    const IShape* maxShape = shapes[0].get();
    for (const auto& shape : shapes)
    {
        double area = shape->GetArea();
        if (area > maxArea)
        {
            maxArea = area;
            maxShape = shape.get();
        }
    }
    return maxShape;
}

const IShape* MaxPerimeter(const std::vector<std::unique_ptr<IShape>>& shapes)
{
    if (shapes.empty()) return nullptr;
    double maxPerimeter = 0;
    const IShape* maxShape = shapes[0].get();
    for (const auto& shape : shapes)
    {
        double perimeter = shape->GetPerimeter(); 
        if (perimeter > maxPerimeter)
        {
            maxPerimeter = perimeter;
            maxShape = shape.get();
        }
    }
    return maxShape;
}