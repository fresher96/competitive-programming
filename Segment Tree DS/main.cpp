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
// |x| stand for ceil(x) & n is the number of array nodes
// set 2^( |lgn| + 1 ) ans the size of ST
#define OO INT_MAX
#define nMax (2000000)
#define IDX (4194304 + 9)
int S = 1, E = nMax;
int interval[IDX] = {0};
struct node{
    int v;
    int toAdd;
    node(int _v = 0)
    {
        v = _v;
        toAdd = 0;
    }
};
node ST[IDX];

// in the big-O notation n is the number of nodes in the ST
// i.e n = IDX from above

// to initialize the leaves with 0, use memset
// initializing the leaves with 1
int build(int s = S, int e = E, int p = 1){ // O(n)
    if(s == e)  return interval[p] = 1;
    int m = (s+e)/2;
    return interval[p] = build(s, m, 2*p) + build(m+1, e, 2*p+1);
}
//
// inserting v and returning its order (kth order)
int insert(int v, int s = S, int e = E, int p = 1){ // O(lgn)
    interval[p]++;
    if(s == e)  return interval[p];
    
    int m = (s+e)/2;
    if(v <= m)
        return insert(v, s, m, 2*p);
    else
        return interval[2*p] + insert(v, m+1, e, 2*p+1);
}
//
// removing v and returning its order (kth order)
int remove(int v, int s = S, int e = E, int p = 1){ // O(lgn)
    interval[p]--;
    if(s == e)  return interval[p]+1;
    
    int m = (s+e)/2;
    if(v <= m)
        return remove(v, s, m, 2*p);
    else
        return interval[2*p] + remove(v, m+1, e, 2*p+1);
}
//
// deleting the kth element and returning it's value
int delKth(int k, int s = S, int e = E, int p = 1){ // O(lgn)
    if(interval[p] < k)   return -1;
    
    interval[p]--;
    if(s == e)  return s;
    
    int m = (s+e)/2;
    if(k <= interval[2*p])
        return delKth(k, s, m, 2*p);
    else
        return delKth(k - interval[2*p], m+1, e, 2*p+1);
}
//
// get the value of the kth element
int getKth(int k, int s = S, int e = E, int p = 1){ // O(lgn)
    if(interval[p] < k)   return -1;
    
    if(s == e)  return s;
    
    int m = (s+e)/2;
    if(k <= interval[2*p])
        return getKth(k, s, m, 2*p);
    else
        return getKth(k - interval[2*p], m+1, e, 2*p+1);
}
//
void inorder_display(int s = S, int e = E, int p = 1){
    if(s == e)
    {
        int cnt = interval[p];
        while(cnt--)    cout<< s <<' ';
        cout<<endl;
    }
    else if(s < e) // just to be sure
    {
        int m = (s+e)/2;
        inorder_display(s, m, 2*p);
        inorder_display(m+1, e, 2*p+1);
    }
}
//
node merge(node l, node r){
    if(l.v <= r.v)      return l;
    else                return r;
}
void insert(int i, int v, int s = S, int e = E, int p = 1){ // O(lgn)
    if(s == e)
    {
        ST[p].v = v;
        return;
    }
    
    int m = (s+e)/2;
    if(i <= m)
        insert(i, v, s, m, 2*p);
    else
        insert(i, v, m+1, e, 2*p+1);
    
    ST[p] = merge(ST[2*p], ST[2*p+1]);
}
int fr, to;
node query(int s = S, int e = E, int p = 1){ // O(lgn)
    if(fr > e || to < s)        return node(OO);      // because min(x, OO) = x
    if(fr <= s && e <= to)      return ST[p];
    
    int m = (s+e)/2;
    if(to <= m)
        return query(s, m, 2*p);
    if(m < fr)
        return query(m+1, e, 2*p+1);
    
    node q1 = query(s, m, 2*p);
    node q2 = query(m+1, e, 2*p+1);
    return merge(q1, q2);
}
//
void update_node(int v, int s, int e, int p){
    // toAdd contains the hidden information from the children
    // toAdd = 0 means no hidden information
    ST[p].toAdd += v;
    ST[p].v += (e-s+1) * v;
}
void update_child(int s, int e, int p){
    // be sure that s != e i.e. not leaf node and children exist
    int m = (s+e)/2;
    update_node(ST[p].toAdd, s, m, 2*p);
    update_node(ST[p].toAdd, m+1, e, 2*p+1);
    ST[p].toAdd = 0;
    // toAdd here can be as a boolean
    // if toAdd == 0 then nothing will be updated
    // meaning that children are already updated
    // else then we have to update them and
    // make toAdd = 0 because we updated them
}
void lazy_update(int v, int s = S, int e = E, int p = 1){ // O(lgn)
    if(e < fr || s > to)  return;
    if(fr <= s && e <= to)
    {
        update_node(v, s, e, p);
        return;
    }
    
    update_child(s, e, p);
    
    int m = (s+e)/2;
    lazy_update(v, s, m, 2*p);
    lazy_update(v, m+1, e, 2*p+1);
    
    // merging
    ST[p].v = ST[2*p].v + ST[2*p+1].v;
}
node lazy_query(int s = S, int e = E, int p = 1){ // O(lgn)
    if(e < fr || s > to)        return node(0);       // neutral node
    if(fr <= s && e <= to)      return ST[p];
    
    update_child(s, e, p);
    
    int m = (s+e)/2;
    node q1 = lazy_query(s, m, 2*p);
    node q2 = lazy_query(m+1, e, 2*p+1);
    
    // merging
    node q;     q.v = q1.v + q2.v;
    return q;
}
//
int main(){
    read_file(false);
    
}
