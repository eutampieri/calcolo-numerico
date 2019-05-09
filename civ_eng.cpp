#include <cmath>
#include <cstdio>
using namespace std;

double my_erfc(double x){
    double res = 0, h=1e-1;
    for(double i = 10; i>=x; i-=h){
        res+=(exp(-(i*i))+exp(-((i-h)*(i-h))))*h/2.0;
    }
    return res;
}
int main(){
    double c = 1.75*(my_erfc(0.656)+exp(32.73)*my_erfc(5.758));
    double val = my_erfc(0.656);
    double true_error = erfc(0.656) - val;
    double arterr = abs(true_error/erfc(0.656))*100;
    printf("%lf %lf %lf %lf\n", c, val, true_error, arterr);
}