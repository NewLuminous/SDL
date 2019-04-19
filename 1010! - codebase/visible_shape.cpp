/*!
    \file       visible_shape.cpp
    \brief      Implementation file for VisibleShape handling.
*/

#include "visible_shape.h"

VisibleShape::VisibleShape() {}

VisibleShape::~VisibleShape() {}

VisibleShape::VisibleShape(const unsigned int &row, const unsigned int &col) {fillBitMap(row, col);}

VisibleShape::VisibleShape(const std::vector<std::vector<bool> > &bitmap) {setBitMap(bitmap);}

void VisibleShape::setUnitSquareImg(Image img) {
    img.setCoordinate(getX(), getY());
    img.setSize(munit_square_img.getWidth(), munit_square_img.getHeight());
    munit_square_img = img;
}

Image VisibleShape::getUnitSquareImg() const {return munit_square_img;}

void VisibleShape::setCoordinate(const int &x, const int &y) {munit_square_img.setCoordinate(x, y);}

int VisibleShape::getX() const {return munit_square_img.getX();}

int VisibleShape::getY() const {return munit_square_img.getY();}

void VisibleShape::setColor(const RGBColor &color) {mcolor = color;}

RGBColor VisibleShape::getColor() const {return mcolor;}

void VisibleShape::setUnitSquareSize(const unsigned int &_size) {munit_square_img.setSize(_size, _size);}

int VisibleShape::getUnitSquareSize() const {return munit_square_img.getHeight();}

int VisibleShape::getWidth() const {return getUnitSquareSize() * getColNum();}

int VisibleShape::getHeight() const {return getUnitSquareSize() * getRowNum();}

bool VisibleShape::inside(const int &mouse_x, const int &mouse_y) {
    mmouse_x = mouse_x - getX();
    mmouse_y = mouse_y - getY();
    return (-getUnitSquareSize() / 2 <= mmouse_y && mmouse_y < getHeight() + getUnitSquareSize() / 2
            && -getUnitSquareSize() / 2 <= mmouse_x && mmouse_x < getWidth() + getUnitSquareSize() / 2
            && getBit(mmouse_y / getUnitSquareSize(), mmouse_x / getUnitSquareSize()));
}

int VisibleShape::getMouseX() const {return mmouse_x;}

int VisibleShape::getMouseY() const {return mmouse_y;}
