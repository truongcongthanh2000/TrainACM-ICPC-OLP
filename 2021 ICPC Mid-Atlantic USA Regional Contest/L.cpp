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

const int maxN = 1e6 + 100;
const int MOD = 1e9 + 7;

void sol() {
    int n, m;
    cin >> n >> m;
    vector<string> s(n);
    cin >> s;

    queue<pair<int, int> > Q;
    vector<vector<int> > attack(n, vector<int>(m, 0));
    vector<vector<int> > visited(n, vector<int>(m, 0));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (s[i][j] == 'R') {
                Q.push({i, j});
                visited[i][j] = 1;
            }
            if (s[i][j] == 'K') {
                for (int dx : {-1, 1, -2, 2}) {
                    for (int dy : {abs(dx) - 3, 3 - abs(dx)}) {
                        int x = i + dx;
                        int y = j + dy;
                        if (x >= 0 && x < n && y >= 0 && y < m) {
                            attack[x][y] += 1;
                        }
                    }
                }
            }
        }
    }

    while ((int)Q.size() != 0) {
        auto it = Q.front();
        Q.pop();
        int i = it.first, j = it.second;
        if (s[i][j] == 'T') {
            cout << "yes";
            return;
        }

        if (s[i][j] == 'K') {
            for (int ddx : {-1, 1, -2, 2}) {
                for (int ddy : {abs(ddx) - 3, 3 - abs(ddx)}) {
                    int x = i + ddx;
                    int y = j + ddy;
                    if (x >= 0 && x < n && y >= 0 && y < m && --attack[x][y] == 0) {
                        for (int h = 0; h < 4 && visited[x][y] == 0; h++) {
                            for (int k = 1; k <= max(n, m); k++) {
                                int u = x + dx[h] * k;
                                int v = y + dy[h] * k;
                                if (u >= 0 && u < n && v >= 0 && v < m) {
                                    if (visited[u][v] == 1) {
                                        visited[x][y] = 1;
                                        Q.push({x, y});
                                        break;
                                    }
                                    if (s[u][v] == 'K' && visited[u][v] == 0) {
                                        break;
                                    } 
                                } else {
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }

        for (int h = 0; h < 4; h++) {
            for (int k = 1; k <= max(n, m); k++) {
                int u = i + dx[h] * k;
                int v = j + dy[h] * k;
                if (u >= 0 && u < n && v >= 0 && v < m) {
                    if (visited[u][v] == 0 && attack[u][v] == 0) {
                        visited[u][v] = 1;
                        Q.push({u, v});
                    }
                    if (s[u][v] == 'K' && visited[u][v] == 0) {
                        break;
                    }
                } else {
                    break;
                }
            }
        }
    }
    cout << "no";
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
