#include "CompositeShape.h"
#include "Constants.h"

void CompositeShape::AddChild(std::unique_ptr<IShape> child)
{
	children.push_back(std::move(child));
}

std::vector<std::unique_ptr<IShape>> CompositeShape::ExtractChildren()
{
	std::vector<std::unique_ptr<IShape>> result = std::move(children);
	children.clear();
	return result;
}

bool CompositeShape::IsInside(const CPoint& point) const
{
	return std::any_of(children.begin(), children.end(),
		[&](const auto& child) {
			return child->IsInside(point);
		});
}

sf::FloatRect CompositeShape::GetBoundingBox() const
{
	if (children.empty())
		return sf::FloatRect();

	sf::FloatRect bounds = children[0]->GetBoundingBox();
	for (size_t i = 1; i < children.size(); ++i)
	{
		sf::FloatRect childBounds = children[i]->GetBoundingBox();
		float left = std::min(bounds.position.x, childBounds.position.x);
		float top = std::min(bounds.position.y, childBounds.position.y);
		float right = std::max(bounds.position.x + bounds.size.x, childBounds.position.x + childBounds.size.x);
		float bottom = std::max(bounds.position.y + bounds.size.y, childBounds.position.y + childBounds.size.y);
		bounds = sf::FloatRect(sf::Vector2(left, top), sf::Vector2(right - left, bottom - top));
	}
	return bounds;
}

std::string CompositeShape::ToString() const
{
	return "Composite Shape (" + std::to_string(children.size()) + " items)";
}

void CompositeShape::Move(float dx, float dy)
{
	for (auto& child : children)
	{
		child->Move(dx, dy);
	}
}

double CompositeShape::GetArea() const
{
	double area = 0;
	for (const auto& c : children)
		area += c->GetArea();
	return area;
}

std::string CompositeShape::GetShapeType() const
{
	return Constants::TYPE_COMPOSITE;
}

double CompositeShape::GetPerimeter() const
{
	return 0;
}

bool CompositeShape::IsComposite() const
{
	return true;
}

const std::vector<std::unique_ptr<IShape>>& CompositeShape::GetChildren() const
{
	return children;
}