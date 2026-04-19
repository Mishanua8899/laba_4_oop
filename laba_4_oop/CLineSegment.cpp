#include <cmath>
#include <sstream>
#include <iomanip>
#include "CLineSegment.h"
#include "CalcModule.h"
CLineSegment::CLineSegment(CPoint startPoint, CPoint endPoint, uint32_t outlineColor)
{
    this->endPoint = endPoint;
    this->startPoint = startPoint;

	this->outlineColor = outlineColor;
}

double CLineSegment::GetArea() const
{
	return 0.0;
}

double CLineSegment::GetPerimeter() const
{
    double result = std::hypot(endPoint.x - startPoint.x, endPoint.y - startPoint.y);
	return roundToHundredths(result);
}

/*uint32_t CLineSegment::GetOutlineColor() const
{
    return outlineColor;
}*/

CPoint CLineSegment::GetStartPoint() const
{
    return startPoint;
}

CPoint CLineSegment::GetEndPoint() const
{
    return endPoint;
}

std::string CLineSegment::ToString() const
{
    std::ostringstream oss;
    oss << "line: start (" << startPoint.x << ", " << startPoint.y << ")"
        << ", end (" << endPoint.x << ", " << endPoint.y << ")"
        << ", area=" << GetArea()
        << ", perimeter=" << GetPerimeter()
        << ", outlineColor=#" << std::hex << std::setfill('0') << std::setw(6) << (outlineColor & 0xFFFFFF);
    return oss.str();
}

std::string CLineSegment::GetShapeType() const
{
    return "line";
}

void CLineSegment::Draw(ICanvas& canvas) const {
    canvas.DrawLine(startPoint, endPoint, outlineColor);
}
