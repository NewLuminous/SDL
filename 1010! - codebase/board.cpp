/*!
    \file       board.cpp
    \brief      Implementation file for Board handling.
*/

#include "board.h"

Board::~Board() {}

void Board::setColor(const RGBColor &color) {
    VisibleShape::setColor(color);
    for (int i = 0; i < getRowNum(); ++i)
        for (int j = 0; j < getColNum(); ++j) mcolor_map[i][j] = color;
}

void Board::setUnitSquareColor(const int &i, const int &j, const RGBColor &c) {mcolor_map[i][j] = c;}

RGBColor Board::getUnitSquareColor(const int &i, const int &j) const {return mcolor_map[i][j];}


void Board::clear() {
    mcolor_map = std::vector<std::vector<RGBColor> >(getRowNum(), std::vector<RGBColor>(getColNum(), getColor()));
    mplacement = std::vector<std::vector<bool> >(getRowNum(), std::vector<bool>(getColNum(), false));
    mrow = std::vector<int>(getRowNum(), 0);
    mcol = std::vector<int>(getColNum(), 0);
}

bool Board::canPlaceShapeAtPos(const Shape* piece, const int &i_origin, const int &j_origin) const {
    if (piece->getRowNum() == 0 || piece->getColNum() == 0) return false;
    for (int i = 0; i < piece->getRowNum(); ++i)
        for (int j = 0; j < piece->getColNum(); ++j)
            if (piece->getBit(i, j) && mplacement[i_origin + i][j_origin + j]) return false;
    return true;
}

bool Board::isAnySpacePlaceable(const Shape* piece) const {
    for (int i = 0; i <= getRowNum() - piece->getRowNum(); ++i)
        for (int j = 0; j <= getColNum() - piece->getColNum(); ++j)
            if (canPlaceShapeAtPos(piece, i, j)) return true;
    return false;
}

bool Board::place(VisibleShape* piece, const int &i_origin, const int &j_origin, EncryptedNum* score) {
    for (int i = 0; i < piece->getRowNum(); ++i)
        for (int j = 0; j < piece->getColNum(); ++j)
            if (piece->getBit(i, j)) {
                mplacement[i_origin + i][j_origin + j] = true;
                setUnitSquareColor(i_origin + i, j_origin + j, piece->getColor());
                ++mrow[i_origin + i];++mcol[j_origin + j];
            }
    score->inc(piece->getNumBit());
    //!Clear lines when they are completed
    int completed_line_count = 0;
    for (int i = i_origin; i < i_origin + piece->getRowNum(); ++i)
        if (mrow[i] == getColNum()) {
            mrow[i] = 0;
            for (int j = 0; j < getColNum(); ++j) {
                mplacement[i][j] = false;
                setUnitSquareColor(i, j, getColor());
                if (mcol[j] < getRowNum()) --mcol[j];
            }
            ++completed_line_count;
        }
    for (int j = j_origin; j < j_origin + piece->getColNum(); ++j)
        if (mcol[j] == getRowNum()) {
            mcol[j] = 0;
            for (int i = 0; i < getRowNum(); ++i) {
                mplacement[i][j] = false;
                setUnitSquareColor(i, j, getColor());
                if (mrow[i]) --mrow[i];
            }
            ++completed_line_count;
        }
    piece->del();
    return (completed_line_count > 0);
}

std::pair<int, int> Board::getUnitSquarePos(int mouse_x, int mouse_y, const VisibleShape* piece) const {
    mouse_x -= piece->getMouseX() * getUnitSquareSize() / piece->getUnitSquareSize();
    mouse_y -= piece->getMouseY() * getUnitSquareSize() / piece->getUnitSquareSize();
    int j = (mouse_x - getX()) / getUnitSquareSize();
    if ((mouse_x - getX()) * 2 > (2 * j + 1) * getUnitSquareSize()) ++j;
    j = std::min(std::max(j, 0), getColNum() - piece->getColNum());
    int i = (mouse_y - getY()) / getUnitSquareSize();
    if ((mouse_y - getY()) * 2 > (2 * i + 1) * getUnitSquareSize()) ++i;
    i = std::min(std::max(i, 0), getRowNum() - piece->getRowNum());
    return {i, j};
}

bool Board::canPlaceShapeAtCoordinate(const VisibleShape* piece, const int &mouse_x, const int &mouse_y) const {
    std::pair<int, int> pos = getUnitSquarePos(mouse_x, mouse_y, piece);
    return canPlaceShapeAtPos(piece, pos.first, pos.second);
}

bool Board::placeMouse(VisibleShape* piece, const int &mouse_x, const int &mouse_y, EncryptedNum* score) {
    std::pair<int, int> pos = getUnitSquarePos(mouse_x, mouse_y, piece);
    return place(piece, pos.first, pos.second, score);
}

VisibleShape Board::preview(VisibleShape piece, const int &mouse_x, const int &mouse_y, const std::string &path_reverse) const {
    std::pair<int, int> pos = getUnitSquarePos(mouse_x, mouse_y, &piece);
    piece.setUnitSquareImg(Image("", "", path_reverse));
    piece.setCoordinate(getX() + pos.second * getUnitSquareSize(), getY() + pos.first * getUnitSquareSize());
    piece.setUnitSquareSize(getUnitSquareSize());
    return piece;
}

Board Board::sub(const int &x, const int &y, const int &w, const int &h) const {
    std::pair<int, int> pos1 = {(y - getY()) / getUnitSquareSize(), (x - getX()) / getUnitSquareSize()};
    pos1.first = std::min(std::max(pos1.first, 0), getRowNum() - 1);
    pos1.second = std::min(std::max(pos1.second, 0), getColNum() - 1);
    std::pair<int, int> pos2 = {(y + h - 1 - getY()) / getUnitSquareSize(), (x + w - 1 - getX()) / getUnitSquareSize()};
    pos2.first = std::min(std::max(pos2.first, 0), getRowNum() - 1);
    pos2.second = std::min(std::max(pos2.second, 0), getColNum() - 1);
    Board res(pos2.first - pos1.first + 1, pos2.second - pos1.second + 1);
    res.setCoordinate(getX() + pos1.second * getUnitSquareSize(), getY() + pos1.first * getUnitSquareSize());
    res.setUnitSquareImg(getUnitSquareImg());
    res.setUnitSquareSize(getUnitSquareSize());
    for (int i = pos1.first; i <= pos2.first; ++i)
        for (int j = pos1.second; j <= pos2.second; ++j) res.setUnitSquareColor(i - pos1.first, j - pos1.second, getUnitSquareColor(i, j));
    return res;
}
