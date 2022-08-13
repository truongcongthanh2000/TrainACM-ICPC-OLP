#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

using namespace std;

#define INP "input"
#define OUT "output"

/* some template */
template<typename T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& a) {
    out << (int)a.size() << '\n';
    for (const auto& v : a) out << v << ' ';
    out << endl;
    return out;
}

template<typename T>
std::ostream& operator<<(std::ostream& out, const std::vector<vector<T> >& a) {
    out << (int)a.size() << '\n';
    for (const auto& v : a) {
        for (const auto& value : v) out << value << ' ';
        out << endl;
    }
    return out;
}

template <typename T>
std::istream& operator>>(std::istream& is, std::vector<T>& v) {
    std::copy(std::istream_iterator<T>(is), std::istream_iterator<T>(), std::back_inserter(v));
    return is;
}
/* end template */

const long long INF_LL = 1e18;
const int INF = 1e9 + 100;
const long double EPS = 1e-6;
const int BLOCK = 550;
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};

void open_file() {
    #ifdef THEMIS
        freopen(INP ".txt","r",stdin);
        freopen(OUT ".txt","w",stdout);
    #endif // THEMIS
}

const int maxN = 1e6 + 100;
const int MOD = 1e9 + 7;
const int N = 305;

int n, S;
int num[N], p[N];
vector<int> adj[N];
int dp[N][N][2], f[N][2];

void dfs(int u, int pre) {
    dp[u][0][1] = 0;
    dp[u][num[u]][0] = p[u];
    for (int v : adj[u]) if (v != pre) {
        dfs(v, u);
        for (int sumu = 0; sumu <= S; ++sumu) {
            for (int j = 0; j <= 1; ++j) {
                if (dp[u][sumu][j] < 0) {
                    continue;
                }
                for (int sumv = 0; sumv + sumu <= S; ++sumv) {
                    for (int x = 0; x <= 1; ++x) {
                        if ((x | j)) {
                            // if (u == 4 && sumv == 0 && x == 1) {
                            //     cout << sumu << ' ' << sumv << ' ' << dp[u][sumu][j] << ' ' << dp[v][sumv][x] << '\n';
                            // }
                            f[sumv + sumu][j] = max(f[sumu + sumv][j], dp[u][sumu][j] + dp[v][sumv][x]);
                        }
                    }
                }
            }
        }
        for (int sumu = 0; sumu <= S; ++sumu) {
            for (int x = 0; x <= 1; ++x) {
                dp[u][sumu][x] = f[sumu][x];
                f[sumu][x] = -1e9;
            }
        }
    }
}
void sol() {
    cin >> n >> S;
    for (int i = 1; i <= n; ++i) {
        cin >> num[i] >> p[i];
    }
    for (int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= S; ++j) {
            for (int k = 0; k <= 1; ++k) {
                dp[i][j][k] = -1e9;
            }
        }
    }
    int ans = 0;
    dfs(1, 1);
    // cout << dp[4][2][0] << '\n';
    for (int i = 0; i <= S; ++i) {
        ans = max({ans, dp[1][i][0], dp[1][i][1]});
    }
    cout << ans;
}

void solve() {
    clock_t start, end;
    start = clock();
    int T = 1;
    // cin >> T;
    int TestCase = 0;
    while (T--) {
        TestCase += 1;
        cerr << "Processing test = " << TestCase << '\n';
        //cout << "Case #" << TestCase << ": ";
        sol();
        //if (T) cout << '\n';
    }
    end = clock();
    cerr << "Time = " << (double)(end - start) / (double)CLOCKS_PER_SEC << '\n';
}

int main(int argc,char *argv[]) {
    //srand(time(nullptr));
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    open_file();
    solve();
    return 0;
}
