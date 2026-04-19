#pragma once

class CPoint
{
public:
    double x = 0;
    double y = 0;

    CPoint() = default;
    CPoint(double xVal, double yVal) : x(xVal), y(yVal) {}
    bool operator==(const CPoint other) const
    {
        return x == other.x && y == other.y;
    }
};

