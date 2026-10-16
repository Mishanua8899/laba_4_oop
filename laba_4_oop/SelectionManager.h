#pragma once
#include "Drawing.h"
#include "CompositeShape.h"
#include <vector>
#include <set>
#include <SFML/Window.hpp>

class SelectionManager {
public:
    SelectionManager(CompositeDrawing& drawing) : drawing(drawing) {}

    void HandleMouseClick(const CPoint& clickPos, bool isShiftPressed);
    void HandleMouseMove(const CPoint& currentPos);
    void HandleMouseRelease();

    void GroupSelected();
    void UngroupSelected();

    const std::set<IShape*>& GetSelectedShapes();
    sf::FloatRect GetSelectionBounds();

private:
    IShape* FindShapeAt(const CPoint& point);
    void StartDrag(const CPoint& pos);

    CompositeDrawing& drawing;
    std::set<IShape*> selectedShapes;
    bool isDragging = false;
    CPoint lastMousePos = { 0, 0 };
};
