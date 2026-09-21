#include <catch2/catch.hpp>
#include "laba_4_oop/CCircle.h"
#include "laba_4_oop/CalcModule.h"
#include "laba_4_oop/ParseStringModule.h"
#include <fstream>
#include <memory>



TEST_CASE("test circle")
{
	std::ifstream InFile("test_data_circle.txt");
	std::vector<std::unique_ptr<IShape>> shapes;
	std::vector<std::unique_ptr<ICanvasDrawable>> drawableShapes;
	GetShapes(InFile, shapes, drawableShapes);
	SECTION("test perimeter calculation")
	{
		REQUIRE(shapes[0]->GetPerimeter() == 31.4);
		REQUIRE(shapes[1]->GetPerimeter() == 62.8);
		REQUIRE(shapes[2]->GetPerimeter() == 94.2);
	}

	SECTION("test area calculation")
	{
		REQUIRE(shapes[0]->GetArea() == 78.5);
		REQUIRE(shapes[1]->GetArea() == 314);
		REQUIRE(shapes[2]->GetArea() == 706.5);
	}

	SECTION("shapes color(outline, fill)")
	{
		CCircle* firstCircle = dynamic_cast<CCircle*>(shapes[0].get());
		CCircle* secondCircle = dynamic_cast<CCircle*>(shapes[1].get());
		CCircle* thirdCircle = dynamic_cast<CCircle*>(shapes[2].get());
		REQUIRE(firstCircle->GetFillColor() == 0x09ffff);
		REQUIRE(firstCircle->GetOutlineColor() == 0x000cff);
		REQUIRE(secondCircle->GetOutlineColor() == 0x0d00ff);
		REQUIRE(secondCircle->GetFillColor() == 0x000000);
		REQUIRE(thirdCircle->GetOutlineColor() == 0xe000ff);
		REQUIRE(thirdCircle->GetFillColor() == 0xffffff);
	}

	SECTION("shapes color(outline, fill)")
	{
		CCircle* firstCircle = dynamic_cast<CCircle*>(shapes[0].get());
		CCircle* secondCircle = dynamic_cast<CCircle*>(shapes[1].get());
		CCircle* thirdCircle = dynamic_cast<CCircle*>(shapes[2].get());
		REQUIRE(firstCircle->GetRadius() == 5);
		REQUIRE(firstCircle->GetCenter() == CPoint(0, 100));
		REQUIRE(secondCircle->GetRadius() == 10);
		REQUIRE(secondCircle->GetCenter() == CPoint(50, -100));
		REQUIRE(thirdCircle->GetRadius() == 15);
		REQUIRE(thirdCircle->GetCenter() == CPoint(-100, 100));
	}
}