#include <bits/stdc++.h>

using namespace std;

#define INP "solve"
#define OUT "solve"

const int QQ = 3e5 + 10;
const int maxN = 3e5 + 10;
const int maxA = 1e6 + 10;
const long long oo = 1e16;
const int INF = 1e9 + 100;
const int MOD = 1e9 + 7;
const int Base = 30;
const long double du = 1e-9;
const string YES = "YES";
const string NO = "NO";
mt19937 rnd(chrono::system_clock::now().time_since_epoch().count());
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};

void doc() {
    freopen(INP ".inp","r",stdin);
    freopen(OUT ".out","w",stdout);
}

int deg[maxN];
void sol() {
    int n;
    cin >> n;
    vector<int> a(n), c(n), h(n), id(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> c[i];
        h[i] = i;
    }
    sort(h.begin(), h.end(), [&](int i, int j) {
        if (a[i] != a[j]) return a[i] < a[j];
        return i < j;
    });
    map <int, set<int> > Used;
    for (int i = 0; i < n; i++) Used[c[i]].insert(i);
    for (int i = 0; i < n; i++) {
        int p = h[i];
        auto it = Used[c[p]].lower_bound(i);
        if (it != Used[c[p]].end() && *it < p) {
            cout << "NO";
            return;
        }
        Used[c[p]].erase(p);
    }
    cout << "YES";
}

void solve() {
    int T;
    ///cin >> T;
    T = 1;
    int TestCase = 0;
    while (T--) {
        TestCase += 1;
        ///cout << "Case #" << TestCase << ": ";
        sol();
    }
}

int main(int argc,char *argv[]) {
    srand(time(nullptr));
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    ///doc();
    solve();
}
