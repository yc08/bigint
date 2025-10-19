#include<iostream>
#include<bitset>
#include<string>
#include<algorithm>
#include<vector>

struct Bigint{
    std::bitset<128> bits;

    Bigint(){
        bits.reset();
    }
    Bigint(long long value){
        bits = std::bitset<128>(value);
    }
    Bigint(int value){
        bits = std::bitset<128>(value);
    }
    Bigint(const std::string &value){
        bits.reset();
        Bigint ten(10);
        bool isNegative = value[0] == '-';
        for (size_t i = 0; i < value.size(); ++i) {
            char digit = value[i];
            if (digit < '0' || digit > '9') continue;
            Bigint temp = (*this) * ten;
            Bigint digitBigint(digit - '0');
            *this = temp + digitBigint;
        }
        if (isNegative) {
            *this = ~(*this);
            Bigint one(1);
            *this = *this + one;
        }
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

    Bigint operator+(const long long &other) const {
        Bigint result;
        Bigint otherBigint(other);
        result = *this + otherBigint;
        return result;
    }

    Bigint operator+(const int &other) const {
        Bigint result;
        Bigint otherBigint(other);
        result = *this + otherBigint;
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

    Bigint abs() const {
        if (!bits[bits.size()-1]) return *this;
        Bigint inv = ~(*this);
        Bigint one;
        one.bits[0] = 1;
        return inv + one; 
    }

    std::string num() {
        Bigint num = *this;
        Bigint zero(0);
        Bigint ten(10);
        Bigint n = num.abs();
        std::string result;
        if (n == zero) return "0";
        while (n > zero) {
            Bigint remainder;
            Bigint quotient;
            remainder = n;
            quotient = n / ten;
            remainder = n - (quotient * ten);
            char digit = '0' + static_cast<char>(remainder.bits.to_ullong());
            result.push_back(digit);
            n = quotient;
        }
        if (num.bits[num.bits.size()-1]) {
            result.push_back('-');
        }
        std::reverse(result.begin(), result.end());
        return result;
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
    std::cout << "a : "<< a.num() << std::endl;
    std::cout << "b : "<< b.num() << std::endl;
    std::cout << "a + b: "<< c.num() << std::endl;
    std::cout << "a - b: "<< d.num() << std::endl;
    Bigint e = Bigint("123456787654323456776543");
    std::cout << "e : "<< e.num() << std::endl;
    Bigint f;
    std::string s;
    std::cin>>s;
    f = Bigint(s);
    std::cout<<"f : "<<f.num()<<std::endl;
    return 0;
}