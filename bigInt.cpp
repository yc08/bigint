#include<iostream>
#include<string>
#include<climits>

struct int128{
    long long high;
    unsigned long long low;

    int128(): high(0), low(0) {}
    int128(long long value): high(0), low(value) {}

    int128(const std::string& s){
        if(s.size() > 40) throw std::out_of_range("String too long for int128");
        if(s.empty()){ high = 0; low = 0; return; }
        bool neg = s[0] == '-';
        size_t i = neg ? 1 : 0;
        high = 0;
        low = 0;
        for(; i < s.size(); ++i){
            char c = s[i];
            if(c < '0' || c > '9') throw std::invalid_argument("Invalid character in string");
            if(low > (ULLONG_MAX)/10){
                if(high > (LLONG_MAX - 1)/10) throw std::out_of_range("Value too large for int128");
                high = high * 10 + low / (ULLONG_MAX/10 + 1);
                low = low % (ULLONG_MAX/10 + 1) * 10;
            }
            else{
                low = low * 10;
                low += c - '0';
            }
        }
    }
};

int128 operator"" _i(const char* s, std::size_t len){
    return int128(std::string(s, len));
}

std::ostream &operator<<(std::ostream &os, const int128 & value){
    os<< value.high << ":" << value.low;
    return os;
}

int main(){
    int128 a="12345678912345678901234567899"_i;
    int128 b=987654321098765432;
    std::cout<<a;
}