#pragma once
#include "CPoint.h"
#include "IShapeAdapter.h"
#include "SFML/Graphics.hpp"
#include <cstdint>
#include <memory>
#include <string>

class IShape
{
public:
	virtual ~IShape() = default;
	virtual double GetArea() const = 0;
	virtual double GetPerimeter() const = 0;
	virtual std::string ToString() const = 0;
	virtual uint32_t GetOutlineColor() const { return outlineColor; };
	virtual std::string GetShapeType() const = 0;

	virtual bool IsInside(const CPoint& point) const = 0;
	virtual sf::FloatRect GetBoundingBox() const = 0;
	virtual void Move(float dx, float dy) = 0;

	virtual bool IsComposite() const { return false; }

	virtual std::unique_ptr<IShapeAdapter> CreateAdapter() const = 0;

protected:
	uint32_t outlineColor;
};
