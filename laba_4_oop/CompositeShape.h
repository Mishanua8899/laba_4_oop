#pragma once
#include "IShape.h"
#include <vector>
#include <memory>
#include <algorithm>

class CompositeShape : public IShape {
public:
    void AddChild(std::unique_ptr<IShape> child);
    std::vector<std::unique_ptr<IShape>> ExtractChildren();

    bool IsInside(const CPoint& point) const override;
    sf::FloatRect GetBoundingBox() const override;
    void Move(float dx, float dy) override;

    std::string GetShapeType() const override;
    double GetArea() const override;
    double GetPerimeter() const override;
    std::string ToString() const override;

    bool IsComposite() const override;
    const std::vector<std::unique_ptr<IShape>>& GetChildren() const;

    std::unique_ptr<IShapeAdapter> CreateAdapter() const { return nullptr; };
private:
    std::vector<std::unique_ptr<IShape>> children;
};