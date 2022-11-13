#include <bits/stdc++.h>

using namespace std;

void open_file() {
    #ifdef THEMIS
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif // THEMIS
}

const int MOD = 998244353;

struct mt {
    long long c[8][8];
    mt() {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) c[i][j] = 0;
        }
    }

    void gen(int row, vector<int> value) {
        for (int i = 0; i < 8; i++) c[row][i] = value[i];
    }
};

mt init() {
    mt ans;
    for (int i = 0; i < 8; i++) {
        ans.c[i][i] = 1;
    }
    return ans;
}

mt nhan(mt a, mt b) {
    mt c;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            long long value = 0;
            for (int k = 0; k < 8; k++) {
                long long w = a.c[i][k] * b.c[k][j] % MOD;
                value = (value + w) % MOD;
            }
            c.c[i][j] = value;
        }
    }
    return c;
}

mt get(mt a, long long n) {
    mt ans = init();
    for (; n; n >>= 1, a = nhan(a, a)) {
        if (n & 1) {
            ans = nhan(ans, a);
        }
    }
    return ans;
}

void sol() {
    long long n;
    cin >> n;
    mt a;
    a.gen(0, {1, 1, 1, 1, 0, 0, 0, 0});
    a.gen(1, {1, 0, 0, 0, 3, 0, 0, 0});
    a.gen(2, {1, 0, 0, 0, 3, 0, 0, 0});
    a.gen(3, {2, 1, 1, 0, 6, 3, 3, 0});
    a.gen(4, {0, 0, 0, 0, 1, 1, 1, 1});
    a.gen(5, {0, 0, 0, 0, 1, 0, 0, 0});
    a.gen(6, {0, 0, 0, 0, 1, 0, 0, 0});
    a.gen(7, {0, 0, 0, 0, 2, 1, 1, 0});
    mt A = get(a, n - 1);

    long long ans = 0;
    for (int i = 0; i < 4; i++) ans = (ans + A.c[i][4]) % MOD;
    cout << ans;
}
int main() {
    open_file();
    int t = 1;
    //cin >> t;
    while (t--) sol();
}
