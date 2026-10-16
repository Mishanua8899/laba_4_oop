#include "SFMLTriangleAdapter.h"
#include "Constants.h"
#include "CTriangle.h"
void SFMLTriangleAdapter::SyncWith(const IShape& shape) {
	const auto* triangle = dynamic_cast<const CTriangle*>(&shape);
	if (!triangle) return;

	std::vector<CPoint> vertexes{ triangle->GetVertex1(), triangle->GetVertex2(), triangle->GetVertex3() };

    this->shape.setPointCount(3);
    for (size_t i = 0; i < vertexes.size(); ++i)
    {
        this->shape.setPoint(i, sf::Vector2f(static_cast<float>(vertexes[i].x), static_cast<float>(vertexes[i].y)));
    }
    
    sf::Color Fcolor((triangle->GetFillColor() << Constants::ALPHA_SHIFT) | Constants::ALPHA_SHIFT_MASK);
    sf::Color Ocolor((triangle->GetOutlineColor() << Constants::ALPHA_SHIFT) | Constants::ALPHA_SHIFT_MASK);
    this->shape.setFillColor(Fcolor);
    this->shape.setOutlineThickness(1.f);
    this->shape.setOutlineColor(Ocolor);
}

const sf::Drawable& SFMLTriangleAdapter::GetSFMLShape() const {
	return this->shape;
}


