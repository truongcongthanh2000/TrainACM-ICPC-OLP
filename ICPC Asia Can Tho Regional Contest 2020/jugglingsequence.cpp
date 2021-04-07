#include <bits/stdc++.h>

using namespace std;

void doc() {
    #ifdef THEMIS
        freopen("solve.inp", "r", stdin);
        freopen("solve.out", "w", stdout);
    #endif // THEMIS
}

const int maxN = 5e5 + 100;
const long long INF = 1e18 + 100;

void sol() {
    long long n, m;
    cin >> n >> m;
    auto get = [&](long long x) -> long long {
        if (n == 1) return 1;
        long long pw = 1;
        vector<long long> a;
        while ((pw + 1) / 2 < n) {
            long long i = (pw + 1) / 2;
            a.push_back(i);
            pw *= 3;
        }
//        cout << "Case: " << x << '\n';
//        for (auto it : a) cout << it << ' ';
//        cout << '\n';
        int sz = (int)a.size();
        long long ans = 0;
        for (int i = 0; i < sz - 1; i++) {
            long long b = a[i];
            long long cost = min(x, b);
            cost += max(0LL, min(x, b * 3 - 2) - b * 2 + 1);
            ans += cost;
        }
        //cout << ans << '\n';
        long long b = a[sz - 1];
        long long len = n - b + 1;
        long long xx = len / 2;
        long long yy = (len + 1) / 2;
        long long limits = min(x, b * 2 + xx - 1);
        long long lower = b - yy + 1;
        ans += max(0LL, min(x, b) - lower + 1);
        ans += max(0LL, limits - (b * 2) + 1);
        return ans;
    };
    long long L = 1, R = n * 3;
    long long ans = 0;
    while (L <= R) {
        long long mid = (L + R) >> 1;
        long long cost = get(mid);
        //cout << mid << " " << cost << '\n';
        if (cost >= m) {
            ans = mid;
            R = mid - 1;
        }
        else L = mid + 1;
    }
    cout << ans << '\n';
}

void solve() {
    int T;
    //T = 1;
    cin >> T;
    while (T--) {
        sol();
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    doc();
    solve();
}
