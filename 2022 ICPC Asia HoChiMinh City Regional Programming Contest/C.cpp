#include <bits/stdc++.h>

using namespace std;

void open_file() {
    #ifdef THEMIS
        freopen("sol.inp", "r", stdin);
        freopen("sol.out", "w", stdout);
    #endif // THEMIS
}

const int maxN = 5e5 + 100;
const long long INF = 2e9 + 100;

void sol() {
    int n;
    cin >> n;
    if (n % 2 == 0) {
        cout << -1;
        return;
    }
    vector<vector<int> > a(2, vector<int>(n, 0));
    vector<pair<int, int> > p(2 * n);
    int x = 0, y = 0;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
            p[a[i][j]] = {i, j};
            if (a[i][j] == 0) {
                x = i;
                y = j;
            }
        }
    }

    vector<int> ans;
    int d = 1;
    vector<vector<int> > b = a;
    for (int i = 0; i < 4 * n - 2; i++) {
        int nx = x ^ 1, ny = (y + d) % n;
        ans.push_back(b[nx][ny]);
        swap(b[x][y], b[nx][ny]);
        x = nx; y = ny;
        d ^= 1;
    }

    vector<pair<int, int> > np(2 * n);
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < n; j++) {
            np[b[i][j]] = {i, j};
        }
    }

    for (int i = 0; i < 2 * n - 1; i++) {
        int value = a[x ^ 1][y];
        int nx = np[value].first, ny = np[value].second;
        ans.push_back(b[nx][ny]);
        swap(b[x][y], b[nx][ny]);
        x = nx; y = ny;
    }
    cout << (int)ans.size() << '\n';
    for (int x : ans) cout << x << ' ';
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    open_file();
    int t = 1;
//    cin >> t;
    while (t--) sol();
}
