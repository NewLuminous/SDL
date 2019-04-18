/*!
    \file       font_surface.cpp
    \brief      Implementation file for FontSurface.
*/

#include "font_surface.h"
#include <SDL_ttf.h>
#include <iostream>
#include <cstdlib>

void FontSurface::logError(const std::string &msg, const std::string &error, bool fatal) {
    std::cout << msg << " Error: " << error << std::endl;
    if (fatal) {SDL_Quit(); exit(1);}
}

FontSurface::FontSurface(const Font &font) {
    TTF_Font* ttf_font = TTF_OpenFont(font.getSource().c_str(), font.getFontSize());
    if (ttf_font == nullptr) logError("OpenFont", TTF_GetError(), true);
    SDL_Color color = {font.getColor().getR(), font.getColor().getG(), font.getColor().getB()};
    msurface.push_back(TTF_RenderText_Solid(ttf_font, font.getText().c_str(), color));
    if (msurface.back() == nullptr) logError("TTF_RenderText_Solid", TTF_GetError(), true);
    SDL_Rect* rect = new SDL_Rect();
    rect->x = font.getX();
    rect->y = font.getY();
    rect->w = font.getWidth();
    rect->h = font.getHeight();
    mrect.push_back(rect);
    TTF_CloseFont(ttf_font);
}

FontSurface::~FontSurface() {
    SDL_FreeSurface(msurface[0]);
    delete mrect[0];
}

int FontSurface::getNum() {return msurface.size();}

SDL_Surface* FontSurface::get(int i) {return msurface[i];}

SDL_Rect* FontSurface::getSize(int i) {return mrect[i];}

SDL_Color FontSurface::getColor(int i) {return mcolor;}
