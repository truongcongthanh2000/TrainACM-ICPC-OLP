#pragma GCC diagnostic ignored "-Wunused-parameter"
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

using namespace std;

#define INP "solve"
#define OUT "solve"

const long long INF_LL = 1e17;
const int INF = 1e9 + 100;
const int MOD = 1e9 + 7;
const int Base = 50;
const double EPS = 1e-9;
const int BLOCK = 1000;
const int dx[4] = {0, 0, 1, -1};
const int dy[4] = {1, -1, 0, 0};
mt19937 rnd(chrono::system_clock::now().time_since_epoch().count());

void open_file() {
    #ifdef THEMIS
        freopen(INP ".inp","r",stdin);
        freopen(OUT ".out","w",stdout);
    #endif // THEMIS
}

const int maxN = 3e5 + 1;

long long pw[30];
void sol() {
    string s, t;
    cin >> s >> t;
    int n = (int)s.size();
    pw[0] = 1;
    for (int i = 1; i <= 26; i++) pw[i] = pw[i - 1] * Base;
    auto get = [&](char c) {
        return pw[(int)(c - 'a' + 1)];
    };
    auto check = [&](int len, string &res) {
        map<long long, int> used;
        long long h = 0;
        for (int i = 0; i < len - 1; i++) h += get(s[i]);
        for (int i = len - 1; i < n; i++) {
            h += get(s[i]);
            if (used[h] == 0) used[h] = i - len + 2;
            h -= get(s[i - len + 1]);
        }
        int ans = n + 1;
        h = 0;
        for (int i = 0; i < len - 1; i++) h += get(t[i]);
        for (int i = len - 1; i < n; i++) {
            h += get(t[i]);
            if (used[h]) {
                ans = min(ans, used[h]);
            }
            h -= get(t[i - len + 1]);
        }
        if (ans <= n) {
            res = s.substr(ans - 1, len);
            return true;
        }
        return false;
    };
    string ans;
    for (int len = n; len >= 1; len--) {
        if (check(len, ans)) {
            cout << ans << '\n';
            return;
        }
    }
    cout << "NONE" << '\n';
}

void solve() {
    int T;
    cin >> T;
    //T = 1;
    int TestCase = 0;
    while (T--) {
        TestCase += 1;
        //cout << "Case #" << TestCase << ":" << ' ';
        ///cout << "Case #" << TestCase << '\n';
        sol();
    }
}
int main(int argc,char *argv[]) {
    ///srand(time(nullptr));
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    open_file();
    solve();
}
