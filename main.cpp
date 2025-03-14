#include <iostream>
template<int EXP, bool Enable = true>
struct Exp{
    double operator()(double value){
        Exp<EXP -1> next;
        return value * next(value);
    }
};

template<int EXP> //den här distinktionen görs oavsett om vi har  defaultparametern satt till true
struct Exp<EXP, EXP < 0>{ //bättre specialisering
    double operator()(double value){
        Exp<-EXP> next;
        return 1 / next(value);
    }
};
template<>
struct Exp<0>{
    double operator()(double value) {
        return 1.0;
    }
};

int main() {
    Exp<3> exp; //Gör den känslig för negativa exponenter!
    std::cout << exp(3.14159) << "\n"; //29808.9

}