#include<iostream>
#include<bitset>
#include<string>
#include<algorithm>
#include<vector>

template<size_t N>
struct Bigint{
    std::bitset<N> bits;

    Bigint(){
        bits.reset();
    }
    Bigint(long long value){
        bits = std::bitset<N>(value);
    }
    Bigint(int value){
        bits = std::bitset<N>(value);
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

    bool isNegative() const {
        return bits[N-1];
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
        if(isNegative() && !other.isNegative()) return false;
        if(!isNegative() && other.isNegative()) return true;
        for (int i = N - 1; i >= 0; --i) {
            if (bits[i] != other.bits[i]) {
                return bits[i] > other.bits[i];
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

    Bigint operator<<(const size_t &shift) const {
        Bigint result;
        result.bits = bits << shift;
        return result;
    }

    Bigint operator>>(const size_t &shift) const {
        Bigint result;
        result.bits = bits >> shift;
        return result;
    }
    
    Bigint& operator++() {
        *this = *this + Bigint(1);
        return *this;
    }

    Bigint operator++(int) {
        Bigint tmp = *this;
        ++(*this);
        return tmp;
    }

    Bigint operator--() {
        *this = *this - Bigint(1);
        return *this;
    }

    Bigint operator--(int) {
        Bigint tmp = *this;
        --(*this);
        return tmp;
    }

    Bigint operator+(const Bigint &other) const {
        Bigint result;
        bool carry = false;
        for (size_t i = 0; i < N; ++i) {
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

    Bigint operator-(const long long &other) const {
        Bigint negOther = ~other;
        Bigint one;
        one.bits[0] = 1;
        negOther = negOther + one;
        return *this + negOther;
    }

    Bigint operator-(const int &other) const {
        Bigint negOther = ~other;
        Bigint one;
        one.bits[0] = 1;
        negOther = negOther + one;
        return *this + negOther;
    }

    Bigint operator*(const Bigint &other) const {
        Bigint result;
        Bigint multiplicand = *this;
        Bigint multiplier = other;

        for (size_t i = 0; i < N; ++i) {
            if (multiplier.bits[i]) {
                result = result + (multiplicand << i);
            }
        }
        return result;
    }

    Bigint operator/(const Bigint &other) const {
        bool neg = isNegative() ^ other.isNegative();
        Bigint dividend = abs();
        Bigint divisor = other.abs();

        Bigint quotient, remainder;
        for (int i = N - 1; i >= 0; --i) {
            remainder.bits <<= 1;
            remainder.bits[0] = dividend.bits[i];
            if (remainder >= divisor) {
                remainder = remainder - divisor;
                quotient.bits[i] = 1;
            }
        }
        if (neg) {
            quotient = ~quotient + Bigint(1);
        }
        return quotient;
    }


    void print() const {
        for (int i = N - 1; i >= 0; --i) {
            std::cout << bits[i];
        }
        std::cout << std::endl;
    }

    Bigint abs() const {
        if (!bits[N-1]) return *this;
        Bigint inv = ~(*this);
        Bigint one;
        one.bits[0] = 1;
        return inv + one; 
    }

    std::string num() const {
        Bigint<N> zero(0);
        Bigint<N> ten(10);
        Bigint<N> n = abs();
        std::string result;

        while (n > zero) {
            Bigint<N> quotient, remainder;
            quotient = n / ten;
            remainder = n - (quotient * ten);

            unsigned digit = 0;
            for (size_t i = 0; i < N; ++i)
                if (remainder.bits[i]) digit += (1ULL << i);

            result.push_back('0' + digit);
            n = quotient;
        }

        if (result.empty())
            result = "0";

        if (isNegative())
            result.push_back('-');

        std::reverse(result.begin(), result.end());
        return result;
    }

};

int main(){
    Bigint<128>a,b;
    std::string s;
    std::cin>>s;
    a=Bigint<128>(s);
    char op;
    std::cin>>op;
    std::cin>>s;
    b=Bigint<128>(s);
    if(op=='+'){
        std::cout<<(a+b).num()<<std::endl;
    }else if(op=='-'){
        std::cout<<(a-b).num()<<std::endl;
    }else if(op=='*'){
        std::cout<<(a*b).num()<<std::endl;
    }else if(op=='/'){
        std::cout<<(a/b).num()<<std::endl;
    }
    

    return 0;
}