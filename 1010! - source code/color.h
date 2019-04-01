/*!
    \file       color.h
    \brief      Include file for Color handling.
*/
#pragma once

using namespace std;

/*!
    \class      Color
    \brief      A class that defines color
    \details    Color is displayed in RGB Color Model
*/
class Color {
    private:
        Uint8 r, g, b;
    public:
        Color() {}

        Color(const Uint8 &_r, const Uint8 &_g, const Uint8 &_b) {
            r = _r; g = _g; b = _b;
        }

        /*!
            \brief  get the Red value of the color
            \sa     getG()
            \sa     getB()
        */
        Uint8 getR() const {return r;}

        /*!
            \brief  get the Green value of the color
            \sa     getR()
            \sa     getB()
        */
        Uint8 getG() const {return g;}

        /*!
            \brief  get the Blue value of the color
            \sa     getR()
            \sa     getG()
        */
        Uint8 getB() const {return b;}

        /*!
            \brief  check whether two colors are identical
            \return 0 if those are identical
        */
        int cmp(const Color* c) {
            return (r - c->getR()) * 1e6 + (g - c->getG()) * 1e3 + (b - c->getB());
        }
};
