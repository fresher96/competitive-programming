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
#define fi first
#define se second
#define OO (1000000000)         // ToDo
#define EPS (1e-9)              // ToDo
#define MOD (1000000007)        // ToDo
#define all(v) ((v).begin()),((v).end())
#define WT(x) cout<< #x <<" = "<<"\""<< (x) <<"\""<<endl
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
void read_file(bool outToFile = true){
#ifdef LOCAL_TEST
    freopen("in", "rt", stdin);
    if(outToFile)
    freopen("out", "wt", stdout);
#endif
}
//
typedef vector <ll> vll;
typedef vector <vll> vvll;
const int MAXN = 100000+9;
int TC, n, nq;
int A[MAXN] = {0};
/* needed variables */
int sqrtn;      // bucket size
int m;          // number of buckets
vvll bucket;
vll sum, toAdd;
/* needed functions */
void build_buckets(){ // initialization in O(n)
    
    sqrtn = 0;
    while(sqrtn * sqrtn <= n) sqrtn++;
    sqrtn--;
    
    m = (n + sqrtn - 1) / sqrtn;
    bucket.assign(m, vll(sqrtn));
    sum.resize(m);
    toAdd.resize(m);
    
    int idx = 0;
    for(int i=0; i<m; i++)
    {
        sum[i] = 0;
        toAdd[i] = 0;
        for(int j=0; j<sqrtn; j++)
        {
            bucket[i][j] = (idx < n)? A[idx++] : 0;
            sum[i] += bucket[i][j];
        }
    }
}
void update(int x, int y, int v){ // O(sqrt n)
    int xq = x/sqrtn, xr = x - xq * sqrtn;
    int yq = y/sqrtn, yr = y - yq * sqrtn;
    
    if(xq == yq)
    {
        for(int i=xr; i<=yr; i++)
        {
            bucket[xq][i] += v;
            sum[xq] += v;
        }
    }
    else
    {
        for(int i=xr; i<sqrtn; i++)
        {
            bucket[xq][i] += v;
            sum[xq] += v;
        }

        for(int i=xq+1; i<=yq-1; i++)
        {
            sum[i] += 1LL * sqrtn * v;
            toAdd[i] += v;
        }
        
        for(int i=0; i<=yr; i++)
        {
            bucket[yq][i] += v;
            sum[yq] += v;
        }
    }
}
void relax(int idx){ // O(sqrt n)
    for(int j=0; j<sqrtn; j++)
    {
        bucket[idx][j] += toAdd[idx];
    }
    toAdd[idx] = 0;
}
ll query(int x, int y){ // O(sqrt n)
    int xq = x/sqrtn, xr = x - xq * sqrtn;
    int yq = y/sqrtn, yr = y - yq * sqrtn;
    ll ret = 0;

    if(xq == yq)
    {
        relax(xq);
        for(int i=xr; i<=yr; i++)
            ret += bucket[xq][i];
    }
    else
    {
        relax(xq);
        for(int i=xr; i<sqrtn; i++)
            ret += bucket[xq][i];

        for(int i=xq+1; i<=yq-1; i++)
            ret += sum[i];
        
        relax(yq);
        for(int i=0; i<=yr; i++)
            ret += bucket[yq][i];
    }

    return ret;
}
//
int main()
{
    read_file();
    scanf("%d", &TC);
    while(TC--)
    {
        scanf("%d %d", &n, &nq);
        // in this problem A is always a zero array
        
        build_buckets();
        
        while(nq--)
        {
            int c;
            scanf("%d", &c);
            if(c == 0)
            {
                int x, y, v;
                scanf("%d %d %d", &x, &y, &v);
                x--, y--;
                update(x, y, v);
            }
            else
            {
                int x, y;
                scanf("%d %d", &x, &y);
                x--, y--;
                printf("%lld\n", query(x, y));
            }
        }
    }
}
// problem: http://www.spoj.com/problems/HORRIBLE/
// description: given array of length 'n', 'nq' queries of either add v to the
// interval [x, y], or calculate the sum of interval [x, y]
// notes for using the code:
// the indexing must be 0-based for the queries and updates
