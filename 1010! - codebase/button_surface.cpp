/*!
    \file       button_surface.cpp
    \brief      Implementation file for ButtonSurface.
*/

#include "button_surface.h"

ButtonSurface::ButtonSurface(const Button &button) {
    micon = new ImageSurface(button.getIcon());
    msurface.push_back(micon->get(0));
    mrect.push_back(micon->getSize(0));

    mtitle = new FontSurface(button.getTitle());
    msurface.push_back(mtitle->get(0));
    mrect.push_back(mtitle->getSize(0));
}

ButtonSurface::~ButtonSurface() {
    delete micon; delete mtitle;
}

int ButtonSurface::getNum() {return msurface.size();}

SDL_Surface* ButtonSurface::get(int i) {return msurface[i];}

SDL_Rect* ButtonSurface::getSize(int i) {return mrect[i];}

SDL_Color ButtonSurface::getColor(int i) {return {0xFF, 0xFF, 0xFF, 0xFF};}
