/*!
    \file       image.cpp
    \brief      Implementation file for Image handling.
*/

#include "image.h"

Image::Image(const std::string &type, std::string name, const std::string &location) {
    mlocation = location;
    //if (mlocation.size() && (mlocation[mlocation.size() - 1] != '/')) mlocation += '/';
    mname = name;
    mtype = type;
}

std::string Image::getPath() const {
    if (mname.size()) return mlocation + mname + "." + mtype; else return mlocation;
}

void Image::setCoordinate(const int &x, const int &y) {mx = x; my = y;}

int Image::getX() const {return mx;}

int Image::getY() const {return my;}

void Image::setSize(const unsigned int &width, const unsigned int &height) {mw = width; mh = height;}

int Image::getWidth() const {return mw;}

int Image::getHeight() const {return mh;}

void Image::setColor(const RGBColor &color) {mcolor = color;}

RGBColor Image::getColor() const {return mcolor;}
