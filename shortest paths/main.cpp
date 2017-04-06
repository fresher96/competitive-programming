#include <bits/stdc++.h>
using namespace std;
void read_file(bool outToFile = true){
#ifdef LOCAL_TEST
    freopen("in.in", "rt", stdin);
    if(outToFile)
    freopen("out.out", "wt", stdout);
#endif
}
//
typedef pair <int, int> ii;
typedef vector <ii> vii;
typedef vector <vii> vvii;
#define PB push_back
#define MP make_pair
#define OO (int)1e9
#define nMax 1000+9
//
vvii G;
int n, m;
int SP[nMax];
int APSP[nMax][nMax];
//
void scan_graph(){
    cin>>n>>m;
    G.assign(n, vii());
    
    // required to apply floyd warshall
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            APSP[i][j] = (i == j)? 0 : OO;
    
    // required to apply SSSP or dijkstra or bellman
    for(int i=0; i<n; i++)
        SP[i] = OO;
    
    for(int i=0; i<m; i++)
    {
        int u, v, w;
        
        cin>>u>>v>>w;                   // just set w = 1 for unweighted graphs
        //u--, v--;                     // for 1-based
        
        G[u].PB( MP(v, w) );
        //G[v].PB( MP(u, w) );
        
        APSP[u][v] = APSP[v][u] = w;
    }
}
void SSSP(int u){ // unknown complexity
    queue <int> q;      q.push(u);
    SP[u] = 0;
    
    while(!q.empty())
    {
        u = q.front();  q.pop();
        int sz = G[u].size();
        for(int i=0; i<sz; i++)
        {
            int v = G[u][i].first;
            int w = G[u][i].second;
            if(SP[v] > SP[u] + w)
                SP[v] = SP[u] + w, q.push(v);
        }
    }
}
void dijkstra(int u){ // O( (E + V)*lgV )
    // this implementation doesn't work with negative cycles
    // however, it works with negative edges but slower
    
    // this function works in case of
    // multi-edges or self-loops
    
    priority_queue < ii, vii, greater<ii> > pq;
    pq.push( MP(0, u) );
    SP[u] = 0;
    
    while(!pq.empty())
    {
        ii pqtop = pq.top();
        u = pqtop.second;
        int d = pqtop.first;
        pq.pop();
        
        if(d > SP[u])   continue;
        
        int sz = G[u].size();
        for(int i=0; i<sz; i++)
        {
            int v = G[u][i].first;
            int w = G[u][i].second;
            if(SP[v] > SP[u] + w)
                SP[v] = SP[u] + w, pq.push( MP(SP[v], v) );
        }
    }
}
void floyd(){ // O(V^3)
    for(int k=0; k<n; k++)
        for(int i=0; i<n; i++)
            for(int j=0; j<n; j++)
                APSP[i][j] = min(APSP[i][j], APSP[i][k] + APSP[k][j]);
}
void bellman(int s){ // O( (V + E) * V )
    SP[s] = 0;
    bool stillRelaxing = true;
    for(int k=0; k<n-1 && stillRelaxing; k++)
    {
        stillRelaxing = false;
        for(int u=0; u<n; u++)
        {
            int sz = G[u].size();
            for(int i=0; i<sz; i++)
            {
                int v = G[u][i].first;
                int w = G[u][i].second;
                if(SP[v] > SP[u] + w)
                    SP[v] = SP[u] + w, stillRelaxing = true;
            }
        }
    }
}
bool has_negative_cycle(int s=0){ // O( (V + E) * V )
    bellman(s);
    for(int u=0; u<n; u++)
    {
        int sz = G[u].size();
        for(int i=0; i<sz; i++)
        {
            int v = G[u][i].first;
            int w = G[u][i].second;
            if(SP[v] > SP[u] + w)
                return true;
        }
    }
    return false;
}
void test(int what){
    if(what == 1)
    {
        floyd();
        for(int i=0; i<n; i++)
            for(int j=0; j<n; j++)
                printf("%d -> %d : %d\n", i, j, APSP[i][j]);
    }
    
    if(what == 2)
    {
        SSSP(0);
        for(int i=0; i<n; i++)
            printf("%d %d\n", i, SP[i]);
    }
    
    if(what == 3)
    {
        dijkstra(0);
        for(int i=0; i<n; i++)
            printf("%d %d\n", i, SP[i]);
    }
    
    if(what == 4)
    {
        if(has_negative_cycle())
            printf("negative cycle detected\n");
        else
            printf("no negative cycle detected\n");
        
        for(int i=0; i<n; i++)
            printf("%d %d\n", i, SP[i]);
    }
}
//
int main(){
    read_file();
    scan_graph();
    test(4);
}
