/*!
    \file       visible_shape_surface.cpp
    \brief      Implementation file for VisibleShapeSurface.
*/

#include "visible_shape_surface.h"

VisibleShapeSurface::VisibleShapeSurface(const VisibleShape &shape) {
    for (int i = 0; i < shape.getRowNum(); ++i)
        for (int j = 0; j < shape.getColNum(); ++j)
            if (shape.getBit(i, j)) {
                Image img = shape.getUnitSquareImg();
                img.setCoordinate(shape.getX() + j * shape.getUnitSquareSize(), shape.getY() + i * shape.getUnitSquareSize());
                img.setColor(shape.getColor());
                mblock.push_back(new ImageSurface(img));
                msurface.push_back(mblock.back()->get(0));
                mrect.push_back(mblock.back()->getSize(0));
                mcolor.push_back({img.getColor().getR(), img.getColor().getG(), img.getColor().getB()});
            }
}

VisibleShapeSurface::~VisibleShapeSurface() {
    for (int i = 0; i < mblock.size(); ++i) delete mblock[i];
}

int VisibleShapeSurface::getNum() {return msurface.size();}

SDL_Surface* VisibleShapeSurface::get(int i) {return msurface[i];}

SDL_Rect* VisibleShapeSurface::getSize(int i) {return mrect[i];}

SDL_Color VisibleShapeSurface::getColor(int i) {return mcolor[i];}
