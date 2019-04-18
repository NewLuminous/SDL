/*!
    \file       button.h
    \brief      Include file for Button handling.
*/

#ifndef BUTTON_H
#define BUTTON_H

#include "image.h"
#include "font.h"

/*!
    \class      Button
    \brief      A class that defines button including icon and text
*/
class Button {
    private:
        Image micon = Image("", "");
        Font mtitle = Font("", "");
        int mw = 0, mh = 0;
    public:
        Button();

        Button(const Image &icon, Font title = Font("", ""));

        Button(const Font &title);

        virtual ~Button();

        /*!
            \sa     getIcon()
        */
        virtual void setIcon(const Image &icon);

        /*!
            \sa     setIcon()
        */
        virtual Image getIcon() const;

        /*!
            \sa     getTitle()
        */
        virtual void setTitle(const Font &title);

        /*!
            \sa     setTitle()
        */
        virtual Font getTitle() const;

        /*!
            \brief  Set the color of the title
            \sa     getColor()
        */
        virtual void setColor(const RGBColor &color);

        /*!
            \brief  Get the color of the title
            \sa     setColor()
        */
        virtual RGBColor getColor() const;

        /*!
            \brief  Set the coordinate of the top-left corner of the button
            \sa     getX()
            \sa     getY()
        */
        virtual void setCoordinate(const int &x, const int &y);

        /*!
            \brief  Get the x coordinate of the button
            \sa     setCoordinate();
        */
        virtual int getX() const;

        /*!
            \brief  Get the y coordinate of the button
            \sa     setCoordinate();
        */
        virtual int getY() const;

        /*!
            \sa     getHeight()
            \sa     setWidth()
        */
        virtual void setHeight(const unsigned int &height);

        /*!
            \sa     setHeight()
        */
        virtual int getHeight() const;

        /*!
            \sa     getWidth()
            \sa     setHeight()
        */
        virtual void setWidth(const unsigned int &width);

        /*!
            \sa     setWidth()
        */
        virtual int getWidth() const;

        /*!
            \brief      Check whether the mouse currently points at the button
            \details    Always return false if the size of the button has never been set before
            \param      x The x coordinate of the mouse
            \param      y The y coordinate of the mouse
            \sa         setHeight()
            \sa         setWidth()
        */
        virtual bool inside(const int &x, const int &y);
};

#endif
