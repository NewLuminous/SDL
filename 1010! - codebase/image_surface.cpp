/*!
    \file       image_surface.cpp
    \brief      Implementation file for ImageSurface.
*/

#include "image_surface.h"
#include <SDL_image.h>
#include <iostream>
#include <cstdlib>

void ImageSurface::logError(const std::string &msg, const std::string &error, bool fatal) {
    std::cout << msg << " Error: " << error << std::endl;
    if (fatal) {SDL_Quit(); exit(1);}
}

ImageSurface::ImageSurface(const Image &img) {
    msurface.push_back(IMG_Load(img.getPath().c_str()));
    if (msurface.back() == nullptr) logError("IMG_Load", IMG_GetError(), true);
    SDL_Rect* rect = new SDL_Rect();
    rect->x = img.getX();
    rect->y = img.getY();
    rect->w = img.getWidth();
    rect->h = img.getHeight();
    mrect.push_back(rect);
    mcolor.push_back({img.getColor().getR(), img.getColor().getG(), img.getColor().getB(), 0});
}

ImageSurface::~ImageSurface() {
    SDL_FreeSurface(msurface[0]);
    delete mrect[0];
}

int ImageSurface::getNum() {return msurface.size();}

SDL_Surface* ImageSurface::get(int i) {return msurface[i];}

SDL_Rect* ImageSurface::getSize(int i) {return mrect[i];}

SDL_Color ImageSurface::getColor(int i) {return mcolor[i];}
