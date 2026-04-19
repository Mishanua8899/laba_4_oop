#include <catch2/catch.hpp>
#include <fstream>
#include "laba_4_oop/CalcModule.h"
#include "laba_4_oop/ParseStringModule.h"

// TODO: на каждый класс добавить тесты 

TEST_CASE("test programm")
{
	SECTION("test with circle max shape")
	{
		std::ifstream file("test_data.txt");
		std::vector<std::unique_ptr<IShape>> shapes;
		GetShapes(file, shapes);
		REQUIRE(shapes[0]->GetShapeType() == "rectangle");
		REQUIRE(shapes[1]->GetShapeType() == "circle");
		REQUIRE(shapes[2]->GetShapeType() == "line");
		REQUIRE(MaxArea(shapes)->GetArea() == 2826);
		REQUIRE(MaxPerimeter(shapes)->GetPerimeter() == 188.4);
	}

	SECTION("test with rectanle max shape")
	{
		std::ifstream file("test_data_2.txt");
		std::vector<std::unique_ptr<IShape>> shapes;
		GetShapes(file, shapes);
		REQUIRE(shapes[0]->GetShapeType() == "rectangle");
		REQUIRE(shapes[1]->GetShapeType() == "circle");
		REQUIRE(shapes[2]->GetShapeType() == "line");
		REQUIRE(MaxArea(shapes)->GetArea() == 1240.28);
		REQUIRE(MaxPerimeter(shapes)->GetPerimeter() == 142.2);
	}

	SECTION("test with line max shape")
	{
		std::ifstream file("test_data_3.txt");
		std::vector<std::unique_ptr<IShape>> shapes;
		GetShapes(file, shapes);
		REQUIRE(shapes[0]->GetShapeType() == "line");
		REQUIRE(shapes[1]->GetShapeType() == "line");
		REQUIRE(shapes[2]->GetShapeType() == "line");
		REQUIRE(MaxArea(shapes)->GetArea() == 0.0);
		REQUIRE(MaxPerimeter(shapes)->GetPerimeter() == 141.42);
	}

	SECTION("test with triangle max shape")
	{
		std::ifstream file("test_data_4.txt");
		std::vector<std::unique_ptr<IShape>> shapes;
		GetShapes(file, shapes);
		REQUIRE(shapes[0]->GetShapeType() == "triangle");
		REQUIRE(shapes[1]->GetShapeType() == "triangle");
		REQUIRE(shapes[2]->GetShapeType() == "rectangle");
		REQUIRE(shapes[3]->GetShapeType() == "circle");
		REQUIRE(MaxArea(shapes)->GetArea() == 600);
		REQUIRE(MaxPerimeter(shapes)->GetPerimeter() == 114.05);
	}


}

