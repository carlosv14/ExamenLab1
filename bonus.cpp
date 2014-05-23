#include "bonus.h"

bonus::bonus(int x, int y, SDL_Surface *screen,SDL_Surface * surface)
{   this->x  = x;
    this->y = y;
    this->surface = surface;
    this->screen = screen;
    this->borrar = false;
    this->tipo="bon";
}

bonus::bonus()
{
    //ctor
}

bonus::~bonus()
{
    //dtor
}

