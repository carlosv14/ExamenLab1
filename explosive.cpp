#include "explosive.h"

explosive::explosive(int x, int y, SDL_Surface *screen,SDL_Surface * surface)
{
    this->x  = x;
    this->y = y;
    this->surface = surface;
    this->screen = screen;
    this->borrar = false;
    this->tipo= "e";
}

explosive::~explosive()
{
    //dtor
}

void explosive::logica(int clickx,int clicky){

if(clickx>=x && clickx<=x+surface->w
                    &&clicky >=y&& clicky <=y+surface->h){
                    borrar = true;

}
}
