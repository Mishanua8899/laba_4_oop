#include <iostream>
#include <vector>
#include <string>
#include "CalcModule.h"
#include "SfmlWindowModule.h"
#include "ParseStringModule.h"

// TODO: можно в солидшейп вынести филлколор и оутлайн чтобы избавиться от полей в фигурах
// TODO: iDrawable наследовать для фигур 
// узнать зачем использовать ICanvas а не просто использовать CCanvas
int main(int argc, char* argv[])
{
	std::vector<std::unique_ptr<IShape>> shapes;
	
	if (TryGetShape(argc, shapes, argv)) return EXIT_FAILURE;

	auto maxAreaShape = MaxArea(shapes);
	auto maxPerimeterShape = MaxPerimeter(shapes);
	std::cout << "Max Area Shape: " << std::endl;
	std::cout << maxAreaShape->ToString() << std::endl;
	std::cout << "Max Perimeter Shape: " << std::endl;
	std::cout << maxPerimeterShape->ToString() << std::endl;

	sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "Window");
	window.setView(window.getDefaultView());
	CCanvas canvas(window);

	ShowPicture(window, canvas, shapes);

	return EXIT_SUCCESS;
}