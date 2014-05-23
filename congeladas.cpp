#include "congeladas.h"

congeladas::congeladas(int x, int y, SDL_Surface *screen,SDL_Surface * surface)
{
    this->x  = x;
    this->y = y;
    this->surface = surface;
    this->screen = screen;
    this->borrar = false;
    this->tipo= "c";
}
congeladas::congeladas()
{
    //ctor
}


congeladas::~congeladas()
{
    //dtor
}
