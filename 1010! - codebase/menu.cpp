/*!
    \file       menu.cpp
    \brief      Implementation file for Menu handling.
*/

#include "menu.h"

Menu::Menu(Font title) {mtitle = title;}

void Menu::setTitle(const Font &title) {mtitle = title;}

Font Menu::getTitle() const {return mtitle;}

void Menu::setColor(const RGBColor &color) {mtitle.setColor(color);}

RGBColor Menu::getColor() const {return mtitle.getColor();}

void Menu::setCoordinate(const int &x, const int &y) {
    mtitle.setCoordinate(x, y);
    mlist_x = x;
    mlist_y = y + mh / 3;
}

int Menu::getX() const {return mtitle.getX();}

int Menu::getY() const {return mtitle.getY();}

void Menu::setHeight(const unsigned int &height) {
    mh = height;
    mtitle.setHeight(mh / 3);
    mlist_y = getY() + mh / 3;
}

int Menu::getHeight() const {return mh;}

void Menu::setWidth(const unsigned int &width) {
    mw = width;
    mtitle.setWidth(mw);
}

int Menu::getWidth() const {return mw;}

void Menu::setButtonCoordinate(const int &_x, const int &_y) {mlist_x = getX() + _x; mlist_y = getY() + _y;}

void Menu::pushButton(Button button) {
    button_title_max = std::max(button_title_max, (int)button.getTitle().getText().size());
    button.setTitle(Font(mtitle.getSource(), button.getTitle().getText(), mtitle.getFontSize()));
    button.setColor(mtitle.getColor());
    mlist.push_back(button);
    button.setHeight((getY() + mh - mlist_y - 1) / (numButton() * 2 - 1));
    for (int i = 0; i < numButton(); ++i) {
        mlist[i].setHeight(button.getHeight());
        mlist[i].setWidth((mw - button.getHeight() * 2) * mlist[i].getTitle().getText().size() / button_title_max + button.getHeight() * 2);
        mlist[i].setCoordinate(mlist_x, mlist_y + button.getHeight() * i * 2);
    }
}

void Menu::popButton() {mlist.pop_back();}

int Menu::numButton() const {return mlist.size();}

Button* Menu::getButton(const int &i) {if (0 <= i && i < numButton()) return &mlist[i]; else return nullptr;}

int Menu::getButtonIndex(const int &mouse_y) const {
    return (mouse_y - mlist_y) / (mlist[0].getHeight() * 2);
}
