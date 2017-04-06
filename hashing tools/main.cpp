#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair <int, int> ii;
typedef vector <int> vi;
typedef vector <vi> vvi;
typedef vector <ii> vii;
typedef vector <vii> vvii;
#define endl '\n'
#define PB push_back
#define MP make_pair
#define OO (1000000000)         // ToDo
#define EPS (1e-9)              // ToDo
#define MOD (1000000007)        // ToDo
#define all(v) ((v).begin()),((v).end())
#define DEBUG(x) cout<< #x <<" = "<<"\""<< (x) <<"\""<<endl
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
void read_file(bool outToFile = true){
#ifdef LOCAL_TEST
    freopen("in.in", "rt", stdin);
    if(outToFile)
    freopen("out.out", "wt", stdout);
#endif
}
//
#define base 4                  // use a prime number for base
#define nHash 5
#define pMax (1000000)
bitset <pMax + 1> isPrime;
vi prime;
int hashMod[nHash];
//
void sieve(){
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
void gen_primes(){
    sieve();
    
    // lovely primes
    prime.PB(1000000007);
    prime.PB(1000000009);
    prime.PB(1000000021);
    prime.PB(1000000033);
    prime.PB(1000000087);
    prime.PB(1000000093);
    prime.PB(1000000097);
    
    int primeSize = prime.size();
    srand( time(0) );
    
    for(int k=0; k<nHash; k++)
    {
        int pos = rand()%(primeSize - 9592);
        // pos is in range [0, primeSize - 9592 - 1]
        // note that primeSize > 9592
        
        pos += 9592;
        // pos is in range [9592, primeSize - 1]
        // this is to choose primes of at least six digits
        
        hashMod[k] = prime[ pos ];
        // dare to hack? :)
    }
    
//    printf("chosed primes:\n");
//    for(int i=0; i<nHash; i++)
//        printf("%d%c", hashMod[i], " \n"[i == nHash-1]);
}
void filter(string &s){
    // be careful with leading zeros!
    // ex. in cases like "ba" and "b"
    // if you assign a = 0
    // then the two pervious strings will have the same hash
    // b * base^0 + a * base^1 == b * base^0
    
    int n = s.length();
    for(int i=0; i<n; i++)
        s[i] -= 'a' - 1;
}
vi get_hash(string s){
    vi h;
    h.resize(nHash);
    filter(s);
    int n = s.length();
    for(int k=0; k<nHash; k++)
    {
        int hsh = 0;
        int p = 1;
        for(int i=0; i<n; i++)
        {
            hsh += 1LL * s[i] * p %hashMod[k];
            if(hsh >= hashMod[k]) hsh -= hashMod[k];
            p = 1LL * p * base %hashMod[k];
        }
        h[k] = hsh;
    }
    return h;
}
//
int main()
{
    read_file();
    gen_primes();
    
}
