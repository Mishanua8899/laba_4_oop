#include "OutputModule.h"       
void GenerateShapesInfoFile(const std::vector<std::unique_ptr<IShape>>& drawableShapes, std::string fileName)
{
    std::ofstream outFile(fileName);
    if (!outFile.is_open())
    {
        return; 
    }

    for (const auto& shape : drawableShapes)
    {
        if (shape) 
        {
            outFile << shape->ToString() << "\n";
        }
    }

}

void PrintMaxShapesInfo(const IShape* maxPerimeterShape, const IShape* maxAreaShape)
{
    std::cout << "Max Area Shape: " << std::endl;
    std::cout << maxAreaShape->ToString() << std::endl;
    std::cout << "Max Perimeter Shape: " << std::endl;
    std::cout << maxPerimeterShape->ToString() << std::endl;
}
