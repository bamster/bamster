#include "sdl.h"
#include <SDL/SDL.h> 
#include <SDL/SDL_image.h>
 
SDL_Surface* proper_SDL_LoadBMP(const char* File) {
    SDL_Surface* tempSurface = NULL;
    SDL_Surface* returnSurface = NULL;
 
    if((tempSurface = SDL_LoadBMP(File)) == NULL) {
	fprintf(stderr, "Couldn't load file: %s\n", File);	
        return NULL;
    }
 
    returnSurface = SDL_DisplayFormat(tempSurface); // this is supposed to do magic
    SDL_FreeSurface(tempSurface);
 
    return returnSurface;
}

SDL_Surface* properIMGLoad(const char* File) {
    SDL_Surface* tempSurface = NULL;
    SDL_Surface* returnSurface = NULL;
 
    if((tempSurface = SDL_LoadBMP(File)) == NULL) {
	fprintf(stderr, "Couldn't load file: %s\n", File);	
        return NULL;
    }
 
    returnSurface = SDL_DisplayFormatAlpha(tempSurface); // this is supposed to do magic
    SDL_FreeSurface(tempSurface);
 
    return returnSurface;
}
