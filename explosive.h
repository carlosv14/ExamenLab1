#ifndef EXPLOSIVE_H
#define EXPLOSIVE_H
#include <SDL/SDL.h>
#include "burbujita.h"
class explosive : public burbujita
{
    public:
        explosive(int x, int y, SDL_Surface *screen, SDL_Surface * surface);
        explosive();
        virtual ~explosive();
         void logica(int clickx, int clicky);
    protected:
    private:
};

#endif // EXPLOSIVE_H
