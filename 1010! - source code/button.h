/*!
    \file       button.h
    \brief      Include file for Button handling.
*/
#include <stdlib.h>
#include "color.h"

using namespace std;

/*!
    \class      Button
    \brief      A class that defines button including icon and text
*/
class Button {
    private:
        string name = "";
        string icon = "";
        int icon_size = 0;
        string font = "";
        int font_size = 0;
        Color font_color = {0, 0, 0}, triggered_font_color = {0, 0, 0};
        int x = 0, y = 0;
        int width = 0;
        double triggered_size_rate = 1;
        bool is_triggered = false, is_del = false;
    public:
        Button() {}

        /*!
            \brief      Set the name of the button
            \sa         getName()
        */
        void setName(const string &_name) {name = _name;}

        /*!
            \brief      Get the name of the button
            \sa         setName()
        */
        string getName() const {return name;}

        /*!
            \brief      Set the path pointing to the icon
            \param      source The path
            \param      _size The size of the icon
            \sa         getIcon()
        */
        void setIcon(const string &source, const int &_size) {
            icon = source;
            icon_size = _size;
        }

        /*!
            \brief      Get the source of the icon
            \sa         setIcon()
        */
        string getIcon() const {return icon;}

        /*!
            \brief      Set an additional value multiplied into the size of the icon when the button is triggered
            \sa         getTriggeredIconSize()
        */
        void setTriggeredSizeRate(const double &rate) {triggered_size_rate = rate;}

        /*!
            \brief      Get the size of the icon when the button is triggered
            \sa         setTriggeredSizeRate()
        */
        int getTriggeredIconSize() const {return icon_size * triggered_size_rate;}

        /*!
            \brief      Get the size of the icon when the button is not triggered
            \sa         getTriggeredIconSize()
        */
        int getNormalIconSize() const {return icon_size;}

        /*!
            \brief      Get the current size of the icon of the button
            \sa         getNormalIconSize()
            \sa         getTriggeredIconSize()
        */
        int getIconSize() const {return is_triggered? getTriggeredIconSize() : icon_size;}

        /*!
            \brief      Set the font of the text
            \param      source The path pointing to the font
            \param      ptsize The size of the font
            \param      color The color of the font
            \sa         getFont()
            \sa         getFontSize()
            \sa         getFontColor()
        */
        void setFont(const string &source, const int &ptsize, const Color &color) {
            font = source;
            font_size = ptsize;
            if (triggered_font_color.cmp(&font_color) == 0) triggered_font_color = color;
            font_color = color;
        }

        /*!
            \brief      Set the color used to highlight the font of the button when triggered
        */
        void setTriggeredFontColor(const Color &color) {triggered_font_color = color;}

        /*!
            \brief      Get the source of the font
            \sa         setFont()
        */
        string getFont() const {return font;}

        /*!
            \brief      Get the size of the font
            \sa         setFont()
        */
        int getFontSize() const {return font_size;}

        /*!
            \brief      Get the color of the font
            \sa         setFont()
        */
        Color getFontColor() const {return is_triggered? triggered_font_color : font_color;}

        /*!
            \brief      Set the position of the top-left corner of the button
            \param      _x The x coordinate
            \param      _y The y coordinate
            \sa         getX()
            \sa         getY()
        */
        void setPos(const int &_x, const int &_y) {x = _x; y = _y;}

        /*!
            \brief      Get the x coordinate of the button
            \sa         setPos()
        */
        int getX() const {return x;}

        /*!
            \brief      Get the y coordinate of the button
            \sa         setPos()
        */
        int getY() const {return y;}

        /*!
            \brief      Set the width of the button
            \details    If this value is not set, the button never be triggered
            \sa         inside()
        */
        void setWidth(const int &w) {width = w;}

        /*!
            \brief      Check whether the mouse currently points at the button
            \details    Always return false if the width of the button has never been set before or its current value is 0
            \param      _x The x coordinate of the mouse
            \param      _y The y coordinate of the mouse
            \return     true if the button is triggered, false if otherwise
            \sa         setWidth()
        */
        bool inside(const int &_x, const int &_y) {
            if (x <= _x && _x <= x + width - 1 && y <= _y && _y <= y + icon_size - 1) return is_triggered = true; else return is_triggered = false;
        }

        /*!
            \sa         recover()
            \sa         isDel()
        */
        Button* del() {is_del = true; return this;}

        /*!
            \sa         del()
            \sa         isDel()
        */
        Button* recover() {is_del = false; return this;}

        /*!
            \sa         del()
            \sa         recover()
        */
        bool isDel() const {return is_del;}
};
