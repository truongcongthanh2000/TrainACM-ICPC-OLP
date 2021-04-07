#pragma GCC diagnostic ignored "-Wunused-parameter"
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

using namespace std;

#define INP "solve"
#define OUT "solve"

const long long INF_LL = 1e17;
const int INF = 1e9 + 100;
const int MOD = 1e9 + 7;
const int Base = 311;
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

const int maxN = 5e5 + 100;

void sol() {
    int n, k, x;
    cin >> n >> k >> x;
    if (n == k) {
        cout << "FINAL " << 1 << " " << 1 << " " << x << endl;
        return;
    }
    int sl = (n + k - 1) / k;
    vector<long double> ans(sl, 0);
    int last = -1;
    long double last_value = 0;
    auto ask1 = [&]() {
        long double tmp = x;
        vector<long double> add(sl, 0);
        if (last != -1) {
            add[last] = last_value;
            tmp -= last_value;
        }
        for (int i = 0; i < sl; i++) add[i] += tmp / sl;
        cout << "POUR " << sl << ' ';
        for (int i = 0; i < sl; i++) {
            cout << i * k + 1 << " " << fixed << setprecision(10) << add[i] << ' ';
            ans[i] += add[i];
            last_value = ans[i];
        }
        cout << endl;
        int request;
        cin >> request;
        if (k == 1) last = request - 1;
        else {
            if (request % k == 1) last = request / k;
            else last = (request + k - 1) / k;
        }
        ans[last] = 0;
    };
    for (int i = 0; i < 1900; i++) ask1();
    //assert(abs(last_value - x) < EPS);
    vector<int> used(sl, 0);
    used[last] = 1;
    int d = 1;
    auto ask2 = [&]() {
        long double tmp = x;
        cout << "POUR " << sl - d << ' ';
        for (int i = 0; i < sl; i++) {
            if (used[i] == 0) {
                long double cost = tmp / (sl - d);
                cout << i * k + 1 << " " << fixed << setprecision(10) << cost << ' ';
                ans[i] += cost;
            }
        }
        cout << endl;
        int request;
        cin >> request;
        if (k == 1) last = request - 1;
        else {
            if (request % k == 1) last = request / k;
            else last = (request + k - 1) / k;
        }
        if (used[last] == 0) {
            d++;
            ans[last] = 0;
            used[last] = 1;
        }
    };
    for (int i = 0; i < 99 && (sl - d) > 1; i++) ask2();
    for (int i = 0; i < sl; i++) {
        if (used[i] == 0) {
            cout << "FINAL " << 1 << " " << i * k + 1 << " " << x << endl;
            return;
        }
    }
}

void solve() {
    int T;
    //cin >> T;
    T = 1;
    int TestCase = 0;
    while (T--) {
        TestCase += 1;
        //cout << "Case #" << TestCase << ":" << ' ';
        ///cout << "Case #" << TestCase << '\n';
        //cout << "Test " << TestCase << ": ";
        sol();
        //if (T) cout << '\n';
    }
}
int main(int argc,char *argv[]) {
    ///srand(time(nullptr));
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    //open_file();
    solve();
}
