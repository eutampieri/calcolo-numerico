#include <iostream>
#include <cmath>

//#region [rgba(63,32,127,0.7)]
#include "es1.h"
//#include "es2.h"
//#endregion

#define f func

using namespace std;

//#region [rgba(0,0,150,0.15)]
void result(double x, long long iter, bool found){
    cout << "A root has "<<(found?"":"not ")<<"been found in "<<iter<<" iterations: f("<<x<<")="<<func(x)<<'\n';
}
void result(double x, long long iter){
    result(x,iter,true);
}
//#endregion

//#region [rgba(0,155,57,0.25)]
void bisection(double lb, double ub, double precision, long long max_iter){
    long long k=0;
    double x=lb;
    while(abs(func(x))>precision&&k<max_iter){
        x=(ub+lb)/2;
        if(func(x)==0){
            result(x,k);
            return;
        }
        if(func(x)*func(ub)<0){
            lb=x;
        } else{
            ub=x;
        }
        k++;
    }
    result(((lb+ub)/2), k, k<max_iter);
}
void secant(double lb, double ub, double precision, long long max_iter){
    long long k=0;
    double x0=lb;
    double x1=ub, x2;
    while(abs(func(x0))>precision&&k<max_iter){
        double m = (f(x1)-f(x0))/(x1-x0);
        //cout <<m<<' '<< x0 <<' '<<f(x0)<< "\n";
        x2=x1-f(x1)/m;
        if(func(x2)==0){
            result(x2,k);
            return;
        }
        k++;
        x0=x1;
        x1=x2;
    }
    result(x2, k, k<max_iter);

}
void newton(double lb, double ub, double precision, long long max_iter){
    long long k=0;
    double x=lb;
    while(abs(func(x))>precision&&k<max_iter){
        //cout << x <<' '<<f(x)<< "\n";
        x=x-f(x)/derivative(x);
        if(func(x)==0){
            result(x,k);
            return;
        }
        k++;
    }
    result(x, k, k<max_iter);
}
//#endregion

int main(){
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
        bisection(left,right,threshold, calc_limit);
        break;
    case 's':
        secant(left,right,threshold, calc_limit);
        break;
    case 'n':
        newton(left,right,threshold, calc_limit);
        break;
    default:
        cout << "Invalid selection. Have a good day!";
        break;
    }
    return 0;
}
