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

#define task "sol"
#define lb lower_bound
#define ub upper_bound
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define zs(v) ((ll)(v).size())
#define BIT(x, i) (((x) >> (i)) & 1)
#define CNTBIT __builtin_popcountll
#define ALL(v) (v).begin(), (v).end()
#define endl '\n'

typedef long double ld;
typedef long long ll;
typedef pair<ll, ll> pii;

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

const ll N = 1e6 + 5;
struct three {
    ll x, y, u, v;
};
ll n, m, k;
three a[N];
vector<ll> sx, sy;
ll f[1000][1000];

void update(ll x, ll y, ll u, ll v) {
    f[x][y]++;
    f[x][v + 1]--;
    f[u + 1][y]--;
    f[u + 1][v + 1]++;
}

void sol() {
    cin >> n >> m >> k;
    for (ll i = 1; i <= k; ++i) {
        cin >> a[i].x >> a[i].y >> a[i].u >> a[i].v;
        a[i].u += a[i].x;
        a[i].v += a[i].y;
        for (int d = -1; d <= 1; d++) {
            if (a[i].x + d >= 0 && a[i].x + d <= n) sx.pb(a[i].x + d);
            if (a[i].u + d >= 0 && a[i].u + d <= n) sx.pb(a[i].u + d);
            if (a[i].y + d >= 0 && a[i].y + d <= m) sy.pb(a[i].y + d);
            if (a[i].v + d >= 0 && a[i].v + d <= m) sy.pb(a[i].v + d);
        }
    }
    sx.pb(-1);
    sy.pb(-1);
    sort(ALL(sx));
    sx.resize(unique(ALL(sx)) - sx.begin());

    sort(ALL(sy));
    sy.resize(unique(ALL(sy)) - sy.begin());

    for (ll i = 1; i <= k; ++i) {
        a[i].x = lb(ALL(sx), a[i].x) - sx.begin();
        a[i].u = lb(ALL(sx), a[i].u) - sx.begin();
        a[i].y = lb(ALL(sy), a[i].y) - sy.begin();
        a[i].v = lb(ALL(sy), a[i].v) - sy.begin();
        update(a[i].x, a[i].y, a[i].u, a[i].v);
    }

    for (ll i = 1; i < (ll)sx.size(); ++i) {
        for (ll j = 1; j < (ll)sy.size(); ++j) {
            f[i][j] += f[i - 1][j] + f[i][j - 1] - f[i - 1][j - 1];
        }
    }

    ll ans1 = 0, ans2 = 1e18, ans3 = -1;
    for (ll i = 1; i < (ll)sx.size(); ++i) {
        for (ll j = 1; j < (ll)sy.size(); ++j) {
            if (f[i][j] & 1) {
                ans2 = min(ans2, (ll)sy[j] * (n + 1) + sx[i]);
            }
            if (f[i][j] & 1) {
                ans3 = max(ans3, (ll)sy[j] * (n + 1) + sx[i]);
            }
            if (f[i][j] & 1)
                ans1 += (ll)(sx[i] - sx[i - 1]) * (sy[j] - sy[j - 1]);
        }
    }
    cout << ans1 << ' ' << (ans2 == 1e18 ? -1 : ans2) << ' ' << ans3;
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
