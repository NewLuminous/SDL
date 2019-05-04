/*!
    \file       board.h
    \brief      Include file for Board handling.
*/

#ifndef BOARD_H
#define BOARD_H

#include "visible_shape.h"
#include "encrypted_num.h"

/*!
    \class      Board
    \brief      The board where pieces are placed.
    \details    Board is a derived class from VisibleShape.
*/
class Board: public VisibleShape {
    private:
        std::vector<std::vector<RGBColor> > mcolor_map = std::vector<std::vector<RGBColor> >(getRowNum(), std::vector<RGBColor>(getColNum(), getColor()));
        std::vector<std::vector<bool> > mplacement = std::vector<std::vector<bool> >(getRowNum(), std::vector<bool>(getColNum(), false));
        std::vector<int> mrow = std::vector<int>(getRowNum(), 0);
        std::vector<int> mcol = std::vector<int>(getColNum(), 0);
    public:
        using VisibleShape::VisibleShape;

        virtual ~Board();

        /*!
            \brief      Set color of the whole board.
            \sa         Shape::setColor()
        */
        virtual void setColor(const RGBColor &color);

        /*!
            \sa         getUnitSquareColor()
        */
        virtual void setUnitSquareColor(const int &i, const int &j, const RGBColor &c);

        /*!
            \sa         setUnitSquareColor()
        */
        virtual RGBColor getUnitSquareColor(const int &i, const int &j) const;

        /*!
            \brief      Clear the board.
        */
        virtual void clear();

        /*!
            \brief      Check whether the chosen piece can be placed at specific position
            \param      piece     The chosen piece
            \param      i_origin  The topmost row being placed onto
            \param      j_origin  The leftmost column begin placed onto
        */
        virtual bool canPlaceShapeAtPos(const Shape* piece, const int &i_origin, const int &j_origin) const;

        /*!
            \brief      Check whether the chosen piece can be placed onto the board.
            \param      piece The chosen piece
        */
        virtual bool isAnySpacePlaceable(const Shape* piece) const;

        /*!
            \brief      Place the piece onto the board and update the score.
            \param      piece The chosen piece
            \param      i_origin  The topmost row being placed onto
            \param      j_origin  The leftmost column begin placed onto
            \param      score Score being updated
            \return     true if at least one line has been completed
        */
        virtual bool place(VisibleShape* piece, const int &i_origin, const int &j_origin, EncryptedNum* score);

        /*!
            \brief      Find the top-left unit square being overlapped by the piece.
            \param      mouse_x The x coordinate of the mouse
            \param      mouse_y The y coordinate of the mouse
            \param      piece   The chosen piece
            \return     The position of the unit square
        */
        virtual std::pair<int, int> getUnitSquarePos(int mouse_x, int mouse_y, const VisibleShape* piece) const;

        /*!
            \brief      Check whether the chosen piece can be placed with mouse at specific coordinate
            \param      mouse_x The x coordinate of the mouse
            \param      mouse_y The y coordinate of the mouse
            \param      piece   The chosen piece
        */
        virtual bool canPlaceShapeAtCoordinate(const VisibleShape* piece, const int &mouse_x, const int &mouse_y) const;

        /*!
            \brief      Place the piece onto the board by mouse and update the score.
            \param      piece The chosen piece
            \param      mouse_x The x coordinate of the mouse
            \param      mouse_y The y coordinate of the mouse
            \param      score Score being updated
            \return     true if at least one line has been completed
        */
        virtual bool placeMouse(VisibleShape* piece, const int &mouse_x, const int &mouse_y, EncryptedNum* score);

        /*!
            \brief      Preview the piece before it is placed.
            \param      piece The chosen piece
            \param      mouse_x The x coordinate of the mouse
            \param      mouse_y The y coordinate of the mouse
            \param      path_reverse The path pointing to the border image
            \return     A pointer to the piece with a view to rendering it
        */
        virtual VisibleShape preview(VisibleShape piece, const int &mouse_x, const int &mouse_y, const std::string &path_reverse) const;

        /*!
            \brief      Get a part of the board
        */
        virtual Board sub(const int &x, const int &y, const int &w, const int &h) const;
};

#endif
