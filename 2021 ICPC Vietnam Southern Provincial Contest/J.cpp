#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

using namespace std;

#define INP "input"
#define OUT "output"

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

void solve() {
    int n, m; cin >> n >> m;
    vector<string> arr(n);
    for (int i = 0; i < n; ++i) cin >> arr[i];
    vector<vector<int>> left(n, vector<int>(m, 0));
    vector<vector<int>> right(n, vector<int>(m, 0));
    vector<vector<int>> up(n, vector<int>(m, 0));
    vector<vector<int>> down(n, vector<int>(m, 0));
    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (arr[i][j] == '0') continue;
            if (arr[i - 1][j] == '1') up[i][j] = up[i - 1][j] + 1;
        }
    }
    for (int i = n - 2; i >= 0; --i) {
        for (int j = 0; j < m; ++j) {
            if (arr[i][j] == '0') continue;
            if (arr[i + 1][j] == '1') down[i][j] = down[i + 1][j] + 1;
        }
    }
    for (int j = 1; j < m; ++j) {
        for (int i = 0; i < n; ++i) {
            if (arr[i][j] == '0') continue;
            if (arr[i][j - 1] == '1') left[i][j] = left[i][j - 1] + 1;
        }
    }
    for (int j = m - 2; j >= 0; --j) {
        for (int i = 0; i < n; ++i) {
            if (arr[i][j] == '0') continue;
            if (arr[i][j + 1] == '1') right[i][j] = right[i][j + 1] + 1;
        }
    }
    int res = -1;
    int x, y;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (arr[i][j] == '0') continue;
            int tmp = min(left[i][j], right[i][j]);
            tmp = min(tmp, up[i][j]);
            tmp = min(tmp, down[i][j]);
            if (tmp > res) {
                res = tmp;
                x = i + 1;
                y = j + 1;
            }
        }
    }
    if (res == -1) cout << -1;
    else cout << res * 4 + 1 << '\n' << x << ' ' << y;
}

int main(int argc,char *argv[]) {
    //srand(time(nullptr));
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    open_file();
    solve();
    return 0;
}
