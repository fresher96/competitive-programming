#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector <int> vi;
typedef pair <int, int> ii;
typedef vector <vi> vvi;
typedef vector <ii> vii;
typedef vector <vii> vvii;
#define PB push_back
#define MP make_pair
#define OO (1000000000)
#define EPS (1e-9)
#define all(v) ((v).begin()),((v).end())
#define DEBUG(x) cout << #x << " = " <<"\""<< (x) <<"\""<<endl
void read_file(bool outToFile = true){
#ifdef LOCAL_TEST
    freopen("in.in", "rt", stdin);
    if(outToFile)
    freopen("out.out", "wt", stdout);
#endif
}
//
#define nMax 100000+9
#define mMax 317+9      // ceil( nMax/floor( sqrt(nMax) ) )
int n, m, sqt, q;
int A[nMax], MIN[mMax];
vvi bucket;
//
void build_buckets(){ // O(n)
    sqt = 0;
    while(sqt * sqt <= n) sqt++;
    sqt--;
    
    m = (n + sqt-1)/sqt;
    bucket.assign(m, vi(sqt));
    
    int idx = 0;
    for(int i=0; i<m; i++)
    {
        MIN[i] = OO;
        for(int j=0; j<sqt; j++)
            bucket[i][j] = (idx < n)? A[idx++] : OO, MIN[i] = min(MIN[i], bucket[i][j]);
    }
}
void update(int val, int idx){ // O(sqrt n)
    int iq = idx/sqt, ir = idx%sqt;
    A[idx] = val, bucket[iq][ir] = val;
    
    MIN[iq] = OO;
    for(int i=0; i<sqt; i++)
        MIN[iq] = min(MIN[iq], bucket[iq][i]);
}
int query(int x, int y){ // O(sqrt n)
    int xq = x/sqt, xr = x%sqt;
    int yq = y/sqt, yr = y%sqt;
    int ret = OO;

    if(xq == yq)
    {
        for(int i=xr; i<=yr; i++)
            ret = min(ret, bucket[xq][i]);
    }
    else
    {
        for(int i=xr; i<sqt; i++)
            ret = min(ret, bucket[xq][i]);

        for(int i=xq+1; i<=yq-1; i++)
            ret = min(ret, MIN[i]);
        
        for(int i=0; i<=yr; i++)
            ret = min(ret, bucket[yq][i]);
    }

    return ret;
}
//
int main()
{
    ios::sync_with_stdio(false);
    read_file();
    
    while(cin>>n)
    {
        for(int i=0; i<n; i++)
            cin>>A[i];
        
        build_buckets();
        
        cin>>q;
        int idx = 0;
        while(q--)
        {
            update(A[idx], idx);
            idx = (idx+1)%n;
            
            int l, r;   cin>>l>>r;
            cout<< query(l, r) <<endl;
        }
    }
}
