#pragma once
#include "SFML/Graphics.hpp"
#include "IShapeAdapter.h"
class SFMLCircleAdapter : public IShapeAdapter {
public:
    void SyncWith(const IShape& shape) override;
    const sf::Drawable& GetSFMLShape() const override;
private:
    mutable sf::CircleShape shape;
};