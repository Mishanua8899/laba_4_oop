#pragma once
#include "SFML/Graphics.hpp"
class IShape;



class IShapeAdapter {
public:
    virtual ~IShapeAdapter() = default;
    virtual void SyncWith(const IShape& shape) = 0; 
    virtual const sf::Drawable& GetSFMLShape() const = 0;
    

};
