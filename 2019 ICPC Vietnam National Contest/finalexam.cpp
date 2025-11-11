#include <bits/stdc++.h>

using namespace std;

#define INP "solve"
#define OUT "solve"

const int QQ = 3e5 + 10;
const int maxN = 5e5 + 100;
const int maxM = 3e5 + 10;
const long long oo = 5e17;
const int module = 1e9 + 7;
const long double du = 1e-9;

void doc() {
    freopen(INP ".inp","r",stdin);
    freopen(OUT ".out","w",stdout);
}
const int lm = 30000000;
int DA[lm + 2], DB[lm + 2], DC[lm + 2];
typedef pair<int, int> i2;
typedef pair<int, i2> i3;
int F[6000][6000];
bool Used[6000][6000];
int GCD(int a, int b) {
    if (b == 0) return a;
    if (Used[a][b]) return F[a][b];
    Used[a][b] = 1;
    return F[a][b] = GCD(b, a % b);
}
void solve() {
    ///memset(DA, 0, sizeof(DA));
    ///memset(DB, 0, sizeof(DB));
    ///memset(DC, 0, sizeof(DC));
    int na, nb, nc;
    cin >> na >> nb >> nc;
    for (int i = 1; i <= na; i++) {
        int x;
        cin >> x;
        DA[x] += 1;
    }
    for (int i = 1; i <= nb; i++) {
        int x;
        cin >> x;
        DB[x] += 1;
    }
    for (int i = 1; i <= nc; i++) {
        int x;
        cin >> x;
        DC[x] += 1;
    }
    long long Res = 0;
    for (int a = 1; a <= 5477; a++) {
        for (int b = (1 + a % 2); b < a; b += 2) {
            if (a * a + b * b > lm) break;
            if (GCD(a, b) > 1) continue;
            int C = a * a + b * b;
            int A = a * a - b * b;
            int B = 2 * a * b;
            int aa = A;
            int bb = B;
            int cc = C;
            while (C <= lm) {
                if (DA[A] && DB[B] && DC[C]) 
                    Res += 1LL * DA[A] * DB[B] * DC[C];
                if (DA[B] && DB[A] && DC[C]) 
                    Res += 1LL * DA[B] * DB[A] * DC[C];
                A += aa;
                B += bb;
                C += cc;
                ///cout << A << " " << B << " " << C << '\n';
            }
        }
    }
    cout << Res;
}
int main(int argc,char *argv[]) {
    //srand(time(nullptr));
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    ///doc();
    solve();
}
