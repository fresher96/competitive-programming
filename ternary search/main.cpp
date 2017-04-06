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
int n;
#define nMax 1000+9
int A[nMax];
#define itrMax 1000
//
// keep in mind lo must be >= 0
int TS(int lo, int hi){ // O(lgn)
    // lo <= hi
    while(lo != hi)
    {
        int md = (lo+hi)/2;
        
        // in case of sth like [1 2 3 2 1]
        if(A[md] <= A[md+1])
            lo = md+1;
        else
            hi = md;
    }
    return lo;
}
//
ld f(ld x){
    return sin(x);
}
ld TS_on_doubles(ld lo, ld hi){
    // lo <= hi
    int itr = 0;
    while( abs(hi - lo) > EPS && itr < itrMax )
    {
        itr++;
        ld md1 = lo + (hi - lo)/3;
        ld md2 = hi - (hi - lo)/3;

        // in case of sth like [1 2 3 2 1]
        if(f(md1) <= f(md2) + EPS)
            lo = md1 + EPS;
        else
            hi = md2 - EPS;
    }
    
    return lo;
}
//
int main()
{
    read_file();
    
//    while(cin>>n)
//    {
//        for(int i=0; i<n; i++)
//            cin>>A[i];
//        
//        int ans = TS(0, n-1);
//        cout<< A[ans] <<endl;
//    }
    
    // expected PI/2 =~ 1.5707963267949
    cout<< TS_on_doubles(0, 2*acos(-1.0)) <<endl;
}
