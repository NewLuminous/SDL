/*!
    \file       image_surface.h
    \brief      Include file for ImageSurface.
*/

#ifndef IMAGE_SURFACE_H
#define IMAGE_SURFACE_H

#include "isurface.h"
#include "image.h"
#include <vector>

/*!
    \class      ImageSurface
    \brief      The surface loaded from an image
    \details    ImageSurface is a class that implements ISurface
*/
class ImageSurface: public ISurface {
    private:
        std::vector<SDL_Surface*> msurface;
        std::vector<SDL_Rect*> mrect;
        std::vector<SDL_Color> mcolor;
    public:
        virtual void logError(const std::string &msg, const std::string &error, bool fatal);

        ImageSurface(const Image &img);

        virtual ~ImageSurface();

        virtual int getNum();

        virtual SDL_Surface* get(int i);

        virtual SDL_Rect* getSize(int i);

        virtual SDL_Color getColor(int i);
};

#endif
