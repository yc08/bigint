#ifndef BIGINT_CPP
#define BIGINT_CPP
#include<iostream>
#include<bitset>
#include<algorithm>
#include<string>

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

    size_t size(){
        return N;
    }

    Bigint operator ~ () const {
        Bigint result;
        result.bits = ~bits;
        return result;
    }

    Bigint& operator = (const Bigint &other) {
        bits = other.bits;
        return *this;
    }

    Bigint& operator = (const long long &other) {
        Bigint temp(other);
        bits = temp.bits;
        return *this;
    }

    Bigint& operator = (const int &other) {
        Bigint temp(other);
        bits = temp.bits;
        return *this;
    }

    bool operator==( const Bigint &other) const {
        return bits == other.bits;
    }

    bool operator==( const long long &other) const {
        Bigint temp(other);
        return bits == temp.bits;
    }

    bool operator==( const int &other) const {
        Bigint temp(other);
        return bits == temp.bits;
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

    bool operator>( const long long &other) const {
        Bigint temp(other);
        return *this > temp;
    }

    bool operator>( const int &other) const {
        Bigint temp(other);
        return *this > temp;
    }

    bool operator>=( const Bigint &other) const {
        return (*this > other) || (*this == other);
    }

    bool operator>=( const long long &other) const {
        Bigint temp(other);
        return *this >= temp;
    }

    bool operator>=( const int &other) const {
        Bigint temp(other);
        return *this >= temp;
    }

    bool operator<( const Bigint &other) const {
        return !(*this >= other);
    }

    bool operator<( const long long &other) const {
        Bigint temp(other);
        return *this < temp;
    }

    bool operator<( const int &other) const {
        Bigint temp(other);
        return *this < temp;
    }

    bool operator<=( const Bigint &other) const {
        return !(*this > other);
    }

    bool operator<=( const long long &other) const {
        Bigint temp(other);
        return *this <= temp;
    }

    bool operator<=( const int &other) const {
        Bigint temp(other);
        return *this <= temp;
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

    Bigint& operator<<=( const size_t &shift) {
        bits <<= shift;
        return *this;
    }

    Bigint& operator>>=( const size_t &shift) {
        bits >>= shift;
        return *this;
    }

    Bigint operator&(const Bigint &other) const {
        Bigint result;
        result.bits = bits & other.bits;
        return result;
    }

    Bigint operator|(const Bigint &other) const {
        Bigint result;
        result.bits = bits | other.bits;
        return result;
    }

    Bigint operator^(const Bigint &other) const {
        Bigint result;
        result.bits = bits ^ other.bits;
        return result;
    }
    
    Bigint& operator++() {
        *this = *this + 1;
        return *this;
    }

    Bigint operator++(int) {
        Bigint tmp = *this;
        ++(*this);
        return tmp;
    }

    Bigint operator--() {
        *this = *this - 1;
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
    
    Bigint operator+=( const Bigint &other) {
        *this = *this + other;
        return *this;
    }

    Bigint operator+(const long long &other) const {
        Bigint otherBigint(other);
        return *this + otherBigint;
    }

    Bigint operator+=( const long long &other) {
        Bigint otherBigint(other);
        *this = *this + otherBigint;
        return *this;
    }

    Bigint operator+(const int &other) const {
        Bigint otherBigint(other);
        return *this + otherBigint;
    }

    Bigint operator+=( const int &other) {
        Bigint otherBigint(other);
        *this = *this + otherBigint;
        return *this;
    }

    Bigint operator-( Bigint other) const {
        other = ~other;
        return *this + other + 1;
    }

    Bigint& operator-=(const Bigint &other) const {
        Bigint negOther = ~Bigint(other);
        return *this + negOther + 1;
    }

    Bigint operator-( long long other) const {
        Bigint negOther = ~Bigint(other);
        return *this + negOther + 1;
    }

    Bigint& operator-=(const long long &other) const {
        Bigint negOther = ~Bigint(other);
        return *this + negOther + 1;
    }

    Bigint operator-( int other) const {
        Bigint negOther = ~Bigint(other);
        return *this + negOther + 1;
    }

    Bigint& operator-=(const int &other) const {
        Bigint negOther = ~Bigint(other);
        return *this + negOther + 1;
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

    Bigint operator*=( const Bigint &other) {
        *this = *this * other;
        return *this;
    }

    Bigint operator*(const long long &other) const {
        Bigint otherBigint(other);
        return *this * otherBigint;
    }

    Bigint operator*=( const long long &other) {
        Bigint otherBigint(other);
        *this = *this * otherBigint;
        return *this;
    }

    Bigint operator*(const int &other) const {
        Bigint otherBigint(other);
        return *this * otherBigint;
    }

    Bigint operator*=( const int &other) {
        Bigint otherBigint(other);
        *this = *this * otherBigint;
        return *this;
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

    Bigint operator/=( const Bigint &other) {
        *this = *this / other;
        return *this;
    }

    Bigint operator/(const long long &other) const {
        Bigint otherBigint(other);
        return *this / otherBigint;
    }

    Bigint operator/=( const long long &other) {
        Bigint otherBigint(other);
        *this = *this / otherBigint;
        return *this;
    }

    Bigint operator/(const int &other) const {
        Bigint otherBigint(other);
        return *this / otherBigint;
    }

    Bigint operator/=( const int &other) {
        Bigint otherBigint(other);
        *this = *this / otherBigint;
        return *this;
    }

    Bigint operator%(const Bigint &other) const {
        Bigint quotient = *this / other;
        Bigint product = quotient * other;
        Bigint remainder = *this - product;
        return remainder;
    }

    Bigint operator%=( const Bigint &other) {
        *this = *this % other;
        return *this;
    }

    Bigint operator%(const long long &other) const {
        Bigint otherBigint(other);
        return *this % otherBigint;
    }

    Bigint operator%=( const long long &other) {
        Bigint otherBigint(other);
        *this = *this % otherBigint;
        return *this;
    }

    Bigint operator%(const int &other) const {
        Bigint otherBigint(other);
        return *this % otherBigint;
    }

    Bigint operator%=( const int &other) {
        Bigint otherBigint(other);
        *this = *this % otherBigint;
        return *this;
    }

    void printbit() const {
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

            // <-- safe digit extraction: only use bits < 64 to avoid UB
            unsigned digit = 0;
            size_t upto = std::min<size_t>(64, N);
            for (size_t i = 0; i < upto; ++i)
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

template<size_t A, size_t B>
Bigint<(A > B ? A : B)> operator+(const Bigint<A>& l, const Bigint<B>& r) {
    constexpr size_t R = (A > B ? A : B);
    Bigint<R> a;
    Bigint<R> b;
    for (size_t i = 0; i < A; ++i) a.bits[i] = l.bits[i];
    for (size_t i = 0; i < B; ++i) b.bits[i] = r.bits[i];

    return a + b;
}
template<size_t A, size_t B>
Bigint<(A > B ? A : B)> operator-(const Bigint<A>& l, const Bigint<B>& r) {
    constexpr size_t R = (A > B ? A : B);
    Bigint<R> a;
    Bigint<R> b;
    for (size_t i = 0; i < A; ++i) a.bits[i] = l.bits[i];
    for (size_t i = 0; i < B; ++i) b.bits[i] = r.bits[i];
    
    return a - b;
}
template<size_t A, size_t B>
Bigint<(A > B ? A : B)> operator*(const Bigint<A>& l, const Bigint<B>& r) {
    constexpr size_t R = (A > B ? A : B);
    Bigint<R> a;
    Bigint<R> b;
    for (size_t i = 0; i < A; ++i) a.bits[i] = l.bits[i];
    for (size_t i = 0; i < B; ++i) b.bits[i] = r.bits[i];

    return a * b;
}
template<size_t A, size_t B>
Bigint<(A > B ? A : B)> operator/(const Bigint<A>& l, const Bigint<B>& r) {
    constexpr size_t R = (A > B ? A : B);
    Bigint<R> dividend;
    Bigint<R> divisor;
    for (size_t i = 0; i < A; ++i) dividend.bits[i] = l.bits[i];
    for (size_t i = 0; i < B; ++i) divisor.bits[i] = r.bits[i];

    return dividend / divisor;
}
template<size_t A, size_t B>
bool operator<(const Bigint<A>& l, const Bigint<B>& r) {
    constexpr size_t R = (A > B ? A : B);
    Bigint<R> a;
    Bigint<R> b;
    for (size_t i = 0; i < A; ++i) a.bits[i] = l.bits[i];
    for (size_t i = 0; i < B; ++i) b.bits[i] = r.bits[i];

    return a < b;
}

template<size_t A, size_t B>
bool operator >(const Bigint<A>& l, const Bigint<B>& r) {
    constexpr size_t R = (A > B ? A : B);
    Bigint<R> a;
    Bigint<R> b;
    for (size_t i = 0; i < A; ++i) a.bits[i] = l.bits[i];
    for (size_t i = 0; i < B; ++i) b.bits[i] = r.bits[i];

    return a>b;
}
template<size_t A, size_t B>
bool operator <=(const Bigint<A>& l, const Bigint<B>& r) {
    constexpr size_t R = (A > B ? A : B);
    Bigint<R> a;
    Bigint<R> b;
    for (size_t i = 0; i < A; ++i) a.bits[i] = l.bits[i];
    for (size_t i = 0; i < B; ++i) b.bits[i] = r.bits[i];

    return a<=b;
}
template<size_t A, size_t B>
bool operator >=(const Bigint<A>& l, const Bigint<B>& r) {
    constexpr size_t R = (A > B ? A : B);
    Bigint<R> a;
    Bigint<R> b;
    for (size_t i = 0; i < A; ++i) a.bits[i] = l.bits[i];
    for (size_t i = 0; i < B; ++i) b.bits[i] = r.bits[i];

    return a>=b;
}
template<size_t A, size_t B>
bool operator ==(const Bigint<A>& l, const Bigint<B>& r) {
    constexpr size_t R = (A > B ? A : B);
    Bigint<R> a;
    Bigint<R> b;
    for (size_t i = 0; i < A; ++i) a.bits[i] = l.bits[i];
    for (size_t i = 0; i < B; ++i) b.bits[i] = r.bits[i];

    return a==b;
}
template<size_t A, size_t B>
Bigint<(A > B ? A : B)> operator%(const Bigint<A>& l, const Bigint<B>& r) {
    constexpr size_t R = (A > B ? A : B);
    Bigint<R> dividend;
    Bigint<R> divisor;
    for (size_t i = 0; i < A; ++i) dividend.bits[i] = l.bits[i];
    for (size_t i = 0; i < B; ++i) divisor.bits[i] = r.bits[i];

    return dividend % divisor;
}
template<size_t A, size_t B>
Bigint<(A > B ? A : B)> operator&(const Bigint<A>& l, const Bigint<B>& r) {
    constexpr size_t R = (A > B ? A : B);
    Bigint<R> a;
    Bigint<R> b;
    for (size_t i = 0; i < A; ++i) a.bits[i] = l.bits[i];
    for (size_t i = 0; i < B; ++i) b.bits[i] = r.bits[i];

    return a&b;
}
template<size_t A, size_t B>
Bigint<(A > B ? A : B)> operator|(const Bigint<A>& l, const Bigint<B>& r) {
    constexpr size_t R = (A > B ? A : B);
    Bigint<R> a;
    Bigint<R> b;
    for (size_t i = 0; i < A; ++i) a.bits[i] = l.bits[i];
    for (size_t i = 0; i < B; ++i) b.bits[i] = r.bits[i];

    return a|b;
}
template<size_t A, size_t B>
Bigint<(A > B ? A : B)> operator^(const Bigint<A>& l, const Bigint<B>& r) {
    constexpr size_t R = (A > B ? A : B);
    Bigint<R> a;
    Bigint<R> b;
    for (size_t i = 0; i < A; ++i) a.bits[i] = l.bits[i];
    for (size_t i = 0; i < B; ++i) b.bits[i] = r.bits[i];

    return a^b;
}
template<size_t A, size_t B>
Bigint<(A > B ? A : B)> operator&=(const Bigint<A>& l, const Bigint<B>& r) {
    constexpr size_t R = (A > B ? A : B);
    Bigint<R> a;
    Bigint<R> b;
    for (size_t i = 0; i < A; ++i) a.bits[i] = l.bits[i];
    for (size_t i = 0; i < B; ++i) b.bits[i] = r.bits[i];

    a = a & b;
    return a;
}
template<size_t A, size_t B>
Bigint<(A > B ? A : B)> operator|=(const Bigint<A>& l, const Bigint<B>& r) {
    constexpr size_t R = (A > B ? A : B);
    Bigint<R> a;
    Bigint<R> b;
    for (size_t i = 0; i < A; ++i) a.bits[i] = l.bits[i];
    for (size_t i = 0; i < B; ++i) b.bits[i] = r.bits[i];

    a = a | b;
    return a;
}
template<size_t A, size_t B>
Bigint<(A > B ? A : B)> operator^=(const Bigint<A>& l, const Bigint<B>& r) {
    constexpr size_t R = (A > B ? A : B);
    Bigint<R> a;
    Bigint<R> b;
    for (size_t i = 0; i < A; ++i) a.bits[i] = l.bits[i];
    for (size_t i = 0; i < B; ++i) b.bits[i] = r.bits[i];

    a = a ^ b;
    return a;
}

#endif