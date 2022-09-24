#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

using namespace std;

#define INP "input"
#define OUT "output"

/* some template */
template <typename T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& a) {
    out << (int)a.size() << '\n';
    for (const auto& v : a) out << v << ' ';
    out << endl;
    return out;
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const std::vector<vector<T> >& a) {
    out << (int)a.size() << '\n';
    for (const auto& v : a) {
        for (const auto& value : v) out << value << ' ';
        out << endl;
    }
    return out;
}

template <typename T>
std::istream& operator>>(std::istream& is, std::vector<T>& v) {
    for (auto& x : v) is >> x;
    return is;
}
/* end template */

const long long INF_LL = 1e18;
const int INF = 1e9 + 100;
const long double EPS = 1e-6;
const int BLOCK = 550;
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};

void open_file() {
#ifdef THEMIS
    freopen(INP ".txt", "r", stdin);
    freopen(OUT ".txt", "w", stdout);
#endif  // THEMIS
}

const int maxN = 1e6 + 100;
const int MOD = 1e9 + 7;
const int N = 1e5 + 5;

int n, a[N];
int l[N], r[N];

#define ll long long

bool umax(ll& a, ll b) {
    if (a < b) {
        a = b;
        return 1;
    }
    return 0;
}
void sol() {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    stack<int> stk;
    a[n + 1] = -1e9;
    for (int i = 1; i <= n + 1; ++i) {
        while (stk.size() && a[stk.top()] > a[i]) {
            r[stk.top()] = i - 1;
            stk.pop();
        }
        if (stk.size())
            l[i] = stk.top() + 1;
        else
            l[i] = 1;
        stk.push(i);
    }

    // for (int i = 1; i <= n; ++i) {
    //     cout << l[i] << ' ' << r[i] << '\n';
    // }
    ll ans = -1, lef = 1e18, rig = 1e18;
    for (int i = 1; i <= n; ++i) {
        if (umax(ans, (ll)(r[i] - l[i] + 1) * a[i])) {
            lef = l[i];
            rig = r[i];
        } else if (ans == (ll)(r[i] - l[i] + 1) * a[i] && lef > l[i]) {
            lef = l[i];
            rig = r[i];
        }
    }
    cout << lef << " " << rig << " " << ans;
}

void solve() {
    clock_t start, end;
    start = clock();
    int T = 1;
    // cin >> T;
    int TestCase = 0;
    while (T--) {
        TestCase += 1;
        cerr << "Processing test = " << TestCase << '\n';
        // cout << "Case #" << TestCase << ": ";
        sol();
        // if (T) cout << '\n';
    }
    end = clock();
    cerr << "Time = " << (double)(end - start) / (double)CLOCKS_PER_SEC << '\n';
}

int main(int argc, char* argv[]) {
    // srand(time(nullptr));
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);
    open_file();
    solve();
    return 0;
}
