#include "Drawing.h"
#include "Constants.h"
#include <string>

CompositeDrawing::CompositeDrawing(std::vector<std::unique_ptr<IShape>> shapes)
{
	this->shapes = std::move(shapes);
}

void CompositeDrawing::PushShape(std::unique_ptr<IShape> shape)
{
	if (shape)
	{
		shapes.push_back(std::move(shape));
	}
}

std::size_t CompositeDrawing::GetCountShapes() const noexcept
{
	return shapes.size();
}

const IShape* CompositeDrawing::GetShape(std::size_t index) const
{
	if (index >= shapes.size())
	{
		throw std::out_of_range(Constants::OUT_OF_RANGE_MESSAGE_DRAWING);
	}
	return shapes[index].get();
}

IShape* CompositeDrawing::GetShape(std::size_t index)
{
	if (index >= shapes.size())
	{
		throw std::out_of_range(Constants::OUT_OF_RANGE_MESSAGE_DRAWING);
	}
	return shapes[index].get();
}

std::unique_ptr<IShape> CompositeDrawing::ExtractShape(const IShape* shapePtr)
{
	for (auto it = shapes.begin(); it != shapes.end(); ++it)
	{
		if (it->get() == shapePtr)
		{
			std::unique_ptr<IShape> extracted = std::move(*it);
			shapes.erase(it);
			return extracted;
		}
	}
	return nullptr;
}