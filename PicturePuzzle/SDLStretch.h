#ifndef INCLUDE_SDLSTRETCH
#define INCLUDE_SDLSTRETCH

//#include "../global.h"
#include "SDL.h"

#define sign(x) ((x)>0 ? 1:-1)

void SDL_StretchSurface(SDL_Surface* src_surface, SDL_Rect* src_rect, SDL_Surface* dst_surface, SDL_Rect* dst_rect, Uint32* voiLUT = NULL);
void SDL_StretchSurface(SDL_Surface* src_surface, int xs1, int ys1, int xs2, int ys2, SDL_Surface* dst_surface, int xd1, int yd1, int xd2, int yd2, Uint32* voiLUT = NULL);

#endif
