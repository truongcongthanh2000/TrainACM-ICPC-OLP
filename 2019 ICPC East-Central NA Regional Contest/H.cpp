#pragma GCC diagnostic ignored "-Wunused-parameter"

#include <bits/stdc++.h>

using namespace std;

#define INP "solve"
#define OUT "solve"

const long long INF_LL = 1e17;
const int INF = 1e9 + 100;
const int MOD = 1e9 + 7;
const int Base = 30;
const double EPS = 1e-9;
const int BLOCK = 1000;
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};

void open_file() {
    #ifdef THEMIS
        freopen(INP ".inp","r",stdin);
        freopen(OUT ".out","w",stdout);
    #endif // THEMIS
}

const int maxN = 5e2 + 10;

long long extgcd(long long a, long long b, long long &x, long long &y) {
    long long g = a; x = 1; y = 0;
    if (b != 0) g = extgcd(b, a % b, y, x), y -= (a / b) * x;
    return g;
}
bool linearCongruences(vector<long long> a, vector<long long> b, vector<long long> m, long long &x, long long &M) {
    long long n = a.size();
    x = 0; M = 1;
    for (int i = 0; i < n; i++) {
        long long a_ = a[i] * M, b_ = b[i] - a[i] * x, m_ = m[i];
        long long y, t, g = extgcd(a_, m_, y, t);
        if (b_ % g) return false;
        b_ /= g; m_ /= g;
        x += M * (y * b_ % m_);
        M *= m_;
    }
    x = (x + M) % M;
    return true;
}
void sol() {
    int a, b, c, d, e, f, g;
    cin >> a >> b >> c >> d >> e >> f >> g;
    vector<int> L;
    for (int t = 1; 2 * t < a; t++) {
        int cost = (a - 2 * t) * (b - 2 * t) * t;
        L.push_back(cost);
    }
    sort(L.begin(), L.end(), greater<int>());
    long long x = 0;
    long long M = 0;
    linearCongruences({1, 1, 1}, {c, d, e}, {L[0], L[1], L[2]}, x, M);
    cerr << M << '\n';
    long long k = (f - x) / M;
    while (x + k * M < f) k++;
    x = x + k * M;
    cout << x;
}

void solve() {
    int T;
    ///cin >> T;
    T = 1;
    int TestCase = 0;
    while (T--) {
        TestCase += 1;
        //cout << "Case #" << TestCase << ":" << ' ';
        ///cout << "Case #" << TestCase << '\n';
        sol();
    }
}
int main(int argc,char *argv[]) {
    //srand(time(nullptr));
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    open_file();
    solve();
}
