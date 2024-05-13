#pragma once

#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <SDL.h>
#include <SDL_image.h>

#include <iostream>


class TextureManager {
public:
	static SDL_Texture* LoadTexture(const char* fileName, SDL_Renderer* renderer) {
	
		SDL_Surface* tempSurface = IMG_Load(fileName);
		SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, tempSurface);
		SDL_FreeSurface(tempSurface);

		if (!tempSurface) {
			std::cout << "Texture not loaded!";
		}

		return tex;
	
	}


private:



};



#endif