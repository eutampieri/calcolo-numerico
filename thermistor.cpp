#include "functions.hpp"
#include <iostream>
void result(PointSearchResult res){
    std::cout << "A root has "<<(res.found?"":"not ")<<"been found in "<<res.iter<<" iterations: f("<<res.x<<")="<<res.y<<'\n';
}

int main(){
    Logarithmic log_fn = Logarithmic();
    Cubic poly = Cubic(8.775468e-8,0,2.341077e-4, 1.129241e-3-0.003423016362);
    DerivableCompositeFunction f = DerivableCompositeFunction(&poly, &log_fn);
    result(f.findRootNewton(1e2, 1e-7, 1e7));
    result(f.findRootBisection(-1e2,2e5, 1e-7, 1e7));
    result(f.findRootSecants(1,1e4, 1e-7, 1e7));
}
