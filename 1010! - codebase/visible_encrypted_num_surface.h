/*!
    \file       visible_encrypted_num_surface.h
    \brief      Include file for VisibleEncryptedNumSurface.
*/

#ifndef VISIBLE_ENCRYPTED_NUM_SURFACE_H
#define VISIBLE_ENCRYPTED_NUM_SURFACE_H

#include "image_surface.h"
#include "visible_encrypted_num.h"
#include <vector>

/*!
    \class      VisibleEncryptedNumSurface
    \brief      The surface loaded from an encrypted number
    \details    VisibleEncryptedNumSurface is a class that implements ISurface
*/
class VisibleEncryptedNumSurface: public ISurface {
    private:
        std::vector<SDL_Surface*> msurface;
        std::vector<SDL_Rect*> mrect;
        std::vector<ImageSurface*> mdigit;
    public:
        VisibleEncryptedNumSurface(const VisibleEncryptedNum &num);

        virtual ~VisibleEncryptedNumSurface();

        virtual int getNum();

        virtual SDL_Surface* get(int i);

        virtual SDL_Rect* getSize(int i);

        virtual SDL_Color getColor(int i);
};

#endif
