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
typedef vector <int> vi;
//
struct union_find{
    vi par, rnk;
    union_find(int n = 0){ // O(n)
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
        
        if(rnk[i] >= rnk[j])
            par[j] = i, rnk[i] += (rnk[i] == rnk[j]);
        else
            par[i] = j;
    }
} UF;
//
int main()
{
    read_file(false);
    UF = union_find(5);
    
}
