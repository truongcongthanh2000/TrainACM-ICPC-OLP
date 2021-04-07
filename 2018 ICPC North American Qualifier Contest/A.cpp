#pragma GCC diagnostic ignored "-Wunused-parameter"
#define _USE_MATH_DEFINES
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
const int dx[4] = {0, 0, 1, -1};
const int dy[4] = {1, -1, 0, 0};

void open_file() {
    #ifdef THEMIS
        freopen(INP ".inp","r",stdin);
        freopen(OUT ".out","w",stdout);
    #endif // THEMIS
}

const int maxN = 1e3 + 10;

bool has(vector<int> &root, vector<int> &a) {
    for (int x : a) {
        if (find(root.begin(), root.end(), x) == root.end()) return false;
    }
    return true;
}
bool ok(vector<vector<vector<int> > > &a, int x, int y) {
    map<int, int> M;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            M[a[x][i][j]] = i + 1;
        }
    }
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            int w = a[y][i][j];
            if (M[w]) {
                int old = M[w] - 1;
                vector<int> value;
                for (int k = 0; k < 5; k++) {
                    if (a[x][old][k] == w) continue;
                    value.push_back(a[x][old][k]);
                }
                for (int k = 0; k < 5; k++) {
                    if (a[y][i][k] == w) continue;
                    value.push_back(a[y][i][k]);
                }
                bool failed = false;
                for (int k = 0; failed == false && k < (int)a.size(); k++) {
                    if (k == x || k == y) continue;
                    for (int u = 0; u < 5; u++) {
                        if (has(value, a[k][u])) {
                            failed = true;
                            break;
                        }
                    }
                }
                if (failed) continue;
                return true;
            }
        }
    }
    return false;
}
void sol() {
    int n;
    cin >> n;
    vector<vector<vector<int> > > a(n);
    for (int i = 0; i < n; i++) {
        a[i] = vector<vector<int> > (5, vector<int>(5, 0));
        for (int k = 0; k < 5; k++) {
            for (int u = 0; u < 5; u++) cin >> a[i][k][u];
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (ok(a, i, j)) {
                cout << i + 1 << " " << j + 1;
                return;
            }
        }
    }
    cout << "no ties";
}

void solve() {
    int T;
    //cin >> T;
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
