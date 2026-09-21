#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <string>
#include "IShape.h"

void GenerateShapesInfoFile(const std::vector<std::unique_ptr<IShape>>& drawableShapes, std::string fileName = "shapes_info.txt");
void PrintMaxShapesInfo(const IShape* maxPerimeterShape, const IShape* maxAreaShape);