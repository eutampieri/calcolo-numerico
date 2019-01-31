#include <iostream>
#include <cmath>
#include "functions.hpp"

using namespace std;

//#region [rgba(0,0,150,0.15)]
void result(RootFindingResult res){
    cout << "A root has "<<(res.found?"":"not ")<<"been found in "<<res.iter<<" iterations: f("<<res.x<<")="<<res.y<<'\n';
}
//#endregion

int main(){
    //Polynomial fun = Polynomial();
    Quadratic q = Quadratic(1.0,-2.0,1.0);
    Polynomial p = Polynomial();
    DerivableCompositeFunction fun = DerivableCompositeFunction(&q, &p);
    cout << fun.func(3);
    char choice;
    double left=-1e2,right=2e2, threshold=1e-7;
    long long calc_limit=1e8;
    cout << "--- Numerical Methods ---\n";
    cout << "Leftmost point of the interval: ";
    cin >> left;
    cout << "Rightmost point of the interval: ";
    cin >> right;
    cout << "=========================\n     Choose a method     \n=========================\n\t[b] for bisection method\n\t[s] for the secant method\n\t[n] for Newton's method\nYour choice: ";
    cin >> choice;
    switch(choice){
    case 'b':
        result(fun.findRootBisection(left, right, threshold, calc_limit));
        break;
    case 's':
        result(fun.findRootSecant(left, right, threshold, calc_limit));
        break;
    case 'n':
        result(fun.findRootNewton(left, right, threshold, calc_limit));
        break;
    default:
        cout << "Invalid selection. Have a good day!";
        break;
    }
    return 0;
}
