#include "burbujita.h"

burbujita::burbujita(int x, int y ,SDL_Surface *screen ,SDL_Surface* surface)
{
    this->x  = x;
    this->y = y;
    this->surface = surface;
    this->screen = screen;
    this->borrar = false;
    this->tipo="n";
}
burbujita::burbujita()
{
}
burbujita::~burbujita()
{
    //dtor
}

void burbujita::dibujar(){
SDL_Rect offset;

    //Get offsets
    offset.x = x;
    offset.y = y;

    //Blit
    SDL_BlitSurface( surface , NULL, screen, &offset );
}

void burbujita::mover(){
this->x++;

}
void burbujita::logica(int clickx,int clicky){

if(clickx>=x && clickx<=x+surface->w
                    &&clicky >=y&& clicky <=y+surface->h){
                    borrar = true;



}
}

