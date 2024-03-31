#pragma once
#include<iostream>
#include <cstdint>

template<typename T = int32_t>
class Reverse {
private:
    bool* digits;
    int sizeT;

    void writeInBinary(T decimalNumber) {
        int i = sizeT - 1;
        digits[0] = decimalNumber < 0; // sign

        while (i > 0) {
            T remainder = decimalNumber % 2;
            // Divide the number by 2
            decimalNumber = decimalNumber / 2;

            digits[i] = remainder == !digits[0];

            --i;
        }
    }

public:

    void showbinary() {
        for (int i = 0; i < sizeT; ++i) {
            std::cout << digits[i];
        }
    }

    // constructor
    Reverse(T decimalNumber) {
        this->sizeT = sizeof(decimalNumber) * 8; // size of given type
        this->digits = new bool[this->sizeT];
        writeInBinary(decimalNumber);
    }
    
    // decimal representation of number
    T toDecimal() {
        T number{};
        T base = 1;
        for (int i = sizeT - 1; i > 0; --i) {
            number += (digits[0] ^ digits[i]) * base;
            base *= 2;
        }
        
        if (digits[0]) {
            return number * (-1);
        } else {
            return number;
        }   
    }

    // copy constructor
    Reverse(const Reverse<T>& number) {
        this->sizeT = number.sizeT;
        this->digits = new bool[this->sizeT];
        
        for (int i = 0; i < this->sizeT; ++i) {
            this->digits[i] = number.digits[i];
        }
    }

    // assignment operator
    Reverse<T>& operator= (const Reverse<T>& num) {
        if (this->digits != num.digits){
            for (int i = 0; i < sizeT; ++i) {
                this->digits[i] = num.digits[i];
            }
        }
        
        return *this;
    };

    // binary plus
    Reverse<T> operator+ (const Reverse<T>& Rnum) const {
        bool offset = 0;

        Reverse<T> res(0);

        for (int i = sizeT - 1; i >= 0; --i) {
            if (this->digits[i] ^ Rnum.digits[i]) {
                res.digits[i] = 1 ^ offset;
                if (res.digits[i]) {
                    offset = 0;
                }
                else {
                    offset = 1;
                }
            }
            else {
                if (this->digits[i]) {
                    res.digits[i] = offset;
                    offset = 1;
                }
                else {
                    res.digits[i] = offset;
                    offset = 0;
                }
            }
        }
        int i = sizeT - 1;
        while (offset && i >= 0) {
            res.digits[i] = res.digits[i] ^ offset;
            offset = res.digits[i] ^ offset;
            --i;
        }

        return res;
    }

    // unary minus
    Reverse<T> operator- () const {

        Reverse<T> res(0);
        for (int i = 0; i < sizeT; ++i) {
            res.digits[i] = !this->digits[i];
        }

        return res;
    }
    // binary minus
    Reverse<T> operator- (const Reverse<T>& Rnum) const {
        Reverse<T> res = *this + (-Rnum);

        return res;
    }
    // unary plus
    Reverse<T> operator+ () const {

        Reverse<T> res(0);
        for (int i = 0; i < sizeT; ++i) {
            res.digits[i] = this->digits[i];
        }

        return res;
    }
    
    bool operator==(const Reverse<T>& Rnum) const {
        // considering 0
        bool isZero = true;
        for (int i = 1; i < sizeT; ++i) {
            if (this->digits[i] ^ this->digits[0] || Rnum.digits[i] ^ Rnum.digits[0]) {
                isZero = false;
            }
        }
        if (isZero) return true;

        for (int i = 0; i < sizeT; ++i) {
            if (this->digits[i] != Rnum.digits[i]) {
                return false;
            }
        }
        return true;
    }

    bool operator<(const Reverse<T>& Rnum) const {
        
        if (*this == Rnum) return false; // equality
        if (Rnum.digits[0] && !this->digits[0]) return false; // different signs
        if (!Rnum.digits[0] && this->digits[0]) return true; // different signs

        // consider same signs
        for (int i = 1; i < sizeT; ++i) {
            if (this->digits[i] ^ Rnum.digits[i]) { // first different bits
                if (this->digits[i]) { // module of left number is greater
                    return this->digits[0];
                }
                else {
                    return !this->digits[0];
                }

            }
        }
        return true;
    }

    bool operator>(const Reverse<T>& Rnum) const {
        if (*this == Rnum) return false;
        return !(*this < Rnum);
    }

    bool operator!=(const Reverse<T>& Rnum) const {
        return !(*this == Rnum);
    }

    bool operator<=(const Reverse<T>& Rnum) const {
        return *this < Rnum || *this == Rnum;
    }

    bool operator>=(const Reverse<T>& Rnum) const {
        return *this > Rnum || *this == Rnum;
    }
    
    // multiplication operator
    Reverse<T> operator* (Reverse<T> Rnum) const {
        Reverse<T> res(0);
        bool sign = 0;

        if (Rnum < res) {
            for (int i = 0; i < sizeT; ++i) {
                Rnum.digits[i] = !Rnum.digits[i];
            }
            sign = !sign;
        }

        for (int i = sizeT - 1; i > 0; --i) {
            if (this->digits[i] ^ this->digits[0]) {
                res = res + Rnum;
            }
            Rnum = Rnum << 1;
        }
        
        res.digits[0] = this->digits[0] ^ sign;
        if (res.digits[0]){
            for (int i = 1; i < sizeT; ++i){
                res.digits[i] = !res.digits[i];
            }
        }
        return res;
    }

    // left-shift operator
    Reverse<T> operator<<(int numShift) const {
        Reverse<T> newNum(*this);

        if (numShift > 0) {
            for (int i = 1; i < sizeT; ++i) {
                if (sizeT - i > numShift) {
                    newNum.digits[i] = this->digits[i + numShift];
                }
                else {
                    newNum.digits[i] = 0;
                }
            }
        }
        else if (numShift < 0) {
            std::cerr << "Left-shift by a negative number of bits\n";
        }

        return newNum;
    }

    // right-shift operator
    Reverse<T> operator>>(int numShift) const {
        Reverse<T> newNum(*this);
        if (numShift > 0) {
            for (int i = sizeT - 1; i > 0; --i) {
                if (i > numShift) {
                    newNum.digits[i] = this->digits[i - numShift];
                }
                else {
                    newNum.digits[i] = this->digits[0];
                }
            }
        }
        else if (numShift < 0) {
            std::cerr << "Right-shift by a negative number of bits\n";
        }

        return newNum;
    }

    // division operator
    Reverse<T> operator/ (Reverse<T> Rnum) const {
        Reverse<T> res(0);
        if (Rnum == res) {
            std::cerr << "Division by zero\n";
            return *this;
        }

        res = *this;

        Reverse<T> quotient(0);
        
        bool sign = 0;
        if (res.digits[0] ^ Rnum.digits[0])  sign = !sign;

        if (res.digits[0]) {
            res = -res;
        }
        if (Rnum.digits[0]) {
            Rnum = -Rnum;
        }
        while (res >= Rnum) {
            res = res - Rnum;
            quotient = quotient + Reverse<T>(1);
        }
        if (sign) {
            quotient = -quotient;
        }
        return quotient;
    }
    
    Reverse<T> operator% (Reverse<T> Rnum) const {
        Reverse<T> res(0);
        bool sign = 0;
        if (Rnum < res){
            Rnum = -Rnum;
        }
        if (*this < res){
            res = -*this;
            sign = !sign;
        } 
        else {
            res = *this;
        }
        
        res = res - (res / Rnum) * Rnum;

        return res;
    }

    ~Reverse() {
        delete[] digits;
    }
};
