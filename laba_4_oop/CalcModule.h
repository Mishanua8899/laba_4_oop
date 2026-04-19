#pragma once

#include <vector>
#include <memory>
#include "IShape.h"

double roundToHundredths(double value);
const IShape* MaxArea(const std::vector<std::unique_ptr<IShape>>& shapes);
const IShape* MaxPerimeter(const std::vector<std::unique_ptr<IShape>>& shapes);