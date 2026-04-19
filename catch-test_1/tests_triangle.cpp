#include <catch2/catch.hpp>
#include "laba_4_oop/CTriangle.h"
#include "laba_4_oop/CalcModule.h"
#include "laba_4_oop/ParseStringModule.h"
#include <fstream>
#include <memory>

TEST_CASE("test triangle")
{
    std::ifstream InFile("test_data_triangle.txt");
    std::vector<std::unique_ptr<IShape>> shapes;
    GetShapes(InFile, shapes);

    SECTION("test perimeter calculation")
    {
        REQUIRE(shapes[0]->GetPerimeter() == 12.0);   
        REQUIRE(shapes[1]->GetPerimeter() == 24.0);   
        REQUIRE(shapes[2]->GetPerimeter() == 12.0);   
    }

    SECTION("test area calculation")
    {
        REQUIRE(shapes[0]->GetArea() == 6.0);
        REQUIRE(shapes[1]->GetArea() == 24.0);
        REQUIRE(shapes[2]->GetArea() == 6.0);
    }

    SECTION("test colors (outline, fill)")
    {
        CTriangle* firstTri = dynamic_cast<CTriangle*>(shapes[0].get());
        CTriangle* secondTri = dynamic_cast<CTriangle*>(shapes[1].get());
        CTriangle* thirdTri = dynamic_cast<CTriangle*>(shapes[2].get());

        REQUIRE(firstTri->GetOutlineColor() == 0xff0000);
        REQUIRE(firstTri->GetFillColor() == 0x00ff00);

        REQUIRE(secondTri->GetOutlineColor() == 0x0000ff);
        REQUIRE(secondTri->GetFillColor() == 0xffffff);

        REQUIRE(thirdTri->GetOutlineColor() == 0xff0000);
        REQUIRE(thirdTri->GetFillColor() == 0x00ff00);
    }

    SECTION("test triangle vertices")
    {
        CTriangle* firstTri = dynamic_cast<CTriangle*>(shapes[0].get());
        CTriangle* secondTri = dynamic_cast<CTriangle*>(shapes[1].get());
        CTriangle* thirdTri = dynamic_cast<CTriangle*>(shapes[2].get());

        REQUIRE(firstTri->GetVertex1() == CPoint(0, 0));
        REQUIRE(firstTri->GetVertex2() == CPoint(3, 0));
        REQUIRE(firstTri->GetVertex3() == CPoint(0, 4));

        REQUIRE(secondTri->GetVertex1() == CPoint(0, 0));
        REQUIRE(secondTri->GetVertex2() == CPoint(6, 0));
        REQUIRE(secondTri->GetVertex3() == CPoint(0, 8));

        REQUIRE(thirdTri->GetVertex1() == CPoint(-3, -4));
        REQUIRE(thirdTri->GetVertex2() == CPoint(0, -4));
        REQUIRE(thirdTri->GetVertex3() == CPoint(-3, 0));
    }
}