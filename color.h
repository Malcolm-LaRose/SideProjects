// color.h
#ifndef COLOR_H
#define COLOR_H

#include <SDL.h>

#include <vector>
#include <stdexcept>

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

    static std::vector<int> getColorVector(NamedColor namedColor) {
        switch (namedColor) {
        case WHITE:   return { 255, 255, 255, 255 };
        case BLACK:   return { 0, 0, 0, 255 };
        case RED:     return { 255, 0, 0, 255 };
        case GREEN:   return { 0, 255, 0, 255 };
        case BLUE:    return { 0, 0, 255, 255 };
        case PHSORNG: return { 255, 204, 0, 255 };
        case MAGENTA: return { 255, 0, 255, 255 };
        default:      throw std::invalid_argument("Invalid named color");
        }
    }

    static SDL_Color getSDLColor(NamedColor namedColor) {
        switch (namedColor) {
        case WHITE:   return { 255, 255, 255, 255 };
        case BLACK:   return { 0, 0, 0, 255 };
        case RED:     return { 255, 0, 0, 255 };
        case GREEN:   return { 0, 255, 0, 255 };
        case BLUE:    return { 0, 0, 255, 255 };
        case PHSORNG: return { 255, 204, 0, 255 };
        case MAGENTA: return { 255, 0, 255, 255 };
        default:      throw std::invalid_argument("Invalid named color");
        }
    }
};

#endif // COLOR_H