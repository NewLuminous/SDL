/*!
    \file       encrypted_num.cpp
    \brief      Implementation file for EncryptedNum handling.
*/

#include <fstream>
#include <stdlib.h>
#include <time.h>
#include "encrypted_num.h"

class EncryptedNum::impl {
    public:
        static const int VAL_SIZE;
        static const int MIN;
        static const int MOD;
        static const int MIN2;
        static const int MOD2;
        static const int HIDE_LENGTH;
        static const int HIDE_POS;

        std::string mval;

        void encode(int val);

        std::string encode2(int val) const;

        int decode() const;

        int decode2(const std::string &s) const;
};

const int EncryptedNum::impl::VAL_SIZE = 3;
const int EncryptedNum::impl::MIN = 33;
const int EncryptedNum::impl::MOD = 256 - MIN;
const int EncryptedNum::impl::MIN2 = 45;
const int EncryptedNum::impl::MOD2 = 256 - MIN2;
const int EncryptedNum::impl::HIDE_LENGTH = 100;
const int EncryptedNum::impl::HIDE_POS = MOD % (HIDE_LENGTH - VAL_SIZE * 2 + 1) + 1;

void EncryptedNum::impl::encode(int val) {
    mval = "";
    for (; val; val /= MOD) mval += char(MIN + val % MOD);
    while ((int)mval.size() < VAL_SIZE) mval += char(MIN);
}

std::string EncryptedNum::impl::encode2(int val) const {
    std::string s = "";
    for (; val; val /= MOD2) s += char(MIN2 + val % MOD2);
    while ((int)s.size() < VAL_SIZE) s += char(MIN2);
    return s;
}

int EncryptedNum::impl::decode() const {
    int res = 0;
    for (int i = VAL_SIZE - 1; i >= 0; --i) res = res * MOD + (mval[i] - MIN + 256) % 256;
    return res;
}

int EncryptedNum::impl::decode2(const std::string &s) const {
    int res = 0;
    for (int i = s.size() - 1; i >= (int)s.size() - VAL_SIZE; --i) res = res * MOD2 + (s[i] - MIN2 + 256) % 256;
    return res;
}

const std::string EncryptedNum::DEFAULT_FILE_PATH = "data.dat";

EncryptedNum::EncryptedNum(): pimpl{new impl} {pimpl->encode(0);}

EncryptedNum::EncryptedNum(const unsigned int &v) {pimpl->encode(v);}

EncryptedNum::~EncryptedNum() {}

int EncryptedNum::val() const {return pimpl->decode();}

void EncryptedNum::setVal(const unsigned int &v) {pimpl->encode(v);}

int EncryptedNum::cmp(const EncryptedNum* b) const {return val() - b->val();}

void EncryptedNum::inc(int inc_val) {pimpl->encode(pimpl->decode() + inc_val);}

void EncryptedNum::save(std::string path) {
    std::ofstream file(path);
    srand(time(NULL));
    for (int i = 1; i < pimpl->HIDE_POS; ++i) file << char(pimpl->MIN + rand() % pimpl->MOD);
    file << pimpl->mval;
    for (int i = pimpl->HIDE_POS + pimpl->VAL_SIZE; i <= pimpl->HIDE_LENGTH - pimpl->VAL_SIZE; ++i) file << char(pimpl->MIN + rand() % pimpl->MOD);
    file << pimpl->encode2(pimpl->decode());
}

void EncryptedNum::load(std::string path) {
    std::ifstream file(path);
    if (!file) save(path);
    else {
        std::string s;
        getline(file, s);
        pimpl->mval = "";
        for (int i = pimpl->HIDE_POS; i < pimpl->HIDE_POS + pimpl->VAL_SIZE; ++i) pimpl->mval += s[i - 1];
        if (pimpl->decode() != pimpl->decode2(s)) {
            pimpl->encode(0); return;
        }
    }
}
