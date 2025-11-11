#pragma GCC diagnostic ignored "-Wunused-parameter"
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

using namespace std;

#define INP "solve"
#define OUT "solve"

const long long INF_LL = 8e18;
const int INF = 1e9 + 100;
const int MOD = 1e9 + 7;
//const int Base = 311;9
const long double EPS = 1e-10;
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

const int maxN = 1e6 + 100;

void sol(){
    int n;
    cin >> n;
    vector<int> s(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        s[i] = s[i - 1] + x;
    }

    auto sum = [&](int L, int R) {
        return s[R] - s[L - 1];
    };

    auto up10 = [&](int s) {
        return (s + 9) / 10 * 10;
    };

    set<pair<int, int> > line;
    line.insert({n, 1});
    long long old_sum = up10(s[n]);
    long long ans = old_sum;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        auto it = line.lower_bound({x, -1});
        int L = it->second, R = it->first;
        assert(it != line.end());
        line.erase(it);
        int sub = sum(L, R);
        old_sum -= up10(sub);
        if (x > L) {
            old_sum += up10(sum(L, x - 1));
            line.insert({x - 1, L});
        }
        if (x < R) {
            old_sum += up10(sum(x + 1, R));
            line.insert({R, x + 1});
        }
        long long cost = 1LL * old_sum * (int)line.size();
        ans = max(ans, cost);
    }
    cout << ans;
}

void solve() {
    clock_t begin = clock();
    int T;
//    cin >> T;
    T = 1;
    int TestCase = 0;
    while (T--) {
        TestCase += 1;
        //cout << "Case #" << TestCase << ":" << ' ';
        //cout << "Test " << TestCase << ": ";
        sol();
    }
    clock_t end = clock();
    cerr << "Time: " << fixed << setprecision(10) << (double)(end - begin) / (double)CLOCKS_PER_SEC << '\n';
}

int main(int argc,char *argv[]) {
    ///srand(time(nullptr));
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    open_file();
    solve();
}
