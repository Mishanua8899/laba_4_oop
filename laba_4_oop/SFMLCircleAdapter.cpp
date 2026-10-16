#include "SFMLCircleAdapter.h"
#include "CCircle.h"
#include "Constants.h"

void SFMLCircleAdapter::SyncWith(const IShape& shape)
{
	const auto* circle = dynamic_cast<const CCircle*>(&shape);
	if (!circle)
		return;

	this->shape.setRadius(circle->GetRadius());

	double centerX = circle->GetCenter().x - circle->GetRadius();
	double centerY = circle->GetCenter().y - circle->GetRadius();
	this->shape.setPosition(sf::Vector2f(static_cast<float>(centerX), static_cast<float>(centerY)));

	sf::Color Fcolor((circle->GetFillColor() << Constants::ALPHA_SHIFT) | Constants::ALPHA_SHIFT_MASK);
	sf::Color Ocolor((circle->GetOutlineColor() << Constants::ALPHA_SHIFT) | Constants::ALPHA_SHIFT_MASK);

	this->shape.setFillColor(Fcolor);
	this->shape.setOutlineThickness(1.f);
	this->shape.setOutlineColor(Ocolor);
}

const sf::Drawable& SFMLCircleAdapter::GetSFMLShape() const
{
	return this->shape;
}
