#include <stdio.h>

class Polynomial
{
  protected:
    double coefficients[11];
    int order;

  public:
    double func(double x){
        double res = 0;
        for (int i = 0; i <= order; i++){
            double exp = 1;
            for (int _ = 0; _ < i; _++){
                exp *= x;
            }
            res += exp * coefficients[i];
        }
        return res;
    }
    double f(double x){
        return func(x);
    }
    double derivative(double x){
        double res = 0;
        for (int i = 1; i <= order; i++){
            double exp = i;
            for (int _ = 1; _ < i; _++){
                exp *= x;
            }
            res += exp * coefficients[i];
        }
        return res;
    }
    Polynomial(){
        FILE *f = fopen("func.dat", "r");
        fscanf(f, "%d", &order);
        for (int i = 0; i <= order;i++){
            fscanf(f, "%lf", &coefficients[i]);
            printf("%lf%cx^%d = ", coefficients[i], 'a' - i + order, i);
        }
    }
};

class Linear: Polynomial{
    public:
    Linear(double m, double q){
        order = 1;
        coefficients[0] = q;
        coefficients[1] = m;
    }
};

class Quadratic: Polynomial{
    public:
    Quadratic(double a, double b, double c){
        order = 1;
        coefficients[0] = c;
        coefficients[1] = b;
        coefficients[2] = a;
    }
};

class Cubic: Polynomial{
    public:
    Cubic(double a, double b, double c, double d){
        order = 1;
        coefficients[0] = d;
        coefficients[1] = c;
        coefficients[2] = b;
        coefficients[3] = a;
    }
};
