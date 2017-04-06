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
#define nMax (100+1)
#define mMax nMax
int FT[nMax];
int BIT[nMax];
int T[nMax];
int n, m;
//
int freqAt(int idx){ // O(lgn)
    int sum = FT[idx];
    if(idx > 0)
    {
        int z = idx - (idx & -idx);
        int y = idx - 1;
        while(y != z)
        {
            sum -= FT[y];
            y -= (y & -y);
        }
    }
    return sum;
}
void update(int idx, int val){ // O(lgn)
    val -= freqAt(idx);
    // be sure idx != 0
    while(idx <= n)
    {
        FT[idx] += val;
        idx += (idx & -idx);
    }
}
void insert(int *FT, int idx, int val){ // O(lgn)
    // don't forget to initialize FT with zeros
    // be sure idx != 0
    while(idx <= n)
    {
        FT[idx] += val;
        idx += (idx & -idx);
    }
}
int freqTo(int *FT, int idx){ // O(lgn)
    int sum = 0;
    while(idx > 0)
    {
        sum += FT[idx];
        idx -= (idx & -idx);
    }
    return sum;
}
int query(int x){ // O(lgn)
    return freqTo(BIT, x)*x - freqTo(T, x);
}
void build(){ // O(n)
    int x;
    memset(FT, 0, sizeof FT);
    for(int i=1; i<=n; i++)
    {
        scanf("%d", &x);
        insert(FT, i, x);
    }
}
//
int main(){
    read_file(false);
    int TC;     scanf("%d", &TC);
    while(TC--)
    {
        // this code is for range-update range-query
        // solving the range-sum-query
        scanf("%d %d", &n, &m);
        memset(BIT, 0, sizeof BIT);
        memset(T, 0, sizeof T);
        while(m--)
        {
            int x, y;
            int c;      scanf("%d", &c);
            if(c == 0)
            {
                // update range [x, y] with v
                int v;
                scanf("%d %d %d", &x, &y, &v);
                
                insert(BIT, x, v);
                insert(BIT, y+1, -v);
                
                insert(T, x, v*(x-1));
                insert(T, y+1, -v*y);
            }
            else
            {
                // range [x, y] query
                scanf("%d %d", &x, &y);
                printf("%d\n", query(y) - query(x-1) );
            }
        }
    }
}
