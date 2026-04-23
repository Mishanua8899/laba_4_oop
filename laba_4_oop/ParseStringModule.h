#pragma once

#include <vector>
#include <memory>
#include <iosfwd> 

class IShape;
class ICanvasDrawable;
void GetShapes(std::istream& fIn, std::vector<std::unique_ptr<IShape>>& shapes, std::vector<std::unique_ptr<ICanvasDrawable>>& drawableShapes);
int TryGetShape(int argc, std::vector<std::unique_ptr<IShape>>& shapes, std::vector<std::unique_ptr<ICanvasDrawable>>& drawableShapes, char* argv[]);