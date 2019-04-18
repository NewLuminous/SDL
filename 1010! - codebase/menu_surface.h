/*!
    \file       menu_surface.h
    \brief      Include file for MenuSurface.
*/

#ifndef MENU_SURFACE_H
#define MENU_SURFACE_H

#include "button_surface.h"
#include "menu.h"

/*!
    \class      MenuSurface
    \brief      The surface loaded from a menu
    \details    MenuSurface is a class that implements ISurface
*/
class MenuSurface: public ISurface {
    private:
        std::vector<SDL_Surface*> msurface;
        std::vector<SDL_Rect*> mrect;
        FontSurface* mtitle;
        std::vector<ButtonSurface*> mbutton;
    public:
        MenuSurface(Menu &menu);

        virtual ~MenuSurface();

        virtual int getNum();

        virtual SDL_Surface* get(int i);

        virtual SDL_Rect* getSize(int i);

        virtual SDL_Color getColor(int i);
};

#endif
