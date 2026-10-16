#include "SFMLRectangleAdapter.h"
#include "CRectangle.h"
#include "Constants.h"
void SFMLRectangleAdapter::SyncWith(const IShape& shape)
{
	const auto* rect = dynamic_cast<const CRectangle*>(&shape);
	if (!rect)
		return;
	this->shape.setSize({ static_cast<float>(rect->GetWidth()), static_cast<float>(rect->GetHeight()) });
	this->shape.setPosition({ static_cast<float>(rect->GetLeftTop().x), static_cast<float>(rect->GetLeftTop().y) });

	sf::Color Fcolor((rect->GetFillColor() << Constants::ALPHA_SHIFT) | Constants::ALPHA_SHIFT_MASK);
	sf::Color Ocolor((rect->GetOutlineColor() << Constants::ALPHA_SHIFT) | Constants::ALPHA_SHIFT_MASK);

	this->shape.setFillColor(Fcolor);
	this->shape.setOutlineThickness(1.f);
	this->shape.setOutlineColor(Ocolor);
}

const sf::Drawable& SFMLRectangleAdapter::GetSFMLShape() const
{
	return this->shape;
}
