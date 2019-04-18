/*!
    \file       font.h
    \brief      Implementation file for Font handling.
*/

#include "font.h"

const int Font::DEFAULT_SIZE = 72;

Font::Font(const std::string &source, const std::string &text, const int font_size) {
    msrc = source; mtext = text; msize = font_size;
}

std::string Font::getSource() const {return msrc;}

std::string Font::getText() const {return mtext;}

bool Font::empty() const {return (int)mtext.size() == 0;}

int Font::getFontSize() const {return msize;}

void Font::setColor(const RGBColor &color) {mcolor = color;}

RGBColor Font::getColor() const {return mcolor;}

void Font::setCoordinate(const int &x, const int &y) {mx = x; my = y;}

int Font::getX() const {return mx;}

int Font::getY() const {return my;}

void Font::setHeight(const unsigned int &height) {
    if (empty()) return;
    mh = height;
}

int Font::getHeight() const {return mh;}

void Font::setWidth(const unsigned int &width) {if (!empty()) mw = width;}

int Font::getWidth() const {return mw;}
