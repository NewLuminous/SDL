/*!
    \file       button_surface.h
    \brief      Include file for ButtonSurface.
*/

#ifndef BUTTON_SURFACE_H
#define BUTTON_SURFACE_H

#include "image_surface.h"
#include "font_surface.h"
#include "button.h"

/*!
    \class      ButtonSurface
    \brief      The surface loaded from a button
    \details    ButtonSurface is a class that implements ISurface
*/
class ButtonSurface: public ISurface {
    private:
        std::vector<SDL_Surface*> msurface;
        std::vector<SDL_Rect*> mrect;
        ImageSurface* micon;
        FontSurface* mtitle;
    public:
        ButtonSurface(const Button &button);

        virtual ~ButtonSurface();

        virtual int getNum();

        virtual SDL_Surface* get(int i);

        virtual SDL_Rect* getSize(int i);

        virtual SDL_Color getColor(int i);
};

#endif
