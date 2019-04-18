/*!
    \file       font.h
    \brief      Include file for Font handling.
*/

#ifndef FONT_H
#define FONT_H

#include "rgb_color.h"
#include <string>

/*!
    \class      Font
    \brief      A class that defines font
*/
class Font {
    private:
        static const int DEFAULT_SIZE;

        std::string msrc;
        std::string mtext;
        int msize;
        RGBColor mcolor = RGBColor(0, 0, 0);
        int mx = 0, my = 0, mh = 0, mw = 0;
    public:
        /*!
            \sa     getSource()
            \sa     getText()
            \sa     getFontSize()
        */
        Font(const std::string &source, const std::string &text, const int font_size = DEFAULT_SIZE);

        std::string getSource() const;

        std::string getText() const;

        bool empty() const;

        int getFontSize() const;

        /*!
            \sa     getColor()
        */
        void setColor(const RGBColor &color);

        /*!
            \sa     setColor()
        */
        RGBColor getColor() const;

        /*!
            \brief  Set the coordinate of the top-left corner of the text
            \sa     getX()
            \sa     getY()
        */
        void setCoordinate(const int &x, const int &y);

        /*!
            \brief  Get the x coordinate of the text
            \sa     setCoordinate();
        */
        int getX() const;

        /*!
            \brief  Get the y coordinate of the text
            \sa     setCoordinate();
        */
        int getY() const;

        /*!
            \sa     getHeight()
            \sa     setWidth()
        */
        void setHeight(const unsigned int &height);

        /*!
            \sa     setHeight()
        */
        int getHeight() const;

        /*!
            \sa     getWidth()
            \sa     setHeight()
        */
        void setWidth(const unsigned int &width);

        /*!
            \details Not available if the text currently is empty
            \sa     setWidth()
            \sa     empty()
        */
        int getWidth() const;
};

#endif
