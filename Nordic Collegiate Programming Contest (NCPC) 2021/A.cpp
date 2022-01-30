#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

using namespace std;

#define INP "input"
#define OUT "output"

const long long INF_LL = 1e18;
const int INF = 1e9 + 100;
const long double EPS = 1e-6;
const int BLOCK = 550;
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};

void open_file() {
    #ifdef THEMIS
        freopen(INP ".txt","r",stdin);
        freopen(OUT ".txt","w",stdout);
    #endif // THEMIS
}

const int maxN = 1e6 + 100;
const int MOD = 1e9 + 7;

template <typename T, class func = function<T(const T&, const T&)> >
struct SegmentTree {
public:
    SegmentTree(int _n, T _base, func _F) : F(_F), base(_base) {
        n = _n;
        IT = vector<T>(n * 4, _base);
    }
    void update(int idx, T val) {
        update(1, 0, n - 1, idx, val);
    }
    T get(int L, int R) {
        return get(1, 0, n - 1, L, R);
    }
private: 
    int n;
    vector<T> IT; 
    T base;
    func F;
    void update(int i, int L, int R, int u, T val) {
        if (L > u || R < u) return;
        if (L == R) {
            IT[i] = val;
            return;
        }
        int mid = (L + R) >> 1;
        update(i << 1, L, mid, u, val);
        update(i << 1 | 1, mid + 1, R, u, val);
        IT[i] = F(IT[i << 1], IT[i << 1 | 1]);
    }
    T get(int i, int L, int R, int u, int v) {
        if (L > v || R < u) return base;
        if (L >= u && R <= v) return IT[i];
        int mid = (L + R) >> 1;
        T left = get(i << 1, L, mid, u, v);
        T right = get(i << 1 | 1, mid + 1, R, u, v);
        return F(left, right);
    }
};

void sol1(vector<pair<long long, long long> > x, long long c, vector<long long> &ans) {
    sort(x.begin(), x.end());
    int n = (int)x.size();
    SegmentTree<long long> st(n, INF_LL, [&](long long a, long long b) {
        return min(a, b);
    });
    for (auto it : x) {
        long long value = it.first;
        long long idx = it.second;
        ans[idx] = max(ans[idx], value - c * idx - st.get(0, idx - 1));
        st.update(idx, value - c * idx);
    }
}
void sol2(vector<pair<long long, long long> > x, long long c, vector<long long> &ans) {
    sort(x.begin(), x.end(), greater<pair<long long, long long> >());
    int n = (int)x.size();
    SegmentTree<long long> st(n, -INF_LL, [&](long long a, long long b) {
        return max(a, b);
    });
    for (auto it : x) {
        long long value = it.first;
        long long idx = it.second;
        ans[idx] = max(ans[idx], -(value + c * idx) + st.get(0, idx - 1));
        st.update(idx, value + c * idx);
    }
}
void sol() {
    int n, c;
    cin >> n >> c;
    vector<pair<long long, long long> > x(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i].first;
        x[i].second = i;
    }
    vector<long long> ans(n, 0);
    sol1(x, c, ans);
    sol2(x, c, ans);
    for (int i = 0; i < n; i++) cout << ans[i] << ' ';
}

void solve() {
    int T = 1;
    //cin >> T;
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
