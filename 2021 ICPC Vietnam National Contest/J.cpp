#include<bits/stdc++.h>

using namespace std;

void ioFiles() {
    #ifdef THEMIS
        freopen("solve.txt", "r", stdin);
        freopen("solve.out", "w", stdout);
    #endif // THEMIS
}

const int maxN = 1e7 + 100;

int c[3][3];
void solve() {
    int nc;
    cin >> nc;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) cin >> c[i][j];
    }
    cout << "YES" << '\n';
    vector<vector<int> > ans;
    { ///A
        int n = (c[1][2] - c[0][1] + nc) % nc;
        c[0][0] = (c[0][0] + n) % nc;
        c[0][1] = (c[0][1] + n) % nc;
        c[1][0] = (c[1][0] + n) % nc;
        c[1][1] = (c[1][1] + n) % nc;
        if (n > 0) ans.push_back({1, 0, 0, 0, 1, n});
    }
    { ///AB
        int n = (c[2][1] - c[1][0] + nc) % nc;
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 3; j++) c[i][j] = (c[i][j] + n) % nc;
        }
        if (n > 0) ans.push_back({1, 1, 0, 0, 1, n});
    }
    { ///B
        int n = (c[1][0] - c[1][1] + nc) % nc;
        for (int i = 0; i < 2; i++) {
            for (int j = 1; j < 3; j++) c[i][j] = (c[i][j] + n) % nc;
        }
        if (n > 0) ans.push_back({0, 1, 0, 0, 3, n});
    }
    { ///C
        int n = (c[0][1] - c[1][1] + nc) % nc;
        for (int i = 1; i < 3; i++) {
            for (int j = 0; j < 2; j++) c[i][j] = (c[i][j] + n) % nc;
        }
        if (n > 0) ans.push_back({0, 0, 1, 0, 7, n});
    }
    { ///AD
        int n = (nc - c[1][0]) % nc;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                c[i][j] = (c[i][j] + n) % nc;
            }
        }
        c[0][2] = (c[0][2] - n + nc) % nc;
        c[2][0] = (c[2][0] - n + nc) % nc;
        if (n > 0) ans.push_back({1, 0, 0, 1, 1, n});
    }
    { ///1
        int n = (nc - c[0][0]) % nc;
        if (n > 0) ans.push_back({0, 0, 0, 0, 1, n});
    }
    { ///2
        int n = (nc - c[0][2]) % nc;
        if (n > 0) ans.push_back({0, 0, 0, 0, 3, n});
    }
    { ///3
        int n = (nc - c[2][2]) % nc;
        if (n > 0) ans.push_back({0, 0, 0, 0, 9, n});
    }
    { ///4
        int n = (nc - c[2][0]) % nc;
        if (n > 0) ans.push_back({0, 0, 0, 0, 7, n});
    }
    cout << (int)ans.size() << '\n';
    for (auto x : ans) {
        for (auto y : x) cout << y << ' ';
        cout << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    ioFiles();
    int t = 1;
    //cin >> t;
    while (t--) solve();
}
