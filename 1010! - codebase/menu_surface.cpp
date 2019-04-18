/*!
    \file       menu_surface.cpp
    \brief      Implementation file for MenuSurface.
*/

#include "menu_surface.h"

MenuSurface::MenuSurface(Menu &menu) {
    mtitle = new FontSurface(menu.getTitle());
    msurface.push_back(mtitle->get(0));
    mrect.push_back(mtitle->getSize(0));
    for (int i = 0; i < menu.numButton(); ++i) {
        mbutton.push_back(new ButtonSurface(*menu.getButton(i)));
        for (int j = 0; j < mbutton.back()->getNum(); ++j) {
            msurface.push_back(mbutton.back()->get(j));
            mrect.push_back(mbutton.back()->getSize(j));
        }
    }
}

MenuSurface::~MenuSurface() {
    delete mtitle;
    for (int i = 0; i < mbutton.size(); ++i) delete mbutton[i];
}

int MenuSurface::getNum() {return msurface.size();}

SDL_Surface* MenuSurface::get(int i) {return msurface[i];}

SDL_Rect* MenuSurface::getSize(int i) {return mrect[i];}

SDL_Color MenuSurface::getColor(int i) {return {0xFF, 0xFF, 0xFF, 0xFF};}
