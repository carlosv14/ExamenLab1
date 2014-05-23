#ifndef BADBUBBLES_H
#define BADBUBBLES_H
#include "burbujita.h"

class badbubbles : public burbujita
{
    public:

        badbubbles(int x, int y, SDL_Surface *screen,SDL_Surface * surface);
        badbubbles();
        virtual ~badbubbles();
    protected:
    private:
};

#endif // BADBUBBLES_H
