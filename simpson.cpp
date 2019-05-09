#define H 1e-3
#include <iostream>
#include <cmath>
using namespace std;

double xi(double start, double i){
    return start + i*H;
}

double f(double x){
    return exp(-x*x);
}

int main(){
    double start = 0, end = 5;

    double res = 0;
    for(double i = 1; i<= (end-start)/H/2.0; i++){
        res += f(xi(start, 2*i-2))+4*f(xi(start, 2*i-1))+f(xi(start, 2*i));
    }
    res*=H/3.0;
    cout << res<<'\n';
}