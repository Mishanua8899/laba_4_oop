#pragma once
#include "IShape.h"
#include <stdexcept> 
#include <memory>
#include <vector>



class CompositeDrawing
{
public:
    CompositeDrawing(std::vector<std::unique_ptr<IShape>> shapes);
    ~CompositeDrawing() = default;
    void PushShape(std::unique_ptr<IShape> shape);
    size_t GetCountShapes() const noexcept;
    const IShape* GetShape(size_t index) const;
    IShape* GetShape(size_t index);
    std::unique_ptr<IShape> ExtractShape(const IShape* shapePtr);

private:
    std::vector<std::unique_ptr<IShape>> shapes;
};
