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
// mt19937 rnd(chrono::system_clock::now().time_since_epoch().count());

void open_file() {

}

const int maxN = 1e6 + 100;
const int MOD = 1e9 + 7;

void sol() {
    int n, U, M;
    cin >> n >> U >> M;
    vector<int> w(n);
    for (int i = 0; i < n; i++) cin >> w[i];
    sort(w.begin(), w.end());

    auto ok = [&](int x) {
        int s = 0;
        for (int y : w) s += y;

        int time = x * M;
        for (int i = n - 1; i >= 0; i--) {
            if (time >= w[i]) {
                time -= w[i];
                s -= w[i];
            }
        }
        return U * x >= s;    
    };
    
    int L = 0, R = 1e5;
    int ans = R;
    while (L <= R) {
        int mid = (L + R) >> 1;
        if (ok(mid)) {
            ans = mid;
            R = mid - 1;
        }
        else L = mid + 1;
    }
    cout << ans << '\n';
}

void solve() {
    int T = 1;
    cin >> T;
    int TestCase = 0;
    while (T--) {
        TestCase += 1;
        cerr << "Processing test = " << TestCase << '\n';
        //cout << "Case #" << TestCase << ": ";
        sol();
        //if (T) cout << '\n';
    }
}

int main(int argc,char *argv[]) {
    //srand(time(nullptr));
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    open_file();
    solve();
    return 0;
}
