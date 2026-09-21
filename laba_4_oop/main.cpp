#include <iostream>
#include <vector>
#include <string>
#include "CalcModule.h"
#include "SfmlWindowModule.h"
#include "ParseStringModule.h"
#include "OutputModule.h"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGTH = 600;
const std::string WINDOW_NAME = "Window";


int main(int argc, char* argv[])
{
	std::vector<std::unique_ptr<IShape>> shapes;
	std::vector<std::unique_ptr<ICanvasDrawable>> drawableShapes;

	if (TryGetShape(argc, shapes, drawableShapes, argv)) return EXIT_FAILURE;

	auto maxAreaShape = MaxArea(shapes);
	auto maxPerimeterShape = MaxPerimeter(shapes);
	
	PrintMaxShapesInfo(maxPerimeterShape, maxAreaShape);

	sf::RenderWindow window(sf::VideoMode({ WINDOW_WIDTH, WINDOW_HEIGTH }), WINDOW_NAME);
	window.setView(window.getDefaultView());
	CCanvas canvas(window);

	ShowPicture(window, canvas, drawableShapes);
	GenerateShapesInfoFile(shapes);

	return EXIT_SUCCESS;
}