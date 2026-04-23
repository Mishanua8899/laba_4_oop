#include <catch2/catch.hpp>
#include "laba_4_oop/CLineSegment.h"
#include "laba_4_oop/CalcModule.h"
#include "laba_4_oop/ParseStringModule.h"
#include <fstream>
#include <memory>

TEST_CASE("test line segment")
{
    std::ifstream InFile("test_data_line.txt");
    std::vector<std::unique_ptr<IShape>> shapes;
    std::vector<std::unique_ptr<ICanvasDrawable>> drawableShapes;
    GetShapes(InFile, shapes, drawableShapes);

    REQUIRE(shapes.size() == 3); 

    SECTION("test perimeter calculation (length)")
    {
        REQUIRE(shapes[0]->GetPerimeter() == 5);
        REQUIRE(shapes[1]->GetPerimeter() == 10);
        REQUIRE(shapes[2]->GetPerimeter() == 5);
    }

    SECTION("test area calculation (always 0)")
    {
        REQUIRE(shapes[0]->GetArea() == 0.0);
        REQUIRE(shapes[1]->GetArea() == 0.0);
        REQUIRE(shapes[2]->GetArea() == 0.0);
    }

    SECTION("test outline color")
    {
        
        CLineSegment* firstLine = dynamic_cast<CLineSegment*>(shapes[0].get());
        CLineSegment* secondLine = dynamic_cast<CLineSegment*>(shapes[1].get());
        CLineSegment* thirdLine = dynamic_cast<CLineSegment*>(shapes[2].get());

        REQUIRE(firstLine->GetOutlineColor() == 0xff0000);
        REQUIRE(secondLine->GetOutlineColor() == 0x00ff00);
        REQUIRE(thirdLine->GetOutlineColor() == 0x0000ff);
    }

    SECTION("test line endpoints")
    {
        CLineSegment* firstLine = dynamic_cast<CLineSegment*>(shapes[0].get());
        CLineSegment* secondLine = dynamic_cast<CLineSegment*>(shapes[1].get());
        CLineSegment* thirdLine = dynamic_cast<CLineSegment*>(shapes[2].get());

        REQUIRE(firstLine->GetStartPoint() == CPoint(0, 0));
        REQUIRE(firstLine->GetEndPoint() == CPoint(3, 4));

        REQUIRE(secondLine->GetStartPoint() == CPoint(0, 0));
        REQUIRE(secondLine->GetEndPoint() == CPoint(6, 8));

        REQUIRE(thirdLine->GetStartPoint() == CPoint(-3, -4));
        REQUIRE(thirdLine->GetEndPoint() == CPoint(0, 0));
    }
}