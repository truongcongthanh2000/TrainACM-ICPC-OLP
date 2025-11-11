#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
#include <immintrin.h>

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
std::ostream& operator<<(std::ostream& out, const std::vector<vector<T>>& a) {
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
const long double EPS = 1e-12;
const int BLOCK = 330;
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};

mt19937 rnd(chrono::system_clock::now().time_since_epoch().count());

const int maxN = 2e6 + 100;
const int MOD = 1e9 + 7;

void sol() {
    int n;
    cin >> n;
    vector<pair<int, long long>> a(n);
    for (int i = 0; i < n; i++) cin >> a[i].first >> a[i].second;
    sort(a.begin(), a.end(), greater<pair<int, int>>());
    int last = a[0].first;
    priority_queue<pair<int, long long>> Q;
    for (int i = 0; i < n; ) {
        int j = i;
        while (j < n && a[i].first == a[j].first) j++;
        for (int k = i; k < j; k++) {
            Q.push({a[k].second * 2 + 1, k});
        }
        int segment = a[i].first - (j == n ? 0 : a[j].first);
        int idx = Q.top().second; Q.pop();
        a[idx].second += segment;
        Q.push({a[idx].second * 2 + 1, idx});
        i = j;
    }
    long long ans = 0;
    for (int i = 0; i < n; i++) ans += a[i].second * a[i].second;
    cout << ans << '\n';
}

void solve() {
    clock_t start, end;
    start = clock();
    int T = 1;
    cin >> T;
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
    solve();
    return 0;
}
