#include "SFMLWindowHandler.h"
#include <optional>

SFMLWindowHandler::SFMLWindowHandler(int width, int height, const std::string& title)
	: window(sf::VideoMode({ static_cast<unsigned>(width), static_cast<unsigned>(height) }), title)
{
	window.setView(window.getDefaultView());
}

void SFMLWindowHandler::Run(CompositeDrawing& drawing)
{
	SelectionManager selectionMgr(drawing);

	while (window.isOpen())
	{
		ProcessEvents(selectionMgr);
		Render(drawing, selectionMgr);
	}
}

void SFMLWindowHandler::ProcessEvents(SelectionManager& selectionMgr)
{
	while (const std::optional<sf::Event> event = window.pollEvent())
	{
		if (event->is<sf::Event::Closed>())
		{
			window.close();
		}
		if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>())
		{
			if (mousePressed->button == sf::Mouse::Button::Left)
			{
				CPoint clickPos = {
					static_cast<float>(mousePressed->position.x),
					static_cast<float>(mousePressed->position.y)
				};
				bool isShift = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RShift);
				selectionMgr.HandleMouseClick(clickPos, isShift);
			}
		}
		if (const auto* mouseMoved = event->getIf<sf::Event::MouseMoved>())
		{
			CPoint currentPos = {
				static_cast<float>(mouseMoved->position.x),
				static_cast<float>(mouseMoved->position.y)
			};
			selectionMgr.HandleMouseMove(currentPos);
		}
		if (const auto* mouseReleased = event->getIf<sf::Event::MouseButtonReleased>())
		{
			if (mouseReleased->button == sf::Mouse::Button::Left)
			{
				selectionMgr.HandleMouseRelease();
			}
		}
		if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
		{
			bool isCtrl = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RControl);
			if (isCtrl && keyPressed->code == sf::Keyboard::Key::G)
			{
				selectionMgr.GroupSelected();
			}
			if (isCtrl && keyPressed->code == sf::Keyboard::Key::U)
			{
				selectionMgr.UngroupSelected();
			}
		}
	}
}

void SFMLWindowHandler::Render(CompositeDrawing& drawing, SelectionManager& selectionMgr)
{
	window.clear(sf::Color::White);
	renderer.Draw(drawing, window, selectionMgr);
	window.display();
}