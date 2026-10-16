#include "Application.h"
#include "Constants.h"
#include "Drawing.h"
#include "SFMLWindowHandler.h"
#include "ShapeController.h"
#include <iostream>

Application& Application::GetInstance()
{
	static Application instance;
	return instance;
}

bool Application::Initialize(int argc, char* argv[])
{
	m_controller = std::make_unique<ShapeController>();
	if (!m_controller->Initialize(argc, argv))
	{
		return false;
	}

	m_controller->ProcessAndExportInfo();
	auto shapes = m_controller->ExtractShapes();

	m_drawing = std::make_unique<CompositeDrawing>(std::move(shapes));

	m_windowHandler = std::make_unique<SFMLWindowHandler>(
		Constants::WINDOW_WIDTH,
		Constants::WINDOW_HEIGHT,
		Constants::WINDOW_NAME);

	return true;
}

void Application::Run()
{
	if (m_windowHandler && m_drawing)
	{
		m_windowHandler->Run(*m_drawing);
	}
}

CompositeDrawing& Application::GetDrawing()
{
	return *m_drawing;
}

SFMLWindowHandler& Application::GetWindowHandler()
{
	return *m_windowHandler;
}