#ifndef CONGELADAS_H
#define CONGELADAS_H
#include "burbujita.h"

class congeladas : public burbujita
{
    public:
        congeladas(int x, int y, SDL_Surface *screen,SDL_Surface * surface);
        congeladas();
        void logica(int clickx, int clicky);
        virtual ~congeladas();
    protected:
    private:
};

#endif // CONGELADAS_H
