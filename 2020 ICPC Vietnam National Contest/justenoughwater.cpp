#include <bits/stdc++.h>

using namespace std;

void doc() {
    #ifdef THEMIS
        freopen("solve.inp", "r", stdin);
        freopen("solve.out", "w", stdout);
    #endif
}

const int maxN = 1e3 + 100;
const int INF = 1e6 + 100;
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};

int stk[maxN];
long long s[maxN];
long long get(vector<int> &h) {
    int top = 0;
    int n = (int)h.size();
    s[0] = h[0];
    for (int i = 0; i < n; i++) {
        while (top >= 2 && h[stk[top - 1]] >= h[stk[top]] && h[stk[top]] < h[i]) top--;
        stk[++top] = i;
        if (i) s[i] = s[i - 1] + h[i];
    }
    long long res = 0;
    for (int i = 1; i < top; i++) {
        int mn = min(h[stk[i]], h[stk[i + 1]]);
        int dist = stk[i + 1] - stk[i] - 1;
        res += 1LL * mn * dist;
        long long sum = s[stk[i + 1] - 1] - s[stk[i]];
        res -= sum;
    }
    return res;
}

int n;
vector<int> h;
long long res = 0;
void vet(int i, int last) {
    if (last == 0) {
        res = max(res, get(h));
        return;
    }
    if (i == n - 1) {
        h[i] += last;
        res = max(res, get(h));
        h[i] -= last;
        return;
    }
    for (int val = 0; val <= last; val++) {
        h[i] += val;
        vet(i + 1, last - val);
        h[i] -= val;
    }
}
void sol() {
    int k;
    cin >> n >> k;
    h.resize(n);
    for (int i = 0; i < n; i++) cin >> h[i];
    vet(0, k);
    cout << res;
}

void solve() {
    int T;
    //cin >> T;
    T = 1;
    while (T--) {
        sol();
    }
}
int main(){
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    doc();
    solve();
}
