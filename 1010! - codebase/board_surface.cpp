/*!
    \file       board_surface.cpp
    \brief      Implementation file for BoardSurface.
*/

#include "board_surface.h"

BoardSurface::BoardSurface(const Board &board) {
    for (int i = 0; i < board.getRowNum(); ++i)
        for (int j = 0; j < board.getColNum(); ++j) {
            Image img = board.getUnitSquareImg();
            img.setCoordinate(board.getX() + j * board.getUnitSquareSize(), board.getY() + i * board.getUnitSquareSize());
            img.setColor(board.getUnitSquareColor(i, j));
            mblock.push_back(new ImageSurface(img));
            msurface.push_back(mblock.back()->get(0));
            mrect.push_back(mblock.back()->getSize(0));
            mcolor.push_back({img.getColor().getR(), img.getColor().getG(), img.getColor().getB(), 0});
        }
}

BoardSurface::~BoardSurface() {
    for (int i = 0; i < mblock.size(); ++i) delete mblock[i];
}

int BoardSurface::getNum() {return msurface.size();}

SDL_Surface* BoardSurface::get(int i) {return msurface[i];}

SDL_Rect* BoardSurface::getSize(int i) {return mrect[i];}

SDL_Color BoardSurface::getColor(int i) {return mcolor[i];}
