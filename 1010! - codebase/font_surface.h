/*!
    \file       font_surface.h
    \brief      Include file for FontSurface.
*/

#ifndef FONT_SURFACE_H
#define FONT_SURFACE_H

#include "isurface.h"
#include "font.h"
#include <vector>

/*!
    \class      FontSurface
    \brief      The surface loaded from a font
    \details    FontSurface is a class that implements ISurface
*/
class FontSurface: public ISurface {
    private:
        std::vector<SDL_Surface*> msurface;
        std::vector<SDL_Rect*> mrect;
        SDL_Color mcolor = {0xFF, 0xFF, 0xFF};
    public:
        virtual void logError(const std::string &msg, const std::string &error, bool fatal);

        FontSurface(const Font &font);

        virtual ~FontSurface();

        virtual int getNum();

        virtual SDL_Surface* get(int i);

        virtual SDL_Rect* getSize(int i);

        virtual SDL_Color getColor(int i);
};

#endif
