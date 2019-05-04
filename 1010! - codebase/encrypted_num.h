/*!
    \file       encrypted_num.h
    \brief      Include file for EncryptedNum handling.
*/

#ifndef ENCRYPTED_NUM_H
#define ENCRYPTED_NUM_H

#include <memory>
#include <string>

/*!
    \class      EncryptedNum
    \brief      A class that encrypts number
*/
class EncryptedNum {
    private:
        class impl;
        std::unique_ptr<impl> pimpl;
        static const std::string DEFAULT_FILE_PATH;
    public:
        /*!
            \brief Constructor with value set at 0
        */
        EncryptedNum();

        /*!
            \brief  Constructor with specific value
        */
        EncryptedNum(const unsigned int &v);

        virtual ~EncryptedNum();

        /*!
            \sa     setVal()
        */
        virtual int val() const;

        /*!
            \sa     val()
        */
        virtual void setVal(const unsigned int &v);

        /*!
            \brief  Compare two number.
        */
        virtual int cmp(const EncryptedNum* b) const;

        /*!
            \brief Increase the number
        */
        virtual void inc(int inc_val);

        /*!
            \brief Set where the number is saved to
        */
        virtual void setPath(std::string path);

        /*!
            \brief  Encrypt the number and save it to a file
            \sa     load()
        */
        virtual void save();

        /*!
            \brief  Load number from a file and decrypt it
            \sa     save()
        */
        virtual void load();
};

#endif
