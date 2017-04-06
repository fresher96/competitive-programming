#include <bits/stdc++.h>
#include <windows.h>
using namespace std;
typedef long long ll;
typedef pair <int, int> ii;
typedef vector <int> vi;
typedef vector <vi> vvi;
typedef vector <ii> vii;
typedef vector <vii> vvii;
#define endl '\n'
#define PB push_back
#define MP make_pair
#define OO (1000000000)
#define EPS (1e-9)
#define MOD (1000000007)
#define all(v) ((v).begin()),((v).end())
#define DEBUG(x) cout<< #x <<" = "<<"\""<< (x) <<"\""<<endl
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
void read_file(bool outToFile = true){
#ifdef LOCAL_TEST
    #define LL "%lld"
    freopen("in.in", "rt", stdin);
    if(outToFile)
    freopen("out.out", "wt", stdout);
#else
    #define LL "%I64d"
#endif
}
//
#define nMax (100000+9)
#define lgnMax (17+9)

int P[nMax][lgnMax];
// P[i][j] = 2^j -th ancestor of node i

int dp[nMax][lgnMax];
// dp[i][j] = max weight on the path from i to its 2^j -th ancestor

int L[nMax];
int n; // the number of vertexes
vvii G;
//
void init(){ // O(n lgn)
    memset(P, -1, sizeof P);
    for(int i=0; i<nMax; i++)
        for(int j=0; j<lgnMax; j++)
            dp[i][j] = -OO;
}
void DFS(int u = 0, int p = -1){ // O(n)
    // we deal with a tree rooted at 0
    P[u][0] = p;
    L[u] = p == -1? 0 : L[p] + 1;
    for(int i=0, sz = G[u].size(); i<sz; i++)
    {
        int v = G[u][i].first;
        int w = G[u][i].second;
        if(v == p)
        {
            dp[u][0] = w;
            continue;
        }
        DFS(v, u);
    }
}
void build_P(){ // preprocessing in O(n lgn)
    
    for(int j=1; (1<<j)<n; j++)
    {
        for(int i=0; i<n; i++)
        {
            if(P[i][j-1] != -1)
            {
                P[i][j] = P[P[i][j-1]][j-1];
                dp[i][j] = max(dp[i][j-1], dp[P[i][j-1]][j-1]);
            }
        }
    }
    
    // with the help of P[u], it's possible to reach any ancestor of u
    // at any distance. using binary lifting method.
    // see kth_par function
}
int kth_par(int u, int K){
    int l = L[u] - K;
    // l is the level of the kth parent
    assert(l >= 0);
    
    int lg = 0;
    while((1<<lg) <= L[u]) lg++;
    lg--;
    
    for(int j=lg; j>=0; j--)
        if(P[u][j] != -1 && L[P[u][j]] >= l)
            u = P[u][j];
    
    return u;
}
int LCA(int u, int v){ // O(lg n) per query
    if(L[u] < L[v]) swap(u, v);
    
    int lg = 0;
    while((1<<lg) <= L[u]) lg++;
    lg--;
    
    // binary lifting u until L[u] == L[v]
    for(int j=lg; j>=0; j--)
        if(P[u][j] != -1 && L[P[u][j]] >= L[v])
            u = P[u][j];
    
    if(u == v) return u;
    
    for(int j=lg; j>=0; j--)
        if(P[u][j] != -1 && P[u][j] != P[v][j])
            u = P[u][j], v = P[v][j];
    
    return P[u][0];
}
int max_weight(int u, int v){ // O(lgn)
    if(L[u] < L[v]) swap(u, v);
    
    int lg = 0;
    while((1<<lg) <= L[u]) lg++;
    lg--;
    
    int ret = -OO;
    for(int j=lg; j>=0; j--)
        if(P[u][j] != -1 && L[P[u][j]] >= L[v])
            ret = max(ret, dp[u][j]), u = P[u][j];
    
    if(u == v) return ret;
    
    for(int j=lg; j>=0; j--)
        if(P[u][j] != -1 && P[u][j] != P[v][j])
            ret = max(ret, max(dp[u][j], dp[v][j])), u = P[u][j], v = P[v][j];
    
    ret = max(ret, max(dp[u][0], dp[v][0]));
    return ret;
}
//
int main()
{
    read_file();
    while(cin>>n)
    {
        G.assign(n, vii());
        for(int i=0, u, v, w; i<n-1; i++)
            cin>>u>>v>>w, G[u].PB(MP(v, w)), G[v].PB(MP(u, w));
        
        init();
        DFS();
        build_P();
        
        int u, v;
        while(cin>>u>>v)
        {
            cout<< LCA(u, v) <<endl;
            cout<< max_weight(u, v) <<endl;
            cout<<endl;
            
//            cout<< kth_par(u, v) <<endl;
//            cout<<endl;
        }
    }
}
