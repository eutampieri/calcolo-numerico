#include <iostream>
using namespace std;
double f(double x){
    return x; // y = x
}
int main(){
    double start = 0, end = 5, steps = 1e3;
    double h = (end-start)/steps;

    double res = 0;

    for(double i = start; i<=end; i+=h){
        double lower_area = h*f(i);
        double upper_area = h*f(i+h);
        res+=(lower_area+upper_area)/2.0;
    }
    cout << "Integral of f(x) between "<<start << " and "<< end <<" = "<<res<<'\n';
}