/*!
    \file       visible_encrypted_num_surface.cpp
    \brief      Implementation file for VisibleEncryptedNumSurface.
*/

#include "visible_encrypted_num_surface.h"

VisibleEncryptedNumSurface::VisibleEncryptedNumSurface(const VisibleEncryptedNum &num) {
    std::vector<int> d;
    for (int val = num.val(); val; val /= 10) d.push_back(val % 10);
    while ((int)d.size() < 6) d.push_back(0);
    for (int i = 0; i < d.size(); ++i) {
        Image img = num.getDigitImage(d[i]);
        img.setCoordinate(num.getX() + ((int)d.size() - i - 1) * num.getDWidth(), num.getY());
        mdigit.push_back(new ImageSurface(img));
        msurface.push_back(mdigit.back()->get(0));
        mrect.push_back(mdigit.back()->getSize(0));
    }
}

VisibleEncryptedNumSurface::~VisibleEncryptedNumSurface() {
    for (int i = 0; i < mdigit.size(); ++i) delete mdigit[i];
}

int VisibleEncryptedNumSurface::getNum() {return msurface.size();}

SDL_Surface* VisibleEncryptedNumSurface::get(int i) {return msurface[i];}

SDL_Rect* VisibleEncryptedNumSurface::getSize(int i) {return mrect[i];}

SDL_Color VisibleEncryptedNumSurface::getColor(int i) {return {0xFF, 0xFF, 0xFF, 0xFF};}
