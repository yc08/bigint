#include<iostream>
#include<vector>
#include<string>
#include<sstream>
#include"BigInt.h"
#define bigint Bigint<256>

bigint cal(std::vector<std::string>&arr){
    size_t n=arr.size();
    std::vector<char>ops(n,' ');
    std::vector<bigint>nums(n);
    int numCount=0,opCount=0;
    for(const auto &token:arr){
        
    }
    return nums[0];
}

int main(){
    std::vector<std::string>arr;
    std::string line;
    getline(std::cin,line);
    std::stringstream ss(line);
    std::string token;
    while(ss>>token){
        if(token.empty()) continue;
        arr.push_back(token);
    }
    std::cout<<cal(arr).num()<<"\n";
    return 0;
}