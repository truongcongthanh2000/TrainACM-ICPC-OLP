#include <bits/stdc++.h>
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#define TASK "task"

using namespace std;

void openFiles() {
#ifdef THEMIS
    freopen(TASK ".inp", "r", stdin);
    freopen(TASK ".out", "w", stdout);
#endif
}

void solve() {
    int n; cin >> n; 
    int m = n * n - n + 1;
    vector<vector<int>> res(m, vector<int>(n, 0));
    vector<vector<int>> tmp(n - 1, vector<int>(n - 1, 0));
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - 1; ++j) tmp[i][j] = i * (n - 1) + j + n + 1;
    }

    for (int i = 0; i < n; ++i) res[0][i] = i + 1;
    for (int i = 1; i < n; ++i) {
        for (int j = 1; j < n; ++j) {
            res[i][j] = tmp[i - 1][j - 1];
        }
    }

    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - 1; ++j) {
            for (int k = 0; k < n - 1; ++k) {
                res[i * (n - 1) + j + n][k + 1] = tmp[k][(j + i * k) % (n - 1)];
            }
        }
    }

    for (int i = 1; i < m; ++i) {
        res[i][0] = (i - 1) / (n - 1) + 1;
    }

    cout << m << '\n';
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) cout << res[i][j] << ' ';
        cout << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    openFiles();
    solve();
}