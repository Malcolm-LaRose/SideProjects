// color.h
#pragma once

#ifndef COLOR_H
#define COLOR_H



#include <SDL.h>

#include <vector>
#include <stdexcept>

// Use Color::function(Color::namedColor)
// or using namespace Color; --> (risky) 
// function(namedColor) 

class Color {
public:

    enum NamedColor {
        WHITE,
        BLACK,
        RED,
        GREEN,
        BLUE,
        PHSORNG,
        MAGENTA,
        DRKGRY,
        EIGENGRAU,
        LANDLORDWHITE,
        TRANSP
    };

    static std::vector<int> getRGBAColorVector(NamedColor namedColor) {
        // { r, g, b, opacity }
        switch (namedColor) {
        case WHITE:   return { 255, 255, 255, 255 };
        case BLACK:   return { 0, 0, 0, 255 };
        case RED:     return { 255, 0, 0, 255 };
        case GREEN:   return { 0, 255, 0, 255 };
        case BLUE:    return { 0, 0, 255, 255 };
        case PHSORNG: return { 255, 204, 0, 255 };
        case MAGENTA: return { 255, 0, 255, 255 };
        case DRKGRY: return { 55, 55, 55, 255 };
        case EIGENGRAU: return { 22, 22, 29, 255 };
        case LANDLORDWHITE: return { 250, 249, 246, 255 };
        case TRANSP: return { 0, 0, 0, 0 };
        default:      throw std::invalid_argument("Invalid named color");
        }
    }

    static std::vector<int> getRGBColorVector(NamedColor namedColor) {
        // { r, g, b }
        switch (namedColor) {
        case WHITE:   return { 255, 255, 255 };
        case BLACK:   return { 0, 0, 0 };
        case RED:     return { 255, 0, 0 };
        case GREEN:   return { 0, 255, 0 };
        case BLUE:    return { 0, 0, 255 };
        case PHSORNG: return { 255, 204, 0 };
        case MAGENTA: return { 255, 0, 255 };
        case DRKGRY: return { 55, 55, 55, };
        case EIGENGRAU: return { 22, 22, 29, 255 };
        case LANDLORDWHITE: return { 250, 249, 246, 255 };
        case TRANSP: return { 0, 0, 0, 0 };
        default:      throw std::invalid_argument("Invalid named color");
        }
    }

    static SDL_Color getSDLColor(NamedColor namedColor) {
        // { r, g, b, opacity }
        switch (namedColor) {
        case WHITE:   return { 255, 255, 255, 255 };
        case BLACK:   return { 0, 0, 0, 255 };
        case RED:     return { 255, 0, 0, 255 };
        case GREEN:   return { 0, 255, 0, 255 };
        case BLUE:    return { 0, 0, 255, 255 };
        case PHSORNG: return { 255, 204, 0, 255 };
        case MAGENTA: return { 255, 0, 255, 255 };
        case DRKGRY: return { 55, 55, 55, 255 };
        case EIGENGRAU: return { 22, 22, 29, 255 };
        case LANDLORDWHITE: return { 250, 249, 246, 255 };
        case TRANSP: return { 0, 0, 0, 0 };
        default:      throw std::invalid_argument("Invalid named color");
        }
    }
};

#endif // COLOR_H