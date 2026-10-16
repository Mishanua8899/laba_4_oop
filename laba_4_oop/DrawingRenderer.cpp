#include "DrawingRenderer.h"
#include "Drawing.h"
#include "IShapeAdapter.h"
#include "SFMLCircleAdapter.h"
#include "SFMLLineAdapter.h"
#include "SFMLRectangleAdapter.h"
#include "SFMLTriangleAdapter.h"
#include "SelectionManager.h"
#include <memory>

/* константы в отдельный файл вынести, RenderWindow не должен быть в main(handler сделать), инфу всю о фигурах MaxArea, MaxPerimeter, PrintMaxShapesInfo, GenerateShapesInfoFile, TryGetShape(наверное в отдельный класс-обработчик) вынести в класс по типу ShapeParser */

void DrawingRenderer::Draw(const CompositeDrawing& drawing, sf::RenderTarget& target, SelectionManager& selectionMgr)
{
	for (size_t i = 0; i < drawing.GetCountShapes(); ++i)
	{
		DrawShapeRecursive(*drawing.GetShape(i), target);
	}

	DrawSelectionBox(target, selectionMgr);
}

void DrawingRenderer::DrawShapeRecursive(const IShape& shape, sf::RenderTarget& target)
{
	if (shape.IsComposite())
	{
		const auto& composite = static_cast<const CompositeShape&>(shape);
		for (const auto& child : composite.GetChildren())
		{
			DrawShapeRecursive(*child, target);
		}
		return;
	}

	auto adapter = shape.CreateAdapter();

	if (adapter)
	{
		adapter->SyncWith(shape);
		target.draw(adapter->GetSFMLShape());
	}
}

void DrawingRenderer::DrawSelectionBox(sf::RenderTarget& target, SelectionManager& selectionMgr)
{
	if (selectionMgr.GetSelectedShapes().empty())
		return;

	sf::FloatRect bounds = selectionMgr.GetSelectionBounds();

	sf::RectangleShape frame(sf::Vector2f(bounds.size.x, bounds.size.y));
	frame.setPosition(sf::Vector2(bounds.position.x, bounds.position.y));
	frame.setFillColor(sf::Color::Transparent);
	frame.setOutlineColor(sf::Color::Blue);
	frame.setOutlineThickness(2.f);
	target.draw(frame);
}