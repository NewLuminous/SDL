/*!
    \file       score.h
    \brief      Include file for Score handling.
*/
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <vector>

using namespace std;

/*!
    \class      Score
    \brief      A class that defines score
*/
class Score {
    private:
        const int SVAL_SIZE = 3;
        const int MIN = 33;
        const int MOD = 256 - MIN;
        const int MIN2 = 45;
        const int MOD2 = 256 - MIN2;
        const int HIDE_LENGTH = 100;
        const int HIDE_POS = MOD % (HIDE_LENGTH - SVAL_SIZE * 2 + 1) + 1;

        string s_val = "";
        int x = 0, y = 0;
        int d_size_x = 0, d_size_y = 0;
        string img_source, img_type;

        void encode(int val) {
            s_val = "";
            for (; val; val /= MOD) s_val += char(MIN + val % MOD);
            while ((int)s_val.size() < SVAL_SIZE) s_val += char(MIN);
        }

        string encode2(int val) const {
            string s = "";
            for (; val; val /= MOD2) s += char(MIN2 + val % MOD2);
            while ((int)s.size() < SVAL_SIZE) s += char(MIN2);
            return s;
        }

        int decode() const {
            int res = 0;
            for (int i = SVAL_SIZE - 1; i >= 0; --i) res = res * MOD + (s_val[i] - MIN + 256) % 256;
            return res;
        }

        int decode2(const string &s) const {
            int res = 0;
            for (int i = s.size() - 1; i >= s.size() - SVAL_SIZE; --i) res = res * MOD2 + (s[i] - MIN2 + 256) % 256;
            return res;
        }
    public:
        /*!
            \brief Constructor with score set at 0
        */
        Score() {encode(0);}

        /*!
            \brief  Constructor with score set at specific value
        */
        Score(const unsigned int &v) {encode(v);}

        /*!
            \sa     setVal()
        */
        int val() const {return decode();}

        /*!
            \sa     val()
        */
        void setVal(const unsigned int &v) {encode(v);}

        /*!
            \brief  Compare two score values.
        */
        int cmp(const Score* b) const {return val() - b->val();}

        /*!
            \brief Increase the score
        */
        void inc(int inc_val) {encode(decode() + inc_val);}

        /*!
            \brief  Get last digits of the score
            \param  num Number of digits
            \return set of digits if it is sufficient for displaying score, set of 9 digits if otherwise
        */
        vector<int> getDigits(int num) const {
            vector<int> vec_d;
            int tmp = decode();
            for (; num; --num, tmp /= 10) vec_d.push_back(tmp % 10);
            if (tmp) vec_d = vector<int>(vec_d.size(), 9);
            return vec_d;
        }

        /*!
            \brief  Save score to a file
            \sa     load()
        */
        void save() {
            ofstream file("data.dat");
            srand(time(NULL));
            for (int i = 1; i < HIDE_POS; ++i) file << char(MIN + rand() % MOD);
            file << s_val;
            for (int i = HIDE_POS + SVAL_SIZE; i <= HIDE_LENGTH - SVAL_SIZE; ++i) file << char(MIN + rand() % MOD);
            file << encode2(decode());
        }

        /*!
            \brief  Load score from a file
            \sa     save()
        */
        void load() {
            ifstream file("data.dat");
            if (!file) save();
            else {
                string s;
                getline(file, s);
                s_val = "";
                for (int i = HIDE_POS; i < HIDE_POS + SVAL_SIZE; ++i) s_val += s[i - 1];
                if (decode() != decode2(s)) {
                    encode(0); return;
                }
            }
        }

        /*!
            \brief  Set the position of the top-left corner of the score
            \param  _x The x coordinate
            \param  _y The y coordinate
            \sa     getX()
            \sa     getY()
        */
        void setPos(const int &_x, const int &_y) {x = _x; y = _y;}

        /*!
            \brief  Get the x coordinate of the score
            \sa     getY()
        */
        int getX() const {return x;}

        /*!
            \brief  Get the y coordinate of the score
            \sa     getX()
        */
        int getY() const {return y;}

        /*!
            \brief  Set the digit size
            \param  size_x The width of the digit
            \param  size_y The height of the digit
            \sa     getDSizeX()
            \sa     getDSizeY()
        */
        void setDSize(const unsigned int &size_x, const unsigned int &size_y) {d_size_x = size_x; d_size_y = size_y;}

        /*!
            \brief  Get the width of the digit
            \sa     setDSize()
        */
        int getDSizeX() const {return d_size_x;}

        /*!
            \brief  Get the height of the digit
            \sa     setDSize()
        */
        int getDSizeY() const {return d_size_y;}

        /*!
            \brief  set the source of the digit image
            \param  source The path pointing to the image
            \param  type The image type
            \sa     getDigitImg()
        */
        void setDigitImg(const string &source, const string &type) {
            img_source = source; img_type = type;
        }

        /*!
            \brief  get the path pointing to the digit image
            \sa     setDigitImg()
        */
        string getDigitImg(int d) const {
            return img_source + char(d + '0') + "." + img_type;
        }
};
