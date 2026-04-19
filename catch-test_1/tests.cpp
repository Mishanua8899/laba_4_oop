#include <vector>
#include "catch-sample_1.h"
#include "catch/fakeit.hpp"
#include "laba_4_oop/ICanvas.h"
#include "laba_4_oop/CRectangle.h"
#include "laba_4_oop/CTriangle.h"
#include "laba_4_oop/CCircle.h"
#include "laba_4_oop/CLineSegment.h"
#include "laba_4_oop/CPoint.h"

using namespace fakeit;
// TODO: диаграмму класса сделать модуль на парсинг строки и его тоже отразить в диаграмме
TEST_CASE("Testing drawing")
{
    SECTION("test rectangle draw")
    {
        Mock<ICanvas> mock;
        When(Method(mock, FillPolygon)).AlwaysReturn();
        When(Method(mock, DrawLine)).AlwaysReturn();

        ICanvas& canvas = mock.get();

        CPoint leftTop(10, 10);
        double width = 10;
        double height = 20;
        uint32_t outlineColor = 0x00000000;
        uint32_t fillColor = 0x00ffffff;
        CRectangle rectangle(leftTop, width, height, outlineColor, fillColor);

        rectangle.Draw(canvas);

        CPoint rightTop(20, 10);
        CPoint rightBottom(20, 30);
        CPoint leftBottom(10, 30);
        std::vector<CPoint> expectedPoints = { leftTop, rightTop, rightBottom, leftBottom };

        Verify(Method(mock, FillPolygon).Using(expectedPoints, fillColor)).Once();
        Verify(Method(mock, DrawLine).Using(leftTop, rightTop, outlineColor)).Once();
        Verify(Method(mock, DrawLine).Using(rightTop, rightBottom, outlineColor)).Once();
        Verify(Method(mock, DrawLine).Using(rightBottom, leftBottom, outlineColor)).Once();
        Verify(Method(mock, DrawLine).Using(leftBottom, leftTop, outlineColor)).Once();
    }

    SECTION("test triangle draw")
    {
        Mock<ICanvas> mock;
        When(Method(mock, FillPolygon)).AlwaysReturn();
        When(Method(mock, DrawLine)).AlwaysReturn();

        ICanvas& canvas = mock.get();

        CPoint vertex1(0, 0);
        CPoint vertex2(10, 0);
        CPoint vertex3(5, 10);
        uint32_t outlineColor = 0xFF0000;
        uint32_t fillColor = 0x00FF00;
        CTriangle triangle(vertex1, vertex2, vertex3, outlineColor, fillColor);

        triangle.Draw(canvas);

        std::vector<CPoint> expectedPoints = { vertex1, vertex2, vertex3 };
        Verify(Method(mock, FillPolygon).Using(expectedPoints, fillColor)).Once();
        Verify(Method(mock, DrawLine).Using(vertex1, vertex2, outlineColor)).Once();
        Verify(Method(mock, DrawLine).Using(vertex2, vertex3, outlineColor)).Once();
        Verify(Method(mock, DrawLine).Using(vertex3, vertex1, outlineColor)).Once();
    }

    SECTION("test circle draw")
    {
        Mock<ICanvas> mock;
        When(Method(mock, DrawCircle)).AlwaysReturn();
        When(Method(mock, FillCircle)).AlwaysReturn();

        ICanvas& canvas = mock.get();

        CPoint center(5, 5);
        double radius = 10;
        uint32_t outlineColor = 0x0000FF;
        uint32_t fillColor = 0xFFFF00;
        CCircle circle(center, radius, outlineColor, fillColor);

        circle.Draw(canvas);

        Verify(Method(mock, DrawCircle).Using(center, radius, outlineColor)).Once();
        Verify(Method(mock, FillCircle).Using(center, radius, fillColor)).Once();
    }

    SECTION("test line draw")
    {
        Mock<ICanvas> mock;
        When(Method(mock, DrawLine)).AlwaysReturn();

        ICanvas& canvas = mock.get();

        CPoint start(1, 2);
        CPoint end(3, 4);
        uint32_t outlineColor = 0x123456;
        CLineSegment line(start, end, outlineColor);

        line.Draw(canvas);

        Verify(Method(mock, DrawLine).Using(start, end, outlineColor)).Once();
    }
}