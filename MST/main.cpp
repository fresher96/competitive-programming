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
typedef pair <int, ii> edge;
typedef vector <edge> edge_list;
typedef priority_queue < edge, edge_list, greater <edge> > prim_PQ;
//
struct union_find{
    vi par, rnk;
    int cnt;
    union_find(int n = 0){ // O(n)
        cnt = n;
        rnk.assign(n, 0);
        par.resize(n);
        for(int i=0; i<n; i++)
            par[i] = i;
    }
    
    // all these functions work in ~O(1)
    int find_par(int i){
        if( par[i] == i )
            return i;
        else
            return par[i] = find_par( par[i] );
    }
    bool in_the_same_set(int i, int j){
        return find_par(i) == find_par(j);
    }
    void set_union(int i, int j){
        i = find_par(i), j = find_par(j);
        if(i == j)      return;
        
        cnt--;
        if(rnk[i] >= rnk[j])
            par[j] = i, rnk[i] += (rnk[i] == rnk[j]);
        else
            par[i] = j;
    }
};
//
#define nMax (1000+9)
vvii G;
edge_list E;
int n, m;
bool vis[nMax];
//
void scan_graph(){
    G.assign(n, vii());
    E.assign(m, edge());
    for(int i=0; i<m; i++)
    {
        int u, v, w;
        cin>>u>>v>>w;
        
        G[u].PB( MP(v, w) );
        G[v].PB( MP(u, w) );
        
        // works in case of multi-edges and self-loops
        E[i] = edge(w, ii(u, v));
    }
}
int kruskal(){ // O(E * lgE)
    
    sort(all(E));
    int mst = 0;
    union_find UF(n);
    
    for(int i=0; i<m && UF.cnt>1; i++)
    {
        int u = E[i].second.first, v = E[i].second.second;
        int w = E[i].first;
        if(!UF.in_the_same_set(u, v))
        {
            // we add edge (u <-> v)
            UF.set_union(u, v);
            mst += w;
        }
    }
    
    if(UF.cnt > 1)
        mst = OO;
    
    return mst;
}
//
void process(int u, prim_PQ &PQ){
    vis[u] = 1;
    for(int i=0,sz=G[u].size(); i<sz; i++)
    {
        int v = G[u][i].first, w = G[u][i].second;
        if(vis[v]) continue;
        PQ.push( MP(w, MP(u, v)) );
    }
}
int prim(){ // O(E * lgE)
    
    // make sure G is not empty
    memset(vis, 0, sizeof vis);
    prim_PQ PQ;
    process(0, PQ);
    
    int mst = 0;
    int addedEdges = 0;
    
    while(!PQ.empty() && addedEdges != n-1)
    {
        edge top = PQ.top();
        PQ.pop();
        
        int v = top.second.second, w = top.first;
        if(vis[v]) continue;
        
        // add edge top i.e (u <-> v)
        mst += w;
        process(v, PQ);
        addedEdges++;
    }
    
    if(addedEdges != n-1) // the initial graph is disconnected
        mst = OO;
    
    return mst;
}
//
int main()
{
    read_file();
    
}
