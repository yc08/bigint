#include<iostream>
#include<vector>
#include<string>
#include<sstream>
#include"BigInt.h"
#define bigint Bigint<256>
void printbig(const std::vector<bigint>&vec){
    for(int i=0;i<vec.size();++i){
        std::cout<<vec[i].num()<<" ";
    }
    std::cout<<"\n";
}
template<typename T>
void printVec(const std::vector<T>&vec){
    for(const T &v:vec){
        std::cout<<v<<" ";
    }
    std::cout<<"\n";
}

bigint cal(bigint x,bigint y,int op){
    switch(op){
        case 0:
            return x*y;
        case 1:
            return x/y;
        case 2:
            return x%y;
        case 3:
            return x+y;
        case 4:
            return x-y;
        default:
            return bigint(0);
    }
}

bigint calculator(std::vector<std::string>&arr){
    size_t n=arr.size();
    std::vector<int>ops(n,0);
    std::vector<bigint>nums(n);
    std::vector<char>precedence={'*','/','%','+','-','E'};
    int numCount=-1,opCount=-1;
    for(const auto &token:arr){
        int op=-1;
        for(int i=0;i<precedence.size();++i){
            if(token[0]==precedence[i]&&token.size()==1){
                op=i;
                break;
            }
        }
        if(op!=-1){
            if(ops[opCount]<op){
                while(opCount >= 0 && ops[opCount] <= op){
                    char oper=ops[opCount--];
                    bigint b=nums[numCount--];
                    bigint a=nums[numCount];
                    bigint res;
                    nums[numCount]=cal(a,b,oper);
                }
            }
            ops[++opCount]=op;
        }
        else{
            nums[++numCount]=bigint(token);
        }
        // printbig(nums);
        // printVec(ops);
    }
    return nums[0];
}

void formatInput(std::string &input){
    std::string formatted;
    for(char c:input){
        if(c=='+'||c=='-'||c=='*'||c=='/'||c=='%'||c=='('||c==')'){
            formatted+=' ';
            formatted+=c;
            formatted+=' ';
        }
        else{
            formatted+=c;
        }
    }
    input=formatted;
}

int main(){
    std::vector<std::string>arr;
    std::string line;
    getline(std::cin,line);
    formatInput(line);
    std::stringstream ss(line);
    std::string token;
    while(ss>>token){
        if(token.empty()) continue;
        arr.push_back(token);
    }
    arr.push_back("E");
    std::cout<<calculator(arr).num()<<"\n";
    return 0;
}