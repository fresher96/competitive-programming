#include <bits/stdc++.h>
using namespace std;
//
#define EPS (1e-9)
typedef long double ld;
//
ld f(ld x){
    return cos(x) - x;
}
ld solve_equation(ld a, ld b, ld eps){
    while(true)
    {
        ld c = (a+b)/2.0;
        if( fabs(c-a) <= eps + EPS )    return c;
        else if(f(c) > 0.0 + EPS)       a = c;
        else                            b = c;
        //printf("f(%lf) = %lf\n", c, f(c));
    }
}
//
int main(){
    printf("%.20Lf\n", solve_equation(0.0, 1.0, 0.0000000000000000001) );
    // expected ~ 0.73908513321516064165
    // printed  = 0.73908513318747282028
}
