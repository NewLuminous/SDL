/*!
    \file       board.h
    \brief      Include file for Board handling.
*/
#include "shape.h"
#include "score.h"

using namespace std;

/*!
    \class      Board
    \brief      The board where pieces are placed.
    \details    Board is a derived class from Shape.
*/
class Board: public Shape {
    private:
        Color color = Color(0xFF, 0xFF, 0xFF);
        vector<vector<Color> > color_map = vector<vector<Color> >(getHeight(), vector<Color>(getWidth(), color));
        vector<int> cntRow = vector<int>(getHeight(), 0);
        vector<int> cntCol = vector<int>(getWidth(), 0);

        void setUnitSquareColor(const int &i, const int &j, const Color &c) {color_map[i][j] = c;}

        /*!
            \brief      Find the top-left unit square being overlapped by the piece.
            \param      mouse_x The x coordinate of the mouse
            \param      mouse_y The y coordinate of the mouse
            \param      piece   The chosen piece
            \return     The position of the unit square
        */
        pair<int, int> getUnitSquarePos(int mouse_x, int mouse_y, const Shape* piece) const {
            mouse_x -= piece->getMouseX() * getUnitSquareSize() / piece->getUnitSquareSize();
            mouse_y -= piece->getMouseY() * getUnitSquareSize() / piece->getUnitSquareSize();
            int j = (mouse_x - getX()) / getUnitSquareSize();
            if ((mouse_x - getX()) * 2 > (2 * j + 1) * getUnitSquareSize()) ++j;
            j = max(j, 0);
            if (j + piece->getWidth() > getWidth()) j = getWidth() - piece->getWidth();
            int i = (mouse_y - getY()) / getUnitSquareSize();
            if ((mouse_y - getY()) * 2 > (2 * i + 1) * getUnitSquareSize()) ++i;
            i = max(i, 0);
            if (i + piece->getHeight() > getHeight()) i = getHeight() - piece->getHeight();
            return {i, j};
        }

        /*!
            \brief      Check whether the chosen piece can be placed at specific position
            \param      i_base  The topmost row being placed onto
            \param      j_base  The leftmost column begin placed onto
        */
        bool collide(const int &i_base, const int &j_base, const Shape* piece) const {
            for (int i = 0; i < piece->getHeight(); ++i)
                for (int j = 0; j < piece->getWidth(); ++j)
                    if (piece->getBit(i, j) && !getBit(i_base + i, j_base + j)) return true;
            return false;
        }
    public:
        using Shape::Shape;

        /*!
            \brief      Set color of the whole board.
            \sa         Shape::setColor()
        */
        void setColor(const Uint8 &r, const Uint8 &g, const Uint8 &b) {
            color = {r, g, b};
            for (int i = 0; i < getHeight(); ++i)
                for (int j = 0; j < getWidth(); ++j) color_map[i][j] = {r, g, b};
        }

        Color getUnitSquareColor(const int &i, const int &j) const {return color_map[i][j];}

        /*!
            \brief      Check whether the board is being pointed at
            \param      mouse_x The x coordinate of the mouse
            \param      mouse_y The y coordinate of the mouse
        */
        bool inside(const int &mouse_x, const int &mouse_y) const {
            if (getY() <= mouse_y && mouse_y < getY() + getSizeY() && getX() <= mouse_x && mouse_x < getX() + getSizeX()) return true; else return false;
        }

        /*!
            \brief      Preview the piece before it is placed.
            \param      mouse_x The x coordinate of the mouse
            \param      mouse_y The y coordinate of the mouse
            \param      piece The chosen piece
            \return     A pointer to the piece with a view to rendering it
        */
        Shape* preview(const int &mouse_x, const int &mouse_y, Shape piece) const {
            pair<int, int> pos = getUnitSquarePos(mouse_x, mouse_y, &piece);
            piece.setPos(getX() + pos.second * getUnitSquareSize(), getY() + pos.first * getUnitSquareSize());
            piece.setUnitSquareSize(getUnitSquareSize());
            piece.recover();
            return &piece;
        }

        /*!
            \brief      Check whether the chosen piece can be placed at specific position.
            \param      mouse_x The x coordinate of the mouse
            \param      mouse_y The y coordinate of the mouse
            \param      piece   The chosen piece
        */
        bool collideMouse(const int &mouse_x, const int &mouse_y, const Shape* piece) const {
            pair<int, int> pos = getUnitSquarePos(mouse_x, mouse_y, piece);
            return collide(pos.first, pos.second, piece);
        }

        /*!
            \brief      Place the piece onto the board.
            \param      mouse_x The x coordinate of the mouse
            \param      mouse_y The y coordinate of the mouse
            \param      piece The chosen piece
            \param      score Score being updated
        */
        void set(const int &mouse_x, const int &mouse_y, Shape* piece, Score* score) {
            pair<int, int> pos = getUnitSquarePos(mouse_x, mouse_y, piece);
            piece->recover();
            for (int i = 0; i < piece->getHeight(); ++i)
                for (int j = 0; j < piece->getWidth(); ++j)
                    if (piece->getBit(i, j)) {
                        setBit(pos.first + i, pos.second + j, 0);
                        setUnitSquareColor(pos.first + i, pos.second + j, piece->getColor());
                        ++cntRow[pos.first + i];++cntCol[pos.second + j];
                    }
            piece->del();
            score->inc(piece->getNumBit());
            //!Clear lines when they are completed
            for (int i = pos.first; i < pos.first + piece->getHeight(); ++i)
                if (cntRow[i] == getWidth()) {
                    cntRow[i] = 0;
                    for (int j = 0; j < getWidth(); ++j) {
                        setBit(i, j, 1);
                        setUnitSquareColor(i, j, color);
                        if (cntCol[j] < getHeight()) --cntCol[j];
                    }
                }
            for (int j = pos.second; j < pos.second + piece->getWidth(); ++j)
                if (cntCol[j] == getHeight()) {
                    cntCol[j] = 0;
                    for (int i = 0; i < getHeight(); ++i) {
                        setBit(i, j, 1);
                        setUnitSquareColor(i, j, color);
                        if (cntRow[i]) --cntRow[i];
                    }
                }
        }

        /*!
            \brief      Check whether the chosen piece can be placed onto the board.
            \param      piece The chosen piece
        */
        bool canSet(const Shape* piece) const {
            for (int i = 0; i <= getHeight() - piece->getHeight(); ++i)
                for (int j = 0; j <= getWidth() - piece->getWidth(); ++j)
                    if (!collide(i, j, piece)) return true;
            return false;
        }

        /*!
            \brief      Clear the board.
        */
        void clear() {
            setBitMap(vector<vector<bool> >(getHeight(), vector<bool>(getWidth(), true)));
            color_map = vector<vector<Color> >(getHeight(), vector<Color>(getWidth(), color));
            cntRow = vector<int>(getHeight(), 0);
            cntCol = vector<int>(getWidth(), 0);
        }

        /*!
            \sa         Shape::del()
        */
        Board* del() {Shape::del(); return this;}

        /*!
            \sa         Shape::recover()
        */
        Board* recover() {Shape::recover(); return this;}
};
