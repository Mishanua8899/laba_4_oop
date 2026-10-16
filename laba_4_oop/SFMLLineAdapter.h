#pragma once
#include "SFML/Graphics.hpp"
#include "IShapeAdapter.h"
class SFMLLineAdapter : public IShapeAdapter {
public:
    void SyncWith(const IShape& shape) override;
    const sf::Drawable& GetSFMLShape() const override;

private:
    mutable sf::VertexArray shape;
};
