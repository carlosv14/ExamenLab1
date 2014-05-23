#include "badbubbles.h"

badbubbles::badbubbles()
{
    //ctor
}

badbubbles::badbubbles(int x, int y, SDL_Surface *screen,SDL_Surface * surface)
{
    this->x  = x;
    this->y = y;
    this->surface = surface;
    this->screen = screen;
    this->borrar = false;
    this->tipo= "b";
}


badbubbles::~badbubbles()
{
    //dtor
}
