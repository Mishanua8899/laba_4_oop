#pragma once

#include <vector>
#include <memory>
#include <iosfwd> 

class IShape;

void GetShapes(std::istream& fIn, std::vector<std::unique_ptr<IShape>>& shapes);
int TryGetShape(int argc, std::vector<std::unique_ptr<IShape>>& shapes, char* argv[]);