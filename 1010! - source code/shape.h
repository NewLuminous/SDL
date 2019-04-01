/*!
    \file       shape.h
    \brief      Include file for Shape handling.
*/
#include <vector>
#include <stdlib.h>
#include "color.h"

using namespace std;

/*!
    \class      Shape
    \brief      A bitmap representing shape.
*/
class Shape {
    private:
        int width = 0, height = 0;
        vector<vector<bool> > bitmap;
        int x = 0, y = 0;
        int num_bit = -1;
        Color color = Color(0xFF, 0xFF, 0xFF);
        int unit_square_size = 0;
        string unit_square_img;
        bool is_del = false;
        int mouse_x = 0, mouse_y = 0;
    public:
        /*!
            \brief      constructor with no description
        */
        Shape() {}

        /*!
            \brief      constructor for any shape
            \param      _bitmap The bitmap representing the shape.
            \sa         setBitMap()
        */
        Shape(const vector<vector<bool> > &_bitmap) {
            bitmap = _bitmap;
            height = bitmap.size();
            if (height) width = bitmap[0].size();
            num_bit = -1;
        }

        /*!
            \brief      constructor for filled rectangle
            \param      _width The width of the rectangle
            \param      _height The height of the rectangle
        */
        Shape(const unsigned int &_width, const unsigned int &_height) {
            bitmap.resize(_height, vector<bool>(_width, true));
            width = _width;
            height = _height;
            num_bit = width * height;
        }

        /*!
            \brief      set bitmap of the shape
        */
        void setBitMap(const vector<vector<bool> > &_bitmap) {
            bitmap = _bitmap;
            height = bitmap.size();
            if (height) width = bitmap[0].size();
            num_bit = -1;
        }

        /*!
            \brief      set bit at specific position
            \param      i The row containing the bit
            \param      j The column containing the bit
            \param      k New value of the bit
            \sa         getBit()
        */
        void setBit(const int &i, const int &j, const bool &k) {
            if (num_bit >= 0) num_bit -= bitmap[i][j] - k;
            bitmap[i][j] = k;
        }

        /*!
            \brief      Count the number of unit squares inside the shape
        */
        int getNumBit() {
            if (num_bit >= 0) return num_bit;
            for (int i = 0; i < height; ++i)
                for (int j = 0; j < width; ++j)
                    if (bitmap[i][j]) ++num_bit;
            return ++num_bit;
        }

        /*!
            \brief      get bit at specific position
            \param      i The row containing the bit
            \param      j The column containing the bit
            \sa         setBit()
        */
        bool getBit(const int &i, const int &j) const {return bitmap[i][j];}

        /*!
            \brief      Set the position of the top-left corner of the shape
            \param      _x The x coordinate
            \param      _y The y coordinate
            \sa         getX()
            \sa         getY()
        */
        void setPos(const int &_x, const int &_y) {x = _x; y = _y;}

        /*!
            \brief      Get the x coordinate of the shape
            \sa         setPos()
        */
        int getX() const {return x;}

        /*!
            \brief      Get the y coordinate of the shape
            \sa         setPos()
        */
        int getY() const {return y;}

        /*!
            \brief      Set the shape color
            \sa         getColor()
        */
        void setColor(const Uint8 &r, const Uint8 &g, const Uint8 &b) {color = {r, g, b};}

        /*!
            \brief      Get the shape color
            \sa         setColor()
        */
        Color getColor() const {return color;}

        /*!
            \brief      Set the unit square size
            \sa         getUnitSquareSize()
        */
        void setUnitSquareSize(const unsigned int &_size) {unit_square_size = _size;}

        /*!
            \brief      Get the unit square size
            \sa         setUnitSquareSize()
        */
        int getUnitSquareSize() const {return unit_square_size;}

        /*!
            \brief      Set the path pointing to the image for unit square
            \sa         getUnitSquareImg()
        */
        void setUnitSquareImg(const string &path) {unit_square_img = path;}

        /*!
            \brief      Get the path pointing to the image for unit square
            \sa         setUnitSquareImg()
        */
        string getUnitSquareImg() const {return unit_square_img;}

        /*!
            \brief      Get the width int unit squares of the shape
            \sa         getHeight()
        */
        int getWidth() const {return width;}

        /*!
            \brief      Get the height in unit squares of the shape
            \sa         getWidth()
        */
        int getHeight() const {return height;}

        /*!
            \brief      Get the width in pixels of the shape
            \sa         getSizeY()
        */
        int getSizeX() const {return unit_square_size * width;}

        /*!
            \brief      Get the height in pixels of the shape
            \sa         getSizeX()
        */
        int getSizeY() const {return unit_square_size * height;}

        /*!
            \brief      Check whether the shape is being pointed at.
            \details    Simultaneously save the position of the mouse.
            \param      _mouse_x The x coordinate of the mouse
            \param      _mouse_y The y coordinate of the mouse
        */
        bool inside(const int &_mouse_x, const int &_mouse_y) {
            if (is_del) return false;
            mouse_x = _mouse_x - x;
            mouse_y = _mouse_y - y;
            return (0 <= mouse_y && mouse_y < getSizeY() && 0 <= mouse_x && mouse_x < getSizeX() && bitmap[mouse_y / unit_square_size][mouse_x / unit_square_size]);
        }

        /*!
            \brief      Get the x coordinate of the mouse with the origin at the top-left corner of the shape
            \details    Always return 0 if whether the mouse pointer is inside the shape, has never been checked.
            \sa         inside()
            \sa         getMouseY()
        */
        int getMouseX() const {return mouse_x;}

        /*!
            \brief      Get the y coordinate of the mouse with the origin at the top-left corner of the shape
            \details    Always return 0 if whether the mouse pointer is inside the shape, has never been checked.
            \sa         inside()
            \sa         getMouseX()
        */
        int getMouseY() const {return mouse_y;}

        /*!
            \sa         recover()
            \sa         isDel()
        */
        Shape* del() {is_del = true; return this;}

        /*!
            \sa         del()
            \sa         isDel()
        */
        Shape* recover() {is_del = false; return this;}

        /*!
            \sa         del()
            \sa         recover()
        */
        bool isDel() const {return is_del;}
};
