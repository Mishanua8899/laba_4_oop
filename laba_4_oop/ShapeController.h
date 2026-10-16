#pragma once
#include <vector>
#include <memory>
#include "IShape.h"

class ShapeController {
public:
    bool Initialize(int argc, char* argv[]);

    void ProcessAndExportInfo() const;

    std::vector<std::unique_ptr<IShape>> ExtractShapes();

private:
    std::vector<std::unique_ptr<IShape>> shapes;

    const IShape* FindMaxAreaShape() const;
    const IShape* FindMaxPerimeterShape() const;
    void PrintMaxShapesInfo(const IShape* maxPerimeterShape, const IShape* maxAreaShape) const;
    void PrintStatistics() const;
    void GenerateInfoFile(const std::vector<std::unique_ptr<IShape>>& drawableShapes, std::string fileName = "shapes_info") const;
    double roundToHundredths(double value);
    const IShape* MaxArea(const std::vector<std::unique_ptr<IShape>>& shapes) const;
    const IShape* MaxPerimeter(const std::vector<std::unique_ptr<IShape>>& shapes) const;
};
