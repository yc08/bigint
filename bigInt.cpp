#include <iostream>
#include <string>
#include <climits>
#include <stdexcept>
#include <cctype>
#include <cstddef>
#include <cstdint>
#include <vector>
#include <algorithm>

struct int128{
    long long high;
    unsigned long long low;

    int128(): high(0), low(0) {}
    // sign-extend high for signed 64-bit input
    int128(long long value): high(value < 0 ? -1 : 0), low(static_cast<unsigned long long>(value)) {}
    int128(unsigned long long value): high(0), low(value) {}

    // multiply (hi,lo) by 10 and add digit d (0..9), portable (no __int128)
    static void mul10_add(unsigned long long &hi, unsigned long long &lo, unsigned int d){
        // lo * 10 = lo*8 + lo*2
        unsigned long long lo8 = lo << 3;
        unsigned long long lo2 = lo << 1;
        unsigned long long carry = (lo >> 61) + (lo >> 63);
        unsigned long long lo_mul = lo8 + lo2;
        if(lo_mul < lo8) ++carry;
        unsigned long long new_lo = lo_mul + d;
        if(new_lo < lo_mul) ++carry;
        if(hi > (ULLONG_MAX - carry) / 10) throw std::out_of_range("Value too large for int128");
        hi = hi * 10 + carry;
        lo = new_lo;
    }

    // decimal string constructor (portable)
    int128(const std::string& s){
        if(s.size() > 40) throw std::out_of_range("String too long for int128");
        if(s.empty()){ high = 0; low = 0; return; }
        bool neg = s[0] == '-';
        size_t i = neg ? 1 : 0;

        unsigned long long hi = 0;
        unsigned long long lo = 0;

        for(; i < s.size(); ++i){
            unsigned char ch = static_cast<unsigned char>(s[i]);
            if(ch < '0' || ch > '9') throw std::invalid_argument("Invalid character in string");
            unsigned int d = ch - '0';
            mul10_add(hi, lo, d);
        }

        const unsigned long long POS_HI_MAX = static_cast<unsigned long long>(LLONG_MAX); // 2^63-1
        const unsigned long long NEG_HI_LIMIT = (1ULL << 63); // 2^63

        if(!neg){
            if(hi > POS_HI_MAX) throw std::out_of_range("Value too large for positive int128");
            high = static_cast<long long>(hi);
            low = lo;
        }else{
            if(hi > NEG_HI_LIMIT || (hi == NEG_HI_LIMIT && lo != 0)) throw std::out_of_range("Value too large (negative) for int128");
            // two's complement negate (hi,lo)
            lo = ~lo;
            lo = lo + 1;
            unsigned long long carry2 = (lo == 0) ? 1ULL : 0ULL;
            hi = ~hi;
            hi = hi + carry2;
            high = static_cast<long long>(hi);
            low = lo;
        }
    }

    // produce full decimal string (portable, no __int128)
    std::string toString() const {
        // get unsigned magnitude
        uint64_t hi = static_cast<uint64_t>(high);
        uint64_t lo = low;
        bool negative = (high < 0);

        if(negative){
            hi = ~hi;
            lo = ~lo;
            ++lo;
            if(lo == 0) ++hi;
        }

        if(hi == 0 && lo == 0) return std::string(negative ? "-0" : "0");

        // divide unsigned 128 by 10 repeatedly
        auto divmod_u128_by_10 = [](uint64_t hi_in, uint64_t lo_in, uint64_t &qh, uint64_t &ql)->uint32_t{
            qh = 0; ql = 0;
            uint32_t rem = 0;
            for(int pos = 127; pos >= 0; --pos){
                unsigned int bit;
                if(pos >= 64) bit = (hi_in >> (pos - 64)) & 1U;
                else bit = (lo_in >> pos) & 1U;
                rem = (rem << 1) | bit;
                if(rem >= 10){
                    rem -= 10;
                    if(pos >= 64) qh |= (1ULL << (pos - 64));
                    else ql |= (1ULL << pos);
                }
            }
            return rem;
        };

        std::vector<char> digits;
        while(hi != 0 || lo != 0){
            uint64_t qh=0, ql=0;
            uint32_t rem = divmod_u128_by_10(hi, lo, qh, ql);
            digits.push_back(char('0' + rem));
            hi = qh; lo = ql;
        }

        if(negative) digits.push_back('-');
        std::reverse(digits.begin(), digits.end());
        return std::string(digits.begin(), digits.end());
    }
};

int128 operator"" _i(const char* s, std::size_t len){
    return int128(std::string(s, len));
}

std::ostream &operator<<(std::ostream &os, const int128 & value){
    os << value.toString();
    return os;
}

std::istream &operator>>(std::istream &is, int128& value){
    std::string s;
    is>>s;
    value = int128(s);
    return is;
}

int128 operator+(const int128 &a, const int128 &b){
    int128 res;
    res.low = a.low + b.low;
    res.high = a.high + b.high + (res.low < a.low ? 1 : 0);
    return res;
}

int128 operator-(const int128 &a, const int128 &b){
    int128 res;
    res.low = a.low + -b.low;
    res.high = a.high + -b.high - (b.low > a.low ? 1 : 0);
    return res;
}

int main(){
    int128 a="12345678912345678901234567899"_i;
    int128 b=987654321098765432LL , c;
    std::cin>>b>>c;
    std::cout<<a<<'\n';
    std::cout<<b<<' '<<c<<std::endl;
    std::cout<<(b+c)<<' '<<(b-c)<<std::endl;
    return 0;
}