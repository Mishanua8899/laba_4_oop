#pragma once
#include <string>

namespace Constants {
    constexpr int WINDOW_WIDTH = 800;
    constexpr int WINDOW_HEIGHT = 600; 
    constexpr int COUNT_OF_COLOR_BYTES = 6;
    constexpr double PI = 3.14;

    constexpr const char* ERROR_MESSAGE_PARSE = "ERROR: cannot parse this line";
    constexpr const char* ERROR_MESSAGE_PARAMS = "ERROR: incorrect number of parameters";
    constexpr const char* ERROR_MESSAGE_PARSE_COLOR = "hex color must be described in 6 symbols";

    const std::string OUT_OF_RANGE_MESSAGE = "Index out of bounds in GetShape";
    const std::string WINDOW_NAME = "Shapes Viewer";
    const std::string OUT_OF_RANGE_MESSAGE_DRAWING = "Index out of bounds in GetShape";
    const std::string TYPE_LINE = "line";
    const std::string TYPE_TRIANGLE = "triangle";
    const std::string TYPE_CIRCLE = "circle";
    const std::string TYPE_COMPOSITE = "composite";
    const std::string TYPE_RECTANGLE = "rectangle";
    const std::string POINT_POS = " left top ";
    const std::string START_POINT = "start";
    const std::string END_POINT = "end";
    const std::string MAX_AREA = "Max Area Shape: ";
    const std::string MAX_PERIMETR = "Max Perimetr Shape: ";
    const std::string AREA_INFO = ", area=";
    const std::string PERIMETR_INFO = ", perimeter=";
    const std::string WIDTH_INFO = ", width=";
    const std::string HEIGHT_INFO = ", height=";
    const std::string OUTLINECOLOR_INFO = ", outlineColor=#";
    const std::string FILLCOLOR_INFO = ", fillColor=#";
    const std::string VERTICES = "vertices";

    const int HALFBITES_COUNT = 6;
    constexpr int RGBMask = 0xFFFFFF;
    const int ALPHA_SHIFT = 8;
    const int ALPHA_SHIFT_MASK = 0x000000FF;
}