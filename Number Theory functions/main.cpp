#include <bits/stdc++.h>
using namespace std;
//
#define MOD 1000000007
#define pMax 10000000
#define PB push_back
#define MP make_pair
typedef vector <int> vi;
typedef long long ll;
typedef pair <ll, int> plli;
typedef vector <ll> vll;
typedef vector <plli> vplli;
//
bitset <pMax + 1> isPrime;
vi prime;
//
int gcd(int a, int b){ // O( lg min(a, b) )
    // undefined if (a == 0 && b == 0)
    if(!a)      return b;
    else        return gcd(b%a, a);
}
void bezout(int a, int b, int &x, int &y, int &g){ // O( lg min(a, b) )
    // be sure (a != 0 || b != 0)
    int q, tmp;
    int u1 = 0, u2 = 1, v1 = 1, v2 = 0;
    while(a != 0)
    {
        q = b/a;
        g = b%a;
        
        tmp = u2;
        u2 = u1 - u2 * q;
        u1 = tmp;
        
        tmp = v2;
        v2 = v1 - v2 * q;
        v1 = tmp;
        
        b = a;
        a = g;
    }
    g = b, x = u1, y = v1;
    // x = x0 + b/g * t
    // y = y0 - a/g * t
    // to have positive values for x and y
    // loop t from (-x0 * g/b) to (+y0 * g/a) inclusive
}
int multiplicative_inverse(int a, int n){ // O( lg min(a, b) )
    int ret, tmp, gcd;
    bezout(a, n, ret, tmp, gcd);
    
    if(gcd != 1)        return -1;
    else                return (ret%n + n)%n;
}
int chinese_remainder(vi r, vi n){ // O( k * lg min(a, b) )
    // n[i] have to be pairwise coprimes
    int k = n.size();
    
    int N = 1;
    for(int i=0; i<k; i++)
        N *= n[i];
    
    vi c(k);
    for(int i=0; i<k; i++)
        c[i] = multiplicative_inverse(N/n[i], n[i]);
    
    int ret = 0;
    for(int i=0; i<k; i++)
        ret = (1LL * ret + N/n[i] * r[i] * c[i])%N;
    
    return ret;
}
void sieve(){ // O(n ln ln n)
    isPrime.set();
    isPrime[0] = isPrime[1] = 0;
    
    prime.PB(2);
    for(int i=4; i<=pMax; i+=2)
        isPrime[i] = 0;
    
    for(int i=3; i<=pMax; i+=2)
    {
        if(isPrime[i])
        {
            prime.PB(i);
            if(1LL*i*i > pMax) continue;
            for(int j=i*i; j<=pMax; j+=i)
                isPrime[j] = 0;
        }
    }
}
// these functions only works for x <= (prime.back())^2
bool is_prime(ll n){ // ~O(logn)
    if(n < 0)
        return false;
    
    if(n <= pMax)
        return isPrime[n];
    
    int idx = 0;
    int pf = prime[idx];
    while(1LL*pf*pf <= n)
    {
        if(n%pf == 0) return false;
        if(pf == prime.back()) break;
        pf = prime[++idx];
    }
    return true;
}
vplli prime_factors(ll n){ // ~O(logn)
    vplli ret;
    int idx = 0;
    int pf = prime[idx];
    while(1LL*pf*pf <= n)
    {
        int power = 0;
        while(n%pf == 0)
            power++, n /= pf;
        
        if(power)
            ret.PB( MP(pf, power) );
        
        if(pf == prime.back()) break;
        pf = prime[++idx];
    }
    
    if(n != 1) // is the remaining n a prime ?
        ret.PB( MP(n, 1) );
    
    return ret;
    // this does not handle {0, 1}
    // be careful with negative n
}
ll totient(ll n){ // ~O(logn)
    // a^( totient(n) ) = 1 (mod n) where gcd(a, n) == 1
    // totient(n) = number of integers in range [1, n)
    // that are relatively prime to n
    ll ret = n;
    vplli pf = prime_factors(n);
    for(int i=0; i<pf.size(); i++)
        ret -= ret/pf[i].first;
    return ret;
}
//
int power_of_p_in_fact_n(int n, int p){ // O(logn in base p)
    // p must be prime
    int ret = 0;
    for(int i=p; i<=n; i*=p)
        ret += n/i;
    return ret;
}
ll sum_of_powers(int a, int n){
    // return a^1 + a^2 + ... + a^n in O(lgn)
    if(n == 0)   return 0;
    if(n%2 == 1) return a * (1 + sum_of_powers(a, n-1));
    
    ll b = sum_of_powers(a, n/2 - 1);
    ll c = a*(1 + b);
    c = c * (1 + c - b);
    return c;
}
//
int main()
{
    // don't forget to call sieve()
    
}
