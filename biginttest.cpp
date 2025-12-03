#include<iostream>
#include "Bigint.h"
using namespace std;
int main(){
    Bigint<1024> a("290000000000000000000000000");
    Bigint<512> b(15);

    Bigint<1024> c = a + b;
    Bigint<1024> d = c - 10;
    Bigint<1024> e = d ^ c;
    Bigint<1024> f = a * b;
    Bigint<1024> g = a / b;
    Bigint<1024> h = a % b;
    Bigint<1024> i = a & b;
    Bigint<1024> j = a | b;

    std::cout << "a: " << a.num() << "\n";
    std::cout << "b: " << b.num() << "\n";
    std::cout << "a + b: " << c.num() << "\n";
    std::cout << "a + b - 10: " << d.num() << "\n";
    std::cout << "(a + b) ^ (a + b - 10): " << e.num() << "\n";
    std::cout << "a * b: " << f.num() << "\n";
    std::cout << "a / b: " << g.num() << "\n";
    std::cout << "a % b: " << h.num() << "\n";
    std::cout << "a & b: " << i.num() << "\n";
    std::cout << "a | b: " << j.num() << "\n";

    return 0;
}