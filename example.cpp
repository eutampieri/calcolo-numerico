#include <iostream>
#include "functions.hpp"

using namespace std;

void result(PointSearchResult res){
    cout << "A root has "<<(res.found?"":"not ")<<"been found in "<<res.iter<<" iterations: f("<<res.x<<")="<<res.y<<'\n';
}

int main(){
    double coeffs[] =  {0,0,0,0,0,1};
    Polynomial fifth = Polynomial(5, coeffs);
    // Initialize y=x^5
    Quadratic parabola = Quadratic(0.5, -4, +7);
    // y=1/2x^2-4x+7
    Exponential e = Exponential();
    // y=e^x
    Sine sine = Sine();
    // y=sin(x)
    DerivableCompositeFunction f1 = DerivableCompositeFunction(&fifth, &parabola);
    // f1(x)=(1/2x^2-4x+7)^5
    DerivableCompositeFunction f2 = DerivableCompositeFunction(&sine, &e);
    // f2(x)=sin(e^x)
    cout << "f1: ";
    result(f1.findRootBisection(-1, 7, 1e-9, 1e7));
    cout << "f2: ";
    result(f2.findRootNewton(3, 1e-9, 1e7));
    SumOfDerivableFunctions f3 = SumOfDerivableFunctions(&e, &f1, true);
    result(f3.findRootNewton(3, 1e-9, 1e7));
    // Calculate the intersection between e^x and (1/2x^2-4x+7)^5
}
