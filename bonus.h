#ifndef BONUS_H
#define BONUS_H
#include "burbujita.h"

class bonus : public burbujita
{
    public:

        bonus();
        bonus(int x, int y, SDL_Surface *screen,SDL_Surface * surface);
        virtual ~bonus();
    protected:
    private:
};

#endif // BONUS_H
