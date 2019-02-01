#include "functions.hpp"
#include <iostream>

using namespace std;

void result(PointSearchResult res){
    cout << "A root has "<<(res.found?"":"not ")<<"been found in "<<res.iter<<" iterations: f("<<res.x<<")="<<res.y<<'\n';
}

int main(){
    double a, b;
    cin >> a >> b;
    Cubic f = Cubic(-0.50598e-10, 0.38292e-7, 0.74363e-4, 0.88318e-2);
    cout << "Newton's method: ";
    result(f.findRootNewton(a, 1e-5, 1e7));
    cout << "Bisection method: ";
    result(f.findRootBisection(a, b, 1e-5, 1e7));
    cout << "Secants method: ";
    result(f.findRootSecants(a, b,1e-5, 1e7));
}