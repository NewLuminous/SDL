/*!
    \file       isurface.h
    \brief      Include file for ISurface.
*/

#ifndef ISURFACE_H
#define ISURFACE_H

#include <SDL.h>

/*!
    \class      ISurface
    \brief      An interface of surface.
*/
class ISurface {
    public:
        ISurface() {}
        virtual ~ISurface() {}

        virtual int getNum() = 0;

        virtual SDL_Surface* get(int) = 0;

        virtual SDL_Rect* getSize(int) = 0;

        virtual SDL_Color getColor(int) = 0;
};

#endif
