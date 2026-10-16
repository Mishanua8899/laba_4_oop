#include "ParseStringModule.h"
#include "ShapeController.h"

#include "Constants.h"
#include <fstream>
#include <iostream>

void ShapeController::PrintMaxShapesInfo(const IShape* maxPerimeterShape, const IShape* maxAreaShape) const
{
	std::cout << Constants::MAX_AREA << std::endl;
	std::cout << maxAreaShape->ToString() << std::endl;
	std::cout << Constants::MAX_PERIMETR << std::endl;
	std::cout << maxPerimeterShape->ToString() << std::endl;
}

bool ShapeController::Initialize(int argc, char* argv[])
{
	if (TryGetShape(argc, shapes, argv) != 0)
	{
		return false;
	}
	return true;
}

void ShapeController::ProcessAndExportInfo() const
{
	PrintStatistics();
	GenerateInfoFile(shapes);
}

std::vector<std::unique_ptr<IShape>> ShapeController::ExtractShapes()
{
	return std::move(shapes);
}

const IShape* ShapeController::FindMaxAreaShape() const
{
	return MaxArea(shapes);
}

const IShape* ShapeController::FindMaxPerimeterShape() const
{
	return MaxPerimeter(shapes);
}

void ShapeController::PrintStatistics() const
{
	const IShape* maxArea = FindMaxAreaShape();
	const IShape* maxPerimeter = FindMaxPerimeterShape();
	PrintMaxShapesInfo(maxPerimeter, maxArea);
}

void ShapeController::GenerateInfoFile(const std::vector<std::unique_ptr<IShape>>& drawableShapes, std::string fileName) const
{
	std::ofstream outFile(fileName);
	if (!outFile.is_open())
	{
		return;
	}

	for (const auto& shape : drawableShapes)
	{
		if (shape)
		{
			outFile << shape->ToString() << "\n";
		}
	}
}

double ShapeController::roundToHundredths(double value)
{
	return std::round(value * 100.0) / 100.0;
}

const IShape* ShapeController::MaxArea(const std::vector<std::unique_ptr<IShape>>& shapes) const
{
	if (shapes.empty())
		return nullptr;
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

const IShape* ShapeController::MaxPerimeter(const std::vector<std::unique_ptr<IShape>>& shapes) const
{
	if (shapes.empty())
		return nullptr;
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