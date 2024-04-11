// color.h
#ifndef COLOR_H
#define COLOR_H

#include <vector>
#include <stdexcept> // for std::invalid_argument

class Color {
public:
    enum NamedColor {
        WHITE,
        BLACK,
        RED,
        GREEN,
        BLUE,
        PHSORNG,
        MAGENTA
    };

    static std::vector<int> getColorVector(NamedColor namedColor);

private:
    Color() = default; // Use default constructor to prevent instantiation
};

#endif // COLOR_H