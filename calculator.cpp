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

std::vector<char>precedence={'*','/','%','+','-','&','^','|','(',')','E'};

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
        case 5:
            return x&y;
        case 6:
            return x^y;
        case 7:
            return x|y;
        default:
            return bigint(0);
    }
}

bigint calculator(std::vector<std::string>&arr){
    size_t n=arr.size();
    std::vector<int>ops(n,0);
    std::vector<bigint>nums(n);
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
                    if(precedence[op]=='(') break;
                    if(precedence[op]==')' && precedence[ops[opCount]]=='('){
                        ops[opCount--]=0;
                        break;
                    }
                    char oper=ops[opCount--];
                    ops[opCount+1]=0;
                    bigint b=nums[numCount--];
                    nums[numCount+1]=0;
                    bigint a=nums[numCount];
                    nums[numCount]=cal(a,b,oper);
                }
            }
            if(precedence[op]!=')')ops[++opCount]=op;
        }
        else{
            nums[++numCount]=bigint(token);
        }
        // printbig(nums);
        // printVec(ops);
        // std::cout<<std::endl;
    }
    return nums[0];
}

void formatInput(std::string &input, std::vector<std::string>&arr){
    std::string formatted;
    for(char &c:input){
        if(c>='0' && c<='9'){
            formatted+=c;
            continue;
        }
        formatted+=" ";
        formatted+=c;
        formatted+=" ";
    }
    formatted+=" E";
    std::stringstream ss(formatted);
    std::string token;
    
    while(ss>>token){
        if(token.empty()) continue;
        arr.push_back(token);
    }
}

bool init(){
    std::vector<std::string>arr;

    std::string line;
    getline(std::cin,line);
    if(line.empty()) return false;
    formatInput(line,arr);

    std::cout<<calculator(arr).num()<<"\n------------\n";

    return true;
}

int main(){

    while(init()) {
        void();
    }

    return 0;
}