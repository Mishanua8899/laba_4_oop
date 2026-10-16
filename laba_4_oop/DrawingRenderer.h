#pragma once
#include "Drawing.h"
#include "SFML/Graphics.hpp"
#include "SelectionManager.h"
class DrawingRenderer {
public:
	DrawingRenderer() = default;

	void Draw(const CompositeDrawing& drawing, sf::RenderTarget& target, SelectionManager& selectionMgr);

	void DrawShapeRecursive(const IShape& shape, sf::RenderTarget& target);
	void DrawSelectionBox(sf::RenderTarget& target, SelectionManager& selectionMgr);
};