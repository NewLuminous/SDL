/*!
    \file       shape.cpp
    \brief      Implementation file for Shape handling.
*/

#include "shape.h"

const int Shape::UNDEFINED_NUM = -1;

Shape::~Shape() {}

Shape::Shape() {}

Shape::Shape(const unsigned int &row, const unsigned int &col) {
    mbitmap.resize(row, std::vector<bool>(col, true));
    mcol = col;
    mrow = row;
    mnum_bit = mcol * mrow;
}

Shape::Shape(const std::vector<std::vector<bool> > &bitmap) {
    mbitmap = bitmap;
    mrow = mbitmap.size();
    if (mrow) mcol = mbitmap[0].size();
    mnum_bit = -1;
}

void Shape::fillBitMap(const unsigned int &row, const unsigned int &col) {
    mbitmap.resize(row, std::vector<bool>(col, true));
    mcol = col;
    mrow = row;
    mnum_bit = mcol * mrow;
}

void Shape::setBitMap(const std::vector<std::vector<bool> > &bitmap) {
    mbitmap = bitmap;
    mrow = mbitmap.size();
    if (mrow) mcol = mbitmap[0].size();
    mnum_bit = -1;
}

int Shape::getNumBit() {
    if (mnum_bit >= 0) return mnum_bit;
    for (int i = 0; i < mrow; ++i)
        for (int j = 0; j < mcol; ++j)
            if (mbitmap[i][j]) ++mnum_bit;
    return ++mnum_bit;
}

void Shape::setBit(const int &i, const int &j, const bool &k) {
    if (mnum_bit >= 0) mnum_bit -= (mbitmap[i][j] ^ k);
    mbitmap[i][j] = k;
}

bool Shape::getBit(const int &i, const int &j) const {return mbitmap[i][j];}

int Shape::getColNum() const {return mcol;}

int Shape::getRowNum() const {return mrow;}

void Shape::del() {mcol = mrow = 0;}
