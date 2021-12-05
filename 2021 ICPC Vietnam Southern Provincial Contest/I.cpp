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

int IT[maxN * 4];
void update(int i, int L, int R, int u, int val) {
    if (L > u || R < u) return;
    if (L == R) {
        IT[i] = val;
        return;
    }
    int mid = (L + R) >> 1;
    update(i << 1, L, mid, u, val);
    update(i << 1 | 1, mid + 1, R, u, val);
    IT[i] = IT[i << 1] + IT[i << 1 | 1];
}

int get(int i, int L, int R, int u, int v) {
    if (L > v || R < u) return 0;
    if (L >= u && R <= v) return IT[i];
    int mid = (L + R) >> 1;
    int left = get(i << 1, L, mid, u, v);
    int right = get(i << 1 | 1, mid + 1, R, u, v);
    return left + right;
}

int a[maxN], id[maxN], w1[maxN], w2[maxN];
void sol() {
    int n;
    cin >> n;

    long long num = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        id[a[i]] = i;
        w1[i] = get(1, 1, n, a[i] + 1, n);
        num += w1[i];
        update(1, 1, n, a[i], 1);
    }
    for (int i = 1; i <= 4 * n; i++) IT[i] = 0;
    for (int i = n; i >= 1; i--) {
        w2[i] = get(1, 1, n, 1, a[i] - 1);
        update(1, 1, n, a[i], 1);
    }

    long long ans = num;
    for (int i = n; i >= 1; i--) {
        int idx = id[i];
        num -= w2[idx];
        ans = min(ans, num);
        num += w1[idx];
    }
    cout << ans;
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
