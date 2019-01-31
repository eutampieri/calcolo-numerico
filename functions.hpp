#include <cmath>
#include <stdio.h>

struct RootFindingResult
{
    double x;
    double y;
    long long iter;
    bool found;
};

class Function
{
  public:
    virtual double func(double x) = 0;
    RootFindingResult findRootBisection(double lb, double ub, double precision, long long max_iter)
    {
        long long k = 0;
        double x = (ub + lb) / 2;
        RootFindingResult final_result;
        while (abs(func(x)) > precision && k < max_iter)
        {
            x = (ub + lb) / 2;
            if (func(x) == 0)
            {
                final_result.found = true;
                final_result.iter = k;
                final_result.x = x;
                final_result.y = func(x);
                return final_result;
            }
            if (func(x) * func(ub) < 0)
            {
                lb = x;
            }
            else
            {
                ub = x;
            }
            k++;
        }
        final_result.found = k < max_iter;
        final_result.iter = k;
        final_result.x = ((lb + ub) / 2.0);
        final_result.y = func(final_result.x);
        return final_result;
    }
    RootFindingResult findRootSecant(double lb, double ub, double precision, long long max_iter)
    {
        long long k = 0;
        double x0 = lb;
        double x1 = ub, x2;
        RootFindingResult final_result;
        while (abs(func(x0)) > precision && k < max_iter)
        {
            double m = (func(x1) - func(x0)) / (x1 - x0);
            //cout <<m<<' '<< x0 <<' '<<f(x0)<< "\n";
            x2 = x1 - func(x1) / m;
            if (func(x2) == 0)
            {
                final_result.found = true;
                final_result.iter = k;
                final_result.x = x2;
                final_result.y = func(x2);
                return final_result;
            }
            k++;
            x0 = x1;
            x1 = x2;
        }
        final_result.found = k < max_iter;
        final_result.iter = k;
        final_result.x = x2;
        final_result.y = func(x2);
        return final_result;
    }
};

class DerivableFunction : public Function
{
  public:
    virtual double derivative(double x) = 0;
    RootFindingResult findRootNewton(double guess, double precision, long long max_iter)
    {
        long long k = 0;
        double x = guess;
        RootFindingResult final_result;
        while (abs(func(x)) > precision && k < max_iter)
        {
            //cout << x <<' '<<f(x)<< "\n";
            x = x - func(x) / derivative(x);
            if (func(x) == 0)
            {
                final_result.found = true;
                final_result.iter = k;
                final_result.x = x;
                final_result.y = func(x);
                return final_result;
            }
            k++;
        }
        final_result.found = k < max_iter;
        final_result.iter = k;
        final_result.x = x;
        final_result.y = func(x);
        return final_result;
    }
};

class CompositeFunction : public Function
{
  protected:
    Function *f;
    Function *g;

  public:
    CompositeFunction(Function *first, Function *second)
    {
        f = first;
        g = second;
    }
    double func(double x)
    {
        return f->func(g->func(x));
    }
};

class DerivableCompositeFunction : public DerivableFunction
{
  protected:
    DerivableFunction *f;
    DerivableFunction *g;

  public:
    DerivableCompositeFunction(DerivableFunction *first, DerivableFunction *second)
    {
        f = first;
        g = second;
    }
    double func(double x)
    {
        return f->func(g->func(x));
    }
    double derivative(double x)
    {
        return f->derivative(g->func(x)) * g->derivative(x);
    }
};

class Sine : public DerivableFunction
{
  public:
    double func(double x)
    {
        return sin(x);
    }
    double derivative(double x)
    {
        return cos(x);
    }
};

class Cosine : public DerivableFunction
{
  public:
    double func(double x)
    {
        return cos(x);
    }
    double derivative(double x)
    {
        return -sin(x);
    }
};

class Exponential : public DerivableFunction
{
  private:
    double base;

  public:
    double func(double x)
    {
        return pow(base, x);
    }
    double derivative(double x)
    {
        return func(x) * log(base);
    }
    Exponential()
    {
        base = exp(1);
    }
    Exponential(double b)
    {
        base = b;
    }
};

class Logarithmic : public DerivableFunction
{
  private:
    double base;

  public:
    double func(double x)
    {
        return log(x) / log(base);
    }
    double derivative(double x)
    {
        return 1.0 / (x * log(base));
    }
    Logarithmic()
    {
        base = exp(1);
    }
    Logarithmic(double b)
    {
        base = b;
    }
};
class Polynomial : public DerivableFunction
{
  protected:
    double coefficients[11];
    int order;

  public:
    double func(double x)
    {
        double res = 0;
        for (int i = 0; i <= order; i++)
        {
            double exp = 1;
            for (int _ = 0; _ < i; _++)
            {
                exp *= x;
            }
            res += exp * coefficients[i];
        }
        return res;
    }
    double derivative(double x)
    {
        double res = 0;
        for (int i = 1; i <= order; i++)
        {
            double exp = i;
            for (int _ = 1; _ < i; _++)
            {
                exp *= x;
            }
            res += exp * coefficients[i];
        }
        return res;
    }
    Polynomial(){}
    Polynomial(char *filename)
    {
        FILE *f = fopen(filename, "r");
        fscanf(f, "%d", &order);
        for (int i = 0; i <= order; i++)
        {
            fscanf(f, "%lf", &coefficients[i]);
        }
    }
};

class Linear : public Polynomial
{
  public:
    Linear(double m, double q)
    {
        order = 1;
        coefficients[0] = q;
        coefficients[1] = m;
    }
};

class Quadratic : public Polynomial
{
  public:
    Quadratic(double a, double b, double c)
    {
        order = 2;
        coefficients[0] = c;
        coefficients[1] = b;
        coefficients[2] = a;
    }
};

class Cubic : public Polynomial
{
  public:
    Cubic(double a, double b, double c, double d)
    {
        order = 3;
        coefficients[0] = d;
        coefficients[1] = c;
        coefficients[2] = b;
        coefficients[3] = a;
    }
};
