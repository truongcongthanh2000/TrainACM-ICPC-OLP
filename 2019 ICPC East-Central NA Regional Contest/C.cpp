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

template<typename num_t>
struct LPsolver {
    const num_t eps = 1e-9;

    inline int sign(num_t x) {return x < -eps ? -1 : +eps < x;}
    inline int sign(num_t x, num_t y) {return sign(x - y);}
    int m, n;
    vector<int> B, N;
    vector<vector<double>> D;
    LPsolver(const vector<vector<double>> &A, const vector<num_t> &b, const vector<num_t> &c) : m(b.size()), n(c.size()), N(n + 1), B(m), D(m + 2, vector<num_t>(n + 2)) {
        for (int i = 0; i < m; i++) for (int j = 0; j < n; j++) D[i][j] = A[i][j];
        for (int i = 0; i < m; i++) {
            B[i] = n + i;
            D[i][n] = -1;
            D[i][n + 1] = b[i];
        }
        for (int j = 0; j < n; j++) {
            N[j] = j;
            D[m][j] = -c[j];
        }
        N[n] = -1;
        D[m + 1][n] = 1;
    }
    void pivot(int r, int s) {
        for (int i = 0; i < m + 2; i++) if (i != r) {
            for (int j = 0; j < n + 2; j++) if (j != s) {
                D[i][j] -= D[r][j] * D[i][s] / D[r][s];
            }
        }
        for (int j = 0; j < n + 2; j++) if (j != s) D[r][j] /= D[r][s];
        for (int i = 0; i < m + 2; i++) if (i != r) D[i][s] /= -D[r][s];
        D[r][s] = 1.0 / D[r][s];
        swap(B[r], N[s]);
    }
    int simple(int phase) {
        int x = phase == 1 ? m + 1 : m;
        while (1) {
            int s = -1;
            for (int j = 0; j <= n; j++) {
                if (phase == 2 && N[j] == -1) continue;
                if (s == -1 || D[x][j] < D[x][s] || D[x][j] == D[x][s] && N[j] < N[s]) s = j;
            }
            if (sign(D[x][s]) >= 0) return 1;
            int r = -1;
            for (int i = 0; i < m; i++) {
                if (sign(D[i][s]) <= 0) continue;
                if (r == -1 || D[i][n + 1] / D[i][s] < D[r][n + 1] / D[r][s] || D[i][n + 1] / D[i][s] == D[r][n + 1] / D[r][s] && B[i] < B[r]) r = i;
            }
            if (r == -1) return 0;
            pivot(r, s);
        }
    }
    num_t solve(vector<num_t>& x) {
        int r = 0;
        for (int i = 1; i < m; i++) if (D[i][n + 1] < D[r][n + 1]) r = i;
        if (sign(D[r][n + 1]) < 0) {
            pivot(r, n);
            if (!simple(1) || sign(D[m + 1][n + 1]) < 0) return -numeric_limits<num_t>::infinity();
            for (int i = 0; i < m; i++) if (B[i] == -1) {
                int s = -1;
                for (int j = 0; j <= n; j++) {
                    if (s == -1 || D[i][j] < D[i][s] || D[i][j] == D[i][s] && N[j] < N[s]) s = j;
                }
                pivot(i, s);
            }
        }
        if (!simple(2)) return numeric_limits<num_t>::infinity();
        x = vector<num_t>(n);
        for (int i = 0; i < m; i++) if (B[i] < n) x[B[i]] = D[i][n + 1];
        return D[m][n + 1];
    }
};

void sol() {
    int n, m;
    cin >> n >> m;
    vector<double> b(n);
    for (int i = 0; i < n; i++) cin >> b[i];
    vector<vector<double> > A(n, vector<double>(m, 0));
    vector<double> T(m);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> A[j][i];
            A[j][i] /= 100.0;
        }
        cin >> T[i];
    }
    LPsolver<double> df(A, b, T);
    vector<double> x;
    double res = df.solve(x);
    cout << fixed << setprecision(2) << res;
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
