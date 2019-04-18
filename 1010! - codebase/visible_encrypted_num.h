/*!
    \file       visible_encrypted_num.h
    \brief      Include file for VisibleEncryptedNum handling.
*/

#ifndef VISIBLE_ENCRYPTED_NUM_H
#define VISIBLE_ENCRYPTED_NUM_H

#include "encrypted_num.h"
#include "image.h"

/*!
    \class      VisibleEncryptedNum
    \brief      A class that encrypts visible number
    \details    VisibleEncryptedNum is a derived class from EncryptedNum.
*/
class VisibleEncryptedNum: public EncryptedNum {
    private:
        std::string mtype, mlocation;
        int mx = 0, my = 0, mdh = 0, mdw = 0;
    public:
        virtual ~VisibleEncryptedNum();

        VisibleEncryptedNum();

        /*!
            \param  type The image type of the number
            \param  location The location of the image
            \param  v The value of the number
        */
        VisibleEncryptedNum(const std::string &type, const std::string &location = "", const int v = 0);

        virtual void setType(const std::string &type);

        virtual void setLocation(const std::string &location);

        Image getDigitImage(const int &d) const;

        /*!
            \brief      Set the coordinate of the top-left corner of the number
            \param      x The x coordinate
            \param      y The y coordinate
            \sa         getX()
            \sa         getY()
        */
        virtual void setCoordinate(const int &x, const int &y);

        /*!
            \brief      Get the x coordinate of the number
            \sa         setCoordinate()
        */
        virtual int getX() const;

        /*!
            \brief      Get the y coordinate of the number
            \sa         setCoordinate()
        */
        virtual int getY() const;

        /*!
            \brief      Set the height of the digit
            \sa         getHeight()
        */
        virtual void setDHeight(const int &height);

        /*!
            \brief      Get the height of the digit
            \sa         setHeight()
        */
        virtual int getDHeight() const;

        /*!
            \brief      Set the width of the digit
            \sa         getDWidth()
        */
        virtual void setDWidth(const int &width);

        /*!
            \brief      Get the width of the digit
            \sa         setDWidth()
        */
        virtual int getDWidth() const;
};

#endif
