/*!
    \file       rgb_color.cpp
    \brief      Implementation file for RGBColor handling.
*/

#include "rgb_color.h"

RGBColor::RGBColor(const int &r, const int &g, const int &b) {
    mr = r; mg = g; mb = b;
}

int RGBColor::getR() const {return mr;}

int RGBColor::getG() const {return mg;}

int RGBColor::getB() const {return mb;}

int RGBColor::cmp(const RGBColor* c) {
    return (mr - c->getR()) * 1e6 + (mg - c->getG()) * 1e3 + (mb - c->getB());
}
