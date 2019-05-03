/*!
    \file       visible_shape.h
    \brief      Include file for VisibleShape handling.
*/

#ifndef VISIBLE_SHAPE_H
#define VISIBLE_SHAPE_H

#include "shape.h"
#include "image.h"
#include "rgb_color.h"

/*!
    \class      VisibleShape
    \brief      A class that defines visible shape.
    \details    VisibleShape is a derived class from Shape.
*/
class VisibleShape: public Shape {
    private:
        Image munit_square_img = Image("", "");
        RGBColor mcolor = RGBColor(0xFF, 0xFF, 0xFF);
        int mmouse_x = 0, mmouse_y = 0;
    public:
        VisibleShape();

        /*!
            \brief      constructor for filled rectangle
            \param      row The number of rows of the rectangle
            \param      col The number of columns of the rectangle
        */
        VisibleShape(const unsigned int &row, const unsigned int &col);

        /*!
            \brief      constructor for any shape
            \param      bitmap The bitmap representing the shape.
            \sa         setBitMap()
        */
        VisibleShape(const std::vector<std::vector<bool> > &bitmap);

        virtual ~VisibleShape();

        /*!
            \sa     getUnitSquareImg()
        */
        virtual void setUnitSquareImg(Image img);

        /*!
            \sa     setUnitSquareImg()
        */
        virtual Image getUnitSquareImg() const;

        /*!
            \brief      Set the coordinate of the top-left corner of the shape
            \param      x The x coordinate
            \param      y The y coordinate
            \sa         getX()
            \sa         getY()
        */
        virtual void setCoordinate(const int &x, const int &y);

        /*!
            \brief      Get the x coordinate of the shape
            \sa         setCoordinate()
        */
        virtual int getX() const;

        /*!
            \brief      Get the y coordinate of the shape
            \sa         setCoordinate()
        */
        virtual int getY() const;

        /*!
            \brief      Set the shape color
            \sa         getColor()
        */
        virtual void setColor(const RGBColor &color);

        /*!
            \brief      Get the shape color
            \sa         setColor()
        */
        virtual RGBColor getColor() const;

        /*!
            \brief      Set the unit square size
            \sa         getUnitSquareSize()
        */
        virtual void setUnitSquareSize(const unsigned int &_size);

        /*!
            \brief      Get the unit square size
            \sa         setUnitSquareSize()
        */
        virtual int getUnitSquareSize() const;

        /*!
            \brief      Get the width of the shape
            \sa         getHeight()
        */
        virtual int getWidth() const;

        /*!
            \brief      Get the height of the shape
            \sa         getWidth()
        */
        virtual int getHeight() const;

        /*!
            \brief      Check whether the shape is being pointed at.
            \details    Simultaneously save the position of the mouse.
            \param      mouse_x The x coordinate of the mouse
            \param      mouse_y The y coordinate of the mouse
        */
        virtual bool inside(const int &mouse_x, const int &mouse_y);

        /*!
            \brief      Get the x coordinate of the mouse with the origin at the top-left corner of the shape
            \details    Always return 0 if whether the mouse pointer is inside the shape, has never been checked.
            \sa         inside()
            \sa         getMouseY()
        */
        virtual int getMouseX() const;

        /*!
            \brief      Get the y coordinate of the mouse with the origin at the top-left corner of the shape
            \details    Always return 0 if whether the mouse pointer is inside the shape, has never been checked.
            \sa         inside()
            \sa         getMouseX()
        */
        virtual int getMouseY() const;

        virtual VisibleShape clone(const int &mouse_x, const int &mouse_y) const;
};

#endif
