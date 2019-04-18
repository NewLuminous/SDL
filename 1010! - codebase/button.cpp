/*!
    \file       button.cpp
    \brief      Implementation file for Button handling.
*/

#include "button.h"

Button::Button() {}

Button::~Button() {}

Button::Button(const Image &icon, Font title) {micon = icon; mtitle = title;}

Button::Button(const Font &title) {mtitle = title;}

void Button::setIcon(const Image &icon) {micon = icon;}

Image Button::getIcon() const {return micon;}

void Button::setTitle(const Font &title) {mtitle = title;}

Font Button::getTitle() const {return mtitle;}

void Button::setColor(const RGBColor &color) {mtitle.setColor(color);}

RGBColor Button::getColor() const {return mtitle.getColor();}

void Button::setCoordinate(const int &x, const int &y) {
    micon.setCoordinate(x, y);
    mtitle.setCoordinate(x + mh * 2, y);
}

int Button::getX() const {return micon.getX();}

int Button::getY() const {return micon.getY();}

void Button::setHeight(const unsigned int &height) {
    mh = height;
    micon.setSize(mh, mh);
    mtitle.setHeight(mh);
    mtitle.setWidth(mw - mh * 2);
    mtitle.setCoordinate(getX() + mh * 2, getY());
}

int Button::getHeight() const {return mh;}

void Button::setWidth(const unsigned int &width) {
    mw = mtitle.empty() ? mh : width;
    mtitle.setWidth(mw - mh * 2);
}

int Button::getWidth() const {return mw;}

bool Button::inside(const int &x, const int &y) {
    return (getX() <= x && x <= getX() + getWidth() - 1 && getY() <= y && y <= getY() + getHeight() - 1);
}
