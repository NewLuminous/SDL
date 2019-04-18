/*!
    \file       board_surface.h
    \brief      Include file for BoardSurface.
*/

#ifndef BOARD_SURFACE_H
#define BOARD_SURFACE_H

#include "image_surface.h"
#include "board.h"
#include <vector>

/*!
    \class      BoardSurface
    \brief      The surface loaded from a board
    \details    BoardSurface is a class that implements ISurface
*/
class BoardSurface: public ISurface {
    private:
        std::vector<SDL_Surface*> msurface;
        std::vector<SDL_Rect*> mrect;
        std::vector<ImageSurface*> mblock;
        std::vector<SDL_Color> mcolor;
    public:
        BoardSurface(const Board &board);

        virtual ~BoardSurface();

        virtual int getNum();

        virtual SDL_Surface* get(int i);

        virtual SDL_Rect* getSize(int i);

        virtual SDL_Color getColor(int i);
};

#endif
