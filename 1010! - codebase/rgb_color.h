/*!
    \file       rgb_color.h
    \brief      Include file for RGBColor handling.
*/

#ifndef RGB_COLOR_H
#define RGB_COLOR_H

/*!
    \class      RGBColor
    \brief      A class that defines color displayed in RGB Color Model
*/
class RGBColor {
    private:
        int mr, mg, mb;
    public:
        RGBColor(const int &r, const int &g, const int &b);

        /*!
            \brief  get the Red value of the color
            \sa     getG()
            \sa     getB()
        */
        int getR() const;

        /*!
            \brief  get the Green value of the color
            \sa     getR()
            \sa     getB()
        */
        int getG() const;

        /*!
            \brief  get the Blue value of the color
            \sa     getR()
            \sa     getG()
        */
        int getB() const;

        /*!
            \brief  check whether two colors are identical
            \return 0 if those are identical
        */
        int cmp(const RGBColor* c);
};

#endif
