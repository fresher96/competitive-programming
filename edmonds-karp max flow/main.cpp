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
struct MaxFlow{
    
    // notes:
    // 'int' is used for edge capacity
    // 'll' is used for the maximum flow value
    // 0-based indexing is used for vertexes
    
    
    struct Edge {
        int u, v;
        int w;
        int prv;

        Edge(int u, int v, int w, int prv): u(u), v(v), w(w), prv(prv) {
        }
    };
    
    #define vMax 1000                   // ToDo
    int src, snk;                       // be careful that src != snk
    int par[vMax];
    int flow;
    int idxer;
    int last[vMax];
    vector <Edge> E;
    
    void init(){
        memset(last, -1, sizeof last);
        E.clear();
        idxer = 0;
    }
    
    void add_edge(int u, int v, int dw, int rw){
        // 'dw' = direct weight, 'rw' = reverse weight
    
        Edge de = Edge(u, v, dw, last[u]);
        Edge re = Edge(v, u, rw, last[v]);

        last[u] = idxer++;
        last[v] = idxer++;

        E.PB(de);
        E.PB(re);

        // recall
        // if( (i&1) == 0 ) then E[i] is a direct edge
        // if( (i&1) == 1 ) then E[i] is a reversed edge
        // E[i^1] = the reverse of E[i]
    }
    
    bool BFS(int u, int t){ // O(V + E)
    
        queue <int> Q;
        Q.push(u);

        memset(par, -1, sizeof par);
        par[u] = -2;

        while(!Q.empty())
        {
            u = Q.front();
            Q.pop();

            if(u == t) return true;

            for(int i=last[u]; i!=-1; i=E[i].prv)
            {
                Edge e = E[i];

                int v = e.v;
                int w = e.w;

                if(par[v] != -1 || w == 0) continue;

                par[v] = i;
                Q.push(v);
            }
        }

        return false;
    }
    
    void augment(int v, int minEdge = INT_MAX){ // O(V)
        // augment the founded path with the possible flow
        if(v == src)
        {
            flow = minEdge;
            return;
        }

        int idx = par[v];
        augment(E[idx].u, min(minEdge, E[idx].w) );

        E[idx].w -= flow;
        E[idx ^ 1].w += flow;
    }
    
    ll max_flow(){ // O(V * E^2) time, O(V + E) memory
    
        ll mf = 0;

        // while there exists an augmenting path
        while(BFS(src, snk))
        {
            // O(V * E) iterations

            augment(snk);
            mf += flow;
        }

        return mf;
    }
};
//
int n, m;
int src, snk;
MaxFlow graph;
//
int main()
{
    read_file();
    
    int TC;
    cin>>TC;
    while(TC--)
    {
        cin>>n>>m;
        graph.init();
        for(int i=0; i<m; i++)
        {
            int u, v, w;
            cin>>u>>v>>w;

            // form an edge from u to v for direct flows
            // and from v to u for reversed flows
            // we can pass a flow with value w from u to v
            // we can pass a flow with value 0 from v to u
            
            graph.add_edge(u, v, w, 0);
        }
        
        cin>>src>>snk;
        graph.src = src, graph.snk = snk;
        cout<< graph.max_flow() <<endl;
    }
}
// description: given directed weighted graph with 'n' vertexes 0-based indexed,
// and 'm' edges. find the maximum flow from the given 'src' to the given 'snk'
