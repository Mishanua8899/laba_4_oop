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

inline bool operator==(const sf::VertexArray& lhs, const sf::VertexArray& rhs) {
    if (lhs.getPrimitiveType() != rhs.getPrimitiveType() || lhs.getVertexCount() != rhs.getVertexCount()) {
        return false;
    }
    for (size_t i = 0; i < lhs.getVertexCount(); ++i) {
        if (lhs[i].position != rhs[i].position || lhs[i].color != rhs[i].color) {
            return false;
        }
    }
    return true;
}

inline bool operator==(const sf::RectangleShape& lhs, const sf::RectangleShape& rhs) {
    return lhs.getSize() == rhs.getSize() &&
        lhs.getPosition() == rhs.getPosition() &&
        lhs.getFillColor() == rhs.getFillColor() &&
        lhs.getOutlineColor() == rhs.getOutlineColor() &&
        lhs.getOutlineThickness() == rhs.getOutlineThickness();
}

inline bool operator==(const sf::ConvexShape& lhs, const sf::ConvexShape& rhs) {
    if (lhs.getPointCount() != rhs.getPointCount() ||
        lhs.getFillColor() != rhs.getFillColor() ||
        lhs.getOutlineColor() != rhs.getOutlineColor() ||
        lhs.getOutlineThickness() != rhs.getOutlineThickness()) {
        return false;
    }
    for (size_t i = 0; i < lhs.getPointCount(); ++i) {
        if (lhs.getPoint(i) != rhs.getPoint(i)) return false;
    }
    return true;
}

inline bool operator==(const sf::CircleShape& lhs, const sf::CircleShape& rhs) {
    return lhs.getRadius() == rhs.getRadius() &&
        lhs.getPosition() == rhs.getPosition() &&
        lhs.getFillColor() == rhs.getFillColor() &&
        lhs.getOutlineColor() == rhs.getOutlineColor() &&
        lhs.getOutlineThickness() == rhs.getOutlineThickness();
}

// TODO: диаграмму класса сделать модуль на парсинг строки и его тоже отразить в диаграмме
TEST_CASE("Testing drawing")
{
    SECTION("test rectangle draw")
    {
        Mock<ICanvas> mock;
        bool isCalledCorrectly = false;

        CPoint leftTop(10, 10);
        double width = 10;
        double height = 20;
        uint32_t outlineColor = 0x00000000;
        uint32_t fillColor = 0x00ffffff;

        // Эталонный объект для сравнения
        sf::RectangleShape expectedRect;
        expectedRect.setSize({ static_cast<float>(width), static_cast<float>(height) });
        expectedRect.setPosition({ static_cast<float>(leftTop.x), static_cast<float>(leftTop.y) });
        expectedRect.setFillColor(sf::Color((fillColor << 8) | 0x000000FF));
        expectedRect.setOutlineColor(sf::Color((outlineColor << 8) | 0x000000FF));
        expectedRect.setOutlineThickness(1.f);

        // Проверяем объект ПРЯМО ВО ВРЕМЯ вызова, пока он жив в памяти
        When(Method(mock, Draw)).Do([&](const sf::Drawable& drawable) {
            auto rectPtr = dynamic_cast<const sf::RectangleShape*>(&drawable);
            if (rectPtr && *rectPtr == expectedRect) {
                isCalledCorrectly = true;
            }
            });

        ICanvas& canvas = mock.get();
        CRectangle rectangle(leftTop, width, height, outlineColor, fillColor);
        rectangle.Draw(canvas);

        // В конце просто проверяем флаг успеха и факт вызова
        REQUIRE(isCalledCorrectly == true);
        Verify(Method(mock, Draw)).Once();
    }


    SECTION("test line draw")
    {
        Mock<ICanvas> mock;
        bool isCalledCorrectly = false;

        CPoint startPoint(10, 20);
        CPoint endPoint(50, 60);
        uint32_t outlineColor = 0xff000000;

        sf::VertexArray expectedLine;
        expectedLine.setPrimitiveType(sf::PrimitiveType::Lines);
        sf::Vertex startVertex(sf::Vector2f(static_cast<float>(startPoint.x), static_cast<float>(startPoint.y)), sf::Color((outlineColor << 8) | 0x000000FF));
        sf::Vertex endVertex(sf::Vector2f(static_cast<float>(endPoint.x), static_cast<float>(endPoint.y)), sf::Color((outlineColor << 8) | 0x000000FF));
        expectedLine.append(startVertex);
        expectedLine.append(endVertex);

        When(Method(mock, Draw)).Do([&](const sf::Drawable& drawable) {
            auto linePtr = dynamic_cast<const sf::VertexArray*>(&drawable);
            if (linePtr && *linePtr == expectedLine) {
                isCalledCorrectly = true;
            }
            });

        ICanvas& canvas = mock.get();
        CLineSegment lineSegment(startPoint, endPoint, outlineColor);
        lineSegment.Draw(canvas);

        REQUIRE(isCalledCorrectly == true);
        Verify(Method(mock, Draw)).Once();
    }



    SECTION("test triangle draw")
    {
        Mock<ICanvas> mock;
        bool isCalledCorrectly = false;

        CPoint v1(10, 10);
        CPoint v2(50, 10);
        CPoint v3(30, 50);
        uint32_t outlineColor = 0x00000000;
        uint32_t fillColor = 0x00ff0000;

        std::vector<CPoint> vertexes{ v1, v2, v3 };
        sf::ConvexShape expectedPolygon;
        expectedPolygon.setPointCount(3);
        for (size_t i = 0; i < vertexes.size(); ++i) {
            expectedPolygon.setPoint(i, sf::Vector2f(static_cast<float>(vertexes[i].x), static_cast<float>(vertexes[i].y)));
        }
        expectedPolygon.setFillColor(sf::Color((fillColor << 8) | 0x000000FF));
        expectedPolygon.setOutlineColor(sf::Color((outlineColor << 8) | 0x000000FF));
        expectedPolygon.setOutlineThickness(1.f);

        When(Method(mock, Draw)).Do([&](const sf::Drawable& drawable) {
            auto polPtr = dynamic_cast<const sf::ConvexShape*>(&drawable);
            if (polPtr && *polPtr == expectedPolygon) {
                isCalledCorrectly = true;
            }
            });

        ICanvas& canvas = mock.get();
        CTriangle triangle(v1, v2, v3, outlineColor, fillColor);
        triangle.Draw(canvas);

        REQUIRE(isCalledCorrectly == true);
        Verify(Method(mock, Draw)).Once();
    }



    SECTION("test circle draw")
    {
        Mock<ICanvas> mock;
        bool isCalledCorrectly = false;

        CPoint center(100, 100);
        double radius = 30;
        uint32_t outlineColor = 0x00000000;
        uint32_t fillColor = 0x0000ff00;

        sf::CircleShape expectedCircle;
        expectedCircle.setRadius(radius);
        expectedCircle.setPosition(sf::Vector2f(static_cast<float>(center.x - radius), static_cast<float>(center.y - radius)));
        expectedCircle.setFillColor(sf::Color((fillColor << 8) | 0x000000FF));
        expectedCircle.setOutlineColor(sf::Color((outlineColor << 8) | 0x000000FF));
        expectedCircle.setOutlineThickness(1.f);

        When(Method(mock, Draw)).Do([&](const sf::Drawable& drawable) {
            auto circlePtr = dynamic_cast<const sf::CircleShape*>(&drawable);
            if (circlePtr && *circlePtr == expectedCircle) {
                isCalledCorrectly = true;
            }
            });

        ICanvas& canvas = mock.get();
        CCircle circle(center, radius, outlineColor, fillColor);
        circle.Draw(canvas);

        REQUIRE(isCalledCorrectly == true);
        Verify(Method(mock, Draw)).Once();
    }


}