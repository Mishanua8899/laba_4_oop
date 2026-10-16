#include "CLineSegment.h"
#include "Constants.h"
#include "SFMLLineAdapter.h"
#include <cmath>
#include <iomanip>
#include <sstream>

double roundToHundredths(double value);

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
	oss << Constants::TYPE_LINE << ":" << Constants::START_POINT << "(" << startPoint.x << ", " << startPoint.y << ")"
		<< ", " << Constants::END_POINT << " (" << endPoint.x << ", " << endPoint.y << ")"
		<< Constants::AREA_INFO << GetArea()
		<< Constants::PERIMETR_INFO << GetPerimeter()
		<< Constants::OUTLINECOLOR_INFO << std::hex << std::setfill('0') << std::setw(Constants::HALFBITES_COUNT) << (outlineColor & Constants::RGBMask);
	return oss.str();
}

std::string CLineSegment::GetShapeType() const
{
	return Constants::TYPE_LINE;
}

sf::FloatRect CLineSegment::GetBoundingBox() const
{
	// Ограничивающий прямоугольник строится по минимальным и максимальным координатам концов отрезка
	float left = std::min(startPoint.x, endPoint.x);
	float top = std::min(startPoint.y, endPoint.y);
	float width = std::abs(startPoint.x - endPoint.x);
	float height = std::abs(startPoint.y - endPoint.y);

	return sf::FloatRect(sf::Vector2(left, top), sf::Vector2(width, height));
}

void CLineSegment::Move(float dx, float dy)
{
	startPoint.x += dx;
	startPoint.y += dy;
	endPoint.x += dx;
	endPoint.y += dy;
}

bool CLineSegment::IsInside(const CPoint& point) const
{

	const float selectionThreshold = 5.0f;
	const float thresholdSq = selectionThreshold * selectionThreshold;

	float dx = endPoint.x - startPoint.x;
	float dy = endPoint.y - startPoint.y;

	float lengthSq = dx * dx + dy * dy;

	if (lengthSq == 0.0f)
	{
		float distSq = (point.x - startPoint.x) * (point.x - startPoint.x) + (point.y - startPoint.y) * (point.y - startPoint.y);
		return distSq <= thresholdSq;
	}

	float t = ((point.x - startPoint.x) * dx + (point.y - startPoint.y) * dy) / lengthSq;

	t = std::max(0.0f, std::min(1.0f, t));

	float closestX = startPoint.x + t * dx;
	float closestY = startPoint.y + t * dy;

	float distSq = (point.x - closestX) * (point.x - closestX) + (point.y - closestY) * (point.y - closestY);

	return distSq <= thresholdSq;
}

std::unique_ptr<IShapeAdapter> CLineSegment::CreateAdapter() const
{
	return std::make_unique<SFMLLineAdapter>();
}

/*void CLineSegment::Draw(ICanvas& canvas) const {
	line.setPrimitiveType(sf::PrimitiveType::Lines);

	sf::Vertex startVertex;
	startVertex.position = sf::Vector2f(static_cast<float>(startPoint.x), static_cast<float>(startPoint.y));
	startVertex.color = sf::Color((outlineColor << 8) | 0x000000FF);

	sf::Vertex endVertex;
	endVertex.position = sf::Vector2f(static_cast<float>(endPoint.x), static_cast<float>(endPoint.y));
	endVertex.color = sf::Color((outlineColor << 8) | 0x000000FF);

	line.append(startVertex);
	line.append(endVertex);

	canvas.Draw(line);
}*/
