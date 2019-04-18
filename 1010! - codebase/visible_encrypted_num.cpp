/*!
    \file       visible_encrypted_num.cpp
    \brief      Implementation file for VisibleEncryptedNum handling.
*/

#include "visible_encrypted_num.h"

VisibleEncryptedNum::~VisibleEncryptedNum() {}

VisibleEncryptedNum::VisibleEncryptedNum() {}

VisibleEncryptedNum::VisibleEncryptedNum(const std::string &type, const std::string &location, const int v) {
    mtype = type;
    mlocation = location;
    setVal(v);
}

void VisibleEncryptedNum::setType(const std::string &type) {mtype = type;}

void VisibleEncryptedNum::setLocation(const std::string &location) {mlocation = location;};

Image VisibleEncryptedNum::getDigitImage(const int &d) const {
    std::string s = "";
    Image img = Image(mtype, s + char(d + 48), mlocation);
    img.setCoordinate(mx, my);
    img.setSize(mdw, mdh);
    return img;
}

void VisibleEncryptedNum::setCoordinate(const int &x, const int &y) {mx = x; my = y;}

int VisibleEncryptedNum::getX() const {return mx;}

int VisibleEncryptedNum::getY() const {return my;}

void VisibleEncryptedNum::setDHeight(const int &height) {mdh = height;}

int VisibleEncryptedNum::getDHeight() const {return mdh;}

void VisibleEncryptedNum::setDWidth(const int &width) {mdw = width;}

int VisibleEncryptedNum::getDWidth() const {return mdw;}
