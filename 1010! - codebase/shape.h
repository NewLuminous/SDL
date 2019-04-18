/*!
    \file       shape.h
    \brief      Include file for Shape handling.
*/

#ifndef SHAPE_H
#define SHAPE_H

#include <vector>

/*!
    \class      Shape
    \brief      A bitmap representing shape.
*/
class Shape {
    private:
        static const int UNDEFINED_NUM;

        int mcol = 0, mrow = 0;
        std::vector<std::vector<bool> > mbitmap;
        int mnum_bit = UNDEFINED_NUM;

    public:

        virtual ~Shape();

        Shape();

        /*!
            \brief      constructor for filled rectangle
            \param      row The number of rows of the rectangle
            \param      col The number of columns of the rectangle
        */
        Shape(const unsigned int &row, const unsigned int &col);

        /*!
            \brief      constructor for any shape
            \param      bitmap The bitmap representing the shape.
            \sa         setBitMap()
        */
        Shape(const std::vector<std::vector<bool> > &bitmap);

        virtual void fillBitMap(const unsigned int &row, const unsigned int &col);

        virtual void setBitMap(const std::vector<std::vector<bool> > &bitmap);

        /*!
            \brief      Count the number of unit squares inside the shape
        */
        virtual int getNumBit();

        /*!
            \brief      set bit at specific position
            \param      i The row containing the bit
            \param      j The column containing the bit
            \param      k New value of the bit
            \sa         getBit()
        */
        virtual void setBit(const int &i, const int &j, const bool &k);

        /*!
            \brief      get bit at specific position
            \param      i The row containing the bit
            \param      j The column containing the bit
            \sa         setBit()
        */
        virtual bool getBit(const int &i, const int &j) const;

        /*!
            \brief      Get the number of columns of the shape
            \sa         getRowNum()
        */
        virtual int getColNum() const;

        /*!
            \brief      Get the number of rows of the shape
            \sa         getColNum()
        */
        virtual int getRowNum() const;

        virtual void del();
};

#endif
