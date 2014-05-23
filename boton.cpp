#include "boton.h"

boton::boton(int x, int y ,SDL_Surface *screen ,SDL_Surface* surface)
{
   this->x  = x;
    this->y = y;
    this->surface = surface;
    this->screen = screen;
    }
boton::boton()
{
    //ctor
}

void boton::dibujar(){
SDL_Rect offset;

    //Get offsets
    offset.x = x;
    offset.y = y;

    //Blit
    SDL_BlitSurface( surface , NULL, screen, &offset );

}

void boton :: liberar(){
SDL_FreeSurface(surface);

}
boton::~boton()
{
    //dtor
}
