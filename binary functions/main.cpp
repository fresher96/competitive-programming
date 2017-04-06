#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair <int, int> ii;
typedef vector <ii> vii;
typedef vector <vii> vvii;
typedef vector <int> vi;
typedef vector <vi> vvi;
#define all(v) ((v).begin()),((v).end())
#define PB push_back
#define MP make_pair
#define OO (1000000000)
#define EPS (1e-9)
#define DEBUG(x) cout << #x << " = " <<"\""<< (x) <<"\""<<endl
void read_file(bool outToFile = true){
#ifdef LOCAL_TEST
    freopen("in.in", "rt", stdin);
    if(outToFile)
    freopen("out.out", "wt", stdout);
#endif
}
//
vi A;
int n, x;
//
// all of these functions run in O(lgn)
// keep in mind lo must be >= 0
// and lo must be <= hi
int search(int x){ // classical BS
    int lo = 0, hi = n-1;
    while(lo != hi)
    {
        int md = (lo+hi)/2;
        int res = A[md] - x;
        
        if(res == 0)
            return md;
        else if(res < 0)
            lo = md+1;
        else
            hi = md;
    }
    
    if(A[lo] == x)
        return lo;
    else
        return -1;
}
int lower(int x){ // lower_bound
    int lo = 0, hi = n-1;
    while(lo != hi)
    {
        int md = (lo+hi)/2;
        int res = A[md] - x;
        
        if(res >= 0)
            hi = md;
        else
            lo = md+1;
    }
    
    if(A[lo] >= x)
        return lo;
    else
        return n;
}
int upper(int x){ // upper_bound
    int lo = 0, hi = n-1;
    while(lo != hi)
    {
        int md = (lo+hi)/2;
        int res = A[md] - x;
        
        if(res <= 0)
            lo = md+1;
        else
            hi = md;
    }
    
    if(A[lo] > x)
        return lo;
    else
        return n;
}
//
bool can(int x){
    return 1;
}
// find the minimum value that satisfies can()
int BS_min(){
    // search space looks like 0000001111111
    int lo = 0, hi = n-1;
    while(lo != hi)
    {
        int md = (lo+hi)/2;
        
        if(can(md))
            hi = md;
        else
            lo = md+1;
    }
    
    int ret = can(lo)? lo : -1;
    return ret;
}
// find the maximum value that satisfies can()
int BS_max(){
    // search space looks like 111111100000000
    int lo = 0, hi = n-1 + 1;
    while(lo != hi - 1)
    {
        int md = (lo+hi)/2;
        
        if(can(md))
            lo = md;
        else
            hi = md;
    }
    
    int ret = can(lo)? lo : -1;
    return ret;
}
// another style for BS
int BS_max1(){
    // search space looks like 111111100000000
    int lo = 0, hi = n-1;
    int ret = -1;
    while(lo <= hi)
    {
        int md = (lo+hi)/2;
        
        if(can(md))
            ret = lo, lo = md+1;
        else
            hi = md-1;
    }
    
    return ret;
}
//
int main()
{
    read_file();
    
    while(cin>>x)
    {
        A.clear();      A.PB(x);
        while(cin>>x && x != -1)
            A.PB(x);

        n = A.size();
        while(cin>>x && x != -1)
        {
            printf("%d: ", x);
            printf("%d ", search(x));
            printf("%d ", lower(x));
            printf("%d", upper(x));
            printf("\n");
        }
        
    }
}
