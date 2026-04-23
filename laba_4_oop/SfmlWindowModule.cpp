#include "SfmlWindowModule.h"
#include "ICanvasDrawable.h"
void ShowPicture(sf::RenderWindow& window, CCanvas& canvas, std::vector<std::unique_ptr<ICanvasDrawable>>& shapes)
{
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        window.clear(sf::Color::Black);
        for (const auto& shape : shapes)
        {
            shape->Draw(canvas);
        }
        window.display();
    }
}

