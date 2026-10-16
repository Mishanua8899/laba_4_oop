#pragma once
#include "Drawing.h"
#include "SFMLWindowHandler.h"
#include "ShapeController.h"
#include <memory>

class Application
{
public: 
	static Application& GetInstance();

	Application(const Application&) = delete;
	Application& operator=(const Application&) = delete;

	bool Initialize(int argc, char* argv[]);
	void Run();

	CompositeDrawing& GetDrawing();
	SFMLWindowHandler& GetWindowHandler();
private:
	
	Application() = default;
	~Application() = default;

	std::unique_ptr<ShapeController> m_controller;
	std::unique_ptr<CompositeDrawing> m_drawing;
	std::unique_ptr<SFMLWindowHandler> m_windowHandler;

};