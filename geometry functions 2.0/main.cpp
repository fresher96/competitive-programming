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
#define OO (1e100)              // ToDo
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
#define PI acos(-1.0)
#define origin point(0, 0)
#define undefined point(OO, OO)
#define pp pair <point, point>
#define poly vector <point>
#define vp vector <point>
//
struct point;
struct vec;
struct line;
struct circle;
struct triangle;
//
ld to_rad(ld theta);
ld to_deg(ld theta);
ld dist(point p, point q);
point middle(point p, point q);
point translate(point p, vec u);
ld norm_sq(vec u);
ld dot(vec u, vec v);
ld cross(vec u, vec v);
bool are_parallel(line l, line d);
bool are_same(line l, line d);
ld dist_to_line(point p, point a, point b);
bool ccw(point p, point q, point r);
bool collinear(point p, point q, point r);
//
ld angle(point a, point o, point b);
point rotate(point p, ld theta, point q);
point intersection(line l, line d);
bool check_range(ld v, ld l1, ld r1, ld l2, ld r2);
point segment_intersection(point p, point q, point r, point t);
bool point_on_ray(point p, point a, point b);
bool point_on_segment(point p, point a, point b);
point projection(point p, point a, point b);
ld dist_to_segment(point p, point a, point b);
point reflection(point p, point a, point b);
line perpendicular(point p, point a, point b);
line bisector(point a, point o, point b);
circle find_circle(point p, point q, ld r);
circle in_circle(triangle t);
circle circum_circle(triangle t);
//
ld perimeter(poly P);
ld area(poly P);
bool is_convex(poly P);
bool is_in(point p, poly P);
poly cut(poly P, point a, point b);
bool ch_cmp(point a, point b);
poly convex_hull(poly P);
void print(poly P);
poly polygon_intersection(poly P, poly Q);
void filter(poly &P);
// structures
struct point{
    ld x, y;
    point(ld nx = 0, ld ny = 0){
        x = nx, y = ny;
    }
    bool operator== (point p){
        return fabs(x - p.x) <= EPS && fabs(y - p.y) <= EPS;
    }
    bool operator!= (point p){
        return fabs(x - p.x) > EPS || fabs(y - p.y) > EPS;
    }
    bool operator< (point p) const{
        if(fabs(x - p.x) > EPS)
            return x < p.x - EPS;
        return y < p.y - EPS;
    }
    friend istream &operator>> (istream &is, point &p){
        return is>>p.x>>p.y;
    }
    friend ostream &operator<< (ostream &os, point p){
        return os<<p.x<<' '<<p.y;
    }
};
struct vec{
    ld x, y;
    vec(ld nx = 0, ld ny = 0){
        x = nx, y = ny;
    }
    vec(point p, point q){
        x = q.x - p.x, y = q.y - p.y;
    }
    vec operator+ (vec u){
        return vec(x + u.x, y + u.y); 
    }
    vec operator- (vec u){
        return vec(x - u.x, y - u.y); 
    }
    vec operator* (ld k){
        return vec(k*x, k*y);
    }
    friend istream &operator>> (istream &is, vec &u){
        return is>>u.x>>u.y;
    }
    friend ostream &operator<< (ostream &os, vec u){
        return os<<u.x<<' '<<u.y;
    }
};
struct line{
    ld a, b, c;
    line(ld na = 0, ld nb = 0, ld nc = 0){
        a = na, b = nb, c = nc;
    }
    line(point p, point q){
        // corner case: p == q
        
        ld dx = q.x - p.x;
        ld dy = q.y - p.y;
        
        if(fabs(dx) <= EPS)
        {
            a = 1, b = 0, c = -p.x;
            return;
        }

        a = -dy/dx;
        b = 1.0;
        c = dy/dx * p.x - p.y;
    }
    line(point p, ld m){
        a = -m;
        b = 1.0;
        c = -(a * p.x + p.y);
    }
    pp to_points(){
        point p, q;
        if(fabs(b) <= EPS)
            p.x = -c/a, q.x = p.x, p.y = 0, q.y = 1;
        else
            p.x = 0, q.x = 1, p.y = - (a * p.x + c), q.y = -(a * q.x + c);
        return MP(p, q);
    }
};
struct circle{
    ld x, y, r;
    circle(point c = origin, ld nr = 0){
        x = c.x, y = c.y, r = nr;
    }
    int is_in(point p){
        ld dx = p.x - x, dy = p.y - y;
        ld d = dx*dx + dy*dy, R = r*r;
        return (d < R - EPS)? 0 : (fabs(d - R) <= EPS)? 1 : 2;
    }
    ld perimeter(ld theta = 360){
        theta = to_rad(theta);
        return theta * r;
    }
    ld area(ld theta = 360){
        theta = to_rad(theta);
        return theta * r*r /2;
    }
};
struct triangle{
    point A, B, C;
    ld a, b, c;
    triangle(ld na = 0, ld nb = 0, ld nc = 0){
        a = na, b = nb, c = nc;
    }
    triangle(point nA, point nB, point nC){
        A = nA, B = nB, C = nC;
        c = dist(A, B), a = dist(B, C),b = dist(C, A);
    }
    bool is_triangle(){
        return a+b>c+EPS && b+c>a+EPS && c+a>b+EPS;
    }
    ld perimeter(){
    return a + b + c;
}
    ld area(){
        ld s = perimeter()/2;
        return sqrt(s * (s-a) * (s-b) * (s-c));
    }
};
// one line functions
ld to_rad(ld theta){
    return theta * PI / 180;
}
ld to_deg(ld theta){
    return theta * 180 / PI;
}
ld dist(point p, point q){
    return hypot(p.x - q.x, p.y - q.y);
}
point middle(point p, point q){
    return point((p.x + q.x)/2, (p.y + q.y)/2);
}
point translate(point p, vec u){
    return point(p.x + u.x, p.y + u.y);
}
ld norm_sq(vec u){
    return u.x * u.x + u.y * u.y;
}
ld dot(vec u, vec v){
    return u.x * v.x + u.y * v.y;
}
ld cross(vec u, vec v){
    return u.x * v.y - u.y * v.x;
}
bool are_parallel(line l, line d){
    return fabs(l.a - d.a) <= EPS && fabs(l.b - d.b) <= EPS;
}
bool are_same(line l, line d){
    return are_parallel(l, d) && fabs(l.c - d.c) <= EPS;
}
ld dist_to_line(point p, point a, point b){
    return dist(p, projection(p, a, b));
}
bool ccw(point p, point q, point r){
    return cross(vec(p, q), vec(p, r)) > 0 + EPS;
}
bool collinear(point p, point q, point r){
    return fabs( cross( vec(p, q), vec(p, r)) ) <= EPS;
}
// functions
ld angle(point a, point o, point b){
    // returnes angle in range [0, PI]
    vec oa = vec(o, a), ob = vec(o, b);
    return acos( dot(oa, ob) / sqrt( norm_sq(oa) * norm_sq(ob) ) );
}
point rotate(point p, ld theta, point q = origin){
    vec oq = vec(origin, q);
    p = translate(p, oq * -1);
    
    theta = to_rad(theta);
    ld x = p.x * cos(theta) - p.y * sin(theta);
    ld y = p.x * sin(theta) + p.y * cos(theta);
    
    p = point(x, y);
    p = translate(p, oq);
    return p;
}
point intersection(line l, line d){
    if(are_parallel(l, d)) return undefined;
    
    point p;
    p.x = (d.b * l.c - l.b * d.c) / (d.a * l.b - l.a * d.b);
    
    if(fabs(l.b) > EPS)
        p.y = -(l.a * p.x + l.c);
    else
        p.y = -(d.a * p.x + d.c);
    
    return p;
}
bool check_range(ld v, ld l, ld r){
    if(l > r + EPS) swap(l, r);
    if(fabs(r - l) <= EPS) return fabs(v - l) <= EPS;
    return l < v - EPS && v < r - EPS;
    return l <= v + EPS && v <= r + EPS;
}
point segment_intersection(point p, point q, point r, point t){
    point c = intersection( line(p, q) , line(r, t) );
    if(point_on_segment(c, p, q) && point_on_segment(c, r, t)) return c;
    return undefined;
}
bool point_on_ray(point p, point a, point b){
    // corner case: a == b
    
    if(p == a) return true;
    if(a == b) return false;
    
    vec ap = vec(a, p), ab = vec(a, b);
    return collinear(p, a, b) && dot(ap, ab) >= -EPS;
}
bool point_on_segment(point p, point a, point b){
    // corner case: the segment degenerate into a point
    
    if(p == a || p == b) return true;
    if(a == b) return false;
    
    return point_on_ray(p, a, b) && point_on_ray(p, b, a);
}
point projection(point p, point a, point b){
    vec ap = vec(a, p), ab = vec(a, b);
    ld u = dot(ap, ab) / norm_sq(ab);
    return translate(a, ab * u);
}
ld dist_to_segment(point p, point a, point b){
    vec ap = vec(a, p), ab = vec(a, b);
    ld u = dot(ap, ab) / norm_sq(ab);
    
    if(u < 0 - EPS)
        return dist(p, a);
    if(u > 1 + EPS)
        return dist(p, b);
    
    return dist_to_line(p, a, b);
}
point reflection(point p, point a, point b){
    point c = projection(p, a, b);
    vec pc = vec(p, c);
    return translate(p, pc * 2);
}
line perpendicular(point p, point a, point b){
    if(!collinear(p, a, b))
        return line(p, projection(p, a, b));
    
    line l = line(a, b);
    if(fabs(l.b) <= EPS)
        return line(p, point(p.x+1, p.y));
    
    if(fabs(l.a) <= EPS)
        return line(p, point(p.x, p.y+1));
    
    return line(p, 1/l.a);
}
line bisector(point a, point o, point b){
    ld ratio = dist(o, a)/dist(o, b);
    ratio /= ratio+1;
    vec ab = vec(a, b);
    point c = translate(a, ab * ratio);
    return line(o, c);
}
circle find_circle(point p, point q, ld r){
    point m = middle(p, q);
    vec mp = vec(m, p);
    
    ld mc = r*r - norm_sq(mp);
    if(mc < 0 - EPS) return circle();
    mc = sqrt(mc);
    
    ld u = mc/dist(m, p);
    point c = translate(m, mp * u);
    c = rotate(c, 90, m);
    
    return circle(c, r);
}
circle in_circle(triangle t){
    ld r = 2 * t.area()/t.perimeter();
    if(fabs(r) <= EPS)  return circle();
    line l = bisector(t.B, t.A, t.C);
    line d = bisector(t.C, t.B, t.A);
    point c = intersection(l, d);
    return circle(c, r);
}
circle circum_circle(triangle t){
    ld r = (t.a * t.b * t.c)/(4 * t.area());
    if(fabs(r) <= EPS)  return circle();
    line l = perpendicular(middle(t.A, t.B), t.A, t.B);
    line d = perpendicular(middle(t.A, t.C), t.A, t.C);
    point c = intersection(l, d);
    return circle(c, r);
}
// polygons related functions
// don't forget that P[0] == P[n-1]
// becareful with degenerated polygons
//
// P has to be stored in counter-clockwise for some functions
// P shouldn't have collinear points for some functions
// P has to be convex for some functions
point pivot;
ld area(poly P){ // O(n)
    
    // the polygon must be:
    // cw or ccw
    // with/without collinear points
    // convex/concave/degenrated
    
    int n = P.size();
    ld ret = 0;
    ld x1, x2, y1, y2;
    for(int i=0; i<n-1; i++)
    {
        x1 = P[i].x, x2 = P[i+1].x;
        y1 = P[i].y, y2 = P[i+1].y;
        ret += x1 * y2 - x2 * y1;
    }
    ret /= 2;
    ret = fabs(ret);
    return ret;
}
ld perimeter(poly P){ // O(n)
    
    // the polygon must be:
    // cw or ccw
    // with/without collinear points
    // convex/concave
    
    int n = P.size();
    ld ret = 0;
    for(int i=0; i<n-1; i++)
        ret += dist(P[i], P[i+1]);
    return ret;
}
bool is_convex(poly P){ // O(n)

    // the polygon must be:
    // cw or ccw
    // without collinear points
    // convex/concave/degenrated
    
    int n = P.size();
    if(n <= 3)  return false;
    bool turn = ccw(P[0], P[1], P[2]);
    for(int i=1; i<n-1; i++)
        if(ccw(P[i], P[i+1], P[i+2 != n ? i+2 : 1]) != turn)
            return false;
    return true;
}
bool is_in(point p, poly P){ // O(n)
    
    // the polygon must be:
    // cw or ccw
    // with/without collinear points
    // convex/concave/degenrated
    
    int n = P.size();
    ld sum = 0;
    
    for(int i=0; i<n-1; i++)
        if(ccw(P[i], p, P[i+1]))
            sum += angle(P[i], p, P[i+1]);
        else
            sum -= angle(P[i], p, P[i+1]);
    
    sum = fabs(sum);
    return fabs(sum - 2*PI) <= EPS;
}
poly cut(poly P, point a, point b){ // O(n)
    
    // UNCHECKED: P shouldn't have collinear points
    // UNCHECKED: P has to be stored in counterclockwise
    
    
    // this function is for convex polygon only
    // it returns the left part of the polygon
    // after cutting it with the vector ab
    
    
    int n = P.size();
    poly ret;
    
    for(int i=0; i<n; i++)
    {
        ld left1 = cross(vec(a, b), vec(a, P[i]));
        ld left2 = (i != n-1)? cross(vec(a, b), vec(a, P[i+1])) : 0;
        
        if(left1 >= -EPS)
            ret.PB(P[i]);
        if(left1 * left2 < -EPS)
            ret.PB( intersection(line(a, b), line(P[i], P[i+1])) );
    }
    
    if(!ret.empty() && ret.front() != ret.back())
        ret.PB(ret.front());
    return ret;
}
bool ch_cmp(point a, point b){
    if(collinear(pivot, a, b))
        return dist(pivot, a) < dist(pivot, b) - EPS;
    
    ld dx1 = a.x - pivot.x, dy1 = a.y - pivot.y;
    ld dx2 = b.x - pivot.x, dy2 = b.y - pivot.y;
    
    return atan2(dy1, dx1) < atan2(dy2, dx2) - EPS;
    
    // atan2 : ]-OO, +OO[ -> ]-PI, +PI]
    // undefined when called with (0, 0)
}
poly convex_hull(vp P){ // O(n lgn)
    
    int n = P.size();
    if(n <= 3)
    {
        if(n != 0 && P[0] != P[n-1])
            P.PB(P[0]);
        return P;
    }
    
    int idx = 0;
    for(int i=1; i<n; i++)
        if( P[idx].y > P[i].y + EPS
            || fabs(P[idx].y - P[i].y) <= EPS && P[idx].x < P[i].x - EPS )
            idx = i;
    swap(P[0], P[idx]);
    
    pivot = P[0];
    sort(P.begin()+1, P.end(), ch_cmp);
    
    poly ch;
    ch.PB(P[n-1]), ch.PB(P[0]), ch.PB(P[1]);
    int i = 2;
    
    while(i < n)
    {
        int j = ch.size()-1;
        if(ccw(ch[j-1], ch[j], P[i]) || collinear(ch[j-1], ch[j], P[i]))
            ch.PB(P[i]), i++;
        else
        {
            assert(!ch.empty());
            ch.pop_back();
        }
    }
    
    filter(ch);
    return ch;
}
void print(poly P){
    int n = P.size();
    DEBUG(n);
    for(int i=0; i<n ;i++)
        cout<< P[i] <<endl;
    cout<<"...\n";
}
poly polygon_intersection(poly P, poly Q){ // O(n*m)

    // the polygons must be:
    // cw or ccw
    // with/without collinear points
    // convex/degenrated
    
    // P, Q must be convex
    // 'ret' will be convex as the intersection of two convex polygons
    // is always a convex polygon (or a degenerated polygon)
    poly ret;
    
    int n = P.size();
    int m = Q.size();
    
    for(int i=0; i<n-1; i++)
    {
        for(int j=0; j<m-1; j++)
        {
            // make sure to include all intersection points from
            // all cases of segment intersection.
            point p = segment_intersection(P[i], P[i+1], Q[j], Q[j+1]);
            if(p == undefined) continue;
            ret.PB(p);
        }
    }

    for(int i=0; i<n-1; i++)
    {
        if(is_in(P[i], Q))
            ret.PB(P[i]);
    }
    
    for(int i=0; i<m-1; i++)
    {
        if(is_in(Q[i], P))
            ret.PB(Q[i]);
    }


    ret = convex_hull(ret);
    return ret;
}
void filter(poly &P){ // O(n)
    
    // P points must be given in either
    // clockwise or counter-clockwise order
    
    // this functions will do:
    // remove duplicated points
    // make P[0] == P[n-1]
    // remove collinear points
    // make P points oriented ccw if P is convex
    
    // TESTED: took care of a lot of cases
    // still there may exist some special cases that are not handled
    // or there may be some bugs
    
    vp v;
    int n;
    
    // getting rid of duplicated points
    n = P.size();
    for(int i=0; i<n; i++)
    {
        if(!v.empty() && v[0] == P[i]) break;
        int j = i;
        while(j < n && P[i] == P[j]) j++;
        v.PB(P[i]);
        i = j-1;
    }
    P = v;
//    print(P);
    
    if(P.empty()) return;
    if(P.front() == P.back()) P.pop_back();
    
    n = P.size();
    int idx = -1;
    for(int i=0; i<n && idx == -1; i++)
    {
        int prv = i-1 >= 0? i-1 : n-1;
        int nxt = i+1 < n? i+1 : 0;
        
        if(!collinear(P[i], P[prv], P[nxt]))
            idx = i;
    }
    
    
    // special case for degenerated polygons
    if(idx == -1)
    {
        int i1 = 0, i2 = 0;
        for(int i=0; i<n; i++)
        {
            if( P[i1].x - EPS > P[i].x
                || fabs(P[i1].x - P[i].x) <= EPS && P[i1].y - EPS > P[i].y )
                i1 = i;
            
            if( P[i2].x + EPS < P[i].x
                || fabs(P[i2].x - P[i].x) <= EPS && P[i2].y + EPS < P[i].y )
                i2 = i;
        }
        
        point p = P[i1], q = P[i2];
        P.resize(2);
        P[0] = p, P[1] = q;
        if(P[0] != P[1])
            P.PB(P[0]);
        
        return;
    }
    
    
    // getting rid of collinear points on the edges of P
    v.resize(n);
    for(int i=idx; i<n; i++)
        v[i - idx] = P[i];
    for(int i=0; i<idx; i++)
        v[n-idx + i] = P[i];
    for(int i=0; i<n; i++)
        P[i] = v[i];
    
    P.PB(P[0]);
    n++;
    
    stack <point, vp> stc;
    point p = P[0], q = P[1];
    stc.push(p);
    stc.push(q);
    for(int i=2; i<n; i++)
    {
        if(collinear(p, q, P[i]))
        {
            stc.pop();
            q = P[i];
            stc.push(P[i]);
        }
        else
        {
            p = q;
            q = P[i];
            stc.push(P[i]);
        }
    }
    assert(q == P[0]);
    
    n = stc.size();
    P.resize(n);
    for(int i=n-1; i>=0; i--)
        P[i] = stc.top(), stc.pop();
    
    assert(n >= 4);
    assert(P[0] == P[n-1]);
    
    
    // this is to make the orientation of P counter-clockwise
    // only for convex polygons
    if(!is_convex(P)) return;
    if(ccw(P[0], P[1], P[2])) return;
    reverse(all(P));
}
//
int main()
{
    // be careful that points don't coincide
    read_file();
    int n;
    while(cin>>n)
    {
        poly P(n);
        for(int i=0; i<n; i++) cin>>P[i];
        filter(P);
        
        print(P);
        cout<<endl;
    }
}
