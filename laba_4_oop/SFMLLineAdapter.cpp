#include "SFMLLineAdapter.h"
#include "CLineSegment.h"
#include "Constants.h"
void SFMLLineAdapter::SyncWith(const IShape& shape)
{
	const auto* line = dynamic_cast<const CLineSegment*>(&shape);
	if (!line)
		return;

	this->shape.setPrimitiveType(sf::PrimitiveType::Lines);
	sf::Vertex startVertex;
	startVertex.position = sf::Vector2f(static_cast<float>(line->GetStartPoint().x), static_cast<float>(line->GetStartPoint().y));
	startVertex.color = sf::Color((line->GetOutlineColor() << Constants::ALPHA_SHIFT) | Constants::ALPHA_SHIFT_MASK);

	sf::Vertex endVertex;
	endVertex.position = sf::Vector2f(static_cast<float>(line->GetEndPoint().x), static_cast<float>(line->GetEndPoint().y));
	endVertex.color = sf::Color((line->GetOutlineColor() << Constants::ALPHA_SHIFT) | Constants::ALPHA_SHIFT_MASK);

	this->shape.append(startVertex);
	this->shape.append(endVertex);
}

const sf::Drawable& SFMLLineAdapter::GetSFMLShape() const
{
	return this->shape;
}
