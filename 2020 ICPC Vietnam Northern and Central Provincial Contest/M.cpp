#pragma GCC diagnostic ignored "-Wunused-parameter"
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

using namespace std;

#define INP "solve"
#define OUT "solve"

const long long INF_LL = 8e18;
const int INF = 1e9 + 100;
const int MOD = 1e9 + 7;
const int Base = 311;
const double EPS = 1e-9;
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

const int maxN = 5e5 + 1000;

///IT Line: Max y = ax + b;
struct Line {
    ///y = a * x + b;
    long long a, b;
    Line(){};
    Line(long long _a, long long _b) {
        a = _a;
        b = _b;
    }
};

Line IT[maxN * 4];
vector<long long> realX;
long long get(Line L, int x) {
    if (L.a == 0 && L.b == 0) return -INF_LL;
    return L.a * realX[x] + L.b;
}
void update(int i, int L, int R, int u, int v, Line val) {
    if (L > v || R < u) return;
    int mid = (L + R) >> 1;
    if (L >= u && R <= v) {
        if (get(IT[i], L) >= get(val, L) && get(IT[i], R) >= get(val, R)) return;
        if (get(IT[i], L) <= get(val, L) && get(IT[i], R) <= get(val, R)) {
            IT[i] = val;
            return;
        }
        if (get(IT[i], L) >= get(val, L) && get(IT[i], mid) >= get(val, mid)) {
            update(i << 1 | 1, mid + 1, R, u, v, val);
            return;
        }
        if (get(IT[i], L) <= get(val, L) && get(IT[i], mid) <= get(val, mid)) {
            update(i << 1 | 1, mid + 1, R, u, v, IT[i]);
            IT[i] = val;
            return;
        }
        if (get(IT[i], mid + 1) >= get(val, mid + 1) && get(IT[i], R) >= get(val, R)) {
            update(i << 1, L, mid, u, v, val);
            return;
        }
        if (get(IT[i], mid + 1) <= get(val, mid + 1) && get(IT[i], R) <= get(val, R)) {
            update(i << 1, L, mid, u, v, IT[i]);
            IT[i] = val;
            return;
        }
    }
    update(i << 1, L, mid, u, v, val);
    update(i << 1 | 1, mid + 1, R, u, v, val);
}
long long get(int i, int L, int R, int x)
{
    if (L > x || R < x) return -INF_LL;
    if (L >= x && R <= x) return get(IT[i], x);
    int mid = (L + R) >> 1;
    long long left = get(i << 1, L, mid, x);
    long long right = get(i << 1 | 1, mid + 1, R, x);
    return max(max(left,right), get(IT[i], x));
}

long long S[maxN], T[maxN];
long long getF(vector<int> &a) {
    int n = (int)a.size();
    realX = vector<long long> {0};
    for (int i = 1; i <= n; i++) {
        S[i] = S[i - 1] + a[i - 1];
        T[i] = T[i - 1] + S[i];
        realX.push_back(S[i]);
    }
    sort(realX.begin(), realX.end());
    realX.resize(unique(realX.begin(), realX.end()) - realX.begin());
    int m = (int)realX.size();
    for (int i = 0; i < m * 4; i++) IT[i] = Line(0, 0);
    long long res = -INF_LL;
    for (int i = n; i >= 1; i--) {
        //T[j] - j * S(i - 1) - T(i - 1) + S(i - 1) * (i - 1)
        Line val(-i, T[i]);
        update(1, 0, m - 1, 0, m - 1, val);

        int x = lower_bound(realX.begin(), realX.end(), S[i - 1]) - realX.begin();
        long long cost = get(1, 0, m - 1, x);
        cost += S[i - 1] * (i - 1) - T[i - 1];
        res = max(res, cost);
    }
    return res;
}
void sol(){
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    //reverse(a.begin(), a.end());
    cout << getF(a);
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
        sol();
    }
}
int main(int argc,char *argv[]) {
    ///srand(time(nullptr));
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    open_file();
    solve();
}
