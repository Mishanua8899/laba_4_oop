#pragma once
#include <SFML/Graphics.hpp>
#include "Drawing.h" 
#include "DrawingRenderer.h"
#include "SelectionManager.h"

class SFMLWindowHandler {
public:
    SFMLWindowHandler(int width, int height, const std::string& title);

    void Run(CompositeDrawing& drawing);

private:
    sf::RenderWindow window;
    DrawingRenderer renderer;

    void ProcessEvents(SelectionManager& selectionMgr);
    void Render(CompositeDrawing& drawing, SelectionManager& selectionMgr);
};