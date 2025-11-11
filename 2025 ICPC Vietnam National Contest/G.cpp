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
const int MOD = 998244353;

class SegmentTree {
   private:
    vector<int> IT;
    int n;

    void update(int i, int L, int R, int u, int val) {
        if (L > u || R < u) return;
        IT[i] += val;
        if (L == R) {
            return;
        }
        int mid = (L + R) >> 1;
        update(i << 1, L, mid, u, val);
        update(i << 1 | 1, mid + 1, R, u, val);
    }

    int get(int i, int L, int R, int u, int v) {
        if (L > v || R < u) return 0;
        if (L >= u && R <= v) return IT[i];
        int mid = (L + R) >> 1;
        int left = get(i << 1, L, mid, u, v);
        int right = get(i << 1 | 1, mid + 1, R, u, v);
        return left + right;
    }

   public:
    SegmentTree(int _n = 1) {
        IT = vector<int>(_n * 4, 0);
        n = _n;
    }
    void update(int u, int val) {
        update(1, 1, n, u, val);
    }

    int get(int L, int R) {
        return get(1, 1, n, L, R);
    }
};

void sol() {
    int n, q;
    cin >> n >> q;
    SegmentTree count(n), sum(n);
    count.update(n, 1);
    sum.update(n, n);
    set<pair<int, pair<int, char>>> S;
    S.insert({0, {n - 1, 'A'}});

    auto update = [&](int l, int r, int val) {
        if (l > r) return;
        int k = r - l + 1;
        count.update(k, val);
        sum.update(k, val * k);
    };
    while (q--) {
        int t;
        cin >> t;
        if (t == 2) {
            int k;
            cin >> k;
            int s = sum.get(k + 1, n);
            int c = count.get(k + 1, n);
            cout << s - c * k << '\n';
            continue;
        }
        int l, r;
        cin >> l >> r;
        char c;
        cin >> c;
        // list all segment intersect [l, r]
        vector<pair<int, pair<int, char>>> segments;
        auto it = S.lower_bound({l, {-1, 'A'}});
        if (it != S.begin()) {
            it--;
        }
        while (it != S.end() && it->first <= r + 1) {
            segments.push_back(*it);
            it = S.erase(it);
        }
        for (int i = 0; i < segments.size(); i++) {
            update(segments[i].first, segments[i].second.first, -1);
        }
        vector<pair<int, pair<int, char>>> add_segments;
        // merge left
        if (segments[0].first < l) {
            add_segments.push_back({segments[0].first, {l - 1, segments[0].second.second}});
        }
        // merge origin
        add_segments.push_back({l, {r, c}});
        // merege right
        if (segments.back().second.first > r) {
            add_segments.push_back({r + 1, {segments.back().second.first, segments.back().second.second}});
        }
        for (int i = 0; i < add_segments.size(); ) {
            int j = i;
            while (j < add_segments.size() && add_segments[i].second.second == add_segments[j].second.second) j++;
            update(add_segments[i].first, add_segments[j - 1].second.first, 1);
            S.insert({add_segments[i].first, {add_segments[j - 1].second.first, add_segments[i].second.second}});
            i = j;
        }
    }
}

void solve() {
    clock_t start, end;
    start = clock();
    int T = 1;
    // cin >> T;
    int TestCase = 0;
    while (T--) {
        TestCase += 1;
        // cerr << "Processing test = " << TestCase << '\n';
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
