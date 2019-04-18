/*!
    \file       visible_shape_surface.h
    \brief      Include file for VisibleShapeSurface.
*/

#ifndef VISIBLE_SHAPE_SURFACE_H
#define VISIBLE_SHAPE_SURFACE_H

#include "image_surface.h"
#include "visible_shape.h"
#include <vector>

/*!
    \class      VisibleShapeSurface
    \brief      The surface loaded from a shape
    \details    VisibleShapeSurface is a class that implements ISurface
*/
class VisibleShapeSurface: public ISurface {
    private:
        std::vector<SDL_Surface*> msurface;
        std::vector<SDL_Rect*> mrect;
        std::vector<ImageSurface*> mblock;
        std::vector<SDL_Color> mcolor;
    public:
        VisibleShapeSurface(const VisibleShape &shape);

        virtual ~VisibleShapeSurface();

        virtual int getNum();

        virtual SDL_Surface* get(int i);

        virtual SDL_Rect* getSize(int i);

        virtual SDL_Color getColor(int i);
};

#endif
