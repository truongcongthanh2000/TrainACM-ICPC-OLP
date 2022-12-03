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

void sol() {
    auto ask = [&](string s) {
        cout << "? " << s << endl;
        int n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++) cin >> a[i];
        sort(a.begin(), a.end());
        return a;
    };

    string all;
    for (int i = 0; i < 26; i++) all += char(i + 'a');
    vector<int> v_all = ask(all);
    int n = (int)v_all.size();

    vector<vector<int> > depth = {v_all};
    vector<pair<int, int> > cur = {{0, 25}};

    for (int i = 0; i < 5; i++) {
        vector<pair<int, int> > next;
        string s;
        for (auto [L, R] : cur) {
            if (L == R) continue;
            int mid = (L + R) >> 1;
            next.push_back({L, mid});
            for (int j = L; j <= mid; j++) s += char(j + 'a');
            next.push_back({mid + 1, R});
        }
        vector<int> v = ask(s);
        depth.push_back(v);

        swap(cur, next);
    }

    vector<int> ans(n, 0);
    function<void(int, int, int, vector<int>)> dfs = [&](int L, int R, int d, vector<int> cur) {
        if (L == R) {
            for (int x : cur) {
                ans[x - 1] = L;
            }
            return;
        }
        int mid = (L + R) >> 1;
        vector<int> next = depth[d + 1];

        vector<int> cur_L, cur_R;
        for (int x : cur) {
            if (binary_search(next.begin(), next.end(), x)) {
                cur_L.push_back(x);
            } else {
                cur_R.push_back(x);
            }
        }

        dfs(L, mid, d + 1, cur_L);
        dfs(mid + 1, R, d + 1, cur_R);
    };
    dfs(0, 25, 0, depth[0]);

    string result;
    for (int i = 0; i < n; i++) result += char(ans[i] + 'a');

    cout << "! " << result << endl;
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
