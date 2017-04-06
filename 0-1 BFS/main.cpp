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
const int nMax = 100000+9;
int n;
int SP[nMax];
bool vis[nMax];
vvii G;
//
void BFS(int u){ // total of O(V + E)
    
    for(int i=0; i<n; i++)
        SP[i] = OO, vis[i] = 0;
    
    SP[u] = 0;
    deque <int> DQ;
    DQ.push_front(u);
    
    while(!DQ.empty())
    {
        u = DQ.front();
        DQ.pop_front();
        
        if(vis[u]) continue;
        vis[u] = 1;
        
        for(int i=0,sz=G[u].size(); i<sz; i++)
        {
            int v = G[u][i].first;
            int w = G[u][i].second;
            
            if(SP[v] <= SP[u] + w) continue;
            
            SP[v] = SP[u] + w;
            if(w == 0)
                DQ.push_front(v);
            else
                DQ.push_back(v);
        }
    }
}
//
int main()
{
    read_file();
    
}
// editorial link:
// http://codeforces.com/blog/entry/22276
