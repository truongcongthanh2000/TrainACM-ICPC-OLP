#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

using namespace std;

#define INP "input"
#define OUT "output"

/* some template */
template <typename T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& a) {
    out << (int)a.size() << '\n';
    for (const auto& v : a) out << v << ' ';
    out << endl;
    return out;
}

template <typename T>
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
    for (auto& x : v) is >> x;
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
    freopen(INP ".txt", "r", stdin);
    freopen(OUT ".txt", "w", stdout);
#endif  // THEMIS
}

const int maxN = 2e7 + 100;
const int MOD = 1e9 + 7;

struct MaxBipartiteMatching {  /// base 1th; X -> Y
    int n, m;
    vector<int> link, match, stk, Used;
    bool Found;
    vector<vector<int> > adj;
    MaxBipartiteMatching(){};
    MaxBipartiteMatching(int _n, int _m) {
        n = _n;                  /// Size(X)
        m = _m;                  /// Size(Y)
        link.assign(n + 7, 0);   /// X
        match.assign(m + 7, 0);  /// match[y] = x, if have x -> y in MaxBipartiteMatching or 0 if not
        Used.assign(m + 7, 0);
        stk.clear();
        adj.resize(n + 7);
    }

    void addEdge(int u, int v) {  /// u in X and v in Y
        adj[u].push_back(v);
    }

    void DFS(int u) {
        for (int v : adj[u]) {
            if (Used[v] == 0) {
                Used[v] = 1;
                stk.push_back(v);
                if (match[v] == 0)
                    Found = true;
                else
                    DFS(match[v]);
                if (Found) {
                    match[v] = u;
                    return;
                }
            }
        }
    }

    int getCost() {  /// get size MaxBipartiteMatching
        int Nlink = n;
        for (int i = 1; i <= n; i++) link[i] = i;
        for (int i = 1; i <= m; i++) match[i] = 0;
        int old;
        do {
            old = Nlink;
            for (int x : stk) Used[x] = 0;
            stk.clear();
            for (int i = Nlink; i >= 1; i--) {
                Found = false;
                DFS(link[i]);
                if (Found) {
                    link[i] = link[Nlink--];
                }
            }
        } while (old != Nlink);
        return n - old;
    }

    int getX(int y) {  /// match[y] = x, if have x -> y in MaxBipartiteMatching or 0 if not
        return match[y];
    }
};

int p[maxN];

void sieve() {
    for (int i = 2; i * i < maxN; i++) {
        if (!p[i]) {
            for (int j = i * i; j < maxN; j += i) {
                p[j] = 1;
            }
        }
    }
}

void sol() {
    sieve();
    int n;
    cin >> n;
    vector<int> a;

    vector<int> even, odd;
    int has = 0;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        if (x % 2 == 0) {
            even.push_back(x);
        } else {
            if (x == 1) {
                if (!has) odd.push_back(x);
                has = 1;
            } else
                odd.push_back(x);
        }
    }

    MaxBipartiteMatching mbm((int)even.size(), (int)odd.size());
    for (int i = 0; i < (int)even.size(); i++) {
        for (int j = 0; j < (int)odd.size(); j++) {
            if (!p[even[i] + odd[j]]) {
                mbm.addEdge(i + 1, j + 1);
            }
        }
    }

    cout << (int)even.size() + (int)odd.size() - mbm.getCost() << endl;
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
        // cout << "Case #" << TestCase << ": ";
        sol();
        // if (T) cout << '\n';
    }
    end = clock();
    cerr << "Time = " << (double)(end - start) / (double)CLOCKS_PER_SEC << '\n';
}

int main(int argc, char* argv[]) {
    // srand(time(nullptr));
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);
    open_file();
    solve();
    return 0;
}
