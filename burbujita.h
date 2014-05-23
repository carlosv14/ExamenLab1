#ifndef BURBUJITA_H
#define BURBUJITA_H
#include <SDL/SDL.h>
#include <list>
#include <iostream>
using namespace std;
class burbujita
{
    public:
         SDL_Surface * surface ;
            int x;
            int y;
            string tipo;
            SDL_Surface * screen;
            bool borrar;
        burbujita();
        burbujita(int x, int y, SDL_Surface *screen,SDL_Surface * surface);
        void dibujar();
        void mover();
        void logica(int clickx, int clicky);
        virtual ~burbujita();
    protected:
    private:
};

#endif // BURBUJITA_H
