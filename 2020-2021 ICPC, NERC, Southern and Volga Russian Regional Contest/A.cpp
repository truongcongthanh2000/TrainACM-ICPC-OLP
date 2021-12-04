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

const int maxN = 3e5 + 100;

struct SegmentTree {
    int n;
    vector<int> IT;
    SegmentTree(int _n = 0) {
        n = _n;
        IT = vector<int>((n + 1) * 4, 0);
    }
    void update(int i, int L, int R, int u, int val) {
        if (L > u || R < u) return;
        if (L == R) {
            IT[i] = val;
            return;
        }
        int mid = (L + R) >> 1;
        update(i << 1, L, mid, u, val);
        update(i << 1 | 1, mid + 1, R, u, val);
        IT[i] = max(IT[i << 1], IT[i << 1 | 1]);
    }

    int get(int i, int L, int R, int u, int v) {
        if (L > v || R < u) return 0;
        if (L >= u && R <= v) return IT[i];
        int mid = (L + R) >> 1;
        int left = get(i << 1, L, mid, u, v);
        int right = get(i << 1 | 1, mid + 1, R, u, v);
        return max(left, right);
    }

};

void sol(){
    int n;
    cin >> n;
    vector<pair<int, int> > a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].first;
        a[i].second = i;
    }
    vector<int> left(n, -1);
    stack<int> stk;
    for (int i = 0; i < n; i++) {
        while ((int)stk.size() > 0 && a[stk.top()] <= a[i]) stk.pop();
        if ((int)stk.size() != 0) {
            left[i] = stk.top();
        }
        stk.push(i);
    }
    sort(a.begin(), a.end());

    SegmentTree st(n);
    for (auto [x, id] : a) {
        int dp = st.get(1, 0, n - 1, 0, id) + 1;
        if (left[id] != -1) dp = max(dp, st.get(1, 0, n - 1, 0, left[id] - 1) + 2);
        st.update(1, 0, n - 1, id, dp);
    }
    cout << st.IT[1] << '\n';
}

void solve() {
    clock_t begin = clock();
    int T;
    cin >> T;
    //T = 1;
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
