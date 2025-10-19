#include<iostream>
#include<bitset>

struct Bigint{
    std::bitset<16> bits;

    Bigint(){
        bits.reset();
    }
    Bigint operator ~ () const {
        Bigint result;
        result.bits = ~bits;
        return result;
    }

    Bigint operator = (const Bigint &other) {
        bits = other.bits;
        return *this;
    }

    bool operator==( const Bigint &other) const {
        return bits == other.bits;
    }

    bool operator>( const Bigint &other) const {
        for (int i = bits.size() - 1; i >= 0; --i) {
            if (bits[i] != other.bits[i]) {
                return bits[i];
            }
        }
        return false;
    }

    bool operator>=( const Bigint &other) const {
        return (*this > other) || (*this == other);
    }

    bool operator<( const Bigint &other) const {
        return !(*this >= other);
    }

    bool operator<=( const Bigint &other) const {
        return !(*this > other);
    }
    
    Bigint operator+(const Bigint &other) const {
        Bigint result;
        bool carry = false;
        for (size_t i = 0; i < bits.size(); ++i) {
            bool bit1 = bits[i];
            bool bit2 = other.bits[i];
            result.bits[i] = bit1 ^ bit2 ^ carry;
            carry = (bit1 && bit2) || (carry && (bit1 ^ bit2));
        }
        return result;
    }

    Bigint operator-(const Bigint &other) const {
        Bigint negOther = ~other;
        Bigint one;
        one.bits[0] = 1;
        negOther = negOther + one;
        return *this + negOther;
    }

    Bigint operator*(const Bigint &other) const {
        Bigint result;
        for (size_t i = 0; i < bits.size(); ++i) {
            if (other.bits[i]) {
                Bigint temp = *this;
                temp.bits <<= i;
                result = result + temp;
            }
        }
        return result;
    }

    Bigint operator/(const Bigint &other) const {
        Bigint quotient, remainder;
        for (int i = bits.size() - 1; i >= 0; --i) {
            remainder.bits <<= 1;
            remainder.bits[0] = bits[i];
            if (remainder >= other) {
                remainder = remainder - other;
                quotient.bits[i] = 1;
            }
        }
        return quotient;
    }

    void print() const {
        for (int i = bits.size() - 1; i >= 0; --i) {
            std::cout << bits[i];
        }
        std::cout << std::endl;
    }

};

int main(){
    Bigint a, b, c, d;
    a.bits[0] = 1; // 1
    a.bits[3] = 1; // 8
    b.bits[1] = 1; // 2
    b.bits[3] = 1; // 8

    c = a + b; // should be 10 (1010)
    d = a - b; // should be -6 (in two's complement)

    std::cout << "a: ";
    a.print();
    std::cout << "b: ";
    b.print();
    std::cout << "a + b: ";
    c.print();
    std::cout << "a - b: ";
    d.print();
    std::cout << "a * b: ";
    Bigint e = a * b; // should be 90 (1011010)
    e.print();
    std::cout << "a / b: ";
    Bigint f = a / b; // should be 0 (0)
    f.print();
    return 0;
}