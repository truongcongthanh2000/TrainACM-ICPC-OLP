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
    int n; cin >> n;
    map<int, int> xx, yy;
    map<vector<int>, int> cnt;
    for (int i = 0; i < n; ++i) {
        int x, y; cin >> x >> y;
        xx[x]++;
        yy[y]++;
        cnt[{x, y}]++;
    }
    long long res = 0;
    for (auto it : xx) {
        int val = it.second;
        res += 1ll * val * (val - 1) / 2;
    }
    for (auto it : yy) {
        int val = it.second;
        res += 1ll * val * (val - 1) / 2;
    }
    for (auto it : cnt) {
        int val = it.second;
        res -= 1ll * val * (val - 1) / 2;
    }
    cout << res;
}

int main(int argc,char *argv[]) {
    //srand(time(nullptr));
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    open_file();
    solve();
    return 0;
}
