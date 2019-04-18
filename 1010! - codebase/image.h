/*!
    \file       image.h
    \brief      Include file for Image handling.
*/

#ifndef IMAGE_H
#define IMAGE_H

#include "rgb_color.h"
#include <string>

/*!
    \class      Image
    \brief      A class that defines image
*/
class Image {
    private:
        std::string mlocation, mname, mtype;
        int mx = 0, my = 0, mw = 0, mh = 0;
        RGBColor mcolor = {0xFF, 0xFF, 0xFF};
    public:
        /*!
            \sa     getPath()
        */
        Image(const std::string &type, std::string name, const std::string &location = "");

        std::string getPath() const;

        /*!
            \brief  Set the coordinate of the top-left corner of the image
            \sa     getX()
            \sa     getY()
        */
        void setCoordinate(const int &x, const int &y);

        /*!
            \brief  Get the x coordinate of the image
            \sa     setCoordinate();
        */
        int getX() const;

        /*!
            \brief  Get the y coordinate of the image
            \sa     setCoordinate();
        */
        int getY() const;

        /*!
            \sa     getWidth()
            \sa     getHeight()
        */
        void setSize(const unsigned int &width, const unsigned int &height);

        /*!
            \sa     setSize()
        */
        int getWidth() const;

        /*!
            \sa     setSize()
        */
        int getHeight() const;

        /*!
            \sa     getColor()
        */
        void setColor(const RGBColor &color);

        /*!
            \sa     setColor()
        */
        RGBColor getColor() const;
};

#endif
