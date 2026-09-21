#include <catch2/catch.hpp>
#include "laba_4_oop/CRectangle.h"
#include "laba_4_oop/CalcModule.h"
#include "laba_4_oop/ParseStringModule.h"
#include <fstream>
#include <memory>

// Перегрузка оператора == для sf::RectangleShape (используется в CRectangle)



TEST_CASE("test rectangle")
{
    std::ifstream InFile("test_data_rectangle.txt");
    std::vector<std::unique_ptr<IShape>> shapes;
    std::vector<std::unique_ptr<ICanvasDrawable>> drawableShapes;
    GetShapes(InFile, shapes, drawableShapes);

    SECTION("test perimeter calculation")
    {
        REQUIRE(shapes[0]->GetPerimeter() == 60);   
        REQUIRE(shapes[1]->GetPerimeter() == 140);  
        REQUIRE(shapes[2]->GetPerimeter() == 40);   
    }

    SECTION("test area calculation")
    {
        REQUIRE(shapes[0]->GetArea() == 200); 
        REQUIRE(shapes[1]->GetArea() == 1200);  
        REQUIRE(shapes[2]->GetArea() == 75);    
    }

    SECTION("test colors (outline, fill)")
    {
        CRectangle* firstRect = dynamic_cast<CRectangle*>(shapes[0].get());
        CRectangle* secondRect = dynamic_cast<CRectangle*>(shapes[1].get());
        CRectangle* thirdRect = dynamic_cast<CRectangle*>(shapes[2].get());

        REQUIRE(firstRect->GetFillColor() == 0x00ff00);
        REQUIRE(firstRect->GetOutlineColor() == 0xff0000);
        REQUIRE(secondRect->GetOutlineColor() == 0x0000ff);
        REQUIRE(secondRect->GetFillColor() == 0xffffff);
        REQUIRE(thirdRect->GetOutlineColor() == 0x123456);
        REQUIRE(thirdRect->GetFillColor() == 0xabcdef);
    }

    SECTION("test rectangle properties")
    {
        CRectangle* firstRect = dynamic_cast<CRectangle*>(shapes[0].get());
        CRectangle* secondRect = dynamic_cast<CRectangle*>(shapes[1].get());
        CRectangle* thirdRect = dynamic_cast<CRectangle*>(shapes[2].get());

        REQUIRE(firstRect->GetLeftTop() == CPoint(0, 0));
        REQUIRE(firstRect->GetWidth() == 10);
        REQUIRE(firstRect->GetHeight() == 20);
        REQUIRE(firstRect->GetRightBottom() == CPoint(10, 20));

        REQUIRE(secondRect->GetLeftTop() == CPoint(5, 5));
        REQUIRE(secondRect->GetWidth() == 30);
        REQUIRE(secondRect->GetHeight() == 40);
        REQUIRE(secondRect->GetRightBottom() == CPoint(35, 45));

        REQUIRE(thirdRect->GetLeftTop() == CPoint(-10, -10));
        REQUIRE(thirdRect->GetWidth() == 5);
        REQUIRE(thirdRect->GetHeight() == 15);
        REQUIRE(thirdRect->GetRightBottom() == CPoint(-5, 5));
    }
}