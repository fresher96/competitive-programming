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
int n, m;
vvii G;
const int MAXN = 50+9;
const int MAXM = 1000+9;
vi euler;
bool used[MAXM];
//
void find_euler(int u){
    while(!G[u].empty())
    {
        int v = G[u].back().first;
        int edge = G[u].back().second;
        G[u].pop_back();
        
        if(used[edge]) continue;
        used[edge] = 1;
        
        find_euler(v);
    }
    euler.PB(u);
}
void find_euler_path(){ // O(n + m)
    
    // notes:
    // $ check for graph connectivity
    // $ this algorithm works in case of multi-edges, self loops
    // and works with directed graphs
    // $ G[u][i] is an edge in which the first element is the vertex and
    // the second element is an id for it

    /*
     * theory:
     * $ An undirected graph has an eulerian circuit if and only if it is
     * connected and each vertex has an even degree.
     * $ An undirected graph has an eulerian path if and only if it is connected
     * and all vertices except 2 have even degree. One of those 2 vertices that
     * have an odd degree must be the start vertex, and the other one must be
     * the end vertex.
     * $ A directed graph has an eulerian circuit if and only if it is connected
     * and each vertex has the same in-degree as out-degree.
     * $ A directed graph has an eulerian path if and only if it is connected
     * and each vertex except 2 have the same in-degree as out-degree, and one
     * of those 2 vertices has out-degree with one greater than in-degree(this
     * is the start vertex), and the other vertex has in-degree with one greater
     * than out-degree (this is the end vertex).
     */
    
    
    memset(used, 0, sizeof used);
    euler.clear();
    
    // make sure to start from the right vertex
    find_euler(0);
    
    reverse(all(euler));
}
//
int main()
{
    read_file();
    
}
// sample problem: The Necklace 10054 uva
