#include "SelectionManager.h"

void SelectionManager::HandleMouseClick(const CPoint& clickPos, bool isShiftPressed)
{
	IShape* clickedShape = FindShapeAt(clickPos);

	if (clickedShape)
	{
		if (isShiftPressed)
		{
			if (selectedShapes.count(clickedShape))
			{
				selectedShapes.erase(clickedShape);
			}
			else
			{
				selectedShapes.insert(clickedShape);
			}
		}
		else
		{
			selectedShapes.clear();
			selectedShapes.insert(clickedShape);
		}
		StartDrag(clickPos);
	}
	else
	{
		if (!isShiftPressed)
		{
			selectedShapes.clear();
		}
	}
}

void SelectionManager::HandleMouseMove(const CPoint& currentPos)
{
	if (isDragging && !selectedShapes.empty())
	{
		float dx = currentPos.x - lastMousePos.x;
		float dy = currentPos.y - lastMousePos.y;
		for (auto* shape : selectedShapes)
		{
			shape->Move(dx, dy);
		}
		lastMousePos = currentPos;
	}
}

void SelectionManager::HandleMouseRelease()
{
	isDragging = false;
}

void SelectionManager::GroupSelected()
{
	if (selectedShapes.size() < 2)
		return;

	auto composite = std::make_unique<CompositeShape>();
	std::vector<IShape*> toRemove(selectedShapes.begin(), selectedShapes.end());

	for (auto* shapePtr : toRemove)
	{
		auto extracted = drawing.ExtractShape(shapePtr);
		if (extracted)
		{
			composite->AddChild(std::move(extracted));
		}
	}

	drawing.PushShape(std::move(composite));
	selectedShapes.clear();
	selectedShapes.insert(drawing.GetShape(drawing.GetCountShapes() - 1));
}

void SelectionManager::UngroupSelected()
{
	if (selectedShapes.size() != 1)
		return;

	IShape* selected = *selectedShapes.begin();
	if (!selected->IsComposite())
		return;

	auto compositePtr = dynamic_cast<CompositeShape*>(selected);
	auto extractedComposite = drawing.ExtractShape(selected);

	if (extractedComposite)
	{
		auto children = compositePtr->ExtractChildren();
		selectedShapes.clear();
		for (auto& child : children)
		{
			IShape* childPtr = child.get();
			drawing.PushShape(std::move(child));
			selectedShapes.insert(childPtr);
		}
	}
}

sf::FloatRect SelectionManager::GetSelectionBounds()
{
	if (selectedShapes.empty())
		return sf::FloatRect();
	auto it = selectedShapes.begin();
	sf::FloatRect bounds = (*it)->GetBoundingBox();
	++it;
	for (; it != selectedShapes.end(); ++it)
	{
		sf::FloatRect childBounds = (*it)->GetBoundingBox();
		float left = std::min(bounds.position.x, childBounds.position.x);
		float top = std::min(bounds.position.y, childBounds.position.y);
		float right = std::max(bounds.position.x + bounds.size.x, childBounds.position.x + childBounds.size.x);
		float bottom = std::max(bounds.position.y + bounds.size.y, childBounds.position.y + childBounds.size.y);
		bounds = sf::FloatRect(sf::Vector2(left, top), sf::Vector2(right - left, bottom - top));
	}
	return bounds;
}

const std::set<IShape*>& SelectionManager::GetSelectedShapes()
{
	return selectedShapes;
}

void SelectionManager::StartDrag(const CPoint& pos)
{
	isDragging = true;
	lastMousePos = pos;
}

IShape* SelectionManager::FindShapeAt(const CPoint& point)
{
	for (int i = drawing.GetCountShapes() - 1; i >= 0; --i)
	{
		IShape* shape = drawing.GetShape(i);
		if (shape->IsInside(point))
			return shape;
	}
	return nullptr;
}
