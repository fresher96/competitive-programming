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
struct AVL{
    int v, n, frq, h;
    AVL *l, *r;
    AVL(int _v = 0){
        v = _v;
        frq = n = h = 1;
        l = r = NULL;
    }
    ~AVL(){
        if(!this) return;
        delete l;
        delete r;
    }
};
int get_n(AVL *cur){
    if(!cur)    return 0;
    else        return cur->n;
}
int get_h(AVL * cur){
    if(!cur)    return 0;
    else        return cur->h;
}
int BF(AVL *cur){
    if(!cur)    return 0;
    else        return get_h(cur->l) - get_h(cur->r);
}
void upd(AVL *cur){
    if(!cur)    return;
    cur->n = cur->frq + get_n(cur->l) + get_n(cur->r);
    cur->h = 1 + max( get_h(cur->l) , get_h(cur->r) );
}
//
AVL *right_rot(AVL *Q){
    AVL *P = Q->l;
    Q->l = P->r;
    P->r = Q;
    
    upd(Q);
    upd(P);
    return P;
}
AVL *left_rot(AVL *P){
    AVL *Q = P->r;
    P->r = Q->l;
    Q->l = P;
    
    upd(P);
    upd(Q);
    return Q;
}
AVL *balance(AVL *cur){
    if(BF(cur) == 2)    // left
    {
        if(BF(cur->l) == -1)    // left right
            cur->l = left_rot(cur->l);
        cur = right_rot(cur);
    }
    else if(BF(cur) == -2)      // right
    {
        if(BF(cur->r) == 1)     // right left
            cur->r = right_rot(cur->r);
        cur = left_rot(cur);
    }
    return cur;
}
AVL *insert(AVL *cur, int v){ // O(lgn)
    if(!cur)
        return new AVL(v);
    else if(v < cur->v)
        cur->l = insert(cur->l, v);
    else if(cur->v < v)
        cur->r = insert(cur->r, v);
    else
        cur->frq++;
    
    upd(cur);
    return balance(cur);
}
//
AVL *find_min(AVL *cur){
    if(!cur)    return NULL;
    while(cur->l)
        cur = cur->l;
    return cur;
}
AVL *remove(AVL *cur, int v){ // O(lgn)
    if(!cur)    return NULL;
    if(v < cur->v)
        cur->l = remove(cur->l, v);
    else if(cur->v < v)
        cur->r = remove(cur->r, v);
    else if(cur->frq > 1)
        cur->frq--;
    else if( !cur->l || !cur->r )
        cur = (cur->l)? cur->l : cur->r;
    else
    {
        AVL *suc = find_min(cur->r);
        int _v = suc->v, _frq = suc->frq;
        suc->frq = 1, cur->r = remove(cur->r, suc->v);
        cur->v = _v, cur->frq = _frq;
    }
    
    upd(cur);
    return balance(cur);
}
//
AVL *search(AVL *cur, int v){ // O(lgn)
    if(!cur)    return NULL;
    if(v < cur->v)
        return search(cur->l, v);
    else if(cur->v < v)
        return search(cur->r, v);
    else
        return cur;
}
AVL *getKth(AVL *cur, int k){ // O(lgn)
    if(!cur)    return NULL;
    if(k <= get_n(cur->l))
        return getKth(cur->l, k);
    else if( k <= get_n(cur->l) + cur->frq )
        return cur;
    else
        return getKth(cur->r, k - get_n(cur->l) - cur->frq );
}
int count(AVL *cur, int v){
    if(!cur)    return 0;
    if(v == cur->v)     return get_n(cur->l);
    if(v < cur->v)      return count(cur->l, v);
    else                return get_n(cur->l) + cur->frq + count(cur->r, v);
}
void debug(AVL *cur){
    if(!cur)    return;
    debug(cur->l);
    printf("debugging %d, frq = %d, n = %d\n", cur->v, cur->frq, cur->n);
    debug(cur->r);
}
//
int main()
{
    read_file();
    AVL *root = NULL;
    root = insert(root, 5);
    root = remove(root, 5);
    
    delete root;
}
