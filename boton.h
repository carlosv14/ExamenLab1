#ifndef BOTON_H
#define BOTON_H
#include <SDL/SDL.h>

class boton
{
    public:
      SDL_Surface * surface ;
            int x;
            int y;
            SDL_Surface * screen;
        boton();
        boton(int x, int y, SDL_Surface *screen,SDL_Surface * surface);
        void liberar();
        void dibujar();
        virtual ~boton();
    protected:
    private:
};

#endif // BOTON_H
