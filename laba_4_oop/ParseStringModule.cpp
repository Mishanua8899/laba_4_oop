#include "ParseStringModule.h"
#include "IShape.h"
#include "CRectangle.h"
#include "CTriangle.h"
#include "CLineSegment.h"
#include "CCircle.h"
#include <sstream>
#include <iostream>
#include <fstream>
#include <string>

constexpr const char* ERROR_MESSAGE_PARSE = "ERROR: cannot parse this line";
constexpr const char* ERROR_MESSAGE_PARAMS = "ERROR: incorrect number of parameters";

static uint32_t ParseColor(const std::string& hex)
{
    if (hex.size() == 6)
    {
        return std::stoul(hex, nullptr, 16);
    }
    else
    {
        throw std::invalid_argument("hex color must be described in 6 symbols");
    }
}

void SetRectangle(std::vector<std::unique_ptr<IShape>>& shapes, std::vector<std::unique_ptr<ICanvasDrawable>>& drawableShapes, std::stringstream& lineStream)
{
    double x, y, w, h;
    std::string outlineStr, fillStr;
    if (lineStream >> x >> y >> w >> h >> outlineStr >> fillStr)
    {
        try
        {
            uint32_t outline = ParseColor(outlineStr);
            uint32_t fill = ParseColor(fillStr);
            shapes.push_back(std::make_unique<CRectangle>(CPoint(x, y), w, h, outline, fill));
            drawableShapes.push_back(std::make_unique<CRectangle>(CPoint(x, y), w, h, outline, fill));
        }
        catch (...)
        {
            std::cout << ERROR_MESSAGE_PARSE << std::endl;
        }
    }
    else
    {
        std::cout << ERROR_MESSAGE_PARAMS << std::endl;
    }
}

void SetLine(std::vector<std::unique_ptr<IShape>>& shapes, std::vector<std::unique_ptr<ICanvasDrawable>>& drawableShapes, std::stringstream& lineStream)
{
    double x1, y1, x2, y2;
    std::string outlineStr;
    if (lineStream >> x1 >> y1 >> x2 >> y2 >> outlineStr)
    {
        try
        {
            uint32_t outline = ParseColor(outlineStr);
            shapes.push_back(std::make_unique<CLineSegment>(CPoint(x1, y1), CPoint(x2, y2), outline));
            drawableShapes.push_back(std::make_unique<CLineSegment>(CPoint(x1, y1), CPoint(x2, y2), outline));
        }
        catch (...)
        {
            std::cout << ERROR_MESSAGE_PARSE << std::endl;
        }
    }
    else
    {
        std::cout << ERROR_MESSAGE_PARAMS << std::endl;
    }
}

void SetTriangle(std::vector<std::unique_ptr<IShape>>& shapes, std::vector<std::unique_ptr<ICanvasDrawable>>& drawableShapes, std::stringstream& lineStream)
{
    double x1, y1, x2, y2, x3, y3;
    std::string outlineStr, fillStr;
    if (lineStream >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> outlineStr >> fillStr)
    {
        try
        {
            uint32_t outline = ParseColor(outlineStr);
            uint32_t fill = ParseColor(fillStr);
            shapes.push_back(std::make_unique<CTriangle>(CPoint(x1, y1), CPoint(x2, y2), CPoint(x3, y3), outline, fill));
            drawableShapes.push_back(std::make_unique<CTriangle>(CPoint(x1, y1), CPoint(x2, y2), CPoint(x3, y3), outline, fill));
        }
        catch (...)
        {
            std::cout << ERROR_MESSAGE_PARSE << std::endl;
        }
    }
    else
    {
        std::cout << ERROR_MESSAGE_PARAMS << std::endl;
    }
}

void SetCircle(std::vector<std::unique_ptr<IShape>>& shapes, std::vector<std::unique_ptr<ICanvasDrawable>>& drawableShapes, std::stringstream& lineStream)
{
    double x, y, radius;
    std::string outlineStr, fillStr;
    if (lineStream >> x >> y >> radius >> outlineStr >> fillStr)
    {
        try
        {
            uint32_t outline = ParseColor(outlineStr);
            uint32_t fill = ParseColor(fillStr);
            shapes.push_back(std::make_unique<CCircle>(CPoint(x, y), radius, outline, fill));
            drawableShapes.push_back(std::make_unique<CCircle>(CPoint(x, y), radius, outline, fill));
        }
        catch (...)
        {
            std::cout << ERROR_MESSAGE_PARSE << std::endl;
        }
    }
    else
    {
        std::cout << ERROR_MESSAGE_PARAMS << std::endl;
    }
}

void SetShape(std::vector<std::unique_ptr<IShape>>& shapes, std::vector<std::unique_ptr<ICanvasDrawable>>& drawableShapes, std::string& word, std::stringstream& lineStream)
{
    if (word == "rectangle")
    {
        SetRectangle(shapes, drawableShapes, lineStream);
    }
    else if (word == "line")
    {
        SetLine(shapes, drawableShapes, lineStream);
    }
    else if (word == "triangle")
    {
        SetTriangle(shapes, drawableShapes, lineStream);
    }
    else if (word == "circle")
    {
        SetCircle(shapes, drawableShapes, lineStream);
    }
}

void GetShapes(std::istream& fIn, std::vector<std::unique_ptr<IShape>>& shapes, std::vector<std::unique_ptr<ICanvasDrawable>>& drawableShapes)
{
    std::string line;
    while (std::getline(fIn, line))
    {
        if (line.empty()) continue;
        std::stringstream lineStream(line);
        std::string word;
        lineStream >> word;
        SetShape(shapes, drawableShapes, word, lineStream);
    }
}

int TryGetShape(int argc, std::vector<std::unique_ptr<IShape>>& shapes, std::vector<std::unique_ptr<ICanvasDrawable>>& drawableShapes, char* argv[])
{
    if (argc == 1)
    {
        GetShapes(std::cin, shapes, drawableShapes);
        return 0;
    }
    else if (argc == 2)
    {
        std::ifstream inFile(argv[1]);
        if (!inFile.is_open())
        {
            std::cout << "ERROR: cannot open " << argv[1] << std::endl;
            return 1;
        }
        GetShapes(inFile, shapes, drawableShapes);
        return 0;
    }
    else
    {
        std::cout << ERROR_MESSAGE_PARAMS << std::endl;
        return 1;
    }
}