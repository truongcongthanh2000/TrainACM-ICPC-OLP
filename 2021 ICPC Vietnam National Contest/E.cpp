#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

using namespace std;

#define INP "solve"
#define OUT "solve"

const long long INF_LL = 1e18;
const int INF = 1e9 + 100;
const long double EPS = 1e-6;
const int BLOCK = 550;
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};
mt19937 rnd(chrono::system_clock::now().time_since_epoch().count());

void open_file() {
    #ifdef THEMIS
        freopen(INP ".txt","r",stdin);
        freopen(OUT ".out","w",stdout);
    #endif // THEMIS
}

const int maxN = 1e6 + 100;
const int MOD = 998244353;

void sol() {
    int n, m;
    cin >> n >> m;
    if (m == 0) {
        cout << 0 << '\n';
        return;
    }
    vector<vector<int> > ans;
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        if (y == n) {
            if (x == 0) {
                ans.push_back({x + 1, y - 1, x, y - 1, x, y});
                ans.push_back({x + 1, y - 1, x + 1, y, x, y});
                ans.push_back({x + 1, y, x, y, x, y - 1});
            } else {
                ans.push_back({x - 1, y - 1, x - 1, y, x, y});
                ans.push_back({x - 1, y - 1, x, y - 1, x, y});
                ans.push_back({x, y - 1, x, y, x - 1, y});
            }
        }
        else {
            if (x < n) {
                ans.push_back({x + 1, y + 1, x + 1, y, x, y});
                ans.push_back({x + 1, y + 1, x, y + 1, x, y});
                ans.push_back({x + 1, y, x, y, x, y + 1});
            }
            else {
                ans.push_back({x - 1, y, x, y, x, y + 1});
                ans.push_back({x, y, x, y + 1, x - 1, y + 1});
                ans.push_back({x, y, x - 1, y, x - 1, y + 1});
            }
        }
    }
    cout << (int)ans.size() << '\n';
    for (auto it : ans) {
        cout << (int)it.size() / 2 - 1 << ' ';
        for (int x : it) cout << x << ' ';
        cout << '\n';
    }
}

void solve() {
//    clock_t start, end;
//    start = clock();
    int T = 1;
    cin >> T;
    int TestCase = 0;
    while (T--) {
        TestCase += 1;
        //cerr << "Processing test = " << TestCase << '\n';
        //cout << "Case #" << TestCase << ": ";
        sol();
        //if (T) cout << '\n';
    }
//    end = clock();
//    cerr << "Time = " << (double)(end - start) / (double)CLOCKS_PER_SEC << '\n';
}

int main(int argc,char *argv[]) {
    //srand(time(nullptr));
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    open_file();
    solve();
    return 0;
}
