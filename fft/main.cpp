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
#define fi first
#define se second
#define OO (1000000000)         // ToDo
#define EPS (1e-9)              // ToDo
#define MOD (1000000007)        // ToDo
#define all(v) ((v).begin()),((v).end())
#define WT(x) cout<< #x <<" = "<<"\""<< (x) <<"\""<<endl
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
void read_file(bool outToFile = true) {
#ifdef LOCAL_TEST
    freopen("in", "rt", stdin);
    if (outToFile)
        freopen("out", "wt", stdout);
#endif
}
//
struct FFT {
    
    typedef vector <int> poly;   // ToDo: 'int' or 'll'?
    
    struct complex {
        double r, i;

        complex(double _r = 0.0, double _i = 0.0) {
            r = _r, i = _i;
        }

        complex operator+(const complex & b) {
            return complex(r + b.r, i + b.i);
        }

        complex operator-(const complex & b) {
            return complex(r - b.r, i - b.i);
        }

        complex operator *(const complex & b) {
            return complex(r * b.r - i * b.i, r * b.i + i * b.r);
        }
    };

    static void change(vector<complex> &y) {
        int ln = y.size();
        for (int i = 1, j = ln >> 1; i < ln - 1; i++)
        {
            if (i < j) swap(y[i], y[j]);
            int k = ln >> 1;
            while (j >= k)
            {
                j -= k;
                k >>= 1;
            }
            j += k;
        }
    }

    static void fft(vector<complex> &y, int on) {
        change(y);
        int len = y.size();
        for (int m = 2; m <= len; m <<= 1)
        {
            const static double Pi = acos(-1.0);
            complex wm(cos(-on * 2 * Pi / m), sin(-on * 2 * Pi / m));
            for (int k = 0; k < len; k += m)
            {
                complex w(1, 0);
                for (int j = 0; j < m / 2; j++)
                {
                    complex u = y[k + j];
                    complex t = w * y[k + j + m / 2];
                    y[k + j] = u + t;
                    y[k + j + m / 2] = u - t;
                    w = w * wm;
                }
            }
        }

        if (on == -1)
        {
            for (int i = 0; i < len; i++)
                y[i].r /= len;
        }
    }

    static poly mult(poly a, poly b) {

    	//multiplys two polynomials of degree n in O(n lgn)

        int len = 1;
        int la = a.size();
        int lb = b.size();
        while (len < la + lb) len <<= 1;

        vector<complex> x1(len);
        vector<complex> x2(len);

        for (int i = 0; i < la; i++)    x1[i] = complex(a[i], 0);
        for (int i = la; i < len; i++)  x1[i] = complex(0, 0);
        for (int i = 0; i < lb; i++)    x2[i] = complex(b[i], 0);
        for (int i = lb; i < len; i++)  x2[i] = complex(0, 0);

        fft(x1, 1);
        fft(x2, 1);

        for (int i = 0; i < len; i++)   x1[i] = x1[i] * x2[i];

        fft(x1, -1);

        poly sol(len);
        for (int i = 0; i < len; i++)
        {
            sol[i] = x1[i].r + 0.5;
        }

        return sol;
    }
};
//
int main()
{
    //read_file();
    
    int A[] = {1, 2, 3};
    vi a(A, A+3);
    
    int B[] = {4, 3};
    vi b(B, B+2);
    
    vi c = FFT::mult(a, b);
    
    
    for(int i=0; i<c.size(); i++)
        cout<< c[i] <<endl;
}
// code source: https://pastebin.com/Tt5ayubN
// description: given two polynomials 'a' and 'b' find their convolution
// time complexity: multiplying two polynomials of degree n in O(n lgn)
