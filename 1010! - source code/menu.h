/*!
    \file       menu.h
    \brief      Include file for Menu handling.
*/
#include "button.h"
#include <vector>

using namespace std;

/*!
    \class      Menu
    \brief      A class that defines menu consisting of buttons
*/
class Menu {
    private:
        string title = "";
        int x = 0, y = 0;
        int width = 0, height = 0;
        string font = "";
        int font_size = 0;
        Color font_color = {0, 0, 0};
        vector<Button> button_list;
        int button_x = 0, button_y = 0;
        bool is_del = false;
    public:
        /*!
            \brief  Constructor
            \param  _x The x coordinate of the top-left corner
            \param  _y The y coordinate of the top-left corner
            \param  w The width of the menu
            \param  h The height of the menu
            \param  s The title of the menu
            \sa     getX()
            \sa     getY()
            \sa     getWidth()
            \sa     getHeight()
            \sa     getTitle()
        */
        Menu(const int &_x, const int &_y, const int &w, const int &h, const string &s) {
            x = _x; y = _y;
            width = w; height = h;
            title = s;
            button_x = x;
            button_y = y + height / 3;
        }

        /*!
            \brief  Get the x coordinate of the top-left corner of the menu
            \sa     getY()
        */
        int getX() const {return x;}

        /*!
            \brief  Get the y coordinate of the top-left corner of the menu
            \sa     getX()
        */
        int getY() const {return y;}

        /*!
            \brief  Get the width of the menu
            \sa     getHeight()
        */
        int getWidth() const {return width;}

        /*!
            \brief  Get the height of the menu
            \sa     getWidth()
        */
        int getHeight() const {return height;}

        /*!
            \brief  Get the title of the menu
        */
        string getTitle() const {return title;}

        /*!
            \brief  Set the text font
            \param  source The path pointing to the font
            \param  ptsize The size of the font
            \param  color The color of the font
            \sa     getFont()
            \sa     getFontSize()
            \sa     getFontColor()
        */
        void setFont(const string &source, const int &ptsize, const Color &color) {
            font = source;
            font_size = ptsize;
            font_color = color;
        }

        /*!
            \brief  Get the source of the font
            \sa     setFont()
        */
        string getFont() const {return font;}

        /*!
            \brief  Get the size of the font
            \sa     setFont()
        */
        int getFontSize() const {return font_size;}

        /*!
            \brief  Get the color of the font
            \sa     getFont()
        */
        Color getFontColor() const {return font_color;}

        /*!
            \brief  Set the position of the top-left corner of the first button
            \param  _x The x coordinate of the first button with the origin at the top-left corner of the menu
            \param  _y The y coordinate of the first button with the origin at the top-left corner of the menu
        */
        void setButtonPos(const int &_x, const int &_y) {button_x = x + _x; button_y = y + _y;}

        /*!
            \brief  Find the button corresponding to the position of the mouse
            \param  mouse_y The y coordinate of the mouse
        */
        int getButtonIndex(const int &mouse_y) const {
            return (mouse_y - button_y) / (button_list[0].getNormalIconSize() * 2);
        }

        /*!
            \brief  Add new button to the menu
            \sa     popButton()
        */
        void pushButton(Button button) {
            button.setFont(font, font_size, font_color);
            button.setWidth(width);
            button_list.push_back(button);
            button.setIcon("", (y + height - button_y) / (button_list.size() * 2 - 1));
            for (int i = 0; i < button_list.size(); ++i) {
                button_list[i].setIcon(button_list[i].getIcon(), button.getIconSize());
                button_list[i].setPos(button_x, button_y + button.getIconSize() * i * 2);
            }
        }

        /*!
            \brief  Remove the last added button from the menu
            \sa     pushButton()
        */
        void popButton() {button_list.pop_back();}

        /*!
            \brief  Get the number of buttons in the menu
        */
        int numButton() const {return button_list.size();}

        /*!
            \brief  Allow access to a button of the menu for modification
            \param  i index of the button
        */
        Button* getButton(const int &i) {if (0 <= i && i < button_list.size()) return &button_list[i]; else return nullptr;}

        /*!
            \sa         recover()
            \sa         isDel()
        */
        Menu* del() {is_del = true; return this;}

        /*!
            \sa         del()
            \sa         isDel()
        */
        Menu* recover() {is_del = false; return this;}

        /*!
            \sa         del()
            \sa         recover()
        */
        bool isDel() const {return is_del;}
};
