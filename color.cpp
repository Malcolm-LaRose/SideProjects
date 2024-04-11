// color.cpp
#include "color.h"

// Usage
// std::vector<int> white = Color::getColorVector(Color::WHITE);

std::vector<int> Color::getColorVector(Color::NamedColor namedColor) {
    switch (namedColor) {
    case WHITE:
        return { 255, 255, 255, 255 };
    case BLACK:
        return { 0, 0, 0, 255 };
    case RED:
        return { 255, 0, 0, 255 };
    case GREEN:
        return { 0, 255, 0, 255 };
    case BLUE:
        return { 0, 0, 255, 255 };
    case PHSORNG:
        return { 255, 204, 0, 255 }; // 593nm phosphor orange
    case MAGENTA:
        return { 255, 0, 255, 255};
    default:
        throw std::invalid_argument("Invalid named color");
    }
}