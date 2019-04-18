/*!
    \file       menu.h
    \brief      Include file for Menu handling.
*/

#ifndef MENU_H
#define MENU_H

#include "button.h"
#include <vector>

/*!
    \class      Menu
    \brief      A class that defines menu consisting of buttons
*/
class Menu {
    private:
        Font mtitle = Font("", "");
        int mw = 0, mh = 0;
        std::vector<Button> mlist;
        int mlist_x = 0, mlist_y = 0;
    public:
        /*!
            \details Buttons will have the same font as the title even if it is not set
            \sa     getTitle()
        */
        Menu(Font title = Font("", ""));

        /*!
            \details Buttons will have the same font as the title even if it is not set
            \sa     getTitle()
        */
        void setTitle(const Font &title);

        /*!
            \sa     setTitle()
        */
        Font getTitle() const;

        /*!
            \brief  Set the color of texts
            \sa     getColor()
        */
        void setColor(const RGBColor &color);

        /*!
            \brief  Get the color of texts
            \sa     setColor()
        */
        RGBColor getColor() const;

        /*!
            \brief  Set the coordinate of the top-left corner of the menu
            \sa     getX()
            \sa     getY()
        */
        void setCoordinate(const int &x, const int &y);

        /*!
            \brief  Get the x coordinate of the menu
            \sa     setCoordinate();
        */
        int getX() const;

        /*!
            \brief  Get the y coordinate of the menu
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
            \sa     setWidth()
        */
        int getWidth() const;

        /*!
            \brief  Set the coordinate of the top-left corner of the list
            \param  _x The x coordinate of the list with the origin at the top-left corner of the menu
            \param  _y The y coordinate of the list with the origin at the top-left corner of the menu
        */
        void setButtonCoordinate(const int &_x, const int &_y);

        /*!
            \brief  Add new button to the menu
            \sa     popButton()
        */
        void pushButton(Button button);

        /*!
            \brief  Remove the last added button from the menu
            \sa     pushButton()
        */
        void popButton();

        /*!
            \brief  Get the number of buttons in the menu
        */
        int numButton() const;

        /*!
            \brief  Get a specific button of the menu
            \param  i index of the button
        */
        Button* getButton(const int &i);

        /*!
            \brief  Find the button corresponding to the position of the mouse
            \param  mouse_y The y coordinate of the mouse
        */
        int getButtonIndex(const int &mouse_y) const;
};

#endif
